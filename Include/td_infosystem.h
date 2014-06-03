/*========================================================================*/
/* NOM DU FICHIER  : td_infosystem.h				                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 21/12/2009                                           */
/* Libelle         : Base de donn�es: Type definition info system		  */
/* Projet          : WRM100                                               */
/* Indice          : BE002                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 21/12/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define NB_MIN_DATA_INFOSYSTEM	56
#define NB_MAX_DATA_INFOSYSTEM	1024
#define VALEUR_INFOSYSSTART	'@'
#define TAILLE_MAX_VALEUR_INFOSYSVERSION 50	//caract�res
enum LISTE_FIELD_INFO_SYSTEM
{
	INFOSYS_START = 0,		//1 octet
	INFOSYS_LENGTH = 1,		//2 octets
	INFOSYS_VERSION = 3,	//50 octets
	INFOSYS_APP_ACTIF = 53,
	NB_MAX_INFOSYS
};
//Define in execupdate.h (for Wilinks)
/*enum LISTE_MODES_BOOT
{
	MODE_BOOT_AUCUN = 0,
	MODE_BOOT_APP1,
	MODE_BOOT_APP2,
	NB_MAX_MODES_BOOT
};*/

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

