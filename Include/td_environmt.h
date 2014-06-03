/*========================================================================*/
/* NOM DU FICHIER  : td_environmt.h	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010											  */
/* Libelle         : Base de donn�es: Type def environnement			  */
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
/* structure environnement de l'�quipement */
//******************************************
typedef struct 
{
	//Entete
	u16sod	u16_checksum_file;	//Checksum de la base de donn�es
	u8sod	u8_start;			//debut des donn�es de configuration

	u16sod	u16_countryID;		//CountryID cod� avec adresse MAC de l'ethernet
								//permet de connaitre la liste des fr�quences r�glementaires
								//les valeurs possibles sont d�finis dans Driver-N/hal/ah_regdomain.h
	
}S_STRUCT_ENVIRONNEMENT;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


