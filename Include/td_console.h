/*========================================================================*/
/* NOM DU FICHIER  : td_console.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 08/10/2007											  */
/* Libelle         : Base de données: Type def console					  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

enum LISTE_DES_COULEURS_DE_LA_CONSOLE
{
	COULEUR_CONSOLE_BLANC = 0,
	COULEUR_CONSOLE_NOIR,
	COULEUR_CONSOLE_JAUNE,
	COULEUR_CONSOLE_VERT,
	COULEUR_CONSOLE_BLEU,
	COULEUR_CONSOLE_ROUGE,
	COULEUR_CONSOLE_MAGENTA,
	COULEUR_CONSOLE_ORANGE,
	NB_MAX_COULEUR_CONSOLE
};

#define	TAILLE_MAX_MESSAGE_CONSOLE_HTTP		256

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef struct 
{
	u8sod	u8_flag;
	u8sod	u8_couleur;
	s8sod	ps8_chaine[TAILLE_MAX_MESSAGE_CONSOLE_HTTP];
}S_STRUCT_CONSOLE_HTTP_MESSAGE;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

