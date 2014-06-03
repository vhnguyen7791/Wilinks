/*========================================================================*/
/* NOM DU FICHIER  : mib_wrm100_data.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : NET-SNMP: MIB WRM100								  */
/* Projet          : WRM100                                               */
/* Indice          : BE059                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
// - CREATION
//BE019 16/03/2010 CM
// - Ajout MIB wrm100 dans agent SNMP
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE038 09/07/2010 CM
// - Ajout variables SNMP : stp (bridge), seuil rx (wifi), temperature
//BE040 13/09/2010 CM
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE053 16/12/2010 CM
// - Modification de la MIB / agent SNMP (suite integration Driver-N)
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
// - Correction bug dans MIB/agent SNMP variables specifique au mode radio modem
//BE055 17/01/2011 CM
// - Modification configuration des antennes
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
// - Modification gestion exploitation wifi
// - Ajout dans exploitation du canal en cours (sur AP et STA)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Correction bug sur variable SNMP mgmtWirelessAdv-Fragment-Thrsld
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_______II - DEFINE ______________________________________________________*/

#define MIB_WRM100_DATA_H

/*_______III - INCLUDES - DIRECTIVES ______________________________________*/
#include "headers.h"
#include "mib_wrm100_data.h"

/*_______IV  - PROTOTYPES IMPORTES _____________________MODULE______________*/

/** Function declarations */
/** ** for MIB Tree       */
WriteMethod write_descStruID;
WriteMethod write_descStruLocation;
WriteMethod write_descStruLanguage;
//Sous noeud command
WriteMethod write_cmdGeneralRestart;
WriteMethod write_cmdClearAlarms;
WriteMethod write_cmdClearLog;
WriteMethod write_cmdClearAll;
WriteMethod write_cmdGenerateLogFile;

/** ** for Tables         */
WriteMethod write_mgmtEvtUsed;
WriteMethod write_mgmtEvtLOG;
WriteMethod write_mgmtEvtSynthesis1;

/*_______VI  - PROCEDURES __________________________________________________*/

//=====================================================================================
// Fonction		: ps8CaptureString_wrm100
// Entrees		: <loc_s32_vpmagic> : 
//				  <loc_pt_write_method< : 
//				  <loc_pt_var_len< : 
// Sortie		: <loc_ps8_cp< : pointeur sur chaine retournée
// Auteur		: CM - 09/09/2009 -
// Description	: Gestion des variables scalaires de la MIB WRM100 de type STRING
//=====================================================================================
s8sod* ps8CaptureString_wrm100(s32sod loc_s32_vpmagic, WriteMethod ** loc_pt_write_method, size_t * loc_pt_var_len)
{
	s8sod	*loc_ps8_cp;
	u16sod	loc_u6_cpt_erreur;
	s32sod	loc_s32_sem;
	
	*loc_pt_var_len = 1; //INIT par defaut on renvoi 1 seul caractere!
	loc_ps8_cp = NULL; //INIT
	loc_u6_cpt_erreur = 0; //INIT

	//Variables de configuration
	switch (loc_s32_vpmagic)
	{
		case DESCSTRUID:
			loc_ps8_cp = &s_config_process_snmpd.s_admin.ps8_identifiant[0];
			*loc_pt_var_len = strlen(loc_ps8_cp);
			*loc_pt_write_method = write_descStruID;
			break;
		case DESCSTRULOCATION:
			loc_ps8_cp = &s_config_process_snmpd.s_admin.ps8_localisation[0];
			*loc_pt_var_len = strlen(loc_ps8_cp);
			*loc_pt_write_method = write_descStruLocation;
			break;
		case MGMTNETHOSTNAME:
			loc_ps8_cp = &s_config_process_snmpd.s_gene.ps8_hostname[0];
			*loc_pt_var_len = strlen(loc_ps8_cp);
			break;
		case MGMTNETBRIDGEIPADDRESS:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_bridge_adresse_ip);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETBRIDGEMASK:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_bridge_masque_reseau);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETBRIDGEGATEWAY:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_bridge_gateway);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETBRIDGEDHCPFALLBACKIP:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_bridge_dhcp_fallback_ip);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETLANIPADDRESS:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_lan_adresse_ip);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETLANMASK:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_lan_masque_reseau);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETWLANIPADDRESS:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_wlan_adresse_ip);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETWLANMASK:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_wlan_masque_reseau);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETWLANGATEWAY:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_wlan_gateway);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETWLANDHCPFALLBACKIP:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_wlan_dhcp_fallback_ip);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETVLAN_NAME:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(TRUE == s_config_process_snmpd.s_gene.u8_vlan_autoriser)
				{
					loc_ps8_cp = s_config_process_snmpd.s_gene.ps8_vlan_nom;
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETVLAN_NOTAGGEDLANIPADDRESS:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if((TRUE == s_config_process_snmpd.s_gene.u8_vlan_autoriser)&&
				   (TRUE == s_config_process_snmpd.s_gene.u8_vlan_interface_notag)
				  )
				{
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_vlan_notag_adresse_ip);
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNETVLAN_NOTAGGEDLANMASK:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if((TRUE == s_config_process_snmpd.s_gene.u8_vlan_autoriser)&&
				   (TRUE == s_config_process_snmpd.s_gene.u8_vlan_interface_notag)
				  )
				{
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_vlan_notag_masque_reseau);
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_NETWORK_ROUTER
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTWIRELESSSSID:
			loc_ps8_cp = &s_config_process_snmpd.s_wifi.ps8_ssid_primary[0];
			*loc_pt_var_len = strlen(loc_ps8_cp);
			break;
		case MGMTWIRELESSCHANNELSPECTRUMWIDTH:
			loc_ps8_cp = &T_TB_VAL.ps_channel_spectrum_width[T_TB_VAL.pt_definition_mode_wifi[s_config_process_snmpd.s_wifi.u8_mode_802_11x].u8_channelspectrumwidth].ps8_message[0];
			*loc_pt_var_len = strlen(loc_ps8_cp);
			break;
		case MGMTWIRELESSSECONDARYSSID:
#ifdef _WRM100_ABG_SELECT
			strcpy(ps8_data_a_tout_faire,"");
			loc_ps8_cp = ps8_data_a_tout_faire;
#endif
#ifdef _WRM100_N_SELECT
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == s_config_process_snmpd.s_wifi.u8_dual_ssid)
				{
					loc_ps8_cp = &s_config_process_snmpd.s_wifi.ps8_ssid_secondary[0];
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else	//MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
#endif
			break;
		case MGMTDHCPIPADDRESSSTART:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(FCT_DHCP_SERVER == s_config_process_snmpd.s_gene.u8_lan_fonction_dhcp)
				{
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_lan_dhcpsrv_ip_min);
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else //FCT_DHCP_NONE, FCT_DHCP_RELAY
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTDHCPIPADDRESSSTOP:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(FCT_DHCP_SERVER == s_config_process_snmpd.s_gene.u8_lan_fonction_dhcp)
				{
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_lan_dhcpsrv_ip_max);
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else //FCT_DHCP_NONE, FCT_DHCP_RELAY
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTDHCPRELAYTARGETIP:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(FCT_DHCP_RELAY == s_config_process_snmpd.s_gene.u8_lan_fonction_dhcp)
				{
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_gene.u32_lan_dhcprelay_ip);
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else //FCT_DHCP_NONE, FCT_DHCP_SERVER
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case MGMTNTP_SERVER:
			switch(s_config_process_snmpd.s_admin.u8_mode_mah)
			{
				case MODE_MAH_NTP:
				case MODE_MAH_SNTP:
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL]);
					*loc_pt_var_len = strlen(loc_ps8_cp);
					break;
				case MODE_MAH_MANUELLE:
				default:
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
			}
			break;
		case MGMTNTP_FALLBACKSERVER:
			switch(s_config_process_snmpd.s_admin.u8_mode_mah)
			{
				case MODE_MAH_NTP:
				case MODE_MAH_SNTP:
					loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS]);
					*loc_pt_var_len = strlen(loc_ps8_cp);
					break;
				case MODE_MAH_MANUELLE:
				default:
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
			}
			break;

		case MGMTLOGSYSTEM_IPADDRESS:
			if((TRUE == s_config_process_snmpd.s_admin.u8_syslog_activation)||
			   (TRUE == s_config_process_snmpd.s_admin.u8_mode_RSSI)
			  )
			{
				loc_ps8_cp = ps8GetStringIp(s_config_process_snmpd.s_admin.u32_syslog_adresse_IP);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
			
		default:
			loc_u6_cpt_erreur ++;
			break;   
	}
	
	
	
	//Variables d'exploitation
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	switch (loc_s32_vpmagic) {
		case DESCSTRUEQUIPMENTTYPE:
			loc_ps8_cp = ps8ConvertChaineToSnmp((s8sod*)S_DESCRIPT_EQUIPEMENT[ u8_snmp_type_equipement ].ps8_nom[u8_snmp_langue]);
			*loc_pt_var_len = strlen(loc_ps8_cp);
			break;
		case STANETWORKLAN_MACADDRESS:
			if(TRUE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
			{
				loc_ps8_cp = ps8GetChAddressMac(s_exploit_process_snmpd.s_general.ps_interface[INTERFACE_LAN].pu8_add_mac);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //Erreur lecture
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case STANETWORKLAN_IPADDRESS:
			if(TRUE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
			{
				loc_ps8_cp = s_exploit_process_snmpd.s_general.ps_interface[INTERFACE_LAN].ps8_add_ip;
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //Erreur lecture
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case STANETWORKWLAN_MACADDRESS:
			if(TRUE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
			{
				loc_ps8_cp = ps8GetChAddressMac(s_exploit_process_snmpd.s_general.ps_interface[INTERFACE_WLAN].pu8_add_mac);
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //Erreur lecture
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case STANETWORKWLAN_IPADDRESS:
			if(TRUE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
			{
				loc_ps8_cp = s_exploit_process_snmpd.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip;
				*loc_pt_var_len = strlen(loc_ps8_cp);
			}
			else //Erreur lecture
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case STAWIRELESSAP_CHANNELINUSE:
#ifdef _WRM100_ABG_SELECT
			strcpy(ps8_data_a_tout_faire,"");
			loc_ps8_cp = ps8_data_a_tout_faire;
#endif
#ifdef _WRM100_N_SELECT
			if(MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == u8FillExploitAccessPointFile(&s_exploit_process_snmpd.s_access_point))
				{
					sprintf(ps8_data_a_tout_faire,"%d MHz - CH=%d",
							s_exploit_process_snmpd.s_access_point.u16_freq_MHz_inprogress,
							s_exploit_process_snmpd.s_access_point.u16_channel_inprogress);
					loc_ps8_cp = ps8_data_a_tout_faire;
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else //Erreur lecture
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_RADIO_MODEM_STATION ou MODE_RADIO_MODEM_MONITOR
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
#endif
			break;
		case STAWIRELESSSTA_BSSID:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == u8GetWifiBSSID_Ioctl(&s_exploit_process_snmpd.s_station))
				{
					if(STATUT_CONNEXION__ASSOCIATED == s_exploit_process_snmpd.s_station.u8_statut_connexion)
					{
						sprintf(ps8_data_a_tout_faire,"%02X:%02X:%02X:%02X:%02X:%02X",
								s_exploit_process_snmpd.s_station.pu8_bssid_add_mac[0], s_exploit_process_snmpd.s_station.pu8_bssid_add_mac[1],
								s_exploit_process_snmpd.s_station.pu8_bssid_add_mac[2], s_exploit_process_snmpd.s_station.pu8_bssid_add_mac[3],
								s_exploit_process_snmpd.s_station.pu8_bssid_add_mac[4], s_exploit_process_snmpd.s_station.pu8_bssid_add_mac[5]);
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					else //CONDITION: BSS non détecté ou invalid
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
				}
				else
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case STAWIRELESSSTA_SSID:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == u8FillExploitStationFile(&s_exploit_process_snmpd.s_station))
				{
					loc_ps8_cp = &s_exploit_process_snmpd.s_station.ps8_ssid_inprogress[0];
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else //Erreur lecture
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		case STAWIRELESSSTA_CHANNELINUSE:
#ifdef _WRM100_ABG_SELECT
			strcpy(ps8_data_a_tout_faire,"");
			loc_ps8_cp = ps8_data_a_tout_faire;
#endif
#ifdef _WRM100_N_SELECT
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == u8FillExploitStationFile(&s_exploit_process_snmpd.s_station))
				{
					sprintf(ps8_data_a_tout_faire,"%d MHz - CH=%d",
							s_exploit_process_snmpd.s_station.u16_freq_MHz_inprogress,
							s_exploit_process_snmpd.s_station.u16_channel_inprogress);
					loc_ps8_cp = ps8_data_a_tout_faire;
					*loc_pt_var_len = strlen(loc_ps8_cp);
				}
				else //Erreur lecture
				{
					strcpy(ps8_data_a_tout_faire,"");
					loc_ps8_cp = ps8_data_a_tout_faire;
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
#endif
			break;
		case CMDLASTDATEOFCLEANINGALARMS:
			if(TRUE == u8FillExploitEventsGlobalFile(&s_exp_events_process_snmpd))
			{
				strcpy(ps8_data_a_tout_faire, ps8GetChDate(&s_exp_events_process_snmpd.s_date_dernier_reset));
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			else //CONDITION: erreur lecture
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			break;
		default:
			loc_u6_cpt_erreur ++;
			break;   
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	//Variable JDB
	switch (loc_s32_vpmagic) {
		case CMDLASTDATEOFCLEANINGLOG:
			s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
			if(TRUE == u8FillStatutJdb(&s_statutjdb_from_snmpd, IDXSTATUTJDB_RAM)) 
			{
				strcpy(ps8_data_a_tout_faire,ps8GetChDate(&s_statutjdb_from_snmpd.s_date_dernier_reset));
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			else //CONDITION: erreur lecture
			{
				strcpy(ps8_data_a_tout_faire,"");
				loc_ps8_cp = ps8_data_a_tout_faire;
			}
			s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
			break;
		default:
			loc_u6_cpt_erreur ++;
			break;   
	}
	
	
	if(loc_u6_cpt_erreur >= 3)
	{
		DEBUGMSGTL(("sodielec", "unknown sub-id %d in ps8CaptureString_wrm100\n", loc_s32_vpmagic));
	}
	
	return loc_ps8_cp;
}/*ps8CaptureString_wrm100*/

//=====================================================================================
// Fonction		: s32CaptureInt_wrm100
// Entrees		: <loc_s32_vpmagic> : 
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 09/09/2009 -
// Description	: Gestion des variables scalaires de la MIB WRM100 de type STRING
//=====================================================================================
s32sod s32CaptureInt_wrm100(s32sod loc_s32_vpmagic, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u6_cpt_erreur;
	s32sod  loc_s32_valeur;
	s32sod	loc_s32_sem;
	u16sod	loc_u16_index;
	u8sod	loc_u8_lecture_ok;
#ifdef _WRM100_N_SELECT
	struct ieee80211req_get_userinfo loc_t_userinfo_tempo;

	memset(&loc_t_userinfo_tempo, 0, sizeof(struct ieee80211req_get_userinfo)); //INIT
#endif

	long_return = 0; //INIT
	loc_u6_cpt_erreur = 0; //INIT
	loc_u16_index = 0; //INIT

	loc_s32_valeur = 0; //INIT
	loc_u8_lecture_ok = FALSE;	//INIT

	//Variables de configuration
	switch (loc_s32_vpmagic)
	{
		case DESCSTRULANGUAGE:
			long_return = s_config_process_snmpd.s_admin.u8_langue+1;
			*loc_pt_write_method = write_descStruLanguage;
			break;
		case MGMTMODERADIOMODEM:
			long_return = s_config_process_snmpd.s_gene.u8_mode_radio_modem+1;
			break;
		case MGMTNETMODE:
			long_return = s_config_process_snmpd.s_gene.u8_mode_network+1;
			break;
		case MGMTNETBRIDGEIPMODE:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_gene.u8_bridge_mode_ip+1;
			}
			else //MODE_NETWORK_ROUTER
			{
				long_return = 0;
			}
			break;
		case MGMTNETBRIDGESTP:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_gene.u8_bridge_stp+1;
			}
			else //MODE_NETWORK_ROUTER
			{
				long_return = 0;
			}
			break;
		case MGMTNETLANIPMODE:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = MODE_IP_STATIQUE+1;
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTNETWLANIPMODE:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_gene.u8_wlan_mode_ip+1;
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTNETVLAN_SUPPORT:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_gene.u8_vlan_autoriser+1;
			}
			else //MODE_NETWORK_ROUTER
			{
				long_return = 0;
			}
			break;
		case MGMTNETVLAN_ID:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(TRUE == s_config_process_snmpd.s_gene.u8_vlan_autoriser)
				{
					long_return = s_config_process_snmpd.s_gene.u16_vlan_id;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_NETWORK_ROUTER
			{
				long_return = 0;
			}
			break;
		case MGMTNETVLAN_RESERVENOTAGGEDLAN:
			if(MODE_NETWORK_BRIDGE == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(TRUE == s_config_process_snmpd.s_gene.u8_vlan_autoriser)
				{
					long_return = s_config_process_snmpd.s_gene.u8_vlan_interface_notag+1;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_NETWORK_ROUTER
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSSSIDMASK:
			if(MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				long_return = s_config_process_snmpd.s_wifi.u8_masquage_ssid+1;
			}
			else //MODE_RADIO_MODEM_STATION ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESS802DOT11MODE:
			long_return = s_config_process_snmpd.s_wifi.u8_mode_802_11x+1;
			break;
		case MGMTWIRELESSCHANNEL:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_MONITOR == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				long_return = s_config_process_snmpd.s_wifi.u16_iso_canal_radio;
			}
			else //MODE_RADIO_MODEM_STATION
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSFREQUENCY_MHZ:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_MONITOR == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_snmpd, s_config_process_snmpd.s_wifi.u16_iso_canal_radio, s_config_process_snmpd.s_wifi.u8_mode_802_11x);
				if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
				{
					long_return = s_list_freq_process_snmpd.s_channel[loc_u16_index].u16_freq_MHz;
				}
				else //ERREUR
				{
					long_return = 0;
				}
			}
			else //MODE_RADIO_MODEM_STATION
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSCHANNELMODE:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				long_return = s_config_process_snmpd.s_wifi.u8_type_selection_canal + 1;
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSISOCHANNEL:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TYPE_SELECTION_CANAL_ISO == s_config_process_snmpd.s_wifi.u8_type_selection_canal)
				{
					long_return = s_config_process_snmpd.s_wifi.u16_iso_canal_radio;
				}
				else //TYPE_SELECTION_CANAL_MULTI,TYPE_SELECTION_CANAL_AUTO
				{
					long_return = 0;
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSISOFREQUENCY_MHZ:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TYPE_SELECTION_CANAL_ISO == s_config_process_snmpd.s_wifi.u8_type_selection_canal)
				{
					loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_snmpd, s_config_process_snmpd.s_wifi.u16_iso_canal_radio, s_config_process_snmpd.s_wifi.u8_mode_802_11x);
					if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
					{
						long_return = s_list_freq_process_snmpd.s_channel[loc_u16_index].u16_freq_MHz;
					}
					else //ERREUR
					{
						long_return = 0;
					}
				}
				else //TYPE_SELECTION_CANAL_MULTI,TYPE_SELECTION_CANAL_AUTO
				{
					long_return = 0;
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;

		case MGMTWIRELESSTRANSMITTERPOWER_DBM:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				long_return = s_config_process_snmpd.s_wifi.u8_power_tx;
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSDATARATE:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				long_return = s_config_process_snmpd.s_wifi.u8_data_rate+1;
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSSECURITYMODE:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				long_return = s_config_process_snmpd.s_wifi.u8_mode_securite_wifi+1;
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSWPAAUTHENTICATION:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				switch(s_config_process_snmpd.s_wifi.u8_mode_securite_wifi)
				{
					case MODE_SECURITE_WIFI_AUCUN:
					case MODE_SECURITE_WIFI_WEP:
						long_return = 0;
						break;
					default: //WPA
						long_return = s_config_process_snmpd.s_wifi.s_wpa_security.u8_authentification+1;
						break;
				}
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSADV_ACKTIMEOUT:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
#ifdef _WRM100_ABG_SELECT
				long_return = s_config_process_snmpd.s_wifi.u16_protcl_ABG_ACK_timeout;
#endif
#ifdef _WRM100_N_SELECT
				long_return = s_config_process_snmpd.s_wifi.u16_protcl_N_ACK_timeout;
#endif
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSADV_PREAMBLETYPE:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				if(MODE_WIFI_802_11B == s_config_process_snmpd.s_wifi.u8_mode_802_11x)
				{
					long_return = s_config_process_snmpd.s_wifi.u8_protcl_type_preambule+1;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSADV_FRAGMENT_THRSLD:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				if((TRUE == u8IsMode80211ag(s_config_process_snmpd.s_wifi.u8_mode_802_11x))||
				   (TRUE == u8IsMode80211b(s_config_process_snmpd.s_wifi.u8_mode_802_11x))
				  )//CONDITION: valable pour 11a/11g et 11b
				{
					long_return = s_config_process_snmpd.s_wifi.u16_protcl_fragment_threshold;
				}
				else //Condition: 11n
				{
					long_return = 0;
				}
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSADV_RTS_CTS_THRSLD:
			long_return = s_config_process_snmpd.s_wifi.u16_protcl_RTS_CTS_threshold;
			break;
		case MGMTWIRELESSADV_BEACONPERIOD:
			if(MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				long_return = s_config_process_snmpd.s_wifi.u16_protcl_beacon_period;
			}
			else //MODE_RADIO_MODEM_STATION ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSADV_WMMENABLED:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
#ifdef _WRM100_ABG_SELECT
				long_return = 0;
#endif
#ifdef _WRM100_N_SELECT
				long_return = s_config_process_snmpd.s_wifi.u8_activation_WMM+1;
#endif
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSADV_DFSDISABLED:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
#ifdef _WRM100_ABG_SELECT
				long_return = 0;
#endif
#ifdef _WRM100_N_SELECT
				long_return = s_config_process_snmpd.s_wifi.u8_desactivation_DFS+1;
#endif
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSANTENNA_TRANSMITTER:
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
#ifdef _WRM100_ABG_SELECT
				switch(s_config_process_snmpd.s_wifi.u8_ant_ABG_tx_selection)
				{
					case ABG_SELECT_TX_ANTENNE_1:
						long_return = 1;
						break;
					case ABG_SELECT_TX_ANTENNE_2:
						long_return = 2;
						break;
					default:
						long_return = 0;
						break;
				}
#endif
#ifdef _WRM100_N_SELECT
				switch(s_config_process_snmpd.s_wifi.u8_ant_N_selection)
				{
					case N_SELECT_ANTENNE_1:
						long_return = 1;
						break;
					case N_SELECT_ANTENNES_1_ET_2:
						long_return = 3;
						break;
					case N_SELECT_ANTENNES_1_ET_2_ET_3:
						long_return = 4;
						break;
					default:
						long_return = 0;
						break;
				}
#endif
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSANTENNA_RECEIVER:
#ifdef _WRM100_ABG_SELECT
			switch(s_config_process_snmpd.s_wifi.u8_ant_ABG_rx_selection)
			{
				case ABG_SELECT_RX_ANTENNE_1:
					long_return = 1;
					break;
				case ABG_SELECT_RX_ANTENNE_2:
					long_return = 2;
					break;
				case ABG_SELECT_RX_DIVERSITY:
					long_return = 3;
					break;
				default:
					long_return = 0;
					break;
			}
#endif
#ifdef _WRM100_N_SELECT
			switch(s_config_process_snmpd.s_wifi.u8_ant_N_selection)
			{
				case N_SELECT_ANTENNE_1:
					long_return = 1;
					break;
				case N_SELECT_ANTENNES_1_ET_2:
					long_return = 4;
					break;
				case N_SELECT_ANTENNES_1_ET_2_ET_3:
					long_return = 5;
					break;
				default:
					long_return = 0;
					break;
			}
#endif
			break;
		case MGMTWIRELESSRECEIVEDLEVELTHRESHOLD_DBM:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				long_return = (s32sod)s_config_process_snmpd.s_wifi.s8_seuil_rx;
			}
			else	//MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
			break;
		case MGMTWIRELESSENABLESECONDARYSSID:
#ifdef _WRM100_ABG_SELECT
			long_return = 0;
#endif
#ifdef _WRM100_N_SELECT
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				long_return = s_config_process_snmpd.s_wifi.u8_dual_ssid+1;
			}
			else	//MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
#endif
			break;
		case MGMTWIRELESSGUARDINTERVAL:
#ifdef _WRM100_ABG_SELECT
			long_return = 0;
#endif
#ifdef _WRM100_N_SELECT
			if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)||
			   (MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			  )
			{
				if(TRUE == u8IsMode80211n(s_config_process_snmpd.s_wifi.u8_mode_802_11x))
				{
					long_return = s_config_process_snmpd.s_wifi.u8_11n_guard_interval+1;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
#endif
			break;
			
		case MGMTIPROUTINGRIP_ACTIVATION:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_ip_routing.u8_ripv2_activation+1;
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTIPROUTINGRIP_LANUSEDINTERFACE:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(TRUE == s_config_process_snmpd.s_ip_routing.u8_ripv2_activation)
				{
					long_return = s_config_process_snmpd.s_ip_routing.pu8_rip_interface_used[RIP_INTERF_LAN]+1;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTIPROUTINGRIP_WLANUSEDINTERFACE:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(TRUE == s_config_process_snmpd.s_ip_routing.u8_ripv2_activation)
				{
					long_return = s_config_process_snmpd.s_ip_routing.pu8_rip_interface_used[RIP_INTERF_WLAN]+1;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTIPROUTINGRIP_AUTHENTICATION:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(TRUE == s_config_process_snmpd.s_ip_routing.u8_ripv2_activation)
				{
					long_return = s_config_process_snmpd.s_ip_routing.u8_rip_authentification+1;
				}
				else
				{
					long_return = 0;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTDHCPFUNCTION:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_gene.u8_lan_fonction_dhcp+1;
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTDHCPLEASETIME:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				if(FCT_DHCP_SERVER == s_config_process_snmpd.s_gene.u8_lan_fonction_dhcp)
				{
					long_return = s_config_process_snmpd.s_gene.u32_lan_dhcpsrv_duree_vie_bail;
				}
				else //FCT_DHCP_NONE, FCT_DHCP_RELAY
				{
					long_return = 0;
				}
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTNAT_ENABLED:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_nat.u8_nat_activation+1;
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;
		case MGMTNTP_MODE:
			long_return = s_config_process_snmpd.s_admin.u8_mode_mah+1;
			break;
		case MGMTNTP_TIMEZONE:
			switch(s_config_process_snmpd.s_admin.u8_mode_mah)
			{
				case MODE_MAH_NTP:
				case MODE_MAH_SNTP:
				long_return = (long)(char signed)s_config_process_snmpd.s_admin.s_client_ntp.s8_fuseau_horaire;
					break;
				case MODE_MAH_MANUELLE:
				default:
					long_return = 0;
					break;
			}
			break;
		case MGMTNTP_SNTPUPDATEFREQUENCY:
			switch(s_config_process_snmpd.s_admin.u8_mode_mah)
			{
				case MODE_MAH_SNTP:
					long_return = s_config_process_snmpd.s_admin.s_client_ntp.u16_freq_maj_sntp;
					break;
				case MODE_MAH_NTP:
				case MODE_MAH_MANUELLE:
				default:
					long_return = 0;
					break;
			}
			break;
		case MGMTLOGSYSTEM_ENABLED:
			long_return = s_config_process_snmpd.s_admin.u8_syslog_activation+1;
			break;
		case MGMTLOGSYSTEM_PORT:
			if((TRUE == s_config_process_snmpd.s_admin.u8_syslog_activation)||
			   (TRUE == s_config_process_snmpd.s_admin.u8_mode_RSSI)
			  )
			{
				long_return = s_config_process_snmpd.s_admin.u16_syslog_port;
			}
			else
			{
				long_return = 0;
			}
			break;
		case MGMTLOGRSSIMODE_ENABLED:
#ifdef _WRM100_ABG_SELECT
			long_return = 0;
#endif
#ifdef _WRM100_N_SELECT
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				switch(s_config_process_snmpd.s_wifi.u8_mode_securite_wifi)
				{
					case MODE_SECURITE_WIFI_AUCUN:
					case MODE_SECURITE_WIFI_WEP:
						long_return = 0;
						break;
					case MODE_SECURITE_WIFI_WPA:
					case MODE_SECURITE_WIFI_WPA_TKIP:
					case MODE_SECURITE_WIFI_WPA_AES:
					case MODE_SECURITE_WIFI_WPA2:
					case MODE_SECURITE_WIFI_WPA2_TKIP:
					case MODE_SECURITE_WIFI_WPA2_AES:
						long_return = s_config_process_snmpd.s_admin.u8_mode_RSSI+1;
						break;
					default:
						break;
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0;
			}
#endif
			break;
		case MGMTMULTICAST_IGMPPROXY:
			if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
			{
				long_return = s_config_process_snmpd.s_multicast.u8_proxy_igmp_activation+1;
			}
			else //MODE_NETWORK_BRIDGE
			{
				long_return = 0;
			}
			break;

		default:
			loc_u6_cpt_erreur ++;
			break;
	}
	
	//Variables d'exploitation
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	switch (loc_s32_vpmagic)
	{
		case STAWIRELESSAP_NUMBERASSOCIATION:
			if(MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == u8FillExploitAccessPointFile(&s_exploit_process_snmpd.s_access_point))
				{
					long_return = s_exploit_process_snmpd.s_access_point.u16_nb_associations; 
				}
				else
				{
					long_return = 0; 
				}
			}
			else //MODE_RADIO_MODEM_STATION ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0; 
			}
			break;
		case STAWIRELESSSTA_STATUS:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
				if(TRUE == u8FillExploitStationFile(&s_exploit_process_snmpd.s_station))
				{
					if(STATUT_CONNEXION__ASSOCIATED == s_exploit_process_snmpd.s_station.u8_statut_connexion)
					{
						long_return = 2;	//connected
					}
					else
					{
						long_return = 1;	//not-connected
					}
				}
				else //Erreur lecture
				{
					long_return = 0; 
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = 0; 
			}
			break;
		case STAWIRELESSSTA_RSSI_DBM:
			if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
			{
//				if(TRUE == u8GetWifiRSSIRaw_Ioctl(&loc_s32_valeur))
#ifdef _WRM100_ABG_SELECT
				loc_u8_lecture_ok = u8WlanABG_GetWifiRSSIRaw_Ioctl(&loc_s32_valeur);
#endif
#ifdef _WRM100_N_SELECT
				loc_u8_lecture_ok = u8WlanN_GetWifiUserInfo_Ioctl(&loc_t_userinfo_tempo);
				if(TRUE == loc_u8_lecture_ok)
				{
					loc_s32_valeur = (u32sod)loc_t_userinfo_tempo.u8_rssi_raw;
				}
#endif
				if(TRUE == loc_u8_lecture_ok)
				{
					//On met à jour l'information RSSI avec la valeur brute (uniquement si valeur retournée par IOCTL est non nulle)
					//car de temps en temps, la fonction Ioctl retourne une valeur nulle!
					if(0 != loc_s32_valeur) //CONDITION: valeur RSSI non nulle
					{
						long_return = s32ConvertRssiToDBm(loc_s32_valeur);
					}
					else  //CONDITION: valeur RSSI nulle
					{
						//On met à jour l'information RSSI avec la valeur filtrée (issue de la base de données)
						if(TRUE == u8FillExploitStationFile(&s_exploit_process_snmpd.s_station))
						{
							long_return = s_exploit_process_snmpd.s_station.s32_rssi_dbm;
						}
						else
						{
							long_return = -999; 
						}
					}
				}
				else
				{
					long_return = -999; 
				}
			}
			else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
			{
				long_return = -999; 
			}
			break;
		case STAGENERALTEMPERATURE:
#ifdef _WRM100_ABG_SELECT
			if(TRUE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
			{
				if(VALEUR_TEMPERATURE_INCONNUE == s_exploit_process_snmpd.s_general.s32_temperature)
				{
					long_return = 0; 
				}
				else
				{
					long_return = s_exploit_process_snmpd.s_general.s32_temperature;
				}
			}
			else
			{
				long_return = 0; 
			}
#endif
#ifdef _WRM100_N_SELECT
			long_return = 0;
#endif
			break;
		default:
			loc_u6_cpt_erreur ++;
			break;
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	//Variables commandes
	switch (loc_s32_vpmagic) {
		case CMDGENERALRESTART:
			long_return = 1; //inactive
			*loc_pt_write_method = write_cmdGeneralRestart;
			break;
		case CMDCLEARALARMS:
			long_return = 1;	//inactive
			*loc_pt_write_method = write_cmdClearAlarms;
			break;
		case CMDCLEARLOG:
			long_return = 1;	//inactive
			*loc_pt_write_method = write_cmdClearLog;
			break;
		case CMDCLEARALL:
			long_return = 1;	//inactive
			*loc_pt_write_method = write_cmdClearAll;
			break;
		case CMDGENERATELOGFILE:
			long_return = 1;	//inactive
			*loc_pt_write_method = write_cmdGenerateLogFile;
			break;
		default:
			loc_u6_cpt_erreur ++;
			break;
	}
	
	if(loc_u6_cpt_erreur >= 3)
	{
		DEBUGMSGTL(("sodielec", "unknown sub-id %d in s32CaptureInt_wrm100\n", loc_s32_vpmagic));
	}
	
	return long_return;
}/*s32CaptureInt_wrm100*/


/** ** for Tables         */

//=====================================================================================
// Fonction		: captureString_funcSoftwareRevisionTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: type string de la table
//=====================================================================================
char *
   captureString_funcSoftwareRevisionTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	s32sod loc_s32_sem;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
	{
		loc_s32_vpmagic = (-1); //erreur
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	switch (loc_s32_vpmagic) {
		case FUNCSOFTWAREREVISIONDESCRIPTION:
			loc_ps8_cp = pt_tb_msg[u8_snmp_langue].ps8_msg_nom_logiciel[loc_s32_iindex];
			break;
		case FUNCSOFTWAREREVISIONNUMBER:
			switch(loc_s32_iindex)
			{
				case VERSION_LOGICIELLE_APPLI_CPU:
#if AFFICHAGE_NUMERO_PROGRAMME_VERSION_LOGICIELLE
					if(INFO_VERSION_PROG_NUMERO_1 == s_exploit_process_snmpd.s_general.s_version[loc_s32_iindex].u8_info_suppl)
					{
						sprintf(ps8_data_a_tout_faire,"%s (%s n°1)",
								loc_ps_exp_general->s_version[loc_s32_iindex].ps8_message,
								pt_tb_msg[u8_snmp_langue].ps8_msg_programme);
					}
					else
					{
						if(INFO_VERSION_PROG_NUMERO_2 == s_exploit_process_snmpd.s_general.s_version[loc_s32_iindex].u8_info_suppl)
						{
							sprintf(ps8_data_a_tout_faire,"%s (%s n°2)",
									s_exploit_process_snmpd.s_general.s_version[loc_s32_iindex].ps8_message,
									pt_tb_msg[u8_snmp_langue].ps8_msg_programme);
						}
						else
						{
							sprintf(ps8_data_a_tout_faire,"%s (%s n°?)",
									s_exploit_process_snmpd.s_general.s_version[loc_s32_iindex].ps8_message,
									pt_tb_msg[u8_snmp_langue].ps8_msg_programme);
						}
					}
#else
					sprintf(ps8_data_a_tout_faire,"%s",
							s_exploit_process_snmpd.s_general.s_version[loc_s32_iindex].ps8_message);
#endif
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				default:
					sprintf(ps8_data_a_tout_faire,"%s",
							s_exploit_process_snmpd.s_general.s_version[loc_s32_iindex].ps8_message);
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
			}
			break;
		default:
			DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_funcSoftwareRevisionTable\n", loc_s32_vpmagic));
			break;   
	}

	return loc_ps8_cp;
}/*captureString_funcSoftwareRevisionTable*/

//=====================================================================================
// Fonction		: captureInt_funcSoftwareRevisionTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: type Integer de la table
//=====================================================================================
long
   captureInt_funcSoftwareRevisionTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	long_return = 0; //INIT

	switch (loc_s32_vpmagic) {
		case FUNCSOFTWAREREVISIONINDEX:
			long_return = loc_s32_iindex + 1;
			break;
		default:
			DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_funcSoftwareRevisionTable\n", loc_s32_vpmagic));
			break;
	}
	return long_return;
}/*captureInt_funcSoftwareRevisionTable*/

//=====================================================================================
// Fonction		: captureString_mgmtWirelessMultiTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtWirelessMultiTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u8sod loc_u8_index_canal;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if((0 <= loc_s32_iindex) && (loc_s32_iindex < NB_MAX_MULTI_CANAUX))
	{
		switch (loc_s32_vpmagic) {
			default:
				break;   
		}
	}
	else
	{
		DEBUGMSGTL(("sodielec", "captureString_mgmtWirelessMultiTable index=%d KO\n", loc_s32_iindex));
	}

	return loc_ps8_cp;
}/*captureString_mgmtWirelessMultiTable*/

//=====================================================================================
// Fonction		: captureInt_mgmtWirelessMultiTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtWirelessMultiTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s32sod loc_s32_sem;
	u16sod loc_u16_index;

	long_return = 0; //INIT
	loc_u16_index = 0; //INIT

	if((0 <= loc_s32_iindex) && (loc_s32_iindex < NB_MAX_MULTI_CANAUX))
	{
		switch (loc_s32_vpmagic) {
			case MGMTWIRELESSMULTI_INDEX:
				long_return = (long)loc_s32_iindex;
				break;
			case MGMTWIRELESSMULTI_CHANNEL:
				if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
				{
					if(TYPE_SELECTION_CANAL_MULTI == s_config_process_snmpd.s_wifi.u8_type_selection_canal)
					{
						if(s_config_process_snmpd.s_wifi.pu16_multi_canal_radio[loc_s32_iindex] != CHANNEL_RADIO_DISABLED)
						{
							long_return = (long)s_config_process_snmpd.s_wifi.pu16_multi_canal_radio[loc_s32_iindex];
						}
						else//CONDITION: canal non sélectionné
						{
							long_return = (-1);
						}
					}
					else
					{
						long_return = 0;
					}
				}
				else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
				{
					long_return = 0;
				}
				break;
			case MGMTWIRELESSMULTI_FREQUENCY:
				if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
				{
					if(TYPE_SELECTION_CANAL_MULTI == s_config_process_snmpd.s_wifi.u8_type_selection_canal)
					{
						if(s_config_process_snmpd.s_wifi.pu16_multi_canal_radio[loc_s32_iindex] != CHANNEL_RADIO_DISABLED)
						{

							loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_snmpd, s_config_process_snmpd.s_wifi.pu16_multi_canal_radio[loc_s32_iindex], s_config_process_snmpd.s_wifi.u8_mode_802_11x);
							if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
							{
								long_return = s_list_freq_process_snmpd.s_channel[loc_u16_index].u16_freq_MHz;
							}
							else //ERREUR
							{
								long_return = 0;
							}
						}
						else//CONDITION: canal non sélectionné
						{
							long_return = (-1);
						}
					}
					else
					{
						long_return = 0;
					}
				}
				else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
				{
					long_return = 0;
				}
				break;
			default:
				break;   
		}
	}
	else
	{
		DEBUGMSGTL(("sodielec", "captureInt_mgmtWirelessMultiTable index=%d KO\n", loc_s32_iindex));
	}

	return long_return;
}/*captureInt_mgmtWirelessMultiTable*/

//=====================================================================================
// Fonction		: captureString_mgmtIProutingStaticTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtIProutingStaticTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;
	S_STRUCT_IP_ROUTE_STATIC	loc_s_route;	//une route

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_ROUTES_IP_STATIC)
		{
			loc_s_route = s_config_process_snmpd.s_ip_routing.ps_route_ip_static[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTIPROUTINGSTATIC_DESTINATIONIP:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_route.u32_destination_ip));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				case MGMTIPROUTINGSTATIC_DESTINATIONMASK:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_route.u32_destination_mask));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				case MGMTIPROUTINGSTATIC_GATEWAY:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_route.u32_gateway_ip));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_mgmtIProutingStaticTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_mgmtIProutingStaticTable\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_mgmtIProutingStaticTable*/

//=====================================================================================
// Fonction		: captureInt_mgmtIProutingStaticTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtIProutingStaticTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;
	S_STRUCT_IP_ROUTE_STATIC	loc_s_route;	//une route

	long_return = 0; //INIT

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_ROUTES_IP_STATIC)
		{
			loc_s_route = s_config_process_snmpd.s_ip_routing.ps_route_ip_static[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTIPROUTINGSTATIC_INDEX:
					long_return = loc_s32_iindex;
					break;
				case MGMTIPROUTINGSTATIC_INTERFACE:
					long_return = loc_s_route.u8_interface+1;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_mgmtIProutingStaticTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureInt_mgmtIProutingStaticTable\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_mgmtIProutingStaticTable*/

//=====================================================================================
// Fonction		: captureString_mgmtIProutingPolicyTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 22/04/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtIProutingPolicyTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;
	S_STRUCT_ROUTE_POLICY	loc_s_route;	//une route
	s8sod loc_ps8_addr_ip_start[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_ip_end[MAX_LG_FORMAT_ADRESSE_IP+1];

	loc_u16_index = (u16sod)loc_s32_iindex-1;
	strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_POLICY_ROUTING)
		{
			loc_s_route = s_config_process_snmpd.s_ip_routing.ps_route_policy[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTIPROUTINGPOLICY_IPSOURCEVALUE:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_IP])
					{
						strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(loc_s_route.u32_critere_src_ip_start));
						strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(loc_s_route.u32_critere_src_ip_end));
						sprintf(ps8_data_a_tout_faire,"%s - %s",
								loc_ps8_addr_ip_start,
								loc_ps8_addr_ip_end);
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					else
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					break;
				case MGMTIPROUTINGPOLICY_IPDESTINATIONVALUE:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_IP])
					{
						strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(loc_s_route.u32_critere_dst_ip_start));
						strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(loc_s_route.u32_critere_dst_ip_end));
						sprintf(ps8_data_a_tout_faire,"%s - %s",
								loc_ps8_addr_ip_start,
								loc_ps8_addr_ip_end);
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					else
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					break;
				case MGMTIPROUTINGPOLICY_PACKETLENGTHVALUE:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])
					{
						sprintf(ps8_data_a_tout_faire,"%d - %d",
								loc_s_route.u16_critere_len_packet_min,
								loc_s_route.u16_critere_len_packet_max);
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					else
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					break;
				case MGMTIPROUTINGPOLICY_PORTSOURCEVALUE:
					if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
					{
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])
						{
							sprintf(ps8_data_a_tout_faire,"%d - %d",
									loc_s_route.u16_critere_src_port_start,
									loc_s_route.u16_critere_src_port_end);
							loc_ps8_cp = ps8_data_a_tout_faire;
						}
						else
						{
							strcpy(ps8_data_a_tout_faire,"");
							loc_ps8_cp = ps8_data_a_tout_faire;
						}
					}
					else
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					break;
				case MGMTIPROUTINGPOLICY_PORTDESTINATIONVALUE:
					if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
					{
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT])
						{
							sprintf(ps8_data_a_tout_faire,"%d - %d",
									loc_s_route.u16_critere_dst_port_start,
									loc_s_route.u16_critere_dst_port_end);
							loc_ps8_cp = ps8_data_a_tout_faire;
						}
						else
						{
							strcpy(ps8_data_a_tout_faire,"");
							loc_ps8_cp = ps8_data_a_tout_faire;
						}
					}
					else
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					break;
				case MGMTIPROUTINGPOLICY_GATEWAYNEW:
					if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY])
					{
						strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_route.u32_new_gateway));
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					else
					{
						strcpy(ps8_data_a_tout_faire,"");
						loc_ps8_cp = ps8_data_a_tout_faire;
					}
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_mgmtIProutingPolicyTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_mgmtIProutingPolicyTable\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_mgmtIProutingPolicyTable*/

//=====================================================================================
// Fonction		: captureInt_mgmtIProutingPolicyTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 22/04/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtIProutingPolicyTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;
	S_STRUCT_ROUTE_POLICY	loc_s_route;	//une route

	long_return = 0; //INIT

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_POLICY_ROUTING)
		{
			loc_s_route = s_config_process_snmpd.s_ip_routing.ps_route_policy[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTIPROUTINGPOLICY_INDEX:
					long_return = loc_s32_iindex;
					break;
				case MGMTIPROUTINGPOLICY_IPSOURCECRITERIA:
					long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_IP]+1;
					break;
				case MGMTIPROUTINGPOLICY_IPSOURCENOT:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_IP])
					{
						long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_SRC_IP]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_IPDESTINATIONCRITERIA:
					long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_IP]+1;
					break;
				case MGMTIPROUTINGPOLICY_IPDESTINATIONNOT:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_IP])
					{
						long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_DST_IP]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_PACKETLENGTHCRITERIA:
					long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET]+1;
					break;
				case MGMTIPROUTINGPOLICY_PACKETLENGTHNOT:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])
					{
						long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_IPPROTOCOLCRITERIA:
					long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL]+1;
					break;
				case MGMTIPROUTINGPOLICY_IPPROTOCOLVALUE:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])
					{
						long_return = loc_s_route.u8_critere_ip_protocol+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_IPPROTOCOLNOT:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])
					{
						long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_PORTSOURCECRITERIA:
					if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
					{
						long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_PORTSOURCENOT:
					if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
					{
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])
						{
							long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_SRC_PORT]+1;
						}
						else
						{
							long_return = 0;
						}
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_PORTDESTINATIONCRITERIA:
					if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
					{
						long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_PORTDESTINATIONNOT:
					if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
					{
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT])
						{
							long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_DST_PORT]+1;
						}
						else
						{
							long_return = 0;
						}
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_CLASSSELECTORCRITERIA:
					long_return = loc_s_route.pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR]+1;
					break;
				case MGMTIPROUTINGPOLICY_CLASSSELECTORVALUE:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])
					{
						long_return = loc_s_route.u8_critere_class_selector+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_CLASSSELECTORNOT:
					if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])
					{
						long_return = loc_s_route.pu8_not_critere[CRITERIAPOLICY_CLASS_SELECTOR]+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				case MGMTIPROUTINGPOLICY_GATEWAYACTION:
					long_return = loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY]+1;
					break;
				case MGMTIPROUTINGPOLICY_CLASSSELECTORACTION:
					long_return = loc_s_route.pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR]+1;
					break;
				case MGMTIPROUTINGPOLICY_CLASSSELECTORNEW:
					if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])
					{
						long_return = loc_s_route.u8_new_class_selector+1;
					}
					else
					{
						long_return = 0;
					}
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_mgmtIProutingPolicyTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureInt_mgmtIProutingPolicyTable\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_mgmtIProutingPolicyTable*/

//=====================================================================================
// Fonction		: captureString_mgmtNatPortForwardingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtNatPortForwardingTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;
	S_STRUCT_NAT_RULE_PORT_FORWARDING loc_s_rule_pfwd;

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_RULES_PORT_FORWARDING)
		{
			loc_s_rule_pfwd = s_config_process_snmpd.s_nat.ps_rule_port_forwarding[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTNATPORTFORWARDING_PRIVATEIPADDRESS:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_rule_pfwd.u32_private_ip));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				case MGMTNATPORTFORWARDING_COMMENT:
					strcpy(ps8_data_a_tout_faire,  loc_s_rule_pfwd.ps8_commentaire);
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_mgmtNatPortForwardingTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_mgmtNatPortForwardingTable\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_mgmtNatPortForwardingTable*/

//=====================================================================================
// Fonction		: captureInt_mgmtNatPortForwardingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtNatPortForwardingTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;
	S_STRUCT_NAT_RULE_PORT_FORWARDING loc_s_rule_pfwd;

	long_return = 0; //INIT

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_RULES_PORT_FORWARDING)
		{
			loc_s_rule_pfwd = s_config_process_snmpd.s_nat.ps_rule_port_forwarding[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTNATPORTFORWARDING_INDEX:
					long_return = loc_s32_iindex;
					break;
				case MGMTNATPORTFORWARDING_PRIVATEPORT:
					long_return = loc_s_rule_pfwd.u16_private_port;
					break;
				case MGMTNATPORTFORWARDING_PROTOCOL:
					long_return = loc_s_rule_pfwd.u8_protocole+1;
					break;
				case MGMTNATPORTFORWARDING_PUBLICPORT:
					long_return = loc_s_rule_pfwd.u16_public_port;
					break;
				case MGMTNATPORTFORWARDING_ENABLED:
					long_return = loc_s_rule_pfwd.u8_enable+1;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_mgmtNatPortForwardingTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureInt_mgmtNatPortForwardingTable\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_mgmtNatPortForwardingTable*/

//=====================================================================================
// Fonction		: captureString_mgmtNatAddressesMappingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtNatAddressesMappingTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;
	S_STRUCT_NAT_RULE_MAP_ADRESSES loc_s_rule_mapadr;

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_NAT_ALIAS_IP)
		{
			loc_s_rule_mapadr = s_config_process_snmpd.s_nat.ps_rule_mapping_adresse[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTNATADDRESSESMAPPING_PRIVATEIPADDRESS:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_rule_mapadr.u32_private_ip));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				case MGMTNATADDRESSESMAPPING_PUBLICIPADDRESS:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_rule_mapadr.u32_public_alias_ip));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				case MGMTNATADDRESSESMAPPING_COMMENT:
					strcpy(ps8_data_a_tout_faire,  loc_s_rule_mapadr.ps8_commentaire);
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_mgmtNatAddressesMappingTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_mgmtNatAddressesMappingTable\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_mgmtNatAddressesMappingTable*/

//=====================================================================================
// Fonction		: captureInt_mgmtNatAddressesMappingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtNatAddressesMappingTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;
	S_STRUCT_NAT_RULE_MAP_ADRESSES loc_s_rule_mapadr;

	long_return = 0; //INIT

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_NAT_ALIAS_IP)
		{
			loc_s_rule_mapadr = s_config_process_snmpd.s_nat.ps_rule_mapping_adresse[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTNATADDRESSESMAPPING_INDEX:
					long_return = loc_s32_iindex;
					break;
				case MGMTNATADDRESSESMAPPING_ENABLED:
					long_return = loc_s_rule_mapadr.u8_enable+1;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_mgmtNatAddressesMappingTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureInt_mgmtNatAddressesMappingTable\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_mgmtNatAddressesMappingTable*/

//=====================================================================================
// Fonction		: captureString_mgmtEvtTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtEvtTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_indEvt;
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;
	s32sod	loc_s32_sem;

	//On recherche index de l'evt (car iindex = numéro de l'évt)
	loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if(loc_u16_indEvt != US_INDICE_NON_TROUVE)
	{
		loc_s_cfg_evt = s_config_process_snmpd.s_tabevt.s_event[loc_u16_indEvt];

		switch (loc_s32_vpmagic) {
			case MGMTEVTSEVERITYLEVEL:
				ChNiveauGravite(ps8_data_a_tout_faire, loc_s_cfg_evt.u8_niveau_gravite, u8_snmp_langue);
				loc_ps8_cp = ps8ConvertChaineToSnmp(ps8_data_a_tout_faire);
				break;
			case MGMTEVTTEXT:
				loc_ps8_cp = ps8ConvertChaineToSnmp(pt_tb_msg[u8_snmp_langue].ps8_msg_lib_evenement[loc_u16_indEvt]);
				break;
			default:
				DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_mgmtEvtTable\n", loc_s32_vpmagic));
				break;   
		}
	}
	else
	{
		DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_mgmtEvtTable\n", loc_s32_iindex));
	}

	return loc_ps8_cp;
}/*captureString_mgmtEvtTable*/

//=====================================================================================
// Fonction		: captureInt_mgmtEvtTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtEvtTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_indEvt;
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;

	long_return = 0; //INIT

	//On recherche index de l'evt (car iindex = numéro de l'évt)
	loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);

	if(loc_u16_indEvt != US_INDICE_NON_TROUVE)
	{
		loc_s_cfg_evt = s_config_process_snmpd.s_tabevt.s_event[loc_u16_indEvt];
		
		switch (loc_s32_vpmagic) {
			case MGMTEVTINDEX:
				long_return = loc_s32_iindex;
				break;
			case MGMTEVTCODE:
				long_return =  S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt;
				break;
			case MGMTEVTUSED:
				if((TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
				   (TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
				  )	//CONDITION: Evts communs à tous les équipements ou evt de type info
				{
					long_return = 3;	//na
					//valeur non configurable
				}
				else // TYPE_EVT_ALARME
				{
					if(TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_VALIDE))
					{
						long_return = 1;	//on
					}
					else
					{
						long_return = 2;	//off
					}
					*loc_pt_write_method = write_mgmtEvtUsed;
				}
				break;
			case MGMTEVTLOG:
				if(		(TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
				  )	//CONDITION: Evts communs à tous les équipements
				{
					long_return = 3;	//na
					//valeur non configurable
				}
				else // TYPE_EVT_INFO ou TYPE_EVT_ALARME
				{
					if(TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_JDB))
					{
						long_return = 1;	//on
					}
					else
					{
						long_return = 2;	//off
					}
					*loc_pt_write_method = write_mgmtEvtLOG;
				}
				break;
			case MGMTEVTSYNTHESIS1:
				if((TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
				   (TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
				   (EVT000_AL_SYNTHESE_1 == loc_u16_indEvt)
				  )	//CONDITION: Evts communs à tous les équipements ou evt de type info ou  evts de synthèse
				{
					long_return = 3;	//na
					//valeur non configurable
				}
				else // TYPE_EVT_ALARME
				{
					if(TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_SYNTHESE_1))
					{
						long_return = 1;	//on
					}
					else
					{
						long_return = 2;	//off
					}
					*loc_pt_write_method = write_mgmtEvtSynthesis1;
				}
				break;
			case MGMTEVTAVAILABLE:
				//Disponibilité
				if(TRUE == u8TestEventDisponible(loc_u16_indEvt)) //CONDITION: Disponible
				{
					long_return = 2;	//yes
				}
				else
				{
					long_return = 1;	//no
				}
				break;
			default:
				DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_mgmtEvtTable\n", loc_s32_vpmagic));
				break;   
		}
	}
	else
	{
		DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureInt_mgmtEvtTable\n", loc_s32_iindex));
	}

	return long_return;
}/*captureInt_mgmtEvtTable*/

//=====================================================================================
// Fonction		: captureString_mgmtMulticast_Sources_Table
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_mgmtMulticast_Sources_Table(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;
	S_STRUCT_SRC_MULTICAST loc_s_src_multicast;

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_SRC_MULTICAST)
		{
			loc_s_src_multicast = s_config_process_snmpd.s_multicast.ps_source_multicast[loc_u16_index];

			switch (loc_s32_vpmagic) {
				case MGMTMULTICAST_SOURCES_ADDRIP:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_src_multicast.u32_adresse_reseau));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				case MGMTMULTICAST_SOURCES_MASK:
					strcpy(ps8_data_a_tout_faire, ps8GetStringIp(loc_s_src_multicast.u32_masque_reseau));
					loc_ps8_cp = ps8_data_a_tout_faire;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_mgmtMulticast_Sources_Table\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_mgmtMulticast_Sources_Table\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_mgmtMulticast_Sources_Table*/

//=====================================================================================
// Fonction		: captureInt_mgmtMulticast_Sources_Table
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_mgmtMulticast_Sources_Table(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;

	long_return = 0; //INIT

	loc_u16_index = (u16sod)loc_s32_iindex-1;

	if(MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)
	{
		if(loc_u16_index < NB_MAX_SRC_MULTICAST)
		{
			switch (loc_s32_vpmagic) {
				case MGMTMULTICAST_SOURCES_INDEX:
					long_return = loc_s32_iindex;
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_mgmtMulticast_Sources_Table\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureInt_mgmtMulticast_Sources_Table\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_mgmtMulticast_Sources_Table*/

//=====================================================================================
// Fonction		: captureString_staAlarmslistTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_staAlarmslistTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_indEvt;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT

	//On recherche index de l'evt (car loc_s32_iindex = numéro de l'évt)
	loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);

	if(loc_u16_indEvt != US_INDICE_NON_TROUVE)
	{
		switch (loc_s32_vpmagic) {
			case STAALARMSLISTDESCRIPTION:
				loc_ps8_cp = ps8ConvertChaineToSnmp(pt_tb_msg[u8_snmp_langue].ps8_msg_lib_evenement[loc_u16_indEvt]);
				break;
			default:
				DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_staAlarmslistTable\n", loc_s32_vpmagic));
				break;   
		}
	}
	else
	{
		DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_staAlarmslistTable\n", loc_s32_iindex));
	}

	return loc_ps8_cp;
}/*captureString_staAlarmslistTable*/

//=====================================================================================
// Fonction		: captureInt_staAlarmslistTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_staAlarmslistTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_indEvt;
	u8sod	loc_u8_etat_alarme;

	long_return = 0; //INIT

	//On recherche index de l'evt (car loc_s32_iindex = numéro de l'évt)
	loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);

	if(loc_u16_indEvt != US_INDICE_NON_TROUVE)
	{
		switch (loc_s32_vpmagic) {
			case STAALARMSLISTINDEX:
				long_return = loc_s32_iindex;
				break;
			case STAALARMSLISTSTATUS:
				if(TRUE == u8TestEventDisponible(loc_u16_indEvt)) //CONDITION: Disponible
				{
					loc_u8_etat_alarme = u8GetEtatAlarme(&s_exp_events_process_snmpd, loc_u16_indEvt);
					if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
					{
						if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
						{
							long_return = 1;	//alarm
						}
						else
						{
							long_return = 2; //no-alarm
						}
					}
					else
					{
						long_return = 3; //unused
					}
				}
				else
				{
					long_return = 0; //not-available
				}
				break;
			case STAALARMSLISTLATCHEDSTATUS:
				if(TRUE == u8TestEventDisponible(loc_u16_indEvt)) //CONDITION: Disponible
				{
					loc_u8_etat_alarme = u8GetEtatAlarme(&s_exp_events_process_snmpd, loc_u16_indEvt);
					if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
					{
						if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT2_ETAT_MEMORISE))
						{
							long_return = 1;	//alarm
						}
						else
						{
							long_return = 2; //no-alarm
						}
					}
					else
					{
						long_return = 3; //unused
					}
				}
				else
				{
					long_return = 0; //not-available
				}
				break;

			default:
				DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_staAlarmslistTable\n", loc_s32_vpmagic));
				break;   
		}
	}
	else
	{
		DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt %d in captureInt_staAlarmslistTable\n", loc_s32_iindex));
	}

	return long_return;
}/*captureInt_staAlarmslistTable*/

//=====================================================================================
// Fonction		: captureString_staWirelessApClientTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_staWirelessApClientTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT
	
	loc_u16_index = (u16sod)(loc_s32_iindex-1);

	if(MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
	{
		if(loc_u16_index < NB_ASSOCIATED_STATIONS_MAX)
		{
			switch (loc_s32_vpmagic) {
				case STAWIRELESSAP_CLIENT_MACADDRESS:
					loc_ps8_cp = ps8GetChAddressMac(s_exploit_process_snmpd.s_access_point.s_wifi_client[loc_u16_index].pu8_add_mac);
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_staWirelessApClientTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_staWirelessApClientTable\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_staWirelessApClientTable*/

//=====================================================================================
// Fonction		: captureInt_staWirelessApClientTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_staWirelessApClientTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;
	u32sod loc_u32_exp_statut_client_wifi;

	long_return = 0; //INIT

	loc_u16_index = (u16sod)(loc_s32_iindex-1);

	if(MODE_RADIO_MODEM_ACCESS_POINT == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
	{
		if(loc_u16_index < NB_ASSOCIATED_STATIONS_MAX)
		{
			switch (loc_s32_vpmagic) {
				case STAWIRELESSAP_CLIENT_INDEX:
					long_return = (long)loc_u16_index;
					break;
				case STAWIRELESSAP_CLIENT_RSSI_DBM:
					long_return = (long)s_exploit_process_snmpd.s_access_point.s_wifi_client[loc_u16_index].s32_rssi_dbm;
					break;
				case STAWIRELESSAP_CLIENT_STATUS:
					loc_u32_exp_statut_client_wifi = s_exploit_process_snmpd.s_access_point.s_wifi_client[loc_u16_index].u32_statut;
					switch(s_config_process_snmpd.s_wifi.u8_mode_securite_wifi)
					{
						case MODE_SECURITE_WIFI_AUCUN:
						case MODE_SECURITE_WIFI_WEP:
							if((u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED) == (loc_u32_exp_statut_client_wifi & (u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED)))
							{
								long_return = 2; //associated
							}
							else
							{
								long_return = 1; //not-associated
							}
							break;
						case MODE_SECURITE_WIFI_WPA:
						case MODE_SECURITE_WIFI_WPA_TKIP:
						case MODE_SECURITE_WIFI_WPA_AES:
						case MODE_SECURITE_WIFI_WPA2:
						case MODE_SECURITE_WIFI_WPA2_TKIP:
						case MODE_SECURITE_WIFI_WPA2_AES:
							if((u32sod)(1<<BIT2_STA_CLIENTWIFI_AUTHORIZED) == (loc_u32_exp_statut_client_wifi & (u32sod)(1<<BIT2_STA_CLIENTWIFI_AUTHORIZED)))
							{
								long_return = 3; //activated-wpa-connexion
							}
							else
							{
								if((u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED) == (loc_u32_exp_statut_client_wifi & (u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED)))
								{
									long_return = 2; //associated
								}
								else
								{
									long_return = 1; //not-associated
								}
							}
							break;
						default:
							break;
					}
					break;

				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_staWirelessApClientTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt %d in captureInt_staWirelessApClientTable\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_staWirelessApClientTable*/

//=====================================================================================
// Fonction		: captureString_staDhcpClientsTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *
   captureString_staDhcpClientsTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	s8sod *loc_ps8_cp;
	u16sod	loc_u16_index;

	strcpy(ps8_data_a_tout_faire,""); //INIT
	loc_ps8_cp = ps8_data_a_tout_faire; //INIT
	
	loc_u16_index = (u16sod)(loc_s32_iindex-1);

	if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
	{
		if(loc_u16_index < NB_MAX_CLIENTS_DHCP)
		{
			switch (loc_s32_vpmagic) {
				case STADHCPCLIENTS_MACADDRESS:
					loc_ps8_cp = ps8GetChAddressMac(s_exploit_process_snmpd.s_dhcp.s_client_connected[loc_u16_index].pu8_add_mac);
					break;
				case STADHCPCLIENTS_IPADDRESS:
					loc_ps8_cp = ps8GetStringIp(s_exploit_process_snmpd.s_dhcp.s_client_connected[loc_u16_index].u32_adresse_ip);
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_staDhcpClientsTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt KO: %d in captureString_staDhcpClientsTable\n", loc_s32_iindex));
		}
	}

	return loc_ps8_cp;
}/*captureString_staDhcpClientsTable*/

//=====================================================================================
// Fonction		: captureInt_staDhcpClientsTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long
   captureInt_staDhcpClientsTable(s32sod loc_s32_vpmagic, s32sod loc_s32_iindex, WriteMethod ** loc_pt_write_method)
{
	u16sod	loc_u16_index;
	u32sod loc_u32_exp_statut_client_wifi;

	long_return = 0; //INIT

	loc_u16_index = (u16sod)(loc_s32_iindex-1);

	if(MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)
	{
		if(loc_u16_index < NB_MAX_CLIENTS_DHCP)
		{
			switch (loc_s32_vpmagic) {
				case STADHCPCLIENTS_INDEX:
					long_return = (long)loc_u16_index;
					break;
				case STADHCPCLIENTS_REMAININGLEASE:
					long_return = (long)s_exploit_process_snmpd.s_dhcp.s_client_connected[loc_u16_index].u32_temps_restant;
					break;

				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_staDhcpClientsTable\n", loc_s32_vpmagic));
					break;   
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u16RechercheIndiceEvt %d in captureInt_staDhcpClientsTable\n", loc_s32_iindex));
		}
	}

	return long_return;
}/*captureInt_staDhcpClientsTable*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: initdata_mib_wrm100
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation de ce module
//=====================================================================================
void initdata_mib_wrm100(void)
{
	
}/*initdata_mib_wrm100*/
