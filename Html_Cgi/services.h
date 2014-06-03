/*========================================================================*/
/* NOM DU FICHIER  : services.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 29/09/2009                                           */
/* Libelle         : HTML_CGI: listes des headers						  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE037 06/07/2010 CM
// - Ajout exploitation temperature 
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE055 17/01/2011 CM
// - Modification configuration des antennes
/*========================================================================*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "./Utile/Html_define.h"

#include "../Include/headers.h"
#include "../LibrarySystem/headers.h"
#include "../LibraryBdd/headers.h"

#include "./Utile/bdd_html.h"
#include "./Utile/divers.h"
#include "./Utile/javascript.h"
#include "./Utile/refresh.h"

#include "./Frame/frame.h"
#include "./Frame/vhomeA.h"
#include "./Frame/vhomeB.h"
#include "./Frame/vhomeC.h"
#include "./Frame/vaccueil.h"
#include "./Frame/vconsole.h"
#include "./Frame/vcontact.h"
#include "./Frame/vwarning.h"
#include "./Frame/vsynoptique.h"
#include "./Frame/vcfginprogress.h"

#include "./Admin/pages.h"
#include "./Admin/suadmcontrol.h"
#include "./Admin/suadmidentif.h"
#include "./Admin/sutime.h"
#include "./Admin/susecurite.h"
#include "./Admin/vadmversions.h"
#include "./Admin/sulangue.h"
#include "./Admin/surefresh.h"
#include "./Admin/susystemlog.h"

#include "./Config/suconfigMode.h"
#include "./Config/suconfigNetwork.h"
#include "./Config/suconfigWirelessBasic.h"
#include "./Config/suconfigWirelessAdv.h"
#include "./Config/suconfigHandoff.h"
#include "./Config/suconfigRoutingGene.h"
#include "./Config/suconfigRoutingStatic.h"
#include "./Config/suconfigRoutingPolitic.h"
#include "./Config/suconfigRoutingRip.h"
#include "./Config/suconfigDhcp.h"
#include "./Config/suconfigSnmp.h"
#include "./Config/suconfigNat.h"
#include "./Config/suconfigMulticast.h"

#include "./Exploit/vexploitWireless.h"
#include "./Exploit/vexploitNetwork.h"
#include "./Exploit/vexploitDhcpClient.h"
#include "./Exploit/vexploitGeneral.h"

//
//#include "./Config/vconfig.h"
//#include "./Config/vconfigASI.h"


#include "./Evt/vlisteEvt.h"
#include "./Evt/suevt.h"
#include "./Evt/vjdbevt.h"
#include "./Evt/vtrap.h"

#include "./Alarme/valarme.h"
#include "./Alarme/vlistealarme.h"

#include "./Hdebug/vdebug.h"
#include "./Hdebug/vtestfinal.h"

#include "./Cgi/cgi.h"
#include "./Cgi/cgivars.h"


