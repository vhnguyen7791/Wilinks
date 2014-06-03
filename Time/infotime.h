/*========================================================================*/
/* NOM DU FICHIER  : infotime.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/06/2010                                           */
/* Libelle         : SAVETIME/RESTORETIME: module de dialogue			  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _INFOTIME
#define _INFOTIME_EXT
#else
#define _INFOTIME_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: WriteInfoTime
// Entrees		: <loc_ps8_nomfichier< : Nom du fichier
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Ecriture du fichier d'information issu du processu restoretime
//=====================================================================================
void WriteInfoTime(s8sod *loc_ps8_nomfichier);

//=====================================================================================
// Fonction		: ReadInfoTime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Lecture du fichier d'information issu du processu restoretime
//=====================================================================================
void ReadInfoTime(void);

//=====================================================================================
// Fonction		: InitModule_InfoTime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Initialisation du module de infotime
//=====================================================================================
void InitModule_InfoTime(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//index de la position dans la partition en cours
_INFOTIME_EXT u32sod u32_idx_position_time;
//Flag de la partition en cours
_INFOTIME_EXT u8sod u8_ispartition_first;

