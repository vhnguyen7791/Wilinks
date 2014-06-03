/*========================================================================*/
/* NOM DU FICHIER  : td_cip_monitor.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 03/03/2010											  */
/* Libelle         : Base de données: Communic. Inter Process (monitor)   */
/* Projet          : WRM100                                               */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Probleme horodatage de l'évènement JDB lors d'un RAZ général
//BE058 21/01/2011 CM
// - Synchronisation configuration / exploitation
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_CIP_MONITOR
//Champs : pu8_flag_errorconfig[NB_MAX_ERRORCONFIG]
enum LISTE_ERROR_CONFIG
{
	ERRORCONFIG_PASSAGE_PAR_DEFAUT = 0,
	ERRORCONFIG_INSTALLATION,
	NB_MAX_ERRORCONFIG
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//définition des informations à échanger avec le processus monitor
typedef struct 
{
	u8sod	pu8_flag_newcfg[NB_MAX_IDXCONFIG];		//Signale une susceptible évolution de la configuration pour le fichier défini par son index

	u8sod	u8_bridge_statut_ip;	//Statut de l'adresse IP de l'interface bridge
	u8sod	u8_wlan_statut_ip;		//Statut de l'adresse IP de l'interface WLAN

	u8sod	u8_raz_jdb;				//Ordre raz du jdb (TRUE:activé, FALSE: désactivé)

	u8sod	u8_raz_alarmes_memorisees;	//Ordre raz des alarmes mémorisées (TRUE:activé, FALSE: désactivé)

	u8sod	u8_raz_general;	//Ordre raz général (TRUE:activé, FALSE: désactivé)
	
	u8sod	u8_restart_equipment;	//Ordre de redémarrer l'équipement a été donné (Ce champ permet de renseigner le journal de bord et les traps)
														//TRUE ordre donné
	u8sod	pu8_flag_errorconfig[NB_MAX_ERRORCONFIG];	//Signale un problème de configuration (nécessaire pour calculer l'alarme associée)
														//TRUE probleme de configuration, sinon FALSE
	u8sod	u8_info_reconfig_time;	//signale reconfiguration ntp/sntp
	u8sod	u8_info_reconfig_radiomodem;	//Signale la re-configuration du radio modem
	
}S_STRUCT_CIP_MONITOR;



/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




