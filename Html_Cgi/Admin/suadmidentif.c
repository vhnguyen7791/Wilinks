/*========================================================================*/
/* NOM DU FICHIER  : suadmidentif.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML Administration - Identification */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUADMIDENTIF


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_IDEquipement			[LG_NOM_IDENTIFIANT + 1];
	s8sod	ps8_LocalisationEquipement	[LG_NOM_LOCALISATION + 1];
	s8sod	ps8_hidden1					[20 + 1];
} S_CONFIG_ADMINIDENTIF_RESULTS;

FIELD_LIST s_ConfigAdmFields[] = {
	{"IDEquipement",			"%s",		offsetof(S_CONFIG_ADMINIDENTIF_RESULTS, ps8_IDEquipement)				},
	{"LocalisationEquipement",	"%s",		offsetof(S_CONFIG_ADMINIDENTIF_RESULTS, ps8_LocalisationEquipement)	},
	{"hidden1",					"%s",		offsetof(S_CONFIG_ADMINIDENTIF_RESULTS, ps8_hidden1)					},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: SUAdmIdentification
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: 
// Description	: Page HTML Administration: Identification
//=====================================================================================
void SUAdmIdentification(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_ADMINIDENTIF_RESULTS loc_s_results;
	s8sod loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;

	loc_u8_result_test = FALSE; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */
	
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUAdmIdentification");
		return;
	}

	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_ADMINIDENTIF_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigAdmFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
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
				strcpy((s8sod *)(s_html_cfg_eqpmt.s_admin.ps8_identifiant),loc_s_results.ps8_IDEquipement);
				strcpy((s8sod *)(s_html_cfg_eqpmt.s_admin.ps8_localisation),loc_s_results.ps8_LocalisationEquipement);
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
			
			sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
					WARNING_RELOAD_SUADMINDENTIF_ET_RELOAD_FRAME_A);
			Html_GotoPage(ps8_pageHtmlRetour);
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
			 pt_tb_msg[u8_html_langue].ps8_msg_identification);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUAdmIdentification");	//pour la fonction Actualiser

	JSTextCheck();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"formIdentif\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmIdentification");//permet d'avoir la bonne page de rafraichit!!

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_identification);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_identification);
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
			 pt_tb_msg[u8_html_langue].ps8_msg_description);
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_radio_modem);
	html_tag("		</tr> \n");

	//Identifiant de l'équipement
	html_tag("		<tr> \n");
	html_tag("			<td nowrap>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_identifiant_equipement);
	html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"IDEquipement\" value=\"%s\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
			 LG_NOM_IDENTIFIANT,
			 LG_NOM_IDENTIFIANT,
			 s_html_cfg_eqpmt.s_admin.ps8_identifiant);
	html_tag("		</tr> \n");

	//Localisation de l'équipement
	html_tag("		<tr> \n");
	html_tag("			<td nowrap>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_localisation_equipement);
	html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"LocalisationEquipement\" value=\"%s\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
			 LG_NOM_LOCALISATION,
			 LG_NOM_LOCALISATION,
			 s_html_cfg_eqpmt.s_admin.ps8_localisation);
	html_tag("		</tr> \n");

	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"submit\" value=\"%s\"> </td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider);
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUAdmIdentification*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUAdmIdentif
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de suadmidentif
//=====================================================================================
void InitModule_SUAdmIdentif(void)
{
}/*InitModule_SUAdmIdentif*/
