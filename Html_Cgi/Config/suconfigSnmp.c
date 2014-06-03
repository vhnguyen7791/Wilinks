/*========================================================================*/
/* NOM DU FICHIER  : suconfigsnmp.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 15/10/2009                                           */
/* Libelle         : HTML CGI: pages HTML de config SNMP				  */
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGSNMP

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGSNMP
{
	FORM_SUCONFIGSNMP_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGSNMP_VALID_0,
	FORM_SUCONFIGSNMP_VALID_1,
	FORM_SUCONFIGSNMP_VALID_2,
	FORM_SUCONFIGSNMP_VALID_3,
	FORM_SUCONFIGSNMP_REPLAYTRAP,
	FORM_SUCONFIGSNMP_VALID_4,
	FORM_SUCONFIGSNMP_VALID_5,
	FORM_SUCONFIGSNMP_VALID_ALL,
	NB_MAX_FORM_SUCONFIGSNMP
};

#define REPLAY_TRAP_INACTIVE	1
#define REPLAY_TRAP_ACTIVE	2

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/* Structures pour la modificaton de la configuration */
typedef struct 
{
	s8sod	ps8_versionSnmp			[10 + 1];
	
	s8sod	ps8_NomCommunauteGET	[LG_MAX_NOM_COMMUNAUTE_SNMP + 1];
	s8sod	ps8_NomCommunauteSET	[LG_MAX_NOM_COMMUNAUTE_SNMP + 1];
	s8sod	ps8_NomCommunauteTRAP	[LG_MAX_NOM_COMMUNAUTE_SNMP + 1];

	s8sod	ps8_NomManager [NB_MANAGER_SNMP_MAX]				[LG_NOM_MANAGER_SNMP + 1];
	s8sod	ps8_presentManager [NB_MANAGER_SNMP_MAX]			[10 + 1];
	s8sod	ps8_AdresseManager [NB_MANAGER_SNMP_MAX]			[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_typeNotificationManager [NB_MANAGER_SNMP_MAX]	[10 + 1];
	
	s8sod	ps8_SendTrap			[10 + 1];
	s8sod	ps8_activationSigneVie	[10 + 1];
	s8sod	ps8_cycleSigneVie		[10 + 1];
	
	s8sod	ps8_NbEmissionTrap [NIV_GRAVITE_MAX]	[10 + 1];
	s8sod	ps8_CycleTrap  [NIV_GRAVITE_MAX]		[10 + 1];

	s8sod	ps8_NbEmissionInform	[10 + 1];
	s8sod	ps8_CycleInform			[10 + 1];
	
	s8sod	ps8_hidden1				[10 + 1];
} S_CONFIG_SNMP_RESULTS;

FIELD_LIST s_ConfigSnmpFields[] = {

	{"vSNMP",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_versionSnmp)		},
	
	{"NCGET",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomCommunauteGET)		},
	{"NCSET",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomCommunauteSET)		},
	{"NCTRAP",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomCommunauteTRAP)		},
	
	{"NM1",			"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomManager[0])			},
	{"prM1",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_presentManager[0])		},
	{"AdM1",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_AdresseManager[0])		},
	{"tnM1",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_typeNotificationManager[0])},

	{"NM2",			"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomManager[1])			},
	{"prM2",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_presentManager[1])		},
	{"AdM2",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_AdresseManager[1])		},
	{"tnM2",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_typeNotificationManager[1])},

	{"NM3",			"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomManager[2])			},
	{"prM3",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_presentManager[2])		},
	{"AdM3",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_AdresseManager[2])		},
	{"tnM3",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_typeNotificationManager[2])},

	{"NM4",			"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomManager[3])			},
	{"prM4",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_presentManager[3])		},
	{"AdM4",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_AdresseManager[3])		},
	{"tnM4",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_typeNotificationManager[3])},

	{"NM5",			"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NomManager[4])			},
	{"prM5",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_presentManager[4])		},
	{"AdM5",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_AdresseManager[4])		},
	{"tnM5",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_typeNotificationManager[4])},
	
	{"SdTrap",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_SendTrap)				},
	{"ActSV",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_activationSigneVie)	},
	{"CycleSV",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_cycleSigneVie)		},

	{"NbET0",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NbEmissionTrap[NIV_GRAVITE_INDETERMINE])},
	{"CyT0",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_CycleTrap[NIV_GRAVITE_INDETERMINE])		},
	{"NbET1",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NbEmissionTrap[NIV_GRAVITE_CRITIQUE])	},
	{"CyT1",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_CycleTrap[NIV_GRAVITE_CRITIQUE])		},
	{"NbET2",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NbEmissionTrap[NIV_GRAVITE_MAJEUR])		},
	{"CyT2",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_CycleTrap[NIV_GRAVITE_MAJEUR])			},
	{"NbET3",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NbEmissionTrap[NIV_GRAVITE_MINEUR])		},
	{"CyT3",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_CycleTrap[NIV_GRAVITE_MINEUR])			},
	{"NbET4",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NbEmissionTrap[NIV_GRAVITE_AVERTISSEMENT])	},
	{"CyT4",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_CycleTrap[NIV_GRAVITE_AVERTISSEMENT])		},

	{"NbEI",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_NbEmissionInform)		},
	{"CyI",			"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_CycleInform)		},
	
	{"hidden1",		"%s",	offsetof(S_CONFIG_SNMP_RESULTS, ps8_hidden1)				},
	{NULL	}
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigSnmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: code de javascript des pages Config - Snmp
//=====================================================================================
void proc_JavaScript_SUConfigSnmp(void)
{
	u16sod	loc_u16_i;

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript SelectFormulaire
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{ \n"
			 "	form.hidden1.value = i_numForm;\n"
			 "	form.submit();\n"
			 "} \n");	

	//Fonction javascript JsTestAdresseIpManager
	html_tag("function JsTestAdresseIpManager(numero_manager, objet_change) \n"
			 "{ \n"
			 "	var loc_resultat = false; \n"
			 "	with (document) \n"
			 "	{ \n"
			 "		switch(numero_manager) \n"
			 "		{ \n");
	for(loc_u16_i=0;loc_u16_i<NB_MANAGER_SNMP_MAX;loc_u16_i++)
	{
		html_tag("			case %d: \n"
				 "				loc_resultat = validAddr(form.AdM%d, (true == form.prM%d.checked)); \n",
				 loc_u16_i+1,
				 loc_u16_i+1,
				 loc_u16_i+1);
		html_tag("				if(false == loc_resultat)\n"
				 "				{ \n"
				 "					switch(objet_change) \n"
				 "					{ \n"
				 "						case 1: \n"	//objet presence
				 "							form.prM%d.checked =false;\n"	//INACTIVE
				 "							break; \n"
				 "						case 2: \n"	//objet adresseIP
				 "							break; \n"
				 "						default: \n"
				 "							break; \n"
				 "					} \n"
				 "				} \n"
				 "				break; \n",
				 loc_u16_i+1);
	}
	html_tag("			default: \n"
			 "				break;\n"
			 "		} \n"
			 "	} \n"
			 "	return(loc_resultat); \n"
			 "} \n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigSnmp*/

//=====================================================================================
// Fonction		: SUConfigSNMP
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Page HTML Configuration: SNMP
//=====================================================================================
void SUConfigSNMP(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s8sod	loc_ps8_emsg[50];
	s32sod  loc_s32_NumeroForm;
	u16sod	loc_u16_i;
	u8sod	loc_u8_i;
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	S_CONFIG_SNMP_RESULTS 	loc_s_results_reseau;

	loc_u8_result_test = FALSE; //INIT

	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigSNMP");
		return;  
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results_reseau
		memset(&loc_s_results_reseau, '\0', sizeof(S_CONFIG_SNMP_RESULTS));
		
		// Décodage de la requête
		if (!form_decode(s_ConfigSnmpFields, &loc_s_results_reseau, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
			//on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			loc_s32_NumeroForm = atoi(loc_s_results_reseau.ps8_hidden1);
			
			if((loc_s32_NumeroForm > FORM_SUCONFIGSNMP_NULL)||
			   (loc_s32_NumeroForm < NB_MAX_FORM_SUCONFIGSNMP)
			  )
			{
				// Version SNMP
				if((FORM_SUCONFIGSNMP_VALID_0 == loc_s32_NumeroForm)||
				   (FORM_SUCONFIGSNMP_VALID_ALL == loc_s32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_snmp.u8_version_snmp = (u8sod)atoi(loc_s_results_reseau.ps8_versionSnmp);
						if(TRUE==u8TestConfigSnmp(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigSnmp(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				// Table de Communautés
				if((FORM_SUCONFIGSNMP_VALID_1 == loc_s32_NumeroForm)||
				   (FORM_SUCONFIGSNMP_VALID_ALL == loc_s32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						if((VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp)||
						   (VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
						  )//CONDITION: SNMPv1 ou SNMPv2c
						{
							strncpy(s_html_cfg_eqpmt.s_snmp.ps8_nom_communaute_get,loc_s_results_reseau.ps8_NomCommunauteGET,(LG_MAX_NOM_COMMUNAUTE_SNMP+1));
							strncpy(s_html_cfg_eqpmt.s_snmp.ps8_nom_communaute_set,loc_s_results_reseau.ps8_NomCommunauteSET,(LG_MAX_NOM_COMMUNAUTE_SNMP+1));
							strncpy(s_html_cfg_eqpmt.s_snmp.ps8_nom_communaute_trap,loc_s_results_reseau.ps8_NomCommunauteTRAP,(LG_MAX_NOM_COMMUNAUTE_SNMP+1));
						}
						if(TRUE==u8TestConfigSnmp(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigSnmp(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				// Table des Managers SNMP
				if((FORM_SUCONFIGSNMP_VALID_2 == loc_s32_NumeroForm)||
				   (FORM_SUCONFIGSNMP_VALID_ALL == loc_s32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						for(loc_u16_i=0;loc_u16_i<NB_MANAGER_SNMP_MAX;loc_u16_i++)
						{
							strncpy(s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].ps8_nom,loc_s_results_reseau.ps8_NomManager[loc_u16_i], (LG_NOM_MANAGER_SNMP+1));
							s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u32_adresse_ip = u32DecodageAdresseReseau(loc_s_results_reseau.ps8_AdresseManager[loc_u16_i], &loc_u8_ret);
							if (0 == strcmp(loc_s_results_reseau.ps8_presentManager[loc_u16_i], "ON"))
							{	
								s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u8_presence = MANAGER_SNMP_PRESENT;
							}
							else
							{	
								s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u8_presence = MANAGER_SNMP_ABSENT;
							}
							if(VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv2c
							{
								s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u8_type_notification = (u8sod)atoi(loc_s_results_reseau.ps8_typeNotificationManager[loc_u16_i]);
							}

						}
						
						if(TRUE==u8TestConfigSnmp(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigSnmp(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				// Table de Emission TRaps
				if((FORM_SUCONFIGSNMP_VALID_3 == loc_s32_NumeroForm)||
				   (FORM_SUCONFIGSNMP_VALID_ALL == loc_s32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_snmp.u8_emission_trap = (u8sod)atoi(loc_s_results_reseau.ps8_SendTrap);
						s_html_cfg_eqpmt.s_snmp.s_trap_signevie.u8_activation = (u8sod)atoi(loc_s_results_reseau.ps8_activationSigneVie);
						s_html_cfg_eqpmt.s_snmp.s_trap_signevie.u16_cycle = (u16sod)atoi(loc_s_results_reseau.ps8_cycleSigneVie);
						if(TRUE==u8TestConfigSnmp(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigSnmp(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				//Rejouer les TRAP
				if(FORM_SUCONFIGSNMP_REPLAYTRAP == loc_s32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						loc_u8_result_test = TRUE;
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
					
					if(VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
					{
						s32Lock_Get(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillCipSnmpd(&s_cip_snmpd_from_html))
						{
							s_cip_snmpd_from_html.u8_replay_trap = TRUE;
							u8EditCipSnmpd(&s_cip_snmpd_from_html);
						}
						s32Lock_Release(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on relache le sem
					}
				}
				
				// Table de Protocoles d'émission TRAPs (SNMPv1)
				if((FORM_SUCONFIGSNMP_VALID_4 == loc_s32_NumeroForm)||
				   (FORM_SUCONFIGSNMP_VALID_ALL == loc_s32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						if(VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement en SNMPv1
						{
							for(loc_u16_i=0;loc_u16_i<NIV_GRAVITE_MAX;loc_u16_i++)
							{
								s_html_cfg_eqpmt.s_snmp.s_trap_SNMPv1[loc_u16_i].u16_nb_emission = (u16sod)atoi(loc_s_results_reseau.ps8_NbEmissionTrap[loc_u16_i]);
								s_html_cfg_eqpmt.s_snmp.s_trap_SNMPv1[loc_u16_i].u16_interval = (u16sod)atoi(loc_s_results_reseau.ps8_CycleTrap[loc_u16_i]);
							}
						}
						if(TRUE==u8TestConfigSnmp(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigSnmp(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				// Table de Protocoles d'émission Informs (SNMPv2c)
				if((FORM_SUCONFIGSNMP_VALID_5 == loc_s32_NumeroForm)||
				   (FORM_SUCONFIGSNMP_VALID_ALL == loc_s32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
					{
						if(VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement en SNMPv2c
						{
							s_html_cfg_eqpmt.s_snmp.s_inform_SNMPv2c.u16_nb_emission = (u16sod)atoi(loc_s_results_reseau.ps8_NbEmissionInform);
							s_html_cfg_eqpmt.s_snmp.s_inform_SNMPv2c.u16_interval = (u16sod)atoi(loc_s_results_reseau.ps8_CycleInform);
						}
						if(TRUE==u8TestConfigSnmp(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigSnmp(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
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
				PreparePageCfgInProgress("SUConfigSNMP");
				VCfgInProgress(loc_p_varlist, loc_s32_form_method);
				return; // on sort!
			}
		}
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_SNMP);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");
	
	
	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigSNMP");	//pour la fonction Actualiser
	
	JSNumCheck();
	JSIPCheck();
	JSTextCheck();
	
	proc_JavaScript_SUConfigSnmp();

	
	html_tag("<body> \n");
	// Start the form 
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigSNMP");//permet d'avoir la bonne page de rafraichit!!
	html_tag("\n");
	
	
	// On déclare un paramètre caché pour prendre en charge les différents validé
	form_hidden("hidden1","0");
	
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_SNMP);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigSnmp);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//Version SNMP
	//Sélection de la version SNMP
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_selection_version_snmp);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"215\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"150\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("			<th width=\"80\">&nbsp;</th> \n");
	html_tag("		</tr> \n");
	//Version SNMP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_version_snmp);
	html_tag("			<td><SELECT name=vSNMP> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_VERSIONS_SNMP;loc_u8_i++)
	{
		html_tag("			<option %s value=\"%d\">%s</option> \n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_version_snmp[loc_u8_i]);
	}
	html_tag("			</select></td> \n");
	html_tag("		<td align=\"center\"><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGSNMP_VALID_0);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");

	if((VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp)||
	   (VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
	  )//CONDITION: SNMPv1 ou SNMPv2c
	{
		//Table Communautés (SNMPv1 / SNMPv2c)
		html_tag("<tr><td><P class=undermenu>%s (%s / %s)</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_communautes,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_version_snmp[VERSION_SNMPV1],
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_version_snmp[VERSION_SNMPV2C]);
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"160\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"160\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
		html_tag("			<th width=\"80\">&nbsp;</th> \n");
		html_tag("		</tr> \n");
		//GET
		html_tag("		<tr> \n");
		html_tag("			<td>GET</td> \n");
		html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"NCGET\" value=\"%s\" width=\"15\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
				 LG_MAX_NOM_COMMUNAUTE_SNMP,
				 LG_MAX_NOM_COMMUNAUTE_SNMP,
				 s_html_cfg_eqpmt.s_snmp.ps8_nom_communaute_get);
		html_tag("			<td>&nbsp;</td> \n");
		html_tag("		</tr> \n");
		//SET
		html_tag("		<tr> \n");
		html_tag("			<td>SET</td> \n");
		html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"NCSET\" value=\"%s\" width=\"15\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
				 LG_MAX_NOM_COMMUNAUTE_SNMP,
				 LG_MAX_NOM_COMMUNAUTE_SNMP,
				 s_html_cfg_eqpmt.s_snmp.ps8_nom_communaute_set);
		html_tag("			<td>&nbsp;</td> \n");
		html_tag("		</tr> \n");
		//TRAP
		html_tag("		<tr> \n");
		html_tag("			<td>TRAP</td> \n");
		html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"NCTRAP\" value=\"%s\" width=\"15\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
				 LG_MAX_NOM_COMMUNAUTE_SNMP,
				 LG_MAX_NOM_COMMUNAUTE_SNMP,
				 s_html_cfg_eqpmt.s_snmp.ps8_nom_communaute_trap);
		html_tag("		<td align=\"center\"><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valider,
				 FORM_SUCONFIGSNMP_VALID_1);
		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");
	}

	//Table Managers SNMP
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_managers_snmp);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	switch(s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
	{
		case VERSION_SNMPV2C:
			html_tag("<TR><TD><P>%s</P></TD></TR> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_manager_snmpv2c);
			break;
		default:
		case VERSION_SNMPV1:
			html_tag("<TR><TD><P>%s</P></TD></TR> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_manager_snmpv1);
			break;
	}
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"160\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_libelles);
	html_tag("			<th>%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_present);
	html_tag("			<th width=\"160\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_adresse_internet_ip);
	if(VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv2c
	{
		html_tag("			<th nowrap>%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_type_notification);
	}
	html_tag("			<th width=\"80\">&nbsp;</th> \n");
	html_tag("		</tr> \n");
	for(loc_u16_i=0;loc_u16_i<NB_MANAGER_SNMP_MAX;loc_u16_i++)
	{
		html_tag("		<tr> \n");
		//Nom du manager SNMP
		html_tag("			<td><input type=\"text\" size=\"20\" maxlength=\"20\" name=\"NM%d\" value=\"%s\" width=\"15\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
				 loc_u16_i+1,
				 s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].ps8_nom);
		//Présence du manager SNMP
		html_tag("			<td>&nbsp;<input type=\"checkbox\" %s name=\"prM%d\" value=\"ON\" onclick=\"return(JsTestAdresseIpManager(%d, 1))\"></td> \n",
				 ((MANAGER_SNMP_PRESENT == s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u8_presence) ? "checked" : ""),
				 loc_u16_i+1,
				 loc_u16_i+1);
		//Adresse IP du manager SNMP
		html_tag("			<td><input type=\"text\" size=\"15\" name=\"AdM%d\" value=\"%s\" width=\"15\" onchange=\"return(JsTestAdresseIpManager(%d, 2))\"></td> \n",
				 loc_u16_i+1,
				 ps8GetStringIp(s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u32_adresse_ip),
				 loc_u16_i+1);
		if(VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv2c
		{
			//Type de notification
			html_tag("			<td><SELECT name=tnM%d> \n",
					loc_u16_i+1);
			for(loc_u8_i=0;loc_u8_i<NB_MAX_TYPES_NOTIFICATION;loc_u8_i++)
			{
				html_tag("			<option %s value=\"%d\">%s</option> \n",
						 ((loc_u8_i == s_html_cfg_eqpmt.s_snmp.s_manager_snmp[loc_u16_i].u8_type_notification) ? "selected" : ""),
						 loc_u8_i,
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_type_notification[loc_u8_i]);
			}
			html_tag("			</select></td> \n");
		}
		//Bouton valider
		if ((NB_MANAGER_SNMP_MAX - 1) == loc_u16_i)	//dernière ligne
		{
			html_tag("		<td align=\"center\"><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_valider,
					 FORM_SUCONFIGSNMP_VALID_2);
		}
		else
		{
			html_tag("			<td>&nbsp;</td> \n");
		}
		html_tag("		</tr> \n");
	}
	
	html_tag("</table></td></tr> \n");
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	//Table Configuration Général TRAP/INFORMS
	switch(s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
	{
		case VERSION_SNMPV2C:
			html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_configuration_emission_traps_informs);
			break;
		default:
		case VERSION_SNMPV1:
			html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_configuration_emission_traps);
			break;
	}
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"215\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"150\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("			<th width=\"80\">&nbsp;</th> \n");
	html_tag("		</tr> \n");
	//Activation / desactivation émission TRAP/INFORM
	html_tag("		<tr> \n");
	switch(s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
	{
		case VERSION_SNMPV2C:
			html_tag("			<td>%s&nbsp;<SUP>1)</SUP></td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_emission_traps_informs);
			break;
		default:
		case VERSION_SNMPV1:
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_emission_traps);
			break;
	}
	html_tag("			<td><SELECT name=SdTrap> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((EMISSION_TRAP_INACTIVE == s_html_cfg_eqpmt.s_snmp.u8_emission_trap) ? "selected" : ""),
			 EMISSION_TRAP_INACTIVE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((EMISSION_TRAP_ACTIVE == s_html_cfg_eqpmt.s_snmp.u8_emission_trap) ? "selected" : ""),
			 EMISSION_TRAP_ACTIVE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("			<td>&nbsp;</td> \n");
	html_tag("		</tr> \n");
	//Autorisation Signe de Vie
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_signe_vie);
	html_tag("			<td><SELECT name=ActSV> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_snmp.s_trap_signevie.u8_activation) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_snmp.s_trap_signevie.u8_activation) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("			<td>&nbsp;</td> \n");
	html_tag("		</tr> \n");
	//Temporisation de signe de Vie
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_temporisation_signe_vie);
	html_tag("			<TD><input align=\"center\" type=\"text\" name=\"CycleSV\" size=\"5\" value=\"%d\" onchange=return(isInteger(this,%d,%d))> %s</TD> \n",
			 s_html_cfg_eqpmt.s_snmp.s_trap_signevie.u16_cycle,
			 VALEUR_MIN_CYCLE_VIE,
			 VALEUR_MAX_CYCLE_VIE,
			 pt_tb_msg[u8_html_langue].ps8_msg_minutes);
	html_tag("		<td align=\"center\"><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGSNMP_VALID_3);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");

	if(VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv2c
	{
		html_tag("<tr><td>&nbsp;<SUP>1)</SUP>&nbsp;%s</td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_info_emission_trapv2);
	}

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	if(VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
	{
		//Rejouer les TRAPs
		html_tag("<tr><td>&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
				pt_tb_msg[u8_html_langue].ps8_msg_rejouer_traps_presents,
				FORM_SUCONFIGSNMP_REPLAYTRAP);
	}
	
	
	if(VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
	{
		//Table Protocole d'emission des TRAPs (SNMPv1)
		html_tag("<tr><td><P class=undermenu>%s (%s)</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_protocole_emission_traps,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_version_snmp[VERSION_SNMPV1]);
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<TR><TD><P>%s</P></TD></TR> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_snmp_prctl_traps);
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"160\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_niveau_de_gravite);
		html_tag("			<th width=\"120\">%s&nbsp;<SUP>1)</SUP></th> \n",pt_tb_msg[u8_html_langue].ps8_msg_nombre_emission);
		html_tag("			<th nowrap width=\"150\">%s<BR>(%s)</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_intervalle_reemission,
				 pt_tb_msg[u8_html_langue].ps8_msg_secondes);
		html_tag("			<th width=\"80\">&nbsp;</th> \n");
		html_tag("		</tr> \n");
		for(loc_u16_i=0;loc_u16_i<NIV_GRAVITE_MAX;loc_u16_i++)
		{
			html_tag("		<tr> \n");
			switch(loc_u16_i)
			{
				case NIV_GRAVITE_INDETERMINE:
					html_tag("			<td>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_indetermine);
					break;
				case NIV_GRAVITE_CRITIQUE:
					html_tag("			<td>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_critique);
					break;
				case NIV_GRAVITE_MAJEUR:
					html_tag("			<td>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_majeur);
					break;
				case NIV_GRAVITE_MINEUR:
					html_tag("			<td>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_mineur);
					break;
				case NIV_GRAVITE_AVERTISSEMENT:
					html_tag("			<td>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_avertissement);
					break;
				default:
					html_tag("			<td>?</td> \n");
					break;
			}
			html_tag("			<TD><input align=\"center\" type=\"text\" name=\"NbET%d\" size=\"5\" value=\"%d\" onchange=return(isInteger(this,%d,%d))> </TD> \n",
					 loc_u16_i,
					 s_html_cfg_eqpmt.s_snmp.s_trap_SNMPv1[loc_u16_i].u16_nb_emission,
					 REEMISSION_TRAPV1_MIN,
					 REEMISSION_TRAPV1_MAX);
			html_tag("			<TD><input align=\"center\" type=\"text\" name=\"CyT%d\" size=\"5\" value=\"%d\" onchange=return(isInteger(this,%d,%d))> </TD> \n",
					 loc_u16_i,
					 s_html_cfg_eqpmt.s_snmp.s_trap_SNMPv1[loc_u16_i].u16_interval,
					 INTERVAL_TRAPV1_MIN,
					 INTERVAL_TRAPV1_MAX);
			if ((NIV_GRAVITE_MAX - 1) == loc_u16_i)	//dernière ligne
			{
				html_tag("		<td align=\"center\"><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_valider,
						 FORM_SUCONFIGSNMP_VALID_4);
			}
			else
			{
				html_tag("			<td>&nbsp;</td> \n");
			}
			html_tag("		</tr> \n");
		}
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;<SUP>1)</SUP>&nbsp;%s</td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_info_ack_trapv1);
	}
	
	if(VERSION_SNMPV2C == s_html_cfg_eqpmt.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv2c
	{
		//Table Protocole d'emission des INFORM (SNMPv2c)
		html_tag("<tr><td><P class=undermenu>%s (%s)</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_protocole_emission_informs,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_version_snmp[VERSION_SNMPV2C]);
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<TR><TD><P>%s</P></TD></TR> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_snmp_prtcl_inform);
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"120\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nombre_emission);
		html_tag("			<th nowrap width=\"150\">%s<BR>(%s)</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_intervalle_reemission,
				 pt_tb_msg[u8_html_langue].ps8_msg_secondes);
		html_tag("			<th width=\"80\">&nbsp;</th> \n");
		html_tag("		</tr> \n");
		html_tag("		<tr> \n");
		html_tag("			<td><input align=\"center\" type=\"text\" name=\"NbEI\" size=\"5\" value=\"%d\" onchange=return(isInteger(this,%d,%d))> </td> \n",
				 s_html_cfg_eqpmt.s_snmp.s_inform_SNMPv2c.u16_nb_emission,
				 REEMISSION_INFORM_MIN,
				 REEMISSION_INFORM_MAX);
		html_tag("			<td><input align=\"center\" type=\"text\" name=\"CyI\" size=\"5\" value=\"%d\" onchange=return(isInteger(this,%d,%d))> </td> \n",
				 s_html_cfg_eqpmt.s_snmp.s_inform_SNMPv2c.u16_interval,
				 INTERVAL_INFORM_MIN,
				 INTERVAL_INFORM_MAX);
		html_tag("		<td align=\"center\"><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valider,
				 FORM_SUCONFIGSNMP_VALID_5);
		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");
	}

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider_formulaire,
			 FORM_SUCONFIGSNMP_VALID_ALL);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
	
}/*SUConfigSNMP*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigSnmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de suconfigSnmp
//=====================================================================================
void InitModule_SUConfigSnmp(void)
{
	;
}/*InitModule_SUConfigSnmp*/

