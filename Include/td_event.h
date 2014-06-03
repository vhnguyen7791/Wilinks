/*========================================================================*/
/* NOM DU FICHIER  : td_event.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/05/2008											  */
/* Libelle         : Base de donn�es: Type def event					  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Int�gration gestion des �v�nements
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
/* structure de d�finition des �vts		  */
//*****************************************
typedef struct 
{
	u16sod	u16_index_evt;						//index de l'�vt
	u16sod	u16_numero_evt;						//num�ro de l'�vt
	u8sod	u8_type_evt;						//type de l'�vt (alarme, info ou g�n�rique)
	u8sod	u8_groupe;							//groupe de l'alarme
	u8sod	u8_valeur_associee_action;			//Action � appliquer en fonction des valeurs associ�es � l'�vt
	u8sod	u8_format_valeur_jdb;				//Format de la valeur dans jdb
	u8sod	u8_format_valeur_trap;				//Format de la valeur dans trap
	u8sod	u8_disponible;						//disponibilit� de l'�vt
}S_STRUCT_DESCRIPTION_EVT;

//*****************************************
/* structure de d�finition du groupe	  */
//*****************************************
typedef struct 
{
	u16sod	u16_index_groupe;					//index du groupe
	u8sod	u8_disponible;						//disponibilit� du groupe

}S_STRUCT_DESCRIPTION_GROUPE_EVT;

//*********************************************
/* structure de d�finition des �vts/groupes	  */
//*********************************************
typedef struct 
{
	S_STRUCT_DESCRIPTION_EVT		ps_description_event	[NB_MAX_EVENEMENTS];
	S_STRUCT_DESCRIPTION_GROUPE_EVT	ps_description_groupe	[NB_MAX_GROUPES];
}S_STRUCT_EVENTSYSTEM;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

