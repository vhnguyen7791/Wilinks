/*========================================================================*/
/* NOM DU FICHIER  : execsavetime.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/06/2010                                           */
/* Libelle         : SAVETIME: Processus de sauvegarde heure			  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECSAVETIME
#define _EXECSAVETIME_EXT
#else
#define _EXECSAVETIME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: SaveTimeToFlash
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Sauve la date/heure dans la FLASH NOR
//=====================================================================================
void SaveTimeToFlash(void);

//=====================================================================================
// Fonction		: u8CreateFileTimeBinary
// Entrees		: <loc_u32_time>
// Sortie		: <loc_u8_resultat>: TRUE ou FALSE
// Auteur		: CM - 30/06/2010 -
// Description	: Création du fichier binaire minitime.bin (contenu à sauver dans la FLASH NOR)
//=====================================================================================
u8sod u8CreateFileTimeBinary(u32sod loc_u32_time);

//=====================================================================================
// Fonction		: InitModule_ExecSavetime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Initialisation du module de ExecSavetime
//=====================================================================================
void InitModule_ExecSavetime(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
