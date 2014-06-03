/*========================================================================*/
/* NOM DU FICHIER  : td_cip_jdb.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010											  */
/* Libelle         : Base de donn�es: Communication Inter Process (jdb)   */
/* Projet          : WRM100                                               */
/* Indice          : BE015                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/


#define TAILLE_MAX_CIP_ELEMENTS_FIFOJDB	200


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//d�finition des informations � �changer avec le processus jdb
typedef struct 
{
	u8sod	pu8_flag_newcfg[NB_MAX_IDXCONFIG];		//Signale une susceptible �volution de la configuration pour le fichier d�fini par son index

	u8sod	u8_effacer_jdb;		//Ordre d'effacer le jdb (TRUE: ordre activ�, FALSE: ordre d�sactiv�)
	u8sod	u8_generer_jdb;		//Ordre de g�n�rer le fichier jdb (TRUE: ordre activ�, FALSE: ordre d�sactiv�)

}S_STRUCT_CIP_JDB;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




