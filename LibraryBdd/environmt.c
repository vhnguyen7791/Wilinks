/*========================================================================*/
/* NOM DU FICHIER  : environmt.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010                                           */
/* Libelle         : Base de données: environnement						  */
/* Projet          : WRM100                                               */
/* Indice	       : BE056												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 11/10/2010 CM
// - CREATION
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//Base de données de gestion de l'environnement de l'équipement
//sauvé dans la partition de flash-config


/*_____II - DEFINE SBIT __________________________________________________*/

#define _ENVIRONMT

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM ENV.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_ENV_INI[] = {
	{	"wiid",		FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ENVIRONNEMENT, u16_countryID)	},
	{	CH_BDDFILECHECKSUM,		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ENVIRONNEMENT, u16_checksum_file)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER ENV.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_ENV_INI =
{
#ifdef _WRM100_ABG_SELECT
	PATH_DIR__FLASH_CONFIG_ENV "env-ABG.ini", //ps8_path_file
#endif
#ifdef _WRM100_N_SELECT
	PATH_DIR__FLASH_CONFIG_ENV "env.ini", //ps8_path_file
#endif
	DEFFILE_TYPE_SYSTEM, //u8_type
	TRUE,	//u8_avec_checksum
	PT_CONTENU_FILE_ENV_INI ,//pt_contenu
};

//****************************************
//DEFINITION DU FICHIER ENV.SAV
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_ENV_SAV =
{
#ifdef _WRM100_ABG_SELECT
	PATH_DIR__FLASH_CONFIG_ENV "env-ABG.sav", //ps8_path_file
#endif
#ifdef _WRM100_N_SELECT
	PATH_DIR__FLASH_CONFIG_ENV "env.sav", //ps8_path_file
#endif
	DEFFILE_TYPE_SYSTEM, //u8_type
	TRUE,	//u8_avec_checksum
	PT_CONTENU_FILE_ENV_INI ,//pt_contenu
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillEnvFile
// Entrees		: <loc_ps_environnement< : pointeur sur la base de données environnement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillEnvFile(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_environnement, &T_DEF_FILE_ENV_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillEnvFile KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillEnvFile*/

//=====================================================================================
// Fonction		: u8EditEnvFile
// Entrees		: <loc_ps_environnement< : pointeur sur la base de données environnement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditEnvFile(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_environnement, &T_DEF_FILE_ENV_INI);

	return loc_u8_resultat;
}/*u8EditEnvFile*/

//=====================================================================================
// Fonction		: u8TestEnvFile
// Entrees		: <loc_ps_environnement< : pointeur sur la base de données environnement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Test des données de la structure S_STRUCT_ENVIRONNEMENT
//=====================================================================================
u8sod u8TestEnvFile(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;

	return loc_u8_resultat;
}/*u8TestEnvFile*/

//=====================================================================================
// Fonction		: PassageParDefautEnvironnement
// Entrees		: <loc_ps_environnement< : pointeur sur la base de données environnement
//				: <loc_pu8_add_mac_ethernet< : pointeur sur adresse mac ethernet 
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Passage par défaut de l'environnement
//=====================================================================================
void PassageParDefautEnvironnement(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement, u8sod *loc_pu8_add_mac_ethernet)
{
	u16sod loc_u16_mac;

	loc_u16_mac = (u16sod)loc_pu8_add_mac_ethernet[4] | ((u16sod)loc_pu8_add_mac_ethernet[5] << 8);
	
	*loc_ps_environnement = S_ENVIRONMT_EQUIPEMENT_DEFAUT;

	//On transcode le countryID en fonction de l'adresse MAC
	loc_ps_environnement->u16_countryID ^= loc_u16_mac;

}/*PassageParDefautEnvironnement*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitBDD_Environmt
// Entrees		: <loc_ps_environnement< : pointeur sur la base de données à initialiser
//				: <loc_pu8_add_mac_ethernet< : pointeur sur adresse mac ethernet 
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation de la base de données de environnement
//=====================================================================================
void InitBDD_Environmt(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement, u8sod *loc_pu8_add_mac_ethernet)
{
	u8sod loc_u8_etat_base; //etat du fichier de base
	u16sod loc_u16_chk_base; //checksum du fichier de base
	u8sod loc_u8_etat_backup; //etat du fichier de backup
	u16sod loc_u16_chk_backup;//checksum du fichier de backup

	memset(loc_ps_environnement,'\0',sizeof(S_STRUCT_ENVIRONNEMENT));

	//**Etape n°2**: Vérification présence / validité des fichiers de configuration dans la mémoire non volatile
	//on parcourt les fichiers de configuration (dans mémoire non volatile)
	loc_u8_etat_base = u8Transfert_FileToStruct(loc_ps_environnement, &T_DEF_FILE_ENV_INI);
	loc_u16_chk_base = loc_ps_environnement->u16_checksum_file;
	loc_u8_etat_backup = u8Transfert_FileToStruct(loc_ps_environnement, &T_DEF_FILE_ENV_SAV);
	loc_u16_chk_backup = loc_ps_environnement->u16_checksum_file;

	printf("************************************************ \n");
	printf("* InitBDD_Environmt: \n");
	printf("*                  	env.ini (STATUT=%d CHK=%d) \n",
		   loc_u8_etat_base,loc_u16_chk_base);
	printf("*                  	env.sav (STATUT=%d CHK=%d) \n",
		   loc_u8_etat_backup,loc_u16_chk_backup);
	printf("************************************************ \n");

	if(TRUE == loc_u8_etat_base) //CONDITION: fichier de base OK
	{
		if(TRUE == loc_u8_etat_backup) //CONDITION: fichier de backup OK
		{
			//On vérifie qu'il y a le meme checksum
			//si différent, il faut copier le fichier env.ini dans env.sav
			if(loc_u16_chk_base != loc_u16_chk_backup)
			{
				//on copie ini => sav
				u8CmdSystem_CopyFile(T_DEF_FILE_ENV_INI.ps8_path_file,
									 T_DEF_FILE_ENV_SAV.ps8_path_file);
			}
		}
		else //CONDITION: fichier de backup KO
		{
			//on copie ini => sav
			u8CmdSystem_CopyFile(T_DEF_FILE_ENV_INI.ps8_path_file,
								 T_DEF_FILE_ENV_SAV.ps8_path_file);
		}
	}
	else  //CONDITION: fichier de base KO
	{
		if(TRUE == loc_u8_etat_backup) //CONDITION: fichier de backup OK
		{
			//on copie sav => ini
			u8CmdSystem_CopyFile(T_DEF_FILE_ENV_SAV.ps8_path_file,
								 T_DEF_FILE_ENV_INI.ps8_path_file);
		}
		else //CONDITION: fichier de backup KO
		{
			printf("InitBDD_Environmt: PASSAGE CONFIGURATION PAR DEFAUT\n");
			PassageParDefautEnvironnement(loc_ps_environnement, loc_pu8_add_mac_ethernet);
			//Les 2 fichiers sont KO
			u8Transfert_StructToFile(loc_ps_environnement, &T_DEF_FILE_ENV_INI);
			//on copie ini => save
			u8CmdSystem_CopyFile(T_DEF_FILE_ENV_INI.ps8_path_file,
								 T_DEF_FILE_ENV_SAV.ps8_path_file);
		}
	}
		
}/*InitBDD_Environmt*/

//=====================================================================================
// Fonction		: InitModule_Environmt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation du module de environmt de l'équipement
//=====================================================================================
void InitModule_Environmt(void)
{
	
}/*InitModule_Environmt*/

