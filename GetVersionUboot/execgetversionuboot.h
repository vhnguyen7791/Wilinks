/*========================================================================*/
/* NOM DU FICHIER  : execgetversionuboot.h								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 17/12/2009                                           */
/* Libelle         : getversion_uboot: Processus récupére version U-BOOT  */
/* Projet          : WRM100	                                              */
/* Indice          : BE002                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 17/12/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECGETVERSIONUBOOT
#define _EXECGETVERSIONUBOOT_EXT
#else
#define _EXECGETVERSIONUBOOT_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8TestValidInfoSystem
// Entrees		: <loc_pu8_infosystem< : pointeur sur zone info systeme
// Sortie		: <loc_u8_resultat>: TRUE, sinon FALSE
// Auteur		: CM - 16/12/2009 -
// Description	: Test si les infos systèmes sont valides
//=====================================================================================
u8sod u8TestValidInfoSystem(u8sod *loc_pu8_infosystem);

//=====================================================================================
// Fonction		: InitModule_ExecGetVersionUboot
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/12/2009 -
// Description	: Initialisation du module de ExecGetVersionUboot
//=====================================================================================
void InitModule_ExecGetVersionUboot(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
