/*========================================================================*/
/* NOM DU FICHIER  : cfg_ntp.c	 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/02/2010                                           */
/* Libelle         : Principal: Configuration du CLIENT NTP				  */
/* Projet          : WRM100                                               */
/* Indice          : BE050                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE009 01/02/2010 CM
// - CREATION
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_NTP


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

#define FICHIER_CONFIG_NTP PATH_DIR_ETC	 "ntp.conf"

#define DEBOUNCE_RESPONSE_NTP	10	//secondes


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u8sod u8_request_inprogress;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_ClientNtp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 01/02/2010 -
// Description	: Installe client NTP
//=====================================================================================
void Install_ClientNtp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_ClientNtp\n");

	//Création du fichier de configuration
	if(FALSE == u8CreationFichierCfgNtp(loc_ps_config))
	{
		printf("Install_ClientNtp: u8CreationFichierCfgNtp KO \n");
	}

	//On configure le Time zone
	Install_ZoneTime(loc_ps_config);

	//On force la mise à l'heure immédiate
	RequestNtp(loc_ps_config);

	//-g: force la mise à l'heure meme si ecart très important
	CmdSystem_Generique("ntpd -g -c %s",
						FICHIER_CONFIG_NTP);
	
}/*Install_ClientNtp*/

//=====================================================================================
// Fonction		: Uninstall_ClientNtp
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 01/02/2010 -
// Description	: Désinstalle  client NTP
//=====================================================================================
void Uninstall_ClientNtp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_ClientNtp\n");

	//on tue les processus
	u8CmdSystem_RemoveFile(FICHIER_STATUS_NTPDATE_ACTIA);
	CmdSystem_Generique("killall ntpd");
	CmdSystem_Generique("killall -q ntpdate");

	Uninstall_ZoneTime(loc_ps_config);
	
}/*Uninstall_ClientNtp*/

//=====================================================================================
// Fonction		: RequestNtp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Requete Ntp
//=====================================================================================
void RequestNtp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_serveur_principal[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_serveur_secours[MAX_LG_FORMAT_ADRESSE_IP+1];

	strcpy(loc_ps8_serveur_principal, ps8GetStringIp(loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])); //INIT
	strcpy(loc_ps8_serveur_secours, ""); //INIT

//	printf("RequestNtp\n");

	//Adresse du serveur NTP (de secours)
	if(ADRESSE_IP_NULLE != loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])
	{
		sprintf(loc_ps8_serveur_secours,"%s",
				ps8GetStringIp(loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS]));
	}

	//On force la mise à l'heure immédiate
	//-b: Force the time to be stepped using the settimeofday() system call, rather than slewed (default) using the adjtime() system call. This option should be used when called from a startup file at boot time.
	//-s: Divert logging output from the standard output (default) to the system syslog facility. This is designed primarily for convenience of cron scripts.
	//-u: pour ne pas bloquer la requete si socket en cours d'utilisation
	CmdSystem_Generique("killall -q ntpdate");
	CmdSystem_Generique("ntpdate -b -u -s %s %s &",
						loc_ps8_serveur_principal,
						loc_ps8_serveur_secours);

	u8_request_inprogress = TRUE;
	
}/*RequestNtp*/

//=====================================================================================
// Fonction		: GestionClientNTP
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Gestion client NTP
//=====================================================================================
void GestionClientNTP(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_donnees_inaccessible;
	s32sod	loc_s32_pid;
	u8sod	loc_u8_force_request_ntp;
	u32sod	loc_u32_nb_serveurs_dropped;
	FILE *	loc_pf_file;

	loc_pf_file = NULL;	//INIT
	loc_u8_donnees_inaccessible = FALSE; //INIT
	loc_u8_force_request_ntp = FALSE;	//INIT
	loc_u32_nb_serveurs_dropped = 0;	//INIT

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitGeneralFile(&s_exploit_process_prncpl.s_general))
	{
		loc_u8_donnees_inaccessible = TRUE; //défaut accès bdd
	}
	
	if(TRUE == u8_request_inprogress)
	{
		loc_s32_pid = s32GetPidProcessus("ntpdate", FICHIER_VAR_NTPDATE_PID);

		if(loc_s32_pid < 0) //CONDITION: Processus hostapd en cours d'execution
		{
			if(NULL != (loc_pf_file = fopen(FICHIER_STATUS_NTPDATE_ACTIA, "rt"))) //CONDITION: Fichier présent
			{
				//fermeture du fichier
				fclose(loc_pf_file);
				
				//On copie le fichier de statut de ntpdate dans sntp.info
				CmdSystem_Generique("cp %s %s",FICHIER_STATUS_NTPDATE_ACTIA, FICHIER_NTP_INFO);
				//Puis on calcul le nombre de lignes dans le fichiers de type "serveur dropped"
				loc_u32_nb_serveurs_dropped = u32GetNumberLineFile(FICHIER_NTP_INFO, FICHIER_NTP_INFO_LINE);
				if(ADRESSE_IP_NULLE != loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])
				{
					if(2 == loc_u32_nb_serveurs_dropped)//CONDITION: pas de réponse des 2 serveurs
					{
						loc_u8_force_request_ntp = TRUE;
					}
				}
				else
				{
					if(1 == loc_u32_nb_serveurs_dropped)//CONDITION: pas de réponse du serveur principal
					{
						loc_u8_force_request_ntp = TRUE;
					}
				}
				u8_request_inprogress = FALSE;	//RAZ
			}
			else //CONDITION: pas de réponse de ntpdate
			{
				loc_u8_force_request_ntp = TRUE;
			}
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	if(FALSE == loc_u8_donnees_inaccessible) //CONDITION: BDD OK
	{
		//on fait une requete à la seconde tant que serveur n'a pas répondu
		if (TRUE == loc_u8_force_request_ntp)
		{
			RequestNtp(loc_ps_config);
		}
	}


}/*GestionClientNTP*/


//=====================================================================================
// Fonction		: u8CreationFichierCfgNtp
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 01/02/2010 -
// Description	: Edition du fichier ntp.conf pour le processus ntpd
//=====================================================================================
u8sod u8CreationFichierCfgNtp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	FILE *	loc_pf_file;
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(NULL == (loc_pf_file = fopen(FICHIER_CONFIG_NTP, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgNtp: Erreur creation fichier %s\n",FICHIER_CONFIG_NTP));
		loc_u8_resultat = FALSE;
	}
	else
	{
		//Adresse du serveur NTP (principal)
		fprintf(loc_pf_file,"server %s\n",
				ps8GetStringIp(loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL]));

		//Adresse du serveur NTP (de secours)
		if(ADRESSE_IP_NULLE != loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])
		{
			fprintf(loc_pf_file,"server %s\n",
					ps8GetStringIp(loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS]));
		}
		
		fprintf(loc_pf_file,"driftfile /var/lib/ntp/drift\n");

		//fermeture du fichier
		fclose(loc_pf_file);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_NTP, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgNtp*/



/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Ntp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/02/2010 -
// Description	: Initialisation du module de cfg_ntp
//=====================================================================================
void InitModule_Cfg_Ntp(void)
{
	u8_request_inprogress = FALSE;	//INIT
	
}/*InitModule_Cfg_Ntp*/

