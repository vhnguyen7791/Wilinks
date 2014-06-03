/*========================================================================*/
/* NOM DU FICHIER  : evt_debug.h			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : Monitor: Calcul des évènements debug				  */
/* Projet          : WRM100                                               */
/* Indice          : BE015                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 11/03/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EVT_DEBUG
#define _EVT_DEBUG_EXT
#else
#define _EVT_DEBUG_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_Debug
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 04/03/2010 -
// Description	: Calcul les évènements de debug
//=====================================================================================
void CalculEvents_Debug(void);

//=====================================================================================
// Fonction		: InitModule_Evt_Debug
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Initialisation du module evt_debug
//=====================================================================================
void InitModule_Evt_Debug(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

