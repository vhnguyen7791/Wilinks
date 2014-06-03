/*========================================================================*/
/* NOM DU FICHIER  : exp_event.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : Base de données: exploitation des évènements		  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE016 11/03/2010 CM
// - CREATION
//BE017 12/03/2010 CM
// - Optimisation contenu du fichier evt_global.exp
//BE037 06/07/2010 CM
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
// - Ajout gestion des évènements spécifiques à l'équipement
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EXP_EVENT


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER EVT_GLOBAL.EXP
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_STATEVT[] = {
	{	"etat",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATE_EVENT, u8_etat_evt)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_EVTGLOBAL_EXP[] = {
	{	"date",			FTYPVAL_DATE,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, s_date_dernier_reset)	},
	{	"evt000",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT000_AL_SYNTHESE_1])},
	{	"evt001",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT001_DEFAUT_EQUIPEMENT])},
	{	"evt002",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT002_AL_TEMPERATURE])},
	{	"evt003",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT003_AL_ETHERNET_LAN_1])},
	{	"evt004",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT004_AL_ETHERNET_LAN_2])},
	{	"evt005",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT005_AL_NIVEAU_RECU])},
	{	"evt006",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT006_STATION_NON_CONNECTEE])},
	{	"evt007",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT007_PROBLEME_CONFIGURATION])},
	{	"evt010",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE])},
#if TEST_DEBUG_EVENT
//d: ------------- debug -----------------------------------------------
	{	"evt177",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT177_RESERVE])		},
	{	"evt178",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT178_RESERVE])		},
	{	"evt179",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_STATEVT,	(u16sod)sizeof(S_STRUCT_STATE_EVENT),	0,	MACRO_OFFSETOF(S_STRUCT_EXPLOIT_EVENTS, ps_statut[EVT179_RESERVE])		},
//f: ------------- debug -----------------------------------------------
#endif
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER EVT_GLOBAL.EXP
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_EVTGLOBAL_EXP =
{
	PATH_DIR__BDD_EXPLOIT "evt_global.exp", //ps8_path_file
	DEFFILE_TYPE_EXPLOIT, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_EVTGLOBAL_EXP ,//pt_contenu
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillExploitEventsGlobalFile
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillExploitEventsGlobalFile(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_exp_events, &T_DEF_FILE_EVTGLOBAL_EXP);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillExploitEventsGlobalFile KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillExploitEventsGlobalFile*/

//=====================================================================================
// Fonction		: u8EditExploitEventsGlobalFile
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditExploitEventsGlobalFile(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_exp_events, &T_DEF_FILE_EVTGLOBAL_EXP);

	return loc_u8_resultat;
}/*u8EditExploitEventsGlobalFile*/

//=====================================================================================
// Fonction		: u8GetEtatAlarme
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
//				: <loc_u16_index_evt> : index de l'evt
// Sortie		: <loc_u8_etat>
// Auteur		: CM - 11/03/2010 -
// Description	: Retourne l'état de l'alarme (synthèse de l'evt)
//=====================================================================================
u8sod u8GetEtatAlarme(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events, u16sod loc_u16_index_evt)
{
	u8sod	loc_u8_etat;

	loc_u8_etat = 0x00;	//INIT

	if(loc_u16_index_evt<NB_MAX_EVENEMENTS)
	{
		if(TRUE == u8TestEvenementValide(loc_u16_index_evt))//CONDITION: Evt OK
		{
			loc_u8_etat = loc_ps_exp_events->ps_statut[loc_u16_index_evt].u8_etat_evt;
		}
	}

	return loc_u8_etat;
}/*u8GetEtatAlarme*/

//=====================================================================================
// Fonction		: u8GetEtatGroupeAlarme
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
//				: <loc_u8_groupe_alarme> : index du groupe d'alarmes
// Sortie		: <loc_u8_etat>
// Auteur		: CM - 10/07/2007 -
// Description	: Retourne l'état du groupe d'alarme
//=====================================================================================
u8sod u8GetEtatGroupeAlarme(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events, u8sod loc_u8_groupe_alarme)
{
	u8sod	loc_u8_etat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;

	loc_u8_etat = 0x00;	//INIT

	switch(loc_u8_groupe_alarme)
	{
		default:
			for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
			{
				loc_u16_indEvt = loc_u16_i;
				if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
				{
					if(loc_u8_groupe_alarme == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_groupe)
					{
						loc_u8_etat |= loc_ps_exp_events->ps_statut[loc_u16_indEvt].u8_etat_evt;
					}
				}
			}
			break;
	}

	return loc_u8_etat;
}/*u8GetEtatGroupeAlarme*/



 /*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitStateEvt
// Entrees		: <loc_ps_state_evt< : pointeur sur un évènement exploit
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation statut d'un évènement
//=====================================================================================
void InitStateEvt(S_STRUCT_STATE_EVENT *loc_ps_state_evt)
{
	loc_ps_state_evt->u16_index_evt = NUM_EVT_INTERDIT; //RAZ
	loc_ps_state_evt->t_valeur_evt = 0; //RAZ
	loc_ps_state_evt->u8_etat_evt = 0; //RAZ
	loc_ps_state_evt->u_info_sup1.u32_term = 0; //RAZ
	loc_ps_state_evt->u8_info_sup2 = 0; //RAZ
	memset(loc_ps_state_evt->pu8_tab_info_sup3, 0, TAILLE_MAX_TAB_INFO_SUP3);  //RAZ
	loc_ps_state_evt->u8_syst_evt = (1 << BIT0_SYST_EVT_USED);	//RAZ
}/*InitStateEvt*/

//=====================================================================================
// Fonction		: InitBDD_Exp_Event
// Entrees		: <loc_ps_exp_events< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Initialisation de la base de données de http
//=====================================================================================
void InitBDD_Exp_Event(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events)
{
	s32sod loc_s32_sem;
	u16sod loc_u16_i;

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore

	memset(loc_ps_exp_events,'\0',sizeof(S_STRUCT_EXPLOIT_EVENTS)); //INIT

	InitStructDate(&loc_ps_exp_events->s_date_dernier_reset); //INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		InitStateEvt(&loc_ps_exp_events->ps_statut[loc_u16_i]); //INIT
	}


	u8EditExploitEventsGlobalFile(loc_ps_exp_events); //INIT
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

}/*InitBDD_Exp_Event*/


//=====================================================================================
// Fonction		: InitModule_Exp_Event
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Initialisation du module de exp_event
//=====================================================================================
void InitModule_Exp_Event(void)
{

}/*InitModule_Exp_Event*/

