/*========================================================================*/
/* NOM DU FICHIER  : suevt.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010											  */
/* Libelle         : HTML CGI: page HTML Evenements - config UN EVT		  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUEVT
#define _SUEVT_EXT
#else
#define _SUEVT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigEvt
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 24/06/2007
// Description	: Page HTML Configuration: configuration d'UN EVT
//				"URL=SUConfigEvt&param=<parametre>&hidden1=<numForm>"
//					<parametre> : numeroEvt + Page ListeEvt
//					<numForm> : suite action boutons
//=====================================================================================
void SUConfigEvt(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUEvt
//=====================================================================================
void InitModule_SUEvt(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
