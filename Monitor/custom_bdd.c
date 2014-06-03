/*========================================================================*/
/* NOM DU FICHIER  : custom_bdd.c	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: Personnalise la base de données			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout nouveaux évènements liés au DFS
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _CUSTOM_BDD

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CustomBdd_EnFonctionAllOptionsHard
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Personnalise la base de données en fonction de toutes
// les options hards
//=====================================================================================
void CustomBdd_EnFonctionAllOptionsHard(void)
{
}/*CustomBdd_EnFonctionAllOptionsHard*/


//=====================================================================================
// Fonction		: CustomBdd_EnFonctionConfig
// Entrees		: <loc_ps_config<: pointeur sur configuration equipement
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Personnalise la base de données en fonction de la configuration
//=====================================================================================
void CustomBdd_EnFonctionConfig(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	

}/*CustomBdd_EnFonctionConfig*/


//=====================================================================================
// Fonction		: CustomBddEvents_EnFonctionConfig
// Entrees		: <loc_ps_config<: pointeur sur configuration equipement
//				: <loc_pt_eventsystem< : pointeur sur systeme evt
// Sortie		: rien
// Auteur		: CM - 08/07/2010 -
// Description	: Personnalise la base de données des évènements en fonction de la configuration
//=====================================================================================
void CustomBddEvents_EnFonctionConfig(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EVENTSYSTEM *loc_pt_eventsystem)
{
	s32sod	loc_s32_sem;

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillEventSystemFile(loc_pt_eventsystem))
	{
		switch(loc_ps_config->s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_ACCESS_POINT:
				ResetEventDisponible(EVT005_AL_NIVEAU_RECU);
				ResetEventDisponible(EVT006_STATION_NON_CONNECTEE);
				ResetEventDisponible(EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE);
				ResetEventDisponible(EVT009_RETOUR_SUR_SSID_PRIMAIRE);
				if(FALSE == loc_ps_config->s_wifi.u8_desactivation_DFS)
				{
					SetEventDisponible(EVT011_RADAR_DETECTE_SUR_CANAL);
					SetEventDisponible(EVT012_BASCULEMENT_VERS_CANAL);
				}
				else
				{
					ResetEventDisponible(EVT011_RADAR_DETECTE_SUR_CANAL);
					ResetEventDisponible(EVT012_BASCULEMENT_VERS_CANAL);
				}
				SetEventDisponible(EVT013_CONNEXION_STATION);
				SetEventDisponible(EVT014_DECONNEXION_STATION);
				ResetEventDisponible(EVT015_CONNEXION_ACCESS_POINT);
				ResetEventDisponible(EVT016_DECONNEXION_ACCESS_POINT);
				break;
			case MODE_RADIO_MODEM_STATION:
				SetEventDisponible(EVT005_AL_NIVEAU_RECU);
				SetEventDisponible(EVT006_STATION_NON_CONNECTEE);
				if(TRUE == loc_ps_config->s_wifi.u8_dual_ssid)
				{
					SetEventDisponible(EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE);
					SetEventDisponible(EVT009_RETOUR_SUR_SSID_PRIMAIRE);
				}
				else
				{
					ResetEventDisponible(EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE);
					ResetEventDisponible(EVT009_RETOUR_SUR_SSID_PRIMAIRE);
				}
				ResetEventDisponible(EVT011_RADAR_DETECTE_SUR_CANAL);
				ResetEventDisponible(EVT012_BASCULEMENT_VERS_CANAL);
				ResetEventDisponible(EVT013_CONNEXION_STATION);
				ResetEventDisponible(EVT014_DECONNEXION_STATION);
				SetEventDisponible(EVT015_CONNEXION_ACCESS_POINT);
				SetEventDisponible(EVT016_DECONNEXION_ACCESS_POINT);
				break;
			case MODE_RADIO_MODEM_MONITOR:
				ResetEventDisponible(EVT005_AL_NIVEAU_RECU);
				ResetEventDisponible(EVT006_STATION_NON_CONNECTEE);
				ResetEventDisponible(EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE);
				ResetEventDisponible(EVT009_RETOUR_SUR_SSID_PRIMAIRE);
				ResetEventDisponible(EVT011_RADAR_DETECTE_SUR_CANAL);
				ResetEventDisponible(EVT012_BASCULEMENT_VERS_CANAL);
				ResetEventDisponible(EVT013_CONNEXION_STATION);
				ResetEventDisponible(EVT014_DECONNEXION_STATION);
				ResetEventDisponible(EVT015_CONNEXION_ACCESS_POINT);
				ResetEventDisponible(EVT016_DECONNEXION_ACCESS_POINT);
				break;
			default:
				break;
		}

		switch(loc_ps_config->s_admin.u8_mode_mah)
		{
			case MODE_MAH_NTP:
			case MODE_MAH_SNTP:
				SetEventDisponible(EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE);
				break;
			case MODE_MAH_MANUELLE:
			default:
				ResetEventDisponible(EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE);
				break;
		}
		
		u8EditEventSystemFile(loc_pt_eventsystem);
	}
	else
	{
		printf("CustomBddEvents_EnFonctionConfig: Erreur lecture EventSystem \n");
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem

}/*CustomBddEvents_EnFonctionConfig*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_CustomBdd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/05/2008 -
// Description	: Initialisation du module custom_Bdd
//=====================================================================================
void InitModule_CustomBdd(void)
{
	
}/*InitModule_CustomBdd*/
