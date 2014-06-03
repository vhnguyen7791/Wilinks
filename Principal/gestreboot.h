/*========================================================================*/
/* NOM DU FICHIER  : gestreboot.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
/* Libelle         : Principal: gestion du reboot de l'équipement		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _GESTREBOOT
#define _GESTREBOOT_EXT
#else
#define _GESTREBOOT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: ExecuteGestionReboot
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Gestion du reboot de l'équipement
//=====================================================================================
void ExecuteGestionReboot(void);

//=====================================================================================
// Fonction		: InitModule_GestReboot
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de gestreboot
//=====================================================================================
void InitModule_GestReboot(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

