/*========================================================================*/
/* NOM DU FICHIER  : bddsystemfile.c 		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: Systeme des fichiers				  */
/* Projet          : WRM100                                               */
/* Indice          : BE036                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE006 20/01/2010 CM
// - Modification gestion couche haute des fichiers
//		modif appel u8Transfert_StructToFile, u8Transfert_FileToStruct, u8Display_FileToStruct
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _BDDSYSTEMFILE

#define ESSAI_MAX_ACCES_FILE	2

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8Transfert_StructToFile
// Entrees		: <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 24/09/2009 -
// Description	: Tranfert les données contenues dans la structure dans le fichier
//=====================================================================================
u8sod u8Transfert_StructToFile(void *loc_pt_structure, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_return;
	u8sod	loc_u8_cpt_essai;
	
	loc_u8_return = TRUE;	//INIT
	loc_u8_cpt_essai = 0;	//INIT

	if(loc_pt_def_file != NULL)
	{
		do{
//			//On autorise l'accès en écriture
//			CmdSystem_Generique("chmod 777 %s \n",
//							   loc_pt_def_file->ps8_path_file);
			
			// Ouverture du fichier 
			if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "wt" )))
			{
				MACRO_PRINTF(("u8Transfert_StructToFile: Impossible de creer le fichier %s\n",
							  loc_pt_def_file->ps8_path_file));
				loc_u8_return = FALSE;
			}
			else
			{
				if(loc_pt_def_file->pt_contenu != NULL)
				{
					// Edition du fichier 
					loc_u8_return = u8BddFilePrintf(loc_p_handle,
													(T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
													loc_pt_structure,
													loc_pt_def_file->u8_avec_checksum);
					if(FALSE == loc_u8_return)
					{
						MACRO_PRINTF(("u8Transfert_StructToFile: Erreur dans fichier %s\n",
									  loc_pt_def_file->ps8_path_file));
					}
				}
				else
				{
					loc_u8_return = FALSE;
					MACRO_PRINTF(("u8Transfert_StructToFile: Contenu INDEFINI dans fichier %s\n",
								 loc_pt_def_file->ps8_path_file));
				}

				//fermeture du fichier
				fclose (loc_p_handle);
				
				//Fixe permission du fichier
				u8CmdSystem_ChmodFile(loc_pt_def_file->ps8_path_file, CHMOD_FILE_ROOT_751);
			}
			
			loc_u8_cpt_essai ++;
		}while( (FALSE == loc_u8_return) &&
				(loc_u8_cpt_essai<ESSAI_MAX_ACCES_FILE)
			  );
	}
	else
	{
		MACRO_PRINTF(("u8Transfert_StructToFile: ERREUR DEFINITION FICHIER\n"));
		loc_u8_return = FALSE;
	}

	return loc_u8_return;
} /*u8Transfert_StructToFile*/

//=====================================================================================
// Fonction		: u8Transfert_FileToStruct
// Entrees		: <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE lecture OK / FALSE lecture KO
// Auteur		: CM - 24/09/2009 -
// Description	: Tranfert les données contenues dans le fichier vers la structure
//=====================================================================================
u8sod u8Transfert_FileToStruct(void *loc_pt_structure, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_return; 
	u8sod	loc_u8_cpt_essai;

	loc_u8_return = TRUE;	//INIT
	loc_u8_cpt_essai = 0;	//INIT

	if(loc_pt_def_file != NULL)
	{
		do{
			// Ouverture du fichier 
			if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt" )))
			{
				MACRO_PRINTF(("u8Transfert_FileToStruct: Impossible d'ouvrir le fichier %s\n",
							 loc_pt_def_file->ps8_path_file));
				loc_u8_return = FALSE;
			}
			else
			{
				// Lecture du fichier 
				if(loc_pt_def_file->pt_contenu != NULL)
				{

					loc_u8_return = u8BddFileScanf(loc_p_handle,
												   (T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
												   loc_pt_structure,
												   loc_pt_def_file->u8_avec_checksum);
					if(FALSE == loc_u8_return)
					{
						MACRO_PRINTF(("u8Transfert_FileToStruct: Erreur dans fichier %s\n",
									  loc_pt_def_file->ps8_path_file));
					}
				}
				else
				{
					loc_u8_return = FALSE;
					MACRO_PRINTF(("u8Transfert_StructToFile: Contenu INDEFINI dans fichier %s\n",
								  loc_pt_def_file->ps8_path_file));
				}

				//fermeture du fichier
				fclose (loc_p_handle);
			}
			
			loc_u8_cpt_essai ++;
		}while( (FALSE == loc_u8_return) &&
				(loc_u8_cpt_essai<ESSAI_MAX_ACCES_FILE)
			  );
	}
	else
	{
		MACRO_PRINTF(("u8Transfert_FileToStruct: ERREUR DEFINITION FICHIER\n"));
		loc_u8_return = FALSE;
	}

	return loc_u8_return;
}/*u8Transfert_FileToStruct*/

//=====================================================================================
// Fonction		: u8Display_FileToStruct
// Entrees		: <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE lecture OK / FALSE lecture KO
// Auteur		: CM - 24/09/2009 -
// Description	: Affichage printf d'une structure à partir du contenu du fichier
//=====================================================================================
u8sod u8Display_FileToStruct(void *loc_pt_structure, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_return; 
	u8sod	loc_u8_cpt_essai;

	loc_u8_return = TRUE;	//INIT
	loc_u8_cpt_essai = 0;	//INIT

	if(loc_pt_def_file != NULL)
	{
		MACRO_PRINTF(("******** DEBUT LECTURE FICHIER: %s \n",
					  loc_pt_def_file->ps8_path_file));
		
		do{
			// Ouverture du fichier 
			if(NULL == (loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt" )))
			{
				MACRO_PRINTF(("u8Display_FileToStruct: Impossible d'ouvrir le fichier %s\n",
							   loc_pt_def_file->ps8_path_file));
				loc_u8_return = FALSE;
			}
			else
			{
				// Lecture du fichier 
				if(loc_pt_def_file->pt_contenu != NULL)
				{
					loc_u8_return = u8BddFileScanf(loc_p_handle,
												   (T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
												   loc_pt_structure,
												   loc_pt_def_file->u8_avec_checksum);
					if(FALSE == loc_u8_return)
					{
						MACRO_PRINTF(("u8Display_FileToStruct: Erreur dans fichier %s\n",
									  loc_pt_def_file->ps8_path_file));
					}
					else
					{
						BddFile_DisplayFieldValue((T_STRUCT_FILE_FIELD *)loc_pt_def_file->pt_contenu,
												  loc_pt_structure);
					}
				}
				else
				{
					loc_u8_return = FALSE;
					MACRO_PRINTF(("u8Display_FileToStruct: Contenu INDEFINI dans fichier %s\n",
								  loc_pt_def_file->ps8_path_file));
				}

				//fermeture du fichier
				fclose (loc_p_handle);
			}
			
			loc_u8_cpt_essai ++;
		}while( (FALSE == loc_u8_return) &&
				(loc_u8_cpt_essai<ESSAI_MAX_ACCES_FILE)
			  );

		MACRO_PRINTF(("******** FIN LECTURE FICHIER \n"));
		
	}
	else
	{
		MACRO_PRINTF(("u8Display_FileToStruct: ERREUR DEFINITION FICHIER\n"));
		loc_u8_return = FALSE;
	}

	return loc_u8_return;
}/*u8Display_FileToStruct*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_BddSystemFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de bddsystemfile
//=====================================================================================
void InitModule_BddSystemFile(void)
{

}/*InitModule_BddSystemFile*/

