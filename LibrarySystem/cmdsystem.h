/*========================================================================*/
/* NOM DU FICHIER  : cmdsystem.h			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
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
//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE053 16/12/2010 CM
// - Désactivation de la gestion de l'heure dans la FLASH NOR
// - Correction bug commande pidof via hostapd
//BE060 16/03/2011
// - Ajout fonction qui liste les fichiers dans répertoire
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _CMDSYSTEM
#define _CMDSYSTEM_EXT
#else
#define _CMDSYSTEM_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: CmdSystem_Generique
// Entrees		: <loc_ps8_fmtp< : format
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 03/10/2008 -
// Description	: Execute la commande système
//=====================================================================================
void CmdSystem_Generique(s8sod *loc_ps8_fmtp, ...);

//=====================================================================================
// Fonction		: u8CmdSystem_RemoveFile
// Entrees		: <loc_ps8_file_remove< : chemin du fichier à supprimer
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 02/03/2010 -
// Description	: Supprime fichier si existe
//=====================================================================================
u8sod u8CmdSystem_RemoveFile(s8sod *loc_ps8_file_remove);

//=====================================================================================
// Fonction		: u8CmdSystem_CopyFile
// Entrees		: <loc_ps8_file_src< : chemin du fichier source
// Entrees		: <loc_ps8_file_dst< : chemin du fichier destination
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 03/10/2008 -
// Description	: Copie fichier scr vers fichier dst
//=====================================================================================
u8sod u8CmdSystem_CopyFile(s8sod *loc_ps8_file_src, s8sod *loc_ps8_file_dst);

//=====================================================================================
// Fonction		: u32GetSizeOfFile
// Entrees		: <loc_ps8_name_file< : nom du fichier
// Sortie		: <loc_u32_size< : Taille du fichier en octets
// Auteur		: CM - 13/11/2009 -
// Description	: Retourne la taille du fichier
//=====================================================================================
u32sod u32GetSizeOfFile(s8sod *loc_ps8_name_file);

//=====================================================================================
// Fonction		: s32GetPidProcessus
// Entrees		: <loc_ps8_nom_processus< : nom du processus
//				  <loc_ps8_fileofpid<	  : chemin du fichier résultat du pid
// Sortie		: <loc_s32_pid> : PID du processus (<0,si impossible)
// Auteur		: CM - 26/11/2009 -
// Description	: Retourne le PID du processus
//=====================================================================================
s32sod s32GetPidProcessus(s8sod *loc_ps8_nom_processus, s8sod *loc_ps8_fileofpid);

//=====================================================================================
// Fonction		: u32GetNumberLineFile
// Entrees		: <loc_ps8_name_file< : nom du fichier à calculer
//				: <loc_ps8_file_tmp< : nom du fichier temporaire
// Sortie		: <loc_u32_nb_line< : Nombre de lignes du fichier à calculer
// Auteur		: CM - 02/03/2010 -
// Description	: Retourne le nombre de lignes du fichier à calculer
//=====================================================================================
u32sod u32GetNumberLineFile(s8sod *loc_ps8_name_file,s8sod *loc_ps8_file_tmp);

//=====================================================================================
// Fonction		: CmdSysteme_MiseAHeure
// Entrees		: <loc_ps_date<: date
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Mise à l'heure du systeme
//=====================================================================================
void CmdSysteme_MiseAHeure(S_STRUCT_DATE *loc_ps_date);

//=====================================================================================
// Fonction		: CmdSysteme_MiseAHeure_Par_Defaut
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/12/2010 -
// Description	: Mise à l'heure du systeme par défaut
//=====================================================================================
void CmdSysteme_MiseAHeure_Par_Defaut(void);

//=====================================================================================
// Fonction		: u8CmdSystem_ChmodFile
// Entrees		: <loc_ps8_file< : chemin du fichier
//				: <loc_t_permission> : permission
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 05/07/2010 -
// Description	: Change permission fichier
//=====================================================================================
u8sod u8CmdSystem_ChmodFile(s8sod *loc_ps8_file, mode_t loc_t_permission);

//=====================================================================================
// Fonction		: u8CmdSystem_PresenceFile
// Entrees		: <loc_ps8_file< : chemin du fichier 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 17/12/2010 -
// Description	: Test présence fichier
//=====================================================================================
u8sod u8CmdSystem_PresenceFile(s8sod *loc_ps8_file);

//=====================================================================================
// Fonction		: s32ReadPid_InFile
// Entrees		: <loc_ps8_fileofpid<	  : chemin du fichier résultat du pid
// Sortie		: <loc_s32_pid> : PID du processus (<0,si impossible)
// Auteur		: CM - 17/12/2010 -
// Description	: Retourne le PID lu dans fichier
//=====================================================================================
s32sod s32ReadPid_InFile(s8sod *loc_ps8_fileofpid);

//=====================================================================================
// Fonction		: u8CmdSystem_ListFileInDirectory
// Entrees		: <loc_ps8_path_repertoire< : chemin du repertoire
//				: <loc_ps_tab_file< : liste des noms de fichiers (pointeur sur tableau)
//				: <loc_u16_size_tab_file> : taille max du tableau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 05/07/2010 -
// Description	: Liste les fichiers dans un répertoire
//=====================================================================================
u8sod u8CmdSystem_ListFileInDirectory(s8sod *loc_ps8_path_repertoire, S_STRUCT_SYST_FILE *loc_ps_tab_file, u16sod loc_u16_size_tab_file);

//=====================================================================================
// Fonction		: u32CmdSystem_GetSizeFile
// Entrees		: <loc_ps8_file< : chemin du fichier
// Sortie		: <loc_u32_size>  : taille en octes
// Auteur		: CM - 23/03/2011 -
// Description	: Calcule la taille d'un fichier en octets
//=====================================================================================
u32sod u32CmdSystem_GetSizeFile(s8sod *loc_ps8_file);

//=====================================================================================
// Fonction		: RazSystFile
// Entrees		: <loc_ps_syst_file<: pointeur sur fichier du systeme
// Sortie		: rien
// Auteur		: CM - 23/03/2011 -
// Description	: Raz du syst file
//=====================================================================================
void RazSystFile(S_STRUCT_SYST_FILE *loc_ps_syst_file);

//=====================================================================================
// Fonction		: InitModule_CmdSystem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de cmdsystem
//=====================================================================================
void InitModule_CmdSystem(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

