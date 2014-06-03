/*========================================================================*/
/* NOM DU FICHIER  : cfg_time.c	 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/12/2010                                           */
/* Libelle         : Principal: Configuration du date/heure via network	  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE050 09/12/2010 CM
// - CREATION
//BE060 16/03/2011
// - Ajout configuration date/heure au démarrage de l'équipement
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_TIME


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

#define FICHIER_ETC_LOCALTIME PATH_DIR_ETC	 "localtime"
#define PATH_DIR_ZONEINFOP PATH_DIR_USR	 "share/zoneinfo/"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Time
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Installe time
//=====================================================================================
void Install_Time(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Time\n");

	switch(loc_ps_config->s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
			Install_ClientNtp(loc_ps_config);
			break;
		case MODE_MAH_SNTP:
			Install_ClientSntp(loc_ps_config);
			break;
		case MODE_MAH_MANUELLE:
		default:
			break;
	}
	//On signale la reconfiguration du temps
	u8_info_restart_time = TRUE;
	
}/*Install_Time*/

//=====================================================================================
// Fonction		: Uninstall_Time
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Désinstalle time
//=====================================================================================
void Uninstall_Time(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_Time\n");
	
	switch(loc_ps_config->s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
			Uninstall_ClientNtp(loc_ps_config);
			break;
		case MODE_MAH_SNTP:
			Uninstall_ClientSntp(loc_ps_config);
			break;
		case MODE_MAH_MANUELLE:
		default:
			break;
	}
	
}/*Uninstall_Time*/

//=====================================================================================
// Fonction		: Install_ZoneTime
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Installe time zone (fuseau horaire)
//=====================================================================================
void Install_ZoneTime(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_timezone[20+1];
	
	printf("Install_ZoneTime\n");
	strcpy(loc_ps8_timezone, ""); //INIT

	//On configure le Time zone

	switch(loc_ps_config->s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
		case MODE_MAH_SNTP:
			if(0 == loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire)
			{
//				CmdSystem_Generique("export TZ=\"GMT\" ");
				strcpy(loc_ps8_timezone, "Etc/GMT");
			}
			else
			{
				if(0 < loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire) //CONDITION: positif
				{
					//pour un fuseau horaire positif, timezone est de type: "Etc/GMT-xx"
					sprintf(loc_ps8_timezone, "Etc/GMT-%d",
							loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire);
//					CmdSystem_Generique("export TZ=\"GMT-%d\" ",
//										loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire);


				}
				else //CONDITION: négatif
				{
					//pour un fuseau horaire négatif, timezone est de type: "Etc/GMT+xx"
					sprintf(loc_ps8_timezone, "Etc/GMT+%d",
							(u8sod)abs(loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire));
//					CmdSystem_Generique("export TZ=\"GMT+%d\" ",
//										(u8sod)abs(loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire));
				}
			}
			break;
		case MODE_MAH_MANUELLE:
		default:
			//on force Time Zone à UTC
			strcpy(loc_ps8_timezone, "UTC");
			break;
	}
	printf("TIME ZONE = %s \n",loc_ps8_timezone);
	CmdSystem_Generique("ln -sf %s%s %s",
						PATH_DIR_ZONEINFOP,loc_ps8_timezone,
						FICHIER_ETC_LOCALTIME);
	
}/*Install_ZoneTime*/

//=====================================================================================
// Fonction		: Uninstall_ZoneTime
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Désinstalle time zone (fuseau horaire)
//=====================================================================================
void Uninstall_ZoneTime(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_timezone[20+1];
	
	printf("Uninstall_ZoneTime\n");

	strcpy(loc_ps8_timezone, ""); //INIT

	//on force Time Zone à UTC
	strcpy(loc_ps8_timezone, "UTC");
	CmdSystem_Generique("ln -sf %s%s %s",
						PATH_DIR_ZONEINFOP,loc_ps8_timezone,
						FICHIER_ETC_LOCALTIME);
}/*Uninstall_ZoneTime*/

//=====================================================================================
// Fonction		: GestionConfigTime
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Gestion config time
//=====================================================================================
void GestionConfigTime(S_STRUCT_CONFIGURATION *loc_ps_config)
{

	switch(loc_ps_config->s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
			GestionClientNTP(loc_ps_config);
			break;
		case MODE_MAH_SNTP:
			GestionClientSntp(loc_ps_config);
			break;
		case MODE_MAH_MANUELLE:
		default:
			break;
	}

}/*GestionConfigTime*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Time
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/12/2010 -
// Description	: Initialisation du module de cfg_time
//=====================================================================================
void InitModule_Cfg_Time(void)
{
	u8_info_restart_time = FALSE; //INIT
	
}/*InitModule_Cfg_Time*/

