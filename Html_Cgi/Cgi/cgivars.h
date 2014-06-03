/*========================================================================*/
/* NOM DU FICHIER  : cgivars.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 12/12/2005                                           */
/* Libelle         : HTML CGI:											  */
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/
#ifdef _CGIVARS
#define _CGIVARS_EXT
#else
#define _CGIVARS_EXT extern
#endif

/* method */
#define CGIFORM_METHOD_GET			0
#define CGIFORM_METHOD_POST			1

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/* function prototypes */
//=====================================================================================
// Fonction		: getRequestMethod
// Entrees		: rien
// Sortie		: <form_method> (CGIFORM_METHOD_GET or CGIFORM_METHOD_POST) on success,	-1 on failure.
// Auteur		: 
// Description	: 
//=====================================================================================
int getRequestMethod();

//=====================================================================================
// Fonction		: getGETvars
// Entrees		: rien
// Sortie		: <getvars<
// Auteur		: 
// Description	: 
//=====================================================================================
s8sod **getGETvars();

//=====================================================================================
// Fonction		: getPOSTvars
// Entrees		: rien
// Sortie		: <postvars<
// Auteur		: 
// Description	: 
//=====================================================================================
s8sod **getPOSTvars();

//=====================================================================================
// Fonction		: s32CleanUp
// Entrees		: 
// Sortie		: 
// Auteur		: 
// Description	: free the mallocs
//=====================================================================================
s32sod s32CleanUp(s32sod loc_s32_form_method, s8sod **loc_pps8_getvars, s8sod **loc_pps8_postvars);

//=====================================================================================
// Fonction		: s32GetArgNb
// Entrees		: <loc_pps8_postvars<
// Sortie		: <loc_s32_Idx>
// Auteur		: 
// Description	: free the mallocs
//=====================================================================================
s32sod s32GetArgNb(s8sod **loc_pps8_postvars);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
