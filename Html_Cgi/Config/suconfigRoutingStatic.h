/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingStatic.h							  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing / Static */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGROUTINGSTATIC
#define _SUCONFIGROUTINGSTATIC_EXT
#else
#define _SUCONFIGROUTINGSTATIC_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigRoutingStatic
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: IP Routing 
//				"URL=SUConfigRoutingStatic"
//=====================================================================================
void SUConfigRoutingStatic(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingStatic
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingStatic
//=====================================================================================
void InitModule_SUConfigRoutingStatic(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
