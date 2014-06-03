/*========================================================================*/
/* NOM DU FICHIER  : watchdogwifi.c		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/12/2010                                           */
/* Libelle         : Principal: gestion de la surveillance wifi			  */
/* Projet          : WRM100                                               */
/* Indice          : BE065                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE047 01/12/2010 CM
// - CREATION
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE065.0 14/03/2012 (CM)
// - Correction bug inactivité Quelque soit le mode de sécurité
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _WATCHDOGWIFI

//Surveillance wifi
#define TIMEOUT_STATION_NOCONNECTED_FOR_SHORT_CHANNELLIST	30	//secondes
#define TIMEOUT_STATION_NOCONNECTED_FOR_LONG_CHANNELLIST	120	//secondes
#define NB_MAX_TENTATIVES_STATION_TO_CONNECTED	5

//d: BE065.0 27/03/2012 (CM) - Correction bug inactivité station
#define TIMEOUT_STATION_ACTIVITEE	30	//secondes
//f: BE065.0 27/03/2012 (CM) - Correction bug inactivité station


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u16sod u16_cpt_tentatives_reconnect;
static u32sod u32_memo_cptsecond_noconnected;
//d: BE065.0 27/03/2012 (CM) - Correction bug inactivité station
static u32sod u32_cptsecond_connected;
static u8sod  pu8_memo_add_mac_AP[ETHER_ADDR_LEN];
//f: BE065.0 27/03/2012 (CM) - Correction bug inactivité station

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Watchdog_Wifi
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 01/12/2010 -
// Description	: Surveillance Wifi
//=====================================================================================
void Watchdog_Wifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_donnees_inaccessible;
	u8sod	loc_u8_ordre_reconfig;
	u32sod	loc_u32_timeout_noconnected;
	u8sod	loc_u8_surveillance_active;
	FILE	*loc_p_handle;

	loc_u8_donnees_inaccessible = FALSE; //INIT
	loc_u8_ordre_reconfig = FALSE;	//INIT
	loc_u32_timeout_noconnected = 0;	//INIT
	loc_u8_surveillance_active = FALSE;	//INIT
	loc_p_handle = NULL; //INIT

	switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_AUCUN:
		case MODE_SECURITE_WIFI_WEP:
			break;
		default: //WPA
			loc_u8_surveillance_active = TRUE; //surveillance autorisée
			break;
	}
	

	if((TRUE == loc_u8_surveillance_active)&&
	   (FALSE == u8TestConfig_InProgress())
	  ) //CONDITION: surveillance activé sans reconfiguration en cours
	{
		switch(loc_ps_config->s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_ACCESS_POINT:
			case MODE_RADIO_MODEM_MONITOR:
				u16_cpt_tentatives_reconnect = 0;	//RAZ
				u32_memo_cptsecond_noconnected = 0;	//RAZ
				break;
			case MODE_RADIO_MODEM_STATION:
				s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
				if(FALSE == u8FillExploitStationFile(&s_exploit_process_prncpl.s_station))
				{
					loc_u8_donnees_inaccessible = TRUE; //défaut accès bdd
				}
				s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

				if(FALSE == loc_u8_donnees_inaccessible) //CONDITION: BDD OK
				{
					if(STATUT_CONNEXION__ASSOCIATED != s_exploit_process_prncpl.s_station.u8_statut_connexion) //CONDITION: station non connectée
					{
//						printf("u32_cptsecond_noconnected=%lu memo=%lu \n",
//							   s_exploit_process_prncpl.s_station.u32_cptsecond_noconnected, u32_memo_cptsecond_noconnected);
						switch(loc_ps_config->s_wifi.u8_type_selection_canal)
						{
							case TYPE_SELECTION_CANAL_ISO:
							case TYPE_SELECTION_CANAL_MULTI:
								loc_u32_timeout_noconnected = TIMEOUT_STATION_NOCONNECTED_FOR_SHORT_CHANNELLIST;
								break;
							case TYPE_SELECTION_CANAL_AUTO:
							default:
								loc_u32_timeout_noconnected = TIMEOUT_STATION_NOCONNECTED_FOR_LONG_CHANNELLIST;
								break;
						}

						if(s_exploit_process_prncpl.s_station.u32_cptsecond_noconnected > loc_u32_timeout_noconnected)//CONDITION: station non connectée depuis un certain temps
						{
							//toutes les 30 secondes (jusqu'à 5 tentatives, on fait un iwlist ath0 scan)
							//puis à la fin si toujours non connecté, on reconfigure le driver
							if(s_exploit_process_prncpl.s_station.u32_cptsecond_noconnected < u32_memo_cptsecond_noconnected)
							{
								u32_memo_cptsecond_noconnected = 0;	//RAZ: ce n'est pas normal
							}

							if((s_exploit_process_prncpl.s_station.u32_cptsecond_noconnected - u32_memo_cptsecond_noconnected) > loc_u32_timeout_noconnected)
							{
								u32_memo_cptsecond_noconnected = s_exploit_process_prncpl.s_station.u32_cptsecond_noconnected;
								u16_cpt_tentatives_reconnect++;
								if(u16_cpt_tentatives_reconnect < NB_MAX_TENTATIVES_STATION_TO_CONNECTED)
								{
									printf("Watchdog_Wifi: Force background scannning \n");
									CmdSystem_Generique("iwlist %s scan >/dev/null 2>&1",
										NOM_INTERFACE_WIFI);
								}
								else
								{
										//Re-configuration de l'équipement
									loc_u8_ordre_reconfig = TRUE;
								}
							}
						}
						else //CONDITION: station non connectée (depuis pas longtemps)
						{
							u32_memo_cptsecond_noconnected = 0;	//RAZ
						}
					}
					else //CONDITION: station connectée
					{
						u16_cpt_tentatives_reconnect = 0;	//RAZ
						u32_memo_cptsecond_noconnected = 0;	//RAZ
					}
				}			
				break;
			default:
				break;
		}

		if(TRUE == loc_u8_ordre_reconfig)
		{
			s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
			printf("Watchdog_Wifi: Force reconfiguration totale \n");
			Ordre_ReconfigurationTotale();
			s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
			u16_cpt_tentatives_reconnect = 0;	//RAZ
			u32_memo_cptsecond_noconnected = 0;	//RAZ
		}
	}
	else
	{
		u16_cpt_tentatives_reconnect = 0;	//RAZ
		u32_memo_cptsecond_noconnected = 0;	//RAZ
	}
}/*Watchdog_Wifi*/


//d: BE065.0 27/03/2012 (CM) - Correction bug inactivité station
//=====================================================================================
// Fonction		: Watchdog_ActivityWifi
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 01/12/2010 -
// Description	: Signal activité Wifi à l'AP
//=====================================================================================
void Watchdog_ActivityWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_donnees_inaccessible;

	loc_u8_donnees_inaccessible = FALSE; //INIT

	if(FALSE == u8TestConfig_InProgress()) //CONDITION: pas de reconfiguration en cours
	{
		switch(loc_ps_config->s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_ACCESS_POINT:
			case MODE_RADIO_MODEM_MONITOR:
				memcpy(pu8_memo_add_mac_AP, PU8_ADD_MAC_NULL, ETHER_ADDR_LEN);
				u32_cptsecond_connected = 0;	//RAZ
				break;
			case MODE_RADIO_MODEM_STATION:
				s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
				if(FALSE == u8FillExploitStationFile(&s_exploit_process_prncpl.s_station))
				{
					loc_u8_donnees_inaccessible = TRUE; //défaut accès bdd
				}
				s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

				if(FALSE == loc_u8_donnees_inaccessible) //CONDITION: BDD OK
				{
					if(STATUT_CONNEXION__ASSOCIATED == s_exploit_process_prncpl.s_station.u8_statut_connexion) //CONDITION: station connectée
					{
						if(0 == memcmp(pu8_memo_add_mac_AP, s_exploit_process_prncpl.s_station.pu8_bssid_add_mac, ETHER_ADDR_LEN)) //CONDITION: adresse MAC identique
						{
							u32_cptsecond_connected++;
							if(u32_cptsecond_connected > TIMEOUT_STATION_ACTIVITEE)
							{
								u32_cptsecond_connected = 0;	//RAZ
								//On envoie un datanull à l'AP (pour lui indiquer notre présence en cas d'inactivité)
								CmdSystem_Generique("iwpriv %s fr_sendnulldata 0",
													NOM_INTERFACE_WIFI);
							}
						}
						else
						{
							memcpy(pu8_memo_add_mac_AP, &s_exploit_process_prncpl.s_station.pu8_bssid_add_mac, ETHER_ADDR_LEN);
							u32_cptsecond_connected = 0;	//RAZ
						}
					}
					else //CONDITION: station non connectée
					{
						memcpy(pu8_memo_add_mac_AP, PU8_ADD_MAC_NULL, ETHER_ADDR_LEN);
						u32_cptsecond_connected = 0;	//RAZ
					}
				}			
				break;
			default:
				break;
		}
	}
	else
	{
		memcpy(pu8_memo_add_mac_AP, PU8_ADD_MAC_NULL, ETHER_ADDR_LEN);
		u32_cptsecond_connected = 0;	//RAZ
	}
}/*Watchdog_ActivityWifi*/
//f: BE065.0 27/03/2012 (CM) - Correction bug inactivité station


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_WatchdogWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 01/12/2010 -
// Description	: Initialisation du module de watchdogwifi
//=====================================================================================
void InitModule_WatchdogWifi(void)
{
	u16_cpt_tentatives_reconnect = 0;	//INIT
	u32_memo_cptsecond_noconnected = 0;	//INIT
//d: BE065.0 27/03/2012 (CM) - Correction bug inactivité station
	u32_cptsecond_connected = 0;	//INIT
	memcpy(pu8_memo_add_mac_AP, PU8_ADD_MAC_NULL, ETHER_ADDR_LEN); //INIT
//f: BE065.0 27/03/2012 (CM) - Correction bug inactivité station

}/*InitModule_WatchdogWifi*/

