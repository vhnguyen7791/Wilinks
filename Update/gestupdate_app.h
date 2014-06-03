/*========================================================================*/
/* NOM DU FICHIER  : gestupdate_app.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 17/12/2009                                           */
/* Libelle         : Update: gestion mise � jour de l'application		  */
/* Projet          : WRM100                                               */
/* Indice          : BE002                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 17/12/09 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _GESTUPDATE_APP
#define _GESTUPDATE_APP_EXT
#else
#define _GESTUPDATE_APP_EXT	extern
#endif
//#include "execupdate.h"
/*_____III - DEFINITIONS DE TYPES_____________________________________________*/


/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: u8TestIntegrityFileGz
// Entrees		: <loc_ps8_error< : detail erreur
// Sortie		: <loc_u8_resultat>: TRUE, sinon FALSE
// Auteur		: CM - 18/12/2009 -
// Description	: Test si le fichier compress� est valide
//					"corrupted data","crc error","incorrect length"
//=====================================================================================
u8sod u8TestIntegrityFileGz(s8sod *loc_ps8_error);

//=====================================================================================
// Fonction		: u8TestValidApp
// Entrees		: rien
// Sortie		: <loc_u8_resultat>: TRUE, sinon FALSE
// Auteur		: CM - 16/12/2009 -
// Description	: Test si l'application est valide
//=====================================================================================
u8sod u8TestValidApp(void);

u8sod u8MiseAJourInfoSystem(T_E_LISTE_MODES_BOOT e_mode_boot_tmp, s8sod *UNUSED(ps8_update__version_be_uboot));

//=====================================================================================
// Fonction		: ExecuteGestionUpdateApp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/12/2009 -
// Description	: Gestion mise � jour de l'application
//=====================================================================================
void ExecuteGestionUpdateApp(void);

//=====================================================================================
// Fonction		: InitModule_GestUpdate_App
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/12/2009 -
// Description	: Initialisation du module de gestupdate_app
//=====================================================================================
void InitModule_GestUpdate_App(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

