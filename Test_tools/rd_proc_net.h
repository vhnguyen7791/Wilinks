/*========================================================================*/
/* NOM DU FICHIER  : rd_proc_net.h				                          */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Test lecture /proc/net/...							  */
/* Projet          : WRM100		                                          */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _RD_PROC_NET
#define _RD_PROC_NET_EXT
#else
#define _RD_PROC_NET_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: TestLecture_ProcNetRoute
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste de lecture de /proc/net/route
//=====================================================================================
void TestLecture_ProcNetRoute(void);

//=====================================================================================
// Fonction		: TestLecture_ProcNetAssociatedSta
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste de lecture de /proc/net/madwifi/wifi0/associated_sta
//=====================================================================================
void TestLecture_ProcNetAssociatedSta(void);

//=====================================================================================
// Fonction		: InitModule_RdProcNet
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de rd_proc_net
//=====================================================================================
void InitModule_RdProcNet(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

