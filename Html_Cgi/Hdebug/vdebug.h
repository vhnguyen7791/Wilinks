/*========================================================================*/
/* NOM DU FICHIER  : vdebug.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 04/07/2007                                           */
/* Libelle         : HTML CGI: pages HTML de debug						  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Int�gration gestion des �v�nements
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VDEBUG
#define _VDEBUG_EXT
#else
#define _VDEBUG_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: VdbgSodielec
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 04/07/2007
// Description	: Page HTML: debug
//=====================================================================================
void VdbgSodielec(s8sod **loc_p_varlist, s32sod loc_s32_form_method);


//=====================================================================================
// Fonction		: VDebugConfiguration
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: rien
// Auteur		: CM - 28/01/2010
// Description	: Page HTML: DEBUG - CONFIGURATION
//=====================================================================================
void VDebugConfiguration(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VDebugInformations
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 06/05/2008
// Description	: Page HTML: debug d'informations diverses
//=====================================================================================
void VDebugInformations(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VDebugMsgDebug
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 10/07/2007
// Description	: Page HTML: debug
//=====================================================================================
void VDebugMsgDebug(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VDebugSizeOf
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 06/05/2008
// Description	: Page HTML: debug sizeof bdd
//=====================================================================================
void VDebugSizeOf(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VDebugLogOut
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 06/05/2008
// Description	: Page HTML: permettant de se d�connecter
//=====================================================================================
void VDebugLogOut(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: VDebugSystemEvent
// Entrees		: <loc_p_varlist< : liste des param�tres URL
//				  <loc_s32_form_method> : m�thode du formulaire
// Sortie		: Rien
// Auteur		: CM - 22/05/2008
// Description	: Page HTML: debug system event
//=====================================================================================
void VDebugSystemEvent(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_VDebug
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de VDebug
//=====================================================================================
void InitModule_VDebug(void);





/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
