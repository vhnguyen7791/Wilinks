/*========================================================================*/
/* NOM DU FICHIER  : headers.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 09/09/2009                                           */
/* Libelle         : SNMPD: PROCESS AGENT SNMP					          */
/* Projet          : WRM100                                               */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 CM 09/09/09
// - CREATION
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
/*========================================================================*/

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "../../Include/headers.h"
#include "../../LibrarySystem/headers.h"
#include "../../LibraryBdd/headers.h"
#include "../../LibraryWifi/headers.h"

#include "bdd_snmp.h"
#include "exectrap.h"
#include "statustrap.h"

