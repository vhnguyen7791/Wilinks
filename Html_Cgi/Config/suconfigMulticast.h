/*========================================================================*/
/* NOM DU FICHIER  : suconfigMulticast.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/03/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Multicast		  */
/* Projet          : WRM100                                               */
/* Indice          : BE022                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE022 30/03/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGMULTICAST
#define _SUCONFIGMULTICAST_EXT
#else
#define _SUCONFIGMULTICAST_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigMulticast
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 30/03/2010
// Description	: Page HTML Configuration: Multicast
//				"URL=SUConfigMulticast"
//=====================================================================================
void SUConfigMulticast(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigMulticast
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/03/2010
// Description	: Initialisation du module de SUConfigMulticast
//=====================================================================================
void InitModule_SUConfigMulticast(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
