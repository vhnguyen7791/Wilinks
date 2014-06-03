/*========================================================================*/
/* NOM DU FICHIER  : td_bddsystemfile.h				                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: Type definition systeme de fichiers */
/* Projet          : WRM100                                               */
/* Indice          : BE064                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE006 20/01/2010 CM
// - Modification gestion couche haute des fichiers
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE013 26/02/2010 CM
// - Modification chemins des bdd (sous /tmp)
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE018 15/03/2010 CM
// - Correction risque de corruption du journal de bord sauvé en FLASH lors de l'écriture d'un évènement
//	en effet, on va sécurisé l'écriture dans le fichier jdbpart en doublant l'écriture dans un autre fichier (jdbcur.log)
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE023 01/04/2010 CM
// - Ajout gestion premier démarrage du processus principal
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
//BE027 28/04/2010 CM
// - Modification nom /mnt/nand-config --> /mnt/flash-config
// - Modification nom /mnt/nand-jdb --> /mnt/flash-jdb
//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
//BE036 02/07/2010 CM
// - Modification des chemins de fichiers qui se trouvent dans /var => /tmp
// - Ajout gestion des logins
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
//BE042 07/10/2010 CM
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
// - Ajout gestion liste des fréquences réglementaires
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE054 11/01/2011 CM
// - Suppression du fichier de configuration advwf
// - Ajout gestion mode monitor
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout fonction impose config au démarrage (pour chaque bdd de config)
// - Correction bug au démarrage de l'équipement accès HTTP à des données pas encore initialisées
//BE061 10/05/2011
// - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
// - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//BE064.0 25/11/2011 (CM)
// - Correction bug de la configuration par sFTP (lors changement countryId)
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define MAX_LG_NOM_FICHIER		200


//***************************************
//LISTE DES FICHIERS ASSOCIÉS À LA CONFIGURATION
//***************************************
enum LISTE_ID_FILE_CONFIG
{
	ID_FILE_CFG_NULL = 0,
	
	ID_FILE_FLASH_CFG_BASE_ADMIN,
	ID_FILE_FLASH_CFG_BACKUP_ADMIN,
	ID_FILE_BDD_ADMIN_CFG,
	
	ID_FILE_FLASH_CFG_BASE_CONSTRUCTEUR,
	ID_FILE_FLASH_CFG_BACKUP_CONSTRUCTEUR,
	ID_FILE_BDD_CONSTRUCTEUR_CFG,

	ID_FILE_FLASH_CFG_BASE_SNMP,
	ID_FILE_FLASH_CFG_BACKUP_SNMP,
	ID_FILE_BDD_SNMP_CFG,

	ID_FILE_FLASH_CFG_BASE_GENE,
	ID_FILE_FLASH_CFG_BACKUP_GENE,
	ID_FILE_BDD_GENE_CFG,

	ID_FILE_FLASH_CFG_BASE_WIFI,
	ID_FILE_FLASH_CFG_BACKUP_WIFI,
	ID_FILE_BDD_WIFI_CFG,

	ID_FILE_FLASH_CFG_BASE_ROUTING,
	ID_FILE_FLASH_CFG_BACKUP_ROUTING,
	ID_FILE_BDD_ROUTING_CFG,

	ID_FILE_FLASH_CFG_BASE_NAT,
	ID_FILE_FLASH_CFG_BACKUP_NAT,
	ID_FILE_BDD_NAT_CFG,

	ID_FILE_FLASH_CFG_BASE_MULTICAST,
	ID_FILE_FLASH_CFG_BACKUP_MULTICAST,
	ID_FILE_BDD_MULTICAST_CFG,
	
	ID_FILE_FLASH_CFG_BASE_TABEVT,
	ID_FILE_FLASH_CFG_BACKUP_TABEVT,
	ID_FILE_BDD_TABEVT_CFG,

	ID_FILE_FLASH_CFG_BASE_HANDOFF,
	ID_FILE_FLASH_CFG_BACKUP_HANDOFF,
	ID_FILE_BDD_HANDOFF_CFG,
	
	NB_MAX_ID_FILES_CONFIG
};

//***************************************
//LISTE DES FICHIERS ASSOCIÉS À LA CONFIGURATION
//***************************************
enum LISTE_ID_FILE_EXPLOIT
{
	ID_FILE_EXP_NULL = 0,
	ID_FILE_BDD_GENERAL_EXP,
	ID_FILE_BDD_STATION_EXP,
	ID_FILE_BDD_ACCESSPOINT_EXP,
	ID_FILE_BDD_DHCP_EXP,
	NB_MAX_ID_FILES_EXPLOIT	
};

//***************************************
//Liste des PATHS
//***************************************
#if DEBUG_PC_LINUX
#define PATH_DIR_ROOT "/home/cm/workspace/FileSystem/"
#else
#define PATH_DIR_ROOT "/"
#endif

#define PATH_DIR__FLASH_CONFIG			PATH_DIR_ROOT  "mnt/flash-config/"
#define PATH_DIR__FLASH_CONFIG_BASE		PATH_DIR__FLASH_CONFIG "base/"
#define PATH_DIR__FLASH_CONFIG_BACKUP	PATH_DIR__FLASH_CONFIG "backup/"
#define PATH_DIR__FLASH_CONFIG_ENV		PATH_DIR__FLASH_CONFIG "env/"
#define PATH_DIR__FLASH_CONFIG_CERTIFICATS			PATH_DIR__FLASH_CONFIG	"certificats/"
#define PATH_DIR__FLASH_JDB			PATH_DIR_ROOT  "mnt/flash-jdb/"
#define PATH_DIR_TMP		PATH_DIR_ROOT	"tmp/"
#define PATH_DIR__BDD_CONFIG		PATH_DIR_TMP	"bdd_config/"
#define PATH_DIR__BDD_EXPLOIT		PATH_DIR_TMP	"bdd_exploit/"
#define PATH_DIR__BDD_MISC			PATH_DIR_TMP	"bdd_misc/"
#define PATH_DIR__BDD_EVT			PATH_DIR_TMP	"bdd_evt/"
#define PATH_DIR__BDD_BOOT			PATH_DIR_TMP	"bdd_boot/"
#define PATH_DIR__BDD_TIME			PATH_DIR_TMP	"bdd_time/"
#define PATH_DIR_VAR		PATH_DIR_ROOT	"var/"
#define PATH_DIR_ETC		PATH_DIR_ROOT	"etc/"
#define PATH_DIR_PROC		PATH_DIR_ROOT	"proc/"
//#define PATH_DIR_UPDATE		PATH_DIR_ROOT	"update/"
#define PATH_DIR_DEV		PATH_DIR_ROOT	"dev/"
#define PATH_DIR_USR		PATH_DIR_ROOT	"usr/"
#define PATH_DIR_HOME		PATH_DIR_ROOT	"home/"
#define PATH_DIR_USB		"/USB/"
#define PATH_DIR_LIB		PATH_DIR_ROOT	"lib/"
#define PATH_DIR_RW			PATH_DIR_ROOT	"rw/"
//d: Modif PCR le 14/10/2013 Intégration Modifs GT
//#define PATH_DIR_UPDATE		PATH_DIR_VAR	"update/"
#define PATH_DIR_UPDATE		PATH_DIR_TMP	"/var/update/"
//f: Modif PCR le 14/10/2013 Intégration Modifs GT
#define PATH_DIR__TMP_CERTIFICATS			PATH_DIR_TMP	"certificats/"
#define PATH_DIR__ETC_CERTIFICATS			PATH_DIR_ETC	"certificats/"
#define PATH_DIR__VAR_CERTIFICATS			PATH_DIR_VAR	"CERTIFICATS/"

#define PATH_DIR_VAR_CONF		PATH_DIR_VAR "conf/"

//Nombre de certificats max
#define NB_MAX_CERTIFICATS			10

//Liste des noms de fichiers (sans extension)
#define NFILE_ADMIN			"admin"
#define NFILE_CONSTRUCTEUR	"constructeur"
#define NFILE_SNMP			"snmp"
#define NFILE_NEWCFG		"newcfg"
#define NFILE_GENERAL		"general"
#define NFILE_STATION		"station"
#define NFILE_WIFI			"wifi"
#define	NFILE_ROUTING		"routing"
#define NFILE_ACCESS_POINT	"accesspoint"
#define NFILE_DHCP			"dhcp"
#define NFILE_NAT			"nat"
#define NFILE_MULTICAST		"multicast"
#define NFILE_TABEVT		"tabevt"
#define NFILE_JDBPART		"jdbpart"
#define NFILE_HANDOFF		"handoff"
//d:BE063.0 06/10/2011
#define NFILE_GLOBALE		"config_wrm100"
//f:BE063.0 06/10/2011

//Liste des extensions
#define EXT_INI		".ini"
#define EXT_CFG		".cfg"
#define EXT_BACKUP  ".backup"
#define EXT_EXP		".exp"
#define EXT_GIF		".gif"
#define EXT_LOG		".log"
#define EXT_STA		".sta"


//**************************************
//Liste des fichiers
//**************************************



//Définition du fichier logo client
#define NFILE_LOGO_CLIENT	"logo_client"
#define	FICHIER_LOGO_CLIENT		PATH_DIR_VAR	"boa/" NFILE_LOGO_CLIENT EXT_GIF
//Définition du fichier /var/reset.now
#define	FICHIER_RESET_NOW		PATH_DIR_VAR	"reset.now"

//Définition du fichier /proc/net/route
#define TAILLE_MAX_LIGNE_PROCNETROUTE   256
#define FICHIER_PROC_NET_ROUTE	PATH_DIR_PROC	"net/route"
//Définition des fichiers sous /proc/sys/dev/wifi0
#define PATH_DIR__SYS_DEV_WIFI0 PATH_DIR_PROC "sys/dev/wifi0/"
#define FICHIER__SYS_DEV_WIFI0_DIVERSITY PATH_DIR__SYS_DEV_WIFI0 "diversity"
#define FICHIER__SYS_DEV_WIFI0_RXANTENNA PATH_DIR__SYS_DEV_WIFI0 "rxantenna"
#define FICHIER__SYS_DEV_WIFI0_TXANTENNA PATH_DIR__SYS_DEV_WIFI0 "txantenna"
#define FICHIER__SYS_DEV_WIFI0_ACKTIMEOUT PATH_DIR__SYS_DEV_WIFI0 "acktimeout"

//Définition des fichiers sous /proc/sys/net/ipv4
#define PATH_DIR__SYS_NET_IPV4 PATH_DIR_PROC "sys/net/ipv4/"
#define FICHIER__SYS_NET_IPV4_IP_FORWARD PATH_DIR__SYS_NET_IPV4 "ip_forward"

//Définition du fichier d'exploitation du serveur DHCP
#define FICHIER_UDHCPD_LEASES PATH_DIR_VAR "lib/misc/udhcpd.leases"

//Fichier pour récupérer valeur du PID du processus "udhcpc"
#define FICHIER_VAR_UDHCPC_PID		PATH_DIR_VAR "run/udhcpc.pid"


//Définition du fichier /var/log/actia.dbg
#define	TAILLE_MAX_MESSAGE_DEBUG	500
#define MAX_SIZE_F_ACTIA_DEBUG		20000	//20ko
#define FILE_ACTIA_DEBUG PATH_DIR_VAR "log/actia.dbg"

//Définition du fichier /var/log/jdb.log
#define FICHIER_JDB_EQUIPMENT PATH_DIR_VAR "log/jdb.log"

//Définition du fichier /tmp/bdd_boot/modeboot.ini
#define FILE_MODEBOOT_INIT PATH_DIR__BDD_BOOT "modeboot.ini"
//Définition du fichier /tmp/bdd_boot/uboot.ini
#define FILE_UBOOT_INIT PATH_DIR__BDD_BOOT "uboot.ini"

//Définition du fichier /tmp/bdd_boot/infosystemX.ini
#define FILE_INFOSYSTEM_X PATH_DIR__BDD_BOOT "infosystemX.ini"
#define FILE_INFOSYSTEM_1 PATH_DIR__BDD_BOOT "infosystem1.ini"
#define FILE_INFOSYSTEM_2 PATH_DIR__BDD_BOOT "infosystem2.ini"

//Définition des fichiers sous /update
//#define FICHIER_UPDATE_CPU_BIN PATH_DIR_UPDATE "cpu.bin" //Redefined to adapt for Wilinks
#define FICHIER_UPDATE_CPU_BIN PATH_DIR_UPDATE "initramfs_AP.bin"
#define FICHIER_UPDATE_CPU_BIN_GZ PATH_DIR_UPDATE "initramfs_AP.bin.gz"
#define FICHIER_UPDATE_TMPFILE_GZ PATH_DIR_UPDATE "tmpfile.gz"
#define FICHIER_UPDATE_TESTGZ PATH_DIR_UPDATE "testgz.ini"

//Définition des devices
#define DEVICE_MTD_NOR_INFOSYSTEM1 PATH_DIR_DEV "infosystem1"
#define DEVICE_MTD_NOR_INFOSYSTEM2 PATH_DIR_DEV "infosystem2"
#define DEVICE_MTD_NAND_APP1	PATH_DIR_DEV "app1"
#define DEVICE_MTD_NAND_APP2	PATH_DIR_DEV "app2"
#define DEVICE_MTD_FLASH_CONFIG	PATH_DIR_DEV "config"
#define DEVICE_MTD_FLASH_JDB	PATH_DIR_DEV "jdb"
#define DEVICE_MTD_NAND_USER	PATH_DIR_DEV "user"
#define DEVICE_MTD_NOR_TIMESAVE1 PATH_DIR_DEV "timesave1"
#define DEVICE_MTD_NOR_TIMESAVE2 PATH_DIR_DEV "timesave2"

//Définition des fichiers sous /var/run
//Fichier pour récupérer valeur du PID du processus "hostapd"
#define FICHIER_VAR_HOSTAPD_PID		PATH_DIR_VAR "run/hostapd.pid"
//Fichier pour récupérer valeur du PID du processus "wpa_supplicant"
#define FICHIER_VAR_WPA_SUPPLICANT_PID		PATH_DIR_VAR "run/wpa_supplicant.pid"
//Fichier pour récupérer valeur du PID du processus "wpa_supplicant"
#define FICHIER_VAR_NTPDATE_PID		PATH_DIR_VAR "run/ntpdate.pid"

//Définition du fichier de debug
//Configuration de debug
#define FICHIER_BDD__DEBUG_INI	PATH_DIR__BDD_MISC "debug.ini"
#define FICHIER_MNT_FLASH_CONFIG__DEBUG_SAV	PATH_DIR__FLASH_CONFIG "debug.sav"

//Fichier pour indiquer que les modules chargés sont ceux du madwifi
#define FILE_DEBUG_MADWIFI_ON	PATH_DIR_TMP	"madwifi.on"

//d: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//Forcer configuration par défaut (au moment de la restauration des fichiers de configuration
#define FICHIER_SETCONFIGDEFAULT PATH_DIR_TMP  "setconfigdefault_"
//f: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

//d: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//Signalisation nouveau equipement
#define FICHIER_NEW_EQUIPMENT PATH_DIR_TMP  "new_equipment"
//f: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

//Exploitation Wifi ACCESS POINT
#define FICHIER_HOSTAPD_DUMP	PATH_DIR__BDD_EXPLOIT	"hostapd.dump"
//Fichier d'information de la table NAT
#define TAILLE_MAX_LIGNE_TABLE_FILTER   256
#define FICHIER_TABLE_NAT_ACTIVE	PATH_DIR__BDD_MISC "table_nat.info"
//Fichier d'information de la table FILTER
#define FICHIER_TABLE_FILTER_ACTIVE	PATH_DIR__BDD_MISC "table_filter.info"
//Fichier d'information de la table MANGLE
#define TAILLE_MAX_LIGNE_TABLE_MANGLE	512
#define FICHIER_TABLE_MANGLE_ACTIVE	PATH_DIR__BDD_MISC "table_mangle.info"
//Fichier d'information des règles ip
#define TAILLE_MAX_LIGNE_FICHIER_IP_RULE_SHOW	100
#define FICHIER_IP_RULE_SHOW	PATH_DIR__BDD_MISC "ip_rule.info"
//Fichier d'information des routes ip politique
#define TAILLE_MAX_LIGNE_FICHIER_IP_ROUTE_SHOW	100
#define FICHIER_IP_ROUTE_SHOW	PATH_DIR__BDD_MISC "ip_route.info"

//Fichier courant JDB
#define FILE_FLASH_JDBCUR	PATH_DIR__FLASH_JDB "jdbcur.log"

//Fichier premier démarrage de principal
#define FILE_FIRSTSTART_ON	PATH_DIR_TMP	"firststart.on"

//Fichier initialisation de la bdd (crée dans S22principal)
#define FILE_INITBDD_ON	PATH_DIR_TMP	"initbdd.on"

//Fichier pour signaler nouveau countryID
#define FICHIER_NEW_COUNTRYID_ORDER PATH_DIR__BDD_CONFIG "new_countryid.order"

//Fichier pour signaler une configuration en cours
#define FICHIER_CONFIG_INPROGRESS PATH_DIR__BDD_CONFIG "config.inprogress"

//copie define dans ntpdate.c
#define FICHIER_STATUS_NTPDATE_ACTIA	"/etc/ntp/ntpdate_actia.status"
//Gestion exploitation sntp
#define FICHIER_SNTP_INFO PATH_DIR__BDD_EXPLOIT "sntp.info"
#define FICHIER_SNTP_INFO_LINE PATH_DIR__BDD_EXPLOIT "sntp.info.line"
//Gestion exploitation ntp
#define FICHIER_NTP_INFO_LINE	PATH_DIR__BDD_EXPLOIT "ntp.info.line"
#define FICHIER_NTP_INFO PATH_DIR__BDD_EXPLOIT "ntp.info"

//Script de redirection de tcpdump sur syslog
#define SCRIPT_SYSLG_TCPDUMP PATH_DIR_ETC "syslg_tcpdump.sh"

//***************************************
//Liste des configurations
//***************************************
enum LISTE_DES_CONFIGURATIONS
{
	IDXCFG_ADMIN,
	IDXCFG_CONSTRUCTEUR,
	IDXCFG_SNMP,
	IDXCFG_GENERAL,
	IDXCFG_WIFI,
	IDXCFG_ROUTING,
	IDXCFG_NAT,
	IDXCFG_MULTICAST,
	IDXCFG_TABEVT,
	IDXCFG_HANDOFF,
	NB_MAX_IDXCONFIG
};


//Variable : T_STRUCT_DEFINITION_FILE_FS
//Champs : u8_type
enum LISTE_TYPE_FILE_FS
{
	DEFFILE_TYPE_AUCUN = 0,
	DEFFILE_TYPE_CONFIG,
	DEFFILE_TYPE_SYSTEM,
	DEFFILE_TYPE_EXPLOIT,
	NB_MAX_DEFFILE_TYPES
};


//Permissions des fichiers
#define CHMOD_FILE_ROOT_751 (S_IRWXU|S_IRGRP|S_IWGRP|S_IXOTH)
#define CHMOD_FILE_ROOT_755 (S_IRWXU|S_IRGRP|S_IWGRP|S_IROTH|S_IXOTH)


/*_____III - DEFINITIONS DE TYPES_________________________________________*/


//****************************************
//Définition d'un fichier dans le systeme de fichiers
//****************************************
typedef struct 
{
	s8sod					*ps8_path_file;		//Chemin du fichier dans le systeme de fichiers
	u8sod					u8_type;			//Type de fichier (config, System, ...)
	u8sod					u8_avec_checksum;	//Fichier sécurisé avec checksum (TRUE: activé, FALSE: sinon)
	T_STRUCT_FILE_FIELD		*pt_contenu;		//Pointeur sur le contenu
	
}T_STRUCT_DEFINITION_FILE_FS;


//****************************************
//Description d'une configuration
//****************************************
typedef struct 
{
	s8sod		*ps8_cfgnom;	  //nom de la configuration
	u16sod		u16_idx_base; //index du fichier de configuration de base (dans mémoire non volatile)
	u16sod		u16_idx_backup; //index du fichier de configuration de backup (dans mémoire non volatile)
	u16sod		u16_idx_bdd; //index du fichier de configuration dans la RAM DISK (bdd)
	u8sod		(*u8TestConfig)(S_STRUCT_CONFIGURATION*); //Fonction test de cohérence de la configuration (sur les champs définis dans le fichier)
	void		(*CopyConfig)(S_STRUCT_CONFIGURATION*,S_STRUCT_CONFIGURATION*); //Fonction copie de la configuration dst=src  de type CopyConfig(SRC,DST) 
	u8sod		(*u8FillConfig)(S_STRUCT_CONFIGURATION*); //Fonction de lecture de la configuration dans le fichier (RAM)
	u8sod		(*u8EditConfig)(S_STRUCT_CONFIGURATION*); //Fonction d'écriture de la configuration dans le fichier (RAM)
	u8sod		(*u8DiffConfig)(S_STRUCT_CONFIGURATION*,S_STRUCT_CONFIGURATION*); //Fonction de comparaison de la configuration
	u8sod		(*u8ImposeInitConfig)(S_STRUCT_CONFIGURATION*); //Fonction qui impose configuration (lors de la phase de restauration de la configuration)
}T_STRUCT_DESCRIPTION_CONFIGURATION;


//****************************************
//Définition de la gestion de l'évolution de la configuration
//****************************************
typedef struct 
{
	u8sod		pu8_flag[NB_MAX_IDXCONFIG]; //indique une susceptible évolution de la configuration pour le fichier défini par son index
//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
	u8sod		u8_change_cfg_FTP; //indique une configuration par FTP
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
}T_STRUCT_OF_FILE_NEWCFG_INI;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

