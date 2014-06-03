/*========================================================================*/
/* NOM DU FICHIER  : libraryBdd.c		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: initialisation de la librarie bdd	  */
/* Projet          : WRM100                                               */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE037 06/07/2010 CM
// - Ajout exploitation temperature 
// - Ajout récupération statut ethernet des 2 ports ethernet
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _LIBRARYBDD

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_LibraryBdd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de libraryBdd
//=====================================================================================
void InitModule_LibraryBdd(void)
{
	InitModule_Debug();
	InitModule_Timeout();
	InitModule_Locksem();
	InitModule_BddFile();
	InitModule_BddSystemFile();
	InitModule_Def_ConfigFiles();
	InitModule_Def_ExploitFiles();
	InitModule_Config();
	InitModule_Exploit();
	InitModule_Langue();
	InitModule_Client();
	InitModule_Http();
	InitModule_FctU8Bit();
	InitModule_Valeurs();
	InitModule_Custom_Langue();
	InitModule_ProcFile();
	InitModule_Event();
	InitModule_Cip_Monitor();
	InitModule_Cip_Snmpd();
	InitModule_Cip_Trap();
	InitModule_BddJdb();
	InitModule_Cip_Jdb();
	InitModule_Exp_Event();
	InitModule_Ad7814();
	InitModule_Ksz8893();
	InitModule_Environmt();
	InitModule_ListFreq();
	
}/*InitModule_LibraryBdd*/

