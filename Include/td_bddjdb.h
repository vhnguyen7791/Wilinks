/*========================================================================*/
/* NOM DU FICHIER  : td_bddjdb.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010											  */
/* Libelle         : Base de donn�es: Journal de bord					  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
//BE018 15/03/2010 CM
// - Correction risque de corruption du journal de bord sauv� en FLASH lors de l'�criture d'un �v�nement
//	en effet, on va s�curis� l'�criture dans le fichier jdbpart en doublant l'�criture dans un autre fichier (jdbcur.log)
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/



#define TAILLE_MAX_JDBEVT		1000	// nombre maximum d'�v�nements dans le journal de bord
#define NB_MAX_EVT_PAR_JDBPART	100		// nombre d'�v�nements max par fichier jdbpart

//Nombre de fichiers jdbpart<num>.log � g�rer (dans la FLASH)
#define NB_MAX_JDBPART			(TAILLE_MAX_JDBEVT / NB_MAX_EVT_PAR_JDBPART)

//Num�ro d'identification du fichier jdbcur.log
#define NUM_JDBCUR	0xFF

//***************************************
//Liste des statutjdb
//***************************************
enum LISTE_DES_STATUTJDB
{
	IDXSTATUTJDB_BASE = 0,	//[FLASH]
	IDXSTATUTJDB_BACKUP,	//[FLASH]
	IDXSTATUTJDB_RAM,		//[RAM]
	NB_MAX_IDXSTATUTJDB
};


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//d�finition d'un �v�nement du journal de bord
typedef struct 
{
	S_STRUCT_DATE		s_date;				//Date/Heure de la derni�re occurrence de l'�v�nement � renseigner dans  la table alarme SNMP
	u16sod				u16_index_evt;		//Index de l'�v�nement
	T_SIZE_VALEUR_EVT	t_valeur_evt;		//Valeur associ�e � l'�v�nement
	u8sod				u8_etat_evt;		//Etat de l'�v�nement
	U_UNION_INFO_SUP	u_info_sup1;		//Information suppl�mentaire 1
	u8sod				u8_info_sup2;		//Information suppl�mentaire 2
	u8sod				pu8_tab_info_sup3[TAILLE_MAX_TAB_INFO_SUP3];	//Information suppl�mentaire 3
}S_STRUCT_JDBEVT;

//d�finition du fichier de statut du jdb
typedef struct 
{
	//param�tres sauv�s en FLASH et en RAM
	S_STRUCT_DATE	s_date_dernier_reset;	//Date/Heure du dernier reset du journal de bord
	u8sod			u8_numrd_jdbpart;		//Premier num�ro du fichier cr�� dans la rotation
	u8sod			u8_numwr_jdbpart;		//Num�ro du fichier en cours d'�criture dans la rotation
	u16sod			u16_checksum_file;		//Checksum de la base de donn�es

	//param�tres sauv�s uniquement en RAM
	u16sod	u16_nb_total_evt;	//Nombre total d'�v�nements dans le journal de bord de l'�quipement
	u16sod	u16_nbevt_jdbpart_encours;	//Nombre d'�v�nements en cours dans le fichier num jdbpart

}S_STRUCT_STATUTJDB;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




