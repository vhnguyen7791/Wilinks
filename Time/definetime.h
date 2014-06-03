/*========================================================================*/
/* NOM DU FICHIER  : definetime.h                                         */
/*========================================================================*/
/* Auteur		   : CM                                                   */
/* Date			   : 01/07/2010                                           */
/* Libelle  	   : DEFINE												  */
/* Projet          : WRM100                                               */
/* Indice          : BE036												  */
/*========================================================================*/
/*  Historique		:                                                     */
//BE035 01/07/2010 CM
// - CREATION
//BE036 02/07/2010 CM
// - Modification des chemins de fichiers qui se trouvent dans /var => /tmp
/*========================================================================*/

/*______I - COMMENTAIRES - DEFINITIONS - REMARQUES________________________*/

/*______II - DEFINE - SBIT________________________________________________*/

//Offset estimé suite à A/M de l'équipement
#define OFFSET_RESTORETIME		50	//secondes

//Taille d'une partition
#define TAILLE_MAX_PARTITION_TIME_SAVE	(128*1024) //128ko

#define NB_MAX_DATA_TIME	8	//4+4: nombre d'octets sauvés à chaque fois

#define VALEUR_TIME_VIERGE	0xFFFFFFFF

//Taille des informations echangées par le processus restoretime vers savetime
// - numero partition 
// - index position dans cette partition
#define TAILLE_MAX_MSG_INFO_TIME	50

//Fichiers temporaires
#define FILE_TIME_INFO_DLG PATH_DIR__BDD_TIME		"timeinfo.dlg"
#define FILE_TIME_INFO_STA PATH_DIR__BDD_TIME		"timeinfo.sta"
#define FILE_MINITIME_BINARY PATH_DIR__BDD_TIME		"minitime.bin"
#define FILE_TIMESAVE1_BINARY PATH_DIR__BDD_TIME	"timesave1.bin"
#define FILE_TIMESAVE2_BINARY PATH_DIR__BDD_TIME	"timesave2.bin"

/*______III - INCLUDES - DIRECTIVES_______________________________________*/

/*______IV - PROTOTYPES DEFINIS___________________________________________*/

/*______V - DEFINITION DE TYPES___________________________________________*/


/*______VI - CONSTANTES ET VARIABLES______________________________________*/

/*________VII - PROCEDURES D'INITIALISATION ______________________________*/
