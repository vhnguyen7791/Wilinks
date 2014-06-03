/*========================================================================*/
/* NOM DU FICHIER  : cip_snmpd.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/03/2010                                           */
/* Libelle         : Base de données: CIP pour processus snmpd			  */
/* Projet          : WRM100                                               */
/* Indice	       : BE013												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 02/03/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//Base de données CIP (Comminication Inter Processus) pour partager des données
//avec le processus snmpd


/*_____II - DEFINE SBIT __________________________________________________*/

#define _CIP_SNMPD

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM CIP_SNMPD.INI
//***************************************************************************

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CIP_SNMPD_INI[] = {
	{	"replay_trap",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_SNMPD, u8_replay_trap)	},
 	{	"flag_newcfg",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_TABU8,	sizeof(u8sod),	NB_MAX_IDXCONFIG,	MACRO_OFFSETOF(S_STRUCT_CIP_SNMPD, pu8_flag_newcfg[0]) },
	{	"acquit_all_traps",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_SNMPD, u8_acquit_all_traps)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER CIP_SNMPD.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_SNMPD_INI =
{
	PATH_DIR__BDD_MISC "cip_snmpd.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CIP_SNMPD_INI ,//pt_contenu
};



/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillCipSnmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 02/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillCipSnmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_cip_snmpd, &T_DEF_FILE_CIP_SNMPD_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillCipSnmpd KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillCipSnmpd*/

//=====================================================================================
// Fonction		: u8EditCipSnmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 02/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditCipSnmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_cip_snmpd, &T_DEF_FILE_CIP_SNMPD_INI);

	return loc_u8_resultat;
}/*u8EditCipSnmpd*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: Raz_Cip_Snmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: RAZ des ordres de la base de données de cip_snmpd
//=====================================================================================
void Raz_Cip_Snmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd)
{
	u8sod	loc_u8_i;

	loc_ps_cip_snmpd->u8_replay_trap = FALSE;	//RAZ
	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		loc_ps_cip_snmpd->pu8_flag_newcfg[loc_u8_i] = FALSE;	//RAZ
	}
	loc_ps_cip_snmpd->u8_acquit_all_traps = FALSE;	//RAZ
}/*Raz_Cip_Snmpd*/

//=====================================================================================
// Fonction		: InitBDD_Cip_Snmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation de la base de données de cip_snmpd
//=====================================================================================
void InitBDD_Cip_Snmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd)
{
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem; 	

	s32Lock_Get(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on lève le sémaphore
	
	memset(loc_ps_cip_snmpd, 0, sizeof(S_STRUCT_CIP_SNMPD)); //INIT

	loc_ps_cip_snmpd->u8_replay_trap = FALSE;	//INIT
	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		loc_ps_cip_snmpd->pu8_flag_newcfg[loc_u8_i] = FALSE;	//INIT
	}
	
	u8EditCipSnmpd(loc_ps_cip_snmpd); //INIT
	s32Lock_Release(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_Cip_Snmpd*/

//=====================================================================================
// Fonction		: InitModule_Cip_Snmpd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation du module de cip_snmpd
//=====================================================================================
void InitModule_Cip_Snmpd(void)
{
	
}/*InitModule_Cip_Snmpd*/

