/*========================================================================*/
/* NOM DU FICHIER  : cfg_dhcp.c	 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 15/01/2010                                           */
/* Libelle         : Principal: Configuration du serveur / relai DHCP	  */
/* Projet          : WRM100                                               */
/* Indice          : BE036                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE005 15/01/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_DHCP

//Paramétrage du serveur udhcpd
#define FICHIER_CONFIG_UDHCPD PATH_DIR_ETC	 "udhcpd.conf"
#define OPTIONUDHCPD_AUTO_TIME		10 //temps d'écriture du fichier udhcpd.leases

//Fichier pour récupérer valeur du PID du processus "udhcpd"
#define FICHIER_VAR_UDHCPD_PID		PATH_DIR_VAR "run/udhcpd.pid"

// The time period at which udhcpd will write out a dhcpd.leases
// file. If this is 0, udhcpd will never automatically write a
// lease file. (specified in seconds)
#define AUTOTIME_UDHCPD_LEASES	1	//seconde

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_FctDHCP
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Installe la configuration de la fonction DHCP
//=====================================================================================
void Install_FctDHCP(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	if(TRUE == u8TestFctDHCP_Fonctionnelle(loc_ps_config)) //CONDITION: configuration DHCP valide
	{
		switch(loc_ps_config->s_gene.u8_lan_fonction_dhcp)
		{
			case FCT_DHCP_NONE:
				break;
			case FCT_DHCP_SERVER:
				Install_DHCP_serveur(loc_ps_config);
				break;
			case FCT_DHCP_RELAY:
				Install_DHCP_relay(loc_ps_config);
				break;
			default:
				break;
		}
	}
	else
	{
		printf("PROBLEME Install_FctDHCP\n");
	}
			
}/*Install_FctDHCP*/

//=====================================================================================
// Fonction		: Uninstall_FctDHCP
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Désinstalle la configuration de la fonction DHCP
//=====================================================================================
void Uninstall_FctDHCP(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	switch(loc_ps_config->s_gene.u8_lan_fonction_dhcp)
	{
		case FCT_DHCP_NONE:
			break;
		case FCT_DHCP_SERVER:
			Uninstall_DHCP_serveur(loc_ps_config);
			break;
		case FCT_DHCP_RELAY:
			Uninstall_DHCP_relay(loc_ps_config);
			break;
		default:
			break;
	}
}/*Uninstall_FctDHCP*/


//=====================================================================================
// Fonction		: Install_DHCP_serveur
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Installe la configuration du serveur DHCP
//=====================================================================================
void Install_DHCP_serveur(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s32sod loc_s32_pid;

	printf("Install_DHCP_serveur\n");

	loc_s32_pid = s32GetPidProcessus("udhcpd", FICHIER_VAR_UDHCPD_PID);
	printf("PID Processus udhcpd = %ld \n",loc_s32_pid);

	if(loc_s32_pid > 0)
	{
		CmdSystem_Generique("kill %d",loc_s32_pid);
	}

	//Création du fichier de configuration
	if(FALSE == u8CreationFichierCfgUdhcpd(loc_ps_config))
	{
		printf("Install_DHCP_serveur: u8CreationFichierCfgUdhcpd KO \n");
	}

	//on lance en deamon
	CmdSystem_Generique("udhcpd %s &",
						FICHIER_CONFIG_UDHCPD);


}/*Install_DHCP_serveur*/

//=====================================================================================
// Fonction		: Uninstall_DHCP_serveur
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Désinstalle la configuration du serveur DHCP
//=====================================================================================
void Uninstall_DHCP_serveur(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_DHCP_serveur\n");

	//on tue le processus
	CmdSystem_Generique("killall udhcpd");

}/*Uninstall_DHCP_serveur*/

//=====================================================================================
// Fonction		: Install_DHCP_relay
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Installe la configuration du relai DHCP
//=====================================================================================
void Install_DHCP_relay(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_DHCP_relay\n");

	//on lance en deamon
	CmdSystem_Generique("dhcprelay %s %s %s &",
						NOM_INTERFACE_ETHERNET,
					    NOM_INTERFACE_WIFI,
					    ps8GetStringIp(loc_ps_config->s_gene.u32_lan_dhcprelay_ip));


}/*Install_DHCP_relay*/

//=====================================================================================
// Fonction		: Uninstall_DHCP_relay
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Désinstalle la configuration du relay DHCP
//=====================================================================================
void Uninstall_DHCP_relay(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_DHCP_relay\n");

	//on tue le processus
	CmdSystem_Generique("killall dhcprelay");

}/*Uninstall_DHCP_relay*/
   

//=====================================================================================
// Fonction		: u8CreationFichierCfgUdhcpd
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 15/01/2010 -
// Description	: Edition du fichier udhcpd.conf pour le processus udhcpd (busybox)
//=====================================================================================
u8sod u8CreationFichierCfgUdhcpd(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	FILE *	loc_pf_file;
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(NULL == (loc_pf_file = fopen(FICHIER_CONFIG_UDHCPD, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgUdhcpd: Erreur creation fichier %s\n",FICHIER_CONFIG_UDHCPD));
		loc_u8_resultat = FALSE;
	}
	else
	{
		fprintf(loc_pf_file,"start	%s\n",ps8GetStringIp(loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_min));
		fprintf(loc_pf_file,"end	%s\n",ps8GetStringIp(loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_max));
		fprintf(loc_pf_file,"interface	%s\n",NOM_INTERFACE_ETHERNET);
		fprintf(loc_pf_file,"max_leases	%d\n",NB_MAX_CLIENTS_DHCP);
		fprintf(loc_pf_file,"auto_time	%d\n",AUTOTIME_UDHCPD_LEASES); //en secondes
		fprintf(loc_pf_file,"lease_file %s\n",FICHIER_UDHCPD_LEASES);
		fprintf(loc_pf_file,"option	subnet	%s\n",ps8GetStringIp(loc_ps_config->s_gene.u32_lan_masque_reseau));
		//passerelle par défaut: le serveur DHCP
		fprintf(loc_pf_file,"opt	router	%s\n",ps8GetStringIp(loc_ps_config->s_gene.u32_lan_adresse_ip));
		fprintf(loc_pf_file,"option	lease	%lu\n",loc_ps_config->s_gene.u32_lan_dhcpsrv_duree_vie_bail * 60); //en secondes

		//fermeture du fichier
		fclose(loc_pf_file);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_UDHCPD, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgUdhcpd*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Dhcp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/01/2010 -
// Description	: Initialisation du module de cfg_dhcp
//=====================================================================================
void InitModule_Cfg_Dhcp(void)
{
	
}/*InitModule_Cfg_Dhcp*/

