/*========================================================================*/
/* NOM DU FICHIER  : execconf_sftp.c 	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : JP                                                   */
/* Date			   : 25/10/2011                                           */
/* Libelle         : conf_sftp: processus de gestion config par sFTP	  */
/* Projet          : WRM100                                               */
/* Indice          : BE063                                                */
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECCONF_SFTP


/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Description	: PROCESSUS gestin de la config par sFTP
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	printf("Debut processus gestconf_sftp... \n");

	//Initialisation des modules de la librairie bdd
	InitModule_LibraryBdd();
	
	//Initialisation des modules de la librairie system
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(printf);

	//init du module
	InitModule_GestConfsFTP();

	do{

		sleep(1);

		u8GestionConfSFTP();

	}while(1);

	return 0;
}/*main*/

	
