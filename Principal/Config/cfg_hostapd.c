/*========================================================================*/
/* NOM DU FICHIER  : cfg_hostapd.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/11/2009                                           */
/* Libelle         : Principal: Configuration du HOSTAPD				  */
/* Projet          : WRM100                                               */
/* Indice          : BE053                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/11/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Modification chemin des fichiers de configuration
//		/tmp/hostapd.conf => /etc/hostapd.conf
//BE007 25/01/2010 CM
// - Correction bug hostapd lors de modification paramètres réseau (en particulier ath0 down)
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE053 16/12/2010 CM
// - Correction bug commande pidof via hostapd
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_HOSTAPD

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"
#include "cfg_wlan_N.h" //Add by VuHai for table ISO3166_COUNTRY_CODE

#define FICHIER_CONFIG_HOSTAPD PATH_DIR_ETC	 "hostapd.conf"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: ExecReconfiguration_HostApd
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Reconfigurer le processus hostapd (si présent)
//=====================================================================================
void ExecReconfiguration_HostApd(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	//Reconfigurer (sans tuer le processus) ne fonctionne pas
	if(TRUE == u8TestOrdreReconfiguration(ORDRE_RECONFIG__HOSTAPD))
	{
//		loc_s32_pid = s32GetPidProcessus("hostapd", FICHIER_VAR_HOSTAPD_PID);
//		printf("PID Processus hostapd = %d \n",loc_s32_pid);
//	
//		if(loc_s32_pid > 0)
//		{
//			kill(loc_s32_pid, SIGHUP);//envoi signal vers processus pour reconfig
//		}

		printf("ExecReconfiguration_HostApd\n");
		//On stoppe le processus et on le relance
		Uninstall_Hostapd(loc_ps_config);
		Install_Hostapd(loc_ps_config);
	}
}/*ExecReconfiguration_HostApd*/

//=====================================================================================
// Fonction		: Install_Hostapd
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Installe hostapd
//=====================================================================================
void Install_Hostapd(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	
	printf("Install_Hostapd\n");
	//Création du fichier de configuration
	if(FALSE == u8CreationFichierCfgHostapd(loc_ps_config))
	{
		printf("Install_Hostapd: u8CreationFichierCfgHostapd KO \n");
	}
	//hostapd n'est pas démarré
	if(TRUE == s_debug_global_process_prncpl.u8_dbg_hostapd) //CONDITION: debug activé
	{
		//d: ---------- debug ------------------
		//on lance en mode debug
		CmdSystem_Generique("hostapd -ddt -T -P %s %s &",
							FICHIER_VAR_HOSTAPD_PID,
							FICHIER_CONFIG_HOSTAPD);
		//f: ---------- debug ------------------
	}
	else //CONDITION: debug désactivé
	{
		//on lance en deamon
		CmdSystem_Generique("hostapd -B -P %s %s &",
							FICHIER_VAR_HOSTAPD_PID,
							FICHIER_CONFIG_HOSTAPD);
	}
	printf("************ VuHai:  Start  SET bitrate  ************\n");
	sleep(1);

	u16sod  u16_ieee;
	u16sod  loc_u16_index;
	/*printf("************ Channel 2 ************\n");
	CmdIfconfig_Down(NOM_INTERFACE_WIFI);
	loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
	u16_ieee = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_ieee;
	CmdSystem_Generique("iw %s set channel %d HT20",
			    NOM_INTERFACE_WIFI,
			    u16_ieee);
	CmdIfconfig_Up(NOM_INTERFACE_WIFI, loc_ps_config);
	printf("************ Channel 2 ************\n");*/
	//Data rate
	switch(loc_ps_config->s_wifi.u8_data_rate)
	{
		case DATA_RATE_AUTOMATIC:
			
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
			printf("iwconfig %s rate %dk\n",
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
		case DATA_RATE_MCS16:
		case DATA_RATE_MCS17:
		case DATA_RATE_MCS18:
		case DATA_RATE_MCS19:
		case DATA_RATE_MCS20:
		case DATA_RATE_MCS21:
		case DATA_RATE_MCS22:
		case DATA_RATE_MCS23:
				//iwpriv ath0 set11NRates $6
				//iwpriv ath0 set11NRetries 0x01
			/*printf("iwpriv %s set11NRates 0x%02X\n",
					    NOM_INTERFACE_WIFI,
					    T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);*/
			//printf(" set11NRates %d\n",T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
			if(TRUE == u8IsMode80211ng(loc_ps_config->s_wifi.u8_mode_802_11x))
			{
				if(GUARD_INTERVAL_SHORT == loc_ps_config->s_wifi.u8_11n_guard_interval)
					CmdSystem_Generique("iw %s set bitrates legacy-2.4 ht-mcs-2.4 %d sgi-2.4",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
				else	CmdSystem_Generique("iw %s set bitrates legacy-2.4 ht-mcs-2.4 %d",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
			}
			if(TRUE == u8IsMode80211na(loc_ps_config->s_wifi.u8_mode_802_11x))
			{
				if(GUARD_INTERVAL_SHORT == loc_ps_config->s_wifi.u8_11n_guard_interval)
					CmdSystem_Generique("iw %s set bitrates legacy-5 ht-mcs-5 %d sgi-5",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
				else	CmdSystem_Generique("iw %s set bitrates legacy-5 ht-mcs-5 %d",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
			}	
			break;
		default:
			//printf("iwconfig %s rate auto",NOM_INTERFACE_WIFI);
					    
			break;
	}
	printf("************ VuHai:  Fin  SET bitrate ************\n");
	
	ClearOrdreReconfiguration(ORDRE_RECONFIG__HOSTAPD);
	//u8EditListFreqFile2();
	
}/*Install_Hostapd*/

//=====================================================================================
// Fonction		: Uninstall_Hostapd
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Désinstalle hostapd
//=====================================================================================
void Uninstall_Hostapd(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_Hostapd\n");

	//on tue le processus
	CmdSystem_Generique("killall hostapd");
	u8CmdSystem_RemoveFile(FICHIER_VAR_HOSTAPD_PID);
	u8CmdSystem_RemoveFile(FICHIER_HOSTAPD_DUMP);

	//on fait une pause
	sleep(1);
	
}/*Uninstall_Hostapd*/

//=====================================================================================
// Fonction		: u8CreationFichierCfgHostapd
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 24/11/2009 -
// Description	: Edition du fichier hostapd.conf pour le processus hostapd
//=====================================================================================
u8sod u8CreationFichierCfgHostapd(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	FILE *	loc_pf_file;
	u8sod	loc_u8_resultat;
	s8sod   s8_code_string_country[2];
	u16sod	loc_u16_index;
	u16sod  u16_ieee;	//Numero de canal
	s8sod   s8_flag_ht_capab[35+1];

	
	loc_u8_resultat = TRUE;			//INIT
	loc_u16_index = IDX_CHANNEL_UNKNOWN;	//INIT
	u16_ieee = 0;				//INIT

	if(NULL == (loc_pf_file = fopen(FICHIER_CONFIG_HOSTAPD, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgHostapd: Erreur creation fichier %s\n",FICHIER_CONFIG_HOSTAPD));
		loc_u8_resultat = FALSE;
	}
	else
	{
		fprintf(loc_pf_file,"interface=%s\n",NOM_INTERFACE_WIFI);
#ifdef _WRM100_ABG_SELECT
		fprintf(loc_pf_file,"driver=madwifi\n");
#endif
#ifdef _WRM100_N_SELECT
		fprintf(loc_pf_file,"driver=nl80211\n");//Modif by VuHai (from atheros to nl80211)
#endif
		fprintf(loc_pf_file,"bridge=%s\n",NOM_INTERFACE_BRIDGE);
		
		//Add by VuHai
		//fprintf(loc_pf_file,"ctrl_interface=/var/run/hostapd\n");
		
		strcpy(s8_code_string_country,ISO3166_COUNTRY_CODE[loc_ps_config->s_wifi.u8_countryID]);
		fprintf(loc_pf_file,"country_code=%s\n",s8_code_string_country);
		fprintf(loc_pf_file,"ieee80211d=1\n");//DFS support
		fprintf(loc_pf_file,"ieee80211h=1\n");//DFS support
		switch(loc_ps_config->s_wifi.u8_mode_802_11x)
		{
			case MODE_WIFI_802_11G:
				fprintf(loc_pf_file,"hw_mode=g\n");
				break;
			case MODE_WIFI_802_11A:
				fprintf(loc_pf_file,"hw_mode=a\n");
				break;
			case MODE_WIFI_802_11NGHT20:
				fprintf(loc_pf_file,"hw_mode=g\n");
				fprintf(loc_pf_file,"ieee80211n=1\n");
				strcpy(s8_flag_ht_capab,"[HT20]");
				break;
			case MODE_WIFI_802_11NGHT40PLUS:
				fprintf(loc_pf_file,"hw_mode=g\n");
				fprintf(loc_pf_file,"ieee80211n=1\n");
				strcpy(s8_flag_ht_capab,"[HT40+]");
				break;
			case MODE_WIFI_802_11NGHT40MINUS:
				fprintf(loc_pf_file,"hw_mode=g\n");
				fprintf(loc_pf_file,"ieee80211n=1\n");
				strcpy(s8_flag_ht_capab,"[HT40-]");
				break;
			case MODE_WIFI_802_11NAHT20:
				fprintf(loc_pf_file,"hw_mode=a\n");
				fprintf(loc_pf_file,"ieee80211n=1\n");
				strcpy(s8_flag_ht_capab,"[HT20]");
				break;
			case MODE_WIFI_802_11NAHT40PLUS:
				fprintf(loc_pf_file,"hw_mode=a\n");
				fprintf(loc_pf_file,"ieee80211n=1\n");
				strcpy(s8_flag_ht_capab,"[HT40+]");
#ifdef _TEST_AC			
				fprintf(loc_pf_file,"ieee80211ac=1\n");
				fprintf(loc_pf_file,"vht_oper_chwidth=1\n");
				fprintf(loc_pf_file,"vht_oper_centr_freq_seg0_idx=42\n");
#endif
				break;
			case MODE_WIFI_802_11NAHT40MINUS:
				fprintf(loc_pf_file,"hw_mode=a\n");
				fprintf(loc_pf_file,"ieee80211n=1\n");
				strcpy(s8_flag_ht_capab,"[HT40-]");
				break;
			default:
				fprintf(loc_pf_file,"hw_mode=g\n");
				break;
		}//Fin Add by VuHai
		// hostapd event logger configuration
		//
		// Two output method: syslog and stdout (only usable if not forking to
		// background).
		//
		// Module bitfield (ORed bitfield of modules that will be logged; -1 = all
		// modules):
		// bit 0 (1) = IEEE 802.11
		// bit 1 (2) = IEEE 802.1X
		// bit 2 (4) = RADIUS
		// bit 3 (8) = WPA
		// bit 4 (16) = driver interface
		// bit 5 (32) = IAPP
		// bit 6 (64) = MLME
		//
		// Levels (minimum value for logged events):
		//  0 = verbose debugging
		//  1 = debugging
		//  2 = informational messages
		//  3 = notification
		//  4 = warning

		//Add by VuHai
		//fprintf(loc_pf_file,"local_pwr_constraint=127\n");
		//fprintf(loc_pf_file,"spectrum_mgmt_required=1\n");		      
		if(MODE_NETWORK_BRIDGE == loc_ps_config->s_gene.u8_mode_network)
		{
			fprintf(loc_pf_file,"wds_sta=1\n");	
		}
		
		//Set up ht_capab if mode 80211n
		if(GUARD_INTERVAL_SHORT == loc_ps_config->s_wifi.u8_11n_guard_interval)
		{
			if(TRUE == u8IsMode80211nHT40(loc_ps_config->s_wifi.u8_mode_802_11x))
				strcat(s8_flag_ht_capab,"[SHORT-GI-20][SHORT-GI-40]");
			else
				strcat(s8_flag_ht_capab,"[SHORT-GI-20]");
		}
		if(TRUE == u8IsMode80211n(loc_ps_config->s_wifi.u8_mode_802_11x))
			fprintf(loc_pf_file,"ht_capab=%s[SMPS-STATIC][TX-STBC][RX-STBC1][MAX-AMSDU-7935][DSSS_CCK-40]\n",s8_flag_ht_capab);
		//Set up the channel
		loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
		//printf("HOST APD: u16_index = %d \n", loc_u16_index);
		if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
		{
			u16_ieee = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_ieee;
			//printf("HOST APD: u16_ieee = %d \n", u16_ieee);
			fprintf(loc_pf_file,"channel=%d\n",u16_ieee);
		}
		else printf("u8CreationFichierCfgHostapd: Index for channel is UNKNOWN\n");

		//Set up Fragementation threshold
		if((TRUE == u8IsMode80211ag(loc_ps_config->s_wifi.u8_mode_802_11x))||
		   (TRUE == u8IsMode80211b(loc_ps_config->s_wifi.u8_mode_802_11x))
		  )//CONDITION: valable pour 11a/11g et 11b
		{
			fprintf(loc_pf_file,"fragm_threshold=%d\n",loc_ps_config->s_wifi.u16_protcl_fragment_threshold);
		}
		
		//Set up RTC/CTS threshold
		switch(loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold)
		{
			case WF_RTS_CTS_THRESHOLD_MAX:
				fprintf(loc_pf_file,"rts_threshold=%d\n",WF_RTS_CTS_THRESHOLD_MAX);
				break;
			default:
				fprintf(loc_pf_file,"rts_threshold=%d\n", loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold);	
				break;
		}

		//Set up Beacon Interval
		fprintf(loc_pf_file,"beacon_int=%d\n",loc_ps_config->s_wifi.u16_protcl_beacon_period);

		//Mask SSID
		if(TRUE == loc_ps_config->s_wifi.u8_masquage_ssid)
		{
			printf("Hostapd: Hide SSID\n");
			fprintf(loc_pf_file,"ignore_broadcast_ssid=2\n");
		}

		//WMM (Wireless for MultiMedia)
		if(TRUE == loc_ps_config->s_wifi.u8_activation_WMM)
		{
			printf("Hostapd: WMM Enabled\n");
			fprintf(loc_pf_file,"wmm_enabled=1\n");
		}
		//Fin Add by VuHai
		
		fprintf(loc_pf_file,"logger_syslog=-1\n");
		fprintf(loc_pf_file,"logger_syslog_level=0\n");	//SYSLOG: envoie de tous les messages
		fprintf(loc_pf_file,"logger_stdout=-1\n");
		fprintf(loc_pf_file,"logger_stdout_level=2\n");
		
		fprintf(loc_pf_file,"ctrl_interface_group=0\n");
		fprintf(loc_pf_file,"macaddr_acl=0\n");
		if(WPA_AUTHENTIFICATION_PSK == loc_ps_config->s_wifi.s_wpa_security.u8_authentification)
		{
			fprintf(loc_pf_file,"auth_algs=1\n");
		}
		else //WPA_AUTHENTIFICATION_EAP
		{
			//IEEE 802.11 specifies two authentication algorithms (Open System Authentication / Shared Key Authentication)
			fprintf(loc_pf_file,"auth_algs=1\n");
			//The own IP address of the access point (used as NAS-IP-Address)
			fprintf(loc_pf_file,"own_ip_addr=%s\n",
					ps8GetStringIp(ADRESSE_IP_LOCALE));
			//Optional NAS-Identifier string for RADIUS messages
//			fprintf(loc_pf_file,"nas_identifier=wpa1\n"); //ce n'est pas utile
			//RADIUS authentication server
			fprintf(loc_pf_file,"auth_server_addr=%s\n",
					ps8GetStringIp(loc_ps_config->s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip));
			fprintf(loc_pf_file,"auth_server_port=%d\n",
					loc_ps_config->s_wifi.s_wpa_security.s_server_radius.u16_radius_port);
			fprintf(loc_pf_file,"auth_server_shared_secret=%s\n",
					loc_ps_config->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared);
#if 0
			//RADIUS accounting server
			fprintf(loc_pf_file,"acct_server_addr=%s\n",
					ps8GetStringIp(loc_ps_config->s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip));
			fprintf(loc_pf_file,"acct_server_port=%d\n",PORT_UDP__ACCT_RADIUS);
			fprintf(loc_pf_file,"acct_server_shared_secret=%s\n",
					loc_ps_config->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared);
#endif
			//Require IEEE 802.1X authorization
			fprintf(loc_pf_file,"ieee8021x=1\n");
			//EAP reauthentication period
			fprintf(loc_pf_file,"eap_reauth_period=%lu\n",
				   loc_ps_config->s_wifi.s_wpa_security.u32_eap_reauth_period);
		}
		fprintf(loc_pf_file,"eapol_key_index_workaround=0\n");
		fprintf(loc_pf_file,"eapol_version=1\n");
		fprintf(loc_pf_file,"eap_server=0\n");
		//fprintf(loc_pf_file,"dump_file=%s\n",FICHIER_HOSTAPD_DUMP);Modif
		//by VuHai
		
		fprintf(loc_pf_file,"ssid=%s\n",
			   loc_ps_config->s_wifi.ps8_ssid_primary);

		switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
		{
			case MODE_SECURITE_WIFI_WPA:
			case MODE_SECURITE_WIFI_WPA_TKIP:
			case MODE_SECURITE_WIFI_WPA_AES:
				fprintf(loc_pf_file,"wpa=1\n");
				break;
			case MODE_SECURITE_WIFI_WPA2:
			case MODE_SECURITE_WIFI_WPA2_TKIP:
			case MODE_SECURITE_WIFI_WPA2_AES:
				fprintf(loc_pf_file,"wpa=2\n");
				break;
			default:
				fprintf(loc_pf_file,"wpa=0\n");
				break;
		}

		if(WPA_AUTHENTIFICATION_PSK == loc_ps_config->s_wifi.s_wpa_security.u8_authentification)
		{
			fprintf(loc_pf_file,"wpa_key_mgmt=WPA-PSK\n");
			switch(loc_ps_config->s_wifi.s_wpa_security.u8_wpa_key_type)
			{
				case KEY_TYPE_HEXA:
					fprintf(loc_pf_file,"wpa_psk=%s\n",
							loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key);
					break;
				case KEY_TYPE_ASCII:
					fprintf(loc_pf_file,"wpa_passphrase=%s\n",
							loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key);
					break;
				default:
					break;
			}			
		}
		else //WPA_AUTHENTIFICATION_EAP
		{
			fprintf(loc_pf_file,"wpa_key_mgmt=WPA-EAP\n");
		}

		switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
		{
			case MODE_SECURITE_WIFI_WPA:
			case MODE_SECURITE_WIFI_WPA2:
				fprintf(loc_pf_file,"wpa_pairwise=TKIP CCMP\n");
				break;
			case MODE_SECURITE_WIFI_WPA_TKIP:
			case MODE_SECURITE_WIFI_WPA2_TKIP:
				fprintf(loc_pf_file,"wpa_pairwise=TKIP\n");
				break;
			case MODE_SECURITE_WIFI_WPA_AES:
			case MODE_SECURITE_WIFI_WPA2_AES:
				fprintf(loc_pf_file,"wpa_pairwise=CCMP\n");
				break;
			default:
				break;
		}
		fprintf(loc_pf_file,"wpa_group_rekey=%lu\n",loc_ps_config->s_wifi.s_wpa_security.u32_gp_key_update_interval);
		
		//fermeture du fichier
		fclose(loc_pf_file);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_HOSTAPD, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgHostapd*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Hostapd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Initialisation du module de cfg_hostapd
//=====================================================================================
void InitModule_Cfg_Hostapd(void)
{
	
}/*InitModule_Cfg_Hostapd*/

