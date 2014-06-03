/*========================================================================*/
/* NOM DU FICHIER  : td_event.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/05/2008											  */
/* Libelle         : Base de données: Type def event					  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/


//Variable : S_STRUCT_DESCRIPTION_EVT
//Champs : u8_format_valeur_jdb
//Champs : u8_format_valeur_trap
#define FV_NULL		0x00
#define FV_AUTRES	0x08

/*_____III - DEFINITIONS DE TYPES_________________________________________*/


//*****************************************
//Definition de la taille de la valeur de event
//*****************************************
typedef u32sod T_SIZE_VALEUR_EVT;

//*****************************************
/* structure de définition des évts		  */
//*****************************************
typedef struct 
{
	u16sod	u16_index_evt;						//index de l'évt
	u16sod	u16_numero_evt;						//numéro de l'évt
	u8sod	u8_type_evt;						//type de l'évt (alarme, info ou générique)
	u8sod	u8_groupe;							//groupe de l'alarme
	u8sod	u8_valeur_associee_action;			//Action à appliquer en fonction des valeurs associées à l'évt
	u8sod	u8_format_valeur_jdb;				//Format de la valeur dans jdb
	u8sod	u8_format_valeur_trap;				//Format de la valeur dans trap
	u8sod	u8_disponible;						//disponibilité de l'évt
}S_STRUCT_DESCRIPTION_EVT;

//*****************************************
/* structure de définition du groupe	  */
//*****************************************
typedef struct 
{
	u16sod	u16_index_groupe;					//index du groupe
	u8sod	u8_disponible;						//disponibilité du groupe

}S_STRUCT_DESCRIPTION_GROUPE_EVT;

//*********************************************
/* structure de définition des évts/groupes	  */
//*********************************************
typedef struct 
{
	S_STRUCT_DESCRIPTION_EVT		ps_description_event	[NB_MAX_EVENEMENTS];
	S_STRUCT_DESCRIPTION_GROUPE_EVT	ps_description_groupe	[NB_MAX_GROUPES];
}S_STRUCT_EVENTSYSTEM;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

