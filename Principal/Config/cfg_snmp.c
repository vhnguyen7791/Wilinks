/*========================================================================*/
/* NOM DU FICHIER  : cfg_snmp.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/11/2009                                           */
/* Libelle         : Principal: Configuration du serveur SNMP			  */
/* Projet          : WRM100                                               */
/* Indice          : BE054                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 12/11/09 CM
// - CREATION
//BE008 28/01/2010 CM
// - Modification chemin des fichiers de configuration
//BE012 24/02/2010 CM
// - Correction chemin du fichier snmpd.conf
// - Integration SNMPv1/SNMPv2c
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE019 16/03/2010 CM
// - Ajout gestion sysservice de la MIB-II
//BE034 28/06/2010 CM
// - Correction pour SNMP du type d'interfaces (ifType dans la table ifTable)
//	de plus il faut gérer le cas où l'interface VLAN est configuré
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE040 13/09/2010 CM
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Ajout gestion debit MCS pour 802.11n
//BE052 15/12/2010 CM
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE054 11/01/2011 CM
// - Modification info snmp debit max de l'interface wifi
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_SNMP

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

//Fichier pour récupérer valeur du PID du processus "snmpd"
#define FICHIER_VAR_SNMPD_PID PATH_DIR_VAR "run/snmpd.pid"

//Définition du fichier de configuration snmpd.conf
#define FICHIER_CONFIG_SNMPD PATH_DIR_ETC "snmp/snmpd.conf"

//Sysservice est calculé avec la somme de 2^(layer-1)
// layer      functionality
//	1        physical (e.g., repeaters)
//	2        datalink/subnetwork (e.g., bridges)
//	3        internet (e.g., supports the IP)
//	4        end-to-end  (e.g., supports the TCP)
//	7        applications (e.g., supports the SMTP)
#define VALEUR_MIBII_SYSSERVICE	78


/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Snmp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Installe snmp
//=====================================================================================
void Install_Snmp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Snmp\n");
	s32sod loc_s32_pid;

	//On récupère le PID du processus snmpd
	loc_s32_pid = s32GetPidProcessus("snmpd", FICHIER_VAR_SNMPD_PID);
	printf("loc_s32_pid (snmpd) = %ld \n",loc_s32_pid);

	//Création du fichier de configuration
	/*if(FALSE == u8CreationFichierCfgSnmpd(loc_ps_config, s_exploit_process_prncpl.s_general.u8_type_equipement, loc_ps_config->s_admin.u8_langue))
	{
		printf("Install_Snmp: u8CreationFichierCfgSnmpd KO \n");
	}*///Modif by VuHai

	//Reconfiguration (si déjà executé), sinon on démarre snmpd
	if(loc_s32_pid > 0)
	{
		kill(loc_s32_pid, SIGHUP);//envoi signal vers processus snmpd pour reconfig
	}
	else
	{
		//Snmpd n'est pas démarré
		printf("Install_Snmp: snmpd -C -c %s\n",FICHIER_CONFIG_SNMPD);
		CmdSystem_Generique("snmpd -C -c %s &",FICHIER_CONFIG_SNMPD);
	}

}/*Install_Snmp*/

//=====================================================================================
// Fonction		: u8CreationFichierCfgSnmpd
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u8_type_equipement> : type de l'équipement
//				  <loc_u8_langue> : langue
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 12/11/2009 -
// Description	: Edition du fichier snmpd.conf pour le processus snmpd
//=====================================================================================
u8sod u8CreationFichierCfgSnmpd(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_type_equipement, u8sod loc_u8_langue)
{
	FILE *	loc_pf_snmpconf;
	u16sod	loc_u16_i;
	u16sod	loc_u16_retries;
	u8sod	loc_u8_resultat;
	u32sod	loc_u32_wifi_debit_max;

	loc_u8_resultat = TRUE;	//INIT
	loc_u16_retries = 0;	//INIT
	loc_u32_wifi_debit_max = 0;	//INIT

	if(NULL == (loc_pf_snmpconf = fopen(FICHIER_CONFIG_SNMPD, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgSnmpd: Erreur creation fichier %s\n",FICHIER_CONFIG_SNMPD));
		loc_u8_resultat = FALSE;
	}
	else
	{
		//System Group
		fprintf(loc_pf_snmpconf,"sysdescr %s\n",pt_tb_msg[loc_u8_langue].ps8_msg_radio_modem);
		fprintf(loc_pf_snmpconf,"syslocation Unknown\n");
		fprintf(loc_pf_snmpconf,"syscontact %s\n",NOM_DU_CONSTRUCTEUR);
		fprintf(loc_pf_snmpconf,"sysname %s\n",S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[loc_u8_langue]);
		fprintf(loc_pf_snmpconf,"sysservices %d\n",VALEUR_MIBII_SYSSERVICE);

		//Interfaces Group
		//can be used to provide appropriate type and speed settings for interfaces
		//where the agent fails to determine this information correctly.
		//TYPE is a type value as given in the IANAifType-MIB, and can be specified numerically or by name (assuming this MIB is loaded). 
		//->					 interface NAME TYPE SPEED
		switch(loc_ps_config->s_wifi.u8_mode_802_11x)
		{
			case MODE_WIFI_802_11B:
				if(DATA_RATE_AUTOMATIC == loc_ps_config->s_wifi.u8_data_rate)
				{
					loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_11_MBPS].u32_rateKbps_basic*1000;
				}
				else
				{
					loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_basic*1000;
				}
				break;
			case MODE_WIFI_802_11A:
			case MODE_WIFI_802_11G:
				if(DATA_RATE_AUTOMATIC == loc_ps_config->s_wifi.u8_data_rate)
				{
					loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_54_MBPS].u32_rateKbps_basic*1000;
				}
				else
				{
					loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_basic*1000;
				}
				break;
			case MODE_WIFI_802_11NGHT20:
			case MODE_WIFI_802_11NAHT20:
				if(DATA_RATE_AUTOMATIC == loc_ps_config->s_wifi.u8_data_rate)
				{
					if(UN_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
					{
						loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS7].u32_rateKbps_HT20*1000;
					}
					if(DEUX_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
					{
						loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS15].u32_rateKbps_HT20*1000;
					}
					if(TROIS_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
					{
						loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS23].u32_rateKbps_HT20*1000;
					}
				}
				else
				{
					loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_HT20*1000;
				}
				break;
			case MODE_WIFI_802_11NGHT40PLUS:
			case MODE_WIFI_802_11NGHT40MINUS:
			case MODE_WIFI_802_11NGHT40:
			case MODE_WIFI_802_11NAHT40PLUS:
			case MODE_WIFI_802_11NAHT40MINUS:
			case MODE_WIFI_802_11NAHT40:
				if(GUARD_INTERVAL_LONG == loc_ps_config->s_wifi.u8_11n_guard_interval)
				{
					if(DATA_RATE_AUTOMATIC == loc_ps_config->s_wifi.u8_data_rate)
					{
						if(UN_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
						{
							loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS7].u32_rateKbps_HT40_longGI*1000;
						}
						if(DEUX_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
						{
								loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS15].u32_rateKbps_HT40_longGI*1000;
						}
						if(TROIS_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
						{
							loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS23].u32_rateKbps_HT40_longGI*1000;
						}
					}
					else
					{
						loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_HT40_longGI*1000;
					}
				}
				else //GUARD_INTERVAL_SHORT
				{
					if(DATA_RATE_AUTOMATIC == loc_ps_config->s_wifi.u8_data_rate)
					{
						if(UN_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
						{
							loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS7].u32_rateKbps_HT40_shortGI*1000;
						}
						if(DEUX_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))
						{
							loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS15].u32_rateKbps_HT40_shortGI*1000;
						}
						if(TROIS_STREAM == u8GetNbStream(loc_ps_config->s_wifi.u8_ant_N_selection))  
						{
							loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[DATA_RATE_MCS23].u32_rateKbps_HT40_shortGI*1000;
						}
					}
					else
					{
						loc_u32_wifi_debit_max = (u32sod)T_TB_VAL.pt_definition_rate[loc_ps_config->s_wifi.u8_data_rate].u32_rateKbps_HT40_shortGI*1000;
					}
				}
				break;
			default:
				break;
		}
		fprintf(loc_pf_snmpconf,"interface %s %d %d\n",NOM_INTERFACE_ETHERNET, IANAIFTYPE_FASTETHER, DEBIT_MAX_INTERFACE_ETHERNET);
		fprintf(loc_pf_snmpconf,"interface %s %d %lu\n",NOM_INTERFACE_WIFI, IANAIFTYPE_IEEE80211, loc_u32_wifi_debit_max); 
		fprintf(loc_pf_snmpconf,"interface %s %d %d\n",NOM_INTERFACE_BRIDGE, IANAIFTYPE_BRIDGE, DEBIT_MAX_INTERFACE_ETHERNET);

		if(TRUE == loc_ps_config->s_gene.u8_vlan_autoriser) //CONDITION: VLAN autorisé
		{
			if(MODE_NETWORK_BRIDGE == loc_ps_config->s_gene.u8_mode_network)
			{
				fprintf(loc_pf_snmpconf,"interface %s.%d %d %d\n",NOM_INTERFACE_ETHERNET, loc_ps_config->s_gene.u16_vlan_id, IANAIFTYPE_FASTETHER, DEBIT_MAX_INTERFACE_ETHERNET);
			}
		}
		
		
		// On doit mettre les champs nom de communautes
		//com2sec <name> <source> <community>
		//		Avec <source> : default
		fprintf(loc_pf_snmpconf,"com2sec secprive    default	   %s \n",
				loc_ps_config->s_snmp.ps8_nom_communaute_set);
		fprintf(loc_pf_snmpconf,"com2sec secpublic   default	   %s \n",
				loc_ps_config->s_snmp.ps8_nom_communaute_get);

		//Définition des groupes
		//   group <name> <model> <security>
		//	Avec <model>: v1 ou v2 
		if((VERSION_SNMPV1 == loc_ps_config->s_snmp.u8_version_snmp)||
		   (VERSION_SNMPV2C == loc_ps_config->s_snmp.u8_version_snmp)
		  )
		{
			fprintf(loc_pf_snmpconf,"group   RWGroup1     v1             secprive \n");
			fprintf(loc_pf_snmpconf,"group   ROGroup1     v1             secpublic \n");
		}
		if(VERSION_SNMPV2C == loc_ps_config->s_snmp.u8_version_snmp)
		{
			fprintf(loc_pf_snmpconf,"group   RWGroup2     v2c             secprive \n");
			fprintf(loc_pf_snmpconf,"group   ROGroup2     v2c             secpublic \n");
		}

		//Définition de la vue
		//   view <name> <type> <subtree>
		//	Avec : <type>: included ou excluded.
		fprintf(loc_pf_snmpconf,"view    tout        included      .1 \n");

		//Définition des modèles de sécurité
		//access <name> <context> <model> <level> <prefix> READ WRITE NOTIFY
		//		Avec 	<model>: v1 ou v2c ou usm
		//		<level>: noauth, auth ou priv
		//		<prefix>: exact ou prefix
		//		<READ WRITE NOTIFY>: définie la view
		//	Pour SNMPv1 et SNMPv2c, <level>=noauth et <context>=""
		if((VERSION_SNMPV1 == loc_ps_config->s_snmp.u8_version_snmp)||
		   (VERSION_SNMPV2C == loc_ps_config->s_snmp.u8_version_snmp)
		  )
		{
			fprintf(loc_pf_snmpconf,"access  ROGroup1     \"\"       v1          noauth      exact   tout    none     none \n");
			fprintf(loc_pf_snmpconf,"access  RWGroup1     \"\"       v1          noauth      exact   tout    tout     tout \n");
		}
		if(VERSION_SNMPV2C == loc_ps_config->s_snmp.u8_version_snmp)
		{
			fprintf(loc_pf_snmpconf,"access  ROGroup2     \"\"       v2c          noauth      exact   tout    none     none \n");
			fprintf(loc_pf_snmpconf,"access  RWGroup2     \"\"       v2c          noauth      exact   tout    tout     tout \n");
		}

		//Définition de la communauté de TRAP
		if((VERSION_SNMPV1 == loc_ps_config->s_snmp.u8_version_snmp)||
		   (VERSION_SNMPV2C == loc_ps_config->s_snmp.u8_version_snmp)
		  )
		{
			//trapcommunity <string>
			fprintf(loc_pf_snmpconf,"trapcommunity %s\n",
					loc_ps_config->s_snmp.ps8_nom_communaute_trap);
		}
		

	   // On doit mettre les adresses des managers en NVRAM
		for (loc_u16_i=0;loc_u16_i<NB_MANAGER_SNMP_MAX;loc_u16_i++)
		{
			if (MANAGER_SNMP_PRESENT == loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_presence)
			{
				switch(loc_ps_config->s_snmp.u8_version_snmp)
				{
					case VERSION_SNMPV1:
						fprintf(loc_pf_snmpconf,"trapsink %s\n",
								ps8GetStringIp(loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u32_adresse_ip));
						break;
					case VERSION_SNMPV2C:
						switch(loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_type_notification)
						{
							case TYPE_NOTIFICATION_TRAP:
								fprintf(loc_pf_snmpconf,"trap2sink %s\n",
										ps8GetStringIp(loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u32_adresse_ip));
								break;
							case TYPE_NOTIFICATION_INFORM:
								//trapsess -v 2c -c <community> -Ci -r <retries> -t <timeout> <host>:162
								//-v <versionSNMP>: version SNMP => 2c
								//-Ci: pour inform
								//-c :
								if(loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_nb_emission >= 1)
								{
									loc_u16_retries = (loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_nb_emission-1);
								}
								else
								{
									loc_u16_retries = 0;
								}
								fprintf(loc_pf_snmpconf,"trapsess -v 2c -c %s -Ci -r %d -t %d %s:%d\n",
										loc_ps_config->s_snmp.ps8_nom_communaute_trap,
										loc_u16_retries,
										loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_interval,
										ps8GetStringIp(loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u32_adresse_ip),
									    PORT_UDP__SNMP_NOTIFICATION);
								break;
							default:
								break;
						}
						break;
					default:
						break;
				}
			}
		}
		
		//fermeture du fichier
		fclose(loc_pf_snmpconf);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_SNMPD, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgSnmpd*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Snmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Initialisation du module de cfg_snmp
//=====================================================================================
void InitModule_Cfg_Snmp(void)
{
	
}/*InitModule_Cfg_Snmp*/

