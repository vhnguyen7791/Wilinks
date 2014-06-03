/*========================================================================*/
/* NOM DU FICHIER  : cfg_network.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/11/2009                                           */
/* Libelle         : Principal: Configuration du réseau					  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 12/11/2009 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration hostname
// - Intégration configuration par DHCP client
//BE007 25/01/2010 CM
// - Correction bug hostapd lors de modification paramètres réseau (en particulier ath0 down)
// - Ajout configuration du "forward delay" du bridge 
//	C'est conseillé pour l'utilisation de hostapd (voir madwifi-project.org/wiki/UserDocs/HostAP) : "brctl setfd br0 0"
// - Modification gestion routage statique
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
// - Ajout information statut IP des interfaces
//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calculée dans le processus 'monitor'.
// - Correction bug appel udhcpc (client) commamde ligne trop grande
//		->toutes les options ne sont pas passées (défaut lié à la busybox, mais défaut non corrigé)
//		taille limite des options de udhcpc est de 100 caractères
//		en attendant, on diminue la taille de la commande udhcpc
// - Ajout option compilation "-Wall" + correction w@rning
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE021 24/03/2010 CM
// - Correction BUG liaison bridge-bridge
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Correction bug passerelle perdue (quand interface down) (cas avec cmd route)
// - Modification gestion reconfiguration (quand interface down)
// - Modification gestion routage par le processus bird
//	et non plus via des commandes de type "route"
// - Ajout gestion routage dynamique RIPv2
//BE026 26/04/2010 CM
// - Correction gestion passerelle via bird (qd station / router en client DHCP)
// - Correction bug désactivation client DHCP en mode station/router
//BE032 16/06/2010 CM
// - Correction commande iwconfig 'txpower' (Wifi) repasse au maximum sur A/M ou sur down/up interface Wifi
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
// - Correction configuration du paramètre bmiss (handoff)
//	uniquement prise en compte suite à un "ifconfig ath0 up"
//BE049 08/12/2010 CM
// - Correction configuration du paramètre bmiss (handoff)
//	annule correction faite dans BE047
//BE060 16/03/2011
// - Correction bug pb liaison bridge-bridge de temps en temps (adresse MAC du bridge affecté est @MAC de l'ethernet)
//		la connexion réseau ne fonctionne pas (si @MAC du bridge est celle de l'ethernet)!
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_NETWORK

//Fichier script DHCP client
#define FICHIER_SCRIPT_UDHCPC PATH_DIR_USR	 "share/udhcpc/simple.script"
//Fichier script DHCP client
#define FICHIER_LINK_SCRIPT_UDHCPC PATH_DIR_USR	 "udhcpc.script"

//Paramétrage du protocole DHCP client
#define OPTIONUDHCPC_NB_MAX_REQUETS		40 //max requetes
#define OPTIONUDHCPC_TIMEOUT_GET_LEASE	3 //secondes
#define OPTIONUDHCPC_TIMEOUT_FAILED		1 //secondes

//Forward delay du bridge
#define BRIDGE_FORWARD_DELAY	0

//Nom de l'alias non taggé
#define NOM_ALIAS_ACCES_NON_TAGGE	"ntg"

//Nom de l'alias ethernet temporaire
#define NOM_ALIAS_ETHERNET_TEMPO "tmp"

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: CmdIfconfig_Down
// Entrees		: <loc_ps8_nom_interface> : nom de l'interface à mettre DOWN
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Mise DOWN de l'interface
//=====================================================================================
void CmdIfconfig_Down(s8sod *loc_ps8_nom_interface)
{
	CmdSystem_Generique("ifconfig %s down",
						loc_ps8_nom_interface);

	if(0 == strcmp(loc_ps8_nom_interface, NOM_INTERFACE_WIFI)) //CONDITION: interface WIFI
	{
		//Ordre de reconfiguration de hostapd (si présent)
		SetOrdreReconfiguration(ORDRE_RECONFIG__HOSTAPD);

		//Ordre de reconfiguration de wpa_supplicant (si présent)
		SetOrdreReconfiguration(ORDRE_RECONFIG__WPA_SUPPLICANT);

		//Ordre de reconfiguration de la table de routage politique
		SetOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_POLICY);

		//Ordre de reconfiguration de route pour multicast
		SetOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_MULTICAST);
	}

	if(0 == strcmp(loc_ps8_nom_interface, NOM_INTERFACE_ETHERNET)) //CONDITION: interface ETHERNET
	{
		//Ordre de reconfiguration de la table de routage politique
		SetOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_POLICY);
	}
	
}/*CmdIfconfig_Down*/

//=====================================================================================
// Fonction		: CmdIfconfig_Up
// Entrees		: <loc_ps8_nom_interface> : nom de l'interface à mettre UP
//				: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Mise UP de l'interface
//=====================================================================================
void CmdIfconfig_Up(s8sod *loc_ps8_nom_interface, S_STRUCT_CONFIGURATION *loc_ps_config)
{
	CmdSystem_Generique("ifconfig %s up",
						loc_ps8_nom_interface);

	if(0 == strcmp(loc_ps8_nom_interface, NOM_INTERFACE_WIFI)) //CONDITION: interface WIFI
	{
		//On reconfigure la puissance d'émission
		Install_TxPowerWifi(loc_ps_config);
	}
	
}/*CmdIfconfig_Up*/


//=====================================================================================
// Fonction		: CmdIfconfigEthernetAliasTempo_Down
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Mise DOWN de l'interface temporaire (alias)
//=====================================================================================
void CmdIfconfigEthernetAliasTempo_Down(void)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	
	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	
	CmdSystem_Generique("ifconfig %s:%s %s down",
						NOM_INTERFACE_ETHERNET,
					    NOM_ALIAS_ETHERNET_TEMPO,
					    loc_ps8_addr_ip);

	CmdSystem_Generique("ifconfig %s down",
						NOM_INTERFACE_ETHERNET);
	
}/*CmdIfconfigEthernetAliasTempo_Down*/

//=====================================================================================
// Fonction		: CmdIfconfigEthernetAliasTempo_Up
// Entrees		: <loc_u32_adresse_ip> : adresse IP
//				: <loc_u32_mask> : masque de sous-reseau
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Mise UP de l'interface temporaire (alias)
//=====================================================================================
void CmdIfconfigEthernetAliasTempo_Up(u32sod loc_u32_adresse_ip, u32sod loc_u32_mask)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];


	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	CmdSystem_Generique("ifconfig %s %s",
						NOM_INTERFACE_ETHERNET,
						loc_ps8_addr_ip);
	
						strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_u32_adresse_ip));
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_u32_mask));
	CmdSystem_Generique("ifconfig %s:%s %s netmask %s up",
						NOM_INTERFACE_ETHERNET,
					    NOM_ALIAS_ETHERNET_TEMPO,
					    loc_ps8_addr_ip,
					    loc_ps8_addr_mask);

}/*CmdIfconfigEthernetAliasTempo_Up*/

//=====================================================================================
// Fonction		: Install_Hostname
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 06/01/2010 -
// Description	: Installe la configuration du hostname
//=====================================================================================
void Install_Hostname(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Install_Hostname\n");
	if(strlen(loc_ps_config->s_gene.ps8_hostname) >= LG_MIN_HOSTNAME) //CONDITION: chaine non vide
	{
		CmdSystem_Generique("hostname %s",loc_ps_config->s_gene.ps8_hostname);
	}

}/*Install_Hostname*/

//=====================================================================================
// Fonction		: Install_BridgeVlan
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 23/03/2010 -
// Description	: Installe la configuration VLAN (bridge)
//=====================================================================================
void Install_BridgeVlan(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_nom_interf_vlan[10+1];
	s8sod loc_ps8_nom_interf_novlan[10+1];
	u8sod	loc_pu8_add_mac[ETHER_ADDR_LEN]; //Adresse MAC de l'interface

	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_nom_interf_vlan, ""); //INIT
	strcpy(loc_ps8_nom_interf_novlan, ""); //INIT
	memset(loc_pu8_add_mac, 0, ETHER_ADDR_LEN); //INIT
	
	if(TRUE == loc_ps_config->s_gene.u8_vlan_autoriser) //CONDITION: VLAN autorisé
	{
		printf("Install_BridgeVlan\n");
		
		//Détermination nom interface (vlan et non taggé)
		strcpy(loc_ps8_nom_interf_vlan, NOM_INTERFACE_ETHERNET); //coté vlan
		strcpy(loc_ps8_nom_interf_novlan, NOM_INTERFACE_WIFI); //coté non vlan
		
		//Création d'un alias pour conserver accès non taggé (si autorisé)
		if(TRUE == loc_ps_config->s_gene.u8_vlan_interface_notag) //CONDITION: accès non taggé autorisé
		{
			strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_vlan_notag_adresse_ip)); //INIT
			strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_ps_config->s_gene.u32_vlan_notag_masque_reseau)); //INIT
			CmdSystem_Generique("ifconfig %s:%s %s netmask %s",
								loc_ps8_nom_interf_vlan,
								NOM_ALIAS_ACCES_NON_TAGGE,
								loc_ps8_addr_ip,
								loc_ps8_addr_mask);
		}

		//Création du VLAN
		CmdSystem_Generique("vconfig add %s %d",loc_ps8_nom_interf_vlan,loc_ps_config->s_gene.u16_vlan_id);
		//Activation de l'interface vlan
		CmdSystem_Generique("ifconfig %s.%d %s",loc_ps8_nom_interf_vlan,loc_ps_config->s_gene.u16_vlan_id,ps8GetStringIp(ADRESSE_IP_NULLE));
		

		//Création du bridge
		printf("Install_BridgeVlan: Add interface %s.%d to the bridge\n",loc_ps8_nom_interf_vlan,loc_ps_config->s_gene.u16_vlan_id);
		CmdSystem_Generique("brctl addif %s %s.%d",NOM_INTERFACE_BRIDGE,loc_ps8_nom_interf_vlan,loc_ps_config->s_gene.u16_vlan_id);
		printf("Install_BridgeVlan: Add interface %s to the bridge\n",loc_ps8_nom_interf_novlan);
		//CmdSystem_Generique("iw dev %s set 4addr on", loc_ps8_nom_interf_novlan);//Add by VuHai      
		CmdSystem_Generique("brctl addif %s %s",NOM_INTERFACE_BRIDGE,loc_ps8_nom_interf_novlan);
		switch(loc_ps_config->s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_STATION:
			case MODE_RADIO_MODEM_ACCESS_POINT:
				//On force l'adresse MAC de l'interface Wifi sur le l'interface bridge (car sinon pb liaison bridge-bridge)
				if(TRUE == u8GetMacAddress(NOM_INTERFACE_WIFI, loc_pu8_add_mac))
				{
					CmdSystem_Generique("ifconfig %s hw ether %s",
										NOM_INTERFACE_BRIDGE,
										ps8GetChAddressMac(loc_pu8_add_mac));
				}
				break;
			case MODE_RADIO_MODEM_MONITOR:
			default:
				//On force l'adresse MAC de l'interface Ethernet sur le l'interface bridge
				if(TRUE == u8GetMacAddress(NOM_INTERFACE_ETHERNET, loc_pu8_add_mac))
				{
					CmdSystem_Generique("ifconfig %s hw ether %s",
										NOM_INTERFACE_BRIDGE,
										ps8GetChAddressMac(loc_pu8_add_mac));
				}
				break;
		}
	}
}/*Install_BridgeVlan*/

//=====================================================================================
// Fonction		: Uninstall_BridgeVlan
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 23/03/2010 -
// Description	: Désinstalle la configuration VLAN (bridge)
//=====================================================================================
void Uninstall_BridgeVlan(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_nom_interf_vlan[10+1];
	s8sod loc_ps8_nom_interf_novlan[10+1];

	strcpy(loc_ps8_nom_interf_vlan, ""); //INIT
	strcpy(loc_ps8_nom_interf_novlan, ""); //INIT

	if(TRUE == loc_ps_config->s_gene.u8_vlan_autoriser) //CONDITION: VLAN autorisé
	{
		printf("Uninstall_BridgeVlan\n");

		//Détermination nom interface (vlan et non taggé)
		strcpy(loc_ps8_nom_interf_vlan, NOM_INTERFACE_ETHERNET); //coté vlan
		strcpy(loc_ps8_nom_interf_novlan, NOM_INTERFACE_WIFI); //coté non vlan

		//Suppression d'un alias pour conserver accès non taggé (si autorisé)
		if(TRUE == loc_ps_config->s_gene.u8_vlan_interface_notag) //CONDITION: accès non taggé autorisé
		{
			CmdSystem_Generique("ifconfig %s:%s down",
								loc_ps8_nom_interf_vlan,
								NOM_ALIAS_ACCES_NON_TAGGE);
		}

		
		//Suppression du VLAN
		CmdSystem_Generique("vconfig rem %s.%d",loc_ps8_nom_interf_vlan,loc_ps_config->s_gene.u16_vlan_id);
		
		//Delete interfaces to the bridge
		CmdSystem_Generique("brctl delif %s %s.%d",NOM_INTERFACE_BRIDGE,loc_ps8_nom_interf_vlan,loc_ps_config->s_gene.u16_vlan_id);
		CmdSystem_Generique("brctl delif %s %s",NOM_INTERFACE_BRIDGE,loc_ps8_nom_interf_novlan);
		
	}
	
}/*Uninstall_BridgeVlan*/

//=====================================================================================
// Fonction		: Install_NetworkBridge
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du réseau bridge
//=====================================================================================
void Install_NetworkBridge(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_option_udhcpc[50+1];
	u8sod	loc_pu8_add_mac[ETHER_ADDR_LEN]; //Adresse MAC de l'interface

	strcpy(loc_ps8_option_udhcpc, ""); //INIT

	strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_adresse_ip)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_masque_reseau)); //INIT
	memset(loc_pu8_add_mac, 0, ETHER_ADDR_LEN); //INIT
	
	printf("Install_NetworkBridge\n");

	RazStatutIP_Interfaces(); //RAZ
	
	//Zero IP the interfaces (shut down)
	printf("Install_NetworkBridge: Zero IP the interfaces (shut down)\n");
	CmdIfconfig_Down(NOM_INTERFACE_ETHERNET);
	CmdIfconfig_Down(NOM_INTERFACE_WIFI);
	//Zero IP the interfaces (UP)
	printf("Install_NetworkBridge: Zero IP the interfaces (up)\n");
	CmdSystem_Generique("ifconfig %s %s",NOM_INTERFACE_ETHERNET,ps8GetStringIp(ADRESSE_IP_NULLE));
	CmdSystem_Generique("ifconfig %s %s",NOM_INTERFACE_WIFI,ps8GetStringIp(ADRESSE_IP_NULLE));
	
	//Create the bridge interface
	printf("Install_NetworkBridge: Create the bridge interface\n");
	CmdSystem_Generique("brctl addbr %s",NOM_INTERFACE_BRIDGE);

	//Add interfaces to the bridge
	if(TRUE == loc_ps_config->s_gene.u8_vlan_autoriser) //CONDITION: VLAN autorisé
	{
		Install_BridgeVlan(loc_ps_config);
	}
	else //CONDITION: VLAN non autorisé
	{
		printf("Install_NetworkBridge: Add interface %s to the bridge\n",NOM_INTERFACE_ETHERNET);
		CmdSystem_Generique("brctl addif %s %s",NOM_INTERFACE_BRIDGE,NOM_INTERFACE_ETHERNET);
		printf("Install_NetworkBridge: Add interface %s to the bridge\n",NOM_INTERFACE_WIFI);
		//CmdSystem_Generique("iw dev %s set 4addr on",NOM_INTERFACE_WIFI);//Add by VuHai
		CmdSystem_Generique("brctl addif %s %s",NOM_INTERFACE_BRIDGE,NOM_INTERFACE_WIFI);
		switch(loc_ps_config->s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_STATION:
			case MODE_RADIO_MODEM_ACCESS_POINT:
				//On force l'adresse MAC de l'interface Wifi sur le l'interface bridge (car sinon pb liaison bridge-bridge)
				if(TRUE == u8GetMacAddress(NOM_INTERFACE_WIFI, loc_pu8_add_mac))
				{
					CmdSystem_Generique("ifconfig %s hw ether %s",
										NOM_INTERFACE_BRIDGE,
										ps8GetChAddressMac(loc_pu8_add_mac));
				}
				break;
			case MODE_RADIO_MODEM_MONITOR:
			default:
				//On force l'adresse MAC de l'interface Ethernet sur le l'interface bridge
				if(TRUE == u8GetMacAddress(NOM_INTERFACE_ETHERNET, loc_pu8_add_mac))
				{
					CmdSystem_Generique("ifconfig %s hw ether %s",
										NOM_INTERFACE_BRIDGE,
										ps8GetChAddressMac(loc_pu8_add_mac));
				}
				break;
		}
	}
	
	//Zero IP the interfaces (up) (on réinssiste au cas où)
	CmdIfconfig_Up(NOM_INTERFACE_ETHERNET, loc_ps_config);
	CmdIfconfig_Up(NOM_INTERFACE_WIFI, loc_ps_config);

	//Configuration du forward delay conseillé pour l'utilisation de hostapd (voir madwifi-project.org/wiki/UserDocs/HostAP)
	CmdSystem_Generique("brctl setfd %s %d",NOM_INTERFACE_BRIDGE, BRIDGE_FORWARD_DELAY);
	
	
	//Configure IP parameters of the bridge
	if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_bridge_mode_ip)
	{
		printf("Install_NetworkBridge: setup IP static\n");
		//on configure l'adresse IP du bridge
		CmdIfconfig_Down(NOM_INTERFACE_BRIDGE);
		CmdSystem_Generique("ifconfig %s %s netmask %s",
							NOM_INTERFACE_BRIDGE,
							loc_ps8_addr_ip,
							loc_ps8_addr_mask);
		//Puis up du bridge
		CmdIfconfig_Up(NOM_INTERFACE_BRIDGE, loc_ps_config);
		
		printf("MODE_IP_STATIQUE: ifconfig %s %s netmask %s down\n",
			   NOM_INTERFACE_BRIDGE,
			   loc_ps8_addr_ip,
			   loc_ps8_addr_mask);

		//Add gateway
		if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_bridge_gateway)//CONDITION: passerelle activée
		{
			CmdSystem_Generique("route add default gw %s dev %s",
								ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_gateway),
							    NOM_INTERFACE_BRIDGE);
		}
		
		u8_bridge_autostatut_ip = STATUT_IP__STATIC;
	}
	else //MODE_IP_DHCP_CLIENT
	{
		printf("Install_NetworkBridge: setup IP DHCP\n");
		CmdIfconfig_Up(NOM_INTERFACE_BRIDGE, loc_ps_config);

		strcpy(loc_ps8_option_udhcpc, ""); //RAZ
		if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip)
		{
			strcat(loc_ps8_option_udhcpc, "-n "); //on sort si echec au bout du temps spécifié
		}

		if(strlen(loc_ps_config->s_gene.ps8_hostname) >= LG_MIN_HOSTNAME) //CONDITION: chaine non vide
		{
			//La taille max de la commande udhcpc ne doit pas dépassée 100 caractères
			CmdSystem_Generique("udhcpc -i %s -s %s -p %s -H %s -t %d -T %d -A %d -a -q %s &",
								NOM_INTERFACE_BRIDGE,
								FICHIER_LINK_SCRIPT_UDHCPC,
								FICHIER_VAR_UDHCPC_PID,
								loc_ps_config->s_gene.ps8_hostname,
								OPTIONUDHCPC_NB_MAX_REQUETS,
								OPTIONUDHCPC_TIMEOUT_GET_LEASE,
								OPTIONUDHCPC_TIMEOUT_FAILED,
							    loc_ps8_option_udhcpc);
		}
		else
		{
			//La taille max de la commande udhcpc ne doit pas dépassée 100 caractères
			CmdSystem_Generique("udhcpc -i %s -s %s -p %s -t %d -T %d -A %d -a -q %s &",
								NOM_INTERFACE_BRIDGE,
								FICHIER_LINK_SCRIPT_UDHCPC,
								FICHIER_VAR_UDHCPC_PID,
								OPTIONUDHCPC_NB_MAX_REQUETS,
								OPTIONUDHCPC_TIMEOUT_GET_LEASE,
								OPTIONUDHCPC_TIMEOUT_FAILED,
							    loc_ps8_option_udhcpc);
		}
		u8_start_installDHCPClient = TRUE;	//START INSTALLATION DHCP CLIENT
	}

	//Spanning Tree Protocol
	if(TRUE == loc_ps_config->s_gene.u8_bridge_stp)
	{
		CmdSystem_Generique("brctl stp %s on",
							NOM_INTERFACE_BRIDGE);
	}
	else
	{
		CmdSystem_Generique("brctl stp %s off",
							NOM_INTERFACE_BRIDGE);
	}
	
	if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_bridge_mode_ip)
	{
		//Multicast
		Install_MulticastBridge(loc_ps_config);
	}//MODE_IP_DHCP_CLIENT: configuré dès réception de l'adresse IP

	//Hostname
	Install_Hostname(loc_ps_config);

	printf("***** Install_WdsWifi in Install_NetworkBridge *********\n");
	//Wds
	Install_WdsWifi(loc_ps_config);//Modif by VuHai to ignore
	//error used by driver Aquila

}/*Install_NetworkBridge*/

//=====================================================================================
// Fonction		: Uninstall_NetworkBridge
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du réseau bridge
//=====================================================================================
void Uninstall_NetworkBridge(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_NetworkBridge\n");

	//Shut down the bridge interface
	CmdIfconfig_Down(NOM_INTERFACE_BRIDGE);

	//Delete interfaces to the bridge
	if(TRUE == loc_ps_config->s_gene.u8_vlan_autoriser) //CONDITION: VLAN autorisé
	{
		Uninstall_BridgeVlan(loc_ps_config);
	}
	else //CONDITION: VLAN non autorisé
	{
		CmdSystem_Generique("brctl delif %s %s",NOM_INTERFACE_BRIDGE,NOM_INTERFACE_ETHERNET);
		CmdSystem_Generique("brctl delif %s %s",NOM_INTERFACE_BRIDGE,NOM_INTERFACE_WIFI);
	}

	//Delete the bridge interface
	CmdSystem_Generique("brctl delbr %s",NOM_INTERFACE_BRIDGE);

	//Delete gateway
	if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_bridge_gateway)//CONDITION: passerelle activée
	{
		CmdSystem_Generique("route del default gw %d",
						   ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_gateway));
	}

	//Disabled DHCP client
	if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_bridge_mode_ip)
	{
		CmdSystem_Generique("killall udhcpc");
		u8_start_installDHCPClient = FALSE;	//FIN INSTALLATION DHCP CLIENT
		RazStatutIP_Interfaces(); //RAZ
	}

	//Multicast
	Uninstall_MulticastBridge(loc_ps_config);

}/*Uninstall_NetworkBridge*/

//=====================================================================================
// Fonction		: Install_NetworkRouter
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du réseau router
//=====================================================================================
void Install_NetworkRouter(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_option_udhcpc[50+1];

	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_option_udhcpc, ""); //INIT

	printf("Install_NetworkRouter\n");
	
	RazStatutIP_Interfaces(); //RAZ
	
	//Interface Ethernet
	strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_lan_adresse_ip)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_ps_config->s_gene.u32_lan_masque_reseau)); //INIT
	CmdSystem_Generique("ifconfig %s %s netmask %s",
						NOM_INTERFACE_ETHERNET,
						loc_ps8_addr_ip,
						loc_ps8_addr_mask);

	//Interface Wifi
	if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
	{
		strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_wlan_adresse_ip)); //INIT
		strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_ps_config->s_gene.u32_wlan_masque_reseau)); //INIT
		CmdSystem_Generique("ifconfig %s %s netmask %s",
							NOM_INTERFACE_WIFI,
							loc_ps8_addr_ip,
							loc_ps8_addr_mask);

		u8_wlan_autostatut_ip = STATUT_IP__STATIC;
	}
	else //MODE_IP_DHCP_CLIENT
	{
		printf("Install_NetworkRouter: setup IP DHCP\n");

		strcpy(loc_ps8_option_udhcpc, ""); //RAZ
		if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip)
		{
			strcat(loc_ps8_option_udhcpc, "-n "); //on sort si echec au bout du temps spécifié
		}
		
		if(strlen(loc_ps_config->s_gene.ps8_hostname) >= LG_MIN_HOSTNAME) //CONDITION: chaine non vide
		{
			//La taille max de la commande udhcpc ne doit pas dépassée 100 caractères
			CmdSystem_Generique("udhcpc -i %s -s %s -p %s -H %s -t %d -T %d -A %d -a -q %s &",
								NOM_INTERFACE_WIFI,
								FICHIER_LINK_SCRIPT_UDHCPC,
								FICHIER_VAR_UDHCPC_PID,
								loc_ps_config->s_gene.ps8_hostname,
								OPTIONUDHCPC_NB_MAX_REQUETS,
								OPTIONUDHCPC_TIMEOUT_GET_LEASE,
								OPTIONUDHCPC_TIMEOUT_FAILED,
								loc_ps8_option_udhcpc);
		}
		else
		{
			//La taille max de la commande udhcpc ne doit pas dépassée 100 caractères
			CmdSystem_Generique("udhcpc -i %s -s %s -p %s -t %d -T %d -A %d -a -q %s &",
								NOM_INTERFACE_WIFI,
								FICHIER_LINK_SCRIPT_UDHCPC,
								FICHIER_VAR_UDHCPC_PID,
								OPTIONUDHCPC_NB_MAX_REQUETS,
								OPTIONUDHCPC_TIMEOUT_GET_LEASE,
								OPTIONUDHCPC_TIMEOUT_FAILED,
								loc_ps8_option_udhcpc);
		}
		u8_start_installDHCPClient = TRUE;	//START INSTALLATION DHCP CLIENT
	}

	if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
	{
		//Installation Routage statique + dynamique
		Install_Bird(loc_ps_config, loc_ps_config->s_gene.u32_wlan_adresse_ip, loc_ps_config->s_gene.u32_wlan_masque_reseau, loc_ps_config->s_gene.u32_wlan_gateway);
		
		//Routage politique
		Install_RulesForPolicyRouting(loc_ps_config);
		//Multicast
		Install_MulticastRouter(loc_ps_config);
	}
	//en MODE_IP_DHCP_CLIENT: les routes seront configurées uniquement dès que l'adresse IP sera configurée

	//Installation iptables pour le routage politique
	Install_IptablesMangleForPolicyRouting(loc_ps_config);
	
	
	//Hostname
	Install_Hostname(loc_ps_config);

	
	//Wds
	Install_WdsWifi(loc_ps_config);
	
}/*Install_NetworkRouter*/

//=====================================================================================
// Fonction		: Uninstall_NetworkRouter
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du réseau router
//=====================================================================================
void Uninstall_NetworkRouter(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_NetworkRouter\n");

	//Shut down Interface Ethernet
	CmdIfconfig_Down(NOM_INTERFACE_ETHERNET);
	//Shut down Interface Wifi
	CmdIfconfig_Down(NOM_INTERFACE_WIFI);

	//Disabled DHCP client
	if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_wlan_mode_ip)
	{
		CmdSystem_Generique("killall udhcpc");
		u8_start_installDHCPClient = FALSE;	//FIN INSTALLATION DHCP CLIENT
		RazStatutIP_Interfaces(); //RAZ
	}

	//Désinstallation Routage statique + dynamique
	Uninstall_Bird(loc_ps_config);
	

	//Routage politique
	Uninstall_PolicyRouting(loc_ps_config);
	
	//Multicast
	Uninstall_MulticastRouter(loc_ps_config);

}/*Uninstall_NetworkRouter*/

//=====================================================================================
// Fonction		: ExecReconfiguration_Routage
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 25/01/2010 -
// Description	: Reconfigurer la table de routage
//=====================================================================================
void ExecReconfiguration_Routage(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	if(TRUE == u8TestOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_POLICY))
	{
		Install_RulesForPolicyRouting(loc_ps_config);
	}
}/*ExecReconfiguration_Routage*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: RazStatutIP_Interfaces
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/02/2010 -
// Description	: Remise à zéro du statut des interfaces
//=====================================================================================
void RazStatutIP_Interfaces(void)
{
	u8_wlan_autostatut_ip = STATUT_IP__UNDEFINED;	//RAZ
	u8_bridge_autostatut_ip = STATUT_IP__UNDEFINED;	//RAZ
}/*RazStatutIP_Interfaces*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Network
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Initialisation du module de cfg_network
//=====================================================================================
void InitModule_Cfg_Network(void)
{
	u8_start_installDHCPClient = FALSE; //INIT
	u8_wlan_autostatut_ip = STATUT_IP__UNDEFINED;	//INIT
	u8_bridge_autostatut_ip = STATUT_IP__UNDEFINED;	//INIT

	//On crée un fichier lien udhcpc (comme la taille de la ligne de commande est limitée à 100 caractères)
	CmdSystem_Generique("ln -sf %s %s",
						FICHIER_SCRIPT_UDHCPC,
						FICHIER_LINK_SCRIPT_UDHCPC);

	
}/*InitModule_Cfg_Network*/

