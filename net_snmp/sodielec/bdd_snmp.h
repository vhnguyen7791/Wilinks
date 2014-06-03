/*========================================================================*/
/* NOM DU FICHIER  : bdd_snmp.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009											  */
/* Libelle         : SNMP CGI: Base de données pour le serveur SNMP       */
/* Projet          : WRM100                                               */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
// - CREATION
//BE019 16/03/2010 CM
// - Ajout MIB wrm100 dans agent SNMP
//BE042 07/10/2010 CM
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
// - Ajout gestion liste des fréquences réglementaires
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _BDD_SNMP
#define _BDD_SNMP_EXT
#else
#define _BDD_SNMP_EXT extern
#endif

//Noeud OID MIB Administration
#define _ENTERPRISE_SODIELECV2_ADMINISTRATION	 1,3,6,1,4,1,9153,2,1,2
#define _ENTERPRISE_SODIELECV2_ADMINISTRATIONV1	 _ENTERPRISE_SODIELECV2_ADMINISTRATION,1

//Noeud OID MIB WRM100
#define _NOEUD_OID_MIB_PRODUIT	1,3,6,1,4,1,9153,2,1,3,2,1

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8CheckClientSnmpAllowed
// Entrees		: rien
// Sortie		: <loc_u8_result< : TRUE si autorisée, FALSE sinon
// Auteur		: CM - 25/09/2007 -
// Description	: Fonction qui test si accès en écriture est autorisée
//=====================================================================================
u8sod u8CheckClientSnmpAllowed(void);

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: ps8ConvertChaineToSnmp
//	Entrées		: <loc_ps8_chaine_initiale< : chaîne à converir
//	Sortie		: <ps8_chaine_convertie_snmp< : chaîne modifiée (variable globale)
//	Auteur		: CM - 04/09/2007
//	Description : Conversion d'une chaîne de caractères adaptée pour
//	snmp
//	Seuls les caractères suivants sont autorisés au niveau SNMP:
//		- A to Z
//		- a to z
//		- 0 to 9
//		- :;|=,{}<.()[]-'"
// -------------------------------------------------------------------------------------------------------- //
s8sod *ps8ConvertChaineToSnmp(s8sod *loc_ps8_chaine_initiale);

//=====================================================================================
// Fonction		: InitModule_Bdd_Snmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/06/2007 -
// Description	: Initialisation du module Bdd_snmp
//=====================================================================================
void InitModule_Bdd_Snmp(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef	_BDD_SNMP
const S_STRUCT_CONSTRUCTEUR S_CONFIG_CONSTRUCTEUR_DEFAUT =
{
	0x5A,	//u8_start
	NOM_DU_CONSTRUCTEUR,
	TELEPHONE_DU_CONSTRUCTEUR,
	FAX_DU_CONSTRUCTEUR,
	ADRESSE_DU_CONSTRUCTEUR_L1,
	ADRESSE_DU_CONSTRUCTEUR_L2,
	SITE_DU_CONSTRUCTEUR
};
#else
extern const S_STRUCT_CONSTRUCTEUR S_CONFIG_CONSTRUCTEUR_DEFAUT;
#endif


_BDD_SNMP_EXT S_STRUCT_CONFIGURATION s_config_process_snmpd; //Configuration en cours du processus snmpd
_BDD_SNMP_EXT S_STRUCT_CONFIGURATION s_cfg_tempo_snmpd; //Configuration temporaire du processus snmpd
_BDD_SNMP_EXT S_STRUCT_EXPLOITATION s_exploit_process_snmpd; //Exploitation
_BDD_SNMP_EXT S_STRUCT_EXPLOIT_EVENTS s_exp_events_process_snmpd;
_BDD_SNMP_EXT S_STRUCT_EVENTSYSTEM	*pt_eventsystem_process_snmpd;
_BDD_SNMP_EXT	S_STRUCT_LIST_FREQ s_list_freq_process_snmpd;

//Langue sélectionnée pour l'agent SNMP
_BDD_SNMP_EXT u8sod u8_snmp_langue;

//Type d'équipement
_BDD_SNMP_EXT u8sod u8_snmp_type_equipement;

//Gestion CIP
_BDD_SNMP_EXT S_STRUCT_CIP_MONITOR s_cip_monitor_from_snmpd;
_BDD_SNMP_EXT S_STRUCT_CIP_JDB s_cip_jdb_from_snmpd;

//Gestion du journal de bord
_BDD_SNMP_EXT S_STRUCT_STATUTJDB s_statutjdb_from_snmpd;


_BDD_SNMP_EXT s8sod ps8_data_a_tout_faire[1024+1];

