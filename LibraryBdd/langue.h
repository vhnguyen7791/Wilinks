/*========================================================================*/
/* NOM DU FICHIER  : langue.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : Base de données: langue							  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _LANGUE
#define _LANGUE_EXT
#else
#define _LANGUE_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: InitModule_Langue
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/07/2007 -
// Description	: Initialisation du module Langue
//=====================================================================================
void InitModule_Langue(void);

/*_______VI - CONSTANTES ET VARIABLES ______________________________________*/


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//Module langue
_LANGUE_EXT	S_TYPE_MESSAGE *pt_tb_msg;
