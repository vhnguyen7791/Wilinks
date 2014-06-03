/*========================================================================*/
/* NOM DU FICHIER  : librarySystem.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/07/2010                                           */
/* Libelle         : Base de données: initialisation de la librarie system*/
/* Projet          : WRM100                                               */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 01/07/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _LIBRARYSYSTEM
#define _LIBRARYSYSTEM_EXT
#else
#define _LIBRARYSYSTEM_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: FunctionPrintfVide
//Entrée	 : <loc_ps8_fmtp< : message du texte dans debug
// Sortie		: void
// Auteur		: CM - 07/07/2010 -
// Description	: Fonction de la printf video
//=====================================================================================
void FunctionPrintfVide(s8sod *loc_ps8_fmtp, ...);

//=====================================================================================
// Fonction		: SetConfig_LibrarySystem
// Entrees		: <loc_pf_functionPrintf>	: fonction de debug
// Sortie		: rien
// Auteur		: CM - 01/07/2010 -
// Description	: Configure la library system
//=====================================================================================
void SetConfig_LibrarySystem(void *loc_pf_functionPrintf);

//=====================================================================================
// Fonction		: InitModule_LibrarySystem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/07/2010 -
// Description	: Initialisation du module de librarySystem
//=====================================================================================
void InitModule_LibrarySystem(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//Fonction de debug
_LIBRARYSYSTEM_EXT void (*pf_functionPrintf)(s8sod *loc_ps8_fmtp, ...);
