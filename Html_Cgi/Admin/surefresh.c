/*========================================================================*/
/* NOM DU FICHIER  : surefresh.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 23/08/2007                                           */
/* Libelle         : HTML CGI: page HTML de config refresh HTML			  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUREFRESH


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_tps_refresh			[20 + 1];
	s8sod	ps8_hidden1				[20 + 1];
} S_CONFIG_ADMREFRESH_RESULTS;

FIELD_LIST s_ConfigAdmRefreshFields[] = {
	{"tps_refresh",	  "%s",		offsetof(S_CONFIG_ADMREFRESH_RESULTS, ps8_tps_refresh)	},
	{"hidden1",		  "%s",		offsetof(S_CONFIG_ADMREFRESH_RESULTS, ps8_hidden1)		},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: SUAdmRefresh
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 23/08/07
// Description	: Page HTML Administration: REfresh
//=====================================================================================
void SUAdmRefresh(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_ADMREFRESH_RESULTS loc_s_results;
	s8sod loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;

	loc_u8_result_test = FALSE; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */
	
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUAdmRefresh");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_ADMREFRESH_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigAdmRefreshFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
			if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
			{
				s_html_cfg_eqpmt.s_admin.u16_tps_refresh_html = (u16sod)atoi(loc_s_results.ps8_tps_refresh);
				if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
				{
					if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
					{
						loc_u8_result_test = TRUE;
					}
				}
			}
			s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

			if(FALSE == loc_u8_result_test)
			{
				sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
						WARNING_CONFIG_KO);
				Html_GotoPage(ps8_pageHtmlRetour);
				return;
			}

			//On recharge la page pour re-initialiser les champs "objets" HTML
			Html_GotoPage("/cgi-bin/cgi_fh?URL=SUAdmRefresh");
			return; // on sort!
		}
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	

	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_rafraichissement);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUAdmRefresh");	//pour la fonction Actualiser

	JSNumCheck();

#if ACTIVATION_CONSOLE_HTML
	//on rafraichie la console dans le cas d'un changement de la config
	html_tag("<SCRIPT LANGUAGE=\"JavaScript\"> \n");
	html_tag("parent.frame_console.document.location.reload(); \n");
	html_tag ("</SCRIPT> \n");
#endif
	
	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmRefresh");//permet d'avoir la bonne page de rafraichit!!

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_rafraichissement);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUAdmRefresh);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Table
	html_tag("<tr><td><table width=\"500\" border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");

	//Temps de rafraichissement minimum
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_temps_rafraichissement_minimum);
	html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"tps_refresh\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;%s</td> \n",
			 s_html_cfg_eqpmt.s_admin.u16_tps_refresh_html,
			 TPS_REFRESH_HTML_MIN,
			 TPS_REFRESH_HTML_MAX,
			pt_tb_msg[u8_html_langue].ps8_msg_secondes);
	html_tag("		</tr> \n");

	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"submit\" value=\"%s\"> </td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider);
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUAdmRefresh*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SURefresh
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SURefresh
//=====================================================================================
void InitModule_SURefresh(void)
{
}/*InitModule_SURefresh*/
