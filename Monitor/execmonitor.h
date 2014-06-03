/*========================================================================*/
/* NOM DU FICHIER  : execmonitor.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Processus monitor de l'application					  */
/* Projet          : WRM100	                                              */
/* Indice          : BE051                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE051 13/12/2010 CM
// - Incohérence horodatage de l'action suppression jdb et de l'évènement
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECMONITOR
#define _EXECMONITOR_EXT
#else
#define _EXECMONITOR_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: GestionFinExploitation
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/12/2010 -
// Description	: Gestion fin exploitation
//=====================================================================================
void GestionFinExploitation(void);

//=====================================================================================
// Fonction		: RazExploitEvents_FonctionConfig
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
//				: <loc_ps_config<: pointeur sur configuration equipement
// Sortie		: rien
// Auteur		: CM - 07/07/2010 -
// Description	: Remise à zero de l'exploitation des évènements en fonction de la config
//=====================================================================================
void RazExploitEvents_FonctionConfig(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events, S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: LectureConfigurationEquipement_PourProcessus
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Lecture de la configuration pour le processus
//=====================================================================================
void LectureConfigurationEquipement_PourProcessus(void);

//=====================================================================================
// Fonction		: u8GetAutoStatutIP_Interface
// Entrees		: <loc_u8_interface>: sur l'interface sélectionnée
// Sortie		: <loc_u8_statutIp>: statut ip
// Auteur		: CM - 15/02/2010 -
// Description	: Retourne statut de l'interface (auto)
//=====================================================================================
u8sod u8GetAutoStatutIP_Interface(u8sod loc_u8_interface);

//=====================================================================================
// Fonction		: InitModule_ExecMonitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/03/2010 -
// Description	: Initialisation du module de ExecMonitor
//=====================================================================================
void InitModule_ExecMonitor(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//Configuration de l'équipement pour le processus Monitor
_EXECMONITOR_EXT S_STRUCT_CONFIGURATION s_config_process_mntr;

//Exploitation de l'équipement pour le processus Monitor
_EXECMONITOR_EXT S_STRUCT_EXPLOITATION s_exploit_process_mntr;

//Exploitation des évènements de l'équipement pour le processus Monitor
_EXECMONITOR_EXT S_STRUCT_EXPLOIT_EVENTS s_exp_events_process_mntr;


//Pointeur courant sur information système
_EXECMONITOR_EXT S_STRUCT_EVENTSYSTEM	*pt_process_eventsystem;

//Données du processus monitor echangées par les autres processus
_EXECMONITOR_EXT S_STRUCT_CIP_MONITOR s_cip_monitor_courant;

//Flag pour indiquer que les drivers wifi chargés sont issus du projet madwifi (d'origine), et non du sous traitant
_EXECMONITOR_EXT	u8sod u8_debug_madwifi_on;

//d:BE062.0 JP : Gestion des leds de la carte CPU
//Flag pour memoriser l'etat de la led3, utile pour la faire clignoter...
_EXECMONITOR_EXT u8sod u8_monitor_etat_led3;
//f:BE062.0 JP : Gestion des leds de la carte CPU
