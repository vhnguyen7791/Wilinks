/*========================================================================*/
/* NOM DU FICHIER  : http.c												  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 04/07/2007                                           */
/* Libelle         : Base de données: serveur HTTP						  */
/* Projet          : WRM100                                               */
/* Indice	       : BE047												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE013 26/02/2010 CM
// - Modification chemins des bdd (sous /tmp)
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//Base de données partagées entre les processus du serveur HTTP


/*_____II - DEFINE SBIT __________________________________________________*/

#define _HTTP

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"
#include "../Html_Cgi/Utile/Html_define.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM HTTP.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_CLIENT[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"connecte",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CLIENT_CONNECTE, u8_flag_connecte)},
	{	"addrIP",			FTYPVAL_STRING,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CLIENT_CONNECTE, ps8_addrIP)		},
	{	"level",			FTYPVAL_S32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CLIENT_CONNECTE, s32_AccessLevel)	},
	{	"time",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CLIENT_CONNECTE, u32_time)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_HTTP_INI[] = {
	{	"nom_page_html_enter_pwd",		FTYPVAL_STRING,		NULL,	TAILLE_MAX_NOM_PAGE_HTML,	0,	MACRO_OFFSETOF(S_STRUCT_HTTP_GLOBAL, ps8_nom_page_html_enter_pwd)	},
	{	"s_client",						FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_CLIENT,	sizeof(S_STRUCT_CLIENT_CONNECTE),	NB_CLIENT_IP_MAX,	MACRO_OFFSETOF(S_STRUCT_HTTP_GLOBAL, s_client[0])	},
	{	"connexion_prioritaire_http",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_HTTP_GLOBAL, u8_connexion_prioritaire_http)	},
	{	"url_cfginprogress",			FTYPVAL_STRING,		NULL,	TAILLE_MAX_NOM_PAGE_HTML,	0,	MACRO_OFFSETOF(S_STRUCT_HTTP_GLOBAL, ps8_url_cfginprogress)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER HTTP.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_HTTP_INI =
{
	PATH_DIR__BDD_MISC "http.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_HTTP_INI ,//pt_contenu
};



/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillHttpFile
// Entrees		: <loc_ps_http< : pointeur sur la base de données HTTP
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillHttpFile(S_STRUCT_HTTP_GLOBAL *loc_ps_http)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_http, &T_DEF_FILE_HTTP_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillHttpFile KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillHttpFile*/

//=====================================================================================
// Fonction		: u8EditHttpFile
// Entrees		: <loc_ps_http< : pointeur sur la base de données HTTP
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditHttpFile(S_STRUCT_HTTP_GLOBAL *loc_ps_http)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_http, &T_DEF_FILE_HTTP_INI);

	return loc_u8_resultat;
}/*u8EditHttpFile*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitClientIp
// Entrees		: <loc_ps_client< : pointeur du client
// Sortie		: rien
// Auteur		: CM - 04/07/2007 -
// Description	: Initialisation du module de Http de l'équipement
//=====================================================================================
void InitClientIp(S_STRUCT_CLIENT_CONNECTE	*loc_ps_client)
{
	loc_ps_client->u8_flag_connecte = FALSE;		//INIT
	strcpy(loc_ps_client->ps8_addrIP, "0.0.0.0");	//INIT
	loc_ps_client->s32_AccessLevel = 0;				//INIT
	loc_ps_client->u32_time = 0;					//INIT
}/*InitClientIp*/

//=====================================================================================
// Fonction		: InitBDD_Http
// Entrees		: <loc_ps_http< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 04/07/2007 -
// Description	: Initialisation de la base de données de http
//=====================================================================================
void InitBDD_Http(S_STRUCT_HTTP_GLOBAL *loc_ps_http)
{
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem; 	
	

	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
	
	memset(loc_ps_http,'\0',sizeof(S_STRUCT_HTTP_GLOBAL));

	strcpy(loc_ps_http->ps8_nom_page_html_enter_pwd, "/cgi-bin/cgi_fh?URL=Vaccueil");	//INIT

	for(loc_u8_i=0;loc_u8_i<NB_CLIENT_IP_MAX;loc_u8_i++)
	{
		InitClientIp(&loc_ps_http->s_client[loc_u8_i]); //INIT
	}
	loc_ps_http->u8_connexion_prioritaire_http = FALSE; //INIT
	strcpy(loc_ps_http->ps8_url_cfginprogress, "/cgi-bin/cgi_fh?URL=Vaccueil");	//INIT
	
	u8EditHttpFile(loc_ps_http); //INIT
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_Http*/

//=====================================================================================
// Fonction		: InitModule_Http
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 04/07/2007 -
// Description	: Initialisation du module de Http de l'équipement
//=====================================================================================
void InitModule_Http(void)
{
	
}/*InitModule_Http*/

