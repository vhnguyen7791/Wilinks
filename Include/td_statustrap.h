/*========================================================================*/
/* NOM DU FICHIER  : td_statustrap.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010											  */
/* Libelle         : Base de données: typedef gestion de liste status traps*/
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source BE373 - SDVB200)
//BE058 21/01/2011 CM
// - Ajout champs info_sup1 dans gestion trap
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Estimation: 250 évts + 100 evts connexion + 100 evts deconnexion
#define TAILLE_MAX_TABLE_STATUSTRAP	450

//Variable : S_STRUCT_STATUS_TRAPS
//Champs : s_trap[].u8_val_snmp
#define VAL_SNMP_NON_ACQUITTER	0
#define VAL_SNMP_ACQUITTER		1
#define VAL_SNMP_SUPPRIMER		2


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//définition d'un trap
typedef struct 
{
	struct S_STRUCT_STA_TRAP *ps_next;		//Pointeur sur le prochain trap géré dans le mécanisme
	u16sod				u16_idx_table;		//Index de la table s_trap[]
	u16sod				u16_index_evt;		//Index de l'évènement qui permet de déterminer le Numéro d'évènement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associée à l'évènement
	u32sod				u32_cpt_emission_trap;	//Nombre de réemission d'un trap
	u32sod				u32_cpt_interval_trap;	//Intervalle en secondes entre 2 émissions de trap identiques
	S_STRUCT_DATE		s_date;				//Date/Heure de la dernière occurrence de l'évènement à renseigner dans  la table alarme SNMP
	u8sod				u8_val_snmp;		//Valeur pour agent snmp (non acquitter, acquitter, supprimer)
	u8sod				u8_etat_evt;		//Etat de l'évènement (ETAT_EVT_DEBUT, ETAT_EVT_FIN, ETAT_EVT_INFO, ETAT_EVT_NON_DEFINI)
	U_UNION_INFO_SUP	u_info_sup1;		//Information supplémentaire 1
	u8sod				u8_info_sup2;		//Information supplémentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information supplémentaire 3
}S_STRUCT_STA_TRAP;

//Définition de la base de données d'envoi des traps
typedef struct 
{
	u32sod			u32_sequence_counter;				//Sequence counter (à incrémenter à chaque nouveau trap émis).
	S_STRUCT_STA_TRAP	*ps_premier_trap;				//Pointeur sur le premier trap enregistré dans le tableau de TRAPS
	S_STRUCT_STA_TRAP	s_trap [TAILLE_MAX_TABLE_STATUSTRAP];	//Liste du statut des traps
	
}S_STRUCT_STATUS_TRAPS;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




