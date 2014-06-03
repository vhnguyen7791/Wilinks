/*========================================================================*/
/* NOM DU FICHIER  : vsynoptique.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML synoptique					  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VSYNOPTIQUE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/
#if ACTIVATION_PRESENCE_SYNOPTIQUE

//=====================================================================================
// Fonction		: VSynoptique
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: page HTML synoptique
//=====================================================================================
void VSynoptique(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigConstructeur(&s_html_cfg_eqpmt))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	
	printf("Content-type: text/html\n\n");/* Mandatory */
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		PreparePagePswd("VSynoptique");
		return;  
	}

	html_tag("<HTML>\n");

	// Header
	html_tag("<HEAD>\n");
	html_tag("<TITLE>VSynoptique</TITLE>\n");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("p.header { \n");
	html_tag("	font-size: 15pt; \n");
	html_tag("	font-weight: normal; \n");
	html_tag("} \n");
	html_tag("</STYLE> \n");
	html_tag("</head>\n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VSynoptique");	//pour la fonction Actualiser

	html_tag("<body> \n");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><TD vAlign=top height=52><P class=header>%s: %s</P></TD></tr> \n",
			 s_html_cfg_eqpmt.s_constructeur.ps8_nom,
			 pt_tb_msg[u8_html_langue].ps8_msg_synoptique);
	html_tag("<tr><td><P>&nbsp;</P></td></tr> \n");
	html_tag("<TR><TD><IMG align=left src=\"smx601GB.gif\"></TD></TR>\n");

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<TR><TD>%s</TD></TR> \n",
			 ps8_msg_presentation[u8_html_langue]);

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("</table> \n");


	html_tag("</BODY>\n");
	html_tag("</HTML>\n");
}/*VSynoptique*/

#endif

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


//=====================================================================================
// Fonction		: InitModule_Vsynoptique
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation du module Vsynoptique
//=====================================================================================
void InitModule_Vsynoptique(void)
{

}/*InitModule_Vsynoptique*/
