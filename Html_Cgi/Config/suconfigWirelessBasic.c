/*========================================================================*/
/* NOM DU FICHIER  : suconfigWirelessBasic.c							  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Wireless (Basic) */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Correction bug javascript page configuration Wifi
//		cght du mode wifi avec plusieurs canaux
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
//BE040 13/09/2010 CM
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Correction configuration mode 802.11 (associé au driver-N)
// - Ajout gestion liste des fréquences réglementaires
// - Ajout paramètre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
// - Correction test valeur SSID (champs vide non autorisé)
//BE052 15/12/2010 CM
// - Correction bug configuration delay GTK (pb cast)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification une seule antenne autorisée dans les modes 802.11abg (Driver-N)
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
// - Modification débit emission MCS0 à MCS15 autorisé quelque soit nb antennes
// - Correction bug HTLML affichage des password sous Internet Explorer (IE)
//		-> on ne peut change le type d'une balise INPUT de "text" --> "password" (ou vice et versa)
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Correction taille page configuration wifi basique
//		au niveau de la listbox du canal
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout fonction qui liste les fichiers dans répertoire
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGWIRELESSBASIC

enum LISTE_DES_FORM_SUCONFIGWIRELESSBASIC
{
	FORM_SUCONFIGWIRELESSBASIC_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGWIRELESSBASIC_VALID_1,
	FORM_SUCONFIGWIRELESSBASIC_VALID_2,
	FORM_SUCONFIGWIRELESSBASIC_VALID_ALL,
	FORM_SUCONFIGWIRELESSBASIC_REMOVE_CERTIFICAT,
	NB_MAX_FORM_SUCONFIGWIRELESSBASIC
};

#define CH_CERTIFICAT_NO_SELECTED "noselected"

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_ssid		[NB_MAX_CHAINE_SSID + 1];
	s8sod	ps8_dual_ssid		[10 + 1];
	s8sod	ps8_second_ssid		[NB_MAX_CHAINE_SSID + 1];
	s8sod	ps8_mask_ssid	[10 + 1];
	s8sod	ps8_mode_802_11	[10 + 1];
	s8sod	ps8_guardInt	[10 + 1];
	s8sod	ps8_mode_canal	[10 + 1];
	s8sod	ps8_canal_iso	[10 + 1];
	s8sod	ps8_canal_multi[NB_MAX_MULTI_CANAUX]	[10 + 1];
#ifdef _WRM100_ABG_SELECT
	s8sod	ps8_ABG_antenne_tx		[10 + 1];
	s8sod	ps8_ABG_antenne_rx		[10 + 1];
#endif
#ifdef _WRM100_N_SELECT
	s8sod	ps8_N_antenne		[10 + 1];
#endif
	s8sod	ps8_puissance_tx[10 + 1];
	s8sod	ps8_data_rate	[10 + 1];
	s8sod	ps8_seuil_rx	[10 + 1];
	s8sod	ps8_max_station	[10 + 1];
	s8sod	ps8_mode_securite[10 + 1];
	s8sod	ps8_wep_key_lg	[10 + 1];
	s8sod	ps8_wep_key_type[10 + 1];
	s8sod	ps8_wep_key_value[NB_MAX_IDX_WEP_KEY][KEY_WEP_VALUE_LENGTH_MAX + 1];
	s8sod	ps8_wep_key_default[10 + 1];
	s8sod	ps8_wep_authentification[10 + 1];
	s8sod	ps8_wpa_authentification[10 + 1];
	s8sod	ps8_psk_type[10 + 1];
	s8sod	ps8_wpa_key_psk_value[LG_MAX_PRESHARED_WPA_TOTAL + 1];
	s8sod	ps8_wpa_update_interval[10 + 1];
	s8sod	ps8_wep_key_display[10 + 1];
	s8sod	ps8_wpa_key_display[10 + 1];
	s8sod	ps8_adrIpRadius		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_portRadius		[10 + 1];
	s8sod	ps8_keyRadius		[LG_MAX_SHARED_RADIUS + 1];
	s8sod	ps8_eap_reauth_period[10 + 1];
	s8sod	ps8_eap_method		[10 + 1];
	s8sod	ps8_eap_identity		[LG_MAX_EAP_IDENTITY + 1];
#if PARAMETERS_RADIUS_NOT_USED
	s8sod	ps8_eap_user_name	[LG_MAX_EAP_USER_NAME + 1];
#endif
	s8sod	ps8_eap_user_password	[LG_MAX_EAP_USER_PASSWORD + 1];
	s8sod	ps8_eap_file_certificat_authority[LG_MAX_NOM_CERTIFICAT + 1];
	s8sod	ps8_eap_file_certificat_client[LG_MAX_NOM_CERTIFICAT + 1];
	s8sod	ps8_eap_private_key_password[LG_MAX_PRIVATE_KEY_PWD + 1];
	s8sod	ps8_eap_remove_file_certificat[LG_MAX_NOM_CERTIFICAT + 1];
	s8sod	ps8_eap_key_display[10 + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_WIRELESS_BASIC_RESULTS;

FIELD_LIST s_FormConfigWirelessBasicFields[] = {
	{"ssid",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_ssid)		},
	{"dualssid",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_dual_ssid)	},
	{"secondssid",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_second_ssid)	},
	{"ssidMask",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_mask_ssid)	},
	{"mode802",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_mode_802_11)	},
	{"guardInt",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_guardInt)	},
	{"channelMode",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_mode_canal)	},
	{"ch0",					"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_canal_iso)	},
	{"ch1",					"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_canal_multi[0])	},
	{"ch2",					"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_canal_multi[1])	},
	{"ch3",					"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_canal_multi[2])	},
	{"ch4",					"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_canal_multi[3])	},
	{"ch5",					"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_canal_multi[4])	},
#ifdef _WRM100_ABG_SELECT
	{"ant_ABG_tx",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_ABG_antenne_tx)},
	{"ant_ABG_rx",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_ABG_antenne_rx)},
#endif
#ifdef _WRM100_N_SELECT
	{"ant_N",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_N_antenne)},
#endif
	{"power",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_puissance_tx)	},
	{"rate",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_data_rate)	},
	{"seuilRx",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_seuil_rx)	},
	{"maxSta",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_max_station)	},
	{"secuMode",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_mode_securite)	},
	{"wepKeyLg",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_lg)	},
	{"wepKeyTp",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_type)	},
	{"wepkey0",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_value[IDX_WEP_KEY_1])	},
	{"wepkey1",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_value[IDX_WEP_KEY_2])	},
	{"wepkey2",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_value[IDX_WEP_KEY_3])	},
	{"wepkey3",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_value[IDX_WEP_KEY_4])	},
	{"wepKeyCx",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_default)	},
	{"wepAuth",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_authentification)	},
	{"wpaAuth",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wpa_authentification)	},
	{"pskTp",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_psk_type)	},
	{"wpakey",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wpa_key_psk_value)	},
	{"wpaUpdt",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wpa_update_interval)	},
	{"wepKeyDisplay",		"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wep_key_display)	},
	{"wpaKeyDisplay",		"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_wpa_key_display)	},
	{"adrIpRadius",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_adrIpRadius)	},
	{"portRadius",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_portRadius)	},
	{"keyRadius",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_keyRadius)	},
	{"eapReauthPd",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_reauth_period)	},
	{"eapMethod",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_method)	},
	{"eapId",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_identity)	},
#if PARAMETERS_RADIUS_NOT_USED
	{"eapUserName",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_user_name)	},
#endif
	{"eapUserPwd",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_user_password)	},
	{"eapFileCA",			"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_file_certificat_authority)	},
	{"eapFileCertClt",		"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_file_certificat_client)	},
	{"eapPrivKeyPwd",		"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_private_key_password)	},
	{"eapRemoveCert",		"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_remove_file_certificat)	},
	{"eapKeyDisplay",		"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_eap_key_display)	},

	{"hidden1",				"%s",	offsetof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS, ps8_hidden1)		},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigWirelessBasic
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigWirelessBasic
//=====================================================================================
void proc_JavaScript_SUConfigWirelessBasic(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigWirelessBasic
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigWirelessBasic
//=====================================================================================
void proc_JavaScript_SUConfigWirelessBasic(void)
{
	u8sod	loc_u8_i;
	u16sod	loc_u16_i;
#ifdef _WRM100_N_SELECT
	u8sod	loc_u8_k;
#endif
	s8sod	loc_ps8_chaine_debit[UI_TAILLE_MAX_MESSAGE];

	strcpy(loc_ps8_chaine_debit, "");	//INIT
	
	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : ResetBoite
	//*************************************
	html_tag("function ResetBoite(boite)  \n");
	html_tag("{  \n");
	html_tag("	var loc_i_i; \n");
	html_tag("	for(loc_i_i=0; loc_i_i<boite.length; loc_i_i++)  \n");
	html_tag("	{  \n");
	html_tag("		boite.options[loc_i_i] = null;  \n");
	html_tag("	} \n");
	html_tag("	boite.length = 0;  \n");
	html_tag("	boite.disabled = true;  \n");
	html_tag("}  \n"); /*ResetBoite*/

	//Fonction javascript : optionValueIndexOf
	//*************************************
	html_tag("function optionValueIndexOf(boite, value)  \n");
	html_tag("{  \n");
	html_tag("	var loc_i_i; \n");
	html_tag("	var loc_i_ixd_trouve = -1; \n");
	html_tag("	for(loc_i_i=0; loc_i_i<boite.length; loc_i_i++)  \n");
	html_tag("	{  \n");
	html_tag("		if(value == boite.options[loc_i_i].value)  \n");
	html_tag("		{  \n");
	html_tag("			loc_i_ixd_trouve = loc_i_i;  \n");
	html_tag("			loc_i_i = boite.length+1;  \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_i_ixd_trouve; \n");
	html_tag("}  \n"); /*optionValueIndexOf*/
	
	//Fonction javascript : JSChangeTextResultChannelSpectrumWidth
	//*************************************
	html_tag("function JSChangeTextResultChannelSpectrumWidth(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_ch_tempo; \n");
	html_tag("	loc_ch_tempo = \"\"; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(Number(form.mode802.value)) \n");
	html_tag("		{ \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_WIFI_802_11;loc_u8_i++)
	{
		html_tag("			case %d:\n",loc_u8_i);
		html_tag("				loc_ch_tempo = \"%s\"; \n",T_TB_VAL.ps_channel_spectrum_width[T_TB_VAL.pt_definition_mode_wifi[loc_u8_i].u8_channelspectrumwidth].ps8_message);
		html_tag("				break;\n");
	}
	html_tag("			default: \n");
	html_tag("				break;\n");
	html_tag("		} \n");
	html_tag("		getElementById(\"textResultChannelSpectrumWidth\").innerHTML = \"\"+loc_ch_tempo; \n");
	html_tag("	}  \n");
	html_tag("}\n");

	//Fonction javascript : JsPrintHtmlMode80211
	//*************************************
	html_tag("function JsPrintHtmlMode80211(loc_mode80211_cur) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		document.writeln('<select name=\"mode802\" size=\"1\" onchange=\"return(JsChangeMode802_11x(form))\"> '); \n");
	html_tag("		SetBoiteMode80211(form.mode802, loc_mode80211_cur); \n");
	html_tag("		document.writeln('</select> '); \n");
	html_tag("	} \n");
	html_tag("} \n");/*JsPrintHtmlMode80211*/

	//Fonction javascript : SetBoiteMode80211
	//*************************************
	html_tag("function SetBoiteMode80211(boite, loc_mode80211_cur)  \n");
	html_tag("{ \n");
	html_tag("	var loc_i; \n");
	html_tag("	var loc_index_selected = 0; \n");
	html_tag("	var loc_cpt = 0; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		boite.disabled = false; \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_WIFI_802_11;loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pt_definition_radio_modem[s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem].pu8_flag_mode_80211x[loc_u8_i])
		{
			html_tag("		boite.options[loc_cpt] = new Option(\"%s\", %d); \n",
					 T_TB_VAL.pt_definition_mode_wifi[loc_u8_i].ps8_message,
					 loc_u8_i);
			html_tag("		if(%d == loc_mode80211_cur) \n",loc_u8_i);
			html_tag("		{ \n");
			html_tag("			loc_index_selected = loc_cpt; \n");
			html_tag("		} \n");
			html_tag("		loc_cpt ++; \n");
		}
	}
	html_tag("		boite.length = loc_cpt; \n");
	html_tag("		boite.selectedIndex = loc_index_selected;  \n");
	html_tag("	} \n");
	html_tag("} \n"); /*SetBoiteMode80211*/
	
	//Fonction javascript : JsChangeMode802_11x
	//*************************************
	html_tag("function JsChangeMode802_11x(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_k; \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var loc_number_channel_cur; \n");
	html_tag("	var loc_rate_cur; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	//canal
	html_tag("		for(loc_k=0;loc_k<%d;loc_k++) \n",NB_MAX_MULTI_CANAUX+1); //canaux multi + canal iso
	html_tag("		{ \n");
	html_tag("			loc_nom_variable = \"form.ch\"+loc_k; \n");
	html_tag("			loc_number_channel_cur = eval(loc_nom_variable).value;  \n");
	html_tag("			ResetBoite(eval(loc_nom_variable)); \n");
	html_tag("			JsCreateSelectChannel(loc_k, loc_number_channel_cur); \n");
	html_tag("		} \n");
	//Antennes
#ifdef _WRM100_N_SELECT
	html_tag("		JsChangeNAntenne(form, false); \n");
#endif
	//datarate
	html_tag("		loc_rate_cur = form.rate.value;  \n");
	html_tag("		ResetBoite(form.rate); \n");
	html_tag("		SetBoiteDataRate(form.rate, loc_rate_cur); \n");
	//powertx
	html_tag("		if(false == JsChangePowerTx(form, false)) \n");
	html_tag("		{ \n");
#ifdef _WRM100_ABG_SELECT
	html_tag("			form.power.value = %d; \n",POWER_TX_802_11ABG_MIN);
#endif
#ifdef _WRM100_N_SELECT
	html_tag("			form.power.value = %d; \n",POWER_TX_802_11ABGN_MIN);
#endif
	html_tag("			alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_puissance_configuree_au_minimum);
	html_tag("		} \n");
	//Intervalle de garde
	html_tag("		JsDisplayIntervalGuard(form); \n");
	//Channel width
	html_tag("		JSChangeTextResultChannelSpectrumWidth(form); \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("} \n");/*JsChangeMode802_11x*/

#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Fonction javascript : JSChangeDualSSID
		//*************************************
		html_tag("function JSChangeDualSSID(form) \n");
		html_tag("{ \n");
		html_tag("	with(document) \n");
		html_tag("	{ \n");
		html_tag("		if(true == form.dualssid.checked) \n"); 
		html_tag("		{ \n");
		html_tag("			form.secondssid.disabled = false; \n");
		html_tag("		} \n");
		html_tag("		else \n");
		html_tag("		{ \n");
		html_tag("			form.secondssid.disabled = true; \n");
		html_tag("		} \n");
		html_tag("	} \n");
		html_tag("	return true; \n");
		html_tag("} \n");/*JsChangeIntervalGuard*/
	}
#endif
	
	//Fonction javascript : JsChangeIntervalGuard
	//*************************************
	html_tag("function JsChangeIntervalGuard(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_rate_cur; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	//datarate
	html_tag("		loc_rate_cur = form.rate.value;  \n");
	html_tag("		ResetBoite(form.rate); \n");
	html_tag("		SetBoiteDataRate(form.rate, loc_rate_cur); \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("} \n");/*JsChangeIntervalGuard*/
	
	//Fonction javascript : JsDisplayIntervalGuard
	//*************************************
	html_tag("function JsDisplayIntervalGuard(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_k; \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var loc_mode802; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	  )
	{
	html_tag("		loc_mode802 = Number(form.mode802.value); \n");
	//si mode 11abg
	html_tag("		if((true == JsIsMode80211ag(loc_mode802))|| \n");
	html_tag("		   (true == JsIsMode80211b(loc_mode802))) \n");
	html_tag("		{ \n");
	html_tag("			getElementById(\"TR_GUARD_INTERVAL\").style.display=\"none\";  \n");
	html_tag("		} \n");

	//si mode 11nht20
	html_tag("		if(true == JsIsMode80211nht20(loc_mode802)) \n");
	html_tag("		{ \n");
	//Modif by VuHai
	//html_tag("			form.guardInt.selectedIndex = %d; \n",GUARD_INTERVAL_LONG);
	//html_tag("			form.guardInt.disabled = true; \n");
	html_tag("			form.guardInt.disabled = false; \n");
	//Fin modif by VuHai
	html_tag("			getElementById(\"TR_GUARD_INTERVAL\").style.display=\"\";  \n");
	html_tag("		} \n");

	//si mode 11nht40
	html_tag("		if((true == JsIsMode80211nht40(loc_mode802))|| \n");
	html_tag("		   (true == JsIsMode80211ac(loc_mode802))) \n");
	html_tag("		{ \n");
	html_tag("			form.guardInt.disabled = false; \n");
	html_tag("			getElementById(\"TR_GUARD_INTERVAL\").style.display=\"\";  \n");
	html_tag("		} \n");
	}
	else //MODE_RADIO_MODEM_MONITOR
	{
		html_tag("				getElementById(\"TR_GUARD_INTERVAL\").style.display=\"none\";  \n");
	}
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("} \n");/*JsDisplayIntervalGuard*/
	
	//Fonction javascript : JsChangeModeSecurity
	//*************************************
	html_tag("function JsChangeModeSecurity(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_wep;\n");
	html_tag("	var loc_wpa; \n");
	html_tag("	var loc_psk_eap; \n");
	html_tag("	var loc_eap_tls; \n");
	html_tag("	loc_wep = false; \n"); //init
	html_tag("	loc_wpa = false; \n"); //init
	html_tag("	loc_psk_eap = false; \n"); //init
	html_tag("	loc_eap_tls = false; \n"); //init
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.secuMode.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_SECURITE_WIFI_AUCUN);
	html_tag("				break; \n");
	html_tag("			case %d: \n",MODE_SECURITE_WIFI_WEP);
	html_tag("				loc_wep = true;\n");
	html_tag("				JSChangeTextWepKeyType(form);\n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				loc_wpa = true;\n");
	html_tag("				loc_psk_eap = true;\n");
	html_tag("				JsChangeWPAauthentication(form);\n");
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("				if((%d == Number(form.wpaAuth.value))&&\n",WPA_AUTHENTIFICATION_EAP);
		html_tag("				   (%d == Number(form.eapMethod.value))\n",EAP_METHOD__TLS);
		html_tag("				  )\n");
		html_tag("				{ \n");
		html_tag("					loc_eap_tls = true; \n");
		html_tag("				} \n");
	}
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	}\n");
	html_tag("	var elmt = document.getElementsByTagName(\"TR\"); \n");
	html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++) \n");
	html_tag("	{\n");
	html_tag("		if(\"TR_WEP_SECU\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_wep)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if(\"TR_WPA_SECU\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_wpa)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
	html_tag("			}\n");
	html_tag("			else\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if((\"TR_WPA_PSK\" == elmt[loc_i_i].className) || (\"TR_WPA_EAP\" == elmt[loc_i_i].className)) \n");
	html_tag("		{\n");
	html_tag("			if(false == loc_psk_eap)\n");
	html_tag("			{\n");
	html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
	html_tag("			}\n");
	html_tag("		}\n");
	html_tag("		if(\"TR_WPA_EAP_TLS\" == elmt[loc_i_i].className) \n");
	html_tag("		{\n");
	html_tag("			if(true == loc_eap_tls)\n");
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
	html_tag("}\n"); /*JsChangeModeSecurity*/

	//Fonction javascript : JsChangeChannelMode
	//*************************************
	html_tag("function JsChangeChannelMode(form) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.channelMode.value))  \n");
	html_tag("		{  \n");
	html_tag("			case %d: \n",TYPE_SELECTION_CANAL_ISO);
	html_tag("				getElementById(\"TR_CHANNEL_ISO_FREQ\").style.display=\"\";  \n");
	html_tag("				getElementById(\"TR_CHANNEL_MULTI_FREQ\").style.display=\"none\";  \n");
	html_tag("			break; \n");
	html_tag("			case %d: \n",TYPE_SELECTION_CANAL_MULTI);
	html_tag("				getElementById(\"TR_CHANNEL_ISO_FREQ\").style.display=\"none\";  \n");
	html_tag("				getElementById(\"TR_CHANNEL_MULTI_FREQ\").style.display=\"\";  \n");
	html_tag("				break;  \n");
	html_tag("			case %d: \n",TYPE_SELECTION_CANAL_AUTO);
	html_tag("				getElementById(\"TR_CHANNEL_ISO_FREQ\").style.display=\"none\";  \n");
	html_tag("				getElementById(\"TR_CHANNEL_MULTI_FREQ\").style.display=\"none\";  \n");
	html_tag("				break;  \n");
	html_tag("			default:  \n");
	html_tag("				break;  \n");
	html_tag("		}  \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("} \n");/*JsChangeChannelMode*/

	//Fonction javascript : JsIsChannelForMode80211
	//*************************************
	html_tag("function JsIsChannelForMode80211(loc_mode802, flags_channel) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("			switch(loc_mode802) \n");
	html_tag("			{ \n");
	html_tag("				case %d: \n",MODE_WIFI_802_11G);
	html_tag("					if(flags_channel & %d) \n",(1 << BIT0_FLAG_CHANNEL_2GHZ));
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d:\n",MODE_WIFI_802_11B);
	html_tag("					if(flags_channel & %d) \n",(1 << BIT0_FLAG_CHANNEL_2GHZ));
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11A);
	html_tag("					if(flags_channel & %d) \n",(1 << BIT1_FLAG_CHANNEL_5GHZ));
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NGHT20);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT0_FLAG_CHANNEL_2GHZ));
	html_tag("					  (flags_channel & %d) \n",(1 << BIT2_FLAG_CHANNEL_HT20));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NGHT40PLUS);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT0_FLAG_CHANNEL_2GHZ));
	html_tag("					  (flags_channel & %d) \n",(1 << BIT3_FLAG_CHANNEL_HT40PLUS));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NGHT40MINUS);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT0_FLAG_CHANNEL_2GHZ));
	html_tag("					  (flags_channel & %d) \n",(1 << BIT4_FLAG_CHANNEL_HT40MINUS));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NGHT40);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT0_FLAG_CHANNEL_2GHZ));
	html_tag("					   ((flags_channel & %d)|| \n",(1 << BIT4_FLAG_CHANNEL_HT40MINUS));
	html_tag("					    (flags_channel & %d)) \n",(1 << BIT3_FLAG_CHANNEL_HT40PLUS));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NAHT20);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT1_FLAG_CHANNEL_5GHZ));
	html_tag("					  (flags_channel & %d) \n",(1 << BIT2_FLAG_CHANNEL_HT20));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NAHT40PLUS);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT1_FLAG_CHANNEL_5GHZ));
	html_tag("					  (flags_channel & %d) \n",(1 << BIT3_FLAG_CHANNEL_HT40PLUS));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NAHT40MINUS);
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT1_FLAG_CHANNEL_5GHZ));
	html_tag("					  (flags_channel & %d) \n",(1 << BIT4_FLAG_CHANNEL_HT40MINUS));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11NAHT40);
	html_tag("				case %d: \n",MODE_WIFI_802_11ACHT80);//VuHai FixMe
	html_tag("					if((flags_channel & %d)&& \n",(1 << BIT1_FLAG_CHANNEL_5GHZ));
	html_tag("					   ((flags_channel & %d)|| \n",(1 << BIT4_FLAG_CHANNEL_HT40MINUS));
	html_tag("					    (flags_channel & %d)) \n",(1 << BIT3_FLAG_CHANNEL_HT40PLUS));
	html_tag("					 ) \n");
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				default: \n");
	html_tag("					break;\n");
	html_tag("			} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsIsChannelForMode80211*/
	
	//Fonction javascript : JsCreateSelectChannel
	//*************************************
	html_tag("function JsCreateSelectChannel(loc_index, loc_canal_courant) \n");
	html_tag("{ \n");
	html_tag("	var loc_tab_canal=[");
	for(loc_u16_i=0;loc_u16_i<NB_MAX_CHANNEL;loc_u16_i++)
	{
		html_tag("[%d,\"%d\",%d],",
				 s_html_list_freq.s_channel[loc_u16_i].u16_ieee,
				 s_html_list_freq.s_channel[loc_u16_i].u16_freq_MHz,
				 s_html_list_freq.s_channel[loc_u16_i].u16_flags);
	}
	html_tag("]; \n");
	html_tag("	var loc_index_selected = 0; \n");
	html_tag("	var loc_cpt = 0; \n");
	html_tag("	var loc_mode802; \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var loc_i; \n");
	html_tag("	var loc_tmp; \n");

	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_mode802 = Number(form.mode802.value); \n");
	html_tag("		loc_nom_variable = \"form.ch\"+loc_index; \n");
	html_tag("		if(loc_index > 0) \n");
	html_tag("		{ \n");
	html_tag("			eval(loc_nom_variable).options[loc_cpt] = new Option(\"%s\", %d); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_inactif_m,
			 CHANNEL_RADIO_DISABLED);
	html_tag("			if(%d == loc_canal_courant) \n",CHANNEL_RADIO_DISABLED);
	html_tag("			{ \n");
	html_tag("				loc_index_selected = loc_cpt; \n");
	html_tag("			} \n");
	html_tag("			loc_cpt ++; \n");
	html_tag("		} \n");
	html_tag("		for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_CHANNEL);
	html_tag("		{ \n");
	html_tag("			if(true == JsIsChannelForMode80211(loc_mode802, loc_tab_canal[loc_i][2])) \n");
	html_tag("			{ \n");
	html_tag("				if(loc_tab_canal[loc_i][0] != %d) \n",CHANNEL_RADIO_DISABLED);
	html_tag("				{ \n");
	html_tag("					loc_tmp=loc_tab_canal[loc_i][1]+\"MHz - CH=\"+loc_tab_canal[loc_i][0]; \n");
	html_tag("					eval(loc_nom_variable).options[loc_cpt] = new Option(loc_tmp, loc_tab_canal[loc_i][0]); \n");
	html_tag("					if(loc_tab_canal[loc_i][0] == loc_canal_courant) \n");
	html_tag("					{ \n");
	html_tag("						loc_index_selected = loc_cpt; \n");
	html_tag("					} \n");
	html_tag("					loc_cpt ++; \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("		eval(loc_nom_variable).length = loc_cpt;  \n");
	html_tag("		eval(loc_nom_variable).selectedIndex = loc_index_selected;  \n");
	html_tag("		eval(loc_nom_variable).disabled = false;  \n");
	html_tag("	} \n");
	html_tag("} \n"); /*JsCreateSelectChannel*/

	//Fonction javascript : JsPrintHtmlChannel
	//*************************************
	html_tag("function JsPrintHtmlChannel(loc_index, loc_canal_courant) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		document.writeln('<SELECT name=\"ch'+loc_index+'\"> '); \n");
	html_tag("		JsCreateSelectChannel(loc_index, loc_canal_courant); \n");
	html_tag("		document.writeln('</select> '); \n");
	html_tag("	} \n");
	html_tag("} \n");

	//Fonction javascript : JsIsMode80211ag
	//*************************************
	html_tag("function JsIsMode80211ag(loc_mode802) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(loc_mode802) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_WIFI_802_11G);
	html_tag("			case %d: \n",MODE_WIFI_802_11A);
	html_tag("				loc_result = true; \n");
	html_tag("				break;\n");
	html_tag("			default: \n");
	html_tag("				break;\n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsIsMode80211ag*/

	//Fonction javascript : JsIsMode80211b
	//*************************************
	html_tag("function JsIsMode80211b(loc_mode802) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(loc_mode802) \n");
	html_tag("		{ \n");
	html_tag("			case %d:\n",MODE_WIFI_802_11B);
	html_tag("				loc_result = true; \n");
	html_tag("				break;\n");
	html_tag("			default: \n");
	html_tag("				break;\n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsIsMode80211b*/
	
	//Fonction javascript : JsIsMode80211nht20
	//*************************************
	html_tag("function JsIsMode80211nht20(loc_mode802) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(loc_mode802) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_WIFI_802_11NAHT20);
	html_tag("			case %d: \n",MODE_WIFI_802_11NGHT20);
	html_tag("				loc_result = true; \n");
	html_tag("				break;\n");
	html_tag("			default: \n");
	html_tag("				break;\n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsIsMode80211nht20*/

	//Fonction javascript : JsIsMode80211nht40
	//*************************************
	html_tag("function JsIsMode80211nht40(loc_mode802) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(loc_mode802) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_WIFI_802_11NGHT40PLUS);
	html_tag("			case %d: \n",MODE_WIFI_802_11NGHT40MINUS);
	html_tag("			case %d: \n",MODE_WIFI_802_11NGHT40);
	html_tag("			case %d: \n",MODE_WIFI_802_11NAHT40PLUS);
	html_tag("			case %d: \n",MODE_WIFI_802_11NAHT40MINUS);
	html_tag("			case %d: \n",MODE_WIFI_802_11NAHT40);
	html_tag("				loc_result = true; \n");
	html_tag("				break;\n");
	html_tag("			default: \n");
	html_tag("				break;\n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsIsMode80211nht40*/


	//Fonction javascript : JsIsMode80211ac
	//*************************************
	html_tag("function JsIsMode80211ac(loc_mode802) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		switch(loc_mode802) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_WIFI_802_11ACHT20);
	html_tag("			case %d: \n",MODE_WIFI_802_11ACHT40);
	html_tag("			case %d: \n",MODE_WIFI_802_11ACHT80);
	html_tag("				loc_result = true; \n");
	html_tag("				break;\n");
	html_tag("			default: \n");
	html_tag("				break;\n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsIsMode80211ac*/
	
#ifdef _WRM100_N_SELECT
	//Fonction javascript : JsChangeNAntenne
	//*************************************
	html_tag("function JsChangeNAntenne(form, flag_change_Antenne) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = true; \n");
	html_tag("	var loc_mode802; \n");
	html_tag("	var loc_rate; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		loc_mode802 = Number(form.mode802.value); \n");
	if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	  )
	{
		//Test fonction du mode / debit
		html_tag("		loc_rate = Number(form.rate.value); \n");

		html_tag("		if(true == flag_change_Antenne)  \n");
		html_tag("		{ \n");
		//datarate
		html_tag("			ResetBoite(form.rate); \n");
		html_tag("			SetBoiteDataRate(form.rate, loc_rate); \n");
		html_tag("			loc_rate = Number(form.rate.value); \n"); //MAj si necessaire
		//powertx
		html_tag("			if(false == JsChangePowerTx(form, false)) \n");
		html_tag("			{ \n");
#ifdef _WRM100_ABG_SELECT
		html_tag("				form.power.value = %d; \n",POWER_TX_802_11ABG_MIN);
#endif
#ifdef _WRM100_N_SELECT
		html_tag("				form.power.value = %d; \n",POWER_TX_802_11ABGN_MIN);
#endif
		html_tag("				alert(\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_puissance_configuree_au_minimum);
		html_tag("			} \n");
		html_tag("		} \n");
		
		//si mode 11abg
		html_tag("		if((true == JsIsMode80211ag(loc_mode802))|| \n");
		html_tag("		   (true == JsIsMode80211b(loc_mode802))) \n");
		html_tag("		{ \n");
		//on force à 1 antenne
		html_tag("			form.ant_N.disabled = true; \n");
		html_tag("			if(%d != form.ant_N.selectedIndex) \n",N_SELECT_ANTENNE_1);
		html_tag("			{ \n");
		html_tag("				form.ant_N.selectedIndex = %d; \n",N_SELECT_ANTENNE_1);
		html_tag("				alert(\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_configuration_antenne_1);
		html_tag("			} \n");
		html_tag("		} \n");
		
		//si mode 11nht20
		html_tag("		if(true == JsIsMode80211nht20(loc_mode802)) \n");
		html_tag("		{ \n");
		html_tag("			form.ant_N.disabled = false; \n");
		html_tag("		} \n");
		
		//si mode 11nht40
		html_tag("		if(true == JsIsMode80211nht40(loc_mode802)) \n");
		html_tag("		{ \n");
		html_tag("			form.ant_N.disabled = false; \n");
		//test fonction debit: si MCS8 à MCS15, 1 ant non autorisée
		html_tag("			if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_MCS8, DATA_RATE_MCS15);
		html_tag("			{ \n");
		html_tag("				if(%d == form.ant_N.selectedIndex) \n",N_SELECT_ANTENNE_1);
		html_tag("				{ \n");
		html_tag("					alert (\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_configuration_antenne_non_autorisee);
		html_tag("					loc_result = false; \n");
		html_tag("				} \n");
		html_tag("			} \n");
		//test fonction debit: si MCS16 à MCS23, 1 ou 2 ant non autorisée
		html_tag("			if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_MCS16, DATA_RATE_MCS23);
		html_tag("			{ \n");
		html_tag("				if((%d == form.ant_N.selectedIndex)|| \n",N_SELECT_ANTENNE_1);
		html_tag("				(%d == form.ant_N.selectedIndex)) \n",N_SELECT_ANTENNES_1_ET_2);
		html_tag("				{ \n");
		html_tag("					alert (\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_configuration_antenne_non_autorisee);
		html_tag("					loc_result = false; \n");
		html_tag("				} \n");
		html_tag("			} \n");
		html_tag("		} \n");

		//si mode 11ac
		html_tag("		if(true == JsIsMode80211ac(loc_mode802)) \n");
		html_tag("		{ \n");
		html_tag("			form.ant_N.disabled = false; \n");
		//test fonction debit: si NSS1, 1 ant non autorisée
		html_tag("			if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_NSS1_MCS0, DATA_RATE_NSS1_MCS9);
		html_tag("			{ \n");
		html_tag("				if(%d == form.ant_N.selectedIndex) \n",N_SELECT_ANTENNE_1);
		html_tag("				{ \n");
		html_tag("					alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration_antenne_non_autorisee);
		html_tag("					loc_result = false; \n");
		html_tag("				} \n");
		html_tag("			} \n");
		//test fonction debit: si NSS2, 1 ou 2 ant non autorisée
		html_tag("			if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_NSS2_MCS0, DATA_RATE_NSS2_MCS9);
		html_tag("			{ \n");
		html_tag("				if((%d == form.ant_N.selectedIndex)|| \n",N_SELECT_ANTENNE_1);
		html_tag("				(%d == form.ant_N.selectedIndex)) \n",N_SELECT_ANTENNES_1_ET_2);
		html_tag("				{ \n");
		html_tag("					alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration_antenne_non_autorisee);
		html_tag("					loc_result = false; \n");
		html_tag("				} \n");
		html_tag("			} \n");
		html_tag("		} \n");
	}
	else //MODE_RADIO_MODEM_MONITOR
	{
		//si mode 11abg
		html_tag("		if((true == JsIsMode80211ag(loc_mode802))|| \n");
		html_tag("		   (true == JsIsMode80211b(loc_mode802))) \n");
		html_tag("		{ \n");
		//on force à 1 antenne
		html_tag("			form.ant_N.disabled = true; \n");
		html_tag("			if(%d != form.ant_N.selectedIndex) \n",N_SELECT_ANTENNE_1);
		html_tag("			{ \n");
		html_tag("				form.ant_N.selectedIndex = %d; \n",N_SELECT_ANTENNE_1);
		html_tag("				alert(\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_configuration_antenne_1);
		html_tag("			} \n");
		html_tag("		} \n");
		
		//si mode 11nht20
		html_tag("		if(true == JsIsMode80211nht20(loc_mode802)) \n");
		html_tag("		{ \n");
		html_tag("			form.ant_N.disabled = false; \n");
		html_tag("		} \n");
		
		//si mode 11nht40
		html_tag("		if(true == JsIsMode80211nht40(loc_mode802)) \n");
		html_tag("		{ \n");
		html_tag("			form.ant_N.disabled = false; \n");
		html_tag("		} \n");

		//si mode 11ac
		html_tag("		if(true == JsIsMode80211ac(loc_mode802)) \n");
		html_tag("		{ \n");
		html_tag("			form.ant_N.disabled = false; \n");
		html_tag("		} \n");
	}
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsChangeNAntenne*/
#endif
	
#ifdef _WRM100_ABG_SELECT
	//Fonction javascript : JsChangePowerTx
	//*************************************
	html_tag("function JsChangePowerTx(form, flag_test_box) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = true; \n");
	html_tag("	var loc_mode802; \n");
	html_tag("	var loc_power_cur; \n");
	html_tag("	var loc_powermin= %d;\n",POWER_TX_802_11ABG_MIN);
	html_tag("	var loc_powermax=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_WIFI_802_11;loc_u8_i++)
	{
		html_tag("%d,",u8Get_ABG_PowerTxMax(loc_u8_i));
	}
	html_tag("]; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_mode802 = Number(form.mode802.value); \n");
	html_tag("		if (true == flag_test_box) \n");
	html_tag("		{ \n");
	html_tag("			if (false == isInteger(form.power,loc_powermin,loc_powermax[loc_mode802])) \n");
	html_tag("			{ \n");
	html_tag("				form.power.value = form.power.defaultValue; \n");
	html_tag("				loc_result = false; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			loc_power_cur = Number(form.power.value); \n");
	html_tag("			if((loc_powermin <= loc_power_cur)&& \n");
	html_tag("			   (loc_power_cur <= loc_powermax[loc_mode802]) \n");
	html_tag("			  ) \n");
	html_tag("			{ \n");
	html_tag("				loc_result = false; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result;\n");
	html_tag("} \n");/*JsChangePowerTx*/
#endif

#ifdef _WRM100_N_SELECT
	//Fonction javascript : JsChangePowerTx
	//*************************************
	html_tag("function JsChangePowerTx(form, flag_test_box) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = true; \n");
	html_tag("	var loc_mode802; \n");
	html_tag("	var loc_rate; \n");
	html_tag("	var loc_antenne; \n");
	html_tag("	var loc_power_cur; \n");
	html_tag("	var loc_powermin=%d; \n",POWER_TX_802_11ABGN_MIN);
	html_tag("	var loc_powermax=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_WIFI_802_11;loc_u8_i++)
	{
		html_tag("[");
		for(loc_u16_i=0;loc_u16_i<NB_MAX_DATA_RATE;loc_u16_i++)
		{
			html_tag("[");
			for(loc_u8_k=0;loc_u8_k<NB_MAX_N_SELECT_ANTENNES;loc_u8_k++)
			{
				html_tag("%d,",u8Get_N_PowerTxMax(loc_u8_i,(u8sod)loc_u16_i,loc_u8_k));
			}			 
			html_tag("],");
		}
		html_tag("],\n");
	}
	html_tag("]; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_mode802 = Number(form.mode802.value); \n");
	html_tag("		loc_rate = Number(form.rate.value); \n");
	html_tag("		loc_antenne = form.ant_N.selectedIndex; \n");
	html_tag("		if (true == flag_test_box) \n");
	html_tag("		{ \n");
	html_tag("			if (false == isInteger(form.power,loc_powermin,loc_powermax[loc_mode802][loc_rate][loc_antenne])) \n");
	html_tag("			{ \n");
	html_tag("				form.power.value = loc_powermax[loc_mode802][loc_rate][loc_antenne]; \n");
	html_tag("				loc_result = false; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			loc_power_cur = Number(form.power.value); \n");
	html_tag("			if((loc_powermin <= loc_power_cur)&& \n");
	html_tag("			   (loc_power_cur <= loc_powermax[loc_mode802][loc_rate][loc_antenne]) \n");
	html_tag("			  ) \n");
	html_tag("			{ \n");
	html_tag("				;  \n");//OK
	html_tag("			} \n");
	html_tag("			else \n");
	html_tag("			{ \n");
	html_tag("				loc_result = false; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result;\n");
	html_tag("} \n");/*JsChangePowerTx*/
#endif

	//Fonction javascript : JsTestDataRate
	//*************************************
	html_tag("function JsTestDataRate(loc_rate, loc_mode802, loc_select_antennes) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	var loc_tab_rate_vs_mode80211=[");
	for(loc_u16_i=0;loc_u16_i<NB_MAX_DATA_RATE;loc_u16_i++)
	{
		html_tag("%d,",T_TB_VAL.pt_definition_rate[loc_u16_i].u8_mode80211_valid);
	}
	html_tag("]; \n");
	
	html_tag("	with(document) \n");
	html_tag("	{  \n");

	//si mode 11b
	html_tag("		if(true == JsIsMode80211b(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			if(loc_tab_rate_vs_mode80211[loc_rate] & %d) \n",M80211_VALID_11B);
	html_tag("			{ \n");
	html_tag("				loc_result = true; \n");
	html_tag("			} \n");
	html_tag("		} \n");

	//si mode 11ag
	html_tag("		if(true == JsIsMode80211ag(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			if(loc_tab_rate_vs_mode80211[loc_rate] & %d) \n",M80211_VALID_11AG);
	html_tag("			{ \n");
	html_tag("				loc_result = true; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	
#ifdef _WRM100_N_SELECT
	//si mode 11nht20
	html_tag("		if(true == JsIsMode80211nht20(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			if(loc_tab_rate_vs_mode80211[loc_rate] & %d) \n",M80211_VALID_11N);
	html_tag("			{ \n");
	html_tag("				if((%d == loc_rate)||  \n",DATA_RATE_AUTOMATIC);
	html_tag("				   ((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_MCS0, DATA_RATE_MCS7);
	html_tag("				  ) \n");
	html_tag("				{ \n");
	html_tag("					loc_result = true; \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("		} \n");

	//si mode 11nht40
	html_tag("		if(true == JsIsMode80211nht40(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			if(loc_tab_rate_vs_mode80211[loc_rate] & %d) \n",M80211_VALID_11N);
	html_tag("			{ \n");
	html_tag("				if((%d == loc_rate)||  \n",DATA_RATE_AUTOMATIC);
	html_tag("				   ((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_MCS0, DATA_RATE_MCS7);
	html_tag("				  ) \n");
	html_tag("				{ \n");
	html_tag("					loc_result = true; \n");
	html_tag("				} \n");
	/*html_tag("				else \n"); //DATA_RATE_MCS8 à DATA_RATE_MCS15
	html_tag("				{ \n");
	html_tag("					if(%d != loc_select_antennes) \n",N_SELECT_ANTENNE_1);
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("				} \n");*/

						//test fonction debit: si MCS8 à MCS15, 1 ant non autorisée
	html_tag("				if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_MCS8, DATA_RATE_MCS15);
	html_tag("				{ \n");
	html_tag("					if(%d != loc_select_antennes) \n",N_SELECT_ANTENNE_1);
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("				} \n");
						//test fonction debit: si MCS16 à MCS23, 1 ou 2 ant non autorisée
	html_tag("				if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_MCS16, DATA_RATE_MCS23);
	html_tag("				{ \n");
	html_tag("					if((%d != loc_select_antennes)&& \n",N_SELECT_ANTENNE_1);
	html_tag("					(%d != loc_select_antennes)) \n",N_SELECT_ANTENNES_1_ET_2);
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("		} \n");

	//si mode 11ac
	html_tag("		if(true == JsIsMode80211ac(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			if(loc_tab_rate_vs_mode80211[loc_rate] & %d) \n",M80211_VALID_11AC);
	html_tag("			{ \n");
	html_tag("				if((%d == loc_rate)||  \n",DATA_RATE_AUTOMATIC);
	html_tag("				   ((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_NSS1_MCS0, DATA_RATE_NSS1_MCS9);
	html_tag("				  ) \n");
	html_tag("				{ \n");
	html_tag("					loc_result = true; \n");
	html_tag("				} \n");
						//test fonction debit: si NSS2 1 ant non autorisée
	html_tag("				if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_NSS2_MCS0, DATA_RATE_NSS2_MCS9);
	html_tag("				{ \n");
	html_tag("					if(%d != loc_select_antennes) \n",N_SELECT_ANTENNE_1);
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("				} \n");
						//test fonction debit: si NSS3, 1 ou 2 ant non autorisée
	html_tag("				if((%d <= loc_rate)&&(loc_rate <= %d))  \n",DATA_RATE_NSS3_MCS0, DATA_RATE_NSS3_MCS9);
	html_tag("				{ \n");
	html_tag("					if((%d != loc_select_antennes)&& \n",N_SELECT_ANTENNE_1);
	html_tag("					(%d != loc_select_antennes)) \n",N_SELECT_ANTENNES_1_ET_2);
	html_tag("					{ \n");
	html_tag("						loc_result = true; \n");
	html_tag("					} \n");
	html_tag("				} \n");
						//802.11AC ht20 ne support pas MCS9 
	html_tag("				if((%d == loc_rate)||(loc_rate == %d)||(loc_rate == %d))  \n",DATA_RATE_NSS1_MCS9, DATA_RATE_NSS2_MCS9, DATA_RATE_NSS3_MCS9);
	html_tag("				{ \n");
	html_tag("					if(%d == loc_mode802) \n",MODE_WIFI_802_11ACHT20);
	html_tag("					{ \n");
	html_tag("						loc_result = false; \n");
	html_tag("					} \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("		} \n");
#endif
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsTestDataRate*/


	//Fonction javascript : JsGetChDataRate
	//*************************************
	html_tag("function JsGetChDataRate(loc_idx_rate, loc_mode802, loc_guardInt) \n");
	html_tag("{ \n");
	html_tag("	var loc_ch_result = \"\"; \n");
	//Construction tableau des chaines définissant le débit
	//pour mode 11b
	html_tag("	var loc_ch_datarate_11b=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11B)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11B, GUARD_INTERVAL_LONG));
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11ag
	html_tag("	var loc_ch_datarate_11ag=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AG)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11A, GUARD_INTERVAL_LONG)); //ou MODE_WIFI_802_11G
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11nh20 long GI
	html_tag("	var loc_ch_datarate_11nh20_longGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11N)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11NAHT20, GUARD_INTERVAL_LONG)); //ou MODE_WIFI_802_11NGHT20
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");

	//pour mode 11nh20 short GI
	html_tag("	var loc_ch_datarate_11nh20_shortGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11N)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11NAHT20, GUARD_INTERVAL_SHORT)); //ou MODE_WIFI_802_11NGHT20
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11nh40 long GI
	html_tag("	var loc_ch_datarate_11nh40_longGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11N)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11NAHT40, GUARD_INTERVAL_LONG)); //ou MODE_WIFI_802_11NGHT40
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11nh40 short GI
	html_tag("	var loc_ch_datarate_11nh40_shortGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11N)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11NAHT40, GUARD_INTERVAL_SHORT)); //ou MODE_WIFI_802_11NGHT40
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");

	//pour mode 11ac20 long GI
	html_tag("	var loc_ch_datarate_11ac20_shortGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AC)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11ACHT20, GUARD_INTERVAL_LONG)); //ou MODE_WIFI_802_11NGHT20
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11ac20 short GI
	html_tag("	var loc_ch_datarate_11ac20_longGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AC)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11ACHT20, GUARD_INTERVAL_SHORT)); //ou MODE_WIFI_802_11NGHT20
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11ac40 long GI
	html_tag("	var loc_ch_datarate_11ac40_longGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AC)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11ACHT40, GUARD_INTERVAL_LONG)); //ou MODE_WIFI_802_11NGHT40
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11ac40 short GI
	html_tag("	var loc_ch_datarate_11ac40_shortGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AC)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11ACHT40, GUARD_INTERVAL_SHORT)); //ou MODE_WIFI_802_11NGHT40
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11ac80 long GI
	html_tag("	var loc_ch_datarate_11ac80_longGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AC)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11ACHT80, GUARD_INTERVAL_LONG)); //ou MODE_WIFI_802_11NGHT40
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	//pour mode 11ac80 short GI
	html_tag("	var loc_ch_datarate_11ac80_shortGi=[");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_DATA_RATE;loc_u8_i++)
	{
		if(T_TB_VAL.pt_definition_rate[loc_u8_i].u8_mode80211_valid & M80211_VALID_11AC)
		{
			strcpy(loc_ps8_chaine_debit, "");	//RAZ
			if(0 != strcmp(T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain, ""))
			{
				strcat(loc_ps8_chaine_debit, T_TB_VAL.pt_definition_rate[loc_u8_i].ps8_chain);
				strcat(loc_ps8_chaine_debit, " - ");
			}
			strcat(loc_ps8_chaine_debit, ps8GetChDataRate(loc_u8_i, u8_html_langue, MODE_WIFI_802_11ACHT80, GUARD_INTERVAL_SHORT)); //ou MODE_WIFI_802_11NGHT40
			html_tag("\"%s\",",loc_ps8_chaine_debit);
		}
		else
		{
			html_tag("\" \",");
		}
	}
	html_tag("]; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	//si mode 11b
	html_tag("		if(true == JsIsMode80211b(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			loc_ch_result = loc_ch_datarate_11b[loc_idx_rate]; \n");
	html_tag("		} \n");
	//si mode 11ag
	html_tag("		if(true == JsIsMode80211ag(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			loc_ch_result = loc_ch_datarate_11ag[loc_idx_rate]; \n");
	html_tag("		} \n");
#ifdef _WRM100_N_SELECT
	//si mode 11nht20
	html_tag("		if(true == JsIsMode80211nht20(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("				if(%d == loc_guardInt) \n",GUARD_INTERVAL_LONG);
	html_tag("				{ \n");
	html_tag("					loc_ch_result = loc_ch_datarate_11nh20_longGi[loc_idx_rate]; \n");
	html_tag("				} \n");
	html_tag("				else \n"); //GUARD_INTERVAL_SHORT
	html_tag("				{ \n");
	html_tag("					loc_ch_result = loc_ch_datarate_11nh20_shortGi[loc_idx_rate]; \n");
	html_tag("				} \n");
	html_tag("		} \n");
	//si mode 11nht40
	html_tag("		if(true == JsIsMode80211nht40(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("				if(%d == loc_guardInt) \n",GUARD_INTERVAL_LONG);
	html_tag("				{ \n");
	html_tag("					loc_ch_result = loc_ch_datarate_11nh40_longGi[loc_idx_rate]; \n");
	html_tag("				} \n");
	html_tag("				else \n"); //GUARD_INTERVAL_SHORT
	html_tag("				{ \n");
	html_tag("					loc_ch_result = loc_ch_datarate_11nh40_shortGi[loc_idx_rate]; \n");
	html_tag("				} \n");
	html_tag("		} \n");
	//si mode 11ac
	html_tag("		if(true == JsIsMode80211ac(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			switch(loc_mode802) \n");
	html_tag("			{ \n");
	html_tag("				case %d: \n",MODE_WIFI_802_11ACHT20);
	html_tag("					if(%d == loc_guardInt) \n",GUARD_INTERVAL_LONG);
	html_tag("					{ \n");
	html_tag("						loc_ch_result = loc_ch_datarate_11ac20_longGi[loc_idx_rate]; \n");
	html_tag("					} \n");
	html_tag("					else \n"); //GUARD_INTERVAL_SHORT
	html_tag("					{ \n");
	html_tag("						loc_ch_result = loc_ch_datarate_11ac20_shortGi[loc_idx_rate]; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11ACHT40);
	html_tag("					if(%d == loc_guardInt) \n",GUARD_INTERVAL_LONG);
	html_tag("					{ \n");
	html_tag("						loc_ch_result = loc_ch_datarate_11ac40_longGi[loc_idx_rate]; \n");
	html_tag("					} \n");
	html_tag("					else \n"); //GUARD_INTERVAL_SHORT
	html_tag("					{ \n");
	html_tag("						loc_ch_result = loc_ch_datarate_11ac40_shortGi[loc_idx_rate]; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				case %d: \n",MODE_WIFI_802_11ACHT80);
	html_tag("					if(%d == loc_guardInt) \n",GUARD_INTERVAL_LONG);
	html_tag("					{ \n");
	html_tag("						loc_ch_result = loc_ch_datarate_11ac80_longGi[loc_idx_rate]; \n");
	html_tag("					} \n");
	html_tag("					else \n"); //GUARD_INTERVAL_SHORT
	html_tag("					{ \n");
	html_tag("						loc_ch_result = loc_ch_datarate_11ac80_shortGi[loc_idx_rate]; \n");
	html_tag("					} \n");
	html_tag("					break;\n");
	html_tag("				default: \n");
	html_tag("					break;\n");
	html_tag("			} \n");
	html_tag("		} \n");
#endif
	html_tag("	} \n");
	html_tag("	return loc_ch_result; \n");
	html_tag("} \n");/*JsGetChDataRate*/
	
	//Fonction javascript : JsPrintHtmlDataRate
	//*************************************
	html_tag("function JsPrintHtmlDataRate(loc_rate_cur) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		document.writeln('<select name=\"rate\" size=\"1\" onchange=\"return(JsChangeDataRate(form))\"> '); \n");
	html_tag("		SetBoiteDataRate(form.rate, loc_rate_cur); \n");
	html_tag("		document.writeln('</select> '); \n");
	html_tag("	} \n");
	html_tag("} \n");/*JsPrintHtmlDataRate*/
	
	//Fonction javascript : SetBoiteDataRate
	//*************************************
	html_tag("function SetBoiteDataRate(boite, loc_rate_cur)  \n");
	html_tag("{ \n");
	html_tag("	var loc_indexrate; \n");
	html_tag("	var loc_mode802; \n");
	html_tag("	var loc_antenne; \n");
	html_tag("	var loc_cpt = 0; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		boite.disabled = false; \n");
	html_tag("		loc_mode802 = Number(form.mode802.value); \n");
#ifdef _WRM100_ABG_SELECT
	html_tag("		loc_antenne = form.ant_ABG_tx.selectedIndex; \n");
#endif
#ifdef _WRM100_N_SELECT
	html_tag("		loc_antenne = form.ant_N.selectedIndex; \n");
#endif
	//si mode 11b
	html_tag("		if(true == JsIsMode80211b(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			loc_cpt = 0; \n"); //RAZ
	html_tag("			for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_DATA_RATE);
	html_tag("			{ \n");
	html_tag("				if(true == JsTestDataRate(loc_i, loc_mode802, loc_antenne)) \n");
	html_tag("				{ \n");
	html_tag("					loc_ch_rate = JsGetChDataRate(loc_i, loc_mode802, %d);  \n",GUARD_INTERVAL_LONG);
	html_tag("					boite.options[loc_cpt] = new Option(loc_ch_rate, loc_i); \n");
	html_tag("					loc_cpt++; \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("			boite.length = loc_cpt; \n");
	html_tag("		} \n");
	//si mode 11ag
	html_tag("		if(true == JsIsMode80211ag(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			loc_cpt = 0; \n"); //RAZ
	html_tag("			for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_DATA_RATE);
	html_tag("			{ \n");
	html_tag("				if(true == JsTestDataRate(loc_i, loc_mode802, loc_antenne)) \n");
	html_tag("				{ \n");
	html_tag("					loc_ch_rate = JsGetChDataRate(loc_i, loc_mode802, %d);  \n",GUARD_INTERVAL_LONG);
	html_tag("					boite.options[loc_cpt] = new Option(loc_ch_rate, loc_i); \n");
	html_tag("					loc_cpt++; \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("			boite.length = loc_cpt; \n");
	html_tag("		} \n");
#ifdef _WRM100_N_SELECT
	//si mode 11n
	html_tag("		if((true == JsIsMode80211nht20(loc_mode802))|| \n");
	html_tag("		   (true == JsIsMode80211nht40(loc_mode802)) \n");
	html_tag("		  ) \n");
	html_tag("		{ \n");
	html_tag("			loc_cpt = 0; \n"); //RAZ
	html_tag("			for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_DATA_RATE);
	html_tag("			{ \n");
	html_tag("				if(true == JsTestDataRate(loc_i, loc_mode802, loc_antenne)) \n");
	html_tag("				{ \n");
	html_tag("					loc_ch_rate = JsGetChDataRate(loc_i, loc_mode802, Number(form.guardInt.value));  \n");
	html_tag("					boite.options[loc_cpt] = new Option(loc_ch_rate, loc_i); \n");
	html_tag("					loc_cpt++; \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("			boite.length = loc_cpt; \n");
	html_tag("		} \n");
	//si mode 11ac
	html_tag("		if(true == JsIsMode80211ac(loc_mode802)) \n");
	html_tag("		{ \n");
	html_tag("			loc_cpt = 0; \n"); //RAZ
	html_tag("			for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_DATA_RATE);
	html_tag("			{ \n");
	html_tag("				if(true == JsTestDataRate(loc_i, loc_mode802, loc_antenne)) \n");
	html_tag("				{ \n");
	html_tag("					loc_ch_rate = JsGetChDataRate(loc_i, loc_mode802, Number(form.guardInt.value));  \n");
	html_tag("					boite.options[loc_cpt] = new Option(loc_ch_rate, loc_i); \n");
	html_tag("					loc_cpt++; \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("			boite.length = loc_cpt; \n");
	html_tag("		} \n");
#endif
	html_tag("		loc_indexrate = optionValueIndexOf(boite,loc_rate_cur); \n");
	html_tag("		if(loc_indexrate < 0) \n"); //CONDITION: non trouvé
	html_tag("		{ \n");
	html_tag("			boite.selectedIndex = 0; \n");
	html_tag("			alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_debit_configure_en_automatique);
	html_tag("		} \n");
	html_tag("		else \n"); //CONDITION: valeur débit inchangée
	html_tag("		{ \n");
	html_tag("			boite.selectedIndex = loc_indexrate; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n"); /*SetBoiteDataRate*/
	
	//Fonction javascript : JsChangeDataRate
	//*************************************
	html_tag("function JsChangeDataRate(form) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
#ifdef _WRM100_ABG_SELECT
#endif	
#ifdef _WRM100_N_SELECT
	html_tag("		if(false == JsChangePowerTx(form, false)) \n");
	html_tag("		{ \n");
	html_tag("			form.power.value = %d; \n",POWER_TX_802_11ABGN_MIN);
	html_tag("			alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_puissance_configuree_au_minimum);
	html_tag("		} \n");
#endif
	html_tag("	} \n");
	html_tag("	return true;\n");
	html_tag("} \n"); /*JsChangeDataRate*/
	
	//Fonction javascript : JsReturnWepKeyLgValid
	//*************************************
	html_tag("function JsReturnWepKeyLgValid(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_lg_wep_valid = 0;");
	html_tag("	var loc_tab_lg_wep_key = [");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_WEP_KEY_LENGTH;loc_u8_i++)
	{
		html_tag("[");
		for(loc_u16_i=0;loc_u16_i<NB_MAX_KEY_TYPE;loc_u16_i++)
		{
			html_tag("%d,",T_TB_VAL.pu8_lg_wep_key[loc_u8_i][loc_u16_i]);
		}
		html_tag("],");
	}
	html_tag("]; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_lg_wep_valid = loc_tab_lg_wep_key[Number(form.wepKeyLg.value)][Number(form.wepKeyTp.value)];\n");
	html_tag("	} \n");
	html_tag("	return loc_lg_wep_valid;\n");
	html_tag("}\n");/*JsReturnWepKeyLgValid*/

	//Fonction javascript : JsChangeLgTypeWEPkey
	//*************************************
	html_tag("function JsChangeLgTypeWEPkey(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_length;\n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_length = JsReturnWepKeyLgValid(form); \n");
	html_tag("		for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_IDX_WEP_KEY);
	html_tag("		{ \n");
	html_tag("			nom_variable = \"form.wepkey\"+loc_i; \n");
	html_tag("			eval(nom_variable).value = \"\";  \n");
	html_tag("			eval(nom_variable).maxLength = loc_length; \n");
	html_tag("		} \n");
	html_tag("		JSChangeTextWepKeyType(form); \n");
	html_tag("	} \n");
	html_tag("	return true;\n");
	html_tag("}\n");/*JsReturnWepKeyLgValid*/
	
	
	//Fonction javascript : JSChangeTextWepKeyType
	//*************************************
	html_tag("function JSChangeTextWepKeyType(form) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.wepKeyLg.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d:\n",WEP_KEY_LENGTH_64BIT);
	html_tag("				switch(Number(form.wepKeyTp.value)) \n");
	html_tag("				{ \n");
	html_tag("					case %d: \n",KEY_TYPE_HEXA);
	html_tag("						getElementById(\"SPAN_WEP_KEY_TYPE\").innerHTML = \"%s\"; \n",
			pt_tb_msg[u8_html_langue].ps8_msg_info_saisie_cle_WEP[WEP_KEY_LENGTH_64BIT][KEY_TYPE_HEXA]);
	html_tag("						break; \n");
	html_tag("					case %d: \n",KEY_TYPE_ASCII);
	html_tag("						getElementById(\"SPAN_WEP_KEY_TYPE\").innerHTML = \"%s\"; \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_info_saisie_cle_WEP[WEP_KEY_LENGTH_64BIT][KEY_TYPE_ASCII]);
	html_tag("						break; \n");
	html_tag("					default: \n");
	html_tag("						break; \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",WEP_KEY_LENGTH_128BIT);
	html_tag("				switch(Number(form.wepKeyTp.value)) \n");
	html_tag("				{ \n");
	html_tag("					case %d: \n",KEY_TYPE_HEXA);
	html_tag("						getElementById(\"SPAN_WEP_KEY_TYPE\").innerHTML = \"%s\"; \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_info_saisie_cle_WEP[WEP_KEY_LENGTH_128BIT][KEY_TYPE_HEXA]);
	html_tag("						break; \n");
	html_tag("					case %d: \n",KEY_TYPE_ASCII);
	html_tag("						getElementById(\"SPAN_WEP_KEY_TYPE\").innerHTML = \"%s\"; \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_info_saisie_cle_WEP[WEP_KEY_LENGTH_128BIT][KEY_TYPE_ASCII]);
	html_tag("						break; \n");
	html_tag("					default: \n");
	html_tag("						break; \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");

	html_tag("		}\n");
	html_tag("	return true;\n");
	html_tag("}\n");/*JSChangeTextWepKeyType*/

	//Fonction javascript : JsChangeDefaultWEPkey
	//*************************************
	html_tag("function JsChangeDefaultWEPkey(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = true; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_result = JsChangeWEPkey(form, Number(form.wepKeyCx.value)); \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsChangeDefaultWEPkey*/

	//Fonction javascript : JsChangeWEPkey
	//*************************************
	html_tag("function JsChangeWEPkey(form, loc_i_numKey) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = true; \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var loc_key; \n");
	html_tag("	var loc_lg_valid; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_lg_valid = JsReturnWepKeyLgValid(form); \n");
	html_tag("		loc_nom_variable = \"form.wepkey\"+loc_i_numKey; \n");
	html_tag("		if(isValidText(eval(loc_nom_variable),false,true)) \n");
	html_tag("		{ \n");
	html_tag("			loc_key = eval(loc_nom_variable).value; \n");
	html_tag("			if (loc_key.length != loc_lg_valid)  \n");//CONDITION: saisie d'une clé à longueur non valide
	html_tag("			{ \n");
	html_tag("				loc_result = false; \n");
	html_tag("			} \n");
	html_tag("			else \n");
	html_tag("			{ \n");
	html_tag("				switch(Number(form.wepKeyTp.value))  \n");
	html_tag("				{  \n");
	html_tag("					case %d: \n",KEY_TYPE_HEXA);
	html_tag("						var loc_got = eval(loc_nom_variable).value.match (/^\\s*([0-9a-fA-F]+)\\s*$/); \n");
	html_tag("						if (!loc_got) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("						break;  \n");
	html_tag("					case %d: \n",KEY_TYPE_ASCII);
	html_tag("						break;  \n");
	html_tag("					default:  \n");
	html_tag("						break;  \n");
	html_tag("				}  \n");
	html_tag("			} \n");
	html_tag("			if(false == loc_result) \n");
	html_tag("			{ \n");
	html_tag("				alert(\"%s (%s \"+ (loc_i_numKey+1) + \")\"); \n",
			pt_tb_msg[u8_html_langue].ps8_msg_la_valeur_de_la_cle_est_invalide,
			pt_tb_msg[u8_html_langue].ps8_msg_cle_WEP);
	html_tag("				eval(loc_nom_variable).value = \"\"; \n");
	html_tag("			}	 \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsChangeWEPkey*/

	//Fonction javascript : JSDisplayWEPKey
	//*************************************
	html_tag("function JSDisplayWEPKey(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var loc_ch_type =\"\"; \n");
	html_tag("	var loc_valeur; \n");
	html_tag("	var loc_i; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		for(loc_i=0;loc_i<%d;loc_i++) \n",NB_MAX_IDX_WEP_KEY);
	html_tag("		{ \n");
	html_tag("			loc_nom_variable = \"form.wepkey\"+loc_i; \n");
	html_tag("			loc_valeur = eval(loc_nom_variable).value; \n");
	html_tag("			if(true == form.wepKeyDisplay.checked) \n");
	html_tag("			{ \n");
	html_tag("				loc_ch_type = \"text\"; \n");
	html_tag("			} \n");
	html_tag("			else \n");
	html_tag("			{ \n");
	html_tag("				loc_ch_type = \"password\"; \n");
	html_tag("			} \n");
	html_tag("			getElementById('ID_DIV_WEPKEY'+loc_i).innerHTML = '<input type='+loc_ch_type+' size=\"%d\" maxlength=\"%d\" name=\"wepkey'+loc_i+'\" value=\"\" onchange=\"return(JsChangeWEPkey(form,'+loc_i+'))\">'; \n",
			 KEY_WEP_VALUE_LENGTH_MAX+1,
			 KEY_WEP_VALUE_LENGTH_MAX);
	html_tag("			eval(loc_nom_variable).value = loc_valeur; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("} \n");/*JSDisplayWEPKey*/

	
	//Fonction javascript : JsChangeWPAauthentication
	//*************************************
	html_tag("function JsChangeWPAauthentication(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_i_i; \n");
	html_tag("	var loc_psk = false; \n");
	html_tag("	var loc_eap = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.wpaAuth.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",WPA_AUTHENTIFICATION_PSK);
	html_tag("				loc_psk = true; \n");
	html_tag("				JsChangePSKtype(form); \n");
	html_tag("				JSChangeTextPSKType(form); \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",WPA_AUTHENTIFICATION_EAP);
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("				JsChangeEapMethod(form); \n");
	}
	html_tag("				loc_eap = true; \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("		var elmt = document.getElementsByTagName(\"TR\"); \n");
	html_tag("		for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++)  \n");
	html_tag("		{ \n");
	html_tag("			if(\"TR_WPA_PSK\" == elmt[loc_i_i].className)  \n");
	html_tag("			{ \n");
	html_tag("				if(true == loc_psk) \n");
	html_tag("				{ \n");
	html_tag("					elmt[loc_i_i].style.display = \"\";  \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					elmt[loc_i_i].style.display = \"none\";  \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("			if(\"TR_WPA_EAP\" == elmt[loc_i_i].className)  \n");
	html_tag("			{ \n");
	html_tag("				if(true == loc_eap) \n");
	html_tag("				{ \n");
	html_tag("					elmt[loc_i_i].style.display = \"\";  \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					elmt[loc_i_i].style.display = \"none\";  \n");
	html_tag("				} \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("}\n");/*JsChangeWPAauthentication*/ 


	//Fonction javascript : JsChangePSKtype
	//*************************************
	html_tag("function JsChangePSKtype(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = true; \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_nom_variable = \"form.wpakey\"; \n");
	html_tag("		if(false == JsTestPSKLgValid(form)) \n");
	html_tag("		{ \n");
	html_tag("			eval(loc_nom_variable).value = \"\"; \n");
	html_tag("			loc_result = false; \n");
	html_tag("		} \n");
	html_tag("		switch(Number(form.pskTp.value))  \n");
	html_tag("		{  \n");
	html_tag("			case %d: \n",KEY_TYPE_HEXA);
	html_tag("				eval(loc_nom_variable).maxLength = %d; \n",LG_MAX_PRESHARED_KEY_WPA_HEXA);
	html_tag("				break;  \n");
	html_tag("			case %d: \n",KEY_TYPE_ASCII);
	html_tag("				eval(loc_nom_variable).maxLength = %d; \n",LG_MAX_PRESHARED_KEY_WPA_ASCII);
	html_tag("				break;  \n");
	html_tag("			default:  \n");
	html_tag("				break;  \n");
	html_tag("		} \n");
	html_tag("			JSChangeTextPSKType(form); \n");
	html_tag("	} \n");
	html_tag("		return loc_result; \n");
	html_tag("}\n");/*JsChangePSKtype*/ 

	//Fonction javascript : JsTestPSKLgValid
	//*************************************
	html_tag("function JsTestPSKLgValid(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	var loc_lg_key; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_lg_key = form.wpakey.value.length; \n");
	html_tag("		switch(Number(form.pskTp.value))  \n");
	html_tag("		{  \n");
	html_tag("			case %d: \n",KEY_TYPE_HEXA);
	html_tag("				if(%d == loc_lg_key) \n",LG_MAX_PRESHARED_KEY_WPA_HEXA);
	html_tag("				{ \n");
	html_tag("					loc_result = true; \n");
	html_tag("				} \n");
	html_tag("				break;  \n");
	html_tag("			case %d: \n",KEY_TYPE_ASCII);
	html_tag("				if((%d <= loc_lg_key) && (loc_lg_key <=%d)) \n",
			LG_MIN_PRESHARED_KEY_WPA,
			 LG_MAX_PRESHARED_KEY_WPA_ASCII);
	html_tag("				{ \n");
	html_tag("					loc_result = true; \n");
	html_tag("				} \n");
	html_tag("				break;  \n");
	html_tag("			default:  \n");
	html_tag("				break;  \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsTestPSKLgValid*/

	//Fonction javascript : JsTestPSKLgValid
	//*************************************
	html_tag("function JSChangeTextPSKType(form)  \n");
	html_tag("{  \n");
	html_tag("	with(document)  \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(form.pskTp.value))  \n");
	html_tag("		{  \n");
	html_tag("			case %d: \n",KEY_TYPE_HEXA);
	html_tag("				getElementById(\"SPAN_WPA_PSK_TYPE\").innerHTML = \"%s\";  \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_info_saisie_PSK[KEY_TYPE_HEXA]);
	html_tag("				break;  \n");
	html_tag("			case %d: \n",KEY_TYPE_ASCII);
	html_tag("				getElementById(\"SPAN_WPA_PSK_TYPE\").innerHTML = \"%s\";  \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_info_saisie_PSK[KEY_TYPE_ASCII]);
	html_tag("				break;  \n");
	html_tag("			default:  \n");
	html_tag("				break;  \n");
	html_tag("		} \n");
	html_tag("	}   \n");
	html_tag("} \n");/*JSChangeTextWepKeyType*/

	//Fonction javascript : JsChangeWPAkey
	//*************************************
	html_tag("function JsChangeWPAkey(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_result; \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	loc_result = true; //init \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_nom_variable = \"form.wpakey\"; \n");
	html_tag("		if(isValidText(eval(loc_nom_variable),false,true)) \n");
	html_tag("		{ \n");
	html_tag("			if(false == JsTestPSKLgValid(form)) \n");
	html_tag("			{ \n");
	html_tag("				loc_result = false; \n");
	html_tag("			} \n");
	html_tag("			else \n");
	html_tag("			{ \n");
	html_tag("				switch(Number(form.pskTp.value))  \n");
	html_tag("				{  \n");
	html_tag("					case %d: \n",KEY_TYPE_HEXA);
	html_tag("						var loc_got = eval(loc_nom_variable).value.match (/^\\s*([0-9a-fA-F]+)\\s*$/); \n");
	html_tag("						if (!loc_got) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false; \n");
	html_tag("						} \n");
	html_tag("						break;  \n");
	html_tag("					case %d: \n",KEY_TYPE_ASCII);
	html_tag("						break;  \n");
	html_tag("					default:  \n");
	html_tag("						break;  \n");
	html_tag("				}  \n");
	html_tag("			} \n");
	html_tag("			if(false == loc_result) \n");
	html_tag("			{ \n");
	html_tag("				alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_la_valeur_de_la_cle_est_invalide);
	html_tag("				eval(loc_nom_variable).value = \"\"; \n");
	html_tag("			}	 \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsChangeWPAkey*/

	//Fonction javascript : JSDisplayWPAKey
	//*************************************
	html_tag("function JSDisplayWPAKey(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var loc_ch_type =\"\"; \n");
	html_tag("	var loc_valeur; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_nom_variable = \"form.wpakey\"; \n");
	html_tag("		loc_valeur = eval(loc_nom_variable).value; \n");
	html_tag("		if(true == form.wpaKeyDisplay.checked) \n");
	html_tag("		{ \n");
	html_tag("			loc_ch_type = \"text\"; \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			loc_ch_type = \"password\"; \n");
	html_tag("		} \n");
	html_tag("		getElementById('ID_DIV_WPAKEY').innerHTML = '<input type='+loc_ch_type+' size=\"%d\" maxlength=\"%d\" name=\"wpakey\" value=\"\" onchange=\"return(JsChangeWPAkey(form))\">'; \n",
			 LG_MAX_PRESHARED_WPA_TOTAL,
			 LG_MAX_PRESHARED_WPA_TOTAL);
	html_tag("		eval(loc_nom_variable).value = loc_valeur; \n");
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("}\n");/*JSDisplayWPAKey*/

	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Fonction javascript : JsChangeEapMethod
		//*************************************
		html_tag("function JsChangeEapMethod(form) \n");
		html_tag("{ \n");
		html_tag("	var loc_eap_tls; \n");
		html_tag("	loc_eap_tls = false; \n"); //init
		html_tag("	with(document) \n");
		html_tag("	{ \n");
		html_tag("		switch(Number(form.eapMethod.value)) \n");
		html_tag("		{ \n");
		html_tag("			case %d: \n",EAP_METHOD__TLS);
		html_tag("				getElementById(\"TR_EAPUSERPWD\").style.display=\"none\";  \n");
		html_tag("				getElementById(\"TR_EAPFILECA\").style.display=\"\";  \n");
		html_tag("				getElementById(\"TR_EAPFILECERTCLT\").style.display=\"\";  \n");
		html_tag("				getElementById(\"TR_EAPPRIVKEYPWD\").style.display=\"\";  \n");
		html_tag("				getElementById(\"TR_EAPREMOVECERT\").style.display=\"\";  \n");
		html_tag("				loc_eap_tls = true; \n");
		html_tag("				break;  \n");
		html_tag("			default:  \n");
		html_tag("				getElementById(\"TR_EAPUSERPWD\").style.display=\"\";  \n");
		html_tag("				getElementById(\"TR_EAPFILECA\").style.display=\"none\";  \n");
		html_tag("				getElementById(\"TR_EAPFILECERTCLT\").style.display=\"none\";  \n");
		html_tag("				getElementById(\"TR_EAPPRIVKEYPWD\").style.display=\"none\";  \n");
		html_tag("				getElementById(\"TR_EAPREMOVECERT\").style.display=\"none\";  \n");
		html_tag("				break;  \n");
		html_tag("		}  \n");
		html_tag("	} \n");
		html_tag("	var elmt = document.getElementsByTagName(\"TR\"); \n");
		html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++) \n");
		html_tag("	{\n");
		html_tag("		if(\"TR_WPA_EAP_TLS\" == elmt[loc_i_i].className) \n");
		html_tag("		{\n");
		html_tag("			if(true == loc_eap_tls)\n");
		html_tag("			{\n");
		html_tag("				elmt[loc_i_i].style.display = \"\"; \n");
		html_tag("			}\n");
		html_tag("			else\n");
		html_tag("			{\n");
		html_tag("				elmt[loc_i_i].style.display = \"none\"; \n");
		html_tag("			}\n");
		html_tag("		}\n");
		html_tag("	}\n");
		
		html_tag("	return true; \n");
		html_tag("}\n");/*JsChangeEapMethod*/
	}
	

	//Fonction javascript : JsChangeEapReauthPeriod
	//*************************************
	html_tag("function JsChangeEapReauthPeriod(form, loc_min, loc_max) \n");
	html_tag("{ \n");
	html_tag("	var loc_result = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if(%d == Number(form.eapReauthPd.value))\n",EAP_REAUTH_PERIOD_DISABLED);
	html_tag("		{ \n");
	html_tag("			loc_result = true; \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			if(true == isInteger(form.eapReauthPd, loc_min, loc_max))\n");
	html_tag("			{ \n");
	html_tag("				loc_result = true; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_result; \n");
	html_tag("} \n");/*JsChangeEapReauthPeriod*/
	
			
	//Fonction javascript : JSDisplayEAPKey
	//*************************************
	html_tag("function JSDisplayEAPKey(form) \n");
	html_tag("{ \n");
	switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
			html_tag("	var loc_nom_variable; \n");
			html_tag("	var loc_ch_type =\"\"; \n");
			html_tag("	var loc_valeur; \n");
			html_tag("	with(document) \n");
			html_tag("	{ \n");
			html_tag("		if(true == form.eapKeyDisplay.checked) \n");
			html_tag("		{ \n");
			html_tag("			loc_ch_type = \"text\"; \n");
			html_tag("		} \n");
			html_tag("		else \n");
			html_tag("		{ \n");
			html_tag("			loc_ch_type = \"password\"; \n");
			html_tag("		} \n");
			//keyRadius
			html_tag("		loc_nom_variable = \"form.keyRadius\"; \n");
			html_tag("		loc_valeur = eval(loc_nom_variable).value; \n");
			html_tag("		getElementById('ID_DIV_KEYRADIUS').innerHTML = '<input type='+loc_ch_type+' size=\"%d\" maxlength=\"%d\" name=\"keyRadius\" value=\"\" onchange=\"return(isValidText(this,true,true))\">';\n", //isValidText: espace interdit
					 LG_MAX_SHARED_RADIUS,
					 LG_MAX_SHARED_RADIUS);
			html_tag("		eval(loc_nom_variable).value = loc_valeur; \n");
			html_tag("	} \n");
			break;
		case MODE_RADIO_MODEM_STATION:
			html_tag("	var loc_nom_variable; \n");
			html_tag("	var loc_ch_type =\"\"; \n");
			html_tag("	var loc_valeur; \n");
			html_tag("	with(document) \n");
			html_tag("	{ \n");
			html_tag("		if(true == form.eapKeyDisplay.checked) \n");
			html_tag("		{ \n");
			html_tag("			loc_ch_type = \"text\"; \n");
			html_tag("		} \n");
			html_tag("		else \n");
			html_tag("		{ \n");
			html_tag("			loc_ch_type = \"password\"; \n");
			html_tag("		} \n");
			//eapuserpwd
			html_tag("		loc_nom_variable = \"form.eapUserPwd\"; \n");
			html_tag("		loc_valeur = eval(loc_nom_variable).value; \n");
			html_tag("		getElementById('ID_DIV_EAPUSERPWD').innerHTML = '<input type='+loc_ch_type+' size=\"%d\" maxlength=\"%d\" name=\"eapUserPwd\" value=\"\" onchange=\"return(isValidText(this,true,true))\">';\n", //isValidText: espace interdit
					 LG_MAX_EAP_USER_PASSWORD,
					 LG_MAX_EAP_USER_PASSWORD);
			html_tag("		eval(loc_nom_variable).value = loc_valeur; \n");
			//eapPrivKeyPwd
			html_tag("		loc_nom_variable = \"form.eapPrivKeyPwd\"; \n");
			html_tag("		loc_valeur = eval(loc_nom_variable).value; \n");
			html_tag("		getElementById('ID_DIV_EAPPRIVKEYPWD').innerHTML = '<input type='+loc_ch_type+' size=\"%d\" maxlength=\"%d\" name=\"eapPrivKeyPwd\" value=\"\" onchange=\"return(isValidText(this,true,true))\">';\n", //isValidText: espace interdit
					 LG_MAX_PRIVATE_KEY_PWD,
					 LG_MAX_PRIVATE_KEY_PWD);
			html_tag("		eval(loc_nom_variable).value = loc_valeur; \n");
			html_tag("	} \n");
			break;
		case MODE_RADIO_MODEM_MONITOR:
			break;
		default:
			break;
	}
	html_tag("	return true; \n");
	html_tag("} \n");/*JSDisplayEAPKey*/

	//Fonction javascript : JsDisplayRadioModem
	//*************************************
	html_tag("function JsDisplayRadioModem(form) \n");
	html_tag("{ \n");
	html_tag("	var loc_i_i; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	if(MODE_RADIO_MODEM_MONITOR == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("	getElementById(\"TR_SSID_PRIMARY\").style.display=\"none\";  \n");
		html_tag("	getElementById(\"TR_POWER\").style.display=\"none\";  \n");
		html_tag("	getElementById(\"TR_RATE\").style.display=\"none\";  \n");
		html_tag("	var elmt = document.getElementsByTagName(\"TR\"); \n");
		html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++) \n");
		html_tag("	{\n");
		html_tag("		if(\"TR_SECU\" == elmt[loc_i_i].className) \n");
		html_tag("		{\n");
		html_tag("			elmt[loc_i_i].style.display = \"none\"; \n");
		html_tag("		}\n");
		html_tag("	}\n");
#ifdef _WRM100_ABG_SELECT
		html_tag("	getElementById(\"TR_ANT_TX\").style.display=\"none\";  \n");
#endif
	}
	else //MODE_RADIO_MODEM_STATION ou MODE_RADIO_MODEM_ACCESS_POINT
	{
		html_tag("	getElementById(\"TR_SSID_PRIMARY\").style.display=\"\";  \n");
		html_tag("	getElementById(\"TR_POWER\").style.display=\"\";  \n");
		html_tag("	getElementById(\"TR_RATE\").style.display=\"\";  \n");
		html_tag("	var elmt = document.getElementsByTagName(\"TR\"); \n");
		html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++) \n");
		html_tag("	{\n");
		html_tag("		if(\"TR_SECU\" == elmt[loc_i_i].className) \n");
		html_tag("		{\n");
		html_tag("			elmt[loc_i_i].style.display = \"\"; \n");
		html_tag("		}\n");
		html_tag("	}\n");
#ifdef _WRM100_ABG_SELECT
		html_tag("	getElementById(\"TR_ANT_TX\").style.display=\"\";  \n");
#endif
	}
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("} \n");/*JsDisplayRadioModem*/
	
	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript(form)  \n");
	html_tag("{  \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		JsDisplayRadioModem(form); \n");
	html_tag("		JsChangeChannelMode(form); \n");
	html_tag("		JsChangeModeSecurity(form); \n");
	html_tag("		JSChangeTextResultChannelSpectrumWidth(form); \n");
	html_tag("		JsDisplayIntervalGuard(form); \n");
#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("		JSChangeDualSSID(form); \n");
	}
#endif
#ifdef _WRM100_ABG_SELECT
	if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	  )
	{
		html_tag("		getElementById(\"TR_ANT_TX\").style.display=\"\";  \n");
	}
	else //MODE_RADIO_MODEM_MONITOR
	{
		html_tag("		getElementById(\"TR_ANT_TX\").style.display=\"none\";  \n");
	}
#endif
#ifdef _WRM100_N_SELECT
	html_tag("		JsChangeNAntenne(form, false); \n");
#endif
	html_tag("	} \n");
	html_tag("	return true; \n");
	html_tag("}  \n");/*StartJavaScript*/

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("	var	loc_canal_valid = false; \n"); //INIT
	html_tag("	var loc_nom_variable; \n");
	html_tag("	var	loc_i_ch; \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//test si un canal est configuré dans le mode multi-frequence
		html_tag("		if((%d == i_numForm)||(%d == i_numForm))  \n",
				 FORM_SUCONFIGWIRELESSBASIC_VALID_1,FORM_SUCONFIGWIRELESSBASIC_VALID_ALL);
		html_tag("		{  \n");
		html_tag("			if(%d == Number(form.channelMode.value))  \n",
				TYPE_SELECTION_CANAL_MULTI);
		html_tag("			{  \n");
		html_tag("				for(loc_i_ch=1;loc_i_ch<(%d+1);loc_i_ch++)  \n",
				 NB_MAX_MULTI_CANAUX);
		html_tag("				{  \n");
		html_tag("					loc_nom_variable = \"form.ch\"+loc_i_ch; \n");
		html_tag("					if(%d != Number(eval(loc_nom_variable).value))  \n",CHANNEL_RADIO_DISABLED);
		html_tag("					{  \n");
		html_tag("						loc_canal_valid = true;  \n");
		html_tag("					}  \n");
		html_tag("				}  \n");
		html_tag("				if(false == loc_canal_valid)  \n"); //CONDITION: aucun canal sélectionné
		html_tag("				{  \n");
		html_tag("					loc_result = false;\n");
		html_tag("					alert(\"%s\"); \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_configurez_un_canal_valide);
		html_tag("				}  \n");
		html_tag("			}  \n");
		html_tag("		} \n");

		html_tag("		if(%d == i_numForm)  \n",
				 FORM_SUCONFIGWIRELESSBASIC_REMOVE_CERTIFICAT);
		html_tag("		{  \n");
		html_tag("			if(\"%s\" != form.eapRemoveCert.value)  \n",
				 CH_CERTIFICAT_NO_SELECTED);
		html_tag("			{  \n");
		html_tag("				if (false == confirm(\"%s\") )\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_etes_vous_sur_de_supprimer_ce_certificat);
		html_tag("				{ \n");
		html_tag("					loc_result = false;\n");
		html_tag("					form.eapRemoveCert.value=\"%s\";  \n",
				 CH_CERTIFICAT_NO_SELECTED);
		html_tag("				} \n");
		html_tag("			}  \n");
		html_tag("			else \n");
		html_tag("			{ \n");
		html_tag("				loc_result = false;\n");
		html_tag("			} \n");

		html_tag("		}  \n");
		
	}
	html_tag("		switch(Number(form.secuMode.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_SECURITE_WIFI_AUCUN);
	html_tag("				break; \n");
	html_tag("			case %d: \n",MODE_SECURITE_WIFI_WEP);
	//on vérifie que la clé WEP sélectionnée est bien codée
	html_tag("				if(false == JsChangeDefaultWEPkey(form)) \n");
	html_tag("				{ \n");
	html_tag("					loc_result = false;\n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n"); //WPA
	html_tag("				switch(Number(form.wpaAuth.value)) \n");
	html_tag("				{ \n");
	html_tag("					case %d: \n",WPA_AUTHENTIFICATION_PSK);
	//on vérifie que la clé PSK est bien codée
	html_tag("						if(false == JsChangeWPAkey(form)) \n");
	html_tag("						{ \n");
	html_tag("							loc_result = false;\n");
	html_tag("						} \n");
	html_tag("						break; \n");
	html_tag("					case %d: \n",WPA_AUTHENTIFICATION_EAP);
	if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//on vérifie que l'adresse IP du serveur RADIUS est non nulle
		html_tag("						if(false == validAddr(form.adrIpRadius, true)) \n");
		html_tag("						{  \n");
		html_tag("							loc_result = false;  \n");
		html_tag("						}  \n");
	}
	html_tag("						break; \n");
	html_tag("					default: \n");
	html_tag("						break; \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag( "	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigWirelessBasic*/

//=====================================================================================
// Fonction		: SUConfigWirelessBasic
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: Wireless (Basic)
//				"URL=SUConfigWirelessBasic"
//=====================================================================================
void SUConfigWirelessBasic(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_WIRELESS_BASIC_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_i;
	u8sod	loc_u8_display_rate;
	s8sod	loc_ps8_chaine_debit[UI_TAILLE_MAX_MESSAGE];
	S_STRUCT_SYST_FILE loc_ps_certificat_file[NB_MAX_CERTIFICATS];
	u8sod	loc_u8_certificat_CA_cfg_present;
	u8sod	loc_u8_certificat_Clt_cfg_present;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;

	loc_u8_result_test = FALSE; //INIT
	loc_u8_display_rate = FALSE;	//INIT
	strcpy(loc_ps8_chaine_debit, "");	//INIT
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
	{
		RazSystFile(&loc_ps_certificat_file[loc_u8_i]); //INIT
	}
	loc_u8_certificat_CA_cfg_present = FALSE;	//INIT
	loc_u8_certificat_Clt_cfg_present = FALSE;	//INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigWirelessBasic");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigWirelessBasic&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_WIRELESS_BASIC_RESULTS));

		// Décodage de la requete
		if (!form_decode(s_FormConfigWirelessBasicFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGWIRELESSBASIC)
			{
				if((FORM_SUCONFIGWIRELESSBASIC_VALID_1 == loc_u8_numForm) ||
				   (FORM_SUCONFIGWIRELESSBASIC_VALID_ALL == loc_u8_numForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on leve le semaphore
					if(	(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))&&
						(TRUE == u8FillConfigWifi(&s_html_cfg_eqpmt))
					  )
					{
						if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
						   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						  )
						{
							strcpy(s_html_cfg_eqpmt.s_wifi.ps8_ssid_primary, loc_s_results.ps8_ssid);
						}
#ifdef _WRM100_N_SELECT
						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							if(0 == strcmp(loc_s_results.ps8_dual_ssid, CHECKBOX_VALUE_CHECKED))
							{
								s_html_cfg_eqpmt.s_wifi.u8_dual_ssid = TRUE;
							}
							else
							{
								s_html_cfg_eqpmt.s_wifi.u8_dual_ssid = FALSE;
							}
							if(TRUE == s_html_cfg_eqpmt.s_wifi.u8_dual_ssid)
							{
								strcpy(s_html_cfg_eqpmt.s_wifi.ps8_ssid_secondary, loc_s_results.ps8_second_ssid);
							}
						}
#endif
						
						if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s_html_cfg_eqpmt.s_wifi.u8_masquage_ssid = (u8sod)atoi(loc_s_results.ps8_mask_ssid);
						}
						
						s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x = (u8sod)atoi(loc_s_results.ps8_mode_802_11);
						
						
						if(TRUE == u8IsMode80211n(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))
						{
							if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
							   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
							  )
							{
								s_html_cfg_eqpmt.s_wifi.u8_11n_guard_interval = (u8sod)atoi(loc_s_results.ps8_guardInt);
							}
						}
						if(TRUE == u8IsMode80211ac(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))//Add by VuHai
						{
							if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
							   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
							  )
							{
								s_html_cfg_eqpmt.s_wifi.u8_11n_guard_interval = (u8sod)atoi(loc_s_results.ps8_guardInt);
							}
						}

#ifdef _WRM100_N_SELECT
						if((TRUE == u8IsMode80211ag(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))||
						   (TRUE == u8IsMode80211b(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x))
						  )//CONDITION: valable pour 11a/11g et 11b
						{
							{
								//on force à une antenne
								s_html_cfg_eqpmt.s_wifi.u8_ant_N_selection = N_SELECT_ANTENNE_1;
							}
						}
#endif
						
						if(s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)
						{
							s_html_cfg_eqpmt.s_wifi.u8_channel_spectrum_width = T_TB_VAL.pt_definition_mode_wifi[s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x].u8_channelspectrumwidth;
						}
						s_html_cfg_eqpmt.s_wifi.u16_iso_canal_radio = (u16sod)atoi(loc_s_results.ps8_canal_iso);
						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s_html_cfg_eqpmt.s_wifi.u8_type_selection_canal = (u8sod)atoi(loc_s_results.ps8_mode_canal);
							if(TRUE == T_TB_VAL.pt_definition_radio_modem[s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem].pu8_flag_mode_canal[s_html_cfg_eqpmt.s_wifi.u8_type_selection_canal])
							{
								for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
								{
									s_html_cfg_eqpmt.s_wifi.pu16_multi_canal_radio[loc_u8_i] = (u16sod)atoi(loc_s_results.ps8_canal_multi[loc_u8_i]);
								}
							}
						}
						
						if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
						   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						  )
						{
							
#ifdef _WRM100_ABG_SELECT
							//Antenne TX
							s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_tx_selection = (u8sod)atoi(loc_s_results.ps8_ABG_antenne_tx);
							//Antenne RX
							s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_rx_selection = (u8sod)atoi(loc_s_results.ps8_ABG_antenne_rx);
#endif
#ifdef _WRM100_N_SELECT
							//Antenne TX/RX
							s_html_cfg_eqpmt.s_wifi.u8_ant_N_selection = (u8sod)atoi(loc_s_results.ps8_N_antenne);
#endif
							s_html_cfg_eqpmt.s_wifi.u8_power_tx = (u8sod)atoi(loc_s_results.ps8_puissance_tx);
							s_html_cfg_eqpmt.s_wifi.u8_data_rate = (u8sod)atoi(loc_s_results.ps8_data_rate);
						}
						else //MODE_RADIO_MODEM_MONITOR
						{
#ifdef _WRM100_ABG_SELECT
							//Antenne RX
							s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_rx_selection = (u8sod)atoi(loc_s_results.ps8_ABG_antenne_rx);
							//Antenne TX = RX (en mode monitor)
							s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_tx_selection = s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_rx_selection;
#endif
#ifdef _WRM100_N_SELECT
							//Antenne TX/RX
							s_html_cfg_eqpmt.s_wifi.u8_ant_N_selection = (u8sod)atoi(loc_s_results.ps8_N_antenne);
#endif
						}
						
						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s_html_cfg_eqpmt.s_wifi.s8_seuil_rx = (s8sod)atoi(loc_s_results.ps8_seuil_rx);
						}
#if VERSION_WRM100_DEMO
#else
						if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s_html_cfg_eqpmt.s_wifi.u16_nb_max_associated_stations = (u16sod)atoi(loc_s_results.ps8_max_station);
						}
#endif

#ifdef _WRM100_N_SELECT
						if(FALSE == u8TestCfg_N_AckTimeout(&s_html_cfg_eqpmt))
						{
							s_html_cfg_eqpmt.s_wifi.u16_protcl_N_ACK_timeout = WF_N_ACK_TIMEOUT_DEFAULT;
						}
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

				if((FORM_SUCONFIGWIRELESSBASIC_VALID_2 == loc_u8_numForm) ||
				   (FORM_SUCONFIGWIRELESSBASIC_VALID_ALL == loc_u8_numForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on leve le semaphore
					if(	(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))&&
						  (TRUE == u8FillConfigWifi(&s_html_cfg_eqpmt))
					  )
					{
						if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
						   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						  )
						{
							s_html_cfg_eqpmt.s_wifi.u8_mode_securite_wifi = (u8sod)atoi(loc_s_results.ps8_mode_securite);
							switch(s_html_cfg_eqpmt.s_wifi.u8_mode_securite_wifi)
							{
								case MODE_SECURITE_WIFI_AUCUN:
									break;
								case MODE_SECURITE_WIFI_WEP:
									s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_key_length = (u8sod)atoi(loc_s_results.ps8_wep_key_lg);
									s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_wep_key_type = (u8sod)atoi(loc_s_results.ps8_wep_key_type);
									for(loc_u8_i=0;loc_u8_i<NB_MAX_IDX_WEP_KEY;loc_u8_i++)
									{
										strcpy(s_html_cfg_eqpmt.s_wifi.s_wep_security.ps8_key_value[loc_u8_i] , loc_s_results.ps8_wep_key_value[loc_u8_i]);
									}
									s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_index_key_default = (u8sod)atoi(loc_s_results.ps8_wep_key_default);
									s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_authentification = (u8sod)atoi(loc_s_results.ps8_wep_authentification);
									break;
								default: //WPA
									s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_authentification = (u8sod)atoi(loc_s_results.ps8_wpa_authentification);
									s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_wpa_key_type = (u8sod)atoi(loc_s_results.ps8_psk_type);
									if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
									{
										s_html_cfg_eqpmt.s_wifi.s_wpa_security.u32_gp_key_update_interval = (u32sod)atoi(loc_s_results.ps8_wpa_update_interval);
									}
									switch(s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_authentification)
									{
										case WPA_AUTHENTIFICATION_PSK:
											strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_pre_shared_key, loc_s_results.ps8_wpa_key_psk_value);
											break;
										case WPA_AUTHENTIFICATION_EAP:
											if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
											{
												s_html_cfg_eqpmt.s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIpRadius, &loc_u8_ret);
												s_html_cfg_eqpmt.s_wifi.s_wpa_security.s_server_radius.u16_radius_port = (u16sod)atoi(loc_s_results.ps8_portRadius);
												strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared, loc_s_results.ps8_keyRadius);
												s_html_cfg_eqpmt.s_wifi.s_wpa_security.u32_eap_reauth_period = (u32sod)atoi(loc_s_results.ps8_eap_reauth_period);
											}
											else //MODE_RADIO_MODEM_STATION
											{
												s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_eap_method = (u8sod)atoi(loc_s_results.ps8_eap_method);
												strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_identity, loc_s_results.ps8_eap_identity);
#if PARAMETERS_RADIUS_NOT_USED
												strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_user_name, loc_s_results.ps8_eap_user_name);
#endif											
												strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_user_password, loc_s_results.ps8_eap_user_password);
												if(0 != strcmp(loc_s_results.ps8_eap_file_certificat_authority, CH_CERTIFICAT_NO_SELECTED))
												{
													strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_authority, loc_s_results.ps8_eap_file_certificat_authority);
												}
												else
												{
													strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_authority, "");
												}
												if(0 != strcmp(loc_s_results.ps8_eap_file_certificat_client, CH_CERTIFICAT_NO_SELECTED))
												{
													strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_client, loc_s_results.ps8_eap_file_certificat_client);
												}
												else
												{
													strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_client, "");
												}
												strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_private_key_password, loc_s_results.ps8_eap_private_key_password);
											}
											break;
										default:
											break;
									}
									break; /*default*/
							}

							if(TRUE==u8TestConfigWifi(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigWifi(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGWIRELESSBASIC_REMOVE_CERTIFICAT == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on leve le semaphore
					if((TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))&&
					   (TRUE == u8FillConfigWifi(&s_html_cfg_eqpmt))
					  )
					{
						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							if(0 != strcmp(loc_s_results.ps8_eap_remove_file_certificat, CH_CERTIFICAT_NO_SELECTED))
							{
								if(0==strcmp(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_authority, loc_s_results.ps8_eap_remove_file_certificat))
								{
									strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_authority, "");
								}
								if(0==strcmp(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_client, loc_s_results.ps8_eap_remove_file_certificat))
								{
									strcpy(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_client, "");
								}

								if(TRUE==u8TestConfigWifi(&s_html_cfg_eqpmt))
								{
									if(TRUE == u8EditConfigWifi(&s_html_cfg_eqpmt))
									{
										CmdSystem_Generique("rm -rf %s%s\n",PATH_DIR__ETC_CERTIFICATS,loc_s_results.ps8_eap_remove_file_certificat);
										CmdSystem_Generique("rm -rf %s%s\n",PATH_DIR__FLASH_CONFIG_CERTIFICATS,loc_s_results.ps8_eap_remove_file_certificat);
										loc_u8_result_test = TRUE;
									}
								}
							}
							else//CONDITION: aucun certificat à supprimer
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
				PreparePageCfgInProgress("SUConfigWirelessBasic");
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
	//Lecture des certificats
	if(FALSE == u8CmdSystem_ListFileInDirectory(PATH_DIR__ETC_CERTIFICATS, loc_ps_certificat_file, NB_MAX_CERTIFICATS))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on leve le semaphore
	if(FALSE == u8FillListFreqFile(&s_html_list_freq))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}//Modif by VuHai
	s32Lock_Release(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on relache le sem
	
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
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("	tr.TR_SECU {\n");
	html_tag("}\n");
	html_tag("	tr.TR_WEP_SECU {\n");
	html_tag("}\n");
	html_tag("	tr.TR_WPA_SECU {\n");
	html_tag("}\n");
	html_tag("	tr.TR_WPA_PSK {\n");
	html_tag("}\n");
	html_tag("	tr.TR_WPA_EAP {\n");
	html_tag("}\n");
	html_tag("	tr.TR_WPA_EAP_TLS {\n");
	html_tag("}\n");
	html_tag("</STYLE>\n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigWirelessBasic");	//pour la fonction Actualiser

	JSNumCheck();
	JSTextCheck();
	JSIPCheck();

	proc_JavaScript_SUConfigWirelessBasic();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigWirelessBasic");//permet d'avoir la bonne page de rafraichit!!
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
			 "				<td><ul><li><B>%s</B></li></ul></td> \n"
			 "				<td>&nbsp;&nbsp;</td> \n"
			 "				<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=SUConfigWirelessAdv\" target=\"frame_c\">%s</a></li></ul></td> \n"
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
	
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//SSID
	html_tag("		<tr id=TR_SSID_PRIMARY> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_SSID);
	html_tag("			<td><input type=\"text\" size=%d maxlength=%d name=\"ssid\" value=\"%s\" onchange=\"return(isValidText(this,false,false))\"></td> \n", //champ vide non autorisé
			 NB_MAX_CHAINE_SSID + 15, //size (rmq:+15 pour pouvoir lire la totalité de la chaine de caractères
			 NB_MAX_CHAINE_SSID, //maxlength
			 s_html_cfg_eqpmt.s_wifi.ps8_ssid_primary);
	html_tag("		</tr> \n");
#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Activation SSID secondaire
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_activation_ssid_secondaire);
		html_tag("			<td><input name=\"dualssid\" type=\"checkbox\" %s value=\"%s\" onClick=\"return(JSChangeDualSSID(form))\"></td> \n",
				 (TRUE == s_html_cfg_eqpmt.s_wifi.u8_dual_ssid)? "checked" : "",
				 CHECKBOX_VALUE_CHECKED);
		html_tag("		</tr> \n");
		//SSID secondaire
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_SSID_secondaire);
		html_tag("			<td><input type=\"text\" size=%d maxlength=%d name=\"secondssid\" value=\"%s\" onchange=\"return(isValidText(this,true,false))\"></td> \n", //champ vide non autorisé
				 NB_MAX_CHAINE_SSID + 15, //size (rmq:+15 pour pouvoir lire la totalité de la chaine de caractères
				 NB_MAX_CHAINE_SSID, //maxlength
				 s_html_cfg_eqpmt.s_wifi.ps8_ssid_secondary);
		html_tag("		</tr> \n");
	}
#endif
	
	if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//SSID Mask
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_masquer_ssid);
		html_tag("			<td>");
		html_tag("<input type=\"radio\" %s name=\"ssidMask\" value=\"%d\">%s",
				 ((FALSE == s_html_cfg_eqpmt.s_wifi.u8_masquage_ssid) ? "checked" : ""),
				 FALSE,
				 pt_tb_msg[u8_html_langue].ps8_msg_non);
		html_tag("&nbsp;&nbsp; \n");
		html_tag("<input type=\"radio\" %s name=\"ssidMask\" value=\"%d\">%s",
				 ((TRUE == s_html_cfg_eqpmt.s_wifi.u8_masquage_ssid) ? "checked" : ""),
				 TRUE,
				 pt_tb_msg[u8_html_langue].ps8_msg_oui);
		html_tag("</td> \n");
		html_tag("		</tr> \n");
	}
	
	//Mode 802.11x
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_802_11);
	html_tag("			<td><SCRIPT language=JavaScript>JsPrintHtmlMode80211(%d);</SCRIPT></td> \n",
			 s_html_cfg_eqpmt.s_wifi.u8_mode_802_11x);
	html_tag("		</tr> \n");

	//Intervalle de garde
	html_tag("		<tr id=TR_GUARD_INTERVAL> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_intervalle_garde);
	html_tag("			<td><SELECT name=\"guardInt\" size=\"1\" onchange=\"return(JsChangeIntervalGuard(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_TYPE_GUARD_INTERVAL;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_11n_guard_interval) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_intervalle_garde[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	
	//Channel spectrum width
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_largeur_spectre_canal);
	html_tag("			<td><P ID=textResultChannelSpectrumWidth></P></td> \n");
	html_tag("		</tr> \n");
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Channel mode
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_mode_canal);
		html_tag("			<td><SELECT name=\"channelMode\" size=\"1\" onchange=\"return(JsChangeChannelMode(form))\"> \n");
		for(loc_u8_i=0;loc_u8_i<NB_MAX_TYPE_SELECTION_CANAL;loc_u8_i++)
		{
			if(TRUE == T_TB_VAL.pt_definition_radio_modem[s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem].pu8_flag_mode_canal[loc_u8_i])
			{
				html_tag("		   <option %s value=\"%d\">%s</option>	\n",
						 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_type_selection_canal) ? "selected" : ""),
						 loc_u8_i,
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_canal[loc_u8_i]);
			}
		}
		html_tag("				  </select></td> \n");
		html_tag("		</tr> \n");
	}
	else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
	{
		html_tag("<input type=\"hidden\" name=\"channelMode\" value=\"%d\"> \n",TYPE_SELECTION_CANAL_ISO);
	}
	//Channel iso
	html_tag("		<tr id=TR_CHANNEL_ISO_FREQ> \n");
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("			<td>%s (%s)</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_canal,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_canal[TYPE_SELECTION_CANAL_ISO]);
	}
	else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
	{
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_canal);
	}
	html_tag("			<td><SCRIPT language=JavaScript>JsPrintHtmlChannel(0, %d);</SCRIPT></td> \n",
			s_html_cfg_eqpmt.s_wifi.u16_iso_canal_radio);
	html_tag("		</tr> \n");
	//Channel multi
	html_tag("		<tr id=TR_CHANNEL_MULTI_FREQ> \n");
	html_tag("			<td>%s (%s)</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_canal,
			 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_canal[TYPE_SELECTION_CANAL_MULTI]);
	html_tag("			<td nowrap><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
	{
		html_tag("<tr><td><B>%d:</B></td><td><SCRIPT language=JavaScript>JsPrintHtmlChannel(%d, %d);</SCRIPT></td><tr> \n",
				loc_u8_i+1,
				loc_u8_i+1,
				s_html_cfg_eqpmt.s_wifi.pu16_multi_canal_radio[loc_u8_i]);
	}
	html_tag("			</table></td> \n");
	html_tag("		</tr> \n");

#ifdef _WRM100_ABG_SELECT
	//Antenne Tx (ABG)
	html_tag("		<tr id=TR_ANT_TX> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_selection_antenne_tx);
	html_tag("			<td><SELECT name=\"ant_ABG_tx\" size=\"1\" > \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ABG_SELECT_ANT_TX;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_tx_selection) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_ABG_choix_antenne_tx[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	//Antenne Rx (ABG) 
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_selection_antenne_rx);
	html_tag("			<td><SELECT name=\"ant_ABG_rx\" size=\"1\" > \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ABG_SELECT_ANT_RX;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_ant_ABG_rx_selection) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_ABG_choix_antenne_rx[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
#endif

#ifdef _WRM100_N_SELECT
	//Antenne Tx/RX (N)
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_selection_antenne);
	html_tag("			<td><SELECT name=\"ant_N\" size=\"1\" onchange=\"return(JsChangeNAntenne(form, true))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_N_SELECT_ANTENNES;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_ant_N_selection) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_N_choix_antenne[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
#endif
	
	//Puissance d'émission
	html_tag("		<tr id=TR_POWER> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_puissance_emetteur);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"power\" value=%d onchange=\"return(JsChangePowerTx(form, true))\">&nbsp;dBm</td> \n",
			 s_html_cfg_eqpmt.s_wifi.u8_power_tx);
	html_tag("		</tr> \n");
	//Débit données
	html_tag("		<tr id=TR_RATE> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_debit_donnees);
	html_tag("			<td><SCRIPT language=JavaScript>JsPrintHtmlDataRate(%d);</SCRIPT></td> \n",
			 s_html_cfg_eqpmt.s_wifi.u8_data_rate);
	html_tag("		</tr> \n");
	//Seuil de niveau reçu
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_seuil_reception);
		html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"seuilRx\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;dBm</td> \n",
				 s_html_cfg_eqpmt.s_wifi.s8_seuil_rx,
				 SEUIL_RX_MIN,
				 SEUIL_RX_MAX);
		html_tag("		</tr> \n");
	}
	
#if VERSION_WRM100_DEMO
#else
	if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Nombre maximum de stations connectés à l'Access Point
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nombre_maximum_stations_associees);
		html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"maxSta\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
				 s_html_cfg_eqpmt.s_wifi.u16_nb_max_associated_stations,
				 NB_ASSOCIATED_STATIONS_MIN,
				 NB_ASSOCIATED_STATIONS_MAX);
		html_tag("		</tr> \n");
	}
#endif
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGWIRELESSBASIC_VALID_1);

	//Paramétrage du mode de sécurité
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_securite_wifi);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Mode sécurité
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_securite);
	if((MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	  )
	{
		html_tag("			<td><SELECT name=\"secuMode\" size=\"1\" onchange=\"return(JsChangeModeSecurity(form))\"> \n");
		for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_SECURITE_WIFI;loc_u8_i++)
		{
			if(TRUE == T_TB_VAL.pt_definition_mode_securite_wifi[loc_u8_i].u8_flag)
			{
				html_tag("		   <option %s value=\"%d\">%s</option>	\n",
						 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.u8_mode_securite_wifi) ? "selected" : ""),
						 loc_u8_i,
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_securite_wifi[loc_u8_i]);
			}
		}
		html_tag("				  </select></td> \n");
	}
	else //MODE_RADIO_MODEM_MONITOR
	{
		html_tag("<input type=\"hidden\" name=\"secuMode\" value=\"%d\"> \n",MODE_SECURITE_WIFI_AUCUN);
	}
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;</td></tr> \n");

	//Paramètrage WEP
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WEP_SECU\"><td><P class=undermenu>%s</P></td></tr> \n",
			pt_tb_msg[u8_html_langue].ps8_msg_WEP);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WEP_SECU\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WEP_SECU\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Longueur de la clé WEP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_longueur_cle_WEP);
	html_tag("			<td><SELECT name=\"wepKeyLg\" size=\"1\" onchange=\"return(JsChangeLgTypeWEPkey(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_WEP_KEY_LENGTH;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_key_length) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_type_cle_WEP[loc_u8_i]);
	}
	html_tag("				  </select>&nbsp;&nbsp;(%s)</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_longueur_appliquee_a_toutes_les_cles);
	html_tag("		</tr> \n");
	//Type de la clé WEP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_type_cle_WEP);
	html_tag("			<td><SELECT name=\"wepKeyTp\" size=\"1\" onchange=\"return(JsChangeLgTypeWEPkey(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_KEY_TYPE;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_wep_key_type) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_type_cle_WEP[loc_u8_i]);
	}
	html_tag("				  </select>&nbsp;&nbsp;(%s)<BR>&nbsp;&nbsp;(<em><span id=SPAN_WEP_KEY_TYPE></span></em>)</td> \n",
			pt_tb_msg[u8_html_langue].ps8_msg_type_applique_a_toutes_les_cles);
	html_tag("		</tr> \n");
	//Clé WEP de 1 à 4
	for(loc_u8_i=0;loc_u8_i<NB_MAX_IDX_WEP_KEY;loc_u8_i++)
	{
		html_tag("		<tr> \n");
		html_tag("			<td>%s %d</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_cle_WEP,
				 loc_u8_i+1);
		//la balise div est une solution pour modifier type de la balise INPUT sous IE
		html_tag("			<td><div id=ID_DIV_WEPKEY%d><input type=\"password\" size=\"%d\" maxlength=\"%d\" name=\"wepkey%d\" value=\"%s\" onchange=\"return(JsChangeWEPkey(form,%d))\"></div></td> \n",
				 loc_u8_i,
				 KEY_WEP_VALUE_LENGTH_MAX+1,
				 KEY_WEP_VALUE_LENGTH_MAX,
				 loc_u8_i,
				 s_html_cfg_eqpmt.s_wifi.s_wep_security.ps8_key_value[loc_u8_i],
				 loc_u8_i);
		html_tag("		</tr> \n");
	}
	//Afficher toutes les clés
	html_tag("		<tr> \n");
	html_tag("			<td>&nbsp;</td> \n");
	html_tag("			<td>&nbsp;&nbsp;&nbsp;%s :&nbsp;<input name=\"wepKeyDisplay\" type=\"checkbox\" onClick=\"return(JSDisplayWEPKey(form))\"></td>  \n",
			pt_tb_msg[u8_html_langue].ps8_msg_afficher_toutes_les_cles_WEP);
	html_tag("		</tr> \n");
	//Clé WEP par défaut
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cle_WEP_par_defaut);
	html_tag("			<td><SELECT name=\"wepKeyCx\" size=\"1\" onchange=\"return(JsChangeDefaultWEPkey(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_IDX_WEP_KEY;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s %d</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_index_key_default) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_cle_WEP,
				 loc_u8_i+1);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	//WEP Authentification
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_authentification);
	html_tag("			<td><SELECT name=\"wepAuth\" size=\"1\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_WEP_AUTHENTIFICATION;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wep_security.u8_authentification) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_authentification_WEP[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");



	//Paramètrage WPA / WPA2
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_SECU\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_WPA);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_SECU\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_SECU\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//WPA authentication
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_authentification);
	html_tag("			<td><SELECT name=\"wpaAuth\" size=\"1\" onchange=\"return(JsChangeWPAauthentication(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_WPA_AUTHENTIFICATION;loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pu8_flag_affichage_wpa_authentification[loc_u8_i])
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_authentification) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_authentification_WPA[loc_u8_i]);
		}
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	if(MODE_RADIO_MODEM_ACCESS_POINT == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Group key update interval
		html_tag("		<tr> \n");
		html_tag("			<td nowrap>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_intervalle_mise_a_jour_cle_wpa);
		html_tag("			<td><input type=\"text\" size=\"6\" maxlength=5 name=\"wpaUpdt\" value=%lu onchange=\"return(isInteger(this,%d,%d))\">&nbsp;%s</td> \n",
				 s_html_cfg_eqpmt.s_wifi.s_wpa_security.u32_gp_key_update_interval,
				 GP_KEY_UPDATE_INTERVAL_MIN,
				 GP_KEY_UPDATE_INTERVAL_MAX,
				 pt_tb_msg[u8_html_langue].ps8_msg_secondes);
		html_tag("		</tr> \n");
	}
	html_tag("</table></td></tr> \n");

	//Paramètrage PSK
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_PSK\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_PSK);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_PSK\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_PSK\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//PSK Key type
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_type_cle_PSK);
	html_tag("			<td><SELECT name=\"pskTp\" size=\"1\" onchange=\"return(JsChangePSKtype(form))\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_KEY_TYPE;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_wpa_key_type) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_type_cle_WEP[loc_u8_i]);
	}
	html_tag("				  </select><BR>&nbsp;&nbsp;(<em><span id=SPAN_WPA_PSK_TYPE></span></em>)</td> \n");
	html_tag("		</tr> \n");
	//Pre-shared key
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cle_pre_partagee);
	html_tag("			<td><div id=ID_DIV_WPAKEY><input type=\"password\" size=\"%d\" maxlength=\"%d\" name=\"wpakey\" value=\"%s\" onchange=\"return(JsChangeWPAkey(form))\"></div></td> \n",
			LG_MAX_PRESHARED_WPA_TOTAL,
			LG_MAX_PRESHARED_WPA_TOTAL,
			s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_pre_shared_key);
	html_tag("		</tr> \n");
	//Afficher la clé PSK
	html_tag("		<tr> \n");
	html_tag("			<td>&nbsp;</td> \n");
	html_tag("			<td nowrap>&nbsp;&nbsp;&nbsp;%s :&nbsp;<input name=\"wpaKeyDisplay\" type=\"checkbox\" onClick=\"return(JSDisplayWPAKey(form))\"></td>  \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_afficher_cle_PSK);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");


	//Paramètrage EAP
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_EAP\"><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_EAP);
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_EAP\"><td>&nbsp;</td></tr> \n");
	if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		//Test si présence du certificat CA configuré
		loc_u8_certificat_CA_cfg_present = FALSE;	//RAZ
		loc_u8_certificat_Clt_cfg_present = FALSE;	//RAZ
		for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
		{
			if(0!=strcmp(loc_ps_certificat_file[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
			{
				if(0 == strcmp(loc_ps_certificat_file[loc_u8_i].ps8_nom,s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_authority))
				{
					loc_u8_certificat_CA_cfg_present = TRUE;
				}
				if(0 == strcmp(loc_ps_certificat_file[loc_u8_i].ps8_nom,s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_client))
				{
					loc_u8_certificat_Clt_cfg_present = TRUE;
				}
			}
		}
		if((FALSE == loc_u8_certificat_CA_cfg_present)||
		   (FALSE == loc_u8_certificat_Clt_cfg_present)
		  )
		{
			html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_EAP_TLS\"><td><P class=warning><B>%s!</B> %s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_attention,
					 pt_tb_msg[u8_html_langue].ps8_avertissement_eap_tls_certificat);
			html_tag("</td></tr> \n");
			html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_EAP_TLS\"><td>&nbsp;</td></tr> \n");
		}
	}
	html_tag("<tr STYLE=\"display:none\" class=\"TR_WPA_EAP\"><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
			//EAP authentication timeout
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_reauthentification_period);
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"eapReauthPd\" value=%lu onchange=\"return(JsChangeEapReauthPeriod(form,%d,%d))\">&nbsp;%s&nbsp;&nbsp;(<em>%s</em>)</td> \n",
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.u32_eap_reauth_period,
					 EAP_REAUTH_PERIOD_MIN,
					 EAP_REAUTH_PERIOD_MAX,
					 pt_tb_msg[u8_html_langue].ps8_msg_secondes,
					 pt_tb_msg[u8_html_langue].ps8_msg_info_sup_eap_reauth_period);
			html_tag("		</tr> \n");
			//Adresse Ip du serveur RADIUS
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip_serveur_radius);
			html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIpRadius\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
					 ps8GetStringIp(s_html_cfg_eqpmt.s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip));
			html_tag("		</tr> \n");
			//Port du serveur RADIUS
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_port_serveur_radius);
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"portRadius\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.s_server_radius.u16_radius_port,
					 PORT_UDP_TCP_MIN,
					 PORT_UDP_TCP_MAX);
			html_tag("		</tr> \n");
			//Clé serveur RADIUS
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_cle_serveur_radius);
			html_tag("			<td><div id=ID_DIV_KEYRADIUS><input type=\"password\" size=\"%d\" maxlength=\"%d\" name=\"keyRadius\" value=\"%s\" onchange=\"return(isValidText(this,true,true))\"></div></td> \n", //isValidText: espace interdit
					 LG_MAX_SHARED_RADIUS,
					 LG_MAX_SHARED_RADIUS,
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared);
			html_tag("		</tr> \n");
			//Afficher la clé 
			html_tag("		<tr> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td nowrap>&nbsp;&nbsp;&nbsp;%s :&nbsp;<input name=\"eapKeyDisplay\" type=\"checkbox\" onClick=\"return(JSDisplayEAPKey(form))\"></td>  \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_afficher_cle_EAP);
			html_tag("		</tr> \n");
			break;
		case MODE_RADIO_MODEM_STATION:
			//EAP method
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_method);
			html_tag("			<td><SELECT name=\"eapMethod\" size=\"1\" onchange=\"return(JsChangeEapMethod(form))\"> \n");
			for(loc_u8_i=0;loc_u8_i<NB_MAX_EAP_METHOD;loc_u8_i++)
			{
				html_tag("		   <option %s value=\"%d\">%s</option>	\n",
						 ((loc_u8_i == s_html_cfg_eqpmt.s_wifi.s_wpa_security.u8_eap_method) ? "selected" : ""),
						 loc_u8_i,
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_EAP_methode[loc_u8_i]);
			}
			html_tag("				  </select></td> \n");
			html_tag("		</tr> \n");
			//EAP identity
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_identity);
			html_tag("			<td><input type=\"text\" size=%d maxlength=%d name=\"eapId\" value=\"%s\" onchange=\"return(isValidText(this,true,true))\"></td> \n", //isValidText: espace interdit
					 LG_MAX_EAP_IDENTITY + 15, //size (rmq:+15 pour pouvoir lire la totalité de la chaine de caractères
					 LG_MAX_EAP_IDENTITY, //maxlength
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_identity);
			html_tag("		</tr> \n");
#if PARAMETERS_RADIUS_NOT_USED
			//EAP user name
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_user_name);
			html_tag("			<td><input type=\"text\" size=%d maxlength=%d name=\"eapUserName\" value=\"%s\" onchange=\"return(isValidText(this,true,true))\"></td> \n", //isValidText: espace interdit
					 LG_MAX_EAP_USER_NAME + 15, //size (rmq:+15 pour pouvoir lire la totalité de la chaine de caractères
					 LG_MAX_EAP_USER_NAME, //maxlength
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_user_name);
			html_tag("		</tr> \n");
#endif
			//EAP user password
			html_tag("		<tr id=TR_EAPUSERPWD> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_user_password);
			html_tag("			<td><div id=ID_DIV_EAPUSERPWD><input type=\"password\" size=\"%d\" maxlength=\"%d\" name=\"eapUserPwd\" value=\"%s\" onchange=\"return(isValidText(this,true,true))\"></div></td> \n", //isValidText: espace interdit
					 LG_MAX_EAP_USER_PASSWORD,
					 LG_MAX_EAP_USER_PASSWORD,
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_user_password);
			html_tag("		</tr> \n");

			//EAP file certificat d'autorité
			html_tag("		<tr id=TR_EAPFILECA> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_certificat_autorite);
			html_tag("			<td><SELECT name=\"eapFileCA\" size=\"1\"> \n");
			html_tag("				<option value=\"%s\">%s</option>	\n",
					 CH_CERTIFICAT_NO_SELECTED,
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_aucun_certificat_selectionne);
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					html_tag("		   <option %s value=\"%s\">%s</option>	\n",
							 ((0 == strcmp(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_authority, loc_ps_certificat_file[loc_u8_i].ps8_nom)) ? "selected" : ""),
							 loc_ps_certificat_file[loc_u8_i].ps8_nom,
							 loc_ps_certificat_file[loc_u8_i].ps8_nom);
				}
			}
			html_tag("				  </select></td> \n");
			html_tag("		</tr> \n");
			//EAP file certificat du client
			html_tag("		<tr id=TR_EAPFILECERTCLT> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_certificat_client);
			html_tag("			<td><SELECT name=\"eapFileCertClt\" size=\"1\"> \n");
			html_tag("				<option value=\"%s\">%s</option>	\n",
					 CH_CERTIFICAT_NO_SELECTED,
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_aucun_certificat_selectionne);
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					html_tag("		   <option %s value=\"%s\">%s</option>	\n",
							 ((0 == strcmp(s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_file_certificat_client, loc_ps_certificat_file[loc_u8_i].ps8_nom)) ? "selected" : ""),
							 loc_ps_certificat_file[loc_u8_i].ps8_nom,
							 loc_ps_certificat_file[loc_u8_i].ps8_nom);
				}
			}
			html_tag("				  </select></td> \n");
			html_tag("		</tr> \n");
			//EAP Clé privée 
			html_tag("		<tr id=TR_EAPPRIVKEYPWD> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_private_key_password);
			html_tag("			<td><div id=ID_DIV_EAPPRIVKEYPWD><input type=\"password\" size=\"%d\" maxlength=\"%d\" name=\"eapPrivKeyPwd\" value=\"%s\" onchange=\"return(isValidText(this,true,true))\"></div></td> \n", //isValidText: espace interdit
					 LG_MAX_PRIVATE_KEY_PWD,
					 LG_MAX_PRIVATE_KEY_PWD,
					 s_html_cfg_eqpmt.s_wifi.s_wpa_security.ps8_private_key_password);
			html_tag("		</tr> \n");
			//Afficher la clé 
			html_tag("		<tr> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td nowrap>&nbsp;&nbsp;&nbsp;%s :&nbsp;<input name=\"eapKeyDisplay\" type=\"checkbox\" onClick=\"return(JSDisplayEAPKey(form))\"></td>  \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_afficher_cle_EAP);
			html_tag("		</tr> \n");
			//EAP Supprimer un certificat
			html_tag("		<tr id=TR_EAPREMOVECERT> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_supprimer_certificat);
			html_tag("			<td><SELECT name=\"eapRemoveCert\" size=\"1\"> \n");
			html_tag("		   <option selected value=\"%s\">%s</option>	\n",
					 CH_CERTIFICAT_NO_SELECTED,
					 pt_tb_msg[u8_html_langue].ps8_msg_eap_aucun_certificat_selectionne);
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					html_tag("		   <option value=\"%s\">%s</option>	\n",
							 loc_ps_certificat_file[loc_u8_i].ps8_nom,
							 loc_ps_certificat_file[loc_u8_i].ps8_nom);
				}
			}
			html_tag("				  </select>&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
					pt_tb_msg[u8_html_langue].ps8_msg_supprimer,
					FORM_SUCONFIGWIRELESSBASIC_REMOVE_CERTIFICAT);
			html_tag("		</tr> \n");
			
			break;
		default:
			break;
	}
	html_tag("</table></td></tr> \n");
	
	
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGWIRELESSBASIC_VALID_2);

	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;</td></tr> \n");
	html_tag("<tr STYLE=\"display:none\" class=\"TR_SECU\"><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider_formulaire,
			 FORM_SUCONFIGWIRELESSBASIC_VALID_ALL);
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigWirelessBasic*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigWirelessBasic
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigWirelessBasic
//=====================================================================================
void InitModule_SUConfigWirelessBasic(void)
{
}/*InitModule_SUConfigWirelessBasic*/
