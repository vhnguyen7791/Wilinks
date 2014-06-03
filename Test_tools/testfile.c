/*========================================================================*/
/* NOM DU FICHIER  : testfile.c	  	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 22/01/2010                                           */
/* Libelle         : Test gestion fichier								  */
/* Projet          : WRM100		                                          */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE006 22/01/2010 CM
// - CREATION
//BE013 26/02/2010 CM
// - Ajout type FTYPVAL_DATE dans gestion des fichiers
//BE017 12/03/2010 CM
// - Ajout structure simple dans gestion bddfile
//BE035 30/06/2010 CM
// - Correction bug dans le mode test du fichier modele
//BE060 16/03/2011
// - Ajout nouveau type dans gestion bdd/file
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _TESTFILE

#define TAILLE_MAX_MOT1		50
#define TAILLE_MAX_MTSTTAB	3
#define TAILLE_MAX_MOT2		10

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//*****************************************
/* structure (RAM) de TEST				  */
//*****************************************
typedef struct 
{
	s8sod	ps8_ministring[TAILLE_MAX_MOT1+1];	//FTYPVAL_STRING
	u8sod	u8_miniu8;	//FTYPVAL_U8SOD
	s8sod	s8_minis8;	//FTYPVAL_S8SOD
	u16sod	u16_miniu16;	//FTYPVAL_U16SOD
	s16sod	s16_minis16;	//FTYPVAL_S16SOD
	u32sod	u32_miniu32;	//FTYPVAL_U32SOD
	s32sod	s32_minis32;	//FTYPVAL_S32SOD
	u8sod	pu8_miniadrmac	[ETHER_ADDR_LEN];	//FTYPVAL_ADR_MAC
	S_STRUCT_DATE	s_minidate;				//FTYPVAL_DATE
	u8sod	pu8_minitabu8_hexa[TAILLE_MAX_MOT2];	//FTYPVAL_TABU8_HEXA

}S_STRUCT_MINI_MODTEST;

typedef struct 
{
	s8sod	ps8_mtststring[TAILLE_MAX_MOT1+1];	//FTYPVAL_STRING
	u8sod	u8_mtstu8;	//FTYPVAL_U8SOD
	s8sod	s8_mtsts8;	//FTYPVAL_S8SOD
	u16sod	u16_mtstu16;	//FTYPVAL_U16SOD
	s16sod	s16_mtsts16;	//FTYPVAL_S16SOD
	u32sod	u32_mtstu32;	//FTYPVAL_U32SOD
	s32sod	s32_mtsts32;	//FTYPVAL_S32SOD
	u8sod	pu8_mtstadrmac[ETHER_ADDR_LEN];	//FTYPVAL_ADR_MAC
	S_STRUCT_DATE	s_mtstdate;				//FTYPVAL_DATE
	u8sod	pu8_mtsttabu8_hexa[TAILLE_MAX_MOT2];	//FTYPVAL_TABU8_HEXA

	//complexe
	S_STRUCT_MINI_MODTEST	ps_mtsttabstruc[TAILLE_MAX_MTSTTAB]; //FTYPVAL_TABSTRUCT
	//tableau
	u8sod	pu8_mtsttabu8[TAILLE_MAX_MTSTTAB];	//FTYPVAL_TABSTRUCT
	//structure simple
	S_STRUCT_MINI_MODTEST	s_mtststrucsimple; //FTYPVAL_TABSTRUCT

}S_STRUCT_MODELE_TST;

S_STRUCT_MODELE_TST T_MODELETEST_PAR_DEFAUT = {
	"TEST STRING",	//ps8_mtststring
	85,	//u8_mtstu8
	(-85),	//s8_mtsts8*
	1245,	//u16_mtstu16
	(-1245),//s16_mtsts16
	0xF1234567,	//u32_mtstu32
	(-987654321),	//s32_mtsts32
	{0xF1,0xE2,0xD3,0xC4,0xB5,0xA6}, //pu8_mtstadrmac
	{2010,02,27,15,21,49}, //s_mtstdate
	{0x19,0x91,0x28,0x82,0x37,0x73,0x46,0x64,0xAB,0xCD}, //pu8_minitabu8_hexa[TAILLE_MAX_MOT2]
	{//ps_mtsttabstruc[TAILLE_MAX_MTSTTAB]
		{//ps_mtsttabstruc[0]
			"TEST MINI 1",	//ps8_mtststring
			101,	//u8_mtstu8
			(-101),	//s8_mtsts8*
			1001,	//u16_mtstu16
			(-1001),//s16_mtsts16
			10001001,	//u32_mtstu32
			(-10001001),	//s32_mtsts32
			{0x11,0x12,0x13,0x14,0x15,0x16}, //pu8_mtstadrmac
			{2011,03,24,8,01,51}, //s_minidate
			{0x01,0x23,0x45,0x67,0x89,0x98,0x76,0x54,0x32,0x10}, //pu8_mtsttabu8_hexa[TAILLE_MAX_MOT2]
		},
		{//ps_mtsttabstruc[1]
			"TEST MINI 2",	//ps8_mtststring
			102,	//u8_mtstu8
			(-102),	//s8_mtsts8*
			1002,	//u16_mtstu16
			(-1002),//s16_mtsts16
			20002002,	//u32_mtstu32
			(-20002002),	//s32_mtsts32
			{0x21,0x22,0x23,0x24,0x25,0x26}, //pu8_mtstadrmac
			{2010,11,3,2,48,07}, //s_minidate
			{0xA1,0xB2,0xC3,0xD4,0xE5,0xF6,0x07,0x18,0x29,0x3A}, //pu8_mtsttabu8_hexa[TAILLE_MAX_MOT2]
		},
		{//ps_mtsttabstruc[1]
			"TEST MINI 3",	//ps8_mtststring
			103,	//u8_mtstu8
			(-103),	//s8_mtsts8*
			1003,	//u16_mtstu16
			(-1003),//s16_mtsts16
			30003003,	//u32_mtstu32
			(-30003003),	//s32_mtsts32
			{0x31,0x32,0x33,0x34,0x35,0x36}, //pu8_mtstadrmac
			{2013,6,7,19,30,15}, //s_minidate
			{0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE,0xCA,0xFE}, //pu8_mtsttabu8_hexa[TAILLE_MAX_MOT2]
		},
	},
	{100,50,25},//pu8_mtsttabu8[TAILLE_MAX_MTSTTAB]
	//structure simple
	{//s_mtststrucsimple
		"TEST STRUCT SIMPLE",	//ps8_mtststring
		244,	//u8_mtstu8
		(-99),	//s8_mtsts8*
		22045,	//u16_mtstu16
		(-11201),//s16_mtsts16
		10203040,	//u32_mtstu32
		(-10203040),	//s32_mtsts32
		{0x31,0x32,0x33,0x34,0x35,0x36}, //pu8_mtstadrmac
		{2028,4,8,01,12,35}, //s_minidate
		{0xCA,0xFE,0x00,0x00,0xCA,0xFE,0x00,0x00,0xCA,0xFE}, //pu8_mtsttabu8_hexa[TAILLE_MAX_MOT2]
	},
};

//****************************************
//Définition du fichier MODELE.TST
//****************************************
//Définition du tableau de structure
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_MINITABSTRUCT[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0},
	{	"ministring",		FTYPVAL_STRING,		NULL,	TAILLE_MAX_MOT1,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, ps8_ministring)	},
	{	"miniu8",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, u8_miniu8)	},
	{	"minis8",			FTYPVAL_S8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s8_minis8)	},
	{	"miniu16",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, u16_miniu16)	},
	{	"minis16",			FTYPVAL_S16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s16_minis16)	},
	{	"miniu32",			FTYPVAL_U32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, u32_miniu32)	},
	{	"minis32",			FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s32_minis32)	},
	{	"miniadrmac",		FTYPVAL_ADR_MAC,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, pu8_miniadrmac)	},
	{	"minidate",			FTYPVAL_DATE,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s_minidate)	},
	{	"minitabu8_hexa",	FTYPVAL_TABU8_HEXA,	NULL,	TAILLE_MAX_MOT2,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, pu8_minitabu8_hexa)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//Définition de structure simple
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_MINIONLYSTRUCT[] = {
	{	"ministring",		FTYPVAL_STRING,		NULL,	TAILLE_MAX_MOT1,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, ps8_ministring)	},
	{	"miniu8",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, u8_miniu8)	},
	{	"minis8",			FTYPVAL_S8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s8_minis8)	},
	{	"miniu16",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, u16_miniu16)	},
	{	"minis16",			FTYPVAL_S16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s16_minis16)	},
	{	"miniu32",			FTYPVAL_U32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, u32_miniu32)	},
	{	"minis32",			FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s32_minis32)	},
	{	"miniadrmac",		FTYPVAL_ADR_MAC,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, pu8_miniadrmac)	},
	{	"minidate",			FTYPVAL_DATE,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, s_minidate)	},
	{	"minitabu8_hexa",	FTYPVAL_TABU8_HEXA,	NULL,	TAILLE_MAX_MOT2,	0,	MACRO_OFFSETOF(S_STRUCT_MINI_MODTEST, pu8_minitabu8_hexa)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};


T_STRUCT_FILE_FIELD PT_CONTENU_FILE_MODEL_TST[] = {
	{	"mtststring",		FTYPVAL_STRING,		NULL,	TAILLE_MAX_MOT1,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, ps8_mtststring)	},
	{	"mtstu8",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, u8_mtstu8)	},
	{	"mtsts8",			FTYPVAL_S8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, s8_mtsts8)	},
	{	"mtstu16",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, u16_mtstu16)	},
	{	"mtsts16",			FTYPVAL_S16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, s16_mtsts16)	},
	{	"mtstu32",			FTYPVAL_U32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, u32_mtstu32)	},
	{	"mtsts32",			FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, s32_mtsts32)	},
	{	"mtstadrmac",		FTYPVAL_ADR_MAC,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, pu8_mtstadrmac)	},
	{	"mtstdate",			FTYPVAL_DATE,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, s_mtstdate)	},
	{	"mtsttabu8_hexa",	FTYPVAL_TABU8_HEXA,	NULL,	TAILLE_MAX_MOT2,	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, pu8_mtsttabu8_hexa)	},
	{	"mtsttabstruc",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_MINITABSTRUCT,	(u16sod)sizeof(S_STRUCT_MINI_MODTEST),	TAILLE_MAX_MTSTTAB,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, ps_mtsttabstruc[0]) },
	{	"mtsttabu8",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_TABU8,	sizeof(u8sod),	TAILLE_MAX_MTSTTAB,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, pu8_mtsttabu8[0]) },
	{	"mtststrucsimple",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_MINIONLYSTRUCT,	(u16sod)sizeof(S_STRUCT_MINI_MODTEST),	0,	MACRO_OFFSETOF(S_STRUCT_MODELE_TST, s_mtststrucsimple) },

	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_MODELE_TST =
{
	PATH_DIR_ROOT "modele.tst", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_MODEL_TST ,//pt_contenu
};

static	S_STRUCT_MODELE_TST s_modele_test;
/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: TestFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/01/2010 -
// Description	: Teste la gestion fcihier
//=====================================================================================
void TestFile(void)
{
	//Initialisation structure RAM
	memset(&s_modele_test, 0, sizeof(S_STRUCT_MODELE_TST)); //INIT
	s_modele_test = T_MODELETEST_PAR_DEFAUT;	//INIT
	//TEST DU FICHIER MODELE
	printf("Edition du fichier de TEST ... \n");
	if(TRUE == u8Transfert_StructToFile(&s_modele_test, &T_DEF_FILE_MODELE_TST))
	{
		memset(&s_modele_test, 0, sizeof(S_STRUCT_MODELE_TST)); //RAZ
		printf("Lecture du fichier de TEST ...\n");
		if(TRUE == u8Transfert_FileToStruct(&s_modele_test, &T_DEF_FILE_MODELE_TST))
		{
			printf("LECTURE OK ... \n");
			memset(&s_modele_test, 0, sizeof(S_STRUCT_MODELE_TST)); //RAZ
			printf("Affichage du contenu (RAM) de TEST ... \n");
			u8Display_FileToStruct(&s_modele_test, &T_DEF_FILE_MODELE_TST);
			printf("Comparaison avec donnees initiales ... \n");
			if(0 == memcmp(&s_modele_test, &T_MODELETEST_PAR_DEFAUT, sizeof(S_STRUCT_MODELE_TST)))
			{
				printf("COMPARAISON OK \n");
			}
			else
			{
				printf("COMPARAISON KO \n");
			}
		}
		else
		{
			printf("LECTURE KO ... \n");
		}
	}
	else
	{
		printf("Edition du fichier de TEST KO ...\n");
	}

}/*TestFile*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_TestFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/01/2010 -
// Description	: Initialisation du module de testfile
//=====================================================================================
void InitModule_TestFile(void)
{
}/*InitModule_TestFile*/

