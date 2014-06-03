/*========================================================================*/
/* NOM DU FICHIER  : testfile.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 22/01/2010                                           */
/* Libelle         : Test gestion fichier								  */
/* Projet          : WRM100		                                          */
/* Indice          : BE006                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE006 22/01/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _TESTFILE
#define _TESTFILE_EXT
#else
#define _TESTFILE_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: TestFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/01/2010 -
// Description	: Teste la gestion fcihier
//=====================================================================================
void TestFile(void);

//=====================================================================================
// Fonction		: InitModule_TestFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/01/2010 -
// Description	: Initialisation du module de testfile
//=====================================================================================
void InitModule_TestFile(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

