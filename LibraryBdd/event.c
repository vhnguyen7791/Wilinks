/*========================================================================*/
/* NOM DU FICHIER  : event.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010                                           */
/* Libelle         : Base de données: gestion des évènements			  */
/* Projet          : WRM100                                               */
/* Indice          : BE024                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION (base source SDBVB200 BE373)
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EVENT


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM EVENT.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_DESCRIPTION_EVT[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"numero_evt",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u16_numero_evt)},
	{	"type_evt",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u8_type_evt)},
	{	"groupe",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u8_groupe)},
	{	"valToAction",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u8_valeur_associee_action)},
	{	"fmtJdb",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u8_format_valeur_jdb)},
	{	"fmtTrap",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u8_format_valeur_trap)},
	{	"dispo",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_EVT, u8_disponible)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_DEF_STRUCT_DESCRIPTION_GROUPE[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"dispo",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_DESCRIPTION_GROUPE_EVT, u8_disponible)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_EVENT_INI[] = {
	{	"descript_evt",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_DESCRIPTION_EVT,	(u16sod)sizeof(S_STRUCT_DESCRIPTION_EVT),	NB_MAX_EVENEMENTS,	MACRO_OFFSETOF(S_STRUCT_EVENTSYSTEM, ps_description_event[0])	},
	{	"descript_group",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_DESCRIPTION_GROUPE,	(u16sod)sizeof(S_STRUCT_DESCRIPTION_GROUPE_EVT),	NB_MAX_GROUPES,	MACRO_OFFSETOF(S_STRUCT_EVENTSYSTEM, ps_description_groupe[0])	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER EVENT.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_EVENT_INI =
{
	PATH_DIR__BDD_EVT "event.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_EVENT_INI ,//pt_contenu
};

//Variable globale au module
S_STRUCT_EVENTSYSTEM			t_eventsystem;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillEventSystemFile
// Entrees		: <loc_pt_eventsystem< : pointeur sur systeme evt
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 01/03/2010 -
// Description	: Lecture du fichier système event.ini
//=====================================================================================
u8sod u8FillEventSystemFile(S_STRUCT_EVENTSYSTEM	*loc_pt_eventsystem)
{
	u8sod loc_u8_resultat;

	if(&t_eventsystem == loc_pt_eventsystem) //CONDITION: adresse identique à la variable globale
	{
		loc_u8_resultat = u8Transfert_FileToStruct(loc_pt_eventsystem, &T_DEF_FILE_EVENT_INI);
		if(FALSE == loc_u8_resultat)
		{
			MACRO_PRINTF(("u8FillEventSystemFile: KO 1 \n"));
		}
	}
	else //CONDITION: appel de la fonction erronée
	{
		MACRO_PRINTF(("u8FillEventSystemFile: KO 2 \n"));
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}/*u8FillEventSystemFile*/

//=====================================================================================
// Fonction		: u8EditEventSystemFile
// Entrees		: <loc_pt_eventsystem< : pointeur sur systeme evt
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 01/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditEventSystemFile(S_STRUCT_EVENTSYSTEM	*loc_pt_eventsystem)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_pt_eventsystem, &T_DEF_FILE_EVENT_INI);

	return loc_u8_resultat;
}/*u8EditEventSystemFile*/


//=====================================================================================
// Fonction		: u8TestEvenementValide
// Entrees		: <loc_u16_indice_evt>
// Sortie		: <loc_i_resultat> : TRUE valide / FALSE non valide
// Auteur		: CM - 29/06/2007 -
// Description	: Test si evt valide
//=====================================================================================
u8sod u8TestEvenementValide(u16sod loc_u16_indice_evt)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(loc_u16_indice_evt < NB_MAX_EVENEMENTS)
	{
		if(	(NUM_EVT_INTERDIT != S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice_evt].u16_numero_evt)
		  )//CONDITION:EVT valide	
		{
			loc_u8_resultat = TRUE;
		}
	}

	return(loc_u8_resultat);		
}/*u8TestEvenementValide*/

//=====================================================================================
// Fonction		: u8TestIfLogFilter
// Entrees		: <loc_ps_config< : configuration de l'équipement
// Sortie		: <loc_i_resultat> : TRUE jdb filtré / FALSE jdb non filtré
// Auteur		: CM - 02/07/2007 -
// Description	: retourne si le jdb est filtré
//=====================================================================================
u8sod u8TestIfLogFilter(S_STRUCT_CONFIGURATION	*loc_ps_config)
{
	u8sod loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;

	loc_u8_resultat = FALSE;	//INIT

	//Filtre sur les évènements
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{
			loc_s_cfg_evt = loc_ps_config->s_tabevt.s_event[loc_u16_indEvt];
			if(FALSE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_FILTRE_JDB))
			{
				loc_u8_resultat = TRUE;
				loc_u16_i = NB_MAX_EVENEMENTS+1;	//on sort
			}
		}
	}
	
	return(loc_u8_resultat);		
}/*u8TestIfLogFilter*/

//=====================================================================================
// Fonction		: u16GetFirstIndiceEvenementValide
// Entrees		: rien
// Sortie		: <loc_us_premier_indice> : nouvel indice sinon US_INDICE_NON_TROUVE
// Auteur		: CM - 31/08/2005 -
// Description	: Recherche le premier indice d'evt valide
//=====================================================================================
u16sod u16GetFirstIndiceEvenementValide(void)
{
	u16sod	loc_u16_i;
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_premier_indice;

	loc_u8_resultat = FALSE;	//INIT

	for (loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if(TRUE == u8TestEvenementValide(loc_u16_i))
		{
			loc_u8_resultat = TRUE;	//TROUVE
			loc_u16_premier_indice = (u16sod)loc_u16_i;
			loc_u16_i = NB_MAX_EVENEMENTS + 1;	//on sort
		}
	}
	if (FALSE == loc_u8_resultat)	//CONDITION: pas d'indice valide
	{
		loc_u16_premier_indice = US_INDICE_NON_TROUVE;
	}

	return(loc_u16_premier_indice);		
}/*u16GetFirstIndiceEvenementValide*/

//=====================================================================================
// Fonction		: u16GetNextIndiceEvenementValide
// Entrees		: <loc_u16_indice_evt>
// Sortie		: <loc_u16_indice_evt_next> : nouvel indice sinon US_INDICE_NON_TROUVE
// Auteur		: CM - 31/08/2005 -
// Description	: Recherche de l'indice du prochain evt valide
//=====================================================================================
u16sod u16GetNextIndiceEvenementValide(u16sod loc_u16_indice_evt)
{
	u16sod	loc_u16_i;
	u16sod	loc_u16_indice_evt_next;

	loc_u16_indice_evt_next = US_INDICE_NON_TROUVE; //INIT

	for (loc_u16_i=(loc_u16_indice_evt+1);loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if(TRUE == u8TestEvenementValide(loc_u16_i))
		{
			loc_u16_indice_evt_next = (u16sod)loc_u16_i;
			loc_u16_i = NB_MAX_EVENEMENTS + 1;	//on sort
		}
	}
	
	return(loc_u16_indice_evt_next);		
}/*u16GetNextIndiceEvenementValide*/

//=====================================================================================
// Fonction		: u16GetPreviousIndiceEvenementValide
// Entrees		: <loc_u16_indice_evt>
// Sortie		: <loc_u16_indice_evt_previous> : nouvel indice sinon US_INDICE_NON_TROUVE
// Auteur		: CM - 19/09/2005 -
// Description	: Recherche de l'indice du précedent evt valide
//=====================================================================================
u16sod u16GetPreviousIndiceEvenementValide(u16sod loc_u16_indice_evt)
{
	s16sod	loc_s16_i;
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_indice_evt_previous;

	loc_u8_resultat = FALSE;	//INIT

	if(loc_u16_indice_evt != 0)
	{
		for (loc_s16_i=(s16sod)(loc_u16_indice_evt-1);
			 ((loc_s16_i>=0)&&(FALSE == loc_u8_resultat));
			 loc_s16_i--)
		{
			if(TRUE == u8TestEvenementValide((u16sod)loc_s16_i))
			{
				loc_u8_resultat = TRUE;	//TROUVE
				loc_u16_indice_evt_previous = (u16sod)loc_s16_i;
			}
		}
	}

	if (FALSE == loc_u8_resultat)	//CONDITION: pas d'indice valide
	{
		loc_u16_indice_evt_previous = US_INDICE_NON_TROUVE;
	}

	return(loc_u16_indice_evt_previous);		
}/*GetPreviousIndiceEvenementValide*/

//=====================================================================================
// Fonction		: u16RechercheIndiceEvt
// Entrees		: <loc_u16_numEvt>
// Sortie		: <loc_u16_index> : index
//					retourne US_INDICE_NON_TROUVE si pas trouvé
// Auteur		: CM - 01/04/2004 -
// Description	: Retourne index de l'événement avec le numéro évenement
//=====================================================================================
u16sod u16RechercheIndiceEvt(u16sod loc_u16_numEvt)
{
	u16sod	loc_u16_k;
	u16sod	loc_u16_index;

	loc_u16_index = US_INDICE_NON_TROUVE; //INIT

	for (loc_u16_k=0;loc_u16_k<NB_MAX_EVENEMENTS;loc_u16_k++)
	{
		if (loc_u16_numEvt == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_k].u16_numero_evt)	//CONDITION: Numéro Evt identique
		{
			loc_u16_index = loc_u16_k;
			loc_u16_k = NB_MAX_EVENEMENTS+1;	//on sort
		}
	}

	return loc_u16_index;
	
}/*u16RechercheIndiceEvt*/

//=====================================================================================
// Fonction		: tConvertValeurToJdb
// Entrees		: <loc_u16_index_evt>	: index de l'évènement
//				  <loc_t_valeur_evt>	: valeur de l'evt 
// Sortie		: <loc_t_valeur_evt_jdb> : format de valeur jdb
// Auteur		: CM - 05/03/2010 -
// Description	: retourne la valeur du jdb de l'évènement
//=====================================================================================
T_SIZE_VALEUR_EVT tConvertValeurToJdb(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt)
{
	T_SIZE_VALEUR_EVT	loc_t_valeur_evt_jdb;

	loc_t_valeur_evt_jdb = 0;	//INIT

	if(loc_u16_index_evt < NB_MAX_EVENEMENTS)
	{
		loc_t_valeur_evt_jdb = loc_t_valeur_evt;	//INIT
	}
	
	return (loc_t_valeur_evt_jdb);
}/*tConvertValeurToJdb*/

//=====================================================================================
// Fonction		: tConvertValeurToTrap
// Entrees		: <loc_u16_index_evt>	: index de l'évènement
//				  <loc_t_valeur_evt>	: valeur de l'evt 
// Sortie		: <loc_t_valeur_evt_trap> : format de valeur trap
// Auteur		: CM - 05/03/2010 -
// Description	: retourne la valeur du trap de l'évènement
//=====================================================================================
T_SIZE_VALEUR_EVT tConvertValeurToTrap(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt)
{
	T_SIZE_VALEUR_EVT loc_t_valeur_evt_trap;

	loc_t_valeur_evt_trap = 0;	//INIT

	if(loc_u16_index_evt < NB_MAX_EVENEMENTS)
	{
		loc_t_valeur_evt_trap = loc_t_valeur_evt; 
	}

	return (loc_t_valeur_evt_trap);
}/*tConvertValeurToTrap*/

//============================================================================
// Fonction		: SetGroupeEvtDisponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 26/05/2008 -
// Description	: force disponibilité du groupe
//============================================================================
void SetGroupeEvtDisponible(u16sod loc_u16_indice_groupe)
{
	t_eventsystem.ps_description_groupe[loc_u16_indice_groupe].u8_disponible = TRUE;
}/*SetGroupeEvtDisponible*/

//============================================================================
// Fonction		: ResetGroupeEvtDisponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 26/05/2008 -
// Description	: annule disponibilité du groupe
//============================================================================
void ResetGroupeEvtDisponible(u16sod loc_u16_indice_groupe)
{
	t_eventsystem.ps_description_groupe[loc_u16_indice_groupe].u8_disponible = FALSE;
}/*ResetGroupeEvtDisponible*/
   
//============================================================================
// Fonction		: u8TestGroupeEvtDisponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: <loc_u8_resultat> : TRUE si dispo, sinon FALSE
// Auteur		: CM - 26/05/2008 -
// Description	: retourne si groupe est disponible
//============================================================================
u8sod u8TestGroupeEvtDisponible(u16sod loc_u16_indice_groupe)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(loc_u16_indice_groupe < NB_MAX_GROUPES)
	{
		loc_u8_resultat = t_eventsystem.ps_description_groupe[loc_u16_indice_groupe].u8_disponible;
	}

	return loc_u8_resultat;
}/*u8TestGroupeEvtDisponible*/

//============================================================================
// Fonction		: SetEventDisponible
// Entrees		: <loc_u16_indice_evt> : index de l'évènement
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: force disponibilité de l'évènement
//============================================================================
void SetEventDisponible(u16sod loc_u16_indice_evt)
{
	t_eventsystem.ps_description_event[loc_u16_indice_evt].u8_disponible = TRUE;
}/*SetEventDisponible*/

//============================================================================
// Fonction		: ResetEventDisponible
// Entrees		: <loc_u16_indice_evt> : index de l'évènement
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: annule disponibilité de l'évènement
//============================================================================
void ResetEventDisponible(u16sod loc_u16_indice_evt)
{
	t_eventsystem.ps_description_event[loc_u16_indice_evt].u8_disponible = FALSE;
}/*ResetEventDisponible*/

//============================================================================
// Fonction		: u8TestEventDisponible
// Entrees		: <loc_u16_indice_evt> : index de l'évènement
// Sortie		: <loc_u8_resultat> : TRUE si dispo, sinon FALSE
// Auteur		: CM - 22/05/2008 -
// Description	: retourne si l'évt est disponible
//============================================================================
u8sod u8TestEventDisponible(u16sod loc_u16_indice_evt)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT
	
	if(loc_u16_indice_evt < NB_MAX_EVENEMENTS)
	{
		loc_u8_resultat = t_eventsystem.ps_description_event[loc_u16_indice_evt].u8_disponible;
	}

	return loc_u8_resultat;
}/*u8TestEventDisponible*/

//============================================================================
// Fonction		: Set_Groupe_And_Events_Disponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 13/08/2008 -
// Description	: force disponibilité du groupe et de ses évènements
//============================================================================
void Set_Groupe_And_Events_Disponible(u16sod loc_u16_indice_groupe)
{
	u16sod	loc_u16_i;
	SetGroupeEvtDisponible(loc_u16_indice_groupe);

	for (loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if(TRUE == u8TestEvenementValide(loc_u16_i))
		{
			if(loc_u16_indice_groupe == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u8_groupe)
			{
				SetEventDisponible(loc_u16_i);
			}
		}
	}
	
}/*Set_Groupe_And_Events_Disponible*/

//============================================================================
// Fonction		: Reset_Groupe_And_Events_Disponible
// Entrees		: <loc_u16_indice_groupe> : index du groupe
// Sortie		: rien
// Auteur		: CM - 13/08/2008 -
// Description	: annule disponibilité du groupe et de ses évènements
//============================================================================
void Reset_Groupe_And_Events_Disponible(u16sod loc_u16_indice_groupe)
{
	u16sod	loc_u16_i;
	ResetGroupeEvtDisponible(loc_u16_indice_groupe);

	for (loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if(TRUE == u8TestEvenementValide(loc_u16_i))
		{
			if(loc_u16_indice_groupe == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u8_groupe)
			{
				ResetEventDisponible(loc_u16_i);
			}
		}
	}

}/*Reset_Groupe_And_Events_Disponible*/

//=====================================================================================
// Fonction		: ptGetPtrEventSystem
// Entrees		: rien
// Sortie		: <loc_pt_return< : adresse de la variable globale eventsystem
// Auteur		: CM - 01/03/2010 -
// Description	: Retourne l'adresse de la variable globale eventsystem
//=====================================================================================
S_STRUCT_EVENTSYSTEM* ptGetPtrEventSystem(void)
{
	S_STRUCT_EVENTSYSTEM *loc_pt_return;

	loc_pt_return = &t_eventsystem;
	
	return loc_pt_return;
}/*ptGetPtrEventSystem*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitBDD_Event
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Initialisation de la base de données event
//=====================================================================================
void InitBDD_Event(void)
{
	u16sod loc_u16_i;
	s32sod	loc_s32_sem; 	

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	
	memset(&t_eventsystem,'\0',sizeof(S_STRUCT_EVENTSYSTEM)); //INIT
	
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		t_eventsystem.ps_description_event[loc_u16_i] = S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i];
	}

	for(loc_u16_i=0;loc_u16_i<NB_MAX_GROUPES;loc_u16_i++)
	{
		t_eventsystem.ps_description_groupe[loc_u16_i] = S_DESCRIPTION_GROUPE_EVT_PAR_DEFAUT[loc_u16_i];
	}

	u8EditEventSystemFile(&t_eventsystem); //INIT
	
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_Event*/

//=====================================================================================
// Fonction		: InitModule_Event
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/06/2007 -
// Description	: Initialisation du module de Event
//=====================================================================================
void InitModule_Event(void)
{
	memset(&t_eventsystem, 0, sizeof(S_STRUCT_EVENTSYSTEM)); //INIT

}/*InitModule_Event*/

