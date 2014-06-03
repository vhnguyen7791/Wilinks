/*========================================================================*/
/* NOM DU FICHIER  : evt_ap.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/01/2011                                           */
/* Libelle         : Monitor: Calcul des évènements de l'AP				  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE058 24/01/2011 CM
// - CREATION
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EVT_AP

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u16sod u16_memo_channel;
static u16sod u16_memo_freq_radar_found;

//Mémorisation des clients WIFI connectés
static S_STRUCT_MEMO_WIFI_CLIENT s_memo_clientWifi[NB_ASSOCIATED_STATIONS_MAX];

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_AP
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Gestion des évènements AP
//=====================================================================================
void CalculEvents_AP(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit)
{
#ifdef _WRM100_N_SELECT
	if((MODE_RADIO_MODEM_ACCESS_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)&&
	   (FALSE == s_cip_monitor_courant.u8_info_reconfig_radiomodem)
	  )
	{
//		printf("%dMHZ CH=%d \n",loc_ps_exploit->s_access_point.u16_freq_MHz_inprogress,loc_ps_exploit->s_access_point.u16_channel_inprogress);
		if(FALSE == loc_ps_config->s_wifi.u8_desactivation_DFS)
		{
			if(CHANNEL_RADIO_DISABLED == u16_memo_channel)
			{
				u16_memo_channel = loc_ps_config->s_wifi.u16_iso_canal_radio;
			}
			else
			{
				if(loc_ps_exploit->s_access_point.u16_channel_inprogress != u16_memo_channel)
				{
					u16_memo_channel = loc_ps_exploit->s_access_point.u16_channel_inprogress;
					RegisterEvent(EVT012_BASCULEMENT_VERS_CANAL,0, (((u32sod)loc_ps_exploit->s_access_point.u16_channel_inprogress << 16)|(u32sod)(loc_ps_exploit->s_access_point.u16_freq_MHz_inprogress)), 0, NULL, 0, ETAT_EVT_INFO);
				}
			}

			if(u16_memo_freq_radar_found != t_driverWifiN_userinfo.u16_freq_radar_found)
			{
				RegisterEvent(EVT011_RADAR_DETECTE_SUR_CANAL,0, ((u32sod)u16MhzToIeee(t_driverWifiN_userinfo.u16_freq_radar_found) << 16)|(u32sod)(t_driverWifiN_userinfo.u16_freq_radar_found), 0, NULL, 0, ETAT_EVT_INFO);
				u16_memo_freq_radar_found = t_driverWifiN_userinfo.u16_freq_radar_found;
			}
		}
		else
		{
			u16_memo_channel = CHANNEL_RADIO_DISABLED; //RAZ
			u16_memo_freq_radar_found = 0; //RAZ
		}
	}
	else
	{
		u16_memo_channel = CHANNEL_RADIO_DISABLED; //RAZ
		u16_memo_freq_radar_found = 0; //RAZ
	}
#endif

	//Gestion de calcul des evts de connexion / déconnexion des stations
	CalculEvents_ConnexionDeconnexionStations(loc_ps_config, loc_ps_exploit);
	
}/*CalculEvents_AP*/

//=====================================================================================
// Fonction		: CalculEvents_ConnexionDeconnexionStations
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Gestion des évènements de connexion/deconnexion des stations sur l'AP
//=====================================================================================
void CalculEvents_ConnexionDeconnexionStations(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit)
{
	u16sod loc_u16_i;
	u8sod loc_u8_i;
	u8sod loc_u8_station_connected;

	loc_u8_station_connected = FALSE;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_ASSOCIATED_STATIONS_MAX;loc_u16_i++)
	{
		loc_u8_station_connected = FALSE; //RAZ

		//Détermine si station est connectée
		switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
		{
			case MODE_SECURITE_WIFI_AUCUN:
				if(TRUE == loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u8_present)
				{
					if((u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED) == (loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u32_statut & (u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED)))
					{
						loc_u8_station_connected = TRUE;
					}
				}
			break;
			case MODE_SECURITE_WIFI_WEP:
				break;
			case MODE_SECURITE_WIFI_WPA:
			case MODE_SECURITE_WIFI_WPA_TKIP:
			case MODE_SECURITE_WIFI_WPA_AES:
			case MODE_SECURITE_WIFI_WPA2:
			case MODE_SECURITE_WIFI_WPA2_TKIP:
			case MODE_SECURITE_WIFI_WPA2_AES:
				if(TRUE == loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u8_present)
				{
					if((u32sod)(1<<BIT2_STA_CLIENTWIFI_AUTHORIZED) == (loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u32_statut & (u32sod)(1<<BIT2_STA_CLIENTWIFI_AUTHORIZED)))
					{
						loc_u8_station_connected = TRUE;
					}
				}
				break;
			default:
				break;
		}

		if((TRUE == s_memo_clientWifi[loc_u16_i].u8_present)||
		   (TRUE == loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u8_present)
		  )		   
		{
#if 0
			printf("Memo Client Wifi %s u8_connected=%d time=%lu \n",
				   ps8GetChAddressMac(s_memo_clientWifi[loc_u16_i].pu8_add_mac),
				   s_memo_clientWifi[loc_u16_i].u8_connected,
				   s_memo_clientWifi[loc_u16_i].u32_time_reconnexion);
			printf("Actual Client Wifi %s u8_connected=%d time=%lu \n",
				   ps8GetChAddressMac(loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].pu8_add_mac),
				   loc_u8_station_connected,
				  loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u32_time_reconnexion);
#endif
			
			//Calcul des évènements
			if(TRUE == s_memo_clientWifi[loc_u16_i].u8_connected) //CONDITION: on a une station mémorisée
			{
				//Test si nouvelle station (avec adresse MAC différente)
				if(0 != memcmp(s_memo_clientWifi[loc_u16_i].pu8_add_mac, loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].pu8_add_mac, ETHER_ADDR_LEN))
				{
					//Déconnexion de la station mémorisée
					RegisterEvent(EVT014_DECONNEXION_STATION, (u32sod)(loc_u16_i+1), 0, 0, s_memo_clientWifi[loc_u16_i].pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
					RazMemoClientWifi(&s_memo_clientWifi[loc_u16_i]);	//RAZ
				}
				else
				{
					//Test si station déconnectée
					if(FALSE == loc_u8_station_connected)
					{
						//Déconnexion de la station mémorisée
						RegisterEvent(EVT014_DECONNEXION_STATION, (u32sod)(loc_u16_i+1), 0, 0, s_memo_clientWifi[loc_u16_i].pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
						RazMemoClientWifi(&s_memo_clientWifi[loc_u16_i]);	//RAZ
					}
					else
					{
						if(0 == s_memo_clientWifi[loc_u16_i].u32_time_reconnexion)//CONDITION: Initialisation
						{
							//on met à jour le time_reconnexion
							s_memo_clientWifi[loc_u16_i].u32_time_reconnexion = loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u32_time_reconnexion;
						}
						else
						{
							//test si station s'est reconnecté (si c'est le cas, c'est que la station s'est déconnecté mais n'a pas informé l'AP)
							if(s_memo_clientWifi[loc_u16_i].u32_time_reconnexion != loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].u32_time_reconnexion)
							{
								//on déconnecte d'abord
								RegisterEvent(EVT014_DECONNEXION_STATION, (u32sod)(loc_u16_i+1), 0, 0, s_memo_clientWifi[loc_u16_i].pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
								RazMemoClientWifi(&s_memo_clientWifi[loc_u16_i]);	//RAZ
							}
						}
					}
				}
			}
			else
			{
				if(TRUE == loc_u8_station_connected) //CONDITION: nouvelle station
				{
					//On mémorise la nouvelle station
					s_memo_clientWifi[loc_u16_i].u8_present = TRUE;
					s_memo_clientWifi[loc_u16_i].u8_connected = TRUE;
					for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
					{
						s_memo_clientWifi[loc_u16_i].pu8_add_mac[loc_u8_i] = loc_ps_exploit->s_access_point.s_wifi_client[loc_u16_i].pu8_add_mac[loc_u8_i];
					}
					s_memo_clientWifi[loc_u16_i].u32_time_reconnexion = 0;	//reste à 0 (on attend la prochaine seconde pour le mettre à jour, car on n'a pas encore le statut de hostapd)


					//Connexion de la station mémorisée
					RegisterEvent(EVT013_CONNEXION_STATION, (u32sod)(loc_u16_i+1), 0, 0, s_memo_clientWifi[loc_u16_i].pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
				}
			}
		}
	}
	
}/*CalculEvents_ConnexionDeconnexionStations*/

//=====================================================================================
// Fonction		: RazMemoClientWifi
// Entrees		: <loc_ps_memo_clientwifi< : pointeur sur client mémorisé
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Raz d'un clients wifi mémorisé
//=====================================================================================
void RazMemoClientWifi(S_STRUCT_MEMO_WIFI_CLIENT *loc_ps_memo_clientwifi)
{
	u8sod loc_u8_i;

	loc_ps_memo_clientwifi->u8_present = FALSE;	//RAZ
	loc_ps_memo_clientwifi->u8_connected = FALSE;	//RAZ
	for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
	{
		loc_ps_memo_clientwifi->pu8_add_mac[loc_u8_i] = 0x00;	//RAZ
	}
	loc_ps_memo_clientwifi->u32_time_reconnexion = 0;	//INIT

}/*RazMemoClientWifi*/

//=====================================================================================
// Fonction		: RazAllMemoClientsWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Raz de tous les clients wifi mémorisés
//=====================================================================================
void RazAllMemoClientsWifi(void)
{
	u16sod loc_u16_i;

	for(loc_u16_i=0;loc_u16_i<NB_ASSOCIATED_STATIONS_MAX;loc_u16_i++)
	{
		RazMemoClientWifi(&s_memo_clientWifi[loc_u16_i]);	//RAZ
	}
	
}/*RazAllMemoClientsWifi*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Evt_AP
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Initialisation du module evt_AP
//=====================================================================================
void InitModule_Evt_AP(void)
{
	u16_memo_channel = CHANNEL_RADIO_DISABLED; //INIT
	u16_memo_freq_radar_found = 0; //INIT

	RazAllMemoClientsWifi();	//INIT
	
}/*InitModule_Evt_AP*/
