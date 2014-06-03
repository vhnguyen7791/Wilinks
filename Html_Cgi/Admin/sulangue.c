/*========================================================================*/
/* NOM DU FICHIER  : sulangue.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 03/07/2007                                           */
/* Libelle         : HTML CGI: page HTML adminsitration - Langue		  */
/* Projet          : WRM100                                               */
/* Indice          : BE008				  								  */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - Modification page HTML langue (+générique)
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SULANGUE


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_langue				[20 + 1];
	s8sod	ps8_hidden1				[20 + 1];
} S_CONFIG_ADMLANGUE_RESULTS;

FIELD_LIST s_ConfigAdmLangueFields[] = {
	{"langue",		  "%s",		offsetof(S_CONFIG_ADMLANGUE_RESULTS, ps8_langue)	},
	{"hidden1",		  "%s",		offsetof(S_CONFIG_ADMLANGUE_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: SUAdmLangue
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 03/07/07
// Description	: Page HTML Administration: Langue
//=====================================================================================
void SUAdmLangue(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_ADMLANGUE_RESULTS loc_s_results;
	s8sod loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_i;

	loc_u8_result_test = FALSE; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */
	
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUAdmLangue");
		return;
	}

	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_ADMLANGUE_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigAdmLangueFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
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
				s_html_cfg_eqpmt.s_admin.u8_langue = (u8sod)atoi(loc_s_results.ps8_langue);
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
		}

				
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_RELOAD_SUADMLANGUE_ET_RELOAD_FRAME_A_FRAME_B);
		Html_GotoPage(ps8_pageHtmlRetour);
		return; // on sort!
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
			 pt_tb_msg[u8_html_langue].ps8_msg_langue);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUAdmLangue");	//pour la fonction Actualiser

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmLangue");//permet d'avoir la bonne page de rafraichit!!

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_langue);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUAdmLangue);
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

	//Description
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_langue);
	html_tag("			<td><SELECT name=\"langue\">  \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_LANGUES;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_admin.u8_langue) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_langue[loc_u8_i]);
	}
	html_tag("		</select></td> \n");
	html_tag("		</tr> \n");

	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"submit\" value=\"%s\"> </td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider);
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUAdmLangue*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SULangue
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SULangue
//=====================================================================================
void InitModule_SULangue(void)
{
}/*InitModule_SULangue*/
