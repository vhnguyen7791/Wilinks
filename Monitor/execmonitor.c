/*========================================================================*/
/* NOM DU FICHIER  : execmonitor.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Processus monitor de l'application				      */
/* Projet          : WRM100	                                              */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
// - Ajout calcul evt EquipmentOn
//BE017 12/03/2010 CM
// - Correction bug evt Equipment ON non calculé
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
// - Ajout exploitation du client NTP
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Incohérence horodatage de l'action suppression jdb et de l'évènement
//BE058 21/01/2011 CM
// - Synchronisation configuration / exploitation
// - Ajout nouveaux évènements liés au DFS
//BE062.0 13/09/2011 JP
// - Gestion des leds de la carte CPU

/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECMONITOR

#define TIME_OUT_CALCUL_ALARME	10	//secondes


/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

#define FICHIER_SYS_LED1 PATH_DIR_PROC "sys/wrm100/led1"
#define FICHIER_SYS_LED2 PATH_DIR_PROC "sys/wrm100/led2"
#define FICHIER_SYS_LED3 PATH_DIR_PROC "sys/wrm100/led3"
#define FICHIER_SYS_CFGDFT PATH_DIR_PROC "sys/wrm100/conf_def"
/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Configuration tempo
static S_STRUCT_CONFIGURATION s_config_tempo;

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
// Auteur		: CM - 01/03/2010 -
// Description	: PROCESSUS MONITOR
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	struct timeval  loc_t_time1;
	struct timeval  loc_t_time2;
	s32sod	loc_s32_sem;
	s32sod	loc_s32_synchro;
	u8sod	loc_u8_cpt_demarrage_process;

//d:BE062.0 JP : Gestion des leds de la carte CPU
	FILE	*loc_p_handle;
	u8sod	loc_u8_etat_alarme_lan, loc_u8_etat_alarme;
	s8sod	loc_ps8_chaine10[10+1];//au max on a besoin de 1+1 caracteres
	u8sod	loc_u8_etat_entree_cfg_dft;

	loc_u8_etat_entree_cfg_dft=0;
//f:BE062.0 JP : Gestion des leds de la carte CPU
			
	printf("Debut processus Monitor... \n");

	//-----------------------------------------------
	//Initialisation des variables locales
	//-----------------------------------------------
	gettimeofday(&loc_t_time1, (struct timezone *) NULL); //INIT
	gettimeofday(&loc_t_time2, (struct timezone *) NULL); //INIT
	loc_u8_cpt_demarrage_process = 0;	//INIT

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
	InitModule_ExecMonitor();
	InitModule_CustomBdd();
	InitModule_ExecEvent();
	InitModule_InternEvent();
	InitModule_Evt_Generique();
	InitModule_Evt_Debug();
	InitModule_Evt_System();
	InitModule_Evt_STA();
	InitModule_Evt_AP();
	InitModule_GestExploit();
	InitModule_Exp_Versions();
	InitModule_Exp_Network();
	InitModule_Exp_Wifi_Station();
	InitModule_Exp_Wifi_AP();
	InitModule_Exp_Dhcp();
	InitModule_Exp_Ntp();
	InitModule_Exp_Sntp();
#ifdef _WRM100_ABG_SELECT
	InitModule_Exp_Wlan_ABG();
#endif
#ifdef _WRM100_N_SELECT
	InitModule_Exp_Wlan_N();
#endif

	//-----------------------------------------------
	//Initialisation des modules de la librairie system
	//-----------------------------------------------
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(AddMsgDbgLog);
	SetConfig_SetDateManuelle();
	
	//-----------------------------------------------
	//Initialisation des modules de la librairie bdd
	//-----------------------------------------------
	InitModule_LibraryBdd();

	//-----------------------------------------------
	//Initialisation des modules de la librairie Network
	//-----------------------------------------------
	InitModule_LibraryNetwork();

	//-----------------------------------------------
	//Initialisation des modules de la librairie Wifi
	//-----------------------------------------------
	InitModule_LibraryWifi();
	
	//---------------------------------------------------------------
	//Lecture des informations CIP propres au processus monitor
	//---------------------------------------------------------------
	printf("Monitor: Lecture bdd cip ... \n");
	s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillCipMonitor(&s_cip_monitor_courant)) //INIT
	{
		printf("Monitor: Lecture bdd cip : KO \n");
		MACRO_PRINTF(("Processus Monitor: Probleme de lecture de la base de donnees (cip monitor)... \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
	
	//-----------------------------------------------
	//Lecture de la base de données configuration (INITIALISATION)
	//-----------------------------------------------
	printf("Monitor: Lecture bdd config ... \n");
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigEquipement(&s_config_process_mntr)) //INIT
	{
		printf("Monitor: Lecture bdd config : KO \n");
		MACRO_PRINTF(("Processus Monitor: Probleme de lecture de la base de donnees (CONFIG)... \n"));
	}
	MiseAJourConfigToAllStateEvt(&s_config_process_mntr);
	s_config_tempo = s_config_process_mntr; //INIT
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//-----------------------------------------------
	//Lecture de la base de données evenements systeme (INITIALISATION)
	//-----------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillEventSystemFile(pt_process_eventsystem))
	{
		printf("Monitor: lecture bdd EventSystem KO \n");
		MACRO_PRINTF(("Processus Monitor: Probleme de lecture de la base de donnees (EventSystem)... \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem
	
	//-----------------------------------------------
	//Lecture de la base de données exploitation (INITIALISATION)
	//-----------------------------------------------
	printf("Monitor: Lecture bdd exploit ...\n");
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitEquipement(&s_exploit_process_mntr)) //INIT
	{
		printf("Monitor: Lecture bdd exploit : KO \n");
		MACRO_PRINTF(("Processus Monitor: Probleme de lecture de la base de donnees (EXPLOIT) ... \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	//-----------------------------------------------
	//Lecture de la base de données exploit des évènements (INITIALISATION)
	//-----------------------------------------------
	printf("Monitor: Lecture bdd evenement (exp) ...\n");
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitEventsGlobalFile(&s_exp_events_process_mntr)) //INIT
	{
		printf("Monitor: Lecture bdd evenement (exp) : KO \n");
		MACRO_PRINTF(("Processus Monitor: Probleme de lecture de la base de donnees (EXPLOIT EVENEMENT) ... \n"));
	}
	else
	{
		RazExploitEvents_FonctionConfig(&s_exp_events_process_mntr, &s_config_process_mntr);
		u8EditExploitEventsGlobalFile(&s_exp_events_process_mntr); 
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	//-----------------------------------------------
	//Mise à jour de données exploitation (INITIALISATION)
	//-----------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	//Lecture des versions logicielles
	MiseAjour_Versions(&s_exploit_process_mntr);
	//Lecture des adresses MAC des interfaces
	MiseAjour_ExploitAdressMAC(&s_exploit_process_mntr);
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	//RAZ des alarmes mémoriséesMise à jour horodatage de l'heure de reset des alarmes mémorisées
	SetDate(&s_exp_events_process_mntr.s_date_dernier_reset, METHODE_SETDATE_MANUEL); //MAJ: INIT


	//Personalisation bdd des évènements
	CustomBddEvents_EnFonctionConfig(&s_config_process_mntr, pt_process_eventsystem); //INIT
	
	//-----------------------------------------------
	//Evenement EquipementON
	//-----------------------------------------------
	Calcul_Evt_EquipmentOn(&s_config_process_mntr);
	

	//-----------------------------------------------
	//				Tache de fond
	//-----------------------------------------------
	do{
		usleep(300000); //tempo de 300 ms

		//-----------------------------------------------
		//Génération seconde
		//-----------------------------------------------
		gettimeofday(&loc_t_time1, (struct timezone *) NULL);
		if(loc_t_time1.tv_sec != loc_t_time2.tv_sec) //CONDITION: nouvelle seconde
		{
			loc_t_time2 = loc_t_time1; //RAZ

			//******** d: SYNCHRO CONFIG / EXPLOIT ******************************
			s32Lock_Get(SEMAPHORE_SYNCHRO_PRNCPL_MNTR, &loc_s32_synchro);	//on lève le sémaphore
			
			//on sauve la date/heure de la seconde
			SetConfig_SetDateManuelle();

			if(loc_u8_cpt_demarrage_process < TIME_OUT_CALCUL_ALARME) //CONDITION: démarrage
			{
				loc_u8_cpt_demarrage_process ++;

				//-----------------------------------------------
				//Lecture de la configuration de l'équipement
				//-----------------------------------------------
				LectureConfigurationEquipement_PourProcessus();	//MAJ

				//-----------------------------------------------
				//On met à jour la base de données (si necessaire)
				//-----------------------------------------------
				CustomBdd_EnFonctionConfig(&s_config_process_mntr);

				//-----------------------------------------------
				// La BBD étant partagée par d'autres processus, on protège par sémaphore
				//-----------------------------------------------
				s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore

				//Mise à jour des evts
				CalculEvent_PbConfig(&s_config_process_mntr, &s_exploit_process_mntr);
				
				//-----------------------------------------------
				//Calcul JDB/TRAP/EXPLOIT des évènements
				//-----------------------------------------------
				GestionExecEvent(&s_exp_events_process_mntr);

				//-----------------------------------------------
				//Edition de l'exploitation des évènements
				//-----------------------------------------------
				if(FALSE == u8EditExploitEventsGlobalFile(&s_exp_events_process_mntr))
				{
					MACRO_PRINTF(("Monitor: Erreur Edition exploit events \n"));
				}
				
				s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le semaphore

//d:BE062.0 JP : Gestion des leds de la carte CPU et du passage en config par defaut
				
				//test de l'état de l'entree config par defaut (PSC3_7)
				if(NULL != (loc_p_handle = fopen( FICHIER_SYS_CFGDFT, "rt" )))
				{
							//Lecture de la ligne
					if (NULL != fgets(loc_ps8_chaine10,5,loc_p_handle))
					{
						if (loc_ps8_chaine10[0] == 0x30)
						{
							//on lit un 0, on incremente le nb de lecture
							loc_u8_etat_entree_cfg_dft++;
						}
						
					}
					//fermeture du fichier
					fclose (loc_p_handle);
				}					
				
				
				//Gestion de la led "alim", en fait demarrage : toujours allume
				if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED1, "wt" )))
				{
					fprintf(loc_p_handle,"1");
					//fermeture du fichier
					fclose (loc_p_handle);
				}					
				
				//Gestion de la led alarme LAN
				loc_u8_etat_alarme_lan=0;
				loc_u8_etat_alarme=u8GetEtatAlarme(&s_exp_events_process_mntr,EVT003_AL_ETHERNET_LAN_1);
				//alarme si cfg_valid et si etat courant
				if((TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID)) &&
					(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT)))
				{
					loc_u8_etat_alarme_lan=1;
				}
				loc_u8_etat_alarme=u8GetEtatAlarme(&s_exp_events_process_mntr,EVT004_AL_ETHERNET_LAN_2);
				//alarme si cfg_valid et si etat courant
				if((TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID)) &&
				   (TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT)))
				{
					loc_u8_etat_alarme_lan=1;
				}

				if (loc_u8_etat_alarme_lan==1)
				{ //on eteint la led2
					if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED2, "wt" )))
					{
						fprintf(loc_p_handle,"0");
						//fermeture du fichier
						fclose (loc_p_handle);
					}					
				}
				else
				{ //on allume la led2
					if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED2, "wt" )))
					{
						fprintf(loc_p_handle,"1");
						//fermeture du fichier
						fclose (loc_p_handle);
					}					
				}


				//Gestion de la led WLAN
				switch(s_config_process_mntr.s_gene.u8_mode_radio_modem)
				{
					case MODE_RADIO_MODEM_STATION:
						if(STATUT_CONNEXION__ASSOCIATED == s_exploit_process_mntr.s_station.u8_statut_connexion)
						{
							//connecte: on allume la led led3
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								fprintf(loc_p_handle,"1");
								//fermeture du fichier
								fclose (loc_p_handle);
							}
							u8_monitor_etat_led3=1;
						}
						else
						{
							//deconnecte: on eteint la led led3
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								fprintf(loc_p_handle,"0");
								//fermeture du fichier
								fclose (loc_p_handle);
								u8_monitor_etat_led3=0;
							}
						}
						break;
					
					case MODE_RADIO_MODEM_ACCESS_POINT:
						if (0==s_exploit_process_mntr.s_access_point.u16_nb_associations)
						{
							//on allume la led led3
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								fprintf(loc_p_handle,"1");
								//fermeture du fichier
								fclose (loc_p_handle);
								u8_monitor_etat_led3=1;

							}
						}
						else
						{
							//on fait clignoter la led led3
							
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								if (u8_monitor_etat_led3==1)
								{
									fprintf(loc_p_handle,"0");
									u8_monitor_etat_led3=0;
								}
								else
								{
									fprintf(loc_p_handle,"1");
									u8_monitor_etat_led3=1;									
								}

								//fermeture du fichier
								fclose (loc_p_handle);
							}
						}
						break;
					default:
					case MODE_RADIO_MODEM_MONITOR:
						//on eteint la led led3
						if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
						{
							fprintf(loc_p_handle,"0");
								//fermeture du fichier
							fclose (loc_p_handle);
							u8_monitor_etat_led3=0;

						}
						break;
				}

//f:BE062.0 JP : Gestion des leds de la carte CPU
				
				

				
				//-----------------------------------------------
				//Fin exploitation
				//-----------------------------------------------
				GestionFinExploitation();
			}
			else
			{
				loc_u8_cpt_demarrage_process = TIME_OUT_CALCUL_ALARME+1; //on peut calculer les alarmes


//d:BE062.0 JP : passage en config par defaut sur boucle externe
				if (loc_u8_etat_entree_cfg_dft > 7)
				{ // les 7 premières secondes avec l'entree cfg par defaut a 0 => on passe en config par defaut
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					memset(&s_config_tempo,'\0',sizeof(S_STRUCT_CONFIGURATION)); //RAZ
					PassageConfigDefaut(&s_config_tempo, MODE_PASSAGECONFIGDEFAUT_TOTAL);
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

					//Puis on reset l'équipement
					OrdreResetUc();					
				}
//d:BE062.0 JP : passage en config par defaut sur boucle externe
				
				//-----------------------------------------------
				//Lecture de la configuration de l'équipement
				//-----------------------------------------------
				LectureConfigurationEquipement_PourProcessus();	//MAJ

				//-----------------------------------------------
				//On met à jour la base de données (si necessaire)
				//-----------------------------------------------
				CustomBdd_EnFonctionConfig(&s_config_process_mntr);
				
				//-----------------------------------------------
				// La BBD étant partagée par d'autres processus, on protège par sémaphore
				//-----------------------------------------------
				s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
				//-----------------------------------------------
				//Gestion de l'exploitation de l'équipement
				//-----------------------------------------------
				GestionExecExploitation(&s_config_process_mntr, &s_exploit_process_mntr);
				
				//Mise à jour des evts
				CalculEvent_PbConfig(&s_config_process_mntr, &s_exploit_process_mntr);
				CalculEvents_System(&s_config_process_mntr, &s_exploit_process_mntr);
				CalculEvents_STA(&s_config_process_mntr, &s_exploit_process_mntr);
				CalculEvents_AP(&s_config_process_mntr, &s_exploit_process_mntr);

				//-----------------------------------------------
				//Evenement Signe de Vie
				//-----------------------------------------------
				Calcul_Evt_SigneVie(&s_config_process_mntr);
				
#if TEST_DEBUG_EVENT
				//-----------------------------------------------
				//Evenements debug
				//-----------------------------------------------
				CalculEvents_Debug();
#endif

				//-----------------------------------------------
				//Calcul JDB/TRAP/EXPLOIT des évènements
				//-----------------------------------------------
				GestionExecEvent(&s_exp_events_process_mntr);

				//-----------------------------------------------
				//Edition de l'exploitation des évènements
				//-----------------------------------------------
				if(FALSE == u8EditExploitEventsGlobalFile(&s_exp_events_process_mntr))
				{
					MACRO_PRINTF(("Monitor: Erreur Edition exploit events \n"));
				}

				s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le semaphore


//d:BE062.0 JP : Gestion des leds de la carte CPU
				//Gestion de la led "alim", en fait demarrage : toujours allume
				if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED1, "wt" )))
				{
					fprintf(loc_p_handle,"1");
					//fermeture du fichier
					fclose (loc_p_handle);
				}					

				//Gestion de la led alarme LAN
				loc_u8_etat_alarme_lan=0;
				loc_u8_etat_alarme=u8GetEtatAlarme(&s_exp_events_process_mntr,EVT003_AL_ETHERNET_LAN_1);
				//alarme si cfg_valid et si etat courant
				if((TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID)) &&
				   (TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT)))
				{
					loc_u8_etat_alarme_lan=1;
				}
				loc_u8_etat_alarme=u8GetEtatAlarme(&s_exp_events_process_mntr,EVT004_AL_ETHERNET_LAN_2);
				//alarme si cfg_valid et si etat courant
				if((TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID)) &&
				   (TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT)))
				{
					loc_u8_etat_alarme_lan=1;
				}

				if (loc_u8_etat_alarme_lan==1)
				{ //on eteint la led2
					if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED2, "wt" )))
					{
						fprintf(loc_p_handle,"0");
						//fermeture du fichier
						fclose (loc_p_handle);
					}					
				}
				else
				{ //on allume la led2
					if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED2, "wt" )))
					{
						fprintf(loc_p_handle,"1");
						//fermeture du fichier
						fclose (loc_p_handle);
					}					
				}


				//Gestion de la led WLAN
				switch(s_config_process_mntr.s_gene.u8_mode_radio_modem)
				{
					case MODE_RADIO_MODEM_STATION:
						if(STATUT_CONNEXION__ASSOCIATED == s_exploit_process_mntr.s_station.u8_statut_connexion)
						{
							//connecte: on allume la led led3
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								fprintf(loc_p_handle,"1");
								//fermeture du fichier
								fclose (loc_p_handle);
							}
							u8_monitor_etat_led3=1;
						}
						else
						{
							//deconnecte: on eteint la led led3
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								fprintf(loc_p_handle,"0");
								//fermeture du fichier
								fclose (loc_p_handle);
								u8_monitor_etat_led3=0;
							}
						}
						break;

					case MODE_RADIO_MODEM_ACCESS_POINT:
						if (0==s_exploit_process_mntr.s_access_point.u16_nb_associations)
						{
							//on allume la led led3
							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								fprintf(loc_p_handle,"1");
								//fermeture du fichier
								fclose (loc_p_handle);
								u8_monitor_etat_led3=1;

							}
						}
						else
						{
							//on fait clignoter la led led3

							if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
							{
								if (u8_monitor_etat_led3==1)
								{
									fprintf(loc_p_handle,"0");
									u8_monitor_etat_led3=0;
								}
								else
								{
									fprintf(loc_p_handle,"1");
									u8_monitor_etat_led3=1;									
								}

								//fermeture du fichier
								fclose (loc_p_handle);
							}
						}
						break;
					default:
					case MODE_RADIO_MODEM_MONITOR:
						//on eteint la led led3
						if(NULL != (loc_p_handle = fopen( FICHIER_SYS_LED3, "wt" )))
						{
							fprintf(loc_p_handle,"0");
								//fermeture du fichier
							fclose (loc_p_handle);
							u8_monitor_etat_led3=0;

						}
						break;
				}

//f:BE062.0 JP : Gestion des leds de la carte CPU


				//-----------------------------------------------
				//Fin exploitation
				//-----------------------------------------------
				GestionFinExploitation();
				
				//d: debug performance
//				gettimeofday(&loc_t_time1, (struct timezone *) NULL);
//				MACRO_PRINTF(("Monitor: %d us\n",
//							  ((loc_t_time1.tv_sec - loc_t_time2.tv_sec)*1000000 + (loc_t_time1.tv_usec - loc_t_time2.tv_usec))));
				//f: debug performance
				
			}

			s32Lock_Release(SEMAPHORE_SYNCHRO_PRNCPL_MNTR, &loc_s32_synchro);	//on relache le sem
			//******** f: SYNCHRO CONFIG / EXPLOIT ******************************
		}

	}while(1);
	
	return 0;
}/*main*/

//=====================================================================================
// Fonction		: GestionFinExploitation
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/12/2010 -
// Description	: Gestion fin exploitation
//=====================================================================================
void GestionFinExploitation(void)
{
	s32sod	loc_s32_sem;
	S_STRUCT_STATUTJDB	loc_s_statutjdb;

	
	//Cohérence date/heure du raz du JDB (entre evt et exploit)
	if(TRUE == s_cip_monitor_courant.u8_raz_jdb)
	{
		s_cip_monitor_courant.u8_raz_jdb = FALSE;	//on RAZ au cas où
		s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillStatutJdb(&loc_s_statutjdb, IDXSTATUTJDB_RAM)) 
		{
			SetDate(&loc_s_statutjdb.s_date_dernier_reset, METHODE_SETDATE_MANUEL);
			u8EditStatutJdb(&loc_s_statutjdb, IDXSTATUTJDB_BASE);
			//on copie base => backup
			u8EditStatutJdb(&loc_s_statutjdb, IDXSTATUTJDB_BACKUP);
			//Edition du fichier en ram
			u8EditStatutJdb(&loc_s_statutjdb, IDXSTATUTJDB_RAM);
		}
		s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
	}

}/*GestionFinExploitation*/

//=====================================================================================
// Fonction		: RazExploitEvents_FonctionConfig
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
//				: <loc_ps_config<: pointeur sur configuration equipement
// Sortie		: rien
// Auteur		: CM - 07/07/2010 -
// Description	: Remise à zero de l'exploitation des évènements en fonction de la config
//=====================================================================================
void RazExploitEvents_FonctionConfig(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events, S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod loc_u16_i;

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		InitStateEvt(&loc_ps_exp_events->ps_statut[loc_u16_i]); //RAZ
		if(TRUE == u8TestEvenementValide(loc_u16_i))
		{
			if(TRUE == u8TestEventDisponible(loc_u16_i))
			{
				if(TRUE == u8GetEventAction(loc_ps_config->s_tabevt.s_event[loc_u16_i].u16_action, ACTION_EVT_VALIDE))
				{
					loc_ps_exp_events->ps_statut[loc_u16_i].u8_etat_evt |= (1 << BIT7_ETAT_CFG_VALID);
				}
			}
		}
		
	}
	
}/*RazExploitEvents_FonctionConfig*/

//=====================================================================================
// Fonction		: LectureConfigurationEquipement_PourProcessus
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Lecture de la configuration pour le processus
//=====================================================================================
void LectureConfigurationEquipement_PourProcessus(void)
{
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem;
	S_STRUCT_CIP_MONITOR loc_s_cip_monitor_tempo;
	u8sod	loc_u8_new_config;

	memset(&loc_s_cip_monitor_tempo, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT
	loc_u8_new_config = FALSE;	//INIT
	
	//---------------------------------------------------------------
	//Lecture des informations CIP propres au processus monitor
	//---------------------------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
	Raz_Cip_Monitor(&s_cip_monitor_courant); //RAZ
	if(TRUE == u8FillCipMonitor(&loc_s_cip_monitor_tempo))
	{
		//Copie tempo => courant
		s_cip_monitor_courant = loc_s_cip_monitor_tempo; //MAJ

		Raz_Cip_Monitor(&loc_s_cip_monitor_tempo);
		u8EditCipMonitor(&loc_s_cip_monitor_tempo);
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		if(TRUE == s_cip_monitor_courant.pu8_flag_newcfg[loc_u8_i])
		{
			loc_u8_new_config = TRUE;	//nouvelle configuration
			if(FALSE == u8Transfert_FileToStruct(&s_config_process_mntr, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_i].u16_idx_bdd ]))
			{
				printf("LectureConfigurationEquipement_PourProcessus: Erreur lecture config idx=%d \n",loc_u8_i);
			}
			else
			{
				if(TRUE == s_cip_monitor_courant.pu8_flag_newcfg[IDXCFG_TABEVT])
				{
					MiseAJourConfigToAllStateEvt(&s_config_process_mntr);
				}

				if(TRUE == s_cip_monitor_courant.pu8_flag_newcfg[IDXCFG_SNMP])
				{
					//En cas d'activation de l'émission des traps, il faut rejouer les traps (quelque soit la version SNMP)
					if(s_config_process_mntr.s_snmp.u8_emission_trap != s_config_tempo.s_snmp.u8_emission_trap) //CONDITION: émission trap différent
					{
						if(EMISSION_TRAP_ACTIVE == s_config_process_mntr.s_snmp.u8_emission_trap) //CONDITION: émission trap activé
						{
							//On signale un ordre de raz des trap
							OrdreMntr_RAZ_Trap(); //suite à activation émission trap
						}
					}
				}
			}
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
	
	//Personalisation bdd des évènements
	if(TRUE == loc_u8_new_config) //CONDITION: nouvelle configuration
	{
		s_config_tempo = s_config_process_mntr; //MAJ
		
		CustomBddEvents_EnFonctionConfig(&s_config_process_mntr, pt_process_eventsystem);
	}

	
}/*LectureConfigurationEquipement_PourProcessus*/

//=====================================================================================
// Fonction		: u8GetAutoStatutIP_Interface
// Entrees		: <loc_u8_interface>: sur l'interface sélectionnée
// Sortie		: <loc_u8_statutIp>: statut ip
// Auteur		: CM - 15/02/2010 -
// Description	: Retourne statut de l'interface (auto)
//=====================================================================================
u8sod u8GetAutoStatutIP_Interface(u8sod loc_u8_interface)
{
	u8sod loc_u8_statutIp;
	loc_u8_statutIp = STATUT_IP__UNDEFINED; //INIT
	switch(loc_u8_interface)
	{
		case INTERFACE_BRIDGE:
			loc_u8_statutIp = s_cip_monitor_courant.u8_bridge_statut_ip;
			break;
		case INTERFACE_WLAN:
			loc_u8_statutIp = s_cip_monitor_courant.u8_wlan_statut_ip;
			break;
		default:
			break;
	}

	return loc_u8_statutIp;
}/*u8GetAutoStatutIP_Interface*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecMonitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/03/2010 -
// Description	: Initialisation du module de ExecMonitor
//=====================================================================================
void InitModule_ExecMonitor(void)
{
	FILE	*loc_p_handle;

	loc_p_handle = NULL; //INIT
	
	memset(&s_config_process_mntr,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	memset(&s_exploit_process_mntr,'\0',sizeof(S_STRUCT_EXPLOITATION)); //INIT
	memset(&s_exp_events_process_mntr,'\0',sizeof(S_STRUCT_EXPLOIT_EVENTS)); //INIT

	pt_process_eventsystem = ptGetPtrEventSystem(); //INIT

	memset(&s_cip_monitor_courant, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT

	u8_debug_madwifi_on = FALSE;	//INIT
	if(NULL != (loc_p_handle = fopen( FILE_DEBUG_MADWIFI_ON, "r" ))) //CONDITION: fichier présent
	{
//d: -------------------------------- DEBUG -------------------------------------------------------						
		printf("***********************************************************\n");
		printf("*****    DEBUG MADWIFI ACTIVE                        ******\n");
		printf("***********************************************************\n");
		u8_debug_madwifi_on = TRUE;	//debug activé
//f -------------------------------- DEBUG -------------------------------------------------------						
		//fermeture du fichier
		fclose (loc_p_handle);
	}

	//Configuration tempo
	memset(&s_config_tempo,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	
}/*InitModule_ExecMonitor*/

