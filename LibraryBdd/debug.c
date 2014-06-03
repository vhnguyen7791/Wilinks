/*========================================================================*/
/* NOM DU FICHIER  : debug.c			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 16/10/2009                                           */
/* Libelle         : Base de données: debug								  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 25/09/09 CM
// - CREATION
//BE008 28/01/2010 CM
// - Gestion fichier configuration debug.ini
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE051 13/12/2010 CM
// - Ajout debug pour désactiver watchdog_wifi
//BE055 17/01/2011 CM
// - Ajout information "Debug Activé" sur frame A
// - Ajout configuration Country ID pour le client
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _DEBUG


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Gestion debug log
s8sod	ps8_debug_vsprintbuffer[TAILLE_MAX_MESSAGE_DEBUG];

//Gestion debug ini
//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM DEBUG.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_DEBUG_INI[] = {
	{	"syslogd_level",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_syslogd_level)	},
	{	"klogd_level",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_klogd_level)	},
	{	"dbg_hostapd",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_dbg_hostapd)	},
	{	"dbg_wpa_supplicant",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_dbg_wpa_supplicant)	},
	{	"dbg_iptables",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_dbg_iptables)	},
	{	"dbg_stop_watchdog_wifi",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_dbg_stop_watchdog_wifi)	},
	{	"dbg_countryID",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_dbg_countryID)	},
	{	"mode_test_final",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_mode_test_final)	},
	{	"cfg_test_final",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_DEBUG_GLOBAL, u8_cfg_test_final)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER DEBUG.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_DEBUG_INI =
{
	FICHIER_BDD__DEBUG_INI, //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_DEBUG_INI ,//pt_contenu
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillDebugFile
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/01/2010 -
// Description	: Lecture du fichier
//=====================================================================================
u8sod u8FillDebugFile(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_debug_global, &T_DEF_FILE_DEBUG_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillDebugFile KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillDebugFile*/

//=====================================================================================
// Fonction		: u8EditDebugFile
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/01/2010 -
// Description	: Ecriture  du fichier
//=====================================================================================
u8sod u8EditDebugFile(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_debug_global, &T_DEF_FILE_DEBUG_INI);

	return loc_u8_resultat;
}/*u8EditDebugFile*/


//=========================================================================
//Procedure	 : AddMsgDbgLog
//Entrée	 : <loc_ps8_fmtp< : message du texte dans debug
//Sortie	 : Rien
//Auteur	 : CM - 16/10/2009 -
//Description: Ajoute message debug
//=========================================================================
void AddMsgDbgLog(s8sod *loc_ps8_fmtp, ...)
{
	va_list loc_t_argp;
	u16sod	loc_u16_n;
	s32sod	loc_s32_sem;

	va_start(loc_t_argp, loc_ps8_fmtp);
	loc_u16_n = vsnprintf(ps8_debug_vsprintbuffer, TAILLE_MAX_MESSAGE_DEBUG, loc_ps8_fmtp, loc_t_argp);

	if((0<loc_u16_n) && (loc_u16_n < TAILLE_MAX_MESSAGE_DEBUG))	//CONDITION: nb caractères OK
	{
		if(strlen(ps8_debug_vsprintbuffer) < TAILLE_MAX_MESSAGE_DEBUG)
		{
			s32Lock_Get(SEMAPHORE_BDD_DEBUGLOG, &loc_s32_sem);	//on lève le sem
			u8AddInFileDebugLog(ps8_debug_vsprintbuffer);
			s32Lock_Release(SEMAPHORE_BDD_DEBUGLOG, &loc_s32_sem);	//on relache le sem
		}
	}
}/*AddMsgDbgLog*/

//=====================================================================================
// Fonction		: u8AddInFileDebugLog
// Entrees		: loc_ps8_message
// Sortie		: <loc_u8_resultat> : TRUE (si OK),sinon FALSE
// Auteur		: CM - 16/10/2009 -
// Description	: Ajoute un message dans le fichier actia.log
//=====================================================================================
u8sod u8AddInFileDebugLog(s8sod *loc_ps8_message)
{
	FILE		*loc_p_handle;
	s32sod		loc_s32_numwritten;
	u8sod		loc_u8_resultat;
	u32sod		loc_u32_size_file;

	loc_u8_resultat = TRUE;	//INIT
	loc_u32_size_file = u32GetSizeOfFile(FILE_ACTIA_DEBUG); //INIT

	if(loc_u32_size_file < MAX_SIZE_F_ACTIA_DEBUG)
	{
		// Ouverture du fichier de actia.dbg
		if(NULL == (loc_p_handle = fopen( FILE_ACTIA_DEBUG, "a" )))
		{
	//		printf("AddInFileDebug : Impossible d'ouvrir le fichier %s\n", FILE_ACTIA_DEBUG);
			loc_u8_resultat = FALSE;
		}
		else
		{
			loc_s32_numwritten = fprintf(loc_p_handle,	"%s",
										 loc_ps8_message);
			if(loc_s32_numwritten < 0)	//CONDITION: ecriture KO
			{
				loc_u8_resultat = FALSE;
			}

			//fermeture du fichier
			fclose (loc_p_handle);
		}
	}
	return loc_u8_resultat;
}/*u8AddInFileDebugLog*/

//=====================================================================================
// Fonction		: u8TestDebugActive
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: <loc_u8_resultat> : TRUE (si OK),sinon FALSE
// Auteur		: CM - 17/01/2011 -
// Description	: Test si debug activé
//=====================================================================================
u8sod u8TestDebugActive(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global)
{
	u8sod		loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if((TRUE == loc_ps_debug_global->u8_dbg_hostapd)||
	   (TRUE == loc_ps_debug_global->u8_dbg_wpa_supplicant)||
	   (TRUE == loc_ps_debug_global->u8_dbg_iptables)||
	   (TRUE == loc_ps_debug_global->u8_dbg_stop_watchdog_wifi)||
	   (TRUE == loc_ps_debug_global->u8_dbg_countryID)
	  )
	{
		loc_u8_resultat = TRUE;
	}
	
	return loc_u8_resultat;
}/*u8TestDebugActive*/

//=====================================================================================
// Fonction		: FunctionMacroPrintf
// Entrees		: <loc_ps8_message<: message à afficher
// Sortie		: void
// Auteur		: CM - 07/07/2010 -
// Description	: Fonction de la macro printf
//=====================================================================================
void FunctionMacroPrintf(s8sod *loc_ps8_message)
{
	MACRO_PRINTF((loc_ps8_message));
}/*FunctionMacroPrintf*/

//=====================================================================================
// Fonction		: InitDebugGlobal
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: rien
// Auteur		: CM - 29/01/2010 -
// Description	: Initialisation de la structure de debug globale
//=====================================================================================
void InitDebugGlobal(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global)
{
	memset(loc_ps_debug_global,'\0',sizeof(S_STRUCT_DEBUG_GLOBAL)); //RAZ
	
	//Debug concernant le system log
	loc_ps_debug_global->u8_syslogd_level = LOGLEVEL_DBG_DISABLED; //INIT
	loc_ps_debug_global->u8_klogd_level = LOGLEVEL_DBG_DISABLED; //INIT
	//Debug concernant hostapd
	loc_ps_debug_global->u8_dbg_hostapd = FALSE; //INIT
	//Debug concernant wpa_supplicant
	loc_ps_debug_global->u8_dbg_wpa_supplicant = FALSE; //INIT
	//Debug concernant iptables
	loc_ps_debug_global->u8_dbg_iptables = FALSE;	//INIT
	//Debug concernant watchdog_wifi
	loc_ps_debug_global->u8_dbg_stop_watchdog_wifi = FALSE;	//INIT
	loc_ps_debug_global->u8_dbg_countryID = FALSE;	//INIT

	//Test final
	loc_ps_debug_global->u8_mode_test_final= MODE_AP_TF;	//INIT
	loc_ps_debug_global->u8_cfg_test_final= ANT1_2_4G;	//INIT
	loc_ps_debug_global->u8_etat_cnx_test_final=0;
	
}/*InitDebugGlobal*/

//=====================================================================================
// Fonction		: InitBDD_Debug
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: rien
// Auteur		: CM - 16/10/2009 -
// Description	: Initialisation de la base de données de debug
//=====================================================================================
void InitBDD_Debug(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global)
{
	s32sod	loc_s32_sem; 	
	FILE *loc_p_handle;
	
	//On supprime le fichier de debug
	if(NULL != (loc_p_handle = fopen( FILE_ACTIA_DEBUG, "r" )))//CONDITION: fichier présent
	{
		//fichier bien présent
		fclose (loc_p_handle);

		//on supprime le fichier de debug
		CmdSystem_Generique("rm %s", FILE_ACTIA_DEBUG);
	}

	//On vient récupérer le fichier sauvé dans la FLASH (si il existe!)
	if(NULL != (loc_p_handle = fopen( FICHIER_MNT_FLASH_CONFIG__DEBUG_SAV, "r" )))//CONDITION: fichier présent
	{
		//fichier bien présent
		fclose (loc_p_handle);
		
		CmdSystem_Generique("cp %s %s",	FICHIER_MNT_FLASH_CONFIG__DEBUG_SAV, FICHIER_BDD__DEBUG_INI);
	}
	
	//Initialisation du fichier de debug.ini
	s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore

	InitDebugGlobal(loc_ps_debug_global); //INIT

	//On teste si le fichier est présent
	if(NULL != (loc_p_handle = fopen( FICHIER_BDD__DEBUG_INI, "r" )))//CONDITION: fichier présent
	{
		//fichier bien présent
		fclose (loc_p_handle);

		//On vient lire le contenu (si possible)
		if(FALSE == u8FillDebugFile(loc_ps_debug_global)) //CONDITION: Lecture KO
		{
			//On réedite le fichier
			InitDebugGlobal(loc_ps_debug_global); //RAZ

			u8EditDebugFile(loc_ps_debug_global); //INIT
		}
	}
	else //CONDITION: Fichier absent
	{
		//On réedite le fichier
		InitDebugGlobal(loc_ps_debug_global); //RAZ

		u8EditDebugFile(loc_ps_debug_global); //INIT
	}
	
	s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem

}/*InitBDD_Debug*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Debug
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009 -
// Description	: Initialisation du module de Debug de l'équipement
//=====================================================================================
void InitModule_Debug(void)
{
	strcpy(ps8_debug_vsprintbuffer, "");	//INIT
	
}/*InitModule_Debug*/

