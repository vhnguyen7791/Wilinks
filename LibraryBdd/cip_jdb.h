/*========================================================================*/
/* NOM DU FICHIER  : cip_jdb.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Base de données: Communication Inter Process (jdb)   */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la communication inter processus:
//  --> pour échanger les évènements entre processus monitor et processus jdb
//  --> pour échanger des données supplémentaires avec le processus jdb

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CIP_JDB
#define _CIP_JDB_EXT
#else
#define _CIP_JDB_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: Start_CipFifoJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Démarrage de gestion de fifo
//=====================================================================================
void Start_CipFifoJdb(void);

// -------------------------------------------------------------
// Fonction		: u8AddCipFifoJdb
// Entrees		: <loc_ps_elt_fifojdb< : elt jdb à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure empile l'evt jdb dans le fichier cip_fifojdb
// -------------------------------------------------------------
u8sod u8AddCipFifoJdb(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);

// -------------------------------------------------------------
// Fonction		: u8ReadCipFifoJdb
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture de l'élément de fifojdb
//				: <loc_pu16_cpt_elt_jdb_lus<	: pointeur sur compteur élément jdb lus avec succès
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure lit les evts jdb dans le fichier cip_fifojdb
// -------------------------------------------------------------
u8sod u8ReadCipFifoJdb(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod	(*loc_func_u8Action)(S_STRUCT_JDBEVT*), u16sod *loc_pu16_cpt_elt_jdb_lus);

//=====================================================================================
// Fonction		: EnregistreJdb
// Entrees		: <loc_u16_index_evt> : index de l'évènement
//				  <loc_t_valeur_evt>  : valeur de l'évènement
//				  <loc_u32_info_sup1> : info 1
//				  <loc_u8_info_sup2>  : information summplémentaire 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u8_etat_evt>	  : etat : début / fin / info
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Fonction d'enregistrement des évènements du Jdb
//=====================================================================================
void EnregistreJdb(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info_sup1, u8sod loc_u8_info_sup2, u8sod *loc_pu8_info3, u8sod loc_u8_etat_evt);

//=====================================================================================
// Fonction		: u8FillCipJdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillCipJdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb);

//=====================================================================================
// Fonction		: u8EditCipJdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditCipJdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb);

//=====================================================================================
// Fonction		: InitBDD_Cip_FifoJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de la base de données de cip_fifojdb
//=====================================================================================
void InitBDD_Cip_FifoJdb(void);

//=====================================================================================
// Fonction		: Raz_Cip_Jdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: RAZ des ordres de la base de données de cip_jdb
//=====================================================================================
void Raz_Cip_Jdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb);

//=====================================================================================
// Fonction		: InitBDD_Cip_Jdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de la base de données de cip_jdb
//=====================================================================================
void InitBDD_Cip_Jdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb);

//=====================================================================================
// Fonction		: InitModule_Cip_Jdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation du module de cip_jdb
//=====================================================================================
void InitModule_Cip_Jdb(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//Définition du fichier cip_fifojdb
_CIP_JDB_EXT T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_FIFOJDB_INI;

