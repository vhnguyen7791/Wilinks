/*========================================================================*/
/* NOM DU FICHIER  : testswap_app.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 21/12/2009                                           */
/* Libelle         : Test le swap sur l'autre application				  */
/* Projet          : WRM100		                                          */
/* Indice          : BE002                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 21/12/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _TESTSWAP_APP
#define _TESTSWAP_APP_EXT
#else
#define _TESTSWAP_APP_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: TestSwap_App
// Entrees		: <loc_u8_mode_app>: app à activer
// Sortie		: rien
// Auteur		: CM - 21/12/2009 -
// Description	: Teste le basculement sur l'autre application
//=====================================================================================
void TestSwap_App(u8sod loc_u8_mode_app);

//=====================================================================================
// Fonction		: InitModule_TestSwap_App
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 21/12/2009 -
// Description	: Initialisation du module de testswap_app
//=====================================================================================
void InitModule_TestSwap_App(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

