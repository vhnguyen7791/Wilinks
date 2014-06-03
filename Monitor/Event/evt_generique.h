/*========================================================================*/
/* NOM DU FICHIER  : evt_generique.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: Calcul des évènements génériques			  */
/* Projet          : WRM100                                               */
/* Indice          : BE016                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE016 11/03/2010 CM
// - Ajout calcul evt EquipmentOn
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EVT_GENERIQUE
#define _EVT_GENERIQUE_EXT
#else
#define _EVT_GENERIQUE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: Calcul_Evt_EquipmentOn
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: Gestion de l'evènement de EquipementOn
//=====================================================================================
void Calcul_Evt_EquipmentOn(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Calcul_Evt_SigneVie
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 01/03/2010 -
// Description	: Gestion de l'evènement de signe de vie
//=====================================================================================
void Calcul_Evt_SigneVie(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Evt_Generique
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/03/2010 -
// Description	: Initialisation du module evt_generique
//=====================================================================================
void InitModule_Evt_Generique(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

