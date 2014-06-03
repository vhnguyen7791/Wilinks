/*========================================================================*/
/* NOM DU FICHIER  : testmac.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Test sur le MAC									  */
/* Projet          : WRM100		                                          */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _TESTMAC
#define _TESTMAC_EXT
#else
#define _TESTMAC_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: TestMAC_LanInterface
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste la fonction MAC sur l'accès LAN
//=====================================================================================
void TestMAC_LanInterface(void);

//=====================================================================================
// Fonction		: TestMAC_WLanInterface
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste la fonction MAC sur l'accès WLAN
//=====================================================================================
void TestMAC_WLanInterface(void);

//=====================================================================================
// Fonction		: InitModule_TestMac
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de testmac
//=====================================================================================
void InitModule_TestMac(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

