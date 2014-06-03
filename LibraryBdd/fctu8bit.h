/*========================================================================*/
/* NOM DU FICHIER  : fctu8bit.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 29/08/2007                                           */
/* Libelle         : Base de données: gestion binaire mot de 8bit		  */
/* Projet          : WRM100                                               */
/* Indice	       : BE000												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _FCTU8BIT
#define _FCTU8BIT_EXT
#else
#define _FCTU8BIT_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8GetU8EtatBit
// Entrees		: <loc_u8_valeur_etat>
//				  <loc_u8_index_bit>
// Sortie		: <loc_i_resultat> : TRUE valide / FALSE non valide
// Auteur		: CM - 29/08/2007 -
// Description	: retourne si bit valide ou non
//=====================================================================================
u8sod u8GetU8EtatBit(u8sod loc_u8_valeur_etat, u8sod loc_u8_index_bit);

//=====================================================================================
// Fonction		: SetU8EtatBit
// Entrees		: <loc_pu8_valeur_etat< : valeur etat à modifier
//				  <loc_u8_index_bit>
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Force bit à 1
//=====================================================================================
void SetU8EtatBit(u8sod *loc_pu8_valeur_etat, u8sod	loc_u8_index_bit);

//=====================================================================================
// Fonction		: ResetU8EtatBit
// Entrees		: <loc_pu8_valeur_etat< : valeur etat à modifier
//				  <loc_u8_index_bit>
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Reset bit 
//=====================================================================================
void ResetU8EtatBit(u8sod *loc_pu8_valeur_etat, u8sod	loc_u8_index_bit);

//=====================================================================================
// Fonction		: InitModule_FctU8Bit
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du module de fctu8bit
//=====================================================================================
void InitModule_FctU8Bit(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

