/*========================================================================*/
/* NOM DU FICHIER  : vhomeC.c       									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML  homeC						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _VHOMEC

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: HomeC
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Cadre principal vide
//=====================================================================================
void HomeC(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{	

	printf("Content-type: text/html\n\n");/* Mandatory */
	html_tag("<HTML>\n");	

  // Header
	html_tag("<HEAD>\n");	
	html_tag("<TITLE>HOME C</TITLE>");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</HEAD>\n");	

	//variable stockant la page cible apres saisie du mot de passe
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("      var Adresse = \"/cgi-bin/cgi_fh?URL=Vaccueil\";\n");//par defaut!
	html_tag("</SCRIPT>\n");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("</table> \n");

	html_tag("</HTML>");

}/*HomeC*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VHomeC
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module vhomeC
//=====================================================================================
void InitModule_VHomeC(void)
{

}/*InitModule_VHomeC*/
