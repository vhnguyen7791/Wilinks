/*========================================================================*/
/* NOM DU FICHIER  : temperature.h				                          */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/07/2010                                           */
/* Libelle         : Base de données: mesure de la temperature			  */
/* Projet          : WRM100                                               */
/* Indice          : BE037                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE037 06/07/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _TEMPERATURE
#define _TEMPERATURE_EXT
#else
#define _TEMPERATURE_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: s32GetTemperature
// Entrees		: rien
// Sortie		: <loc_s32_valeur> : valeur de la température
// Auteur		: CM - 06/07/2010 -
// Description	: Mesure de la temperature
//=====================================================================================
s32sod s32GetTemperature(void);

//=====================================================================================
// Fonction		: InitModule_Ad7814
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Initialisation du module de ad7814
//=====================================================================================
void InitModule_Ad7814(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

