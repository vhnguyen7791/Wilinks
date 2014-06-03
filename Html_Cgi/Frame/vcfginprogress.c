/*========================================================================*/
/* NOM DU FICHIER  : vcfginprogress.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/12/2010                                           */
/* Libelle         : HTML CGI: pages HTML pour afficher "config en cours" */
/* Projet          : WRM100                                               */
/* Indice          : BE049                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE047 02/12/2010 CM
// - CREATION
//BE049 08/12/2010 CM
// - Correction actualiser page vcfginprogress
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VCFGINPROGRESS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Pour gérer configuration encours
static u8sod u8_html_ordre_configuration;

enum LISTE_HTML_CFGINPROGRESS
{
	HTML_CFGINPROGRESS_NULL = 0,
	HTML_CFGINPROGRESS_ORDER,
	HTML_CFGINPROGRESS_TEST,
	HTML_CFGINPROGRESS_MAX	
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: VCfgInProgress_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 02/12/2010
// Description	: Page rafraichissement page 
//				"URL=VCfgInProgress_Dyn
//=====================================================================================
void VCfgInProgress_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
//	printf("Content-type: text/html\n\n");/* Mandatory */
	printf("Content-type: text/plain\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}

	//On surveille si configuration en cours
	if(TRUE == u8TestConfig_InProgress())
	{
		html_tag("|");
		html_tag("&&&id:SPAN_CONFIG_INPROGRESS&&&innerHTML:&&&");
	}
	else
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	html_tag("|");
		

}/*VCfgInProgress_Dyn*/

//============================================================================
// Fonction		: PreparePageCfgInProgress
// Entrees		: <loc_ps8_adresse_url<: une chaine de cractere contenant l'adresse de la page demandee
// Sortie		: rien
// Auteur		: CM - 03/12/2010
// Description	: on sauve  la page à accéder et on charge la page HTML CfgInProgress
//============================================================================
void PreparePageCfgInProgress (s8sod *loc_ps8_adresse_url)
{
	s32sod	loc_s32_sem;

	// on recharge la page cachee pour sauvegarder la page demandee
	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
	//On recherche si déjà présent
	if(TRUE == u8FillHttpFile(&s_html_global))
	{
		strcpy(s_html_global.ps8_url_cfginprogress, "/cgi-bin/cgi_fh?URL=");
		strcat(s_html_global.ps8_url_cfginprogress, loc_ps8_adresse_url);
		u8EditHttpFile(&s_html_global);
	}
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem

	//On signal une configuration en cours
	u8_html_ordre_configuration = TRUE;


}/*PreparePageCfgInProgress*/

//=====================================================================================
// Fonction		: VCfgInProgress
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 02/12/2010 -
// Description	: page HTML d'avertissement
//=====================================================================================
void VCfgInProgress(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	u16sod	loc_u16_numPage;

	loc_u16_numPage = HTML_CFGINPROGRESS_NULL; //INIT
	sprintf(ps8_pageHtmlRetour,"cgi_fh?URL=VCfgInProgress&%d",loc_u16_numPage);
	
	if(FALSE == u8_html_ordre_configuration)
	{
		if (loc_p_varlist[2] != NULL)
		{
			loc_u16_numPage = (u16sod)atoi(loc_p_varlist[2]);
			if(loc_u16_numPage < HTML_CFGINPROGRESS_MAX)
			{
				sprintf(ps8_pageHtmlRetour,"cgi_fh?URL=VCfgInProgress&%d",loc_u16_numPage);
			}
		}
		
		printf("Content-type: text/html\n\n");/* Mandatory */
	}
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
			//On retourne à la page d'accueil ( c'est normal )
		PreparePagePswd("Vaccueil");
		return;  
	}

	html_tag("<HTML>\n");

	// Header
	html_tag("<HEAD>\n");
	html_tag("<TITLE>CfgInProgress</TITLE>");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE> \n");
	html_tag("	TD.warning { \n");
	html_tag("		font-size: 12pt; \n");
	html_tag("		font-weight: bold; \n");
	html_tag("		text-align: center; \n");
	html_tag("} \n");
	html_tag("</STYLE> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head>\n");

	html_tag("<body> \n");

	sprintf(ps8_pageHtmlRetour,"cgi_fh?URL=VCfgInProgress&%d",HTML_CFGINPROGRESS_NULL); 
	JSActualiser(ps8_pageHtmlRetour);	//pour la fonction Actualiser
	if(HTML_CFGINPROGRESS_TEST == loc_u16_numPage)
	{
		RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=VCfgInProgress_Dyn", (u32sod)1000); //On force raffraichissement à la seconde (car config non dispo)
	}

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("	<TR><TD vAlign=top height=40><P class=header>%s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_avertissement);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("	<TR><TD align=center class=warning>%s<BR>%s</TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration_en_cours,
			 pt_tb_msg[u8_html_langue].ps8_msg_veuillez_patienter);
	html_tag("<span id=SPAN_CONFIG_INPROGRESS></span> \n");
	//On surveille si configuration en cours
	if((TRUE == u8TestConfig_InProgress())||
	   (TRUE == u8_html_ordre_configuration)||
	   (HTML_CFGINPROGRESS_ORDER == loc_u16_numPage)

	  ) //CONDITION: configuration en cours ou ordre donné en interne 
	{
		if(TRUE == u8_html_ordre_configuration)
		{
			html_tag("<script language=\"javascript\">\n");
			html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=VCfgInProgress&%d\");",HTML_CFGINPROGRESS_ORDER);
			html_tag("</script>\n");
		}
		else
		{
			if(HTML_CFGINPROGRESS_ORDER == loc_u16_numPage)
			{
				html_tag("<script language=\"javascript\">\n");
				html_tag("setTimeout('self.location.replace(\"/cgi-bin/cgi_fh?URL=VCfgInProgress&%d\")',2000);",HTML_CFGINPROGRESS_TEST);
				html_tag("</script>\n");
			}
		}
	}
	else//CONDITION: configuration terminée
	{
		html_tag("<script language=\"javascript\">\n");
		s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillHttpFile(&s_html_global))
		{
			html_tag("self.location.replace(\"%s\");", s_html_global.ps8_url_cfginprogress);
		}
		else
		{
			html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=Vaccueil\");");
		}
		s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem
		html_tag("</script>\n");
	}

	
	html_tag("</table> \n");
	html_tag("</body>\n");
	html_tag("</html>\n");

}/*VCfgInProgress*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


//=====================================================================================
// Fonction		: InitModule_VcfgInProgress
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Initialisation du module Vcfginprogress
//=====================================================================================
void InitModule_VcfgInProgress(void)
{
	u8_html_ordre_configuration = FALSE;	//INIT

}/*InitModule_VcfgInProgress*/
