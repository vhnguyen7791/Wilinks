/*========================================================================*/
/* NOM DU FICHIER  : headers.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM												      */
/* Date			   : 09/09/2009                                           */
/* Libelle         : MONITOR: listes des headers				          */
/* Projet          : WRM100	                                              */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
// - Ajout exploitation du client NTP
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE058 21/01/2011 CM
// - Synchronisation configuration / exploitation
/*========================================================================*/

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>		/* struct timeval */

#include "../Include/headers.h"
#include "../LibrarySystem/headers.h"
#include "../LibraryBdd/headers.h"
#include "../LibraryNetwork/headers.h"
#include "../LibraryWifi/headers.h"

#include "execmonitor.h"
#include "custom_bdd.h"

#include "Event/internevent.h"
#include "Event/execevent.h"
#include "Event/evt_generique.h"
#include "Event/evt_debug.h"
#include "Event/evt_system.h"
#include "Event/evt_ap.h"
#include "Event/evt_sta.h"

#include "Exploit/gestexploit.h"
#include "Exploit/exp_versions.h"
#include "Exploit/exp_dhcp.h"
#include "Exploit/exp_wifi_station.h"
#include "Exploit/exp_wifi_ap.h"
#include "Exploit/exp_network.h"
#include "Exploit/exp_ntp.h"
#include "Exploit/exp_sntp.h"
#ifdef _WRM100_ABG_SELECT
#include "Exploit/exp_wlan_ABG.h"
#endif
#ifdef _WRM100_N_SELECT
#include "Exploit/exp_wlan_N.h"
#endif


