/*========================================================================*/
/* NOM DU FICHIER  : testwifi.c	  	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : Test sur le wifi									  */
/* Projet          : WRM100		                                          */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE040 13/09/2010 CM
// - Suppresion code inutile
//BE047 29/11/2010 CM
// - Gestion mode dégradé - connection à AP impossible en permanence suite à configuration wifi 
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _TESTWIFI

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

#include "../LibraryWifi/wifi_tools.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: TestWifi_ExtractBSSID
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Teste la fonction wifi : extraction info BSSID
//=====================================================================================
void TestWifi_ExtractBSSID(void)
{
	S_STRUCT_EXP_STATION loc_s_exp_station;
	
	memset(&loc_s_exp_station, 0, sizeof(S_STRUCT_EXP_STATION)); //INIT
	if(TRUE == u8GetWifiBSSID_Ioctl(&loc_s_exp_station))
	{
		printf("TestWifi_ExtractBSSID: OK statut=%d bssid=%02X:%02X:%02X:%02X:%02X:%02X\n",
			   loc_s_exp_station.u8_statut_connexion,
			   loc_s_exp_station.pu8_bssid_add_mac[0], loc_s_exp_station.pu8_bssid_add_mac[1],
			   loc_s_exp_station.pu8_bssid_add_mac[2], loc_s_exp_station.pu8_bssid_add_mac[3],
			   loc_s_exp_station.pu8_bssid_add_mac[4], loc_s_exp_station.pu8_bssid_add_mac[5]);
	}
	else
	{
		printf("TestWifi_ExtractBSSID: KO\n");
	}

}/*TestWifi_ExtractBSSID*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_TestWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de testwifi
//=====================================================================================
void InitModule_TestWifi(void)
{
}/*InitModule_TestWifi*/

