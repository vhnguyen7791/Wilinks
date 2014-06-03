/*========================================================================*/
/* NOM DU FICHIER  : resetfile.h			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/01/2010                                           */
/* Libelle         : Base de données: gestion ordre reset CPU			  */
/* Projet          : WRM100                                               */
/* Indice          : BE007                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE007 26/01/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _RESETFILE
#define _RESETFILE_EXT
#else
#define _RESETFILE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: OrdreResetUc
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Ordre de Reset du uC
//=====================================================================================
void OrdreResetUc(void);

//=====================================================================================
// Fonction		: InitModule_ResetFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/01/2010 -
// Description	: Initialisation du module de resetfile
//=====================================================================================
void InitModule_ResetFile(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

