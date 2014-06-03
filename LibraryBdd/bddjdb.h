/*========================================================================*/
/* NOM DU FICHIER  : bddjdb.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Base de données: Journal de bord					  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
//BE017 12/03/2010 CM
// - Optimisation contenu des fichiers jdbpart, cip_fifojdb et cip_fifotrap
//BE018 15/03/2010 CM
// - Correction risque de corruption du journal de bord sauvé en FLASH lors de l'écriture d'un évènement
//	en effet, on va sécurisé l'écriture dans le fichier jdbpart en doublant l'écriture dans un autre fichier (jdbcur.log)
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la base de données du journal de bord

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _BDDJDB
#define _BDDJDB_EXT
#else
#define _BDDJDB_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/


//=====================================================================================
// Fonction		: u8TestEvtJdb
// Entrees		: <loc_ps_evtjdb< : pointeur sur un évènement jdb
// Sortie		: <loc_u8_resultat> : TRUE,si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Test un évènement type du jdb
//=====================================================================================
u8sod u8TestEvtJdb(S_STRUCT_JDBEVT *loc_ps_evtjdb);

//============================================================================
// Fonction		: ps8GetChNomFileJdbPart
// Entrees		: <loc_u8_numjdbpart> : numéro du jdbpart
// Sortie		: <loc_ps8_nomFileJdbPart< : chaine 
// Auteur		: CM - 10/03/2010 -
// Description	: renvoie la chaîne du nom du fichier jdbpart
//============================================================================
s8sod* ps8GetChNomFileJdbPart(u8sod loc_u8_numjdbpart);

// -------------------------------------------------------------
// Fonction		: u8RemoveJdbPart
// Entrees		: <loc_u8_numjdbpart> : numéro du jdbpart
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 10/03/2010
// Description	: Suppression du fichier jdbpart identifié par son numéro
// -------------------------------------------------------------
u8sod u8RemoveJdbPart(u8sod loc_u8_numjdbpart);

// -------------------------------------------------------------
// Fonction		: u8AddEvtJdbPart
// Entrees		: <loc_ps_elt_fifojdb< : elt jdb à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
//				  <loc_u8_numjdbpart> : numéro du jdbpart
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure empile l'evt jdb dans le fichier jdbpart 
// -------------------------------------------------------------
u8sod u8AddEvtJdbPart(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod loc_u8_numjdbpart);

// -------------------------------------------------------------
// Fonction		: u8ReadEvtJdbPart
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				  <loc_u8_numjdbpart>			 : numéro du jdbpart
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture de l'élément de fifojdb
//				: <loc_pu16_cpt_elt_jdb_lus<	: pointeur sur compteur élément jdb lus avec succès
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure lit les evts jdb dans le fichier jdbpart
// -------------------------------------------------------------
u8sod u8ReadEvtJdbPart(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod loc_u8_numjdbpart, u8sod	(*loc_func_u8Action)(S_STRUCT_JDBEVT*), u16sod *loc_pu16_cpt_elt_jdb_lus);

//=====================================================================================
// Fonction		: u8FillStatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
//				: <loc_u16_idx_statutjdb>: index du fichier statutjdb
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillStatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb, u16sod loc_u16_idx_statutjdb);

//=====================================================================================
// Fonction		: u8EditStatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
//				: <loc_u16_idx_statutjdb>: index du fichier statutjdb
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditStatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb, u16sod loc_u16_idx_statutjdb);

//=====================================================================================
// Fonction		: InitStatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de statutjdb
//=====================================================================================
void InitStatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb);

//=====================================================================================
// Fonction		: RazJournalDeBord
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Remise à zéro du journal de bord
//=====================================================================================
void RazJournalDeBord(S_STRUCT_STATUTJDB *loc_ps_statutjdb);

//=====================================================================================
// Fonction		: InitBDD_StatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de la base de données de statutjdb
//=====================================================================================
void InitBDD_StatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb);


//=====================================================================================
// Fonction		: InitEvtJdb
// Entrees		: <loc_ps_evtjdb< : pointeur sur un évènement jdb
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation d'un évènement type du jdb
//=====================================================================================
void InitEvtJdb(S_STRUCT_JDBEVT *loc_ps_evtjdb);

//=====================================================================================
// Fonction		: InitModule_BddJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation du module de bddjdb
//=====================================================================================
void InitModule_BddJdb(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _BDDJDB
//-----------------------------------------------------
//	DEFINITION D'UN EVT JDB DANS FICHIER
//-----------------------------------------------------
//Remarque: noms raccourcis pour pouvoir economiser place lors de la sauvegarde dans la FLASH
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_SIMPLE_EVTJDB[] = {
	{	"D",			FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, s_date)},
	{	"V",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, t_valeur_evt)},
	{	"E",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, u8_etat_evt)},
	{	"i1",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, u_info_sup1)},
	{	"i2",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, u8_info_sup2)},
	{	"i3",			FTYPVAL_TABU8_HEXA,	NULL, TAILLE_MAX_TAB_INFO_SUP3,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, pu8_tab_info_sup3)},
	//positionné à la fin pour s'assurer que lecture soit correcte
	{	"I",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_JDBEVT, u16_index_evt)}, 
	{	NULL,	0,	NULL,	0,	0,	0	}
};
#else
_BDDJDB_EXT T_STRUCT_FILE_FIELD PT_DEF_STRUCT_SIMPLE_EVTJDB[];
#endif

_BDDJDB_EXT T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_JDBPART;


