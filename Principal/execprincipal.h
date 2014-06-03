/*========================================================================*/
/* NOM DU FICHIER  : execprincipal.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Processus principal de l'application			      */
/* Projet          : WRM100	                                              */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE008 28/01/2010 CM
// - Gestion fichier configuration debug.ini
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECPRINCIPAL
#define _EXECPRINCIPAL_EXT
#else
#define _EXECPRINCIPAL_EXT	extern
#endif

//Liste des modes du processus execprincipal
enum LISTE_DES_MODES_EXECPRINCIPAL
{
	MODE_EXECPRINCIPAL_AUCUN =0	,
	MODE_EXECPRINCIPAL_NORADIO,
	NB_MAX_MODES_EXECPRINCIPAL
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SetSignalNewConfig
// Entrees		: <loc_pt_newcfg< : pointeur info nouvelle configuration
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Positionne le signal de la nouvelle configuration
//=====================================================================================
void SetSignalNewConfig(T_STRUCT_OF_FILE_NEWCFG_INI *loc_pt_info_newcfg);

//=====================================================================================
// Fonction		: SignalNewConfig_AllProcess
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Signale nouvelle configuration aux autres processus
//=====================================================================================
void SignalNewConfig_AllProcess(void);

//=====================================================================================
// Fonction		: Dialog_CipPrincipalToMonitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 08/03/2010 -
// Description	: Dialogue vers le processus 'monitor'
//=====================================================================================
void Dialog_CipPrincipalToMonitor(void);

//=====================================================================================
// Fonction		: u16GetCountryID
// Entrees		: <loc_ps_environnement< : pointeur sur la base de données à initialiser
// Sortie		: <loc_u16_countryID> : valeur du countryID
// Auteur		: CM - 11/10/2010 -
// Description	: Récupère countryID
//=====================================================================================
u16sod u16GetCountryID(S_STRUCT_ENVIRONNEMENT *loc_ps_environnement);

//=====================================================================================
// Fonction		: ControleNewCountryID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: controle si nouveau countryID
//=====================================================================================
void ControleNewCountryID(void);

//=====================================================================================
// Fonction		: InitModule_ExecPrincipal
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de ExecPrincipal
//=====================================================================================
void InitModule_ExecPrincipal(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_EXECPRINCIPAL_EXT	S_STRUCT_HTTP_GLOBAL s_http_process_prncpl;
_EXECPRINCIPAL_EXT	S_STRUCT_CONFIGURATION s_config_process_prncpl;
_EXECPRINCIPAL_EXT	S_STRUCT_EXPLOITATION s_exploit_process_prncpl;
_EXECPRINCIPAL_EXT	S_STRUCT_DEBUG_GLOBAL s_debug_global_process_prncpl;
_EXECPRINCIPAL_EXT	S_STRUCT_EXPLOIT_EVENTS s_exp_events_process_prncpl;
_EXECPRINCIPAL_EXT	S_STRUCT_ENVIRONNEMENT s_environmt_process_prncpl;
_EXECPRINCIPAL_EXT	S_STRUCT_LIST_FREQ s_list_freq_process_prncpl;

_EXECPRINCIPAL_EXT	S_STRUCT_CIP_MONITOR s_cip_monitor_courant;
_EXECPRINCIPAL_EXT	S_STRUCT_CIP_SNMPD s_cip_snmpd_courant;
_EXECPRINCIPAL_EXT	T_STRUCT_OF_FILE_NEWCFG_INI t_principal_newcfgini;
_EXECPRINCIPAL_EXT	S_STRUCT_CIP_JDB s_cip_jdb_courant;
_EXECPRINCIPAL_EXT	S_STRUCT_STATUTJDB s_statutjdb_courant;

//pour la gestion de l'alarme probleme de configuration : passage par défaut
_EXECPRINCIPAL_EXT	u8sod	pu8_signal_passage_config_par_defaut[NB_MAX_IDXCONFIG];


_EXECPRINCIPAL_EXT	u8sod u8_mode_execPrincipal;

//Flag pour indiquer que les drivers wifi chargés sont issus du projet madwifi (d'origine), et non du sous traitant
_EXECPRINCIPAL_EXT	u8sod u8_debug_madwifi_on;

//CountryID debug
_EXECPRINCIPAL_EXT	u16sod u16_countryID_debug;

_EXECPRINCIPAL_EXT u8sod u8_ordre_installRadioModem;
