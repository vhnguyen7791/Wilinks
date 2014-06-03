/*========================================================================*/
/* NOM DU FICHIER  : cip_monitor.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 03/03/2010                                           */
/* Libelle         : Base de données: CIP pour processus monitor		  */
/* Projet          : WRM100                                               */
/* Indice	       : BE058												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 03/03/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Probleme horodatage de l'évènement JDB lors d'un RAZ général
//BE058 21/01/2011 CM
// - Synchronisation configuration / exploitation
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//Base de données CIP (Comminication Inter Processus) pour partager des données
//avec le processus monitor


/*_____II - DEFINE SBIT __________________________________________________*/

#define _CIP_MONITOR

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM CIP_MONITOR.INI
//***************************************************************************

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CIP_MONITOR_INI[] = {
 	{	"flag_newcfg",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_TABU8,	(u16sod)sizeof(u8sod),	NB_MAX_IDXCONFIG,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, pu8_flag_newcfg[0]) },
	{	"bridge_statut_ip",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_bridge_statut_ip) },
	{	"wlan_statut_ip",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_wlan_statut_ip) },
	{	"raz_jdb",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_raz_jdb) },
	{	"raz_alarm_memo",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_raz_alarmes_memorisees) },
	{	"raz_general",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_raz_general) },
	{	"restart_equipment",FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_restart_equipment) },
	{	"flag_errorcfg",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_TABU8,	(u16sod)sizeof(u8sod),	NB_MAX_ERRORCONFIG,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, pu8_flag_errorconfig[0]) },
	{	"info_restart_ntp",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_info_reconfig_time) },
	{	"info_reconfig_radio",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_MONITOR, u8_info_reconfig_radiomodem) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER CIP_MONITOR.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_MONITOR_INI =
{
	PATH_DIR__BDD_MISC "cip_monitor.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CIP_MONITOR_INI ,//pt_contenu
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillCipMonitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 03/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillCipMonitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_cip_monitor, &T_DEF_FILE_CIP_MONITOR_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillCipMonitor KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillCipMonitor*/

//=====================================================================================
// Fonction		: u8EditCipMonitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 03/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditCipMonitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_cip_monitor, &T_DEF_FILE_CIP_MONITOR_INI);

	return loc_u8_resultat;
}/*u8EditCipMonitor*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: Raz_Cip_Monitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: RAZ des ordres de la base de données de cip_monitor
//=====================================================================================
void Raz_Cip_Monitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor)
{
	u8sod	loc_u8_i;

	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		loc_ps_cip_monitor->pu8_flag_newcfg[loc_u8_i] = FALSE;	//RAZ
	}
	loc_ps_cip_monitor->u8_raz_jdb = FALSE;	//RAZ
	loc_ps_cip_monitor->u8_raz_alarmes_memorisees = FALSE;	//RAZ
	loc_ps_cip_monitor->u8_restart_equipment = FALSE;	//RAZ
	loc_ps_cip_monitor->u8_info_reconfig_time = FALSE; //RAZ
	loc_ps_cip_monitor->u8_info_reconfig_radiomodem = FALSE; //RAZ
	
}/*Raz_Cip_Monitor*/

//=====================================================================================
// Fonction		: InitBDD_Cip_Monitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Initialisation de la base de données de cip_monitor
//=====================================================================================
void InitBDD_Cip_Monitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor)
{
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem; 	

	s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
	
	memset(loc_ps_cip_monitor, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT

	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		loc_ps_cip_monitor->pu8_flag_newcfg[loc_u8_i] = FALSE;	//INIT
	}
	loc_ps_cip_monitor->u8_bridge_statut_ip = STATUT_IP__UNDEFINED; //INIT
	loc_ps_cip_monitor->u8_bridge_statut_ip = STATUT_IP__UNDEFINED; //INIT

	loc_ps_cip_monitor->u8_raz_jdb = FALSE;	//INIT

	loc_ps_cip_monitor->u8_raz_alarmes_memorisees = FALSE;	//INIT

	loc_ps_cip_monitor->u8_raz_general = FALSE;	//INIT
	
	loc_ps_cip_monitor->u8_restart_equipment  = FALSE;	//INIT
	
	for(loc_u8_i=0; loc_u8_i<NB_MAX_ERRORCONFIG; loc_u8_i++)
	{
		loc_ps_cip_monitor->pu8_flag_errorconfig[loc_u8_i] = FALSE;	//INIT
	}
	loc_ps_cip_monitor->u8_info_reconfig_time = FALSE; //INIT
	loc_ps_cip_monitor->u8_info_reconfig_radiomodem = FALSE; //INIT
	
	u8EditCipMonitor(loc_ps_cip_monitor); //INIT
	s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_Cip_Monitor*/

//=====================================================================================
// Fonction		: InitModule_Cip_Monitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Initialisation du module de cip_monitor
//=====================================================================================
void InitModule_Cip_Monitor(void)
{
	
}/*InitModule_Cip_Monitor*/

