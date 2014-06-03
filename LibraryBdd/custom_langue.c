/*========================================================================*/
/* NOM DU FICHIER  : custom_langue.c	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Base de données: personalisation de libellés langue  */
/* Projet          : WRM100                                               */
/* Indice	       : BE060												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE007 25/01/2010 CM
// - Ajout exploitation de l'ACCESS POINT
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE042 07/10/2010 CM
// - Ajout gestion debit MCS pour 802.11n
//BE051 13/12/2010 CM
// - Correction gestion alarme niveau rx de la station
//BE058 21/01/2011 CM
// - Ajout nouveaux évènements liés au DFS
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define	_CUSTOM_LANGUE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//Fonction: ps8ChLibelleEvt
static	s8sod	ps8_chaine_col_general[UI_TAILLE_MAX_MESSAGE_2];
static	s8sod	ps8_chaine_col0[UI_TAILLE_MAX_MESSAGE];
static	s8sod	ps8_chaine_col1[UI_TAILLE_MAX_MESSAGE];
static	s8sod	ps8_chaine_col2[UI_TAILLE_MAX_MESSAGE];
static	s8sod	ps8_chaine_col3[UI_TAILLE_MAX_MESSAGE];
static	s8sod	ps8_chaine_libelle_evt_detaille[4*UI_TAILLE_MAX_MESSAGE];

//============================================================================
// Fonction		: ps8GetChAddressMac
// Entrees		: <loc_pu8_adr_mac< : pointeur sur tableau adresse MAC
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 26/10/2009 -
// Description	: renvoie la chaîne à afficher de l'adresse MAC
//============================================================================
s8sod* ps8GetChAddressMac(u8sod *loc_pu8_adr_mac)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	sprintf(loc_ps8_chaine,"%02X:%02X:%02X:%02X:%02X:%02X",
			loc_pu8_adr_mac[0], loc_pu8_adr_mac[1],
			loc_pu8_adr_mac[2], loc_pu8_adr_mac[3],
			loc_pu8_adr_mac[4], loc_pu8_adr_mac[5]);

	return (&loc_ps8_chaine[0]);
}/*ps8GetChAddressMac*/

//============================================================================
// Fonction		: ps8GetChBssid
// Entrees		: <loc_ps_exploit_gene> : pointeur sur exploit générale
//				 <loc_u8_index_langue> : index de la langue à afficher
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 26/10/2009 -
// Description	: renvoie la chaîne à afficher de l'état de la connexion BSSID
//============================================================================
s8sod* ps8GetChBssid(S_STRUCT_EXP_STATION *loc_ps_exploit_station, u8sod loc_u8_index_langue)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	switch(loc_ps_exploit_station->u8_statut_connexion)
	{
		case STATUT_CONNEXION__NOT_ASSOCIATED:
		case STATUT_CONNEXION__INVALID:
		case STATUT_CONNEXION__NONE:
			sprintf(loc_ps8_chaine,"%s",
					pt_tb_msg[loc_u8_index_langue].ps8_msg_choix_station_connexion[loc_ps_exploit_station->u8_statut_connexion]);
			break;
		case STATUT_CONNEXION__ASSOCIATED:
			sprintf(loc_ps8_chaine,"%s: %s",
					pt_tb_msg[loc_u8_index_langue].ps8_msg_choix_station_connexion[loc_ps_exploit_station->u8_statut_connexion],
					ps8GetChAddressMac(loc_ps_exploit_station->pu8_bssid_add_mac));
			break;
		default:
			break;
	}

	return (&loc_ps8_chaine[0]);
}/*ps8GetChBssid*/

//============================================================================
// Fonction		: ps8GetChStatutClientWifi
// Entrees		: <loc_u8_cfg_mode_securite_wifi> : mode de sécurité wifi configuré
//		  		  <loc_u32_exp_statut_client_wifi> : statut client wifi
//		  		  <loc_u8_index_langue> : index de la langue à afficher
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 26/01/2010 -
// Description	: renvoie la chaîne à afficher du statut du client Wifi
//============================================================================
s8sod* ps8GetChStatutClientWifi(u8sod loc_u8_cfg_mode_securite_wifi, u32sod loc_u32_exp_statut_client_wifi, u8sod loc_u8_index_langue)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	switch(loc_u8_cfg_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_AUCUN:
			if((u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED) == (loc_u32_exp_statut_client_wifi & (u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED)))
			{
				sprintf(loc_ps8_chaine,"%s",
						pt_tb_msg[loc_u8_index_langue].ps8_msg_associe);
			}
			else
			{
				sprintf(loc_ps8_chaine,"%s",
						pt_tb_msg[loc_u8_index_langue].ps8_msg_non_associe);
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
			if((u32sod)(1<<BIT2_STA_CLIENTWIFI_AUTHORIZED) == (loc_u32_exp_statut_client_wifi & (u32sod)(1<<BIT2_STA_CLIENTWIFI_AUTHORIZED)))
			{
				sprintf(loc_ps8_chaine,"%s",
						pt_tb_msg[loc_u8_index_langue].ps8_msg_connection_wpa_active);
			}
			else
			{
				if((u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED) == (loc_u32_exp_statut_client_wifi & (u32sod)(1<<BIT1_STA_CLIENTWIFI_ASSOCIATED)))
				{
					sprintf(loc_ps8_chaine,"%s",
							pt_tb_msg[loc_u8_index_langue].ps8_msg_associe);
				}
				else
				{
					sprintf(loc_ps8_chaine,"%s",
							pt_tb_msg[loc_u8_index_langue].ps8_msg_non_associe);
				}
			}
			break;
		default:
			break;
	}

	return (&loc_ps8_chaine[0]);
}/*ps8GetChStatutClientWifi*/

//============================================================================
// Fonction    : ChNiveauGravite
// Entrees     : <loc_u8_niveauGravite> : niveau de gravité
//				 <loc_ps8_chaine<	: chaine retournée
//				 <loc_u8_index_langue> : index de la langue à afficher
// Sortie	   : rien
// Auteur	   : CM - 26/10/2009 -
// Description : Procedure qui retourne en chaine de caractère le niveau de gravité
// Historique  : 
//============================================================================
void ChNiveauGravite(s8sod *loc_ps8_chaine, u8sod loc_u8_niveauGravite, u8sod	loc_u8_index_langue)
{
	loc_ps8_chaine[0] =0;

	switch(loc_u8_niveauGravite)
	{
		case NIV_GRAVITE_INDETERMINE:
			strcpy(loc_ps8_chaine,pt_tb_msg[loc_u8_index_langue].ps8_msg_indetermine);
			break;
		case NIV_GRAVITE_CRITIQUE:
			strcpy(loc_ps8_chaine,pt_tb_msg[loc_u8_index_langue].ps8_msg_critique);
			break;
		case NIV_GRAVITE_MAJEUR:
			strcpy(loc_ps8_chaine,pt_tb_msg[loc_u8_index_langue].ps8_msg_majeur);
			break;
		case NIV_GRAVITE_MINEUR:
			strcpy(loc_ps8_chaine,pt_tb_msg[loc_u8_index_langue].ps8_msg_mineur);
			break;
		case NIV_GRAVITE_AVERTISSEMENT:
			strcpy(loc_ps8_chaine,pt_tb_msg[loc_u8_index_langue].ps8_msg_avertissement);
			break;
		default:
			strcpy((s8sod *)loc_ps8_chaine,(const s8sod *)"?");
			break;
	}
}/*ChNiveauGravite*/

//============================================================================
// Fonction		: ps8ChLibelleEvt
// Entrees		: <loc_u16_indice_evt> : indice evt
//				 <loc_t_valeur_evt> : valeur evt
//				 <loc_u32_info_sup1> : info supplémentaire 1 de l'evt
//				 <loc_u8_info_sup2> : info supplémentaire 2 de l'evt
//				 <loc_pu8_info_sup3> : info supplémentaire 3 de l'evt
//				 <loc_u8_etat_evt> : état evt
//				 <loc_u8_index_langue> : index de la langue à afficher
//				 <loc_u8_mode_affichage> : mode d'affichage pour HTML ou fichier log
// Sortie	    : <ps8_chaine_libelle_evt_detaille< : chaîne retournée
// Auteur		: CM - 26/10/2009 -
// Description	: Procedure qui retourne en chaine de caractère le libellé des évènements
// Historique	: 
//============================================================================
s8sod* ps8ChLibelleEvt(u16sod			 loc_u16_indice_evt,
					   T_SIZE_VALEUR_EVT loc_t_valeur_evt,
					   u32sod			 loc_u32_info_sup1,
					   u8sod			 loc_u8_info_sup2,
					   u8sod			 *loc_pu8_info_sup3,
					   u8sod			 loc_u8_etat_evt,
					   u8sod			 loc_u8_index_langue,
					   u8sod			 loc_u8_mode_affichage)
{
	
	U_UNION_INFO_SUP	loc_u_info_sup1;

	loc_u_info_sup1.u32_term = loc_u32_info_sup1;

	ps8_chaine_libelle_evt_detaille[0] =0; //INIT
	strcpy(ps8_chaine_col0, "");	//INIT
	strcpy(ps8_chaine_col1, "");	//INIT
	strcpy(ps8_chaine_col2, "");	//INIT
	strcpy(ps8_chaine_col3, "");	//INIT

	if (loc_u16_indice_evt < NB_MAX_EVENEMENTS)
	{
		//Champs: libellé de l'évènement
		strcpy(ps8_chaine_col1,pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_evenement[loc_u16_indice_evt]);

		//Détail pour chaque évènements
		switch(loc_u16_indice_evt)
		{
			case EVT005_AL_NIVEAU_RECU:
				if(ETAT_EVT_DEBUT == loc_u8_etat_evt)
				{
					if(VALEUR_RSSI_NULL == (s32sod)loc_u_info_sup1.u32_term)
					{
						sprintf(ps8_chaine_col2, "<%ld dBm", (s32sod)VALEUR_RSSI_MIN);
					}
					else
					{
						sprintf(ps8_chaine_col2, "%ld dBm", (s32sod)loc_u_info_sup1.u32_term);
					}
				}
				break;
			case EVT007_PROBLEME_CONFIGURATION:
				if((loc_t_valeur_evt-1) < NB_MAX_ERRORCONFIG)
				{
					strcpy(ps8_chaine_col2,pt_tb_msg[loc_u8_index_langue].ps8_msg_lib_errorconfig[(loc_t_valeur_evt-1)]);
				}
				break;
#if TEST_DEBUG_EVENT
//d: ------------- debug -----------------------------------------------
			case EVT177_RESERVE:
				sprintf(ps8_chaine_col2, "(%lu)", loc_t_valeur_evt);
				break;
//f: ------------- debug -----------------------------------------------
#endif
			case EVT011_RADAR_DETECTE_SUR_CANAL:
				sprintf(ps8_chaine_col2, "(%d MHz / CH=%d)",
						loc_u_info_sup1.pu16_term[1],
						loc_u_info_sup1.pu16_term[0]);
				break;
			case EVT012_BASCULEMENT_VERS_CANAL:
				sprintf(ps8_chaine_col2, "(%d MHz / CH=%d)",
						loc_u_info_sup1.pu16_term[1],
					    loc_u_info_sup1.pu16_term[0]);
				break;
			case EVT013_CONNEXION_STATION:
			case EVT014_DECONNEXION_STATION:
			case EVT015_CONNEXION_ACCESS_POINT:
			case EVT016_DECONNEXION_ACCESS_POINT:
				strcpy(ps8_chaine_col2, ps8GetChAddressMac(loc_pu8_info_sup3));
				break;
			default:
				break;
		}

		if(MODE_AFF_LIB_EVT_POUR_HTML == loc_u8_mode_affichage)
		{
			strcpy(ps8_chaine_col_general,""); //RAZ
			
			strcat(ps8_chaine_col_general,ps8_chaine_col1);
			
			if(		(0 != strcmp(ps8_chaine_col2, ""))
				||	(0 != strcmp(ps8_chaine_col3, ""))
			  )
			{
				if(0 != strcmp(ps8_chaine_col2, ""))
				{
					strcat(ps8_chaine_col_general, " / "); //Ajout séparateur
					strcat(ps8_chaine_col_general, ps8_chaine_col2);
				}
				if(0 != strcmp(ps8_chaine_col3, ""))
				{
					strcat(ps8_chaine_col_general, " / "); //Ajout séparateur
					strcat(ps8_chaine_col_general, ps8_chaine_col3);
				}
			}
			
			sprintf(ps8_chaine_libelle_evt_detaille,"%-68s",
					ps8_chaine_col_general);
		}
		else //MODE_AFF_LIB_EVT_POUR_FICHIER
		{
			//on insère des tabulations entre champs (pour que le
			//fichier soit exploitable par Excel)
			sprintf(ps8_chaine_libelle_evt_detaille,"%-60s\t%-35s\t%-40s",
					ps8_chaine_col1,
					ps8_chaine_col2,
					ps8_chaine_col3);
		}
	}
	else
	{
		strcpy((s8sod *)ps8_chaine_libelle_evt_detaille,(const s8sod *)"?");
	}

	return (&ps8_chaine_libelle_evt_detaille[0]);
}/*ps8ChLibelleEvt*/

//============================================================================
// Fonction		: ps8GetChEtatAlarme
// Entrees		: <loc_u8_etat_alarme> : état de l'alarme
//				  <loc_u8_index_langue> : index de la langue à afficher
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 26/10/2009 -
// Description	: renvoie la chaîne à afficher de l'état en cours de l'alarme
//============================================================================
s8sod* ps8GetChEtatAlarme(u8sod loc_u8_etat_alarme, u8sod loc_u8_index_langue)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
	{
		if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
		{
			strcpy(loc_ps8_chaine, pt_tb_msg[loc_u8_index_langue].ps8_msg_alarme_minuscule);
		}
		else
		{
			strcpy(loc_ps8_chaine, pt_tb_msg[loc_u8_index_langue].ps8_msg_pas_d_alarme);
		}
	}
	else
	{
		strcpy(loc_ps8_chaine, pt_tb_msg[loc_u8_index_langue].ps8_msg_non_utilise_m);
	}

	return (&loc_ps8_chaine[0]);
}/*ps8GetChEtatAlarme*/

//============================================================================
// Fonction		: ps8GetChDataRate
// Entrees		: <loc_u8_idxrate> : index du débit à afficher
//				: <loc_u8_index_langue> : index de la langue à afficher
//				: <loc_u8_mode80211> : mode 802.11
//				: <loc_u8_guard_interval> : type intervalle de garde
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 11/10/2010 -
// Description	: renvoie la chaîne à afficher du débit de données
//============================================================================
s8sod* ps8GetChDataRate(u8sod loc_u8_idxrate, u8sod loc_u8_index_langue, u8sod loc_u8_mode80211, u8sod loc_u8_guard_interval)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	switch(loc_u8_idxrate)
	{
		case DATA_RATE_AUTOMATIC:
			strcpy(loc_ps8_chaine, pt_tb_msg[loc_u8_index_langue].ps8_msg_automatique);
			break;
		case DATA_RATE_1_MBPS:
		case DATA_RATE_2_MBPS:
		case DATA_RATE_5_5_MBPS:
		case DATA_RATE_11_MBPS:
		case DATA_RATE_6_MBPS:
		case DATA_RATE_9_MBPS:
		case DATA_RATE_12_MBPS:
		case DATA_RATE_18_MBPS:
		case DATA_RATE_24_MBPS:
		case DATA_RATE_36_MBPS:
		case DATA_RATE_48_MBPS:
		case DATA_RATE_54_MBPS:
			sprintf(loc_ps8_chaine, "%.1f Mbps",
					(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_basic / 1000.0);
			break;
		case DATA_RATE_MCS0:
		case DATA_RATE_MCS1:
		case DATA_RATE_MCS2:
		case DATA_RATE_MCS3:
		case DATA_RATE_MCS4:
		case DATA_RATE_MCS5:
		case DATA_RATE_MCS6:
		case DATA_RATE_MCS7:
		case DATA_RATE_MCS8:
		case DATA_RATE_MCS9:
		case DATA_RATE_MCS10:
		case DATA_RATE_MCS11:
		case DATA_RATE_MCS12:
		case DATA_RATE_MCS13:
		case DATA_RATE_MCS14:
		case DATA_RATE_MCS15:
		case DATA_RATE_MCS16:
		case DATA_RATE_MCS17:
		case DATA_RATE_MCS18:
		case DATA_RATE_MCS19:
		case DATA_RATE_MCS20:
		case DATA_RATE_MCS21:
		case DATA_RATE_MCS22:
		case DATA_RATE_MCS23:
			switch(loc_u8_mode80211)
			{
				case MODE_WIFI_802_11NAHT20:
				case MODE_WIFI_802_11NGHT20:
					if(GUARD_INTERVAL_LONG == loc_u8_guard_interval)
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT20_longGI / 1000.0);
					}
					else //GUARD_INTERVAL_SHORT
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT20_shortGI / 1000.0);
					}
					break;
				case MODE_WIFI_802_11NGHT40PLUS:
				case MODE_WIFI_802_11NGHT40MINUS:
				case MODE_WIFI_802_11NGHT40:
				case MODE_WIFI_802_11NAHT40PLUS:
				case MODE_WIFI_802_11NAHT40MINUS:
				case MODE_WIFI_802_11NAHT40:
					if(GUARD_INTERVAL_LONG == loc_u8_guard_interval)
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
								(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT40_longGI / 1000.0);
					}
					else //GUARD_INTERVAL_SHORT
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
								(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT40_shortGI / 1000.0);
					}
					break;
				default:
					break;
			}
			break;
		case DATA_RATE_NSS1_MCS0:
		case DATA_RATE_NSS1_MCS1:
		case DATA_RATE_NSS1_MCS2:
		case DATA_RATE_NSS1_MCS3:
		case DATA_RATE_NSS1_MCS4:
		case DATA_RATE_NSS1_MCS5:
		case DATA_RATE_NSS1_MCS6:
		case DATA_RATE_NSS1_MCS7:
		case DATA_RATE_NSS1_MCS8:
		case DATA_RATE_NSS1_MCS9:
		case DATA_RATE_NSS2_MCS0:
		case DATA_RATE_NSS2_MCS1:
		case DATA_RATE_NSS2_MCS2:
		case DATA_RATE_NSS2_MCS3:
		case DATA_RATE_NSS2_MCS4:
		case DATA_RATE_NSS2_MCS5:
		case DATA_RATE_NSS2_MCS6:
		case DATA_RATE_NSS2_MCS7:
		case DATA_RATE_NSS2_MCS8:
		case DATA_RATE_NSS2_MCS9:
		case DATA_RATE_NSS3_MCS0:
		case DATA_RATE_NSS3_MCS1:
		case DATA_RATE_NSS3_MCS2:
		case DATA_RATE_NSS3_MCS3:
		case DATA_RATE_NSS3_MCS4:
		case DATA_RATE_NSS3_MCS5:
		case DATA_RATE_NSS3_MCS6:
		case DATA_RATE_NSS3_MCS7:
		case DATA_RATE_NSS3_MCS8:
		case DATA_RATE_NSS3_MCS9:
			switch(loc_u8_mode80211)
			{
				case MODE_WIFI_802_11ACHT20:
					if(GUARD_INTERVAL_LONG == loc_u8_guard_interval)
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT20_longGI / 1000.0);
					}
					else //GUARD_INTERVAL_SHORT
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT20_shortGI / 1000.0);
					}
					break;
				case MODE_WIFI_802_11ACHT40:
					if(GUARD_INTERVAL_LONG == loc_u8_guard_interval)
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT40_longGI / 1000.0);
					}
					else //GUARD_INTERVAL_SHORT
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT40_shortGI / 1000.0);
					}
					break;
				case MODE_WIFI_802_11ACHT80: 
					if(GUARD_INTERVAL_LONG == loc_u8_guard_interval)
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT80_longGI / 1000.0);
					}
					else //GUARD_INTERVAL_SHORT
					{
						sprintf(loc_ps8_chaine, "%.1f Mbps",
							(f32sod)T_TB_VAL.pt_definition_rate[loc_u8_idxrate].u32_rateKbps_HT80_shortGI / 1000.0);
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	


	return (&loc_ps8_chaine[0]);
}/*ps8GetChDataRate*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Custom_Langue
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Initialisation du module custom_Langue
//=====================================================================================
void InitModule_Custom_Langue(void)
{
	strcpy(ps8_chaine_col_general,""); //INIT
	
	strcpy(ps8_chaine_col0, "");	//INIT
	strcpy(ps8_chaine_col1, "");	//INIT
	strcpy(ps8_chaine_col2, "");	//INIT
	strcpy(ps8_chaine_col3, "");	//INIT
	
}/*InitModule_Custom_Langue*/

