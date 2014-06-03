/*========================================================================*/
/* NOM DU FICHIER  : internevent.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: gestion interne des �v�nements			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source BE373 - SDVB200)
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE016 11/03/2010 CM
// - Modification struture de la gestion interne des �v�nements
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _INTERNEVENT

#define IDX_INTERNEVENT_INDISPONIBLE	0xFFFF

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

#define DBG_INTERNEVENT	printf	//MACRO_PRINTF

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//d: DEBUG suivi ev�nement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
const s8sod PS8_MSG_ETAT_EVENT[NB_MAX_ETATS_EVENT][20] =
{
	"DEBUT",	//ETAT_EVT_DEBUT
	"FIN",		//ETAT_EVT_FIN
	"INFO",		//ETAT_EVT_INFO
};
#endif

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: RazOneAlarmeMemorisee
// Entrees		: <loc_u16_index_evt> : index de l'evt
// Sortie		: <loc_u8_etat>
// Auteur		: CM - 13/02/2009 -
// Description	: Raz de l'alarme m�moris�e
//=====================================================================================
void RazOneAlarmeMemorisee(u16sod loc_u16_index_evt)
{
	u16sod	loc_u16_cpt;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_encours;

	if(loc_u16_index_evt < NB_MAX_EVENEMENTS)
	{
		if(NULL != ps_internal_event[loc_u16_index_evt].ps_next) //CONDITION: premiere valeur de l'�vt
		{
			loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)ps_internal_event[loc_u16_index_evt].ps_next; // INIT
			loc_u16_cpt = 0; //INIT
			while( (NULL != loc_ps_encours) && (loc_u16_cpt<NB_MAX_INTERNAL_EVENTS))
			{
				ResetU8EtatBit(&loc_ps_encours->s_statut.u8_etat_evt, BIT2_ETAT_MEMORISE);

				//On passe au suivant
				loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)loc_ps_encours->ps_next;
				loc_u16_cpt++;
			};
		}

		ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt, BIT2_ETAT_MEMORISE);
	}
}/*RazOneAlarmeMemorisee*/

//=====================================================================================
// Fonction		: RazAllAlarmesMemorisees
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: RAZ de toutes les alarmes m�moris�es
//=====================================================================================
void RazAllAlarmesMemorisees(void)
{
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;
	u8sod	loc_u8_raz_autorisee;
	u8sod	loc_u8_index_groupe;

	loc_u8_raz_autorisee = FALSE;	//INIT
	loc_u8_index_groupe = 0;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))
		{
			loc_u8_raz_autorisee = FALSE; //RAZ
			loc_u8_index_groupe = S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_groupe;
			switch(loc_u8_index_groupe)
			{
				default:
					loc_u8_raz_autorisee = TRUE;
					break;
			}
			
			if(TRUE == loc_u8_raz_autorisee) //CONDITION: RAZ autoris�e
			{
				RazOneAlarmeMemorisee(loc_u16_indEvt);

			}
		}
	}
	
}/*RazAllAlarmesMemorisees*/

//=====================================================================================
// Fonction		: RazGroupeAlarmesMemorisees
// Entrees		: <loc_u16_indice_groupe>
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: RAZ des alarmes du groupe
//=====================================================================================
void RazGroupeAlarmesMemorisees(u16sod loc_u16_indice_groupe)
{
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;

	switch(loc_u16_indice_groupe)
	{
		default:
			for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
			{
				loc_u16_indEvt = loc_u16_i;
				if(TRUE == u8TestEvenementValide(loc_u16_indEvt))
				{
					if(loc_u16_indice_groupe == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_groupe)
					{
						RazOneAlarmeMemorisee(loc_u16_indEvt);
					}
				}
			}
			break;
	}
	
}/*RazGroupeAlarmesMemorisees*/

//=====================================================================================
// Fonction		: MiseAJourConfigToAllStateEvt
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: Mise � jour de la config de toutes les alarmes
//=====================================================================================
void MiseAJourConfigToAllStateEvt(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{
			MiseAJourConfigToStateEvt(loc_u16_indEvt, &loc_ps_config->s_tabevt.s_event[loc_u16_indEvt]);
		}
	}

}/*MiseAJourConfigToAllStateEvt*/

//=====================================================================================
// Fonction		: MiseAJourConfigToStateEvt
// Entrees		: <loc_u16_IndiceEvt> : indice de l'�v�nement
//				  >loc_ps_cfg_evt<	: structure concernant la configuration de l'�v�nement
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: Mise � jour de la config des alarmes
//=====================================================================================
void MiseAJourConfigToStateEvt(u16sod loc_u16_IndiceEvt,S_STRUCT_CFG_EVENT *loc_ps_cfg_evt)
{
	//validation
	if(TRUE == u8GetEventAction(loc_ps_cfg_evt->u16_action, ACTION_EVT_VALIDE))
	{
		SetU8EtatBit(&ps_internal_event[loc_u16_IndiceEvt].s_statut.u8_etat_evt, BIT7_ETAT_CFG_VALID);
	}
	else
	{
		ResetU8EtatBit(&ps_internal_event[loc_u16_IndiceEvt].s_statut.u8_etat_evt, BIT7_ETAT_CFG_VALID);
	}

}/*MiseAJourConfigToStateEvt*/

//=====================================================================================
// Fonction		: u8GetStatEventMask
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  <loc_t_mask_valeur_evt>  : masque binaire valeur de l'�vt
//				  >loc_pps_stat_event_retourne< : adresse du nouveau pointeur
// Sortie		: <loc_u8_trouve> : TRUE si trouv�, sinon FALSE
// Auteur		: CM - 23/04/2009 -
// Description	: retourne le statut de l'�vt associ� au couple (index, valeur) avec valeur Masqu�e
//=====================================================================================
u8sod u8GetStatEventMask(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, T_SIZE_VALEUR_EVT loc_t_mask_valeur_evt, S_STRUCT_INTERNAL_EVENTS **loc_pps_stat_event_retourne)
{
	u8sod loc_u8_trouve;
	u16sod loc_u16_cpt;
	S_STRUCT_INTERNAL_EVENTS *loc_ps_encours;

	loc_u8_trouve = FALSE; //INIT

	if(V_NO_ACTION != pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action) //CONDITION: evt � valeurs
	{
		if(NULL != ps_internal_event[loc_u16_index_evt].ps_next) //CONDITION: premiere valeur de l'�vt
		{
			loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)ps_internal_event[loc_u16_index_evt].ps_next; // INIT
			loc_u16_cpt = 0; //INIT
			while( (NULL != loc_ps_encours) && (loc_u16_cpt<NB_MAX_INTERNAL_EVENTS))
			{
				if((loc_t_valeur_evt & loc_t_mask_valeur_evt) == (loc_ps_encours->s_statut.t_valeur_evt & loc_t_mask_valeur_evt))//CONDITION: evt trouv�
				{
					*loc_pps_stat_event_retourne = loc_ps_encours;
					loc_u8_trouve = TRUE; //TROUVE
					loc_u16_cpt = NB_MAX_INTERNAL_EVENTS; //on sort
				}

				//On passe au suivant
				loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)loc_ps_encours->ps_next;
				loc_u16_cpt++;
			};
		}
	}
	else	//CONDITION: sans valeur
	{
		loc_ps_encours = &ps_internal_event[loc_u16_index_evt];
		if((loc_t_valeur_evt & loc_t_mask_valeur_evt) == (loc_ps_encours->s_statut.t_valeur_evt & loc_t_mask_valeur_evt))//CONDITION: evt trouv�
		{
			*loc_pps_stat_event_retourne = loc_ps_encours;
			loc_u8_trouve = TRUE; //TROUVE
		}
	}

	return loc_u8_trouve;
}/*u8GetStatEventCoupleMasquee*/

//=====================================================================================
// Fonction		: u16SearchFreeLstStatusEvent
// Entrees		: rien
// Sortie		: <loc_u16_index>
// Auteur		: CM - 03/10/2007 -
// Description	: recherche dans s_statevent[] une position disponible
//					dans la zone dynamique
//=====================================================================================
u16sod u16SearchFreeLstStatusEvent(void)
{
	u16sod	loc_u16_index;
	u16sod	loc_u16_i;

	loc_u16_index = IDX_INTERNEVENT_INDISPONIBLE; //INIT

	//Recherche dans la zone dynamique
	for(loc_u16_i=NB_MAX_EVENEMENTS;loc_u16_i<NB_MAX_INTERNAL_EVENTS;loc_u16_i++)
	{
		if(NUM_EVT_INTERDIT == ps_internal_event[loc_u16_i].s_statut.u16_index_evt) //CONDITION: m�moire disponible
		{
			loc_u16_index = loc_u16_i;	//trouv�
			loc_u16_i = NB_MAX_INTERNAL_EVENTS+1;	//on sort
		}
	}

	return loc_u16_index;
}/*u16SearchFreeLstStatusEvent*/

//=====================================================================================
// Fonction		: u8AddLst_StatusEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  <loc_u32_info1>	  : info 1
//				  <loc_u8_info2>	  : info 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u16_sizeinfo3>  : taille du tableau d�fini par info 3
//				  >loc_pps_stat_event_retourne< : adresse du nouveau pointeur
// Sortie		: <loc_u8_result> : TRUE si ajout r�ussi, sinon FALSE
// Auteur		: CM - 10/03/2007 -
// Description	: Ajout evt (index,valeur) � la liste chain�e (par
// ordre croissante sur valeur evt)
//=====================================================================================
u8sod u8AddLst_StatusEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info1, u8sod loc_u8_info2, u8sod *loc_pu8_info3, u16sod loc_u16_sizeinfo3, S_STRUCT_INTERNAL_EVENTS **loc_pps_stat_event_retourne)
{
	u8sod						loc_u8_result;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_encours;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_trouve;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_precedent;
	u16sod				loc_u16_cpt;
	u16sod				loc_u16_idx_dispo;

	loc_ps_precedent = NULL;	//INIT
	loc_u8_result = TRUE;		//INIT

	loc_u16_idx_dispo = u16SearchFreeLstStatusEvent();

	if(V_NO_ACTION != pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action) //CONDITION: uniquement pour les �vts � valeurs
	{
		if(IDX_INTERNEVENT_INDISPONIBLE != loc_u16_idx_dispo) //CONDITION: m�moire disponible
		{
			if(NULL == ps_internal_event[loc_u16_index_evt].ps_next) //CONDITION: premiere valeur de l'�vt
			{
				//on ajoute la premiere valeur
				loc_ps_trouve = &ps_internal_event[loc_u16_idx_dispo];
				SetStatutEvent(loc_ps_trouve, loc_u16_index_evt, loc_t_valeur_evt, loc_u32_info1, loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3);

				*loc_pps_stat_event_retourne = loc_ps_trouve;
				
				ps_internal_event[loc_u16_index_evt].ps_next = (struct S_STRUCT_INTERNAL_EVENTS*)loc_ps_trouve;
				loc_ps_trouve->ps_next = NULL;
			}
			else //CONDITION: ce n'est pas la premiere valeur de l'�vt
			{
				loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)ps_internal_event[loc_u16_index_evt].ps_next; // INIT
				loc_u16_cpt = 0; //INIT
				while( (NULL != loc_ps_encours) && (loc_u16_cpt<NB_MAX_INTERNAL_EVENTS))
				{
					if(loc_t_valeur_evt < loc_ps_encours->s_statut.t_valeur_evt)
					{
						loc_ps_trouve = &ps_internal_event[loc_u16_idx_dispo];
						SetStatutEvent(loc_ps_trouve, loc_u16_index_evt, loc_t_valeur_evt, loc_u32_info1, loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3);

						*loc_pps_stat_event_retourne = loc_ps_trouve;
						
						//on insere la valeur de l'�v�nement avant
						if((S_STRUCT_INTERNAL_EVENTS*)ps_internal_event[loc_u16_index_evt].ps_next == loc_ps_encours)
						{
							ps_internal_event[loc_u16_index_evt].ps_next = (struct S_STRUCT_INTERNAL_EVENTS*)loc_ps_trouve;
						}
						else
						{
							loc_ps_precedent->ps_next = (struct S_STRUCT_INTERNAL_EVENTS*)loc_ps_trouve;
						}

						loc_ps_trouve->ps_next = (struct S_STRUCT_INTERNAL_EVENTS*)loc_ps_encours;


						loc_u16_cpt = NB_MAX_INTERNAL_EVENTS+1;	//on sort

					}
					else
					{
						if(loc_t_valeur_evt == loc_ps_encours->s_statut.t_valeur_evt)
						{
							loc_u8_result = FALSE;
							DBG_INTERNEVENT("u8AddLst_StatusEvent KO: evt d�j� pr�sent (%d,%lu)",loc_u16_index_evt,loc_t_valeur_evt);
							//ERREUR
							//ERREUR
							//ERREUR
							//ERREUR
						}
						else
						{
							if(NULL == loc_ps_encours->ps_next) //CONDITION: c'est le dernier
							{
								loc_ps_trouve = &ps_internal_event[loc_u16_idx_dispo];
								SetStatutEvent(loc_ps_trouve, loc_u16_index_evt, loc_t_valeur_evt, loc_u32_info1, loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3);

								*loc_pps_stat_event_retourne = loc_ps_trouve;
								
								//on insere le trap apr�s
								loc_ps_encours->ps_next = (struct S_STRUCT_INTERNAL_EVENTS*)loc_ps_trouve;

								loc_ps_trouve->ps_next = NULL;

								loc_u16_cpt = NB_MAX_INTERNAL_EVENTS+1;	//on sort
							}
						}
					}
					
					//On passe au suivant
					loc_ps_precedent = loc_ps_encours;
					loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)loc_ps_encours->ps_next;
					loc_u16_cpt++;
				}
			}
		}
		else //CONDITION: LISTE CHAINEE PLEINE
		{
			loc_u8_result = FALSE;
			DBG_INTERNEVENT("u8AddLst_StatusEvent KO: liste chain�e pleine");
			//ERREUR
			//ERREUR
			//ERREUR
			//ERREUR
		}
	}
	else //CONDITION: IMPOSSIBLE
	{
		loc_u8_result = FALSE;
		DBG_INTERNEVENT("u8AddLst_StatusEvent KO: evt non adapt� (%d)",loc_u16_index_evt);
		//ERREUR
		//ERREUR
		//ERREUR
		//ERREUR
	}

	return loc_u8_result;
}/*u8AddLst_StatusEvent*/

//=====================================================================================
// Fonction		: u8GetStatEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  >loc_pps_stat_event_retourne< : adresse du nouveau pointeur
// Sortie		: <loc_u8_trouve> : TRUE si trouv�, sinon FALSE
// Auteur		: CM - 03/10/2007 -
// Description	: retourne le statut de l'�vt associ� au couple (index, valeur)
//=====================================================================================
u8sod u8GetStatEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, S_STRUCT_INTERNAL_EVENTS **loc_pps_stat_event_retourne)
{
	u8sod loc_u8_trouve;
	u16sod loc_u16_cpt;
	S_STRUCT_INTERNAL_EVENTS		*loc_ps_encours;

	loc_u8_trouve = FALSE; //INIT

	if(V_NO_ACTION != pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action) //CONDITION: evt � valeurs
	{
		if(NULL != ps_internal_event[loc_u16_index_evt].ps_next) //CONDITION: premiere valeur de l'�vt
		{
			loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)ps_internal_event[loc_u16_index_evt].ps_next; // INIT
			loc_u16_cpt = 0; //INIT
			while( (NULL != loc_ps_encours) && (loc_u16_cpt<NB_MAX_INTERNAL_EVENTS))
			{
				if(loc_t_valeur_evt == loc_ps_encours->s_statut.t_valeur_evt)//CONDITION: evt trouv�
				{
					*loc_pps_stat_event_retourne = loc_ps_encours;
					loc_u8_trouve = TRUE; //TROUVE
					loc_u16_cpt = NB_MAX_INTERNAL_EVENTS; //on sort
				}
				else
				{
					if(loc_ps_encours->s_statut.t_valeur_evt > loc_t_valeur_evt)//CONDITION: evt n'est pas pr�sent
					{
						loc_u16_cpt = NB_MAX_INTERNAL_EVENTS; //on sort
					}
				}

				//On passe au suivant
				loc_ps_encours = (S_STRUCT_INTERNAL_EVENTS*)loc_ps_encours->ps_next;
				loc_u16_cpt++;
			};
		}
	}
	else //CONDITION: existe par d�faut
	{
		*loc_pps_stat_event_retourne = &ps_internal_event[loc_u16_index_evt];
		loc_u8_trouve = TRUE; //TROUVE
	}

	return loc_u8_trouve;
}/*u8GetStatEvent*/


//=====================================================================================
// Fonction		: RegisterEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  <loc_u32_info1>	  : info 1
//				  <loc_u8_info2>	  : info 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u16_sizeinfo3>  : taille du tableau d�fini par info 3
//				  <loc_u8_etat>		  : �tat (ETAT_EVT_DEBUT, ETAT_EVT_FIN, ETAT_EVT_INFO)
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Enregistre l'�v�nement dans la table de statut des evts
//=====================================================================================
void RegisterEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info1, u8sod loc_u8_info2, u8sod *loc_pu8_info3, u16sod loc_u16_sizeinfo3, u8sod loc_u8_etat)
{
	S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt;

	loc_ps_intern_evt = NULL;	//INIT

//d: DEBUG suivi ev�nement dans la gestion
#if ACTIVATION_DEBUG_SUIVI_EVENT
	if(INDEX_DEBUG_EVENT == loc_u16_index_evt)
	{
//		printf("%lu (INFO)\n",loc_ps_intern_evt->s_statut.u_info_sup1.u32_term);
		DBG_INTERNEVENT("RegisterEvent: %d, %lu (%s) \n",
					  loc_u16_index_evt,
					  loc_t_valeur_evt,
					  PS8_MSG_ETAT_EVENT[loc_u8_etat]);
	}
#endif	
//f: DEBUG suivi ev�nement dans la gestion

	
	if(TRUE == u8TestEventDisponible(loc_u16_index_evt)) //CONDITION: �v�nement disponible
	{

		//Au pr�alable, on met � jour certains param�tres en fonction
		//de la base de donn�es courante
		// ........
		// ........
		// ........


		
		//Puis on met � jour la base de donn�es
		if(FALSE == u8GetStatEvent(loc_u16_index_evt,loc_t_valeur_evt,&loc_ps_intern_evt)) //CONDITION: evt n'est pas pr�sent dans la bdd
		{
//			DBG_INTERNEVENT("RegisterEvent: u8AddLst_StatusEvent");
			//Ajoute le nouvel evt dans la table de statut des evts
			u8AddLst_StatusEvent(loc_u16_index_evt,loc_t_valeur_evt,loc_u32_info1,loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3, &loc_ps_intern_evt);

			//Mise � jour aussi de l'evt de synth�se
			if(&ps_internal_event[loc_u16_index_evt] != loc_ps_intern_evt) //CONDITION: evt diff�rent de evt de synth�se
			{
				//on copie la valeur et les info suppl�mentaires (au cas o� la partie est commune)
				SetStatutEvent(&ps_internal_event[loc_u16_index_evt], loc_u16_index_evt, loc_t_valeur_evt, loc_u32_info1, loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3);
			}
		}
		else
		{
			//Mise � jour des infos
			SetStatutEvent(loc_ps_intern_evt, loc_u16_index_evt, loc_t_valeur_evt, loc_u32_info1, loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3);

			//Mise � jour aussi de l'evt de synth�se
			if(&ps_internal_event[loc_u16_index_evt] != loc_ps_intern_evt) //CONDITION: evt diff�rent de evt de synth�se
			{
				//on copie la valeur et les info suppl�mentaires (au cas o� la partie est commune)
				SetStatutEvent(&ps_internal_event[loc_u16_index_evt], loc_u16_index_evt, loc_t_valeur_evt, loc_u32_info1, loc_u8_info2, loc_pu8_info3, loc_u16_sizeinfo3);
			}
		}

		if(loc_ps_intern_evt != NULL) //CONDITION: evt existe
		{
			//Mise � jour de l'�tat de l'�vt
			if(		(ETAT_EVT_DEBUT == loc_u8_etat)
				||	(ETAT_EVT_INFO == loc_u8_etat)
			  )
			{
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT3_ETAT_MESURE);
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT1_ETAT_REEL);
			}
			else
			{
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT3_ETAT_MESURE);
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT1_ETAT_REEL);
			}

			//On indique que la mesure est r�alis�e
			SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_etat_evt,BIT4_FLAG_MESURE_CALCULEE);

			//Puis on met � jour la synth�se de l'�vt associ� si l'evt est
			//compos�e de plusieurs valeurs
			if(V_NO_ACTION != pt_process_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action)
			{
				if(		(ETAT_EVT_DEBUT == loc_u8_etat)
					||	(ETAT_EVT_INFO == loc_u8_etat)
				  )
				{
					SetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT3_ETAT_MESURE);
					SetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT1_ETAT_REEL);
				}
				else
				{
					//il ne faut pas positionner � tort � 0 dans la synth�se de l'alarme, lorsque alarme d�j� calcul�
					if(FALSE == u8GetU8EtatBit(ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT4_FLAG_MESURE_CALCULEE)) //CONDITION: pas encore calcul�
					{
						ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT1_ETAT_REEL);
					}
				}
				//On indique que la mesure est r�alis�e
				SetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT4_FLAG_MESURE_CALCULEE);
			}
		}
		else
		{
			DBG_INTERNEVENT("RegisterEvent: evt (%d,%lu) n'a pu �tre cr��",loc_u16_index_evt,loc_t_valeur_evt);
		}
	}
	else //CONDITION: �v�nement INDISPONIBLE
	{
		//Mise � jour de l'�tat OFF (m�me si info)
		ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT3_ETAT_MESURE);
		ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT4_FLAG_MESURE_CALCULEE);
		ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_etat_evt,BIT1_ETAT_REEL);
	}
	
}/*RegisterEvent*/

//=====================================================================================
// Fonction		: SetUseEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  <loc_u8_synthesis>  : indique si il faut mettre � jour l'evt de synth�se
// Sortie		: rien
// Auteur		: CM - 21/04/2008 -
// Description	: Permet de valider un �v�nement identifi� par le couple (idx/valeur)
//=====================================================================================
void SetUseEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u8sod loc_u8_synthesis)
{
	S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt;

	loc_ps_intern_evt = NULL;	//INIT

	if(TRUE == u8TestEventDisponible(loc_u16_index_evt)) //CONDITION: �v�nement disponible
	{
		if(TRUE == loc_u8_synthesis) //CONDITION: ordre de valider evt de synth�se
		{
			SetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_syst_evt, BIT0_SYST_EVT_USED);
		}
		else
		{
			//On valide l'evt identifi� par le couple
			if(TRUE == u8GetStatEvent(loc_u16_index_evt,loc_t_valeur_evt,&loc_ps_intern_evt)) //CONDITION: evt n'est pas pr�sent dans la bdd
			{
				SetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_syst_evt, BIT0_SYST_EVT_USED);
			}
		}
	}
	
}/*SetUseEvent*/

//=====================================================================================
// Fonction		: ResetUseEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  <loc_u8_synthesis>  : indique si il faut d�valider l'evt de synth�se
// Sortie		: rien
// Auteur		: CM - 21/04/2008 -
// Description	: Permet de d�valider un �v�nement identifi� par le couple (idx/valeur)
//					de fa�on ind�pendante de l'�tat BIT7_ETAT_CFG_VALID
//=====================================================================================
void ResetUseEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u8sod loc_u8_synthesis)
{
	S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt;

	loc_ps_intern_evt = NULL;	//INIT

	if(TRUE == u8TestEventDisponible(loc_u16_index_evt)) //CONDITION: �v�nement disponible
	{
		if(TRUE == loc_u8_synthesis)  //CONDITION: ordre de d�valider evt de synth�se
		{
			ResetU8EtatBit(&ps_internal_event[loc_u16_index_evt].s_statut.u8_syst_evt, BIT0_SYST_EVT_USED);
		}
		else
		{
			//On d�valide l'evt identifi� par le couple
			if(TRUE == u8GetStatEvent(loc_u16_index_evt,loc_t_valeur_evt,&loc_ps_intern_evt)) //CONDITION: evt n'est pas pr�sent dans la bdd
			{
				ResetU8EtatBit(&loc_ps_intern_evt->s_statut.u8_syst_evt, BIT0_SYST_EVT_USED);
			}
		}
	}

}/*ResetUseEvent*/

//=====================================================================================
// Fonction		: SetStatutEvent
// Entrees		: <loc_ps_intern_evt_maj< : pointeur du statut de l'evt
//				  <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'�vt
//				  <loc_u32_info1>	  : info 1
//				  <loc_u8_info2>	  : info 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u16_sizeinfo3>  : taille du tableau d�fini par info 3
// Sortie		: rien
// Auteur		: CM - 02/02/2009 -
// Description	: Fixe index/valeur/info de l'evt
//=====================================================================================
void SetStatutEvent(S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt_maj, u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info1, u8sod loc_u8_info2, u8sod *loc_pu8_info3, u16sod loc_u16_sizeinfo3)
{
	u16sod loc_u16_i;
	
	loc_ps_intern_evt_maj->s_statut.u16_index_evt = loc_u16_index_evt;
	loc_ps_intern_evt_maj->s_statut.t_valeur_evt = loc_t_valeur_evt;
	loc_ps_intern_evt_maj->s_statut.u_info_sup1.u32_term = loc_u32_info1;
	loc_ps_intern_evt_maj->s_statut.u8_info_sup2 = loc_u8_info2;
	//Copie champ info sup 3
	if(NULL == loc_pu8_info3) //CONDITION: info3 non d�fini
	{
		for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_TAB_INFO_SUP3;loc_u16_i++)
		{
			loc_ps_intern_evt_maj->s_statut.pu8_tab_info_sup3[loc_u16_i] = 0; //RAZ
		}
	}
	else
	{
		for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_TAB_INFO_SUP3;loc_u16_i++)
		{
			if(loc_u16_i<loc_u16_sizeinfo3)
			{
				loc_ps_intern_evt_maj->s_statut.pu8_tab_info_sup3[loc_u16_i] = loc_pu8_info3[loc_u16_i];
			}
			else
			{
				loc_ps_intern_evt_maj->s_statut.pu8_tab_info_sup3[loc_u16_i] = 0;	//RAZ
			}
		}
	}
}/*SetStatutEvent*/

 /*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitTableInternalEvent_ParDefaut
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Initialisation d'une partie de la table par d�faut
//=====================================================================================
void InitTableInternalEvent_ParDefaut(void)
{
	u16sod	loc_u16_i;

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		ps_internal_event[loc_u16_i].s_statut.u16_index_evt = S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u16_index_evt; //PAR DEFAUT
	}
	
}/*InitTableInternalEvent_ParDefaut*/

//=====================================================================================
// Fonction		: InitInternalEvent
// Entrees		: <loc_ps_intern_evt< : pointeur sur la base de donn�es � initialiser
// Sortie		: rien
// Auteur		: CM - 10/07/2007 -
// Description	: Initialisation d'un status d'evt
//=====================================================================================
void InitInternalEvent(S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt)
{
	loc_ps_intern_evt->ps_next = NULL;			//INIT
	InitStateEvt(&loc_ps_intern_evt->s_statut); //INIT
}/*InitInternalEvent*/

//=====================================================================================
// Fonction		: InitModule_InternEvent
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/07/2007 -
// Description	: Initialisation du module de internevent
//=====================================================================================
void InitModule_InternEvent(void)
{
	u16sod	loc_u16_i;
	
	for(loc_u16_i=0;loc_u16_i<NB_MAX_INTERNAL_EVENTS;loc_u16_i++)
	{
		InitInternalEvent(&ps_internal_event[loc_u16_i]);
	}

	InitTableInternalEvent_ParDefaut();
	
}/*InitModule_InternEvent*/

