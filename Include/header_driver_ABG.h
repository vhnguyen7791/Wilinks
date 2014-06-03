/*========================================================================*/
/* NOM DU FICHIER  : header_driver_ABG.h                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 14/09/2010                                           */
/* Libelle         : Include des headers du wifi ABG					  */
/* Projet          : WRM100		                                          */
/* Indice          : BE056                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 14/09/2010 CM
// - CREATION
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _HEADER_DRIVER_ABG
#define _HEADER_DRIVER_ABG_EXT
#else
#define _HEADER_DRIVER_ABG_EXT extern
#endif

/* private ioctls */
#define IEEE80211_IOCTL_GETRAWRSSI 			(SIOCIWFIRSTPRIV+19)
#define IEEE80211_IOCTL_GETRSSI				(SIOCIWFIRSTPRIV+23)
#define IEEE80211_IOCTL_SETCHANNELBW		(SIOCIWFIRSTPRIV+11)
#define IEEE80211_IOCTL_GETCHANNELBW		(SIOCIWFIRSTPRIV+25)

//d: ----- issu du module wlib.h ----------------
/* Standard headers */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>		/* gethostbyname, getnetbyname */
#include <net/ethernet.h>	/* struct ether_addr */
#include <sys/time.h>		/* struct timeval */
#include <unistd.h>

/* This is our header selection. Try to hide the mess and the misery :-(
 * Don't look, you would go blind ;-)
 * Note : compatibility with *old* distributions has been removed,
 * you will need Glibc 2.2 and older to compile (which means 
 * Mandrake 8.0, Debian 2.3, RH 7.1 or older).
 */

/* Set of headers proposed by Dr. Michael Rietz <rietz@mail.amps.de>, 27.3.2 */
#include <net/if_arp.h>		/* For ARPHRD_ETHER */
#include <sys/socket.h>		/* For AF_INET & struct sockaddr */
#include <netinet/in.h>         /* For struct sockaddr_in */
#include <netinet/if_ether.h>

/* Fixup to be able to include kernel includes in userspace.
 * Basically, kill the sparse annotations... Jean II */
#ifndef __user
#define __user
#endif

#include <linux/types.h>		/* for "caddr_t" et al		*/

/* Glibc systems headers are supposedly less problematic than kernel ones */
#include <sys/socket.h>			/* for "struct sockaddr" et al	*/
#include <net/if.h>			/* for IFNAMSIZ and co... */

//Include du wireless.h (copie du fichier issu du wireless-tools)
#include "wireless.h"
//f: ----- issu du module wlib.h ----------------

//Include dans WRM100_APPLI/Driver-ABG
#include <include/compat.h>
#include "net80211/ieee80211_ioctl.h"

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

