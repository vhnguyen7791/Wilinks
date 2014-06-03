/*========================================================================*/
/* NOM DU FICHIER  : cfg_sntp.c	 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/12/2010                                           */
/* Libelle         : Principal: Configuration du CLIENT SNTP			  */
/* Projet          : WRM100                                               */
/* Indice          : BE050                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE050 09/12/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_SNTP


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

#define DEBOUNCE_RESPONSE_SNTP	30	//secondes	
#define STARTING_REQUESTE_SNTP	20	//secondes

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u8sod u8_request_inprogress;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_ClientSntp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Installe client SNTP
//=====================================================================================
void Install_ClientSntp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_ClientSntp\n");

	//On configure le Time zone
	Install_ZoneTime(loc_ps_config);

	//On force la mise à l'heure immédiate
	RequestSntp(loc_ps_config);

}/*Install_ClientSntp*/

//=====================================================================================
// Fonction		: Uninstall_ClientSntp
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Désinstalle  client SNTP
//=====================================================================================
void Uninstall_ClientSntp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_ClientSntp\n");

	u8CmdSystem_RemoveFile(FICHIER_STATUS_NTPDATE_ACTIA);
	CmdSystem_Generique("killall -q ntpdate");
	Uninstall_ZoneTime(loc_ps_config);
	u8_request_inprogress = FALSE;	//RAZ
	
}/*Uninstall_ClientSntp*/

//=====================================================================================
// Fonction		: RequestSntp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Requete Sntp
//=====================================================================================
void RequestSntp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_serveur_principal[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_serveur_secours[MAX_LG_FORMAT_ADRESSE_IP+1];

	strcpy(loc_ps8_serveur_principal, ps8GetStringIp(loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])); //INIT
	strcpy(loc_ps8_serveur_secours, ""); //INIT

//	printf("RequestSntp\n");

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
}/*RequestSntp*/

//=====================================================================================
// Fonction		: GestionClientSntp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Gestion client SNTP
//=====================================================================================
void GestionClientSntp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_donnees_inaccessible;
	s32sod loc_s32_pid;
	u8sod	loc_u8_force_request_sntp;
	struct tm *loc_ps_tm;
	time_t	loc_s_time_t;
	FILE *	loc_pf_file;
	u32sod	loc_u32_nb_serveurs_dropped;

	loc_pf_file = NULL;	//INIT
	loc_u8_donnees_inaccessible = FALSE; //INIT
	loc_u8_force_request_sntp = FALSE;	//INIT
	loc_ps_tm = NULL;	//INIT
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
				CmdSystem_Generique("cp %s %s",FICHIER_STATUS_NTPDATE_ACTIA, FICHIER_SNTP_INFO);

				//Puis on calcul le nombre de lignes dans le fichiers de type "serveur dropped"
				loc_u32_nb_serveurs_dropped = u32GetNumberLineFile(FICHIER_SNTP_INFO, FICHIER_SNTP_INFO_LINE);
				if(ADRESSE_IP_NULLE != loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])
				{
					if(2 == loc_u32_nb_serveurs_dropped)//CONDITION: pas de réponse des 2 serveurs
					{
						loc_u8_force_request_sntp = TRUE;
					}
				}
				else
				{
					if(1 == loc_u32_nb_serveurs_dropped)//CONDITION: pas de réponse du serveur principal
					{
						loc_u8_force_request_sntp = TRUE;
					}
				}
				
				u8_request_inprogress = FALSE;	//RAZ
			}
			else //CONDITION: pas de réponse de ntpdate
			{
				loc_u8_force_request_sntp = TRUE;
			}
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	if(FALSE == loc_u8_donnees_inaccessible) //CONDITION: BDD OK
	{
		if (TRUE == loc_u8_force_request_sntp)
		{
			RequestSntp(loc_ps_config);
		}
		else
		{
			//on demande l'heure toujours a 00h10 puis a 00h10+u16_freq_maj_sntp
			//Recupère l'heure
			time(&loc_s_time_t);
			loc_ps_tm = localtime(&loc_s_time_t);

			if ( ((0 == loc_ps_tm->tm_hour)||
				  (0 == (loc_ps_tm->tm_hour % loc_ps_config->s_admin.s_client_ntp.u16_freq_maj_sntp))
				 )&&
				 (10 == loc_ps_tm->tm_min)&& 
				 ((loc_ps_tm->tm_sec > 0) && (loc_ps_tm->tm_sec < 10))//pour etre sur de ne pas le louper
			   ) //CONDITION: il faut faire une requete
			{
				RequestSntp(loc_ps_config);
			}
		}
	}
	
	
}/*GestionClientSntp*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Sntp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Initialisation du module de cfg_sntp
//=====================================================================================
void InitModule_Cfg_Sntp(void)
{
	u8_request_inprogress = FALSE;	//INIT
}/*InitModule_Cfg_Sntp*/

