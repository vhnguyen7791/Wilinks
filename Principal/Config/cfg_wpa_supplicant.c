/*========================================================================*/
/* NOM DU FICHIER  : cfg_wpa_supplicant.c 		                          */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/11/2009                                           */
/* Libelle         : Principal: Configuration du WPA_SUPPLICANT			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/11/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Modification chemin des fichiers de configuration
//		/tmp/wpa_supplicant.conf => /etc/wpa_supplicant.conf
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE021 24/03/2010 CM
// - Correction BUG liaison bridge-bridge
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
// - Correction désinstallation wpa_supplicant (à sécuriser)
//	car le processus wpa_supplicant se tue lentement
//BE029 10/05/2010 CM
// - Ajout des modes sécurités Wifi de type WPA2
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE033 25/06/2010 CM
// - Correction configuration  wpa_supplicant en WPAxxxx - PSK (ap_scan=1)
//	=> il faut laisser ap_scan=1
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE048 29/11/2010 CM
// - Correction re-configuration wpa_supplicant
//	il faut acquitter cette re-config (pas de défaut constaté, mais il faut le faire)
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
//BE050 09/12/2010 CM
// - Ajout valeur PEAP/MSCHAPv2 dans authentification EAP (Radius)
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout fonction qui liste les fichiers dans répertoire
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_WPA_SUPPLICANT

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

#define WPASUPPLICANT_MODE_DEBUG	0	//0: debug désactivé 1:activé
#define FICHIER_CONFIG_WPA_SUPPLICANT PATH_DIR_ETC	 "wpa_supplicant.conf"

//Compteur essai
#define CPT_MAX_FIN_WPA_SUPPLICANT	5

//Gestion des certificats
#define TIMEOUT__AVEC_CERTIFICATS_DANS_VAR	15 //secondes
#define SIZE_MAX_CERTIFICAT		(20*1024)	//octets

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static u16sod u16_timeout_avec_certificats_dans_var;
static u8sod u8_memo_nb_certificats_dans_var;
static u32sod u32_memo_total_size_certificats_dans_var;

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_EditFprintfZoneNetwork
// Entrees		: <loc_pf_file< : pointeur sur fichier
//				: <loc_ps_config< : config de l'équipement
//				: <loc_ps8_ssid< : ssid spécifique au network
// Sortie		: rien
// Auteur		: CM - 08/12/2010 -
// Description	: Edition de la zone network dans fichier de configuration
//=====================================================================================
void proc_EditFprintfZoneNetwork(FILE *loc_pf_file, S_STRUCT_CONFIGURATION *loc_ps_config, s8sod *loc_ps8_ssid);

//=====================================================================================
// Fonction		: ExecReconfiguration_WpaSupplicant
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 26/03/2010 -
// Description	: Reconfigurer le processus wpa_supplicant (si présent)
//=====================================================================================
void ExecReconfiguration_WpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	if(TRUE == u8TestOrdreReconfiguration(ORDRE_RECONFIG__WPA_SUPPLICANT))
	{
		printf("ExecReconfiguration_WpaSupplicant\n");
		//On stoppe le processus et on le relance
		Uninstall_WpaSupplicant(loc_ps_config);
		Install_WpaSupplicant(loc_ps_config);
	}
}/*ExecReconfiguration_WpaSupplicant*/

//=====================================================================================
// Fonction		: Install_WpaSupplicant
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Installe wpa_supplicant
//=====================================================================================
void Install_WpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_options_wpa_supplicant[100+1];
	
	printf("Install_WpaSupplicant\n");

	strcpy(loc_ps8_options_wpa_supplicant, ""); ///INIT

	//Création du fichier de configuration
	if(FALSE == u8CreationFichierCfgWpaSupplicant(loc_ps_config))
	{
		printf("Install_WpaSupplicant: u8CreationFichierCfgWpaSupplicant KO \n");
	}

	//wpa_supplicant n'est pas démarré
	if(TRUE == s_debug_global_process_prncpl.u8_dbg_wpa_supplicant) //CONDITION: debug activé
	{
		strcat(loc_ps8_options_wpa_supplicant, "-ddt -T  "); 
	}

	if(MODE_NETWORK_BRIDGE == loc_ps_config->s_gene.u8_mode_network)
	{
		strcat(loc_ps8_options_wpa_supplicant, "-b"); 
		strcat(loc_ps8_options_wpa_supplicant, NOM_INTERFACE_BRIDGE); 
		strcat(loc_ps8_options_wpa_supplicant, " "); 
	}

	//on lance en deamon
#ifdef _WRM100_ABG_SELECT
	CmdSystem_Generique("wpa_supplicant -Dwext -i%s %s -c %s &",
						NOM_INTERFACE_WIFI,
						loc_ps8_options_wpa_supplicant,
						FICHIER_CONFIG_WPA_SUPPLICANT);
#endif
#ifdef _WRM100_N_SELECT
	//Modif by VuHai, change Driver from madwifi to nl80211
	CmdSystem_Generique("wpa_supplicant -Dnl80211 -i%s %s -c %s &",
						NOM_INTERFACE_WIFI,
						loc_ps8_options_wpa_supplicant,
						FICHIER_CONFIG_WPA_SUPPLICANT);
#endif

	//Add by VuHai
	//Data rate
	printf("************ VuHai:  Start  SET bitrates  ************\n");
	sleep(1);

	u16sod  u16_ieee;
	u16sod  loc_u16_index;
	switch(loc_ps_config->s_wifi.u8_data_rate)
	{
		case DATA_RATE_AUTOMATIC:

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
			printf("iwconfig %s rate %dk\n",
			       NOM_INTERFACE_WIFI,
			       T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_basic);
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
				//iwpriv ath0 set11NRates $6
				//iwpriv ath0 set11NRetries 0x01
			/*printf("iwpriv %s set11NRates 0x%02X\n",
					    NOM_INTERFACE_WIFI,
					    T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);*/
			//printf(" set11NRates %d\n",T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
			if(TRUE == u8IsMode80211ng(loc_ps_config->s_wifi.u8_mode_802_11x))
			{
				if(GUARD_INTERVAL_SHORT == loc_ps_config->s_wifi.u8_11n_guard_interval)
					CmdSystem_Generique("iw %s set bitrates legacy-2.4 ht-mcs-2.4 %d sgi-2.4",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
				else	CmdSystem_Generique("iw %s set bitrates legacy-2.4 ht-mcs-2.4 %d",
					NOM_INTERFACE_WIFI,
					T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
			}
			if(TRUE == u8IsMode80211na(loc_ps_config->s_wifi.u8_mode_802_11x))
			{
				if(GUARD_INTERVAL_SHORT == loc_ps_config->s_wifi.u8_11n_guard_interval)
					CmdSystem_Generique("iw %s set bitrates legacy-5 ht-mcs-5 %d sgi-5",
						NOM_INTERFACE_WIFI,
						T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
				else	CmdSystem_Generique("iw %s set bitrates legacy-5 ht-mcs-5 %d",
					NOM_INTERFACE_WIFI,
					T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u8_codeRate);
			}	
			break;
		default:
			//printf("iwconfig %s rate auto",NOM_INTERFACE_WIFI);

			break;
	}
	printf("************ VuHai:  Fin SET bitrates  ************\n");

	//On reset le flag de reconfiguration (comme c'est fait!)
	ClearOrdreReconfiguration(ORDRE_RECONFIG__WPA_SUPPLICANT);
	
}/*Install_WpaSupplicant*/

//=====================================================================================
// Fonction		: Uninstall_WpaSupplicant
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Désinstalle wpa_supplicant
//=====================================================================================
void Uninstall_WpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod loc_u16_cpt;
	s32sod loc_s32_pid;

	loc_u16_cpt = 0;	//INIT
	loc_s32_pid = (-1);	//INIT
	
	printf("Uninstall_WpaSupplicant\n");

	//on tue le processus
	CmdSystem_Generique("killall wpa_supplicant");

	//Comme le processus met du temps avant de se tuer
	//On vérifie si processus wpa_supplicant est présent, alors on patiente
	do{
		loc_s32_pid = s32GetPidProcessus("wpa_supplicant", FICHIER_VAR_WPA_SUPPLICANT_PID);
		if(loc_s32_pid > 0) //CONDITION: processus déjà présent
		{
			//on fait une pause
			sleep(1);
		}
		loc_u16_cpt ++;
	}while((loc_u16_cpt < CPT_MAX_FIN_WPA_SUPPLICANT)&&
		   (loc_s32_pid > 0));
	
	if(loc_s32_pid > 0) //CONDITION: processus déjà présent
	{
		printf("FIN *** Uninstall_WpaSupplicant KO *** \n");
		//on force
		CmdSystem_Generique("kill -9 %ld",loc_s32_pid);
	}
	else
	{
		printf("FIN *** Uninstall_WpaSupplicant OK (cpt=%d) *** \n",loc_u16_cpt);
	}

}/*Uninstall_WpaSupplicant*/

//=====================================================================================
// Fonction		: u8CreationFichierCfgWpaSupplicant
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 24/11/2009 -
// Description	: Edition du fichier wpa_supplicant.conf pour le processus wpa_supplicant
//=====================================================================================
u8sod u8CreationFichierCfgWpaSupplicant(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	FILE *	loc_pf_file;
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(NULL == (loc_pf_file = fopen(FICHIER_CONFIG_WPA_SUPPLICANT, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgWpaSupplicant: Erreur creation fichier %s\n",FICHIER_CONFIG_WPA_SUPPLICANT));
		loc_u8_resultat = FALSE;
	}
	else
	{
		//fprintf(loc_pf_file,"ctrl_interface=/var/run/wpa_supplicant\n");

		//IEEE 802.1X/EAPOL version
		fprintf(loc_pf_file,"eapol_version=1\n");
		
		//AP scanning/selection
		if(WPA_AUTHENTIFICATION_PSK == loc_ps_config->s_wifi.s_wpa_security.u8_authentification)
		{
			fprintf(loc_pf_file,"ap_scan=1\n");
		}
		else //WPA_AUTHENTIFICATION_EAP
		{
			//pas de ap_scan=1 (pour WPA-EAP)
		}
		
		//EAP fast re-authentication

		//Remarque: pour EAP-TTLS/XXX (avec FreeRadius)
		//Avec "fast_reauth=1", on a l'erreur suivante sur le serveur RADIUS:
		//[ttls] eaptls_process returned 3 
		//[ttls] Skipping Phase2 due to session resumption
		//[ttls] FAIL: Forcibly stopping session resumption as it is not allowed.
		//Failed to authenticate the user.
		//Par contre, avec fast_reauth=0 pas de défaut
		fprintf(loc_pf_file,"fast_reauth=0\n");
		
		
		//Network SSID primary
		proc_EditFprintfZoneNetwork(loc_pf_file, loc_ps_config, loc_ps_config->s_wifi.ps8_ssid_primary);

#ifdef _WRM100_N_SELECT
		//Network SSID secondary
		if(TRUE == loc_ps_config->s_wifi.u8_dual_ssid) //CONDITION: second SSID activé
		{
			proc_EditFprintfZoneNetwork(loc_pf_file, loc_ps_config, loc_ps_config->s_wifi.ps8_ssid_secondary);
		}		
#endif
		
		//fermeture du fichier
		fclose(loc_pf_file);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_WPA_SUPPLICANT, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgWpaSupplicant*/

//=====================================================================================
// Fonction		: proc_EditFprintfZoneNetwork
// Entrees		: <loc_pf_file< : pointeur sur fichier
//				: <loc_ps_config< : config de l'équipement
//				: <loc_ps8_ssid< : ssid spécifique au network
// Sortie		: rien
// Auteur		: CM - 08/12/2010 -
// Description	: Edition de la zone network dans fichier de configuration
//=====================================================================================
void proc_EditFprintfZoneNetwork(FILE *loc_pf_file, S_STRUCT_CONFIGURATION *loc_ps_config, s8sod *loc_ps8_ssid)
{
	fprintf(loc_pf_file,"network={\n");
	fprintf(loc_pf_file,"	ssid=\"%s\"\n",loc_ps8_ssid);

	//Add by VuHai
	//Set up the channel
	u16sod	loc_u16_frequence;
	u16sod	loc_u16_index;
	u16sod	loc_u16_min_index;
	u16sod	loc_u16_max_index;
	u8sod	loc_u8_i;
	u8sod	loc_u8_trouve;
	s8sod	loc_ps8_chainlist[300+1];
	s8sod	loc_ps8_tempo[100+1];
	
	loc_u16_frequence = 0; //INIT
	loc_u16_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u16_min_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u16_max_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_u8_trouve = FALSE;	//INIT
	strcpy(loc_ps8_chainlist, "");	//INIT
	strcpy(loc_ps8_tempo, "");	//INIT
	


	switch(loc_ps_config->s_wifi.u8_type_selection_canal)
	{
		case TYPE_SELECTION_CANAL_ISO:
			loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.u16_iso_canal_radio, loc_ps_config->s_wifi.u8_mode_802_11x);
			//printf("WPA SUP: u16_index = %d \n", loc_u16_index);
			if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
			{
				loc_u16_frequence = s_list_freq_process_prncpl.s_channel[loc_u16_index].u16_freq_MHz;
				//printf("WPA SUP: u16_freq_MHz = %d \n", loc_u16_frequence);
				//fprintf(loc_pf_file,"	frequency=%d\n",loc_u16_frequence);
				fprintf(loc_pf_file,"	scan_freq=%d\n",loc_u16_frequence);
				
			}
			else printf("u8CreationFichierCfgWpaSupplicant: Index for channel is UNKNOWN\n");
			break;
		case TYPE_SELECTION_CANAL_MULTI:
			loc_u8_trouve = FALSE;	//RAZ
			strcpy(loc_ps8_tempo, "");	//RAZ
			for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
			{
				if(CHANNEL_RADIO_DISABLED != loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i])
				{
					loc_u16_index = u16GetIdx_ForChannelAndMode(&s_list_freq_process_prncpl, loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i], loc_ps_config->s_wifi.u8_mode_802_11x);
					if(IDX_CHANNEL_UNKNOWN != loc_u16_index)
					{
						loc_u16_frequence = u16IeeeToMhz(loc_ps_config->s_wifi.pu16_multi_canal_radio[loc_u8_i]);
						sprintf(loc_ps8_tempo,"%d ",loc_u16_frequence);
						strcat(loc_ps8_chainlist, loc_ps8_tempo);
						loc_u8_trouve = TRUE;
					}
				}
			}
			if(FALSE == loc_u8_trouve) //CONDITION: aucun canal configuré, on passe en mode automatique
			{
				//on passe en mode auto
				printf("****** Mode Multi-freq but no channel is selected ********\n");
			}
			else
			{
				printf("******* List Channel Selected:  %s\n",loc_ps8_chainlist);
				fprintf(loc_pf_file,"	scan_freq=%s\n",loc_ps8_chainlist);
			}
			break;
		case TYPE_SELECTION_CANAL_AUTO:
			
			break;
		default:
			break;
	}
	fprintf(loc_pf_file,"	key_mgmt=NONE\n");
	//fprintf(loc_pf_file,"ht_mcs=\"0x00 01 00 00 00 00 00 00 00 00 \"\n");
	
	//Fin add by VuHai


	/*switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_AUCUN:
	if(WPA_AUTHENTIFICATION_PSK == loc_ps_config->s_wifi.s_wpa_security.u8_authentification)
	{
		switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
		{
			case MODE_SECURITE_WIFI_WPA:
			case MODE_SECURITE_WIFI_WPA_TKIP:
			case MODE_SECURITE_WIFI_WPA_AES:
				fprintf(loc_pf_file,"	proto=WPA\n");
				break;
			case MODE_SECURITE_WIFI_WPA2:
			case MODE_SECURITE_WIFI_WPA2_TKIP:
			case MODE_SECURITE_WIFI_WPA2_AES:
				fprintf(loc_pf_file,"	proto=RSN\n");
				break;
			default:
				break;
		}
		fprintf(loc_pf_file,"	key_mgmt=WPA-PSK\n");
	}
	else //WPA_AUTHENTIFICATION_EAP
	{
		fprintf(loc_pf_file,"	key_mgmt=WPA-EAP\n");

		//identity: Identity string for EAP
		fprintf(loc_pf_file,"	identity=\"%s\"\n",
				loc_ps_config->s_wifi.s_wpa_security.ps8_identity);

//		//anonymous_identity: Anonymous identity string for EAP
//		fprintf(loc_pf_file,"	anonymous_identity=\"%s\"\n",
//				loc_ps_config->s_wifi.s_wpa_security.ps8_user_name);

		//password: Password string for EAP
		if(EAP_METHOD__TLS != loc_ps_config->s_wifi.s_wpa_security.u8_eap_method)
		{
			fprintf(loc_pf_file,"	password=\"%s\"\n",
					loc_ps_config->s_wifi.s_wpa_security.ps8_user_password);
		}
		
		switch(loc_ps_config->s_wifi.s_wpa_security.u8_eap_method)
		{
			case EAP_METHOD__TTLS_PAP:
				fprintf(loc_pf_file,"	eap=TTLS\n");
				fprintf(loc_pf_file,"	phase2=\"auth=PAP\"\n");
				break;
			case EAP_METHOD__TTLS_CHAP:
				fprintf(loc_pf_file,"	eap=TTLS\n");
				fprintf(loc_pf_file,"	phase2=\"auth=CHAP\"\n");
				break;
			case EAP_METHOD__TTLS_EAP_MD5:
				fprintf(loc_pf_file,"	eap=TTLS\n");
				fprintf(loc_pf_file,"	phase2=\"auth=MD5\"\n");
				break;
			case EAP_METHOD__PEAP_MSCHAPV2:
				fprintf(loc_pf_file,"	eap=PEAP\n");
				fprintf(loc_pf_file,"	phase2=\"auth=MSCHAPV2\"\n");
				break;
			case EAP_METHOD__TLS:
				fprintf(loc_pf_file,"	eap=TLS\n");
				fprintf(loc_pf_file,"	ca_cert=\"%s%s\"\n",PATH_DIR__ETC_CERTIFICATS,loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_authority);
				fprintf(loc_pf_file,"	client_cert=\"%s%s\"\n",PATH_DIR__ETC_CERTIFICATS,loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_client);
				fprintf(loc_pf_file,"	private_key=\"%s%s\"\n",PATH_DIR__ETC_CERTIFICATS,loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_client);
				fprintf(loc_pf_file,"	private_key_passwd=\"%s\"\n",loc_ps_config->s_wifi.s_wpa_security.ps8_private_key_password);
				break;
			default:
				break;
		}
		//scan with SSID-specific Probe Request frames
		fprintf(loc_pf_file,"	scan_ssid=1\n");
		//eapol_flags: IEEE 802.1X/EAPOL options (bit field)
		fprintf(loc_pf_file,"	eapol_flags=0\n");
	}*/

	switch(loc_ps_config->s_wifi.u8_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_WPA:
		case MODE_SECURITE_WIFI_WPA2:
			fprintf(loc_pf_file,"	pairwise=TKIP CCMP\n");
			//group: en TKIP et CCMP (tout le temps, car AP peut envoyer des requetes boardcast en TKIP uniquement)
			fprintf(loc_pf_file,"	group=TKIP CCMP\n");
			break;
		case MODE_SECURITE_WIFI_WPA_TKIP:
		case MODE_SECURITE_WIFI_WPA2_TKIP:
			fprintf(loc_pf_file,"	pairwise=TKIP\n");
			fprintf(loc_pf_file,"	group=TKIP\n"); //TKIP seul autorisé
			break;
		case MODE_SECURITE_WIFI_WPA_AES:
		case MODE_SECURITE_WIFI_WPA2_AES:
			fprintf(loc_pf_file,"	pairwise=CCMP\n");
			//group: en TKIP et CCMP (tout le temps, car AP peut envoyer des requetes boardcast en TKIP uniquement)
			fprintf(loc_pf_file,"	group=TKIP CCMP\n");
			break;
		default:
			break;
	}


	//fprintf(loc_pf_file,"	auth_alg=OPEN\n");Modif by VuHai

	/*if(WPA_AUTHENTIFICATION_PSK == loc_ps_config->s_wifi.s_wpa_security.u8_authentification)
	{
		switch(loc_ps_config->s_wifi.s_wpa_security.u8_wpa_key_type)
		{
			case KEY_TYPE_HEXA:
				fprintf(loc_pf_file,"	psk=%s\n",
						loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key);
				break;
			case KEY_TYPE_ASCII:
				fprintf(loc_pf_file,"	psk=\"%s\"\n",
						loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key);
				break;
			default:
				break;
		}
	}*/
	fprintf(loc_pf_file,"}\n");

}/*proc_EditFprintfZoneNetwork*/

//=====================================================================================
// Fonction		: CopyCertificats_FlashToEtc
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 23/03/2011 -
// Description	: copie tous les fichiers stockés dans la flash sous ETC
//=====================================================================================
void CopyCertificats_FlashToEtc(void)
{
	//On supprime tous les fichiers de /etc/certificats
	CmdSystem_Generique("rm -rf %s*",PATH_DIR__ETC_CERTIFICATS);
	//Copie tous les fichiers stockés dans la flash sous ETC
	CmdSystem_Generique("cp %s* %s",
						PATH_DIR__FLASH_CONFIG_CERTIFICATS,
						PATH_DIR__ETC_CERTIFICATS);
	
}/*CopyCertificats_FlashToEtc*/

//=====================================================================================
// Fonction		: GestionCertificats_InVar
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: rien
// Auteur		: CM - 23/03/2011 -
// Description	: gère les certificats postés par SFTP par l'utilisateur (STATION)
//=====================================================================================
void GestionCertificats_InVar(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_i;
	u8sod	loc_u8_k;
	u8sod	loc_u8_cpt;
	u8sod	loc_u8_cpt_certificat_dans_flash;
	u8sod	loc_u8_cpt_certificat_dans_var;
	u8sod	loc_u8_cpt_certificat_dans_tmp;
	u32sod	loc_u32_total_size_certificats_dans_var;
	u8sod	loc_u8_cpt_certificat_libre;
	S_STRUCT_SYST_FILE loc_ps_certificat_file_flash[NB_MAX_CERTIFICATS];
	S_STRUCT_SYST_FILE loc_ps_certificat_file_var[NB_MAX_CERTIFICATS];
	S_STRUCT_SYST_FILE loc_ps_certificat_file_tmp[NB_MAX_CERTIFICATS];
	u8sod	loc_u8_ordre_reconfig_wifi;

	loc_u8_cpt = 0;	//INIT
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
	{
		RazSystFile(&loc_ps_certificat_file_flash[loc_u8_i]); //INIT
		RazSystFile(&loc_ps_certificat_file_var[loc_u8_i]); //INIT
		RazSystFile(&loc_ps_certificat_file_tmp[loc_u8_i]); //INIT
	}
	loc_u8_cpt_certificat_dans_flash = 0;	//INIT
	loc_u8_cpt_certificat_dans_var = 0;	//INIT
	loc_u8_cpt_certificat_dans_tmp = 0; //INIT
	loc_u32_total_size_certificats_dans_var = 0;	//INIT
	loc_u8_cpt_certificat_libre = 0;	//INIT
	loc_u8_ordre_reconfig_wifi = FALSE;	//INIT
	

	//-----------------------------------------------------------
	//Lecture des certificats dans /var
	//-----------------------------------------------------------
	if(FALSE == u8CmdSystem_ListFileInDirectory(PATH_DIR__VAR_CERTIFICATS, loc_ps_certificat_file_var, NB_MAX_CERTIFICATS))
	{
		printf("GestionCertificats_InVar: Erreur lecture dans %s\n",PATH_DIR__VAR_CERTIFICATS);
	}
	//-----------------------------------------------------------
	//Nombre de certificats dèjà stockés dans /var
	//-----------------------------------------------------------
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
	{
		if(0!=strcmp(loc_ps_certificat_file_var[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
		{
			loc_u32_total_size_certificats_dans_var += loc_ps_certificat_file_var[loc_u8_i].u32_sizeoffile;
			loc_u8_cpt_certificat_dans_var++;
		}
	}

	if(loc_u8_cpt_certificat_dans_var > 0)//CONDITION: fichiers détectés dans var
	{
		if((u8_memo_nb_certificats_dans_var != loc_u8_cpt_certificat_dans_var)||
		   (u32_memo_total_size_certificats_dans_var != loc_u32_total_size_certificats_dans_var)
		  )//CONDITION: nb certificats ou total de la taille des certificats différents 
		{
			u8_memo_nb_certificats_dans_var = loc_u8_cpt_certificat_dans_var;
			u32_memo_total_size_certificats_dans_var = loc_u32_total_size_certificats_dans_var;
			u16_timeout_avec_certificats_dans_var = 0;	//RAZ
		}
		else
		{
			u16_timeout_avec_certificats_dans_var++;
		}

		if(u16_timeout_avec_certificats_dans_var > TIMEOUT__AVEC_CERTIFICATS_DANS_VAR) //CONDITION: nb certificats stables depuis un certain temps
		{
			//on réinitialise tous les paramètres de gestion
			u16_timeout_avec_certificats_dans_var = 0;	//RAZ
			u8_memo_nb_certificats_dans_var = 0;	//RAZ
			u32_memo_total_size_certificats_dans_var = 0;	//RAZ
			
			//-----------------------------------------------------------
			//Suppression des certificats non valides (fichier trop gros ou nom incorrecte)
			//-----------------------------------------------------------
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file_var[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					if((loc_ps_certificat_file_var[loc_u8_i].u32_sizeoffile > SIZE_MAX_CERTIFICAT)||
					   (strstr(loc_ps_certificat_file_var[loc_u8_i].ps8_nom, " ")!=NULL) //CONDITION : certificat trop grand ou espace trouvée (donc nom incorrecte)!!
					  )
					{
						//on le supprime
						printf("CERTIFICAT NON VALIDE suppression : \"%s\" (taille: %lu octets)\n",
							   loc_ps_certificat_file_var[loc_u8_i].ps8_nom,
							   loc_ps_certificat_file_var[loc_u8_i].u32_sizeoffile);
						CmdSystem_Generique("rm -rf \"%s%s\"\n", //avec de \"<path>\" pour pouvoir supprimer fichier
											PATH_DIR__VAR_CERTIFICATS,
											loc_ps_certificat_file_var[loc_u8_i].ps8_nom);
						strcpy(loc_ps_certificat_file_var[loc_u8_i].ps8_nom, "");	//RAZ
					}
				}
			}
			
			//-----------------------------------------------------------
			//on coupe/colle les certificats stockés de /var vers /tmp
			//-----------------------------------------------------------
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file_var[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					CmdSystem_Generique("mv %s%s %s\n",
										PATH_DIR__VAR_CERTIFICATS,loc_ps_certificat_file_var[loc_u8_i].ps8_nom,
										PATH_DIR__TMP_CERTIFICATS);
				}
			}
			//-----------------------------------------------------------
			//Lecture des certificats dans /tmp
			//-----------------------------------------------------------
			if(FALSE == u8CmdSystem_ListFileInDirectory(PATH_DIR__TMP_CERTIFICATS, loc_ps_certificat_file_tmp, NB_MAX_CERTIFICATS))
			{
				printf("GestionCertificats_InVar: Erreur lecture dans %s\n",PATH_DIR__TMP_CERTIFICATS);
			}
			//-----------------------------------------------------------
			//Nombre de certificats dèjà stockés dans /tmp
			//-----------------------------------------------------------
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					loc_u8_cpt_certificat_dans_tmp++;
				}
			}
		
			//-----------------------------------------------------------
			//Lecture des certificats dans /mnt/flash-config
			//-----------------------------------------------------------
			if(FALSE == u8CmdSystem_ListFileInDirectory(PATH_DIR__FLASH_CONFIG_CERTIFICATS, loc_ps_certificat_file_flash, NB_MAX_CERTIFICATS))
			{
				printf("GestionCertificats_InVar: Erreur lecture dans %s\n",PATH_DIR__FLASH_CONFIG_CERTIFICATS);
			}
			//-----------------------------------------------------------
			//Nombre de certificats dèjà stockés dans /mnt/flash-config
			//-----------------------------------------------------------
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0!=strcmp(loc_ps_certificat_file_flash[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					loc_u8_cpt_certificat_dans_flash++;
				}
			}
			printf("CERTIFICAT DETECTES (dans tmp %d / dans flash-config %d)\n",loc_u8_cpt_certificat_dans_tmp,loc_u8_cpt_certificat_dans_flash);
			
			//-----------------------------------------------------------
			//Est-ce que on remplace un certificat existant?
			//-----------------------------------------------------------
			for(loc_u8_i=0;loc_u8_i<NB_MAX_CERTIFICATS;loc_u8_i++)
			{
				if(0 != strcmp(loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
				{
					//recherche dans la FLASH,d'un certificat avec le meme nom
					for(loc_u8_k=0;loc_u8_k<NB_MAX_CERTIFICATS;loc_u8_k++)
					{
						if(0 == strcmp(loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom, loc_ps_certificat_file_flash[loc_u8_k].ps8_nom))//CONDITION: fichier présent
						{
							loc_u8_k = NB_MAX_CERTIFICATS+1; //on sort de la recherche
							
							printf("CERTIFICAT %s remplace\n",loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom);
							//on remplace
							CmdSystem_Generique("cp %s%s %s\n",
												PATH_DIR__TMP_CERTIFICATS,loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom,
												PATH_DIR__ETC_CERTIFICATS);
							//on remplace
							CmdSystem_Generique("cp %s%s %s\n",
												PATH_DIR__TMP_CERTIFICATS,loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom,
												PATH_DIR__FLASH_CONFIG_CERTIFICATS);

							//Si il s'agit d'un certificat utilisé dans la config
							if((0==strcmp(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_authority, loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom))||
							   (0==strcmp(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_client, loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom))
							  )
							{
								//on reconfigure le wifi 
								loc_u8_ordre_reconfig_wifi = TRUE;
							}
							RazSystFile(&loc_ps_certificat_file_tmp[loc_u8_i]); //on acquitte ce certificat
						}
					}
				}
			}
			
			if(loc_u8_cpt_certificat_dans_flash < NB_MAX_CERTIFICATS) //CONDITION: on peut sauver des certificats
			{
				//-----------------------------------------------------------
				//Combien reste-t-il de certificats dispo?
				//-----------------------------------------------------------
				loc_u8_cpt_certificat_libre = NB_MAX_CERTIFICATS - loc_u8_cpt_certificat_dans_flash;

				//-----------------------------------------------------------
				//On sauve le reste des certificats
				//-----------------------------------------------------------
				loc_u8_cpt = 0;	//RAZ
				for(loc_u8_i=0;((loc_u8_cpt<loc_u8_cpt_certificat_libre)&&(loc_u8_i<NB_MAX_CERTIFICATS));loc_u8_i++)
				{
					if(0 != strcmp(loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom, ""))//CONDITION: fichier présent
					{
						loc_u8_cpt++;
						printf("CERTIFICAT %s copie\n",loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom);
						printf("cp %s%s %s\n",
											PATH_DIR__TMP_CERTIFICATS,loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom,
											PATH_DIR__ETC_CERTIFICATS);
						//on copie
						CmdSystem_Generique("cp %s%s %s\n",
											PATH_DIR__TMP_CERTIFICATS,loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom,
											PATH_DIR__ETC_CERTIFICATS);
						//on copie
						CmdSystem_Generique("cp %s%s %s\n",
											PATH_DIR__TMP_CERTIFICATS,loc_ps_certificat_file_tmp[loc_u8_i].ps8_nom,
											PATH_DIR__FLASH_CONFIG_CERTIFICATS);
						RazSystFile(&loc_ps_certificat_file_tmp[loc_u8_i]); //on acquitte ce certificat
					}
				}
			}

			//On supprime tous les fichiers collés dans /tmp/CERTIFICATS
			CmdSystem_Generique("rm -rf %s*\n",PATH_DIR__TMP_CERTIFICATS);
		}
		//sinon on attend que les fichiers soient complètement postés
	}
	else
	{
		//sinon on fait rien
		u16_timeout_avec_certificats_dans_var = 0; //RAZ
		u8_memo_nb_certificats_dans_var = 0;	//RAZ
		u32_memo_total_size_certificats_dans_var = 0;	//RAZ
	}
	
	if(TRUE == loc_u8_ordre_reconfig_wifi)
	{
		if((MODE_RADIO_MODEM_STATION == loc_ps_config->s_gene.u8_mode_radio_modem)&&
		   (WPA_AUTHENTIFICATION_EAP == loc_ps_config->s_wifi.s_wpa_security.u8_authentification)&&
		   (EAP_METHOD__TLS == loc_ps_config->s_wifi.s_wpa_security.u8_eap_method)
		  )
		{
			//Il faut reconfigurer le wifi pour prendre en compte
			Ordre_ReconfigurationTotale();
		}
	}
	
}/*GestionCertificats_InVar*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Wpa_Supplicant
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/11/2009 -
// Description	: Initialisation du module de cfg_wpa_supplicant
//=====================================================================================
void InitModule_Cfg_Wpa_Supplicant(void)
{
	u16_timeout_avec_certificats_dans_var = 0; //INIT
	u8_memo_nb_certificats_dans_var = 0;	//INIT
	u32_memo_total_size_certificats_dans_var = 0;	//INIT
	
}/*InitModule_Cfg_Wpa_Supplicant*/

