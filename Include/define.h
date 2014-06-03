/*========================================================================*/
/* NOM DU FICHIER  : define.h                                             */
/*========================================================================*/
/* Auteur		   : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle  	   : DEFINE												  */
/* Projet          : WRM100                                               */
/* Indice          : BE060												  */
/*========================================================================*/
/*  Historique		:                                                     */
//BE000 09/09/2009 CM
// - CREATION
//BE012 24/02/2010 CM
// - Modification nom de l'interface "BRIDGE"
//		"bridge" remplacé par "br0"
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//BE025 15/04/2010 CM
// - Modification gestion routage par le processus bird
//	et non plus via des commandes de type "route"
//BE026 26/04/2010 CM
// - Correction lecture /proc/net/route
//	il faut comptabiliser les routes statiques, dynamiques 
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE042 07/10/2010 CM
// - Definition macro RSSI => dBm (et inverse)
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout nouveaux évènements liés au DFS
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/

/*______I - COMMENTAIRES - DEFINITIONS - REMARQUES________________________*/

/*______II - DEFINE - SBIT________________________________________________*/

#ifdef _DEFINE
#define _DEFINE_EXT
#else
#define _DEFINE_EXT	extern
#endif

#define DEBUG_PC_LINUX			0	//1:activée 0: désactivée

#if DEBUG_PC_LINUX
#warning "########### DEBUG_PC_LINUX: ACTIVE ##########"
#warning "########### DEBUG_PC_LINUX: ACTIVE ##########"
#warning "########### DEBUG_PC_LINUX: ACTIVE ##########"
#endif

#define VERSION_WRM100_DEMO	1	//1:activée 0: désactivée
								//avec mode 802.11 forcé en 11a uniquement
								//	   type_canal en station = automatic	
								//	   mode securite = aucun

#define CLIENT_NTP_ACTIF	1	//0:non 1:oui

#define SERVEUR_FTP_ACTIF	1	//0:non 1:oui

//d: DEBUG suivi evènement dans la gestion
#define ACTIVATION_DEBUG_SUIVI_EVENT		0   	//1:activée 0: désactivée
#define INDEX_DEBUG_EVENT		EVT012_BASCULEMENT_VERS_CANAL	//index de l'evt suivi pour le debug
#if ACTIVATION_DEBUG_SUIVI_EVENT
#warning "########### ACTIVATION_DEBUG_SUIVI_EVENT: ACTIVE ##########"
#warning "########### ACTIVATION_DEBUG_SUIVI_EVENT: ACTIVE ##########"
#warning "########### ACTIVATION_DEBUG_SUIVI_EVENT: ACTIVE ##########"
#endif
//f: DEBUG suivi evènement dans la gestion

#define TEST_DEBUG_EVENT 0	//0: désactivé 1:activé
#if TEST_DEBUG_EVENT
#warning "########### TEST_DEBUG_EVENT: ACTIVE ##########"
#warning "########### TEST_DEBUG_EVENT: ACTIVE ##########"
#warning "########### TEST_DEBUG_EVENT: ACTIVE ##########"
#endif

//Radius
#define PARAMETERS_RADIUS_NOT_USED	0	//0:désactivé 1:activé


//#define MACRO_PRINTF(x)     if (1) {printf x;}
#define MACRO_PRINTF(x)     if (1) {AddMsgDbgLog x;}
//Add by Vu Hai for api_network.h
#define LOG_CONSOLE			0x10
#define LOG_ONLY_CONSOLE	0x80
//------------------------------------------------------------------------------------------
#define MACRO_DPRINTF(type, message, ...)     if (1) {\
					      if(0 != ((LOG_CONSOLE|LOG_ONLY_CONSOLE) & type)) \
					      { \
					      printf(message, ##__VA_ARGS__); \
					      } \
					      if(0 == (LOG_ONLY_CONSOLE & type)) \
					      { \
					      SyslogSodielec(LOG_PRI(type), message, ##__VA_ARGS__); \
					      } \
}
//------------------------------------------------------------------------------------------
//Fin Add by VuHai

#define TRUE 1
#define FALSE 0

#define OUI TRUE
#define NON FALSE

#define ON  TRUE
#define OFF FALSE

#define SUCCESS  TRUE
#define FAIL	 FALSE

//Mot de passe (par défaut pour développeur)
#define MOT_DE_PASSE_SODIELEC "goLum"

#define NB_BITS_DANS_U32	32

//Définition format de l'adresse IP
#define MAX_LG_FORMAT_ADRESSE_IP  15 //caracteres

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.u8_langue
enum LISTE_DES_LANGUES
{
	LANGUE_FRANCAIS =0	,
	LANGUE_ANGLAIS		,
	NB_MAX_LANGUES
};

#define LANGUE_PAR_DEFAUT	LANGUE_FRANCAIS

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_ip_routing.ps_route_ip_static[].u8_interface
//Variable : S_STRUCT_EXPLOITATION
//Champs : s_general.ps_interface[]
enum LISTE_INTERFACES
{
	INTERFACE_AUTOMATIQUE = 0,
	INTERFACE_LAN,
	INTERFACE_WLAN ,
	NB_MAX_INTERFACES
};

//Pour pouvoir utiliser la référence bridge
#define INTERFACE_BRIDGE INTERFACE_AUTOMATIQUE


//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.u16_nb_max_associated_stations
//Variable : S_STRUCT_EXPLOITATION
//Champs : s_access_point.s_wifi_client[]
#define NB_ASSOCIATED_STATIONS_MIN  1
#define NB_ASSOCIATED_STATIONS_MAX  100


#define NOM_INTERFACE_ETHERNET		"eth0"
#define NOM_INTERFACE_WIFI			"wlan0" //Modif by VuHai
#define NOM_INTERFACE_BRIDGE		"br0"
#define NOM_INTERFACE_LOOPBACK		"lo"
#define NOM_INTERFACE_LMAC_WIFI		"wifi0"

//Debit interface ethernet
#define DEBIT_MAX_INTERFACE_ETHERNET	100000000		//bits/s

//********************************************************
//Longueur max autorisé dans les chaines de caractères
//********************************************************
#define U16_LG_MAX_CHAINE_VALIDE		500
//********************************************************
//Liste des catactères autorisés pour les chaînes de caractères
//********************************************************
#define U8_CARACT_ASCII_AUTORISE_MIN		0x20	//' '
#define U8_CARACT_ASCII_AUTORISE_MAX		0xFF
//********************************************************
//sauf des catactères interdits
//********************************************************
#define U8_CARACT_ASCII_INTERDIT_GUILLEMENT		'\"'	//0x22
#define U8_CARACT_ASCII_INTERDIT_POURCENTAGE	'\%'	//0x25
#define U8_CARACT_ASCII_INTERDIT_ETNUMERIC		'&'		//0x26
#define U8_CARACT_ASCII_INTERDIT_APOSTROPHE		'\''	//0x27
#define U8_CARACT_ASCII_INTERDIT_BACKSLASH		'\\'	//0x5C
#define U8_CARACT_ASCII_INTERDIT_PIPE			'|'		//0x7C
#define U8_CARACT_ASCII_INTERDIT_MIN			0x7F		
#define U8_CARACT_ASCII_INTERDIT_MAX			0x9F
#define U8_CARACT_ASCII_TIRET					0x2D	// (45) => '-'	
#define U8_CARACT_ASCII_POINT_VIRGULE			0x3B	// (59) => ';'	
#define U8_CARACT_ASCII_ZERO					0x30	// (48) => '0'	
#define U8_CARACT_ASCII_NEUF					0x39	// (57) => '9'	


//Paramètres IP particuliers
#define MASK_RESEAU_SUR_24	0xFFFFFF00
#define ADRESSE_IP_NULLE	0x00000000
#define MASK_RESEAU_SUR_32	0xFFFFFFFF
#define ADRESSE_IP_LOCALE	0x7F000001	//127.0.0.1

//Paramètres IP multicast
#define	ADRESSE_MULTICAST_MIN	0xE0000000
#define	ADRESSE_MULTICAST_MAX	0xEFFFFFFF
#define MASK_MULTICAST			0xF0000000
//Add by Vu Hai for api_network.h
#define	ADRESSE_MULTICAST_RESERVED_MIN			0xE0000000
#define	ADRESSE_MULTICAST_RESERVED_MAX			0xE0000012
//Fin Add by Vu Hai

//Nombre total de routes (statique + dynamique)
#define NB_MAX_ROUTES_IP_TOTAL		1000

//Variable : S_STRUCT_EXPLOITATION
//Champs : s_general.ps_interface[].u8_statut_ip
//Variable : S_STRUCT_CIP_MONITOR
//Champs : u8_bridge_autostatut_ip
//Champs : u8_wlan_autostatut_ip
enum LISTE_DES_STATUTS_IP
{
	STATUT_IP__UNDEFINED = 0,
	STATUT_IP__STATIC,
	STATUT_IP__DHCP_IN_PROGRESS,
	STATUT_IP__SUCCESS_DHCP,
	STATUT_IP__FAILURE_DHCP,
	NB_MAX_STATUTS_IP
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_wifi.ps8_ssid_primary[]
//Champs : s_wifi.ps8_ssid_secondary[]
//Variable : S_STRUCT_EXPLOITATION
//Champs : s_station.ps8_ssid_inprogress[]
#define NB_MIN_CHAINE_SSID  1
#define NB_MAX_CHAINE_SSID  31

//Variable : S_STRUC_EXP_ACCESS_POINT
//Champs : s_general.pu8_presence_serveur_ntp[]
//Variable : S_STRUCT_CONFIGURATION
//Champs : s_admin.pu32_adresse_serveur[]
enum LIST_SERVEURS_NTP
{
	SERVEUR_NTP_PRINCIPAL = 0,
	SERVEUR_NTP_SECOURS,
	NB_MAX_SERVEURS_NTP
};

//Valeur RSSI_Max (atheros)
//mesurée de façon empirique (en comparant niveau reçu (en dBm) de /proc/net/wireless  et la valeur RSSI de Ioctl_RSSIFilter)
//	(voir spec_mesure_RSSI_dBm.ods)
#define RSSI_MAX_ATHEROS	107 
#define OFFSET_RSSI_ATHEROS 95 

//MACRO RSSI => DBM
#define MACRO_RSSI2DBM(val_rssi) ((val_rssi * RSSI_MAX_ATHEROS)/100 - OFFSET_RSSI_ATHEROS)
//MACRO DBM => RSSI
#define MACRO_DBM2RSSI(val_dbm) (((val_dbm + OFFSET_RSSI_ATHEROS)*100)/RSSI_MAX_ATHEROS)


//Variable : S_STRUCT_JDBEVT
//Champs : s_evt[].u8_etat_evt
//Variable : S_STRUCT_CIP_ELEMENT_FIFOTRAP
//Champs : u8_etat_evt
//Variable : S_STRUCT_STATUS_TRAPS
//Champs : s_trap[].u8_etat_evt
enum LISTE_ETAT_EVENT
{
	ETAT_EVT_DEBUT =0,
	ETAT_EVT_FIN,
	ETAT_EVT_INFO,
	NB_MAX_ETATS_EVENT,
	ETAT_EVT_NON_DEFINI
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_snmp.s_trap_SNMPv1[]
//Champs : s_tabevt.s_event[].u8_niveau_gravite
enum LISTE_NIVEAUX_GRAVITE
{
	NIV_GRAVITE_INDETERMINE = 0,
	NIV_GRAVITE_CRITIQUE,
	NIV_GRAVITE_MAJEUR,
	NIV_GRAVITE_MINEUR,
	NIV_GRAVITE_AVERTISSEMENT,
	NIV_GRAVITE_MAX
};

//Variable : S_STRUCT_CONFIGURATION
//Champs : s_tabevt.s_event[].u16_action
enum LISTE_DES_ACTIONS_ASSOCIES_A_EVENEMENT
{
	ACTION_EVT_SYNTHESE_1 =0	,
	ACTION_EVT_VALIDE			,
	ACTION_EVT_JDB				,
	ACTION_EVT_TRAP				,
	NB_MAX_ACTION_EVT			,
	ACTION_EVT_FILTRE_JDB =14	,
	ACTION_EVT_PHASE_INIT =15
};

//Variable : S_STRUCT_DESCRIPTION_EVT
//Champs : u8_type_evt
#define TYPE_EVT_ALARME			0
#define TYPE_EVT_INFO			1
#define TYPE_EVT_GENERIQUE		2
#define TYPE_EVT_INCONNU		3

//Variable : S_STRUCT_DESCRIPTION_EVT
//Champs : u8_groupe
enum LISTE_DES_GROUPES_DES_EVTS
{
	GROUPE_AL_SYSTEME	= 0,
#if TEST_DEBUG_EVENT
	GROUPE_AL_DEBUG,
#endif
	GROUPE_AL_NOT_USED,
	NB_MAX_GROUPES
};

//Variable : S_STRUCT_DESCRIPTION_EVT
//Champs : u8_valeur_associee_action
#define  V_JDB			0x01	//bit1
#define  V_TRAP			0x02	//bit2
#define  V_NO_ACTION	0x00

//-------------------------------------
//LISTE DES EVENEMENTS
//-------------------------------------
enum LISTE_DES_EVENEMENTS
{
	EVT000_AL_SYNTHESE_1 = 0,
	EVT001_DEFAUT_EQUIPEMENT,
	EVT002_AL_TEMPERATURE,
	EVT003_AL_ETHERNET_LAN_1,
	EVT004_AL_ETHERNET_LAN_2,
	EVT005_AL_NIVEAU_RECU,
	EVT006_STATION_NON_CONNECTEE,
	EVT007_PROBLEME_CONFIGURATION,
	EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE,
	EVT009_RETOUR_SUR_SSID_PRIMAIRE,
	EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE,
	EVT011_RADAR_DETECTE_SUR_CANAL,
	EVT012_BASCULEMENT_VERS_CANAL,
	EVT013_CONNEXION_STATION,
	EVT014_DECONNEXION_STATION,
	EVT015_CONNEXION_ACCESS_POINT,
	EVT016_DECONNEXION_ACCESS_POINT,
	EVT017_RESERVE,
	EVT018_RESERVE,
	EVT019_RESERVE,
	EVT020_RESERVE,
	EVT021_RESERVE,
	EVT022_RESERVE,
	EVT023_RESERVE,
	EVT024_RESERVE,
	EVT025_RESERVE,
	EVT026_RESERVE,
	EVT027_RESERVE,
	EVT028_RESERVE,
	EVT029_RESERVE,
	EVT030_RESERVE,
	EVT031_RESERVE,
	EVT032_RESERVE,
	EVT033_RESERVE,
	EVT034_RESERVE,
	EVT035_RESERVE,
	EVT036_RESERVE,
	EVT037_RESERVE,
	EVT038_RESERVE,
	EVT039_RESERVE,
	EVT040_RESERVE,
	EVT041_RESERVE,
	EVT042_RESERVE,
	EVT043_RESERVE,
	EVT044_RESERVE,
	EVT045_RESERVE,
	EVT046_RESERVE,
	EVT047_RESERVE,
	EVT048_RESERVE,
	EVT049_RESERVE,
	EVT050_RESERVE,
	EVT051_RESERVE,
	EVT052_RESERVE,
	EVT053_RESERVE,
	EVT054_RESERVE,
	EVT055_RESERVE,
	EVT056_RESERVE,
	EVT057_RESERVE,
	EVT058_RESERVE,
	EVT059_RESERVE,
	EVT060_RESERVE,
	EVT061_RESERVE,
	EVT062_RESERVE,
	EVT063_RESERVE,
	EVT064_RESERVE,
	EVT065_RESERVE,
	EVT066_RESERVE,
	EVT067_RESERVE,
	EVT068_RESERVE,
	EVT069_RESERVE,
	EVT070_RESERVE,
	EVT071_RESERVE,
	EVT072_RESERVE,
	EVT073_RESERVE,
	EVT074_RESERVE,
	EVT075_RESERVE,
	EVT076_RESERVE,
	EVT077_RESERVE,
	EVT078_RESERVE,
	EVT079_RESERVE,
	EVT080_RESERVE,
	EVT081_RESERVE,
	EVT082_RESERVE,
	EVT083_RESERVE,
	EVT084_RESERVE,
	EVT085_RESERVE,
	EVT086_RESERVE,
	EVT087_RESERVE,
	EVT088_RESERVE,
	EVT089_RESERVE,
	EVT090_RESERVE,
	EVT091_RESERVE,
	EVT092_RESERVE,
	EVT093_RESERVE,
	EVT094_RESERVE,
	EVT095_RESERVE,
	EVT096_RESERVE,
	EVT097_RESERVE,
	EVT098_RESERVE,
	EVT099_RESERVE,
	EVT100_RESERVE,
	EVT101_RESERVE,
	EVT102_RESERVE,
	EVT103_RESERVE,
	EVT104_RESERVE,
	EVT105_RESERVE,
	EVT106_RESERVE,
	EVT107_RESERVE,
	EVT108_RESERVE,
	EVT109_RESERVE,
	EVT110_JOURNAL_BORD_EFFACE,
	EVT111_INF_RAZ_ALARMES_MEMO,
	EVT112_EVOLUTION_CONFIGURATION,
	EVT113_ORDRE_RESET_TELECOMMANDE,
	EVT114_RESERVE,
	EVT115_RESERVE,
	EVT116_RESERVE,
	EVT117_RESERVE,
	EVT118_RESERVE,
	EVT119_RESERVE,
	EVT120_RESERVE,
	EVT121_RESERVE,
	EVT122_RESERVE,
	EVT123_RESERVE,
	EVT124_RESERVE,
	EVT125_RESERVE,
	EVT126_RESERVE,
	EVT127_RESERVE,
	EVT128_RESERVE,
	EVT129_RESERVE,
	EVT130_RESERVE,
	EVT131_RESERVE,
	EVT132_RESERVE,
	EVT133_RESERVE,
	EVT134_RESERVE,
	EVT135_RESERVE,
	EVT136_RESERVE,
	EVT137_RESERVE,
	EVT138_RESERVE,
	EVT139_RESERVE,
	EVT140_RESERVE,
	EVT141_RESERVE,
	EVT142_RESERVE,
	EVT143_RESERVE,
	EVT144_RESERVE,
	EVT145_RESERVE,
	EVT146_RESERVE,
	EVT147_RESERVE,
	EVT148_RESERVE,
	EVT149_RESERVE,
	EVT150_RESERVE,
	EVT151_RESERVE,
	EVT152_RESERVE,
	EVT153_RESERVE,
	EVT154_RESERVE,
	EVT155_RESERVE,
	EVT156_RESERVE,
	EVT157_RESERVE,
	EVT158_RESERVE,
	EVT159_RESERVE,
	EVT160_RESERVE,
	EVT161_RESERVE,
	EVT162_RESERVE,
	EVT163_RESERVE,
	EVT164_RESERVE,
	EVT165_RESERVE,
	EVT166_RESERVE,
	EVT167_RESERVE,
	EVT168_RESERVE,
	EVT169_RESERVE,
	EVT170_RESERVE,
	EVT171_RESERVE,
	EVT172_RESERVE,
	EVT173_RESERVE,
	EVT174_RESERVE,
	EVT175_INF_EQUIPEMENT_ON,
	EVT176_INF_SIGNE_DE_VIE,
	EVT177_RESERVE,
	EVT178_RESERVE,
	EVT179_RESERVE,
	NB_MAX_EVENEMENTS,
	EVT255_NON_VALIDE = 0xFF
};

//Autres défines pour gestion des évènements
#define US_INDICE_NON_TROUVE	0xFFFF
#define	NUM_EVT_INTERDIT		0
#define IDX_MEMOIRE_DISPO	0xFFFF


/*______III - INCLUDES - DIRECTIVES_______________________________________*/

/*______IV - PROTOTYPES DEFINIS___________________________________________*/

/*______V - DEFINITION DE TYPES___________________________________________*/


/*______VI - CONSTANTES ET VARIABLES______________________________________*/

/*________VII - PROCEDURES D'INITIALISATION ______________________________*/
