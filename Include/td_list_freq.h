/*========================================================================*/
/* NOM DU FICHIER  : td_list_freq.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/10/2010                                           */
/* Libelle         : Base de données: type def liste des frequences regl. */
/* Projet          : WRM100                                               */
/* Indice	       : BE042												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 12/10/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

//Variable : S_STRUCT_LIST_FREQ
//Champs : s_channel[]
#define NB_MAX_CHANNEL	300 //estimation, comprend les canaux de 2 GHz et de 5GHz

//Variable : S_STRUCT_CHANNEL
//Champs : s_channel[].u16_ieee
#define IEEE_CHANNEL_NO_VALID  0xFFFF

//Variable : S_STRUCT_CHANNEL
//Champs : s_channel[].u16_flags
enum LISTE_DES_FLAGS_CHANNEL
{
	BIT0_FLAG_CHANNEL_2GHZ,
	BIT1_FLAG_CHANNEL_5GHZ,
	BIT2_FLAG_CHANNEL_HT20,
	BIT3_FLAG_CHANNEL_HT40PLUS,
	BIT4_FLAG_CHANNEL_HT40MINUS,
};


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

// Caractéristiques d'un canal
typedef struct
{
	u16sod	u16_ieee;		//Numero de canal
	u16sod	u16_freq_MHz;	//Valeur en MHz
	u16sod	u16_flags;		//Flags

}S_STRUCT_CHANNEL;

//*****************************************
/* structure Liste des frequences		  */
//*****************************************
typedef struct 
{
	S_STRUCT_CHANNEL s_channel[NB_MAX_CHANNEL];
	
}S_STRUCT_LIST_FREQ;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


