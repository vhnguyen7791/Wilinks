/*========================================================================*/
/* NOM DU FICHIER  : exectest.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : TEST: Processus de test (wifi, ...)			      */
/* Projet          : WRM100	                                              */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE040 13/09/2010 CM
// - Suppresion code inutile
// - Nouveaux projets WRM100
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE058 21/01/2011 CM
// - Modification gestion exploitation wifi
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECTEST		1

//Liste des tests
enum LISTE_DES_TESTS
{
	MODE_TEST_TOOL_AUCUN =0	,
	MODE_TEST_TOOL_WIFI		,
	MODE_TEST_TOOL_MAC		,
	MODE_TEST_TOOL_READ_PROC_NET_ROUTE	,
	MODE_TEST_TOOL_SWAP_APP1,
	MODE_TEST_TOOL_SWAP_APP2,
	MODE_TEST_TOOL_FILE,
	MODE_TEST_TOOL_PERSO,
	MODE_TEST_TOOL_SETCOUNTRYID,
	NB_MAX_TESTS_TOOLS
};

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

u8sod u8_mode_test;

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
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: PROCESSUS TEST
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	printf("Debut processus Test... \n");

	//-----------------------------------------------
	//Initialisation propres à ce processus
	//-----------------------------------------------
	InitModule_ExecTest();
	InitModule_TestWifi();
	InitModule_RdProcNet();
	InitModule_TestMac();
	InitModule_TestSwap_App();
	InitModule_TestFile();
	InitModule_SetCountryID();

	//-----------------------------------------------
	//Test des arguments passés
	//-----------------------------------------------
	if(loc_s32_argc < 2)//CONDITION: nombre d'argument insufisant
	{
		; //pas assez d'arguments
	}
	else
	{
		if (0 == strcmp(loc_pps8_argv[1],"-w"))
		{
			u8_mode_test = MODE_TEST_TOOL_WIFI;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-mac"))
		{
			u8_mode_test = MODE_TEST_TOOL_MAC;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-route"))
		{
			u8_mode_test = MODE_TEST_TOOL_READ_PROC_NET_ROUTE;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-swap_app1"))
		{
			u8_mode_test = MODE_TEST_TOOL_SWAP_APP1;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-swap_app2"))
		{
			u8_mode_test = MODE_TEST_TOOL_SWAP_APP2;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-file"))
		{
			u8_mode_test = MODE_TEST_TOOL_FILE;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-perso"))
		{
			u8_mode_test = MODE_TEST_TOOL_PERSO;
		}
		if (0 == strcmp(loc_pps8_argv[1],"-setcountryid"))
		{
			if(loc_s32_argc < 3)//CONDITION: nombre d'argument insufisant
			{
				; //pas assez d'arguments
			}
			else
			{
				u8_mode_test = MODE_TEST_TOOL_SETCOUNTRYID;
			}
		}
	}

	if(MODE_TEST_TOOL_AUCUN == u8_mode_test)
	{
		proc_Usage((s8sod *)loc_pps8_argv[0]);
		exit(1);
	}

	//-----------------------------------------------
	//Initialisation des modules de la librairie system
	//-----------------------------------------------
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(AddMsgDbgLog);
	
	//-----------------------------------------------
	//Initialisation des modules de la librairie bdd
	//-----------------------------------------------
	InitModule_LibraryBdd();

	//-----------------------------------------------
	//Initialisation des modules de la librairie Network
	//-----------------------------------------------
	InitModule_LibraryNetwork();

	//-----------------------------------------------
	//Initialisation des modules de la librairie Wifi
	//-----------------------------------------------
	InitModule_LibraryWifi();
	
	switch(u8_mode_test)
	{
		case MODE_TEST_TOOL_WIFI:
			//Extraction info BSSID sur l'accès Wifi
			TestWifi_ExtractBSSID();
			break;
		case MODE_TEST_TOOL_MAC:
			TestMAC_LanInterface();
			TestMAC_WLanInterface();
			break;
		case MODE_TEST_TOOL_READ_PROC_NET_ROUTE:
			TestLecture_ProcNetRoute();
			break;
		case MODE_TEST_TOOL_SWAP_APP1:
			TestSwap_App(MODE_BOOT_APP1);
			break;
		case MODE_TEST_TOOL_SWAP_APP2:
			TestSwap_App(MODE_BOOT_APP2);
			break;
		case MODE_TEST_TOOL_FILE:
			TestFile();
			break;
		case MODE_TEST_TOOL_PERSO:
		{
			S_STRUCT_SYST_FILE loc_ps_tab[NB_MAX_CERTIFICATS];
			u8sod loc_u8_i;
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				RazSystFile(&loc_ps_tab[loc_u8_i]); //INIT
			}
			if(FALSE == u8CmdSystem_ListFileInDirectory(PATH_DIR__ETC_CERTIFICATS,&loc_ps_tab[0],NB_MAX_CERTIFICATS))
			{
				printf("Resultat:KO\n");
			}
			else
			{
				printf("Resultat:\n");
				for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
				{
					if(0 != strcmp(loc_ps_tab[loc_u8_i].ps8_nom, ""))
					{
						printf("%s size=%lu\n",loc_ps_tab[loc_u8_i].ps8_nom,loc_ps_tab[loc_u8_i].u32_sizeoffile);
					}
				}
			}
			break;
		}
		case MODE_TEST_TOOL_SETCOUNTRYID:
			SaveCountryID(loc_pps8_argv[2]);
			break;
		default:
			break;
	}

	
	return 0;
}/*main*/


//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0)
{
	printf("Usage: %s [-OPTION]\n"
		   "	-w: test acces wifi \n"
		   "	-mac: test adresse MAC \n"
		   "	-route: lecture de /proc/net/route \n"
		   "	-swap_app1: pour basculer sur l'application 1 \n"
		   "	-swap_app2: pour basculer sur l'application 2 \n"
		   "	-file: test gestion file (bdd) \n"
		   "	-perso: test perso \n"
//		   "	-setcountryid: NE PAS AFFICHER \n"
		   ,loc_ps8_argv0);
}/*proc_Usage*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecTest
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de ExecTest
//=====================================================================================
void InitModule_ExecTest(void)
{
	u8_mode_test = MODE_TEST_TOOL_AUCUN; //INIT
	
}/*InitModule_ExecTest*/

