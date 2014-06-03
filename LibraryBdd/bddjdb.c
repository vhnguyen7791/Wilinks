/*========================================================================*/
/* NOM DU FICHIER  : bddjdb.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 10/03/2010                                           */
/* Libelle         : Base de données: Journal de bord					  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
//BE017 12/03/2010 CM
// - Optimisation contenu des fichiers jdbpart, cip_fifojdb et cip_fifotrap
//BE018 15/03/2010 CM
// - Correction risque de corruption du journal de bord sauvé en FLASH lors de l'écriture d'un évènement
//	en effet, on va sécurisé l'écriture dans le fichier jdbpart en doublant l'écriture dans un autre fichier (jdbcur.log)
//BE046 17/11/2010 CM
// - Correction force horodatage identique à tous les évènements dans la seconde
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la base de données du journal de bord

/*_____II - DEFINE SBIT __________________________________________________*/
#define _BDDJDB

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER JDBPART<NUM>.LOG
//***************************************************************************
//Remarque: noms raccourcis pour pouvoir economiser place lors de la sauvegarde dans la FLASH
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_JDBPART[] = {
	{	"J",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_SIMPLE_EVTJDB, (u16sod)sizeof(S_STRUCT_JDBEVT),	0,	0}, //structure simple
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER JDBPART<NUM>.LOG
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_JDBPART =
{
	"",		 //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_JDBPART ,//pt_contenu
};


//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM STATUTJDB.SAV [FLASH]
//***************************************************************************
//Ce fichier est sécurisé par checksum!
//Remarque: noms raccourcis pour pouvoir economiser place lors de la sauvegarde dans la FLASH
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_FLASHSTATUTJDB_INI[] = {
	{	"date",				FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, s_date_dernier_reset)	},
	{	"rd",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u8_numrd_jdbpart) },
	{	"wr",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u8_numwr_jdbpart) },
	{	CH_BDDFILECHECKSUM,	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM STATUTJDB.INI [RAM]
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_RAMSTATUTJDB_INI[] = {
	{	"date",				FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, s_date_dernier_reset)	},
	{	"rd",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u8_numrd_jdbpart) },
	{	"wr",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u8_numwr_jdbpart) },
	{	"nbevt",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u16_nb_total_evt) },
	{	"nbevt_part",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_STATUTJDB, u16_nbevt_jdbpart_encours) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};


//****************************************
//DEFINITION DU FICHIER STATUTJDB.XXX
//****************************************
T_STRUCT_DEFINITION_FILE_FS PT_DEF_FILE_STATUTJDB[NB_MAX_IDXSTATUTJDB] =
{
	{//IDXSTATUTJDB_BASE
		PATH_DIR__FLASH_JDB "statutjdb.sav", //ps8_path_file
		DEFFILE_TYPE_SYSTEM, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_FLASHSTATUTJDB_INI ,//pt_contenu
	},
	{//IDXSTATUTJDB_BACKUP
		PATH_DIR__FLASH_JDB "statutjdb.bak", //ps8_path_file
		DEFFILE_TYPE_SYSTEM, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_FLASHSTATUTJDB_INI ,//pt_contenu
	},
	{//IDXSTATUTJDB_RAM
		PATH_DIR__BDD_EVT "statutjdb.ini", //ps8_path_file
		DEFFILE_TYPE_SYSTEM, //u8_type
		FALSE,	//u8_avec_checksum
		PT_CONTENU_FILE_RAMSTATUTJDB_INI ,//pt_contenu
	},
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8TestEvtJdb
// Entrees		: <loc_ps_evtjdb< : pointeur sur un évènement jdb
// Sortie		: <loc_u8_resultat> : TRUE,si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Test un évènement type du jdb
//=====================================================================================
u8sod u8TestEvtJdb(S_STRUCT_JDBEVT *loc_ps_evtjdb)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(loc_ps_evtjdb->u16_index_evt >= NB_MAX_EVENEMENTS)
	{
		loc_u8_resultat = FALSE;
	}
	if((ETAT_EVT_NON_DEFINI != loc_ps_evtjdb->u8_etat_evt)&&
	   (loc_ps_evtjdb->u8_etat_evt >= NB_MAX_ETATS_EVENT)
	  )
	{
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}/*u8TestEvtJdb*/

//============================================================================
// Fonction		: ps8GetChNomFileJdbPart
// Entrees		: <loc_u8_numjdbpart> : numéro du jdbpart
// Sortie		: <loc_ps8_nomFileJdbPart< : chaine 
// Auteur		: CM - 10/03/2010 -
// Description	: renvoie la chaîne du nom du fichier jdbpart
//============================================================================
s8sod* ps8GetChNomFileJdbPart(u8sod loc_u8_numjdbpart)
{
	static s8sod loc_ps8_nomFileJdbPart[100+1];

	if(loc_u8_numjdbpart < NB_MAX_JDBPART) //CONDITION: numéro fichier jdbpart valide
	{
		sprintf(loc_ps8_nomFileJdbPart, "%s%s%d%s",
				PATH_DIR__FLASH_JDB,NFILE_JDBPART,loc_u8_numjdbpart,EXT_LOG);
	}
	else
	{
		if(NUM_JDBCUR == loc_u8_numjdbpart) //CONDITION: numéro fichier jdbcur valide
		{
			strcpy(loc_ps8_nomFileJdbPart, FILE_FLASH_JDBCUR);
		}
		else
		{
			strcpy(loc_ps8_nomFileJdbPart, "");
		}
	}
	
	return (&loc_ps8_nomFileJdbPart[0]);
}/*ps8GetChNomFileJdbPart*/

// -------------------------------------------------------------
// Fonction		: u8RemoveJdbPart
// Entrees		: <loc_u8_numjdbpart> : numéro du jdbpart
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 10/03/2010
// Description	: Suppression du fichier jdbpart identifié par son numéro
// -------------------------------------------------------------
u8sod u8RemoveJdbPart(u8sod loc_u8_numjdbpart)
{
	u8sod loc_u8_return;

	loc_u8_return = FALSE;	//INIT
	
	if((loc_u8_numjdbpart < NB_MAX_JDBPART) ||
	   (NUM_JDBCUR == loc_u8_numjdbpart)
	  )  //CONDITION: numéro fichier jdbpart valide
	{
		loc_u8_return = u8CmdSystem_RemoveFile(ps8GetChNomFileJdbPart(loc_u8_numjdbpart));
	}
		

	return loc_u8_return;
}/*u8RemoveJdbPart*/


// -------------------------------------------------------------
// Fonction		: u8AddEvtJdbPart
// Entrees		: <loc_ps_elt_fifojdb< : elt jdb à empiler
//				  <loc_pt_def_file< : pointeur sur définition du fichier
//				  <loc_u8_numjdbpart> : numéro du jdbpart
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure empile l'evt jdb dans le fichier jdbpart 
// -------------------------------------------------------------
u8sod u8AddEvtJdbPart(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod loc_u8_numjdbpart)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;

	loc_p_handle = NULL;	//INIT
	loc_u8_return = TRUE;	//INIT
	loc_u16_idx = 0;		//INIT
	loc_u8_suivant = TRUE;	//INIT

	if((loc_u8_numjdbpart < NB_MAX_JDBPART) ||
	   (NUM_JDBCUR == loc_u8_numjdbpart)
	  )  //CONDITION: numéro fichier jdbpart valide ou jdbcur valide
	{
		// Ouverture du fichier 
		if(NULL == (loc_p_handle = fopen( ps8GetChNomFileJdbPart(loc_u8_numjdbpart), "at" )))
		{
			MACRO_PRINTF(("u8AddEvtJdbPart: Impossible de creer le fichier %s\n",
						  ps8GetChNomFileJdbPart(loc_u8_numjdbpart)));
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
					MACRO_PRINTF(("u8AddEvtJdbPart: Erreur dans fichier %s\n",
								  ps8GetChNomFileJdbPart(loc_u8_numjdbpart)));
				}
			}
			else
			{
				loc_u8_return = FALSE;
				MACRO_PRINTF(("u8AddEvtJdbPart: Contenu INDEFINI dans fichier %s\n",
							  ps8GetChNomFileJdbPart(loc_u8_numjdbpart)));
			}

			//fermeture du fichier
			fclose (loc_p_handle);
		}
	}
	else
	{
		loc_u8_return = FALSE;
		MACRO_PRINTF(("u8AddEvtJdbPart: Numéro du fichier errone %d\n",
					  loc_u8_numjdbpart));
	}
		

	return loc_u8_return;
}/*u8AddEvtJdbPart*/

// -------------------------------------------------------------
// Fonction		: u8ReadEvtJdbPart
// Entrees		: <loc_pt_def_file<				: pointeur sur définition du fichier
//				  <loc_u8_numjdbpart>			 : numéro du jdbpart
//				: <loc_func_u8Action<			: pointeur sur fonction action suite à lecture de l'élément de fifojdb
//				: <loc_pu16_cpt_elt_jdb_lus<	: pointeur sur compteur élément jdb lus avec succès
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 09/03/2010
// Description	: cette procedure lit les evts jdb dans le fichier jdbpart
// -------------------------------------------------------------
u8sod u8ReadEvtJdbPart(T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file, u8sod loc_u8_numjdbpart, u8sod	(*loc_func_u8Action)(S_STRUCT_JDBEVT*), u16sod *loc_pu16_cpt_elt_jdb_lus)
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

	if((loc_u8_numjdbpart < NB_MAX_JDBPART) ||
	   (NUM_JDBCUR == loc_u8_numjdbpart)
	  )  //CONDITION: numéro fichier jdbpart valide ou jdbcur valide
	{
		// Ouverture du fichier 
		if(NULL == (loc_p_handle = fopen( ps8GetChNomFileJdbPart(loc_u8_numjdbpart), "rt" )))
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
					InitEvtJdb(&loc_s_elt_fifojdb); //RAZ
					loc_s_elt_fifojdb.u16_index_evt = 0xFFFF; //RAZ: pour s'assurer que la lecture est effectuée sur toute la ligne
					
					loc_u8_return = u8BddFile_ReadLine(loc_p_handle,
														(T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
														&loc_s_elt_fifojdb,
														FALSE,
														&loc_u8_isEndOfFile);

					if(FALSE == loc_u8_isEndOfFile) //CONDITION: Ce n'est pas la fin de fichier
					{
						if(FALSE == loc_u8_return)
						{
							MACRO_PRINTF(("u8ReadEvtJdbPart: Erreur dans fichier %s\n",
										  ps8GetChNomFileJdbPart(loc_u8_numjdbpart)));
						}
						else
						{
							if(NULL != loc_func_u8Action) //CONDITION: Fonction présente
							{
								loc_u8_action_avec_succes = loc_func_u8Action(&loc_s_elt_fifojdb);
								if(TRUE == loc_u8_action_avec_succes)
								{
									(*loc_pu16_cpt_elt_jdb_lus) ++;
								}
							}
							else
							{
								if(TRUE == u8TestEvtJdb(&loc_s_elt_fifojdb))
								{
									(*loc_pu16_cpt_elt_jdb_lus) ++;
								}
								else
								{
									MACRO_PRINTF(("u8ReadEvtJdbPart: Erreur lecture evt dans fichier %s\n",
												ps8GetChNomFileJdbPart(loc_u8_numjdbpart)));
									loc_u8_return = FALSE;	//Erreur lecture ligne
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
				MACRO_PRINTF(("u8ReadEvtJdbPart: Contenu INDEFINI dans fichier %s\n",
							  ps8GetChNomFileJdbPart(loc_u8_numjdbpart)));
			}

			//fermeture du fichier
			fclose (loc_p_handle);
		}
	}
	else
	{
		loc_u8_return = FALSE;
		MACRO_PRINTF(("u8ReadEvtJdbPart: Numéro du fichier errone %d\n",
					  loc_u8_numjdbpart));
	}

	return loc_u8_return;
}/*u8ReadEvtJdbPart*/

//=====================================================================================
// Fonction		: u8FillStatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
//				: <loc_u16_idx_statutjdb>: index du fichier statutjdb
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillStatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb, u16sod loc_u16_idx_statutjdb)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE; //INIT
	
	if(loc_u16_idx_statutjdb < NB_MAX_IDXSTATUTJDB)
	{
		loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_statutjdb, &PT_DEF_FILE_STATUTJDB[loc_u16_idx_statutjdb]);
		if(FALSE == loc_u8_resultat)
		{
			MACRO_PRINTF(("u8FillStatutJdb: Lecture KO idx=%d \n",loc_u16_idx_statutjdb));
		}
	}
	else
	{
		MACRO_PRINTF(("u8FillStatutJdb: Erreur idx=%d \n",loc_u16_idx_statutjdb));
	}

	return loc_u8_resultat;
}/*u8FillStatutJdb*/

//=====================================================================================
// Fonction		: u8EditStatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
//				: <loc_u16_idx_statutjdb>: index du fichier statutjdb
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditStatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb, u16sod loc_u16_idx_statutjdb)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE; //INIT

	if(loc_u16_idx_statutjdb < NB_MAX_IDXSTATUTJDB)
	{
		loc_u8_resultat = u8Transfert_StructToFile(loc_ps_statutjdb, &PT_DEF_FILE_STATUTJDB[loc_u16_idx_statutjdb]);
	}
	else
	{
		MACRO_PRINTF(("u8EditStatutJdb: Erreur idx=%d \n",loc_u16_idx_statutjdb));
	}

	return loc_u8_resultat;
}/*u8EditStatutJdb*/

//=====================================================================================
// Fonction		: InitStatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de statutjdb
//=====================================================================================
void InitStatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb)
{
	InitStructDate(&loc_ps_statutjdb->s_date_dernier_reset);	//INIT
	loc_ps_statutjdb->u8_numrd_jdbpart = 0;		//INIT
	loc_ps_statutjdb->u8_numwr_jdbpart = 0;		//INIT
	loc_ps_statutjdb->u16_checksum_file = 0;	//INIT
	loc_ps_statutjdb->u16_nb_total_evt = 0;		//INIT
	loc_ps_statutjdb->u16_nbevt_jdbpart_encours = 0;//INIT
}/*InitStatutJdb*/

//=====================================================================================
// Fonction		: RazJournalDeBord
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Remise à zéro du journal de bord
//=====================================================================================
void RazJournalDeBord(S_STRUCT_STATUTJDB *loc_ps_statutjdb)
{
	u8sod loc_u8_i;

	//On efface tous les fichiers
	for(loc_u8_i=0;loc_u8_i<NB_MAX_JDBPART;loc_u8_i++)
	{
		u8RemoveJdbPart(loc_u8_i);
	}
	//On supprime ensuite le fichier courant
	u8RemoveJdbPart(NUM_JDBCUR);
	
	u8CmdSystem_RemoveFile(PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BASE].ps8_path_file);
	u8CmdSystem_RemoveFile(PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BACKUP].ps8_path_file);

	//Raz statutjdb
	InitStatutJdb(loc_ps_statutjdb);	//RAZ

	//On horodate le raz
	SetDate(&loc_ps_statutjdb->s_date_dernier_reset, METHODE_SETDATE_SYSTEM);
	
	u8EditStatutJdb(loc_ps_statutjdb, IDXSTATUTJDB_BASE);
	//on copie base => backup
	u8CmdSystem_CopyFile(PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BASE].ps8_path_file,
						 PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BACKUP].ps8_path_file);

	//Edition du fichier en ram
	u8EditStatutJdb(loc_ps_statutjdb, IDXSTATUTJDB_RAM);
}/*RazJournalDeBord*/

//=====================================================================================
// Fonction		: InitBDD_StatutJdb
// Entrees		: <loc_ps_statutjdb< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation de la base de données de statutjdb
//=====================================================================================
void InitBDD_StatutJdb(S_STRUCT_STATUTJDB *loc_ps_statutjdb)
{
	s32sod	loc_s32_sem; 	
	u8sod	loc_u8_etat_base; //etat du fichier de base
	u16sod	loc_u16_chk_base; //checksum du fichier de base
	u8sod	loc_u8_etat_backup; //etat du fichier de backup
	u16sod	loc_u16_chk_backup;//checksum du fichier de backup
	u8sod	loc_u8_etat_bdd; //etat du fichier de backup
	u8sod	loc_u8_numid_jdbpart;
	u16sod	loc_u16_cpt;
	u16sod	loc_u16_nbevt_jdbpart;
	u8sod	loc_u8_etat_rd_jdbpart;
	u16sod	loc_u16_nbevt_jdbcur;
	u8sod	loc_u8_etat_rd_jdbcur;

	loc_u8_etat_base = FALSE; //INIT
	loc_u16_chk_base = 0 ; //INIT
	loc_u8_etat_backup = FALSE; //INIT
	loc_u16_chk_backup = 0 ; //INIT
	loc_u8_etat_bdd = TRUE;	//INIT
	loc_u8_numid_jdbpart = 0;	//INIT
	loc_u16_cpt = 0;	//INIT
	loc_u16_nbevt_jdbpart = 0; //INIT
	loc_u8_etat_rd_jdbpart = FALSE;	//INIT
	loc_u16_nbevt_jdbcur = 0;	//INIT
	loc_u8_etat_rd_jdbcur = FALSE;	//INIT
	
	//Gestion du fichier statutjdb
	s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore

	//**Etape n°1**: Initialisation de la structure
	memset(loc_ps_statutjdb, 0, sizeof(S_STRUCT_STATUTJDB)); //INIT
	InitStatutJdb(loc_ps_statutjdb);	//INIT
	
	//**Etape n°2**: Vérification présence / validité des fichiers de configuration dans la mémoire non volatile
	//on parcourt les fichiers de configuration (dans mémoire non volatile)
	loc_u8_etat_base = u8Transfert_FileToStruct(loc_ps_statutjdb, &PT_DEF_FILE_STATUTJDB[ IDXSTATUTJDB_BASE ]);
	loc_u16_chk_base = loc_ps_statutjdb->u16_checksum_file;
	loc_u8_etat_backup = u8Transfert_FileToStruct(loc_ps_statutjdb, &PT_DEF_FILE_STATUTJDB[ IDXSTATUTJDB_BACKUP ]);
	loc_u16_chk_backup = loc_ps_statutjdb->u16_checksum_file;

	printf("************************************************ \n");
	printf("* InitBDD_StatutJdb: RESULTAT TEST STATUTJDB \n");
	printf("*                  	BASE(STATUT=%d CHK=%d) \n",
		   loc_u8_etat_base,loc_u16_chk_base);
	printf("*                  	BACKUP(STATUT=%d CHK=%d) \n",
		   loc_u8_etat_backup,loc_u16_chk_backup);
	printf("************************************************ \n");

	if(TRUE == loc_u8_etat_base) //CONDITION: fichier de base OK
	{
		if(TRUE == loc_u8_etat_backup) //CONDITION: fichier de backup OK
		{
			//On vérifie qu'il y a le meme checksum
			//si différent, il faut copier le fichier de base dans backup
			if(loc_u16_chk_base != loc_u16_chk_backup)
			{
				//on copie base => backup
				u8CmdSystem_CopyFile(PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BASE].ps8_path_file,
									 PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BACKUP].ps8_path_file);
			}
		}
		else //CONDITION: fichier de backup KO
		{
			//on copie base => backup
			u8CmdSystem_CopyFile(PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BASE].ps8_path_file,
								 PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BACKUP].ps8_path_file);
		}
	}
	else  //CONDITION: fichier de base KO
	{
		if(TRUE == loc_u8_etat_backup) //CONDITION: fichier de backup OK
		{
			//on copie backup => base
			u8CmdSystem_CopyFile(PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BACKUP].ps8_path_file,
								 PT_DEF_FILE_STATUTJDB[IDXSTATUTJDB_BASE].ps8_path_file);
		}
		else //CONDITION: fichier de backup KO
		{
			MACRO_PRINTF(("InitBDD_StatutJdb: RAZ DU JOURNAL DE BORD \n"));
			loc_u8_etat_bdd = FALSE;
		}
	}

	if(TRUE == loc_u8_etat_bdd) //CONDITION: Pour l'instant pas de problème de la base de données du JDB
	{
		//On vérifie ensuite la cohérence des paramètres sauvés
		if((loc_ps_statutjdb->u8_numrd_jdbpart >= NB_MAX_JDBPART)||
		   (loc_ps_statutjdb->u8_numwr_jdbpart >= NB_MAX_JDBPART) ||
		   (FALSE == u8TestDate_Valide(&loc_ps_statutjdb->s_date_dernier_reset))
		  )
		{
			MACRO_PRINTF(("InitBDD_StatutJdb: Erreur donnees numrd_jdbpart=%d, numwr_jdbpart=%d KO \n",
						   loc_ps_statutjdb->u8_numrd_jdbpart,
						   loc_ps_statutjdb->u8_numwr_jdbpart));
			MACRO_PRINTF(("InitBDD_StatutJdb: Erreur donnees s_date_dernier_reset=%d/%d/%d %d:%d:%d KO \n",
						   loc_ps_statutjdb->s_date_dernier_reset.u16_annee,
						   loc_ps_statutjdb->s_date_dernier_reset.u8_mois,
						   loc_ps_statutjdb->s_date_dernier_reset.u8_jour,
						   loc_ps_statutjdb->s_date_dernier_reset.u8_heure,
						   loc_ps_statutjdb->s_date_dernier_reset.u8_minute,
						   loc_ps_statutjdb->s_date_dernier_reset.u8_seconde));
			
			loc_u8_etat_bdd = FALSE;
		}
		else
		{
			if(loc_ps_statutjdb->u8_numrd_jdbpart == loc_ps_statutjdb->u8_numwr_jdbpart) //CONDITION: un seul fichier jdbpart
			{
				if(0 == loc_ps_statutjdb->u8_numrd_jdbpart)
				{
					loc_u8_numid_jdbpart = loc_ps_statutjdb->u8_numrd_jdbpart;
					//Lecture du fichier
					loc_u8_etat_rd_jdbpart = u8ReadEvtJdbPart(&T_DEF_FILE_JDBPART, loc_ps_statutjdb->u8_numrd_jdbpart, NULL, &loc_u16_nbevt_jdbpart);
					loc_u8_etat_rd_jdbcur = u8ReadEvtJdbPart(&T_DEF_FILE_JDBPART, NUM_JDBCUR, NULL, &loc_u16_nbevt_jdbcur);
					printf("InitBDD_StatutJdb: Lecture dernier fichier jdbpart=%d / %d \n",
							loc_u8_etat_rd_jdbpart, loc_u16_nbevt_jdbpart);
					printf("InitBDD_StatutJdb: Lecture dernier fichier jdbcur=%d / %d \n",
							loc_u8_etat_rd_jdbcur, loc_u16_nbevt_jdbcur);
					
					if(TRUE == loc_u8_etat_rd_jdbpart) //CONDITION: jdbpart valide
					{
						if(TRUE == loc_u8_etat_rd_jdbcur) //CONDITION: jdbcur valide
						{
							if(loc_u16_nbevt_jdbpart != loc_u16_nbevt_jdbcur)
							{
								printf("InitBDD_StatutJdb: cp jdbpart%d => jdbcur\n",loc_ps_statutjdb->u8_numrd_jdbpart);
								//On supprime le fichier courant
								u8RemoveJdbPart(NUM_JDBCUR);
								//on copie jdbpart => jdbcur
								u8CmdSystem_CopyFile(ps8GetChNomFileJdbPart(loc_ps_statutjdb->u8_numrd_jdbpart), FILE_FLASH_JDBCUR);
								loc_u16_nbevt_jdbcur = loc_u16_nbevt_jdbpart; //RAZ
							}
						}
						else //CONDITION: jdbcur invalide
						{
							printf("InitBDD_StatutJdb: cp jdbpart%d => jdbcur\n",loc_ps_statutjdb->u8_numrd_jdbpart);
							//On supprime le fichier courant
							u8RemoveJdbPart(NUM_JDBCUR);
							//on copie jdbpart => jdbcur
							u8CmdSystem_CopyFile(ps8GetChNomFileJdbPart(loc_ps_statutjdb->u8_numrd_jdbpart), FILE_FLASH_JDBCUR);
							loc_u8_etat_rd_jdbcur = TRUE; //RAZ
							loc_u16_nbevt_jdbcur = loc_u16_nbevt_jdbpart; //RAZ
						}
					}
					else  //CONDITION: jdbpart invalide
					{
						if(TRUE == loc_u8_etat_rd_jdbcur) //CONDITION: jdbcur valide
						{
							printf("InitBDD_StatutJdb: cp jdbcur => jdbpart%d\n",loc_ps_statutjdb->u8_numrd_jdbpart);
							//On supprime le fichier jdbpart
							u8RemoveJdbPart(loc_ps_statutjdb->u8_numrd_jdbpart);
							//on copie jdbcur => jdbpart
							u8CmdSystem_CopyFile(FILE_FLASH_JDBCUR, ps8GetChNomFileJdbPart(loc_ps_statutjdb->u8_numrd_jdbpart));
							loc_u8_etat_rd_jdbpart = TRUE; //RAZ
							loc_u16_nbevt_jdbpart = loc_u16_nbevt_jdbcur; //RAZ
						}
						else
						{
							MACRO_PRINTF(("InitBDD_StatutJdb: Impossible de récupérer %s \n",
										  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
						}
					}
					
					if((FALSE == loc_u8_etat_rd_jdbpart) ||
					   (FALSE == loc_u8_etat_rd_jdbcur)
					  )
					{
						loc_u8_etat_bdd = FALSE;
						MACRO_PRINTF(("InitBDD_StatutJdb: Erreur lecture %s \n",
									  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
					}
					else
					{
						if(loc_u16_nbevt_jdbpart > NB_MAX_EVT_PAR_JDBPART)
						{
							loc_u8_etat_bdd = FALSE;
							MACRO_PRINTF(("InitBDD_StatutJdb: Erreur nb_evt_lus=%d dans %s KO \n",
										  loc_u16_nbevt_jdbpart,
										  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
						}
						else
						{
							loc_ps_statutjdb->u16_nbevt_jdbpart_encours = loc_u16_nbevt_jdbpart;
							loc_ps_statutjdb->u16_nb_total_evt = loc_u16_nbevt_jdbpart;
						}
					}
				}
				else //CONDITION: erreur
				{
					loc_u8_etat_bdd = FALSE;
					MACRO_PRINTF(("InitBDD_StatutJdb: Erreur donnees numrd_jdbpart=%d , numwr_jdbpart=%d KO \n",
								   loc_ps_statutjdb->u8_numrd_jdbpart,
								   loc_ps_statutjdb->u8_numwr_jdbpart));
				}
			}
			else //CONDITION: plusieurs fichiers jdbpart
			{
				loc_u16_cpt = 0;	//RAZ
				loc_u8_numid_jdbpart = loc_ps_statutjdb->u8_numrd_jdbpart; //RAZ
				loc_ps_statutjdb->u16_nb_total_evt = 0; //RAZ
				while((TRUE == loc_u8_etat_bdd)&&
					  (loc_u16_cpt < NB_MAX_JDBPART)
					 )
				{
					//Lecture du fichier
					loc_u8_etat_rd_jdbpart = u8ReadEvtJdbPart(&T_DEF_FILE_JDBPART, loc_u8_numid_jdbpart, NULL, &loc_u16_nbevt_jdbpart);
					if(loc_u8_numid_jdbpart == loc_ps_statutjdb->u8_numwr_jdbpart) //CONDITION: il s'agit du fichier en cours d'écriture
					{
						//Lecture du fichier courant
						loc_u8_etat_rd_jdbcur = u8ReadEvtJdbPart(&T_DEF_FILE_JDBPART, NUM_JDBCUR, NULL, &loc_u16_nbevt_jdbcur);
						printf("InitBDD_StatutJdb: Lecture dernier fichier jdbpart=%d / %d \n",
							   loc_u8_etat_rd_jdbpart, loc_u16_nbevt_jdbpart);
						printf("InitBDD_StatutJdb: Lecture dernier fichier jdbcur=%d / %d \n",
							   loc_u8_etat_rd_jdbcur, loc_u16_nbevt_jdbcur);

						if(TRUE == loc_u8_etat_rd_jdbpart) //CONDITION: jdbpart valide
						{
							if(TRUE == loc_u8_etat_rd_jdbcur) //CONDITION: jdbcur valide
							{
								if(loc_u16_nbevt_jdbpart != loc_u16_nbevt_jdbcur)
								{
									printf("InitBDD_StatutJdb: cp jdbpart%d => jdbcur\n",loc_u8_numid_jdbpart);
									//On supprime le fichier courant
									u8RemoveJdbPart(NUM_JDBCUR);
									//on copie jdbpart => jdbcur
									u8CmdSystem_CopyFile(ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart), FILE_FLASH_JDBCUR);
									loc_u16_nbevt_jdbcur = loc_u16_nbevt_jdbpart; //RAZ
								}
							}
							else //CONDITION: jdbcur invalide
							{
								printf("InitBDD_StatutJdb: cp jdbpart%d => jdbcur\n",loc_u8_numid_jdbpart);
								//On supprime le fichier courant
								u8RemoveJdbPart(NUM_JDBCUR);
								//on copie jdbpart => jdbcur
								u8CmdSystem_CopyFile(ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart), FILE_FLASH_JDBCUR);
								loc_u8_etat_rd_jdbcur = TRUE; //RAZ
								loc_u16_nbevt_jdbcur = loc_u16_nbevt_jdbpart; //RAZ
							}
						}
						else  //CONDITION: jdbpart invalide
						{
							if(TRUE == loc_u8_etat_rd_jdbcur) //CONDITION: jdbcur valide
							{
								printf("InitBDD_StatutJdb: cp jdbcur => jdbpart%d\n",loc_u8_numid_jdbpart);
								//On supprime le fichier jdbpart
								u8RemoveJdbPart(loc_u8_numid_jdbpart);
								//on copie jdbcur => jdbpart
								u8CmdSystem_CopyFile(FILE_FLASH_JDBCUR, ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart));
								loc_u8_etat_rd_jdbpart = TRUE; //RAZ
								loc_u16_nbevt_jdbpart = loc_u16_nbevt_jdbcur; //RAZ
							}
							else
							{
								MACRO_PRINTF(("InitBDD_StatutJdb: Impossible de récupérer %s \n",
											  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
							}
						}
					}
					else
					{
						//Pour les autres fichiers,
						loc_u8_etat_rd_jdbcur = TRUE;	//RAZ
					}

					if((FALSE == loc_u8_etat_rd_jdbpart) ||
					   (FALSE == loc_u8_etat_rd_jdbcur)
					  )
					{
						loc_u8_etat_bdd = FALSE;
						MACRO_PRINTF(("InitBDD_StatutJdb: Erreur lecture %s \n",
									  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
					}
					else
					{
						if(loc_u16_nbevt_jdbpart > NB_MAX_EVT_PAR_JDBPART)
						{
							loc_u8_etat_bdd = FALSE;
							MACRO_PRINTF(("InitBDD_StatutJdb: Erreur nb_evt_lus=%d dans %s KO \n",
										  loc_u16_nbevt_jdbpart,
										  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
						}
						else
						{
							printf("InitBDD_StatutJdb: nb_evt_lus=%d dans %s \n",
								   loc_u16_nbevt_jdbpart,
								   ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart));
							loc_ps_statutjdb->u16_nb_total_evt += loc_u16_nbevt_jdbpart;
							if(loc_u8_numid_jdbpart == loc_ps_statutjdb->u8_numwr_jdbpart) //CONDITION: dernier fichier
							{
								loc_ps_statutjdb->u16_nbevt_jdbpart_encours = loc_u16_nbevt_jdbpart;
							}
							else
							{
								if(loc_u16_nbevt_jdbpart != NB_MAX_EVT_PAR_JDBPART) //CONDITION: vérification que les autres jdbpart sont complets
								{
									loc_u8_etat_bdd = FALSE;
									MACRO_PRINTF(("InitBDD_StatutJdb: Erreur nb_evt_lus=%d dans %s KO \n",
										loc_u16_nbevt_jdbpart,
										ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
								}
							}
						}
					}
					loc_u16_cpt ++;
					if(loc_u8_numid_jdbpart == loc_ps_statutjdb->u8_numwr_jdbpart)
					{
						loc_u16_cpt = NB_MAX_JDBPART+1;	//on sort
					}
					
					loc_u8_numid_jdbpart ++;
					if(loc_u8_numid_jdbpart >= NB_MAX_JDBPART)
					{
						loc_u8_numid_jdbpart = 0;	//RAZ
					}
				}
			}

			//On vérifie ensuite la cohérence des autes paramètres
			if((loc_ps_statutjdb->u16_nbevt_jdbpart_encours > NB_MAX_EVT_PAR_JDBPART)||
			   (loc_ps_statutjdb->u16_nb_total_evt > TAILLE_MAX_JDBEVT)
			  )
			{
				MACRO_PRINTF(("InitBDD_StatutJdb: Erreur nbevt_jdbpart_encours=%d , nb_total_evt=%d KO \n",
							  loc_ps_statutjdb->u16_nbevt_jdbpart_encours,
							  loc_ps_statutjdb->u16_nb_total_evt));
				loc_u8_etat_bdd = FALSE;
			}
		}
	}

	printf("************************************************ \n");
	printf("* InitBDD_StatutJdb: RESULTAT TEST JDB => %s \n",
		   (TRUE == loc_u8_etat_bdd)?"OK":"KO");
	printf("************************************************ \n");
	
	if(FALSE == loc_u8_etat_bdd) //CONDITION: Erreur dans la base de données du JDB
	{
		MACRO_PRINTF(("InitBDD_StatutJdb: ERREUR DANS BASE DE DONNEES JDB => ERASE ALL \n"));
		RazJournalDeBord(loc_ps_statutjdb);
	}
	else
	{
		printf("InitBDD_StatutJdb: Pour information nbevt_jdbpart_encours=%d , nb_total_evt=%d \n",
			   loc_ps_statutjdb->u16_nbevt_jdbpart_encours,
			   loc_ps_statutjdb->u16_nb_total_evt);
	}

	//Puis on génère le fichier dans la RAM
	u8EditStatutJdb(loc_ps_statutjdb, IDXSTATUTJDB_RAM);

	s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem


}/*InitBDD_StatutJdb*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitEvtJdb
// Entrees		: <loc_ps_evtjdb< : pointeur sur un évènement jdb
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation d'un évènement type du jdb
//=====================================================================================
void InitEvtJdb(S_STRUCT_JDBEVT *loc_ps_evtjdb)
{
	InitStructDate(&loc_ps_evtjdb->s_date);	//RAZ
	loc_ps_evtjdb->u16_index_evt = 0; //RAZ
	loc_ps_evtjdb->t_valeur_evt = 0; //RAZ
	loc_ps_evtjdb->u8_etat_evt = ETAT_EVT_NON_DEFINI; //RAZ
	loc_ps_evtjdb->u_info_sup1.u32_term = 0; //RAZ
	loc_ps_evtjdb->u8_info_sup2 = 0; //RAZ
	memset(loc_ps_evtjdb->pu8_tab_info_sup3, 0, TAILLE_MAX_TAB_INFO_SUP3);  //RAZ
}/*InitEvtJdb*/

//=====================================================================================
// Fonction		: InitModule_BddJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010
// Description	: Initialisation du module de bddjdb
//=====================================================================================
void InitModule_BddJdb(void)
{

}/*InitModule_BddJdb*/

