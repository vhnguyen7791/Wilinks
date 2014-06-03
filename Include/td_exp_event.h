/*========================================================================*/
/* NOM DU FICHIER  : td_exp_event.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : Base de donn�es: typedef gestion exploit des evts	  */
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
	BIT0_ETAT_COURANT = 0,		//si TYPE_EVT_ALARME : �tat courant dans la seconde
	BIT1_ETAT_REEL,				//si TYPE_EVT_ALARME : �tat r�el dans la seconde
	BIT2_ETAT_MEMORISE,			//si TYPE_EVT_ALARME : �tat m�moris�
	BIT3_ETAT_MESURE,			//si TYPE_EVT_INFO ou TYPE_EVT_ALARME : �tat mesur� dans la seconde
	BIT4_FLAG_MESURE_CALCULEE,	//si TYPE_EVT_ALARME
	BIT5_ETAT_COURANT_POUR_JDB,	//si TYPE_EVT_ALARME : �tat � la seconde courante pour JDB
	BIT6_ETAT_COURANT_POUR_TRAP,//si TYPE_EVT_ALARME : �tat � la seconde courante pour TRAP
	BIT7_ETAT_CFG_VALID,		//si TYPE_EVT_ALARME : config "validation" de l'�v�nement (copie)
	NB_MAX_BITS_ETATS_STATUT_EVENT
};

//Variable : S_STRUCT_STATE_EVENT
//Champs : u8_syst_evt
enum LISTE_DES_BITS_SYST_EVT
{
	BIT0_SYST_EVT_USED = 0,		//si TYPE_EVT_ALARME : indique si evt est utilis� (1: oui, 0: non)
	BIT1_SYST_COPIE_CFG_VALID,
	NB_MAX_BITS_SYST_EVENT
};

//Variable : S_STRUCT_STATE_EVENT
//Champs : pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3]
#define TAILLE_MAX_TAB_INFO_SUP3          6

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//****************************************************
/* structure de d�finition INFO_SUP					 */
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
/* structure de d�finition du statut d'un �v�nement	 */
//****************************************************
typedef struct 
{
	u16sod				u16_index_evt;		//Index de l'�v�nement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associ�e � l'�v�nement
	u8sod				u8_etat_evt;		//Etat de l'�v�nement
											//	- si evt est de type TYPE_EVT_ALARME (voir DESCRIPTION_EVENT) :
											//		b0: �tat de l'�v�nement courant (0: inactif, 1:actif)
											//		b1: �tat de l'�v�nement r�el (0: inactif, 1:actif)
											//		b2: �tat m�moris� (0: inactif, 1:actif)
											//		b3: �tat de l'�v�nement dans la seconde(0: inactif, 1:actif)
											//		ce bit est positionn� � 1 lorsque l'alarme est prs�ente;
											//		Et il est repositionn� � 0, lorsque le processus l'a pris en compte pour jdb et trap.
											//		b4: Flag mesure faite (0: KO, 1:OK)
											//		b5: �tat � la seconde courante pour JDB
											//		b6: �tat � la seconde courante pour TRAP
											//		b7: �tat config validation (0: non, 1: oui)
											//
											//		- si evt est de type TYPE_EVT_INFO (voir DESCRIPTION_EVENT) :
											//		b0: non utilis�
											//		b1: non utilis�
											//		b2: non utilis�
											//		b3: �tat de l'�v�nement dans la seconde(0: inactif, 1:actif)
											//		ce bit est positionn� � 1 lorsque l'�v�nement appara�t;
											//		Et il est repositionn� � 0, lorsque le processus l'a pris en compte pour jdb et trap.
											//		b4: non utilis�
											//		b5: non utilis�
											//		b6: non utilis�
											//		b7: non utilis�
	U_UNION_INFO_SUP	u_info_sup1;		//Information suppl�mentaire 1
	u8sod				u8_info_sup2;		//Information suppl�mentaire 2
											//		b0.b5: � d�finir
											//		b6: r�serv� pour indiquer si evt concerne l'entr�e RF ou l'entr�e ASI
											//		b7: r�serv� pour indiquer si champs PID pr�sent dans valeur de l'�v�nement
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information suppl�mentaire 3
	u8sod				u8_syst_evt;		//Systeme evt
											//		b0: indique si l'evt est valid� ou d�valid� par le systeme
}S_STRUCT_STATE_EVENT;


//********************************************************
/* structure de d�finition de l'exploit des �v�nements	 */
//********************************************************
typedef struct 
{
	S_STRUCT_DATE			s_date_dernier_reset;			//Date/Heure du dernier reset des alarmes m�moris�es
	S_STRUCT_STATE_EVENT	ps_statut[NB_MAX_EVENEMENTS];	//Liste des etats des �v�nements
}S_STRUCT_EXPLOIT_EVENTS;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

