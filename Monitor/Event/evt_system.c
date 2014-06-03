/*========================================================================*/
/* NOM DU FICHIER  : evt_system.c	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/07/2010                                           */
/* Libelle         : Monitor: Calcul des évènements system				  */
/* Projet          : WRM100                                               */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE037 06/07/2010 CM
// - CREATION
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
// - Correction alarme température à tort suite A/M
//		durée de 1 seconde
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
// - Correction debounce alarme non connecté de la station
// - Correction gestion alarme niveau rx de la station
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout nouveaux évènements liés au DFS
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _EVT_SYSTEM

#define	SEUIL_ALARME_TEMPERATURE	85	//°Celsius

#define MAX_DEBOUNCE_AL_TEMPERATURE		3	//secondes

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u8sod u8_debounce_al_temperature;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_System
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Gestion des évènements system
//=====================================================================================
void CalculEvents_System(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit)
{
	u8sod loc_u8_i;
	
	//Alarme temperature
	if(loc_ps_exploit->s_general.s32_temperature > SEUIL_ALARME_TEMPERATURE)//CONDITION: température au dessus du seuil défini
	{
		u8_debounce_al_temperature++;

		if(u8_debounce_al_temperature >= MAX_DEBOUNCE_AL_TEMPERATURE)//CONDITION: debounce OK
		{
			u8_debounce_al_temperature = MAX_DEBOUNCE_AL_TEMPERATURE; //on sature
			RegisterEvent(EVT002_AL_TEMPERATURE, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
		}
		else
		{
			RegisterEvent(EVT002_AL_TEMPERATURE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
		}
	}
	else
	{
		u8_debounce_al_temperature = 0; //RAZ
		RegisterEvent(EVT002_AL_TEMPERATURE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
	}

	//Alarme Ethernet LAN 1
	if(FALSE == loc_ps_exploit->s_general.u8_link_statut_ethernet[PORT_ETHERNET_1]) //CONDITION: non connecté?
	{
		RegisterEvent(EVT003_AL_ETHERNET_LAN_1, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
	}
	else//CONDITION: connecté
	{
		RegisterEvent(EVT003_AL_ETHERNET_LAN_1, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
	}

	//Alarme Ethernet LAN 2
	if(FALSE == loc_ps_exploit->s_general.u8_link_statut_ethernet[PORT_ETHERNET_2]) //CONDITION: non connecté?
	{
		RegisterEvent(EVT004_AL_ETHERNET_LAN_2, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
	}
	else//CONDITION: connecté
	{
		RegisterEvent(EVT004_AL_ETHERNET_LAN_2, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
	}
	
	//Gestion de l'évolution de la configuration
	for(loc_u8_i=0; loc_u8_i<NB_MAX_IDXCONFIG; loc_u8_i++)
	{
		if(TRUE == s_cip_monitor_courant.pu8_flag_newcfg[loc_u8_i])
		{
			RegisterEvent(EVT112_EVOLUTION_CONFIGURATION,0, 0, 0, NULL, 0, ETAT_EVT_INFO);
			loc_u8_i = NB_MAX_IDXCONFIG + 1; //on sort
		}
	}
	
	//Calcul alarme "aucun serveur NTP accessible"
	switch(loc_ps_config->s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
		case MODE_MAH_SNTP:
			if((TRUE == loc_ps_exploit->s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_PRINCIPAL])||
			   ((ADRESSE_IP_NULLE != loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])&&
				  (TRUE == loc_ps_exploit->s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_SECOURS]))
			  )	//CONDITION: au moins un serveur accessible
			{
				RegisterEvent(EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
			}
			else //CONDITION: aucun serveur NTP accessible
			{
				RegisterEvent(EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE, 0, 0, 0, NULL, 0, ETAT_EVT_DEBUT);
			}
			break;
		case MODE_MAH_MANUELLE:
		default:
			RegisterEvent(EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE, 0, 0, 0, NULL, 0, ETAT_EVT_FIN);
			break;
	}
	
	//Gestion redémarrage télécommandé de l'équipement
	if(TRUE == s_cip_monitor_courant.u8_restart_equipment) //CONDITION: ordre donné
	{
		RegisterEvent(EVT113_ORDRE_RESET_TELECOMMANDE,0, 0, 0, NULL, 0, ETAT_EVT_INFO);
	}

}/*CalculEvents_System*/

//=====================================================================================
// Fonction		: CalculEvent_PbConfig
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Gestion de l'évènement probleme configuration
//=====================================================================================
void CalculEvent_PbConfig(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit)
{
	u8sod loc_u8_i;

	for(loc_u8_i=0; loc_u8_i<NB_MAX_ERRORCONFIG; loc_u8_i++)
	{
		if(TRUE == s_cip_monitor_courant.pu8_flag_errorconfig[loc_u8_i])
		{
			RegisterEvent(EVT007_PROBLEME_CONFIGURATION, (u32sod)(loc_u8_i+1), 0, 0, NULL, 0, ETAT_EVT_DEBUT);
		}
		else
		{
			RegisterEvent(EVT007_PROBLEME_CONFIGURATION, (u32sod)(loc_u8_i+1), 0, 0, NULL, 0, ETAT_EVT_FIN);
		}
	}
	
}/*CalculEvent_PbConfig*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Evt_System
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Initialisation du module evt_system
//=====================================================================================
void InitModule_Evt_System(void)
{
	u8_debounce_al_temperature = 0; //INIT
	
}/*InitModule_Evt_System*/
