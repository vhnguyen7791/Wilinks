/*========================================================================*/
/* NOM DU FICHIER  : bddsystemfile.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
/* Libelle         : Base de données: système des fichiers				  */
/* Projet          : WRM100                                               */
/* Indice          : BE006                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE006 20/01/2010 CM
// - Modification gestion couche haute des fichiers
//		modif appel u8Transfert_StructToFile, u8Transfert_FileToStruct, u8Display_FileToStruct
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _BDDSYSTEMFILE
#define _BDDSYSTEMFILE_EXT
#else
#define _BDDSYSTEMFILE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: u8Transfert_StructToFile
// Entrees		: <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE écriture OK / FALSE écriture KO
// Auteur		: CM - 24/09/2009 -
// Description	: Tranfert les données contenues dans la structure dans le fichier
//=====================================================================================
u8sod u8Transfert_StructToFile(void *loc_pt_structure, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);

//=====================================================================================
// Fonction		: u8Transfert_FileToStruct
// Entrees		: <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE lecture OK / FALSE lecture KO
// Auteur		: CM - 24/09/2009 -
// Description	: Tranfert les données contenues dans le fichier vers la structure
//=====================================================================================
u8sod u8Transfert_FileToStruct(void *loc_pt_structure, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);

//=====================================================================================
// Fonction		: u8Display_FileToStruct
// Entrees		: <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_pt_def_file< : pointeur sur définition du fichier
// Sortie		: <loc_u8_return>: TRUE lecture OK / FALSE lecture KO
// Auteur		: CM - 24/09/2009 -
// Description	: Affichage printf d'une structure à partir du contenu du fichier
//=====================================================================================
u8sod u8Display_FileToStruct(void *loc_pt_structure, T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file);

//=====================================================================================
// Fonction		: InitModule_BddSystemFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de bddsystemfile
//=====================================================================================
void InitModule_BddSystemFile(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/



