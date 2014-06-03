/*========================================================================*/
/* NOM DU FICHIER  : suconfigDhcp.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/01/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - DHCP server/relay*/
/* Projet          : WRM100                                               */
/* Indice          : BE005                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE005 15/01/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGDHCP
#define _SUCONFIGDHCP_EXT
#else
#define _SUCONFIGDHCP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigDhcp
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/01/2010
// Description	: Page HTML Configuration: DHCP
//				"URL=SUConfigDhcp"
//=====================================================================================
void SUConfigDhcp(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigDhcp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/01/2010
// Description	: Initialisation du module de SUConfigDhcp
//=====================================================================================
void InitModule_SUConfigDhcp(void);



/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
