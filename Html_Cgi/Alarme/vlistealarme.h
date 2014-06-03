/*========================================================================*/
/* NOM DU FICHIER  : vlistealarme.h	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/07/2007                                           */
/* Libelle         : HTML CGI: page HTML exploitation Liste alarmes		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VLISTEALARME
#define _VLISTEALARME_EXT
#else
#define _VLISTEALARME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VListeAlarme_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page rafraichissement page Alarme
//				"URL=VListeAlarme_Dyn
//=====================================================================================
void VListeAlarme_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VListeAlarme
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page HTML Exploitation: Alarme
//				"URL=VListeAlarme"
//=====================================================================================
void VListeAlarme(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VListeAlarme
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/07/2007
// Description	: Initialisation du module de VListeAlarme
//=====================================================================================
void InitModule_VListeAlarme(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
