/*========================================================================*/
/* NOM DU FICHIER  : suconfigDhcp.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 15/01/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - DHCP server/relay*/
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE005 15/01/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE020 23/03/2010 CM
// - Correction erreur javascript dans page HTML Configuration - DHCP
// - Correction w@rning dans FireFox "Element referencé par son ID/NAME ..."
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGDHCP

enum LISTE_DES_FORM_SUCONFIGDHCP
{
	FORM_SUCONFIGDHCP_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGDHCP_VALID_1,
	FORM_SUCONFIGDHCP_VALID_2,
	FORM_SUCONFIGDHCP_VALID_3,
	NB_MAX_FORM_SUCONFIGDHCP
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_fct_dhcp		[10 + 1];

	s8sod	ps8_adrIpStart		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_adrIpStop		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_leasetime		[10 + 1];
	
	s8sod	ps8_adrIpRelai		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_DHCP_RESULTS;

FIELD_LIST s_FormConfigDhcpFields[] = {
	{"fctDhcp",				"%s",	offsetof(S_FORM_CONFIG_DHCP_RESULTS, ps8_fct_dhcp)		},
	{"adrIpStart",			"%s",	offsetof(S_FORM_CONFIG_DHCP_RESULTS, ps8_adrIpStart)		},
	{"adrIpStop",			"%s",	offsetof(S_FORM_CONFIG_DHCP_RESULTS, ps8_adrIpStop)		},
	{"leasetime",			"%s",	offsetof(S_FORM_CONFIG_DHCP_RESULTS, ps8_leasetime)		},

	{"adrIpRelai",			"%s",	offsetof(S_FORM_CONFIG_DHCP_RESULTS, ps8_adrIpRelai)	},
	
	{"hidden1",		"%s",		offsetof(S_FORM_CONFIG_DHCP_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigDhcp
// Entrees		: <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: rien
// Auteur		: CM - 15/01/2010
// Description	: code de javascript de la page HTML SUConfigDhcp
//=====================================================================================
void proc_JavaScript_SUConfigDhcp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigDhcp
// Entrees		: <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: rien
// Auteur		: CM - 15/01/2010
// Description	: code de javascript de la page HTML SUConfigDhcp
//=====================================================================================
void proc_JavaScript_SUConfigDhcp(S_STRUCT_CONFIGURATION *loc_ps_config)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : JsChangeFctDHCP
	//*************************************
	html_tag("function JsChangeFctDHCP(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_dhcp_server;\n");
	html_tag("	var loc_dhcp_relay; \n");
	html_tag("	var loc_dhcp_none; \n");
	html_tag("	loc_dhcp_server = false; \n"); //init
	html_tag("	loc_dhcp_relay = false; \n"); //init
	html_tag("	loc_dhcp_none = false; \n"); //init
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.fctDhcp.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",FCT_DHCP_NONE);
	html_tag("				loc_dhcp_none = true;\n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",FCT_DHCP_SERVER);
	html_tag("				loc_dhcp_server = true;\n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",FCT_DHCP_RELAY);
	html_tag("				loc_dhcp_relay = true;\n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	}\n");
	html_tag("	var elmt = document.getElementsByTagName(\"TR\"); \n");
	html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++) \n");
	html_tag("	{\n");
	html_tag("		if(\"TR_DHCP_NONE\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_dhcp_none)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if(\"TR_DHCP_SERVER\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_dhcp_server)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if(\"TR_DHCP_RELAY\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_dhcp_relay)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("	}\n");
	html_tag("	return true;\n");
	html_tag("}\n"); /*JsChangeFctDHCP*/

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{\n");
	html_tag("	with(document)\n");
	html_tag("	{\n");
	html_tag("		JsChangeFctDHCP(form); \n");
	html_tag("	}\n");
	html_tag("} \n");

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = false; \n"); //INIT
	html_tag("		with(document) \n");
	html_tag("		{  \n");
	html_tag("			switch(i_numForm)  \n");
	html_tag("			{  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGDHCP_VALID_2);
	html_tag("					loc_result = true;  \n");
	html_tag("					var loc_lan_ip = \"%s\";  \n",
			 ps8GetStringIp(loc_ps_config->s_gene.u32_lan_adresse_ip));
	html_tag("					var loc_lan_mask_net = \"%s\";  \n",
			 ps8GetStringIp(loc_ps_config->s_gene.u32_lan_masque_reseau));
	html_tag("					var ip_address_from = IPAddressToUnsignedInteger(form.adrIpStart.value); \n");
	html_tag("					var ip_address_to = IPAddressToUnsignedInteger(form.adrIpStop.value); \n");
	html_tag("					var network_address = IPAddressToUnsignedInteger(loc_lan_ip); \n");
	html_tag("					var subnet_mask = IPAddressToUnsignedInteger(loc_lan_mask_net); \n");
	html_tag("					var host_mask = (~subnet_mask) & 0xffffffff; \n");
	html_tag("					var subnet = network_address & subnet_mask; \n");
	html_tag("					if ((ip_address_from & subnet_mask) != subnet) { \n"
			 "						alert(\"%s\"); \n"
			 "						return false; \n"
			 "					} \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_js_adresse_dhcp_FROM_pas_dans_LAN);
	html_tag("					if ((ip_address_to & subnet_mask) != subnet) { \n"
			 "						alert(\"%s\"); \n"
			 "						return false; \n"
			 "					} \n",
			pt_tb_msg[u8_html_langue].ps8_msg_js_adresse_dhcp_TO_pas_dans_LAN);
	html_tag("					if ((ip_address_from & host_mask) == 0) { \n"
			 "						alert(\"%s\"); \n"
			 "						return false; \n"
			 "					} \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_js_adresse_dhcp_FROM_invalid);
	html_tag("					if (ip_address_from > ip_address_to) { \n"
			 "						alert(\"%s\"); \n"
			 "						return false; \n"
			 "					} \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_js_plage_adresse_dhcp_FROM_TO_invalid);
	html_tag("					if (((ip_address_from & host_mask) == host_mask) || ((ip_address_to & host_mask) == host_mask)) { \n"
			 "						alert(\"%s\"); \n"
			 "						return false; \n"
			 "					} \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_js_plage_adresse_dhcp_broadcast_invalid);
	html_tag("					if ((ip_address_to - ip_address_from) > %d) { \n"
			 "						alert(\"%s\"); \n"
			 "						return false; \n"
			 "					} \n",
			 NB_MAX_CLIENTS_DHCP,
			 pt_tb_msg[u8_html_langue].ps8_msg_js_plage_adresse_dhcp_exceed_limit_max);
	html_tag("					break;  \n");
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

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigDhcp*/

//=====================================================================================
// Fonction		: SUConfigDhcp
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/01/2010
// Description	: Page HTML Configuration: DHCP
//				"URL=SUConfigDhcp"
//=====================================================================================
void SUConfigDhcp(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_DHCP_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_i;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigDhcp");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigDhcp&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_DHCP_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigDhcpFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGDHCP)
			{
				if(FORM_SUCONFIGDHCP_VALID_1 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_gene.u8_lan_fonction_dhcp = (u8sod)atoi(loc_s_results.ps8_fct_dhcp);
						if(TRUE==u8TestConfigGeneral(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigGeneral(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGDHCP_VALID_2 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_gene.u8_lan_fonction_dhcp = (u8sod)atoi(loc_s_results.ps8_fct_dhcp);
						s_html_cfg_eqpmt.s_gene.u32_lan_dhcpsrv_ip_min = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpStart, &loc_u8_ret);
						s_html_cfg_eqpmt.s_gene.u32_lan_dhcpsrv_ip_max = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpStop, &loc_u8_ret);
						s_html_cfg_eqpmt.s_gene.u32_lan_dhcpsrv_duree_vie_bail = (u32sod)atoi(loc_s_results.ps8_leasetime);
						if(TRUE==u8TestConfigGeneral(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigGeneral(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGDHCP_VALID_3 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_gene.u8_lan_fonction_dhcp = (u8sod)atoi(loc_s_results.ps8_fct_dhcp);
						s_html_cfg_eqpmt.s_gene.u32_lan_dhcprelay_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpRelai, &loc_u8_ret);
						if(TRUE==u8TestConfigGeneral(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigGeneral(&s_html_cfg_eqpmt))
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
				PreparePageCfgInProgress("SUConfigDhcp");
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
			 pt_tb_msg[u8_html_langue].ps8_msg_serveur_relai_dhcp);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("	tr.TR_DHCP_NONE {\n"
			 "}\n");
	html_tag("	tr.TR_DHCP_SERVER {\n"
			 "}\n");
	html_tag("	tr.TR_DHCP_RELAY {\n"
			 "}\n");
	html_tag("</STYLE>\n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigDhcp");	//pour la fonction Actualiser

	JSNumCheck();
	JSIPCheck();

	proc_JavaScript_SUConfigDhcp(&s_html_cfg_eqpmt);

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigDhcp");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_serveur_relai_dhcp);
	html_tag("<tr><td><P>%s<BR>%s<BR>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigDHCP,
			 pt_tb_msg[u8_html_langue].ps8_msg_info_sur_dhcp_serveur,
			 pt_tb_msg[u8_html_langue].ps8_msg_info_sur_dhcp_relai);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	if(FALSE == s_html_exploit.s_general.ps_interface[INTERFACE_LAN].u8_presence) //CONDITION: interface LAN présent
	{
		html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_attention,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_interface_non_detecte[INTERFACE_LAN]);
	}
	if(FALSE == s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].u8_presence) //CONDITION: interface WLAN présent
	{
		html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_attention,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_interface_non_detecte[INTERFACE_WLAN]);
	}
	if((MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)&&
	   (MODE_NETWORK_ROUTER == s_html_cfg_eqpmt.s_gene.u8_mode_network)
	  )
	{
		if(FALSE == u8TestFctDHCP_Fonctionnelle(&s_html_cfg_eqpmt)) //CONDITION: configuration DHCP valide
		{
			switch(s_html_cfg_eqpmt.s_gene.u8_lan_fonction_dhcp)
			{
				case FCT_DHCP_NONE:
					break;
				case FCT_DHCP_SERVER:
					html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_attention,
							 pt_tb_msg[u8_html_langue].ps8_msg_configuration_serveur_DHCP_non_fonctionnel);
					break;
				case FCT_DHCP_RELAY:
					html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_attention,
							 pt_tb_msg[u8_html_langue].ps8_msg_configuration_relai_DHCP_non_fonctionnel);
					break;
				default:
					break;
			}
		}
	}

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Fonction DHCP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_fonction_dhcp);
	html_tag("			<td><SELECT name=\"fctDhcp\" size=\"1\" onchange=\"return(JsChangeFctDHCP(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_FCT_DHCP;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_gene.u8_lan_fonction_dhcp) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_fct_dhcp[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_NONE\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGDHCP_VALID_1);

	//Paramètres serveur DHCP
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_SERVER\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_serveur_dhcp);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_SERVER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_SERVER\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Plage d'adresses IP DHCP
	html_tag("		<tr> \n");
	html_tag("			<td nowrap>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_plage_adresse_ip_dhcp);
	html_tag("			<td nowrap>&nbsp; %s &nbsp;<input type=\"text\" size=\"15\" name=\"adrIpStart\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\">&nbsp;%s&nbsp;",
			 pt_tb_msg[u8_html_langue].ps8_msg_from,
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_lan_dhcpsrv_ip_min),
			 pt_tb_msg[u8_html_langue].ps8_msg_to);
	html_tag("				<input type=\"text\" size=\"15\" name=\"adrIpStop\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\">&nbsp;(%s) \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_lan_dhcpsrv_ip_max),
			 pt_tb_msg[u8_html_langue].ps8_msg_adresses_dans_sous_reseau_lan);
	html_tag("			</td> \n");
	html_tag("		</tr> \n");
	//Durée du bail DHCP
	html_tag("		<tr> \n");
	html_tag("			<td nowrap>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_duree_bail_dhcp);
	html_tag("			<td><input type=\"text\" size=\"6\" maxlength=6 name=\"leasetime\" value=%lu onchange=\"return(isInteger(this,%d,%d))\">&nbsp;%s</td> \n",
			 s_html_cfg_eqpmt.s_gene.u32_lan_dhcpsrv_duree_vie_bail,
			 DHCP_DUREE_VIE_BAIL_MIN,
			 DHCP_DUREE_VIE_BAIL_MAX,
			 pt_tb_msg[u8_html_langue].ps8_msg_minutes);
	html_tag("		</tr> \n");
	
	html_tag("</table></td></tr> \n");


	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_SERVER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_SERVER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_SERVER\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGDHCP_VALID_2);
	

	//Paramètres du relai DHCP
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_RELAY\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_relai_dhcp);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_RELAY\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_RELAY\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Adresse IP cible du relai DHCP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_dhcp_relai_ip_cible);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpRelai\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_lan_dhcprelay_ip));
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_RELAY\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_RELAY\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_DHCP_RELAY\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGDHCP_VALID_3);
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigDhcp*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigDhcp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/01/2010
// Description	: Initialisation du module de SUConfigDhcp
//=====================================================================================
void InitModule_SUConfigDhcp(void)
{
}/*InitModule_SUConfigDhcp*/
