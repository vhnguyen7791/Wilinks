/*========================================================================*/
/* NOM DU FICHIER  : execjdb.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Jdb: Processus de gestion du journal de bord	      */
/* Projet          : WRM100                                               */
/* Indice          : BE015                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION (à partir source SDVB200 - BE374)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère le journal de bord


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECJDB
#define _EXECJDB_EXT
#else
#define _EXECJDB_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8AjouteEvtFifoInterJdb
// Entrees		: <loc_ps_elt_fifojdb<	: element qui doit etre ajouté
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ajoute element jdb dans la fifo intermédiaire
//=====================================================================================
u8sod u8AjouteEvtFifoInterJdb(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb);

//=====================================================================================
// Fonction		: u8CreationFichierJdbLog
// Entrees		: <loc_u8_langue> : langue
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Génération du fichier Jdb.log
//=====================================================================================
u8sod u8CreationFichierJdbLog(u8sod	loc_u8_langue);

//=====================================================================================
// Fonction		: AjoutJdbPartToJdbLog
// Entrees		: <loc_u16_nb_evt_lus> : nombre d'évènements lus du fichier jdbpart
//				: <loc_pf_jdblog< : pointeur sur fichier jdb.log
//				: <loc_u8_langue> : langue
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Edition du fichier jdb.log en transferant tous les évènements de jdbpart dans jdb.log
//=====================================================================================
void AjoutJdbPartToJdbLog(u16sod loc_u16_nb_evt_lus, FILE *	loc_pf_jdblog, u8sod loc_u8_langue);

//=====================================================================================
// Fonction		: EditionEvtJdbLog
// Entrees		: <loc_ps_evt<	: element qui doit etre édité
//				: <loc_pf_jdblog< : pointeur sur fichier jdb.log
//				: <loc_u8_langue> : langue
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Edition de la ligne de l'évènement dans fichier jdb.log
//=====================================================================================
void EditionEvtJdbLog(S_STRUCT_JDBEVT *loc_ps_evt, FILE *loc_pf_jdblog, u8sod loc_u8_langue);

//=====================================================================================
// Fonction		: InitFifoInterJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation de la fifo intermédiaire (du jdb)
//=====================================================================================
void InitFifoInterJdb(void);

//=====================================================================================
// Fonction		: InitModule_ExecJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation du module de ExecJdb
//=====================================================================================
void InitModule_ExecJdb(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_EXECJDB_EXT S_STRUCT_CIP_JDB s_cip_jdb_courant;
_EXECJDB_EXT S_STRUCT_STATUTJDB s_statutjdb_courant;

//Photo de la configuration
_EXECJDB_EXT S_STRUCT_CONFIGURATION s_config_process_jdb;




