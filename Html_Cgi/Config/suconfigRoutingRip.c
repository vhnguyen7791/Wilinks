/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingRip.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 20/04/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing / RIP	  */
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 20/04/2010 CM
// - CREATION
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGROUTINGRIP


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGROUTINGRIP
{
	FORM_SUCONFIGROUTINGRIP_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGROUTINGRIP_VALID_ALL,
	NB_MAX_FORM_SUCONFIGROUTINGRIP
};

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_activation	[10 + 1];
	s8sod	ps8_interface_rip[NB_MAX_RIP_INTERFACES]	[10 + 1];
	s8sod	ps8_authentication	[10 + 1];
	s8sod	ps8_password	[TAILLE_MAX_RIP_PASSWORD + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_ROUTINGRIP_RESULTS;

FIELD_LIST s_FormConfigRoutingRipFields[] = {
	{"actRip",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGRIP_RESULTS, ps8_activation)	},
	{"ifrip0",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGRIP_RESULTS, ps8_interface_rip[RIP_INTERF_LAN])	},
	{"ifrip1",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGRIP_RESULTS, ps8_interface_rip[RIP_INTERF_WLAN])	},
	{"authRip",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGRIP_RESULTS, ps8_authentication)	},
	{"pwdRip",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGRIP_RESULTS, ps8_password)	},
	
	{"hidden1",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGRIP_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingRip
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigRoutingRip
//=====================================================================================
void proc_JavaScript_SUConfigRoutingRip(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingRip
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigRoutingRip
//=====================================================================================
void proc_JavaScript_SUConfigRoutingRip(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		JSChangeActivationRip(); \n");
	html_tag("	} \n");
	html_tag("} \n");

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("		with(document) \n");
	html_tag("		{  \n");
	html_tag("			switch(i_numForm)  \n");
	html_tag("			{  \n");
	html_tag("				case %d:  \n",FORM_SUCONFIGROUTINGRIP_VALID_ALL);
	html_tag("					if((false == form.ifrip%d.checked)&&  \n",RIP_INTERF_LAN);
	html_tag("					   (false == form.ifrip%d.checked)&&  \n",RIP_INTERF_WLAN);
	html_tag("					   (%d == Number(form.actRip.value)) \n",TRUE);
	html_tag("					  )  \n");
	html_tag("					{  \n");
	html_tag("						alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_il_faut_selectionner_interface_rip);
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("					break;	  \n");
	html_tag("				default:  \n");
	html_tag("					loc_result = true; \n");
	html_tag("					break;	  \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag( "	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	//Fonction javascript : JSChangeAuthRip
	//*************************************
	html_tag("function JSChangeAuthRip() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if(%d == Number(form.actRip.value)) \n",TRUE);
	html_tag("		{ \n");
	html_tag("			switch(Number(form.authRip.value)) \n");
	html_tag("			{ \n");
	html_tag("				case %d: \n",RIP_AUTHENTICATION_PLAIN_TEXT);
	html_tag("				case %d: \n",RIP_AUTHENTICATION_MD5);
	html_tag("					form.pwdRip.disabled = false; \n");
	html_tag("					break; \n");
	html_tag("				case %d: \n",RIP_AUTHENTICATION_NONE);
	html_tag("				default: \n");
	html_tag("					form.pwdRip.disabled = true; \n");
	html_tag("					break; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			form.pwdRip.disabled = true; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeAuthRip*/

	//Fonction javascript : JSChangeActivationRip
	//*************************************
	html_tag("function JSChangeActivationRip() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.actRip.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",TRUE);
	html_tag("				form.ifrip%d.disabled = false; \n",RIP_INTERF_LAN);
	html_tag("				form.ifrip%d.disabled = false; \n",RIP_INTERF_WLAN);
	html_tag("				form.authRip.disabled = false; \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",FALSE);
	html_tag("			default: \n");
	html_tag("				form.ifrip%d.disabled = true; \n",RIP_INTERF_LAN);
	html_tag("				form.ifrip%d.checked = false; \n",RIP_INTERF_LAN);
	html_tag("				form.ifrip%d.disabled = true; \n",RIP_INTERF_WLAN);
	html_tag("				form.ifrip%d.checked = false; \n",RIP_INTERF_WLAN);
	html_tag("				form.authRip.disabled = true; \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("		JSChangeAuthRip(); \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeActivationRip*/
			
	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigRoutingRip*/

//=====================================================================================
// Fonction		: SUConfigRoutingRip
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 20/04/2010
// Description	: Page HTML Configuration: IP Routing  / RIP
//				"URL=SUConfigRoutingRip"
//=====================================================================================
void SUConfigRoutingRip(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_ROUTINGRIP_RESULTS loc_s_results;
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
		PreparePagePswd("SUConfigRoutingRip");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigRoutingRip&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_ROUTINGRIP_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigRoutingRipFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGROUTINGRIP)
			{
				if(FORM_SUCONFIGROUTINGRIP_NULL == loc_u8_numForm)
				{
					loc_u8_result_test = TRUE;
				}
				
				if(FORM_SUCONFIGROUTINGRIP_VALID_ALL == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigRouting(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_ip_routing.u8_ripv2_activation = (u8sod)atoi(loc_s_results.ps8_activation);
						for(loc_u8_i=0;loc_u8_i<NB_MAX_RIP_INTERFACES;loc_u8_i++)
						{
							s_html_cfg_eqpmt.s_ip_routing.pu8_rip_interface_used[loc_u8_i] = (u8sod)atoi(loc_s_results.ps8_interface_rip[loc_u8_i]);
						}
						s_html_cfg_eqpmt.s_ip_routing.u8_rip_authentification = (u8sod)atoi(loc_s_results.ps8_authentication);
						if(RIP_AUTHENTICATION_NONE != s_html_cfg_eqpmt.s_ip_routing.u8_rip_authentification)
						{
							strcpy(s_html_cfg_eqpmt.s_ip_routing.ps8_rip_password, loc_s_results.ps8_password);
						}
						if(TRUE==u8TestConfigRouting(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigRouting(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
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
				PreparePageCfgInProgress("SUConfigRoutingRip");
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
	if( (FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) ||
		(FALSE == u8FillConfigRouting(&s_html_cfg_eqpmt))
	  )
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	//Page accéssible uniquement en mode STATION / router
	if((MODE_RADIO_MODEM_STATION != s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem) ||
	   (MODE_NETWORK_ROUTER != s_html_cfg_eqpmt.s_gene.u8_mode_network)
	  )//CONDITION: STATION / router
	{
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_MODE_ONLY_STATION_ROUTER);
		Html_GotoPage(ps8_pageHtmlRetour);
		return;
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigRoutingRip");	//pour la fonction Actualiser

	JSTextCheck();

	proc_JavaScript_SUConfigRoutingRip();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigRoutingRip");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigRouting);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//ONGLET
	HtmlPrint_OngletRouting(PAGE_HTML_SUCONFIGROUTING__RIP);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_detail_onglet_SUConfigRoutingRip);

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Activation RIPv2
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_rip);
	html_tag("			<td><SELECT name=actRip onchange=\"return(JSChangeActivationRip())\"> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_ip_routing.u8_ripv2_activation) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_ip_routing.u8_ripv2_activation) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Interfaces RIP utilisées
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
	pt_tb_msg[u8_html_langue].ps8_msg_interfaces_utilises_par_rip);
	html_tag("			<td nowrap> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_RIP_INTERFACES;loc_u8_i++)
	{
		html_tag("&nbsp;%s&nbsp;:&nbsp;<input name=\"ifrip%d\" type=\"checkbox\" %s value=\"%s\"><BR> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_interfaces_rip[loc_u8_i],
				 loc_u8_i,
				 (TRUE == s_html_cfg_eqpmt.s_ip_routing.pu8_rip_interface_used[loc_u8_i])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED);
	}
	html_tag("			</td> \n");
	html_tag("		</tr> \n");
	//Authentification
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_authentification);
	html_tag("			<td><SELECT name=authRip onchange=\"return(JSChangeAuthRip())\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_RIP_AUTHENTICATION;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_ip_routing.u8_rip_authentification) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_authentification_rip[loc_u8_i]);
	}
	html_tag("			</select></td> \n");
	html_tag("		</tr> \n");
	//Mode de passe
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mot_passe);
	html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"pwdRip\" value=\"%s\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
			 TAILLE_MAX_RIP_PASSWORD,
			 TAILLE_MAX_RIP_PASSWORD,
			 s_html_cfg_eqpmt.s_ip_routing.ps8_rip_password);
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider_formulaire,
			 FORM_SUCONFIGROUTINGRIP_VALID_ALL);
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigRoutingRip*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingRip
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingRip
//=====================================================================================
void InitModule_SUConfigRoutingRip(void)
{
}/*InitModule_SUConfigRoutingRip*/
