/*========================================================================*/
/* NOM DU FICHIER  : cfg_http.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/02/2010                                           */
/* Libelle         : Principal: Configuration du serveur HTTP			  */
/* Projet          : WRM100                                               */
/* Indice          : BE009                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE009 01/02/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_HTTP


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

#define FILE_INDEX_HTML PATH_DIR_ROOT "home/httpd/index.html"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Http
// Entrees		: <loc_ps_exploit<: exploitation (RAM) pour ce processus
//				: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Installe http
//=====================================================================================
void Install_Http(S_STRUCT_EXPLOITATION *loc_ps_exploit, S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Http\n");

	if(TRUE == u8CreationFichierIndexHtml(loc_ps_exploit->s_general.u8_type_equipement, loc_ps_config->s_admin.u8_langue))
	{
		printf("u8CreationFichierIndexHtml OK \n");
	}
	else
	{
		printf("u8CreationFichierIndexHtml KO \n");
	}
	
}/*Install_Http*/

//=====================================================================================
// Fonction		: Uninstall_Http
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Désinstalle  http
//=====================================================================================
void Uninstall_Http(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_Http\n");

}/*Uninstall_Http*/

//=====================================================================================
// Fonction		: u8CreationFichierIndexHtml
// Entrees		: <loc_u8_type_equipement> : type d'équipement
//				  <loc_u8_langue> : langue
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 10/10/2007 -
// Description	: Edition du fichier index.html pour le serveur boa
//=====================================================================================
u8sod u8CreationFichierIndexHtml(u8sod loc_u8_type_equipement, u8sod loc_u8_langue)
{
	FILE *	loc_pf_indexhtml;
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(NULL == (loc_pf_indexhtml = fopen( FILE_INDEX_HTML, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierIndexHtml: KO %s\n",FILE_INDEX_HTML));
		loc_u8_resultat = FALSE;
	}
	else
	{
		fprintf(loc_pf_indexhtml,"<HTML> \r\n");
		fprintf(loc_pf_indexhtml,"<HEAD> \r\n");
		fprintf(loc_pf_indexhtml,"<TITLE>%s</TITLE> \r\n", S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[loc_u8_langue]);
		fprintf(loc_pf_indexhtml,"<frameset rows='90,*' frameborder='YES' border='1' framespacing='0'>  \r\n");
		fprintf(loc_pf_indexhtml,"	<frame src='/cgi-bin/cgi_fh?URL=HomeA' name='frame_a' frameborder='YES' noresize scrolling='NO'> \r\n");
		fprintf(loc_pf_indexhtml,"	<frameset cols='220,*'> \r\n");
#if	ACTIVATION_CONSOLE_HTML		
		fprintf(loc_pf_indexhtml,"		<frameset rows='*,60'> \r\n");
		fprintf(loc_pf_indexhtml,"			<frame src='/cgi-bin/cgi_fh?URL=HomeB'		name='frame_b'	frameborder='NO' noresize scrolling='YES'> \r\n");
		fprintf(loc_pf_indexhtml,"			<frame src='/cgi-bin/cgi_fh?URL=VConsole'		name='frame_console' frameborder='NO' noresize scrolling='NO'> \r\n");
		fprintf(loc_pf_indexhtml,"		</frameset> \r\n");
#else
		fprintf(loc_pf_indexhtml,"			<frame src='/cgi-bin/cgi_fh?URL=HomeB'		name='frame_b'	frameborder='NO' noresize scrolling='YES'> \r\n");
#endif
		fprintf(loc_pf_indexhtml,"		<frame src='/cgi-bin/cgi_fh?URL=Vaccueil'	name='frame_c'	frameborder='NO'  noresize scrolling='YES'> \r\n");
		fprintf(loc_pf_indexhtml,"	</frameset> \r\n");
		fprintf(loc_pf_indexhtml,"</frameset> \r\n");
		fprintf(loc_pf_indexhtml,"</HEAD> \r\n");
		fprintf(loc_pf_indexhtml,"</HTML> \r\n");

		fclose(loc_pf_indexhtml);
	}

	return loc_u8_resultat;
}/*u8CreationFichierIndexHtml*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Http
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 28/01/2010 -
// Description	: Initialisation du module de cfg_http
//=====================================================================================
void InitModule_Cfg_Http(void)
{
	
}/*InitModule_Cfg_Http*/

