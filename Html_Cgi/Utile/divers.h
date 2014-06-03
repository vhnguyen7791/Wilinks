/*========================================================================*/
/* NOM DU FICHIER  : divers.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: divers									  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _DIVERS
#define _DIVERS_EXTERN
#else
#define _DIVERS_EXTERN extern
#endif


//macro utilise pour le decodage de form html
#ifndef offsetof
#define offsetof(type,fld) ((u32sod)&((type *)0)->fld)
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef struct
{
	char *namep;		/* Pointer to field name */
	char *formatp;		/* Pointer to scanf format string */
	int moffset;		/* Offset to structure member */
} FIELD_LIST;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: ps8EncadreText
// Entrees		: <loc_ps8_balise_debut< : balise HTML début
//				: <loc_ps8_name_html< : texte à cadrer par les balises HTML
//				: <loc_ps8_balise_fin< : balise HTML fin
// Sortie		: rien
// Auteur		: CM - 25/07/2007 -
// Description	: Encadre le texte des balises
//=====================================================================================
s8sod* ps8EncadreText(s8sod *loc_ps8_balise_debut, s8sod *loc_ps8_text, s8sod *loc_ps8_balise_fin);

//=====================================================================================
// Fonction		: Html_GotoPage
// Entrees		: <loc_ps8_name_html< : Nom de la page HTML à charger
// Sortie		: rien
// Auteur		: CM - 31/08/2006 -
// Description	: Gère retours à une page HTML (suite validation)
//=====================================================================================
void Html_GotoPage(s8sod *loc_ps8_name_html);

//============================================================================
// Fonction		: form_hidden
// Entrees		: <loc_ps8_namep< : nom de la variable cree
// Entrees		: <loc_ps8_valuep< : valeur init
// Sortie		: rien
// Description	: declare une variable cachee dans un form
//============================================================================
void form_hidden(s8sod *loc_ps8_namep, s8sod *loc_ps8_valuep);

//============================================================================
// Fonction	: form_decode 
// Entrees	: <loc_t_ftp< : pointeur sur la structure type de la form
//            <loc_t_structp< : pointeur sur la structure de sortie (la ou va etre mis la recuperation)
//            <loc_p_varlist< : la liste des parametres d'entree de la form
//            <loc_ps8_emsgp< : pointeur sur une chaine de caractere : si erreur lors de la recup, contient la cause de l'erreur
// Sortie	: 1 ou 0 suivant le succes ou non de la recuperation
// Description	: recupere les parametres d'un form dans la structure 
//                passee en parametre
//============================================================================
s32sod form_decode (FIELD_LIST *loc_t_ftp, 
					void	*loc_t_structp, 
					s8sod	**loc_p_varlist, 
					s8sod	*loc_ps8_emsgp);

//============================================================================
// Fonction	: PagePbdebug 
// Entrees	: tableau de pointeur sur les parametres de la page
//            <loc_ps8_emsgp< : pointeur sur une chaine de caractere : si erreur lors de la recup, contient la cause de l'erreur
// Sortie	: Rien
// Description	: recupere les parametres d'un form dans la structure 
//                passee en parametre
//============================================================================
void PagePbdebug (s8sod **loc_p_varlist, s8sod *loc_ps8_emsgp);

//============================================================================
// Fonction		: PreparePagePswd
// Entrees		: une chaine de cractere contenant l'adresse de la page demandee
// Sortie		: Rien
// Auteur		: 
// Description	: on sauve  la page à accéder et on charge la page HTML enter_pwd
//============================================================================
void PreparePagePswd (const s8sod *loc_ps8_adresse);

//============================================================================
// Fonction		: AfficheDansToutesLesPages
// Entrees		: Rien
// Sortie		: Rien
// Auteur		: MS
// Description	: permet d'afficher un message commun à toutes les pages
//				  attention : à chaque création de pages HTML, il faut appeler cette
//				  fonction
//============================================================================
void AfficheDansToutesLesPages ();

//=====================================================================================
// Fonction		: InitModule_Divers
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de divers
//=====================================================================================
void InitModule_Divers(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

