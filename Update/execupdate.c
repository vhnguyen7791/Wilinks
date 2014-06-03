/*========================================================================*/
/* NOM DU FICHIER  : execupdate.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 18/12/2009                                           */
/* Libelle         : UPDATE: Processus de mise à jour logicielle		  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 18/12/2009 CM
// - CREATION
//BE010 03/02/2010 CM
// - Modification processus update (independance avec principal)
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECUPDATE


/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0);

//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0)
{
	printf("Usage: %s [modeboot]\n"
		   "	modeboot: programme en cours d'exécution 0:aucun, 1:app1, 2:app2 \n"
		   ,loc_ps8_argv0);
}/*proc_Usage*/

//=====================================================================================
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Auteur		: CM - 18/12/2009 -
// Description	: PROCESSUS UPDATE
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	printf("Debut processus update... \n");

	InitModule_ExecUpdate();

	//Test des arguments passés
	if(loc_s32_argc >= 2)//CONDITION: nombre d'argument insufisant
	{
		
		if (0 == strcmp(loc_pps8_argv[1],"0"))
		{
			e_modeboot_encours = E_MODE_BOOT_AUCUN;
		}
		else
		{
			if (0 == strcmp(loc_pps8_argv[1],"1"))
			{
				e_modeboot_encours = E_MODE_BOOT_APP1;
			}
			else
			{
				if (0 == strcmp(loc_pps8_argv[1],"2"))
				{
					e_modeboot_encours = E_MODE_BOOT_APP2;
				}
				else
				{
					proc_Usage(loc_pps8_argv[0]);
					exit(1);
				}
			}
		}
	}

	//Initialisation des modules de la librairie system
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(printf);
	
	
	//Initialisation des modules associés à ce processus
	InitModule_GestUpdate_App();


	do{
		
		sleep(1);

		ExecuteGestionUpdateApp();


		
	}while(1);
	
	
	return 0;
}/*main*/


/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecUpdate
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/12/2009 -
// Description	: Initialisation du module de ExecUpdate
//=====================================================================================
void InitModule_ExecUpdate(void)
{
//	FILE	*loc_p_handle;
//	s8sod	*loc_ps8_result_fgets;
//	s8sod	loc_ps8_ligne[TAILLE_MAX_MSG_VERSION_UBOOT+1];

//	loc_p_handle = NULL; //INIT
//	loc_ps8_result_fgets = NULL; //INIT
	
	e_modeboot_encours = E_MODE_BOOT_AUCUN; //INIT

	//Lecture de la version BOOT
	/* MEC - - WILINK retour version boot pas utile */
//	strcpy(ps8_update__version_be_uboot,""); //INIT
//	if(NULL != (loc_p_handle = fopen( FILE_UBOOT_INIT, "rt" ))) //CONDITION: fichier présent
//	{
//		loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_MSG_VERSION_UBOOT,loc_p_handle);
//		if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue
//		{
//			strcpy(ps8_update__version_be_uboot, loc_ps8_ligne);
//		}
//		fclose (loc_p_handle);
//	}
	
}/*InitModule_ExecUpdate*/

