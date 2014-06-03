/*========================================================================*/
/* NOM DU FICHIER  : vhomeB.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML frames homeA homeB homeC		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VHOMEB
#define _VHOMEB_EXT
#else
#define _VHOMEB_EXT	extern
#endif


// Fonction		: PageTestAccesPossible
//				  <ui_mode_test> : Test à faire
#define	PAGE_TEST_INFO_VALIDE			0x0001
#define	PAGE_TEST_MODE_LOCAL			0x0002


//Define liens menu
#define LIEN_HTML_MENU_ALARME	1
#define LIEN_HTML_MENU_ANALYSE	2

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: JavaScript_HomeB
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/04/2004 -
// Description	: code de javascript de la page HomeB
//=====================================================================================
void JavaScript_HomeB(void);

//=====================================================================================
// Fonction		: HomeB
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Menu général
//=====================================================================================
void HomeB(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VHomeB
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module vhomeB
//=====================================================================================
void InitModule_VHomeB(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

