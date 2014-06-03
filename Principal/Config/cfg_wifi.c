/*========================================================================*/
/* NOM DU FICHIER  : cfg_wifi.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/11/2009                                           */
/* Libelle         : Principal: Configuration du Wifi					  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 12/11/2009 CM
// - CREATION
//BE021 24/03/2010 CM
// - Correction BUG liaison bridge-bridge
//BE032 16/06/2010 CM
// - Correction commande iwconfig 'txpower' (Wifi) repasse au maximum sur A/M ou sur down/up interface Wifi
// - Correction BUG SSID avec des espaces
//	=> iwconfig ath0 essid <chaine avec espace> => KO
//BE039 26/08/2010 CM
// - Intégration des modifications release_v2
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE042 07/10/2010 CM
// - Integration des paramètres handoff
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
//BE060 16/03/2011
// - Ajout fonction qui liste les fichiers dans répertoire
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_WIFI

//Pour forcer la puissance d'émission, il faut soustraire la valeur désirée de l'offset
#define OFFSET_TXPOWER_DRIVER_ATHEROS	0

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_SecuriteWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration de la sécurité wifi
//=====================================================================================
void Install_SecuriteWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_SecuriteWifi\n");

	//On le fait tout le temps (car si l'utilsateur souhaite appliquée la config EAP-TLS il aura les certificats
	CopyCertificats_FlashToEtc();
	
	//Il faut installer la sécurité après la configuration du bridge
	switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_AUCUN:
			//Add by VuHai
			if(MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				Install_Hostapd(loc_ps_config);
			}
			if(MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				Install_WpaSupplicant(loc_ps_config);
			}
			//Fin Add by VuHai
			break;
		case MODE_SECURITE_WIFI_WEP:
			//Add by VuHai
			if(MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				Install_Hostapd(loc_ps_config);
			}
			if(MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				Install_WpaSupplicant(loc_ps_config);
			}
			//Fin Add by VuHai
			break;
		default: //WPA
			switch(loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				case MODE_RADIO_MODEM_ACCESS_POINT:
					Install_Hostapd(loc_ps_config);
					break;
				case MODE_RADIO_MODEM_STATION:
					Install_WpaSupplicant(loc_ps_config);
					break;
				case MODE_RADIO_MODEM_MONITOR:
				default:
					break;
			}
			break;
	}
	
}/*Install_SecuriteWifi*/

//=====================================================================================
// Fonction		: Uninstall_SecuriteWifi
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration de la sécurité wifi
//=====================================================================================
void Uninstall_SecuriteWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_SecuriteWifi\n");

	//Modif by VuHai
	/*switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_AUCUN:
			break;
		case MODE_SECURITE_WIFI_WEP:
			break;
		default: //WPA
			*/switch(loc_ps_config->s_gene.u8_mode_radio_modem)
			{
				case MODE_RADIO_MODEM_ACCESS_POINT:
					Uninstall_Hostapd(loc_ps_config);
					break;
				case MODE_RADIO_MODEM_STATION:
					Uninstall_WpaSupplicant(loc_ps_config);
					break;
				case MODE_RADIO_MODEM_MONITOR:
				default:
					break;
			}
			/*break;
	}*/

}/*Uninstall_SecuriteWifi*/

//=====================================================================================
// Fonction		: Install_WdsWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/03/2010 -
// Description	: Installe la configuration du wifi (wds) 
//=====================================================================================
void Install_WdsWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_WdsWifi\n");
	//if (MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem){
	if(MODE_NETWORK_BRIDGE == loc_ps_config->s_gene.u8_mode_network)
	{
		//pour station et access point bridge, on active pour que la liaison bridge-bridge fonctionne
		//CmdSystem_Generique("iwpriv %s wds 1",
			//				NOM_INTERFACE_WIFI);
		CmdSystem_Generique("iw dev %s set 4addr on", NOM_INTERFACE_WIFI);//Modif by VuHai
	}
	else
	{
		//CmdSystem_Generique("iwpriv %s wds 0",
			//				NOM_INTERFACE_WIFI);
		CmdSystem_Generique("iw dev %s set 4addr off", NOM_INTERFACE_WIFI);//Modif by VuHai
	}//}
	
}/*Install_WdsWifi*/

//=====================================================================================
// Fonction		: Install_FrequenceWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (fréquence)
//=====================================================================================
void Install_FrequenceWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_FrequenceWifi\n");

#ifdef _WRM100_ABG_SELECT
	WlanABG_Install_FrequenceWifi(loc_ps_config);
#endif

#ifdef _WRM100_N_SELECT
	WlanN_Install_FrequenceWifi(loc_ps_config);
#endif

}/*Install_FrequenceWifi*/

//=====================================================================================
// Fonction		: Install_TxPowerWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 16/06/2010 -
// Description	: Installe la configuration du wifi (puissance)
//=====================================================================================
void Install_TxPowerWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_TxPowerWifi\n");

	/*CmdSystem_Generique("iwconfig %s txpower %d",
						NOM_INTERFACE_WIFI,
						((s8sod)loc_ps_config->s_wifi.u8_power_tx-OFFSET_TXPOWER_DRIVER_ATHEROS));*/
	//printf("**********Txpower will be set is:%d\n", 100*((s8sod)loc_ps_config->s_wifi.u8_power_tx-OFFSET_TXPOWER_DRIVER_ATHEROS));
	CmdSystem_Generique("iw dev  %s set txpower fixed %d",
			    NOM_INTERFACE_WIFI,
			    100*((s8sod)loc_ps_config->s_wifi.u8_power_tx-OFFSET_TXPOWER_DRIVER_ATHEROS));//Modif by VuHai, replace iwconfig by iw
	
}/*Install_TxPowerWifi*/

//=====================================================================================
// Fonction		: Install_Wifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du wifi (basic)
//=====================================================================================
void Install_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Wifi\n");
	
	//Shut down Interface Wifi
	CmdIfconfig_Down(NOM_INTERFACE_WIFI);

	/*u16sod  u16_ieee;
	u16sod  loc_u16_index;
	printf("************ Channel 1 ************\n");
	loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
	u16_ieee = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_ieee;
	CmdSystem_Generique("iw %s set channel %d HT20",
			    NOM_INTERFACE_WIFI,
			    u16_ieee);
	printf("************ Channel 1 ************\n");*/
	
#ifdef _WRM100_ABG_SELECT
	WlanABG_Install_Wifi(loc_ps_config);
#endif
	
#ifdef _WRM100_N_SELECT
	WlanN_Install_Wifi(loc_ps_config);
	//WlanN_Install_Handoff(loc_ps_config);
	//WlanN_Install_ModeRSSI(loc_ps_config);
#endif

	
	//Power on Interface Wifi
	CmdIfconfig_Up(NOM_INTERFACE_WIFI, loc_ps_config);

	printf("***** Install_WdsWifi in Install_Wifi *********\n");
	//Wds
	Install_WdsWifi(loc_ps_config);

}/*Install_Wifi*/


//=====================================================================================
// Fonction		: Uninstall_Wifi
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du wifi
//=====================================================================================
void Uninstall_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_Wifi\n");


}/*Uninstall_Wifi*/

//=====================================================================================
// Fonction		: Install_AdvWifi
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du advwifi (avancé et antennes)
//=====================================================================================
void Install_AdvWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_valeur; 

	loc_u8_valeur = 0; //INIT

	printf("Install_AdvWifi\n");

	//Shut down Interface Wifi
	CmdIfconfig_Down(NOM_INTERFACE_WIFI);

#ifdef _WRM100_ABG_SELECT
	WlanABG_Install_AdvWifi(loc_ps_config);
#endif

#ifdef _WRM100_N_SELECT
	WlanN_Install_AdvWifi(loc_ps_config);
#endif

	//Power on Interface Wifi
	CmdIfconfig_Up(NOM_INTERFACE_WIFI, loc_ps_config);

}/*Install_AdvWifi*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Wifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Initialisation du module de cfg_wifi
//=====================================================================================
void InitModule_Cfg_Wifi(void)
{
	
}/*InitModule_Cfg_Wifi*/

