/*========================================================================*/
/* NOM DU FICHIER  : cfg_bird.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 20/04/2010                                           */
/* Libelle         : Principal: Configuration de bird					  */
/* Projet          : WRM100                                               */
/* Indice          : BE048                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 20/04/2010 CM
// - CREATION
// - Modification gestion routage par le processus bird
//	et non plus via des commandes de type "route"
//BE026 26/04/2010 CM
// - Correction gestion passerelle via bird (qd station / router en client DHCP)
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		=> ajout permission root only pour fichiers de configuration
//BE048 29/11/2010 CM
// - Correction routage statique vers un HOST
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_BIRD

#define DEBUG_BIRD	0	//0:desactivé 1:activé
#if DEBUG_BIRD
#warning "DEBUG BIRD ACTIVE"
#endif

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"

#define FICHIER_CONFIG_BIRD PATH_DIR_ETC	 "bird.conf"
#define FICHIER_LOG_BIRD PATH_DIR_VAR	 "log/bird.log"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Bird
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_u32_wlan_adr_ip> : adresse IP de l'accès WLAN
//				: <loc_u32_wlan_mask> : Masque sous-réseau de l'accès WLAN
//				: <loc_u32_wlan_gateway> : Passerelle de l'accès WLAN
// Sortie		: rien
// Auteur		: CM - 20/04/2010 -
// Description	: Installe bird
//=====================================================================================
void Install_Bird(S_STRUCT_CONFIGURATION *loc_ps_config, u32sod loc_u32_wlan_adr_ip, u32sod loc_u32_wlan_mask, u32sod loc_u32_wlan_gateway)
{
	printf("Install_Bird\n");

	//Création du fichier de configuration
	if(FALSE == u8CreationFichierCfgBird(loc_ps_config, loc_u32_wlan_adr_ip, loc_u32_wlan_mask, loc_u32_wlan_gateway))
	{
		printf("Install_Bird: u8CreationFichierCfgBird KO \n");
	}

	//on lance en deamon
#if DEBUG_BIRD
	CmdSystem_Generique("bird -c %s -d &",
						FICHIER_CONFIG_BIRD);
#else
	CmdSystem_Generique("bird -c %s &",
						FICHIER_CONFIG_BIRD);
#endif
	
}/*Install_Bird*/

//=====================================================================================
// Fonction		: Uninstall_Bird
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 20/04/2010 -
// Description	: Désinstalle bird
//=====================================================================================
void Uninstall_Bird(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	printf("Uninstall_Bird\n");

	//on tue le processus
	CmdSystem_Generique("killall bird");

}/*Uninstall_Bird*/

//=====================================================================================
// Fonction		: u8CreationFichierCfgBird
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u32_wlan_adr_ip> : adresse IP de l'accès WLAN
//				: <loc_u32_wlan_mask> : Masque sous-réseau de l'accès WLAN
//				: <loc_u32_wlan_gateway> : Passerelle de l'accès WLAN
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 20/04/2010 -
// Description	: Edition du fichier bird.conf pour le processus bird
//=====================================================================================
u8sod u8CreationFichierCfgBird(S_STRUCT_CONFIGURATION *loc_ps_config, u32sod loc_u32_wlan_adr_ip, u32sod loc_u32_wlan_mask, u32sod loc_u32_wlan_gateway)
{
	FILE *	loc_pf_file;
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_gw[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_nom_interface[20+1];
	s8sod loc_ps8_type_via[50+1];
	
	loc_u8_resultat = TRUE;	//INIT
	strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_mask, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_gw, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_nom_interface, ""); //INIT
	strcpy(loc_ps8_type_via, ""); //INIT

	if(NULL == (loc_pf_file = fopen(FICHIER_CONFIG_BIRD, "wt")))
	{
		MACRO_PRINTF(("u8CreationFichierCfgBird: Erreur creation fichier %s\n",FICHIER_CONFIG_BIRD));
		loc_u8_resultat = FALSE;
	}
	else
	{
#if DEBUG_BIRD
		fprintf(loc_pf_file,"log \"%s\" all;\n",FICHIER_LOG_BIRD);
#endif

		// This pseudo-protocol performs synchronization between BIRD's routing
		// tables and the kernel. If your kernel supports multiple routing tables
		// (as Linux 2.2.x does), you can run multiple instances of the kernel
		// protocol and synchronize different kernel tables with different BIRD tables.
		fprintf(loc_pf_file,"protocol kernel {\n");
//		fprintf(loc_pf_file,"	persist;\n");
//		fprintf(loc_pf_file,"	learn;\n");			//Learn all alien routes from the kernel
		//pour que les routes soient supprimées (si elle disparaissent)
		fprintf(loc_pf_file,"	scan time 20;\n");	//Scan kernel routing table every 20 seconds
			fprintf(loc_pf_file,"	export all;\n");	//Default is export none
		fprintf(loc_pf_file,"} \n");//fin protocol kernel

		//This pseudo-protocol watches all interface up/down events.
	    fprintf(loc_pf_file,"protocol device {\n");
//		fprintf(loc_pf_file,"	scan time 10; \n");	//Scan interfaces every 10 seconds
		fprintf(loc_pf_file,"}\n");//fin protocol device

		//Configuration du RIP
		if(TRUE == loc_ps_config->s_ip_routing.u8_ripv2_activation)
		{
			fprintf(loc_pf_file,"protocol rip MyRIP {\n");

			fprintf(loc_pf_file,"	export all;\n");
			fprintf(loc_pf_file,"	import all;\n");
#if DEBUG_BIRD
			fprintf(loc_pf_file,"	debug all;\n");
#endif
			fprintf(loc_pf_file,"	port %d;\n",PORT_UDP__RIP);

			if(TRUE == loc_ps_config->s_ip_routing.pu8_rip_interface_used[RIP_INTERF_LAN])
			{
				fprintf(loc_pf_file,"	interface \"%s\"{mode multicast;};\n",NOM_INTERFACE_ETHERNET);
			}
			else
			{
				fprintf(loc_pf_file,"	interface \"%s\"{mode quiet;mode nolisten;};\n",NOM_INTERFACE_ETHERNET);
			}

			if(TRUE == loc_ps_config->s_ip_routing.pu8_rip_interface_used[RIP_INTERF_WLAN])
			{
				fprintf(loc_pf_file,"	interface \"%s\"{mode multicast;};\n",NOM_INTERFACE_WIFI);
			}
			else
			{
				fprintf(loc_pf_file,"	interface \"%s\"{mode quiet;mode nolisten;};\n",NOM_INTERFACE_WIFI);
			}
			
			fprintf(loc_pf_file,"	honor always;\n");
			
			switch(loc_ps_config->s_ip_routing.u8_rip_authentification)
			{
				case RIP_AUTHENTICATION_PLAIN_TEXT:
					fprintf(loc_pf_file,"	authentication plaintext;\n");
					break;
				case RIP_AUTHENTICATION_MD5:
					fprintf(loc_pf_file,"	authentication md5;\n");
					break;
				case RIP_AUTHENTICATION_NONE:
				default:
					fprintf(loc_pf_file,"	authentication none;\n");
					break;
			}
			if(RIP_AUTHENTICATION_NONE != loc_ps_config->s_ip_routing.u8_rip_authentification)
			{
				fprintf(loc_pf_file,"	password \"%s\";\n",loc_ps_config->s_ip_routing.ps8_rip_password);
			}
			fprintf(loc_pf_file,"}\n");//fin protocol rip MyRIP
		}

		//Configuration du routage
		fprintf(loc_pf_file,"protocol static {\n");
		fprintf(loc_pf_file,"	export all;\n");
		fprintf(loc_pf_file,"	import all;\n");
#if DEBUG_BIRD
		fprintf(loc_pf_file,"	debug { states, routes, filters, interfaces, events, packets }; \n");
		fprintf(loc_pf_file,"	debug all; \n");
#endif
		
		//Routage passerelle
		if(ADRESSE_IP_NULLE != loc_u32_wlan_gateway)//CONDITION: passerelle activée
		{
			fprintf(loc_pf_file,"	route 0.0.0.0/0 via %s;\n",
					ps8GetStringIp(loc_u32_wlan_gateway));
		}

		//Routage multicast
		//ne peut pas etre configuré avec bird car erreur suivante:
		//->Ignoring bogus route 224.0.0.0/4 received via static1
		//-> <TRACE> static1 > invalid 224.0.0.0/4 dev ath0
#if 0		
		strcpy(loc_ps8_addr_ip, ps8GetStringIp(ADRESSE_MULTICAST_MIN)); //INIT
		strcpy(loc_ps8_addr_mask, ps8GetStringIp(MASK_MULTICAST)); //INIT
		fprintf(loc_pf_file,"	route %s:%s via \"%s\";\n",
				loc_ps8_addr_ip,
				loc_ps8_addr_mask,
				NOM_INTERFACE_WIFI);
#endif
		
		//Table de routage statique
		for(loc_u16_i=0;loc_u16_i<NB_MAX_ROUTES_IP_STATIC;loc_u16_i++)
		{
			if(TRUE == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
			{
				strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_ip));
				strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_mask));
				strcpy(loc_ps8_addr_gw, ps8GetStringIp(loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_gateway_ip));
				switch(loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_interface)
				{
					case INTERFACE_LAN:
						strcpy(loc_ps8_nom_interface, NOM_INTERFACE_ETHERNET);
						break;
					case INTERFACE_WLAN:
						strcpy(loc_ps8_nom_interface, NOM_INTERFACE_WIFI);
						break;
					default:
						break;
				}

				//Détermination de la méthode "via ...": soit par interface , soit par passerelle
				if(INTERFACE_AUTOMATIQUE == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_interface)
				{
					strcpy(loc_ps8_type_via, loc_ps8_addr_gw);	//par la passerelle
				}
				else
				{
					sprintf(loc_ps8_type_via, "\"%s\"",loc_ps8_nom_interface); //par l'interface
				}
				

				//on ajoute la route
				if(MASK_RESEAU_SUR_32 == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_mask) //CONDITION: route vers un HOST
				{
					fprintf(loc_pf_file,"	route %s:%s via %s;\n",
							loc_ps8_addr_ip,
							loc_ps8_addr_mask,
							loc_ps8_type_via);
				}
				else //CONDITION: route vers un SOUS-RESEAU
				{
					if(0 == (loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_ip & (u32sod)(~loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_mask))
					  )//CONDITION: l'adresse de destination est un sous-reseau
					{
						fprintf(loc_pf_file,"	route %s:%s via %s;\n",
								loc_ps8_addr_ip,
								loc_ps8_addr_mask,
								loc_ps8_type_via);
					}
					else //CONDITION: l'adresse de destination est un host
					{
						printf("u8CreationFichierCfgBird: route %d netmask invalide\n",loc_u16_i);
					}
				}
			}
		}
		fprintf(loc_pf_file,"}\n");//fin protocol static
		

		//fermeture du fichier
		fclose(loc_pf_file);

		//Fixe permission du fichier
		u8CmdSystem_ChmodFile(FICHIER_CONFIG_BIRD, CHMOD_FILE_ROOT_751);
		
	}

	return loc_u8_resultat;
}/*u8CreationFichierCfgBird*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Bird
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 20/04/2010 -
// Description	: Initialisation du module de cfg_bird
//=====================================================================================
void InitModule_Cfg_Bird(void)
{
	
}/*InitModule_Cfg_Bird*/

