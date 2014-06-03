/*========================================================================*/
/* NOM DU FICHIER  : td_cmdsystem.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 23/03/2011											  */
/* Libelle         : Base de données: Type def cmdsystem				  */
/* Projet          : WRM100                                               */
/* Indice	       : BE060												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE060 23/03/2011 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_SYST_FILE
//Champs : ps8_nom[LG_MAX_PATH_SYST_FILE+1]
#define LG_MAX_PATH_SYST_FILE	100

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//définition d'un fichier dans un systeme de fichier
typedef struct
{
	s8sod ps8_nom[LG_MAX_PATH_SYST_FILE+1];		//nom du fichier
	u32sod	u32_sizeoffile;	//taille du fichier en octets
}S_STRUCT_SYST_FILE;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


