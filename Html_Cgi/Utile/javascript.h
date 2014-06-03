/*========================================================================*/
/* NOM DU FICHIER  : javascript.h			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: fonctions javascripts génériques			  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _JAVASCRIPT
#define _JAVASCRIPT_EXT
#else
#define _JAVASCRIPT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: JSActualiser
// Entrees		: <pc_nomPageHtml<
// Sortie		: rien
// Auteur		: CM - 13/04/2004 -
// Description	: fonction utilisée pour actualiser à partir de HomeB la page HTML
//=====================================================================================
void JSActualiser(char *pc_nomPageHtml);

//=====================================================================================
// Fonction		: JSNumCheck
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2004 -
// Description	: Javascript pour tester des valeurs numériques
//=====================================================================================
void JSNumCheck(void);

//=====================================================================================
// Fonction		: JSIPCheck
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2004 -
// Description	: Javascript pour tester les adresses IP
//=====================================================================================
void JSIPCheck(void);

//=====================================================================================
// Fonction		: JSTextCheck
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2004 -
// Description	: JavaScript pour tester texte
//=====================================================================================
void JSTextCheck(void);

//=====================================================================================
// Fonction		: InitModuleJavaScript
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/04/2004 -
// Description	: Initialisation du module de JavaScript
//=====================================================================================
void InitModuleJavaScript(void);
   
/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

