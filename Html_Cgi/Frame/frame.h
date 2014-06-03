/*========================================================================*/
/* NOM DU FICHIER  : frame.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: pages HTML frame							  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _FRAME
#define _FRAME_EXT
#else
#define _FRAME_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

#if ACTIVATION_CONSOLE_HTML
//=====================================================================================
// Fonction		: VFrame
// Entrees		: <loc_ps8_frame_a< : frame A
//				  <loc_ps8_frame_b< : frame B
//				  <loc_ps8_frame_c< : frame C
//				  <loc_ps8_frame_console< : frame Console
// Sortie		: rien
// Auteur		: CM - 11/06/2007 -
// Description	: Définition des frames du site web
//=====================================================================================
void VFrame(s8sod* loc_ps8_frame_a, s8sod* loc_ps8_frame_b, s8sod* loc_ps8_frame_c, s8sod* loc_ps8_frame_console);

#else

//=====================================================================================
// Fonction		: VFrame
// Entrees		: <loc_ps8_frame_a< : frame A
//				  <loc_ps8_frame_b< : frame B
//				  <loc_ps8_frame_c< : frame C
// Sortie		: rien
// Auteur		: CM - 11/06/2007 -
// Description	: Définition des frames du site web
//=====================================================================================
void VFrame(s8sod* loc_ps8_frame_a, s8sod* loc_ps8_frame_b, s8sod* loc_ps8_frame_c);

#endif

//=====================================================================================
// Fonction		: home
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Frameset d'accueil
//=====================================================================================
void home(s8sod **loc_p_varlist, s32sod loc_s32_form_method);


//=====================================================================================
// Fonction		: InitModule_Frame
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module frame
//=====================================================================================
void InitModule_Frame(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

