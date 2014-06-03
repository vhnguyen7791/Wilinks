/*========================================================================*/
/* NOM DU FICHIER  : apply_cfg.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Principal: Application de la configuration			  */
/* Projet          : WRM100                                               */
/* Indice          : BE059                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE007 25/01/2010 CM
// - Correction bug hostapd lors de modification paramètres réseau (en particulier ath0 down)
// - Modification gestion routage statique
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du système
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calculée dans le processus 'monitor'.
//BE021 24/03/2010 CM
// - Correction BUG liaison bridge-bridge
//BE022 29/03/2010 CM
// - Ajout gestion multicast
// - Correction bug dhcp fallback sur station / bridge
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Modification gestion reconfiguration (quand interface down)
// - Modification gestion routage par le processus bird
//BE026 26/04/2010 CM
// - Correction gestion passerelle via bird (qd station / router en client DHCP)
// - Correction lecture /proc/net/route
//	il faut comptabiliser les routes statiques, dynamiques 
//BE032 16/06/2010 CM
// - Correction des défauts observés lors du changement de paramètres Wifi
//		kernel panic suite à changement de fréquence (en WPA EAP), ....
//	solution: décharger/charger les modules wifi sur changement de paramètres Wifi
//BE034 28/06/2010 CM
// - Correction pour SNMP du type d'interfaces (ifType dans la table ifTable)
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		userhigh / usermiddle / userlow
//BE042 07/10/2010 CM
// - Correction configuration mode 802.11 (associé au driver-N)
// - Integration des paramètres handoff
//BE046.3
// - Correction configuration par défaut
//		si AP => passage en STA / Bridge par erreur
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE052 15/12/2010 CM
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification une seule antenne autorisée dans les modes 802.11abg (Driver-N)
// - Modification plage de timeout ACK (Driver-N)
// - Correction bug commande pidof via hostapd
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
// - Modification débit emission MCS0 à MCS15 autorisé quelque soit nb antennes
// - Suppression du fichier de configuration advwf
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Correction bug configuration des canaux (multi-freq) erronée si chgt de mode 802.11 (g -> a) et de type radiomodem
// - AJout fonction arret AP si ethernet deconnecte
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _APPLY_CFG

//Timout avant vérification echec ou réussite udhcp
#define TIMEOUT_VERIF_DHCP  2 //secondes

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Compteur lorsque le dhcp a terminé pour vérifier si dhcp a réussi ou échoué
static u8sod u8_cpt_timeout_verif_dhcp;

//Configuration 
static S_STRUCT_CONFIGURATION s_config_impose;

//Etat du backbone (Ethernet ou Optique)
static u8sod u8_backbone_connected;


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_General
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe générale
//=====================================================================================
void Install_General(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_General\n");

	//On autorise le routage entre interface
	CmdSystem_Generique("echo '1' > %s",FICHIER__SYS_NET_IPV4_IP_FORWARD);

}/*Install_General*/

//=====================================================================================
// Fonction		: ImposeConfigSiEvolution
// Entrees		: <loc_ps_new_config< : nouvelle configuration
//				: <loc_ps_old_config< : ancienne configuration
//				: <loc_pt_newcfg< : tableau signalant une nouvelle configuration
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Sur changement de certains paramètres, on impose la configuration
//=====================================================================================
void ImposeConfigSiEvolution(S_STRUCT_CONFIGURATION *loc_ps_new_config, S_STRUCT_CONFIGURATION *loc_ps_old_config, T_STRUCT_OF_FILE_NEWCFG_INI *loc_pt_newcfg)
{
	u8sod loc_u8_idx_cfgfile;
	u16sod loc_u16_index;
	u8sod	loc_u8_i;

	loc_u8_idx_cfgfile = 0;	//INIT
	loc_u16_index = 0;	//INIT
	
	//On copie dans une variable temporaire la nouvelle configuration
	s_config_impose = *loc_ps_new_config;
	
	///Condiguration générale
	if(s_config_impose.s_gene.u8_mode_radio_modem != loc_ps_old_config->s_gene.u8_mode_radio_modem)
	{
		switch(s_config_impose.s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_ACCESS_POINT:
			case MODE_RADIO_MODEM_MONITOR:
				s_config_impose.s_gene.u8_mode_network = MODE_NETWORK_BRIDGE;

				switch(s_config_impose.s_wifi.u8_mode_802_11x)
				{
					case MODE_WIFI_802_11NGHT40:
						loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, s_config_impose.s_wifi.u16_iso_canal_radio, MODE_WIFI_802_11NGHT40PLUS);
						if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
						{
							s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NGHT40PLUS;
						}
						else
						{
							loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, s_config_impose.s_wifi.u16_iso_canal_radio, MODE_WIFI_802_11NGHT40MINUS);
							if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
							{
								s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NGHT40MINUS;
							}
							else
							{
								s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NGHT20;
							}
						}
						break;
					case MODE_WIFI_802_11NAHT40:
						loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, s_config_impose.s_wifi.u16_iso_canal_radio, MODE_WIFI_802_11NAHT40PLUS);
						if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
						{
							s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NAHT40PLUS;
						}
						else
						{
							loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, s_config_impose.s_wifi.u16_iso_canal_radio, MODE_WIFI_802_11NAHT40MINUS);
							if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
							{
								s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NAHT40MINUS;
							}
							else
							{
								s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NAHT20;
							}
						}
						break;
					default:
						break;
				}
				break;
			case MODE_RADIO_MODEM_STATION:
				switch(s_config_impose.s_wifi.u8_mode_802_11x)
				{
					case MODE_WIFI_802_11NGHT40PLUS:
					case MODE_WIFI_802_11NGHT40MINUS:
						s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NGHT40;
						break;
					case MODE_WIFI_802_11NAHT40PLUS:
					case MODE_WIFI_802_11NAHT40MINUS:
						s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NAHT40;
						break;
					default:
						break;
				}
				//On force en mode canal-iso
				s_config_impose.s_wifi.u8_type_selection_canal = TYPE_SELECTION_CANAL_ISO;
				//on configure une seule fréquence pour les canaux en multi-frequence
				for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
				{
					s_config_impose.s_wifi.pu16_multi_canal_radio[loc_u8_i] = CHANNEL_RADIO_DISABLED; //RAZ
				}
				s_config_impose.s_wifi.pu16_multi_canal_radio[0] = s_config_impose.s_wifi.u16_iso_canal_radio;
				break;
			default:
				break;
		}
	}

#ifdef _WRM100_N_SELECT
	//Gestion nouveau code pays
	if(s_config_impose.s_wifi.u8_countryID != loc_ps_old_config->s_wifi.u8_countryID)
	{
			//On passe en mode 11g / 1 antenne / debit automatique / puissance par défaut
		s_config_impose.s_wifi.u8_mode_802_11x = MODE_WIFI_802_11G;
		s_config_impose.s_wifi.u16_iso_canal_radio = CHANNEL_DEFAULT_11BG;
		for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
		{
			s_config_impose.s_wifi.pu16_multi_canal_radio[loc_u8_i] = CHANNEL_RADIO_DISABLED; //RAZ
		}
		s_config_impose.s_wifi.pu16_multi_canal_radio[0] = CHANNEL_DEFAULT_11BG;
		s_config_impose.s_wifi.u8_ant_N_selection = N_SELECT_ANTENNE_1;
		s_config_impose.s_wifi.u8_power_tx = POWER_TX_802_11X_DEFAULT;
		s_config_impose.s_wifi.u8_data_rate = DATA_RATE_AUTOMATIC;
	}
#endif
	
	if(MODE_RADIO_MODEM_MONITOR == s_config_impose.s_gene.u8_mode_radio_modem)
	{
#ifdef _WRM100_ABG_SELECT
		s_config_impose.s_wifi.u8_ant_ABG_tx_selection = s_config_impose.s_wifi.u8_ant_ABG_rx_selection;
		s_config_impose.s_wifi.u8_power_tx = POWER_TX_802_11ABG_MIN;
#endif
#ifdef _WRM100_N_SELECT
		s_config_impose.s_wifi.u8_power_tx = POWER_TX_802_11ABGN_MIN;
#endif
		s_config_impose.s_wifi.u8_data_rate = DATA_RATE_AUTOMATIC;
	}
	
#ifdef _WRM100_N_SELECT
	if((TRUE == u8IsMode80211ag(s_config_impose.s_wifi.u8_mode_802_11x))||
	   (TRUE == u8IsMode80211b(s_config_impose.s_wifi.u8_mode_802_11x))
	  )
	{
		//on force à une antenne
		s_config_impose.s_wifi.u8_ant_N_selection = N_SELECT_ANTENNE_1;
	}

	if(FALSE == u8TestCfg_N_AckTimeout(&s_config_impose))
	{
		s_config_impose.s_wifi.u16_protcl_N_ACK_timeout = WF_N_ACK_TIMEOUT_DEFAULT;
	}
	
	if((MODE_RADIO_MODEM_ACCESS_POINT == s_config_impose.s_gene.u8_mode_radio_modem)||
	   (MODE_RADIO_MODEM_STATION == s_config_impose.s_gene.u8_mode_radio_modem)
	  )
	{
		//Test cohérence débit
		if(FALSE == u8Test_N_ConfigDataRate(s_config_impose.s_wifi.u8_data_rate,
										    s_config_impose.s_wifi.u8_mode_802_11x,
										    s_config_impose.s_wifi.u8_ant_N_selection)
		  )
		{
			s_config_impose.s_wifi.u8_data_rate = DATA_RATE_AUTOMATIC;
		}
		
		//Test cohérence puissance
		if(FALSE == u8Test_N_ConfigPowerTx(s_config_impose.s_wifi.u8_power_tx,
										   s_config_impose.s_wifi.u8_mode_802_11x,
										   s_config_impose.s_wifi.u8_data_rate,
										   s_config_impose.s_wifi.u8_ant_N_selection)
		  )
		{
			s_config_impose.s_wifi.u8_power_tx = POWER_TX_802_11ABGN_MIN;
		}
	}
	
#endif

	//Mode RSSI
#ifdef _WRM100_N_SELECT
	if(MODE_RADIO_MODEM_STATION == s_config_impose.s_gene.u8_mode_radio_modem)
	{
		//En station , il n'est pas autorisé de valider la journalisation du systeme et le mode RSSI simultanément
		if((TRUE == s_config_impose.s_admin.u8_syslog_activation)&&
		   (TRUE == s_config_impose.s_admin.u8_mode_RSSI)
		  )
		{
			s_config_impose.s_admin.u8_mode_RSSI = FALSE;	//RAZ
		}
	}
	else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
	{
		s_config_impose.s_admin.u8_mode_RSSI = FALSE;	//RAZ
	}
#endif
	
	//On test si on a changé la configuration
	for(loc_u8_idx_cfgfile=0;loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
	{
		if(TRUE == PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8DiffConfig(&s_config_impose, loc_ps_new_config))
		{ //CONDITION: différence détectée
			if(TRUE == PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8TestConfig(&s_config_impose))
			{//CONDITION: config cohérente
				if(TRUE == PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8EditConfig(&s_config_impose))
				{//CONDITION: ecriture OK
					PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].CopyConfig(&s_config_impose, loc_ps_new_config);
					printf("ImposeConfigSiEvolution: IMPOSE idx=%s\n",
						  PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom);
					loc_pt_newcfg->pu8_flag[loc_u8_idx_cfgfile] = TRUE;	//Nouvelle configuration
				}
			}
		}
	}
	
}/*ImposeConfigSiEvolution*/

//=====================================================================================
// Fonction		: ExecuteApplyConfig
// Entrees		: <loc_ps_new_config< : nouvelle configuration
//				: <loc_ps_old_config< : ancienne configuration
//				: <loc_u32_reconfig_total> : ordre de reconfiguration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Applique la nouvelle configuration
//=====================================================================================
void ExecuteApplyConfig(S_STRUCT_CONFIGURATION *loc_ps_new_config, S_STRUCT_CONFIGURATION *loc_ps_old_config, u32sod loc_u32_reconfig_total)
{
	u8sod loc_u8_i;
	
	//Initialisation :reset ordre quelque soit le mode (station / access point)
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ORDRE_RECONFIG;loc_u8_i++)
	{
		ClearOrdreReconfiguration(loc_u8_i); //RAZ
	}

	
	//Install general
	Install_General(loc_ps_new_config);
	
	if(MODE_EXECPRINCIPAL_NORADIO != u8_mode_execPrincipal)
	{
		//Test si le mode du radio modem a évolué
		//  ou si le mode du réseau a évolué
		//	ou un des paramètres Wifi a évolué
		if( (loc_ps_new_config->s_gene.u8_mode_radio_modem != loc_ps_old_config->s_gene.u8_mode_radio_modem)||
			(loc_ps_new_config->s_gene.u8_mode_network != loc_ps_old_config->s_gene.u8_mode_network)||
			(TRUE == u8DiffConfigWifi(loc_ps_new_config, loc_ps_old_config))||
		    (TRUE == u8DiffConfigHandoff(loc_ps_new_config, loc_ps_old_config))||
			(ORDRE_RECONFIG_TOTALE_ACTIVEE == loc_u32_reconfig_total)			  
			)
		{
			//Désintalle l'ancien mode de radio modem
			Uninstall_RadioModem(loc_ps_old_config);

			//On émet un ordre d'install du radio modem
			u8_ordre_installRadioModem = TRUE;
		}
		else
		{
			switch(loc_ps_new_config->s_gene.u8_mode_network)
			{
				case MODE_NETWORK_BRIDGE:
					if(TRUE == u8DiffConfigGene_NetworkBridge(loc_ps_new_config, loc_ps_old_config))
					{
						//Désintallation du bridge
						Uninstall_NetworkBridge(loc_ps_old_config);

						//Configuration du bridge
						Install_NetworkBridge(loc_ps_new_config);
					}
					break;
				case MODE_NETWORK_ROUTER:
					if((TRUE == u8DiffConfigGene_NetworkRouter(loc_ps_new_config, loc_ps_old_config)) ||
					   (TRUE == u8DiffConfigRouting(loc_ps_new_config, loc_ps_old_config)) ||
					   (TRUE == u8DiffConfigMulticast(loc_ps_new_config, loc_ps_old_config)) ||
					   (TRUE == u8DiffConfigGene_FctDHCP(loc_ps_new_config, loc_ps_old_config)) ||
					   (TRUE == u8DiffConfigNAT(loc_ps_new_config, loc_ps_old_config))
					  )//CONDITION: changement paramètres réseau ou routage ou DHCP ou NAT
					{
						//Désintallation du routeur
						Uninstall_NetworkRouter(loc_ps_old_config);
						//Désinstallation de la fonction DHCP
						Uninstall_FctDHCP(loc_ps_old_config);
						//Désinstallation du NAT
						Uninstall_Nat(loc_ps_old_config);

						//Configuration du router
						Install_NetworkRouter(loc_ps_new_config);
						//Intallation de la fonction DHCP
						Install_FctDHCP(loc_ps_new_config);
						if(MODE_IP_STATIQUE == loc_ps_new_config->s_gene.u8_wlan_mode_ip)
						{
								//Installation du NAT
							Install_Nat(loc_ps_new_config, loc_ps_new_config->s_gene.u32_wlan_adresse_ip, loc_ps_new_config->s_gene.u32_wlan_masque_reseau);
						}
					}
					break;
				default:
					break;
			}
		}

		//Dernière étape
		switch(loc_ps_new_config->s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_ACCESS_POINT:
				ExecReconfiguration_HostApd(loc_ps_new_config);
				break;
			case MODE_RADIO_MODEM_STATION:
				ExecReconfiguration_WpaSupplicant(loc_ps_new_config);
				ExecReconfiguration_Routage(loc_ps_new_config);
				ExecReconfiguration_Multicast(loc_ps_new_config);
				break;
			case MODE_RADIO_MODEM_MONITOR:
			default:
				break;
		}

	}//fin: MODE_EXECPRINCIPAL_NORADIO != u8_mode_execPrincipal

	if(TRUE == u8DiffConfigNtp(loc_ps_new_config, loc_ps_old_config))
	{
		//Désinstallation
		Uninstall_Time(loc_ps_old_config);
		//Installation
		Install_Time(loc_ps_new_config);
	}
	
	//Install SNMP
	if((TRUE == u8DiffConfigSnmp(loc_ps_new_config, loc_ps_old_config))||
	   (loc_ps_new_config->s_wifi.u8_mode_802_11x != loc_ps_old_config->s_wifi.u8_mode_802_11x)||
	   (loc_ps_new_config->s_gene.u8_vlan_autoriser != loc_ps_old_config->s_gene.u8_vlan_autoriser)||
	   (loc_ps_new_config->s_gene.u16_vlan_id != loc_ps_old_config->s_gene.u16_vlan_id)
	  )
	{
		Install_Snmp(loc_ps_new_config);
	}

	//Install syslog
	if(TRUE == u8DiffConfigSyslog(loc_ps_new_config, loc_ps_old_config))
	{
		if(FALSE == loc_ps_new_config->s_admin.u8_syslog_activation)//CONDITION: SYSLOG DESACTIVE
		{
			//Désinstallation
			Uninstall_Systemlog(loc_ps_old_config);
		}
		else//CONDITION: SYSLOG ACTIVE
		{
			//Désinstallation
			Uninstall_Systemlog(loc_ps_old_config);
			
			//Installation
			Install_Systemlog(loc_ps_new_config);
		}
	}

#ifdef _WRM100_N_SELECT
	//Install mode RSSI
	if(FALSE == u8_ordre_installRadioModem) //CONDITION: driver chargé
	{
		//Il n'est pas nécessaire de re-charger le driver
		if(TRUE == u8DiffConfigModeRSSI(loc_ps_new_config, loc_ps_old_config))
		{
			//Installation
			//WlanN_Install_ModeRSSI(loc_ps_new_config);
		}
	}
#endif
	
	//Login / Password
	if(TRUE == u8DiffConfigPassword(loc_ps_new_config, loc_ps_old_config))
	{
		Install_LoginPassword(loc_ps_new_config);
	}

	
}/*ExecuteApplyConfig*/

//=====================================================================================
// Fonction		: ExecuteGestionInstall
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 07/01/2009 -
// Description	: Gestion des installlations réalisées sur les services
//					appelée en tache de fond
//=====================================================================================
void ExecuteGestionInstall(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	//-----------------------------------------------
	//Gestion du DHCP client
	//-----------------------------------------------
	GestionInstall_DHCPClient(loc_ps_config);


	//-----------------------------------------------
	//Gestion sur AP : si ethernet deconnecté, alors RADIO OFF, sion ON
	//-----------------------------------------------
	if(MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		ControlAccessPoint_ON_OFF(loc_ps_config);
	}
	
}/*ExecuteGestionInstall*/

//=====================================================================================
// Fonction		: ControlAccessPoint_ON_OFF
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 21/01/2011 -
// Description	: controle AP en fonction etat ethernet
//=====================================================================================
void ControlAccessPoint_ON_OFF(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod	loc_s32_sem;
	u8sod loc_u8_donnees_inaccessible;
	u8sod loc_u8_etat_backbone;

	loc_u8_donnees_inaccessible = FALSE;	//INIT
	loc_u8_etat_backbone = FALSE;	//INIT

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitGeneralFile(&s_exploit_process_prncpl.s_general))
	{
		loc_u8_donnees_inaccessible = TRUE; //défaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	if(FALSE == loc_u8_donnees_inaccessible)
	{
		if((FALSE == s_exploit_process_prncpl.s_general.u8_link_statut_ethernet[PORT_ETHERNET_1])&&
		   (FALSE == s_exploit_process_prncpl.s_general.u8_link_statut_ethernet[PORT_ETHERNET_2])
		  )   //CONDITION: non connecté?
		{
			loc_u8_etat_backbone = FALSE;
		}
		else//CONDITION: connecté
		{
			loc_u8_etat_backbone = TRUE;
		}

		if(u8_backbone_connected != loc_u8_etat_backbone)
		{
			u8_backbone_connected = loc_u8_etat_backbone; //MAJ
			if(TRUE == u8_backbone_connected)
			{
				//on redemarre
				CmdIfconfig_Up(NOM_INTERFACE_WIFI, loc_ps_config);
			}
			else
			{
				//on stoppe
				//Modif by VuHai
				//CmdIfconfig_Down(NOM_INTERFACE_WIFI);
				printf("******** ControlAccessPoint_ON_OF: Ethernet is disconnected, should put down AP mode ****\n"); 
			}
		}
		
	}

}/*ControlAccessPoint_ON_OFF*/

//=====================================================================================
// Fonction		: GestionInstall_DHCPClient
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 06/01/2010 -
// Description	: Gestion de l'installation du DHCP client (modes dégradés: exemple repli IP, si DHCP echoue)
//=====================================================================================
void GestionInstall_DHCPClient(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod	loc_s32_sem;
	FILE *	loc_pf_file;
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
	u32sod loc_u32_wlan_gateway;
	u32sod loc_u32_wlan_ip_adress;
	u32sod loc_u32_wlan_mask;
	u32sod loc_u32_bridge_ip_adress;
	u32sod loc_u32_bridge_mask;
	u8sod	loc_u8_donnees_inaccessible;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;

	loc_pf_file = NULL;	//INIT
	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	loc_u32_wlan_gateway = ADRESSE_IP_NULLE; //INIT
	loc_u32_wlan_ip_adress = ADRESSE_IP_NULLE;	//INIT
	loc_u32_wlan_mask = ADRESSE_IP_NULLE;	//INIT
	loc_u32_bridge_ip_adress = ADRESSE_IP_NULLE;	//INIT
	loc_u32_bridge_mask = ADRESSE_IP_NULLE;	//INIT
	loc_u8_donnees_inaccessible = FALSE; //INIT

	if(TRUE == u8_start_installDHCPClient) //CONDITION: DHCP client démarré
	{
//		printf("UDHCPC: %d\n",s32GetPidProcessus("udhcpc", 	FICHIER_VAR_UDHCPC_PID));
		//On vérifie si le processus est en cours
//		if((-1) == s32GetPidProcessus("udhcpc", 	FICHIER_VAR_UDHCPC_PID))
		if(NULL == (loc_pf_file = fopen(FICHIER_VAR_UDHCPC_PID, "rt"))) //CONDITION: fichier absent (supprimé automatiquement lorsque le processus se termine)
		{
			u8_cpt_timeout_verif_dhcp ++;

			if(u8_cpt_timeout_verif_dhcp > TIMEOUT_VERIF_DHCP)
			{
				s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
				if(FALSE == u8FillExploitGeneralFile(&s_exploit_process_prncpl.s_general))
				{
					loc_u8_donnees_inaccessible = TRUE; //défaut accès bdd
				}
				s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

				if(FALSE == loc_u8_donnees_inaccessible) //CONDITION: BDD OK
				{
					//donc processus udhcpc a terminé
					//on vérifie si une adresse IP a été affectée
					//Si ce n'est pas le cas, on applique l'adresse IP de repli
					switch(loc_ps_config->s_gene.u8_mode_radio_modem)
					{
						case MODE_RADIO_MODEM_ACCESS_POINT:
						case MODE_RADIO_MODEM_MONITOR:
							if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_bridge_mode_ip)
							{
								if((INADDR_NONE == u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_LAN].ps8_add_ip, &loc_u8_ret))||
								   (INADDR_NONE == u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip, &loc_u8_ret))
								  )//CONDITION: adresses effectées incorrectes
								{
									if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip)
									{
										strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip));
										strcpy(loc_ps8_addr_mask, ps8GetStringIp(MASK_RESEAU_SUR_24));
										printf("Echec udhcpc: Configuration Adresse IP DHCP de repli:%s\n",
											   loc_ps8_addr_ip);
										//on configure l'adresse IP de repli DHCP du bridge
										CmdIfconfig_Down(NOM_INTERFACE_BRIDGE);
										CmdSystem_Generique("ifconfig %s %s netmask %s",
															NOM_INTERFACE_BRIDGE,
															loc_ps8_addr_ip,
															loc_ps8_addr_mask);
										//Puis up du bridge
										CmdIfconfig_Up(NOM_INTERFACE_BRIDGE, loc_ps_config);

										loc_u32_bridge_ip_adress = loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip;
										loc_u32_bridge_mask = MASK_RESEAU_SUR_24;
										
										//Résultat DHCP
										u8_bridge_autostatut_ip = STATUT_IP__FAILURE_DHCP;
									}
								}
								else
								{
									loc_u32_bridge_ip_adress = u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_LAN].ps8_add_ip, &loc_u8_ret);
									loc_u32_bridge_mask = u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_LAN].ps8_mask, &loc_u8_ret);
									
									//Résultat DHCP
									u8_bridge_autostatut_ip = STATUT_IP__SUCCESS_DHCP;
								}

								if(ADRESSE_IP_NULLE != loc_u32_bridge_ip_adress) //CONDITION: adresse IP bridge OK
								{
									//Multicast
									Install_MulticastBridge(loc_ps_config); //ACCESS POINT / Bridge
								}//MODE_IP_DHCP_CLIENT: configuré dès réception de l'adresse IP
							}
							break;
						case MODE_RADIO_MODEM_STATION:
							switch(loc_ps_config->s_gene.u8_mode_network)
							{
								case MODE_NETWORK_BRIDGE:
									if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_bridge_mode_ip)
									{
										if((INADDR_NONE == u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_LAN].ps8_add_ip, &loc_u8_ret))||
										   (INADDR_NONE == u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip, &loc_u8_ret))
										  )//CONDITION: adresses effectées incorrectes
										{
											if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip)
											{
												strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip));
												strcpy(loc_ps8_addr_mask, ps8GetStringIp(MASK_RESEAU_SUR_24));
												printf("Echec udhcpc: Configuration Adresse IP DHCP de repli:%s\n",
														loc_ps8_addr_ip);
												//on configure l'adresse IP de repli DHCP du bridge
												CmdIfconfig_Down(NOM_INTERFACE_BRIDGE);
												CmdSystem_Generique("ifconfig %s %s netmask %s",
																	NOM_INTERFACE_BRIDGE,
																	loc_ps8_addr_ip,
																	loc_ps8_addr_mask);
												//Puis up du bridge
												CmdIfconfig_Up(NOM_INTERFACE_BRIDGE, loc_ps_config);

												loc_u32_bridge_ip_adress = loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip;
												loc_u32_bridge_mask = MASK_RESEAU_SUR_24;

												//Résultat DHCP
												u8_bridge_autostatut_ip = STATUT_IP__FAILURE_DHCP;
											}
										}
										else
										{
											loc_u32_bridge_ip_adress = u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_LAN].ps8_add_ip, &loc_u8_ret);
											loc_u32_bridge_mask = u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_LAN].ps8_mask, &loc_u8_ret);

											//Résultat DHCP
											u8_bridge_autostatut_ip = STATUT_IP__SUCCESS_DHCP;
										}

										if(ADRESSE_IP_NULLE != loc_u32_bridge_ip_adress) //CONDITION: adresse IP bridge OK
										{
											//Multicast
											Install_MulticastBridge(loc_ps_config); //STATION / Bridge
										}//MODE_IP_DHCP_CLIENT: configuré dès réception de l'adresse IP
									}
									break;
								case MODE_NETWORK_ROUTER:
									if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_wlan_mode_ip)
									{
										if(INADDR_NONE == u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip, &loc_u8_ret)) //CONDITION: adresse effectée incorrecte
										{
											if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip)
											{
												strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip));
												strcpy(loc_ps8_addr_mask, ps8GetStringIp(MASK_RESEAU_SUR_24));
												printf("Echec udhcpc: Configuration Adresse IP DHCP de repli:%s\n",
													loc_ps8_addr_ip);
												//on configure l'adresse IP de repli DHCP du WLAN
												CmdIfconfig_Down(NOM_INTERFACE_WIFI);
												CmdSystem_Generique("ifconfig %s %s netmask %s",
																	NOM_INTERFACE_WIFI,
																	loc_ps8_addr_ip,
																	loc_ps8_addr_mask);
												//Puis up du WLAN
												CmdIfconfig_Up(NOM_INTERFACE_WIFI, loc_ps_config);

												loc_u32_wlan_ip_adress = loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip;
												loc_u32_wlan_mask = MASK_RESEAU_SUR_24;

												//Résultat DHCP
												u8_wlan_autostatut_ip = STATUT_IP__FAILURE_DHCP;
											}
										}
										else
										{
											loc_u32_wlan_ip_adress = u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip, &loc_u8_ret);
											loc_u32_wlan_mask = u32DecodageAdresseReseau(s_exploit_process_prncpl.s_general.ps_interface[INTERFACE_WLAN].ps8_mask, &loc_u8_ret);

											//Résultat DHCP
											u8_wlan_autostatut_ip = STATUT_IP__SUCCESS_DHCP;
										}

										if(ADRESSE_IP_NULLE != loc_u32_wlan_ip_adress) //CONDITION: adresse IP WLAN OK
										{
											loc_u32_wlan_gateway = u32GetGatewayByDefault();
											//Installation Routage statique + dynamique
											Install_Bird(loc_ps_config, loc_u32_wlan_ip_adress, loc_u32_wlan_mask, loc_u32_wlan_gateway);
											//Routage politique
											Install_RulesForPolicyRouting(loc_ps_config);
											//Multicast
											Install_MulticastRouter(loc_ps_config);
											//Puis configuration du routeur NAT
											Install_Nat(loc_ps_config, loc_u32_wlan_ip_adress, loc_u32_wlan_mask);
										}
									}
									break;
								default:
									break;
							}
							break;
						default:
							break;
					}

					//Configuration NTP/SNTP client (car l'interface n'était jusqu'à maintenant pas configuré,
					//et aucune requete NTP/SNTP n'était émise)
					Uninstall_Time(loc_ps_config);
					Install_Time(loc_ps_config);

					u8_start_installDHCPClient = FALSE;	//FIN DE L'INSTALLATION DHCP CLIENT
				}
				else
				{
					//sinon on retente au prochain essai
					MACRO_PRINTF(("GestionInstall_DHCPClient: Probleme donnees inacessibles\n"));
					
				}
			}//sinon on attend
		}
		else //FICHIER présent: DISCOVERY DHCP en cours
		{
			u8_cpt_timeout_verif_dhcp = 0; //RAZ
			switch(loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				case MODE_RADIO_MODEM_ACCESS_POINT:
				case MODE_RADIO_MODEM_MONITOR:
					if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_bridge_mode_ip)
					{
						u8_bridge_autostatut_ip = STATUT_IP__DHCP_IN_PROGRESS;
					}
					break;
				case MODE_RADIO_MODEM_STATION:
					switch(loc_ps_config->s_gene.u8_mode_network)
					{
						case MODE_NETWORK_BRIDGE:
							if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_bridge_mode_ip)
							{
								u8_bridge_autostatut_ip = STATUT_IP__DHCP_IN_PROGRESS;
							}
							break;
						case MODE_NETWORK_ROUTER:
							if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_wlan_mode_ip)
							{
								u8_wlan_autostatut_ip = STATUT_IP__DHCP_IN_PROGRESS;
							}
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}

			//fermeture du fichier
			fclose(loc_pf_file);
		}
	}
	else
	{
		u8_cpt_timeout_verif_dhcp = 0; //RAZ
	}

}/*GestionInstall_DHCPClient*/

//=====================================================================================
// Fonction		: u32GetGatewayByDefault
// Entrees		: rien
// Sortie		: <loc_u32_gateway>
// Auteur		: CM - 26/04/2010 -
// Description	: Récupère valeur de l'adresse par défaut (si ça n'existe pas, retourne adresse nulle)
//=====================================================================================
u32sod u32GetGatewayByDefault(void)
{
	u32sod	loc_u32_gateway;
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_PROCNETROUTE+1];
	u16sod	loc_u16_cpt;
	s32sod	loc_s32_sscanf_route;
	S_STRUCT_IP_ROUTE_STATIC	loc_s_route;
	s8sod	loc_ps8_nom_interface[16];

	loc_u32_gateway = ADRESSE_IP_NULLE;	//INIT
	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT
	loc_s32_sscanf_route = 0; //INIT
	memset(&loc_s_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //INIT
	strcpy(loc_ps8_nom_interface,""); //INIT
	
	if(NULL == (loc_p_handle = fopen( FICHIER_PROC_NET_ROUTE, "rt" )))
	{
		printf("u32GetGatewayByDefault: KO lecture impossible!!!\n");
	}
	else
	{
		printf("u32GetGatewayByDefault: Lecture du fichier %s ...\n",FICHIER_PROC_NET_ROUTE);
		//Recherche de la route par défaut
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_PROCNETROUTE,loc_p_handle);
			if((0 != loc_u16_cpt)&&(NULL != loc_ps8_result_fgets)) //CONDITION: ligne lue et ce n'est pas la première
			{
				//La ligne est au format suivant:
				// "Iface\tDestination\tGateway\tFlags\tRefCnt\tUse\tMetric\tMask\t\tMTU\tWindow\tIRTT"
				memset(&loc_s_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //RAZ
				strcpy(loc_ps8_nom_interface,""); //RAZ

				//On lit a part les infos de route et d'interface, car interface mal décodée par sscanf
				loc_s32_sscanf_route = sscanf(loc_ps8_ligne, "%s\t%08lX\t%08lX\t%*04X\t%*d\t%*u\t%*d\t%08lX\t%*d\t%*u\t%*u",
											  loc_ps8_nom_interface,
											  &loc_s_route.u32_destination_ip,
											  &loc_s_route.u32_gateway_ip,
											  &loc_s_route.u32_destination_mask);

				if(4 == loc_s32_sscanf_route)//CONDITION: lecture de 4 valeurs
				{
					if(0==strcmp(loc_ps8_nom_interface, NOM_INTERFACE_WIFI))//CONDITION: INTERFACE WLAN
					{
						if(ADRESSE_IP_NULLE == loc_s_route.u32_destination_ip) //CONDITION: route par défaut
						{
							loc_u32_gateway = loc_s_route.u32_gateway_ip;
							printf("u32GetGatewayByDefault: gateway trouve = %s \n",ps8GetStringIp(loc_u32_gateway));
							loc_u16_cpt = NB_MAX_ROUTES_IP_TOTAL+1; //on sort
						}
					}
				}
				else
				{
					loc_u8_resultat = FALSE; //ligne ko
					printf("u32GetGatewayByDefault: KO decodage ligne (%ld) :%s !!!\n",
						   loc_s32_sscanf_route,
						   loc_ps8_ligne);
				}
			}

			loc_u16_cpt ++;


		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < NB_MAX_ROUTES_IP_TOTAL) &&
			   (TRUE == loc_u8_resultat)
			  );

		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u32_gateway;
	
}/*u32GetGatewayByDefault*/

//=====================================================================================
// Fonction		: ClearOrdreReconfiguration
// Entrees		: <loc_u8_idx_ordre> : index de l'ordre de reconfiguration
// Sortie		: rien
// Auteur		: CM - 21/04/2010 -
// Description	: RAZ ordre de reconfig
//=====================================================================================
void ClearOrdreReconfiguration(u8sod loc_u8_idx_ordre)
{
	if(loc_u8_idx_ordre < NB_MAX_ORDRE_RECONFIG)
	{
		pu8_ordre_reconfig[loc_u8_idx_ordre] = FALSE; //RAZ
	}
}/*ClearOrdreReconfiguration*/

//=====================================================================================
// Fonction		: SetOrdreReconfiguration
// Entrees		: <loc_u8_idx_ordre> : index de l'ordre de reconfiguration
// Sortie		: rien
// Auteur		: CM - 21/04/2010 -
// Description	: Ordre de reconfigurer
//=====================================================================================
void SetOrdreReconfiguration(u8sod loc_u8_idx_ordre)
{
	u8sod loc_u8_ordre;
	s32sod loc_s32_pid;

	loc_u8_ordre = FALSE;	//INIT
	loc_s32_pid = (-1);	//INIT
	
	if(loc_u8_idx_ordre < NB_MAX_ORDRE_RECONFIG)
	{
		switch(loc_u8_idx_ordre)
		{
			case ORDRE_RECONFIG__WPA_SUPPLICANT:
				loc_s32_pid = s32GetPidProcessus("wpa_supplicant", FICHIER_VAR_WPA_SUPPLICANT_PID);

				if(loc_s32_pid > 0) //CONDITION: Processus wpa_supplicant en cours d'execution
				{
					loc_u8_ordre = TRUE;
				}
				break;
			case ORDRE_RECONFIG__HOSTAPD:
				loc_s32_pid = s32ReadPid_InFile(FICHIER_VAR_HOSTAPD_PID);

				if(loc_s32_pid > 0) //CONDITION: Processus hostapd en cours d'execution
				{
					loc_u8_ordre = TRUE;
				}
				break;
			default:
				loc_u8_ordre = TRUE;
				break;
		}

		if(TRUE == loc_u8_ordre)
		{
			pu8_ordre_reconfig[loc_u8_idx_ordre] = TRUE;	//ordre activé
		}
	}
}/*SetOrdreReconfiguration*/

//=====================================================================================
// Fonction		: u8TestOrdreReconfiguration
// Entrees		: <loc_u8_idx_ordre> : index de l'ordre de reconfiguration
// Sortie		: <loc_u8_resultat> : etat de l'ordre de reconfiguration
// Auteur		: CM - 21/04/2010 -
// Description	: Retourne état de l'ordre de reconfiguration
//=====================================================================================
u8sod u8TestOrdreReconfiguration(u8sod loc_u8_idx_ordre)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT
	
	if(loc_u8_idx_ordre < NB_MAX_ORDRE_RECONFIG)
	{
		loc_u8_resultat = pu8_ordre_reconfig[loc_u8_idx_ordre]; //statut
	}
	
	return loc_u8_resultat;
}/*u8TestOrdreReconfiguration*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Apply_Cfg
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de apply_cfg
//=====================================================================================
void InitModule_Apply_Cfg(void)
{
	u8_cpt_timeout_verif_dhcp = 0;	//INIT

	memset(&s_config_impose,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	u8_backbone_connected = TRUE; //INIT
	
}/*InitModule_Apply_Cfg*/

