/*========================================================================*/
/* NOM DU FICHIER  : suconfigWirelessAdv.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Wireless (Adv)	  */
/* Projet          : WRM100                                               */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE042 07/10/2010 CM
// - Configuration seuil de framentation (adv wifi) non autorisé en 11n
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
//BE053 16/12/2010 CM
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Suppression du fichier de configuration advwf
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGWIRELESSADV

enum LISTE_DES_FORM_SUCONFIGWIRELESSADV
{
	FORM_SUCONFIGWIRELESSADV_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGWIRELESSADV_VALID_1,
	FORM_SUCONFIGWIRELESSADV_VALID_2,
	NB_MAX_FORM_SUCONFIGWIRELESSADV
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_ack_timeout		[10 + 1];
	s8sod	ps8_preambule_type	[10 + 1];
	s8sod	ps8_fragmentation_threshold	[10 + 1];
	s8sod	ps8_rts_cts_threshold	[10 + 1];
	s8sod	ps8_rts_retry_limit	[10 + 1];
	s8sod	ps8_beacon_period	[10 + 1];
	s8sod	ps8_act_wmm			[10 + 1];
	s8sod	ps8_desact_dfs		[10 + 1];
	s8sod	ps8_country_id		[10 + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_WIRELESS_ADV_RESULTS;

FIELD_LIST s_FormConfigWirelessAdvFields[] = {
	{"ackT",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_ack_timeout)		},
	{"preambule",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_preambule_type)	},
	{"fragThrld",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_fragmentation_threshold)	},
	{"rtsctsThrld",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_rts_cts_threshold)	},
	{"rtslimit",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_rts_retry_limit)	},
	{"beacon",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_beacon_period)	},
	{"act_wmm",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_act_wmm)	},
	{"desact_dfs",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_desact_dfs)},
	{"country_id",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_country_id)	},

	{"hidden1",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS, ps8_hidden1)		},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigWirelessAdv
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigWirelessAdv
//=====================================================================================
void proc_JavaScript_SUConfigWirelessAdv(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigWirelessAdv
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigWirelessAdv
//=====================================================================================
void proc_JavaScript_SUConfigWirelessAdv(void)
{
	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript(form)  \n");
	html_tag("{  \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("}  \n");/*StartJavaScript*/

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = false; \n"); //INIT
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(i_numForm)  \n");
	html_tag("		{  \n");
	html_tag("			case %d: \n",FORM_SUCONFIGWIRELESSADV_VALID_2);
	html_tag("				if ( confirm(\"%s\") ) \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_etes_vous_sur_de_configurer_nouveau_code_pays);
	html_tag("				{  \n");
	html_tag("					loc_result = true;  \n");
	html_tag("				}  \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				loc_result = true;	  \n");
	html_tag("				break;	  \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag( "	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigWirelessAdv*/

//=====================================================================================
// Fonction		: SUConfigWirelessAdv
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: Wireless (Adv)
//				"URL=SUConfigWirelessAdv"
//=====================================================================================
void SUConfigWirelessAdv(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_WIRELESS_ADV_RESULTS loc_s_results;
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
		PreparePagePswd("SUConfigWirelessAdv");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigWirelessAdv&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_WIRELESS_ADV_RESULTS));

		// Décodage de la requete
		if (!form_decode(s_FormConfigWirelessAdvFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGWIRELESSADV)
			{
				if(FORM_SUCONFIGWIRELESSADV_VALID_1 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on leve le semaphore
					if(	(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))&&
						(TRUE == u8FillConfigWifi(&s_html_cfg_eqpmt))
					  )
					{
#ifdef _WRM100_ABG_SELECT
						s_html_cfg_eqpmt.s_wifi.u16_protcl_ABG_ACK_timeout = (u16sod)atoi(loc_s_results.ps8_ack_timeout);
#endif
#ifdef _WRM100_N_SELECT
						s_html_cfg_eqpmt.s_wifi.u16_protcl_N_ACK_timeout = (u16sod)atoi(loc_s_results.ps8_ack_timeout);
#endif
						if(MODE_WIFI_802_11B == s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x)
						{
							s_html_cfg_eqpmt.s_wifi.u8_protcl_type_preambule = (u8sod)atoi(loc_s_results.ps8_preambule_type);
						}
						if((TRUE == u8IsMode80211ag(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))||
						   (TRUE == u8IsMode80211b(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))
						  )//CONDITION: valable pour 11a/11g et 11b
						{
							s_html_cfg_eqpmt.s_wifi.u16_protcl_fragment_threshold = (u16sod)atoi(loc_s_results.ps8_fragmentation_threshold);
						}
						s_html_cfg_eqpmt.s_wifi.u16_protcl_RTS_CTS_threshold = (u16sod)atoi(loc_s_results.ps8_rts_cts_threshold);
#if VERSION_WRM100_DEMO
#else
						s_html_cfg_eqpmt.s_wifi.u16_protcl_RTS_retry_limit = (u16sod)atoi(loc_s_results.ps8_rts_retry_limit);
#endif
						if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s_html_cfg_eqpmt.s_wifi.u16_protcl_beacon_period = (u16sod)atoi(loc_s_results.ps8_beacon_period);
						}
#ifdef _WRM100_N_SELECT
						s_html_cfg_eqpmt.s_wifi.u8_activation_WMM = (u8sod)atoi(loc_s_results.ps8_act_wmm);
						s_html_cfg_eqpmt.s_wifi.u8_desactivation_DFS = (u8sod)atoi(loc_s_results.ps8_desact_dfs);
#endif
						if(TRUE==u8TestConfigWifi(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigWifi(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

#ifdef _WRM100_N_SELECT
				if(FORM_SUCONFIGWIRELESSADV_VALID_2 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on leve le semaphore
					if(	(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))&&
						  (TRUE == u8FillConfigWifi(&s_html_cfg_eqpmt))
					  )
					{
						s_html_cfg_eqpmt.s_wifi.u8_countryID = (u8sod)atoi(loc_s_results.ps8_country_id);
						if(TRUE==u8TestConfigWifi(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigWifi(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
#endif
				
				if(FALSE == loc_u8_result_test)
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_CONFIG_KO);
					Html_GotoPage(ps8_pageHtmlRetour);
					return;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				PreparePageCfgInProgress("SUConfigWirelessAdv");
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
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on leve le semaphore
	if(	(FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) ||
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
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_wifi);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
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
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigWirelessAdv");	//pour la fonction Actualiser

	JSNumCheck();

	proc_JavaScript_SUConfigWirelessAdv();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigWirelessAdv");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_wifi);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigWireless);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Onglet
	html_tag("<tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n"
			 "			<tr> \n"
			 "				<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=SUConfigWirelessBasic\" target=\"frame_c\">%s</a></li></ul></td> \n"
			 "				<td>&nbsp;&nbsp;</td> \n"
			 "				<td><ul><li><B>%s</B></li></ul></td> \n"
			 "			</tr> \n"
			 "</table></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_basique_wifi,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_avance_wifi);
	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	if(FALSE == s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].u8_presence) //CONDITION: interface WLAN présent
	{
		html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_attention,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_interface_non_detecte[INTERFACE_WLAN]);
	}

	if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	  )
	{
		html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"200\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"250\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
		html_tag("		</tr> \n");
		//ACK timeout
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_timeout_ACK);
#ifdef _WRM100_ABG_SELECT
		html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"ackT\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;µs</td> \n",
				 s_html_cfg_eqpmt.s_wifi.u16_protcl_ABG_ACK_timeout,
				 WF_ABG_ACK_TIMEOUT_MIN,
				 WF_ABG_ACK_TIMEOUT_MAX);
#endif
#ifdef _WRM100_N_SELECT
		if(TRUE == u8IsMode80211nHT40(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))
		{
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"ackT\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;µs</td> \n",
					 s_html_cfg_eqpmt.s_wifi.u16_protcl_N_ACK_timeout,
					 WF_N_ACK_TIMEOUT_MIN,
					 WF_N_ACK_TIMEOUT_11NHT40_MAX);
		}
		else
		{
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"ackT\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;µs</td> \n",
					 s_html_cfg_eqpmt.s_wifi.u16_protcl_N_ACK_timeout,
					 WF_N_ACK_TIMEOUT_MIN,
					 WF_N_ACK_TIMEOUT_11OTHER_MAX);
		}
#endif
		html_tag("		</tr> \n");
		if(MODE_WIFI_802_11B == s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x)
		{
			//Type de preabule
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_type_preambule);
			html_tag("			<td><SELECT name=\"preambule\" size=\"1\" > \n");
			for(loc_u8_i=0;loc_u8_i<NB_MAX_WF_TYPE_PREAMBULE;loc_u8_i++)
			{
				html_tag("		   <option %s value=\"%d\">%s</option>	\n",
						 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_protcl_type_preambule) ? "selected" : ""),
						 loc_u8_i,
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_type_preambule[loc_u8_i]);
			}
			html_tag("				  </select></td> \n");
			html_tag("		</tr> \n");
		}
		if((TRUE == u8IsMode80211ag(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))||
		   (TRUE == u8IsMode80211b(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))
		  )//CONDITION: valable pour 11a/11g et 11b
		{
			//Seuil de fragmentation
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_seuil_fragmentation);
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"fragThrld\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;%s</td> \n",
					 s_html_cfg_eqpmt.s_wifi.u16_protcl_fragment_threshold,
					 WF_FRAGMENT_THRESHOLD_MIN,
					 WF_FRAGMENT_THRESHOLD_MAX,
					 pt_tb_msg[u8_html_langue].ps8_msg_octets);
			html_tag("		</tr> \n");
		}
		//Seuil RTS/CTS
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_seuil_RTS_CTS);
		html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"rtsctsThrld\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;%s</td> \n",
				 s_html_cfg_eqpmt.s_wifi.u16_protcl_RTS_CTS_threshold,
				 WF_RTS_CTS_THRESHOLD_MIN,
				 WF_RTS_CTS_THRESHOLD_MAX,
				 pt_tb_msg[u8_html_langue].ps8_msg_octets);
		html_tag("		</tr> \n");
#if VERSION_WRM100_DEMO
#else
		//RTS retry limit
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_limitation_retransmission_RTS);
		html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"rtslimit\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
				 s_html_cfg_eqpmt.s_wifi.u16_protcl_RTS_retry_limit,
				 WF_RTS_RETRY_LIMIT_MIN,
				 WF_RTS_RETRY_LIMIT_MAX);
		html_tag("		</tr> \n");
#endif

		if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		{
			//Beacon period
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_periode_beacon);
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"beacon\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;ms</td> \n",
					 s_html_cfg_eqpmt.s_wifi.u16_protcl_beacon_period,
					 WF_BEACON_PERIOD_MIN,
					 WF_BEACON_PERIOD_MAX);
			html_tag("		</tr> \n");
		}

#ifdef _WRM100_N_SELECT
		//Activation WMM
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_activation_wmm);
		html_tag("			<td><SELECT name=act_wmm> \n");
		html_tag("			<option %s value=\"%d\">%s</option> \n",
				 ((FALSE == s_html_cfg_eqpmt.s_wifi.u8_activation_WMM) ? "selected" : ""),
				 FALSE,
				 pt_tb_msg[u8_html_langue].ps8_msg_non);
		html_tag("			<option %s value=\"%d\">%s</option> \n",
				 ((TRUE == s_html_cfg_eqpmt.s_wifi.u8_activation_WMM) ? "selected" : ""),
				 TRUE,
				 pt_tb_msg[u8_html_langue].ps8_msg_oui);
		html_tag("				  </select></td> \n");
		html_tag("		</tr> \n");

		//Désactivation DFS
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_desactivation_DFS);
		html_tag("			<td><SELECT name=desact_dfs> \n");
		html_tag("			<option %s value=\"%d\">%s</option> \n",
				 ((FALSE == s_html_cfg_eqpmt.s_wifi.u8_desactivation_DFS) ? "selected" : ""),
				 FALSE,
				 pt_tb_msg[u8_html_langue].ps8_msg_non);
		html_tag("			<option %s value=\"%d\">%s</option> \n",
				 ((TRUE == s_html_cfg_eqpmt.s_wifi.u8_desactivation_DFS) ? "selected" : ""),
				 TRUE,
				 pt_tb_msg[u8_html_langue].ps8_msg_oui);
		html_tag("				  </select></td> \n");
		html_tag("		</tr> \n");
#endif
	
		html_tag("</table></td></tr> \n");
		html_tag("<tr><td>&nbsp;</td></tr> \n");

		html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valider,
				 FORM_SUCONFIGWIRELESSADV_VALID_1);
	}


#ifdef _WRM100_N_SELECT
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<tr><td><P class=warning>%s</td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_avertissement_modification_code_pays);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Country ID
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_code_pays);
	html_tag("			<td><SELECT name=\"country_id\" size=\"1\" > \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_COUNTRY_ID;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_countryID) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_country_id[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGWIRELESSADV_VALID_2);
#endif
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigWirelessAdv*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigWirelessAdv
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigWirelessAdv
//=====================================================================================
void InitModule_SUConfigWirelessAdv(void)
{
}/*InitModule_SUConfigWirelessAdv*/
