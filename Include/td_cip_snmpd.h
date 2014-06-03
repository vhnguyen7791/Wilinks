/*========================================================================*/
/* NOM DU FICHIER  : td_cip_snmpd.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010											  */
/* Libelle         : Base de données: Communication Inter Process (snmpd) */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//définition des informations à échanger avec le processus snmpd
typedef struct 
{
	u8sod	u8_replay_trap;			//Ordre de rejouer les traps (SNMPv1)
	u8sod	pu8_flag_newcfg[NB_MAX_IDXCONFIG];		//Signale une susceptible évolution de la configuration pour le fichier défini par son index
	u8sod	u8_acquit_all_traps;	//Ordre Acquittement de tous les traps (SNMPv1)
}S_STRUCT_CIP_SNMPD;



/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




