/*========================================================================*/
/* NOM DU FICHIER  : suconfigWirelessAdv.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Wireless (Adv)	  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGWIRELESSADV
#define _SUCONFIGWIRELESSADV_EXT
#else
#define _SUCONFIGWIRELESSADV_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigWirelessAdv
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: Wireless (Adv)
//				"URL=SUConfigWirelessAdv"
//=====================================================================================
void SUConfigWirelessAdv(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigWirelessAdv
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigWirelessAdv
//=====================================================================================
void InitModule_SUConfigWirelessAdv(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
