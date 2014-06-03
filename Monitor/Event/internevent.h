/*========================================================================*/
/* NOM DU FICHIER  : internevent.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: gestion interne des évènements			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source BE373 - SDVB200)
//BE016 11/03/2010 CM
// - Modification struture de la gestion interne des évènements
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _INTERNEVENT
#define _INTERNEVENT_EXT
#else
#define _INTERNEVENT_EXT extern
#endif

//Taille maximum de la table interne des évènements
#define	NB_MAX_INTERNAL_EVENTS	500

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//****************************************************
/* structure de définition interne des évènements	 */
//****************************************************
typedef struct 
{
	struct S_STRUCT_INTERNAL_EVENTS *ps_next;	//Pointeur sur prochain évènement pour le même index de l'évènement "type"
	S_STRUCT_STATE_EVENT	s_statut;		//Statut d'un évènement
	
}S_STRUCT_INTERNAL_EVENTS;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: RazOneAlarmeMemorisee
// Entrees		: <loc_u16_index_evt> : index de l'evt
// Sortie		: <loc_u8_etat>
// Auteur		: CM - 13/02/2009 -
// Description	: Raz de l'alarme mémorisée
//=====================================================================================
void RazOneAlarmeMemorisee(u16sod loc_u16_index_evt);

//=====================================================================================
// Fonction		: RazAllAlarmesMemorisees
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: RAZ de toutes les alarmes mémorisées
//=====================================================================================
void RazAllAlarmesMemorisees(void);

//=====================================================================================
// Fonction		: RazGroupeAlarmesMemorisees
// Entrees		: <loc_u16_indice_groupe>
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: RAZ des alarmes du groupe
//=====================================================================================
void RazGroupeAlarmesMemorisees(u16sod loc_u16_indice_groupe);

//=====================================================================================
// Fonction		: MiseAJourConfigToAllStateEvt
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: Mise à jour de la config de toutes les alarmes
//=====================================================================================
void MiseAJourConfigToAllStateEvt(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: MiseAJourConfigToStateEvt
// Entrees		: <loc_u16_IndiceEvt> : indice de l'évènement
//				  >loc_ps_cfg_evt<	: structure concernant la configuration de l'évènement
// Sortie		: rien
// Auteur		: CM - 27/07/2007 -
// Description	: Mise à jour de la config des alarmes
//=====================================================================================
void MiseAJourConfigToStateEvt(u16sod loc_u16_IndiceEvt,S_STRUCT_CFG_EVENT *loc_ps_cfg_evt);

//=====================================================================================
// Fonction		: u16SearchFreeLstStatusEvent
// Entrees		: rien
// Sortie		: <loc_u16_index>
// Auteur		: CM - 03/10/2007 -
// Description	: recherche dans s_statevent[] une position disponible
//					dans la zone dynamique
//=====================================================================================
u16sod u16SearchFreeLstStatusEvent(void);

//=====================================================================================
// Fonction		: u8AddLst_StatusEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  <loc_u32_info1>	  : info 1
//				  <loc_u8_info2>	  : info 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u16_sizeinfo3>  : taille du tableau défini par info 3
//				  >loc_pps_stat_event_retourne< : adresse du nouveau pointeur
// Sortie		: <loc_u8_result> : TRUE si ajout réussi, sinon FALSE
// Auteur		: CM - 10/03/2007 -
// Description	: Ajout evt (index,valeur) à la liste chainée (par
// ordre croissante sur valeur evt)
//=====================================================================================
u8sod u8AddLst_StatusEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info1, u8sod loc_u8_info2, u8sod *loc_pu8_info3, u16sod loc_u16_sizeinfo3, S_STRUCT_INTERNAL_EVENTS **loc_pps_stat_event_retourne);

//=====================================================================================
// Fonction		: u8GetStatEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  >loc_pps_stat_event_retourne< : adresse du nouveau pointeur
// Sortie		: <loc_u8_trouve> : TRUE si trouvé, sinon FALSE
// Auteur		: CM - 03/10/2007 -
// Description	: retourne le statut de l'évt associé au couple (index, valeur)
//=====================================================================================
u8sod u8GetStatEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, S_STRUCT_INTERNAL_EVENTS **loc_pps_stat_event_retourne);

//=====================================================================================
// Fonction		: u8GetStatEventMask
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  <loc_t_mask_valeur_evt>  : masque binaire valeur de l'évt
//				  >loc_pps_stat_event_retourne< : adresse du nouveau pointeur
// Sortie		: <loc_u8_trouve> : TRUE si trouvé, sinon FALSE
// Auteur		: CM - 23/04/2009 -
// Description	: retourne le statut de l'évt associé au couple (index, valeur) avec valeur Masquée
//=====================================================================================
u8sod u8GetStatEventMask(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, T_SIZE_VALEUR_EVT loc_t_mask_valeur_evt, S_STRUCT_INTERNAL_EVENTS **loc_pps_stat_event_retourne);

//=====================================================================================
// Fonction		: RegisterEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  <loc_u32_info1>	  : info 1
//				  <loc_u8_info2>	  : info 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u16_sizeinfo3>  : taille du tableau défini par info 3
//				  <loc_u8_etat>		  : état (ETAT_EVT_DEBUT, ETAT_EVT_FIN, ETAT_EVT_INFO)
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Enregistre l'évènement dans la table de statut des evts
//=====================================================================================
void RegisterEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info1, u8sod loc_u8_info2, u8sod *loc_pu8_info3, u16sod loc_u16_sizeinfo3, u8sod loc_u8_etat);

//=====================================================================================
// Fonction		: SetUseEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  <loc_u8_synthesis>  : indique si il faut mettre à jour l'evt de synthèse
// Sortie		: rien
// Auteur		: CM - 21/04/2008 -
// Description	: Permet de valider un évènement identifié par le couple (idx/valeur)
//=====================================================================================
void SetUseEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u8sod loc_u8_synthesis);

//=====================================================================================
// Fonction		: ResetUseEvent
// Entrees		: <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  <loc_u8_synthesis>  : indique si il faut dévalider l'evt de synthèse
// Sortie		: rien
// Auteur		: CM - 21/04/2008 -
// Description	: Permet de dévalider un évènement identifié par le couple (idx/valeur)
//					de façon indépendante de l'état BIT7_ETAT_CFG_VALID
//=====================================================================================
void ResetUseEvent(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u8sod loc_u8_synthesis);

//=====================================================================================
// Fonction		: SetStatutEvent
// Entrees		: <loc_ps_intern_evt_maj< : pointeur du statut de l'evt
//				  <loc_u16_index_evt> : index de l'evt
//				  <loc_t_valeur_evt>  : valeur de l'évt
//				  <loc_u32_info1>	  : info 1
//				  <loc_u8_info2>	  : info 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u16_sizeinfo3>  : taille du tableau défini par info 3
// Sortie		: rien
// Auteur		: CM - 02/02/2009 -
// Description	: Fixe index/valeur/info de l'evt
//=====================================================================================
void SetStatutEvent(S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt_maj, u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info1, u8sod loc_u8_info2, u8sod *loc_pu8_info3, u16sod loc_u16_sizeinfo3);

//=====================================================================================
// Fonction		: InitTableInternalEvent_ParDefaut
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Initialisation d'une partie de la table par défaut
//=====================================================================================
void InitTableInternalEvent_ParDefaut(void);

//=====================================================================================
// Fonction		: InitInternalEvent
// Entrees		: <loc_ps_intern_evt< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 10/07/2007 -
// Description	: Initialisation d'un status d'evt
//=====================================================================================
void InitInternalEvent(S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt);

//=====================================================================================
// Fonction		: InitModule_InternEvent
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/07/2007 -
// Description	: Initialisation du module de internevent
//=====================================================================================
void InitModule_InternEvent(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

_INTERNEVENT_EXT S_STRUCT_INTERNAL_EVENTS ps_internal_event[NB_MAX_INTERNAL_EVENTS];



