/*========================================================================*/
/* NOM DU FICHIER  : vdebug.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 04/07/2007                                           */
/* Libelle         : HTML CGI: pages HTML de debug						  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE010 03/02/2010 CM
// - Correction problème accès au serveur HTTP (dernière un serveur NAT, avec port forwarding)
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE051 13/12/2010 CM
// - Ajout debug pour désactiver watchdog_wifi
//BE055 17/01/2011 CM
// - Ajout configuration Country ID pour le client
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VDEBUG

//Liste des différents formulaires
enum LISTE_DES_FORM_VDEBUG
{
	FORM_VDEBUG_NULL = 0,
	FORM_VDEBUG_VALID_1,
	FORM_VDEBUG_SAVE_CONFIG_DEBUG,
	FORM_VDEBUG_DELETE_CONFIG_DEBUG,
	NB_MAX_FORM_VDEBUG
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_syslogd_level		[10 + 1];
	s8sod	ps8_klogd_level			[10 + 1];
	s8sod	ps8_dbg_hostapd			[10 + 1];
	s8sod	ps8_dbg_wpa_supplicant	[10 + 1];
	s8sod	ps8_dbg_iptables		[10 + 1];
	s8sod	ps8_dbg_stop_watchdog_wifi	[10 + 1];
	s8sod	ps8_dbg_country_id	[10 + 1];
	s8sod	ps8_hidden1				[10 + 1];
} S_FORM_VDEBUG_RESULTS;

FIELD_LIST s_FormVDebugFields[] = {
	{"syslogd_level",		"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_syslogd_level)	},
	{"klogd_level",			"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_klogd_level)		},
	{"dbg_hostapd",			"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_dbg_hostapd)		},
	{"dbg_wpa_supplicant",	"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_dbg_wpa_supplicant)		},
	{"dbg_iptables",		"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_dbg_iptables)	},
	{"stop_watchdog_wifi",	"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_dbg_stop_watchdog_wifi)},
	{"dbg_country_id",	"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_dbg_country_id)},
	{"hidden1",				"%s",		offsetof(S_FORM_VDEBUG_RESULTS,ps8_hidden1)		},
	{NULL	}
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_VDebugConfiguration
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 28/01/2010
// Description	: java script pour 
//=====================================================================================
void proc_JavaScript_VDebugConfiguration(void);

//=====================================================================================
// Fonction		: VdbgSodielec
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 04/07/2007
// Description	: Page HTML: debug
//=====================================================================================
void VdbgSodielec(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	FILE	*loc_p_handle;

	loc_p_handle = NULL; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */
	
	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
		||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VdbgSodielec");
		return;  
	}

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(TRUE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	
	html_tag("<HTML>\n");	
	
	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: Principale</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");
	
	JSActualiser("/cgi-bin/cgi_fh?URL=VdbgSodielec");	//pour la fonction Actualiser

	html_tag("<body> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Debug: Principale</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page affiche des liens pour accéder aux pages de debug.<BR> \n");
	html_tag("<BR> \n");
#ifdef _WRM100_ABG_SELECT
	html_tag("<B>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PROJET: WRM100-ABG</B><BR> \n");
#endif
#ifdef _WRM100_N_SELECT
	html_tag("<B>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;PROJET: WRM100-N</B><BR> \n");
#endif
	html_tag("<BR>&nbsp;&nbsp;<B>VERSION_BE:</B> %s &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; \n",VERSION_BE);
	switch(s_html_exploit.s_general.s_version[VERSION_LOGICIELLE_APPLI_CPU].u8_info_suppl)
	{
		case INFO_VERSION_PROG_NUMERO_1:
			html_tag("<B> PROGRAMME APP n°1</B><BR> \n");
			break;
		case INFO_VERSION_PROG_NUMERO_2:
			html_tag("<B> PROGRAMME APP n°2</B><BR> \n");
			break;
		default:
			html_tag("<B> PROGRAMME APP n°?</B><BR> \n");
			break;
	}
	html_tag("&nbsp;&nbsp;<B>VERSION_BOOT:</B> %s<BR> \n",s_html_exploit.s_general.ps8_version_be_uboot);
#if VERSION_WRM100_DEMO
	html_tag("<BR>\n");
	html_tag("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<B>$$$$ VERSION DEMO $$$$</B>\n");
#endif

	html_tag("</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Affichage si fichier madwifi.on présent 
	if(NULL != (loc_p_handle = fopen( FILE_DEBUG_MADWIFI_ON, "r" ))) //CONDITION: fichier présent
	{
		html_tag("<tr><td>&nbsp;<P class=warning>DRIVER MADWIFI LOADED !</P></td></tr> \n");

		fclose (loc_p_handle);
	}
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VDebugConfiguration\" target=\"frame_c\">Configuration</a></li></ul></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VDebugInformations\" target=\"frame_c\">Informations</a></li></ul></td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VDebugMsgDebug\" target=\"frame_c\">Messages debug</a></li></ul></td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VDebugSizeOf\" target=\"frame_c\">Debug sizeof</a></li></ul></td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VDebugSystemEvent\" target=\"frame_c\">SYSTEM EVENT</a></li></ul></td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VTestFinal\" target=\"frame_c\">Test Final Production</a></li></ul></td></tr> \n");
	

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
}/*VdbgSodielec*/


//=====================================================================================
// Fonction		: proc_JavaScript_VDebugConfiguration
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 28/01/2010
// Description	: java script pour 
//=====================================================================================
void proc_JavaScript_VDebugConfiguration(void)
{
	html_tag("<SCRIPT language=JavaScript> \n");	//Pour la fonction Actualiser


	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{ \n"
			 "		form.hidden1.value = i_numForm;\n"
			 "		form.submit();\n"
			 "} \n");	

	html_tag("</SCRIPT> \n");
}/*proc_JavaScript_VDebugConfiguration*/

//=====================================================================================
// Fonction		: VDebugConfiguration
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: CM - 28/01/2010
// Description	: Page HTML: DEBUG - CONFIGURATION
//=====================================================================================
void VDebugConfiguration(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod					loc_s32_sem;
	s8sod					loc_ps8_emsg[50];
	u32sod					loc_u32_NumeroForm;
	S_FORM_VDEBUG_RESULTS	loc_s_results;
	u8sod		loc_u8_i;
	FILE	*loc_p_handle;

	loc_p_handle = NULL; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=VDebugConfiguration&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_VDEBUG_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormVDebugFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			loc_u32_NumeroForm = (u32sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u32_NumeroForm < NB_MAX_FORM_VDEBUG)
			{
				switch(loc_u32_NumeroForm)
				{
					case FORM_VDEBUG_VALID_1:
						s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillDebugFile(&s_html_debug_global))
						{
							s_html_debug_global.u8_syslogd_level = (u8sod)atoi(loc_s_results.ps8_syslogd_level);
							s_html_debug_global.u8_klogd_level = (u8sod)atoi(loc_s_results.ps8_klogd_level);

							s_html_debug_global.u8_dbg_hostapd = (u8sod)atoi(loc_s_results.ps8_dbg_hostapd);
							s_html_debug_global.u8_dbg_wpa_supplicant = (u8sod)atoi(loc_s_results.ps8_dbg_wpa_supplicant);
							s_html_debug_global.u8_dbg_iptables = (u8sod)atoi(loc_s_results.ps8_dbg_iptables);
							s_html_debug_global.u8_dbg_stop_watchdog_wifi = (u8sod)atoi(loc_s_results.ps8_dbg_stop_watchdog_wifi);
							s_html_debug_global.u8_dbg_countryID = (u8sod)atoi(loc_s_results.ps8_dbg_country_id);

							u8EditDebugFile(&s_html_debug_global);
						}
						s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem
						break;
					case FORM_VDEBUG_SAVE_CONFIG_DEBUG:
						//On vient sauvé le fichier de configuration (debug.ini) dans la FLASH (si il existe!)
						CmdSystem_Generique("cp %s %s",	FICHIER_BDD__DEBUG_INI, FICHIER_MNT_FLASH_CONFIG__DEBUG_SAV);
						break;
					case FORM_VDEBUG_DELETE_CONFIG_DEBUG:
						//On vient supprimé le fichier de configuration (debug.ini) dans la FLASH (si il existe!)
						CmdSystem_Generique("rm %s", FICHIER_MNT_FLASH_CONFIG__DEBUG_SAV);
						break;
					default:
						break;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				Html_GotoPage("/cgi-bin/cgi_fh?URL=VDebugConfiguration");
				return; // on sort!
			}
			else//CONDITION: page KO
			{
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return;
			}
		}
	}




	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
			||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VDebugConfiguration");
		return;  
	}

	s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillDebugFile(&s_html_debug_global))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: VDebugConfiguration</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VDebugConfiguration");	//pour la fonction Actualiser
	proc_JavaScript_VDebugConfiguration();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","VDebugConfiguration");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");


	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Debug: CONFIGURATION</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page permet de paramétrer le debug sur l'équipement.</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VdbgSodielec\" target=\"frame_c\">Retours à la page Debug: Principale</a></li></ul></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Affichage si fichier debug.sav présent dans la FLASH
	if(NULL != (loc_p_handle = fopen( FICHIER_MNT_FLASH_CONFIG__DEBUG_SAV, "rt" ))) //CONDITION: fichier présent
	{
		html_tag("<tr><td>&nbsp;<P class=warning>FICHIER DEBUG (FLASH) PRESENT!</P></td></tr> \n");
		
		fclose (loc_p_handle);
	}
		

	html_tag("<tr><td><P class=undermenu>DEBUG SYSTEM LOG</P></td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Niveau de syslogd
	html_tag("		<tr> \n");
	html_tag("			<td>Niveau de <B>syslogd</B></td> \n");
	html_tag("			<td><SELECT name=\"syslogd_level\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((LOGLEVEL_DBG_DISABLED == s_html_debug_global.u8_syslogd_level) ? "selected" : ""),
			 LOGLEVEL_DBG_DISABLED,
			 "Niveau par défaut");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_LOGLEVEL;loc_u8_i++)
	{
		html_tag("				<option %s value=\"%d\">Niveau %d</option> \n",
				 ((loc_u8_i == s_html_debug_global.u8_syslogd_level) ? "selected" : ""),
				 loc_u8_i,
				 loc_u8_i);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	//Niveau de klogd
	html_tag("		<tr> \n");
	html_tag("			<td>Niveau de <B>klogd</B></td> \n");
	html_tag("			<td><SELECT name=\"klogd_level\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((LOGLEVEL_DBG_DISABLED == s_html_debug_global.u8_klogd_level) ? "selected" : ""),
			 LOGLEVEL_DBG_DISABLED,
			 "Niveau par défaut");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_LOGLEVEL;loc_u8_i++)
	{
		html_tag("				<option %s value=\"%d\">Niveau %d</option> \n",
				 ((loc_u8_i == s_html_debug_global.u8_klogd_level) ? "selected" : ""),
				 loc_u8_i,
				 loc_u8_i);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");

	html_tag("<tr><th colspan=2>&nbsp;</th></tr> \n");

	//Activation debug hostapd
	html_tag("		<tr> \n");
	html_tag("			<td>Activation debug <B>hostapd</B></td> \n");
	html_tag("			<td><SELECT name=\"dbg_hostapd\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_debug_global.u8_dbg_hostapd) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_debug_global.u8_dbg_hostapd) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");

	html_tag("<tr><th colspan=2>&nbsp;</th></tr> \n");

	//Activation debug wpa_supplicant
	html_tag("		<tr> \n");
	html_tag("			<td>Activation debug <B>wpa_supplicant</B></td> \n");
	html_tag("			<td><SELECT name=\"dbg_wpa_supplicant\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_debug_global.u8_dbg_wpa_supplicant) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_debug_global.u8_dbg_wpa_supplicant) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");

	html_tag("<tr><th colspan=2>&nbsp;</th></tr> \n");
	
	//Activation debug iptables
	html_tag("		<tr> \n");
	html_tag("			<td>Activation debug <B>iptables</B></td> \n");
	html_tag("			<td><SELECT name=\"dbg_iptables\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_debug_global.u8_dbg_iptables) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_debug_global.u8_dbg_iptables) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	
	html_tag("<tr><th colspan=2>&nbsp;</th></tr> \n");

	//Activation debug watchdog_wifi
	html_tag("		<tr> \n");
	html_tag("			<td>Activation STOP <B>Watchdog Wifi</B></td> \n");
	html_tag("			<td><SELECT name=\"stop_watchdog_wifi\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_debug_global.u8_dbg_stop_watchdog_wifi) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_debug_global.u8_dbg_stop_watchdog_wifi) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");


	html_tag("<tr><th colspan=2>&nbsp;</th></tr> \n");
	
	//Activation debug country_id
	html_tag("		<tr> \n");
	html_tag("			<td>Activation debug <B>COUNTRY ID</B></td> \n");
	html_tag("			<td><SELECT name=\"dbg_country_id\" size=\"1\" > \n");
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_debug_global.u8_dbg_countryID) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("				<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_debug_global.u8_dbg_countryID) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	
	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_VDEBUG_VALID_1);

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr nowrap><td> \n");
	html_tag("&nbsp;<input type=\"button\" value=\"  SAUVER DEBUG (FLASH)  \" onclick=\"return SelectFormulaire(%d,form);\"> \n",
			 FORM_VDEBUG_SAVE_CONFIG_DEBUG);
	html_tag("&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"  SUPPRIMER DEBUG (FLASH)   \" onclick=\"return SelectFormulaire(%d,form);\"> \n",
			 FORM_VDEBUG_DELETE_CONFIG_DEBUG);
	html_tag("</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("</form> \n");
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");


}/*VDebugConfiguration*/

//=====================================================================================
// Fonction		: VDebugInformations
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 06/05/2008
// Description	: Page HTML: debug d'informations diverses
//=====================================================================================
void VDebugInformations(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
//	u16sod loc_u6_i;
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
		||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VDebugInformations");
		return;  
	}


	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: VDebugInformations</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VDebugInformations");	//pour la fonction Actualiser

	html_tag("<body> \n");

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","VDebugInformations");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");
	
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Debug: Informations</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page permet d'afficher des informations de debug.</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VdbgSodielec\" target=\"frame_c\">Retours à la page Debug: Principale</a></li></ul></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
//	for(loc_u6_i=0; loc_u6_i<10000; loc_u6_i++)
//	{
//		html_tag("<div>0123456789012345678901234567890123456789012345678901234567890123456789012 Line nr: %03d</div>\n",loc_u6_i);    //100 bytes per line
//	}
	
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
}/*VDebugInformations*/

//=====================================================================================
// Fonction		: VDebugMsgDebug
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 10/07/2007
// Description	: Page HTML: debug
//=====================================================================================
void VDebugMsgDebug(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	FILE	*loc_p_handle;
	u16sod	loc_u16_cpt;
	s32sod	loc_s32_sem;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_MESSAGE_DEBUG+1];

	
	loc_p_handle = NULL; //INIT
	loc_u16_cpt = 0; //INIT
	loc_ps8_result_fgets = NULL;  //INIT
	strcpy(loc_ps8_ligne, ""); //INIT


	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
		||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VDebugMsgDebug");
		return;  
	}


	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: VDebugMsgDebug</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VDebugMsgDebug");	//pour la fonction Actualiser

	html_tag("<body> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Debug: Messages de debug</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page permet de consulter les messages de debug.</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VdbgSodielec\" target=\"frame_c\">Retours à la page Debug: Principale</a></li></ul></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	s32Lock_Get(SEMAPHORE_BDD_DEBUGLOG, &loc_s32_sem);	//on lève le sem
	html_tag("<tr><td><pre> \n");
	if(NULL == (loc_p_handle = fopen( FILE_ACTIA_DEBUG, "r" )))
	{
		html_tag("<B>Fichier %s non présent!</B> \n",FILE_ACTIA_DEBUG);
	}
	else
	{
		html_tag("<B>Début Lecture fichier  %s :</B> \n",FILE_ACTIA_DEBUG);

		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_PROCNETROUTE,loc_p_handle);
			if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue
			{
				html_tag("%s",loc_ps8_ligne);
			}

			loc_u16_cpt ++;


		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < 1000));

		fclose (loc_p_handle);
	}
	html_tag("</pre></td></tr> \n");
	s32Lock_Release(SEMAPHORE_BDD_DEBUGLOG, &loc_s32_sem);	//on relache le sem

	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
}/*VDebugMsgDebug*/


//=====================================================================================
// Fonction		: VDebugSizeOf
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 06/05/2008
// Description	: Page HTML: debug sizeof bdd
//=====================================================================================
void VDebugSizeOf(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{

	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
			||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VDebugClientsHttp");
		return;  
	}


	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: VDebugSizeOf</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VDebugClientsHttp");	//pour la fonction Actualiser

	html_tag("<body> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Debug: Sizeof</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page permet de consulter les sizeof de la base de données.</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VdbgSodielec\" target=\"frame_c\">Retours à la page Debug: Principale</a></li></ul></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>  -> sizeof(S_STRUCT_CONFIGURATION) = %d</td></tr> \n",sizeof(S_STRUCT_CONFIGURATION));
	html_tag("<tr><td>  -> sizeof(S_STRUCT_EXPLOITATION) = %d</td></tr> \n",sizeof(S_STRUCT_EXPLOITATION));
	html_tag("<tr><td>  -> sizeof(S_TYPE_MESSAGE)x%d = %d</td></tr> \n",NB_MAX_LANGUES,NB_MAX_LANGUES*sizeof(S_TYPE_MESSAGE));


	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
}/*VDebugSizeOf*/



//=====================================================================================
// Fonction		: VDebugLogOut
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 06/05/2008
// Description	: Page HTML: permettant de se déconnecter
//=====================================================================================
void VDebugLogOut(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;

	printf("Content-type: text/html\n\n");/* Mandatory */

	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: VDebugLogOut</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VDebugLogOut");	//pour la fonction Actualiser

	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillHttpFile(&s_html_global))
	{
		s_html_global.u8_connexion_prioritaire_http = FALSE;	//on se déconnecte
		u8EditHttpFile(&s_html_global);
	}
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem

	// Redirection vers la page voulue
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=Vaccueil\");");
	html_tag("parent.frame_a.document.location.reload(); \n");
	html_tag("parent.frame_b.document.location.reload(); \n");
#if ACTIVATION_CONSOLE_HTML
	html_tag("parent.frame_console.document.location.reload(); \n");
#endif
	html_tag("</SCRIPT>\n");
	html_tag("</html> \n");


}/*VDebugLogOut*/

//=====================================================================================
// Fonction		: VDebugSystemEvent
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 22/05/2008
// Description	: Page HTML: debug system event
//=====================================================================================
void VDebugSystemEvent(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	u16sod	loc_u16_i;
	u16sod	loc_u16_index_evt;

	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
		||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VDebugSystemEvent");
		return;  
	}

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillEventSystemFile(pt_html_eventsystem))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	
	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Debug: VDebugSystemEvent</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VDebugSystemEvent");	//pour la fonction Actualiser

	html_tag("<body> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Debug: SYSTEME EVENT</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page permet de consulter la base de données de système des évènements.</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VdbgSodielec\" target=\"frame_c\">Retours à la page Debug: Principale</a></li></ul></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td><pre> \n");
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_index_evt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_index_evt))
		{
			html_tag("%5d: %5d ",
					 loc_u16_index_evt,
					 pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u16_numero_evt);

			switch(pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_type_evt)
			{
				case TYPE_EVT_ALARME:
					html_tag("%-17s","TYPE_EVT_ALARME");
					break;
				case TYPE_EVT_INFO:
					html_tag("%-17s","TYPE_EVT_INFO");
					break;
				case TYPE_EVT_GENERIQUE:
					html_tag("%-17s","TYPE_EVT_GENERIQ");
					break;
				case TYPE_EVT_INCONNU:
					html_tag("%-17s","TYPE_EVT_INCONNU");
					break;
				default:
					html_tag("%-17s","?????");
					break;
			}

			
			html_tag("%-28s ",
					 pt_tb_msg[u8_html_langue].ps8_msg_lib_groupe_alarmes[pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_groupe]);

			if(V_JDB == (pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_JDB))
			{
				html_tag("%-7s","V_JDB");
			}
			else
			{
				html_tag("%-7s","");
			}
			if(V_TRAP == (pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_valeur_associee_action & V_TRAP))
			{
				html_tag("%-7s","V_TRAP");
			}
			else
			{
				html_tag("%-7s","");
			}
			
			html_tag(" %02X %02X %s",
					 pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_format_valeur_jdb,
					 pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_format_valeur_trap,
					 (TRUE == pt_html_eventsystem->ps_description_event[loc_u16_index_evt].u8_disponible)?"DISPONIBLE":"-----");

			html_tag("\n"); //retours à la ligne
		}
	}
	html_tag("</pre></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("<tr><td><pre> \n");
	for(loc_u16_i=0;loc_u16_i<NB_MAX_GROUPES;loc_u16_i++)
	{
		html_tag("%5d: %-50s ",
				 pt_html_eventsystem->ps_description_groupe[loc_u16_i].u16_index_groupe,
				 pt_tb_msg[u8_html_langue].ps8_msg_lib_groupe_alarmes[loc_u16_i]);


		html_tag("%s",
				 (TRUE == pt_html_eventsystem->ps_description_groupe[loc_u16_i].u8_disponible)?"DISPONIBLE":"-----");

		html_tag("\n"); //retours à la ligne
	}
	html_tag("</pre></td></tr> \n");


	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
}/*VDebugSystemEvent*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VDebug
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de VDebug
//=====================================================================================
void InitModule_VDebug(void)
{
	;
}/*InitModule_VDebug*/

