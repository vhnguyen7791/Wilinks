/*========================================================================*/
/* NOM DU FICHIER  : bdd_html.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: Base de données commune des pages HTML	  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE008 28/01/2010 CM
// - Gestion fichier configuration debug.ini
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
// - Ajout gestion routage dynamique RIPv2
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE037 06/07/2010 CM
// - Ajout exploitation temperature 
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE055 17/01/2011 CM
// - Modification configuration des antennes
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _BDD_HTML


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//============================================================================
// Fonction		: u8TestStartHtml
// Entrees		: rien
// Sortie		: <loc_u8_resultat> : indique si test démarrage
// Auteur		: CM - 04/11/2009 -
// Description	: renvoie la page d'avertissement si bdd inacessible
//					a appeler au demarrage de chaque page HTML (frameC)
//============================================================================
u8sod u8TestStartHtml(void)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = TRUE; //INIT

	//Test si bdd accessible ou non
	if(TRUE == u8_html_base_donnees_inaccessible) //CONDITION: defaut accès à la base de données
	{
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_BASE_DONNEES_INACCESSIBLE);
		Html_GotoPage(ps8_pageHtmlRetour);
		loc_u8_resultat = FALSE;
	}
	
	return loc_u8_resultat;
}/*u8TestStartHtml*/

//============================================================================
// Fonction		: u16GetTpsRefreshHtml
// Entrees		: 
// Sortie		: <loc_u16_tps_refresh_html> : temps de rafraichissement
// Auteur		: CM - 23/08/2007 -
// Description	: renvoie le tps de rafraichissement des pages HTML actuellement configuree
//============================================================================
u16sod u16GetTpsRefreshHtml(void)
{
	u16sod loc_u16_tps_refresh_html;

	//on ne verrouille pas avec les sémaphores!
	loc_u16_tps_refresh_html = s_html_cfg_eqpmt.s_admin.u16_tps_refresh_html;

	return loc_u16_tps_refresh_html;
}/*u16GetTpsRefreshHtml*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Bdd_Html
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/06/2007 -
// Description	: Initialisation du module Bdd_html
//=====================================================================================
void InitModule_Bdd_Html(void)
{
	s32sod	loc_s32_sem;
	
	//-----------------------------------------------------
	//Initialisation des modules de ce processus
	//-----------------------------------------------------
	InitModule_Pages();
	InitModule_SUAdmControl();
	InitModule_SUAdmIdentif();
	InitModule_SULangue();
	InitModule_SURefresh();
	InitModule_SUSecurite();
	InitModule_SuSystemLog();
	InitModule_SUTime();
	InitModule_VAdmVersions();
	InitModule_VDebug();
	InitModule_SUConfigDhcp();
	InitModule_SUConfigMode();
	InitModule_SUConfigNat();
	InitModule_SUConfigNetwork();
	InitModule_SUConfigRoutingGene();
	InitModule_SUConfigRoutingStatic();
	InitModule_SUConfigRoutingPolitic();
	InitModule_SUConfigRoutingRip();
	InitModule_SUConfigSnmp();
	InitModule_SUConfigWirelessAdv();
	InitModule_SUConfigWirelessBasic();
	InitModule_SUConfigHandoff();
	InitModule_SUConfigMulticast();
	InitModule_Divers();
	InitModuleJavaScript();
	InitModule_Refresh();
	InitModule_VExploitDhcpClient();
	InitModule_VExploitNetwork();
	InitModule_VExploitWireless();
	InitModule_VExploitGeneral();
	InitModule_VAlarme();
	InitModule_VListeAlarme();
	InitModule_SUEvt();
	InitModule_VJdbEvt();
	InitModule_VListeEvt();
	InitModule_VTrap();
	InitModule_Frame();
	InitModule_VAccueil();
	InitModule_VConsole();
	InitModule_Vcontact();
	InitModule_VHomeA();
	InitModule_VHomeB();
	InitModule_VHomeC();
	InitModule_Vsynoptique();
	InitModule_Vwarning();
	InitModule_VcfgInProgress();

	//-----------------------------------------------
	//Initialisation des modules de la librairie system
	//-----------------------------------------------
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(AddMsgDbgLog);
	
	//-----------------------------------------------------
	//Initialisation des modules de la librairie bdd
	//-----------------------------------------------------
	InitModule_LibraryBdd();
	
	//-----------------------------------------------------
	//Initialisation propres à ce processus
	//-----------------------------------------------------
	memset(&s_html_cfg_eqpmt,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	memset(&s_html_exploit,'\0',sizeof(S_STRUCT_EXPLOITATION)); //INIT
	memset(&s_html_global,'\0',sizeof(S_STRUCT_HTTP_GLOBAL)); //INIT
	memset(&s_html_debug_global,'\0',sizeof(S_STRUCT_DEBUG_GLOBAL)); //INIT

	memset(&s_html_exp_events,'\0',sizeof(S_STRUCT_EXPLOIT_EVENTS)); //INIT
	
	pt_html_eventsystem = ptGetPtrEventSystem();; //INIT

	memset(&s_html_list_freq,0xFF,sizeof(S_STRUCT_LIST_FREQ)); //INIT
	
	//Gestion CIP
	memset(&s_cip_snmpd_from_html, 0, sizeof(S_STRUCT_CIP_SNMPD)); //INIT
	memset(&s_cip_jdb_from_html, 0, sizeof(S_STRUCT_CIP_JDB)); //INIT

	//Gestion du journal de bord
	memset(&s_statutjdb_from_html, 0, sizeof(S_STRUCT_STATUTJDB)); //INIT
	
	//-----------------------------------------------------
	//Variables utilisées dans les pages HTML
	//-----------------------------------------------------
	strcpy(ps8_pageHtmlRetour, "");	//INIT
	strcpy(ps8_pageHtmlEnCours, "");//INIT
	
	strcpy(ps8_html_string, "");	//INIT

	u8_html_langue = LANGUE_PAR_DEFAUT; //INIT
	u8_html_base_donnees_inaccessible = FALSE; //INIT

	//-----------------------------------------------------
	//On lit la configuration administration à chaque fois
	//-----------------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
	{
		u8_html_langue = s_html_cfg_eqpmt.s_admin.u8_langue; //MAJ
		SetConfig_ModuleClient(s_html_cfg_eqpmt.s_admin.u8_max_client_ip, s_html_cfg_eqpmt.s_admin.u16_duree_inactivite_http); //MAJ
		SetConfig_ModuleDate(s_html_cfg_eqpmt.s_admin.u8_mode_date_heure); //MAJ
	}
	else
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//-----------------------------------------------------
	//On lit les données http
	//-----------------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillHttpFile(&s_html_global))
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem

}/*InitModule_Bdd_Html*/

