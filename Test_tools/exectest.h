/*========================================================================*/
/* NOM DU FICHIER  : exectest.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : TEST: Processus de test (wifi, ...)			      */
/* Projet          : WRM100	                                              */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECTEST
#define _EXECTEST_EXT
#else
#define _EXECTEST_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecTest
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de ExecTest
//=====================================================================================
void InitModule_ExecTest(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
