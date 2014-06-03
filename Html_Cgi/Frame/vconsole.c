/*========================================================================*/
/* NOM DU FICHIER  : vconsole.c       									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML console						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _VCONSOLE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

const s8sod S8_COULEUR_TEXT_CONSOLE[NB_MAX_COULEUR_CONSOLE][30] =
{
	"#FFFFFF",	//COULEUR_CONSOLE_BLANC
	"#000000",	//COULEUR_CONSOLE_NOIR
	"#FFFF00",	//COULEUR_CONSOLE_JAUNE
	"#008000",	//COULEUR_CONSOLE_VERT
	"#0000FF",	//COULEUR_CONSOLE_BLEU
	"#FF0000",	//COULEUR_CONSOLE_ROUGE
	"#FF00FF",	//COULEUR_CONSOLE_MAGENTA
	"#FFA500",	//COULEUR_CONSOLE_ORANGE
};

/*_____V - PROCEDURES ____________________________________________________*/

#if ACTIVATION_CONSOLE_HTML
//=====================================================================================
// Fonction		: VConsole_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 02/08/2007
// Description	: Page rafraichissement console HTML
//				"URL=VConsole_Dyn
//=====================================================================================
void VConsole_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod		loc_s32_sem;
	s8sod		loc_ps8_couleur[20];

//	printf("Content-type: text/html\n\n");/* Mandatory */
	printf("Content-type: text/plain\n\n");/* Mandatory */
	

	if(TRUE == TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		s32Lock_Get(SEMAPHORE_BDD_CONSOLE_HTTP, &loc_s32_sem);	//on lève le sémaphore

		// Choix de la couleur
		if(ps_msg_consoleHttp->u8_couleur < NB_MAX_COULEUR_CONSOLE)
		{
			strcpy(loc_ps8_couleur, S8_COULEUR_TEXT_CONSOLE[ps_msg_consoleHttp->u8_couleur]);
		}
		else
		{
			strcpy(loc_ps8_couleur, S8_COULEUR_TEXT_CONSOLE[COULEUR_CONSOLE_NOIR]);
		}

		html_tag("|");
		html_tag("&&&id:FONT_TXT&&&stylecolor:%s&&&",
				 loc_ps8_couleur);
		html_tag("|");
		html_tag("&&&id:SPAN_TXT&&&innerHTML:%s&&&",
				 ps8ConvertSansEspaceChaineToHtml(ps_msg_consoleHttp->ps8_chaine));
		html_tag("|");

		s32Lock_Release(SEMAPHORE_BDD_CONSOLE_HTTP, &loc_s32_sem);	//on relache le sem
	}
	else
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE&&&");
		html_tag("|");
	}

}/*VConsole_Dyn*/

//=====================================================================================
// Fonction		: VConsole
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 14/06/2007
// Description	: page HTML de console
//=====================================================================================
void VConsole(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	s8sod loc_ps8_couleur[20];

	printf("Content-type: text/html\n\n");/* Mandatory */

	html_tag("<HTML>\n");

	// Header
	html_tag("<head> \n");
	html_tag("<title>CONSOLE</title> \n");
	html_tag("<STYLE type=text/css> \n"
			 "	 BODY { \n"
			 "		BACKGROUND: #000000; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif \n"
			 "	} \n"
			 "	P { \n"
			 "		FONT-SIZE: 8pt; COLOR: #FFFFFF; FONT-FAMILY: Verdana, Arial, Helvetica, sans-serif \n"
			 "	} \n"
			 "	</STYLE> \n");
	html_tag("</head> \n");

	//Initialisation 

	s32Lock_Get(SEMAPHORE_BDD_CONSOLE_HTTP, &loc_s32_sem);	//on lève le sémaphore

	// Choix de la couleur
	if(ps_msg_consoleHttp->u8_couleur < NB_MAX_COULEUR_CONSOLE)
	{
		strcpy(loc_ps8_couleur, S8_COULEUR_TEXT_CONSOLE[ps_msg_consoleHttp->u8_couleur]);
	}
	else
	{
		strcpy(loc_ps8_couleur, S8_COULEUR_TEXT_CONSOLE[COULEUR_CONSOLE_NOIR]);
	}

	html_tag("<body> \n");
	
	//on rafraichie la console uniquement si on est connecté
	if(TRUE == TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=VConsole_Dyn", (u32sod)u16GetTpsRefreshHtml()*1000);

		// Texte
		html_tag("<p align=center>");
		html_tag("<FONT id=FONT_TXT COLOR=\"%s\">\n", loc_ps8_couleur);
		html_tag("<strong><span id=SPAN_TXT>%s</span></strong>\n", ps_msg_consoleHttp->ps8_chaine);
		html_tag("</FONT>\n");
		html_tag("</p>\n");
	}

	html_tag("</body> \n");
	html_tag("</html> \n");

	s32Lock_Release(SEMAPHORE_BDD_CONSOLE_HTTP, &loc_s32_sem);	//on relache le sem

}/*VConsole*/
#endif

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VConsole
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 14/06/2007 -
// Description	: Initialisation du module VConsole
//=====================================================================================
void InitModule_VConsole(void)
{
}/*InitModule_VConsole*/
