/*========================================================================*/
/* NOM DU FICHIER  : cfg_multicast.c	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/03/2010                                           */
/* Libelle         : Principal: Configuration du Multicast				  */
/* Projet          : WRM100                                               */
/* Indice          : BE036                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE022 30/03/2010 CM
// - CREATION
//BE025 15/04/2010 CM
// - Modification gestion reconfiguration (quand interface down)
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_MULTICAST

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

#define FICHIER_CONFIG_IGMPPROXY PATH_DIR_ETC	 "igmpproxy.conf"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: ExecReconfiguration_Multicast
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 31/03/2010 -
// Description	: Reconfigurer multicast
//=====================================================================================
void ExecReconfiguration_Multicast(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	if(TRUE == u8TestOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_MULTICAST))
	{
		printf("ExecReconfiguration_Multicast\n");
		if(MODE_NETWORK_BRIDGE == loc_ps_config->s_gene.u8_mode_network)
		{
			;	//on fait rien
		}
		else //MODE_NETWORK_ROUTER
		{
			Install_RouteForMulticast(loc_ps_config, INTERFACE_WLAN);
		}
	}
}/*ExecReconfiguration_Multicast*/


//=====================================================================================
// Fonction		: Install_RouteForMulticast
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				  <loc_u8_interface>: sur l'interface sélectionnée
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Installe la route pour multicast
//=====================================================================================
void Install_RouteForMulticast(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_interface)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];

	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_MULTICAST_MIN)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(MASK_MULTICAST)); //INIT

	printf("Install_RouteForMulticast\n");

	switch(loc_u8_interface)
	{
		case INTERFACE_BRIDGE:
			CmdSystem_Generique("route add -net %s netmask %s dev %s",
								loc_ps8_addr_ip,
								loc_ps8_addr_mask,
								NOM_INTERFACE_BRIDGE);
			break;
		case INTERFACE_WLAN:
			CmdSystem_Generique("route add -net %s netmask %s dev %s",
								loc_ps8_addr_ip,
								loc_ps8_addr_mask,
								NOM_INTERFACE_WIFI);
			//On reset le flag de reconfiguration (comme c'est fait!)
			ClearOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_MULTICAST);
			break;
		default:
			break;
	}
	
}/*Install_RouteForMulticast*/

//=====================================================================================
// Fonction		: Uninstall_RouteForMulticast
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
//				  <loc_u8_interface>: sur l'interface sélectionnée
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Désinstalle la route associée au multicast
//=====================================================================================
void Uninstall_RouteForMulticast(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_interface)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];

	printf("Uninstall_RouteForMulticast\n");

	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_MULTICAST_MIN)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(MASK_MULTICAST)); //INIT

	switch(loc_u8_interface)
	{
		case INTERFACE_BRIDGE:
			CmdSystem_Generique("route del -net %s netmask %s dev %s",
								loc_ps8_addr_ip,
								loc_ps8_addr_mask,
								NOM_INTERFACE_BRIDGE);
			break;
		case INTERFACE_WLAN:
			CmdSystem_Generique("route del -net %s netmask %s dev %s",
								loc_ps8_addr_ip,
								loc_ps8_addr_mask,
								NOM_INTERFACE_WIFI);
			break;
		default:
			break;
	}

}/*Uninstall_RouteForMulticast*/

//=====================================================================================
// Fonction		: Install_MulticastBridge
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Installe la configuration du multicast IP (bridge)
//=====================================================================================
void Install_MulticastBridge(S_STRUCT_CONFIGURATION *loc_ps_config)
{

	printf("Install_MulticastBridge\n");

	//On configure uniquement la route
	Install_RouteForMulticast(loc_ps_config, INTERFACE_BRIDGE);

}/*Install_MulticastBridge*/

//=====================================================================================
// Fonction		: Uninstall_MulticastBridge
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Désinstalle la configuration du multicast IP (bridge)
//=====================================================================================
void Uninstall_MulticastBridge(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_MulticastBridge\n");

	Uninstall_RouteForMulticast(loc_ps_config, INTERFACE_BRIDGE);
	
}/*Uninstall_MulticastBridge*/

//=====================================================================================
// Fonction		: Install_MulticastRouter
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Installe la configuration du multicast IP (router)
//=====================================================================================
void Install_MulticastRouter(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_MulticastRouter\n");

	//On configure la route
	Install_RouteForMulticast(loc_ps_config, INTERFACE_WLAN);
		
	//On execute igmpproxy
	if(TRUE == loc_ps_config->s_multicast.u8_proxy_igmp_activation)
	{
		//Création du fichier de configuration
		if(FALSE == u8CreationFichierCfgIgmpProxy(loc_ps_config))
		{
			printf("Install_MulticastRouter: u8CreationFichierCfgIgmpProxy KO \n");
		}

		//on lance le processus igmpproxy
		CmdSystem_Generique("igmpproxy %s &",
							FICHIER_CONFIG_IGMPPROXY);
	}

}/*Install_MulticastRouter*/

//=====================================================================================
// Fonction		: Uninstall_MulticastRouter
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Désinstalle la configuration du multicast IP (router)
//=====================================================================================
void Uninstall_MulticastRouter(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_MulticastRouter\n");

	//on désinstalle la route multicast
	Uninstall_RouteForMulticast(loc_ps_config, INTERFACE_WLAN);

	//on tue le processus
	CmdSystem_Generique("killall igmpproxy");
	
}/*Uninstall_MulticastRouter*/

//=====================================================================================
// Fonction		: u8CreationFichierCfgIgmpProxy
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Edition du fichier igmpproxy.conf pour le processus igmpproxy
//=====================================================================================
u8sod u8CreationFichierCfgIgmpProxy(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	FILE *	loc_pf_file;
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = TRUE;	//INIT

	if(NULL == (loc_pf_file = fopen(FICHIER_CONFIG_IGMPPROXY, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgIgmpProxy: Erreur creation fichier %s\n",FICHIER_CONFIG_IGMPPROXY));
		loc_u8_resultat = FALSE;
	}
	else
	{
		//Conversion for interface WLAN (upstream interface)
		fprintf(loc_pf_file,"phyint %s upstream ratelimit 0 threshold 1\n",NOM_INTERFACE_WIFI);
		for(loc_u16_i=0;loc_u16_i<NB_MAX_SRC_MULTICAST;loc_u16_i++)
		{
			if(TRUE == loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
			{
				fprintf(loc_pf_file,"	altnet %s/%d\n",
						ps8GetStringIp(loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_adresse_reseau),
						u8GetNumberMask(loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_masque_reseau));
				
			}
		}

		//Conversion for interface LAN (downstream interface)
		fprintf(loc_pf_file,"phyint %s downstream ratelimit 0 threshold 1\n",NOM_INTERFACE_ETHERNET);
		fprintf(loc_pf_file,"	altnet %s/%d\n",
				ps8GetStringIp(loc_ps_config->s_gene.u32_lan_adresse_ip & loc_ps_config->s_gene.u32_lan_masque_reseau),
				u8GetNumberMask(loc_ps_config->s_gene.u32_lan_masque_reseau));

		//Configuration for all others interface : disabled
		fprintf(loc_pf_file,"phyint %s disabled\n",NOM_INTERFACE_LOOPBACK);
		
		//fermeture du fichier
		fclose(loc_pf_file);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_IGMPPROXY, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgIgmpProxy*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Multicast
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Initialisation du module de cfg_multicast
//=====================================================================================
void InitModule_Cfg_Multicast(void)
{

}/*InitModule_Cfg_Multicast*/

