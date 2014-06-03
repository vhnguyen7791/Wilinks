/*========================================================================*/
/* NOM DU FICHIER  : testwifi.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : Test sur le wifi									  */
/* Projet          : WRM100		                                          */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE040 13/09/2010 CM
// - Suppresion code inutile
//BE058 21/01/2011 CM
// - Modification gestion exploitation wifi
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _TESTWIFI
#define _TESTWIFI_EXT
#else
#define _TESTWIFI_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: TestWifi_ExtractBSSID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Teste la fonction wifi : extraction info BSSID
//=====================================================================================
void TestWifi_ExtractBSSID(void);

//=====================================================================================
// Fonction		: InitModule_TestWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de testwifi
//=====================================================================================
void InitModule_TestWifi(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

