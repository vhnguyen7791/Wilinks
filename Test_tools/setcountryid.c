/*========================================================================*/
/* NOM DU FICHIER  : setcountryid.c	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010                                           */
/* Libelle         : Test: set country ID								  */
/* Projet          : WRM100		                                          */
/* Indice          : BE042                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 11/10/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _SETCOUNTRYID

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

#include "../LibraryWifi/wifi_tools.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: SaveCountryID
// Entrees		: <loc_ps8_new_countryid< : chaine de caractères du country ID
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Sauvegarde du countryID
//=====================================================================================
void SaveCountryID(s8sod *loc_ps8_new_countryid)
{
	s32sod	loc_s32_sem;
	u16sod loc_u16_countryID;
	u8sod	loc_pu8_add_mac_ethernet[ETHER_ADDR_LEN]; //Adresse MAC de l'interface ethernet
	u16sod loc_u16_mac;
	S_STRUCT_ENVIRONNEMENT loc_s_environnement;

	loc_u16_mac = 0;	//INIT
	memset(loc_pu8_add_mac_ethernet, 0, ETHER_ADDR_LEN); //INIT
	memset(&loc_s_environnement,'\0',sizeof(S_STRUCT_ENVIRONNEMENT));
	
	if(FALSE == u8GetMacAddress(NOM_INTERFACE_ETHERNET,loc_pu8_add_mac_ethernet))
	{
		printf("SaveCountryID: Error 1\n");
	}
	else
	{
		s32Lock_Get(SEMAPHORE_BDD_ENVIRONMT, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillEnvFile(&loc_s_environnement))
		{
			loc_u16_mac = (u16sod)loc_pu8_add_mac_ethernet[4] | ((u16sod)loc_pu8_add_mac_ethernet[5] << 8);
			loc_u16_countryID = (u16sod)atoi(loc_ps8_new_countryid);
			loc_s_environnement.u16_countryID = (loc_u16_mac ^ loc_u16_countryID);
			if(TRUE == u8TestEnvFile(&loc_s_environnement))
			{
				if(TRUE == u8EditEnvFile(&loc_s_environnement))
				{
					//on copie ini => sav
					u8CmdSystem_CopyFile(T_DEF_FILE_ENV_INI.ps8_path_file,
										 T_DEF_FILE_ENV_SAV.ps8_path_file);
					SignalNewCountryID();
					printf("SaveCountryID: OK\n");
				}
				else
				{
					printf("SaveCountryID: Error 3\n");
				}
			}
		}
		else
		{
			printf("SaveCountryID: Error 2\n");
		}
		s32Lock_Release(SEMAPHORE_BDD_ENVIRONMT, &loc_s32_sem);	//on relache le sem
	}
	
}/*SaveCountryID*/

//=====================================================================================
// Fonction		: SignalNewCountryID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: signal nouveau countryID
//=====================================================================================
void SignalNewCountryID(void)
{
	FILE	*loc_p_handle;

	loc_p_handle = NULL; //INIT

	if(NULL != (loc_p_handle = fopen( FICHIER_NEW_COUNTRYID_ORDER, "w" ))) //CONDITION: edition fichier
	{
		//fermeture du fichier
		fclose (loc_p_handle);
	}

}/*SignalNewCountryID*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SetCountryID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation du module de setcountryid
//=====================================================================================
void InitModule_SetCountryID(void)
{
}/*InitModule_SetCountryID*/

