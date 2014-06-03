/*========================================================================*/
/* NOM DU FICHIER  : exectrap.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 22/02/2010                                           */
/* Libelle         : NET-SNMP: gestion d'émission des traps			      */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE012 22/10/2010 CM
// - CREATION (source SDVB200 vB9)
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE019 16/03/2010 CM
// - Ajout MIB wrm100 dans agent SNMP
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE047 29/11/2010 CM
// - Optimisation traitement gestion trap sodielec
// - Optimisation configuration radio modem / amelioration ergonomie
//BE058 21/01/2011 CM
// - Ajout nouveaux évènements liés au DFS
// - Ajout champs info_sup1 dans gestion trap
//BE059 16/02/2011 CM/JP
// - Correction bug sur variable SNMP retournant une chaine date en mode 12H
//	 (comme cmdLastDatEOfCleaningAlarms)
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère l'émission des traps

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECTRAP

#define DEBUG_PERFORMANCE_EXECTRAP	0	//0:debug désactivé	1:debug activé	

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

//Fichiers temporaires
#define FILE_CIP_FIFOTRAP_SNMP_LINE	PATH_DIR__BDD_EVT "cip_fifotrap.snmp.line"
#define FILE_CIP_FIFOTRAP_TEMPO		PATH_DIR__BDD_EVT "cip_fifotrap.tmp"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static struct timeval s_timevalnow;

static	S_STRUCT_CIP_SNMPD s_cip_snmpd_courant;
static	u8sod	u8_premier_passage;

//d: debug - mesure timing
#if DEBUG_PERFORMANCE_EXECTRAP
static struct timeval  t_time1;
static struct timeval  t_time2;
#endif
//f: debug - mesure timing

/*_____V - PROCEDURES ____________________________________________________*/

// -------------------------------------------------------------
// Fonction		: proc_Fonction_Send_Trap
// Entrees		:
//				<loc_u16_numeroEvt> : numéro de l'événement
//				<loc_ps8_NomEquipementEvt< : chaine de caractères correspondant au nom de l'équipement
//				<loc_ps8_descripEvt< : description d evénement	
//				<uc_EtatEvt> : état de l'evénement( debut, fin ou info )
//				<loc_u8_NiveauGraviteEvt> : niveau de gravité de l'evénement
//				<loc_ps8_DateEvenement< : date d'apparition d evénement	
//				<loc_ps8_HeureEvenement< : heure d'apparition d evénement	
//				<loc_t_valeur_evt> : valeur associée à l'evénement
//				<loc_u16_oid_alarmV1Table_line> : oid sur table alarmV1
//				<loc_u16_oid_evtV1configTable_line> : oid sur table evtV1Config
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Envoi le trap
// -------------------------------------------------------------
void proc_Fonction_Send_Trap(  u16sod	loc_u16_numeroEvt,
							   s8sod		*loc_ps8_NomEquipementEvt,
							   s8sod		*loc_ps8_descripEvt,
							   u8sod		loc_u8_EtatEvt,
							   u8sod		loc_u8_NiveauGraviteEvt,
							   s8sod		*loc_ps8_DateEvenement,
							   s8sod		*loc_ps8_HeureEvenement,
							   T_SIZE_VALEUR_EVT loc_t_valeur_evt,
							   u16sod	loc_u16_oid_alarmV1Table_line,
							   u16sod	loc_u16_oid_evtV1configTable_line
							);

//=====================================================================================
// Fonction		: GestionTrapSodielec
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Gestion des traps sodielec (appelé sous snmpd.c)
//=====================================================================================
void GestionTrapSodielec(void)
{
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem;
	u16sod	loc_u16_nbEltTrapTotal;
	u16sod	loc_u16_nbEltTrapLus;
	u8sod	loc_u8_lecture_config;
	u8sod	loc_u8_new_config_snmpd;
	S_STRUCT_CIP_SNMPD loc_s_cip_snmpd_tempo;
	u8sod loc_u8_idx_cfgfile;
	u8sod loc_u8_new_list_freq;

	loc_u16_nbEltTrapTotal = 0;		//INIT
	loc_u16_nbEltTrapLus = 0;	//INIT
	loc_u8_lecture_config = FALSE;	//INIT
	loc_u8_new_config_snmpd = FALSE; //INIT
	memset(&loc_s_cip_snmpd_tempo, 0, sizeof(S_STRUCT_CIP_SNMPD)); //INIT
	loc_u8_idx_cfgfile = 0;	//INIT
	loc_u8_new_list_freq = FALSE; //INIT
	
#if DEBUG_PERFORMANCE_EXECTRAP
	//d: debug - mesure timing
	gettimeofday(&t_time1, (struct timezone *) NULL); //INIT
//	MACRO_PRINTF(("GestionTrapSodielec: 2->1:%d us\n",
//				  ((t_time1.tv_sec - t_time2.tv_sec)*1000000 + (t_time1.tv_usec - t_time2.tv_usec))));
	//f: debug - mesure timing
#endif

	//---------------------------------------------
	//Lecture la Base de données CIP (propre à ce processus)
	//---------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillCipSnmpd(&loc_s_cip_snmpd_tempo))
	{
		s_cip_snmpd_courant = loc_s_cip_snmpd_tempo;
		Raz_Cip_Snmpd(&loc_s_cip_snmpd_tempo);	//RAZ
		u8EditCipSnmpd(&loc_s_cip_snmpd_tempo);
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on relache le sem


	//---------------------------------------------
	//Surveillance de la CIP d'échange de trap
	//---------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on lève le sémaphore

	//Détermination nombre de lignes dans cip_fifotrap (donc nombre d'éléments trap)
	loc_u16_nbEltTrapTotal = (u16sod)u32GetNumberLineFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file, FILE_CIP_FIFOTRAP_SNMP_LINE);

	if(loc_u16_nbEltTrapTotal > 0) //CONDITION: fichier non vide
	{
		//Lecture du fichier cip_fifotrap
		if(TRUE == u8ReadCipFifoTrap(&T_DEF_FILE_CIP_FIFOTRAP_INI, u8AjouteDansStatutTrap, loc_u16_nbEltTrapTotal, &loc_u16_nbEltTrapLus))
		{
			if(loc_u16_nbEltTrapLus < loc_u16_nbEltTrapTotal) //CONDITION: on n'a pas lu tous les traps
			{
				//On copie le fichier cip_fifotrap dans un fichier temporaire
				u8CmdSystem_CopyFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file, FILE_CIP_FIFOTRAP_TEMPO);

				//Puis on supprime le fichier cip_fifotrap (original)
				u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);

				//On lit les lignes non lus du fichier temporaire
				CmdSystem_Generique("sed -n %d,%dp %s > %s",
									(loc_u16_nbEltTrapLus+1),
									loc_u16_nbEltTrapTotal,
									FILE_CIP_FIFOTRAP_TEMPO,
									T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);

				//On supprime le fichier temporaire
				u8CmdSystem_RemoveFile(FILE_CIP_FIFOTRAP_TEMPO);
			}
			else
			{
				//On supprime le fichier cip_fifotrap (original)
				u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
				//Puis on crée un fichier vide
				CmdSystem_Generique("touch %s",
									T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
			}
		}
		else //CONDITION: lecture erronée (on repart de zéro)
		{
			MACRO_PRINTF(("GestionTrapSodielec: ERREUR LECTURE CIP => Suppresion fichier %s \n",
						  T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file));
			//On supprime le fichier cip_fifotrap (original)
			u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
			//Puis on crée un fichier vide
			CmdSystem_Generique("touch %s",
								T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on relache le sem

	//---------------------------------------------
	//Lecture de la configuration SNMP
	//---------------------------------------------
	if(TRUE == u8_premier_passage) //CONDITION: premier passage
	{
		s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillConfigEquipement(&s_config_process_snmpd)) //MAJ
		{
			loc_u8_lecture_config = TRUE;
			u8_snmp_langue = s_config_process_snmpd.s_admin.u8_langue; //MAJ
			SetConfig_ModuleDate(s_config_process_snmpd.s_admin.u8_mode_date_heure); //MAJ
		}
		s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
		u8_premier_passage = FALSE;	//RAZ
	}
	else  //CONDITION: test si évolution de la configuration signalée
	{
		loc_u8_lecture_config = TRUE; //RAZ
		s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
		for(loc_u8_idx_cfgfile=0; loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG; loc_u8_idx_cfgfile++)
		{
			if(TRUE == s_cip_snmpd_courant.pu8_flag_newcfg[loc_u8_idx_cfgfile]) //CONDITION: evolution de la configuration
			{
				//Lecture de la configuration
				if(FALSE == u8Transfert_FileToStruct(&s_config_process_snmpd, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]))
				{
					MACRO_PRINTF(("GestionTrapSodielec: ERREUR LECTURE CONFIG idx=%d \n",loc_u8_idx_cfgfile));
				}
				else //CONDITION: lecture OK
				{
					switch(loc_u8_idx_cfgfile)
					{
						case IDXCFG_ADMIN:
							u8_snmp_langue = s_config_process_snmpd.s_admin.u8_langue; //MAJ
							SetConfig_ModuleDate(s_config_process_snmpd.s_admin.u8_mode_date_heure); //MAJ
							break;
						default:
						case IDXCFG_WIFI:
							//Il faut lire la liste des fréquences réglementaires
							loc_u8_new_list_freq = TRUE;
							break;
					}
				}
			}
		}
		s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

		if(TRUE == loc_u8_new_list_freq)
		{
			s32Lock_Get(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on leve le semaphore
			if(FALSE == u8FillListFreqFile(&s_list_freq_process_snmpd))
			{
				MACRO_PRINTF(("GestionTrapSodielec: ERREUR LECTURE LIST FREQ \n"));
			}
			s32Lock_Release(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on relache le sem
		}
	}
			

	//---------------------------------------------
	//Gestion Replay TRAP
	//---------------------------------------------
	switch(s_config_process_snmpd.s_snmp.u8_version_snmp)
	{
		case VERSION_SNMPV1:
			if (TRUE == s_cip_snmpd_courant.u8_replay_trap) //CONDITION: Ordre de rejouer les traps
			{
				s_cip_snmpd_courant.u8_replay_trap = FALSE; //RAZ au cas où
				ReplayTrap();
			}
			break;
		case VERSION_SNMPV2C:
		default:
			break;
	}

	//---------------------------------------------
	//Gestion Accquittement de tous les traps
	//---------------------------------------------
	switch(s_config_process_snmpd.s_snmp.u8_version_snmp)
	{
		case VERSION_SNMPV1:
			if (TRUE == s_cip_snmpd_courant.u8_acquit_all_traps) //CONDITION: Ordre de rejouer les traps
			{
				s_cip_snmpd_courant.u8_acquit_all_traps = FALSE; //RAZ au cas où
				MACRO_PRINTF(("GestionTrapSodielec: AcquitAllTraps\n"));
				AcquitAllTraps();
			}
			break;
		case VERSION_SNMPV2C:
		default:
			break;
	}
	
	//---------------------------------------------
	//Gestion des TRAPS
	//---------------------------------------------
	if(TRUE == loc_u8_lecture_config)
	{
		if(EMISSION_TRAP_ACTIVE == s_config_process_snmpd.s_snmp.u8_emission_trap)
		{
#if 0		
			//Test la cohérence des valeurs de la table status trap
			//si incohérence trap supprimé
			TestCoherenceValeurTrapAvecConfig();
#else
#warning "Test valeur trap non necessaire"
#endif

			//Gestion liste statusTRAP
			s32Lock_Get(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on lève le sem
			Gestion_StatusTrap();
			s32Lock_Release(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on relache le sem
		}
		else
		{
			//On raz la liste
			s32Lock_Get(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on lève le sem
			InitLst_StatusTrap();
			s32Lock_Release(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on relache le sem
		}
		
		//---------------------------------------------
		//Edition du fichier status des TRAPS (SNMPv1, SNMPv2c, ...)
		//---------------------------------------------
		EditFileStatutTrap();
	}

#if DEBUG_PERFORMANCE_EXECTRAP
	//d: debug - mesure timing
	gettimeofday(&t_time2, (struct timezone *) NULL);
	MACRO_PRINTF(("GestionTrapSodielec: 1->2: %d us\n",
				 ((t_time2.tv_sec - t_time1.tv_sec)*1000000 + (t_time2.tv_usec - t_time1.tv_usec))));
	//f: debug - mesure timing
#endif

	
}/*GestionTrapSodielec*/

//=====================================================================================
// Fonction		: CopyCipFifoToStatusTrap
// Entrees		: <loc_ps_elt_fifotrap<	: element cip fifo trap qui doit etre ajouté à StatutTrap
//				: <loc_ps_trap<   :  résultat
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: transfert element fifo de cip  dans la statut des TRAP
//=====================================================================================
void CopyCipFifoToStatusTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP *loc_ps_elt_fifotrap, S_STRUCT_STA_TRAP *loc_ps_trap)
{
	loc_ps_trap->u16_index_evt = loc_ps_elt_fifotrap->u16_index_evt;	//MAJ
	loc_ps_trap->t_valeur_evt = loc_ps_elt_fifotrap->t_valeur_evt;		//MAJ
	loc_ps_trap->s_date = loc_ps_elt_fifotrap->s_date;					//MAJ
	loc_ps_trap->u32_cpt_emission_trap = 0;				//RAZ	
	loc_ps_trap->u32_cpt_interval_trap = 0;				//RAZ
	loc_ps_trap->u8_val_snmp = VAL_SNMP_NON_ACQUITTER;	//RAZ
	loc_ps_trap->u8_etat_evt = loc_ps_elt_fifotrap->u8_etat_evt;		//MAJ
	loc_ps_trap->u_info_sup1.u32_term = loc_ps_elt_fifotrap->u_info_sup1.u32_term;		//MAJ
	loc_ps_trap->u8_info_sup2 = loc_ps_elt_fifotrap->u8_info_sup2;		//MAJ
	memcpy(loc_ps_trap->pu8_tab_info_sup3, loc_ps_elt_fifotrap->pu8_tab_info_sup3, TAILLE_MAX_TAB_INFO_SUP3);  //MAJ
}/*CopyCipFifoToStatusTrap*/

//=====================================================================================
// Fonction		: u8AjouteDansStatutTrap
// Entrees		: <loc_ps_elt_fifotrap<	: element qui doit etre ajouté à StatutTrap
// Sortie		: <loc_u8_return> : TRUE, si enregistrement OK	FALSE, si enregistrement KO
// Auteur		: CM - 29/08/2007 -
// Description	: ajoute element dans la table statut des TRAP
//=====================================================================================
u8sod u8AjouteDansStatutTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP	*loc_ps_elt_fifotrap)
{
	u16sod			loc_u16_cpt;
	u8sod			loc_u8_return;
	S_STRUCT_STA_TRAP	*loc_ps_trap;
	S_STRUCT_STA_TRAP	*loc_ps_trap_trouve;
	S_STRUCT_STA_TRAP	loc_s_new_trap;	

	loc_u8_return = FALSE;	//INIT : enregistrement des TRAPs non autorisé
	loc_ps_trap_trouve = NULL;	//INIT

	// on ajoute un élément à la Base de données suivant 2 cas : 
	//		- cet element existe dans la table avec une date différente
	//		- cet element n'existe pas


//	DEBUGMSGTL(("sodielec", "u8AjouteDansStatutTrap %d,%d\n",
//				S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_ps_elt_fifotrap->u16_index_evt].u16_numero_evt,
//				loc_ps_elt_fifotrap->t_valeur_evt));
	
	//Recherche correspondance de cet évt (si il existe) dans la table s_trap_statut	
	if(ps_status_trap->ps_premier_trap != NULL) //CONDITION: liste non vide
	{
		loc_ps_trap = ps_status_trap->ps_premier_trap; // INIT
		loc_u16_cpt = 0; //INIT
		do{
			
			if((loc_ps_trap->u16_index_evt == loc_ps_elt_fifotrap->u16_index_evt)&&
			   (loc_ps_trap->t_valeur_evt == loc_ps_elt_fifotrap->t_valeur_evt)
			  ) //CONDITION: couple trouvé
			{
				loc_ps_trap_trouve = loc_ps_trap;	//TROUVE

				//Le TRAP info sera émis seulement si le meme évt précédent a été émis au moins 1 fois
				//Le TRAP alarme sera émis seulement si l'état précédent a été émis au moins 1 fois
				if(loc_ps_trap_trouve->u32_cpt_emission_trap >= 1) //CONDITION: TRAP en cours d'émission émis au moins 1 fois
				{
					//On met à jour
					CopyCipFifoToStatusTrap(loc_ps_elt_fifotrap, loc_ps_trap_trouve); //Mise à jour

					loc_u8_return = TRUE;	// donc on peut enregistrer le TRAP
				}
				else
				{
					DEBUGMSGTL(("sodielec", "AjouteDansStatutTrap : ATTENTE émission evt précédent %d\n",
								loc_ps_trap_trouve->u32_cpt_emission_trap));
				}

				loc_u16_cpt = TAILLE_MAX_TABLE_STATUSTRAP + 1;	//on sort
			}
			
			//On passe au suivant
			loc_ps_trap = (S_STRUCT_STA_TRAP*)loc_ps_trap->ps_next;
			loc_u16_cpt++;
		}while( (NULL != loc_ps_trap) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP));
	}

	if(NULL == loc_ps_trap_trouve)	//CONDITION: trap absent de la liste
	{
//		DEBUGMSGTL(("sodielec", "AddLst_StatusTrap\n"));
		
		//On ajout le nouveau trap dans la liste
		CopyCipFifoToStatusTrap(loc_ps_elt_fifotrap, &loc_s_new_trap); //INIT
		loc_s_new_trap.u16_idx_table = IDX_MEMOIRE_DISPO;			//INIT
		AddLst_StatusTrap(&loc_s_new_trap);
		loc_u8_return = TRUE; 
	}


	return loc_u8_return;
}/*u8AjouteDansStatutTrap*/

//=====================================================================================
// Fonction		: Gestion_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Gestion du statusTRAP
//=====================================================================================
void Gestion_StatusTrap(void)
{
	s32sod	loc_s32_sem;
	S_STRUCT_STA_TRAP		*loc_ps_trap;
	S_STRUCT_STA_TRAP		*loc_ps_precedent;
	S_STRUCT_STA_TRAP		*loc_ps_tempo;
	S_STRUCT_CFG_EVENT	loc_s_cfg_evt;
	s8sod	loc_ps8_nom_equipement[100+1];
	s8sod	loc_ps8_date[10];
	s8sod	loc_ps8_heure[10];
	s8sod	loc_ps8_libelle_evt[UI_TAILLE_MAX_MESSAGE_2];
	u16sod	loc_u16_oid_evtV1configTable_line;
	u16sod	loc_u16_oid_alarmV1Table_line;
	u16sod	loc_u16_cpt;

	loc_ps_trap = NULL;	//INIT
	loc_ps_precedent = NULL;	//INIT
	loc_ps_tempo = NULL;	//INIT
	
	//Recherche correspondance de cet évt (si il existe) dans la table s_trap_statut	
	if(ps_status_trap->ps_premier_trap != NULL) //CONDITION: liste non vide
	{
		
		loc_ps_precedent = ps_status_trap->ps_premier_trap; //INIT
		loc_ps_trap = ps_status_trap->ps_premier_trap; // INIT
		loc_u16_cpt = 0; //INIT
		do{
			if(		(VAL_SNMP_SUPPRIMER == loc_ps_trap->u8_val_snmp) ||					
			        ((VAL_SNMP_ACQUITTER == loc_ps_trap->u8_val_snmp) &&
					 ((ETAT_EVT_FIN == loc_ps_trap->u8_etat_evt) || (ETAT_EVT_INFO == loc_ps_trap->u8_etat_evt))
					) ||
					(FALSE == u8TestEvenementValide(loc_ps_trap->u16_index_evt))
			  )	//CONDITION: (trap à supprimer) ou (trap acquitté  et etat fin ou info) ou (index evt non valide)
			{
				//on supprime le trap
				if(loc_ps_trap == ps_status_trap->ps_premier_trap) //CONDITION: il s'agit du premier
				{
					ps_status_trap->ps_premier_trap = (S_STRUCT_STA_TRAP*)loc_ps_trap->ps_next;
					//on repositionne le pointeur sur le précédent (pour
					//traiter les autres traps)
					loc_ps_precedent = ps_status_trap->ps_premier_trap;
				}
				else
				{
					loc_ps_precedent->ps_next = loc_ps_trap->ps_next;
				}
				//on sauve le pointeur du prochain élément à traiter
				loc_ps_tempo = (S_STRUCT_STA_TRAP*)loc_ps_trap->ps_next;
				InitStatusTrap(loc_ps_trap); //RAZ

				//on repositionne le pointeur sur le suivant
				loc_ps_trap = loc_ps_tempo;
			}
			else
			{
				//Lecture de la configuration de l'évènement
				loc_s_cfg_evt = s_config_process_snmpd.s_tabevt.s_event[loc_ps_trap->u16_index_evt];

				if(TRUE == u8TestStatut_Trap(&loc_s_cfg_evt, loc_ps_trap))
				{
					strcpy(loc_ps8_nom_equipement, S_DESCRIPT_EQUIPEMENT[ u8_snmp_type_equipement ].ps8_nom[u8_snmp_langue]);

					ChLibelleTrap(loc_ps8_libelle_evt, loc_ps_trap->u16_index_evt, loc_ps_trap->t_valeur_evt, loc_ps_trap->u_info_sup1.u32_term, loc_ps_trap->u8_info_sup2, loc_ps_trap->pu8_tab_info_sup3, u8_snmp_langue);

					sprintf(loc_ps8_date, "%04d%02d%02d",loc_ps_trap->s_date.u16_annee,loc_ps_trap->s_date.u8_mois,loc_ps_trap->s_date.u8_jour);
					sprintf(loc_ps8_heure, "%02d%02d%02d",loc_ps_trap->s_date.u8_heure,loc_ps_trap->s_date.u8_minute,loc_ps_trap->s_date.u8_seconde);

					loc_u16_oid_alarmV1Table_line = loc_ps_trap->u16_idx_table+1;
					loc_u16_oid_evtV1configTable_line = S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_ps_trap->u16_index_evt].u16_numero_evt;

//					printf("proc_Fonction_Send_Trap: evt %d,%d\n",loc_ps_trap->u16_index_evt,loc_ps_trap->t_valeur_evt);
					
					proc_Fonction_Send_Trap(
								  S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_ps_trap->u16_index_evt].u16_numero_evt,				//Numéro evt
								  loc_ps8_nom_equipement,				//Equipement
								  loc_ps8_libelle_evt,					//Libellé evt
								  loc_ps_trap->u8_etat_evt,				//Etat evt
								  (loc_s_cfg_evt.u8_niveau_gravite+1),	//Niveau gravité evt
								  loc_ps8_date,							//Date apparition / disparition evt
								  loc_ps8_heure,							//Heure apparition / disparition evt
								  loc_ps_trap->t_valeur_evt,			//Valeur de l'evt
								  loc_u16_oid_alarmV1Table_line,		//valeur OID
								  loc_u16_oid_evtV1configTable_line);	//valeur OID
				}
				//On passe au suivant
				loc_ps_precedent = loc_ps_trap;
				loc_ps_trap = (S_STRUCT_STA_TRAP*)loc_ps_trap->ps_next;
			}
			
			loc_u16_cpt++;
		}while( (NULL != loc_ps_trap) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP));
	}
	
}/*Gestion_StatusTrap*/

//=====================================================================================
// Fonction		: u8TestStatut_Trap
// Entrees		: <loc_ps_cfg_evt< : config de l'évt
//				 <loc_ps_trap< : statut du trap
// Sortie		: rien
//					TRUE	   : conditions verifiées (nombre d'émission) pour l'envoie d' un trap
//					FALSE	   : conditions non verifiées (nombre d'émission), pas d'envoi de trap
// Auteur		: CM - 29/08/2007 -
// Description	: Test pour les traps de type alarme ou info ; verification de l'envoie ou pas du trap
//=====================================================================================
u8sod u8TestStatut_Trap(S_STRUCT_CFG_EVENT	*loc_ps_cfg_evt, S_STRUCT_STA_TRAP	*loc_ps_trap)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	gettimeofday(&s_timevalnow, (struct timezone *) NULL);

	if (FALSE == u8GetEventAction(loc_ps_cfg_evt->u16_action, ACTION_EVT_VALIDE))		//CONDITION: evenement n'est pas valide   
	{
		switch(s_config_process_snmpd.s_snmp.u8_version_snmp)
		{
			case VERSION_SNMPV1:
				// Si on atteint le nombre d'émissions ou si l'on a émis 2 fois dans le cas d'un envoi infini
				if (
					  ((0 != s_config_process_snmpd.s_snmp.s_trap_SNMPv1[loc_ps_cfg_evt->u8_niveau_gravite].u16_nb_emission) && (loc_ps_trap->u32_cpt_emission_trap >= (u32sod)s_config_process_snmpd.s_snmp.s_trap_SNMPv1[loc_ps_cfg_evt->u8_niveau_gravite].u16_nb_emission)) ||
					  ((0 == s_config_process_snmpd.s_snmp.s_trap_SNMPv1[loc_ps_cfg_evt->u8_niveau_gravite].u16_nb_emission) && (2 <= loc_ps_trap->u32_cpt_emission_trap))
				   )
				{
					loc_ps_trap->u8_val_snmp = VAL_SNMP_SUPPRIMER; //on supprimera au prochain passage
				}
				break;
			case VERSION_SNMPV2C:
			default:
				if(loc_ps_trap->u32_cpt_emission_trap >= 1)	//CONDITION: au moins émis
				{
					loc_ps_trap->u8_val_snmp = VAL_SNMP_SUPPRIMER; //on supprimera au prochain passage
				}
				break;
		}
	}
	else
	{
		if (FALSE == u8GetEventAction(loc_ps_cfg_evt->u16_action, ACTION_EVT_TRAP))		//CONDITION: evenement est selectionné pour envoyer un trap (cf. SNMP TRAP sur site web)    
		{
			loc_ps_trap->u8_val_snmp = VAL_SNMP_SUPPRIMER; //on supprimera au prochain passage
		}
	}

	switch(s_config_process_snmpd.s_snmp.u8_version_snmp)
	{
		case VERSION_SNMPV1:
			if 	(VAL_SNMP_NON_ACQUITTER == loc_ps_trap->u8_val_snmp)	//CONDITION: si le trap est non acquitté et 
			{															// dans le cas ou nb_emission est inferieur à celui défini sur le site web
																		// et lorsqu'on depasse l'intervalle de réemission
				
				if(((loc_ps_trap->u32_cpt_emission_trap < (u32sod)s_config_process_snmpd.s_snmp.s_trap_SNMPv1[loc_ps_cfg_evt->u8_niveau_gravite].u16_nb_emission) ||
					 (0 == s_config_process_snmpd.s_snmp.s_trap_SNMPv1[loc_ps_cfg_evt->u8_niveau_gravite].u16_nb_emission)	//Emission Trap infini
				   )&&
				   ((abs(loc_ps_trap->u32_cpt_interval_trap - s_timevalnow.tv_sec) >= (u32sod)s_config_process_snmpd.s_snmp.s_trap_SNMPv1[loc_ps_cfg_evt->u8_niveau_gravite].u16_interval))
				  )
				{
					loc_ps_trap->u32_cpt_emission_trap ++;
					loc_ps_trap->u32_cpt_interval_trap = s_timevalnow.tv_sec;	//Mise à 0	
					loc_u8_resultat = TRUE;
				}
			}
			break;
		case VERSION_SNMPV2C:
		default:
			if(loc_ps_trap->u32_cpt_emission_trap < 1)	//CONDITION: pas encore émis
			{
				loc_ps_trap->u32_cpt_emission_trap ++;
				loc_ps_trap->u32_cpt_interval_trap = s_timevalnow.tv_sec;	//Mise à 0	
				loc_u8_resultat = TRUE;
			}
			break;

	}

	return loc_u8_resultat;
}/*u8TestStatut_Trap*/

// -------------------------------------------------------------
// Fonction		: proc_Fonction_Send_Trap
// Entrees		:
//				<loc_u16_numeroEvt> : numéro de l'événement
//				<loc_ps8_NomEquipementEvt< : chaine de caractères correspondant au nom de l'équipement
//				<loc_ps8_descripEvt< : description d evénement	
//				<uc_EtatEvt> : état de l'evénement( debut, fin ou info )
//				<loc_u8_NiveauGraviteEvt> : niveau de gravité de l'evénement
//				<loc_ps8_DateEvenement< : date d'apparition d evénement	
//				<loc_ps8_HeureEvenement< : heure d'apparition d evénement	
//				<loc_t_valeur_evt> : valeur associée à l'evénement
//				<loc_u16_oid_alarmV1Table_line> : oid sur table alarmV1
//				<loc_u16_oid_evtV1configTable_line> : oid sur table evtV1Config
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Envoi le trap
// -------------------------------------------------------------
void proc_Fonction_Send_Trap( u16sod	loc_u16_numeroEvt,
							  s8sod		*loc_ps8_NomEquipementEvt,
							  s8sod		*loc_ps8_descripEvt,
							  u8sod		loc_u8_EtatEvt,
							  u8sod		loc_u8_NiveauGraviteEvt,
							  s8sod		*loc_ps8_DateEvenement,
							  s8sod		*loc_ps8_HeureEvenement,
							  T_SIZE_VALEUR_EVT	loc_t_valeur_evt,
							  u16sod	loc_u16_oid_alarmV1Table_line,
							  u16sod	loc_u16_oid_evtV1configTable_line
				 )
{
	netsnmp_variable_list *loc_pt_trap_vars;
	s32sod				  loc_s32_specificTrap;
	s32sod  loc_s32_trap_id;
	s32sod  loc_s32_trap_valeur;
	s32sod  loc_s32_trap_acquit;
	s32sod  loc_s32_trap_niveau_gravite;
	

	oid loc_t_objid_enterprise[] = {_ENTERPRISE_SODIELECV2_ADMINISTRATIONV1};

	oid loc_t_objid_oid1[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,4,1,1,4,		loc_u16_oid_alarmV1Table_line		}; // Equipement, STG
	oid loc_t_objid_oid2[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,3,1,1,1,4,	loc_u16_oid_evtV1configTable_line	}; // Description, STG
	oid loc_t_objid_oid3[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,3,1,1,1,5,	loc_u16_oid_evtV1configTable_line	}; // NiveauGravite, INT 1 a 5
	oid loc_t_objid_oid4[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,3,1,1,1,3,	loc_u16_oid_evtV1configTable_line	}; // Id, INT
	oid loc_t_objid_oid5[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,4,1,1,6,		loc_u16_oid_alarmV1Table_line		}; // Date, STG
	oid loc_t_objid_oid6[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,4,1,1,7,		loc_u16_oid_alarmV1Table_line		}; // Heure, STG
	oid loc_t_objid_oid7[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,4,1,1,3,		loc_u16_oid_alarmV1Table_line		}; // Valeur, INT
	oid loc_t_objid_oid8[] = { _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,4,1,1,8,		loc_u16_oid_alarmV1Table_line		}; // Acquit, INT 1 a 3

	DEBUGMSGTL(("sodielec", "proc_Fonction_Send_Trap %d,%d (%d)\n",
				loc_u16_numeroEvt,
				loc_t_valeur_evt,
				loc_u8_EtatEvt));
	
	loc_pt_trap_vars = NULL; //INIT

	//Détermination du numéro de trap
	switch(loc_u8_EtatEvt)
	{
		case ETAT_EVT_DEBUT:
			loc_s32_specificTrap = 1;
			break;
		case ETAT_EVT_FIN:
			loc_s32_specificTrap = 2;
			break;
		case ETAT_EVT_INFO:
			loc_s32_specificTrap = 3;
			break;
		default:
			loc_s32_specificTrap = 0;
			break;
	}

	loc_s32_trap_id		= (s32sod)loc_u16_numeroEvt;	//INIT
	loc_s32_trap_valeur = (s32sod)loc_t_valeur_evt;		//INIT
	loc_s32_trap_acquit = (s32sod)1;		//INIT: ce qui correspond à VAL_SNMP_NON_ACQUITTER au niveau ASN1
	loc_s32_trap_niveau_gravite = (s32sod)loc_u8_NiveauGraviteEvt; //INIT
	
	
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid1, sizeof(loc_t_objid_oid1) / sizeof(oid),
							  ASN_OCTET_STR,
							  (u_char*)loc_ps8_NomEquipementEvt,
							  strlen(loc_ps8_NomEquipementEvt));
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid2, sizeof(loc_t_objid_oid2) / sizeof(oid),
							  ASN_OCTET_STR,
							  (u_char*)loc_ps8_descripEvt,
							  strlen(loc_ps8_descripEvt));
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid3, sizeof(loc_t_objid_oid3) / sizeof(oid),
							  ASN_INTEGER,
							  (const u_char *) &loc_s32_trap_niveau_gravite,
							  sizeof(loc_s32_trap_niveau_gravite));
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid4, sizeof(loc_t_objid_oid4) / sizeof(oid),
							  ASN_INTEGER,
							  (const u_char *) &loc_s32_trap_id,
							  sizeof(loc_s32_trap_id));
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid5, sizeof(loc_t_objid_oid5) / sizeof(oid),
							  ASN_OCTET_STR,
							  (u_char*)loc_ps8_DateEvenement,
							  strlen(loc_ps8_DateEvenement));
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid6, sizeof(loc_t_objid_oid6) / sizeof(oid),
							  ASN_OCTET_STR,
							  (u_char*)loc_ps8_HeureEvenement,
							  strlen(loc_ps8_HeureEvenement));
	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid7, sizeof(loc_t_objid_oid7) / sizeof(oid),
							  ASN_INTEGER,
							  (const u_char *) &loc_s32_trap_valeur,
							  sizeof(loc_s32_trap_valeur));

	snmp_varlist_add_variable(&loc_pt_trap_vars,
							  loc_t_objid_oid8, sizeof(loc_t_objid_oid8) / sizeof(oid),
							  ASN_INTEGER,
							  (const u_char *) &loc_s32_trap_acquit,
							  sizeof(loc_s32_trap_acquit));

  //   void send_enterprise_trap_vars( int trap, oid * enterprise, int enterprise_length, netsnmp_variable_list * vars);

  //   printf("Envoi Trap");
  //   printf(" pour %d (%d); gravite: %d\n", trap_data.trap_id, evtV1configTable_line, trap_data.trap_gravite);


	send_enterprise_trap_vars(SNMP_TRAP_ENTERPRISESPECIFIC, loc_s32_specificTrap, loc_t_objid_enterprise, sizeof(loc_t_objid_enterprise) / sizeof(oid), loc_pt_trap_vars);
	
	snmp_free_varbind(loc_pt_trap_vars);
}/*proc_Fonction_Send_Trap*/

// -------------------------------------------------------------
// Fonction		: ChLibelleTrap
// Entrees		: <loc_ps8_chaine<	: chaine retournée
//				  <loc_u16_indice_evt> : indice evt
//				  <loc_t_valeur_evt> : valeur evt
//				  <loc_u32_info_sup1>	  : info 1
//				  <loc_u8_info_sup2> : information supplémentaire 2
//				  <loc_pu8_info_sup3> : info 3
//				  <loc_u8_index_langue> : index de la langue à afficher
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Procedure qui retourne en chaine de caractère le
// libellé des évènements pour les traps
// -------------------------------------------------------------
void ChLibelleTrap(s8sod *loc_ps8_chaine, u16sod loc_u16_indice_evt,T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info_sup1, u8sod loc_u8_info_sup2, u8sod *loc_pu8_info_sup3, u8sod loc_u8_index_langue)
{
	U_UNION_INFO_SUP	loc_u_info_sup1;
	s8sod	loc_ps8_ch_tempo[50+1];

	loc_ps8_chaine[0] = 0;	//INIT
	loc_u_info_sup1.u32_term = loc_u32_info_sup1;
	loc_ps8_ch_tempo[0] = 0; //INIT

	if (loc_u16_indice_evt < NB_MAX_EVENEMENTS)
	{
		switch(loc_u16_indice_evt)
		{
			case EVT007_PROBLEME_CONFIGURATION:
				strcpy(loc_ps8_chaine,ps8ConvertChaineToSnmp(pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_evenement[loc_u16_indice_evt]));
				if((loc_t_valeur_evt-1) < NB_MAX_ERRORCONFIG)
				{
					strcat(loc_ps8_chaine, " / ");
					strcat(loc_ps8_chaine,ps8ConvertChaineToSnmp(pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_errorconfig[(loc_t_valeur_evt-1)]));
				}
				break;
			case EVT011_RADAR_DETECTE_SUR_CANAL:
				strcpy(loc_ps8_chaine,ps8ConvertChaineToSnmp(pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_evenement[loc_u16_indice_evt]));
				strcat(loc_ps8_chaine, " / ");
				sprintf(loc_ps8_ch_tempo, "(%d MHz / CH=%d)",
						loc_u_info_sup1.pu16_term[1],
						loc_u_info_sup1.pu16_term[0]);
				strcat(loc_ps8_chaine, loc_ps8_ch_tempo);
				break;
			case EVT012_BASCULEMENT_VERS_CANAL:
				strcpy(loc_ps8_chaine,ps8ConvertChaineToSnmp(pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_evenement[loc_u16_indice_evt]));
				strcat(loc_ps8_chaine, " / ");
				sprintf(loc_ps8_ch_tempo, "(%d MHz / CH=%d)",
						loc_u_info_sup1.pu16_term[1],
						loc_u_info_sup1.pu16_term[0]);
				strcat(loc_ps8_chaine, loc_ps8_ch_tempo);
				break;
			case EVT013_CONNEXION_STATION:
			case EVT014_DECONNEXION_STATION:
			case EVT015_CONNEXION_ACCESS_POINT:
			case EVT016_DECONNEXION_ACCESS_POINT:
				strcpy(loc_ps8_chaine,ps8ConvertChaineToSnmp(pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_evenement[loc_u16_indice_evt]));
				strcat(loc_ps8_chaine, " / ");
				strcat(loc_ps8_chaine, ps8GetChAddressMac(loc_pu8_info_sup3));
				break;
			default:
				strcpy(loc_ps8_chaine,ps8ConvertChaineToSnmp(pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_evenement[loc_u16_indice_evt]));
				break;
		}
	}
	else
	{
		strcpy((s8sod *)loc_ps8_chaine,(const s8sod *)"?");
	}
}/*ChLibelleTrap*/

//=====================================================================================
// Fonction		: ReplayTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/12/2007 -
// Description	: Rejoue tous les traps de la table alarme
//=====================================================================================
void ReplayTrap(void)
{
	S_STRUCT_STA_TRAP	*loc_ps_encours;
	u16sod				loc_u16_cpt;

	loc_ps_encours = NULL; //INIT
	loc_u16_cpt = 0; //INIT
	
	if(ps_status_trap->ps_premier_trap != NULL) //CONDITION: liste non vide
	{
		loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
		loc_u16_cpt = 0; //INIT
		do{
			if(		((VAL_SNMP_ACQUITTER == loc_ps_encours->u8_val_snmp) ||	(VAL_SNMP_NON_ACQUITTER == loc_ps_encours->u8_val_snmp))
				&&	(TRUE == u8TestEvenementValide(loc_ps_encours->u16_index_evt))
			  )	//CONDITION: (trap acquitter ou non acquitter) et  ( etat debut) et (index evt valide)
			{
				loc_ps_encours->u32_cpt_emission_trap = 0;							//RAZ	
				loc_ps_encours->u32_cpt_interval_trap = 0;							//RAZ
				loc_ps_encours->u8_val_snmp = VAL_SNMP_NON_ACQUITTER;				//RAZ
			}

			//On passe au suivant
			loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
			loc_u16_cpt++;
		}while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP));
	}
	
}/*ReplayTrap*/


//=====================================================================================
// Fonction		: TestCoherenceValeurTrapAvecConfig
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 07/05/2008 -
// Description	: Test la cohérence des valeurs dans la table par
//					rapport à la configuration
//=====================================================================================
void TestCoherenceValeurTrapAvecConfig(void)
{
	s32sod	loc_s32_sem;
	
	S_STRUCT_STA_TRAP	*loc_ps_encours;
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_flag_presence;

	loc_u8_flag_presence = FALSE;	//INIT

	s32Lock_Get(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on lève le sem
	if(NULL == ps_status_trap->ps_premier_trap) //CONDITION: premier trap
	{
		;	//on ne fait rien
	}
	else
	{
		loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
		loc_u16_cpt = 0; //INIT
		while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP))
		{
			loc_u8_flag_presence = FALSE;	//RAZ
			
			//d: Ajouter condition
			// ...............
			loc_u8_flag_presence = TRUE;
			//f: Ajouter condition

			if(FALSE == loc_u8_flag_presence) //CONDITION: valeur non présente
			{
				if(		(ETAT_EVT_DEBUT != loc_ps_encours->u8_etat_evt)
					&&	(loc_ps_encours->u32_cpt_emission_trap >= 1)
				  ) //CONDITION: on ne peut pas supprimer si l'évt est à DEBUT ET trap émis au moins 1 fois
				{
					loc_ps_encours->u8_val_snmp = VAL_SNMP_SUPPRIMER; //on supprime car config incohérente avec table alarme
				}
			}
			
			//On passe au suivant
			loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
			loc_u16_cpt++;
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on relache le sem
	
}/*TestCoherenceValeurTrapAvecConfig*/

//=====================================================================================
// Fonction		: CopyStatusToCipTrap
// Entrees		: <loc_ps_trap<	: status trap 
//				: <loc_ps_elt_statustrap<	: element cip trap qui doit etre ajouté à StatutTrap
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: transfert statut des TRAPs dans cip élement status trap
//=====================================================================================
void CopyStatusToCipTrap(S_STRUCT_STA_TRAP *loc_ps_trap, S_STRUCT_CIP_ELEMENT_STATUSTRAP *loc_ps_elt_statustrap)
{
	loc_ps_elt_statustrap->u16_idx_table = loc_ps_trap->u16_idx_table;	//MAJ
	loc_ps_elt_statustrap->u16_index_evt = loc_ps_trap->u16_index_evt;	//MAJ
	loc_ps_elt_statustrap->t_valeur_evt = loc_ps_trap->t_valeur_evt;	//MAJ
	loc_ps_elt_statustrap->s_date = loc_ps_trap->s_date;				//MAJ
	loc_ps_elt_statustrap->u8_val_snmp = loc_ps_trap->u8_val_snmp;		//MAJ
	loc_ps_elt_statustrap->u8_etat_evt = loc_ps_trap->u8_etat_evt;		//MAJ
	loc_ps_elt_statustrap->u8_info_sup2 = loc_ps_trap->u8_info_sup2;	//MAJ
	memcpy(loc_ps_elt_statustrap->pu8_tab_info_sup3, loc_ps_trap->pu8_tab_info_sup3, TAILLE_MAX_TAB_INFO_SUP3);  //MAJ
}/*CopyStatusToCipTrap*/

//=====================================================================================
// Fonction		: EditFileStatutTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Edition du fichier statut trap
//=====================================================================================
void EditFileStatutTrap(void)
{
	s32sod	loc_s32_sem;
	S_STRUCT_CIP_ELEMENT_STATUSTRAP loc_s_elt_statustrap;
	S_STRUCT_STA_TRAP	*loc_ps_encours;
	u16sod				loc_u16_cpt;

	memset(&loc_s_elt_statustrap, 0, sizeof(S_STRUCT_CIP_ELEMENT_STATUSTRAP)); //INIT
	loc_ps_encours = NULL; //INIT
	loc_u16_cpt = 0; //INIT

	s32Lock_Get(SEMAPHORE_BDD_CIP_STATUSTRAP, &loc_s32_sem);	//on lève le sémaphore
	
	//On supprime le fichier cip_statustrap
	u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_STATUSTRAP_INI.ps8_path_file);
	
	if(ps_status_trap->ps_premier_trap != NULL) //CONDITION: liste non vide
	{
		loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
		loc_u16_cpt = 0; //INIT
		do{
			if(TRUE == u8TestEvenementValide(loc_ps_encours->u16_index_evt))
			{
				CopyStatusToCipTrap(loc_ps_encours,&loc_s_elt_statustrap);

				if(FALSE == u8AddCipStatusTrap(&loc_s_elt_statustrap, &T_DEF_FILE_CIP_STATUSTRAP_INI))
				{
					MACRO_PRINTF(("EditFileStatutTrap: Erreur\n"));
					loc_u16_cpt = TAILLE_MAX_TABLE_STATUSTRAP+1; //on sort
				}
			}

			//On passe au suivant
			loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
			loc_u16_cpt++;
		}while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP));
	}

	s32Lock_Release(SEMAPHORE_BDD_CIP_STATUSTRAP, &loc_s32_sem);	//on relache le sem
	
}/*EditFileStatutTrap*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du module de ExecTrap
//=====================================================================================
void InitModule_ExecTrap(void)
{
	gettimeofday(&s_timevalnow, (struct timezone *) NULL); //INIT

	memset(&s_cip_snmpd_courant, 0, sizeof(S_STRUCT_CIP_SNMPD)); //INIT
	u8_premier_passage = TRUE;	//INIT

#if DEBUG_PERFORMANCE_EXECTRAP
//d: debug - mesure timing
	gettimeofday(&t_time1, (struct timezone *) NULL); //INIT
	gettimeofday(&t_time2, (struct timezone *) NULL); //INIT
//f: debug - mesure timing
#endif

}/*InitModule_ExecTrap*/

