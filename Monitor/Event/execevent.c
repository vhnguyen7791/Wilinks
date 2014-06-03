/*========================================================================*/
/* NOM DU FICHIER  : execevent.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: gestion du statut des évènements			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source SDVB200 - BE373)
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Modification struture de la gestion interne des évènements
// - Ajout gestion des alarmes
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
//BE051 13/12/2010 CM
// - Incohérence horodatage de l'action suppression jdb et de l'évènement
// - Probleme horodatage de l'évènement JDB lors d'un RAZ général
//BE058 21/01/2011 CM
// - Ajout champs info_sup1 dans gestion trap
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère le statut des évènements

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECEVENT		1

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u8sod	u8_ordreMntr_RAZ_Trap;
static u8sod	u8_flag_signal_RAZ_JDB;
static u8sod	u8_flag_signal_RAZ_TRAP;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: OrdreMntr_RAZ_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Ordre de raz des traps
//=====================================================================================
void OrdreMntr_RAZ_Trap(void)
{
	u8_ordreMntr_RAZ_Trap = TRUE;
}/*OrdreMntr_RAZ_Trap*/

//=====================================================================================
// Fonction		: GestionExecEvent
// Entrees		: <loc_ps_exp_events< : pointeur sur base de données exploit des évènements à mettre à jour
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Gestion à la seconde du statut des évènements
//=====================================================================================
void GestionExecEvent(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events)
{
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_encours;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_precedent;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_suivant;
	u16sod	loc_u16_i;
	u16sod	loc_u16_index_evt;
	u16sod	loc_u16_cpt;
//	printf("debut: GestionExecEvent\n");

	loc_u16_cpt = 0;	//INIT

	//RAZ des alarmes mémorisées
	if((TRUE == s_cip_monitor_courant.u8_raz_alarmes_memorisees)||
	   ((TRUE == s_cip_monitor_courant.u8_raz_general)&&(TRUE == s_cip_monitor_courant.u8_raz_jdb))
	  ) //CONDTION: (raz des alarmes mémorisées) ou (raz général avec info raz jdb effectué)
	{
		s_cip_monitor_courant.u8_raz_alarmes_memorisees = FALSE; //RAZ
		RazAllAlarmesMemorisees();
		//On horodate le reset des alarmes mémorisées
		SetDate(&loc_ps_exp_events->s_date_dernier_reset, METHODE_SETDATE_MANUEL); //MAJ
		RegisterEvent(EVT111_INF_RAZ_ALARMES_MEMO,0, 0, 0, NULL, 0, ETAT_EVT_INFO);
	}

	
	//On controle le fichier fifojdb
	Start_CipFifoJdb();	
	
	//On controle le fichier fifotrap
	Start_CipFifoTrap();
	
	//On signale un RAZ du JDB
	if(TRUE == s_cip_monitor_courant.u8_raz_jdb)
	{
		u8_flag_signal_RAZ_JDB = TRUE;
		RegisterEvent(EVT110_JOURNAL_BORD_EFFACE,0, 0, 0, NULL, 0, ETAT_EVT_INFO);
	}
	else
	{
		u8_flag_signal_RAZ_JDB = FALSE;
	}

	if(TRUE  == u8_ordreMntr_RAZ_Trap) //CONDITION: ordre du raz des traps
	{
		u8_flag_signal_RAZ_TRAP = TRUE;
		//On acquitte
		u8_ordreMntr_RAZ_Trap = FALSE; //RAZ
	}
	else
	{
		u8_flag_signal_RAZ_TRAP = FALSE;
	}
	
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if((EVT000_AL_SYNTHESE_1 == loc_u16_i)
		  ) //CONDITION: alarmes de synhèse
		{
			;	//on ne fait rien pour l'instant
		}
		else //CONDITION: autres alarmes
		{
			loc_u16_index_evt = loc_u16_i;
			
			if(TRUE == u8TestEvenementValide(loc_u16_index_evt))
			{
				if(V_NO_ACTION != pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action) //CONDITION: evt avec valeur
				{
					if(NULL != ps_internal_event[loc_u16_index_evt].ps_next) //CONDITION: premiere valeur de l'évt
					{
						loc_ps_precedent = &ps_internal_event[loc_u16_index_evt]; //INIT
						loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS	*)ps_internal_event[loc_u16_index_evt].ps_next; // INIT
						loc_u16_cpt = 0; //INIT
						while( (NULL != loc_ps_encours) && (loc_u16_cpt<NB_MAX_INTERNAL_EVENTS))
						{
							MajEtatEvent(loc_ps_encours);

							loc_ps_suivant = (S_STRUCT_INTERNAL_EVENTS	*)loc_ps_encours->ps_next;

							if(FALSE == u8GetU8EtatBit(loc_ps_encours->s_statut.u8_etat_evt, BIT4_FLAG_MESURE_CALCULEE)) //CONDITION: alarme non calculée ou evt de type info
							{
//								printf("GestionExecEvent: Suppression evt %d,%d \n",
//									   loc_u16_index_evt,
//									   loc_ps_encours->u16_valeur_evt);

								//on supprime l'evt de la liste
								loc_ps_precedent->ps_next = loc_ps_encours->ps_next;
								InitInternalEvent(loc_ps_encours);
								//Ici, le précédent reste identique
							}
							else
							{
								ResetU8EtatBit(&loc_ps_encours->s_statut.u8_etat_evt, BIT4_FLAG_MESURE_CALCULEE);
								//on mémorise le précédent
								loc_ps_precedent = loc_ps_encours;
							}

							//On passe au suivant
							loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)loc_ps_suivant;
							loc_u16_cpt++;
						};
					}

					//Puis on gère la synthèse de l'evt type
					MajEtatEvent(&ps_internal_event[loc_u16_index_evt]);
					//Et on signale que la gestion de la synthèse est terminée
					ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt, BIT4_FLAG_MESURE_CALCULEE);
				}
				else //CONDITION: evt sans valeur
				{
					MajEtatEvent(&ps_internal_event[loc_u16_index_evt]);
				}
			}
		}
	}

	//Gestion des alarmes de synthèse
	MajEtatEvent(&ps_internal_event[EVT000_AL_SYNTHESE_1]);


	
	//Mise à jour des données d'exploitation des évènements
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_ps_exp_events->ps_statut[loc_u16_i] = ps_internal_event[loc_u16_i].s_statut; //MAJ
	}
	
	//On acquitte le signal de RAZ TRAP
	u8_flag_signal_RAZ_JDB = FALSE;	//RAZ
	u8_flag_signal_RAZ_TRAP = FALSE;	//RAZ
	
//	printf("fin: GestionExecEvent\n");
	
}/*GestionExecEvent*/

//=====================================================================================
// Fonction		: MajEtatEvent
// Entrees		: <loc_ps_intern_evt< : pointeur sur statut d'un evt
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Mise à jour de l'état de l'évènement
//=====================================================================================
void MajEtatEvent(S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt)
{
	u8sod   loc_u8_evolution_config_valid_evt;
	u8sod	loc_u8_etatEvt_encours;
	u8sod	loc_u8_etatEvt_prec_JDB;
	u8sod	loc_u8_etatEvt_prec_TRAP;
	u16sod	loc_u16_index_evt;
	u8sod	loc_u8_evt_a_valeur;
	T_SIZE_VALEUR_EVT loc_t_valeur_evt_jdb; //valeur pour jdb
	T_SIZE_VALEUR_EVT loc_t_valeur_evt_trap; //valeur pour trap

	loc_u8_evolution_config_valid_evt = FALSE;
	loc_u8_etatEvt_encours = ETAT_EVT_FIN;	//INIT
	loc_u8_etatEvt_prec_JDB = ETAT_EVT_FIN;	//INIT
	loc_u8_etatEvt_prec_TRAP = ETAT_EVT_FIN;	//INIT
	loc_u8_evt_a_valeur = TRUE;	//INIT
	loc_t_valeur_evt_jdb = 0; //INIT
	loc_t_valeur_evt_trap = 0; //INIT

//	printf("MajEtatEvent: %d,%d (%d) \n",
//		   loc_ps_intern_evt->s_statut.u16_index_evt,
//		   loc_ps_intern_evt->s_statut.u16_valeur_evt,
//		   loc_ps_intern_evt->s_statut.u8_etat_evt);
		   

	loc_u16_index_evt = loc_ps_intern_evt->s_statut.u16_index_evt; //INIT

	if(&ps_internal_event[loc_u16_index_evt] == loc_ps_intern_evt) //CONDITION: evt de synthèse
	{
		loc_u8_evt_a_valeur = FALSE;
	}

	switch(S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_index_evt].u8_type_evt)
	{
		case TYPE_EVT_ALARME:
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_syst_evt, BIT1_SYST_COPIE_CFG_VALID))
			{ //CONDITION: config evt validé dans la seconde précédente
				if(FALSE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_VALIDE))
					//CONDITION: config evt dévalidé
				{
					loc_u8_evolution_config_valid_evt = TRUE; //on est passé de ON à OFF
				}
			}
			//Mise à jour de la config Validation
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_syst_evt, BIT0_SYST_EVT_USED)) //CONDITION: evt utilisé
			{
				if(TRUE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_VALIDE))
				//CONDITION: config evt validée
				{
					SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT7_ETAT_CFG_VALID);
					SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_syst_evt,BIT1_SYST_COPIE_CFG_VALID);
				}
				else
				{
					ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT7_ETAT_CFG_VALID);
					ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_syst_evt,BIT1_SYST_COPIE_CFG_VALID);
				}
			}
			else
			{
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT7_ETAT_CFG_VALID);
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_syst_evt,BIT1_SYST_COPIE_CFG_VALID);
			}
			
			//Gestion de l'alarme réel
			//Si l'alarme n'a pas été calculée, c'est qu'elle est à OFF réellement
			//sinon c'est que son état réel a bien été renseigné
			if(FALSE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt,BIT4_FLAG_MESURE_CALCULEE)) //CONDITION: pas encore calculé
			{
				ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT1_ETAT_REEL);
			}
			
			//on copie état seconde précédente (JDB) = état seconde courante (JDB)
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt, BIT5_ETAT_COURANT_POUR_JDB))
			{
				loc_u8_etatEvt_prec_JDB = ETAT_EVT_DEBUT;
			}
			else
			{
				loc_u8_etatEvt_prec_JDB = ETAT_EVT_FIN;
			}

			//on copie état seconde précédente (TRAP) = état seconde courante (TRAP)
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt, BIT6_ETAT_COURANT_POUR_TRAP))
			{
				loc_u8_etatEvt_prec_TRAP = ETAT_EVT_DEBUT;
			}
			else
			{
				loc_u8_etatEvt_prec_TRAP = ETAT_EVT_FIN;
			}
			
			//on copie état seconde courante = état dans la seconde (mesuré)
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt, BIT3_ETAT_MESURE))
			{
				loc_u8_etatEvt_encours = ETAT_EVT_DEBUT;
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT0_ETAT_COURANT);
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT5_ETAT_COURANT_POUR_JDB);
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT6_ETAT_COURANT_POUR_TRAP);
			}
			else
			{
				loc_u8_etatEvt_encours = ETAT_EVT_FIN;
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT0_ETAT_COURANT);
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT5_ETAT_COURANT_POUR_JDB);
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT6_ETAT_COURANT_POUR_TRAP);
			}

			//gestion état mémorisé
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt, BIT0_ETAT_COURANT))
			{
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT2_ETAT_MEMORISE);
			}

			//Gestion des conditions de la configuration des évènements
			//(Générale)
			if(		(FALSE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt, BIT7_ETAT_CFG_VALID))
				||	(FALSE == u8TestEventDisponible(loc_u16_index_evt))
			  )//CONDITION: CONFIG validation evt non validé OU évènement INDISPONIBLE
			{
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT0_ETAT_COURANT);
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT2_ETAT_MEMORISE);
				//On raz l'état courante tout de suite comme ça c'est fait
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT5_ETAT_COURANT_POUR_JDB);
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT6_ETAT_COURANT_POUR_TRAP);
				//on force la fin de l'alarme
				loc_u8_etatEvt_encours = ETAT_EVT_FIN;
			}

			//Gestion des conditions de la configuration des évènements
			//(JDB)
			if(	(FALSE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_JDB))
				&& (FALSE == loc_u8_evolution_config_valid_evt)
			  )
			 	//CONDITION: config JDB dévalidée ET pas d'évolution valid evt
			{
				//on raz l'état précédent du JDB
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT5_ETAT_COURANT_POUR_JDB);
				loc_u8_etatEvt_prec_JDB = ETAT_EVT_FIN;
			}

			//Gestion des conditions de la configuration des évènements
			//(TRAP)
			if( (FALSE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_TRAP))
				&& (FALSE == loc_u8_evolution_config_valid_evt)
			 )
			//CONDITION: RAZ TRAP demandé ou config TRAP dévalidée
			{
				//on raz l'état précédent du TRAP
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT6_ETAT_COURANT_POUR_TRAP);
				loc_u8_etatEvt_prec_TRAP = ETAT_EVT_FIN;
			}

			
			//Gestion du RAZ JDB
			if(TRUE == u8_flag_signal_RAZ_JDB)	//CONDITION: RAZ JDB demandé
			{
				//on raz l'état précédent du JDB
				//pour que les alarmes (si elles sont présentes) soient enregistrées dans la seconde précédente
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT5_ETAT_COURANT_POUR_JDB);
				loc_u8_etatEvt_prec_JDB = ETAT_EVT_FIN;
			}

			//Gestion du RAZ TRAP
			if(TRUE == u8_flag_signal_RAZ_TRAP)	//CONDITION: RAZ TRAP demandé
			{
				//on raz l'état précédent du TRAP
				loc_u8_etatEvt_prec_TRAP = ETAT_EVT_FIN;
			}

			//RAZ état mesuré (acquittement)
			ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT3_ETAT_MESURE);

//d: DEBUG suivi evènement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
			if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
			{
				printf("MajEtatEvent:(%d,%lu) statEvent=%02X / systEvent=%02X %d (%d,%02X) jdb=%d, trap=%d, evolution=%d\n",
					   loc_u16_index_evt,loc_ps_intern_evt->s_statut.t_valeur_evt,
					   loc_ps_intern_evt->s_statut.u8_etat_evt,
					   loc_ps_intern_evt->s_statut.u8_syst_evt,
					   loc_u8_etatEvt_encours,
					   loc_u8_evt_a_valeur,pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action,
					   loc_u8_etatEvt_prec_JDB,loc_u8_etatEvt_prec_TRAP,loc_u8_evolution_config_valid_evt);
			}
#endif
//f: DEBUG suivi evènement dans la gestion
			
			//jdb
			if(	(loc_u8_etatEvt_prec_JDB != loc_u8_etatEvt_encours) &&
				(FALSE == u8_flag_signal_RAZ_JDB)
			  )	  //CONDITION: différence d'état ET pas de RAZ du JDB en cours
			{
				if(		(	(TRUE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_JDB))
							|| 	(TRUE == loc_u8_evolution_config_valid_evt)
					)	&&
						(	((TRUE == loc_u8_evt_a_valeur) && (V_JDB == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_JDB)))
						||	((FALSE == loc_u8_evt_a_valeur) && (0 == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_JDB)))
						)
				  ) //CONDITION: autorisation d'enregistrer dans JDB
				{
					loc_t_valeur_evt_jdb = tConvertValeurToJdb(loc_u16_index_evt, loc_ps_intern_evt->s_statut.t_valeur_evt);
					EnregistreJdb(loc_u16_index_evt,
								  loc_t_valeur_evt_jdb,
								  loc_ps_intern_evt->s_statut.u_info_sup1.u32_term,
								  loc_ps_intern_evt->s_statut.u8_info_sup2,
								  loc_ps_intern_evt->s_statut.pu8_tab_info_sup3,
								  loc_u8_etatEvt_encours);
					
//d: DEBUG suivi evènement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
					if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
					{
						printf("EnregistreJdb(%d,%lu=>%lu) %d\n",
							   loc_u16_index_evt,
							   loc_ps_intern_evt->s_statut.t_valeur_evt,
							   loc_t_valeur_evt_jdb,
							   loc_u8_etatEvt_encours);
					}
#endif
//f: DEBUG suivi evènement dans la gestion
				}
			}

			//trap
			if(loc_u8_etatEvt_prec_TRAP != loc_u8_etatEvt_encours) //CONDITION: différence d'état
			{
				if(		(	(TRUE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_TRAP))
						|| 	(TRUE == loc_u8_evolution_config_valid_evt)
				    )	&&
						(	((TRUE == loc_u8_evt_a_valeur) && (V_TRAP == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_TRAP)))
						||	((FALSE == loc_u8_evt_a_valeur) && (0 == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_TRAP)))
						)
				  ) //CONDITION: autorisation d'enregistrer TRAP
				{
					loc_t_valeur_evt_trap = tConvertValeurToTrap(loc_u16_index_evt, loc_ps_intern_evt->s_statut.t_valeur_evt);
					EnregistreTrap(loc_u16_index_evt,
								   loc_t_valeur_evt_trap,
								   loc_ps_intern_evt->s_statut.u_info_sup1.u32_term,
								   loc_ps_intern_evt->s_statut.u8_info_sup2,
								   loc_ps_intern_evt->s_statut.pu8_tab_info_sup3,
								   loc_u8_etatEvt_encours);
					
//d: DEBUG suivi evènement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
					if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
					{
						printf("EnregistreTrap(%d,%lu=>%lu): %d\n",
							   loc_u16_index_evt,
							   loc_ps_intern_evt->s_statut.t_valeur_evt,
							   loc_t_valeur_evt_trap,
							   loc_u8_etatEvt_encours);
					}
#endif
//f: DEBUG suivi evènement dans la gestion
				}
			}

			//Calcul des alarmes de synthèse 
			if(FALSE == loc_u8_evt_a_valeur)
			{
				if((EVT000_AL_SYNTHESE_1 != loc_u16_index_evt)
				  ) //CONDITION: différent de alarmes de synhèse
				{
					if(TRUE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_SYNTHESE_1))
					{
						if(ETAT_EVT_DEBUT == loc_u8_etatEvt_encours)
						{
							SetU8EtatBit(&ps_internal_event[ACTION_EVT_SYNTHESE_1].s_statut.u8_etat_evt,BIT3_ETAT_MESURE);
						}

					}
				}
			}
			
			break;
		case TYPE_EVT_INFO:
			if(TRUE == u8GetU8EtatBit(loc_ps_intern_evt->s_statut.u8_etat_evt, BIT3_ETAT_MESURE))
			{
				//RAZ état mesuré (acquittement)
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt, BIT3_ETAT_MESURE);

//d: DEBUG suivi evènement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
				if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
				{
					printf("MajEtatEvent:(%d,%lu) statEvent=%02X (INFO)\n",
						   loc_u16_index_evt,loc_ps_intern_evt->s_statut.t_valeur_evt,
						   loc_ps_intern_evt->s_statut.u8_etat_evt);
				}
#endif
//f: DEBUG suivi evènement dans la gestion
				
				//jdb
				if(		(TRUE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_JDB))
					&&	(	((TRUE == loc_u8_evt_a_valeur) && (V_JDB == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_JDB)))
						||	((FALSE == loc_u8_evt_a_valeur) && (0 == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_JDB)))
						)
				  ) //CONDITION: autorisation d'enregistrer dans JDB
				{
					loc_t_valeur_evt_jdb = tConvertValeurToJdb(loc_u16_index_evt, loc_ps_intern_evt->s_statut.t_valeur_evt);
					EnregistreJdb(loc_u16_index_evt,
								  loc_t_valeur_evt_jdb,
								  loc_ps_intern_evt->s_statut.u_info_sup1.u32_term,
								  loc_ps_intern_evt->s_statut.u8_info_sup2,
								  loc_ps_intern_evt->s_statut.pu8_tab_info_sup3,
								  ETAT_EVT_INFO);
					
//d: DEBUG suivi evènement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
					if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
					{
						printf("EnregistreJdb(%d,%lu=>%lu) (INFO)\n",
							   loc_u16_index_evt,
							   loc_ps_intern_evt->s_statut.t_valeur_evt,
							   loc_t_valeur_evt_jdb);
					}
#endif
//f: DEBUG suivi evènement dans la gestion
				}

				//trap
				if(		(TRUE == u8GetEventAction(s_config_process_mntr.s_tabevt.s_event[loc_u16_index_evt].u16_action, ACTION_EVT_TRAP))
					&&	(	((TRUE == loc_u8_evt_a_valeur) && (V_TRAP == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_TRAP)))
						||	((FALSE == loc_u8_evt_a_valeur) && (0 == (pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_TRAP)))
						)
				  ) //CONDITION: autorisation d'enregistrer TRAP
				{
					loc_t_valeur_evt_trap = tConvertValeurToTrap(loc_u16_index_evt, loc_ps_intern_evt->s_statut.t_valeur_evt);
					EnregistreTrap(loc_u16_index_evt,
								   loc_t_valeur_evt_trap,
								   loc_ps_intern_evt->s_statut.u_info_sup1.u32_term,
								   loc_ps_intern_evt->s_statut.u8_info_sup2,
								   loc_ps_intern_evt->s_statut.pu8_tab_info_sup3,
								   ETAT_EVT_INFO);
//d: DEBUG suivi evènement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
					if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
					{
						printf("EnregistreTrap(%d,%lu=>%lu) (INFO)\n",
							   loc_u16_index_evt,
							   loc_ps_intern_evt->s_statut.t_valeur_evt,
							   loc_t_valeur_evt_trap);
					}
#endif
//f: DEBUG suivi evènement dans la gestion
				}
			}
			break;
		default:
			break;
	}
}/*MajEtatEvent*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecEvent
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Initialisation du module de ExecEvent
//=====================================================================================
void InitModule_ExecEvent(void)
{
	u8_ordreMntr_RAZ_Trap = FALSE;		//INIT
	
	u8_flag_signal_RAZ_JDB = FALSE;		//INIT
	u8_flag_signal_RAZ_TRAP = FALSE;	//INIT
	
}/*InitModule_ExecEvent*/

