/*========================================================================*/
/* NOM DU FICHIER  : vtrap.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010                                           */
/* Libelle         : HTML CGI: page HTML TRAPs							  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VTRAP
#define _VTRAP_EXT
#else
#define _VTRAP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VTrap
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 19/11/2007
// Description	: Page HTML Evenement: TRAPs
//				"URL=VTrap"
//=====================================================================================
void VTrap(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: u8Html_StatusTrap
// Entrees		: <loc_ps_elt_statustrap< : statut trap à afficher
// Sortie		: <loc_u8_return>
// Auteur		: CM - 03/03/2010
// Description	: Affichage d'une ligne de statut trap
//=====================================================================================
u8sod u8Html_StatusTrap(S_STRUCT_CIP_ELEMENT_STATUSTRAP *loc_ps_elt_statustrap);

//=====================================================================================
// Fonction		: InitModule_VTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 19/11/2007
// Description	: Initialisation du module de VTrap
//=====================================================================================
void InitModule_VTrap(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
