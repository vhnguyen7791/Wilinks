/*========================================================================*/
/* NOM DU FICHIER  : td_date.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 08/10/2007											  */
/* Libelle         : Base de données: Type def date						  */
/* Projet          : WRM100                                               */
/* Indice	       : BE046												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Date/heure par défaut (au démarrage)
#define ANNEE_PAR_DEFAUT		2010
#define MOIS_PAR_DEFAUT			1		//Janvier
#define JOUR_PAR_DEFAUT			1		//jour 1
#define HEURE_PAR_DEFAUT		0
#define MINUTE_PAR_DEFAUT		0
#define SECONDE_PAR_DEFAUT		0

//Methodes pour fixer date (SetDate)
enum LIST_METHODES_SETDATE
{
	METHODE_SETDATE_MANUEL = 0,
	METHODE_SETDATE_SYSTEM,
	NB_MAX_METHODES_SETDATE	
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/


#pragma pack(1)
//définition d'une date
typedef struct
{
	u16sod		u16_annee;
	u8sod		u8_mois;
	u8sod		u8_jour;
	u8sod		u8_heure;
	u8sod		u8_minute;
	u8sod		u8_seconde;
}S_STRUCT_DATE;
#pragma pack()

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


