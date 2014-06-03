/*========================================================================*/
/* NOM DU FICHIER  : statustrap.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : NET-SNMP: gestion de la liste status traps			  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source BE373 - SDVB200)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _STATUSTRAP
#define _STATUSTRAP_EXT
#else
#define _STATUSTRAP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u16SearchFreeLstStatusTrap
// Entrees		: rien
// Sortie		: <loc_u16_index>
// Auteur		: CM - 29/08/2007 -
// Description	: recherche dans s_trap[] une position disponible
//=====================================================================================
u16sod u16SearchFreeLstStatusTrap(void);

//=====================================================================================
// Fonction		: AddLst_StatusTrap
// Entrees		: <loc_ps_trap< : info sur trap à ajouter
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Ajout trap à la liste chainée
//=====================================================================================
void AddLst_StatusTrap(S_STRUCT_STA_TRAP *loc_ps_trap);

//=====================================================================================
// Fonction		: u8Search_IdxStatusTrap
// Entrees		: <loc_u16_idx_table> : index à trouver dans liste chainée
//				  >loc_pps_trap< : statut du trap avec loc_u16_idx_table
// Sortie		: <loc_u8_resultat> : TRUE si trouvé, FALSE si non trouvé
// Auteur		: CM - 29/08/2007 -
// Description	: recherche i dans s_trap[] une position disponible
//=====================================================================================
u8sod u8Search_IdxStatusTrap(u16sod loc_u16_idx_table, S_STRUCT_STA_TRAP **loc_pps_trap);

//=====================================================================================
// Fonction		: AcquitAllTraps
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 08/09/2008 -
// Description	: Acquittement de tous les traps
//=====================================================================================
void AcquitAllTraps(void);

//=====================================================================================
// Fonction		: ptGetPtrStatusTrap
// Entrees		: rien
// Sortie		: <loc_pt_return< : adresse de la variable globale status_trap
// Auteur		: CM - 01/03/2010 -
// Description	: Retourne l'adresse de la variable globale status_trap
//=====================================================================================
S_STRUCT_STATUS_TRAPS* ptGetPtrStatusTrap(void);

//=====================================================================================
// Fonction		: InitStatusTrap
// Entrees		: <loc_ps_trap< : pointeur sur élément trap de la liste chainée
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du status d'un trap
//=====================================================================================
void InitStatusTrap(S_STRUCT_STA_TRAP *loc_ps_trap);

//=====================================================================================
// Fonction		: InitLst_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation de la liste chainée
//=====================================================================================
void InitLst_StatusTrap(void);

//=====================================================================================
// Fonction		: InitModule_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du module de StatusTrap
//=====================================================================================
void InitModule_StatusTrap(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


_STATUSTRAP_EXT S_STRUCT_STATUS_TRAPS s_status_trap;
_STATUSTRAP_EXT S_STRUCT_STATUS_TRAPS *ps_status_trap;

