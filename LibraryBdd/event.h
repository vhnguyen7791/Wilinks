/*========================================================================*/
/* NOM DU FICHIER  : event.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010                                           */
/* Libelle         : Base de données: gestion des évènements			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
// - CREATION
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
//BE057 20/01/2011 CM
// - Ne pas afficher evenements liés à ssid secondaire  sur WRM100-ABG
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout nouveaux évènements liés au DFS
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EVENT
#define _EVENT_EXT
#else
#define _EVENT_EXT extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillEventSystemFile
// Entrees		: <loc_pt_eventsystem< : pointeur sur systeme evt
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 01/03/2010 -
// Description	: Lecture du fichier système event.ini
//=====================================================================================
u8sod u8FillEventSystemFile(S_STRUCT_EVENTSYSTEM *loc_pt_eventsystem);

//=====================================================================================
// Fonction		: u8EditEventSystemFile
// Entrees		: <loc_pt_eventsystem< : pointeur sur systeme evt
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 01/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditEventSystemFile(S_STRUCT_EVENTSYSTEM	*loc_pt_eventsystem);

//=====================================================================================
// Fonction		: u8TestEvenementValide
// Entrees		: <loc_u16_indice_evt>
// Sortie		: <loc_i_resultat> : TRUE valide / FALSE non valide
// Auteur		: CM - 29/06/2007 -
// Description	: Test si evt valide
//=====================================================================================
u8sod u8TestEvenementValide(u16sod loc_u16_indice_evt);

//=====================================================================================
// Fonction		: u8TestIfLogFilter
// Entrees		: <loc_ps_config< : configuration de l'équipement
// Sortie		: <loc_i_resultat> : TRUE jdb filtré / FALSE jdb non filtré
// Auteur		: CM - 02/07/2007 -
// Description	: retourne si le jdb est filtré
//=====================================================================================
u8sod u8TestIfLogFilter(S_STRUCT_CONFIGURATION	*loc_ps_config);

//=====================================================================================
// Fonction		: u16GetFirstIndiceEvenementValide
// Entrees		: rien
// Sortie		: <loc_us_premier_indice> : nouvel indice sinon US_INDICE_NON_TROUVE
// Auteur		: CM - 31/08/2005 -
// Description	: Recherche le premier indice d'evt valide
//=====================================================================================
u16sod u16GetFirstIndiceEvenementValide(void);

//=====================================================================================
// Fonction		: u16GetNextIndiceEvenementValide
// Entrees		: <loc_u16_indice_evt>
// Sortie		: <loc_u16_indice_evt_next> : nouvel indice sinon US_INDICE_NON_TROUVE
// Auteur		: CM - 31/08/2005 -
// Description	: Recherche de l'indice du prochain evt valide
//=====================================================================================
u16sod u16GetNextIndiceEvenementValide(u16sod loc_u16_indice_evt);

//=====================================================================================
// Fonction		: u16GetPreviousIndiceEvenementValide
// Entrees		: <loc_u16_indice_evt>
// Sortie		: <loc_u16_indice_evt_previous> : nouvel indice sinon US_INDICE_NON_TROUVE
// Auteur		: CM - 19/09/2005 -
// Description	: Recherche de l'indice du précedent evt valide
//=====================================================================================
u16sod u16GetPreviousIndiceEvenementValide(u16sod loc_u16_indice_evt);

//=====================================================================================
// Fonction		: u16RechercheIndiceEvt
// Entrees		: <loc_u16_numEvt>
// Sortie		: <loc_u16_index> : index
//					retourne US_INDICE_NON_TROUVE si pas trouvé
// Auteur		: CM - 01/04/2004 -
// Description	: Retourne index de l'événement avec le numéro évenement
//=====================================================================================
u16sod u16RechercheIndiceEvt(u16sod loc_u16_numEvt);

//=====================================================================================
// Fonction		: tConvertValeurToJdb
// Entrees		: <loc_u16_index_evt>	: index de l'évènement
//				  <loc_t_valeur_evt>	: valeur de l'evt 
// Sortie		: <loc_t_valeur_evt_jdb> : format de valeur jdb
// Auteur		: CM - 05/03/2010 -
// Description	: retourne la valeur du jdb de l'évènement
//=====================================================================================
T_SIZE_VALEUR_EVT tConvertValeurToJdb(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt);

//=====================================================================================
// Fonction		: tConvertValeurToTrap
// Entrees		: <loc_u16_index_evt>	: index de l'évènement
//				  <loc_t_valeur_evt>	: valeur de l'evt 
// Sortie		: <loc_t_valeur_evt_trap> : format de valeur trap
// Auteur		: CM - 05/03/2010 -
// Description	: retourne la valeur du trap de l'évènement
//=====================================================================================
T_SIZE_VALEUR_EVT tConvertValeurToTrap(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt);

//============================================================================
// Fonction		: SetGroupeEvtDisponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 26/05/2008 -
// Description	: force disponibilité du groupe
//============================================================================
void SetGroupeEvtDisponible(u16sod loc_u16_indice_groupe);

//============================================================================
// Fonction		: ResetGroupeEvtDisponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 26/05/2008 -
// Description	: annule disponibilité du groupe
//============================================================================
void ResetGroupeEvtDisponible(u16sod loc_u16_indice_groupe);

//============================================================================
// Fonction		: u8TestGroupeEvtDisponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: <loc_u8_resultat> : TRUE si dispo, sinon FALSE
// Auteur		: CM - 26/05/2008 -
// Description	: retourne si groupe est disponible
//============================================================================
u8sod u8TestGroupeEvtDisponible(u16sod loc_u16_indice_groupe);

//============================================================================
// Fonction		: SetEventDisponible
// Entrees		: <loc_u16_indice_evt> : index de l'évènement
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: force disponibilité de l'évènement
//============================================================================
void SetEventDisponible(u16sod loc_u16_indice_evt);

//============================================================================
// Fonction		: ResetEventDisponible
// Entrees		: <loc_u16_indice_evt> : index de l'évènement
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: annule disponibilité de l'évènement
//============================================================================
void ResetEventDisponible(u16sod loc_u16_indice_evt);

//============================================================================
// Fonction		: u8TestEventDisponible
// Entrees		: <loc_u16_indice_evt> : index de l'évènement
// Sortie		: <loc_u8_resultat> : TRUE si dispo, sinon FALSE
// Auteur		: CM - 22/05/2008 -
// Description	: retourne si l'évt est disponible
//============================================================================
u8sod u8TestEventDisponible(u16sod loc_u16_indice_evt);

//============================================================================
// Fonction		: Set_Groupe_And_Events_Disponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 13/08/2008 -
// Description	: force disponibilité du groupe et de ses évènements
//============================================================================
void Set_Groupe_And_Events_Disponible(u16sod loc_u16_indice_groupe);

//============================================================================
// Fonction		: Reset_Groupe_And_Events_Disponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 13/08/2008 -
// Description	: annule disponibilité du groupe et de ses évènements
//============================================================================
void Reset_Groupe_And_Events_Disponible(u16sod loc_u16_indice_groupe);

//=====================================================================================
// Fonction		: ptGetPtrEventSystem
// Entrees		: rien
// Sortie		: <loc_pt_return< : adresse de la variable globale eventsystem
// Auteur		: CM - 01/03/2010 -
// Description	: Retourne l'adresse de la variable globale eventsystem
//=====================================================================================
S_STRUCT_EVENTSYSTEM* ptGetPtrEventSystem(void);

//=====================================================================================
// Fonction		: InitBDD_Event
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Initialisation de la base de données event
//=====================================================================================
void InitBDD_Event(void);

//=====================================================================================
// Fonction		: InitModule_Event
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/06/2007 -
// Description	: Initialisation du module de Event
//=====================================================================================
void InitModule_Event(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


#ifdef _EVENT
const S_STRUCT_DESCRIPTION_EVT S_DESCRIPTION_EVENT_PAR_DEFAUT[NB_MAX_EVENEMENTS] =
{
	{
		EVT000_AL_SYNTHESE_1,
		1,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT001_DEFAUT_EQUIPEMENT,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT002_AL_TEMPERATURE,
		3,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT003_AL_ETHERNET_LAN_1,
		4,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT004_AL_ETHERNET_LAN_2,
		5,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT005_AL_NIVEAU_RECU,
		6,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT006_STATION_NON_CONNECTEE,
		7,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT007_PROBLEME_CONFIGURATION,
		8,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_JDB|V_TRAP,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE,
#ifdef _WRM100_ABG_SELECT
		0,
#else //_WRM100_N_SELECT
		9,
#endif
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT009_RETOUR_SUR_SSID_PRIMAIRE,
#ifdef _WRM100_ABG_SELECT
		0,
#else //_WRM100_N_SELECT
		10,
#endif
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE,
		11,
		TYPE_EVT_ALARME,
		GROUPE_AL_SYSTEME,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	
	{
		EVT011_RADAR_DETECTE_SUR_CANAL,
#ifdef _WRM100_ABG_SELECT
		0,
#else //_WRM100_N_SELECT
		12,
#endif
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT012_BASCULEMENT_VERS_CANAL,
#ifdef _WRM100_ABG_SELECT
		0,
#else //_WRM100_N_SELECT
		13,
#endif
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT013_CONNEXION_STATION,
		14,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_JDB|V_TRAP,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT014_DECONNEXION_STATION,
		15,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_JDB|V_TRAP,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT015_CONNEXION_ACCESS_POINT,
		16,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		FV_NULL,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT016_DECONNEXION_ACCESS_POINT,
		17,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		FV_NULL,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT017_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT018_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT019_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT020_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT021_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT022_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT023_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT024_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT025_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT026_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT027_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT028_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT029_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT030_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT031_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT032_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT033_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT034_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT035_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT036_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT037_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT038_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT039_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT040_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT041_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT042_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT043_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT044_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT045_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT046_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT047_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT048_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT049_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT050_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT051_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT052_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT053_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT054_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT055_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT056_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT057_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT058_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT059_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT060_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT061_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT062_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT063_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT064_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT065_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT066_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT067_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT068_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT069_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT070_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT071_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT072_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT073_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT074_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT075_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT076_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT077_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT078_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT079_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT080_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT081_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT082_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT083_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT084_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT085_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT086_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT087_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT088_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT089_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT090_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT091_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT092_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT093_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT094_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT095_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT096_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT097_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT098_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT099_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT100_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT101_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT102_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT103_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT104_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT105_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT106_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT107_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT108_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT109_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT110_JOURNAL_BORD_EFFACE,
		1000,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT111_INF_RAZ_ALARMES_MEMO,
		1001,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT112_EVOLUTION_CONFIGURATION,
		1002,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT113_ORDRE_RESET_TELECOMMANDE,
		1003,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT114_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT115_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT116_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT117_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT118_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT119_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT120_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT121_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT122_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT123_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT124_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT125_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT126_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT127_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT128_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT129_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT130_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT131_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT132_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT133_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT134_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT135_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT136_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT137_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT138_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT139_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT140_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT141_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT142_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT143_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT144_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT145_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT146_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT147_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT148_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT149_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT150_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT151_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT152_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_JDB,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT153_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT154_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT155_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT156_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT157_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT158_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT159_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT160_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT161_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT162_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT163_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT164_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT165_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT166_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT167_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT168_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT169_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT170_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT171_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT172_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT173_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT174_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT175_INF_EQUIPEMENT_ON,
		10001,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT176_INF_SIGNE_DE_VIE,
		10004,
		TYPE_EVT_INFO,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
#if TEST_DEBUG_EVENT
//d: ------------- debug -----------------------------------------------
	{
		EVT177_RESERVE,
		10111,
		TYPE_EVT_ALARME,
		GROUPE_AL_DEBUG,
		V_JDB|V_TRAP,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT178_RESERVE,
		10122,
		TYPE_EVT_ALARME,
		GROUPE_AL_DEBUG,
		V_JDB|V_TRAP,	//u8_valeur_associee_action
		FV_AUTRES,	//u8_format_valeur_jdb
		FV_AUTRES,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},
	{
		EVT179_RESERVE,
		10123,
		TYPE_EVT_ALARME,
		GROUPE_AL_DEBUG,
		V_NO_ACTION,//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		TRUE,		//u8_disponible
	},	
//f: ------------- debug -----------------------------------------------
#else
	{
		EVT177_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT178_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,	//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},
	{
		EVT179_RESERVE,
		0,
		TYPE_EVT_INCONNU,
		GROUPE_AL_NOT_USED,
		V_NO_ACTION,//u8_valeur_associee_action
		FV_NULL,	//u8_format_valeur_jdb
		FV_NULL,	//u8_format_valeur_trap
		FALSE,		//u8_disponible
	},	//FIN
#endif
		
};
#else
_EVENT_EXT S_STRUCT_DESCRIPTION_EVT S_DESCRIPTION_EVENT_PAR_DEFAUT[NB_MAX_EVENEMENTS];
#endif

#ifdef _EVENT
const S_STRUCT_DESCRIPTION_GROUPE_EVT S_DESCRIPTION_GROUPE_EVT_PAR_DEFAUT[NB_MAX_GROUPES] =
{
	//	u16_index_groupe			u8_disponible	
	{	GROUPE_AL_SYSTEME,				FALSE,		},	//GROUPE_AL_SYSTEME
#if TEST_DEBUG_EVENT
	{	GROUPE_AL_DEBUG,				TRUE,		},	//GROUPE_AL_DEBUG
#endif
	{	GROUPE_AL_NOT_USED,				FALSE,		}	//GROUPE_AL_NOT_USED
};
#else
_EVENT_EXT S_STRUCT_DESCRIPTION_GROUPE_EVT S_DESCRIPTION_GROUPE_EVT_PAR_DEFAUT[NB_MAX_GROUPES];
#endif


