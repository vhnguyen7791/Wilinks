/*========================================================================*/
/* NOM DU FICHIER  : valeurs.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : Base de données: valeurs							  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/* Historique      :                                                      */
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VALEURS
#define _VALEURS_EXT
#else
#define _VALEURS_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: InitModule_Valeurs
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/07/2007 -
// Description	: Initialisation du module Valeurs
//=====================================================================================
void InitModule_Valeurs(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_VALEURS_EXT S_STRUCT_TAB_VALEURS T_TB_VAL;
