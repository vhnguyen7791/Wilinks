/*========================================================================*/
/* NOM DU FICHIER  : td_exp_event.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : Base de données: typedef gestion exploit des evts	  */
/* Projet          : WRM100                                               */
/* Indice	       : BE060												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE016 11/03/2010 CM
// - CREATION
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_STATE_EVENT
//Champs : u8_etat_evt
enum LISTE_DES_BITS_ETAT_EVT
{
	BIT0_ETAT_COURANT = 0,		//si TYPE_EVT_ALARME : état courant dans la seconde
	BIT1_ETAT_REEL,				//si TYPE_EVT_ALARME : état réel dans la seconde
	BIT2_ETAT_MEMORISE,			//si TYPE_EVT_ALARME : état mémorisé
	BIT3_ETAT_MESURE,			//si TYPE_EVT_INFO ou TYPE_EVT_ALARME : état mesuré dans la seconde
	BIT4_FLAG_MESURE_CALCULEE,	//si TYPE_EVT_ALARME
	BIT5_ETAT_COURANT_POUR_JDB,	//si TYPE_EVT_ALARME : état à la seconde courante pour JDB
	BIT6_ETAT_COURANT_POUR_TRAP,//si TYPE_EVT_ALARME : état à la seconde courante pour TRAP
	BIT7_ETAT_CFG_VALID,		//si TYPE_EVT_ALARME : config "validation" de l'évènement (copie)
	NB_MAX_BITS_ETATS_STATUT_EVENT
};

//Variable : S_STRUCT_STATE_EVENT
//Champs : u8_syst_evt
enum LISTE_DES_BITS_SYST_EVT
{
	BIT0_SYST_EVT_USED = 0,		//si TYPE_EVT_ALARME : indique si evt est utilisé (1: oui, 0: non)
	BIT1_SYST_COPIE_CFG_VALID,
	NB_MAX_BITS_SYST_EVENT
};

//Variable : S_STRUCT_STATE_EVENT
//Champs : pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3]
#define TAILLE_MAX_TAB_INFO_SUP3          6

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//****************************************************
/* structure de définition INFO_SUP					 */
//****************************************************
#pragma pack(1)
typedef	union 
{
	u8sod			pu8_term[4];
	u16sod			pu16_term[2];
	f32sod			f32_term;
	u32sod			u32_term;
	s32sod			s32_term;
}U_UNION_INFO_SUP;
#pragma pack()


//****************************************************
/* structure de définition du statut d'un évènement	 */
//****************************************************
typedef struct 
{
	u16sod				u16_index_evt;		//Index de l'évènement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associée à l'évènement
	u8sod				u8_etat_evt;		//Etat de l'évènement
											//	- si evt est de type TYPE_EVT_ALARME (voir DESCRIPTION_EVENT) :
											//		b0: état de l'évènement courant (0: inactif, 1:actif)
											//		b1: état de l'évènement réel (0: inactif, 1:actif)
											//		b2: état mémorisé (0: inactif, 1:actif)
											//		b3: état de l'évènement dans la seconde(0: inactif, 1:actif)
											//		ce bit est positionné à 1 lorsque l'alarme est prséente;
											//		Et il est repositionné à 0, lorsque le processus l'a pris en compte pour jdb et trap.
											//		b4: Flag mesure faite (0: KO, 1:OK)
											//		b5: état à la seconde courante pour JDB
											//		b6: état à la seconde courante pour TRAP
											//		b7: état config validation (0: non, 1: oui)
											//
											//		- si evt est de type TYPE_EVT_INFO (voir DESCRIPTION_EVENT) :
											//		b0: non utilisé
											//		b1: non utilisé
											//		b2: non utilisé
											//		b3: état de l'évènement dans la seconde(0: inactif, 1:actif)
											//		ce bit est positionné à 1 lorsque l'évènement apparaît;
											//		Et il est repositionné à 0, lorsque le processus l'a pris en compte pour jdb et trap.
											//		b4: non utilisé
											//		b5: non utilisé
											//		b6: non utilisé
											//		b7: non utilisé
	U_UNION_INFO_SUP	u_info_sup1;		//Information supplémentaire 1
	u8sod				u8_info_sup2;		//Information supplémentaire 2
											//		b0.b5: à définir
											//		b6: réservé pour indiquer si evt concerne l'entrée RF ou l'entrée ASI
											//		b7: réservé pour indiquer si champs PID présent dans valeur de l'évènement
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information supplémentaire 3
	u8sod				u8_syst_evt;		//Systeme evt
											//		b0: indique si l'evt est validé ou dévalidé par le systeme
}S_STRUCT_STATE_EVENT;


//********************************************************
/* structure de définition de l'exploit des évènements	 */
//********************************************************
typedef struct 
{
	S_STRUCT_DATE			s_date_dernier_reset;			//Date/Heure du dernier reset des alarmes mémorisées
	S_STRUCT_STATE_EVENT	ps_statut[NB_MAX_EVENEMENTS];	//Liste des etats des évènements
}S_STRUCT_EXPLOIT_EVENTS;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

