/*========================================================================*/
/* NOM DU FICHIER  : td_environmt.h	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010											  */
/* Libelle         : Base de données: Type def environnement			  */
/* Projet          : WRM100                                               */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 11/10/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//******************************************
/* structure environnement de l'équipement */
//******************************************
typedef struct 
{
	//Entete
	u16sod	u16_checksum_file;	//Checksum de la base de données
	u8sod	u8_start;			//debut des données de configuration

	u16sod	u16_countryID;		//CountryID codé avec adresse MAC de l'ethernet
								//permet de connaitre la liste des fréquences réglementaires
								//les valeurs possibles sont définis dans Driver-N/hal/ah_regdomain.h
	
}S_STRUCT_ENVIRONNEMENT;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


