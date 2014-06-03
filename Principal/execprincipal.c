/*========================================================================*/
/* NOM DU FICHIER  : execprincipal.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Processus principal de l'application			      */
/* Projet          : WRM100	                                              */
/* Indice          : BE065                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Int�gration configuration par DHCP client
//BE008 28/01/2010 CM
// - Gestion fichier configuration debug.ini
// - Ajout syslog: journalisation du syst�me
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE013 26/02/2010 CM
// - Int�gration gestion des �v�nements
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calcul�e dans le processus 'monitor'.
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE023 01/04/2010 CM
// - Ajout gestion premier d�marrage du processus principal
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
// - Creation de la library static LibrarySystem
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		userhigh / usermiddle / userlow
//BE037 06/07/2010 CM
// - Ajout gestion des �v�nements sp�cifiques � l'�quipement
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE042 07/10/2010 CM
// - Ajout gestion liste des fr�quences r�glementaires
//BE047 29/11/2010 CM
// - Gestion mode d�grad� - connection � AP impossible en permanence suite � configuration wifi 
// - Optimisation configuration radio modem / amelioration ergonomie
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Ajout debug pour d�sactiver watchdog_wifi
//BE053 16/12/2010 CM
// - D�sactivation de la gestion de l'heure dans la FLASH NOR
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fr�quence aux canaux ETSI non DFS pour WRM100-ABG
//BE058 21/01/2011 CM
// - Synchronisation configuration / exploitation
//BE060 16/03/2011
// - Ajout fonction qui liste les fichiers dans r�pertoire
// - Ajout configuration date/heure au d�marrage de l'�quipement
// - Correction bug au d�marrage de l'�quipement acc�s HTTP � des donn�es pas encore initialis�es
//BE061 10/05/2011
// - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//BE065.0 14/03/2012 (CM)
// - Correction bug inactivit� Quelque soit le mode de s�curit�
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECPRINCIPAL		1

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Gestion premier d�marrage
static u8sod u8_firststart_on;

//signale reconfig radio modem
static u8sod u8_install_radiomodem_done;

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
		   "	-noradio: pas de configuration radio \n"
		   ,loc_ps8_argv0);
}/*proc_Usage*/

//=====================================================================================
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: PROCESSUS PRINCIPAL
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	s32sod	loc_s32_sem;
	s32sod	loc_s32_synchro;
	u8sod	loc_pu8_add_mac_ethernet[ETHER_ADDR_LEN]; //Adresse MAC de l'interface ethernet

	loc_s32_sem = 0;	//INIT
	memset(loc_pu8_add_mac_ethernet, 0, ETHER_ADDR_LEN); //INIT
	
	
	printf("Debut processus Principal... \n");
	InitModule_ExecPrincipal();

	//-----------------------------------------------
	//Test des arguments pass�s
	//-----------------------------------------------
	if(loc_s32_argc >= 2)//CONDITION: nombre d'argument insufisant
	{
		if (0 == strcmp(loc_pps8_argv[1],"-noradio"))
		{
			u8_mode_execPrincipal = MODE_EXECPRINCIPAL_NORADIO;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-help"))
		{
			proc_Usage((s8sod *)loc_pps8_argv[0]);
			exit(1);
		}
	}
	
	//-----------------------------------------------
	//Initialisation des s�maphores
	//-----------------------------------------------
	InitAllSemaphores();

	//-----------------------------------------------
	//Initialisation des modules associ�s � ce processus
	//-----------------------------------------------
	InitModule_GestConfig();
	InitModule_GestReboot();
	InitModule_Apply_Cfg();
	InitModule_Passwd();
	InitModule_WatchdogWifi();
	InitModule_Cfg_Monitor();
	InitModule_Cfg_Jdb();
	InitModule_Cfg_RadioModem();
	InitModule_Cfg_Snmp();
	InitModule_Cfg_Wifi();
#ifdef _WRM100_ABG_SELECT
	InitModule_Cfg_Wlan_ABG();
#endif
#ifdef _WRM100_N_SELECT
	InitModule_Cfg_Wlan_N();
#endif
	InitModule_Cfg_Network();
	InitModule_Cfg_PolicyRouting();
	InitModule_Cfg_Bird();
	InitModule_Cfg_Hostapd();
	InitModule_Cfg_Wpa_Supplicant();
	InitModule_Cfg_Dhcp();
	InitModule_Cfg_Syslog();
	InitModule_Cfg_Time();
	InitModule_Cfg_Sntp();
	InitModule_Cfg_Ntp();
	InitModule_Cfg_Nat();
	InitModule_Cfg_Http();
	InitModule_Cfg_Multicast();

	//-----------------------------------------------
	//Initialisation des modules de la librairie system
	//-----------------------------------------------
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(AddMsgDbgLog);

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
	
	//-----------------------------------------------
	//Acquittement premier d�marrage
	//-----------------------------------------------
	u8CmdSystem_RemoveFile(FILE_FIRSTSTART_ON);

	//-----------------------------------------------
	//Force MISE A L HEURE PAR DEFAUT
	//-----------------------------------------------
	CmdSysteme_MiseAHeure_Par_Defaut(); //au lieu d'etre gerer par restoretime
	
	//-----------------------------------------------
	//Initialisation du debug
	//-----------------------------------------------
	InitBDD_Debug(&s_debug_global_process_prncpl); //INIT
	
	//-----------------------------------------------
	//Initialisation de l'exploitation
	//-----------------------------------------------
	InitBDD_ExploitEquipment(&s_exploit_process_prncpl); //INIT

	//-----------------------------------------------
	//Initialisation de l'exploitation des �v�nements
	//-----------------------------------------------
	InitBDD_Exp_Event(&s_exp_events_process_prncpl); //INIT
	
	//-----------------------------------------------
	//D�termination quelle application d�marre (app1 ou app2)
	//rmq: "modeboot" est pass� dans l'argument de boot
	//-----------------------------------------------
	CmdSystem_Generique("echo $modeboot > %s",
						FILE_MODEBOOT_INIT);
	

	//-----------------------------------------------
	//Initialisation de la bdd pour HTTP
	//-----------------------------------------------
	InitBDD_Http(&s_http_process_prncpl); //INIT

	//-----------------------------------------------
	//Initialisation de la bdd pour SYSTEM EVENT
	//-----------------------------------------------
	InitBDD_Event(); //INIT

	//-----------------------------------------------
	//Initialisation de la bdd pour CIP_MONITOR
	//-----------------------------------------------
	InitBDD_Cip_Monitor(&s_cip_monitor_courant); //INIT
	
	//-----------------------------------------------
	//Initialisation de la bdd pour CIP_SNMPD
	//-----------------------------------------------
	InitBDD_Cip_Snmpd(&s_cip_snmpd_courant); //INIT
	
	//-----------------------------------------------
	//Initialisation de la bdd pour CIP_TRAP
	//-----------------------------------------------
	InitBDD_Cip_Trap(); //INIT

	//-----------------------------------------------
	//Initialisation de la bdd pour CIP_FIFOJDB
	//-----------------------------------------------
	InitBDD_Cip_FifoJdb(); //INIT

	//-----------------------------------------------
	//Initialisation de la bdd pour CIP_JDB
	//-----------------------------------------------
	InitBDD_Cip_Jdb(&s_cip_jdb_courant); //INIT

	//-----------------------------------------------
	//Extraction de l'environnement dans la FLASH
	//-----------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_ENVIRONMT, &loc_s32_sem);	//on l�ve le s�maphore
	printf("\nInitBDD_Environmt ... \n");
	memset(&s_environmt_process_prncpl,'\0',sizeof(S_STRUCT_ENVIRONNEMENT)); //INIT
	if(FALSE == u8GetMacAddress(NOM_INTERFACE_ETHERNET,loc_pu8_add_mac_ethernet))
	{
		printf("Erreur Lecture adresse MAC %s KO\n",NOM_INTERFACE_ETHERNET);
	}
	
	InitBDD_Environmt(&s_environmt_process_prncpl, loc_pu8_add_mac_ethernet);
	s32Lock_Release(SEMAPHORE_BDD_ENVIRONMT, &loc_s32_sem);	//on relache le sem
	//R�cup�re countryID debug
	u16_countryID_debug = u16GetCountryID(&s_environmt_process_prncpl);
	
	//-----------------------------------------------
	//Initialisation de la bdd pour LISTFREQ
	//-----------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
	InitBDD_ListFreq(&s_list_freq_process_prncpl);
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
		
	//-----------------------------------------------
	//Initialisation de la bdd pour STATUTJDB
	//-----------------------------------------------
	printf("\nInitBDD_StatutJdb ... \n");
	InitBDD_StatutJdb(&s_statutjdb_courant);
	
	//-----------------------------------------------
	//Extraction de la configuration dans la FLASH
	//-----------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
	printf("\nExecuteStartConfig ... \n");
	memset(&s_config_process_prncpl,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	ExecuteStartConfig(&s_config_process_prncpl);
	//on met � jour donn�es (gestion d�connexion client HTTP)
	SetConfig_ModuleClient(s_config_process_prncpl.s_admin.u8_max_client_ip, s_config_process_prncpl.s_admin.u16_duree_inactivite_http); //MAJ
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//-----------------------------------------------
	//Mise � l'heure en fonction de la configuration (au lieu d'etre gerer par restoretime)
	//-----------------------------------------------
	//il faut configurer le timezone avant de mettre � l'heure
	Uninstall_ZoneTime(&s_config_process_prncpl);	
	Install_ZoneTime(&s_config_process_prncpl);
	CmdSysteme_MiseAHeure(&s_config_process_prncpl.s_admin.s_date_demarrage);
	
	//-----------------------------------------------
	//Serveur HTTP (boa)
	//-----------------------------------------------
	Install_Http(&s_exploit_process_prncpl, &s_config_process_prncpl);

	//-----------------------------------------------
	//Install general
	//-----------------------------------------------
	Install_General(&s_config_process_prncpl); //INIT

	//-----------------------------------------------
	//Install syslog
	//-----------------------------------------------
	if(FALSE == u8_firststart_on)	//CONDITION: ce n'est pas le premier d�marrage
	{
		Uninstall_Systemlog(&s_config_process_prncpl); //INIT
	}
	Install_Systemlog(&s_config_process_prncpl); //INIT

	//-----------------------------------------------
	//Gestion Login / Password
	//-----------------------------------------------
	Install_LoginPassword(&s_config_process_prncpl);

	//-----------------------------------------------
	//Configuration du radio modem (au d�marrage)
	//-----------------------------------------------
	if(MODE_EXECPRINCIPAL_NORADIO != u8_mode_execPrincipal)
	{
		s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
		if(FALSE == u8_firststart_on)	//CONDITION: ce n'est pas le premier d�marrage
		{
			//D�sinstallation du radio modem
			Uninstall_RadioModem(&s_config_process_prncpl); //INIT
		}
		s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
		
		//Installation du radio modem
		Install_RadioModem(&s_config_process_prncpl); //INIT
	}

	//-----------------------------------------------
	//Client NTP
	//-----------------------------------------------
	if(FALSE == u8_firststart_on)	//CONDITION: ce n'est pas le premier d�marrage
	{
		Uninstall_Time(&s_config_process_prncpl);
	}
	Install_Time(&s_config_process_prncpl);
	
	//-----------------------------------------------
	//Processus Monitoring
	//-----------------------------------------------
	Install_Monitor(&s_config_process_prncpl); //INIT

	//-----------------------------------------------
	//Serveur SNMP
	//-----------------------------------------------
	Install_Snmp(&s_config_process_prncpl); //INIT

	//-----------------------------------------------
	//Processus Jdb
	//-----------------------------------------------
//d: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
	if(TRUE == u8TestNewEquipment()) //CONDITION: Nouvel equipement d�tect�
	{
		//On efface le JDB
		printf("RazJournalDeBord\n");
		RazJournalDeBord(&s_statutjdb_courant);		
	}
//f: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
	Install_Jdb(&s_config_process_prncpl); //INIT

//d: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
	//-----------------------------------------------
	//Acquittement d�tection nouvel �quipement
	//-----------------------------------------------
	if(TRUE == u8TestNewEquipment())
	{
		printf("New Equipment detected\n");
		u8CmdSystem_RemoveFile(FICHIER_NEW_EQUIPMENT);
	}
//f: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
	
	//-----------------------------------------------
	//Acquittement fin d'initialisation de la bdd
	//-----------------------------------------------
	u8CmdSystem_RemoveFile(FILE_INITBDD_ON);
	printf("Initialisation terminee\n");

//d: BE063
	//-----------------------------------------------
	//creation du fichier de configuration globale (pour recuperation exterieur par sFTP)
	//-----------------------------------------------
	CmdSystem_Generique("mkdir %s", PATH_DIR_VAR_CONF);
	//on cree le fichier config_wrm100.sta avec le contenu de la configuration
	u8Transfert_StructToFile(&s_config_process_prncpl,&PT_DEF_FILE_CONFIG_GLOBAL_STA);

	//lancement du processus de gestion de la configuration par sFTP
	CmdSystem_Generique("confsftp &");

//f: BE063
	
	
	do{
		//-----------------------------------------------
		//Pause de UNE seconde
		//-----------------------------------------------
		sleep(1);
		memset(&t_principal_newcfgini, 0, sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //RAZ
	
		//******** d: SYNCHRO CONFIG / EXPLOIT ******************************
		s32Lock_Get(SEMAPHORE_SYNCHRO_PRNCPL_MNTR, &loc_s32_synchro);	//on l�ve le s�maphore
		
		//-----------------------------------------------
		//Gestion configuration		
		//-----------------------------------------------
		s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore

			/*u8sod loc_u8_idx_cfgfile_test=3;
			printf("************VuHai %d**************************\n",loc_u8_idx_cfgfile_test);
			
			T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file;
			loc_pt_def_file=&PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile_test].u16_idx_bdd]; 
			FILE	*loc_p_handle;
			char * line = NULL;
			size_t len = 0;
			loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt");
			while ((getline(&line, &len, loc_p_handle)) != -1) {
				printf("%s", line);
			}

			printf("************VuHai %d**************************\n",loc_u8_idx_cfgfile_test);*/
		
		//On v�rifie si il y a un changement de la configuration
		//Si c'est le cas, on installe
		ExecuteGestionConfig(&s_config_process_prncpl);
		//on met � jour donn�es (gestion d�connexion client HTTP)
		SetConfig_ModuleClient(s_config_process_prncpl.s_admin.u8_max_client_ip, s_config_process_prncpl.s_admin.u16_duree_inactivite_http); //MAJ
		s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
		//Pour ne pas bloquer le s�maphore de configuration
		if(TRUE == u8_ordre_installRadioModem)
		{
			u8_ordre_installRadioModem = FALSE;	//RAZ
			printf("=========== DEBUT INSTALL RADIOMODEM ============== \n");
			Install_RadioModem(&s_config_process_prncpl); 
			printf("============ FIN INSTALL RADIOMODEM =============== \n");
			u8_install_radiomodem_done = TRUE;
		}
		
		//-----------------------------------------------
		//Gestion des installations (surveillance, ...)
		//-----------------------------------------------
		ExecuteGestionInstall(&s_config_process_prncpl);
		
		//-----------------------------------------------
		//On signale l'�volution de la configuration aux autres processus
		//-----------------------------------------------
		SignalNewConfig_AllProcess();

		//-----------------------------------------------
		//Dialogue vers le processus monitor
		//-----------------------------------------------
		Dialog_CipPrincipalToMonitor();
		
		s32Lock_Release(SEMAPHORE_SYNCHRO_PRNCPL_MNTR, &loc_s32_synchro);	//on relache le sem
		//******** f: SYNCHRO CONFIG / EXPLOIT ******************************
		

		//-----------------------------------------------
		//On v�rifie si il y a un ordre de reboot de l'�quipement
		//-----------------------------------------------
		ExecuteGestionReboot();

		//-----------------------------------------------
		//On g�re la d�connexion des clients HTTP (temps expir�)
		//-----------------------------------------------
		u8GestionDeconnexionClient();

		//-----------------------------------------------
		//Gestion configuration usine du country ID
		//-----------------------------------------------
		ControleNewCountryID();

		//-----------------------------------------------
		//Gestion configuration Time
		//-----------------------------------------------
		GestionConfigTime(&s_config_process_prncpl);
		

#ifdef _WRM100_N_SELECT
		//-----------------------------------------------
		//Gestion du Watchdog wifi (modes degrad�s)
		//-----------------------------------------------
		if(FALSE == s_debug_global_process_prncpl.u8_dbg_stop_watchdog_wifi) //CONDITION: debug d�sactiv�
		{
			Watchdog_Wifi(&s_config_process_prncpl);
		}

//d: BE065.0 27/03/2012 (CM) - Correction bug inactivit� station
		//-----------------------------------------------
		//Gestion de l'activit� du wifi
		//-----------------------------------------------
		Watchdog_ActivityWifi(&s_config_process_prncpl);
//f: BE065.0 27/03/2012 (CM) - Correction bug inactivit� station
		
#endif
		
		//On signale la fin de la configuration du systeme
		if(TRUE == u8TestConfig_InProgress()) //CONDITION: configuration en cours
		{
			ClearConfig_InProgress(); //RAZ
		}

		//-----------------------------------------------
		//Gestion des certificats (EAP-TLS) sur la STATION
		//-----------------------------------------------
		//On le fait tout le temps (car si l'utilsateur souhaite appliqu�e la config EAP-TLS il aura les certificats
		GestionCertificats_InVar(&s_config_process_prncpl);
		
		//-----------------------------------------------
		//Lecture du fichier debug.ini
		//-----------------------------------------------
		s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on l�ve le s�maphore
		if(FALSE == u8FillDebugFile(&s_debug_global_process_prncpl))//CONDITION: lecture debug.ini KO
		{
			InitDebugGlobal(&s_debug_global_process_prncpl); //RAZ
			u8EditDebugFile(&s_debug_global_process_prncpl);
		}
		s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem
		
	}while (1);
	
	return 0;
}/*main*/

//=====================================================================================
// Fonction		: SetSignalNewConfig
// Entrees		: <loc_pt_newcfg< : pointeur info nouvelle configuration
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Positionne le signal de la nouvelle configuration
//=====================================================================================
void SetSignalNewConfig(T_STRUCT_OF_FILE_NEWCFG_INI *loc_pt_info_newcfg)
{
	t_principal_newcfgini = (*loc_pt_info_newcfg); //MAJ
}/*SetSignalNewConfig*/

//=====================================================================================
// Fonction		: SignalNewConfig_AllProcess
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Signale nouvelle configuration aux autres processus
//=====================================================================================
void SignalNewConfig_AllProcess(void)
{
	s32sod	loc_s32_sem;
	u8sod loc_u8_i;
	u8sod loc_u8_signal_evolution_cfg;

	loc_u8_signal_evolution_cfg = FALSE; //INIT
	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		if(TRUE == t_principal_newcfgini.pu8_flag[loc_u8_i])
		{
			loc_u8_signal_evolution_cfg = TRUE;
		}
	}
	
	if(TRUE == loc_u8_signal_evolution_cfg)
	{
		//On signale l'�volution de la configuration au processus snmpd
		s32Lock_Get(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on l�ve le s�maphore
		if(TRUE == u8FillCipSnmpd(&s_cip_snmpd_courant))
		{
			for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
			{
				if(TRUE == t_principal_newcfgini.pu8_flag[loc_u8_i])
				{
					s_cip_snmpd_courant.pu8_flag_newcfg[loc_u8_i] = TRUE;
				}
			}
			u8EditCipSnmpd(&s_cip_snmpd_courant);
		}
		s32Lock_Release(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on relache le sem

		//On signale l'�volution de la configuration au processus monitor
		s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on l�ve le s�maphore
		if(TRUE == u8FillCipMonitor(&s_cip_monitor_courant))
		{
			for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
			{
				if(TRUE == t_principal_newcfgini.pu8_flag[loc_u8_i])
				{
					s_cip_monitor_courant.pu8_flag_newcfg[loc_u8_i] = TRUE;
				}
			}
			u8EditCipMonitor(&s_cip_monitor_courant);
		}
		s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem

		//On signale l'�volution de la configuration au processus jdb
		s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on l�ve le s�maphore
		if(TRUE == u8FillCipJdb(&s_cip_jdb_courant))
		{
			for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
			{
				if(TRUE == t_principal_newcfgini.pu8_flag[loc_u8_i])
				{
					s_cip_jdb_courant.pu8_flag_newcfg[loc_u8_i] = TRUE;
				}
			}
			u8EditCipJdb(&s_cip_jdb_courant);
		}
		s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
	}
	
}/*SignalNewConfig_AllProcess*/

//=====================================================================================
// Fonction		: Dialog_CipPrincipalToMonitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 08/03/2010 -
// Description	: Dialogue vers le processus 'monitor'
//=====================================================================================
void Dialog_CipPrincipalToMonitor(void)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_new_info;
	u8sod	loc_pu8_flag_errorconfig[NB_MAX_ERRORCONFIG];
	u8sod	loc_u8_i;

	for(loc_u8_i=0; loc_u8_i<NB_MAX_ERRORCONFIG; loc_u8_i++)
	{
		loc_pu8_flag_errorconfig[loc_u8_i] = FALSE;	//INIT
	}
	
	loc_u8_new_info = FALSE;	//INIT

	s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on l�ve le s�maphore
	if(TRUE == u8FillCipMonitor(&s_cip_monitor_courant))
	{

		for(loc_u8_i=0; loc_u8_i<NB_MAX_ERRORCONFIG; loc_u8_i++)
		{
			loc_pu8_flag_errorconfig[loc_u8_i] = s_cip_monitor_courant.pu8_flag_errorconfig[loc_u8_i];
		}
		
		if(s_cip_monitor_courant.u8_bridge_statut_ip != u8_bridge_autostatut_ip)
		{
			s_cip_monitor_courant.u8_bridge_statut_ip = u8_bridge_autostatut_ip;
			loc_u8_new_info = TRUE;
		}
		if(s_cip_monitor_courant.u8_wlan_statut_ip != u8_wlan_autostatut_ip)
		{
			s_cip_monitor_courant.u8_wlan_statut_ip = u8_wlan_autostatut_ip;
			loc_u8_new_info = TRUE;
		}
		//pour la gestion de l'alarme probleme de configuration
		s_cip_monitor_courant.pu8_flag_errorconfig[ERRORCONFIG_PASSAGE_PAR_DEFAUT] = FALSE;	//RAZ
		for(loc_u8_i=0;loc_u8_i<NB_MAX_IDXCONFIG;loc_u8_i++)
		{
			if(TRUE == pu8_signal_passage_config_par_defaut[loc_u8_i])	//CONDITION: erreur signal�e
			{
				s_cip_monitor_courant.pu8_flag_errorconfig[ERRORCONFIG_PASSAGE_PAR_DEFAUT] = TRUE;	
			}
		}

		for(loc_u8_i=0; loc_u8_i<NB_MAX_ERRORCONFIG; loc_u8_i++)
		{
			if(loc_pu8_flag_errorconfig[loc_u8_i] != s_cip_monitor_courant.pu8_flag_errorconfig[loc_u8_i])
			{
				loc_u8_new_info = TRUE;
			}
		}
		
		if(TRUE == u8_info_restart_time)
		{
			s_cip_monitor_courant.u8_info_reconfig_time = TRUE;
			u8_info_restart_time = FALSE;	//RAZ
			loc_u8_new_info = TRUE;
		}

		if(TRUE == u8_install_radiomodem_done)
		{
			s_cip_monitor_courant.u8_info_reconfig_radiomodem = TRUE;
			u8_install_radiomodem_done = FALSE; //RAZ
			loc_u8_new_info = TRUE;
		}
		
		if(TRUE == loc_u8_new_info) //CONDITION: Changement
		{
			u8EditCipMonitor(&s_cip_monitor_courant);
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem

}/*Dialog_CipPrincipalToMonitor*/

//=====================================================================================
// Fonction		: u16GetCountryID
// Entrees		: <loc_ps_environnement< : pointeur sur la base de donn�es � initialiser
// Sortie		: <loc_u16_countryID> : valeur du countryID
// Auteur		: CM - 11/10/2010 -
// Description	: R�cup�re countryID
//=====================================================================================
u16sod u16GetCountryID(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement)
{
	u16sod loc_u16_countryID;
	u8sod	loc_pu8_add_mac_ethernet[ETHER_ADDR_LEN]; //Adresse MAC de l'interface ethernet
	u16sod loc_u16_mac;

	loc_u16_countryID = S_ENVIRONMT_EQUIPEMENT_DEFAUT.u16_countryID; //INIT
	loc_u16_mac = 0;	//INIT
	memset(loc_pu8_add_mac_ethernet, 0, ETHER_ADDR_LEN); //INIT

	if(FALSE == u8GetMacAddress(NOM_INTERFACE_ETHERNET,loc_pu8_add_mac_ethernet))
	{
		printf("u16GetCountryID: Error 1\n");
	}
	else
	{
		loc_u16_mac = (u16sod)loc_pu8_add_mac_ethernet[4] | ((u16sod)loc_pu8_add_mac_ethernet[5] << 8);
		loc_u16_countryID  = (loc_u16_mac ^ loc_ps_environnement->u16_countryID);
		printf("u16GetCountryID: %d\n",loc_u16_countryID);
	}

	return loc_u16_countryID;
}/*u16GetCountryID*/

//=====================================================================================
// Fonction		: ControleNewCountryID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: controle si nouveau countryID
//=====================================================================================
void ControleNewCountryID(void)
{
	FILE	*loc_p_handle;
	s32sod	loc_s32_sem;

	loc_p_handle = NULL; //INIT
	
	if(NULL != (loc_p_handle = fopen( FICHIER_NEW_COUNTRYID_ORDER, "r" ))) //CONDITION: fichier pr�sent
	{
		//fermeture du fichier
		fclose (loc_p_handle);

		//Un nouveau countryID est configur�
		printf("ControleNewCountryID: DETECTED\n");
		s32Lock_Get(SEMAPHORE_BDD_ENVIRONMT, &loc_s32_sem);	//on l�ve le s�maphore
		if(TRUE == u8FillEnvFile(&s_environmt_process_prncpl))
		{
			u16_countryID_debug = u16GetCountryID(&s_environmt_process_prncpl);
		}
		s32Lock_Release(SEMAPHORE_BDD_ENVIRONMT, &loc_s32_sem);	//on relache le sem

		//Il faut reconfigurer le wifi pour recr�er la liste des fr�quences � g�rer
		Ordre_ReconfigurationTotale();

		//on peut supprimer ce fichier
		u8CmdSystem_RemoveFile(FICHIER_NEW_COUNTRYID_ORDER);
	}

}/*ControleNewCountryID*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecPrincipal
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de ExecPrincipal
//=====================================================================================
void InitModule_ExecPrincipal(void)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_i;

	loc_p_handle = NULL; //INIT

	memset(&s_http_process_prncpl,'\0',sizeof(S_STRUCT_HTTP_GLOBAL)); //INIT
	memset(&s_config_process_prncpl,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	memset(&s_exploit_process_prncpl,'\0',sizeof(S_STRUCT_EXPLOITATION)); //INIT
	memset(&s_debug_global_process_prncpl,'\0',sizeof(S_STRUCT_DEBUG_GLOBAL)); //INIT
	memset(&s_exp_events_process_prncpl,'\0',sizeof(S_STRUCT_EXPLOIT_EVENTS)); //INIT
	memset(&s_environmt_process_prncpl,'\0',sizeof(S_STRUCT_ENVIRONNEMENT)); //INIT
	memset(&s_list_freq_process_prncpl,0xFF,sizeof(S_STRUCT_LIST_FREQ)); //INIT

	memset(&s_cip_monitor_courant, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT
	memset(&s_cip_snmpd_courant, 0, sizeof(S_STRUCT_CIP_SNMPD)); //INIT
	memset(&t_principal_newcfgini, 0, sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //INIT
	memset(&s_cip_jdb_courant, 0, sizeof(S_STRUCT_CIP_JDB)); //INIT
	memset(&s_statutjdb_courant, 0, sizeof(S_STRUCT_STATUTJDB)); //INIT
	
	u8_mode_execPrincipal = MODE_EXECPRINCIPAL_AUCUN; //INIT

	u8_debug_madwifi_on = FALSE;	//INIT
	if(NULL != (loc_p_handle = fopen( FILE_DEBUG_MADWIFI_ON, "r" ))) //CONDITION: fichier pr�sent
	{
//d: -------------------------------- DEBUG -------------------------------------------------------						
		printf("***********************************************************\n");
		printf("*****    DEBUG MADWIFI ACTIVE                        ******\n");
		printf("***********************************************************\n");
		u8_debug_madwifi_on = TRUE;	//debug activ�
//f -------------------------------- DEBUG -------------------------------------------------------						
		//fermeture du fichier
		fclose (loc_p_handle);
	}
	
   //Fichier premier d�marrage de principal
	u8_firststart_on = FALSE; //INIT
	if(NULL != (loc_p_handle = fopen( FILE_FIRSTSTART_ON, "r" ))) //CONDITION: fichier pr�sent
	{
		printf("PREMIER DEMARRAGE\n");
		u8_firststart_on = TRUE;	//premier d�marrage du processus principal
		//fermeture du fichier
		fclose (loc_p_handle);
	}


	//pour la gestion de l'alarme probleme de configuration
	for(loc_u8_i=0;loc_u8_i<NB_MAX_IDXCONFIG;loc_u8_i++)
	{
		pu8_signal_passage_config_par_defaut[loc_u8_i] = FALSE;	//INIT
	}

	u8_ordre_installRadioModem = FALSE; //INIT

	u8_install_radiomodem_done = FALSE; //INIT
	
	
}/*InitModule_ExecPrincipal*/

