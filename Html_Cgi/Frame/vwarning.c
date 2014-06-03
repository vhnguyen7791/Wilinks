/*========================================================================*/
/* NOM DU FICHIER  : vwarning.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML de w@rning					  */
/* Projet          : WRM100                                               */
/* Indice          : BE054                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE010 03/02/2010 CM
// - Correction problème accès au serveur HTTP (dernière un serveur NAT, avec port forwarding)
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VWARNING

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: PageWarning
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: page HTML d'avertissement
//=====================================================================================
void PageWarning(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{	
	u16sod	loc_u16_numPage;
	u16sod	loc_u16_i,loc_u16_nb_arg;

	if (loc_p_varlist[2] != NULL)
	{
		loc_u16_numPage = (u16sod)atoi(loc_p_varlist[2]);
		sprintf(ps8_pageHtmlRetour,"cgi_fh?URL=Vwarning&%d",loc_u16_numPage);
	}
	else
	{
		sprintf(ps8_pageHtmlRetour,"cgi_fh?URL=Vwarning");
		loc_u16_numPage = WARNING_PAGE_INDISPONIBLE;
	}

	if(WARNING_RELOAD_SUTIME_ET_RELOAD_FRAME_A!=loc_u16_numPage)
	{
		// Entrée au setup par mot de passe
		if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
		{
			//On retourne à la page d'accueil ( c'est normal )
			PreparePagePswd("Vaccueil");
			return;  
		}
	}
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	html_tag("<HTML>\n");

  // Header
	html_tag("<HEAD>\n");
	html_tag("<TITLE>Warning</TITLE>");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
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
	html_tag("</head>\n");

	html_tag("<body> \n");



	JSActualiser(ps8_pageHtmlRetour);	//pour la fonction Actualiser

	switch(loc_u16_numPage)
	{
		case WARNING_CONFIG_OK_ET_RELOAD_FRAME_A:
			html_tag("<SCRIPT LANGUAGE=\"JavaScript\">");
			html_tag("\n");
			html_tag("setTimeout('parent.frame_a.document.location.reload()',400);\n");
			html_tag ("</SCRIPT>");
			break;
		default:
			break;
	}

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("	<TR><TD vAlign=top height=40><P class=header>%s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_avertissement);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	switch(loc_u16_numPage)
	{
		case WARNING_RELOAD_SUADMINDENTIF_ET_RELOAD_FRAME_A:
			html_tag("<SCRIPT LANGUAGE=\"JavaScript\"> \n");
			html_tag("parent.frame_a.document.location.reload(); \n");
			html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmIdentification\"); \n");
			html_tag ("</SCRIPT> \n");
			break;
		case WARNING_RELOAD_SUTIME_ET_RELOAD_FRAME_A:
			html_tag("<SCRIPT LANGUAGE=\"JavaScript\"> \n");
			html_tag("parent.frame_a.document.location.reload(); \n");
			html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUtime\"); \n");
			html_tag ("</SCRIPT> \n");
			break;

		case WARNING_RELOAD_SUADMLANGUE_ET_RELOAD_FRAME_A_FRAME_B:
			html_tag("<SCRIPT LANGUAGE=\"JavaScript\"> \n");
			html_tag("parent.frame_a.document.location.reload(); \n");
			html_tag("parent.frame_b.document.location.reload(); \n");
			html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmLangue\"); \n");
			html_tag ("</SCRIPT> \n");
			break;
			
		case WARNING_CONFIG_OK_ET_RELOAD_FRAME_A:
			break;
		case WARNING_MAJ_INFO_EN_COURS:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_maj_info_en_cours);
			break;
		case WARNING_CONFIG_OK:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_config_ok);
			break;
		case WARNING_CONFIG_KO:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_config_ko);
			break;
		case WARNING_PAS_D_INFORMATION:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_pas_information);
			break;
		case WARNING_PAGE_INDISPONIBLE:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_page_indisponible);
			loc_u16_nb_arg = s32GetArgNb(loc_p_varlist);
			for (loc_u16_i=0;loc_u16_i<loc_u16_nb_arg;loc_u16_i++)
			{
				html_tag("	<TR><TD>argument%d : %s</TD></TR> \n",loc_u16_i,loc_p_varlist[loc_u16_i]);
			}
			break;
		case WARNING_CONFIG_ADRESSE_IP:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_configurer_maintenant);
			break;
		case WARNING_CHARGEMENT_EN_COURS:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_chargement_en_cours);
			break;
		case WARNING_RESET_EQUIPEMENT_EN_COURS:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_reset_equipement_en_cours);
			break;
		case WARNING_BASE_DONNEES_INACCESSIBLE:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible);
			break;
		case WARNING_MODE_ONLY_STATION_ROUTER:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_seulement_mode_station_router);
			break;
		case WARNING_MODE_ONLY_STATION:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_seulement_mode_station);
			break;
		case WARNING_INDISPONIBLE_MODE_MONITOR:
			html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_non_disponible_en_mode_monitor);
			break;
		default:
			break;
	}

	html_tag("</table> \n");
	html_tag("</body>\n");
	html_tag("</html>\n");

}/*PageWarning*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


//=====================================================================================
// Fonction		: InitModule_Vwarning
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation du module Vwarning
//=====================================================================================
void InitModule_Vwarning(void)
{

}/*InitModule_Vwarning*/
