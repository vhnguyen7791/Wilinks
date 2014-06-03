/*========================================================================*/
/* NOM DU FICHIER  : ksz8893.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/07/2010                                           */
/* Libelle         : Base de données: controle du switch KSZ8893		  */
/* Projet          : WRM100                                               */
/* Indice          : BE037                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE037 06/07/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _KSZ8893
#define _KSZ8893_EXT
#else
#define _KSZ8893_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//=====================================================================================
// Fonction		: u8GetPortLinkStatus
// Entrees		: <loc_ps8_path_link_status< : chemin vers statut du port
// Sortie		: <loc_u8_resultat>: TRUE si connecté, sinon FALSE
// Auteur		: CM - 06/07/2010 -
// Description	: Test de lecture de /proc/sys/smi/portX_link_status
//=====================================================================================
u8sod u8GetPortLinkStatus(s8sod *loc_ps8_path_link_status);

//=====================================================================================
// Fonction		: u8GetEthernetLinkStatus
// Entrees		: <loc_u8_ixd_port> : PORT_ETHERNET_1 ou PORT_ETHERNET_2
// Sortie		: <loc_u8_resultat>: TRUE si connecté, sinon FALSE
// Auteur		: CM - 06/07/2010 -
// Description	: Test le port ethernet
//=====================================================================================
u8sod u8GetEthernetLinkStatus(u8sod loc_u8_ixd_port);

//=====================================================================================
// Fonction		: InitModule_Ksz8893
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Initialisation du module de ksz8893
//=====================================================================================
void InitModule_Ksz8893(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

