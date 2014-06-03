/*========================================================================*/
/* NOM DU FICHIER  : suconfigNetwork.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Network		  */
/* Projet          : WRM100                                               */
/* Indice          : BE065                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration hostname
// - Intégration configuration par DHCP client
//BE005 15/01/2010 CM
// - Correction bug saisi mode ip WLAN (page HTML Configuration - Network)
//BE010 03/02/2010 CM
// - Correction test configuration des adresses IP des interfaces
//  --> vérification que l'adresse IP n'est pas une adresse nulle pour le masque de sous-réseau défini
//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
// - Correction w@rning dans FireFox "Element referencé par son ID/NAME ..."
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE065.1 02/05/2012 (CM)
// - Correction ergonomie page HTML Configuration - Réseau
//		-> ajout bouton valider formulaire
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGNETWORK

enum LISTE_DES_FORM_SUCONFIGNETWORK
{
	FORM_SUCONFIGNETWORK_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGNETWORK_VALID_1,
	FORM_SUCONFIGNETWORK_VALID_2,
	FORM_SUCONFIGNETWORK_VALID_3,
//d: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
	FORM_SUCONFIGNETWORK_VALID_ALL,
//f: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
	NB_MAX_FORM_SUCONFIGNETWORK
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_mode_network	[10 + 1];

	s8sod	ps8_host_name		[LG_MAX_HOSTNAME+1];
	
	s8sod	ps8_modeIpBridge	[10 + 1];
	s8sod	ps8_adrIpBridge		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_maskIpBridge	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_adrGwBridge		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_adrDhcpFallbackIPBridge	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_stpBridge		[10 + 1];

	s8sod	ps8_adrIpLAN		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_maskIpLAN		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	
	s8sod	ps8_modeIpWLAN		[10 + 1];
	s8sod	ps8_adrIpWLAN		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_maskIpWLAN		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_adrGwWLAN		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_adrDhcpFallbackIPWLAN	[MAX_LG_FORMAT_ADRESSE_IP + 1];

	s8sod	ps8_autorise_Vlan	[10 + 1];
	s8sod	ps8_nomVlan			[TAILLE_MAX_VLAN + 1];
	s8sod	ps8_idVlan			[10 + 1];
	s8sod	ps8_enableVlanNoTag	[10 + 1];
	s8sod	ps8_adrIpVlanNoTag	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_maskIpVlanNoTag	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_NETWORK_RESULTS;

FIELD_LIST s_FormConfigNetworkFields[] = {
	{"modeNet",				"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_mode_network)		},
	{"hostname",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_host_name)			},
	{"modeIpBridge",		"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_modeIpBridge)		},
	{"adrIpBridge",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrIpBridge)		},
	{"maskIpBridge",		"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_maskIpBridge)		},
	{"adrGwBridge",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrGwBridge)		},
	{"adrDhcpFBridge",		"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrDhcpFallbackIPBridge)},
	{"stpBridge",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_stpBridge)},

	{"adrIpLAN",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrIpLAN)			},
	{"maskIpLAN",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_maskIpLAN)			},

	{"modeIpWLAN",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_modeIpWLAN)			},
	{"adrIpWLAN",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrIpWLAN)			},
	{"maskIpWLAN",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_maskIpWLAN)			},
	{"adrGwWLAN",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrGwWLAN)			},
	{"adrDhcpFWLAN",		"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrDhcpFallbackIPWLAN)},

	{"autVlan",				"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_autorise_Vlan)		},
	{"nomVlan",				"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_nomVlan)			},
	{"idVlan",				"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_idVlan)				},
	{"notag",				"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_enableVlanNoTag)	},
	{"adrIpNoTag",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_adrIpVlanNoTag)		},
	{"maskIpNoTag",			"%s",	offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_maskIpVlanNoTag)	},
	
	{"hidden1",		"%s",		offsetof(S_FORM_CONFIG_NETWORK_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigNetwork
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigNetwork
//=====================================================================================
void proc_JavaScript_SUConfigNetwork(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigNetwork
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigNetwork
//=====================================================================================
void proc_JavaScript_SUConfigNetwork(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : JsChangeModeNetwork
	//*************************************
	html_tag("function JsChangeModeNetwork(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_mode_bridge;\n");
	html_tag("	var loc_mode_router; \n");
	html_tag("	loc_mode_bridge = false; \n"); //init
	html_tag("	loc_mode_router = false; \n"); //init
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.modeNet.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_NETWORK_BRIDGE);
	html_tag("				loc_mode_bridge = true;\n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",MODE_NETWORK_ROUTER);
	html_tag("				loc_mode_router = true;\n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	}\n");
	html_tag("	var elmt = document.getElementsByTagName(\"TR\"); \n");
	html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++) \n");
	html_tag("	{\n");
	html_tag("		if(\"TR_MODE_VLAN\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_mode_bridge)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if(\"TR_MODE_BRIDGE\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_mode_bridge)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if(\"TR_MODE_ROUTER\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_mode_router)\n");
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
	html_tag("}\n"); /*JsChangeModeNetwork*/

	//Fonction javascript : JsChangeEnableVLAN
	//*************************************
	html_tag("function JsChangeEnableVLAN(form) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if(true == Number(form.autVlan.value)) \n");
	html_tag("		{ \n");
	html_tag("			form.nomVlan.disabled = false; \n");
	html_tag("			form.idVlan.disabled = false; \n");
	html_tag("			form.notag.disabled = false; \n");
	html_tag("			if(true == Number(form.notag.value)) \n");
	html_tag("			{ \n");
	html_tag("				form.adrIpNoTag.disabled = false; \n");
	html_tag("				form.maskIpNoTag.disabled = false; \n");
	html_tag("			} \n");
	html_tag("			else\n");
	html_tag("			{ \n");
	html_tag("				form.adrIpNoTag.disabled = true; \n");
	html_tag("				form.maskIpNoTag.disabled = true; \n");
	html_tag("			} \n");
	html_tag("		}\n");
	html_tag("		else\n");
	html_tag("		{ \n");
	html_tag("			form.nomVlan.disabled = true; \n");
	html_tag("			form.idVlan.disabled = true; \n");
	html_tag("			form.notag.disabled = true; \n");
	html_tag("			form.adrIpNoTag.disabled = true; \n");
	html_tag("			form.maskIpNoTag.disabled = true; \n");
	html_tag("		}\n");
	html_tag("	}\n");
	html_tag("	return true;\n");
	html_tag("}\n"); /*JsChangeEnableVLAN*/
	
	//Fonction javascript : JsClickModeIP
	//*************************************
	html_tag("function JsClickModeIP(acces, form) \n");
	html_tag("{\n");
	html_tag("	with(document)\n");
	html_tag("	{\n");
	html_tag("		switch(acces)\n");
	html_tag("		{\n");
	html_tag("			case 0: \n"); //bridge
	html_tag("				if(true == form.modeIpBridge[0].checked)   //static\n");
	html_tag("				{\n");
	html_tag("					form.adrIpBridge.disabled = false; \n");
	html_tag("					form.maskIpBridge.disabled = false; \n");
	html_tag("					form.adrGwBridge.disabled = false; \n");
	html_tag("					form.adrDhcpFBridge.disabled = true; \n");
	html_tag("				}\n");
	html_tag("				if(true == form.modeIpBridge[1].checked)   //dhcp\n");
	html_tag("				{\n");
	html_tag("					form.adrIpBridge.disabled = true; \n");
	html_tag("					form.maskIpBridge.disabled = true; \n");
	html_tag("					form.adrGwBridge.disabled = true; \n");
	html_tag("					form.adrDhcpFBridge.disabled = false; \n");
	html_tag("				}\n");
	html_tag("				break;\n");
	html_tag("			case 2: \n"); //WLAN
	html_tag("				if(true == form.modeIpWLAN[0].checked)   //static\n");
	html_tag("				{\n");
	html_tag("					form.adrIpWLAN.disabled = false; \n");
	html_tag("					form.maskIpWLAN.disabled = false; \n");
	html_tag("					form.adrGwWLAN.disabled = false; \n");
	html_tag("					form.adrDhcpFWLAN.disabled = true; \n");
	html_tag("				}\n");
	html_tag("				if(true == form.modeIpWLAN[1].checked)   //dhcp\n");
	html_tag("				{\n");
	html_tag("					form.adrIpWLAN.disabled = true; \n");
	html_tag("					form.maskIpWLAN.disabled = true; \n");
	html_tag("					form.adrGwWLAN.disabled = true; \n");
	html_tag("					form.adrDhcpFWLAN.disabled = false; \n");
	html_tag("				}\n");
	html_tag("				break;\n");
	html_tag("			default:\n");
	html_tag("				break;\n");
	html_tag("		}\n");
	html_tag("	}\n");
	html_tag("	return true;\n");
	html_tag("}\n");/*JsClickModeIP*/

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{\n");
	html_tag("	with(document)\n");
	html_tag("	{\n");
	html_tag("		JsChangeModeNetwork(form); \n");
	html_tag("		JsClickModeIP(0, form); \n");
	html_tag("		JsClickModeIP(2, form); \n");
	html_tag("		JsChangeEnableVLAN(form); \n");
	html_tag("	}\n");
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
	html_tag("				case %d: \n",
			 FORM_SUCONFIGNETWORK_VALID_1);
	html_tag("					if(true == form.modeIpBridge[%d].checked)\n", //CONDITION: en mode IP statique
			 MODE_IP_STATIQUE);
	html_tag("					{ \n");
	html_tag("						if(false == JsVerifyIP_Host(form.adrIpBridge.value, form.maskIpBridge.value)) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("						if(false == JsVerifyIP_Subnet(form.adrIpBridge.value, form.maskIpBridge.value, form.adrGwBridge.value)) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("					} \n");
	html_tag("					if((true == Number(form.autVlan.value)) && (true == Number(form.notag.value)))\n"); //CONDITION: VLAN activé et conserver acces non taggé
	html_tag("					{ \n");
	html_tag("						if(false == JsVerifyIP_Host(form.adrIpNoTag.value, form.maskIpNoTag.value)) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("					} \n");
	html_tag("					break;  \n");
	html_tag("				case %d: \n",
			FORM_SUCONFIGNETWORK_VALID_2);
	html_tag("					if(false == JsVerifyIP_Host(form.adrIpLAN.value, form.maskIpLAN.value)) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = false; \n");
	html_tag("					} \n");
	html_tag("					if(true == form.modeIpWLAN[%d].checked)\n", //CONDITION: en mode IP statique
			 MODE_IP_STATIQUE);
	html_tag("					{ \n");
	html_tag("						if(false == JsVerifyIP_Host(form.adrIpWLAN.value, form.maskIpWLAN.value)) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("						if(false == JsVerifyIP_Subnet(form.adrIpWLAN.value, form.maskIpWLAN.value, form.adrGwWLAN.value)) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag(	"					if(JsGetSubnet(form.adrIpLAN.value, form.maskIpLAN.value) == JsGetSubnet(form.adrIpWLAN.value, form.maskIpWLAN.value)) \n");
	html_tag("						{ \n");
	html_tag("							alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_reseau_LAN_WLAN_dvt_etre_different);
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("					} \n");
	html_tag("					else \n"); //CONDITION: en DHCP client
	html_tag("					{ \n");
	html_tag("						if(0 != IPAddressToUnsignedInteger(form.adrDhcpFWLAN.value)) \n"); //CONDITION: adresse IP de repli activée
	html_tag("						{ \n");
	html_tag("							if(JsGetSubnet(form.adrIpLAN.value, form.maskIpLAN.value) == JsGetSubnet(form.adrDhcpFWLAN.value, \"%s\")) \n",ps8GetStringIp(MASK_RESEAU_SUR_24));
	html_tag("							{ \n");
	html_tag("								alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_ip_dhcp_repli_invalide);
	html_tag("								loc_result = false; \n");
	html_tag("							} \n");
	html_tag("						} \n");
	html_tag("					} \n");
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
}/*proc_JavaScript_SUConfigNetwork*/

//=====================================================================================
// Fonction		: SUConfigNetwork
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: Network
//				"URL=SUConfigNetwork"
//=====================================================================================
void SUConfigNetwork(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_NETWORK_RESULTS loc_s_results;
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
		PreparePagePswd("SUConfigNetwork");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigNetwork&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_NETWORK_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigNetworkFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGNETWORK)
			{
//d: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
//				if(FORM_SUCONFIGNETWORK_VALID_1 == loc_u8_numForm)
				if((FORM_SUCONFIGNETWORK_VALID_1 == loc_u8_numForm)||
				   (FORM_SUCONFIGNETWORK_VALID_ALL == loc_u8_numForm)
				  )
//f: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_gene.u8_mode_network = (u8sod)atoi(loc_s_results.ps8_mode_network);
						s_html_cfg_eqpmt.s_gene.u8_bridge_mode_ip = (u8sod)atoi(loc_s_results.ps8_modeIpBridge);
						if(MODE_IP_STATIQUE == s_html_cfg_eqpmt.s_gene.u8_bridge_mode_ip)
						{
							s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
							s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
							/*MACRO_PRINTF(("********************1*****************\n"));
							strcpy(loc_ps8_addr_ip, ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_adresse_ip)); //INIT
							strcpy(loc_ps8_addr_mask, ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_masque_reseau)); //INIT
							MACRO_PRINTF(("MODE_IP_STATIQUE: ip  %s netmask %s down\n",
								loc_s_results.ps8_adrIpBridge,
								loc_s_results.ps8_maskIpBridge));
							MACRO_PRINTF(("********************1*****************\n"));*///Add
									// by VuHai to debug decodage @IP

							s_html_cfg_eqpmt.s_gene.u32_bridge_adresse_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpBridge, &loc_u8_ret);
							s_html_cfg_eqpmt.s_gene.u32_bridge_masque_reseau = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_maskIpBridge, &loc_u8_ret);
							s_html_cfg_eqpmt.s_gene.u32_bridge_gateway = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrGwBridge, &loc_u8_ret);

							/*MACRO_PRINTF(("********************2*****************\n"));
							strcpy(loc_ps8_addr_ip, ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_adresse_ip)); //INIT
							strcpy(loc_ps8_addr_mask, ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_masque_reseau)); //INIT
							MACRO_PRINTF(("MODE_IP_STATIQUE: ip  %s netmask %s down\n",
								loc_s_results.ps8_adrIpBridge,
								loc_s_results.ps8_maskIpBridge));
							MACRO_PRINTF(("********************2*****************\n"));*///Add
									// by VuHai to debug decodage @IP
						}
						else //MODE_IP_DHCP_CLIENT
						{
							s_html_cfg_eqpmt.s_gene.u32_bridge_dhcp_fallback_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrDhcpFallbackIPBridge, &loc_u8_ret);
						}
						if(0 == strcmp(loc_s_results.ps8_stpBridge, CHECKBOX_VALUE_CHECKED))
						{
							s_html_cfg_eqpmt.s_gene.u8_bridge_stp = TRUE;
						}
						else
						{
							s_html_cfg_eqpmt.s_gene.u8_bridge_stp = FALSE;
						}

						s_html_cfg_eqpmt.s_gene.u8_vlan_autoriser = (u8sod)atoi(loc_s_results.ps8_autorise_Vlan);
						if(TRUE == s_html_cfg_eqpmt.s_gene.u8_vlan_autoriser)
						{
							strcpy(s_html_cfg_eqpmt.s_gene.ps8_vlan_nom, loc_s_results.ps8_nomVlan);
							s_html_cfg_eqpmt.s_gene.u16_vlan_id = (u16sod)atoi(loc_s_results.ps8_idVlan);
							s_html_cfg_eqpmt.s_gene.u8_vlan_interface_notag = (u8sod)atoi(loc_s_results.ps8_enableVlanNoTag);

							if(TRUE == s_html_cfg_eqpmt.s_gene.u8_vlan_interface_notag)
							{
								s_html_cfg_eqpmt.s_gene.u32_vlan_notag_adresse_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpVlanNoTag, &loc_u8_ret);
								s_html_cfg_eqpmt.s_gene.u32_vlan_notag_masque_reseau = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_maskIpVlanNoTag, &loc_u8_ret);
							}
						}
						
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

//d: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
//				if(FORM_SUCONFIGNETWORK_VALID_2 == loc_u8_numForm)
				if((FORM_SUCONFIGNETWORK_VALID_2 == loc_u8_numForm)||
				   (FORM_SUCONFIGNETWORK_VALID_ALL == loc_u8_numForm)
				  )
//f: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_gene.u8_mode_network = (u8sod)atoi(loc_s_results.ps8_mode_network);
						s_html_cfg_eqpmt.s_gene.u32_lan_adresse_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpLAN, &loc_u8_ret);
						s_html_cfg_eqpmt.s_gene.u32_lan_masque_reseau = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_maskIpLAN, &loc_u8_ret);
						s_html_cfg_eqpmt.s_gene.u8_wlan_mode_ip = (u8sod)atoi(loc_s_results.ps8_modeIpWLAN);
						if(MODE_IP_STATIQUE == s_html_cfg_eqpmt.s_gene.u8_wlan_mode_ip)
						{
							s_html_cfg_eqpmt.s_gene.u32_wlan_adresse_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpWLAN, &loc_u8_ret);
							s_html_cfg_eqpmt.s_gene.u32_wlan_masque_reseau = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_maskIpWLAN, &loc_u8_ret);
							s_html_cfg_eqpmt.s_gene.u32_wlan_gateway = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrGwWLAN, &loc_u8_ret);
						}
						else //MODE_IP_DHCP_CLIENT
						{
							s_html_cfg_eqpmt.s_gene.u32_wlan_dhcp_fallback_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrDhcpFallbackIPWLAN, &loc_u8_ret);
						}
						
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

//d: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
//				if(FORM_SUCONFIGNETWORK_VALID_3 == loc_u8_numForm)
				if((FORM_SUCONFIGNETWORK_VALID_3 == loc_u8_numForm)||
				   (FORM_SUCONFIGNETWORK_VALID_ALL == loc_u8_numForm)
				  )
//f: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
					{
						strcpy(s_html_cfg_eqpmt.s_gene.ps8_hostname, loc_s_results.ps8_host_name);
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
				PreparePageCfgInProgress("SUConfigNetwork");
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
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_reseau);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("	tr.TR_MODE_VLAN {\n"
			 "}\n");
	html_tag("	tr.TR_MODE_BRIDGE {\n"
			 "}\n");
	html_tag("	tr.TR_MODE_ROUTER {\n"
			 "}\n");
	html_tag("</STYLE>\n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigNetwork");	//pour la fonction Actualiser

	JSNumCheck();
	JSTextCheck();
	JSIPCheck();

	proc_JavaScript_SUConfigNetwork();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigNetwork");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_reseau);
	html_tag("<tr><td><P>%s<BR>%s<BR>%s<BR>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigNetwork,
			 pt_tb_msg[u8_html_langue].ps8_msg_infohtml_access_point_bridge,
			 pt_tb_msg[u8_html_langue].ps8_msg_infohtml_station_bridge_router,
			 pt_tb_msg[u8_html_langue].ps8_msg_infohtml_monitor_bridge);
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
	

	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			pt_tb_msg[u8_html_langue].ps8_msg_parametrage_mode_reseau);

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Mode réseau
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_reseau);
	html_tag("			<td><SELECT name=\"modeNet\" size=\"1\" onchange=\"return(JsChangeModeNetwork(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_NETWORK;loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pt_definition_radio_modem[s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem].pu8_flag_mode_reseau[loc_u8_i])
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_u8_i == s_html_cfg_eqpmt.s_gene.u8_mode_network) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_reseau[loc_u8_i]);
		}
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_attention,
			 pt_tb_msg[u8_html_langue].ps8_msg_avertissement_changement_adresse_ip);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Paramètres gestion VLAN
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_VLAN\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_vlan);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_VLAN\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_VLAN\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Activation VLAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_vlan);
	html_tag("			<td><SELECT name=autVlan onchange=\"return(JsChangeEnableVLAN(form))\"> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_gene.u8_vlan_autoriser) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_gene.u8_vlan_autoriser) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	//VLAN name
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_nom_vlan);
	html_tag("			<td><input type=\"text\" size=%d maxlength=%d name=\"nomVlan\" value=\"%s\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
			 TAILLE_MAX_VLAN + 15, //size (rmq:+15 pour pouvoir lire la totalité de la chaine de caractères
			 TAILLE_MAX_VLAN, //maxlength
			 s_html_cfg_eqpmt.s_gene.ps8_vlan_nom);
	html_tag("		</tr> \n");
	//VLAN ID
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_id_vlan);
	html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"idVlan\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
			 s_html_cfg_eqpmt.s_gene.u16_vlan_id,
			 VLAN_ID_MIN,
			 VLAN_ID_MAX);
	html_tag("		<tr> \n");
	html_tag("			<th colspan=2>&nbsp;</th> \n");
	html_tag("		</tr> \n");
	//Conserver accès non taggé
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_conserver_acces_lan_non_tagge);
	html_tag("			<td><SELECT name=notag onchange=\"return(JsChangeEnableVLAN(form))\"> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_gene.u8_vlan_interface_notag) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_gene.u8_vlan_interface_notag) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	//Adresse IP accès non taggé
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpNoTag\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_vlan_notag_adresse_ip));
	html_tag("		</tr> \n");
	//Masque de sous-reseau accès non taggé
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"maskIpNoTag\" value=\"%s\" width=\"15\" onchange=\"return(validMask(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_vlan_notag_masque_reseau));
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	
	//Paramètres réseau du BRIDGE
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_BRIDGE\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_reseau_bridge);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_BRIDGE\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_BRIDGE\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Adresse MAC Ethernet
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_mac_ethernet);
	html_tag("			<td>%s</td> \n",
			 ps8GetChAddressMac(s_html_exploit.s_general.ps_interface[INTERFACE_LAN].pu8_add_mac));
	html_tag("		</tr> \n");
	//Adresse MAC Wireless
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_mac_wifi);
	html_tag("			<td>%s</td> \n",
			 ps8GetChAddressMac(s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].pu8_add_mac));
	html_tag("		</tr> \n");
	//Mode IP Bridge
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_ip);
	html_tag("			<td>");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_IP;loc_u8_i++)
	{
		html_tag("<input type=\"radio\" %s name=\"modeIpBridge\" value=\"%d\" onclick=\"JsClickModeIP(0, form)\">%s",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_gene.u8_bridge_mode_ip) ? "checked" : ""),
				loc_u8_i,
				pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_ip[loc_u8_i]);
		html_tag("&nbsp;&nbsp; \n");
	}
	html_tag("</td> \n");
	//Adresse IP Bridge
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpBridge\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_adresse_ip));
	html_tag("		</tr> \n");
	//Masque de sous-reseau Bridge
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"maskIpBridge\" value=\"%s\" width=\"15\" onchange=\"return(validMask(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_masque_reseau));
	html_tag("		</tr> \n");
	//Passerelle Bridge
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_passerelle);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrGwBridge\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_gateway));
	html_tag("		</tr> \n");
	//DHCP fallback IP bridge
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_ip_repli_dhcp);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrDhcpFBridge\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_bridge_dhcp_fallback_ip));
	html_tag("		</tr> \n");
	//Spanning Tree Protocol (STP)
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_spanning_tree_protocol);
	html_tag("			<td><input name=\"stpBridge\" type=\"checkbox\" %s value=\"%s\"></td> \n",
			 (TRUE == s_html_cfg_eqpmt.s_gene.u8_bridge_stp)? "checked" : "",
			 CHECKBOX_VALUE_CHECKED);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");


	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_BRIDGE\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_BRIDGE\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_BRIDGE\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGNETWORK_VALID_1);


	

	//Paramètres réseau du LAN
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_reseau_LAN);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Adresse MAC Ethernet
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_mac_ethernet);
	html_tag("			<td>%s</td> \n",
			 ps8GetChAddressMac(s_html_exploit.s_general.ps_interface[INTERFACE_LAN].pu8_add_mac));
	html_tag("		</tr> \n");
	//Mode IP LAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_ip);
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_ip[MODE_IP_STATIQUE]);
	//Adresse IP LAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpLAN\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_lan_adresse_ip));
	html_tag("		</tr> \n");
	//Masque de sous-reseau LAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"maskIpLAN\" value=\"%s\" width=\"15\" onchange=\"return(validMask(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_lan_masque_reseau));
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");

	//Paramètres réseau du WLAN
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_reseau_WLAN);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Adresse MAC Wireless
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_mac_wifi);
	html_tag("			<td>%s</td> \n",
			 ps8GetChAddressMac(s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].pu8_add_mac));
	html_tag("		</tr> \n");
	//Mode IP WLAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_ip);
	html_tag("			<td>");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_IP;loc_u8_i++)
	{
		html_tag("<input type=\"radio\" %s name=\"modeIpWLAN\" value=\"%d\" onclick=\"JsClickModeIP(2, form)\">%s",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_gene.u8_wlan_mode_ip) ? "checked" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_ip[loc_u8_i]);
		html_tag("&nbsp;&nbsp; \n");
	}
	html_tag("</td> \n");
	//Adresse IP WLAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpWLAN\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_wlan_adresse_ip));
	html_tag("		</tr> \n");
	//Masque de sous-reseau WLAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"maskIpWLAN\" value=\"%s\" width=\"15\" onchange=\"return(validMask(this, true))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_wlan_masque_reseau));
	html_tag("		</tr> \n");
	//Passerelle WLAN
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_passerelle);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrGwWLAN\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_wlan_gateway));
	html_tag("		</tr> \n");
	//DHCP fallback IP bridge
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_ip_repli_dhcp);
	html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrDhcpFWLAN\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
			 ps8GetStringIp(s_html_cfg_eqpmt.s_gene.u32_wlan_dhcp_fallback_ip));
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_MODE_ROUTER\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGNETWORK_VALID_2);

	//Paramétrage du hostname
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_hostname);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Host name
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_hostname);
	html_tag("			<td><input type=\"text\" size=%d maxlength=%d name=\"hostname\" value=\"%s\" onchange=\"return(isValidText(this,true,false))\"></td> \n",//isValidText: espace interdit + champ vide non autorisé
			 LG_MAX_HOSTNAME + 15, //size (rmq:+15 pour pouvoir lire la totalité de la chaine de caractères
			 LG_MAX_HOSTNAME, //maxlength
			 s_html_cfg_eqpmt.s_gene.ps8_hostname);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGNETWORK_VALID_3);
	html_tag("<tr><td>&nbsp;</td></tr> \n");


//d: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider_formulaire,
			 FORM_SUCONFIGNETWORK_VALID_ALL);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
//f: BE065.1 02/05/2012 (CM) - Correction ergonomie page HTML Configuration - Réseau
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigNetwork*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigNetwork
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigNetwork
//=====================================================================================
void InitModule_SUConfigNetwork(void)
{
}/*InitModule_SUConfigNetwork*/
