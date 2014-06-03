/*========================================================================*/
/* NOM DU FICHIER  : cfg_jdb.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 10/03/2010                                           */
/* Libelle         : Principal: Configuration du journal de bord		  */
/* Projet          : WRM100                                               */
/* Indice          : BE015                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 10/03/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_JDB

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Jdb
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 10/03/2010 -
// Description	: Installe jdb
//=====================================================================================
void Install_Jdb(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Jdb\n");//Modif by VuHai (from Monitor to Jdb)

	CmdSystem_Generique("jdb &");

}/*Install_Jdb*/

//=====================================================================================
// Fonction		: Uninstall_Jdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/03/2010 -
// Description	: Désinstalle du processus jdb
//=====================================================================================
void Uninstall_Jdb(void)
{
	printf("Uninstall_Jdb\n");
	
	CmdSystem_Generique("killall jdb");

}/*Uninstall_Jdb*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Jdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/03/2010 -
// Description	: Initialisation du module de cfg_jdb
//=====================================================================================
void InitModule_Cfg_Jdb(void)
{
	Uninstall_Jdb(); //INIT
	
}/*InitModule_Cfg_Jdb*/

