/*========================================================================*/
/* NOM DU FICHIER  : td_config.h	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009											  */
/* Libelle         : Base de données: Type def configuration			  */
/* Projet          : WRM100                                               */
/* Indice          : BE061                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration hostname
// - Intégration configuration par DHCP client
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE006 20/01/2010 CM
// - Modification définition de certains fichiers de la base de données
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du système
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE032 16/06/2010 CM
// - Correction BUG SSID si longueur chaine égale 32 caractères
//	=> iwconfig ne prend pas en compte une chaine de 32 caractères
//	par contre 31 caractères OK
// - Ajout gestion Radius / WPA - EAP
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
// - Ajout gestion debit MCS pour 802.11n
//BE043 29/10/2010 CM
// - Correction enum modes 802.11 (meilleur ergonomie)
//BE045 04/11/2010 CM
// - Correction plage des seuils des paramètres handoff
//	afin de pouvoir désactiver le handoff
//BE046 17/11/2010 CM
// - Correction plage du parametre de config vlan id
//	-> valeur 0 non autorisée
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
// - Modification mode scanning (handoff)
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
// - Ajout valeur PEAP/MSCHAPv2 dans authentification EAP (Radius)
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
// - Suppression du fichier de configuration advwf
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout configuration date/heure au démarrage de l'équipement
//BE061 10/05/2011
// - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//		si par exemple on vient du logiciel WRM100-MESH
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_constructeur.ps8_nom
#define LG_NOM_CONSTRUCTEUR		40

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_constructeur.ps8_numero_telephone
//Champs : s_constructeur.ps8_numero_fax
#define LG_NUMERO_TELEPHONE_FAX	30

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_constructeur.ps8_adresse_ligne1
//Champs : s_constructeur.ps8_adresse_ligne2
#define LG_ADRESSE				60

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_constructeur.ps8_site_web
#define LG_SITE_WEB				50

//******************************************************************
//**** DONNEES CONSTRUCTEUR
//******************************************************************
#define	NOM_DU_CONSTRUCTEUR			"ACTIA SODIELEC"
#define	TELEPHONE_DU_CONSTRUCTEUR	"33 (0)5 65 62 37 40"
#define	FAX_DU_CONSTRUCTEUR			"33 (0)5 65 62 30 70"
#define	SITE_DU_CONSTRUCTEUR		"www.sodielec.fr"
#define	ADRESSE_DU_CONSTRUCTEUR_L1	"BP 9"
#define	ADRESSE_DU_CONSTRUCTEUR_L2	"12100 Saint-Georges de Luzencon - FRANCE"
#define VALEUR_CONSTRUCTEUR_NON_UTILISEE "UNK"
//******************************************************************




//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.ps8_identifiant[]
#define LG_NOM_IDENTIFIANT	40

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.ps8_localisation[]
#define LG_NOM_LOCALISATION	40

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.ps8_mot_de_passe_low[]
//Champs : s_admin.ps8_mot_de_passe_middle[]
//Champs : s_admin.ps8_mot_de_passe_high[]
#define LG_NOM_PWD	12


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u16_duree_inactivite_http
#define DUREE_INACTIVITE_HTTP_MIN	1		//minute
#define DUREE_INACTIVITE_HTTP_MAX	1000	//minutes

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u8_max_client_ip
#define NB_CLIENT_IP_MIN	1
#define NB_CLIENT_IP_MAX	5

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u8_securisation_snmp
#define MODE_SECURISATION_SNMP_INACTIF	0
#define MODE_SECURISATION_SNMP_SET	1


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u16_tps_refresh_html
#define TPS_REFRESH_HTML_MIN		1
#define TPS_REFRESH_HTML_MAX		300

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u8_mode_date_heure
#define  MODE_DATE_HEURE_24H	0
#define  MODE_DATE_HEURE_12H	1

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u8_mode_mah
enum LISTE_MODE_MAH
{
	MODE_MAH_MANUELLE = 0,
	MODE_MAH_NTP,
	MODE_MAH_SNTP,
	NB_MAX_MODES_MAH
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.s_client_ntp.s8_fuseau_horaire
#define  VALEUR_MIN_FUSEAU_HORAIRE	(-12)		//heure
#define  VALEUR_MAX_FUSEAU_HORAIRE	12			//heure

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.s_client_ntp.u16_freq_maj_sntp
#define  VALEUR_MIN_FREQ_MAJ_HEURE_SNTP	1
#define  VALEUR_MAX_FREQ_MAJ_HEURE_SNTP	24

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u16_syslog_port
//Champs : s_nat.ps_rule_port_forwarding[].u16_private_port
//Champs : s_nat.ps_rule_port_forwarding[].u16_public_port
//Champs : s_ip_routing.ps_route_policy[].u16_critere_src_port_start
//Champs : s_ip_routing.ps_route_policy[].u16_critere_src_port_end
//Champs : s_ip_routing.ps_route_policy[].u16_critere_dst_port_start
//Champs : s_ip_routing.ps_route_policy[].u16_critere_dst_port_end
//Champs : s_wifi.s_wpa_security.s_server_radius.u16_radius_port
#define		PORT_UDP_TCP_MIN			1
#define		PORT_UDP_TCP_MAX			65535

//Autres ports:
#define		PORT_UDP__SNMP_REQUEST		161
#define		PORT_UDP__SNMP_NOTIFICATION	162
#define		PORT_UDP__SYSLOG			514
#define		PORT_UDP__RIP				520
#define		PORT_UDP__AUTH_RADIUS		1812
#define		PORT_UDP__ACCT_RADIUS		1813


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.u8_version_snmp
enum LISTE_VERSIONS_SNMP
{
	VERSION_SNMPV1 = 0,
	VERSION_SNMPV2C,
	NB_MAX_VERSIONS_SNMP					 
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.ps8_nom_communaute_get[]
//Champs : s_snmp.ps8_nom_communaute_set[]
//Champs : s_snmp.ps8_nom_communaute_trap[]
#define LG_MAX_NOM_COMMUNAUTE_SNMP	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.u8_emission_trap
#define	EMISSION_TRAP_INACTIVE	 0
#define	EMISSION_TRAP_ACTIVE	 1

//Variable : S_STRUCT_CONFIGURATION
//Champs : S_STRUCT_MANAGER_SNMP
#define NB_MANAGER_SNMP_MAX	5

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_manager_snmp[].u8_presence
#define	MANAGER_SNMP_ABSENT		 0
#define	MANAGER_SNMP_PRESENT	 1

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_manager_snmp[].ps8_nom[]
#define LG_NOM_MANAGER_SNMP		20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_manager_snmp[].u8_type_notification
enum LISTE_TYPES_NOTIFICATION
{
	TYPE_NOTIFICATION_TRAP = 0,
	TYPE_NOTIFICATION_INFORM,
	NB_MAX_TYPES_NOTIFICATION
};


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_trap_SNMPv1[].u16_nb_emission
#define	REEMISSION_TRAPV1_INFINI	0
#define	REEMISSION_TRAPV1_MIN	0
#define	REEMISSION_TRAPV1_MAX	65535

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_trap_SNMPv1[].u16_interval
#define	INTERVAL_TRAPV1_MIN	1
#define	INTERVAL_TRAPV1_MAX	65535

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_inform_SNMPv2c.u16_nb_emission
#define	REEMISSION_INFORM_MIN	1
#define	REEMISSION_INFORM_MAX	300

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_inform_SNMPv2c.u16_interval
#define	INTERVAL_INFORM_MIN		1
#define	INTERVAL_INFORM_MAX		60

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_trap_signevie.u16_cycle
#define	VALEUR_MIN_CYCLE_VIE	5
#define	VALEUR_MAX_CYCLE_VIE	43200	//(30 jours)


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.u8_mode_radio_modem
enum LISTE_MODES_RADIO_MODEM
{
	MODE_RADIO_MODEM_ACCESS_POINT = 0,
	MODE_RADIO_MODEM_STATION,
	MODE_RADIO_MODEM_MONITOR,
	NB_MAX_MODES_RADIO_MODEM,
//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
	MODE_RADIO_MODEM_MESH_POINT = 3,
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
};



//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.u8_mode_network
enum LISTE_MODES_NETWORK
{
	MODE_NETWORK_BRIDGE = 0,
	MODE_NETWORK_ROUTER,
	NB_MAX_MODES_NETWORK
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.ps8_hostname[]
#define LG_MIN_HOSTNAME	1
#define LG_MAX_HOSTNAME	30

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.u8_bridge_mode_ip
//Champs : s_gene.u8_wlan_mode_ip
enum LISTE_MODES_IP
{
	MODE_IP_STATIQUE = 0,
	MODE_IP_DHCP_CLIENT,
	NB_MAX_MODES_IP
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.u8_lan_fonction_dhcp
enum LISTE_FONCTIONS_DHCP
{
	FCT_DHCP_NONE = 0,
	FCT_DHCP_SERVER,
	FCT_DHCP_RELAY,
	NB_MAX_FCT_DHCP
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.u32_lan_dhcpsrv_duree_vie_bail
#define DHCP_DUREE_VIE_BAIL_MIN	1
#define DHCP_DUREE_VIE_BAIL_MAX	44640	//31 jours
#define DHCP_DUREE_VIE_BAIL_DEFAUT	1440	//1 jour

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.ps8_vlan_nom[TAILLE_MAX_VLAN +1]
#define TAILLE_MAX_VLAN		20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_gene.u16_vlan_id
#define VLAN_ID_MIN   1
#define VLAN_ID_MAX   4093

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_mode_802_11x
enum LISTE_MODES_WIFI_802_11
{
	MODE_WIFI_802_11G   = 0,
	MODE_WIFI_802_11B,
	MODE_WIFI_802_11A,
	MODE_WIFI_802_11NGHT20,
	MODE_WIFI_802_11NGHT40PLUS,
	MODE_WIFI_802_11NGHT40MINUS,
	MODE_WIFI_802_11NGHT40,
	MODE_WIFI_802_11NAHT20,
	MODE_WIFI_802_11NAHT40PLUS,
	MODE_WIFI_802_11NAHT40MINUS,
	MODE_WIFI_802_11NAHT40,
	MODE_WIFI_802_11ACHT20,
	MODE_WIFI_802_11ACHT40,
	MODE_WIFI_802_11ACHT80,
	NB_MAX_MODES_WIFI_802_11
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_11n_guard_interval
enum LISTE_11N_GUARD_INTERVAL
{
	GUARD_INTERVAL_LONG = 0,
	GUARD_INTERVAL_SHORT,
	NB_MAX_TYPE_GUARD_INTERVAL
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_channel_spectrum_width
enum LISTE_CHANNEL_SPECTRUM_WIDTH
{
	CHANNEL_SPECTRUM_WIDTH_20_MHZ = 0,
	CHANNEL_SPECTRUM_WIDTH_40_MHZ,
	CHANNEL_SPECTRUM_WIDTH_80_MHZ, //Add by VuHai
	NB_MAX_CHANNEL_SPECTRUM_WIDTH
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_type_selection_canal
enum LISTE_TYPE_SELECTION_CANAL
{
	TYPE_SELECTION_CANAL_ISO = 0,
	TYPE_SELECTION_CANAL_MULTI,
	TYPE_SELECTION_CANAL_AUTO,
	NB_MAX_TYPE_SELECTION_CANAL
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.pu16_multi_canal_radio[]
#define NB_MAX_MULTI_CANAUX  5

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_iso_canal_radio
//Champs : s_wifi.pu16_multi_canal_radio[]
#define CHANNEL_RADIO_DISABLED		65535

#define CHANNEL_DEFAULT_11A_FR	36
#define CHANNEL_DEFAULT_11BG	1

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_power_tx
#ifdef _WRM100_ABG_SELECT
#define POWER_TX_802_11ABG_MIN   0	//dBm
#define POWER_TX_802_11BG_MAX	19	//dBm
#define POWER_TX_802_11A_MAX	22	//dBm
#endif

#ifdef _WRM100_N_SELECT
#define POWER_TX_802_11ABGN_MIN	1	//dBm
//Rmq: puissance max fonction debit / nb antennes tx / mode 802.11
#endif

#define POWER_TX_802_11X_DEFAULT	18	//dBm


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_data_rate
enum LISTE_WIFI_DATA_RATE
{
	DATA_RATE_AUTOMATIC = 0,
	DATA_RATE_1_MBPS,
	DATA_RATE_2_MBPS,
	DATA_RATE_5_5_MBPS,
	DATA_RATE_11_MBPS,
	DATA_RATE_6_MBPS,
	DATA_RATE_9_MBPS,
	DATA_RATE_12_MBPS,
	DATA_RATE_18_MBPS,
	DATA_RATE_24_MBPS,
	DATA_RATE_36_MBPS,
	DATA_RATE_48_MBPS,
	DATA_RATE_54_MBPS,
	DATA_RATE_MCS0,
	DATA_RATE_MCS1,
	DATA_RATE_MCS2,
	DATA_RATE_MCS3,
	DATA_RATE_MCS4,
	DATA_RATE_MCS5,
	DATA_RATE_MCS6,
	DATA_RATE_MCS7,
	DATA_RATE_MCS8,
	DATA_RATE_MCS9,
	DATA_RATE_MCS10,
	DATA_RATE_MCS11,
	DATA_RATE_MCS12,
	DATA_RATE_MCS13,
	DATA_RATE_MCS14,
	DATA_RATE_MCS15,
	DATA_RATE_MCS16,
	DATA_RATE_MCS17,
	DATA_RATE_MCS18,
	DATA_RATE_MCS19,
	DATA_RATE_MCS20,
	DATA_RATE_MCS21,
	DATA_RATE_MCS22,
	DATA_RATE_MCS23,
	DATA_RATE_NSS1_MCS0,
	DATA_RATE_NSS1_MCS1,
	DATA_RATE_NSS1_MCS2,
	DATA_RATE_NSS1_MCS3,
	DATA_RATE_NSS1_MCS4,
	DATA_RATE_NSS1_MCS5,
	DATA_RATE_NSS1_MCS6,
	DATA_RATE_NSS1_MCS7,
	DATA_RATE_NSS1_MCS8,
	DATA_RATE_NSS1_MCS9,
	DATA_RATE_NSS2_MCS0,
	DATA_RATE_NSS2_MCS1,
	DATA_RATE_NSS2_MCS2,
	DATA_RATE_NSS2_MCS3,
	DATA_RATE_NSS2_MCS4,
	DATA_RATE_NSS2_MCS5,
	DATA_RATE_NSS2_MCS6,
	DATA_RATE_NSS2_MCS7,
	DATA_RATE_NSS2_MCS8,
	DATA_RATE_NSS2_MCS9,
	DATA_RATE_NSS3_MCS0,
	DATA_RATE_NSS3_MCS1,
	DATA_RATE_NSS3_MCS2,
	DATA_RATE_NSS3_MCS3,
	DATA_RATE_NSS3_MCS4,
	DATA_RATE_NSS3_MCS5,
	DATA_RATE_NSS3_MCS6,
	DATA_RATE_NSS3_MCS7,
	DATA_RATE_NSS3_MCS8,
	DATA_RATE_NSS3_MCS9,
	NB_MAX_DATA_RATE
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s8_seuil_rx
//Champs : s_handoff.s32_fgscan_detection_level
//Champs : s_handoff.s32_bgscan_detection_level
//Champs : s_handoff.s32_iso_detection_level
#define SEUIL_RX_MIN	(-OFFSET_RSSI_ATHEROS) //dBm
#define SEUIL_RX_MAX	(0)	 //dBm

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_mode_securite_wifi
enum LISTE_MODE_SECU_WIFI
{
	MODE_SECURITE_WIFI_AUCUN = 0,
	MODE_SECURITE_WIFI_WEP,
	MODE_SECURITE_WIFI_WPA,
	MODE_SECURITE_WIFI_WPA_TKIP,
	MODE_SECURITE_WIFI_WPA_AES,
	MODE_SECURITE_WIFI_WPA2,
	MODE_SECURITE_WIFI_WPA2_TKIP,
	MODE_SECURITE_WIFI_WPA2_AES,
	NB_MAX_MODES_SECURITE_WIFI
};


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wep_security.u8_key_length
enum LISTE_WEP_KEY_LENGTH
{
	WEP_KEY_LENGTH_64BIT = 0,
	WEP_KEY_LENGTH_128BIT,
	NB_MAX_WEP_KEY_LENGTH
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wep_security.u8_wep_key_type
//Champs : s_wifi.s_wpa_security.u8_wpa_key_type
enum LISTE_KEY_TYPE
{
	KEY_TYPE_HEXA = 0,
	KEY_TYPE_ASCII,
	NB_MAX_KEY_TYPE
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wep_security.ps8_key_value[NB_MAX_IDX_WEP_KEY][KEY_WEP_VALUE_LENGTH_MAX+1]
#define KEY_WEP_VALUE_LENGTH_MAX	26

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wep_security.u8_index_key_default
enum LISTE_WEP_IDX_KEY
{
	IDX_WEP_KEY_1 = 0,
	IDX_WEP_KEY_2,
	IDX_WEP_KEY_3,
	IDX_WEP_KEY_4,
	NB_MAX_IDX_WEP_KEY
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wep_security.u8_authentification
enum LISTE_WEP_AUTHENTIFICATION
{
	WEP_AUTHENTIFICATION_OPEN = 0,
	WEP_AUTHENTIFICATION_SHARED_KEY,
	NB_MAX_WEP_AUTHENTIFICATION
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.u8_authentification
enum LISTE_WPA_AUTHENTIFICATION
{
	WPA_AUTHENTIFICATION_PSK = 0,
	WPA_AUTHENTIFICATION_EAP,
	NB_MAX_WPA_AUTHENTIFICATION
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.u32_gp_key_update_interval
#define GP_KEY_UPDATE_INTERVAL_MIN	30
#define GP_KEY_UPDATE_INTERVAL_MAX	86400


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.ps8_pre_shared_key[LG_MAX_PRESHARED_WPA_TOTAL+1]
#define LG_MIN_PRESHARED_KEY_WPA		8
#define LG_MAX_PRESHARED_KEY_WPA_ASCII	63
#define LG_MAX_PRESHARED_KEY_WPA_HEXA	64
#define LG_MAX_PRESHARED_WPA_TOTAL		64

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared[LG_MAX_SHARED_RADIUS + 1]
#define LG_MAX_SHARED_RADIUS	64

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.u32_eap_reauth_period
#define EAP_REAUTH_PERIOD_DISABLED    0
#define EAP_REAUTH_PERIOD_MIN			30
#define EAP_REAUTH_PERIOD_MAX			86400

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.u8_eap_method
enum LISTE_EAP_METHOD
{
	EAP_METHOD__TTLS_PAP = 0,
	EAP_METHOD__TTLS_CHAP,
	EAP_METHOD__TTLS_EAP_MD5,
	EAP_METHOD__PEAP_MSCHAPV2,
	EAP_METHOD__TLS,
	NB_MAX_EAP_METHOD
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.ps8_identity[LG_MAX_EAP_IDENTITY + 1]
#define LG_MAX_EAP_IDENTITY	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.ps8_user_name[LG_MAX_EAP_USER_NAME + 1]
#define LG_MAX_EAP_USER_NAME	30

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.ps8_user_password[LG_MAX_EAP_USER_PASSWORD + 1]
#define LG_MAX_EAP_USER_PASSWORD	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.ps8_file_certificat_authority[LG_MAX_NOM_CERTIFICAT + 1]
//Champs : s_wifi.s_wpa_security.ps8_file_certificat_client[LG_MAX_NOM_CERTIFICAT + 1]
#define LG_MAX_NOM_CERTIFICAT	50

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.s_wpa_security.ps8_private_key_password[LG_MAX_PRIVATE_KEY_PWD + 1]
#define LG_MAX_PRIVATE_KEY_PWD	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_protcl_ABG_ACK_timeout
#define WF_ABG_ACK_TIMEOUT_MIN	1
#define WF_ABG_ACK_TIMEOUT_MAX	65535
#define WF_ABG_ACK_TIMEOUT_DEFAULT	65535

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_protcl_N_ACK_timeout
#define WF_N_ACK_TIMEOUT_MIN	0
#define WF_N_ACK_TIMEOUT_11NHT40_MAX	204
#define WF_N_ACK_TIMEOUT_11OTHER_MAX	409
#define WF_N_ACK_TIMEOUT_DEFAULT	25

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_protcl_type_preambule
enum LISTE_TYPE_PREAMBULE
{
	WF_TYPE_PREAMBULE_SHORT = 0,
	WF_TYPE_PREAMBULE_LONG,
	NB_MAX_WF_TYPE_PREAMBULE
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_protcl_fragment_threshold
#define	WF_FRAGMENT_THRESHOLD_MIN	256		//octets
#define WF_FRAGMENT_THRESHOLD_MAX	2346	//octets

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_protcl_RTS_CTS_threshold
#define WF_RTS_CTS_THRESHOLD_MIN		1		//octet
#define WF_RTS_CTS_THRESHOLD_MAX		2347	//octets

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_protcl_RTS_retry_limit
#define WF_RTS_RETRY_LIMIT_MIN   1
#define WF_RTS_RETRY_LIMIT_MAX  65535

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_protcl_beacon_period
//Champs : s_wifi.u16_time_between_2_beacon
#define WF_BEACON_PERIOD_MIN	20		//ms
#define WF_BEACON_PERIOD_MAX	1000	//ms

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_countryID
enum LISTE_COUNTRY_ID
{
	COUNTRY_ID_FRANCE = 0,
	COUNTRY_ID_AUSTRIA,
	COUNTRY_ID_BELGIUM,
	COUNTRY_ID_BULGARIA,
	COUNTRY_ID_CYPRUS,
	COUNTRY_ID_CZECH_REPUBLIC,
	COUNTRY_ID_DENMARK,
	COUNTRY_ID_ESTONIA,
	COUNTRY_ID_FINLAND,
	COUNTRY_ID_GERMANY,
	COUNTRY_ID_GREECE,
	COUNTRY_ID_ICELAND,
	COUNTRY_ID_IRELAND,
	COUNTRY_ID_ITALY,
	COUNTRY_ID_LATVIA,
	COUNTRY_ID_LITHUANIA,
	COUNTRY_ID_LUXEMBOURG,
	COUNTRY_ID_MALTA,
	COUNTRY_ID_NETHERLANDS,
	COUNTRY_ID_NORWAY,
	COUNTRY_ID_POLAND,
	COUNTRY_ID_PORTUGAL,
	COUNTRY_ID_ROMANIA,
	COUNTRY_ID_SLOVAKIA,
	COUNTRY_ID_SLOVENIA,
	COUNTRY_ID_SPAIN,
	COUNTRY_ID_SWEDEN,
	COUNTRY_ID_SWITZERLAND,
	COUNTRY_ID_UNITED_KINGDOM,
	COUNTRY_ID_USA,
	COUNTRY_ID_PUBLIC_SAFETY,
	NB_MAX_COUNTRY_ID
};


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_ant_ABG_tx_selection
enum LISTE_ABG_ANTENNE_TX
{
	ABG_SELECT_TX_ANTENNE_1 =  0,
	ABG_SELECT_TX_ANTENNE_2,
	NB_MAX_ABG_SELECT_ANT_TX
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_ant_ABG_rx_selection
enum LISTE_ABG_ANTENNE_RX
{
	ABG_SELECT_RX_ANTENNE_1 =  0,
	ABG_SELECT_RX_ANTENNE_2,
	ABG_SELECT_RX_DIVERSITY,
	NB_MAX_ABG_SELECT_ANT_RX
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u8_ant_N_selection
enum LISTE_N_ANTENNE
{
	N_SELECT_ANTENNE_1 =  0,
	N_SELECT_ANTENNES_1_ET_2,
	N_SELECT_ANTENNES_1_ET_2_ET_3,
	NB_MAX_N_SELECT_ANTENNES
};

//Variable : S_STRUCT_VAL_OPTION
//Champs : pt_definition_rate[].u8_nbstream
#define ZERO_STREAM		0
#define UN_STREAM		1
#define DEUX_STREAM		2
#define TROIS_STREAM		3
#define ALL_STREAM		4

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_ip_static[]
#define NB_MAX_ROUTES_IP_STATIC	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[NB_MAX_POLICY_ROUTING]
#define NB_MAX_POLICY_ROUTING	10

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[].ps8_policy_name
#define TAILLE_MAX_POLICY_NAME	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[].pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
//Champs : s_ip_routing.ps_route_policy[].pu8_not_critere[NB_MAX_CRITERIA_POLICY]
enum LISTE_CRITERES_ROUTE_POLICY
{
	CRITERIAPOLICY_SRC_IP = 0,
	CRITERIAPOLICY_DST_IP,
	CRITERIAPOLICY_LENGTH_PACKET,
	CRITERIAPOLICY_IP_PROTOCOL,
	CRITERIAPOLICY_SRC_PORT,
	CRITERIAPOLICY_DST_PORT,
	CRITERIAPOLICY_CLASS_SELECTOR,
	NB_MAX_CRITERIA_POLICY
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[].u16_critere_len_packet_min
//Champs : s_ip_routing.ps_route_policy[].u16_critere_len_packet_max
#define LEN_PACKET_MIN		0
#define LEN_PACKET_MAX		65535

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[].u8_critere_ip_protocol
enum LISTE_PROTOCOLE_POLICY_ROUTE
{
	POLICYROUTE_PROTOCOLE_UDP = 0,
	POLICYROUTE_PROTOCOLE_TCP,
	POLICYROUTE_PROTOCOLE_ICMP,
	NB_MAX_POLICYROUTE_PROTOCOLES
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[].u8_critere_class_selector
//Champs : s_ip_routing.ps_route_policy[].u8_new_class_selector
enum LISTE_CLASS_SELECTOR
{
	CLASSSELECTOR_CS0 = 0,
	CLASSSELECTOR_CS1,
	CLASSSELECTOR_CS2,
	CLASSSELECTOR_CS3,
	CLASSSELECTOR_CS4,
	CLASSSELECTOR_CS5,
	CLASSSELECTOR_CS6,
	CLASSSELECTOR_CS7,
	NB_MAX_CLASSSELECTOR
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_policy[].pu8_valid_action[NB_MAX_ACTIONS_POLICY]
enum LISTE_ACTIONPOLICY_ROUTE
{
	ACTIONPOLICY_GATEWAY= 0,
	ACTIONPOLICY_CLASS_SELECTOR,
	NB_MAX_ACTIONS_POLICY
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.pu8_rip_interface_used[NB_MAX_RIP_INTERFACES]
enum LISTE_RIP_INTERFACE
{
	RIP_INTERF_LAN = 0,
	RIP_INTERF_WLAN,
	NB_MAX_RIP_INTERFACES
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.u8_rip_authentification
enum LISTE_RIP_AUTHENTICATION
{
	RIP_AUTHENTICATION_NONE = 0,
	RIP_AUTHENTICATION_PLAIN_TEXT,
	RIP_AUTHENTICATION_MD5,
	NB_MAX_RIP_AUTHENTICATION
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps8_rip_password[TAILLE_MAX_RIP_PASSWORD+1]
#define TAILLE_MAX_RIP_PASSWORD	15
   

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_nat.ps_rule_port_forwarding[]
#define NB_MAX_RULES_PORT_FORWARDING	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_nat.ps_rule_port_forwarding[].u8_protocole
enum LISTE_PROTOCOLE_NAT
{
	NAT_PROTOCOLE_NON_SELECTIONNE = 0,
	NAT_PROTOCOLE_UDP,
	NAT_PROTOCOLE_TCP,
	NB_MAX_NAT_PROTOCOLES
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_nat.ps_rule_port_forwarding[].ps8_commentaire
#define TAILLE_MAX_COMMENT_NAT_PFWD	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_nat.ps_rule_mapping_adresse[]
#define NB_MAX_NAT_ALIAS_IP	10

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_nat.ps_rule_mapping_adresse[].ps8_commentaire
#define TAILLE_MAX_COMMENT_NAT_MPADR	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_multicast.ps_source_multicast[NB_MAX_SRC_MULTICAST]
#define NB_MAX_SRC_MULTICAST	20

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u8_scanning_mode
enum LISTE_MODES_SCANNING
{
	HO_MODE_SCANNING_AUTO = 0,
	HO_MODE_SCANNING_ACTIVE,
	HO_MODE_SCANNING_PASSIVE,
	NB_MAX_HO_MODES_SCANNING
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u16_time_between_hand_off
#define HO_TIME_BETW_HANDOFF_MIN		400		//ms
#define HO_TIME_BETW_HANDOFF_MAX		2500	//ms
#define HO_TIME_BETW_HANDOFF_DEFAULT	1000	//ms

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u16_bgscan_recurrence_period
#define HO_BGSCAN_PERIOD_MIN	15		//secondes
#define HO_BGSCAN_PERIOD_MAX	3600	//secondes

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u16_fgscan_beacon_missed_threshold
#define HO_FGSCAN_BEACON_MISSED_THRESH_MIN	10
#define HO_FGSCAN_BEACON_MISSED_THRESH_MAX	1000

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u16_iso_relevant_beacon_threshold
#define HO_ISO_RELEVANT_BEACON_THRESH_MIN	10
#define HO_ISO_RELEVANT_BEACON_THRESH_MAX	1000

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u8_type_filtrage_rssi
enum LISTE_TYPES_FILTRAGES_RSSI
{
	FILTR_RSSI_1 = 0,
	FILTR_RSSI_2,
	FILTR_RSSI_3,
	FILTR_RSSI_4,
	NB_MAX_TYPES_FILTRAGE_RSSI
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_handoff.u16_time_between_2_beacon
#define MINDWELL_TIME_DEFAULT	100	//ms


/*_____III - DEFINITIONS DE TYPES_________________________________________*/


// définition de la configuration du constructeur
//*******************************
typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	s8sod	ps8_nom[LG_NOM_CONSTRUCTEUR+1];					//Nom du constructeur
	s8sod	ps8_numero_telephone[LG_NUMERO_TELEPHONE_FAX+1];//Numéro de téléphone
	s8sod	ps8_numero_fax[LG_NUMERO_TELEPHONE_FAX+1];		//Numéro de fax
	s8sod	ps8_adresse_ligne1[LG_ADRESSE+1];				//Adresse
	s8sod	ps8_adresse_ligne2[LG_ADRESSE+1];				//Adresse
	s8sod	ps8_site_web[LG_SITE_WEB+1];					//Site web
}S_STRUCT_CONSTRUCTEUR;

//definition de la configuration CLIENT NTP
//*******************************
typedef struct 
{
	u32sod	pu32_adresse_serveur[NB_MAX_SERVEURS_NTP];	// Adresse IP du serveur NTP (principal)
	s8sod	s8_fuseau_horaire;		// Fuseau horaire
	u16sod	u16_freq_maj_sntp;		// Fréquence de mise à jour de l'heure par SNTP (en heure)

}S_STRUCT_CLIENT_NTP;

// définition de la configuration administration
//*******************************
typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	// Paramètres Administration : général
	s8sod	ps8_identifiant[LG_NOM_IDENTIFIANT+1];		// identifiant de l'equipement
	s8sod	ps8_localisation[LG_NOM_LOCALISATION+1];	// localisation de l'equipement
	s8sod	ps8_mot_de_passe_low[LG_NOM_PWD+1];			// mot de passe niveau low
	s8sod	ps8_mot_de_passe_middle[LG_NOM_PWD+1];		// mot de passe niveau middle
	s8sod	ps8_mot_de_passe_high[LG_NOM_PWD+1];		// mot de passe niveau high
	u16sod	u16_duree_inactivite_http;			// duree max inactivite sur serveur HTTP
	u8sod	u8_max_client_ip;					// nb max de client simultanes
	u8sod	u8_securisation_snmp;				// type de securisation du serveur SNMP
	u8sod	u8_langue;							// Choix de la langue pour LCD/HTTP/SNMP/FTP/....
	u16sod	u16_tps_refresh_html;				// Tps rafraichissement page HTML minimum (en secondes)

	// Paramètres Administration : dateHeure / NTP
	S_STRUCT_DATE	s_date_demarrage;		// Date/Heure du démarrage de l'équipement (par défaut) 
	u8sod	u8_mode_date_heure;				// Mode d'affichage de la date/heure (12H ou 24H)
	u8sod	u8_mode_mah;					// Mode de mise à l'heure (Manuelle ou NTP ou SNTP)
	S_STRUCT_CLIENT_NTP	s_client_ntp;		// Paramètres CLIENT NTP

	// Paramètres Administration : Syslog
	u8sod	u8_syslog_activation;			// Activation du syslog (TRUE ou FALSE)
	u8sod	u8_mode_RSSI;					// Activation du mode RSSI (syslog)  (TRUE ou FALSE)  pour WRM100-N et en mode station
	u32sod	u32_syslog_adresse_IP;			// Adresse IP, où sera envoyé les messages
	u16sod	u16_syslog_port;				// Port UDP, à partir duquel sera envoyé les messages
	
}S_STRUCT_CFG_ADMIN;



//definition d'un manager SNMP
//*******************************
typedef struct 
{
	s8sod	ps8_nom[LG_NOM_MANAGER_SNMP + 1];	// Nom du manager
	u32sod	u32_adresse_ip;				// Adresse du manager
	u8sod	u8_presence;				// Presence ou non du manager
	u8sod	u8_type_notification;		// Type de notification (trap ou inform) (SNMPv2c)
}S_STRUCT_MANAGER_SNMP;

//definition d'emission d'un trap SNMPv1
//*******************************
typedef struct 
{
	u16sod u16_nb_emission;		// nb de reemission d'un trap
	u16sod u16_interval;		// interval en secondes entre 2 emissions de trap identiques
}S_STRUCT_CFG_TRAPSNMPV1;

//definition d'emission d'un inform SNMPv2c
//*******************************
typedef struct 
{
	u16sod u16_nb_emission;		// nb de reemission d'un trap
	u16sod u16_interval;		// interval en secondes entre 2 emissions de trap identiques
}S_STRUCT_CFG_INFORMSNMPV2C;


//definition du trap de signe de vie 
//*******************************
typedef struct 
{
	u8sod u8_activation;	// Activation/Desactivation du trap SigneVie (TRUE ou FALSE)
	u16sod u16_cycle;		// Cycle de signe de vie (en minutes)
}S_STRUCT_SIGNEVIE_TRAP;

//définition de la configuration SNMP
//*******************************
typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	u8sod	u8_version_snmp;	//Version SNMP de l'agent SNMP (SNMPv1, SNMPv2c ou SNMPv3)
	s8sod	ps8_nom_communaute_get[LG_MAX_NOM_COMMUNAUTE_SNMP+1];// Nom de communaute GET
	s8sod	ps8_nom_communaute_set[LG_MAX_NOM_COMMUNAUTE_SNMP+1];// Nom de communaute SET
	s8sod	ps8_nom_communaute_trap[LG_MAX_NOM_COMMUNAUTE_SNMP+1];// Nom de communaute TRAP
	u8sod	u8_emission_trap;											// Activation / Désactivation émission des TRAPs
	S_STRUCT_MANAGER_SNMP		s_manager_snmp[NB_MANAGER_SNMP_MAX];	// Definition des managers SNMP
	S_STRUCT_CFG_TRAPSNMPV1		s_trap_SNMPv1[NIV_GRAVITE_MAX];			// Parametre du protocole d'émission d'un trapV1 en fonction de niveau de l'evt (SNMPv1)
	S_STRUCT_CFG_INFORMSNMPV2C	s_inform_SNMPv2c;						// Parametre du protocole d'émission d'un inform (SNMPv2c)
	S_STRUCT_SIGNEVIE_TRAP		s_trap_signevie;						// Gestion du trap de Signe de vie
}S_STRUCT_CFG_SNMP;

// Définition de la configuration GENERALE
//*******************************
typedef struct 
{
	u8sod	u8_start;					//debut des données de cette structure
	//Paramètres de configuration des modes
	u8sod	u8_mode_radio_modem;		//Mode de fonctionnement du produit radio modem (mode Access Point ou mode Station)
	u8sod	u8_mode_network;			//Mode réseau (bridge ou routeur)
	s8sod	ps8_hostname[LG_MAX_HOSTNAME+1]; //Hostname (permet d'identifier la machine dans un réseau)
	//Paramètres de configuration réseau du bridge
	u8sod	u8_bridge_mode_ip;			//Mode de fonctionnement IP du bridge (statique ou DHCP client)
	u32sod	u32_bridge_adresse_ip;		//Adresse IP du bridge (en mode statique)
	u32sod	u32_bridge_masque_reseau;	//Masque de sous-réseau du bridge (en mode statique)
	u32sod	u32_bridge_gateway;			//Passerelle du bridge (en mode statique)
	u32sod	u32_bridge_dhcp_fallback_ip;//Adresse IP de repli du bridge (en mode DHCP) avec un masque de 255.255.255.0 (et aucune passerelle)
	u8sod	u8_bridge_stp;				//Spaning Tree Protocol (STP) TRUE:activé, sinon FALSE

	//Paramètres de configuration réseau du routeur (Valable pour STATION uniquement)
	// --> Interface LAN  (en mode static forcé)
	u32sod	u32_lan_adresse_ip;			//Adresse IP de l'accès LAN (en mode statique)
	u32sod	u32_lan_masque_reseau;		//Masque de sous-réseau de l'accès LAN (en mode statique)
	// --> Interface WLAN
	u8sod	u8_wlan_mode_ip;			//Mode de fonctionnement IP de l'accès  WIFI (WLAN) (statique ou DHCP client)
	u32sod	u32_wlan_adresse_ip;		//Adresse IP de l'accès WIFI (en mode statique)
	u32sod	u32_wlan_masque_reseau;		//Masque de sous-réseau de l'accès WIFI (en mode statique)
	u32sod	u32_wlan_gateway;			//Passerelle sur l'accès Wifi (en mode statique)
	u32sod	u32_wlan_dhcp_fallback_ip;	//Adresse IP de repli de l'accès WIFI (en mode DHCP) avec un masque de 255.255.255.0 (et aucune passerelle)

	//Paramètres de configuration du serveur/relai DHCP
	u8sod	u8_lan_fonction_dhcp;		//Choix de la fonction DHCP sur l'accès LAN (aucune, serveur DHCP, relai DHCP)
	u32sod	u32_lan_dhcpsrv_ip_min;		//Adresse IP minimum du serveur DHCP (sur l'accès LAN)
	u32sod	u32_lan_dhcpsrv_ip_max;		//Adresse IP maximum du serveur DHCP (sur l'accès LAN)
	u32sod	u32_lan_dhcpsrv_duree_vie_bail;	//Durée de vie du bail d'attribution d'une adresse IP (minutes)
	u32sod	u32_lan_dhcprelay_ip;			//Adresse IP du serveur DHCP (où les requêtes DHCP sont relayées)

	//Paramètres de configuration du VLAN
	u8sod	u8_vlan_autoriser;			//Autorisation VLAN (TRUE: autorisé, FALSE: non autorisé)
	s8sod	ps8_vlan_nom[TAILLE_MAX_VLAN +1];	//Nom du VLAN
	u16sod	u16_vlan_id;				//ID du VLAN
	u8sod	u8_vlan_interface_notag;	//Autorisation ou non d'un interface non taggé (TRUE: autorisé, sinon FALSE)
	u32sod	u32_vlan_notag_adresse_ip;	//Adresse IP de l'accès non taggé
	u32sod	u32_vlan_notag_masque_reseau;	//Masque de sous-réseau de l'accès non taggé
	
}S_STRUCT_CFG_GENERAL;

//definition du WEP
//*******************************
typedef struct 
{
	u8sod	u8_key_length;		//Longueur de la clé  (64bits, 128bits)
	u8sod	u8_wep_key_type;	//Type de la clé (HEXA, ASCII)
	s8sod	ps8_key_value[NB_MAX_IDX_WEP_KEY][KEY_WEP_VALUE_LENGTH_MAX+1];	//Valeur des 4 clés WEP (pour gérer le changement fréquent des clés)
	u8sod	u8_index_key_default;	//Index par défaut de la clé WEP active (utilisée à l'émission des paquets)
	u8sod	u8_authentification;	//Authentification (Ouverte ou avec clé partagée)
	
}S_STRUCT_WEP_SECURITY;

//definition du serveur RADIUS
//*******************************
typedef struct 
{
	u32sod	u32_radius_adresse_ip;		//Adresse IP du serveur RADIUS
	u16sod	u16_radius_port;			//Port UDP du serveur RADIUS
	s8sod	ps8_radius_shared[LG_MAX_SHARED_RADIUS + 1];	//Clé d'accès au serveur Radius

}S_STRUCT_SERVER_RADIUS;

//definition du WPA
//*******************************
typedef struct 
{
	u8sod	u8_authentification;	//Mode authentification WPA (PSK, EAP)
	u32sod	u32_gp_key_update_interval;	//Intervalle de temps de changement de clés (en seconde)
	u8sod	u8_wpa_key_type;	//Type de clé (HEXA ou ASCII)
	s8sod	ps8_pre_shared_key[LG_MAX_PRESHARED_WPA_TOTAL+1]; //Clé partagée (PSK: Pre-Shared Key) dans le cas où la sécurité WIFI sélectionnée est WPA - PSK.
	
	//Paramètres WPA - EAP
	S_STRUCT_SERVER_RADIUS	s_server_radius;	//Paramètres de configuration d'un serveur RADIUS (WPA - EAP)
	u32sod	u32_eap_reauth_period;	//Période de ré-authentification EAP (en seconde) dans le cas où la sécurité WIFI sélectionnée est WPA - EAP.
	u8sod	u8_eap_method;	//Méthode EAP  (TTLS/CHAP, TTLS/PAP, TTLS/EAP-MD5) dans le cas où la sécurité WIFI sélectionnée est WPA - EAP.
	s8sod	ps8_identity[LG_MAX_EAP_IDENTITY + 1];	//Identité dans le cas où la sécurité WIFI sélectionnée est WPA - EAP.
#if PARAMETERS_RADIUS_NOT_USED
	s8sod	ps8_user_name[LG_MAX_EAP_USER_NAME + 1];	//Nom du user (aussi connu comme identity anonymous) dans le cas où la sécurité WIFI sélectionnée est WPA - EAP.
#endif
	s8sod	ps8_user_password[LG_MAX_EAP_USER_PASSWORD + 1];	//Mot de passe du user dans le cas où la sécurité WIFI sélectionnée est WPA - EAP.
	s8sod	ps8_file_certificat_authority[LG_MAX_NOM_CERTIFICAT + 1];	//Nom du certificat d'autorité spécifié pour la méthode d'authentification EAP-TLS
	s8sod	ps8_file_certificat_client[LG_MAX_NOM_CERTIFICAT + 1];	//Nom du certificat du client spécifié pour la méthode d'authentification EAP-TLS
	s8sod	ps8_private_key_password[LG_MAX_PRIVATE_KEY_PWD + 1];	//Clé privé pour la méthode d'authentification EAP-TLS.
	
}S_STRUCT_WPA_SECURITY;


// Définition de la configuration Wifi
//*******************************
typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	u8sod	u8_mode_802_11x;	//Mode de compatibilité 802.11x
								//   - 802.11g: réseau utilisant la fréquence de 2.4GHz, et fonctionnant à 54Mbits/s
								//   - 802.11b: réseau utilisant la fréquence de 2.4GHz, et fonctionnant à 11Mbits/s
								//   - 802.11a: réseau utilisant la fréquence de 5GHz, et fonctionnant à 54Mbits/s
								//   - 802.11ng: réseau utilisant la fréquence de 2.4GHz, et fonctionnant jusqu'à 300Mbits/s
								//   - 802.11na: réseau utilisant la fréquence de 5GHz, et fonctionnant jusqu'à 300Mbits/s
	s8sod	ps8_ssid_primary[NB_MAX_CHAINE_SSID + 1]; //SSID (Service Set IDentifier) primaire de l'interface Wifi
	u8sod	u8_dual_ssid;		//Activation du second SSID (TRUE ou FALSE)
	s8sod	ps8_ssid_secondary[NB_MAX_CHAINE_SSID + 1]; //SSID (Service Set IDentifier) secondaire de l'interface Wifi
	u8sod	u8_masquage_ssid;	//Masquage du SSID dans les communications entre AP et STATION (TRUE ou FALSE)
	u8sod	u8_11n_guard_interval;	//Intervalle de garde (pour mode 802.11n) (long ou court)
	u8sod	u8_channel_spectrum_width;	//Channel spectrum width
	u8sod	u8_type_selection_canal;	//Type de sélection du canal radio en mode STATION (iso, multi)
	u16sod	u16_iso_canal_radio;		//Numéro du canal radio (en mode iso fréquence)
	u16sod	pu16_multi_canal_radio[NB_MAX_MULTI_CANAUX];	//Liste des canaux  (en mode multi-fréquence)
	u8sod	u8_power_tx;	//Puissance d'émission (dBm)
	u8sod	u8_data_rate;	//Data rate (Automatic, ...)
	s8sod	s8_seuil_rx;	//Seuil du niveau reçu (dBm), au dessous duquel l'alarme associée est activée
	u16sod	u16_nb_max_associated_stations;	//Nombre maximum de stations qui sont autorisées à ce connectés sur l'AP
	u8sod	u8_mode_securite_wifi;	//Mode de sécurité WIFI

	S_STRUCT_WEP_SECURITY	s_wep_security;	//Paramètres de configuration du WEP (Wired Equivalent Privacy)
	S_STRUCT_WPA_SECURITY	s_wpa_security;	//Paramètres de configuration du WPA (Wi-Fi Protected Access)
	
	//Protocole wifi
	u16sod	u16_protcl_ABG_ACK_timeout;	//Timeout sur ACK (en µs) pour Driver-ABG
	u16sod	u16_protcl_N_ACK_timeout;	//Timeout sur ACK (en µs) pour Driver-N
	u8sod	u8_protcl_type_preambule;	//Type du preambule (court , long)
	u16sod	u16_protcl_fragment_threshold;	//Seuil de la fragmentation (en octets): Seuil à partir duquel un paquet est fragmenté
	u16sod	u16_protcl_RTS_CTS_threshold;	//Seuil RTS (en octets): Longueur maximum des paquets transmis sans la procédure RTS/CTS.
	u16sod	u16_protcl_RTS_retry_limit;	//Nombre de transmissions de trames RTS sans être acquittés par une trame CTS
	u16sod	u16_protcl_beacon_period;	//Durée entre balises (beacon)
	u8sod	u8_activation_WMM;		//Activation du WMM (Wireless for MultiMedia) (TRUE ou FALSE)
	u8sod	u8_countryID;		//Code pays pour Driver-N
	u8sod	u8_desactivation_DFS;		//Désactivation DFS (TRUE ou FALSE)

	//Antennes
	u8sod	u8_ant_ABG_tx_selection;	//Sélection de l'antenne TX (pour WRM100-ABG)
	u8sod	u8_ant_ABG_rx_selection;	//Sélection de l'antenne RX (pour WRM100-ABG)
	u8sod	u8_ant_N_selection;	//Sélection de l'antenne TX/RX (pour WRM100-N)
	
}S_STRUCT_CFG_WIFI;

//définition d'une route statique
typedef struct 
{
	u8sod	u8_enabled;				//route autorisée (TRUE ou FALSE)
	u32sod	u32_destination_ip;		//Adresse IP de la destination
	u32sod	u32_destination_mask;	//Masque sous-réseau de destination
	u32sod	u32_gateway_ip;			//Adresse IP de la passerelle
	u8sod	u8_interface;			//Interface
}S_STRUCT_IP_ROUTE_STATIC;

//définition d'une politique de routage IP
typedef struct 
{
	u8sod	u8_enabled;									//Autorisée ou non (TRUE ou FALSE)
	s8sod	ps8_policy_name[TAILLE_MAX_POLICY_NAME+1];	//Nom de la politique de routage
	u8sod	pu8_valid_critere[NB_MAX_CRITERIA_POLICY];	//Autorise ou non le critère de la politique (TRUE ou FALSE)
	u8sod	pu8_not_critere[NB_MAX_CRITERIA_POLICY];	//Inverse ou non le critère de la politique
	//Liste des critères
	u32sod	u32_critere_src_ip_start;					//Début plage des adresses IP source
	u32sod	u32_critere_src_ip_end;						//Fin plage des adresses IP source
	u32sod	u32_critere_dst_ip_start;					//Début plage des adresses IP de destination
	u32sod	u32_critere_dst_ip_end;						//Fin plage des adresses IP de destination
	u16sod	u16_critere_len_packet_min;					//Longueur minimum des paquets
	u16sod	u16_critere_len_packet_max;					//Longueur maximum des paquets
	u8sod	u8_critere_ip_protocol;						//Protocole IP
	u16sod	u16_critere_src_port_start;					//Début de la plage des ports source (pour UDP ou TCP)
	u16sod	u16_critere_src_port_end;					//Fin de la plage des ports source (pour UDP ou TCP)
	u16sod	u16_critere_dst_port_start;					//Début de la plage des ports destination (pour UDP ou TCP)
	u16sod	u16_critere_dst_port_end;					//Fin de la plage des ports destination (pour UDP ou TCP)
	u8sod	u8_critere_class_selector;					//Class selector
	//Liste des actions
	u8sod	pu8_valid_action[NB_MAX_ACTIONS_POLICY];	//Autorise ou non l'action de la politique (TRUE ou FALSE)
	u32sod	u32_new_gateway;							//Valeur de la nouvelle adresse IP de la passerelle
	u8sod	u8_new_class_selector;						//Valeur du nouveau class selector
	
}S_STRUCT_ROUTE_POLICY;


// Définition de la configuration routage
//*******************************

typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	S_STRUCT_IP_ROUTE_STATIC	ps_route_ip_static[NB_MAX_ROUTES_IP_STATIC];	//Liste des routes statiques
	S_STRUCT_ROUTE_POLICY		ps_route_policy[NB_MAX_POLICY_ROUTING];	//Liste des politiques de routage IP
	//paramètres routage dynamique RIPv2
	u8sod	u8_ripv2_activation;	//Activation du routage dynamique RIP2v (TRUE ou FALSE)
	u8sod	pu8_rip_interface_used[NB_MAX_RIP_INTERFACES];	//Interface utilisé pour RIPv2
	u8sod	u8_rip_authentification;	//Authentification RIPv2 (aucun, plain text, md5)
	s8sod	ps8_rip_password[TAILLE_MAX_RIP_PASSWORD+1];	//Mot de passe RIPv2
}S_STRUCT_CFG_IP_ROUTING;


// Définition de la configuration NAT
//*******************************

//définition d'une règle Port forwarding
typedef struct 
{
	u8sod	u8_enable;				//Règle autorisée ou non (TRUE ou FALSE)
	u32sod	u32_private_ip;			//Adresse IP privée
	u16sod	u16_private_port;		//Port privé
	u8sod	u8_protocole;			//Protocole associé au port à rediriger
	u16sod	u16_public_port;		//Port public
	s8sod	ps8_commentaire[TAILLE_MAX_COMMENT_NAT_PFWD + 1];	//Commentaire : pour décrire la règle
}S_STRUCT_NAT_RULE_PORT_FORWARDING;

//définition d'une règle NAT Mapping d'adresses
typedef struct 
{
	u8sod	u8_enable;				//Règle autorisée ou non (TRUE ou FALSE)
	u32sod	u32_private_ip;			//Adresse IP privée
	u32sod	u32_public_alias_ip;	//Adresse IP publique (alias de l'interface WLAN)
	s8sod	ps8_commentaire[TAILLE_MAX_COMMENT_NAT_MPADR + 1];	//Commentaire : pour décrire la règle
}S_STRUCT_NAT_RULE_MAP_ADRESSES;

typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	u8sod	u8_nat_activation;	//Activation on non de la fonction NAT (TRUE ou FALSE)
	S_STRUCT_NAT_RULE_PORT_FORWARDING	ps_rule_port_forwarding[NB_MAX_RULES_PORT_FORWARDING];	//Liste des règles de Port forwarding
	S_STRUCT_NAT_RULE_MAP_ADRESSES	ps_rule_mapping_adresse[NB_MAX_NAT_ALIAS_IP];	//Liste des règles de mapping d'adresses (uniquement si mode IP de l'accès WLAN est statique).
}S_STRUCT_CFG_NAT;

// Définition de la configuration Multicast
//*******************************
//définition d'une source multicast
typedef struct 
{
	u8sod	u8_enable;				//Source autorisée ou non (TRUE ou FALSE)
	u32sod	u32_adresse_reseau;		//Adresse réseau de la source multicast
	u32sod	u32_masque_reseau;		//Masque réseau  de la source multicast
}S_STRUCT_SRC_MULTICAST;

typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	u8sod	u8_proxy_igmp_activation;	//Activation on non du proxy IGMP (TRUE ou FALSE)
	S_STRUCT_SRC_MULTICAST ps_source_multicast[NB_MAX_SRC_MULTICAST];	//Liste des sources multicast autorisées
}S_STRUCT_CFG_MULTICAST;


// Définition de la configuration des évènements
//*******************************

//Définition de la structure de configuration d'un évènement
typedef struct 
{
	u16sod	u16_action;			// Action associé à l'évènement
	u8sod	u8_niveau_gravite;	// Niveau de gravité associé à l'évènement
}S_STRUCT_CFG_EVENT;

typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	S_STRUCT_CFG_EVENT	s_event[NB_MAX_EVENEMENTS];	// Tableau de configuration des évènements
}S_STRUCT_CFG_TABLE_EVT;

// Définition de la configuration de la fonction hand-off
//*******************************
typedef struct 
{
	u8sod	u8_start;			//debut des données de cette structure
	u8sod	u8_scanning_mode;	//Mode scanning (passive ou active ou auto)
	u16sod	u16_time_between_hand_off;		//Intervalle de temps entre 2 hand-off (pour éviter des effets ping-pong du hand-off) (en msec)
	u8sod	u8_bgscan_activation;	//Activation du scanning background (TRUE ou FALSE)
	u16sod	u16_bgscan_recurrence_period;	//Période de récurrence du scanning background (en secondes)
	s32sod	s32_bgscan_detection_level;	//Niveau moyenné de l'AP actuel au dessous duquel la phase de scanning background démarre (en dBm)
	s32sod	s32_fgscan_detection_level;	//Niveau moyenné de l'AP actuel au dessous duquel la phase de scanning foreground démarre (en dBm)
	u16sod	u16_fgscan_beacon_missed_threshold;	//Nombre maximum de balises consécutives (beacons) perdues de l'AP actuel avant que la phase de scanning foreground démarre
	s32sod	s32_iso_detection_level;			//Niveau moyenné du prochain AP au dessus duquel un hand-off est réalisé (cas du hand-off sur le même canal radio). Il faut que le niveau de l'AP actuel soit au-dessous du seuil. (dBm)
	u16sod	u16_iso_relevant_beacon_threshold;	//Nombre de balises consécutives (beacons) qui doivent être reçues au-dessus du niveau de puissance défini ci-dessus, avant de déclencher le hand-off. (cas du hand-off sur le même canal radio)
	u8sod	u8_type_filtrage_rssi;	//Type de filtrage RSSI
	u16sod	u16_time_between_2_beacon; //intervalle de temps entre 2 beacon, permet de fixer le mindwell time et ainsi d'optimiser le roaming
}S_STRUCT_CFG_HANDOFF;


//******************************************
/* structure configuration de l'équipement */
//******************************************
typedef struct 
{
	//Entete
	u16sod	u16_checksum_file;	//Checksum de la base de données
	u8sod	u8_start;	//debut des données de configuration

	S_STRUCT_CONSTRUCTEUR	s_constructeur;	//paramètres constructeur
	S_STRUCT_CFG_ADMIN		s_admin;		//paramètres administration
	S_STRUCT_CFG_SNMP		s_snmp;			//paramètres snmp
	S_STRUCT_CFG_GENERAL	s_gene;			//paramètres générales
	S_STRUCT_CFG_WIFI		s_wifi;			//paramètres wifi
	S_STRUCT_CFG_IP_ROUTING	s_ip_routing;	//paramètres du routage IP
	S_STRUCT_CFG_NAT		s_nat;			//paramètres de configuration de la NAT
	S_STRUCT_CFG_MULTICAST	s_multicast;	//paramètres de configuration du multicast
	S_STRUCT_CFG_TABLE_EVT	s_tabevt;		//Paramètres de configuration des évènements
	S_STRUCT_CFG_HANDOFF	s_handoff;		//Paramètres de configuration de la fonction hand-off
	
}S_STRUCT_CONFIGURATION;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


