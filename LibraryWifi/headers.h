/*========================================================================*/
/* NOM DU FICHIER  : headers.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM												      */
/* Date			   : 14/09/2010                                           */
/* Libelle         : libraryWifi: listes des headers			          */
/* Projet          : WRM100	                                              */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 14/09/10 CM
// - CREATION
/*========================================================================*/


/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _WRM100_ABG_SELECT
#include "../Include/header_driver_ABG.h"
#include "wifi_ABG_tools.h"
#endif

#ifdef _WRM100_N_SELECT
#include "../Include/header_driver_N.h"
#include "wifi_N_tools.h"
#endif
#include "libraryWifi.h"
#include "wifi_tools.h"


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
