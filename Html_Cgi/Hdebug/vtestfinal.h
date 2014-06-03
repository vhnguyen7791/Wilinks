/*========================================================================*/
/* NOM DU FICHIER  : vtestfinal.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : JP                                                   */
/* Date			   : 01/06/2010                                           */
/* Libelle         : HTML CGI: pages HTML de test						  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE031 01/06/2010 JP
// - CREATION
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE034 28/06/2010 CM
// - Correction configuration par défaut suite modif BE032
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE039 26/08/2010 CM
// - Intégration des modifications release_v2
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
// - Ajout paramètre de configuration pour 11n intervalle de garde
// - Integration des paramètres handoff
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Suppression du fichier de configuration advwf
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout nouveaux évènements liés au DFS
// - Ajout configuration "desactivation DFS" (WRM100-N)
// - Correction bug incohérence dans configuration par défaut
//		canal iso: 1 (non valid) --> 36 (valid) en mode 11a
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout configuration date/heure au démarrage de l'équipement
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VTESTFINAL
#define _VTESTFINAL_EXT
#else
#define _VTESTFINAL_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/
typedef struct 
{
	//Mode de fonctionnement
	u8sod	u8_mode;	//0:AP  0xFF:STATION
	//test a faire
	u8sod	u8_cfg_test;//ANT1_2_4G ou ANT1_5G ou ANT2_2_4G ou ANT2_5G
	}S_STRUCT_TESTFINAL;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VTestFinal
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Description	: Page HTML: TEST - FINAL PRODUCTION
//=====================================================================================
void VTestFinal(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VTestFinal_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Description	: Page rafraichissement 
//=====================================================================================
void VTestFinal_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: u8PassageConfigTest
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u8_mode> : mode de test (AP ou STA)
//				: <loc_u8_cfg_test> : test (ANT1_2_4G ou ANT1_5G ou ANT2_2_4G ou ANT2_5G)
// Sortie		: <loc_u8_resultat>: TRUE si OK, sinon FALSE 
// Description	: passage en config pour le test final
//=====================================================================================
u8sod u8PassageConfigTest(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_mode, u8sod loc_u8_cfg_test);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
#ifdef _VTESTFINAL
const S_STRUCT_CONFIGURATION S_CONFIG_EQUIPEMENT_TEST_BASE =
{
	//Entete
	0x0000,	//u16_checksum_file
	0x5A,	//u8_start

	// Paramètres CONSTRUCTEUR
	{//s_constructeur
		0x5A,	//u8_start
		NOM_DU_CONSTRUCTEUR,		//ps8_nom
		TELEPHONE_DU_CONSTRUCTEUR,	//ps8_numero_telephone
		FAX_DU_CONSTRUCTEUR,		//ps8_numero_fax
		ADRESSE_DU_CONSTRUCTEUR_L1,	//ps8_adresse_ligne1
		ADRESSE_DU_CONSTRUCTEUR_L2,	//ps8_adresse_ligne2
		SITE_DU_CONSTRUCTEUR,		//ps8_site_web
	},
	
	// Paramètres Administration
	{//s_admin
		0x5A,	//u8_start
		// Paramètres Administration : général
		{'i','d','e','n','t','i','f','i','a','n','t','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
		'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}, //ps8_identifiant[LG_NOM_IDENTIFIANT+1]
		{'l','o','c','a','l','i','s','a','t','i','o','n','\0','\0','\0','\0','\0','\0','\0','\0','\0',
		'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}, //ps8_localisation[LG_NOM_LOCALISATION+1]
		{'l','o','w','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},//ps8_mot_de_passe_low[LG_NOM_PWD+1]
		{'m','i','d','d','l','e','\0','\0','\0','\0','\0','\0','\0'},//ps8_mot_de_passe_middle[LG_NOM_PWD+1]
		{'h','i','g','h','\0','\0','\0','\0','\0','\0','\0','\0','\0'},//ps8_mot_de_passe_high[LG_NOM_PWD+1]
		10,	//u16_duree_inactivite_http
		5,	//u8_max_client_ip
		MODE_SECURISATION_SNMP_INACTIF,	//u8_securisation_snmp
		LANGUE_PAR_DEFAUT,				//u8_langue
		TPS_REFRESH_HTML_MIN,			//u16_tps_refresh_html
		
		// Paramètres Administration : dateHeure / NTP
		{//s_date_demarrage
			ANNEE_PAR_DEFAUT,	//u16_annee
			MOIS_PAR_DEFAUT,	//u8_mois
			JOUR_PAR_DEFAUT,	//u8_jour
			HEURE_PAR_DEFAUT,	//u8_heure
			MINUTE_PAR_DEFAUT,	//u8_minute
			SECONDE_PAR_DEFAUT,	//u8_seconde
		},
		MODE_DATE_HEURE_24H,			//u8_mode_date_heure
		MODE_MAH_MANUELLE,				//u8_mode_mah
		{//s_client_ntp
			{//s_client_ntp.pu32_adresse_serveur[NB_MAX_SERVEURS_NTP]
				ADRESSE_IP_NULLE,			//pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL]
				ADRESSE_IP_NULLE,			//pu32_adresse_serveur[SERVEUR_NTP_SECOURS]
			},
			1,							//s8_fuseau_horaire
			VALEUR_MIN_FREQ_MAJ_HEURE_SNTP,	//u16_freq_maj_sntp
		},

		// Paramètres Administration : Syslog
		FALSE,				//u8_syslog_activation
		FALSE,				//u8_mode_RSSI
		ADRESSE_IP_NULLE,	//u32_syslog_adresse_IP
		PORT_UDP__SYSLOG,	//u16_syslog_port
	},
	
	// Paramètres SNMP
	{//s_snmp
		0x5A,	//u8_start
		VERSION_SNMPV1,	//u8_version_snmp
		{'p','u','b','l','i','c','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},	//ps8_nom_communaute_get[LG_MAX_NOM_COMMUNAUTE_SNMP+1]
		{'p','r','i','v','a','t','e','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},	//ps8_nom_communaute_set[LG_MAX_NOM_COMMUNAUTE_SNMP+1]
		{'p','u','b','l','i','c','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},	//ps8_nom_communaute_trap[LG_MAX_NOM_COMMUNAUTE_SNMP+1]
		EMISSION_TRAP_ACTIVE,	//u8_emission_trap;				// Activation / Désactivation émission des TRAPs
		//S_STRUCT_MANAGER_SNMP s_manager_snmp[NB_MANAGER_SNMP_MAX];
		{//s_manager_snmp[NB_MANAGER_SNMP_MAX]
			{{'m','a','n','a','g','e','r','1',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[0]
			{{'m','a','n','a','g','e','r','2',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[1]
			{{'m','a','n','a','g','e','r','3',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[2]
			{{'m','a','n','a','g','e','r','4',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[3]
			{{'m','a','n','a','g','e','r','5',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP} //s_manager_snmp[4]
		},
		{//s_trap_SNMPv1[NIV_GRAVITE_MAX]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_INDETERMINE]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_CRITIQUE]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_MAJEUR]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_MINEUR]
			{20,180}	//s_trap_SNMPv1[NIV_GRAVITE_AVERTISSEMENT]
		},
		{REEMISSION_INFORM_MIN, INTERVAL_INFORM_MIN},	//s_inform_SNMPv2c
		{FALSE,	VALEUR_MIN_CYCLE_VIE},// s_trap_signevie
	},


	// Paramètres spécifiques au produit
	//===================================

	//paramètres générales
	{//s_gene
		0x5A,	//u8_start
		//Paramètres de configuration des modes
		MODE_RADIO_MODEM_STATION,		//u8_mode_radio_modem
		MODE_NETWORK_BRIDGE,			//u8_mode_network
		"wrm100",						//ps8_hostname[]
		//Paramètres de configuration réseau du bridge
		MODE_IP_STATIQUE,				//u8_bridge_mode_ip
		0xC05D7922,			//u32_bridge_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_bridge_masque_reseau
		ADRESSE_IP_NULLE,	//u32_bridge_gateway
		ADRESSE_IP_NULLE,	//u32_bridge_dhcp_fallback_ip
		FALSE,				//u8_bridge_stp

		//Paramètres de configuration réseau du routeur (Valable pour STATION uniquement)
		// --> Interface LAN (en mode static forcé)
		0xC05D7922,	//u32_lan_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_lan_masque_reseau
		// --> Interface WLAN
		MODE_IP_STATIQUE,	//u8_wlan_mode_ip
		0xC0A80102,			//u32_wlan_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_wlan_masque_reseau
		ADRESSE_IP_NULLE,	//u32_wlan_gateway
		ADRESSE_IP_NULLE,	//u32_wlan_dhcp_fallback_ip

		//Paramètres de configuration du serveur/relai DHCP
		FCT_DHCP_NONE,		//u8_lan_fonction_dhcp
		ADRESSE_IP_NULLE,	//u32_lan_dhcpsrv_ip_min
		ADRESSE_IP_NULLE,	//u32_lan_dhcpsrv_ip_max
		DHCP_DUREE_VIE_BAIL_DEFAUT,	//u32_lan_dhcpsrv_duree_vie_bail
		ADRESSE_IP_NULLE,	//u32_lan_dhcprelay_ip

		//Paramètres de configuration du VLAN
		FALSE,			//u8_vlan_autoriser
		"",				//ps8_vlan_nom[]
		VLAN_ID_MIN,	//u16_vlan_id
		TRUE,			//u8_vlan_interface_notag
		ADRESSE_IP_NULLE,	//u32_vlan_notag_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_vlan_notag_masque_reseau
	},

	//paramètres wifi
	{//s_wifi
		0x5A,	//u8_start
		MODE_WIFI_802_11A,	//u8_mode_802_11x
		"wrm100",		//ps8_ssid_primary[NB_MAX_CHAINE_SSID + 1]
		FALSE,			//u8_dual_ssid
		"wrm100_secondary",		//ps8_ssid_secondary[NB_MAX_CHAINE_SSID + 1]
		FALSE,			//u8_masquage_ssid
		GUARD_INTERVAL_LONG,	//u8_11n_guard_interval
		CHANNEL_SPECTRUM_WIDTH_20_MHZ,	//u8_channel_spectrum_width
		TYPE_SELECTION_CANAL_AUTO,	//u8_type_selection_canal
		CHANNEL_DEFAULT_11A_FR,	//u16_iso_canal_radio
		{//pu16_multi_canal_radio[NB_MAX_MULTI_CANAUX]
			CHANNEL_RADIO_DISABLED, //[0]
			CHANNEL_RADIO_DISABLED, //[1]
			CHANNEL_RADIO_DISABLED, //[2]
			CHANNEL_RADIO_DISABLED, //[3]
			CHANNEL_RADIO_DISABLED, //[4]
		},
		POWER_TX_802_11X_DEFAULT,	//u8_power_tx
		DATA_RATE_AUTOMATIC,		//u8_data_rate
		SEUIL_RX_MIN,	//s8_seuil_rx
		NB_ASSOCIATED_STATIONS_MAX,	//u16_nb_max_associated_stations
		MODE_SECURITE_WIFI_AUCUN,	//u8_mode_securite_wifi

		{//s_wep_security
			WEP_KEY_LENGTH_64BIT,	//u8_key_length
			KEY_TYPE_ASCII,			//u8_wep_key_type
			{//ps8_key_value[NB_MAX_IDX_WEP_KEY][KEY_WEP_VALUE_LENGTH_MAX+1]
				{"actia"}, //[IDX_WEP_KEY_1]
				{"actia"}, //[IDX_WEP_KEY_2]
				{"actia"}, //[IDX_WEP_KEY_3]
				{"actia"}, //[IDX_WEP_KEY_4]
			},
			IDX_WEP_KEY_1,	//u8_index_key_default
			WEP_AUTHENTIFICATION_OPEN,	//u8_authentification
		},
		{//s_wpa_security
			WPA_AUTHENTIFICATION_PSK,	//u8_authentification
			GP_KEY_UPDATE_INTERVAL_MAX,	//u32_gp_key_update_interval
			KEY_TYPE_ASCII,		//u8_wpa_key_type
			{"actiasodielec"},	//ps8_pre_shared_key[LG_MAX_PRESHARED_WPA_TOTAL+1]
			{//s_server_radius
				ADRESSE_IP_NULLE,		//u32_radius_adresse_ip
				PORT_UDP__AUTH_RADIUS,	//u16_radius_port
				"actiasodielec",		//ps8_radius_shared[LG_MAX_SHARED_RADIUS + 1]
			},
			EAP_REAUTH_PERIOD_DISABLED, //u32_eap_reauth_period
			EAP_METHOD__TTLS_PAP, //u8_eap_method
			"identity", //ps8_identity[LG_MAX_EAP_IDENTITY + 1]
#if PARAMETERS_RADIUS_NOT_USED
			"anonymous@example.com", //ps8_user_name[LG_MAX_EAP_USER_NAME + 1]
#endif
			"actia", //ps8_user_password[LG_MAX_EAP_USER_PASSWORD + 1]
			"",			//ps8_file_certificat_authority[LG_MAX_NOM_CERTIFICAT + 1]
			"",			//ps8_file_certificat_client[LG_MAX_NOM_CERTIFICAT + 1]
			"whatever",	//ps8_private_key_password[LG_MAX_PRIVATE_KEY_PWD + 1]
		},
		//Protocole wifi
		WF_ABG_ACK_TIMEOUT_DEFAULT,		//u16_protcl_ABG_ACK_timeout
		WF_N_ACK_TIMEOUT_DEFAULT,	//u16_protcl_N_ACK_timeout
		WF_TYPE_PREAMBULE_LONG,	//u8_protcl_type_preambule
		WF_FRAGMENT_THRESHOLD_MAX,	//u16_protcl_fragment_threshold
		WF_RTS_CTS_THRESHOLD_MAX,	//u16_protcl_RTS_CTS_threshold
		WF_RTS_RETRY_LIMIT_MAX, //u16_protcl_RTS_retry_limit
		100,			//u16_protcl_beacon_period
		TRUE,	//u8_activation_WMM
		COUNTRY_ID_FRANCE,	//u8_countryID
		FALSE,	//u8_desactivation_DFS

		//Antennes
		ABG_SELECT_TX_ANTENNE_1,	//u8_ant_ABG_tx_selection
		ABG_SELECT_RX_ANTENNE_1,	//u8_ant_ABG_rx_selection
		N_SELECT_ANTENNE_1,			//u8_ant_N_selection
	},

	//paramètres du routage
	{//s_ip_routing
		0x5A,	//u8_start
		{//s_ip_routing.ps_route_ip_static[NB_MAX_ROUTES_IP_STATIC]
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //0
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //1
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //2
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //3
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //4
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //5
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //6
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //7
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //8
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //9
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //10
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //11
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //12
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //13
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //14
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //15
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //16
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //17
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //18
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //19
		},
		{//s_ip_routing.ps_route_policy[NB_MAX_POLICY_ROUTING]
			{//ps_route_policy[0]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[1]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[2]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[3]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[4]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[5]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[6]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[7]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[8]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[9]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
		},
		//paramètres routage dynamique RIPv2
		FALSE,	//u8_ripv2_activation
		{//pu8_rip_interface_used[NB_MAX_RIP_INTERFACES]
			FALSE,	//RIP_INTERF_LAN
			FALSE,	//RIP_INTERF_WLAN
		},
		RIP_AUTHENTICATION_NONE, //u8_rip_authentification
		"actia sodielec",	//ps8_rip_password[TAILLE_MAX_RIP_PASSWORD+1]
	},

	//paramètres du NAT
	{//s_nat
		0x5A,	//u8_start
		FALSE,	//u8_nat_activation
		{//s_nat.ps_rule_port_forwarding[NB_MAX_RULES_PORT_FORWARDING]
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //0
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //1
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //2
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //3
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //4
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //5
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //6
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //7
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //8
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //9
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //10
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //11
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //12
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //13
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //14
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //15
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //16
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //17
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //18
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //19
		},
		{//s_nat.ps_rule_mapping_adresse[NB_MAX_NAT_ALIAS_IP]
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //0
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //1
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //2
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //3
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //4
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //5
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //6
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //7
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //8
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //9
		},
	},

	//paramètres du multicast
	{//s_multicast
		0x5A,	//u8_start
		FALSE,	//u8_proxy_igmp_activation
		{//ps_source_multicast[NB_MAX_SRC_MULTICAST]
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //0
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //1
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //2
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //3
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //4
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //5
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //6
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //7
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //8
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //9
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //10
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //11
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //12
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //13
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //14
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //15
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //16
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //17
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //18
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //19
		},
	},
	
	{//s_tabevt
		0x5A,	//u8_start
		{//s_event[NB_MAX_EVENEMENTS]
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT000_AL_SYNTHESE_1
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT001_DEFAUT_EQUIPEMENT
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT002_AL_TEMPERATURE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT003_AL_ETHERNET_LAN_1
			{0xFFFD, NIV_GRAVITE_INDETERMINE},	//EVT004_AL_ETHERNET_LAN_2 : alarme non validée par défaut
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT005_AL_NIVEAU_RECU
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT006_STATION_NON_CONNECTEE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT007_PROBLEME_CONFIGURATION
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT009_RETOUR_SUR_SSID_PRIMAIRE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT011_RADAR_DETECTE_SUR_CANAL
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT012_BASCULEMENT_VERS_CANAL
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT013_CONNEXION_STATION
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT014_DECONNEXION_STATION
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT015_CONNEXION_ACCESS_POINT
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT016_DECONNEXION_ACCESS_POINT
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT017_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT018_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT019_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT020_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT021_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT022_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT023_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT024_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT025_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT026_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT027_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT028_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT029_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT030_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT031_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT032_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT033_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT034_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT035_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT036_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT037_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT038_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT039_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT040_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT041_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT042_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT043_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT044_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT045_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT046_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT047_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT048_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT049_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT050_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT051_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT052_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT053_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT054_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT055_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT056_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT057_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT058_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT059_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT060_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT061_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT062_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT063_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT064_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT065_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT066_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT067_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT068_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT069_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT070_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT071_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT072_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT073_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT074_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT075_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT076_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT077_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT078_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT079_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT080_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT081_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT082_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT083_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT084_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT085_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT086_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT087_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT088_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT089_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT090_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT091_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT092_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT093_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT094_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT095_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT096_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT097_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT098_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT099_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT100_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT101_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT102_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT103_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT104_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT105_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT106_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT107_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT108_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT109_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT110_JOURNAL_BORD_EFFACE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT111_INF_RAZ_ALARMES_MEMO
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT112_EVOLUTION_CONFIGURATION
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT113_ORDRE_RESET_TELECOMMANDE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT114_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT115_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT116_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT117_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT118_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT119_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT120_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT121_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT122_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT123_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT124_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT125_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT126_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT127_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT128_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT129_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT130_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT131_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT132_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT133_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT134_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT135_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT136_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT137_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT138_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT139_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT140_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT141_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT142_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT143_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT144_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT145_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT146_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT147_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT148_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT149_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT150_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT151_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT152_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT153_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT154_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT155_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT156_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT157_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT158_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT159_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT160_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT161_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT162_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT163_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT164_INF_ACQUIT_ALARMES_IRREVERSIBLES
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT165_INF_NOUVELLE_MISE_REF_ECHOS
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT166_INF_RAZ_MESURES_DVBH
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT167_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT168_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT169_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT170_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT171_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT172_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT173_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT174_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT175_INF_EQUIPEMENT_ON
			{(0xFFFF & (u16sod)(~(1<<ACTION_EVT_JDB))), NIV_GRAVITE_INDETERMINE},	//EVT176_INF_SIGNE_DE_VIE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT177_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT178_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT179_RESERVE
		},
	},

	//Paramètres de configuration de la fonction hand-off
	{//s_handoff
		0x5A,	//u8_start
		HO_MODE_SCANNING_AUTO,	//u8_scanning_mode
		HO_TIME_BETW_HANDOFF_DEFAULT,	//u16_time_between_hand_off
		FALSE,	//u8_bgscan_activation
		HO_BGSCAN_PERIOD_MAX,	//u16_bgscan_recurrence_period
		MACRO_RSSI2DBM(20),	//s32_bgscan_detection_level
		MACRO_RSSI2DBM(15),	//s32_fgscan_detection_level
		HO_FGSCAN_BEACON_MISSED_THRESH_MIN,	//u16_fgscan_beacon_missed_threshold
		MACRO_RSSI2DBM(20),	//s32_iso_detection_level
		HO_ISO_RELEVANT_BEACON_THRESH_MAX,	//u16_iso_relevant_beacon_threshold
		FILTR_RSSI_1,	//u8_type_filtrage_rssi
		MINDWELL_TIME_DEFAULT, //u16_time_between_2_beacon
	},
	
	
};
#else
extern const S_STRUCT_CONFIGURATION S_CONFIG_EQUIPEMENT_TEST_BASE;
#endif
