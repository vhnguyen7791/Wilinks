/*========================================================================*/
/* NOM DU FICHIER  : td_bddfile.h				                          */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: Type definition fichier			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE006 20/01/2010 CM
// - Modification gestion couche basse base de données de fichiers
//BE013 26/02/2010 CM
// - Ajout type FTYPVAL_DATE dans gestion des fichiers
//BE060 16/03/2011
// - Ajout nouveau type dans gestion bdd/file
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

//macro utilise pour le decodage 
#ifndef MACRO_OFFSETOF
	#define MACRO_OFFSETOF(type,fld) ((u32sod)&((type *)0)->fld)
#endif

//Variable : T_STRUCT_FILE_FIELD
//Champs : ps8_nom
#define CH_BDDFILECHECKSUM	"BddFileChecksum"
//d: Ajout gestion tableau dans fichier
#define CH_TAB_INDEX		"idx"
//f: Ajout gestion tableau dans fichier

//Variable : T_STRUCT_FILE_FIELD
//Champs : u8_type_valeur
enum LISTE_FIELD_TYPE_VALEUR
{
	FTYPVAL_STRING = 0,
	FTYPVAL_U8SOD,
	FTYPVAL_S8SOD,
	FTYPVAL_U16SOD,
	FTYPVAL_S16SOD,
	FTYPVAL_U32SOD,
	FTYPVAL_S32SOD,
	FTYPVAL_ADR_MAC,
	FTYPVAL_DATE,
	FTYPVAL_TABSTRUCT,			//tableau de structure
	FTYPVAL_TABU8_HEXA,			//tableau en hexa
//d: BE063.0 12/10/2011	
	FTYPVAL_ADDIP,				//adresse IP en notation pointee
	FTYPVAL_COMMENT,			//ligne de commentaire
//f: BE063.0 12/10/2011

	NB_MAX_FIELD_TYPES_VALEUR	
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//****************************************
//Définition du contenu d'un fichier
//****************************************
typedef struct 
{
	s8sod	*ps8_nom;			//Nom du champ dans le fichier (taille maximum 100 caractères)
	u8sod	u8_type_valeur;		//Type de l'offset
	struct T_STRUCT_FILE_FIELD *pt_contenu_elt;//Contenu d'un élement du tableau
	u16sod	u16_taille_elt;			//Taille d'un élément de type sizeof() (défini par FTYPVAL_TAB)  ou taille max de la chaine de caractères (défini par FTYPVAL_STRING ou FTYPVAL_TABU8_HEXA)
	u16sod	u16_nb_max_elt;			//Taille maximum du tableau (défini par FTYPVAL_TAB)
	u32sod	u32_moffset;		//Offset dans la structure (RAM) dans la base de données
	
}T_STRUCT_FILE_FIELD;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

