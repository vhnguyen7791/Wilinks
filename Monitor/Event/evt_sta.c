/*========================================================================*/
/* NOM DU FICHIER  : evt_sta.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/01/2011                                           */
/* Libelle         : Monitor: Calcul des évènements de la STAtion		  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE058 24/01/2011 CM
// - CREATION
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
// - Correction bug alarmes station non connectée et niveau recu bagottent si station n'est pas connectée
//	à cause de la fonction de watchdog wifi
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EVT_STA


#define MAX_DEBOUNCE_NIVEAU_RX		3	//secondes

#define MAX_DEBOUNCE_AL_STATION_NO_CONNECTED  2	//secondes

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//pour debouncer l'alarme niveau RX
static u8sod u8_debounce_al_niveau_rx;
static u8sod u8_debounce_noal_niveau_rx;

//pour debouncer l'alarme station non connectée
static u8sod u8_debounce_al_no_connected_station;

//Gestion évènement switch from primary SSID to secondary SSID (and vice versa)
enum LIST_WHICH_SSID
{
	WHICH_SSID_NONE = 0,
	WHICH_SSID_PRIMARY,
	WHICH_SSID_SECONDARY,
	NB_MAX_WHICH_SSID
};
static u8sod u8_which_ssid;

//Mémorisation de l'AP connecté
static S_STRUCT_MEMO_BSSID s_memo_bssid;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_STA
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Gestion des évènements STATION
//=====================================================================================
void CalculEvents_STA(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit)
{
	u8sod loc_u8_isconnected;
	u8sod	loc_u8_i;
	
	loc_u8_isconnected = TRUE;	//INIT

	if((MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)&&
	   (FALSE == s_cip_monitor_courant.u8_info_reconfig_radiomodem)
	  )
	{
		//Debounce etat station non connectee
		if(STATUT_CONNEXION__ASSOCIATED != loc_ps_exploit->s_station.u8_statut_connexion) //CONDITION: non connectée
		{
			u8_debounce_al_no_connected_station++;
			if(u8_debounce_al_no_connected_station >= MAX_DEBOUNCE_AL_STATION_NO_CONNECTED)//CONDITION: debounce OK
			{
				loc_u8_isconnected = FALSE;
				u8_debounce_al_no_connected_station = MAX_DEBOUNCE_AL_STATION_NO_CONNECTED+1;	//on sature
			}
		}
		else
		{
			u8_debounce_al_no_connected_station = 0; //RAZ
		}

#if 0
		printf("Memo Bssid %s u8_connected=%d \n",
			   ps8GetChAddressMac(s_memo_bssid.pu8_add_mac),
			   s_memo_bssid.u8_connected);
		printf("Actual Bssid %s u8_connected=%d \n",
			   ps8GetChAddressMac(loc_ps_exploit->s_station.pu8_bssid_add_mac),
			   loc_u8_isconnected);
#endif
			   
		
		//Alarme station non connectée
		if(FALSE == loc_u8_isconnected)
		{
			RegisterEvent(EVT006_STATION_NON_CONNECTEE, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
			RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, VALEUR_RSSI_NULL, 0, NULL, 0, ETAT_EVT_DEBUT);
			u8_debounce_al_niveau_rx = MAX_DEBOUNCE_NIVEAU_RX;	//on sature
			u8_debounce_noal_niveau_rx = 0;	//RAZ
			u8_which_ssid = WHICH_SSID_NONE; //RAZ
			if(TRUE == s_memo_bssid.u8_connected)
			{
				RegisterEvent(EVT016_DECONNEXION_ACCESS_POINT, 0, 0, 0, s_memo_bssid.pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
				RazMemoBssidWifi(&s_memo_bssid); //RAZ
			}
		}
		else //CONDITION: station connectée
		{
			RegisterEvent(EVT006_STATION_NON_CONNECTEE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
			if(0 != memcmp(loc_ps_exploit->s_station.pu8_bssid_add_mac, PU8_ADD_MAC_NULL, ETHER_ADDR_LEN)) //CONDITION: adresse MAC non nulle
			{
				if(TRUE == s_memo_bssid.u8_connected)//CONDITION: STATION est déjà connecté
				{
					//Test si nouveau access point (avec adresse MAC différente)
					if(0 != memcmp(s_memo_bssid.pu8_add_mac, loc_ps_exploit->s_station.pu8_bssid_add_mac, ETHER_ADDR_LEN))
					{
						//on se déconnecte d'abord
						//et dans la prochaine seconde, on se reconnecte
						RegisterEvent(EVT016_DECONNEXION_ACCESS_POINT, 0, 0, 0, s_memo_bssid.pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
						RazMemoBssidWifi(&s_memo_bssid); //RAZ
					}
				}
				else //CONDITION: STATION pas encore connectée
				{
					s_memo_bssid.u8_connected = TRUE;
					for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
					{
						s_memo_bssid.pu8_add_mac[loc_u8_i] = loc_ps_exploit->s_station.pu8_bssid_add_mac[loc_u8_i];
					}
					RegisterEvent(EVT015_CONNEXION_ACCESS_POINT, 0, 0, 0, s_memo_bssid.pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
				}
			}
			else
			{
				printf("CalculEvents_STA MAC AP NULLE \n");
			}

			//Alarme niveau reçu (debounce)
			if(loc_ps_exploit->s_station.s32_rssi_dbm < (s32sod)loc_ps_config->s_wifi.s8_seuil_rx)//CONDITION: niveau rx au dessous du seuil défini
			{
				u8_debounce_al_niveau_rx ++;
				u8_debounce_noal_niveau_rx = 0;	//RAZ
			}
			else
			{
				u8_debounce_al_niveau_rx = 0;	//RAZ
				u8_debounce_noal_niveau_rx++;
			}

			if(u8_debounce_al_niveau_rx >= MAX_DEBOUNCE_NIVEAU_RX)//CONDITION: debounce OK
			{
				u8_debounce_al_niveau_rx = MAX_DEBOUNCE_NIVEAU_RX;	//on sature
				RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, loc_ps_exploit->s_station.s32_rssi_dbm, 0, NULL, 0, ETAT_EVT_DEBUT);
			}
			else
			{
				if(u8_debounce_noal_niveau_rx >= MAX_DEBOUNCE_NIVEAU_RX)//CONDITION: debounce OK
				{
					u8_debounce_noal_niveau_rx = MAX_DEBOUNCE_NIVEAU_RX;	//on sature
					RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, loc_ps_exploit->s_station.s32_rssi_dbm, 0, NULL, 0, ETAT_EVT_FIN);
				}
				else
				{
					//on conserve l'état précédent
					if(TRUE == u8GetU8EtatBit(u8GetEtatAlarme(&s_exp_events_process_mntr, EVT005_AL_NIVEAU_RECU), EVT005_AL_NIVEAU_RECU)) //CONDITION:  alarme présente dans la seconde précedente
					{
						RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, loc_ps_exploit->s_station.s32_rssi_dbm, 0, NULL, 0, ETAT_EVT_DEBUT);
					}
					else
					{
						RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, loc_ps_exploit->s_station.s32_rssi_dbm, 0, NULL, 0, ETAT_EVT_FIN);
					}
				}
			}

			//Gestion évènements dual ssid
			if(TRUE == loc_ps_config->s_wifi.u8_dual_ssid)
			{
//					printf("SSID:*%s*\n",loc_ps_exploit->s_station.ps8_ssid_inprogress);
//					printf("SSID_prim:*%s*\n",loc_ps_config->s_wifi.ps8_ssid_primary);
//					printf("SSID_secon:*%s*\n",loc_ps_config->s_wifi.ps8_ssid_secondary);
				if(0 == strcmp(loc_ps_config->s_wifi.ps8_ssid_primary, loc_ps_exploit->s_station.ps8_ssid_inprogress))
				{
					if(WHICH_SSID_PRIMARY != u8_which_ssid)
					{
						RegisterEvent(EVT009_RETOUR_SUR_SSID_PRIMAIRE,0, 0, 0, NULL, 0, ETAT_EVT_INFO);
						u8_which_ssid = WHICH_SSID_PRIMARY;
					}
				}
				else
				{
					if(0 == strcmp(loc_ps_config->s_wifi.ps8_ssid_secondary, loc_ps_exploit->s_station.ps8_ssid_inprogress))
					{
						if(WHICH_SSID_SECONDARY != u8_which_ssid)
						{
							RegisterEvent(EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE,0, 0, 0, NULL, 0, ETAT_EVT_INFO);
							u8_which_ssid = WHICH_SSID_SECONDARY;
						}
					}
				}
			}
			else
			{
				u8_which_ssid = WHICH_SSID_NONE; //RAZ
			}

		}
	}
	else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR ou (MODE_RADIO_MODEM_STATION et reconfig)
	{
		if(MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)//CONDITION: station qui se reconfigure
		{
			//on conserve l'état précédent
			if(TRUE == u8GetU8EtatBit(u8GetEtatAlarme(&s_exp_events_process_mntr, EVT005_AL_NIVEAU_RECU), EVT005_AL_NIVEAU_RECU)) //CONDITION:  alarme présente dans la seconde précedente
			{
				RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, loc_ps_exploit->s_station.s32_rssi_dbm, 0, NULL, 0, ETAT_EVT_DEBUT);
			}
			else
			{
				RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, loc_ps_exploit->s_station.s32_rssi_dbm, 0, NULL, 0, ETAT_EVT_FIN);
			}
			//on conserve l'état précédent
			if(TRUE == u8GetU8EtatBit(u8GetEtatAlarme(&s_exp_events_process_mntr, EVT006_STATION_NON_CONNECTEE), EVT006_STATION_NON_CONNECTEE)) //CONDITION:  alarme présente dans la seconde précedente
			{
				RegisterEvent(EVT006_STATION_NON_CONNECTEE, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
			}
			else
			{
				RegisterEvent(EVT006_STATION_NON_CONNECTEE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
			}
		}
		else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
		{
			u8_debounce_al_niveau_rx = 0;	//RAZ
			u8_debounce_noal_niveau_rx = 0;	//RAZ
			RegisterEvent(EVT005_AL_NIVEAU_RECU, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
			u8_which_ssid = WHICH_SSID_PRIMARY; //RAZ
			u8_debounce_al_no_connected_station = 0;	//RAZ
			if(TRUE == s_memo_bssid.u8_connected)//CONDITION: STATION était connecté
			{
				//on se déconnecte
				RegisterEvent(EVT016_DECONNEXION_ACCESS_POINT, 0, 0, 0, s_memo_bssid.pu8_add_mac, ETHER_ADDR_LEN, ETAT_EVT_INFO);
			}
			RazMemoBssidWifi(&s_memo_bssid); //RAZ
		}
	}

}/*CalculEvents_STA*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: RazMemoBssidWifi
// Entrees		: <loc_ps_memo_bssidwifi< : pointeur sur AP mémorisé
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Raz du bssid wifi mémorisé
//=====================================================================================
void RazMemoBssidWifi(S_STRUCT_MEMO_BSSID *loc_ps_memo_bssidwifi)
{
	u8sod loc_u8_i;

	loc_ps_memo_bssidwifi->u8_connected = FALSE;	//RAZ
	for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
	{
		loc_ps_memo_bssidwifi->pu8_add_mac[loc_u8_i] = 0x00;	//RAZ
	}

}/*RazMemoBssidWifi*/

//=====================================================================================
// Fonction		: InitModule_Evt_STA
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Initialisation du module evt_sta
//=====================================================================================
void InitModule_Evt_STA(void)
{	u8_debounce_al_niveau_rx = 0;	//INIT
	u8_debounce_noal_niveau_rx = 0;	//INIT
	u8_debounce_al_no_connected_station = 0;	//INIT

	u8_which_ssid = WHICH_SSID_PRIMARY; //INIT

	RazMemoBssidWifi(&s_memo_bssid); //INIT
	
}/*InitModule_Evt_STA*/
