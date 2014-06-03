/*========================================================================*/
/* NOM DU FICHIER  : suconfigMode.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Mode			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE019 16/03/2010 CM
// - Autorisation de passer la station en bridge
//BE042 07/10/2010 CM
// - Correction configuration mode 802.11 (associé au driver-N)
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE057 20/01/2011 CM
// - Désactivation du mode monitor en WRM100-ABG
//BE060 16/03/2011
// - Correction ergonomie dans page HTML Config Mode 
//		qd on ne confirme pas le changement de mode (si bridge), on revient dans le mode configuré
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGMODE

enum LISTE_DES_FORM_SUCONFIGMODE
{
	FORM_SUCONFIGMODE_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGMODE_VALID_1,
	NB_MAX_FORM_SUCONFIGMODE
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_mode			[10 + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_MODE_RESULTS;

FIELD_LIST s_FormConfigModeFields[] = {
	{"mode_radio",	"%s",		offsetof(S_FORM_CONFIG_MODE_RESULTS, ps8_mode)		},
	
	{"hidden1",		"%s",		offsetof(S_FORM_CONFIG_MODE_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigMode
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigMode
//=====================================================================================
void proc_JavaScript_SUConfigMode(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigMode
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigMode
//=====================================================================================
void proc_JavaScript_SUConfigMode(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");
	
	//Fonction javascript : JsChangeModeRadio
	//*************************************
	html_tag("function JsChangeModeRadio(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.mode_radio.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_RADIO_MODEM_ACCESS_POINT);
	html_tag("			case %d: \n",MODE_RADIO_MODEM_STATION);
	html_tag("			case %d: \n",MODE_RADIO_MODEM_MONITOR);
	if(MODE_NETWORK_BRIDGE == s_html_cfg_eqpmt.s_gene.u8_mode_network)
	{
		html_tag("				if ( confirm(\"%s\") )\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_confirmer_changement_radio_modem);
		html_tag("				{ \n");
		html_tag("					loc_result = true;\n");
		html_tag("				} \n");
		html_tag("				else \n");
		html_tag("				{ \n");
		html_tag("					form.mode_radio.value = %d;\n",s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem);
		html_tag("				} \n");
	}
	else //MODE_NETWORK_ROUTER
	{
		//on autorise pas le changement de mode du radio modem (tant que l'équipement est en router)
		html_tag("				alert(\"%s\");\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_changement_radio_modem_non_autorise);
		html_tag("				form.mode_radio.value = %d;\n",s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem);
		html_tag("				loc_result = false;\n");
	}
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	}\n");
	html_tag("	return loc_result;\n");
	html_tag("}\n"); /*JsChangeModeRadio*/
	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true;\n");
	html_tag("	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigMode*/

//=====================================================================================
// Fonction		: SUConfigMode
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: Mode
//				"URL=SUConfigMode"
//=====================================================================================
void SUConfigMode(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_MODE_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_i;

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigMode");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigMode&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_MODE_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigModeFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGMODE)
			{
				if(FORM_SUCONFIGMODE_VALID_1 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						if((s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem != (u8sod)atoi(loc_s_results.ps8_mode))&&
						   (MODE_NETWORK_BRIDGE == s_html_cfg_eqpmt.s_gene.u8_mode_network)
						  ) //CONDITION: changement de mode radio modem Et si Bridge
						{
							s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem = (u8sod)atoi(loc_s_results.ps8_mode);

							if(TRUE==u8TestConfigGeneral(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigGeneral(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
						else
						{
							loc_u8_result_test = TRUE;
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FALSE == loc_u8_result_test)
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_CONFIG_KO);
					Html_GotoPage(ps8_pageHtmlRetour);
					return;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				PreparePageCfgInProgress("SUConfigMode");
				VCfgInProgress(loc_p_varlist, loc_s32_form_method);
				return; // on sort!
			}
			else//CONDITION: page KO
			{
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return;
			}
		}
	}
	

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
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
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_m);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigMode");	//pour la fonction Actualiser

	proc_JavaScript_SUConfigMode();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigMode");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_m);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUconfigMode);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");

	//Mode du radio modem
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_radio_modem);
	html_tag("			<td><SELECT name=\"mode_radio\" size=\"1\" onchange=\"return(JsChangeModeRadio(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_RADIO_MODEM;loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pt_definition_radio_modem[loc_u8_i].u8_flag_affichage)
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_u8_i == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_radio_m[loc_u8_i]);
		}
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");


	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGMODE_VALID_1);
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigMode*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigMode
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigMode
//=====================================================================================
void InitModule_SUConfigMode(void)
{
}/*InitModule_SUConfigMode*/
