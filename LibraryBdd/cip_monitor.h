/*========================================================================*/
/* NOM DU FICHIER  : cip_monitor.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 03/03/2010                                           */
/* Libelle         : Base de données: CIP pour processus monitor		  */
/* Projet          : WRM100                                               */
/* Indice	       : BE013												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 03/03/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CIP_MONITOR
#define _CIP_MONITOR_EXT
#else
#define _CIP_MONITOR_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillCipMonitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 03/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillCipMonitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor);

//=====================================================================================
// Fonction		: u8EditCipMonitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 03/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditCipMonitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor);

//=====================================================================================
// Fonction		: Raz_Cip_Monitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: RAZ des ordres de la base de données de cip_monitor
//=====================================================================================
void Raz_Cip_Monitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor);

//=====================================================================================
// Fonction		: InitBDD_Cip_Monitor
// Entrees		: <loc_ps_cip_monitor< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Initialisation de la base de données de cip_monitor
//=====================================================================================
void InitBDD_Cip_Monitor(S_STRUCT_CIP_MONITOR *loc_ps_cip_monitor);

//=====================================================================================
// Fonction		: InitModule_Cip_Monitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Initialisation du module de cip_monitor
//=====================================================================================
void InitModule_Cip_Monitor(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
