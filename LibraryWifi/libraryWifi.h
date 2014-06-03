/*========================================================================*/
/* NOM DU FICHIER  : libraryWifi.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 14/09/2010                                           */
/* Libelle         : LibraryWifi: initialisation de la librarie Wifi	  */
/* Projet          : WRM100                                               */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 14/09/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _LIBRARYWIFI
#define _LIBRARYWIFI_EXT
#else
#define _LIBRARYWIFI_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: InitModule_LibraryWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 14/09/2010 -
// Description	: Initialisation du module de libraryWifi
//=====================================================================================
void InitModule_LibraryWifi(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

