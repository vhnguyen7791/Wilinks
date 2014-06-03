/*========================================================================*/
/* NOM DU FICHIER  : susecurite.h									   	  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: page HTML sécurité						  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUSECURITE
#define _SUSECURITE_EXT
#else
#define _SUSECURITE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUAdmSecurite
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Page permet de configurer les paramètres de sécurité des serveurs HTTP,SNMP,FTP
//=====================================================================================
void SUAdmSecurite(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUSecurite
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de susecurite
//=====================================================================================
void InitModule_SUSecurite(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
