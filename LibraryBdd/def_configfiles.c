/*========================================================================*/
/* NOM DU FICHIER  : def_configfiles.c	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/01/2010                                           */
/* Libelle         : Base de données: définition des fichiers de config	  */
/* Projet          : WRM100                                               */
/* Indice          : BE064                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE007 26/01/2010 CM
// - CREATION
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du système
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE013 26/02/2010 CM
// - Modification chemins des bdd (sous /tmp)
// - Intégration gestion des évènements
//BE019 16/03/2010 CM
// - Optimisation contenu du fichier newcfg.ini
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Suppression du fichier de configuration advwf
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout fonction impose config au démarrage (pour chaque bdd de config)
// - Ajout configuration date/heure au démarrage de l'équipement
//BE061 10/05/2011
// - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//		si par exemple on vient du logiciel WRM100-MESH
//BE063.0 06/10/2011
// - Ajout du type de fichier pour la configuration par sFTP : un seul fichier pour toute la config 
//BE064.0 25/11/2011 (CM)
// - Correction bug de la configuration par sFTP (lors changement countryId)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _DEF_CONFIGFILES

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION ADMIN
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_ADMIN_CFG[] = {
	{	"identifiant",				FTYPVAL_STRING,	NULL, LG_NOM_IDENTIFIANT,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_identifiant)},
	{	"localisation",				FTYPVAL_STRING,	NULL, LG_NOM_LOCALISATION,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_localisation)},
	{	"mot_de_passe_low",			FTYPVAL_STRING,	NULL, LG_NOM_PWD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_mot_de_passe_low)},
	{	"mot_de_passe_middle",		FTYPVAL_STRING,	NULL, LG_NOM_PWD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_mot_de_passe_middle)},
	{	"mot_de_passe_high",		FTYPVAL_STRING,	NULL, LG_NOM_PWD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_mot_de_passe_high)},
	{	"duree_inactivite_http",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u16_duree_inactivite_http)	},
	{	"max_client_ip",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_max_client_ip)	},
	{	"securisation_snmp",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_securisation_snmp)	},
	{	"langue",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_langue)	},
	{	"tps_refresh_html",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u16_tps_refresh_html)	},
	{	"date_demarrage",			FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_date_demarrage)},
	{	"mode_date_heure",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_mode_date_heure)	},
	{	"mode_mah",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_mode_mah)	},
	{	"client_ntp.adresse_serveur[P]",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])	},
	{	"client_ntp.adresse_serveur[S]",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])	},
	{	"client_ntp.fuseau_horaire",	FTYPVAL_S8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.s8_fuseau_horaire)	},
	{	"client_ntp.freq_maj_sntp",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.u16_freq_maj_sntp)	},
	{	"syslog_activation",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_syslog_activation)	},
	{	"mode_RSSI",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_mode_RSSI)	},
	{	"syslog_adresse_IP",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u32_syslog_adresse_IP)	},
	{	"syslog_port",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u16_syslog_port)			},
	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION CONSTRUCTEUR
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CONSTRUCTEUR_CFG[] = {
	{	"nom",						FTYPVAL_STRING,	NULL, LG_NOM_CONSTRUCTEUR,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_nom)	},
	{	"numero_telephone",			FTYPVAL_STRING,	NULL, LG_NUMERO_TELEPHONE_FAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_numero_telephone)	},
	{	"numero_fax",				FTYPVAL_STRING,	NULL, LG_NUMERO_TELEPHONE_FAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_numero_fax)	},
	{	"adresse_ligne1",			FTYPVAL_STRING,	NULL, LG_ADRESSE,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_adresse_ligne1)	},
	{	"adresse_ligne2",			FTYPVAL_STRING,	NULL, LG_ADRESSE,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_adresse_ligne2)	},
	{	"site_web",					FTYPVAL_STRING,	NULL, LG_SITE_WEB,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_site_web)	},
	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION SNMP
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_SNMP_CFG[] = {
	{	"version_snmp",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.u8_version_snmp)	},
	{	"nom_communaute_get",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_COMMUNAUTE_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.ps8_nom_communaute_get)	},
	{	"nom_communaute_set",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_COMMUNAUTE_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.ps8_nom_communaute_set)	},
	{	"nom_communaute_trap",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_COMMUNAUTE_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.ps8_nom_communaute_trap)	},
	{	"emission_trap",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.u8_emission_trap)	},
	{	"manager_snmp[0].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].ps8_nom)	},
	{	"manager_snmp[0].adresse_ip",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].u32_adresse_ip)	},
	{	"manager_snmp[0].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].u8_presence)	},
	{	"manager_snmp[0].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].u8_type_notification)	},
	{	"manager_snmp[1].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].ps8_nom)	},
	{	"manager_snmp[1].adresse_ip",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].u32_adresse_ip)	},
	{	"manager_snmp[1].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].u8_presence)	},
	{	"manager_snmp[1].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].u8_type_notification)	},
	{	"manager_snmp[2].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].ps8_nom)	},
	{	"manager_snmp[2].adresse_ip",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].u32_adresse_ip)	},
	{	"manager_snmp[2].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].u8_presence)	},
	{	"manager_snmp[2].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].u8_type_notification)	},
	{	"manager_snmp[3].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].ps8_nom)	},
	{	"manager_snmp[3].adresse_ip",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].u32_adresse_ip)	},
	{	"manager_snmp[3].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].u8_presence)	},
	{	"manager_snmp[3].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].u8_type_notification)	},
	{	"manager_snmp[4].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].ps8_nom)	},
	{	"manager_snmp[4].adresse_ip",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].u32_adresse_ip)	},
	{	"manager_snmp[4].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].u8_presence)	},
	{	"manager_snmp[4].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].u8_type_notification)	},
	{	"trap_SNMPv1[0].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_INDETERMINE].u16_nb_emission)	},
	{	"trap_SNMPv1[0].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_INDETERMINE].u16_interval)	},
	{	"trap_SNMPv1[1].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_CRITIQUE].u16_nb_emission)	},
	{	"trap_SNMPv1[1].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_CRITIQUE].u16_interval)	},
	{	"trap_SNMPv1[2].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MAJEUR].u16_nb_emission)	},
	{	"trap_SNMPv1[2].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MAJEUR].u16_interval)	},
	{	"trap_SNMPv1[3].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MINEUR].u16_nb_emission)	},
	{	"trap_SNMPv1[3].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MINEUR].u16_interval)	},
	{	"trap_SNMPv1[4].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_AVERTISSEMENT].u16_nb_emission)	},
	{	"trap_SNMPv1[4].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_AVERTISSEMENT].u16_interval)	},
	{	"inform_SNMPv2c.nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_inform_SNMPv2c.u16_nb_emission)	},
	{	"inform_SNMPv2c.interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_inform_SNMPv2c.u16_interval)	},
	{	"trap_signevie.u8_activation",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_signevie.u8_activation)	},
	{	"trap_signevie.u16_cycle",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_signevie.u16_cycle)	},
	{	CH_BDDFILECHECKSUM,				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION GENERAL
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_GENE_CFG[] = {
	{	"mode_radio_modem",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_mode_radio_modem)	},
	{	"mode_network",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_mode_network)	},
	{	"hostname",						FTYPVAL_STRING,	NULL, LG_MAX_HOSTNAME,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.ps8_hostname)	},
	{	"bridge_mode_ip",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_bridge_mode_ip)	},
	{	"bridge_adresse_ip",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_adresse_ip)	},
	{	"bridge_masque_reseau",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_masque_reseau)	},
	{	"bridge_gateway",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_gateway)		},
	{	"bridge_dhcp_fallback_ip",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_dhcp_fallback_ip)},
	{	"bridge_stp",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_bridge_stp)},
	{	"lan_adresse_ip",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_adresse_ip)		},
	{	"lan_masque_reseau",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_masque_reseau)	},
	{	"wlan_mode_ip",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_wlan_mode_ip)			},
	{	"wlan_adresse_ip",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_adresse_ip)		},
	{	"wlan_masque_reseau",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_masque_reseau)	},
	{	"wlan_gateway",					FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_gateway)			},
	{	"wlan_dhcp_fallback_ip",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_dhcp_fallback_ip)},
	{	"lan_fonction_dhcp",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_lan_fonction_dhcp)		},
	{	"lan_dhcpsrv_ip_min",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcpsrv_ip_min)	},
	{	"lan_dhcpsrv_ip_max",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcpsrv_ip_max)	},
	{	"lan_dhcpsrv_duree_vie_bail",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcpsrv_duree_vie_bail)	},
	{	"lan_dhcprelay_ip",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcprelay_ip)		},
	{	"vlan_autoriser",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_vlan_autoriser)		},
	{	"vlan_nom",						FTYPVAL_STRING,	NULL, TAILLE_MAX_VLAN,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.ps8_vlan_nom)	},
	{	"vlan_id",						FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u16_vlan_id)		},
	{	"vlan_interface_notag",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_vlan_interface_notag)	},
	{	"vlan_notag_adresse_ip",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_vlan_notag_adresse_ip)	},
	{	"vlan_notag_masque_reseau",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_vlan_notag_masque_reseau)	},

	{	CH_BDDFILECHECKSUM,				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION WIFI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_WIFI_CFG[] = {
	{	"mode_802_11x",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_mode_802_11x)		},
	{	"ssid_primary",					FTYPVAL_STRING,	NULL, NB_MAX_CHAINE_SSID,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.ps8_ssid_primary)		},
	{	"dual_ssid",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_dual_ssid)		},
	{	"ssid_secondary",				FTYPVAL_STRING,	NULL, NB_MAX_CHAINE_SSID,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.ps8_ssid_secondary)		},
	{	"masquage_ssid",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_masquage_ssid)		},
	{	"11n_guard_interval",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_11n_guard_interval)		},
	{	"type_selection_canal",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_type_selection_canal)		},
	{	"iso_canal_radio",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_iso_canal_radio)			},
	{	"multi_canal_radio[0]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[0])	},
	{	"multi_canal_radio[1]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[1])	},
	{	"multi_canal_radio[2]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[2])	},
	{	"multi_canal_radio[3]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[3])	},
	{	"multi_canal_radio[4]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[4])	},
	{	"power_tx",						FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_power_tx)				},
	{	"data_rate",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_data_rate)					},
	{	"seuil_rx",						FTYPVAL_S8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s8_seuil_rx)				},
	{	"nb_max_associated_stations",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_nb_max_associated_stations)},
	{	"mode_securite_wifi",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_mode_securite_wifi)		},
	{	"wep_security.key_length",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.u8_key_length)	},
	{	"wep_security.key_type",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.u8_wep_key_type)	},
	{	"wep_security.key_value[0]",	FTYPVAL_STRING,	NULL, KEY_WEP_VALUE_LENGTH_MAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.ps8_key_value[IDX_WEP_KEY_1])	},
	{	"wep_security.key_value[1]",	FTYPVAL_STRING,	NULL, KEY_WEP_VALUE_LENGTH_MAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.ps8_key_value[IDX_WEP_KEY_2])	},
	{	"wep_security.key_value[2]",	FTYPVAL_STRING,	NULL, KEY_WEP_VALUE_LENGTH_MAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.ps8_key_value[IDX_WEP_KEY_3])	},
	{	"wep_security.key_value[3]",	FTYPVAL_STRING,	NULL, KEY_WEP_VALUE_LENGTH_MAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.ps8_key_value[IDX_WEP_KEY_4])	},
	{	"wep_security.index_key_default",FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.u8_index_key_default)	},
	{	"wep_security.authentification",FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wep_security.u8_authentification)	},
	{	"wpa_security.authentification",FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u8_authentification)	},
	{	"wpa_security.gp_key_update_interval",FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u32_gp_key_update_interval)	},
	{	"wpa_security.key_type",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u8_wpa_key_type)	},
	{	"wpa_security.pre_shared_key",	FTYPVAL_STRING,	NULL, LG_MAX_PRESHARED_WPA_TOTAL,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_pre_shared_key)	},
	{	"wpa_security.radius.ip",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip)	},
	{	"wpa_security.radius.port",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.s_server_radius.u16_radius_port)	},
	{	"wpa_security.radius.shared",	FTYPVAL_STRING,	NULL, LG_MAX_SHARED_RADIUS,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared)	},
	{	"wpa_security.eap_reauth_period",FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u32_eap_reauth_period)	},
	{	"wpa_security.eap_method",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u8_eap_method)	},
	{	"wpa_security.identity",		FTYPVAL_STRING,	NULL, LG_MAX_EAP_IDENTITY,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_identity)	},
#if PARAMETERS_RADIUS_NOT_USED
	{	"wpa_security.user_identity",	FTYPVAL_STRING,	NULL, LG_MAX_EAP_USER_NAME,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_user_name)	},
#endif
	{	"wpa_security.user_password",	FTYPVAL_STRING,	NULL, LG_MAX_EAP_USER_PASSWORD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_user_password)	},
	{	"wpa_security.file_cert_auth",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_CERTIFICAT,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_file_certificat_authority)	},
	{	"wpa_security.file_cert_clt",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_CERTIFICAT,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_file_certificat_client)	},
	{	"wpa_security.private_key_pwd",			FTYPVAL_STRING,	NULL, LG_MAX_PRIVATE_KEY_PWD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_private_key_password)	},

	//Protocole wifi
	{	"protcl_ABG_ACK_timeout",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_ABG_ACK_timeout)		},
	{	"protcl_N_ACK_timeout",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_N_ACK_timeout)	},
	{	"protcl_type_preambule",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_protcl_type_preambule)	},
	{	"protcl_fragment_threshold",FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_fragment_threshold)},
	{	"protcl_RTS_CTS_threshold",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_RTS_CTS_threshold)},
	{	"protcl_RTS_retry_limit",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_RTS_retry_limit)},
	{	"protcl_beacon_period",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_beacon_period)},
	{	"activation_WMM",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_activation_WMM)},
	{	"countryID",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_countryID)},
	{	"desactivation_DFS",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_desactivation_DFS)},

	//Antennes
	{	"ant_ABG_tx_selection",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_ant_ABG_tx_selection)	},
	{	"ant_ABG_rx_selection",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_ant_ABG_rx_selection)	},
	{	"ant_N_selection",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_ant_N_selection)	},
	
	{	CH_BDDFILECHECKSUM,				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION ROUTING
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RTESTATIC[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enabl",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u8_enabled)		},
	{	"ip",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u32_destination_ip)},
	{	"mask",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u32_destination_mask)},
	{	"gw",				FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u32_gateway_ip)		},
	{	"if",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u8_interface)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RTEPOLITIC[] = {
	{	CH_TAB_INDEX,	FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enabl",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_enabled) },
	{	"name",			FTYPVAL_STRING,	NULL, TAILLE_MAX_POLICY_NAME,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, ps8_policy_name)	},
	{	"vcr[srcIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_SRC_IP]) },
	{	"vcr[dstIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_DST_IP]) },
	{	"vcr[len]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET]) },
	{	"vcr[prot]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL]) },
	{	"vcr[srcP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_SRC_PORT]) },
	{	"vcr[dstP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_DST_PORT]) },
	{	"vcr[CS]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR]) },
	{	"ncr[srcIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_SRC_IP]) },
	{	"ncr[dstIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_DST_IP]) },
	{	"ncr[len]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET]) },
	{	"ncr[prot]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL]) },
	{	"ncr[srcP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_SRC_PORT]) },
	{	"ncr[dstP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_DST_PORT]) },
	{	"ncr[CS]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_CLASS_SELECTOR]) },
	{	"srcipstart",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_src_ip_start)	},
	{	"srcipend",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_src_ip_end)	},
	{	"dstipstart",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_dst_ip_start)	},
	{	"dstipend",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_dst_ip_end)	},
	{	"len_min",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_len_packet_min)},
	{	"len_max",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_len_packet_max)},
	{	"prot",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_critere_ip_protocol)	},
	{	"srcportstart",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_src_port_start)},
	{	"srcportend",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_src_port_end)},
	{	"dstportstart",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_dst_port_start)},
	{	"dstportend",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_dst_port_end)},
	{	"CS",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_critere_class_selector)},
	{	"vact[gw]",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_action[ACTIONPOLICY_GATEWAY])},
	{	"vact[CS]",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])},
	{	"act_gw",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_new_gateway)	},
	{	"act_CS",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_new_class_selector)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_ROUTING_CFG[] = {
	{	"route_static",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RTESTATIC,	(u16sod)sizeof(S_STRUCT_IP_ROUTE_STATIC),	NB_MAX_ROUTES_IP_STATIC,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.ps_route_ip_static)	},
	{	"route_politic",			FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RTEPOLITIC,	(u16sod)sizeof(S_STRUCT_ROUTE_POLICY),	NB_MAX_POLICY_ROUTING,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.ps_route_policy)	},
	{	"ripv2_activation",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.u8_ripv2_activation)	},
	{	"rip_interface_used[LAN]",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.pu8_rip_interface_used[RIP_INTERF_LAN])	},
	{	"rip_interface_used[WLAN]",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.pu8_rip_interface_used[RIP_INTERF_WLAN])	},
	{	"rip_authentification",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.u8_rip_authentification)	},
	{	"rip_password",				FTYPVAL_STRING,	NULL, TAILLE_MAX_RIP_PASSWORD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.ps8_rip_password)	},
	
	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION NAT
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RULENATPFWD[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enable",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u8_enable)			},
	{	"ip_private",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u32_private_ip)	},
	{	"port_private",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u16_private_port)	},
	{	"protocole",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u8_protocole)		},
	{	"port_public",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u16_public_port)	},
	{	"comment",			FTYPVAL_STRING,	NULL, TAILLE_MAX_COMMENT_NAT_PFWD,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, ps8_commentaire) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RULENATMAPADR[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enable",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, u8_enable)			},
	{	"ip_private",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, u32_private_ip)	},
	{	"ip_public",		FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, u32_public_alias_ip)	},
	{	"comment",			FTYPVAL_STRING,	NULL, TAILLE_MAX_COMMENT_NAT_MPADR,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, ps8_commentaire) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_NAT_CFG[] = {
	{	"nat_activation",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_nat.u8_nat_activation)	},
	{	"rule_port_forwarding",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RULENATPFWD,	(u16sod)sizeof(S_STRUCT_NAT_RULE_PORT_FORWARDING),	NB_MAX_RULES_PORT_FORWARDING,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_nat.ps_rule_port_forwarding)	},
	{	"rule_mapping_adresse",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RULENATMAPADR,	(u16sod)sizeof(S_STRUCT_NAT_RULE_MAP_ADRESSES),	NB_MAX_NAT_ALIAS_IP,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_nat.ps_rule_mapping_adresse)	},

	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION MULTICAST
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_SRCMULTICAST[] = {
	{	CH_TAB_INDEX,	FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enable",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_SRC_MULTICAST, u8_enable)		},
	{	"adr",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_SRC_MULTICAST, u32_adresse_reseau)	},
	{	"mask",			FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_SRC_MULTICAST, u32_masque_reseau)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_MULTICAST_CFG[] = {
	{	"proxy_igmp_activation",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_multicast.u8_proxy_igmp_activation)	},
	{	"source_multicast",			FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_SRCMULTICAST,	(u16sod)sizeof(S_STRUCT_SRC_MULTICAST),	NB_MAX_SRC_MULTICAST,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_multicast.ps_source_multicast)	},

	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION TABLEAU DES EVENEMENTS
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_CFGEVENT[] = {
	{	CH_TAB_INDEX,	FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"action",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CFG_EVENT, u16_action)			},
	{	"niveau",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CFG_EVENT, u8_niveau_gravite)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_TABEVT_CFG[] = {
	{	"event",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_CFGEVENT, (u16sod)sizeof(S_STRUCT_CFG_EVENT), NB_MAX_EVENEMENTS,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_tabevt.s_event) },

	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION HANDOFF
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_HANDOFF_CFG[] = {
	{	"scanning_mode",				FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u8_scanning_mode)	},
	{	"time_between_hand_off",		FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_time_between_hand_off)	},
	{	"bgscan_activation",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u8_bgscan_activation)	},
	{	"bgscan_recur_period",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_bgscan_recurrence_period)	},
	{	"bgscan_detection_level",		FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.s32_bgscan_detection_level)	},
	{	"fgscan_detection_level",		FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.s32_fgscan_detection_level)	},
	{	"fgscan_beacon_missed_thresh",	FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_fgscan_beacon_missed_threshold)	},
	{	"iso_detection_level",			FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.s32_iso_detection_level)	},
	{	"iso_relevant_beacon_thresh",	FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_iso_relevant_beacon_threshold)	},
	{	"type_filtrage_rssi",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u8_type_filtrage_rssi)	},
	{	"time_between_beacon",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_time_between_2_beacon)	},

	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};



//d: BE063.0 06/10/2011

//structure avec les adresses IP en notation pointee
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RTESTATIC_POINT[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enabl",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u8_enabled)		},
	{	"ip",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u32_destination_ip)},
	{	"mask",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u32_destination_mask)},
	{	"gw",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u32_gateway_ip)		},
	{	"if",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_IP_ROUTE_STATIC, u8_interface)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RTEPOLITIC_POINT[] = {
	{	CH_TAB_INDEX,	FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enabl",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_enabled) },
	{	"name",			FTYPVAL_STRING,	NULL, TAILLE_MAX_POLICY_NAME,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, ps8_policy_name)	},
	{	"vcr[srcIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_SRC_IP]) },
	{	"vcr[dstIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_DST_IP]) },
	{	"vcr[len]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET]) },
	{	"vcr[prot]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL]) },
	{	"vcr[srcP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_SRC_PORT]) },
	{	"vcr[dstP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_DST_PORT]) },
	{	"vcr[CS]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR]) },
	{	"ncr[srcIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_SRC_IP]) },
	{	"ncr[dstIP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_DST_IP]) },
	{	"ncr[len]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET]) },
	{	"ncr[prot]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL]) },
	{	"ncr[srcP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_SRC_PORT]) },
	{	"ncr[dstP]",	FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_DST_PORT]) },
	{	"ncr[CS]",		FTYPVAL_U8SOD,	NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_not_critere[CRITERIAPOLICY_CLASS_SELECTOR]) },
	{	"srcipstart",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_src_ip_start)	},
	{	"srcipend",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_src_ip_end)	},
	{	"dstipstart",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_dst_ip_start)	},
	{	"dstipend",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_critere_dst_ip_end)	},
	{	"len_min",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_len_packet_min)},
	{	"len_max",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_len_packet_max)},
	{	"prot",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_critere_ip_protocol)	},
	{	"srcportstart",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_src_port_start)},
	{	"srcportend",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_src_port_end)},
	{	"dstportstart",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_dst_port_start)},
	{	"dstportend",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u16_critere_dst_port_end)},
	{	"CS",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_critere_class_selector)},
	{	"vact[gw]",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_action[ACTIONPOLICY_GATEWAY])},
	{	"vact[CS]",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])},
	{	"act_gw",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u32_new_gateway)	},
	{	"act_CS",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_ROUTE_POLICY, u8_new_class_selector)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RULENATPFWD_POINT[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enable",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u8_enable)			},
	{	"ip_private",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u32_private_ip)	},
	{	"port_private",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u16_private_port)	},
	{	"protocole",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u8_protocole)		},
	{	"port_public",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, u16_public_port)	},
	{	"comment",			FTYPVAL_STRING,	NULL, TAILLE_MAX_COMMENT_NAT_PFWD,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_PORT_FORWARDING, ps8_commentaire) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_DEF_STRUCT_RULENATMAPADR_POINT[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enable",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, u8_enable)			},
	{	"ip_private",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, u32_private_ip)	},
	{	"ip_public",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, u32_public_alias_ip)	},
	{	"comment",			FTYPVAL_STRING,	NULL, TAILLE_MAX_COMMENT_NAT_MPADR,	0,	MACRO_OFFSETOF(S_STRUCT_NAT_RULE_MAP_ADRESSES, ps8_commentaire) },
	{	NULL,	0,	NULL,	0,	0,	0	}
};
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_SRCMULTICAST_POINT[] = {
	{	CH_TAB_INDEX,	FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"enable",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_SRC_MULTICAST, u8_enable)		},
	{	"adr",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_SRC_MULTICAST, u32_adresse_reseau)	},
	{	"mask",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_SRC_MULTICAST, u32_masque_reseau)		},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//***************************************************************************
//**************** CONTENU DU FICHIER DE CONFIGURATION GLOBALE POUR sFTP
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CFG_GLOBALE[] = {
//partie constructeur
	{	"CONSTRUCTEUR",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"nom",						FTYPVAL_STRING,	NULL, LG_NOM_CONSTRUCTEUR,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_nom)	},
	{	"numero_telephone",			FTYPVAL_STRING,	NULL, LG_NUMERO_TELEPHONE_FAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_numero_telephone)	},
	{	"numero_fax",				FTYPVAL_STRING,	NULL, LG_NUMERO_TELEPHONE_FAX,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_numero_fax)	},
	{	"adresse_ligne1",			FTYPVAL_STRING,	NULL, LG_ADRESSE,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_adresse_ligne1)	},
	{	"adresse_ligne2",			FTYPVAL_STRING,	NULL, LG_ADRESSE,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_adresse_ligne2)	},
	{	"site_web",					FTYPVAL_STRING,	NULL, LG_SITE_WEB,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_constructeur.ps8_site_web)	},
//partie admin
	{	"ADMIN",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"identifiant",				FTYPVAL_STRING,	NULL, LG_NOM_IDENTIFIANT,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_identifiant)},
	{	"localisation",				FTYPVAL_STRING,	NULL, LG_NOM_LOCALISATION,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.ps8_localisation)},
	{	"duree_inactivite_http",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u16_duree_inactivite_http)	},
	{	"max_client_ip",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_max_client_ip)	},
	{	"securisation_snmp",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_securisation_snmp)	},
	{	"langue",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_langue)	},
	{	"tps_refresh_html",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u16_tps_refresh_html)	},
	{	"date_demarrage",			FTYPVAL_DATE,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_date_demarrage)},
	{	"mode_date_heure",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_mode_date_heure)	},
	{	"mode_mah",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_mode_mah)	},
	{	"client_ntp.adresse_serveur[P]",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])	},
	{	"client_ntp.adresse_serveur[S]",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])	},
	{	"client_ntp.fuseau_horaire",	FTYPVAL_S8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.s8_fuseau_horaire)	},
	{	"client_ntp.freq_maj_sntp",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.s_client_ntp.u16_freq_maj_sntp)	},
	{	"syslog_activation",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_syslog_activation)	},
	{	"mode_RSSI",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u8_mode_RSSI)	},
	{	"syslog_adresse_IP",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u32_syslog_adresse_IP)	},
	{	"syslog_port",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_admin.u16_syslog_port)			},
//partie snmp
	{	"SNMP",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"version_snmp",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.u8_version_snmp)	},
	{	"nom_communaute_get",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_COMMUNAUTE_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.ps8_nom_communaute_get)	},
	{	"nom_communaute_set",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_COMMUNAUTE_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.ps8_nom_communaute_set)	},
	{	"nom_communaute_trap",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_COMMUNAUTE_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.ps8_nom_communaute_trap)	},
	{	"emission_trap",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.u8_emission_trap)	},
	{	"manager_snmp[0].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].ps8_nom)	},
	{	"manager_snmp[0].adresse_ip",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].u32_adresse_ip)	},
	{	"manager_snmp[0].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].u8_presence)	},
	{	"manager_snmp[0].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[0].u8_type_notification)	},
	{	"manager_snmp[1].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].ps8_nom)	},
	{	"manager_snmp[1].adresse_ip",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].u32_adresse_ip)	},
	{	"manager_snmp[1].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].u8_presence)	},
	{	"manager_snmp[1].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[1].u8_type_notification)	},
	{	"manager_snmp[2].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].ps8_nom)	},
	{	"manager_snmp[2].adresse_ip",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].u32_adresse_ip)	},
	{	"manager_snmp[2].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].u8_presence)	},
	{	"manager_snmp[2].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[2].u8_type_notification)	},
	{	"manager_snmp[3].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].ps8_nom)	},
	{	"manager_snmp[3].adresse_ip",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].u32_adresse_ip)	},
	{	"manager_snmp[3].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].u8_presence)	},
	{	"manager_snmp[3].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[3].u8_type_notification)	},
	{	"manager_snmp[4].nom",			FTYPVAL_STRING,	NULL, LG_NOM_MANAGER_SNMP,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].ps8_nom)	},
	{	"manager_snmp[4].adresse_ip",	FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].u32_adresse_ip)	},
	{	"manager_snmp[4].presence",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].u8_presence)	},
	{	"manager_snmp[4].type_notification",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_manager_snmp[4].u8_type_notification)	},
	{	"trap_SNMPv1[0].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_INDETERMINE].u16_nb_emission)	},
	{	"trap_SNMPv1[0].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_INDETERMINE].u16_interval)	},
	{	"trap_SNMPv1[1].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_CRITIQUE].u16_nb_emission)	},
	{	"trap_SNMPv1[1].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_CRITIQUE].u16_interval)	},
	{	"trap_SNMPv1[2].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MAJEUR].u16_nb_emission)	},
	{	"trap_SNMPv1[2].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MAJEUR].u16_interval)	},
	{	"trap_SNMPv1[3].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MINEUR].u16_nb_emission)	},
	{	"trap_SNMPv1[3].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_MINEUR].u16_interval)	},
	{	"trap_SNMPv1[4].nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_AVERTISSEMENT].u16_nb_emission)	},
	{	"trap_SNMPv1[4].interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_SNMPv1[NIV_GRAVITE_AVERTISSEMENT].u16_interval)	},
	{	"inform_SNMPv2c.nb_emission",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_inform_SNMPv2c.u16_nb_emission)	},
	{	"inform_SNMPv2c.interval",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_inform_SNMPv2c.u16_interval)	},
	{	"trap_signevie.u8_activation",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_signevie.u8_activation)	},
	{	"trap_signevie.u16_cycle",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_snmp.s_trap_signevie.u16_cycle)	},
//General
	{	"GENERAL",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"mode_radio_modem",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_mode_radio_modem)	},
	{	"mode_network",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_mode_network)	},
	{	"hostname",						FTYPVAL_STRING,	NULL, LG_MAX_HOSTNAME,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.ps8_hostname)	},
	{	"bridge_mode_ip",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_bridge_mode_ip)	},
	{	"bridge_adresse_ip",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_adresse_ip)	},
	{	"bridge_masque_reseau",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_masque_reseau)	},
	{	"bridge_gateway",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_gateway)		},
	{	"bridge_dhcp_fallback_ip",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_bridge_dhcp_fallback_ip)},
	{	"bridge_stp",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_bridge_stp)},
	{	"lan_adresse_ip",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_adresse_ip)		},
	{	"lan_masque_reseau",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_masque_reseau)	},
	{	"wlan_mode_ip",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_wlan_mode_ip)			},
	{	"wlan_adresse_ip",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_adresse_ip)		},
	{	"wlan_masque_reseau",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_masque_reseau)	},
	{	"wlan_gateway",					FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_gateway)			},
	{	"wlan_dhcp_fallback_ip",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_wlan_dhcp_fallback_ip)},
	{	"lan_fonction_dhcp",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_lan_fonction_dhcp)		},
	{	"lan_dhcpsrv_ip_min",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcpsrv_ip_min)	},
	{	"lan_dhcpsrv_ip_max",			FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcpsrv_ip_max)	},
	{	"lan_dhcpsrv_duree_vie_bail",	FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcpsrv_duree_vie_bail)	},
	{	"lan_dhcprelay_ip",				FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_lan_dhcprelay_ip)		},
	{	"vlan_autoriser",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_vlan_autoriser)		},
	{	"vlan_nom",						FTYPVAL_STRING,	NULL, TAILLE_MAX_VLAN,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.ps8_vlan_nom)	},
	{	"vlan_id",						FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u16_vlan_id)		},
	{	"vlan_interface_notag",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u8_vlan_interface_notag)	},
	{	"vlan_notag_adresse_ip",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_vlan_notag_adresse_ip)	},
	{	"vlan_notag_masque_reseau",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_gene.u32_vlan_notag_masque_reseau)	},
//partie WiFi
	{	"WIFI",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"mode_802_11x",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_mode_802_11x)		},
	{	"ssid_primary",					FTYPVAL_STRING,	NULL, NB_MAX_CHAINE_SSID,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.ps8_ssid_primary)		},
	{	"dual_ssid",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_dual_ssid)		},
	{	"ssid_secondary",				FTYPVAL_STRING,	NULL, NB_MAX_CHAINE_SSID,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.ps8_ssid_secondary)		},
	{	"masquage_ssid",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_masquage_ssid)		},
	{	"11n_guard_interval",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_11n_guard_interval)		},
	{	"type_selection_canal",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_type_selection_canal)		},
	{	"iso_canal_radio",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_iso_canal_radio)			},
	{	"multi_canal_radio[0]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[0])	},
	{	"multi_canal_radio[1]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[1])	},
	{	"multi_canal_radio[2]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[2])	},
	{	"multi_canal_radio[3]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[3])	},
	{	"multi_canal_radio[4]",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.pu16_multi_canal_radio[4])	},
	{	"power_tx",						FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_power_tx)				},
	{	"data_rate",					FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_data_rate)					},
	{	"seuil_rx",						FTYPVAL_S8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s8_seuil_rx)				},
	{	"nb_max_associated_stations",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_nb_max_associated_stations)},
	{	"mode_securite_wifi",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_mode_securite_wifi)		},
	{	"wpa_security.authentification",FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u8_authentification)	},
	{	"wpa_security.gp_key_update_interval",FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u32_gp_key_update_interval)	},
	{	"wpa_security.key_type",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u8_wpa_key_type)	},
	{	"wpa_security.pre_shared_key",	FTYPVAL_STRING,	NULL, LG_MAX_PRESHARED_WPA_TOTAL,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_pre_shared_key)	},
	{	"wpa_security.radius.ip",		FTYPVAL_ADDIP,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip)	},
	{	"wpa_security.radius.port",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.s_server_radius.u16_radius_port)	},
	{	"wpa_security.radius.shared",	FTYPVAL_STRING,	NULL, LG_MAX_SHARED_RADIUS,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared)	},
	{	"wpa_security.eap_reauth_period",FTYPVAL_U32SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u32_eap_reauth_period)	},
	{	"wpa_security.eap_method",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.u8_eap_method)	},
	{	"wpa_security.identity",		FTYPVAL_STRING,	NULL, LG_MAX_EAP_IDENTITY,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_identity)	},
	{	"wpa_security.user_password",	FTYPVAL_STRING,	NULL, LG_MAX_EAP_USER_PASSWORD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_user_password)	},
	{	"wpa_security.file_cert_auth",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_CERTIFICAT,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_file_certificat_authority)	},
	{	"wpa_security.file_cert_clt",			FTYPVAL_STRING,	NULL, LG_MAX_NOM_CERTIFICAT,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_file_certificat_client)	},
	{	"wpa_security.private_key_pwd",			FTYPVAL_STRING,	NULL, LG_MAX_PRIVATE_KEY_PWD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.s_wpa_security.ps8_private_key_password)	},
	{	"protcl_N_ACK_timeout",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_N_ACK_timeout)	},
	{	"protcl_fragment_threshold",FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_fragment_threshold)},
	{	"protcl_RTS_CTS_threshold",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_RTS_CTS_threshold)},
	{	"protcl_RTS_retry_limit",	FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_RTS_retry_limit)},
	{	"protcl_beacon_period",		FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u16_protcl_beacon_period)},
	{	"activation_WMM",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_activation_WMM)},
	{	"countryID",				FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_countryID)},
	{	"desactivation_DFS",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_desactivation_DFS)},
	{	"ant_N_selection",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_wifi.u8_ant_N_selection)	},
//partie handoff	
	{	"HANDOFF",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"scanning_mode",				FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u8_scanning_mode)	},
	{	"time_between_hand_off",		FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_time_between_hand_off)	},
	{	"bgscan_activation",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u8_bgscan_activation)	},
	{	"bgscan_recur_period",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_bgscan_recurrence_period)	},
	{	"bgscan_detection_level",		FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.s32_bgscan_detection_level)	},
	{	"fgscan_detection_level",		FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.s32_fgscan_detection_level)	},
	{	"fgscan_beacon_missed_thresh",	FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_fgscan_beacon_missed_threshold)	},
	{	"iso_detection_level",			FTYPVAL_S32SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.s32_iso_detection_level)	},
	{	"iso_relevant_beacon_thresh",	FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_iso_relevant_beacon_threshold)	},
	{	"type_filtrage_rssi",			FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u8_type_filtrage_rssi)	},
	{	"time_between_beacon",			FTYPVAL_U16SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_handoff.u16_time_between_2_beacon)	},
//partie routing
	{	"ROUTING",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"route_static",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RTESTATIC_POINT,	(u16sod)sizeof(S_STRUCT_IP_ROUTE_STATIC),	NB_MAX_ROUTES_IP_STATIC,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.ps_route_ip_static)	},
	{	"route_politic",			FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RTEPOLITIC_POINT,	(u16sod)sizeof(S_STRUCT_ROUTE_POLICY),	NB_MAX_POLICY_ROUTING,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.ps_route_policy)	},
	{	"ripv2_activation",			FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.u8_ripv2_activation)	},
	{	"rip_interface_used[LAN]",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.pu8_rip_interface_used[RIP_INTERF_LAN])	},
	{	"rip_interface_used[WLAN]",	FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.pu8_rip_interface_used[RIP_INTERF_WLAN])	},
	{	"rip_authentification",		FTYPVAL_U8SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.u8_rip_authentification)	},
	{	"rip_password",				FTYPVAL_STRING,	NULL, TAILLE_MAX_RIP_PASSWORD,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_ip_routing.ps8_rip_password)	},
//partie NAT
	{	"NAT",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"nat_activation",		FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_nat.u8_nat_activation)	},
	{	"rule_port_forwarding",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RULENATPFWD_POINT,	(u16sod)sizeof(S_STRUCT_NAT_RULE_PORT_FORWARDING),	NB_MAX_RULES_PORT_FORWARDING,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_nat.ps_rule_port_forwarding)	},
	{	"rule_mapping_adresse",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_RULENATMAPADR_POINT,	(u16sod)sizeof(S_STRUCT_NAT_RULE_MAP_ADRESSES),	NB_MAX_NAT_ALIAS_IP,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_nat.ps_rule_mapping_adresse)	},
//partie multicast
	{	"MULTICAST",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"proxy_igmp_activation",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_multicast.u8_proxy_igmp_activation)	},
	{	"source_multicast",			FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_SRCMULTICAST_POINT,	(u16sod)sizeof(S_STRUCT_SRC_MULTICAST),	NB_MAX_SRC_MULTICAST,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_multicast.ps_source_multicast)	},
//partie tabevt
	{	"TABEVT",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},
	{	"event",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_CFGEVENT, (u16sod)sizeof(S_STRUCT_CFG_EVENT), NB_MAX_EVENEMENTS,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, s_tabevt.s_event) },

	{	"CHECKSUM",	FTYPVAL_COMMENT,	NULL,	0,	0,	0	},

	{	CH_BDDFILECHECKSUM,			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u16_checksum_file)	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_DEFINITION_FILE_FS PT_DEF_FILE_CONFIG_GLOBAL_STA=
{
	//ID_FILE_FLASH_CFG_BASE_ADMIN
	PATH_DIR_VAR_CONF NFILE_GLOBALE EXT_STA, //ps8_path_file
	DEFFILE_TYPE_CONFIG, //u8_type
	TRUE,	//u8_avec_checksum
	PT_CONTENU_FILE_CFG_GLOBALE,//pt_contenu
	
};

T_STRUCT_DEFINITION_FILE_FS PT_DEF_FILE_CONFIG_GLOBAL_SANSCHECKSUM=
{
	//ID_FILE_FLASH_CFG_BASE_ADMIN
	PATH_DIR_VAR_CONF NFILE_GLOBALE EXT_CFG, //ps8_path_file
	DEFFILE_TYPE_CONFIG, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_CFG_GLOBALE,//pt_contenu

};

//f:BE063.0 06/10/2011



//****************************************
//DEFINITION DES FICHIERS DE CONFIGURATION
//****************************************
T_STRUCT_DEFINITION_FILE_FS PT_DEF_FILE_CONFIG[NB_MAX_ID_FILES_CONFIG] =
{
	{//ID_FILE_CFG_NULL
		"",	 //ps8_path_file
		DEFFILE_TYPE_AUCUN,	//u8_type
		FALSE,	//u8_avec_checksum
		NULL ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BASE_ADMIN
		PATH_DIR__FLASH_CONFIG_BASE NFILE_ADMIN EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_ADMIN_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_ADMIN
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_ADMIN EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_ADMIN_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_ADMIN_CFG
		PATH_DIR__BDD_CONFIG NFILE_ADMIN EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_ADMIN_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_CONSTRUCTEUR
		PATH_DIR__FLASH_CONFIG_BASE NFILE_CONSTRUCTEUR EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_CONSTRUCTEUR_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_CONSTRUCTEUR
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_CONSTRUCTEUR EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_CONSTRUCTEUR_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_CONSTRUCTEUR_CFG
		PATH_DIR__BDD_CONFIG NFILE_CONSTRUCTEUR EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_CONSTRUCTEUR_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_SNMP
		PATH_DIR__FLASH_CONFIG_BASE NFILE_SNMP EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_SNMP_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_SNMP
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_SNMP EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_SNMP_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_SNMP_CFG
		PATH_DIR__BDD_CONFIG NFILE_SNMP EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_SNMP_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_GENE
		PATH_DIR__FLASH_CONFIG_BASE NFILE_GENERAL EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_GENE_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_GENE
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_GENERAL EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_GENE_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_GENE_CFG
		PATH_DIR__BDD_CONFIG NFILE_GENERAL EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_GENE_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_WIFI
		PATH_DIR__FLASH_CONFIG_BASE NFILE_WIFI EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_WIFI_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_WIFI
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_WIFI EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_WIFI_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_WIFI_CFG
		PATH_DIR__BDD_CONFIG NFILE_WIFI EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_WIFI_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_ROUTING
		PATH_DIR__FLASH_CONFIG_BASE NFILE_ROUTING EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_ROUTING_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_ROUTING
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_ROUTING EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_ROUTING_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_ROUTING_CFG
		PATH_DIR__BDD_CONFIG NFILE_ROUTING EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_ROUTING_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_NAT
		PATH_DIR__FLASH_CONFIG_BASE NFILE_NAT EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_NAT_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_NAT
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_NAT EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_NAT_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_NAT_CFG
		PATH_DIR__BDD_CONFIG NFILE_NAT EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_NAT_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_MULTICAST
		PATH_DIR__FLASH_CONFIG_BASE NFILE_MULTICAST EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_MULTICAST_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_MULTICAST
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_MULTICAST EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_MULTICAST_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_MULTICAST_CFG
		PATH_DIR__BDD_CONFIG NFILE_MULTICAST EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_MULTICAST_CFG ,//pt_contenu
	},
	
	{//ID_FILE_FLASH_CFG_BASE_TABEVT
		PATH_DIR__FLASH_CONFIG_BASE NFILE_TABEVT EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_TABEVT_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_TABEVT
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_TABEVT EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_TABEVT_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_TABEVT_CFG
		PATH_DIR__BDD_CONFIG NFILE_TABEVT EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_TABEVT_CFG ,//pt_contenu
	},

	{//ID_FILE_FLASH_CFG_BASE_HANDOFF
		PATH_DIR__FLASH_CONFIG_BASE NFILE_HANDOFF EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_HANDOFF_CFG ,//pt_contenu
	},
	{//ID_FILE_FLASH_CFG_BACKUP_HANDOFF
		PATH_DIR__FLASH_CONFIG_BACKUP NFILE_HANDOFF EXT_BACKUP, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_HANDOFF_CFG ,//pt_contenu
	},
	{//ID_FILE_BDD_HANDOFF_CFG
		PATH_DIR__BDD_CONFIG NFILE_HANDOFF EXT_CFG, //ps8_path_file
		DEFFILE_TYPE_CONFIG, //u8_type
		TRUE,	//u8_avec_checksum
		PT_CONTENU_FILE_HANDOFF_CFG ,//pt_contenu
	},
	
};


//****************************************
//DESCRIPTION DE LA CONFIGURATION
//****************************************
T_STRUCT_DESCRIPTION_CONFIGURATION PT_DESCRIPTION_CONFIGURATION[NB_MAX_IDXCONFIG] =
{
	{ //IDXCFG_ADMIN
		"IDXCFG_ADMIN",					//ps8_nom
		ID_FILE_FLASH_CFG_BASE_ADMIN,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_ADMIN,	//u16_idx_backup
		ID_FILE_BDD_ADMIN_CFG,			//u16_idx_bdd
		u8TestConfigAdmin,				//u8TestConfig
		CopyConfigAdmin,				//CopyConfig
		u8FillConfigAdmin,				//u8FillConfig
		u8EditConfigAdmin,				//u8EditConfig
		u8DiffConfigAdmin,				//u8DiffConfig
		NULL,							//u8ImposeInitConfig
	},
	{//IDXCFG_CONSTRUCTEUR
		"IDXCFG_CONSTRUCTEUR",					//ps8_nom
		ID_FILE_FLASH_CFG_BASE_CONSTRUCTEUR,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_CONSTRUCTEUR,	//u16_idx_backup
		ID_FILE_BDD_CONSTRUCTEUR_CFG,			//u16_idx_bdd
		u8TestConfigConstructeur,				//u8TestConfig
		CopyConfigConstructeur,					//CopyConfig
		u8FillConfigConstructeur,				//u8FillConfig
		u8EditConfigConstructeur,				//u8EditConfig
		u8DiffConfigConstructeur,				//u8DiffConfig
		NULL,							//u8ImposeInitConfig
	},
	{//IDXCFG_SNMP
		"IDXCFG_SNMP",					//ps8_nom
		ID_FILE_FLASH_CFG_BASE_SNMP,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_SNMP,	//u16_idx_backup
		ID_FILE_BDD_SNMP_CFG,			//u16_idx_bdd
		u8TestConfigSnmp,				//u8TestConfig
		CopyConfigSnmp,					//CopyConfig
		u8FillConfigSnmp,				//u8FillConfig
		u8EditConfigSnmp,				//u8EditConfig
		u8DiffConfigSnmp,				//u8DiffConfig
		NULL,							//u8ImposeInitConfig
	},
	{//IDXCFG_GENERAL
		"IDXCFG_GENERAL",				//ps8_nom
		ID_FILE_FLASH_CFG_BASE_GENE,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_GENE,	//u16_idx_backup
		ID_FILE_BDD_GENE_CFG,			//u16_idx_bdd
		u8TestConfigGeneral,			//u8TestConfig
		CopyConfigGeneral,				//CopyConfig
		u8FillConfigGeneral,			//u8FillConfig
		u8EditConfigGeneral,			//u8EditConfig
		u8DiffConfigGeneral,			//u8DiffConfig
//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//		NULL,							//u8ImposeInitConfig
		u8ImposeInitConfigGeneral,		//u8ImposeInitConfig
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
	},
	{//IDXCFG_WIFI
		"IDXCFG_WIFI",					//ps8_nom
		ID_FILE_FLASH_CFG_BASE_WIFI,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_WIFI,	//u16_idx_backup
		ID_FILE_BDD_WIFI_CFG,			//u16_idx_bdd
		u8TestConfigWifi,				//u8TestConfig
		CopyConfigWifi,					//CopyConfig
		u8FillConfigWifi,				//u8FillConfig
		u8EditConfigWifi,				//u8EditConfig
		u8DiffConfigWifi,				//u8DiffConfig
//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//		NULL,							//u8ImposeInitConfig
		u8ImposeInitConfigWifi,			//u8ImposeInitConfig
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
	},
	{//IDXCFG_ROUTING,
		"IDXCFG_ROUTING",				//ps8_nom
		ID_FILE_FLASH_CFG_BASE_ROUTING,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_ROUTING,//u16_idx_backup
		ID_FILE_BDD_ROUTING_CFG,		//u16_idx_bdd
		u8TestConfigRouting,			//u8TestConfig
		CopyConfigRouting,				//CopyConfig
		u8FillConfigRouting,			//u8FillConfig
		u8EditConfigRouting,			//u8EditConfig
		u8DiffConfigRouting,			//u8DiffConfig
		NULL,							//u8ImposeInitConfig
	},
	{//IDXCFG_NAT,
		"IDXCFG_NAT",				//ps8_nom
		ID_FILE_FLASH_CFG_BASE_NAT,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_NAT,//u16_idx_backup
		ID_FILE_BDD_NAT_CFG,		//u16_idx_bdd
		u8TestConfigNAT,			//u8TestConfig
		CopyConfigNAT,				//CopyConfig
		u8FillConfigNAT,			//u8FillConfig
		u8EditConfigNAT,			//u8EditConfig
		u8DiffConfigNAT,			//u8DiffConfig
		NULL,						//u8ImposeInitConfig
	},
	{//IDXCFG_MULTICAST
		"IDXCFG_MULTICAST",					//ps8_nom
		ID_FILE_FLASH_CFG_BASE_MULTICAST,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_MULTICAST,	//u16_idx_backup
		ID_FILE_BDD_MULTICAST_CFG,			//u16_idx_bdd
		u8TestConfigMulticast,				//u8TestConfig
		CopyConfigMulticast,				//CopyConfig
		u8FillConfigMulticast,				//u8FillConfig
		u8EditConfigMulticast,				//u8EditConfig
		u8DiffConfigMulticast,				//u8DiffConfig
		NULL,								//u8ImposeInitConfig
	},
	{//IDXCFG_TABEVT,
		"IDXCFG_TABEVT",				//ps8_nom
		ID_FILE_FLASH_CFG_BASE_TABEVT,	//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_TABEVT,//u16_idx_backup
		ID_FILE_BDD_TABEVT_CFG,			//u16_idx_bdd
		u8TestConfigTabEvt,				//u8TestConfig
		CopyConfigTabEvt,				//CopyConfig
		u8FillConfigTabEvt,				//u8FillConfig
		u8EditConfigTabEvt,				//u8EditConfig
		u8DiffConfigTabEvt,				//u8DiffConfig
		u8ImposeInitConfigTabEvt,		//u8ImposeInitConfig
	},
	{//IDXCFG_HANDOFF
		"IDXCFG_HANDOFF",					//ps8_nom
		ID_FILE_FLASH_CFG_BASE_HANDOFF,		//u16_idx_base
		ID_FILE_FLASH_CFG_BACKUP_HANDOFF,	//u16_idx_backup
		ID_FILE_BDD_HANDOFF_CFG,			//u16_idx_bdd
		u8TestConfigHandoff,				//u8TestConfig
		CopyConfigHandoff,					//CopyConfig
		u8FillConfigHandoff,				//u8FillConfig
		u8EditConfigHandoff,				//u8EditConfig
		u8DiffConfigHandoff,				//u8DiffConfig
		NULL,								//u8ImposeInitConfig
	},
};



//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM NEWCFG.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_CONTENU_FILE_NEWCFG_INI[] = {
	{	"flag",		FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_TABU8,	(u16sod)sizeof(u8sod),	NB_MAX_IDXCONFIG,	MACRO_OFFSETOF(T_STRUCT_OF_FILE_NEWCFG_INI, pu8_flag[0]) },
//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
	{	"change_cfg_FTP",	FTYPVAL_U8SOD,		NULL,	0,	0,	MACRO_OFFSETOF(T_STRUCT_OF_FILE_NEWCFG_INI, u8_change_cfg_FTP)	},
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER NEWCFG.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_NEWCFG_INI =
{
	PATH_DIR__BDD_CONFIG NFILE_NEWCFG EXT_INI, //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_NEWCFG_INI ,//pt_contenu
};



/*_____V - PROCEDURES ____________________________________________________*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Def_ConfigFiles
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/01/2010 -
// Description	: Initialisation du module de def_configfiles
//=====================================================================================
void InitModule_Def_ConfigFiles(void)
{

}/*InitModule_Def_ConfigFiles*/

