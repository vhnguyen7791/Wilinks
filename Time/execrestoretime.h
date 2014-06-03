/*========================================================================*/
/* NOM DU FICHIER  : execrestoretime.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/06/2010                                           */
/* Libelle         : RESTORETIME: Processus de restauration heure		  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECRESTORETIME
#define _EXECRESTORETIME_EXT
#else
#define _EXECRESTORETIME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: RestoreTimeFromFlash
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: restaure au démarrage la date/heure de la FLASH NOR
//=====================================================================================
void RestoreTimeFromFlash(void);

//=====================================================================================
// Fonction		: u8ReadImageTimePartition
// Entrees		: <loc_ps8_fileimage<: fichier image de la partition
//				  <loc_pu32_new_position<: nouvelle position
//				  <loc_pu32_time_read<: valeur du temps lu
// Sortie		: <loc_u8_resultat>: TRUE ou FALSE
// Auteur		: CM - 30/06/2010 -
// Description	: Lecture de l'image de la partition time_save (et on s'assure que l'image est propre)
//=====================================================================================
u8sod u8ReadImageTimePartition(s8sod *loc_ps8_fileimage, u32sod *loc_pu32_new_position, u32sod *loc_pu32_time_read);

//=====================================================================================
// Fonction		: InitModule_ExecRestoretime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Initialisation du module de ExecRestoretime
//=====================================================================================
void InitModule_ExecRestoretime(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
