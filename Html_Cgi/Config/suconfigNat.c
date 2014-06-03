/*========================================================================*/
/* NOM DU FICHIER  : suconfigNat.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 10/02/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - NAT			  */
/* Projet          : WRM100                                               */
/* Indice          : BE049                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE010 10/02/2010 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE049 08/12/2010 CM
// - Ajout affichage des commandes dans la page de Configuration - NAT
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGNAT


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGNAT
{
	FORM_SUCONFIGNAT_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGNAT_VALID_1,
	FORM_SUCONFIGNAT_VALID_2,
	FORM_SUCONFIGNAT_PFWD_AJOUTER,
	FORM_SUCONFIGNAT_PFWD_EFFACER,
	FORM_SUCONFIGNAT_PFWD_DELETE_MIN,
	FORM_SUCONFIGNAT_PFWD_DELETE_MAX = (FORM_SUCONFIGNAT_PFWD_DELETE_MIN + NB_MAX_RULES_PORT_FORWARDING),
	FORM_SUCONFIGNAT_VALID_3,
	FORM_SUCONFIGNAT_MAPADR_AJOUTER,
	FORM_SUCONFIGNAT_MAPADR_EFFACER,
	FORM_SUCONFIGNAT_MAPADR_DELETE_MIN,
	FORM_SUCONFIGNAT_MAPADR_DELETE_MAX = (FORM_SUCONFIGNAT_MAPADR_DELETE_MIN + NB_MAX_NAT_ALIAS_IP),
	NB_MAX_FORM_SUCONFIGNAT
};

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_nat_enable			[10 + 1];

	//Nat Port forwarding
	s8sod	ps8_pfwd_adrIpPrivate	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_pfwd_portPrivate		[10 + 1];
	s8sod	ps8_pfwd_protocol			[10 + 1];
	s8sod	ps8_pfwd_portPublic		[10 + 1];
	s8sod	ps8_pfwd_commentaire		[TAILLE_MAX_COMMENT_NAT_PFWD + 1];
	s8sod	ps8_pfwd_enable			[10 + 1];
	s8sod	ps8_enable_port_forward[NB_MAX_RULES_PORT_FORWARDING]	[10 + 1];

	//Nat Mapping d'adresses
	s8sod	ps8_mapadr_adrIpPrivate	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_mapadr_adrIpPublic		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_mapadr_commentaire		[TAILLE_MAX_COMMENT_NAT_MPADR + 1];
	s8sod	ps8_mapadr_enable			[10 + 1];
	s8sod	ps8_enable_alias[NB_MAX_NAT_ALIAS_IP]	[10 + 1];

	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_NAT_RESULTS;

FIELD_LIST s_FormConfigNatFields[] = {
	{"natEnable",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_nat_enable)			},

	//Nat Port forwarding
	{"mtoIPpriv",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_pfwd_adrIpPrivate)	},
	{"mtoPrtpriv",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_pfwd_portPrivate)	},
	{"mtoProtclt",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_pfwd_protocol)			},
	{"mtoPrtpub",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_pfwd_portPublic)		},
	{"mtoComment",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_pfwd_commentaire)	},
	{"mtoEnable",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_pfwd_enable)			},
	{"R0",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[0])	},
	{"R1",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[1])	},
	{"R2",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[2])	},
	{"R3",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[3])	},
	{"R4",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[4])	},
	{"R5",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[5])	},
	{"R6",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[6])	},
	{"R7",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[7])	},
	{"R8",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[8])	},
	{"R9",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[9])	},
	{"R10",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[10])},
	{"R11",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[11])},
	{"R12",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[12])},
	{"R13",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[13])},
	{"R14",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[14])},
	{"R15",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[15])},
	{"R16",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[16])},
	{"R17",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[17])},
	{"R18",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[18])},
	{"R19",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_port_forward[19])},


	//Nat Mapping d'adresses
	{"mtmIPpriv",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_mapadr_adrIpPrivate)	},
	{"mtmIPpub",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_mapadr_adrIpPublic)	},
	{"mtmComment",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_mapadr_commentaire)	},
	{"mtmEnable",	"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_mapadr_enable)			},
	{"A0",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[0])	},
	{"A1",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[1])	},
	{"A2",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[2])	},
	{"A3",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[3])	},
	{"A4",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[4])	},
	{"A5",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[5])	},
	{"A6",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[6])	},
	{"A7",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[7])	},
	{"A8",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[8])	},
	{"A9",			"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_enable_alias[9])	},
	
	{"hidden1",		"%s",	offsetof(S_FORM_CONFIG_NAT_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigNat
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: code de javascript de la page HTML SUConfigNat
//=====================================================================================
void proc_JavaScript_SUConfigNat(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigNat
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: code de javascript de la page HTML SUConfigNat
//=====================================================================================
void proc_JavaScript_SUConfigNat(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{ \n");
	html_tag("} \n");

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("		with(document) \n");
	html_tag("		{  \n");
	html_tag("			switch(i_numForm)  \n");
	html_tag("			{  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGNAT_PFWD_AJOUTER);
	html_tag("					if(%d == Number(form.mtoProtclt.value))  \n",NAT_PROTOCOLE_NON_SELECTIONNE);
	html_tag("					{  \n");
	html_tag("						alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_il_faut_selectionner_un_protocole);
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("					else  \n");
	html_tag("					{  \n");
	html_tag("						if(false == validAddr(form.mtoIPpriv, true)) \n");
	html_tag("						{  \n");
	html_tag("							loc_result = false;  \n");
	html_tag("						}  \n");
	html_tag("					}  \n");
	html_tag("					break;  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGNAT_PFWD_EFFACER);
	html_tag("					form.mtoIPpriv.value = \"%s\"; \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("					form.mtoPrtpriv.value = %d; \n",PORT_UDP_TCP_MIN);
	html_tag("					form.mtoProtclt.value = %d; \n",NAT_PROTOCOLE_NON_SELECTIONNE);
	html_tag("					form.mtoPrtpub.value = %d; \n",PORT_UDP_TCP_MIN);
	html_tag("					form.mtoComment.value = \"\"; \n");
	html_tag("					form.mtoEnable.checked = false; \n");
	html_tag("					loc_result = false;  \n");
	html_tag("					break;  \n");
	if(MODE_IP_STATIQUE == s_html_cfg_eqpmt.s_gene.u8_wlan_mode_ip)
	{
		html_tag("				case %d: \n",
				 FORM_SUCONFIGNAT_MAPADR_AJOUTER);
		html_tag("					if((false == validAddr(form.mtmIPpriv, true))|| \n");
		html_tag("					   (false == validAddr(form.mtmIPpub, true)) \n");
		html_tag("					  ) \n");
		html_tag("					{  \n");
		html_tag("						loc_result = false;  \n");
		html_tag("					}  \n");
		html_tag("					break;  \n");
		html_tag("				case %d: \n",
				 FORM_SUCONFIGNAT_MAPADR_EFFACER);
		html_tag("					form.mtmIPpriv.value = \"%s\"; \n",ps8GetStringIp(ADRESSE_IP_NULLE));
		html_tag("					form.mtmIPpub.value = \"%s\"; \n",ps8GetStringIp(ADRESSE_IP_NULLE));
		html_tag("					form.mtmComment.value = \"\"; \n");
		html_tag("					form.mtmEnable.checked = false; \n");
		html_tag("					loc_result = false;  \n");
		html_tag("					break;  \n");
	}
	html_tag("				default:  \n");
	html_tag("					loc_result = true; \n");
	html_tag("					break;	  \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag( "	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigNat*/

//=====================================================================================
// Fonction		: SUConfigNat_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/02/2010
// Description	: Page Dynamique Configuration NAT
//				"URL=SUConfigNat_Dyn
//=====================================================================================
void SUConfigNat_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod				loc_s32_sem;
	
//	printf("Content-type: text/html\n\n");/* Mandatory */
	printf("Content-type: text/plain\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}

	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if( (FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) ||
		  (FALSE == u8FillConfigNAT(&s_html_cfg_eqpmt))
	  )
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem


	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	//Page accéssible uniquement en mode STATION / router
	if((MODE_RADIO_MODEM_STATION != s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem) ||
	   (MODE_NETWORK_ROUTER != s_html_cfg_eqpmt.s_gene.u8_mode_network)
	  )//CONDITION: STATION / router
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}

	if(TRUE == s_html_cfg_eqpmt.s_nat.u8_nat_activation)
	{
		//On surveille le statut IP de l'adresse WLAN
		html_tag("|");
		html_tag("&&&id:SPAN_STATUT_IP_WLAN_%d&&&innerHTML:&&&",
				 s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].u8_statut_ip);
		
		//On surveille le nombre de lignes affichées pour les tables
		html_tag("|");
		html_tag("&&&id:SPAN_RULES_FILTER_ACTIVES_%lu&&&innerHTML:&&&",
				 u32GetSizeOfFile(FICHIER_TABLE_FILTER_ACTIVE));
		html_tag("|");
		html_tag("&&&id:SPAN_RULES_NAT_ACTIVES_%lu&&&innerHTML:&&&",
				 u32GetSizeOfFile(FICHIER_TABLE_NAT_ACTIVE));
	}
	
	html_tag("|");

	

}/*SUConfigNat_Dyn*/

//=====================================================================================
// Fonction		: HtmlPrint_TableRulesFilterActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: Code HTML de la liste des règles FILTER actives
//=====================================================================================
void HtmlPrint_TableRulesFilterActive(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_TABLE_FILTER+1];
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT

	if(NULL == (loc_p_handle = fopen( FICHIER_TABLE_FILTER_ACTIVE, "rt" )))
	{
		html_tag("  <B>%s</B> (%s)\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible,
				 FICHIER_TABLE_FILTER_ACTIVE);
	}
	else
	{
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_TABLE_FILTER,loc_p_handle);
			if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue 
			{
				if((NULL != strstr(loc_ps8_ligne, "Chain"))||
				   (NULL != strstr(loc_ps8_ligne, "target"))||
				   (NULL != strstr(loc_ps8_ligne, "#iptables"))
				  )
				{
					html_tag("<B>%s</B>",loc_ps8_ligne);
				}
				else
				{
					html_tag("%s",loc_ps8_ligne);
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
			}

			loc_u16_cpt ++;

		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < ((NB_MAX_RULES_PORT_FORWARDING+NB_MAX_NAT_ALIAS_IP)*4)) &&
			   (TRUE == loc_u8_resultat)
			  );
		fclose (loc_p_handle);
	}

}/*HtmlPrint_TableRulesFilterActive*/

//=====================================================================================
// Fonction		: HtmlPrint_TableRulesNatActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: Code HTML de la liste des règles NAT actives
//=====================================================================================
void HtmlPrint_TableRulesNatActive(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_TABLE_FILTER+1];
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT

	if(NULL == (loc_p_handle = fopen( FICHIER_TABLE_NAT_ACTIVE, "rt" )))
	{
		html_tag("  <B>%s</B> (%s)\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible,
				 FICHIER_TABLE_NAT_ACTIVE);
	}
	else
	{
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_TABLE_FILTER,loc_p_handle);
			if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue 
			{
				if((NULL != strstr(loc_ps8_ligne, "Chain"))||
				   (NULL != strstr(loc_ps8_ligne, "target"))||
				   (NULL != strstr(loc_ps8_ligne, "#iptables"))
				  )
				{
					html_tag("<B>%s</B>",loc_ps8_ligne);
				}
				else
				{
					html_tag("%s",loc_ps8_ligne);
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
			}

			loc_u16_cpt ++;

		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < ((NB_MAX_RULES_PORT_FORWARDING+NB_MAX_NAT_ALIAS_IP)*4)) &&
			   (TRUE == loc_u8_resultat)
			  );
		fclose (loc_p_handle);
	}
	
}/*HtmlPrint_TableRulesNatActive*/


//=====================================================================================
// Fonction		: SUConfigNat
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 10/02/2010
// Description	: Page HTML Configuration: NAT
//				"URL=SUConfigNat"
//=====================================================================================
void SUConfigNat(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_NAT_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u16sod	loc_u16_numForm;
	u8sod	loc_u8_i;
	u16sod	loc_u16_i;
	u16sod	loc_u16_idx_rule_to_delete;
	u16sod	loc_u16_rules_pfwd_presentes;;
	u16sod	loc_u16_rules_mapadr_presentes;;
	S_STRUCT_NAT_RULE_PORT_FORWARDING loc_s_rule_pfwd;
	S_STRUCT_NAT_RULE_MAP_ADRESSES loc_s_rule_mapadr;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;			/* Init loc */
	
	loc_u8_result_test = FALSE; //INIT
	loc_u16_rules_pfwd_presentes = 0; //INIT
	loc_u16_rules_mapadr_presentes = 0; //INIT
	loc_u16_idx_rule_to_delete = 0;	//INIT
	memset(&loc_s_rule_pfwd, 0, sizeof(S_STRUCT_NAT_RULE_PORT_FORWARDING)); //INIT
	memset(&loc_s_rule_mapadr, 0, sizeof(S_STRUCT_NAT_RULE_MAP_ADRESSES)); //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigNat");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigNat&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_NAT_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigNatFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u16_numForm =  (u16sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u16_numForm < NB_MAX_FORM_SUCONFIGNAT)
			{
				if(FORM_SUCONFIGNAT_VALID_1 == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_nat.u8_nat_activation = (u8sod)atoi(loc_s_results.ps8_nat_enable);
						if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_SUCONFIGNAT_PFWD_AJOUTER == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						loc_s_rule_pfwd.u32_private_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_pfwd_adrIpPrivate, &loc_u8_ret);
						loc_s_rule_pfwd.u16_private_port = (u16sod)atoi(loc_s_results.ps8_pfwd_portPrivate);
						loc_s_rule_pfwd.u8_protocole = (u8sod)atoi(loc_s_results.ps8_pfwd_protocol);
						loc_s_rule_pfwd.u16_public_port = (u16sod)atoi(loc_s_results.ps8_pfwd_portPublic);
						if(0 == strcmp(loc_s_results.ps8_pfwd_enable, CHECKBOX_VALUE_CHECKED))
						{
							loc_s_rule_pfwd.u8_enable = TRUE;
						}
						else
						{
							loc_s_rule_pfwd.u8_enable = FALSE;
						}
						strcpy(loc_s_rule_pfwd.ps8_commentaire, loc_s_results.ps8_pfwd_commentaire);
						if(TRUE == u8AddRuleNatPortFwdFree(&s_html_cfg_eqpmt, &loc_s_rule_pfwd))
						{
							if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGNAT_VALID_2 == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
						{
							if(0 == strcmp(loc_s_results.ps8_enable_port_forward[loc_u16_i], CHECKBOX_VALUE_CHECKED))
							{
								s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable = TRUE;
							}
							else
							{
								s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable = FALSE;
							}
						}
						
						if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if((FORM_SUCONFIGNAT_PFWD_DELETE_MIN <= loc_u16_numForm)&&
				   (loc_u16_numForm <= FORM_SUCONFIGNAT_PFWD_DELETE_MAX)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						loc_u16_idx_rule_to_delete = loc_u16_numForm - FORM_SUCONFIGNAT_PFWD_DELETE_MIN;
						if(loc_u16_idx_rule_to_delete < NB_MAX_RULES_PORT_FORWARDING)
						{
							s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].u8_enable = FALSE; //RAZ
							s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].u32_private_ip = ADRESSE_IP_NULLE; //RAZ
							s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].u16_private_port = PORT_UDP_TCP_MIN; //RAZ
							s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].u8_protocole = NAT_PROTOCOLE_NON_SELECTIONNE; //RAZ
							s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].u16_public_port = PORT_UDP_TCP_MIN; //RAZ
							strcpy(s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].ps8_commentaire, ""); //RAZ
							if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGNAT_MAPADR_AJOUTER == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						loc_s_rule_mapadr.u32_private_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_mapadr_adrIpPrivate, &loc_u8_ret);
						loc_s_rule_mapadr.u32_public_alias_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_mapadr_adrIpPublic, &loc_u8_ret);
						if(0==strcmp(loc_s_results.ps8_mapadr_enable, CHECKBOX_VALUE_CHECKED))
						{
							loc_s_rule_mapadr.u8_enable = TRUE;
						}
						else
						{
							loc_s_rule_mapadr.u8_enable = FALSE;
						}
						
						strcpy(loc_s_rule_mapadr.ps8_commentaire, loc_s_results.ps8_mapadr_commentaire);
						if(TRUE == u8AddRuleNatMapAdrFree(&s_html_cfg_eqpmt, &loc_s_rule_mapadr))
						{
							if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGNAT_VALID_3 == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
						{
							if(0 == strcmp(loc_s_results.ps8_enable_alias[loc_u16_i], CHECKBOX_VALUE_CHECKED))
							{
								s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable = TRUE;
							}
							else
							{
								s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable = FALSE;
							}
						}

						if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				

				if((FORM_SUCONFIGNAT_MAPADR_DELETE_MIN <= loc_u16_numForm)&&
				   (loc_u16_numForm <= FORM_SUCONFIGNAT_MAPADR_DELETE_MAX)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigNAT(&s_html_cfg_eqpmt))
					{
						loc_u16_idx_rule_to_delete = loc_u16_numForm - FORM_SUCONFIGNAT_MAPADR_DELETE_MIN;
						if(loc_u16_idx_rule_to_delete < NB_MAX_NAT_ALIAS_IP)
						{
							s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_idx_rule_to_delete].u8_enable = FALSE; //RAZ
							s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_idx_rule_to_delete].u32_private_ip = ADRESSE_IP_NULLE; //RAZ
							s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_idx_rule_to_delete].u32_public_alias_ip = ADRESSE_IP_NULLE; //RAZ
							strcpy(s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_idx_rule_to_delete].ps8_commentaire, ""); //RAZ
							if(TRUE==u8TestConfigNAT(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigNAT(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FALSE == loc_u8_result_test)
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_CONFIG_KO);
					Html_GotoPage(ps8_pageHtmlRetour);
					return;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				PreparePageCfgInProgress("SUConfigNat");
				VCfgInProgress(loc_p_varlist, loc_s32_form_method);
				return; // on sort!
			}
			else//CONDITION: page KO
			{
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return;
			}
		}
	}
	

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if( (FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) ||
		(FALSE == u8FillConfigNAT(&s_html_cfg_eqpmt))
	  )
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	//Page accéssible uniquement en mode STATION / router
	if((MODE_RADIO_MODEM_STATION != s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem) ||
	   (MODE_NETWORK_ROUTER != s_html_cfg_eqpmt.s_gene.u8_mode_network)
	  )//CONDITION: STATION / router
	{
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_MODE_ONLY_STATION_ROUTER);
		Html_GotoPage(ps8_pageHtmlRetour);
		return;
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_NAT);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigNat");	//pour la fonction Actualiser
	RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=SUConfigNat_Dyn", (u32sod)u16GetTpsRefreshHtml()*1000);

	JSIPCheck();
	JSNumCheck();
	JSTextCheck();

	proc_JavaScript_SUConfigNat();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigNat");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_NAT);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigNat);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Activation NAT
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_NAT);
	html_tag("			<td><SELECT name=natEnable> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_nat.u8_nat_activation) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_nat.u8_nat_activation) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGNAT_VALID_1);

	if(TRUE == s_html_cfg_eqpmt.s_nat.u8_nat_activation)
	{
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td>&nbsp;<B>%s</B> : %s</td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_mode_ip,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_ip[s_html_cfg_eqpmt.s_gene.u8_wlan_mode_ip]);
		html_tag("<tr><td>&nbsp;<B>%s</B> : %s</td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_publique_par_defaut,
				 s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip);
		
		//On surveille le statut IP de l'adresse WLAN
		html_tag("<span id=SPAN_STATUT_IP_WLAN_%d></span> \n",
				 s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].u8_statut_ip);

		if(STATUT_IP__DHCP_IN_PROGRESS != s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].u8_statut_ip)
		{
			if(FALSE == u8TestNAT_Fonctionnelle(&s_html_cfg_eqpmt,
												u32DecodageAdresseReseau(s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].ps8_add_ip, &loc_u8_ret),
												u32DecodageAdresseReseau(s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].ps8_mask, &loc_u8_ret)))
			{
				html_tag("<tr><td>&nbsp;</td></tr> \n");
				html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_attention,
						 pt_tb_msg[u8_html_langue].ps8_msg_configuration_NAT_non_fonctionnelle);
			}
		}
		
		if((MODE_NETWORK_ROUTER == s_html_cfg_eqpmt.s_gene.u8_mode_network)&&
		   (MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		  )
		{
			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
					pt_tb_msg[u8_html_langue].ps8_msg_liste_regles_nat_actives);
			html_tag("<tr><td>&nbsp;</td></tr> \n");

			if(STATUT_IP__DHCP_IN_PROGRESS == s_html_exploit.s_general.ps_interface[INTERFACE_WLAN].u8_statut_ip)
			{
				html_tag("<tr><td><pre><B>%s: %s!</B></pre></td></tr>\n",
						 pt_tb_msg[u8_html_langue].ps8_msg_configuration_nat_non_appliquee,
						 pt_tb_msg[u8_html_langue].ps8_msg_dhcp_en_cours_sur_acces_wlan);
			}
			else //CONDITION: Adresse IP WLAN configurée
			{
				html_tag("<tr><td>\n");
				html_tag("<pre>");
				html_tag("---------------------------------------------------------------------------------------------------------\n");
				HtmlPrint_TableRulesFilterActive();
				html_tag("\n");
				html_tag("---------------------------------------------------------------------------------------------------------\n");
				HtmlPrint_TableRulesNatActive();
				html_tag("\n");
				html_tag("---------------------------------------------------------------------------------------------------------\n");
				html_tag("</pre>\n");
				html_tag("</td></tr> \n");
			}
		}

		//On surveille le nombre de lignes affichées pour les tables
		html_tag("<span id=SPAN_RULES_FILTER_ACTIVES_%lu></span> \n",
				 u32GetSizeOfFile(FICHIER_TABLE_FILTER_ACTIVE));
		html_tag("<span id=SPAN_RULES_NAT_ACTIVES_%lu></span> \n",
				 u32GetSizeOfFile(FICHIER_TABLE_NAT_ACTIVE));
		
		//**********************************************
		//**** PORT FORWARDING (NAT MANY-TO-ONE)   *****
		//**********************************************
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_forwarding);
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_privee);
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_prive);
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_protocole);
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_public);
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_commentaire);
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_autorise);
		html_tag("			<th nowrap>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_action);
		html_tag("		</tr> \n");
		loc_u16_rules_pfwd_presentes = 0; //RAZ
		for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
		{
			if(NAT_PROTOCOLE_NON_SELECTIONNE != s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
			{
				html_tag("		<tr> \n");
				//Adresse IP privée
				html_tag("			<td>%s</td> \n",
						 ps8GetStringIp(s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip));
				//Port privé
				html_tag("			<td>%d</td> \n",
						 s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port);
				//Protocole
				html_tag("			<td>%s</td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_nat_protocole[s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole]);
				//Port public
				html_tag("			<td>%d</td> \n",
						 s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port);
				//Commentaire
				html_tag("			<td nowrap>&nbsp;%s</td> \n",
						 s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].ps8_commentaire);
				//Autorisé
				html_tag("			<td><input %s name=\"R%d\" type=\"checkbox\" value=\"%s\"></td> \n",
						 (TRUE == s_html_cfg_eqpmt.s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable) ? " CHECKED" : "",
						 loc_u16_i,
						 CHECKBOX_VALUE_CHECKED);
				//Action
				html_tag("			<td nowrap>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_supprimer,
						 (FORM_SUCONFIGNAT_PFWD_DELETE_MIN+loc_u16_i));
				html_tag("		</tr> \n");
				loc_u16_rules_pfwd_presentes ++;
			}
		}
		if(0 != loc_u16_rules_pfwd_presentes) //CONDITION: règles présentes
		{
			html_tag("		<tr> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("	<td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_valider,
					 FORM_SUCONFIGNAT_VALID_2);
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("		</tr> \n");
		}
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_ajouter_regle_NAT_port_forwarding);
		if(FALSE == u8TestRuleNatPortFwdFree(&s_html_cfg_eqpmt))
		{
			html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_attention,
					 pt_tb_msg[u8_html_langue].ps8_msg_table_regles_port_forwarding_complete);
		}
		else
		{
			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
			html_tag("		<tr> \n");
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_privee);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_port_prive);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_protocole);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_port_public);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_commentaire);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_autorise);
			html_tag("		</tr> \n");
			html_tag("		<tr> \n");
			//Adresse IP privée
			html_tag("			<td><input type=\"text\" size=\"15\" name=\"mtoIPpriv\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
					ps8GetStringIp(ADRESSE_IP_NULLE));
			//Port privé
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"mtoPrtpriv\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
					 PORT_UDP_TCP_MIN,
					 PORT_UDP_TCP_MIN,
					 PORT_UDP_TCP_MAX);
			//Protocole
			html_tag("			<td><SELECT name=\"mtoProtclt\" size=\"1\"> \n");
			for(loc_u8_i=0;loc_u8_i<NB_MAX_NAT_PROTOCOLES;loc_u8_i++)
			{
				html_tag("		   <option %s value=\"%d\">%s</option>	\n",
						 ((NAT_PROTOCOLE_NON_SELECTIONNE == loc_u8_i) ? "selected" : ""),
						 loc_u8_i,
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_nat_protocole[loc_u8_i]);
			}
			html_tag("				  </select></td> \n");
			//Port public
			html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"mtoPrtpub\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
					 PORT_UDP_TCP_MIN,
					 PORT_UDP_TCP_MIN,
					 PORT_UDP_TCP_MAX);
			//Commentaire
			html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"mtoComment\" value=\" \" onchange=\"return(isValidText(this,false,true))\"></td> \n",
					 TAILLE_MAX_COMMENT_NAT_PFWD,
					 TAILLE_MAX_COMMENT_NAT_PFWD);
			//Autorisé
			html_tag("			<td><input name=\"mtoEnable\" type=\"checkbox\" value=\"%s\"></td> \n",CHECKBOX_VALUE_CHECKED);
			html_tag("		</tr> \n");
			html_tag("</table></td></tr> \n");

			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\" > \n",
					pt_tb_msg[u8_html_langue].ps8_msg_ajouter,
					FORM_SUCONFIGNAT_PFWD_AJOUTER);
			html_tag("&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_effacer,
					FORM_SUCONFIGNAT_PFWD_EFFACER);
		}
		//**********************************************	


		if(MODE_IP_STATIQUE == s_html_cfg_eqpmt.s_gene.u8_wlan_mode_ip)
		{
			//**********************************************
			//**** MAPPING ADRESSES (NAT MANY-TO-MANY) *****
			//**********************************************
			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_mapping_adresses);
			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
			html_tag("		<tr> \n");
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_privee);
			html_tag("			<th nowrap>&nbsp;%s (%s)&nbsp;</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_publique,
					 pt_tb_msg[u8_html_langue].ps8_msg_alias_IP);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_commentaire);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_autorise);
			html_tag("			<th nowrap>%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_action);
			html_tag("		</tr> \n");
			loc_u16_rules_mapadr_presentes = 0; //RAZ
			for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
			{
				if(ADRESSE_IP_NULLE != s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)
				{
					html_tag("		<tr> \n");
					//Adresse IP privée
					html_tag("			<td>%s</td> \n",
							 ps8GetStringIp(s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip));
					//Adresse IP publiqe (alias IP)
					html_tag("			<td>%s</td> \n",
							 ps8GetStringIp(s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip));
					//Commentaire
					html_tag("			<td nowrap>&nbsp;%s</td> \n",
							 s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].ps8_commentaire);
					//Autorisé
					html_tag("			<td><input %s name=\"A%d\" type=\"checkbox\" value=\"%s\"></td> \n",
							 (TRUE == s_html_cfg_eqpmt.s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable) ? " CHECKED" : "",
							 loc_u16_i,
							 CHECKBOX_VALUE_CHECKED);
					//Action
					html_tag("			<td nowrap>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_supprimer,
							 (FORM_SUCONFIGNAT_MAPADR_DELETE_MIN+loc_u16_i));
					html_tag("		</tr> \n");
					loc_u16_rules_mapadr_presentes ++;
				}
			}
			if(0 != loc_u16_rules_mapadr_presentes) //CONDITION: règles présentes
			{
				html_tag("		<tr> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_valider,
						 FORM_SUCONFIGNAT_VALID_3);
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("		</tr> \n");
			}
			html_tag("</table></td></tr> \n");

			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_ajouter_regle_NAT_mapping_adresse);
			if(FALSE == u8TestRuleNatMapAdrFree(&s_html_cfg_eqpmt))
			{
				html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_attention,
						 pt_tb_msg[u8_html_langue].ps8_msg_table_regles_mapping_adresses_complete);
			}
			else
			{
				html_tag("<tr><td>&nbsp;</td></tr> \n");
				html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
				html_tag("		<tr> \n");
				html_tag("			<th nowrap>%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_privee);
				html_tag("			<th nowrap>&nbsp;%s (%s)&nbsp;</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_adresse_IP_publique,
						 pt_tb_msg[u8_html_langue].ps8_msg_alias_IP);
				html_tag("			<th nowrap>%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_commentaire);
				html_tag("			<th nowrap>%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_autorise);
				html_tag("		</tr> \n");
				html_tag("		<tr> \n");
				//Adresse IP privée
				html_tag("			<td><input type=\"text\" size=\"15\" name=\"mtmIPpriv\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
						ps8GetStringIp(ADRESSE_IP_NULLE));
				//Adresse IP publique (alias IP)
				html_tag("			<td><input type=\"text\" size=\"15\" name=\"mtmIPpub\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
						ps8GetStringIp(ADRESSE_IP_NULLE));
				//Commentaire
				html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"mtmComment\" value=\" \" onchange=\"return(isValidText(this,false,true))\"></td> \n",
						 TAILLE_MAX_COMMENT_NAT_MPADR,
						 TAILLE_MAX_COMMENT_NAT_MPADR);
				//Autorisé
				html_tag("			<td><input name=\"mtmEnable\" type=\"checkbox\" value=\"%s\"></td> \n",CHECKBOX_VALUE_CHECKED);
				html_tag("		</tr> \n");
				html_tag("</table></td></tr> \n");

				html_tag("<tr><td>&nbsp;</td></tr> \n");
				html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\" > \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_ajouter,
						 FORM_SUCONFIGNAT_MAPADR_AJOUTER);
				html_tag("&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td></tr> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_effacer,
						 FORM_SUCONFIGNAT_MAPADR_EFFACER);
			}	
			//**********************************************
		}
		
	}/*if(TRUE == s_html_cfg_eqpmt.s_nat.u8_nat_activation)*/

	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigNat*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigNat
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/02/2010
// Description	: Initialisation du module de SUConfigNat
//=====================================================================================
void InitModule_SUConfigNat(void)
{
}/*InitModule_SUConfigNat*/
