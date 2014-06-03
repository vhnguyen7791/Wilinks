/*========================================================================*/
/* NOM DU FICHIER  : infosystem.h			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 21/12/2009                                           */
/* Libelle         : Base de donn�es: gestion partition infosystem		  */
/* Projet          : WRM100                                               */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 21/12/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Modification processus update (independance avec principal)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _INFOSYSTEM
#define _INFOSYSTEM_EXT
#else
#define _INFOSYSTEM_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: u8MiseAJourInfoSystem
// Entrees		: <loc_u8_mode> : mode app � activer
//				: <loc_ps8_version_uboot< : version u-boot
// Sortie		: <loc_u8_resultat>: TRUE,sinon FALSE
// Auteur		: CM - 18/12/2009 -
// Description	: Mise � jour info syst�me
//=====================================================================================
//Modify to adapt wilinks
//u8sod u8MiseAJourInfoSystem(u8sod loc_u8_mode, s8sod *loc_ps8_version_uboot);

//=====================================================================================
// Fonction		: InitModule_InfoSystem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 21/12/2009 -
// Description	: Initialisation du module de infosystem
//=====================================================================================
void InitModule_InfoSystem(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

