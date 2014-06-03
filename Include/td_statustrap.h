/*========================================================================*/
/* NOM DU FICHIER  : td_statustrap.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010											  */
/* Libelle         : Base de donn�es: typedef gestion de liste status traps*/
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
// - DEP: Ajout des �venements de connexion et d�connexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Estimation: 250 �vts + 100 evts connexion + 100 evts deconnexion
#define TAILLE_MAX_TABLE_STATUSTRAP	450

//Variable : S_STRUCT_STATUS_TRAPS
//Champs : s_trap[].u8_val_snmp
#define VAL_SNMP_NON_ACQUITTER	0
#define VAL_SNMP_ACQUITTER		1
#define VAL_SNMP_SUPPRIMER		2


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//d�finition d'un trap
typedef struct 
{
	struct S_STRUCT_STA_TRAP *ps_next;		//Pointeur sur le prochain trap g�r� dans le m�canisme
	u16sod				u16_idx_table;		//Index de la table s_trap[]
	u16sod				u16_index_evt;		//Index de l'�v�nement qui permet de d�terminer le Num�ro d'�v�nement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associ�e � l'�v�nement
	u32sod				u32_cpt_emission_trap;	//Nombre de r�emission d'un trap
	u32sod				u32_cpt_interval_trap;	//Intervalle en secondes entre 2 �missions de trap identiques
	S_STRUCT_DATE		s_date;				//Date/Heure de la derni�re occurrence de l'�v�nement � renseigner dans  la table alarme SNMP
	u8sod				u8_val_snmp;		//Valeur pour agent snmp (non acquitter, acquitter, supprimer)
	u8sod				u8_etat_evt;		//Etat de l'�v�nement (ETAT_EVT_DEBUT, ETAT_EVT_FIN, ETAT_EVT_INFO, ETAT_EVT_NON_DEFINI)
	U_UNION_INFO_SUP	u_info_sup1;		//Information suppl�mentaire 1
	u8sod				u8_info_sup2;		//Information suppl�mentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information suppl�mentaire 3
}S_STRUCT_STA_TRAP;

//D�finition de la base de donn�es d'envoi des traps
typedef struct 
{
	u32sod			u32_sequence_counter;				//Sequence counter (� incr�menter � chaque nouveau trap �mis).
	S_STRUCT_STA_TRAP	*ps_premier_trap;				//Pointeur sur le premier trap enregistr� dans le tableau de TRAPS
	S_STRUCT_STA_TRAP	s_trap [TAILLE_MAX_TABLE_STATUSTRAP];	//Liste du statut des traps
	
}S_STRUCT_STATUS_TRAPS;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




