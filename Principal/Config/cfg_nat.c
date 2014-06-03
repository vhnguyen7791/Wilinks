/*========================================================================*/
/* NOM DU FICHIER  : cfg_nat.c	 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/02/2010                                           */
/* Libelle         : Principal: Configuration du NAT					  */
/* Projet          : WRM100                                               */
/* Indice          : BE049                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE010 11/02/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE049 08/12/2010 CM
// - Ajout affichage des commandes dans la page de Configuration - NAT
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_NAT


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

const s8sod PS8_CHAINE_PROTOCOLE_NAT_IPTABLES[NB_MAX_NAT_PROTOCOLES] [10+1] =
{
	"",			//NAT_PROTOCOLE_NON_SELECTIONNE
	"udp",		//NAT_PROTOCOLE_UDP
	"tcp",		//NAT_PROTOCOLE_TCP
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_Nat
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_u32_adr_ip_public_default> : adresse IP publique par défaut
//				: <loc_u32_mask_ip_public_default> : adresse IP publique par défaut
// Sortie		: rien
// Auteur		: CM - 11/02/2010 -
// Description	: Installe NAT
//=====================================================================================
void Install_Nat(S_STRUCT_CONFIGURATION *loc_ps_config, u32sod loc_u32_adr_ip_public_default, u32sod loc_u32_mask_ip_public_default)
{
	u16sod	loc_u16_i;
	s8sod loc_ps8_addr_ip_privee[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_ip_public[MAX_LG_FORMAT_ADRESSE_IP+1];

	printf("Install_Nat ip=0x%08lX/0x%08lX\n", loc_u32_adr_ip_public_default, loc_u32_mask_ip_public_default);

	strcpy(loc_ps8_addr_ip_privee, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_ip_public, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT

	if(TRUE == loc_ps_config->s_nat.u8_nat_activation) //CONDITION: NAT ACTIVE
	{
		//Définition du comportement par défaut pour les chaines de la table filter
		// -> On autorise les entrées / sorties , et on bloque le routage
		CmdSystem_Generique("iptables -P INPUT ACCEPT");
		CmdSystem_Generique("iptables -P OUTPUT ACCEPT");
		CmdSystem_Generique("iptables -P FORWARD DROP");

		//Supression les chaînes de la table filter (INPUT, FORWARD et OUTPUT)
		CmdSystem_Generique("iptables -F");
		//Supression des chaines personnelles de la table filter
		CmdSystem_Generique("iptables -X");

		//Supression les chaînes de la table nat (PREROUTING, OUTPUT et POSTROUTING)
		CmdSystem_Generique("iptables -t nat -F");
		//Supression des chaines personnelles de la table filter
		CmdSystem_Generique("iptables -t nat -X");

		if((TRUE == u8TestNAT_Fonctionnelle(loc_ps_config, loc_u32_adr_ip_public_default, loc_u32_mask_ip_public_default))&&
		   (ADRESSE_IP_NULLE != loc_u32_adr_ip_public_default)
		  )
		{
			if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
			{
				//On configure d'abord les alias IP si nécessaire
				for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
				{
					if((ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)&&
					   (TRUE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)
					  )
					{
						CmdSystem_Generique("ifconfig %s:%d %s",
											NOM_INTERFACE_WIFI,
											loc_u16_i,
											ps8GetStringIp(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip));
					}
				}
			}

			//-----------------------------------------------------------
			//Configuration de la chaine POSTROUTING (de la table NAT)
			//-----------------------------------------------------------
			//On configure SNAT prioritaires (liès à la configuration NAT Mapping d'adresses)
			//Mapping d'adresses
			if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
			{
				for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
				{
					if((ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)&&
					   (TRUE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)
					  )
					{
						//iptables -t nat -A POSTROUTING -o ath0 
						//			-s <adresseIP_privee> 
						//			-j SNAT --to-source <adresseIP_publique>

						strcpy(loc_ps8_addr_ip_privee, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip)); 
						strcpy(loc_ps8_addr_ip_public, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip));
						CmdSystem_Generique("iptables -t nat -A POSTROUTING -p ALL -o %s -s %s -j SNAT --to-source %s",
											NOM_INTERFACE_WIFI,
											loc_ps8_addr_ip_privee,
											loc_ps8_addr_ip_public);
					}
				}
			}
			//Et on finit de configurer le SNAT IP masquerading (!!! par défaut à la fin !!!)
			//iptables -t nat -A POSTROUTING -p ALL -j MASQUERADE -o ath0: pas utilisé
			//iptables -t nat -A POSTROUTING -p ALL -o ath0 -j SNAT --to-source <adresseIP_publique>
			CmdSystem_Generique("iptables -t nat -A POSTROUTING -p ALL -o %s -j SNAT --to-source %s",
								NOM_INTERFACE_WIFI,
								ps8GetStringIp(loc_u32_adr_ip_public_default));

			//-----------------------------------------------------------
			//Configuration de la chaine PREROUTING (de la table NAT)
			//-----------------------------------------------------------
			//Mapping d'adresses
			if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
			{
				for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
				{
					if((ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)&&
					   (TRUE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)
					  )
					{
						//iptables -t nat -A PREROUTING -p ALL
						//		-d <adresseIP_publique> 
						//		-j DNAT --to-destination <adresseIP_privee>

						strcpy(loc_ps8_addr_ip_privee, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip)); 
						strcpy(loc_ps8_addr_ip_public, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip));
						CmdSystem_Generique("iptables -t nat -A PREROUTING -p ALL -d %s -j DNAT --to-destination %s",
											loc_ps8_addr_ip_public,
											loc_ps8_addr_ip_privee);
					}
				}
			}


			//Port forwarding
			strcpy(loc_ps8_addr_ip_public, ps8GetStringIp(loc_u32_adr_ip_public_default));
			for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
			{
				if(NAT_PROTOCOLE_NON_SELECTIONNE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
				{
					if(TRUE == loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable) //CONDITION:
					{
						//iptables -t nat -A PREROUTING -p <protocole_au_choix> -i ath0
						//		-d <adresseIP_publique> --dport <port_public> 
						//		-j DNAT --to-destination <adresseIP_privee>:<port_privé>

						strcpy(loc_ps8_addr_ip_privee, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip)); 
						CmdSystem_Generique("iptables -t nat -A PREROUTING -p %s -i %s -d %s --dport %d -j DNAT --to-destination %s:%d",
											PS8_CHAINE_PROTOCOLE_NAT_IPTABLES[loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole],
											NOM_INTERFACE_WIFI,
											loc_ps8_addr_ip_public,
											loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port,
											loc_ps8_addr_ip_privee,
											loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port);
					}
				}
			}

			//-----------------------------------------------------------
			//Configuration de la chaine FORWARD (de la table filter)
			//-----------------------------------------------------------
			//Configuration NAT Port forwarding
			for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
			{
				if(NAT_PROTOCOLE_NON_SELECTIONNE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
				{
					if(TRUE == loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable) //CONDITION:
					{
						strcpy(loc_ps8_addr_ip_privee, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip));
						//iptables -A FORWARD -i ath0 -p <protocole_au_choix> --dport <port_privé> -d <adresseIP _privee> -j ACCEPT 
						CmdSystem_Generique("iptables -A FORWARD -i %s -p %s --dport %d -d %s -j ACCEPT",
											NOM_INTERFACE_WIFI,
											PS8_CHAINE_PROTOCOLE_NAT_IPTABLES[loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole],
											loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port,
											loc_ps8_addr_ip_privee);
					}
				}
			}
			//Configuration NAT Mapping d'adresses
			if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
			{
				for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
				{
					if((ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)&&
					   (TRUE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)
					  )
					{
						//iptables -A FORWARD -i ath0 -p ALL -d <adresseIP_privee> -j ACCEPT 
						strcpy(loc_ps8_addr_ip_privee, ps8GetStringIp(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip)); 
						CmdSystem_Generique("iptables -A FORWARD -i %s -p ALL -d %s -j ACCEPT",
											NOM_INTERFACE_WIFI,
											loc_ps8_addr_ip_privee);
					}
				}
			}
			
			//Pour le masquerading IP  (!!! par défaut à la fin !!!)
			CmdSystem_Generique("iptables -A FORWARD -i %s -j ACCEPT",
								NOM_INTERFACE_ETHERNET);
			CmdSystem_Generique("iptables -A FORWARD -i %s -o %s -m state --state ESTABLISHED,RELATED -j ACCEPT",
								NOM_INTERFACE_WIFI,
								NOM_INTERFACE_ETHERNET);
		}//(TRUE == u8TestNAT_Fonctionnelle(......))

		if(TRUE == s_debug_global_process_prncpl.u8_dbg_iptables) //CONDITION: debug activé
		{
			//On affiche la table NAT
			CmdSystem_Generique("iptables -t nat -L");
			//On affiche la table filter
			CmdSystem_Generique("iptables -L");
		}

		//Génération pour information de l'état de la table NAT
		CmdSystem_Generique("echo \"#iptables -L -t nat -n\" >> %s",FICHIER_TABLE_NAT_ACTIVE);
		CmdSystem_Generique("iptables -L -t nat -n >> %s",FICHIER_TABLE_NAT_ACTIVE);
		//Génération pour information de l'état de la table FILTER
		CmdSystem_Generique("echo \"#iptables -L -t filter -n\" >> %s",FICHIER_TABLE_FILTER_ACTIVE);
		CmdSystem_Generique("iptables -L -t filter -n >> %s",FICHIER_TABLE_FILTER_ACTIVE);
	}

}/*Install_Nat*/

//=====================================================================================
// Fonction		: Uninstall_Nat
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 11/02/2010 -
// Description	: Désinstalle  NAT
//=====================================================================================
void Uninstall_Nat(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_i;
	
	printf("Uninstall_Nat\n");

	//Définition du comportement par défaut pour les chaines de la table filter
	// -> On autorise les entrées / sorties / routage
	CmdSystem_Generique("iptables -P INPUT ACCEPT");
	CmdSystem_Generique("iptables -P OUTPUT ACCEPT");
	CmdSystem_Generique("iptables -P FORWARD ACCEPT");

	//Supression les chaînes de la table filter (INPUT, FORWARD et OUTPUT)
	CmdSystem_Generique("iptables -F");
	//Supression des chaines personnelles de la table filter
	CmdSystem_Generique("iptables -X");

	//Supression les chaînes de la table nat (PREROUTING, OUTPUT et POSTROUTING)
	CmdSystem_Generique("iptables -t nat -F");
	//Supression des chaines personnelles de la table nat
	CmdSystem_Generique("iptables -t nat -X");

	//Suppresssion des alias IP
	for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
	{
		CmdSystem_Generique("ifconfig %s:%d down",
							NOM_INTERFACE_WIFI,
							loc_u16_i);
	}

	//Génération pour information de l'état de la table NAT
	CmdSystem_Generique("iptables -L -t nat -n > %s",FICHIER_TABLE_NAT_ACTIVE);
	//Génération pour information de l'état de la table FILTER
	CmdSystem_Generique("iptables -L -t filter -n > %s",FICHIER_TABLE_FILTER_ACTIVE);
	
	
}/*Uninstall_Nat*/



/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_Nat
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/02/2010 -
// Description	: Initialisation du module de cfg_nat
//=====================================================================================
void InitModule_Cfg_Nat(void)
{
	
}/*InitModule_Cfg_Nat*/

