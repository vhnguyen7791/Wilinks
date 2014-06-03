/*========================================================================*/
/* NOM DU FICHIER  : td_cip_trap.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010											  */
/* Libelle         : Base de données: Communication Inter Process (traps) */
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
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/


//Estimation: 200 évts + 100 evts connexion/deconnexion
#define TAILLE_MAX_CIP_ELEMENTS_FIFOTRAP	300

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//définition d'un élément trap échanger du processus monitor vers processus snmpd
typedef struct 
{
	S_STRUCT_DATE		s_date;				//Date/Heure de la dernière occurrence de l'évènement à renseigner dans  la table alarme SNMP
	u16sod				u16_index_evt;		//Index de l'évènement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associée à l'évènement
	u8sod				u8_etat_evt;		//Etat de l'évènement
	U_UNION_INFO_SUP	u_info_sup1;		//Information supplémentaire 1
	u8sod				u8_info_sup2;		//Information supplémentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information supplémentaire 3
}S_STRUCT_CIP_ELEMENT_FIFOTRAP;

//définition d'un élément de statut du trap géré par le processus snmpd
typedef struct 
{
	u16sod				u16_idx_table;		//Index de la table s_trap[]
	u16sod				u16_index_evt;		//Index de l'évènement qui permet de déterminer le Numéro d'évènement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associée à l'évènement
	S_STRUCT_DATE		s_date;				//Date/Heure de la dernière occurrence de l'évènement à renseigner dans  la table alarme SNMP
	u8sod				u8_val_snmp;		//Valeur pour agent snmp (non acquitter, acquitter, supprimer)
	u8sod				u8_etat_evt;		//Etat de l'évènement (ETAT_EVT_DEBUT, ETAT_EVT_FIN, ETAT_EVT_INFO, ETAT_EVT_NON_DEFINI)
	U_UNION_INFO_SUP	u_info_sup1;		//Information supplémentaire 1
	u8sod				u8_info_sup2;		//Information supplémentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information supplémentaire 3
}S_STRUCT_CIP_ELEMENT_STATUSTRAP;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




