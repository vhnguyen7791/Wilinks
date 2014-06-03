/*========================================================================*/
/* NOM DU FICHIER  : exectrap.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 22/02/2010                                           */
/* Libelle         : NET-SNMP: gestion d'�mission des traps			      */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE012 22/10/2010 CM
// - CREATION
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui g�re l'�mission des traps


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECTRAP
#define _EXECTRAP_EXT
#else
#define _EXECTRAP_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: GestionTrapSodielec
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Gestion des traps sodielec
//=====================================================================================
void GestionTrapSodielec(void);

//=====================================================================================
// Fonction		: CopyCipFifoToStatusTrap
// Entrees		: <loc_ps_elt_fifotrap<	: element cip fifo trap qui doit etre ajout� � StatutTrap
//				: <loc_ps_trap<   :  r�sultat
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: transfert element fifo de cip  dans la statut des TRAP
//=====================================================================================
void CopyCipFifoToStatusTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP *loc_ps_elt_fifotrap, S_STRUCT_STA_TRAP *loc_ps_trap);

//=====================================================================================
// Fonction		: u8AjouteDansStatutTrap
// Entrees		: <loc_ps_elt_fifotrap<	: element qui doit etre ajout� � StatutTrap
// Sortie		: <loc_u8_return> : TRUE, si enregistrement OK	FALSE, si enregistrement KO
// Auteur		: CM - 29/08/2007 -
// Description	: ajoute element dans la table statut des TRAP
//=====================================================================================
u8sod u8AjouteDansStatutTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP	*loc_ps_elt_fifotrap);

//=====================================================================================
// Fonction		: Gestion_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Gestion du statusTRAP
//=====================================================================================
void Gestion_StatusTrap(void);

//=====================================================================================
// Fonction		: u8TestStatut_Trap
// Entrees		: <loc_ps_cfg_evt< : config de l'�vt
//				 <loc_ps_trap< : statut du trap
// Sortie		: rien
//					TRUE	   : conditions verifi�es (nombre d'�mission) pour l'envoie d' un trap
//					FALSE	   : conditions non verifi�es (nombre d'�mission), pas d'envoi de trap
// Auteur		: CM - 29/08/2007 -
// Description	: Test pour les traps de type alarme ou info ; verification de l'envoie ou pas du trap
//=====================================================================================
u8sod u8TestStatut_Trap(S_STRUCT_CFG_EVENT	*loc_ps_cfg_evt, S_STRUCT_STA_TRAP	*loc_ps_trap);

// -------------------------------------------------------------
// Fonction		: ChLibelleTrap
// Entrees		: <loc_ps8_chaine<	: chaine retourn�e
//				  <loc_u16_indice_evt> : indice evt
//				  <loc_t_valeur_evt> : valeur evt
//				  <loc_u32_info_sup1>	  : info 1
//				  <loc_u8_info_sup2> : information suppl�mentaire 2
//				  <loc_pu8_info_sup3> : info 3
//				  <loc_u8_index_langue> : index de la langue � afficher
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Procedure qui retourne en chaine de caract�re le
// libell� des �v�nements pour les traps
// -------------------------------------------------------------
void ChLibelleTrap(s8sod *loc_ps8_chaine, u16sod loc_u16_indice_evt,T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info_sup1, u8sod loc_u8_info_sup2, u8sod *loc_pu8_info_sup3, u8sod loc_u8_index_langue);

//=====================================================================================
// Fonction		: ReplayTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/12/2007 -
// Description	: Rejoue tous les traps de la table alarme
//=====================================================================================
void ReplayTrap(void);

//=====================================================================================
// Fonction		: TestCoherenceValeurTrapAvecConfig
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 07/05/2008 -
// Description	: Test la coh�rence des valeurs dans la table par
//					rapport � la configuration
//=====================================================================================
void TestCoherenceValeurTrapAvecConfig(void);

//=====================================================================================
// Fonction		: CopyStatusToCipTrap
// Entrees		: <loc_ps_trap<	: status trap 
//				: <loc_ps_elt_statustrap<	: element cip trap qui doit etre ajout� � StatutTrap
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: transfert statut des TRAPs dans cip �lement status trap
//=====================================================================================
void CopyStatusToCipTrap(S_STRUCT_STA_TRAP *loc_ps_trap, S_STRUCT_CIP_ELEMENT_STATUSTRAP *loc_ps_elt_statustrap);

//=====================================================================================
// Fonction		: EditFileStatutTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Edition du fichier statut trap
//=====================================================================================
void EditFileStatutTrap(void);

//=====================================================================================
// Fonction		: InitModule_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du module de ExecTrap
//=====================================================================================
void InitModule_ExecTrap(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/



