/*========================================================================*/
/* NOM DU FICHIER  : vhomeB.c       									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML homeB						 	  */
/* Projet          : WRM100                                               */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Ajout exploitation adresse IP/Mask des interfaces
//		=> ajout page HTML Exploitation - Réseau
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du système
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
//BE037 06/07/2010 CM
// - Ajout exploitation temperature 
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _VHOMEB

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: JavaScript_HomeB
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/04/2004 -
// Description	: code de javascript de la page HomeB
//=====================================================================================
void JavaScript_HomeB(void)
{
	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript JsShow
	html_tag("function JsShow(Text)\n");
	html_tag("{\n");
	html_tag("	window.status=Text;\n");
	html_tag("	return true;\n");
	html_tag("}\n");

	//Fonction javascript JsReduc
	html_tag("function JsReduc(elmtTitre)\n"
			 "{\n"
			 "	var elmt = elmtTitre.parentNode;\n"
			 "	if (elmt.childNodes[1].className == \"contentVisible\")\n"
			 "	{\n"
			 "		elmt.childNodes[1].className = \"contentInvisible\"; \n"
			 "	}\n"
			 "	else\n"
			 "	{\n"
			 "		elmt.childNodes[1].className = \"contentVisible\"; \n"
			 "	}\n"
			 "}\n");

	//Fonction javascript couleur des liens dans le menu
	html_tag("function JsColorLien(boxlink) \n"
			 "{ \n"
			 "	var elmt = document.getElementsByTagName(\"a\"); \n"
			 "	for(loc_i_i=0;loc_i_i<elmt.length;loc_i_i++)  \n"
			 "	{ \n"
			 "		elmt[loc_i_i].style.color = \"#FFFFF0\";  \n"
			 "	} \n"
			 "	boxlink.style.color = \"#D00216\";  \n"
			 "	return true; \n"
			 "}\n");

	html_tag("</SCRIPT>\n");
	
}/*JavaScript_HomeB*/

//=====================================================================================
// Fonction		: HomeB
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Menu général
//=====================================================================================
void HomeB(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	
	printf("Content-type: text/html\n\n");/* Mandatory */
	
	html_tag("<HTML>\n");
	
	// Header
	html_tag("<HEAD>\n");	
	html_tag("<TITLE>FRAME_B</TITLE>");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("\n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</HEAD>\n");
	
	JavaScript_HomeB();
	
	//BODY
	html_tag("<body class=homeB>\n");
	html_tag("<P class=homeB>\n");
	html_tag("<a class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\"\n",pt_tb_msg[u8_html_langue].ps8_msg_show_accueil);
	html_tag("	  onmouseout=\"return JsShow('')\"\n");
	html_tag("	  href=\"/cgi-bin/cgi_fh?URL=Vaccueil\" target=\"frame_c\">%s</a>\n",pt_tb_msg[u8_html_langue].ps8_msg_accueil);
	html_tag("<BR>\n");
#if ACTIVATION_PRESENCE_SYNOPTIQUE
	html_tag("<a class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\"\n",pt_tb_msg[u8_html_langue].ps8_msg_show_synoptique);
	html_tag("	  onmouseout=\"return JsShow('')\"\n");
	html_tag("	  href=\"/cgi-bin/cgi_fh?URL=VSynoptique\" target=\"frame_c\">%s</a>\n",pt_tb_msg[u8_html_langue].ps8_msg_synoptique);
	html_tag("<BR>\n");
#endif
	html_tag("<BR>\n");
	html_tag("<a  class=homeB onmouseover=\"return JsShow('%s')\"\n",pt_tb_msg[u8_html_langue].ps8_msg_show_actualiser);
	html_tag("   onmouseout=\"return JsShow('')\"\n");
	html_tag("   target=\"frame_c\" \n");
	html_tag("   href=\"javascript:top.frame_c.document.location.href = top.frame_c.FileName;\">%s</a> \n",pt_tb_msg[u8_html_langue].ps8_msg_actualiser);
	html_tag("<BR>\n");

	//Configuration
	html_tag("<div class=\"contentPointer\">"
			 "<span onclick=\"JsReduc(this)\" onmouseover=\"return JsShow('%s')\" onmouseout=\"return JsShow('')\" > "
			 "<P class=homeB><B><u>%s</u></B></P></span>",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration);
	html_tag("<div class=\"contentInvisible\"><pre>\n");
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigMode\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_mode_radio_modem,
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_m);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigNetwork\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_cfg_reseau,
			 pt_tb_msg[u8_html_langue].ps8_msg_reseau);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigWirelessBasic\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_cfg_wifi,
			 pt_tb_msg[u8_html_langue].ps8_msg_wifi);
#ifdef _WRM100_N_SELECT
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigHandoff\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_cfg_hand_off,
			 pt_tb_msg[u8_html_langue].ps8_msg_hand_off);
#endif
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigRoutingGene\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_routage_IP,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigDhcp\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_serveur_relai_dhcp,
			 pt_tb_msg[u8_html_langue].ps8_msg_serveur_relai_dhcp);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigNat\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_NAT,
			 pt_tb_msg[u8_html_langue].ps8_msg_NAT);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigMulticast\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_Multicast,
			 pt_tb_msg[u8_html_langue].ps8_msg_Multicast);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUConfigSNMP\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_SNMP,
			 pt_tb_msg[u8_html_langue].ps8_msg_SNMP);
	html_tag("</pre></div>"
			 "</div> \n");

	//Exploitation
	html_tag("<div class=\"contentPointer\">"
			 "<span onclick=\"JsReduc(this)\" onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" onmouseout=\"return JsShow('')\" > "
			 "<P class=homeB><B><u>%s</u></B></P></span>",
			 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
			 pt_tb_msg[u8_html_langue].ps8_msg_exploitation);
	html_tag("<div class=\"contentInvisible\"><pre>\n");
#if 0
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VconfigEquipement\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_etat_de_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_etat_de_configuration);
#endif
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VListeAlarme\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_liste_alarmes,
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_alarmes);
#if VERSION_WRM100_DEMO
#else
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VExploitGeneral\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_exp_general,
			 pt_tb_msg[u8_html_langue].ps8_msg_generale);
#endif
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VExploitNetwork\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_exp_reseau,
			 pt_tb_msg[u8_html_langue].ps8_msg_reseau);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VExploitWireless\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_exp_wifi,
			 pt_tb_msg[u8_html_langue].ps8_msg_wifi);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VExploitDhcpClient\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_exp_dhcp_client,
			 pt_tb_msg[u8_html_langue].ps8_msg_dhcp_clients);
	html_tag("</pre></div>"
			 "</div> \n");

	//Evenements
	html_tag("<div class=\"contentPointer\">"
			 "<span onclick=\"JsReduc(this)\" onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" onmouseout=\"return JsShow('')\" > "
			 "<P class=homeB><B><u>%s</u></B></P></span>",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements);
	html_tag("<div class=\"contentInvisible\"><pre>\n");
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_parametrage_evenements,
			 PAGE_VLISTEVT_NUM_1,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_evenements);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VJDBEvenement&param=%d\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_journal_de_bord,
			 PAGE_HTML_JDB_CONFIG,
			 pt_tb_msg[u8_html_langue].ps8_msg_journal_de_bord);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VTrap\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_table_alarmes,
			 pt_tb_msg[u8_html_langue].ps8_msg_table_alarmes);
	html_tag("</pre></div>"
			 "</div> \n");

	//Administration
	html_tag("<div class=\"contentPointer\">"
			 "<span onclick=\"JsReduc(this)\" onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" onmouseout=\"return JsShow('')\" > "
			 "<P class=homeB><B><u>%s</u></B></P></span>",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_administration);
	html_tag("<div class=\"contentInvisible\"><pre>\n");
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUAdmIdentification\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_identification,
			 pt_tb_msg[u8_html_langue].ps8_msg_identification);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUAdmLangue\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_langue,
			 pt_tb_msg[u8_html_langue].ps8_msg_langue);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUAdmRefresh\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_rafraichissement,
			 pt_tb_msg[u8_html_langue].ps8_msg_rafraichissement);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUAdmControle\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_controle,
			 pt_tb_msg[u8_html_langue].ps8_msg_controle);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_securite,
			 pt_tb_msg[u8_html_langue].ps8_msg_securite);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUtime\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_mise_a_heure,
			 pt_tb_msg[u8_html_langue].ps8_msg_mise_a_heure);
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=SUAdmSystemLog\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_adm_journal_system,
			 pt_tb_msg[u8_html_langue].ps8_msg_journal_system);
#if AFFICHAGE_HTML_VERSIONS_LOGICIELLES_ONLY
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=Adm_Versions\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_versions_logicielles,
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles);
#else
	html_tag("<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=Adm_Versions\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_show_versions_logicielles_et_options,
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles_et_options);
#endif
	html_tag("</pre></div>"
			 "</div> \n");

	//Test + Debug
	if (TRUE == s_html_global.u8_connexion_prioritaire_http)	//CONDITION : debug HTTP activé
	{
		html_tag("<P class=homeB><B><u>Debug HTTP</u></B><BR> \n");
		html_tag("<a class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('Acces aux pages de debug de SODIELEC')\" \n");
		html_tag("	 onmouseout=\"return JsShow('')\" \n");
		html_tag("   href=\"/cgi-bin/cgi_fh?URL=VdbgSodielec\" target=\"frame_c\">Principal</a><BR> \n");
		html_tag("<a class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('Permet de se déconnecter aux pages de debug SODIELEC')\" \n");
		html_tag("	 onmouseout=\"return JsShow('')\" \n");
		html_tag("   href=\"/cgi-bin/cgi_fh?URL=VDebugLogOut\" target=\"frame_c\">Se déconnecter</a><BR> \n");
		html_tag("</P> \n");
	}
	
	//Contact
	html_tag("	<a  class=homeB onclick=\"return JsColorLien(this)\" onmouseover=\"return JsShow('%s')\" \n"
			 "		onmouseout=\"return JsShow('')\" \n"
			 "	    href=\"/cgi-bin/cgi_fh?URL=VContact\" target=\"frame_c\">%s</a> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_contact,
			 pt_tb_msg[u8_html_langue].ps8_msg_contact);
	
	html_tag("</BODY> \n");
	html_tag("</HTML> \n");
  
}/*HomeB*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VHomeB
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module vhomeB
//=====================================================================================
void InitModule_VHomeB(void)
{

}/*InitModule_VHomeB*/
