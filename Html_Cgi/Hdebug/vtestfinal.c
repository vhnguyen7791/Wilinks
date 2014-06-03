/*========================================================================*/
/* NOM DU FICHIER  : vtestfinal.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : JP                                                   */
/* Date			   : 12/05/2010                                           */
/* Libelle         : HTML CGI: pages HTML pour le test final produit	  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE031 12/05/10 JP
// - CREATION
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE039 26/08/2010 CM
// - Intégration des modifications release_v2
//BE042 07/10/2010 CM
// - Correction configuration mode 802.11 (associé au driver-N)
//BE052 15/12/2010 CM
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
// - Ajout Test final WRM100-3-1-2 (JP)
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Correction kernel panic de temps en temps dans page HTML test final
//		conflit de requete pour temperature
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VTESTFINAL

//Liste des différents formulaires
enum LISTE_DES_FORM_VTESTFINAL
{
	FORM_VTESTFINAL_NULL = 0,
	FORM_VTESTFINAL_VALID_1,
	FORM_VTESTFINAL_VALID_TESTPING,
	FORM_VTESTFINAL_VALID_RST_STAT_CNX,
	FORM_VTESTFINAL_VALID_PE,
	NB_MAX_FORM_VTESTFINAL
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_cfg_test	[10 + 1];
	s8sod	ps8_mode		[10 + 1];
	s8sod	ps8_puissance_tx[10 + 1];
	s8sod	ps8_hidden1		[10 + 1];
} S_FORM_VTESTFINAL_RESULTS;

FIELD_LIST s_FormVTestfinalFields[] = {
	{"cfg_test",			"%s",		offsetof(S_FORM_VTESTFINAL_RESULTS,ps8_cfg_test)	},
	{"mode",				"%s",		offsetof(S_FORM_VTESTFINAL_RESULTS,ps8_mode)	},
	{"power",				"%s",	offsetof(S_FORM_VTESTFINAL_RESULTS, ps8_puissance_tx)	},
	{"hidden1",				"%s",		offsetof(S_FORM_VTESTFINAL_RESULTS,ps8_hidden1)	},
	{NULL	}
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: VTestFinal_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Description	: Page rafraichissement 
//=====================================================================================
void VTestFinal_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod				loc_s32_sem;
	FILE	*loc_p_handle;
	s8sod	loc_s8_chaine10[10];//au max on a besoin de 4+1 caracteres
	s32sod	loc_s32_temp;


	printf("Content-type: text/plain\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}

	//base de donnee debug
	s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillDebugFile(&s_html_debug_global))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	else
	{
		switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_STATION:
				break;
			case MODE_RADIO_MODEM_ACCESS_POINT:
				if(FALSE == u8FillConfigWifi(&s_html_cfg_eqpmt))
				{
					html_tag("|");
					html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
				}
				break;
			case MODE_RADIO_MODEM_MONITOR:
			default:
				break;
		}
	}	
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem


	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
	switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_STATION:
			if(FALSE == u8FillExploitStationFile(&s_html_exploit.s_station))
			{
				html_tag("|");
				html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
			}
			break;
		case MODE_RADIO_MODEM_ACCESS_POINT:
			if(FALSE == u8FillExploitAccessPointFile(&s_html_exploit.s_access_point))
			{
				html_tag("|");
				html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
			}
			break;
		case MODE_RADIO_MODEM_MONITOR:
		default:
			break;
	}

	if(FALSE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	switch(s_html_debug_global.u8_mode_test_final)
	{
		case MODE_STA_TF:
			//Statut de la connexion
			html_tag("|");

			if(STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_statut_connexion)
			{
				if (STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_old_statut_connexion)
				{ //en vert
					html_tag("&&&id:TD_STAT&&&className:&&&");
					html_tag("|");
					html_tag("&&&id:SPAN_STATUT&&&innerHTML:%s&&&",
							 ps8ConvertChaineToHtml(pt_tb_msg[u8_html_langue].ps8_msg_choix_station_connexion[s_html_exploit.s_station.u8_statut_connexion]));
				}
				else
				{ //en orange
					html_tag("&&&id:TD_STAT&&&className:orange&&&");
					html_tag("|");
					html_tag("&&&id:SPAN_STATUT&&&innerHTML:%s&&&",
							 ps8ConvertChaineToHtml(pt_tb_msg[u8_html_langue].ps8_msg_choix_station_connexion[s_html_exploit.s_station.u8_statut_connexion]));
				}
			}
			else
			{//en rouge
				html_tag("&&&id:TD_STAT&&&className:rouge&&&");
				html_tag("|");
				html_tag("&&&id:SPAN_STATUT&&&innerHTML:%s&&&",
						 ps8ConvertChaineToHtml(pt_tb_msg[u8_html_langue].ps8_msg_choix_station_connexion[s_html_exploit.s_station.u8_statut_connexion]));
			}

			//RSSI
			html_tag("|");
			if(STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_statut_connexion)
			{
				html_tag("&&&id:SPAN_RSSI&&&innerHTML:%ld dBm&&&",
						 s_html_exploit.s_station.s32_rssi_dbm);
			}
			else
			{
				html_tag("&&&id:SPAN_RSSI&&&innerHTML:? dBm&&&");
			}
			html_tag("|");
			//Temperature
			loc_s32_temp = s_html_exploit.s_general.s32_temperature;
			if(VALEUR_TEMPERATURE_INCONNUE == loc_s32_temp)
			{
				html_tag("&&&id:SPAN_TEMP&&&innerHTML:%s&&&",ps8ConvertChaineToHtml("??? °C"));
			}
			else
			{
				html_tag("&&&id:SPAN_TEMP&&&innerHTML:%ld %s&&&",
						 loc_s32_temp,ps8ConvertChaineToHtml("°C"));
			}
			html_tag("|");
			//Test Ping
			if(NULL == (loc_p_handle = fopen( "/tmp/res_ping.txt", "rt" )))
			{
				html_tag("&&&id:SPAN_PING&&&innerHTML:??? &&&");
			}
			else
			{
				if (fgets(loc_s8_chaine10,5,loc_p_handle)!=NULL)
				{
					if (atoi(loc_s8_chaine10) == 0)
					{//test ok
						html_tag("&&&id:SPAN_PING&&&innerHTML: OK &&&");
					}
					else
					{//test ko
						html_tag("&&&id:SPAN_PING&&&innerHTML: KO &&&");
					}
				}
				//fermeture du fichier
				fclose (loc_p_handle);
			}
			break;
		case MODE_AP_TF:
			//Liste des clients Wifi
			HtmlDyn_TableClientWifi();
			break;
		default:
			break;
	}

	html_tag("|");


}/*VTestFinal_Dyn*/



//=====================================================================================
// Fonction		: proc_JavaScript_VTestFinal
// Entrees		: rien
// Sortie		: rien
// Description	: java script pour la page
//=====================================================================================
void proc_JavaScript_VTestFinal(void)
{
	html_tag("<SCRIPT language=JavaScript> \n");	//Pour la fonction Actualiser


	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{ \n");
	html_tag("		form.hidden1.value = i_numForm;\n");
	html_tag("		form.submit();\n");
	html_tag("} \n");	

#ifdef _WRM100_ABG_SELECT
	//Fonction javascript : JsChangePowerTx
	//*************************************
	html_tag("function JsChangePowerTx(form) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if ((form.cfg_test[%d].checked) || (form.cfg_test[%d].checked)) \n",ANT1_2_4G,ANT2_2_4G);
	html_tag("		{ \n");
	html_tag("			if (false == isInteger(form.power,%d,%d)) \n",POWER_TX_802_11ABG_MIN, POWER_TX_802_11BG_MAX);
	html_tag("			{ \n");
	html_tag("				form.power.value = %d; \n",POWER_TX_802_11X_DEFAULT);
	html_tag( "				return false; \n");
	html_tag( "			} \n");
	html_tag( "		} \n");
	html_tag( "		else \n");
	html_tag( "		{ \n");
	html_tag( "			if (false == isInteger(form.power,%d,%d)) \n",POWER_TX_802_11ABG_MIN, POWER_TX_802_11A_MAX);
	html_tag( "			{ \n");
	html_tag( "				form.power.value = %d; \n",POWER_TX_802_11X_DEFAULT);
	html_tag( "				return false; \n");
	html_tag( "			} \n");
	html_tag( "		} \n");
	html_tag("	} \n");
	html_tag("	return true;\n");
	html_tag("} \n");/*JsChangePowerTx*/
#endif

#ifdef _WRM100_N_SELECT
	//Fonction javascript : JsChangePowerTx
	//*************************************
	html_tag("function JsChangePowerTx(form) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if (form.cfg_test[%d].checked) \n",ANT1_2_4G);
	html_tag("		{ \n");
	html_tag("			if (false == isInteger(form.power,%d,%d)) \n",POWER_TX_802_11ABGN_MIN, u8Get_N_PowerTxMax(MODE_WIFI_802_11NGHT20,DATA_RATE_MCS3,N_SELECT_ANTENNES_1_ET_2_ET_3));
	html_tag("			{ \n");
	html_tag("				form.power.value = %d; \n",POWER_TX_802_11X_DEFAULT);
	html_tag( "				return false; \n");
	html_tag( "			} \n");
	html_tag( "		} \n");
	html_tag( "		else \n");
	html_tag("		{ \n");
	html_tag("			if (false == isInteger(form.power,%d,%d)) \n",POWER_TX_802_11ABGN_MIN, u8Get_N_PowerTxMax(MODE_WIFI_802_11NAHT20,DATA_RATE_MCS3,N_SELECT_ANTENNES_1_ET_2_ET_3));
	html_tag("			{ \n");
	html_tag("				form.power.value = %d; \n",POWER_TX_802_11X_DEFAULT);
	html_tag( "				return false; \n");
	html_tag( "			} \n");
	html_tag( "		} \n");
	html_tag("	} \n");
	html_tag("	return true;\n");
	html_tag("} \n");/*JsChangePowerTx*/
#endif
	
	html_tag("</SCRIPT> \n");


}/*proc_JavaScript_VTestFinal*/


//=====================================================================================
// Fonction		: VTestFinal
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Description	: Page HTML: TEST - FINAL PRODUCTION
//=====================================================================================
void VTestFinal(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod					loc_s32_sem;
	s8sod					loc_ps8_emsg[50];
	u32sod					loc_u32_NumeroForm;
	S_FORM_VTESTFINAL_RESULTS	loc_s_results;
	FILE	*loc_p_handle;
	s8sod	loc_s8_chaine10[10];//au max on a besoin de 4+1 caracteres
	s32sod	loc_s32_temp;
	u8sod	loc_u8_result_test;
	
	loc_p_handle = NULL; //INIT
	loc_u8_result_test = FALSE; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */

	if (s32GetArgNb(loc_p_varlist) > 3)  
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_VTESTFINAL_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormVTestfinalFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			loc_u32_NumeroForm = (u32sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u32_NumeroForm < NB_MAX_FORM_VTESTFINAL)
			{
				switch(loc_u32_NumeroForm)
				{
					case FORM_VTESTFINAL_VALID_RST_STAT_CNX:
							//Lecture de la base de données
						s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
						if(FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
						{
							u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
						}
						else
						{
							switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
							{
								case MODE_RADIO_MODEM_STATION:
									break;
								case MODE_RADIO_MODEM_ACCESS_POINT:
									if(FALSE == u8FillConfigWifi(&s_html_cfg_eqpmt))
									{
										u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
									}
									break;
								case MODE_RADIO_MODEM_MONITOR:
								default:
									break;
							}
						}
						s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
								if(FALSE == u8FillExploitStationFile(&s_html_exploit.s_station))
								{
									u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
								}
								else
								{
									//on remet l'etat ancien de la connexion identique a l'etat actuel
									s_html_exploit.s_station.u8_old_statut_connexion = s_html_exploit.s_station.u8_statut_connexion;
									//on sauve la nouvelle exploitation
									u8EditExploitStationFile(&s_html_exploit.s_station);
								}
								s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
								
						}
						loc_u8_result_test = TRUE;
						break;
					case FORM_VTESTFINAL_VALID_TESTPING:
						//on efface le fichier /tmp/res_ping.txt
						CmdSystem_Generique("rm /tmp/res_ping.txt");
						//on lance le script /testping.sh
						CmdSystem_Generique("/etc/testping.sh > /tmp/res_ping.txt");
						loc_u8_result_test = TRUE;
						break;
					case FORM_VTESTFINAL_VALID_1:
						//on efface le fichier /tmp/res_ping.txt
						CmdSystem_Generique("rm /tmp/res_ping.txt");
						s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillDebugFile(&s_html_debug_global))
						{
							s_html_debug_global.u8_mode_test_final = (u8sod)atoi(loc_s_results.ps8_mode);
							s_html_debug_global.u8_cfg_test_final = (u8sod)atoi(loc_s_results.ps8_cfg_test);
							u8EditDebugFile(&s_html_debug_global);
						}
						s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem
						
						s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
						memset(&s_html_cfg_eqpmt,'\0',sizeof(S_STRUCT_CONFIGURATION)); //RAZ
						loc_u8_result_test = u8PassageConfigTest(&s_html_cfg_eqpmt, s_html_debug_global.u8_mode_test_final,s_html_debug_global.u8_cfg_test_final);
						s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
						break;
					case FORM_VTESTFINAL_VALID_PE:
						//configuration de la puissance emise
						s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillConfigWifi(&s_html_cfg_eqpmt))
						{
							s_html_cfg_eqpmt.s_wifi.u8_power_tx = (u8sod)atoi(loc_s_results.ps8_puissance_tx);
							if(TRUE==u8TestConfigWifi(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigWifi(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
						s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
						break;
					default:
						break;
				}
				if(FALSE == loc_u8_result_test)
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_CONFIG_KO);
					Html_GotoPage(ps8_pageHtmlRetour);
					return;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				Html_GotoPage("/cgi-bin/cgi_fh?URL=VTestFinal");
				return; // on sort!
			}
			else//CONDITION: page KO
			{
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return;
			}
		}
	}

	// Entrée au setup par mot de passe
	if(		(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
			||	(FALSE == s_html_global.u8_connexion_prioritaire_http)
	  )
	{
		PreparePagePswd("VTestFinal");
		return;  
	}

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	//base de donnee debug
	s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillDebugFile(&s_html_debug_global))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	else
	{
		switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_STATION:
				break;
			case MODE_RADIO_MODEM_ACCESS_POINT:
				if(FALSE == u8FillConfigWifi(&s_html_cfg_eqpmt))
				{
					u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
				}
				break;
			case MODE_RADIO_MODEM_MONITOR:
			default:
				break;
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem


	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
	switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
	{
		case MODE_RADIO_MODEM_STATION:
			if(FALSE == u8FillExploitStationFile(&s_html_exploit.s_station))
			{
				u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
			}
			break;
		case MODE_RADIO_MODEM_ACCESS_POINT:
			if(FALSE == u8FillExploitAccessPointFile(&s_html_exploit.s_access_point))
			{
				u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
			}
			break;
		case MODE_RADIO_MODEM_MONITOR:
		default:
			break;
	}
	if(FALSE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	
	html_tag("<HTML>\n");	

	// Header
	html_tag("<head> \n");
	html_tag("<title>Test: VTestFinal</title> \n");
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VTestFinal");	//pour la fonction Actualiser
	RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=VTestFinal_Dyn", (u32sod)u16GetTpsRefreshHtml()*1000);

	JSNumCheck();
	proc_JavaScript_VTestFinal();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","VTestFinal");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");


	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>Test: Test Final</P></TD></TR> \n");
	html_tag("<tr><td><P>Cette page permet de configurer l'equipement pour le test final usine.</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");




	html_tag("<tr><td><P class=undermenu>TEST FINAL USINE</P></td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");

	//Mode de fonctionnement (AP ou STA)
	html_tag("		<tr> \n");
	html_tag("			<td>Mode de fonctionnement</td> \n");
	html_tag("			<td><SELECT name=\"mode\" size=\"1\"> \n");
	html_tag("				<option %s value=\"%d\">POINT D'ACCES</option> \n",
			 ((MODE_AP_TF == s_html_debug_global.u8_mode_test_final) ? "selected" : ""),
			 MODE_AP_TF);
	html_tag("				<option %s value=\"%d\">STATION</option> \n",
			 ((MODE_STA_TF == s_html_debug_global.u8_mode_test_final) ? "selected" : ""),
			 MODE_STA_TF);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");

	html_tag("</table></td></tr> \n");

	
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//choix des conditions de test
	html_tag("<tr><td><table border=\"1\" cellpadding=\"1\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"580\">%s</th> \n",
			 ((MODE_AP_TF == s_html_debug_global.u8_mode_test_final) ? "Mode Point d'accès" : "Mode station"));
	html_tag("		</tr> \n");
#ifdef _WRM100_ABG_SELECT
	html_tag("		<tr><td><table border=\"0\" cellpadding=\"1\" cellspacing=\"1\">  \n");
	html_tag("			<tr><td><input type=\"radio\" %s name=\"cfg_test\" value=\"%d\" > Test de l'accès ANT1, bande 2.4GHz (ssid=wrm100, 802.11g, 54Mbps, pas de sécurité) \n",((ANT1_2_4G == s_html_debug_global.u8_cfg_test_final) ? "checked" : ""),ANT1_2_4G);
	html_tag("			<tr><td><input type=\"radio\" %s name=\"cfg_test\" value=\"%d\" > Test de l'accès ANT1, bande 5GHz (ssid=wrm100, 802.11a, 54Mbps, pas de sécurité)\n",((ANT1_5G == s_html_debug_global.u8_cfg_test_final) ? "checked" : ""),ANT1_5G);
	html_tag("			<tr><td><input type=\"radio\" %s name=\"cfg_test\" value=\"%d\" > Test de l'accès ANT2, bande 2.4GHz (ssid=wrm100, 802.11g, 54Mbps, pas de sécurité)\n",((ANT2_2_4G == s_html_debug_global.u8_cfg_test_final) ? "checked" : ""),ANT2_2_4G);
	html_tag("			<tr><td><input type=\"radio\" %s name=\"cfg_test\" value=\"%d\" > Test de l'accès ANT2, bande 5GHz (ssid=wrm100, 802.11a, 54Mbps, pas de sécurité)\n",((ANT2_5G == s_html_debug_global.u8_cfg_test_final) ? "checked" : ""),ANT2_5G);
	html_tag("			<tr><td>&nbsp;</td></tr> \n");
	html_tag("			<tr><td>&nbsp;<input type=\"button\" value=\"Application de la Config\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
			 FORM_VTESTFINAL_VALID_1);
	html_tag("		</table></td></tr> \n");
#endif
#ifdef _WRM100_N_SELECT
	html_tag("		<tr><td><table border=\"0\" cellpadding=\"1\" cellspacing=\"1\">  \n");
	html_tag("			<tr><td><input type=\"radio\" %s name=\"cfg_test\" value=\"%d\" > Test en bande 2.4GHz (ssid=wrm100, 802.11nght20, MCS3, 3antennes, pas de sécurité) \n",((ANT1_2_4G == s_html_debug_global.u8_cfg_test_final) ? "checked" : ""),ANT1_2_4G);
	html_tag("			<tr><td><input type=\"radio\" %s name=\"cfg_test\" value=\"%d\" > Test en bande 5GHz (ssid=wrm100, 802.11naht20, MCS3, 3antennes, pas de sécurité)\n",((ANT1_5G == s_html_debug_global.u8_cfg_test_final) ? "checked" : ""),ANT1_5G);
	html_tag("			<tr><td>&nbsp;</td></tr> \n");
	html_tag("			<tr><td>&nbsp;<input type=\"button\" value=\"Application de la Config\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
			 FORM_VTESTFINAL_VALID_1);
	html_tag("		</table></td></tr> \n");
#endif	
	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//les infos d'exploitation
	html_tag("<tr><td><table border=\"1\" cellpadding=\"1\" cellspacing=\"1\">  \n");
	html_tag("		<tr><th width=\"580\">%s</th></tr> \n",
			 ((MODE_AP_TF == s_html_debug_global.u8_mode_test_final) ? "Mode Point d'accès" : "Mode station"));
	html_tag("		<tr><td><table border=\"0\" cellpadding=\"1\" cellspacing=\"1\">  \n");
	switch (s_html_debug_global.u8_mode_test_final)
	{
		case MODE_AP_TF:
			//configuration de la puissance emise
			html_tag("	<tr>\n");
			html_tag("			<td>Puissance emise \n");
			html_tag("			<input type=\"text\" size=\"3\" maxlength=3 name=\"power\" value=%d onchange=\"return(JsChangePowerTx(form))\">&nbsp;dBm \n",
					 s_html_cfg_eqpmt.s_wifi.u8_power_tx);
			html_tag("			<input type=\"button\" value=\"Valider PE\" onclick=\"return SelectFormulaire(%d,form);\"></td> \n",
					 FORM_VTESTFINAL_VALID_PE);
			html_tag("	</tr>\n");

			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td>\n");
			html_tag("<pre>");
			HtmlPrint_TableClientWifi();
			html_tag("</pre>\n");
			html_tag("</td></tr> \n");

			break;
		case MODE_STA_TF:
			//Statut de la connexion
			html_tag("	<tr>\n");
			html_tag("		<td nowrap><B>Statut:</B></td>\n");
			if(STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_statut_connexion)
			{
				if (STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_old_statut_connexion)
				{ //en vert
					html_tag("		<td id=TD_STAT class=\"\">&nbsp;<span id=SPAN_STATUT>%s</span></td>\n",
							 pt_tb_msg[u8_html_langue].ps8_msg_choix_station_connexion[s_html_exploit.s_station.u8_statut_connexion]);
				}
				else
				{ //en orange
					html_tag("		<td id=TD_STAT class=\"orange\">&nbsp;<span id=SPAN_STATUT>%s</span></td>\n",
							 pt_tb_msg[u8_html_langue].ps8_msg_choix_station_connexion[s_html_exploit.s_station.u8_statut_connexion]);
				}
			}
			else
			{//en rouge
				html_tag("		<td id=TD_STAT class=\"rouge\">&nbsp;<span id=SPAN_STATUT>%s</span></td>\n",
						 pt_tb_msg[u8_html_langue].ps8_msg_choix_station_connexion[s_html_exploit.s_station.u8_statut_connexion]);				
			}
			html_tag("	</tr>\n");
			//RSSI
			html_tag("	<tr>\n");
			html_tag("		<td nowrap><B>RSSI  :</B></td>\n");
			if(STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_statut_connexion)
			{
				html_tag("		<td>&nbsp;<span id=SPAN_RSSI>%ld dBm</span></td>\n",
						 s_html_exploit.s_station.s32_rssi_dbm);
			}
			else
			{
				html_tag("		<td>&nbsp;<span id=SPAN_RSSI>? dBm</span></td>\n");
			}
			html_tag("	</tr>\n");
			//Temperature
			loc_s32_temp = s_html_exploit.s_general.s32_temperature;
			if(VALEUR_TEMPERATURE_INCONNUE == loc_s32_temp)
			{
				html_tag("	<tr>\n");
				html_tag("		<td nowrap><B>TEMP  :</B></td>\n");
				html_tag("		<td>&nbsp;<span id=SPAN_TEMP>??? °C</td>\n");
				html_tag("	</tr>\n");
			}
			else
			{
				html_tag("		<td nowrap><B>TEMP  :</B></td>\n");
				html_tag("		<td>&nbsp;<span id=SPAN_TEMP>%ld °C</td>\n",loc_s32_temp);
			}			
			html_tag("			<tr><td>&nbsp;<input type=\"button\" value=\"Reset statut connexion\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
					 FORM_VTESTFINAL_VALID_RST_STAT_CNX);


			
			//Test PING
			html_tag("		<tr><td nowrap><B>TEST PING</B></td></tr>\n");
			html_tag("	<tr><td>&nbsp;<input type=\"button\" value=\"Lancement du test ping\" onclick=\"return SelectFormulaire(%d,form);\"></td></tr> \n",
					 FORM_VTESTFINAL_VALID_TESTPING);
			if(NULL == (loc_p_handle = fopen( "/tmp/res_ping.txt", "rt" )))
			{
				html_tag("		<tr><td nowrap><B>TEST PING :</B></td>\n");
				html_tag("		<td>&nbsp;<span id=SPAN_PING>??? </td></tr>\n");
			}
			else
			{
				if (fgets(loc_s8_chaine10,5,loc_p_handle)!=NULL)
				{
					if (atoi(loc_s8_chaine10) == 0)
					{//test ok
						html_tag("		<tr><td nowrap><B>TEST PING :</B></td>\n");
						html_tag("		<td>&nbsp;<span id=SPAN_PING> OK </td></tr>\n");
					}
					else
					{//test ko
						html_tag("		<tr><td nowrap><B>TEST PING :</B></td>\n");
						html_tag("		<td>&nbsp;<span id=SPAN_PING> KO </td></tr>\n");
					}
				}
				//fermeture du fichier
				fclose (loc_p_handle);
			}
			
			break;
	}

	html_tag("		</table></td></tr> \n");
	html_tag("</table></td></tr> \n");
	
	html_tag("</form> \n");
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");


}/*VDebugTestFinal*/

//=====================================================================================
// Fonction		: u8PassageConfigTest
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u8_mode> : mode de test (AP ou STA)
//				: <loc_u8_cfg_test> : test (ANT1_2_4G ou ANT1_5G ou ANT2_2_4G ou ANT2_5G)
// Sortie		: <loc_u8_resultat>: TRUE si OK, sinon FALSE 
// Description	: passage en config pour le test final
//=====================================================================================
u8sod u8PassageConfigTest(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_mode, u8sod loc_u8_cfg_test)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE; //INIT
	
#ifdef _WRM100_ABG_SELECT
	//partie commune de la configuration
	*loc_ps_config = S_CONFIG_EQUIPEMENT_TEST_BASE;
	switch(loc_u8_mode)
	{
		case MODE_AP_TF:
			//on force le mode AP
			loc_ps_config->s_gene.u8_mode_radio_modem = MODE_RADIO_MODEM_ACCESS_POINT;
			//on passe l'adresse IP en 192.93.121.70
			loc_ps_config->s_gene.u32_bridge_adresse_ip = 0xC05D7946;
			//les autres paramètres restent ok
			break;
		case MODE_STA_TF:
			//rien a faire c'est la config de base!
			break;
		default:
			break;
	}
	switch (loc_u8_cfg_test)
	{
		case ANT1_2_4G:
			//passage en mode 802.11g
			loc_ps_config->s_wifi.u8_mode_802_11x = MODE_WIFI_802_11G;
			//canal milieu :
			loc_ps_config->s_wifi.u8_type_selection_canal=TYPE_SELECTION_CANAL_ISO;
			loc_ps_config->s_wifi.u16_iso_canal_radio=5;
			//Pemise par defaut
			loc_ps_config->s_wifi.u8_power_tx=POWER_TX_802_11X_DEFAULT;
			//debit à 54Mbits/s
			loc_ps_config->s_wifi.u8_data_rate=DATA_RATE_54_MBPS;
			break;
		case ANT1_5G:
			//passage en mode 802.11a
			loc_ps_config->s_wifi.u8_mode_802_11x = MODE_WIFI_802_11A;
			//canal milieu :
			loc_ps_config->s_wifi.u8_type_selection_canal=TYPE_SELECTION_CANAL_ISO;
			loc_ps_config->s_wifi.u16_iso_canal_radio=40;//5200MHz
			//Pemise par defaut
			loc_ps_config->s_wifi.u8_power_tx=POWER_TX_802_11X_DEFAULT;
			//debit à 54Mbits/s
			loc_ps_config->s_wifi.u8_data_rate=DATA_RATE_54_MBPS;
			break;
		case ANT2_2_4G:
			//passage en mode 802.11g
			loc_ps_config->s_wifi.u8_mode_802_11x = MODE_WIFI_802_11G;
			//canal milieu :
			loc_ps_config->s_wifi.u8_type_selection_canal=TYPE_SELECTION_CANAL_ISO;
			loc_ps_config->s_wifi.u16_iso_canal_radio=5;
			//Pemise par defaut
			loc_ps_config->s_wifi.u8_power_tx=POWER_TX_802_11X_DEFAULT;
			//debit à 54Mbits/s
			loc_ps_config->s_wifi.u8_data_rate=DATA_RATE_54_MBPS;
			//antenne 2 pour rx et tx
			loc_ps_config->s_wifi.u8_ant_ABG_tx_selection = ABG_SELECT_TX_ANTENNE_2;
			loc_ps_config->s_wifi.u8_ant_ABG_rx_selection = ABG_SELECT_RX_ANTENNE_2;
			break;
		case ANT2_5G :
			//passage en mode 802.11a
			loc_ps_config->s_wifi.u8_mode_802_11x = MODE_WIFI_802_11A;
			//canal milieu :
			loc_ps_config->s_wifi.u8_type_selection_canal=TYPE_SELECTION_CANAL_ISO;
			loc_ps_config->s_wifi.u16_iso_canal_radio=40;//5200MHz
			//Pemise par defaut
			loc_ps_config->s_wifi.u8_power_tx=POWER_TX_802_11X_DEFAULT;
			//debit à 54Mbits/s
			loc_ps_config->s_wifi.u8_data_rate=DATA_RATE_54_MBPS;
			//antenne 2 pour rx et tx
			loc_ps_config->s_wifi.u8_ant_ABG_tx_selection = ABG_SELECT_TX_ANTENNE_2;
			loc_ps_config->s_wifi.u8_ant_ABG_rx_selection = ABG_SELECT_RX_ANTENNE_2;
			break;
	}
#endif //_WRM100_ABG_SELECT
	
#ifdef _WRM100_N_SELECT
	//partie commune de la configuration
	*loc_ps_config = S_CONFIG_EQUIPEMENT_TEST_BASE;

	switch(loc_u8_mode)
	{
		case MODE_AP_TF:
			//on force le mode AP
			loc_ps_config->s_gene.u8_mode_radio_modem = MODE_RADIO_MODEM_ACCESS_POINT;
			//on passe l'adresse IP en 192.93.121.70
			loc_ps_config->s_gene.u32_bridge_adresse_ip = 0xC05D7946;
			//les autres paramètres restent ok
			break;
		case MODE_STA_TF:
			//rien a faire c'est la config de base!
			break;
		default:
			break;
	}
	switch (loc_u8_cfg_test)
	{
		case ANT1_2_4G:
			//passage en mode 802.11nght20
			loc_ps_config->s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NGHT20;
			//canal milieu :
			loc_ps_config->s_wifi.u8_type_selection_canal=TYPE_SELECTION_CANAL_ISO;
			loc_ps_config->s_wifi.u16_iso_canal_radio=5;
			//Pemise par defaut
			loc_ps_config->s_wifi.u8_power_tx=POWER_TX_802_11X_DEFAULT;
			//debit MCS3
			loc_ps_config->s_wifi.u8_data_rate=DATA_RATE_MCS3;
			//3antennes
			loc_ps_config->s_wifi.u8_ant_N_selection = N_SELECT_ANTENNES_1_ET_2_ET_3;

			break;
		case ANT1_5G:
			//passage en mode 802.11naht20
			loc_ps_config->s_wifi.u8_mode_802_11x = MODE_WIFI_802_11NAHT20;
			//canal milieu :
			loc_ps_config->s_wifi.u8_type_selection_canal=TYPE_SELECTION_CANAL_ISO;
			loc_ps_config->s_wifi.u16_iso_canal_radio=40;//5200MHz
			//Pemise par defaut
			loc_ps_config->s_wifi.u8_power_tx=POWER_TX_802_11X_DEFAULT;
			//debit MCS3
			loc_ps_config->s_wifi.u8_data_rate=DATA_RATE_MCS3;
			//3antennes
			loc_ps_config->s_wifi.u8_ant_N_selection = N_SELECT_ANTENNES_1_ET_2_ET_3;
			break;
		default:
			break;
	}

#endif	

	if(TRUE == u8TestConfigEquipement(loc_ps_config))
	{
		loc_u8_resultat = u8EditConfigEquipement(loc_ps_config);
	}

	return loc_u8_resultat;
}/*u8PassageConfigTest*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VTestFinal
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation de la structure de config de la page
//=====================================================================================
void InitModule_VTestFinal(void)
{
	
}/*InitModule_VTestFinal*/

