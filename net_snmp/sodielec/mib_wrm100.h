/*========================================================================*/
/* NOM DU FICHIER  : mib_wrm100.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009											  */
/* Libelle         : NET-SNMP:											  */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE019 16/03/2010 CM
// - Ajout MIB wrm100 dans agent SNMP
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/


#include "mibdefs.h"

/*_____III - DEFINITIONS DE TYPES_________________________________________*/


/*_______IV  - PROTOTYPES IMPORTES _____________________MODULE______________*/

/** To use 'header_generic', we need the util_funcs module */
config_require(util_funcs)

//=====================================================================================
// Fonction		: init_mib_wrm100
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation de la mib WRM100
//					Main Function called when SNMP is loaded
//=====================================================================================
void init_mib_wrm100(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/** ** for MIB Tree       */
FindVarMethod var_wrm100;
//Sous noeud description
WriteMethod write_descStruID;
WriteMethod write_descStruLocation;
WriteMethod write_descStruLanguage;
//Sous noeud managment
WriteMethod write_mgmtEvtUsed;
WriteMethod write_mgmtEvtLOG;
WriteMethod write_mgmtEvtSynthesis1;
//Sous noeud command
WriteMethod write_cmdGeneralRestart;
WriteMethod write_cmdClearAlarms;
WriteMethod write_cmdClearLog;
WriteMethod write_cmdClearAll;
WriteMethod write_cmdGenerateLogFile;

/** ** for Tables         */
FindVarMethod var_funcSoftwareRevisionTable;
FindVarMethod var_mgmtWirelessMultiTable;
FindVarMethod var_mgmtIProutingStaticTable;
FindVarMethod var_mgmtIProutingPolicyTable;
FindVarMethod var_mgmtNatPortForwardingTable;
FindVarMethod var_mgmtNatAddressesMappingTable;
FindVarMethod var_mgmtEvtTable;
FindVarMethod var_mgmtMulticast_Sources_Table;
FindVarMethod var_staAlarmslistTable;
FindVarMethod var_staWirelessApClientTable;
FindVarMethod var_staDhcpClientsTable;






