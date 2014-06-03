/*========================================================================*/
/* NOM DU FICHIER  : cip_trap.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Base de données: Communication Inter Process (traps) */
/* Projet          : WRM100                                               */
/* Indice          : BE061                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE058 21/01/2011 CM
// - Ajout champs info_sup1 dans gestion trap
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
//BE061 10/05/2011
// - Correction w@rning compilation dans appel de u8AddCipStatusTrap
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la communication inter processus:
//  --> pour échanger les traps entre processus monitor et processus snmpd
//  --> pour que le processus snmpd donne le statut des traps (table alameV1Table) aux autres processus

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CIP_TRAP
#define _CIP_TRAP_EXT
#else
#define _CIP_TRAP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: Start_CipFifoTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 04/03/2010
// Description	: Démarrage de gestion de fifo
//=====================================================================================
void Start_CipFifoTrap(void);

// -------------------------------------------------------------
// Fonction		: u8AddCipFifoTrap
// Entrees		: <loc_ps_elt_fifotrap< : trap à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 02/03/2010
// Description	: cette procedure empile le trap dans le fichier cip_fifotrap
// -------------------------------------------------------------
u8sod u8AddCipFifoTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP *loc_ps_elt_fifotrap, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);

// -------------------------------------------------------------
// Fonction		: u8ReadCipFifoTrap
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture de l'élément trap
//				: <loc_u16_cpt_elt_trap_max>	: nombre max d'éléments traps
//				: <loc_pu16_cpt_elt_trap_lus<	: pointeur sur compteur élément traps lus avec succès
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 02/03/2010
// Description	: cette procedure lit les traps (au max:loc_u16_cpt_elt_trap_max) dans le fichier cip_fifotrap
// -------------------------------------------------------------
u8sod u8ReadCipFifoTrap(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod	(*loc_func_u8Action)(S_STRUCT_CIP_ELEMENT_FIFOTRAP*), u16sod loc_u16_cpt_elt_trap_max, u16sod *loc_pu16_cpt_elt_trap_lus);

//=====================================================================================
// Fonction		: EnregistreTrap
// Entrees		: <loc_u16_index_evt> : index de l'évènement
//				  <loc_t_valeur_evt>  : valeur de l'évènement
//				  <loc_u32_info_sup1> : info 1
//				  <loc_u8_info_sup2>  : information summplémentaire 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u8_etat_evt>	  : etat : début / fin / info
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Fonction d'enregistrement des traps  
//=====================================================================================
void EnregistreTrap(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info_sup1, u8sod loc_u8_info_sup2, u8sod *loc_pu8_info3, u8sod loc_u8_etat_evt);

// -------------------------------------------------------------
// Fonction		: u8AddCipStatusTrap
// Entrees		: <loc_ps_elt_statustrap< : statut trap à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 03/03/2010
// Description	: cette procedure empile le statut trap dans le fichier cip_statustrap
// -------------------------------------------------------------
//d: BE061 10/05/2011 - Correction w@rning compilation dans appel de u8AddCipStatusTrap
//u8sod u8AddCipStatusTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP *loc_ps_elt_statustrap, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);
u8sod u8AddCipStatusTrap(S_STRUCT_CIP_ELEMENT_STATUSTRAP *loc_ps_elt_statustrap, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);
//f: BE061 10/05/2011 - Correction w@rning compilation dans appel de u8AddCipStatusTrap

// -------------------------------------------------------------
// Fonction		: u8ReadCipStatusTrap
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture du statut trap
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 03/03/2010
// Description	: cette procedure lit les statuts des traps dans le fichier cip_statustrap
// -------------------------------------------------------------
u8sod u8ReadCipStatusTrap(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod (*loc_func_u8Action)(S_STRUCT_CIP_ELEMENT_STATUSTRAP*));

//=====================================================================================
// Fonction		: InitBDD_Cip_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation de la base de données de cip_trap
//=====================================================================================
void InitBDD_Cip_Trap(void);

//=====================================================================================
// Fonction		: InitModule_Cip_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/03/2010
// Description	: Initialisation du module de cip_Trap
//=====================================================================================
void InitModule_Cip_Trap(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_CIP_TRAP_EXT T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_FIFOTRAP_INI;

_CIP_TRAP_EXT T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_STATUSTRAP_INI;
