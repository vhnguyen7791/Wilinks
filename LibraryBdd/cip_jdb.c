/*========================================================================*/
/* NOM DU FICHIER  : cip_jdb.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Base de données: Communication Inter Process (jdb)   */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
//BE017 12/03/2010 CM
// - Optimisation contenu des fichiers jdbpart, cip_fifojdb et cip_fifotrap
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la communication inter processus:
//  --> pour échanger les évènements entre processus monitor et processus jdb
//  --> pour échanger des données supplémentaires avec le processus jdb

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CIP_JDB

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

#define FILE_CIP_FIFOJDB_MONITOR_LINE 	PATH_DIR__BDD_EVT "cip_fifojdb.monitor.line"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER CIP_FIFOJDB.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CIP_FIFOJDB_INI[] = {
	{	"jdb",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_SIMPLE_EVTJDB, (u16sod)sizeof(S_STRUCT_JDBEVT),	0,	0}, //strcuture simple
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER CIP_FIFOJDB.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_FIFOJDB_INI =
{
	PATH_DIR__BDD_EVT "cip_fifojdb.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CIP_FIFOJDB_INI ,//pt_contenu
};



//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM CIP_JDB.INI
//***************************************************************************

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CIP_JDB_INI[] = {
	{	"flag_newcfg",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_TABU8,	(u16sod)sizeof(u8sod),	NB_MAX_IDXCONFIG,	MACRO_OFFSETOF(S_STRUCT_CIP_JDB, pu8_flag_newcfg[0]) },
	{	"effacer_jdb",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_JDB, u8_effacer_jdb) },
	{	"generer_jdb",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CIP_JDB, u8_generer_jdb) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER CIP_JDB.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_CIP_JDB_INI =
{
	PATH_DIR__BDD_MISC "cip_jdb.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CIP_JDB_INI ,//pt_contenu
};



/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Start_CipFifoJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Démarrage de gestion de fifo
//=====================================================================================
void Start_CipFifoJdb(void)
{
	s32sod loc_s32_sem;
	u32sod loc_u32_nbEltJdbTotal;
	//Vérification que la taille du fichier ne dépasse pas la taille max définie
	
	s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on lève le sémaphore
	loc_u32_nbEltJdbTotal = (u32sod)u32GetNumberLineFile(T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file, FILE_CIP_FIFOJDB_MONITOR_LINE);
	if(loc_u32_nbEltJdbTotal > TAILLE_MAX_CIP_ELEMENTS_FIFOJDB)
	{
		//On supprime le fichier cip_fifojdb (original)
		u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file);
		//Puis on crée un fichier vide
		CmdSystem_Generique("touch %s",
							T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file);
		MACRO_PRINTF(("Start_CipFifoJdb: fichier TROP grand %s => PERTE EVT JDB \n",
					  T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file));
	}
	s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on relache le sem

}/*Start_CipFifoJdb*/

// -------------------------------------------------------------
// Fonction		: u8AddCipFifoJdb
// Entrees		: <loc_ps_elt_fifojdb< : elt jdb à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure empile l'evt jdb dans le fichier cip_fifojdb
// -------------------------------------------------------------
u8sod u8AddCipFifoJdb(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
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
		MACRO_PRINTF(("u8AddCipFifoJdb: Impossible de creer le fichier %s\n",
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
										  loc_ps_elt_fifojdb,
										  &loc_u16_idx,
										  &loc_u8_suivant)
			  )//CONDITION: Ecriture simple KO
			{
				loc_u8_return = FALSE;
			}
			
			if(FALSE == loc_u8_return)
			{
				MACRO_PRINTF(("u8AddCipFifoJdb: Erreur dans fichier %s\n",
							  loc_pt_def_file->ps8_path_file));
			}
		}
		else
		{
			loc_u8_return = FALSE;
			MACRO_PRINTF(("u8AddCipFifoJdb: Contenu INDEFINI dans fichier %s\n",
						  loc_pt_def_file->ps8_path_file));
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}
	
	return loc_u8_return;
}/*u8AddCipFifoJdb*/

// -------------------------------------------------------------
// Fonction		: u8ReadCipFifoJdb
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture de l'élément de fifojdb
//				: <loc_pu16_cpt_elt_jdb_lus<	: pointeur sur compteur élément jdb lus avec succès
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure lit les evts jdb dans le fichier cip_fifojdb
// -------------------------------------------------------------
u8sod u8ReadCipFifoJdb(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod	(*loc_func_u8Action)(S_STRUCT_JDBEVT*), u16sod *loc_pu16_cpt_elt_jdb_lus)
{
	S_STRUCT_JDBEVT loc_s_elt_fifojdb;
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u8sod	loc_u8_action_avec_succes;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_isEndOfFile;

	InitEvtJdb(&loc_s_elt_fifojdb); //INIT
	loc_p_handle = NULL;	//INIT
	loc_u8_return = TRUE;	//INIT
	loc_u8_action_avec_succes = TRUE;	//INIT
	loc_u16_idx = 0;		//INIT
	loc_u8_suivant = TRUE;	//INIT
	loc_u16_cpt = 0;		//INIT
	loc_u8_isEndOfFile = FALSE; //INIT

	(*loc_pu16_cpt_elt_jdb_lus) = 0;	//RAZ

	// Ouverture du fichier 
	if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt" )))
	{
		loc_u8_return = TRUE;	//Fichier vide
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
												  &loc_s_elt_fifojdb,
												  FALSE,
												  &loc_u8_isEndOfFile);

				if(FALSE == loc_u8_isEndOfFile) //CONDITION: Ce n'est pas la fin de fichier
				{
					if(FALSE == loc_u8_return)
					{
						MACRO_PRINTF(("u8ReadCipFifoJdb: Erreur dans fichier %s\n",
									  loc_pt_def_file->ps8_path_file));
					}
					else
					{
						if(NULL == loc_func_u8Action) //CONDITION: Fonction non présente (pour test)
						{
							printf("jdb: date=%s idx=%d val=%lu etat=%d info2=%d\n",
								   ps8GetChDate(&loc_s_elt_fifojdb.s_date),
								   loc_s_elt_fifojdb.u16_index_evt,
								   loc_s_elt_fifojdb.t_valeur_evt,
								   loc_s_elt_fifojdb.u8_etat_evt,
								   loc_s_elt_fifojdb.u8_info_sup2);
						}
						else
						{
							loc_u8_action_avec_succes = loc_func_u8Action(&loc_s_elt_fifojdb);
							if(TRUE == loc_u8_action_avec_succes)
							{
								(*loc_pu16_cpt_elt_jdb_lus) ++;
							}
						}
					}
				}

				loc_u16_cpt ++;

				if(TRUE == loc_u8_isEndOfFile) //CONDITION: Fin de fichier
				{
					loc_u16_cpt = (TAILLE_MAX_CIP_ELEMENTS_FIFOJDB+1);	//on sort
				}
				
			}while( (loc_u16_cpt < TAILLE_MAX_CIP_ELEMENTS_FIFOJDB) &&
					(TRUE == loc_u8_return) &&
					(TRUE == loc_u8_action_avec_succes)
				  );
		}
		else
		{
			loc_u8_return = FALSE;
			MACRO_PRINTF(("u8ReadCipFifoJdb: Contenu INDEFINI dans fichier %s\n",
						  loc_pt_def_file->ps8_path_file));
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u8_return;
}/*u8ReadCipFifoJdb*/

//=====================================================================================
// Fonction		: EnregistreJdb
// Entrees		: <loc_u16_index_evt> : index de l'évènement
//				  <loc_t_valeur_evt>  : valeur de l'évènement
//				  <loc_u32_info_sup1> : info 1
//				  <loc_u8_info_sup2>  : information summplémentaire 2
//				  <loc_pu8_info3>	  : info 3
//				  <loc_u8_etat_evt>	  : etat : début / fin / info
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Fonction d'enregistrement des évènements du Jdb
//=====================================================================================
void EnregistreJdb(u16sod loc_u16_index_evt, T_SIZE_VALEUR_EVT loc_t_valeur_evt, u32sod loc_u32_info_sup1, u8sod loc_u8_info_sup2, u8sod *loc_pu8_info3, u8sod loc_u8_etat_evt)
{
	S_STRUCT_JDBEVT	loc_s_elt_fifojdb;
	s32sod	loc_s32_sem;

	if(loc_u16_index_evt < NB_MAX_EVENEMENTS)
	{
		loc_s_elt_fifojdb.u16_index_evt = loc_u16_index_evt;
		loc_s_elt_fifojdb.t_valeur_evt = loc_t_valeur_evt;
		loc_s_elt_fifojdb.u8_etat_evt = loc_u8_etat_evt;
		loc_s_elt_fifojdb.u_info_sup1.u32_term = loc_u32_info_sup1;
		loc_s_elt_fifojdb.u8_info_sup2 = loc_u8_info_sup2;
		memcpy(loc_s_elt_fifojdb.pu8_tab_info_sup3, loc_pu8_info3, TAILLE_MAX_TAB_INFO_SUP3); 

		SetDate(&loc_s_elt_fifojdb.s_date, METHODE_SETDATE_MANUEL);
		
//		printf("EnregistreJdb: evt %d,%d \n",loc_u16_index_evt,loc_t_valeur_evt);

		s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on lève le sémaphore
		if(FALSE == u8AddCipFifoJdb(&loc_s_elt_fifojdb, &T_DEF_FILE_CIP_FIFOJDB_INI))
		{
			MACRO_PRINTF(("EnregistreJdb: Erreur fifojdb idxEvt=%d\n",
						  loc_s_elt_fifojdb.u16_index_evt));
		}
		s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on relache le sem
	}
}/*EnregistreJdb*/

//=====================================================================================
// Fonction		: u8FillCipJdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillCipJdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_cip_jdb, &T_DEF_FILE_CIP_JDB_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillCipJdb KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillCipJdb*/

//=====================================================================================
// Fonction		: u8EditCipJdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditCipJdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_cip_jdb, &T_DEF_FILE_CIP_JDB_INI);

	return loc_u8_resultat;
}/*u8EditCipJdb*/

//=====================================================================================
// Fonction		: InitBDD_Cip_FifoJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de la base de données de cip_fifojdb
//=====================================================================================
void InitBDD_Cip_FifoJdb(void)
{
	s32sod	loc_s32_sem; 	

	//on supprime le fichier (si le fichier est présent)
	s32Lock_Get(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on lève le sémaphore
	u8CmdSystem_RemoveFile(T_DEF_FILE_CIP_FIFOJDB_INI.ps8_path_file);
	s32Lock_Release(SEMAPHORE_BDD_CIP_FIFOJDB, &loc_s32_sem);	//on relache le sem

}/*InitBDD_Cip_FifoJdb*/

//=====================================================================================
// Fonction		: Raz_Cip_Jdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: RAZ des ordres de la base de données de cip_jdb
//=====================================================================================
void Raz_Cip_Jdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb)
{
	u8sod	loc_u8_i;

	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		loc_ps_cip_jdb->pu8_flag_newcfg[loc_u8_i] = FALSE;	//RAZ
	}
	loc_ps_cip_jdb->u8_effacer_jdb = FALSE; //RAZ
	loc_ps_cip_jdb->u8_generer_jdb = FALSE; //RAZ
}/*Raz_Cip_Jdb*/

//=====================================================================================
// Fonction		: InitBDD_Cip_Jdb
// Entrees		: <loc_ps_cip_jdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de la base de données de cip_jdb
//=====================================================================================
void InitBDD_Cip_Jdb(S_STRUCT_CIP_JDB *loc_ps_cip_jdb)
{
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem; 	

	//Gestion du fichier cip_jdb
	s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore

	memset(loc_ps_cip_jdb, 0, sizeof(S_STRUCT_CIP_JDB)); //INIT

	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		loc_ps_cip_jdb->pu8_flag_newcfg[loc_u8_i] = FALSE;	//INIT
	}
	loc_ps_cip_jdb->u8_effacer_jdb = FALSE; //INIT
	loc_ps_cip_jdb->u8_generer_jdb = FALSE; //INIT

	u8EditCipJdb(loc_ps_cip_jdb); //INIT
	s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_Cip_Jdb*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cip_Jdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation du module de cip_jdb
//=====================================================================================
void InitModule_Cip_Jdb(void)
{

}/*InitModule_Cip_Jdb*/

