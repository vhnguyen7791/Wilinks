/*========================================================================*/
/* NOM DU FICHIER  : vwarning.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML de w@rning					  */
/* Projet          : WRM100                                               */
/* Indice          : BE054                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _VWARNING
#define _VWARNING_EXT
#else
#define _VWARNING_EXT	extern
#endif

enum LISTE_DES_MESSAGES_AVERTISSEMENTS
{
	WARNING_PAGE_INDISPONIBLE = 0,
	WARNING_MAJ_INFO_EN_COURS,
	WARNING_RELOAD_SUADMINDENTIF_ET_RELOAD_FRAME_A,
	WARNING_RELOAD_SUTIME_ET_RELOAD_FRAME_A,
	WARNING_RELOAD_SUADMLANGUE_ET_RELOAD_FRAME_A_FRAME_B,
	WARNING_CONFIG_OK,
	WARNING_CONFIG_OK_ET_RELOAD_FRAME_A,
	WARNING_CONFIG_OK_ET_RELOAD_FRAME_B,
	WARNING_CONFIG_KO,
	WARNING_PAS_D_INFORMATION,
	WARNING_CONFIG_ADRESSE_IP,
	WARNING_CHARGEMENT_EN_COURS,
	WARNING_RESET_EQUIPEMENT_EN_COURS,
	WARNING_BASE_DONNEES_INACCESSIBLE,
	WARNING_MODE_ONLY_STATION_ROUTER,
	WARNING_MODE_ONLY_STATION,
	WARNING_INDISPONIBLE_MODE_MONITOR,
	NB_MAX_MESSAGES_WARNING
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: PageWarning
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: page HTML d'avertissement
//=====================================================================================
void PageWarning(s8sod **loc_p_varlist, s32sod loc_s32_form_method);

//=====================================================================================
// Fonction		: InitModule_Vwarning
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation du module Vwarning
//=====================================================================================
void InitModule_Vwarning(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

