/*========================================================================*/
/* NOM DU FICHIER  : timeout.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 05/11/2009                                           */
/* Libelle         : Base de données: gestion des timeout				  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _TIMEOUT
#define _TIMEOUT_EXT
#else
#define _TIMEOUT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: StartTimeOut
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 05/11/2009 -
// Description	: Démarre l'incrementation du timeout
//=====================================================================================
void StartTimeOut(S_STRUCT_TIME_OUT *loc_pt_timeout);

//=====================================================================================
// Fonction		: InitStructTimeOut
// Entrees		: <loc_ps_date<
// Sortie		: void
// Auteur		: CM - 05/11/2009 -
// Description	: Initialisation la structure timeout
//=====================================================================================
void InitStructTimeOut(S_STRUCT_TIME_OUT *loc_pt_timeout);

//=====================================================================================
// Fonction		: InitModule_Timeout
// Entrees		: rien
// Sortie		: void
// Auteur		: CM - 05/11/2009 -
// Description	: Initialisation du module de Date
//=====================================================================================
void InitModule_Timeout(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


