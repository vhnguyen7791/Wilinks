/*========================================================================*/
/* NOM DU FICHIER  : cfg_monitor.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/03/2010                                           */
/* Libelle         : Principal: Configuration du processus monitor		  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 02/03/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_MONITOR

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Monitor
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Installe monitor
//=====================================================================================
void Install_Monitor(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Monitor\n");

	CmdSystem_Generique("monitor &");

}/*Install_Monitor*/

//=====================================================================================
// Fonction		: Uninstall_Monitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Désinstalle du processus monitor
//=====================================================================================
void Uninstall_Monitor(void)
{
	printf("Uninstall_Monitor\n");
	
	CmdSystem_Generique("killall monitor");

}/*Uninstall_Monitor*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Monitor
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation du module de cfg_monitor
//=====================================================================================
void InitModule_Cfg_Monitor(void)
{
	Uninstall_Monitor(); //INIT
	
}/*InitModule_Cfg_Monitor*/

