/*========================================================================*/
/* NOM DU FICHIER  : td_cip_trap.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010											  */
/* Libelle         : Base de donn�es: Communication Inter Process (traps) */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE058 21/01/2011 CM
// - Ajout champs info_sup1 dans gestion trap
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
// - DEP: Ajout des �venements de connexion et d�connexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/


//Estimation: 200 �vts + 100 evts connexion/deconnexion
#define TAILLE_MAX_CIP_ELEMENTS_FIFOTRAP	300

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//d�finition d'un �l�ment trap �changer du processus monitor vers processus snmpd
typedef struct 
{
	S_STRUCT_DATE		s_date;				//Date/Heure de la derni�re occurrence de l'�v�nement � renseigner dans  la table alarme SNMP
	u16sod				u16_index_evt;		//Index de l'�v�nement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associ�e � l'�v�nement
	u8sod				u8_etat_evt;		//Etat de l'�v�nement
	U_UNION_INFO_SUP	u_info_sup1;		//Information suppl�mentaire 1
	u8sod				u8_info_sup2;		//Information suppl�mentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information suppl�mentaire 3
}S_STRUCT_CIP_ELEMENT_FIFOTRAP;

//d�finition d'un �l�ment de statut du trap g�r� par le processus snmpd
typedef struct 
{
	u16sod				u16_idx_table;		//Index de la table s_trap[]
	u16sod				u16_index_evt;		//Index de l'�v�nement qui permet de d�terminer le Num�ro d'�v�nement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associ�e � l'�v�nement
	S_STRUCT_DATE		s_date;				//Date/Heure de la derni�re occurrence de l'�v�nement � renseigner dans  la table alarme SNMP
	u8sod				u8_val_snmp;		//Valeur pour agent snmp (non acquitter, acquitter, supprimer)
	u8sod				u8_etat_evt;		//Etat de l'�v�nement (ETAT_EVT_DEBUT, ETAT_EVT_FIN, ETAT_EVT_INFO, ETAT_EVT_NON_DEFINI)
	U_UNION_INFO_SUP	u_info_sup1;		//Information suppl�mentaire 1
	u8sod				u8_info_sup2;		//Information suppl�mentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information suppl�mentaire 3
}S_STRUCT_CIP_ELEMENT_STATUSTRAP;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




