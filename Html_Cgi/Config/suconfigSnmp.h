/*========================================================================*/
/* NOM DU FICHIER  : suconfigsnmp.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/10/2009                                           */
/* Libelle         : HTML CGI: pages HTML de config SNMP				  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _SUCONFIGSNMP
#define _SUCONFIGSNMP_EXT
#else
#define _SUCONFIGSNMP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SUConfigSNMP
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Page HTML Configuration: SNMP
//=====================================================================================
void SUConfigSNMP(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_SUConfigSnmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de suconfigsnmp
//=====================================================================================
void InitModule_SUConfigSnmp(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

