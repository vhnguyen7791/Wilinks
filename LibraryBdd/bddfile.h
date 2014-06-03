/*========================================================================*/
/* NOM DU FICHIER  : bddfile.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
/* Libelle         : Base de données: gestion des fichiers de la BDD	  */
/* Projet          : WRM100                                               */
/* Indice          : BE014                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Ajout type FTYPVAL_DATE dans gestion des fichiers
// - Ajout fonction lecture / écriture dans fichier ligne par ligne
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall"
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _BDDFILE
#define _BDDFILE_EXT
#else
#define _BDDFILE_EXT	extern
#endif

//Taille maximum d'une ligne du fichier
//be0.63: passage avec addresse IP en notation pointee : on agrandit les lignes surtout pour les politiques de routage
//#define	TAILLE_MAX_LIGNE_BDDFILE		500
#define	TAILLE_MAX_LIGNE_BDDFILE		530

//Longueur maximale du nom du CHAMP
#define	LG_MAX_FIELD_NAME		TAILLE_MAX_LIGNE_BDDFILE
//Longueur maximale de la valeur du CHAMP
#define LG_MAX_FIELD_VALUE		TAILLE_MAX_LIGNE_BDDFILE

//Nombre maximum de champs dans un fichier
#define	NB_MAX_FIELDS_BDDFILE			1000

//Nombre maximum de champs dans une structure
#define	NB_MAX_FIELDS_STRUCT			50

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: u8PrintFieldValueSimple
// Entrees		: <loc_ps_one_field< : pointeur sur un champs du fichier
//				  <loc_pt_variable<	: pointeur sur variable de la structure
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui édite le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8PrintFieldValueSimple(T_STRUCT_FILE_FIELD *loc_ps_one_field, void *loc_pt_variable);

//=====================================================================================
// Fonction		: u8PrintFieldValueComplex
// Entrees		: <loc_u16_idx>	: index du tableau
//				  <loc_ps8_name<: nom du tableau
//				  <loc_ps_list_complex<: pointeur sur list complex
//				  <loc_pt_tabstruct<: pointeur sur premier élément du tableau de structure
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui édite le contenu du fichier avec des lignes de type
//					  "|idx=xx|nom1=val1|...|nomN=valN|"
//=====================================================================================
u8sod u8PrintFieldValueComplex(u16sod loc_u16_idx, s8sod *loc_ps8_name, T_STRUCT_FILE_FIELD *loc_ps_list_complex, void *loc_pt_tabstruct);

//=====================================================================================
// Fonction		: BddFile_DisplayFieldValue
// Entrees		: <loc_ps_field_list<	: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
// Sortie		: void
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui affiche sur la console les valeurs associées au fichier
//=====================================================================================
void BddFile_DisplayFieldValue(T_STRUCT_FILE_FIELD *loc_ps_field_list, void *loc_pt_structure);

//=====================================================================================
// Fonction		: u8BddFilePrintf
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_presence_checksum>: Présence du checksum (TRUE ou FALSE)
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui édite le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFilePrintf(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u8sod loc_u8_presence_checksum);

//=====================================================================================
// Fonction		: u8BddFileScanf
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_verif_checksum>: vérification du checksum (TRUE ou FALSE)
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui lit le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFileScanf(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u8sod loc_u8_verif_checksum);

//=====================================================================================
// Fonction		: u8ScanFieldValueSimple
// Entrees		: <loc_ps_one_field<	: pointeur sur un champs du fichier
//				  <loc_pt_variable<: pointeur sur la variable de la structure
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction extrait le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8ScanFieldValueSimple(T_STRUCT_FILE_FIELD *loc_ps_one_field, void *loc_pt_variable, s8sod *loc_ps8_valeur);

//=====================================================================================
// Fonction		: u8ScanFieldValueComplex
// Entrees		: <loc_pt_contenu_elt<	: pointeur sur la définition du contenu  du tableau
//				  <loc_u16_taille_elt>  : taille élément du tableau
//				  <loc_u16_nb_max_elt>  : taille maximum du tableau
//				  <loc_pt_tabstruct<: pointeur sur premier élément du tableau de structure
//				  <loc_ps8_complex_valeur<: chaine de caractères
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui extrait le contenu du fichier avec des lignes de type
//					  "|idx=xx|nom1=val1|...|nomN=valN|"
//=====================================================================================
u8sod u8ScanFieldValueComplex(T_STRUCT_FILE_FIELD *loc_pt_contenu_elt, u16sod loc_u16_taille_elt, u16sod loc_u16_nb_max_elt, void *loc_pt_tabstruct, s8sod *loc_ps8_complex_valeur);

//=====================================================================================
// Fonction		: u8BddFile_Decode
// Entrees		: <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_ps8_ligne_code<	: ligne du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_verif_checksum>: vérification du checksum (TRUE ou FALSE)
//				  >loc_pps_next_list<	: pointeur sur le prochain de la liste
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Decode ligne du fichier au format suivant
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFile_Decode(T_STRUCT_FILE_FIELD *loc_ps_list, s8sod *loc_ps8_ligne_code, void *loc_pt_structure, u8sod loc_u8_verif_checksum, T_STRUCT_FILE_FIELD **loc_pps_next_list);

//=====================================================================================
// Fonction		: u8BddFile_WriteLine
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure<	: pointeur sur structure contenant les données
//				  <loc_pu16_idx<		: pointeur sur index
//				  <loc_pu8_suivant<		: pointeur sur suivant
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 02/03/2010 -
// Description	: Fonction qui édite une seule ligne
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFile_WriteLine(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u16sod *loc_pu16_idx, u8sod *loc_pu8_suivant);

//=====================================================================================
// Fonction		: u8BddFile_ReadLine
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_verif_checksum>: vérification du checksum (TRUE ou FALSE)
//				  <loc_pu8_isEndOfFile<	: pointeur sur info "fin de fichier" (signalé avec val
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 02/03/2010 -
// Description	: Fonction qui lit une seule ligne du fichier de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFile_ReadLine(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u8sod loc_u8_verif_checksum, u8sod *loc_pu8_isEndOfFile);

//=====================================================================================
// Fonction		: InitModule_BddFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de BddFile
//=====================================================================================
void InitModule_BddFile(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _BDDFILE
//Définition du tableau de u8sod
const T_STRUCT_FILE_FIELD PT_DEF_TABU8[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"value",			FTYPVAL_U8SOD,	NULL, 0,	0,	0},
	{	NULL,	0,	NULL,	0,	0,	0}
};
#else
extern T_STRUCT_FILE_FIELD PT_DEF_TABU8[];
#endif

