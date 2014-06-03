/*========================================================================*/
/* NOM DU FICHIER  : cmdsystem.c   		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: liste des commandes system		  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Ajout fonction pour calculer le nombre de ligne d'un fichier (commande linux)
// - Ajout fonction pour supprimer fichier (commande linux)
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE034 28/06/2010 CM
// - Correction bug commande pidof
//	sur AP apparition message "sh: cannot kill pid xxxxx: No such process" apparait de temps en temps
//	=> le défaut est lié à la commande "pidof" qui retourne plusieurs PIDs erronés
//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
// - Creation de la library static LibrarySystem
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE050 09/12/2010 CM
// - Correction fonction s32GetPidProcessus
//	=> retourne un seul PID -> via commande pidof -s
//BE053 16/12/2010 CM
// - Désactivation de la gestion de l'heure dans la FLASH NOR
// - Correction bug commande pidof via hostapd
//BE060 16/03/2011
// - Ajout fonction qui liste les fichiers dans répertoire
// - Ajout fonction qui calcule la taille d'un fichier
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CMDSYSTEM

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

#define TAILLE_MAX_LIGNE_COMMAND_WC		100

#define TAILLE_MAX_COMMANDE_SYSTEM	1500
static s8sod	ps8_commande_system[TAILLE_MAX_COMMANDE_SYSTEM+1];

#define TAILLE_MAX_LIGNE_PROCESSUS_PID	16

#define NB_MAX_FILE_In_DIRECTORY	100

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CmdSystem_Generique
// Entrees		: <loc_ps8_fmtp< : format
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 03/10/2008 -
// Description	: Execute la commande système
//=====================================================================================
void CmdSystem_Generique(s8sod *loc_ps8_fmtp, ...)
{
	va_list loc_t_argp;
	u16sod	loc_u16_n;

	va_start(loc_t_argp, loc_ps8_fmtp);
	loc_u16_n = vsnprintf(ps8_commande_system, TAILLE_MAX_COMMANDE_SYSTEM, loc_ps8_fmtp, loc_t_argp);

	if((0<loc_u16_n) && (loc_u16_n < TAILLE_MAX_COMMANDE_SYSTEM))	//CONDITION: nb caractères OK
	{
		if(strlen(ps8_commande_system) < TAILLE_MAX_COMMANDE_SYSTEM)
		{
			system(ps8_commande_system);
		}
	}
}/*CmdSystem_Generique*/

//=====================================================================================
// Fonction		: u8CmdSystem_RemoveFile
// Entrees		: <loc_ps8_file_remove< : chemin du fichier à supprimer
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 02/03/2010 -
// Description	: Supprime fichier si existe
//=====================================================================================
u8sod u8CmdSystem_RemoveFile(s8sod *loc_ps8_file_remove)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_cpt_essai;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0;	//INIT
	
	if(loc_ps8_file_remove!=NULL)
	{
		//On teste si il y a déjà un fichier dst présent
		if(NULL != (loc_p_handle = fopen( loc_ps8_file_remove, "r" )))
		{
			//fichier bien présent
			fclose (loc_p_handle);

			//on supprime le fichier 
			CmdSystem_Generique("rm %s",
								loc_ps8_file_remove);

			//On vérifie que le fichier est bien supprimé
			if(NULL == (loc_p_handle = fopen( loc_ps8_file_remove, "r" )))
			{
				loc_u8_resultat = TRUE;
			}
			else
			{
				//fichier toujours présent 
				fclose (loc_p_handle);
				pf_functionPrintf("u8CmdSystem_RemoveFile: Impossible de supprimer fichier %s \n",
							  loc_ps8_file_remove);
			}
		}
		else //CONDITION: Fichier à supprimer non présent
		{
			loc_u8_resultat = TRUE;
		}
	}


	return loc_u8_resultat;
}/*u8CmdSystem_RemoveFile*/

//=====================================================================================
// Fonction		: u8CmdSystem_CopyFile
// Entrees		: <loc_ps8_file_src< : chemin du fichier source
// Entrees		: <loc_ps8_file_dst< : chemin du fichier destination
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 03/10/2008 -
// Description	: Copie fichier scr vers fichier dst
//=====================================================================================
u8sod u8CmdSystem_CopyFile(s8sod *loc_ps8_file_src, s8sod *loc_ps8_file_dst)
{
	FILE	*loc_p_handle;
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_cpt_essai;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0;	//INIT

	if(	(loc_ps8_file_src!=NULL) && (loc_ps8_file_dst!=NULL))
	{
		if(0 != strcmp(loc_ps8_file_src,loc_ps8_file_dst))
		{
			do{

				//**Etape 1: On teste si il y a déjà un fichier dst présent
				if(NULL != (loc_p_handle = fopen( loc_ps8_file_dst, "r" )))
				{
					//fichier bien présent
					fclose (loc_p_handle);
					
					//on supprime le fichier dst
					CmdSystem_Generique("rm %s",
										loc_ps8_file_dst);
				}

				//**Etape 2: On vérifie que le fichier dst est bien supprimé
				if(NULL == (loc_p_handle = fopen( loc_ps8_file_dst, "r" )))
				{
					//on copie src => dst
					CmdSystem_Generique("cp %s %s",
										loc_ps8_file_src,
										loc_ps8_file_dst);

					//**Etape 3: On vérifie que le fichier dst a bien été copié
					if(NULL == (loc_p_handle = fopen( loc_ps8_file_dst, "r" )))
					{
						//fichier absent (probleme de copy!!!)
						pf_functionPrintf("u8CmdSystem_CopyFile: Impossible de copier le fichier %s \n",
										  loc_ps8_file_dst);
						loc_u8_resultat = FALSE;
					}
					else
					{
						//fichier bien présent
						fclose (loc_p_handle);
						loc_u8_resultat = TRUE;
					}
				}
				else
				{
					//fichier toujours présent 
					fclose (loc_p_handle);
					pf_functionPrintf("u8CmdSystem_CopyFile: Impossible de supprimer ancien fichier %s \n",
									  loc_ps8_file_dst);
					loc_u8_resultat = FALSE;
				}


				loc_u8_cpt_essai ++;
			}while( (FALSE == loc_u8_resultat) &&
					(loc_u8_cpt_essai<2)
				  );
		}
		else
		{
			pf_functionPrintf("u8CmdSystem_CopyFile: Probleme argument [1] \n");
			loc_u8_resultat = TRUE;
		}
	}
	else
	{
		pf_functionPrintf("u8CmdSystem_CopyFile: Probleme argument [2] \n");
	}
	
	
	return loc_u8_resultat;
}/*u8CmdSystem_CopyFile*/

//=====================================================================================
// Fonction		: u32GetSizeOfFile
// Entrees		: <loc_ps8_name_file< : nom du fichier
// Sortie		: <loc_u32_size< : Taille du fichier en octets
// Auteur		: CM - 13/11/2009 -
// Description	: Retourne la taille du fichier
//=====================================================================================
u32sod u32GetSizeOfFile(s8sod *loc_ps8_name_file)
{
	u32sod loc_u32_size;
	struct stat loc_t_statfile;

	loc_u32_size = 0;	//INIT
	memset(&loc_t_statfile, 0, sizeof(struct stat)); //INIT

	if(loc_ps8_name_file!= NULL)
	{
		if(0 == stat(loc_ps8_name_file,&loc_t_statfile))
		{
			loc_u32_size = (u32sod)loc_t_statfile.st_size;
		}
	}
	
	return loc_u32_size;	
}/*u32GetSizeOfFile*/

//=====================================================================================
// Fonction		: s32GetPidProcessus
// Entrees		: <loc_ps8_nom_processus< : nom du processus
//				  <loc_ps8_fileofpid<	  : chemin du fichier résultat du pid
// Sortie		: <loc_s32_pid> : PID du processus (<0,si impossible)
// Auteur		: CM - 26/11/2009 -
// Description	: Retourne le PID du processus
//=====================================================================================
s32sod s32GetPidProcessus(s8sod *loc_ps8_nom_processus, s8sod *loc_ps8_fileofpid)
{
	s32sod loc_s32_pid;
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_cpt_essai;
	
	loc_s32_pid = -1; //INIT
	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0;	//INIT

	do
	{
		//On copie le PID du processus dans le fichier xxxxx.pid
		CmdSystem_Generique("pidof -s %s > %s",
							loc_ps8_nom_processus,
							loc_ps8_fileofpid);

		//On lit la valeur du PID du processus
		loc_s32_pid = s32ReadPid_InFile(loc_ps8_fileofpid);
		if(loc_s32_pid > 0)
		{
			loc_u8_resultat = TRUE;	//lecture OK
		}
		
		loc_u8_cpt_essai ++;
	}while( (FALSE == loc_u8_resultat) &&
			(loc_u8_cpt_essai<3)
		  );

	return loc_s32_pid;
}/*s32GetPidProcessus*/

//=====================================================================================
// Fonction		: u32GetNumberLineFile
// Entrees		: <loc_ps8_name_file< : nom du fichier à calculer
//				: <loc_ps8_file_tmp< : nom du fichier temporaire
// Sortie		: <loc_u32_nb_line< : Nombre de lignes du fichier à calculer
// Auteur		: CM - 02/03/2010 -
// Description	: Retourne le nombre de lignes du fichier à calculer
//=====================================================================================
u32sod u32GetNumberLineFile(s8sod *loc_ps8_name_file,s8sod *loc_ps8_file_tmp)
{
	FILE	*loc_p_handle;
	u32sod loc_u32_nb_line;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_COMMAND_WC+1];
	s32sod loc_s32_sscanf;

	loc_p_handle = NULL;	//INIT
	loc_u32_nb_line = 0;	//INIT
	strcpy(loc_ps8_ligne, "");	//INIT
	loc_s32_sscanf = 0;	//INIT

	if(NULL != (loc_p_handle = fopen( loc_ps8_name_file, "r" ))) //CONDITION: Fichier présent
	{
		//fermeture du fichier
		fclose (loc_p_handle);
		
		//Retourne le nombre de ligne dans fichier temporaire
		CmdSystem_Generique("wc -l %s > %s",
							loc_ps8_name_file,
							loc_ps8_file_tmp);

		//Lecture du fichier temporaire
		if(NULL == (loc_p_handle = fopen( loc_ps8_file_tmp, "rt" )))
		{
			pf_functionPrintf("u32GetNumberLineFile: erreur lecture fichier temporaire \n");
		}
		else
		{
			if(NULL != fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_PROCESSUS_PID,loc_p_handle)) //CONDITION: ligne lue 
			{
				loc_s32_sscanf = sscanf(loc_ps8_ligne, " %9lu", &loc_u32_nb_line);
				if(1 != loc_s32_sscanf) //CONDITION: erreur lecture
				{
					loc_u32_nb_line = 0;
					pf_functionPrintf("u32GetNumberLineFile: erreur données dans fichier temporaire \n");
				}
			}
			
			//fermeture du fichier
			fclose (loc_p_handle);
		}

		//Puis suppression du fichier résultat
		u8CmdSystem_RemoveFile(loc_ps8_file_tmp);
	}

	//On tronque (au maxi sur 16bits) au cas où
	if(loc_u32_nb_line > 0xFFFF)
	{
		loc_u32_nb_line = 0xFFFF;
	}
	
	return loc_u32_nb_line;	
}/*u32GetNumberLineFile*/

//=====================================================================================
// Fonction		: CmdSysteme_MiseAHeure
// Entrees		: <loc_ps_date<: date
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Mise à l'heure du systeme
//=====================================================================================
void CmdSysteme_MiseAHeure(S_STRUCT_DATE *loc_ps_date)
{
	CmdSystem_Generique("date -s %04d.%02d.%02d-%02d:%02d:%02d",
						loc_ps_date->u16_annee,loc_ps_date->u8_mois,loc_ps_date->u8_jour,
						loc_ps_date->u8_heure,loc_ps_date->u8_minute,loc_ps_date->u8_seconde);

}/*CmdSysteme_MiseAHeure*/

//=====================================================================================
// Fonction		: CmdSysteme_MiseAHeure_Par_Defaut
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/12/2010 -
// Description	: Mise à l'heure du systeme par défaut
//=====================================================================================
void CmdSysteme_MiseAHeure_Par_Defaut(void)
{
	S_STRUCT_DATE loc_s_date;
	
	InitStructDate(&loc_s_date);	//INIT
	loc_s_date = S_DATE_DEFAUT;	//INIT
	CmdSysteme_MiseAHeure(&loc_s_date);

}/*CmdSysteme_MiseAHeure_Par_Defaut*/

//=====================================================================================
// Fonction		: u8CmdSystem_ChmodFile
// Entrees		: <loc_ps8_file< : chemin du fichier
//				: <loc_t_permission> : permission
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 05/07/2010 -
// Description	: Change permission fichier
//=====================================================================================
u8sod u8CmdSystem_ChmodFile(s8sod *loc_ps8_file, mode_t loc_t_permission)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT
	if(0 != chmod(loc_ps8_file, loc_t_permission))
	{
		loc_u8_resultat = FALSE;
		pf_functionPrintf("u8CmdSystem_ChmodFile: Erreur chmod sur fichier %s\n",loc_ps8_file);
	}

	return loc_u8_resultat;
}/*u8CmdSystem_ChmodFile*/

//=====================================================================================
// Fonction		: u8CmdSystem_PresenceFile
// Entrees		: <loc_ps8_file< : chemin du fichier 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 17/12/2010 -
// Description	: Test présence fichier
//=====================================================================================
u8sod u8CmdSystem_PresenceFile(s8sod *loc_ps8_file)
{
	u8sod loc_u8_resultat;
	FILE	*loc_p_handle;

	loc_u8_resultat = FALSE;	//INIT
	loc_p_handle = NULL;	//INIT

	if(NULL != (loc_p_handle = fopen( loc_ps8_file, "r" ))) //CONDITION: Fichier présent
	{
		//fermeture du fichier
		fclose (loc_p_handle);
		loc_u8_resultat = TRUE;
	}
	
	return loc_u8_resultat;
}/*u8CmdSystem_PresenceFile*/

//=====================================================================================
// Fonction		: s32ReadPid_InFile
// Entrees		: <loc_ps8_fileofpid<	  : chemin du fichier résultat du pid
// Sortie		: <loc_s32_pid> : PID du processus (<0,si impossible)
// Auteur		: CM - 17/12/2010 -
// Description	: Retourne le PID lu dans fichier
//=====================================================================================
s32sod s32ReadPid_InFile(s8sod *loc_ps8_fileofpid)
{
	FILE	*loc_p_handle;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_PROCESSUS_PID+1];
	s32sod loc_s32_pid;
	s32sod loc_s32_sscanf;

	strcpy(loc_ps8_ligne, ""); //INIT
	loc_s32_pid = -1; //INIT
	loc_s32_sscanf = 0;	//INIT

	//On lit la valeur du PID du processus
	if(NULL != (loc_p_handle = fopen( loc_ps8_fileofpid, "r" )))
	{
		if(NULL != fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_PROCESSUS_PID,loc_p_handle)) //CONDITION: ligne lue 
		{
			if(NULL == strstr(loc_ps8_ligne, " ")) //CONDITION: ligne sans espace ' '
			{
				loc_s32_sscanf = sscanf(loc_ps8_ligne, "%ld", &loc_s32_pid);
				if(1 != loc_s32_sscanf)
				{
					loc_s32_pid = -1;	//KO
				}
			}
		}

		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_s32_pid;
}/*s32ReadPid_InFile*/

//=====================================================================================
// Fonction		: u8CmdSystem_ListFileInDirectory
// Entrees		: <loc_ps8_path_repertoire< : chemin du repertoire
//				: <loc_ps_tab_file< : liste des noms de fichiers (pointeur sur tableau)
//				: <loc_u16_size_tab_file> : taille max du tableau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 05/07/2010 -
// Description	: Liste les fichiers dans un répertoire
//=====================================================================================
u8sod u8CmdSystem_ListFileInDirectory(s8sod *loc_ps8_path_repertoire, S_STRUCT_SYST_FILE *loc_ps_tab_file, u16sod loc_u16_size_tab_file)
{
	u8sod	loc_u8_resultat;
	struct dirent *loc_ps_lecture;
	DIR		*loc_pd_rep;
	FILE	*loc_pf_file;
	u16sod	loc_u16_cpt_file;
	u16sod	loc_u16_boucle;
	u16sod	loc_u16_i;
	s8sod	loc_ps8_path_complet_file[2*LG_MAX_PATH_SYST_FILE+1]; //2*: car c'est le chemin

	loc_u8_resultat = TRUE;	//INIT
	loc_u16_cpt_file = 0;	//INIT
	loc_u16_boucle = 0; //INIT
	for(loc_u16_i=0;loc_u16_i<NB_MAX_CERTIFICATS;loc_u16_i++)
	{
		RazSystFile(&loc_ps_tab_file[loc_u16_i]); //INIT
	}
	strcpy(loc_ps8_path_complet_file,"");	//INIT
	
	if(NULL != loc_ps8_path_repertoire)
	{
		if(NULL != (loc_pd_rep = opendir(loc_ps8_path_repertoire)))
		{
//			pf_functionPrintf("u8CmdSystem_ListFileInDirectory: Lecture dans %s\n",loc_ps8_path_repertoire);
			while ((loc_u16_cpt_file < loc_u16_size_tab_file)&&
				   (loc_u16_boucle < NB_MAX_FILE_In_DIRECTORY)&&
				   (TRUE == loc_u8_resultat)
				  )
			{
				loc_ps_lecture = readdir(loc_pd_rep);
				if(NULL != loc_ps_lecture)
				{
					loc_u16_boucle++;
					if(DT_REG == loc_ps_lecture->d_type) //CONDTIION: type fichier
					{
						strcpy(loc_ps8_path_complet_file,"");	//RAZ
						strcat(loc_ps8_path_complet_file, loc_ps8_path_repertoire);
						strcat(loc_ps8_path_complet_file, loc_ps_lecture->d_name);
						//Test ouverture
						if(NULL != (loc_pf_file = fopen(loc_ps8_path_complet_file, "rt")))
						{
							fclose(loc_pf_file);
							if(strlen(loc_ps_lecture->d_name) < LG_MAX_PATH_SYST_FILE)
							{
								strcpy(loc_ps_tab_file[loc_u16_cpt_file].ps8_nom, loc_ps_lecture->d_name);
								//puis on calule la taille du fichier
								loc_ps_tab_file[loc_u16_cpt_file].u32_sizeoffile = u32CmdSystem_GetSizeFile(loc_ps8_path_complet_file);
							}
							loc_u16_cpt_file++;
						}
						else
						{
							pf_functionPrintf("u8CmdSystem_ListFileInDirectory: Erreur lecture fichier %s (errno=%d)\n",
											  loc_ps_lecture->d_name,
											  errno);
							loc_u8_resultat = FALSE;
						}
					}
				}
				else
				{
					//on sort
					loc_u16_boucle = NB_MAX_FILE_In_DIRECTORY+1;
				}
			}
			closedir(loc_pd_rep);
		}
	}
	else
	{
		pf_functionPrintf("u8CmdSystem_ListFileInDirectory: Erreur répertoire NULL\n");
		loc_u8_resultat = FALSE;
	}
	

	return loc_u8_resultat;
}/*u8CmdSystem_ListFileInDirectory*/

//=====================================================================================
// Fonction		: u32CmdSystem_GetSizeFile
// Entrees		: <loc_ps8_file< : chemin du fichier
// Sortie		: <loc_u32_size>  : taille en octes
// Auteur		: CM - 23/03/2011 -
// Description	: Calcule la taille d'un fichier en octets
//=====================================================================================
u32sod u32CmdSystem_GetSizeFile(s8sod *loc_ps8_file)
{
	FILE	*loc_p_handle;
	u32sod	loc_u32_size;

	loc_u32_size = 0;	//INIT

	if(NULL != (loc_p_handle = fopen( loc_ps8_file, "r" ))) //CONDITION: Fichier présent
	{
		//On se positionne à la fin du fichier
		if(0 == fseek(loc_p_handle,0,SEEK_END))
		{
			//On détermine la position du pointeur (qui correspond à la taille)
			loc_u32_size = ftell(loc_p_handle);
		}
		
		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u32_size;
}/*u32CmdSystem_GetSizeFile*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: RazSystFile
// Entrees		: <loc_ps_syst_file<: pointeur sur fichier du systeme
// Sortie		: rien
// Auteur		: CM - 23/03/2011 -
// Description	: Raz du syst file
//=====================================================================================
void RazSystFile(S_STRUCT_SYST_FILE *loc_ps_syst_file)
{
	strcpy(loc_ps_syst_file->ps8_nom, "");	//RAZ
	loc_ps_syst_file->u32_sizeoffile = 0;	//RAZ

}/*RazSystFile*/

//=====================================================================================
// Fonction		: InitModule_CmdSystem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de cmdsystem
//=====================================================================================
void InitModule_CmdSystem(void)
{
	strcpy(ps8_commande_system, "");	//INIT
	
}/*InitModule_CmdSystem*/

