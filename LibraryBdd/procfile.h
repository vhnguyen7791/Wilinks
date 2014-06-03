/*========================================================================*/
/* NOM DU FICHIER  : procfile.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/04/2009                                           */
/* Libelle         : Base de données: gestion des fichiers sous /proc	  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _PROCFILE
#define _PROCFILE_EXT
#else
#define _PROCFILE_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: u8ProcNetRoute_DecodeLine
// Entrees		: <loc_ps8_ligne_code<	: ligne du fichier
//				  <loc_pt_route<: pointeur sur route
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Decode ligne du fichier /proc/net/route (liste des routes actives)
//=====================================================================================
u8sod u8ProcNetRoute_DecodeLine(s8sod *loc_ps8_ligne_code, S_STRUCT_IP_ROUTE_STATIC *loc_pt_route);

//=====================================================================================
// Fonction		: InitModule_ProcFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de procFile
//=====================================================================================
void InitModule_ProcFile(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

