/*========================================================================*/
/* NOM DU FICHIER  : vcontact.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML contact						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VCONTACT
#define _VCONTACT_EXT
#else
#define _VCONTACT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VContact
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: page HTML contact (Coordonnées de l'entreprise)
//=====================================================================================
void VContact(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_Vcontact
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation du module Vcontact
//=====================================================================================
void InitModule_Vcontact(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

