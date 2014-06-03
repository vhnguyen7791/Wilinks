/*========================================================================*/
/* NOM DU FICHIER  : vcontact.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML contact						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

//pages HTML sur les coordonnées du constructeur

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VCONTACT

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: VContact
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: page HTML contact (Coordonnées de l'entreprise)
//=====================================================================================
void VContact(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;

	printf("Content-type: text/html\n\n");/* Mandatory */
	
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
	
	html_tag("<HTML>\n");

	// Header
	html_tag("<HEAD>\n");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE> \n");
	html_tag("	TD.contact { \n");
	html_tag("		font-size: 12pt; \n");
	html_tag("		font-weight: normal; \n");
	html_tag("} \n");
	html_tag("</STYLE> \n");
	html_tag("<TITLE>Contact</TITLE>");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head>\n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VContact");	//pour la fonction Actualiser

	html_tag("<body>\n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("	<tr><TD vAlign=top height=52><P class=header>%s</P></TD></tr> \n",
			 s_html_cfg_eqpmt.s_constructeur.ps8_nom);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("	<tr><td class=contact>%s</td></tr> \n",
			 s_html_cfg_eqpmt.s_constructeur.ps8_adresse_ligne1);
	html_tag("	<tr><td class=contact>%s</td></tr> \n",
			 s_html_cfg_eqpmt.s_constructeur.ps8_adresse_ligne2);
	if(0 != strcmp(s_html_cfg_eqpmt.s_constructeur.ps8_numero_telephone, VALEUR_CONSTRUCTEUR_NON_UTILISEE)) //CONDITION: à afficher
	{
		html_tag("	<tr><td class=contact>tel. : %s</td></tr> \n",
				 s_html_cfg_eqpmt.s_constructeur.ps8_numero_telephone);
	}
	if(0 != strcmp(s_html_cfg_eqpmt.s_constructeur.ps8_numero_fax, VALEUR_CONSTRUCTEUR_NON_UTILISEE)) //CONDITION: à afficher
	{
		html_tag("	<tr><td class=contact>fax. : %s</td></tr> \n",
				 s_html_cfg_eqpmt.s_constructeur.ps8_numero_fax);
	}
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	if(0 != strcmp(s_html_cfg_eqpmt.s_constructeur.ps8_site_web, VALEUR_CONSTRUCTEUR_NON_UTILISEE)) //CONDITION: à afficher
	{
		html_tag("	<tr><td class=contact><a href=\"http://%s\" target=\"_new\"><b>http://%s</b></a></td></tr> \n",
				 s_html_cfg_eqpmt.s_constructeur.ps8_site_web,
				 s_html_cfg_eqpmt.s_constructeur.ps8_site_web);
	}
	html_tag("</table> \n");
	html_tag("</body>\n");
	html_tag("</html>\n");

}/*contact*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


//=====================================================================================
// Fonction		: InitModule_Vcontact
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation du module Vcontact
//=====================================================================================
void InitModule_Vcontact(void)
{

}/*InitModule_Vcontact*/
