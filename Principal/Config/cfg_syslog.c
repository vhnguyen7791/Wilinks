/*========================================================================*/
/* NOM DU FICHIER  : cfg_syslog.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 28/01/2010                                           */
/* Libelle         : Principal: Configuration du SYSTEM LOG				  */
/* Projet          : WRM100                                               */
/* Indice          : BE008                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_SYSLOG

//Pour information:
//#define	LOG_EMERG	0	/* system is unusable */
//#define	LOG_ALERT	1	/* action must be taken immediately */
//#define	LOG_CRIT	2	/* critical conditions */
//#define	LOG_ERR		3	/* error conditions */
//#define	LOG_WARNING	4	/* warning conditions */
//#define	LOG_NOTICE	5	/* normal but significant condition */
//#define	LOG_INFO	6	/* informational */
//#define	LOG_DEBUG	7	/* debug-level messages */


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

//Niveau par défaut de syslogd
#define SYSLOGD_LEVEL_PAR_DEFAUT	LOG_DEBUG

//Niveau par défaut de klogd
#define KLOGD_LEVEL_PAR_DEFAUT		LOG_DEBUG

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Systemlog
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Installe systemlog
//=====================================================================================
void Install_Systemlog(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_klogdlevel;
	u8sod loc_u8_syslogdlevel;

	loc_u8_klogdlevel = KLOGD_LEVEL_PAR_DEFAUT; //INIT
	loc_u8_syslogdlevel = SYSLOGD_LEVEL_PAR_DEFAUT; //INIT
	printf("Install_Systemlog\n");

	if(TRUE == loc_ps_config->s_admin.u8_syslog_activation) //CONDITION: log activé
	{
		//d: ---------- debug ------------------
		if(s_debug_global_process_prncpl.u8_syslogd_level < NB_MAX_LOGLEVEL) //CONDITION: debug activé
		{
			loc_u8_syslogdlevel = s_debug_global_process_prncpl.u8_syslogd_level;
		}
		if(s_debug_global_process_prncpl.u8_klogd_level < NB_MAX_LOGLEVEL) //CONDITION: debug activé
		{
			loc_u8_klogdlevel = s_debug_global_process_prncpl.u8_syslogd_level;
		}
		//f: ---------- debug ------------------
		
		CmdSystem_Generique("klogd -c %d",
							(loc_u8_klogdlevel+1));

		if(0 == loc_ps_config->s_admin.u32_syslog_adresse_IP) //CONDITION: log distant désactivé
		{
			CmdSystem_Generique("syslogd -l %d",
								(loc_u8_syslogdlevel+1) );
		}
		else //CONDITION: log distant activé
		{
			CmdSystem_Generique("syslogd -L -l %d -R %s:%d",
								(loc_u8_syslogdlevel+1),
								ps8GetStringIp(loc_ps_config->s_admin.u32_syslog_adresse_IP),
								loc_ps_config->s_admin.u16_syslog_port);
		}
	}
	
}/*Install_Systemlog*/

//=====================================================================================
// Fonction		: Uninstall_Systemlog
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Désinstalle  systemlog
//=====================================================================================
void Uninstall_Systemlog(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_Systemlog\n");

	//on tue les processus
	CmdSystem_Generique("killall klogd");
	CmdSystem_Generique("killall syslogd");
	
}/*Uninstall_Systemlog*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Syslog
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Initialisation du module de cfg_syslog
//=====================================================================================
void InitModule_Cfg_Syslog(void)
{
	
}/*InitModule_Cfg_Syslog*/

