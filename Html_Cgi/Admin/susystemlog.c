/*========================================================================*/
/* NOM DU FICHIER  : susystemlog.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 28/01/2010                                           */
/* Libelle         : HTML CGI: page HTML d'adminsitration - System Log	  */
/* Projet          : WRM100                                               */
/* Indice          : BE059				  								  */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - CREATION
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUSYSTEMLOG

enum LISTE_DES_FORM_SUSYSTEMLOG
{
	FORM_SUSYSTEMLOG_NULL = 0,	//à ne pas utiliser
	FORM_SUSYSTEMLOG_VALID_1,
	NB_MAX_FORM_SUSYSTEMLOG
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_activSyslog			[20 + 1];
	s8sod	ps8_modeRSSI			[20 + 1];
	s8sod	ps8_adrIpSyslog			[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_portSyslog			[20 + 1];
	s8sod	ps8_hidden1				[20 + 1];
} S_CONFIG_ADMSYSTEMLOG_RESULTS;

FIELD_LIST s_ConfigAdmSystemLogFields[] = {
	{"activSyslog",		"%s",		offsetof(S_CONFIG_ADMSYSTEMLOG_RESULTS, ps8_activSyslog)	},
	{"modeRSSI",		"%s",		offsetof(S_CONFIG_ADMSYSTEMLOG_RESULTS, ps8_modeRSSI)	},
	{"adrIpSyslog",		"%s",		offsetof(S_CONFIG_ADMSYSTEMLOG_RESULTS, ps8_adrIpSyslog)	},
	{"portSyslog",		"%s",		offsetof(S_CONFIG_ADMSYSTEMLOG_RESULTS, ps8_portSyslog)	},
	{"hidden1",			"%s",		offsetof(S_CONFIG_ADMSYSTEMLOG_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUAdmSystemLog
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/02/2011
// Description	: code de javascript de la page HTML SUAdmSystemLog
//=====================================================================================
void proc_JavaScript_SUAdmSystemLog(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUAdmSystemLog
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/02/2011
// Description	: code de javascript de la page HTML SUAdmSystemLog
//=====================================================================================
void proc_JavaScript_SUAdmSystemLog(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	html_tag("var val_memo_adrIpSyslog; \n");
	html_tag("var val_memo_portSyslog; \n");
	
	//Fonction javascript : JsChangeActivSyslog
	//*************************************
	html_tag("function JsChangeActivSyslog(form) \n");
	html_tag("{ \n");
	html_tag("	loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("		if(%d == Number(form.modeRSSI.value)) \n",FALSE);
		html_tag("		{ \n");
		html_tag("			loc_result = true; \n");
		html_tag("			JsGriseModes(form); \n");
		html_tag("		} \n");
	}
#endif
	html_tag("	}\n");
	html_tag("	return loc_result;\n");
	html_tag("}\n"); /*JsChangeActivSyslog*/

#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Fonction javascript : JsChangeModeRssi
		//*************************************
		html_tag("function JsChangeModeRssi(form) \n");
		html_tag("{ \n");
		html_tag("	loc_result = false; \n");
		html_tag("	with(document) \n");
		html_tag("	{ \n");
		html_tag("		if(%d == Number(form.activSyslog.value)) \n",FALSE);
		html_tag("		{ \n");
		html_tag("			loc_result = true; \n");
		html_tag("			JsGriseModes(form); \n");
		html_tag("		} \n");
		html_tag("	}\n");
		html_tag("	return loc_result;\n");
		html_tag("}\n"); /*JsChangeModeRssi*/

		//Fonction javascript : JsGriseModes
		//*************************************
		html_tag("function JsGriseModes(form) \n");
		html_tag("{ \n");
		if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		{
			html_tag("		if(%d == Number(form.activSyslog.value)) \n",TRUE);
			html_tag("		{ \n");
			html_tag("			form.modeRSSI.value = %d; \n",FALSE);
			html_tag("			form.modeRSSI.disabled = true; \n"); //on grise le mode RSSI
			html_tag("		} \n");
			html_tag("		else \n");
			html_tag("		{ \n");
			html_tag("			form.modeRSSI.disabled = false; \n"); //on dégrise le mode RSSI
			html_tag("		} \n");
			html_tag("		if(%d == Number(form.modeRSSI.value)) \n",TRUE);
			html_tag("		{ \n");
			html_tag("			form.activSyslog.value = %d; \n",FALSE);
			html_tag("			form.activSyslog.disabled = true; \n"); //on grise l activation syslog
			html_tag("		} \n");
			html_tag("		else \n");
			html_tag("		{ \n");
			html_tag("			form.activSyslog.disabled = false; \n"); //on dégrise le mode RSSI
			html_tag("		} \n");
		}
		html_tag("}\n"); /*JsGriseModes*/
	}
#endif
	
	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript(form)  \n");
	html_tag("{  \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("	val_memo_adrIpSyslog = IPAddressToUnsignedInteger(form.adrIpSyslog.value); \n");
		html_tag("	val_memo_portSyslog = Number(form.portSyslog.value); \n");
		html_tag("	JsGriseModes(form); \n");
	}
#endif
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("}  \n");/*StartJavaScript*/

	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true;\n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(i_numForm)  \n");
	html_tag("		{  \n");
	html_tag("			case %d: \n",
			 FORM_SUSYSTEMLOG_VALID_1);
#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("		if(%d == Number(form.modeRSSI.value)) \n",TRUE);//CONDITION: mode RSSI true
		html_tag("		{ \n");
		html_tag("			if(0 == IPAddressToUnsignedInteger(form.adrIpSyslog.value)) \n"); //CONDITION: adresse IP distant non activée
		html_tag("			{ \n");
		html_tag("				alert (\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_adress_ip_distant_doit_etre_non_nul_en_mode_rssi);
		html_tag("				loc_result = false; \n");
		html_tag("			} \n");
		html_tag("		} \n");
	}
#endif
	html_tag("				break;  \n");
	html_tag("			default:  \n");
	html_tag("				loc_result = true; \n");
	html_tag("				break;	  \n");
	html_tag("		} \n");
	html_tag("		if(true == loc_result) \n");
	html_tag("		{\n");
	html_tag("			form.hidden1.value = i_numForm; \n");
	html_tag("			form.submit(); \n");
	html_tag("		}\n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUAdmSystemLog*/

//=====================================================================================
// Fonction		: SUAdmSystemLog
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 28/01/2010
// Description	: Page HTML Administration: System Log
//=====================================================================================
void SUAdmSystemLog(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_ADMSYSTEMLOG_RESULTS loc_s_results;
	s8sod loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;			/* Init loc */

	loc_u8_result_test = FALSE; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */
	
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUAdmSystemLog");
		return;
	}

	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_ADMSYSTEMLOG_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigAdmSystemLogFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUSYSTEMLOG)
			{
				if(FORM_SUSYSTEMLOG_VALID_1 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if((TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))&&
					   (TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					  )
					{
						s_html_cfg_eqpmt.s_admin.u8_syslog_activation = (u8sod)atoi(loc_s_results.ps8_activSyslog);
#ifdef _WRM100_N_SELECT
						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s_html_cfg_eqpmt.s_admin.u8_mode_RSSI = (u8sod)atoi(loc_s_results.ps8_modeRSSI);
						}
#endif

						s_html_cfg_eqpmt.s_admin.u32_syslog_adresse_IP = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpSyslog, &loc_u8_ret);
						s_html_cfg_eqpmt.s_admin.u16_syslog_port = (u16sod)atoi(loc_s_results.ps8_portSyslog);
						if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
			}

			if(FALSE == loc_u8_result_test)
			{
				sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
						WARNING_CONFIG_KO);
				Html_GotoPage(ps8_pageHtmlRetour);
				return;
			}
		}

				
		//On recharge la page pour re-initialiser les champs "objets" HTML
		Html_GotoPage("/cgi-bin/cgi_fh?URL=SUAdmSystemLog");
		return; // on sort!
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if((FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))||
	   (FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt))||
	   (FALSE == u8FillConfigWifi(&s_html_cfg_eqpmt))
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
	

	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_journal_system);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUAdmSystemLog");	//pour la fonction Actualiser
	proc_JavaScript_SUAdmSystemLog();

	JSIPCheck();
	JSNumCheck();
	
	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmSystemLog");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_journal_system);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUAdmSystemLog);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		switch(s_html_cfg_eqpmt.s_wifi.u8_mode_securite_wifi)
		{
			case MODE_SECURITE_WIFI_AUCUN:
			case MODE_SECURITE_WIFI_WEP:
				html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_attention,
						 pt_tb_msg[u8_html_langue].ps8_msg_mode_rssi_non_fonctionnel_si_wifi_non_secu);
				break;
			case MODE_SECURITE_WIFI_WPA:
			case MODE_SECURITE_WIFI_WPA_TKIP:
			case MODE_SECURITE_WIFI_WPA_AES:
			case MODE_SECURITE_WIFI_WPA2:
			case MODE_SECURITE_WIFI_WPA2_TKIP:
			case MODE_SECURITE_WIFI_WPA2_AES:
				break;
			default:
				break;
		}
	}
#endif
	
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

	//Activation du log
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_journal_system);
	html_tag("			<td><SELECT name=\"activSyslog\" onchange=\"return(JsChangeActivSyslog(form))\">  \n");
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((FALSE == s_html_cfg_eqpmt.s_admin.u8_syslog_activation) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((TRUE == s_html_cfg_eqpmt.s_admin.u8_syslog_activation) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("		</select></td> \n");
	html_tag("		</tr> \n");

#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Activation du mode RSSI
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_activation_mode_rssi);
		html_tag("			<td><SELECT name=\"modeRSSI\" onchange=\"return(JsChangeModeRssi(form))\">  \n");
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((FALSE == s_html_cfg_eqpmt.s_admin.u8_mode_RSSI) ? "selected" : ""),
				 FALSE,
				 pt_tb_msg[u8_html_langue].ps8_msg_non);
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((TRUE == s_html_cfg_eqpmt.s_admin.u8_mode_RSSI) ? "selected" : ""),
				 TRUE,
				 pt_tb_msg[u8_html_langue].ps8_msg_oui);
		html_tag("		</select></td> \n");
		html_tag("		</tr> \n");
	}
#endif
	
	html_tag("<tr><th colspan=2>&nbsp;</th></tr> \n");

	//Adresse Ip du distant
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip_distant_journal_system);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpSyslog\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_admin.u32_syslog_adresse_IP));
	html_tag("		</tr> \n");
	//Port distant
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_port_distant_journal_system);
	html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"portSyslog\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
			 s_html_cfg_eqpmt.s_admin.u16_syslog_port,
			 PORT_UDP_TCP_MIN,
			 PORT_UDP_TCP_MAX);
	html_tag("		</tr> \n");

	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUSYSTEMLOG_VALID_1);
	
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUAdmSystemLog*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SuSystemLog
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de susystemlog
//=====================================================================================
void InitModule_SuSystemLog(void)
{
}/*InitModule_SuSystemLog*/
