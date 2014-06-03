/*========================================================================*/
/* NOM DU FICHIER  : headers.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM												      */
/* Date			   : 09/09/2009                                           */
/* Libelle         : PRINCIPAL: listes des headers					      */
/* Projet          : WRM100	                                              */
/* Indice          : BE050                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration hostname
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calculée dans le processus 'monitor'.
// - Ajout option compilation "-Wall" + correction w@rning
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		userhigh / usermiddle / userlow
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE047 29/11/2010 CM
// - Gestion mode dégradé - connection à AP impossible en permanence suite à configuration wifi 
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
/*========================================================================*/

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../Include/headers.h"
#include "../LibrarySystem/headers.h"
#include "../LibraryBdd/headers.h"
#include "../LibraryNetwork/headers.h"
#include "../LibraryWifi/headers.h"

#include "execprincipal.h"
#include "gestconfig.h"
#include "gestreboot.h"
#include "passwd.h"
#include "watchdogwifi.h"

#include "Config/apply_cfg.h"
#include "Config/cfg_monitor.h"
#include "Config/cfg_jdb.h"
#include "Config/cfg_radiomodem.h"
#include "Config/cfg_wifi.h"
#ifdef _WRM100_ABG_SELECT
#include "Config/cfg_wlan_ABG.h"
#endif
#ifdef _WRM100_N_SELECT
#include "Config/cfg_wlan_N.h"
#endif
#include "Config/cfg_network.h"
#include "Config/cfg_hostapd.h"
#include "Config/cfg_wpa_supplicant.h"
#include "Config/cfg_snmp.h"
#include "Config/cfg_dhcp.h"
#include "Config/cfg_syslog.h"
#include "Config/cfg_time.h"
#include "Config/cfg_sntp.h"
#include "Config/cfg_ntp.h"
#include "Config/cfg_nat.h"
#include "Config/cfg_http.h"
#include "Config/cfg_multicast.h"
#include "Config/cfg_policyrouting.h"
#include "Config/cfg_bird.h"

