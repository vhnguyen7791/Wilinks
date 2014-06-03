/*========================================================================*/
/* NOM DU FICHIER  : cfg_wlan_N.c		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/09/2010                                           */
/* Libelle         : Principal: Configuration du Wifi (N)				  */
/* Projet          : WRM100                                               */
/* Indice          : BE059                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 15/09/2010 CM
// - CREATION
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
// - Ajout paramètre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
// - Integration des paramètres handoff
// - Configuration seuil de framentation (adv wifi) non autorisé en 11n
//BE043 29/10/2010 CM
// - Correction reconfiguration du channel width de l'AP par STATION (en mode 11nht40) non désiré
//		-> donc AP est rejeté par la STATION
// En effet, par défaut le mode CWM (Channel Width Management) est activé.
// Il existe plusieurs conditions pour que la STATION décide de reconfigurer le channel width.
// Il y a par exemple la mesure de l'occupation spectrale.
// Si celui-ci est au-dessus du seuil (extbusythres), alors la STATION reconfigure le channel width de l'AP.
//	(en envoyant un message 802.11 de type ACTION).
// Donc, on va désaciver ce mode (ce sera plus sur)
// - Correction enum modes 802.11 (meilleur ergonomie)
//BE047 29/11/2010 CM
// - Correction configuration du paramètre bmiss (handoff)
//	uniquement prise en compte suite à un "ifconfig ath0 up"
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
// - Correction configuration du paramètre bmiss (handoff)
//	annule correction faite dans BE047
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE055 17/01/2011 CM
// - Correction en mode monitor ne pas configurer ssid
// - Ajout configuration Country ID pour le client
// - Modification configuration des antennes
// - Correction kernel panic sur ACCESS POINT en mode HT40 suite à déchargement du driver-N
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
//BE058 21/01/2011 CM
// - Correction bug mode scanning non appliqué sur Driver-N
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_WLAN_N

#define SEUIL_MIN_TIME_BETWEEN_2_BEACON		30 //ms

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"
#include "../../LibraryBdd/list_freq.h" //Add by VuHai for 2 file T_DEF_FILE_IWLISTFREQ and T_DEF_FILE_HT40_ALLOW_MAP

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u16sod u16_countryID_memorise;
static s8sod s8_code_string_country_memorise[2];

const u16sod U16_COUNTRY_CODE[NB_MAX_COUNTRY_ID]=
{
	CTRY_FRANCE,				//COUNTRY_ID_FRANCE
	CTRY_AUSTRIA,				//COUNTRY_ID_AUSTRIA
	CTRY_BELGIUM,				//COUNTRY_ID_BELGIUM
	CTRY_BULGARIA,				//COUNTRY_ID_BULGARIA
	CTRY_CYPRUS,				//COUNTRY_ID_CYPRUS
	CTRY_CZECH,					//COUNTRY_ID_CZECH_REPUBLIC
	CTRY_DENMARK,				//COUNTRY_ID_DENMARK
	CTRY_ESTONIA,				//COUNTRY_ID_ESTONIA
	CTRY_FINLAND,				//COUNTRY_ID_FINLAND
	CTRY_GERMANY,				//COUNTRY_ID_GERMANY
	CTRY_GREECE,				//COUNTRY_ID_GREECE
	CTRY_ICELAND,				//COUNTRY_ID_ICELAND
	CTRY_IRELAND,				//COUNTRY_ID_IRELAND
	CTRY_ITALY,					//COUNTRY_ID_ITALY
	CTRY_LATVIA,				//COUNTRY_ID_LATVIA
	CTRY_LITHUANIA,				//COUNTRY_ID_LITHUANIA
	CTRY_LUXEMBOURG,			//COUNTRY_ID_LUXEMBOURG
	CTRY_MALTA,					//COUNTRY_ID_MALTA
	CTRY_NETHERLANDS,			//COUNTRY_ID_NETHERLANDS
	CTRY_NORWAY,				//COUNTRY_ID_NORWAY
	CTRY_POLAND,				//COUNTRY_ID_POLAND
	CTRY_PORTUGAL,				//COUNTRY_ID_PORTUGAL
	CTRY_ROMANIA,				//COUNTRY_ID_ROMANIA
	CTRY_SLOVAKIA,				//COUNTRY_ID_SLOVAKIA
	CTRY_SLOVENIA,				//COUNTRY_ID_SLOVENIA
	CTRY_SPAIN,					//COUNTRY_ID_SPAIN
	CTRY_SWEDEN,				//COUNTRY_ID_SWEDEN
	CTRY_SWITZERLAND,			//COUNTRY_ID_SWITZERLAND
	CTRY_UNITED_KINGDOM,		//COUNTRY_ID_UNITED_KINGDOM
	CTRY_UNITED_STATES,			//COUNTRY_ID_USA
	CTRY_UNITED_STATES_FCC49,	//COUNTRY_ID_PUBLIC_SAFETY
};

//Add by VuHai
const s8sod *ISO3166_COUNTRY_CODE[NB_MAX_COUNTRY_ID]=
{
	"FR",				//COUNTRY_ID_FRANCE
	"AT",				//COUNTRY_ID_AUSTRIA
	"BE",				//COUNTRY_ID_BELGIUM
	"BG",				//COUNTRY_ID_BULGARIA
	"CY",				//COUNTRY_ID_CYPRUS
	"CZ",				//COUNTRY_ID_CZECH_REPUBLIC
	"DK",				//COUNTRY_ID_DENMARK
	"EE",				//COUNTRY_ID_ESTONIA
	"FI",				//COUNTRY_ID_FINLAND
	"DE",				//COUNTRY_ID_GERMANY
	"GR",				//COUNTRY_ID_GREECE
	"IS",				//COUNTRY_ID_ICELAND
	"IE",				//COUNTRY_ID_IRELAND
	"IT",				//COUNTRY_ID_ITALY
	"LV",				//COUNTRY_ID_LATVIA
	"LT",				//COUNTRY_ID_LITHUANIA
	"LU",				//COUNTRY_ID_LUXEMBOURG
	"MT",				//COUNTRY_ID_MALTA
	"NL",				//COUNTRY_ID_NETHERLANDS
	"NO",				//COUNTRY_ID_NORWAY
	"PL",				//COUNTRY_ID_POLAND
	"PT",				//COUNTRY_ID_PORTUGAL
	"RO",				//COUNTRY_ID_ROMANIA
	"SK",				//COUNTRY_ID_SLOVAKIA
	"SI",				//COUNTRY_ID_SLOVENIA
	"ES",				//COUNTRY_ID_SPAIN
	"SE",				//COUNTRY_ID_SWEDEN
	"CH",				//COUNTRY_ID_SWITZERLAND
	"UK",				//COUNTRY_ID_UNITED_KINGDOM
	"US",				//COUNTRY_ID_USA
	"UM",				//COUNTRY_ID_PUBLIC_SAFETY
};//Fin Add by VuHai


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: WlanN_Install_Wifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Installe la configuration du wifi (basic)
//=====================================================================================
void WlanN_Install_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod loc_u16_country_id;
	s8sod s8_code_string_country[2];//Add by VuHai
	//802.11 mode
	//Modif by VuHai
	
	/*switch(loc_ps_config->s_wifi.u8_mode_802_11x)
	{
		case MODE_WIFI_802_11G:
			CmdSystem_Generique("iwpriv %s mode 11g",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11B:
			CmdSystem_Generique("iwpriv %s mode 11b",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11A:
			CmdSystem_Generique("iwpriv %s mode 11a",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NGHT20:
			CmdSystem_Generique("iwpriv %s mode 11nght20",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NGHT40PLUS:
			CmdSystem_Generique("iwpriv %s mode 11nght40plus",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NGHT40MINUS:
			CmdSystem_Generique("iwpriv %s mode 11nght40minus",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NGHT40:
			CmdSystem_Generique("iwpriv %s mode 11nght40",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NAHT20:
			CmdSystem_Generique("iwpriv %s mode 11naht20",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NAHT40PLUS:
			CmdSystem_Generique("iwpriv %s mode 11naht40plus",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NAHT40MINUS:
			CmdSystem_Generique("iwpriv %s mode 11naht40minus",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_WIFI_802_11NAHT40:
			CmdSystem_Generique("iwpriv %s mode 11naht40",
								NOM_INTERFACE_WIFI);
			break;
		default:
			CmdSystem_Generique("iwpriv %s mode auto", //auto
								NOM_INTERFACE_WIFI);
			break;
	}*///Fin Modif by VuHai
	
	/*//CountryID
	if(TRUE == s_debug_global_process_prncpl.u8_dbg_countryID) //CONDITION: debug activé
	{
		loc_u16_country_id = u16_countryID_debug;
	}
	else
	{
		loc_u16_country_id = U16_COUNTRY_CODE[loc_ps_config->s_wifi.u8_countryID];
	}
	CmdSystem_Generique("iwpriv %s setCountryID %d",
						NOM_INTERFACE_LMAC_WIFI,
						loc_u16_country_id);*/
	/*if(u16_countryID_memorise != loc_u16_country_id)
	{
		//On peut récupérer la liste des fréquences réglementaires
		WlanN_Get_ListFrequency();
		u16_countryID_memorise = loc_u16_country_id;
	}*///Modif by VuHai to ignore error Get_listfrequency


	//Add by VuHai CountryID
	/*if(TRUE == s_debug_global_process_prncpl.u8_dbg_countryID) //CONDITION: debug activé
	{
		loc_u16_country_id = u16_countryID_debug;
	}*/
	//else
	//{
	strcpy(s8_code_string_country,ISO3166_COUNTRY_CODE[loc_ps_config->s_wifi.u8_countryID]);
	//}
	CmdSystem_Generique("iw reg set %s",s8_code_string_country);
	//Fin Add by VuHai
	
	if(strcmp(s8_code_string_country, s8_code_string_country_memorise)!=0)
	{
		//On peut récupérer la liste des fréquences réglementaires
		WlanN_Get_ListFrequency();
		strcpy(s8_code_string_country_memorise, s8_code_string_country);
	}//Modif by VuHai to ignore error Get_listfrequency

	
	//Fréquence
	Install_FrequenceWifi(loc_ps_config);//Modif by VuHai

	//Paramètres spécifiques au mode du radio modem
	//Modif by VuHai
	/*switch(loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
			//On configure l'intervalle beacon
			CmdSystem_Generique("iwpriv %s bintval %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u16_protcl_beacon_period);

			break;
		case MODE_RADIO_MODEM_STATION:
#warning "BGSCAN non supporte - A CODER"
//			//on désactive bgscan
//			CmdSystem_Generique("iwpriv %s bgscan 0",
//								NOM_INTERFACE_WIFI);
			break;
		case MODE_RADIO_MODEM_MONITOR:
		default:
			break;
	}*/

	if((MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
	  )
	{
		//SSID
		/*CmdSystem_Generique("iwconfig %s essid \"%s\"",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.ps8_ssid_primary);*///Modif
				// by VuHai
	}

	if(MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		if(TRUE == loc_ps_config->s_wifi.u8_dual_ssid) //CONDITION: second SSID activé
		{
			//Second SSID
			/*CmdSystem_Generique("iwconfig %s essid \"%s\" [2]",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.ps8_ssid_secondary);*///Mofif
					// by Vu Hai
		}
	}
	/*
	if(MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		//Mask SSID Move to hostapd
		CmdSystem_Generique("iwpriv %s hide_ssid %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.u8_masquage_ssid);
	}*/

	if((MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
	  )
	{
		//Puissance d'emission
		Install_TxPowerWifi(loc_ps_config);

		/*if(TRUE == u8IsMode80211n(loc_ps_config->s_wifi.u8_mode_802_11x))
		{
			CmdSystem_Generique("iwpriv %s shortgi %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u8_11n_guard_interval);
		}
	
		//Data rate
		switch(loc_ps_config->s_wifi.u8_data_rate)
		{
			case DATA_RATE_AUTOMATIC:
				CmdSystem_Generique("iwconfig %s rate auto",
									NOM_INTERFACE_WIFI);
				break;
			case DATA_RATE_1_MBPS:
			case DATA_RATE_2_MBPS:
			case DATA_RATE_5_5_MBPS:
			case DATA_RATE_11_MBPS:
			case DATA_RATE_6_MBPS:
			case DATA_RATE_9_MBPS:
			case DATA_RATE_12_MBPS:
			case DATA_RATE_18_MBPS:
			case DATA_RATE_24_MBPS:
			case DATA_RATE_36_MBPS:
			case DATA_RATE_48_MBPS:
			case DATA_RATE_54_MBPS:
				CmdSystem_Generique("iwconfig %s rate %dk",
									NOM_INTERFACE_WIFI,
									T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_basic);
				break;
			case DATA_RATE_MCS0:
			case DATA_RATE_MCS1:
			case DATA_RATE_MCS2:
			case DATA_RATE_MCS3:
			case DATA_RATE_MCS4:
			case DATA_RATE_MCS5:
			case DATA_RATE_MCS6:
			case DATA_RATE_MCS7:
			case DATA_RATE_MCS8:
			case DATA_RATE_MCS9:
			case DATA_RATE_MCS10:
			case DATA_RATE_MCS11:
			case DATA_RATE_MCS12:
			case DATA_RATE_MCS13:
			case DATA_RATE_MCS14:
			case DATA_RATE_MCS15:
				//iwpriv ath0 set11NRates $6
				//iwpriv ath0 set11NRetries 0x01
				CmdSystem_Generique("iwpriv %s set11NRates 0x%02X",
									NOM_INTERFACE_WIFI,
									T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
				CmdSystem_Generique("iwpriv %s set11NRetries 0x01",
									NOM_INTERFACE_WIFI);
				break;
			default:
				CmdSystem_Generique("iwconfig %s rate auto",
									NOM_INTERFACE_WIFI);
				break;
		}*/
	}

	//Désactivation du mode CWM (Channel Width Management)
	//La station ne reconfigurera pas une nouvelle largeur de canal de l'ACCESS POINT
	/*CmdSystem_Generique("iwpriv %s cwmenable 0",
						NOM_INTERFACE_WIFI);

	//Désactivation du mode coexistence 20/40MHz (sinon risque kernel panic sur AP)
	CmdSystem_Generique("iwpriv %s disablecoext 1",
						NOM_INTERFACE_WIFI);*/
	
	
	//Nombre maximum de stations associées
#warning "A CODER: iwpriv nb max_station_associees"*/
	
}/*WlanN_Install_Wifi*/

//=====================================================================================
// Fonction		: WlanN_Install_Handoff
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 12/10/2010 -
// Description	: Installe la configuration du handoff
//=====================================================================================
void WlanN_Install_Handoff(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	//Mode scanning
	CmdSystem_Generique("iwpriv %s fr_actprob %d",
						NOM_INTERFACE_WIFI,
					    loc_ps_config->s_handoff.u8_scanning_mode);

	//Intervalle de temps entre 2 hand-off
	CmdSystem_Generique("iwpriv %s fr_mintimeho %d",
						NOM_INTERFACE_WIFI,
						loc_ps_config->s_handoff.u16_time_between_hand_off);

	//Activation du scanning background
	CmdSystem_Generique("iwpriv %s fr_bgactive %d",
						NOM_INTERFACE_WIFI,
						loc_ps_config->s_handoff.u8_bgscan_activation);

	if(TRUE == loc_ps_config->s_handoff.u8_bgscan_activation)
	{
		//Période de récurrence du scanning background
		CmdSystem_Generique("iwpriv %s fr_bgperiod %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_handoff.u16_bgscan_recurrence_period);

		//Période de récurrence du scanning background
		CmdSystem_Generique("iwpriv %s fr_bgrssi %d",
							NOM_INTERFACE_WIFI,
							MACRO_DBM2RSSI(loc_ps_config->s_handoff.s32_bgscan_detection_level));
	}

	//Niveau moyenné de l'AP actuel au dessous duquel la phase de scanning foreground démarre
	CmdSystem_Generique("iwpriv %s fr_weakbrssi %d",
						NOM_INTERFACE_WIFI,
						MACRO_DBM2RSSI(loc_ps_config->s_handoff.s32_fgscan_detection_level));

	//Nombre maximum de balises consécutives (beacons) perdues de l'AP actuel avant que la phase de scanning foreground démarre
	CmdSystem_Generique("iwpriv %s fr_bmiss %d",
						NOM_INTERFACE_WIFI,
						loc_ps_config->s_handoff.u16_fgscan_beacon_missed_threshold);

	//Niveau moyenné du prochain AP au dessus duquel un hand-off est réalisé (cas du hand-off sur le même canal radio). Il faut que le niveau de l'AP actuel soit au-dessous du seuil. (dBm)
	CmdSystem_Generique("iwpriv %s fr_nwaprssi %d",
						NOM_INTERFACE_WIFI,
						MACRO_DBM2RSSI(loc_ps_config->s_handoff.s32_iso_detection_level));
	
	//Nombre de balises consécutives (beacons) qui doivent être reçues au-dessus du niveau de puissance défini ci-dessus, avant de déclencher le hand-off. (cas du hand-off sur le même canal radio)
#if VERSION_WRM100_DEMO
#else
#endif
#warning "A CODER INTERFACE WIFI pour u16_iso_relevant_beacon_threshold"

	//Filtrage RSSI
	CmdSystem_Generique("iwpriv %s fr_rssifil %d",
						NOM_INTERFACE_WIFI,
						loc_ps_config->s_handoff.u8_type_filtrage_rssi);

	//Intervalle de temps entre 2 beacon : mindwell time
	//on limite le minimum a 30ms
	if (loc_ps_config->s_handoff.u16_time_between_2_beacon < SEUIL_MIN_TIME_BETWEEN_2_BEACON)
	{
		CmdSystem_Generique("iwpriv %s fr_mindwell %d",
							NOM_INTERFACE_WIFI,
						    SEUIL_MIN_TIME_BETWEEN_2_BEACON);
	}
	else
		CmdSystem_Generique("iwpriv %s fr_mindwell %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_handoff.u16_time_between_2_beacon);

}/*WlanN_Install_Handoff*/

//=====================================================================================
// Fonction		: WlanN_Install_AdvWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Installe la configuration du advwifi (avancé et antennes)
//=====================================================================================
void WlanN_Install_AdvWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_valeur;
	
	loc_u8_valeur = 0; //INIT

	//Paramètres spécifiques au mode du radio modem
	switch(loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
			//Intervalle beacon VuHai: Move to hostapd
			/*CmdSystem_Generique("iwpriv %s bintval %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u16_protcl_beacon_period);*/
			break;
		case MODE_RADIO_MODEM_STATION:
		case MODE_RADIO_MODEM_MONITOR:
		default:
			break;
	}

	if((MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
	  )
	{
		//TimeOut ACK
		/*CmdSystem_Generique("iwpriv %s acktimeout %d",
							NOM_INTERFACE_LMAC_WIFI,
							loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout);


		//Type du preambule (court , long) only 802.11b
#warning "Type du preambule (court , long) only 802.11b"*/

		/*if((TRUE == u8IsMode80211ag(loc_ps_config->s_wifi.u8_mode_802_11x))||
		   (TRUE == u8IsMode80211b(loc_ps_config->s_wifi.u8_mode_802_11x))
		  )//CONDITION: valable pour 11a/11g et 11b
		{
			//Fragmentation threshold
			CmdSystem_Generique("iwconfig %s frag %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u16_protcl_fragment_threshold);
		}*///Modif by VuHai: Move to hostapd

		//RTC/CTS threshold
		/*switch(loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold)
		{
			case WF_RTS_CTS_THRESHOLD_MAX:
				CmdSystem_Generique("iwconfig %s rts off",
									NOM_INTERFACE_WIFI);
				break;
			default:
				CmdSystem_Generique("iwconfig %s rts %d",
									NOM_INTERFACE_WIFI,
									loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold);
				break;
		}*///Modif by VuHai: Move to hostapd
/*
#if VERSION_WRM100_DEMO
#else
		//RTS_retry_limit
		CmdSystem_Generique("iwconfig %s retry %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.u16_protcl_RTS_retry_limit);
#endif
#warning "PROBLEME: iwconfig RTS_retry_limit"


		//WMM (Wireless for MultiMedia)
		CmdSystem_Generique("iwpriv %s wmm %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.u8_activation_WMM);*/
	}

	//Sélection de l'antenne TX/RX
	loc_u8_valeur = 1; //RAZ
	switch(loc_ps_config->s_wifi.u8_ant_N_selection)
	{
		case N_SELECT_ANTENNE_1:
			loc_u8_valeur = 1;
			break;
		case N_SELECT_ANTENNES_1_ET_2:
			loc_u8_valeur = 3;
			break;
		case N_SELECT_ANTENNES_1_ET_2_ET_3:
			loc_u8_valeur = 7;
			break;
		default:
			break;
	}
	//CmdSystem_Generique("iwpriv %s txchainmask %d",
	//					NOM_INTERFACE_LMAC_WIFI,
	//					loc_u8_valeur);
	//CmdSystem_Generique("iwpriv %s rxchainmask %d",
	//					NOM_INTERFACE_LMAC_WIFI,
	//					loc_u8_valeur);
	CmdSystem_Generique("iw phy#0 set antenna %d %d", loc_u8_valeur, loc_u8_valeur);

}/*WlanN_Install_AdvWifi*/

//=====================================================================================
// Fonction		: WlanN_Install_FrequenceWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Installe la configuration du wifi (fréquence)
//=====================================================================================
void WlanN_Install_FrequenceWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_frequence;
	u16sod	loc_u16_index;
	u16sod	loc_u16_min_index;
	u16sod	loc_u16_max_index;
	u8sod	loc_u8_i;
	u8sod	loc_u8_trouve;
	s8sod	loc_ps8_chainlist[300+1];
	s8sod	loc_ps8_tempo[100+1];

	loc_u16_frequence = 0; //INIT
	loc_u16_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u16_min_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u16_max_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u8_trouve = FALSE;	//INIT
	strcpy(loc_ps8_chainlist, "");	//INIT
	strcpy(loc_ps8_tempo, "");	//INIT

	switch(loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
		case MODE_RADIO_MODEM_MONITOR:
			//On configure la fréquence
			loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
			if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
			{
				loc_u16_frequence = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_freq_MHz;
				/*CmdSystem_Generique("iwconfig %s freq %dM",
									NOM_INTERFACE_WIFI,
									loc_u16_frequence);*/
			}
			break;
		case MODE_RADIO_MODEM_STATION:
			switch(loc_ps_config->s_wifi.u8_type_selection_canal)
			{
				case TYPE_SELECTION_CANAL_ISO:
					loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
					if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
					{
						//CmdSystem_Generique("athchans %d",loc_ps_config->s_wifi.u16_iso_canal_radio);
						//CmdSystem_Generique("iwpriv %s fr_isofreq 1", NOM_INTERFACE_WIFI);
					}
					break;
				case TYPE_SELECTION_CANAL_MULTI:
					/*loc_u8_trouve = FALSE;	//RAZ
					strcpy(loc_ps8_tempo, "");	//RAZ
					for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
					{
						if(CHANNEL_RADIO_DISABLED != loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i])
						{
							loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i], loc_ps_config->s_wifi.u8_mode_802_11x);
							if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
							{
								sprintf(loc_ps8_tempo,"%d ",loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i]);
								strcat(loc_ps8_chainlist, loc_ps8_tempo);
								loc_u8_trouve = TRUE;
							}
						}
					}
					if(FALSE == loc_u8_trouve) //CONDITION: aucun canal configuré, on passe en mode automatique
					{
						//on passe en mode auto
						loc_u16_min_index = u16GetIdx_Min_ForMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u8_mode_802_11x);
						loc_u16_max_index = u16GetIdx_Max_ForMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u8_mode_802_11x);

						if((IDX_CHANNEL_UNKNOWN != loc_u16_min_index)&&
						   (IDX_CHANNEL_UNKNOWN != loc_u16_max_index)
						  )
						{
							printf("athchans %d-%d\n",
								   s_list_freq_process_prncpl.s_channel[loc_u16_min_index].u16_ieee,
								   s_list_freq_process_prncpl.s_channel[loc_u16_max_index].u16_ieee);

							CmdSystem_Generique("athchans %d-%d",
												s_list_freq_process_prncpl.s_channel[loc_u16_min_index].u16_ieee,
												s_list_freq_process_prncpl.s_channel[loc_u16_max_index].u16_ieee);
						}
						else //CONDITION: ERREUR
						{
							printf("WlanN_Install_FrequenceWifi: ERREUR %d %d\n",
								   loc_u16_min_index, loc_u16_max_index);
							printf("athchans 0-255\n");
							CmdSystem_Generique("athchans 0-255");
						}
					}
					else
					{
						printf("athchans %s\n",loc_ps8_chainlist);
						CmdSystem_Generique("athchans %s",loc_ps8_chainlist);
					}*/
					break;
				case TYPE_SELECTION_CANAL_AUTO:
					/*loc_u16_min_index = u16GetIdx_Min_ForMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u8_mode_802_11x);
					loc_u16_max_index = u16GetIdx_Max_ForMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u8_mode_802_11x);

					if((IDX_CHANNEL_UNKNOWN != loc_u16_min_index)&&
					   (IDX_CHANNEL_UNKNOWN != loc_u16_max_index)
					  )
					{
						CmdSystem_Generique("athchans %d-%d",
											s_list_freq_process_prncpl.s_channel[loc_u16_min_index].u16_ieee,
											s_list_freq_process_prncpl.s_channel[loc_u16_max_index].u16_ieee);
					}
					else //CONDITION: ERREUR
					{
						printf("WlanN_Install_FrequenceWifi: ERREUR %d %d\n",
							   loc_u16_min_index, loc_u16_max_index);
						CmdSystem_Generique("athchans 0-255");
					}*/
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

}/*WlanN_Install_FrequenceWifi*/

//=====================================================================================
// Fonction		: WlanN_Get_ListFrequency
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/10/2010 -
// Description	: Récupère la liste des fréquences réglementaires
//=====================================================================================
void WlanN_Get_ListFrequency(void)
{
	struct ieee80211req_chaninfo loc_t_req_listchans;
	//struct iwreq loc_t_req;
	//s32sod	loc_s32_sockfd;

	printf("WlanN_Get_ListFrequency \n");
	
	//memset(&loc_t_req, 0, sizeof(loc_t_req)); //INIT
	/*
	//Edition de la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);
	loc_t_req.u.data.pointer = &loc_t_req_listchans;
	loc_t_req.u.data.length = sizeof(loc_t_req_listchans);

	//par ioctl
	//Open socket
	if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("WlanN_Get_ListFrequency: Could not create simple datagram socket \n");
	}
	else
	{
		//Perform IOCTL
		if(ioctl(loc_s32_sockfd, IEEE80211_IOCTL_GETCHANINFO, &loc_t_req) < 0)
		{
			perror("WlanN_Get_ListFrequency: ioctl failed \n");
		}
		else
		{
			if(loc_t_req.u.data.length == sizeof(loc_t_req_listchans))
			{
				if(loc_t_req_listchans.ic_nchans >= NB_MAX_CHANNEL)//CONDITION: il y a beaucoup trop de canal
				{//on ne va pas tout sauver
					perror("WlanN_Get_ListFrequency: no complete \n");
				}*/

				//Add by VuHai
				CmdSystem_Generique("iw list | grep -F '['  > %s",T_DEF_FILE_IWLISTFREQ.ps8_path_file);
				CmdSystem_Generique("sed -i -e \"s/(no IR, radar detection)//g\" %s",T_DEF_FILE_IWLISTFREQ.ps8_path_file);
				CmdSystem_Generique("sed -i -e \"s/disabled/0.00 dBm/g\" %s",T_DEF_FILE_IWLISTFREQ.ps8_path_file);
				//CmdSystem_Generique("mount -t debugfs
				//debugfs /sys/kernel/debug/"); Move
				//cmd to S70-system_actia.sh
				CmdSystem_Generique("cat /sys/kernel/debug/ieee80211/phy0/ht40allow_map > %s",T_DEF_FILE_HT40_ALLOW_MAP.ps8_path_file);
				CmdSystem_Generique("sed -i -e \"s/Disabled/Disabled NA/g\" %s",T_DEF_FILE_HT40_ALLOW_MAP.ps8_path_file);
				
				//Construction de la liste des fréquence
				BuildListFreq(&s_list_freq_process_prncpl, &loc_t_req_listchans);
			/*}
			else
			{
				perror("WlanN_Get_ListFrequency: length ko \n");
			}
		}
		//Close socket
		close(loc_s32_sockfd);
	}*/
	
}/*WlanN_Get_ListFrequency*/

//=====================================================================================
// Fonction		: WlanN_Install_ModeRSSI
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 17/02/2011 -
// Description	: Installe la configuration du mode RSSI
//=====================================================================================
void WlanN_Install_ModeRSSI(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	if(MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
		{
			case MODE_SECURITE_WIFI_AUCUN:
			case MODE_SECURITE_WIFI_WEP:
				CmdSystem_Generique("iwpriv %s fr_syslog 0",
									NOM_INTERFACE_WIFI);
				break;
			case MODE_SECURITE_WIFI_WPA:
			case MODE_SECURITE_WIFI_WPA_TKIP:
			case MODE_SECURITE_WIFI_WPA_AES:
			case MODE_SECURITE_WIFI_WPA2:
			case MODE_SECURITE_WIFI_WPA2_TKIP:
			case MODE_SECURITE_WIFI_WPA2_AES:
				CmdSystem_Generique("iwpriv %s fr_logIPlsb %lu",
									NOM_INTERFACE_WIFI,
									(loc_ps_config->s_admin.u32_syslog_adresse_IP & 0xFFFF));
				CmdSystem_Generique("iwpriv %s fr_logIPmsb %lu",
									NOM_INTERFACE_WIFI,
									((loc_ps_config->s_admin.u32_syslog_adresse_IP & 0xFFFF0000)>>16));
				CmdSystem_Generique("iwpriv %s fr_logPort %d",
									NOM_INTERFACE_WIFI,
									loc_ps_config->s_admin.u16_syslog_port);

				//Puis on active ou non (et on verrouille l'adresse IP)
				CmdSystem_Generique("iwpriv %s fr_syslog %d",
									NOM_INTERFACE_WIFI,
									loc_ps_config->s_admin.u8_mode_RSSI);
				break;
			default:
				break;
		}
	}
	else
	{
		CmdSystem_Generique("iwpriv %s fr_syslog 0",
							NOM_INTERFACE_WIFI);
	}
	
}/*WlanN_Install_ModeRSSI*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Wlan_N
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Initialisation du module de cfg_wlan_N
//=====================================================================================
void InitModule_Cfg_Wlan_N(void)
{
	u16_countryID_memorise = 0xFFFF;	//INIT
	strcpy(s8_code_string_country_memorise,"99"); //INIT Add by VuHai
}/*InitModule_Cfg_Wlan_N*/

