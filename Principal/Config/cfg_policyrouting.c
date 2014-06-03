/*========================================================================*/
/* NOM DU FICHIER  : cfg_policyrouting.c                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 19/04/2010                                           */
/* Libelle         : Principal: Configuration de la politique de routage  */
/* Projet          : WRM100                                               */
/* Indice          : BE054                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 19/04/2010 CM
// - CREATION
//BE048 29/11/2010 CM
// - Correction bug sur re-configuration des politiques de routage
//		=> certaines règles ne sont plus appliquées
//BE049 08/12/2010 CM
// - Ajout affichage des commandes dans la page de Configuration - Routage Ip - Général
//BE054 11/01/2011 CM
// - Correction bug affichage commande table mangle
//		fichier errone
// - Correction bug affichage commande ip route info
//			mesg suivant sur page HTML Routage IP: "Accès à la base de données impossible ! (/tmp/bdd_misc/ip_route.info)
//			dans le cas où aucune passerelle activée dans les règles de politique de routage
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CFG_POLICYROUTING

#define IP_RULE_PRIORITY_POLICY_MIN	100

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Chaine de caractères pour iptables (routage politique)
static s8sod ps8_chaine_iptables_mangle[250+1];
static s8sod ps8_tempo_iptables_mangle[250+1];

//Protocole pour iptables
const s8sod PS8_CHAINE_PROTOCOLE_POLICYROUTE_IPTABLES[NB_MAX_POLICYROUTE_PROTOCOLES] [10+1] =
{
	"udp",		//POLICYROUTE_PROTOCOLE_UDP
	"tcp",		//POLICYROUTE_PROTOCOLE_TCP
	"icmp",		//POLICYROUTE_PROTOCOLE_ICMP
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Install_IptablesMangleForPolicyRouting
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Installe iptables mangle pour le routage politique
//=====================================================================================
void Install_IptablesMangleForPolicyRouting(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_i;
	S_STRUCT_ROUTE_POLICY	loc_s_route;	//une route
	s8sod loc_ps8_addr_ip_start[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_ip_end[MAX_LG_FORMAT_ADRESSE_IP+1];
	u16sod	loc_u16_table_id;
	u16sod	loc_u16_numberMark;

	printf("Install_IptablesMangleForPolicyRouting \n");
	
	memset(&loc_s_route, 0, sizeof(S_STRUCT_ROUTE_POLICY)); //INIT

	strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	loc_u16_table_id = 0;	//INIT
	loc_u16_numberMark = 0; //INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(TRUE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled) //CONDITION: politique de routage autorisée
		{
			//on fixe le tableid
			loc_u16_table_id = (loc_u16_i+1);
			//on fixe le numberMark
			loc_u16_numberMark = (loc_u16_i+1);

			//on copie la base de données dans loc_s_route
			loc_s_route = loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i];

			//On configure une règle politique à travers la tables mangle
			strcpy(ps8_chaine_iptables_mangle, "");	//RAZ

			//Source IP
			if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_IP])
			{
				strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(loc_s_route.u32_critere_src_ip_start));
				strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(loc_s_route.u32_critere_src_ip_end));

				sprintf(ps8_tempo_iptables_mangle,"-m iprange %s --src-range %s-%s",
						(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_SRC_IP])? "!" : "",
						loc_ps8_addr_ip_start,
						loc_ps8_addr_ip_end);
				strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
				strcat(ps8_chaine_iptables_mangle, " ");
			}
			//Destination IP
			if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_IP])
			{
				strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(loc_s_route.u32_critere_dst_ip_start));
				strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(loc_s_route.u32_critere_dst_ip_end));

				sprintf(ps8_tempo_iptables_mangle,"-m iprange %s --dst-range %s-%s",
						(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_DST_IP])? "!" : "",
						loc_ps8_addr_ip_start,
						loc_ps8_addr_ip_end);
				strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
				strcat(ps8_chaine_iptables_mangle, " ");
			}
			//Longueur des paquets
			if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])
			{
				if(loc_s_route.u16_critere_len_packet_min != loc_s_route.u16_critere_len_packet_max)
				{
					sprintf(ps8_tempo_iptables_mangle,"-m length %s --length %d:%d",
							(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET])? "!" : "",
							loc_s_route.u16_critere_len_packet_min,
							loc_s_route.u16_critere_len_packet_max);
				}
				else
				{
					sprintf(ps8_tempo_iptables_mangle,"-m length %s --length %d",
							(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET])? "!" : "",
							loc_s_route.u16_critere_len_packet_max);
				}
				strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
				strcat(ps8_chaine_iptables_mangle, " ");
			}
			//Protocole IP
			if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])
			{
				sprintf(ps8_tempo_iptables_mangle,"-p %s %s",
						(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL])? "!" : "",
						PS8_CHAINE_PROTOCOLE_POLICYROUTE_IPTABLES[loc_s_route.u8_critere_ip_protocol]);
				strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
				strcat(ps8_chaine_iptables_mangle, " ");
			}

			if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
			{
				//Port source
				if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])
				{
					sprintf(ps8_tempo_iptables_mangle,"--sport %s %d:%d",
							(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_SRC_PORT])? "!" : "",
							loc_s_route.u16_critere_src_port_start,
							loc_s_route.u16_critere_src_port_end);
					strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
					strcat(ps8_chaine_iptables_mangle, " ");
				}
				//Port destination
				if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT])
				{
					sprintf(ps8_tempo_iptables_mangle,"--dport %s %d:%d",
							(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_DST_PORT])? "!" : "",
							loc_s_route.u16_critere_dst_port_start,
							loc_s_route.u16_critere_dst_port_end);
					strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
					strcat(ps8_chaine_iptables_mangle, " ");
				}
			}
			//Class selector
			if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])
			{
				sprintf(ps8_tempo_iptables_mangle,"-m dscp %s --dscp-class  CS%d",
						(TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_CLASS_SELECTOR])? "!" : "",
						loc_s_route.u8_critere_class_selector);
				strcat(ps8_chaine_iptables_mangle, ps8_tempo_iptables_mangle);
				strcat(ps8_chaine_iptables_mangle, " ");
			}

			CmdSystem_Generique("iptables -t mangle -A PREROUTING %s -j MARK --set-mark=%d",
								ps8_chaine_iptables_mangle,
								loc_u16_numberMark);

			//d: debug
			printf("iptables -t mangle -A PREROUTING %s -j MARK --set-mark=%d\n",
				   ps8_chaine_iptables_mangle,
				   loc_u16_numberMark);
			//f: debug

			if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY])
			{
				//On ajoute la règle (avec comme ordre de priorité, l'ordre d'enregistrement)
				CmdSystem_Generique("ip rule add fwmark %d table %d priority %d",
									loc_u16_numberMark,
									loc_u16_table_id,
									(IP_RULE_PRIORITY_POLICY_MIN+loc_u16_table_id));
			}

			
			
			//Puis on applique la nouvelle class selector
			if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])
			{
				CmdSystem_Generique("iptables -t mangle -A FORWARD -m mark --mark %d -j DSCP --set-dscp-class CS%d",
									loc_u16_numberMark,
									loc_s_route.u8_new_class_selector);
			}


		}
	}

	if(TRUE == s_debug_global_process_prncpl.u8_dbg_iptables) //CONDITION: debug activé
	{
		//On affiche la table mangle
		CmdSystem_Generique("iptables -t mangle -L");
	}

	u8CmdSystem_RemoveFile(FICHIER_TABLE_MANGLE_ACTIVE);
	//Génération pour information de l'état de la table MANGLE
	CmdSystem_Generique("echo \"#iptables -L -t mangle -n\" >> %s",FICHIER_TABLE_MANGLE_ACTIVE);
	CmdSystem_Generique("iptables -L -t mangle -n >> %s",FICHIER_TABLE_MANGLE_ACTIVE);

	//Génération pour information des règles IP
	CmdSystem_Generique("echo \"#ip rule list\" >> %s",FICHIER_IP_RULE_SHOW);
	CmdSystem_Generique("ip rule list >>  %s",FICHIER_IP_RULE_SHOW);
	

}/*Install_IptablesMangleForPolicyRouting*/

//=====================================================================================
// Fonction		: Install_RulesForPolicyRouting
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Installe les règles pour le routage politique
//=====================================================================================
void Install_RulesForPolicyRouting(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_i;
	S_STRUCT_ROUTE_POLICY	loc_s_route;	//une route
	u16sod	loc_u16_table_id;
	u16sod	loc_u16_numberMark;
	u8sod	loc_u8_iproute_show_empty;

	printf("Install_RulesForPolicyRouting \n");
	
	memset(&loc_s_route, 0, sizeof(S_STRUCT_ROUTE_POLICY)); //INIT
	loc_u8_iproute_show_empty = TRUE; //INIT

	//Suppression du fichier d'information des routes IP vide
	u8CmdSystem_RemoveFile(FICHIER_IP_ROUTE_SHOW);
	
	loc_u16_table_id = 0;	//INIT
	loc_u16_numberMark = 0; //INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(TRUE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled) //CONDITION: politique de routage autorisée
		{
			//on fixe le tableid
			loc_u16_table_id = (loc_u16_i+1);
			//on fixe le numberMark
			loc_u16_numberMark = (loc_u16_i+1);
			
			//on copie la base de données dans loc_s_route
			loc_s_route = loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i];
			
			//on applique la nouvelle passerelle
			if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY])
			{
				CmdSystem_Generique("ip route add default via %s table %d",
									ps8GetStringIp(loc_s_route.u32_new_gateway),
									loc_u16_table_id);

				//Puis ajout dans fichier d'information des routes IP
				CmdSystem_Generique("echo \"#ip route show table %d\" >> %s",loc_u16_table_id,FICHIER_IP_ROUTE_SHOW);
				CmdSystem_Generique("ip route show table %d >> %s",loc_u16_table_id,FICHIER_IP_ROUTE_SHOW);
				loc_u8_iproute_show_empty = FALSE;
			}
		}
	}
	
	if(TRUE == loc_u8_iproute_show_empty)//CONDITION: fichier vide
	{
		CmdSystem_Generique("echo \"   \" >> %s",FICHIER_IP_ROUTE_SHOW);
	}

	
	//On affiche sur la console la liste des régles définies
	CmdSystem_Generique("ip rule list");
	//On affiche sur la console la liste des routes définies
	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(TRUE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled)
		{
			CmdSystem_Generique("ip route show table %d",
								loc_u16_i);
		}
	}

	//On reset le flag de reconfiguration (comme c'est fait!)
	ClearOrdreReconfiguration(ORDRE_RECONFIG__ROUTAGE_POLICY);
	
}/*Install_RulesForPolicyRouting*/

//=====================================================================================
// Fonction		: Uninstall_PolicyRouting
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Désinstalle le routage politique
//=====================================================================================
void Uninstall_PolicyRouting(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u16sod	loc_u16_i;
	S_STRUCT_ROUTE_POLICY	loc_s_route;	//une route
	u16sod	loc_u16_table_id;
	u16sod	loc_u16_numberMark;

	printf("Uninstall_PolicyRouting \n");

	memset(&loc_s_route, 0, sizeof(S_STRUCT_ROUTE_POLICY)); //INIT
	loc_u16_table_id = 0;	//INIT
	loc_u16_numberMark = 0; //INIT

	//Supression les chaînes de la table mangle (PREROUTING, OUTPUT et POSTROUTING)
	CmdSystem_Generique("iptables -t mangle -F");
	//Supression des chaines personnelles de la table mangle
	CmdSystem_Generique("iptables -t mangle -X");
	
	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(TRUE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled) //CONDITION: politique de routage autorisée
		{
			//on fixe le tableid
			loc_u16_table_id = (loc_u16_i+1);
			//on fixe le numberMark
			loc_u16_numberMark = (loc_u16_i+1);
			
			//Puis on supprime la règle
			CmdSystem_Generique("ip rule del fwmark %d table %d",
								loc_u16_numberMark,
								loc_u16_table_id);

			//Puis on supprime la nouvelle passerelle
			if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY])
			{
				CmdSystem_Generique("ip route del default via %s table %d",
									ps8GetStringIp(loc_s_route.u32_new_gateway),
									loc_u16_table_id);
			}
		}
	}

	u8CmdSystem_RemoveFile(FICHIER_TABLE_MANGLE_ACTIVE);
	//Génération pour information de l'état de la table MANGLE
	CmdSystem_Generique("echo \"#iptables -L -t mangle -n\" >> %s",FICHIER_TABLE_MANGLE_ACTIVE);
	CmdSystem_Generique("iptables -L -t mangle -n >> %s",FICHIER_TABLE_MANGLE_ACTIVE);

	//Suppression du fichier d'information des règle IP
	u8CmdSystem_RemoveFile(FICHIER_IP_RULE_SHOW);
	//Suppression du fichier d'information des routes IP vide
	u8CmdSystem_RemoveFile(FICHIER_IP_ROUTE_SHOW);
	
}/*Uninstall_PolicyRouting*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Cfg_PolicyRouting
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2010 -
// Description	: Initialisation du module de cfg_policyrouting
//=====================================================================================
void InitModule_Cfg_PolicyRouting(void)
{
	strcpy(ps8_chaine_iptables_mangle, "");	//INIT
	strcpy(ps8_tempo_iptables_mangle, "");	//INIT
	
}/*InitModule_Cfg_PolicyRouting*/

