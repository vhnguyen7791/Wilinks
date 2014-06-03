/*========================================================================*/
/* NOM DU FICHIER  : setcountryid.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010                                           */
/* Libelle         : Test: set country ID								  */
/* Projet          : WRM100		                                          */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 11/10/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SETCOUNTRYID
#define _SETCOUNTRYID_EXT
#else
#define _SETCOUNTRYID_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SaveCountryID
// Entrees		: <loc_ps8_new_countryid< : chaine de caractères du country ID
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Sauvegarde du countryID
//=====================================================================================
void SaveCountryID(s8sod *loc_ps8_new_countryid);

//=====================================================================================
// Fonction		: SignalNewCountryID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: signal nouveau countryID
//=====================================================================================
void SignalNewCountryID(void);

//=====================================================================================
// Fonction		: InitModule_SetCountryID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation du module de setcountryid
//=====================================================================================
void InitModule_SetCountryID(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

