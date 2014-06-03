/*========================================================================*/
/* NOM DU FICHIER  : frame.c       										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML frame							  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _FRAME	1

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

#if ACTIVATION_CONSOLE_HTML
//=====================================================================================
// Fonction		: VFrame
// Entrees		: <loc_ps8_frame_a< : frame A
//				  <loc_ps8_frame_b< : frame B
//				  <loc_ps8_frame_c< : frame C
//				  <loc_ps8_frame_console< : frame Console
// Sortie		: rien
// Auteur		: CM - 11/06/2007 -
// Description	: Définition des frames du site web
//=====================================================================================
void VFrame(s8sod* loc_ps8_frame_a, s8sod* loc_ps8_frame_b, s8sod* loc_ps8_frame_c, s8sod* loc_ps8_frame_console)
{
	html_tag(
			 "<frameset rows='90,*' frameborder='YES' border='1' framespacing='0'>\n"
			 "	<frame src='%s' name='frame_a' frameborder='YES' noresize scrolling='NO'>\n"
			 "	<frameset cols='220,*'>\n"
			 "		<frameset rows='*,60'>\n"
			 "			<frame src='%s'		name='frame_b'	frameborder='YES' noresize scrolling='YES'>\n"
			 "			<frame src='%s'		name='frame_console' frameborder='NO' noresize scrolling='NO'>\n"
			 "		</frameset>\n"
			 "		<frame src='%s'	name='frame_c'	frameborder='NO'  noresize scrolling='YES'>\n"
			 "	</frameset>\n"
			 "</frameset>\n", loc_ps8_frame_a, loc_ps8_frame_b, loc_ps8_frame_console, loc_ps8_frame_c);
}/*VFrame*/	

#else

//=====================================================================================
// Fonction		: VFrame
// Entrees		: <loc_ps8_frame_a< : frame A
//				  <loc_ps8_frame_b< : frame B
//				  <loc_ps8_frame_c< : frame C
// Sortie		: rien
// Auteur		: CM - 11/06/2007 -
// Description	: Définition des frames du site web
//=====================================================================================
void VFrame(s8sod* loc_ps8_frame_a, s8sod* loc_ps8_frame_b, s8sod* loc_ps8_frame_c)
{
	html_tag(
			 "<frameset rows='90,*' frameborder='YES' border='1' framespacing='0'>\n"
			 "	<frame src='%s' name='frame_a' frameborder='YES' noresize scrolling='NO'>\n"
			 "	<frameset cols='220,*'>\n"
			 "		<frame src='%s'		name='frame_b'	frameborder='YES' noresize scrolling='YES'>\n"
			 "		<frame src='%s'	name='frame_c'	frameborder='NO'  noresize scrolling='YES'>\n"
			 "	</frameset>\n"
			 "</frameset>\n", loc_ps8_frame_a, loc_ps8_frame_b, loc_ps8_frame_c);
}/*VFrame*/

#endif	

//=====================================================================================
// Fonction		: home
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Frameset d'accueil
//=====================================================================================
void home(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_type_equipement;

	loc_u8_type_equipement = EQUIPEMENT_INCONNU; //INIT
	
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(TRUE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		loc_u8_type_equipement = s_html_exploit.s_general.u8_type_equipement;
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	html_tag("<HTML>\n");
	html_tag("<HEAD>\n");
	// Header
	html_tag("<TITLE>%s</TITLE>",
			 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue]);

	// Javascript pour afficher toujours le meme message dans la barre de statut
	html_tag("<SCRIPT LANGUAGE=\"JavaScript\">");
	html_tag("window.status = \"%s\";",
			 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue]);
	html_tag ("</SCRIPT>");


	// Build the frames
#if ACTIVATION_CONSOLE_HTML
	VFrame("/cgi-bin/cgi_fh?URL=HomeA", "/cgi-bin/cgi_fh?URL=HomeB", "/cgi-bin/cgi_fh?URL=Vaccueil", "/cgi-bin/cgi_fh?URL=VConsole");
#else	
	VFrame("/cgi-bin/cgi_fh?URL=HomeA", "/cgi-bin/cgi_fh?URL=HomeB", "/cgi-bin/cgi_fh?URL=Vaccueil");
#endif

	// Return the HTML page
	html_tag("</HEAD>"); 
	html_tag("</HTML>"); 

}/*home*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Frame
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module frame
//=====================================================================================
void InitModule_Frame(void)
{

}/*InitModule_Frame*/
