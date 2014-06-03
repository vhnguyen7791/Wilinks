/*========================================================================*/
/* NOM DU FICHIER  : td_debug.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 28/01/2010											  */
/* Libelle         : Base de données: Type def debug					  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - CREATION
//BE051 13/12/2010 CM
// - Ajout debug pour désactiver watchdog_wifi
//BE055 17/01/2011 CM
// - Ajout configuration Country ID pour le client
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_DEBUG_GLOBAL
//Champs : u8_syslogd_level
//Champs : u8_klogd_level
#define LOGLEVEL_DBG_DISABLED	0xFF
#define NB_MAX_LOGLEVEL			(LOG_DEBUG+1)

//Variable : S_STRUCT_DEBUG_GLOBAL
//Champs : u8_mode_test_final
#define MODE_AP_TF 0
#define MODE_STA_TF 0xFF

//Variable : S_STRUCT_DEBUG_GLOBAL
//Champs : u8_cfg_test_final
#define ANT1_2_4G	0
#define ANT1_5G		1
#define ANT2_2_4G	2
#define ANT2_5G		3

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//******************************************
/* structure debug de l'équipement		   */
//******************************************
typedef struct 
{
	//Debug concernant le system log
	u8sod	u8_syslogd_level;	//Niveau de syslogd (pour activer: valeur de 0 à 7 cf syslog.h)
	u8sod	u8_klogd_level;		//Niveau de klogd (pour activer: valeur de 0 à 7 cf syslog.h)

	//Debug concernant hostapd
	u8sod	u8_dbg_hostapd;			//Activation du debug hostapd (FALSE ou TRUE)
	//Debug concernant wpa_supplicant
	u8sod	u8_dbg_wpa_supplicant;	//Activation du debug wpa_supplicant (FALSE ou TRUE)
	//Debug concernant iptables
	u8sod	u8_dbg_iptables;	//Activation du debug iptables (FALSE ou TRUE)
	//Debug concernant watchdog_wifi
	u8sod	u8_dbg_stop_watchdog_wifi;	//Activation du debug watchdog_wifi (FALSE ou TRUE)

	//Debug concernant countryID
	u8sod	u8_dbg_countryID;	//Activation du debug countryID (FALSE ou TRUE): permet de configurer un autre country id

	//Debug : mode de test final
	u8sod	u8_mode_test_final;
	//Debug : Config du test final
	u8sod	u8_cfg_test_final;
	//Debug : etat de la connexion (pour page test final)
	u8sod	u8_etat_cnx_test_final;
	
}S_STRUCT_DEBUG_GLOBAL;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


