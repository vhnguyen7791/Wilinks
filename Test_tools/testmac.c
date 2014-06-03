/*========================================================================*/
/* NOM DU FICHIER  : testmac.c	  	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Test sur le MAC									  */
/* Projet          : WRM100		                                          */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _TESTMAC

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: TestMAC_LanInterface
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste la fonction MAC sur l'accès LAN
//=====================================================================================
void TestMAC_LanInterface(void)
{
	u8sod	loc_pu8_add_mac[ETHER_ADDR_LEN];
	if(TRUE == u8GetMacAddress(NOM_INTERFACE_ETHERNET,loc_pu8_add_mac))
	{
		printf("TestMAC_LanInterface: OK valeur=%02X:%02X:%02X:%02X:%02X:%02X \n",
			   loc_pu8_add_mac[0], loc_pu8_add_mac[1],
			   loc_pu8_add_mac[2], loc_pu8_add_mac[3],
			   loc_pu8_add_mac[4], loc_pu8_add_mac[5]);
	}
	else
	{
		printf("TestMAC_LanInterface: KO\n");
	}
	
}/*TestMAC_LanInterface*/

//=====================================================================================
// Fonction		: TestMAC_WLanInterface
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste la fonction MAC sur l'accès WLAN
//=====================================================================================
void TestMAC_WLanInterface(void)
{
	u8sod	loc_pu8_add_mac[ETHER_ADDR_LEN];
	if(TRUE == u8GetMacAddress(NOM_INTERFACE_WIFI,loc_pu8_add_mac))
	{
		printf("TestMAC_WLanInterface: OK valeur=%02X:%02X:%02X:%02X:%02X:%02X \n",
			   loc_pu8_add_mac[0], loc_pu8_add_mac[1],
			   loc_pu8_add_mac[2], loc_pu8_add_mac[3],
			   loc_pu8_add_mac[4], loc_pu8_add_mac[5]);
	}
	else
	{
		printf("TestMAC_WLanInterface: KO\n");
	}

}/*TestMAC_WLanInterface*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_TestMac
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de testmac
//=====================================================================================
void InitModule_TestMac(void)
{
}/*InitModule_TestMac*/

