/*========================================================================*/
/* NOM DU FICHIER  : td_timeout.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 04/07/2007                                           */
/* Libelle         : Base de données: type def timeout					  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/



/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef struct 
{
	u8sod	u8_flag;			//Flag (TRUE ou FALSE)
	u16sod	u16_cpt_timeout;	//Compteur
}S_STRUCT_TIME_OUT;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


