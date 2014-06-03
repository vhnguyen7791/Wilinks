/*========================================================================*/
/* NOM DU FICHIER  : exp_event.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : Base de données: exploitation des évènements		  */
/* Projet          : WRM100                                               */
/* Indice          : BE016                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE016 11/03/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXP_EVENT
#define _EXP_EVENT_EXT
#else
#define _EXP_EVENT_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillExploitEventsGlobalFile
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillExploitEventsGlobalFile(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events);

//=====================================================================================
// Fonction		: u8EditExploitEventsGlobalFile
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditExploitEventsGlobalFile(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events);

//=====================================================================================
// Fonction		: u8GetEtatAlarme
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
//				: <loc_u16_index_evt> : index de l'evt
// Sortie		: <loc_u8_etat>
// Auteur		: CM - 11/03/2010 -
// Description	: Retourne l'état de l'alarme (synthèse de l'evt)
//=====================================================================================
u8sod u8GetEtatAlarme(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events, u16sod loc_u16_index_evt);

//=====================================================================================
// Fonction		: u8GetEtatGroupeAlarme
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
//				: <loc_u8_groupe_alarme> : index du groupe d'alarmes
// Sortie		: <loc_u8_etat>
// Auteur		: CM - 10/07/2007 -
// Description	: Retourne l'état du groupe d'alarme
//=====================================================================================
u8sod u8GetEtatGroupeAlarme(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events, u8sod loc_u8_groupe_alarme);

//=====================================================================================
// Fonction		: InitStateEvt
// Entrees		: <loc_ps_state_evt< : pointeur sur un évènement exploit
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation statut d'un évènement
//=====================================================================================
void InitStateEvt(S_STRUCT_STATE_EVENT *loc_ps_state_evt);

//=====================================================================================
// Fonction		: InitBDD_Exp_Event
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Initialisation de la base de données de http
//=====================================================================================
void InitBDD_Exp_Event(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events);

//=====================================================================================
// Fonction		: InitModule_Exp_Event
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Initialisation du module de exp_event
//=====================================================================================
void InitModule_Exp_Event(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




