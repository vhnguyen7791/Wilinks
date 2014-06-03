/*========================================================================*/
/* NOM DU FICHIER  : execjdb.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Jdb: Processus de gestion du journal de bord	      */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION (à partir source SDVB200 - BE374)
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère le journal de bord

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECJDB

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

//Fichiers temporaires
#define FILE_CIP_FIFOJDB_JDB_LINE	PATH_DIR__BDD_EVT "cip_fifojdb.jdb.line"
#define FILE_CIP_FIFOJDB_TEMPO		PATH_DIR__BDD_EVT "cip_fifojdb.tmp"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Fifo intermédiaire entre le fichier cip_fifojdb et les fichiers jdbpart de la flash
static u16sod u16_wr_fifointerjdb;
static S_STRUCT_JDBEVT ps_fifoInterJdb[TAILLE_MAX_CIP_ELEMENTS_FIFOJDB];

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0);

//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0)
{
	printf("Usage: %s [-OPTION]\n"
		   "	 \n"
		   ,loc_ps8_argv0);
}/*proc_Usage*/

//=====================================================================================
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: PROCESSUS JDB
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	S_STRUCT_CIP_MONITOR loc_s_cip_monitor_tempo;
	u16sod loc_u16_i;
	s32sod	loc_s32_sem;
	S_STRUCT_CIP_JDB loc_s_cip_jdb_tempo;
	u16sod  loc_u16_nbEltJdbTotal;
	u16sod	loc_u16_nbEltJdbLus;
	u8sod	loc_u8_flag_maj_jdb;
	u8sod	loc_u8_etat_bddcfg;
	
	printf("Debut processus jdb... \n");

	//-----------------------------------------------
	//Initialisation des variables locales
	//-----------------------------------------------
	memset(&loc_s_cip_monitor_tempo, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT
	memset(&loc_s_cip_jdb_tempo, 0, sizeof(S_STRUCT_CIP_JDB)); //INIT
	loc_u16_nbEltJdbTotal = 0;	//INIT
	loc_u16_nbEltJdbLus = 0;	//INIT
	loc_u8_flag_maj_jdb = TRUE;	//INIT
	loc_u8_etat_bddcfg = TRUE;	//INIT

	//-----------------------------------------------
	//Test des arguments passés
	//-----------------------------------------------
	if(loc_s32_argc >= 2)//CONDITION: nombre d'argument insufisant
	{
		if (0 == strcmp(loc_pps8_argv[1],"-help"))
		{
			proc_Usage((s8sod *)loc_pps8_argv[0]);
			exit(1);
		}
	}

	//-----------------------------------------------
	//Initialisation propres à ce processus
	//-----------------------------------------------
	InitModule_ExecJdb();
	InitModule_JdbFlash();

	//-----------------------------------------------
	//Initialisation des modules de la librairie system
	//-----------------------------------------------
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(AddMsgDbgLog);
	
	//-----------------------------------------------
	//Initialisation des modules de la librairie bdd
	//-----------------------------------------------
	InitModule_LibraryBdd();

	//---------------------------------------------------------------
	//Lecture des informations CIP propres au processus jdb
	//---------------------------------------------------------------
	printf("Jdb: Lecture bdd cip ... \n");
	s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillCipJdb(&s_cip_jdb_courant)) //INIT
	{
		printf("Jdb: Lecture bdd cip : KO \n");
		MACRO_PRINTF(("Processus jdb: Probleme de lecture de la base de donnees (cip jdb)... \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem

	//---------------------------------------------------------------
	//Lecture du fichier 
	//---------------------------------------------------------------
	printf("Jdb: Lecture bdd JDB ... \n");
	s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_RAM)) //INIT
	{
		printf("Jdb: Lecture bdd jdb : KO \n");
		MACRO_PRINTF(("Processus jdb: Probleme de lecture de la base de donnees (jdb)... \n"));
	}
	printf("Jdb: Pour information rd=%d / wr=%d / nbevt_jdbpart_encours=%d / nb_total_evt=%d \n",
		   s_statutjdb_courant.u8_numrd_jdbpart,
		   s_statutjdb_courant.u8_numwr_jdbpart,
		   s_statutjdb_courant.u16_nbevt_jdbpart_encours,
		   s_statutjdb_courant.u16_nb_total_evt);
	s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
	
	
	//-----------------------------------------------
	//				Tache de fond
	//-----------------------------------------------
	do{

		//-----------------------------------------------
		//Tempo
		//-----------------------------------------------
		sleep(1);

		//---------------------------------------------------------------
		//Lecture des informations CIP propres au processus jdb
		//---------------------------------------------------------------
		s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillCipJdb(&loc_s_cip_jdb_tempo))
		{
			//Copie tempo => courant
			s_cip_jdb_courant = loc_s_cip_jdb_tempo; //MAJ

			Raz_Cip_Jdb(&loc_s_cip_jdb_tempo);
			u8EditCipJdb(&loc_s_cip_jdb_tempo);
		}
		s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem

		//---------------------------------------------------------------
		//Surveillance de la CIP d'échange des évènements du JDB
		//---------------------------------------------------------------
		s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on lève le sémaphore
		//RAZ de la fifo intermédaire (du jdb)
		InitFifoInterJdb(); //RAZ
		//Lecture du fichier cip_fifojdb => ajout dans fifo intermédiaire
		if(FALSE == u8ReadCipFifoJdb(&T_DEF_FILE_CIP_FIFOJDB_INI, u8AjouteEvtFifoInterJdb, &loc_u16_nbEltJdbLus))
		{
			MACRO_PRINTF(("ExecJdb: ERREUR LECTURE CIP => Suppresion fichier %s \n",
						  T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file));
		}
		//On supprime le fichier cip_fifojdb (original)
		u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file);
		//Puis on crée un fichier vide
		CmdSystem_Generique("touch %s",
							T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file);
		s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on relache le sem

		//-----------------------------------------------
		//Ordre raz du jdb
		//-----------------------------------------------
		if(TRUE == s_cip_jdb_courant.u8_effacer_jdb)
		{
			s_cip_jdb_courant.u8_effacer_jdb = FALSE;	//RAZ au cas où
			
			s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
			if(TRUE == u8FillStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_RAM)) 
			{
				RazJournalDeBord(&s_statutjdb_courant);
			}
			s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem


			//On signale le RAZ au processus monitor
			s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
			if(TRUE == u8FillCipMonitor(&loc_s_cip_monitor_tempo))
			{
				loc_s_cip_monitor_tempo.u8_raz_jdb = TRUE;	//activé
				u8EditCipMonitor(&loc_s_cip_monitor_tempo);
			}
			s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
		}

		//-----------------------------------------------
		//Gestion sauvegarde en Flash
		//-----------------------------------------------
		if((loc_u16_nbEltJdbLus != u16_wr_fifointerjdb)||
		   (loc_u16_nbEltJdbLus >= TAILLE_MAX_CIP_ELEMENTS_FIFOJDB)||
		   (u16_wr_fifointerjdb >= TAILLE_MAX_CIP_ELEMENTS_FIFOJDB)
		  )//CONDITION: incohérence entre lecture fichier cip_fifojdb et fifoInterJdb
		{
			MACRO_PRINTF(("ExecJdb: Erreur incompatibilite entre cip_fifojdb et fifoInter (%d / %d) \n",
						  loc_u16_nbEltJdbLus, u16_wr_fifointerjdb));
		}
		else	//CONDITION: cohérence entre lecture fichier cip_fifojdb et fifoInterJdb
		{
			//On peut sauver les nouveaux évènements dans la FLASH
			s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore

			if(TRUE == u8FillStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_RAM)) 
			{
				loc_u8_flag_maj_jdb = TRUE;	//RAZ
				//On lit la fifo intermédaire
				for(loc_u16_i=0;loc_u16_i<u16_wr_fifointerjdb;loc_u16_i++)
				{
					if(FALSE == u8AjouteEvtJdbFlash(&ps_fifoInterJdb[loc_u16_i])) //CONDITION: Erreur lecture
					{
						loc_u8_flag_maj_jdb = FALSE;
					}
//					printf("execJdb:%d/%d \n",
//						   s_statutjdb_courant.u16_nbevt_jdbpart_encours,
//						   s_statutjdb_courant.u16_nb_total_evt);
					
				}
				
				if(FALSE == loc_u8_flag_maj_jdb) //CONDITION: Erreur génération du fichier
				{
					MACRO_PRINTF(("ExecJdb: Erreur ecriture évènement dans JDB de la FLASH \n"));
					RazJournalDeBord(&s_statutjdb_courant);
				}
				
				u8EditStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_RAM);
			}
			
			s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
		}


		//-----------------------------------------------
		//Ordre génération du fichier jdb.log
		//-----------------------------------------------
		if(TRUE == s_cip_jdb_courant.u8_generer_jdb)
		{
			s_cip_jdb_courant.u8_generer_jdb = FALSE;	//RAZ au cas où

			//On supprime d'abord le fichier jdb.log
			u8CmdSystem_RemoveFile(FICHIER_JDB_EQUIPMENT);

			//Comme on a terminé avec la fifoInterJdb (car ici on va l'utiliser)
			InitFifoInterJdb();	//RAZ
			
			loc_u8_etat_bddcfg = TRUE;	//RAZ
			//Lecture de la configuration
			s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
			if(FALSE == u8FillConfigAdmin(&s_config_process_jdb))
			{
				loc_u8_etat_bddcfg = FALSE;	//defaut accès bdd
				MACRO_PRINTF(("ExecJdb: Lecture configuration impossible \n"));
			}
			s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

			if(TRUE == loc_u8_etat_bddcfg)
			{
				s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
				//Puis édition du fichier
				if(FALSE == u8CreationFichierJdbLog(s_config_process_jdb.s_admin.u8_langue))
				{
					MACRO_PRINTF(("ExecJdb: Erreur generation %s\n",FICHIER_JDB_EQUIPMENT));
				}
				s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
			}
			else
			{
				MACRO_PRINTF(("ExecJdb: Erreur generation %s\n",FICHIER_JDB_EQUIPMENT));
			}
		}
		
	}while(1);

	return 1;
}/*main*/


//=====================================================================================
// Fonction		: u8AjouteEvtFifoInterJdb
// Entrees		: <loc_ps_elt_fifojdb<	: element qui doit etre ajouté
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ajoute element jdb dans la fifo intermédiaire
//=====================================================================================
u8sod u8AjouteEvtFifoInterJdb(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = TRUE; //INIT

	if(u16_wr_fifointerjdb < TAILLE_MAX_CIP_ELEMENTS_FIFOJDB)
	{
		//Copie du contenu de l'élément du fichier fifojdb dans la fifo intermédiaire (ram)
		ps_fifoInterJdb[u16_wr_fifointerjdb] = (*loc_ps_elt_fifojdb);

		//Puis on incrémente le pointeur d'écriture
		u16_wr_fifointerjdb ++;		
	}
	else
	{
		MACRO_PRINTF(("u8AjouteEvtFifoInterJdb: Erreur ponteur d'écriture FifoInterJdb => %d \n",
					  u16_wr_fifointerjdb));
	}

	return loc_u8_resultat;
}/*u8AjouteEvtFifoInterJdb*/

//=====================================================================================
// Fonction		: u8CreationFichierJdbLog
// Entrees		: <loc_u8_langue> : langue
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Génération du fichier Jdb.log
//=====================================================================================
u8sod u8CreationFichierJdbLog(u8sod	loc_u8_langue)
{
	u8sod loc_u8_resultat;
	FILE *	loc_pf_jdblog;
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_numid_jdbpart;
	u16sod	loc_u16_nb_evt_lus;

	loc_u8_resultat = TRUE;	//INIT
	loc_u16_cpt = 0;	//INIT
	loc_u8_numid_jdbpart = 0;	//INIT
	loc_u16_nb_evt_lus = 0;	//INIT

	if(NULL == (loc_pf_jdblog = fopen(FICHIER_JDB_EQUIPMENT, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierJdbLog: Erreur creation fichier %s\n",FICHIER_JDB_EQUIPMENT));
		loc_u8_resultat = FALSE;
	}
	else
	{
		//Parcours le JDB de l'évènement le plus récent à l'évènement le plus ancien
		loc_u16_cpt = 0;	//RAZ
		loc_u8_numid_jdbpart = s_statutjdb_courant.u8_numwr_jdbpart; //RAZ: du dernier fichier en cours d'écriture
		while(loc_u16_cpt < NB_MAX_JDBPART)
		{
			InitFifoInterJdb();	//RAZ
			//Lecture total d'un fihier jdbpart
			if(FALSE == u8ReadEvtJdbPart(&T_DEF_FILE_JDBPART, loc_u8_numid_jdbpart, u8AjouteEvtFifoInterJdb, &loc_u16_nb_evt_lus))
			{
				loc_u16_cpt = NB_MAX_JDBPART+1; //on sort
				MACRO_PRINTF(("u8CreationFichierJdbLog: Erreur lecture %s \n",
							  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
				loc_u8_resultat = FALSE;
			}
			else
			{
				if(loc_u16_nb_evt_lus > NB_MAX_EVT_PAR_JDBPART)
				{
					loc_u16_cpt = NB_MAX_JDBPART+1; //on sort
					MACRO_PRINTF(("u8CreationFichierJdbLog: Erreur nb_evt_lus=%d dans %s KO \n",
								  loc_u16_nb_evt_lus,
								  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
					loc_u8_resultat = FALSE;
				}
				else //CONDITION: lecture OK
				{
					AjoutJdbPartToJdbLog(loc_u16_nb_evt_lus, loc_pf_jdblog, loc_u8_langue);
				}
			}

			loc_u16_cpt ++;
			if(loc_u8_numid_jdbpart == s_statutjdb_courant.u8_numrd_jdbpart) //CONDITION: on a tout lu
			{
				loc_u16_cpt = NB_MAX_JDBPART+1;	//on sort
			}
			else
			{
				//on passe à un autre fichier jdbpart
				if(loc_u8_numid_jdbpart > 0)
				{
					loc_u8_numid_jdbpart --;
				}
				else
				{
					loc_u8_numid_jdbpart = (NB_MAX_JDBPART-1);	//RAZ
				}
			}
		}
		
		fclose(loc_pf_jdblog);
	}

	return loc_u8_resultat;
}/*u8CreationFichierJdbLog*/

//=====================================================================================
// Fonction		: AjoutJdbPartToJdbLog
// Entrees		: <loc_u16_nb_evt_lus> : nombre d'évènements lus du fichier jdbpart
//				: <loc_pf_jdblog< : pointeur sur fichier jdb.log
//				: <loc_u8_langue> : langue
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Edition du fichier jdb.log en transferant tous les évènements de jdbpart dans jdb.log
//=====================================================================================
void AjoutJdbPartToJdbLog(u16sod loc_u16_nb_evt_lus, FILE *	loc_pf_jdblog, u8sod loc_u8_langue)
{
	u8sod loc_u8_resultat;
	u16sod loc_u16_idx;
	u16sod loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_u16_idx = 0;	//INIT
	loc_u16_cpt = 0;	//INIT

	if(loc_u16_nb_evt_lus > 0)
	{
		//On lit la fifo à l'envers (du plus récent au plus ancient)
		loc_u16_idx = (loc_u16_nb_evt_lus-1);
		loc_u16_cpt = 0;
		do{
			EditionEvtJdbLog(&ps_fifoInterJdb[loc_u16_idx], loc_pf_jdblog, loc_u8_langue);
			if(0 == loc_u16_idx) //CONDITION: dernier évt
			{
				loc_u8_resultat = FALSE; //on sort
			}
			else
			{
				loc_u16_idx--;
			}
			loc_u16_cpt++;
		}while((TRUE == loc_u8_resultat)&&
			   (loc_u16_cpt < NB_MAX_EVT_PAR_JDBPART)
			  );
	}

}/*AjoutJdbPartToJdbLog*/

//=====================================================================================
// Fonction		: EditionEvtJdbLog
// Entrees		: <loc_ps_evt<	: element qui doit etre édité
//				: <loc_pf_jdblog< : pointeur sur fichier jdb.log
//				: <loc_u8_langue> : langue
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Edition de la ligne de l'évènement dans fichier jdb.log
//=====================================================================================
void EditionEvtJdbLog(S_STRUCT_JDBEVT *loc_ps_evt, FILE *loc_pf_jdblog, u8sod loc_u8_langue)
{
	u16sod	loc_u16_indEvt;
	s8sod	loc_ps8_date[UI_TAILLE_MAX_MESSAGE+1];
	s8sod	loc_ps8_chaine_type_evt[UI_TAILLE_MAX_MESSAGE+1];
	s8sod	*loc_ps8_chaine_libelle;

	loc_u16_indEvt = loc_ps_evt->u16_index_evt; //MAJ
	strcpy(loc_ps8_date, "");	//INIT
	strcpy(loc_ps8_chaine_type_evt, "");	//INIT
	loc_ps8_chaine_libelle = NULL;	//INIT

	if(loc_u16_indEvt < NB_MAX_EVENEMENTS) //CONDITION: evt valide
	{
		//Date
		strcpy(loc_ps8_date, ps8GetChDate(&loc_ps_evt->s_date));

		//Type
		switch(loc_ps_evt->u8_etat_evt)
		{
			case ETAT_EVT_DEBUT:
				strcpy(loc_ps8_chaine_type_evt, pt_tb_msg[loc_u8_langue].ps8_msg_debut);
				break;
			case ETAT_EVT_FIN:
				strcpy(loc_ps8_chaine_type_evt, pt_tb_msg[loc_u8_langue].ps8_msg_fin);
				break;
			case ETAT_EVT_INFO:
				strcpy(loc_ps8_chaine_type_evt, pt_tb_msg[loc_u8_langue].ps8_msg_info);
				break;
			default:
				strcpy(loc_ps8_chaine_type_evt, "?");
				break;
		}

		loc_ps8_chaine_libelle = ps8ChLibelleEvt(loc_u16_indEvt,
								loc_ps_evt->t_valeur_evt,
								loc_ps_evt->u_info_sup1.u32_term,
								loc_ps_evt->u8_info_sup2,
								loc_ps_evt->pu8_tab_info_sup3,
								loc_ps_evt->u8_etat_evt,
								loc_u8_langue,
								MODE_AFF_LIB_EVT_POUR_FICHIER);

		fprintf(loc_pf_jdblog,"%-23s\t%-10s\t%s\r\n",
				loc_ps8_date,
				loc_ps8_chaine_type_evt,
				loc_ps8_chaine_libelle);
	}
}/*EditionEvtJdbLog*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitFifoInterJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation de la fifo intermédiaire (du jdb)
//=====================================================================================
void InitFifoInterJdb(void)
{
	u16sod loc_u16_i;

	//Initialisation de la fifo intermédiaire (du jdb)
	u16_wr_fifointerjdb = 0;	//INIT
	for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_CIP_ELEMENTS_FIFOJDB;loc_u16_i++)
	{
		InitEvtJdb(&ps_fifoInterJdb[loc_u16_i]); //INIT
	}

}/*InitFifoInterJdb*/

//=====================================================================================
// Fonction		: InitModule_ExecJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation du module de ExecJdb
//=====================================================================================
void InitModule_ExecJdb(void)
{
	memset(&s_cip_jdb_courant, 0, sizeof(S_STRUCT_CIP_JDB)); //INIT
	memset(&s_statutjdb_courant, 0, sizeof(S_STRUCT_STATUTJDB)); //INIT
	memset(&s_config_process_jdb,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT

	//Initialisation de la fifo intermédiaire (du jdb)
	InitFifoInterJdb(); //INIT

}/*InitModule_ExecJdb*/

