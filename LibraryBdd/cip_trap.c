/*========================================================================*/
/* NOM DU FICHIER  : cip_trap.c											  */
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
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE017 12/03/2010 CM
// - Optimisation contenu des fichiers jdbpart, cip_fifojdb et cip_fifotrap
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
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
#define _CIP_TRAP

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

#define FILE_CIP_FIFOTRAP_MONITOR_LINE 	PATH_DIR__BDD_EVT "cip_fifotrap.monitor.line"
/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER CIP_FIFOTRAP.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_CIP_ELT_FIFOTRAP[] = {
	{	"date",				FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, s_date)},
	{	"idxEvt",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, u16_index_evt)},
	{	"valeur",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, t_valeur_evt)},
	{	"etat",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, u8_etat_evt)},
	{	"info1",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, u_info_sup1.u32_term)},
	{	"info2",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, u8_info_sup2)},
	{	"info3",			FTYPVAL_TABU8_HEXA,	NULL, TAILLE_MAX_TAB_INFO_SUP3,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_FIFOTRAP, pu8_tab_info_sup3)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CIP_FIFOTRAP_INI[] = {
	{	"trap",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_CIP_ELT_FIFOTRAP, (u16sod)sizeof(S_STRUCT_CIP_ELEMENT_FIFOTRAP),	0,	0}, //structure simple
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER CIP_FIFOTRAP.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_FIFOTRAP_INI =
{
	PATH_DIR__BDD_EVT "cip_fifotrap.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CIP_FIFOTRAP_INI ,//pt_contenu
};


//***************************************************************************
//**************** CONTENU DU FICHIER CIP_STATUSTRAP.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_CIP_ELT_STATUSTRAP[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"idxTable",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, u16_idx_table)},
	{	"idxEvt",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, u16_index_evt)},
	{	"valeur",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, t_valeur_evt)},
	{	"date",				FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, s_date)},
	{	"valSnmp",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, u8_val_snmp)},
	{	"etat",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, u8_etat_evt)},
	{	"info1",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, u_info_sup1.u32_term)},
	{	"info2",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, u8_info_sup2)},
	{	"info3",			FTYPVAL_TABU8_HEXA,	NULL,	TAILLE_MAX_TAB_INFO_SUP3,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_ELEMENT_STATUSTRAP, pu8_tab_info_sup3)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CIP_STATUSTRAP_INI[] = {
	{	"statustrap",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_CIP_ELT_STATUSTRAP, (u16sod)sizeof(S_STRUCT_CIP_ELEMENT_STATUSTRAP),	1,	0},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER CIP_STATUSTRAP.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_STATUSTRAP_INI =
{
	PATH_DIR__BDD_EVT "cip_statustrap.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CIP_STATUSTRAP_INI ,//pt_contenu
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Start_CipFifoTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 04/03/2010
// Description	: Démarrage de gestion de fifo
//=====================================================================================
void Start_CipFifoTrap(void)
{
	s32sod loc_s32_sem;
	u32sod loc_u32_nbEltTrapTotal;
	//Vérification que la taille du fichier ne dépasse pas la taille max définie
	
	s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on lève le sémaphore
	loc_u32_nbEltTrapTotal = u32GetNumberLineFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file, FILE_CIP_FIFOTRAP_MONITOR_LINE);
	if(loc_u32_nbEltTrapTotal > TAILLE_MAX_CIP_ELEMENTS_FIFOTRAP)
	{
		//On supprime le fichier cip_fifotrap (original)
		u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
		//Puis on crée un fichier vide
		CmdSystem_Generique("touch %s",
							T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
		MACRO_PRINTF(("Start_CipFifoTrap: fichier TROP grand %s => PERTE TRAP \n",
					  T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file));
		
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on relache le sem

}/*Start_CipFifoTrap*/

// -------------------------------------------------------------
// Fonction		: u8AddCipFifoTrap
// Entrees		: <loc_ps_elt_fifotrap< : trap à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 02/03/2010
// Description	: cette procedure empile le trap dans le fichier cip_fifotrap
// -------------------------------------------------------------
u8sod u8AddCipFifoTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP *loc_ps_elt_fifotrap, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;

	loc_p_handle = NULL;	//INIT
	loc_u8_return = TRUE;	//INIT
	loc_u16_idx = 0;		//INIT
	loc_u8_suivant = TRUE;	//INIT

	// Ouverture du fichier 
	if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "at" )))
	{
		MACRO_PRINTF(("u8AddCipFifoTrap: Impossible de creer le fichier %s\n",
					  loc_pt_def_file->ps8_path_file));
		loc_u8_return = FALSE;
	}
	else
	{
		if(loc_pt_def_file->pt_contenu != NULL)
		{
			//Edition de la ligne "nom=valeur"
			if(FALSE == u8BddFile_WriteLine(loc_p_handle,
										  (T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
										  loc_ps_elt_fifotrap,
										  &loc_u16_idx,
										  &loc_u8_suivant)
			  )//CONDITION: Ecriture simple KO
			{
				loc_u8_return = FALSE;
			}
			
			if(FALSE == loc_u8_return)
			{
				MACRO_PRINTF(("u8AddCipFifoTrap: Erreur dans fichier %s\n",
							  loc_pt_def_file->ps8_path_file));
			}
		}
		else
		{
			loc_u8_return = FALSE;
			MACRO_PRINTF(("u8AddCipFifoTrap: Contenu INDEFINI dans fichier %s\n",
						  loc_pt_def_file->ps8_path_file));
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}
	
	return loc_u8_return;
}/*u8AddCipFifoTrap*/

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
u8sod u8ReadCipFifoTrap(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod	(*loc_func_u8Action)(S_STRUCT_CIP_ELEMENT_FIFOTRAP*), u16sod loc_u16_cpt_elt_trap_max, u16sod *loc_pu16_cpt_elt_trap_lus)
{
	S_STRUCT_CIP_ELEMENT_FIFOTRAP loc_s_elt_fifotrap;
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u8sod	loc_u8_action_avec_succes;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_isEndOfFile;

	memset(&loc_s_elt_fifotrap, 0, sizeof(S_STRUCT_CIP_ELEMENT_FIFOTRAP)); //INIT
	loc_p_handle = NULL;	//INIT
	loc_u8_return = TRUE;	//INIT
	loc_u8_action_avec_succes = TRUE;	//INIT
	loc_u16_idx = 0;		//INIT
	loc_u8_suivant = TRUE;	//INIT
	loc_u16_cpt = 0;		//INIT
	loc_u8_isEndOfFile = FALSE; //INIT

	(*loc_pu16_cpt_elt_trap_lus) = 0;	//RAZ

	// Ouverture du fichier 
	if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt" )))
	{
		MACRO_PRINTF(("u8ReadCipFifoTrap: Impossible d'ouvrir le fichier %s\n",
					  loc_pt_def_file->ps8_path_file));
		loc_u8_return = FALSE;
	}
	else
	{
		// Lecture du fichier 
		if(loc_pt_def_file->pt_contenu != NULL)
		{
			do
			{
				loc_u8_return = u8BddFile_ReadLine(loc_p_handle,
												  (T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
												  &loc_s_elt_fifotrap,
												  FALSE,
												  &loc_u8_isEndOfFile);

				if(FALSE == loc_u8_isEndOfFile) //CONDITION: Ce n'est pas la fin de fichier
				{
					if(FALSE == loc_u8_return)
					{
						MACRO_PRINTF(("u8ReadCipFifoTrap: Erreur dans fichier %s\n",
									  loc_pt_def_file->ps8_path_file));
					}
					else
					{
						if(NULL == loc_func_u8Action) //CONDITION: Fonction non présente (pour test)
						{
							printf("trap: date=%s idx=%d val=%lu etat=%d info1=%lu info2=%d\n",
								   ps8GetChDate(&loc_s_elt_fifotrap.s_date),
								   loc_s_elt_fifotrap.u16_index_evt,
								   loc_s_elt_fifotrap.t_valeur_evt,
								   loc_s_elt_fifotrap.u8_etat_evt,
								   loc_s_elt_fifotrap.u_info_sup1.u32_term,
								   loc_s_elt_fifotrap.u8_info_sup2);
						}
						else
						{
							loc_u8_action_avec_succes = loc_func_u8Action(&loc_s_elt_fifotrap);
							if(TRUE == loc_u8_action_avec_succes)
							{
								(*loc_pu16_cpt_elt_trap_lus) ++;
							}
						}
					}
				}

				loc_u16_cpt ++;

				if(loc_u16_cpt >= loc_u16_cpt_elt_trap_max) //CONDITION: on a lu suffisament de trap
				{
					loc_u16_cpt = (TAILLE_MAX_CIP_ELEMENTS_FIFOTRAP+1);	//on sort
				}
				if(TRUE == loc_u8_isEndOfFile) //CONDITION: Fin de fichier
				{
					loc_u16_cpt = (TAILLE_MAX_CIP_ELEMENTS_FIFOTRAP+1);	//on sort
				}
				
			}while( (loc_u16_cpt < TAILLE_MAX_CIP_ELEMENTS_FIFOTRAP) &&
					(TRUE == loc_u8_return) &&
					(TRUE == loc_u8_action_avec_succes)
				  );
		}
		else
		{
			loc_u8_return = FALSE;
			MACRO_PRINTF(("u8ReadCipFifoTrap: Contenu INDEFINI dans fichier %s\n",
						  loc_pt_def_file->ps8_path_file));
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u8_return;
}/*u8ReadCipFifoTrap*/

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
void EnregistreTrap(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info_sup1, u8sod loc_u8_info_sup2, u8sod *loc_pu8_info3, u8sod loc_u8_etat_evt)
{
	S_STRUCT_CIP_ELEMENT_FIFOTRAP	loc_s_elt_fifotrap;
	s32sod	loc_s32_sem;

	if(loc_u16_index_evt < NB_MAX_EVENEMENTS)
	{
		loc_s_elt_fifotrap.u16_index_evt = loc_u16_index_evt;
		loc_s_elt_fifotrap.t_valeur_evt = loc_t_valeur_evt;
		loc_s_elt_fifotrap.u8_etat_evt = loc_u8_etat_evt;
		loc_s_elt_fifotrap.u_info_sup1.u32_term = loc_u32_info_sup1;
		loc_s_elt_fifotrap.u8_info_sup2 = loc_u8_info_sup2;
		memcpy(loc_s_elt_fifotrap.pu8_tab_info_sup3, loc_pu8_info3, TAILLE_MAX_TAB_INFO_SUP3); 

		SetDate(&loc_s_elt_fifotrap.s_date, METHODE_SETDATE_MANUEL);
		
//		printf("EnregistreTrap: evt %d,%d \n",loc_u16_index_evt,loc_t_valeur_evt);

		s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on lève le sémaphore
		if(FALSE == u8AddCipFifoTrap(&loc_s_elt_fifotrap, &T_DEF_FILE_CIP_FIFOTRAP_INI))
		{
			MACRO_PRINTF(("EnregistreTrap: Erreur fifotrap idxEvt=%d\n",
						  loc_s_elt_fifotrap.u16_index_evt));
		}
		s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on relache le sem
	}
}/*EnregistreTrap*/

// -------------------------------------------------------------
// Fonction		: u8AddCipStatusTrap
// Entrees		: <loc_ps_elt_statustrap< : statut trap à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 03/03/2010
// Description	: cette procedure empile le statut trap dans le fichier cip_statustrap
// -------------------------------------------------------------
//d: BE061 10/05/2011 - Correction w@rning compilation dans appel de u8AddCipStatusTrap
//u8sod u8AddCipStatusTrap(S_STRUCT_CIP_ELEMENT_FIFOTRAP *loc_ps_elt_statustrap, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
u8sod u8AddCipStatusTrap(S_STRUCT_CIP_ELEMENT_STATUSTRAP *loc_ps_elt_statustrap, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
//f: BE061 10/05/2011 - Correction w@rning compilation dans appel de u8AddCipStatusTrap
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;

	loc_p_handle = NULL;	//INIT
	loc_u8_return = TRUE;	//INIT
	loc_u16_idx = 0;		//INIT
	loc_u8_suivant = TRUE;	//INIT

	// Ouverture du fichier 
	if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "at" )))
	{
		MACRO_PRINTF(("u8AddCipStatusTrap: Impossible de creer le fichier %s\n",
					  loc_pt_def_file->ps8_path_file));
		loc_u8_return = FALSE;
	}
	else
	{
		if(loc_pt_def_file->pt_contenu != NULL)
		{
			//Edition de la ligne "nom=valeur"
			if(FALSE == u8BddFile_WriteLine(loc_p_handle,
											(T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
											loc_ps_elt_statustrap,
											&loc_u16_idx,
											&loc_u8_suivant)
			  )//CONDITION: Ecriture simple KO
			{
				loc_u8_return = FALSE;
			}

			if(FALSE == loc_u8_return)
			{
				MACRO_PRINTF(("u8AddCipStatusTrap: Erreur dans fichier %s\n",
							  loc_pt_def_file->ps8_path_file));
			}
		}
		else
		{
			loc_u8_return = FALSE;
			MACRO_PRINTF(("u8AddCipStatusTrap: Contenu INDEFINI dans fichier %s\n",
						  loc_pt_def_file->ps8_path_file));
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u8_return;
}/*u8AddCipStatusTrap*/

// -------------------------------------------------------------
// Fonction		: u8ReadCipStatusTrap
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture du statut trap
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 03/03/2010
// Description	: cette procedure lit les statuts des traps dans le fichier cip_statustrap
// -------------------------------------------------------------
u8sod u8ReadCipStatusTrap(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod (*loc_func_u8Action)(S_STRUCT_CIP_ELEMENT_STATUSTRAP*))
{
	S_STRUCT_CIP_ELEMENT_STATUSTRAP loc_s_elt_statustrap;
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u8sod	loc_u8_action_avec_succes;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_isEndOfFile;

	memset(&loc_s_elt_statustrap, 0, sizeof(S_STRUCT_CIP_ELEMENT_STATUSTRAP)); //INIT
	loc_p_handle = NULL;	//INIT
	loc_u8_return = TRUE;	//INIT
	loc_u8_action_avec_succes = TRUE;	//INIT
	loc_u16_idx = 0;		//INIT
	loc_u8_suivant = TRUE;	//INIT
	loc_u16_cpt = 0;		//INIT
	loc_u8_isEndOfFile = FALSE; //INIT

	// Ouverture du fichier 
	if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt" )))
	{
		MACRO_PRINTF(("u8ReadCipStatusTrap: Impossible d'ouvrir le fichier %s\n",
					  loc_pt_def_file->ps8_path_file));
		loc_u8_return = FALSE;
	}
	else
	{
		// Lecture du fichier 
		if(loc_pt_def_file->pt_contenu != NULL)
		{
			do
			{
				memset(&loc_s_elt_statustrap, 0, sizeof(S_STRUCT_CIP_ELEMENT_STATUSTRAP)); //RAZ
				loc_u8_return = u8BddFile_ReadLine(loc_p_handle,
													(T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
													&loc_s_elt_statustrap,
													FALSE,
													&loc_u8_isEndOfFile);

				if(FALSE == loc_u8_isEndOfFile) //CONDITION: Ce n'est pas la fin de fichier
				{
					if(FALSE == loc_u8_return)
					{
						MACRO_PRINTF(("u8ReadCipStatusTrap: Erreur dans fichier %s\n",
									  loc_pt_def_file->ps8_path_file));
					}
					else
					{
						if(NULL != loc_func_u8Action) //CONDITION: Fonction présente
						{
							loc_u8_action_avec_succes = loc_func_u8Action(&loc_s_elt_statustrap);
						}
					}
				}

				loc_u16_cpt ++;

				if(TRUE == loc_u8_isEndOfFile) //CONDITION: Fin de fichier
				{
					loc_u16_cpt = (TAILLE_MAX_TABLE_STATUSTRAP+1);	//on sort
				}

			}while( (loc_u16_cpt < TAILLE_MAX_TABLE_STATUSTRAP) &&
					(TRUE == loc_u8_return) &&
					(TRUE == loc_u8_action_avec_succes)
				  );
		}
		else
		{
			loc_u8_return = FALSE;
			MACRO_PRINTF(("u8ReadCipStatusTrap: Contenu INDEFINI dans fichier %s\n",
						  loc_pt_def_file->ps8_path_file));
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u8_return;
}/*u8ReadCipStatusTrap*/

//=====================================================================================
// Fonction		: InitBDD_Cip_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation de la base de données de cip_trap
//=====================================================================================
void InitBDD_Cip_Trap(void)
{
	s32sod	loc_s32_sem; 	

	//on supprime le fichier (si le fichier est présent)
	s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on lève le sémaphore
	u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOTRAP_INI.ps8_path_file);
	s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOTRAP, &loc_s32_sem);	//on relache le sem

	//on supprime le fichier (si le fichier est présent)
	s32Lock_Get(SEMAPHORE_BDD_CIP_STATUSTRAP, &loc_s32_sem);	//on lève le sémaphore
	u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_STATUSTRAP_INI.ps8_path_file);
	s32Lock_Release(SEMAPHORE_BDD_CIP_STATUSTRAP, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_Cip_Trap*/


/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cip_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/03/2010
// Description	: Initialisation du module de cip_Trap
//=====================================================================================
void InitModule_Cip_Trap(void)
{

}/*InitModule_Cip_Trap*/

