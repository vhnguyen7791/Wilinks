/*========================================================================*/
/* NOM DU FICHIER  : fctu8bit.c											  */
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

#define _FCTU8BIT


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8GetU8EtatBit
// Entrees		: <loc_u8_valeur_etat>
//				  <loc_u8_index_bit>
// Sortie		: <loc_i_resultat> : TRUE valide / FALSE non valide
// Auteur		: CM - 29/08/2007 -
// Description	: retourne si bit valide ou non
//=====================================================================================
u8sod u8GetU8EtatBit(u8sod loc_u8_valeur_etat, u8sod loc_u8_index_bit)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(0 != (loc_u8_valeur_etat & (0x01 << loc_u8_index_bit)))//CONDITION:action valide	
	{
		loc_u8_resultat = TRUE;
	}	

	return(loc_u8_resultat);		
}/*u8GetU8EtatBit*/

//=====================================================================================
// Fonction		: SetU8EtatBit
// Entrees		: <loc_pu8_valeur_etat< : valeur etat à modifier
//				  <loc_u8_index_bit>
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Force bit à 1
//=====================================================================================
void SetU8EtatBit(u8sod *loc_pu8_valeur_etat, u8sod	loc_u8_index_bit)
{

	*loc_pu8_valeur_etat |= (0x01 << loc_u8_index_bit);

}/*SetU8EtatBit*/

//=====================================================================================
// Fonction		: ResetU8EtatBit
// Entrees		: <loc_pu8_valeur_etat< : valeur etat à modifier
//				  <loc_u8_index_bit>
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Reset bit 
//=====================================================================================
void ResetU8EtatBit(u8sod *loc_pu8_valeur_etat, u8sod	loc_u8_index_bit)
{

	(*loc_pu8_valeur_etat) &= (u8sod)(~(0x01 << loc_u8_index_bit));

}/*ResetU8EtatBit*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_FctU8Bit
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du module de fctu8bit
//=====================================================================================
void InitModule_FctU8Bit(void)
{
}/*InitModule_FctU8Bit*/

