/*========================================================================*/
/* NOM DU FICHIER  : cfg_wlan_ABG.c		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/09/2010                                           */
/* Libelle         : Principal: Configuration du Wifi (ABG)				  */
/* Projet          : WRM100                                               */
/* Indice          : BE056                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 15/09/2010 CM
// - CREATION
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
// - Ajout gestion debit MCS pour 802.11n
// - Configuration seuil de framentation (adv wifi) non autorisé en 11n
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE055 17/01/2011 CM
// - Correction en mode monitor ne pas configurer ssid
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_WLAN_ABG


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u16sod u16_countryID_memorise;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: WlanABG_Install_Wifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (basic)
//=====================================================================================
void WlanABG_Install_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	//Channel spectrum width (20MHz)
	CmdSystem_Generique("iwpriv %s set_channel_bw \"%d\"",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.ps_channel_spectrum_width[CHANNEL_SPECTRUM_WIDTH_20_MHZ].u16_valeur);

	//802.11 mode
	switch(loc_ps_config->s_wifi.u8_mode_802_11x)
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
		default:
			CmdSystem_Generique("iwpriv %s mode 0", //auto
								NOM_INTERFACE_WIFI);
			break;
	}

	//Gestion du mode monitor
	if(MODE_RADIO_MODEM_MONITOR == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		CmdSystem_Generique("echo '803' > /proc/sys/net/ath0/dev_type"); //format radiotap
	}
	
	//Attention en ABG: il s'agit en fait de la valeur du regdomain
	if(u16_countryID_memorise != u16_countryID_debug)
	{
		//On peut récupérer la liste des fréquences réglementaires
		WlanABG_Get_ListFrequency();
		u16_countryID_memorise = u16_countryID_debug;
	}

	//Fréquence
	Install_FrequenceWifi(loc_ps_config);

	//Paramètres spécifiques au mode du radio modem
	switch(loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
			//On configure l'intervalle beacon
			CmdSystem_Generique("iwpriv %s bintval %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u16_protcl_beacon_period);

			break;
		case MODE_RADIO_MODEM_STATION:
			//on désactive bgscan
			CmdSystem_Generique("iwpriv %s bgscan 0",
								NOM_INTERFACE_WIFI);
			break;
		case MODE_RADIO_MODEM_MONITOR:
		default:
			break;
	}

	if((MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
	  )
	{
		//SSID
		CmdSystem_Generique("iwconfig %s essid \"%s\"",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.ps8_ssid_primary);
	}

	if(MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		//Mask SSID
		CmdSystem_Generique("iwpriv %s hide_ssid %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.u8_masquage_ssid);
	}

	//Puissance d'emission
	Install_TxPowerWifi(loc_ps_config);

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
		default:
			CmdSystem_Generique("iwconfig %s rate auto",
								NOM_INTERFACE_WIFI);
			break;
	}
	//Nombre maximum de stations associées
#warning "A CODER: iwpriv nb max_station_associees"


}/*WlanABG_Install_Wifi*/

//=====================================================================================
// Fonction		: WlanABG_Install_AdvWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du advwifi (avancé et antennes)
//=====================================================================================
void WlanABG_Install_AdvWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_valeur; 

	loc_u8_valeur = 0; //INIT

	//Paramètres spécifiques au mode du radio modem
	switch(loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
			//Intervalle beacon
			CmdSystem_Generique("iwpriv %s bintval %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u16_protcl_beacon_period);
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
		CmdSystem_Generique("echo '%d' > %s",
							loc_ps_config->s_wifi.u16_protcl_ABG_ACK_timeout,
							FICHIER__SYS_DEV_WIFI0_ACKTIMEOUT);

		//Type du preambule (court , long) only 802.11b
		if(MODE_WIFI_802_11B == loc_ps_config->s_wifi.u8_mode_802_11x)
		{
			if(FALSE == u8WlanABG_SetWifiTypePreambule(loc_ps_config->s_wifi.u8_protcl_type_preambule))
			{
				printf("Install_AdvWifi: u8WlanABG_SetWifiTypePreambule KO\n");
			}
			else
			{
				printf("Install_AdvWifi: u8WlanABG_SetWifiTypePreambule OK\n");
			}
		}

		if((TRUE == u8IsMode80211ag(loc_ps_config->s_wifi.u8_mode_802_11x))||
		   (TRUE == u8IsMode80211b(loc_ps_config->s_wifi.u8_mode_802_11x))
		  )//CONDITION: valable pour 11a/11g et 11b
		{
			//Fragmentation threshold
			CmdSystem_Generique("iwconfig %s frag %d",
								NOM_INTERFACE_WIFI,
								loc_ps_config->s_wifi.u16_protcl_fragment_threshold);
		}

		//RTC/CTS threshold
		switch(loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold)
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
		}

#if VERSION_WRM100_DEMO
#else
		//RTS_retry_limit
		CmdSystem_Generique("iwconfig %s retry %d",
							NOM_INTERFACE_WIFI,
							loc_ps_config->s_wifi.u16_protcl_RTS_retry_limit);
#endif
#warning "PROBLEME: iwconfig RTS_retry_limit"
	}

	//Sélection de l'antenne TX
	loc_u8_valeur = 0; //RAZ
	switch(loc_ps_config->s_wifi.u8_ant_ABG_tx_selection)
	{
		case ABG_SELECT_TX_ANTENNE_1:
			loc_u8_valeur = 1; //use antenna 1
			break;
		case ABG_SELECT_TX_ANTENNE_2:
			loc_u8_valeur = 2; //use antenna 2
			break;
		default:
			break;
	}
	CmdSystem_Generique("echo '%d' > %s",
						loc_u8_valeur,
						FICHIER__SYS_DEV_WIFI0_TXANTENNA);

	//Sélection de l'antenne RX
	loc_u8_valeur = 0; //RAZ
	switch(loc_ps_config->s_wifi.u8_ant_ABG_rx_selection)
	{
		case ABG_SELECT_RX_ANTENNE_1:
			loc_u8_valeur = 1; //use antenna 1
			break;
		case ABG_SELECT_RX_ANTENNE_2:
			loc_u8_valeur = 2; //use antenna 2
			break;
		case ABG_SELECT_RX_DIVERSITY:
			loc_u8_valeur = 0; //use diversity 
			break;
		default:
			break;
	}
	CmdSystem_Generique("echo '%d' > %s",
						loc_u8_valeur,
						FICHIER__SYS_DEV_WIFI0_RXANTENNA);
	if(ABG_SELECT_RX_DIVERSITY == loc_ps_config->s_wifi.u8_ant_ABG_rx_selection)
	{
		CmdSystem_Generique("echo '1' > %s", //enabled
							FICHIER__SYS_DEV_WIFI0_DIVERSITY);
	}
	else
	{
		CmdSystem_Generique("echo '0' > %s", //disabled
							FICHIER__SYS_DEV_WIFI0_DIVERSITY);
	}

}/*WlanABG_Install_AdvWifi*/

//=====================================================================================
// Fonction		: WlanABG_Install_FrequenceWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (fréquence)
//=====================================================================================
void WlanABG_Install_FrequenceWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_frequence;
	u16sod	loc_u16_index;
	u8sod	loc_u8_i;
	u8sod	loc_u8_trouve;

	loc_u16_frequence = 0; //INIT
	loc_u16_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u8_trouve = FALSE;	//INIT

	switch(loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_ACCESS_POINT:
		case MODE_RADIO_MODEM_MONITOR:
			//On configure la fréquence
			loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
			if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
			{
				loc_u16_frequence = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_freq_MHz;
				CmdSystem_Generique("iwconfig %s freq %dM",
									NOM_INTERFACE_WIFI,
									loc_u16_frequence);
			}
			break;
		case MODE_RADIO_MODEM_STATION:
			switch(loc_ps_config->s_wifi.u8_type_selection_canal)
			{
				case TYPE_SELECTION_CANAL_ISO:
					loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
					if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
					{
						loc_u16_frequence = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_freq_MHz;
						CmdSystem_Generique("iwpriv %s setchanlist -ALL",
											NOM_INTERFACE_WIFI);
						CmdSystem_Generique("iwpriv %s setchanlist +%d",
											NOM_INTERFACE_WIFI,
											loc_u16_frequence);
					}
					break;
				case TYPE_SELECTION_CANAL_MULTI:
					CmdSystem_Generique("iwpriv %s setchanlist -ALL",
										NOM_INTERFACE_WIFI);
					loc_u8_trouve = FALSE;	//RAZ
					for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
					{
						if(CHANNEL_RADIO_DISABLED != loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i])
						{
							loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i], loc_ps_config->s_wifi.u8_mode_802_11x);
							if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
							{
								loc_u16_frequence = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_freq_MHz;
								CmdSystem_Generique("iwpriv %s setchanlist +%d",
													NOM_INTERFACE_WIFI,
													loc_u16_frequence);
								loc_u8_trouve = TRUE;
							}
						}
					}
					if(FALSE == loc_u8_trouve) //CONDITION: aucun canal configuré, on passe en mode automatique
					{
						CmdSystem_Generique("iwpriv %s setchanlist +ALL",
											NOM_INTERFACE_WIFI);
					}
					break;
				case TYPE_SELECTION_CANAL_AUTO:
					CmdSystem_Generique("iwpriv %s setchanlist +ALL",
										NOM_INTERFACE_WIFI);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

}/*WlanABG_Install_FrequenceWifi*/

//=====================================================================================
// Fonction		: WlanABG_Get_ListFrequency
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/01/2011 -
// Description	: Récupère la liste des fréquences réglementaires
//=====================================================================================
void WlanABG_Get_ListFrequency(void)
{
	struct ieee80211req_chaninfo loc_t_req_listchans;
	struct iwreq loc_t_req;
	s32sod	loc_s32_sockfd;

	printf("WlanABG_Get_ListFrequency \n");

	memset(&loc_t_req, 0, sizeof(loc_t_req)); //INIT

	//Edition de la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);
	loc_t_req.u.data.pointer = &loc_t_req_listchans;
	loc_t_req.u.data.length = sizeof(loc_t_req_listchans);

	//par ioctl
	//Open socket
	if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("WlanABG_Get_ListFrequency: Could not create simple datagram socket \n");
	}
	else
	{
		//Perform IOCTL
		if(ioctl(loc_s32_sockfd, IEEE80211_IOCTL_GETCHANINFO, &loc_t_req) < 0)
		{
			perror("WlanABG_Get_ListFrequency: ioctl failed \n");
		}
		else
		{
			if(loc_t_req.u.data.length == sizeof(loc_t_req_listchans))
			{
				if(loc_t_req_listchans.ic_nchans >= NB_MAX_CHANNEL)//CONDITION: il y a beaucoup trop de canal
				{//on ne va pas tout sauver
					perror("WlanABG_Get_ListFrequency: no complete \n");
				}

				//Construction de la liste des fréquence
//				BuildListFreq_ABG(&s_list_freq_process_prncpl, &loc_t_req_listchans);
				BuildListFreq(&s_list_freq_process_prncpl, &loc_t_req_listchans);

//				{//debugCM
//					u16sod loc_u16_i;
//					struct ieee80211_channel *loc_pt_channel;
//					for (loc_u16_i=0; ((loc_u16_i<loc_t_req_listchans.ic_nchans)&&(loc_u16_i < NB_MAX_CHANNEL)); loc_u16_i++)
//					{
//						loc_pt_channel = &loc_t_req_listchans.ic_chans[loc_u16_i]; //RAZ
//						printf("%d: %dMHz ieee=%d \n",loc_u16_i,loc_pt_channel->ic_freq,loc_pt_channel->ic_ieee);
//					}
//				}
			}
			else
			{
				perror("WlanABG_Get_ListFrequency: length ko \n");
			}
		}
		//Close socket
		close(loc_s32_sockfd);
	}

}/*WlanABG_Get_ListFrequency*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Wlan_ABG
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Initialisation du module de cfg_wlan_ABG
//=====================================================================================
void InitModule_Cfg_Wlan_ABG(void)
{
	
}/*InitModule_Cfg_Wlan_ABG*/

