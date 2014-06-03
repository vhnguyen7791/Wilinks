/*========================================================================*/
/* NOM DU FICHIER  : sutime.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML mise à l'heure				  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE020 23/03/2010 CM
// - Correction w@rning dans FireFox "Element referencé par son ID/NAME ..."
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE037 06/07/2010 CM
// - Modification page HTML Admin - Mise à l'heure
//		-> surveillance etat NTP
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE060 16/03/2011
// - Ajout configuration date/heure au démarrage de l'équipement
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _SUTIME

enum LISTE_DES_FORM_SUTIME
{
	FORM_SUTIME_VALID_1 = 1,
	FORM_SUTIME_VALID_2,
	FORM_SUTIME_VALID_MODE_12H_24H,
	FORM_SUTIME_VALID_3,
	
	NB_MAX_FORM_SUTIME
};


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


typedef struct {
	s8sod	ps8_Year			[4 + 1];	// input SELECT	
	s8sod	ps8_Month			[2 +1];		// input SELECT
	s8sod	ps8_Day				[2 + 1];	// input SELECT
	s8sod	ps8_Hour			[2 + 1];	// input SELECT
	s8sod	ps8_Min				[2 + 1];	// input SELECT
	s8sod	ps8_Sec				[2 + 1];	// input SELECT

	s8sod	ps8_format			[2 + 1];

	s8sod	ps8_startYear		[4 + 1];	// input SELECT	
	s8sod	ps8_startMonth		[2 +1];		// input SELECT
	s8sod	ps8_startDay		[2 + 1];	// input SELECT
	
	s8sod	ps8_modeMAH			[10 + 1];
	s8sod	ps8_AdrNtpServerPrincipal	[MAX_LG_FORMAT_ADRESSE_IP + 1];	// input TEXT
	s8sod	ps8_AdrNtpServerSecours		[MAX_LG_FORMAT_ADRESSE_IP + 1];	// input TEXT
	s8sod	ps8_ntpTimeZone		[15 + 1];	// input SELECT
	s8sod	ps8_FreqMajHeureSntp	[3+1];		// input TEXT

	s8sod	ps8_hidden1			[10 + 1];
} S_TIMER_RESULTS;

FIELD_LIST s_TimerFields[] = {
	{"year",				"%s",		offsetof(S_TIMER_RESULTS, ps8_Year)	},
	{"month",				"%s",		offsetof(S_TIMER_RESULTS, ps8_Month)	},
	{"day",					"%s",		offsetof(S_TIMER_RESULTS, ps8_Day)	},
	{"hour",				"%s",		offsetof(S_TIMER_RESULTS, ps8_Hour)	},
	{"min",					"%s",		offsetof(S_TIMER_RESULTS, ps8_Min)	},
	{"sec",					"%s",		offsetof(S_TIMER_RESULTS, ps8_Sec)	},
	{"format",				"%s",		offsetof(S_TIMER_RESULTS, ps8_format)	},

	{"StartYear",			"%s",		offsetof(S_TIMER_RESULTS, ps8_startYear)	},
	{"StartMonth",			"%s",		offsetof(S_TIMER_RESULTS, ps8_startMonth)	},
	{"StartDay",			"%s",		offsetof(S_TIMER_RESULTS, ps8_startDay)	},
	
	{"modeMAH",				"%s",		offsetof(S_TIMER_RESULTS, ps8_modeMAH)},
	{"AdrNtpPrincipal",		"%s",		offsetof(S_TIMER_RESULTS, ps8_AdrNtpServerPrincipal)},
	{"AdrNtpSecours",		"%s",		offsetof(S_TIMER_RESULTS, ps8_AdrNtpServerSecours)},
	{"ntpTimeZone",			"%s",		offsetof(S_TIMER_RESULTS, ps8_ntpTimeZone)	},
	{"FreqMajHeureSntp",	"%s",		offsetof(S_TIMER_RESULTS, ps8_FreqMajHeureSntp)	},

	{"hidden1",				"%s",		offsetof(S_TIMER_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction	: proc_SetTime
// Entrees	: time
// Sortie	: 
// Description	: Changement de l'heure système
//=====================================================================================
void proc_SetTime(S_TIMER_RESULTS *s_Results);

//=====================================================================================
// Fonction	: TimerHourSelectList
// Entrees	: <loc_s32_Hour>
//			  <loc_ps8_namep<
// Sortie	: rien
// Description	: Affiche la select List pour Heure
//=====================================================================================
void TimerHourSelectList(s32sod loc_s32_Hour, s8sod *loc_ps8_namep);

//=====================================================================================
// Fonction		: proc_JavaScript_SUTime
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/06/2007
// Description	: code de javascript de la page HTML SUTime
//=====================================================================================
void proc_JavaScript_SUTime(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: SUtime_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 08/07/2010
// Description	: Page rafraichissement page Admin Mise à l'heure
//				"URL=VExploitGeneral_Dyn
//=====================================================================================
void SUtime_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
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

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
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


	//On surveille le mode de mise à l'heure
	html_tag("|");
	html_tag("&&&id:SPAN_CFG_MODE_MAH_%d&&&innerHTML:&&&",
			 s_html_cfg_eqpmt.s_admin.u8_mode_mah);
	
	//Présence serveur NTP
	switch(s_html_cfg_eqpmt.s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
		case MODE_MAH_SNTP:
			html_tag("|");
			html_tag("&&&id:SPAN_PRESENCE_NTP_%d&&&innerHTML:&&&",
					 ((TRUE == s_html_exploit.s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_PRINCIPAL])||
					  ((ADRESSE_IP_NULLE != s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])&&
					   (TRUE == s_html_exploit.s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_SECOURS])
					  )
					 ));
			break;
		case MODE_MAH_MANUELLE:
		default:
			break;
	}

	html_tag("|");


}/*SUtime_Dyn*/

//=====================================================================================
// Fonction		: SUtime
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Page de Mise à l'heure
//=====================================================================================
void SUtime(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{	
	S_TIMER_RESULTS	loc_s_results;
	s8sod			loc_ps8_emsg[50];
	s16sod			loc_s16_i;
	time_t			loc_s_time_t;
	struct tm		loc_s_tm;
	s32sod			loc_s32_sem;
	s8sod			loc_s8_i;
	u8sod			loc_u8_numForm;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_i;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;			/* Init loc */

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUtime");
		return;  
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=SUtime&hidden1=<numForm>
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_TIMER_RESULTS));
		
		// Décodage de la requête
		if (!form_decode(s_TimerFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
			//on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{

			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUTIME)
			{
				if(FORM_SUTIME_VALID_MODE_12H_24H == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_admin.u8_mode_date_heure = (u8sod)atoi(loc_s_results.ps8_format);
						if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUTIME_VALID_1 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
					{
						if(MODE_MAH_MANUELLE == s_html_cfg_eqpmt.s_admin.u8_mode_mah)	//CONDITION: mode mise à l'heure manuelle
						{
							//mise à l'heure manuelle
							proc_SetTime(&loc_s_results);
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
					loc_u8_result_test = TRUE;
				}
				
				if(FORM_SUTIME_VALID_2 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_admin.u8_mode_mah = (u8sod)atoi(loc_s_results.ps8_modeMAH);
						switch(s_html_cfg_eqpmt.s_admin.u8_mode_mah)
						{
							case MODE_MAH_NTP:
							case MODE_MAH_SNTP:
								s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL] = u32DecodageAdresseReseau(loc_s_results.ps8_AdrNtpServerPrincipal, &loc_u8_ret);
								s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS] = u32DecodageAdresseReseau(loc_s_results.ps8_AdrNtpServerSecours, &loc_u8_ret);
								s_html_cfg_eqpmt.s_admin.s_client_ntp.s8_fuseau_horaire = (s8sod)atoi(loc_s_results.ps8_ntpTimeZone);
								break;
							case MODE_MAH_MANUELLE:
							default:
								break;
						}
						if(MODE_MAH_SNTP == s_html_cfg_eqpmt.s_admin.u8_mode_mah)	//CONDITION: mode mise à l'heure manuelle
						{
							s_html_cfg_eqpmt.s_admin.s_client_ntp.u16_freq_maj_sntp = (u16sod)atoi(loc_s_results.ps8_FreqMajHeureSntp);
						}
						if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUTIME_VALID_3 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_admin.s_date_demarrage.u16_annee = (u16sod)atoi(loc_s_results.ps8_startYear);
						s_html_cfg_eqpmt.s_admin.s_date_demarrage.u8_mois = (u8sod)atoi(loc_s_results.ps8_startMonth);
						s_html_cfg_eqpmt.s_admin.s_date_demarrage.u8_jour = (u8sod)atoi(loc_s_results.ps8_startDay);
						if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
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
				}
				else
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_RELOAD_SUTIME_ET_RELOAD_FRAME_A);
				}
				Html_GotoPage(ps8_pageHtmlRetour);
				return; // on sort!
			}
		}
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
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

	
	// Get Local Time
	time(&loc_s_time_t);
	loc_s_tm = *localtime((const time_t *)(&loc_s_time_t));
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration_date);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");
	
	html_tag("<body onload=\"return(StartJavaScript());\"> \n");
	
	JSActualiser("/cgi-bin/cgi_fh?URL=SUtime");	//pour la fonction Actualiser
	RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=SUtime_Dyn", (u32sod)u16GetTpsRefreshHtml()*1000);
	
	// Javascript pour chgt format heure selon English ou Latin
	Hour_Javascript();
	
	// Javascript pour chgt format jour selon mois sélectionné
	Day_Javascript();
	
	proc_JavaScript_SUTime(&s_html_cfg_eqpmt);

	
#if CLIENT_NTP_ACTIF
	JSNumCheck();
	JSIPCheck();

#endif
	
	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"timer\" target=\"frame_c\"> \n");
	form_hidden("URL","SUtime");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");
	html_tag("\n");
	
	
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_mise_a_heure);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_mise_a_heure);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

#if CLIENT_NTP_ACTIF
	//On surveille le mode de mise à l'heure
	html_tag("<span id=SPAN_CFG_MODE_MAH_%d></span> \n",
			 s_html_cfg_eqpmt.s_admin.u8_mode_mah);
	
	//Présence serveur NTP
	switch(s_html_cfg_eqpmt.s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
		case MODE_MAH_SNTP:
			//On surveille l'etat du serveur NTP
			html_tag("<span id=SPAN_PRESENCE_NTP_%d></span> \n",
					 ((TRUE == s_html_exploit.s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_PRINCIPAL])||
					  ((ADRESSE_IP_NULLE != s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])&&
					   (TRUE == s_html_exploit.s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_SECOURS])
					  )
					 ));
			if((TRUE == s_html_exploit.s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_PRINCIPAL])||
			   ((ADRESSE_IP_NULLE != s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])&&
				  (TRUE == s_html_exploit.s_general.pu8_presence_serveur_ntp[SERVEUR_NTP_SECOURS]))
			  )	//CONDITION: au moins un serveur fiable 
			{
				;
			}
			else
			{
				html_tag("<TR><TD>&nbsp;<P class=warning><B>%s!</B> %s</P></TD></TR> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_attention,
						 pt_tb_msg[u8_html_langue].ps8_msg_aucun_serveur_NTP);
				html_tag("<tr><td>&nbsp;</td></tr> \n");
			}
			break;
		case MODE_MAH_MANUELLE:
		default:
			break;
	}
#endif

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//Sélection de la mise à l'heure
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration_date_demarrage);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;%s</td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_info_perte_heure_sur_am_equipement);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellspacing=\"1\"> \n");
	html_tag("<tr> \n");
	html_tag("		<th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_annee);
	html_tag("		<th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mois);
	html_tag("	    <th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_jour);
	html_tag("</tr> \n");
	html_tag("<tr> \n");
	//annee
	html_tag("      <td><select name=\"StartYear\" size=\"1\" onchange=\"JSChangeDay(timer.StartYear, timer.StartMonth, timer.StartDay)\"> \n");
	CreateHtmlListOptionYear(s_html_cfg_eqpmt.s_admin.s_date_demarrage.u16_annee);
	html_tag("</select> </td>\n");
	//mois
	html_tag("      <td><select name=\"StartMonth\" size=\"1\" onchange=\"JSChangeDay(timer.StartYear, timer.StartMonth, timer.StartDay)\"> \n");
	CreateHtmlListOptionMonth(s_html_cfg_eqpmt.s_admin.s_date_demarrage.u8_mois);
	html_tag("</select> </td>\n");
	//Jour
	html_tag("      <td><select name=\"StartDay\" size=\"1\"> \n");
	CreateHtmlListOptionDay(s_html_cfg_eqpmt.s_admin.s_date_demarrage.u16_annee, s_html_cfg_eqpmt.s_admin.s_date_demarrage.u8_mois, s_html_cfg_eqpmt.s_admin.s_date_demarrage.u8_jour);
	html_tag("</select></td> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,timer)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUTIME_VALID_3);
	
	//Sélection de la mise à l'heure
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_selection_mise_a_heure);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"80\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Mode de la mise à l'heure
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_mise_a_heure);
	html_tag("			<td><SELECT name=\"modeMAH\" size=\"1\" onchange=\"return(JsChangeModeMAH())\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_MODES_MAH;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_admin.u8_mode_mah) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_mah[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("		<tr> \n");
	html_tag("			<th colspan=2>&nbsp;</th> \n");
	html_tag("		</tr> \n");
	//Adresse du serveur NTP (principal)
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_serveur_ntp);
	html_tag("<td><input type=\"text\" size=\"15\" name=\"AdrNtpPrincipal\" value=\"%s\" width=\"15\" onchange=\"return(JsTestAdresseIpNtpPrincipal())\"></td> \n",
			 ps8GetStringIp((s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])));
	html_tag("		</tr>\n");
	//Adresse du serveur NTP (secours)
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_serveur_ntp_secours);
	html_tag("<td><input type=\"text\" size=\"15\" name=\"AdrNtpSecours\" value=\"%s\" width=\"15\" onchange=\"return(JsTestAdresseIpNtpSecours())\"></td> \n",
			 ps8GetStringIp((s_html_cfg_eqpmt.s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])));
	html_tag("		</tr>\n");
	// Fuseau horaire
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_fuseau_horaire);
	html_tag("			<td><SELECT name=ntpTimeZone> \n");
	for(loc_s8_i=VALEUR_MIN_FUSEAU_HORAIRE; loc_s8_i<=VALEUR_MAX_FUSEAU_HORAIRE; loc_s8_i++)
	{
		html_tag("<OPTION %s VALUE=%d>GMT ",
				 ((loc_s8_i == s_html_cfg_eqpmt.s_admin.s_client_ntp.s8_fuseau_horaire) ? "SELECTED" : ""),
				 loc_s8_i);
		if(0 > loc_s8_i)
		{
			html_tag("%d %s",
					 loc_s8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_heure);
		}
		if(0 < loc_s8_i)
		{
			html_tag("+%d %s",
					 loc_s8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_heure);
		}
		if((-1 > loc_s8_i) || (1 < loc_s8_i))
		{
			html_tag("s");
		}
		html_tag("</OPTION>\n");
	}
	html_tag("		</select></td> \n");
	html_tag("		</tr>\n");
	//Frequence de mise à jour
	html_tag("		<tr id=FREQ_MAJ_SNTP> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_freq_mah_sntp);
	html_tag("			<TD><input align=\"center\" type=\"text\" name=\"FreqMajHeureSntp\" size=\"5\" value=\"%d\" onchange=return(isInteger(this,%d,%d))></TD> \n",
			 s_html_cfg_eqpmt.s_admin.s_client_ntp.u16_freq_maj_sntp,
			 VALEUR_MIN_FREQ_MAJ_HEURE_SNTP,
			 VALEUR_MAX_FREQ_MAJ_HEURE_SNTP);
	html_tag("		</tr>\n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,timer)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUTIME_VALID_2);
	
	//Format heure
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_notation_heure);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"> \n");
	html_tag("<tr> \n");
	html_tag("	<td width=\"100\"><input type=\"radio\" %s name=\"format\" value=\"%d\" \n",
			 (MODE_DATE_HEURE_12H == s_html_cfg_eqpmt.s_admin.u8_mode_date_heure)? "checked" : "",
			 MODE_DATE_HEURE_12H);
	html_tag("		onclick=\"JSChangeHour(timer)\"><b>12 %s</b></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_heures);
	html_tag("	<td><input type=\"radio\" %s name=\"format\" value=\"%d\" \n",
			 (MODE_DATE_HEURE_24H == s_html_cfg_eqpmt.s_admin.u8_mode_date_heure)? "checked" : "",
			 MODE_DATE_HEURE_24H);
	html_tag("		onclick=\"JSChangeHour(timer)\"><b>24 %s</b></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_heures);
	html_tag("</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,timer)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUTIME_VALID_MODE_12H_24H);
	
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mah_manuel);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P>%s</td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mah_manuel_sous_titre);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	//Table Date / Heure
	html_tag("<tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"> \n");
	html_tag("<tr><td><table border=\"1\" cellspacing=\"1\"> \n");
	html_tag("<tr> \n");
	html_tag("		<th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_annee);
	html_tag("		<th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mois);
	html_tag("	    <th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_jour);
	html_tag("</tr> \n");
	html_tag("<tr> \n");
	//annee
	html_tag("      <td><select name=\"year\" size=\"1\" onchange=\"JSChangeDay(timer.year, timer.month, timer.day)\"> \n");
	CreateHtmlListOptionYear(loc_s_tm.tm_year+1900);
	html_tag("</select> </td>\n");
	
	//mois
	html_tag("      <td><select name=\"month\" size=\"1\" onchange=\"JSChangeDay(timer.year, timer.month, timer.day)\"> \n");
	CreateHtmlListOptionMonth(loc_s_tm.tm_mon+1);
	html_tag("</select> </td>\n");
	
	//Jour
	html_tag("      <td><select name=\"day\" size=\"1\"> \n");
	CreateHtmlListOptionDay(loc_s_tm.tm_year, (loc_s_tm.tm_mon+1), loc_s_tm.tm_mday);
	html_tag("</select></td> \n");
	
	html_tag("</table></td> \n");
	html_tag("<td>&nbsp;</td> \n");
	
	html_tag("<td><table border=\"1\" cellspacing=\"1\"> \n");
	html_tag("<tr> \n");
	html_tag("		<th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_heure);
	html_tag("		<th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_minute);
	html_tag("	    <th width=\"80\" ><b>%s</b></th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_seconde);
	html_tag("</tr> \n");
	
	html_tag("<tr> \n");
	//Heure
	TimerHourSelectList((s32sod)loc_s_tm.tm_hour, "hour");
	//Minute
	html_tag("      <td><select name=\"min\" size=\"1\"> \n");
	for(loc_s16_i=0; loc_s16_i<60; loc_s16_i++)
	{	
		html_tag("<OPTION");
		if(loc_s16_i == loc_s_tm.tm_min)
		{
			html_tag(" SELECTED>");
		}
		else
		{
			html_tag(">");
		}
		if(loc_s16_i<10)
		{
			html_tag("0%d\n", loc_s16_i);
		}
		else
		{
			html_tag("%d\n", loc_s16_i);
		}
	}
	html_tag("</select> \n");
	html_tag("</TD>");
	
	//Seconde
	html_tag("      <td><select name=\"sec\" size=\"1\"> \n");
	for(loc_s16_i=0; loc_s16_i<60; loc_s16_i++)
	{	
		html_tag("<OPTION");
		if(loc_s16_i == loc_s_tm.tm_sec)
		{
			html_tag(" SELECTED>");
		}
		else
		{
			html_tag(">");
		}
		if(loc_s16_i<10)
		{
			html_tag("0%d\n", loc_s16_i);
		}
		else
		{
			html_tag("%d\n", loc_s16_i);
		}
	}
	html_tag("</select> \n");
	html_tag("</td></tr>");
	
	html_tag("</tr> \n");
	html_tag("</table></td></tr> \n");
	
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr> \n");
	html_tag("<td><input type=\"reset\"	value=\"%s\" onclick=\"return setCurrent(timer);\"> </td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mah_systeme_PC);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,timer)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUTIME_VALID_1);

	html_tag("</form> \n");
	
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
	
}/*SUtime*/

//=====================================================================================
// Fonction		: CreateHtmlListOptionYear
// Entrees		: <loc_u16_cfg_year>: config année
// Sortie		: rien
// Description	: Création html des options de la boite "année"
//=====================================================================================
void CreateHtmlListOptionYear(u16sod loc_u16_cfg_year)
{
	s16sod loc_s16_i;
	
	for(loc_s16_i=2000; loc_s16_i<2038; loc_s16_i++)
	{	
		html_tag("<OPTION");
		if(loc_s16_i == loc_u16_cfg_year)
		{
			html_tag(" SELECTED VALUE='%d'>", loc_s16_i);
		}
		else
		{
			html_tag(" VALUE='%d'>", loc_s16_i);
		}
		html_tag("%d\n", loc_s16_i);
	}
}/*CreateHtmlListOptionYear*/

//=====================================================================================
// Fonction		: CreateHtmlListOptionMonth
// Entrees		: <loc_u16_cfg_month>: config mois
// Sortie		: rien
// Description	: Création html des options de la boite "mois"
//=====================================================================================
void CreateHtmlListOptionMonth(u16sod loc_u16_cfg_month)
{
	s16sod loc_s16_i;

	for(loc_s16_i=1; loc_s16_i<13; loc_s16_i++)
	{	
		html_tag("<OPTION");
		if(loc_s16_i==loc_u16_cfg_month)
		{
			html_tag(" SELECTED>");
		}
		else
		{
			html_tag(">");
		}
		if(loc_s16_i<10)
		{
			html_tag("0%d\n", loc_s16_i);
		}
		else
		{
			html_tag("%d\n", loc_s16_i);
		}
	}
}/*CreateHtmlListOptionMonth*/

//=====================================================================================
// Fonction		: CreateHtmlListOptionDay
// Entrees		: <loc_u16_cfg_year>: config année
//				: <loc_u8_cfg_month>: config mois
//				: <loc_u8_cfg_day>: config jour
// Sortie		: rien
// Description	: Création html des options de la boite "jour"
//=====================================================================================
void CreateHtmlListOptionDay(u16sod loc_u16_cfg_year, u8sod loc_u8_cfg_month, u8sod loc_u8_cfg_day)
{
	s16sod loc_s16_i;

	switch (loc_u8_cfg_month)
	{
		// Cas particulier du mois de Février 
		case 2:		// February
		{
			// Cas année bissextile ou pas 
			if( ((0==(loc_u16_cfg_year%4))&&(0!=(loc_u16_cfg_year%100)))||
				  (0==(loc_u16_cfg_year%400))
			  )
			{
				// année BISSEXTILE, 29 jours 
				for(loc_s16_i=1; loc_s16_i<30 ; loc_s16_i++)
				{
					html_tag("<OPTION");
					if(loc_s16_i == loc_u8_cfg_day)
					{
						html_tag(" SELECTED>");
					}
					else
					{
						html_tag(">");
					}
					if(loc_s16_i<10)
					{
						html_tag("0%d\n", loc_s16_i);
					}
					else
					{
						html_tag("%d\n", loc_s16_i);
					}
				}
			}
			else
			{
				// année non BISSEXTILE, 28 jours
				for(loc_s16_i=1; loc_s16_i<29 ; loc_s16_i++)
				{
					html_tag("<OPTION");
					if(loc_s16_i == loc_u8_cfg_day)
					{
						html_tag(" SELECTED>");
					}
					else
					{
						html_tag(">");
					}
					if(loc_s16_i<10)
					{
						html_tag("0%d\n", loc_s16_i);
					}
					else
					{
						html_tag("%d\n", loc_s16_i);
					}
				}

			} 

		}		
		break;

		// Mois avec 31 jours 
		case 1:		// January
		case 3:		// March
		case 5:		// May
		case 7:		// July
		case 8:		// August
		case 10:	// October
		case 12:	// December
		{
			for(loc_s16_i=1; loc_s16_i<32 ; loc_s16_i++)
			{
				html_tag("<OPTION");
				if(loc_s16_i == loc_u8_cfg_day)
				{
					html_tag(" SELECTED>");
				}
				else
				{
					html_tag(">");
				}
				if(loc_s16_i<10)
				{
					html_tag("0%d\n", loc_s16_i);
				}
				else
				{
					html_tag("%d\n", loc_s16_i);
				}
			}

		}		
		break;

		// Mois avec 30 jours 
		case 4:		// April
		case 6:		// June
		case 9:		// September
		case 11:	// November
		{
			for(loc_s16_i=1; loc_s16_i<31 ; loc_s16_i++)
			{
				html_tag("<OPTION");
				if(loc_s16_i == loc_u8_cfg_day)
				{
					html_tag(" SELECTED>");
				}
				else
				{
					html_tag(">");
				}
				if(loc_s16_i<10)
				{
					html_tag("0%d\n", loc_s16_i);
				}
				else
				{
					html_tag("%d\n", loc_s16_i);
				}
			}

		}		
		break;

		default: 
			break;

	}	// switch(...)
	
}/*CreateHtmlListOptionDay*/

//=====================================================================================
// Fonction	: Day_Javascript
// Entrees	: rien
// Sortie	: rien
// Description	: Quand on change de "month", on aligne "day" à 28,29,30 ou 31 jours
//=====================================================================================
void Day_Javascript(void)
{
	html_tag("<script language=\"JavaScript\">\n");

	html_tag("function JSChangeDay(boxyear, boxmonth, boxday)\n" );
	html_tag("{\n");
	html_tag("var loc_year;\n");

	html_tag("var day_selected = 0;\n");

	html_tag("day_selected = boxday.selectedIndex;\n");


			 /* On efface la select list "day" */
	html_tag("for(i=0; i < boxday.length ; i++)\n");
	html_tag("{\n");
	html_tag("	 boxday.options[i] = null;\n");
	html_tag("}\n");
	html_tag("boxday.length = 0;\n");


	html_tag("switch (boxmonth.selectedIndex + 1)\n");
	html_tag("{\n");

			 /* Cas particulier du mois de Février */
	html_tag("case 2:\n");		// February
	html_tag("{\n");
	html_tag("	loc_year = parseInt(boxyear.options[boxyear.selectedIndex].value); // année entrée\n");

			 /* cas année bissextile ou pas */
	html_tag("	if( ( (loc_year%%4)==0 && (loc_year%%100)!=0 ) || (loc_year%%400)==0 )	\n");
	html_tag("	{\n");
			 /* année BISSEXTILE */
	html_tag("		for(i=0; i<29 ; i++)\n");
	html_tag("		{	if((i+1)<10)\n");
	html_tag("				boxday.options[i] = new Option(\"0\" + (i+1), i+1);\n");
	html_tag("			else\n");
	html_tag("				boxday.options[i] = new Option(i+1, i+1);\n");
	html_tag("		}\n");
	html_tag("		if(day_selected < boxday.length)\n");
	html_tag("			boxday.selectedIndex = day_selected;\n");
	html_tag("		else\n");
	html_tag("			boxday.selectedIndex = 0;\n");
	html_tag("	}\n");
	html_tag("	else\n");
	html_tag("	{\n");
			 /* année non BISSEXTILE*/
	html_tag("		for(i=0; i<28 ; i++)\n");
	html_tag("		{	if((i+1)<10)\n");
	html_tag("				boxday.options[i] = new Option(\"0\" + (i+1), i+1);\n");
	html_tag("			else\n");
	html_tag("				boxday.options[i] = new Option(i+1, i+1);\n");
	html_tag("		}\n");
	html_tag("		if(day_selected < boxday.length)\n");
	html_tag("			boxday.selectedIndex = day_selected;\n");
	html_tag("		else\n");
	html_tag("			boxday.selectedIndex = 0;\n");
	html_tag("	}\n");

	html_tag("} break;\n");

			 /* Mois avec 31 jours */
	html_tag("case 1:\n");		// January
	html_tag("case 3:\n");		// March
	html_tag("case 5:\n");		// May
	html_tag("case 7:\n");		// July
	html_tag("case 8:\n");		// August
	html_tag("case 10:\n");		// October
	html_tag("case 12:\n");		// December
	html_tag("{\n");
	html_tag("	for(i=0; i<31 ; i++)\n");
	html_tag("	{	if((i+1)<10)\n");
	html_tag("			boxday.options[i] = new Option(\"0\" + (i+1), i+1);\n");
	html_tag("		else\n");
	html_tag("			boxday.options[i] = new Option(i+1, i+1);\n");
	html_tag("	}\n");
	html_tag("	if(day_selected < boxday.length)\n");
	html_tag("		boxday.selectedIndex = day_selected;\n");
	html_tag("	else\n");
	html_tag("		boxday.selectedIndex = 0;\n");
	html_tag("} break;\n");

			 /* Mois avec 30 jours */
	html_tag("case 4:\n");		// April
	html_tag("case 6:\n");		// June
	html_tag("case 9:\n");		// September
	html_tag("case 11:\n");		// November
	html_tag("{\n");
	html_tag("	for(i=0; i<30 ; i++)\n");
	html_tag("	{	if((i+1)<10)\n");
	html_tag("			boxday.options[i] = new Option(\"0\" + (i+1), i+1);\n");
	html_tag("		else\n");
	html_tag("			boxday.options[i] = new Option(i+1, i+1);\n");
	html_tag("	}\n");
	html_tag("	if(day_selected < boxday.length)\n");
	html_tag("		boxday.selectedIndex = day_selected;\n");
	html_tag("	else\n");
	html_tag("		boxday.selectedIndex = 0;\n");
	html_tag("} break;\n");

	html_tag("default: break;\n");
	html_tag("}\n");	// switch(...)


	html_tag("}\n");	// function
	html_tag("</script>\n");
}/*Day_Javascript*/


//=====================================================================================
// Fonction	: Hour_Javascript
// Entrees	: rien
// Sortie	: rien
// Description	: Quand on change le format -> répercussion sur heure
//=====================================================================================
void Hour_Javascript(void)
{
	
	html_tag("<script language=\"JavaScript\">\n");

	html_tag("function JSChangeHour(form)\n");
	html_tag("{\n" );
	html_tag("var hour_selected = 0;\n");
	html_tag("hour_selected = form.hour.options[form.hour.selectedIndex].value;\n");
				/* On efface les choix de la select list */
	html_tag("for(i=0; i<form.hour.length; i++)\n");
	html_tag("{\n");
	html_tag("	form.hour.options[i] = null;\n");
	html_tag("}\n");

	html_tag("form.hour.length = 0;\n");

				/* Cas où mode 12H coché */
	html_tag("if(form.format[0].checked)\n");
	html_tag("{\n");
	html_tag("form.hour.options[0] = new Option(\"12 AM\", 0);\n");
	html_tag("for(i=1; i<12; i++) \n");
	html_tag("{ \n");
	html_tag("if(i<10) \n");
	html_tag("form.hour.options[i] = new Option(\"0\" + i + \" AM\", i);\n");
	html_tag("else \n");
	html_tag("form.hour.options[i] = new Option( i + \" AM\", i); \n");
	html_tag("}\n");
	html_tag("form.hour.options[12] = new Option(\"12 PM\", 12); \n");
	html_tag("for(i=1; i<12; i++) \n");
	html_tag("{\n");
	html_tag("if(i<10) \n");
	html_tag("form.hour.options[i+12] = new Option(\"0\" + i + \" PM\", i+12); \n");
	html_tag("else \n");
	html_tag("form.hour.options[i+12] = new Option(i + \" PM\", i+12); \n");
	html_tag("}\n");
	html_tag("for(i=0; i<form.hour.length; i++) \n");
	html_tag("{\n");
	html_tag("if(form.hour.options[i].value == hour_selected) \n");
	html_tag("{\n");
	html_tag("form.hour.selectedIndex = i; \n");
	html_tag("break; \n");
	html_tag("}\n");
	html_tag("}\n");
	html_tag("}\n");


				/* Cas où mode 24H coché */
	html_tag("if(form.format[1].checked)\n");
	html_tag("{\n");

	html_tag("for(i=0; i<24; i++)\n");
	html_tag("{\n");
	html_tag("	if(i<10)\n");
	html_tag("		form.hour.options[i] = new Option(\"0\" + i, i);\n");
	html_tag("	else\n");
	html_tag("		form.hour.options[i] = new Option( i, i);\n");
	html_tag("}\n"	);

					 // On sélectionne la bonne heure
	html_tag("for(i=0; i<form.hour.length; i++)\n");
	html_tag("{\n");
	html_tag("	if(form.hour.options[i].value == hour_selected)\n");
	html_tag("	{ \n");
	html_tag("		form.hour.selectedIndex = i;\n");
	html_tag("		break;\n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("}\n");

	html_tag("}\n");
	
	html_tag("</script>\n");
}/*Hour_Javascript*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUTime
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/06/2007
// Description	: code de javascript de la page HTML SUTime
//=====================================================================================
void proc_JavaScript_SUTime(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	html_tag("<script language=\"JavaScript\">\n");
	
	//Fonction javascript : setCurrent
	//*************************************
	html_tag("function setCurrent(timer)\n");
	html_tag("{ \n");
	html_tag("	var now; \n");
	html_tag("	localnow = new Date();  \n");
	html_tag("	now = new Date(localnow - (60000 * localnow.getTimezoneOffset()));  \n");
	html_tag("	with(document.timer) \n");
	html_tag("	{ \n");
	html_tag("		year.selectedIndex = now.getUTCFullYear() - 2000; \n");
	html_tag("		month.selectedIndex = Number(now.getUTCMonth()); \n");
	html_tag("		day.selectedIndex = Number(now.getUTCDate()) - 1; \n");
	html_tag("		hour.selectedIndex = Number(now.getUTCHours()); \n");
	html_tag("		min.selectedIndex = Number(now.getUTCMinutes()); \n");
	html_tag("		sec.selectedIndex = Number(now.getUTCSeconds()); \n");
	html_tag("		JSChangeDay(timer.year, timer.month, timer.day); \n");
	html_tag("		JSChangeHour(timer); \n");
	html_tag("	} \n");
	html_tag("	return false; \n");
	html_tag("} \n");

	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,timer) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true;\n");
	html_tag("	switch(i_numForm)\n");
	html_tag("	{\n");
	html_tag("		case %d:\n",FORM_SUTIME_VALID_1);
	html_tag("			if((%d != timer.modeMAH.value)||(%d))\n",MODE_MAH_MANUELLE,(MODE_MAH_MANUELLE != loc_ps_config->s_admin.u8_mode_mah));
	html_tag("			{\n");
	html_tag("				alert(\"%s\"); \n",pt_tb_msg[u8_html_langue].ps8_msg_error_mah_manuel);
	html_tag("				loc_result = false;	\n");
	html_tag("			}\n");
	html_tag("			break;\n");
	html_tag("		case %d:\n",FORM_SUTIME_VALID_2);
	html_tag("			if(false == JsTestAdresseIpNtpPrincipal())\n");
	html_tag("			{\n");
	html_tag("				loc_result = false;	\n");
	html_tag("			}\n");
	html_tag("			if(false == JsTestAdresseIpNtpSecours())\n");
	html_tag("			{\n");
	html_tag("				loc_result = false;	\n");
	html_tag("			}\n");
	html_tag("			break;\n");
	html_tag("		default:\n");
	html_tag("			break;\n");
	html_tag("	}\n");
	html_tag("	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		timer.hidden1.value = i_numForm; \n");
	html_tag("		timer.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	//Fonction javascript : JsTestAdresseIpNtpPrincipal
	//*************************************
	html_tag("function JsTestAdresseIpNtpPrincipal() \n");
	html_tag("{ \n");
	html_tag("	var loc_resultat; \n");
	html_tag("	var loc_resultat = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_resultat = validAddr(timer.AdrNtpPrincipal,(%d != timer.modeMAH.selectedIndex)); \n",MODE_MAH_MANUELLE);
	html_tag("	} \n");
	html_tag("	return(loc_resultat); \n");
	html_tag("} \n");/*JsTestAdresseIpNtpPrincipal*/
	
	//Fonction javascript : JsTestAdresseIpNtpSecours
	//*************************************
	html_tag("function JsTestAdresseIpNtpSecours() \n");
	html_tag("{ \n");
	html_tag("	var loc_resultat = false; \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		loc_resultat = validAddr(timer.AdrNtpSecours,false); \n");
	html_tag("	} \n");
	html_tag("	return(loc_resultat); \n");
	html_tag("} \n");/*JsTestAdresseIpNtpSecours*/

	//Fonction javascript : JsChangeModeMAH
	//*************************************
	html_tag("function JsChangeModeMAH() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(Number(timer.modeMAH.value)) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",MODE_MAH_MANUELLE);
	html_tag("				timer.AdrNtpPrincipal.disabled = true;\n");
	html_tag("				timer.AdrNtpSecours.disabled = true;\n");
	html_tag("				timer.ntpTimeZone.disabled = true;\n");
	html_tag("				timer.FreqMajHeureSntp.disabled = true;\n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",MODE_MAH_NTP);
	html_tag("				timer.AdrNtpPrincipal.disabled = false;\n");
	html_tag("				timer.AdrNtpSecours.disabled = false;\n");
	html_tag("				timer.ntpTimeZone.disabled = false;\n");
	html_tag("				timer.FreqMajHeureSntp.disabled = true;\n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",MODE_MAH_SNTP);
	html_tag("				timer.AdrNtpPrincipal.disabled = false;\n");
	html_tag("				timer.AdrNtpSecours.disabled = false;\n");
	html_tag("				timer.ntpTimeZone.disabled = false;\n");
	html_tag("				timer.FreqMajHeureSntp.disabled = false;\n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return(true); \n");
	html_tag("} \n");/*JsChangeModeMAH*/

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{\n");
	html_tag("	with(document)\n");
	html_tag("	{\n");
	html_tag("		JSChangeHour(document.timer); \n");
	html_tag("		JsChangeModeMAH(); \n");
	html_tag("	}\n");
	html_tag("} \n");

	html_tag("</SCRIPT>\n");
	
	html_tag("</script>\n");
	
}/*SetCurrent_Javascript*/

//=====================================================================================
// Fonction	: proc_SetTime
// Entrees	: time
// Sortie	: <TRUE ou FALSE>
// Description	: Changement de l'heure système
//=====================================================================================
void proc_SetTime(S_TIMER_RESULTS *s_Results)
{
	struct	tm loc_s_tm;
	time_t	loc_s_time_t;

	// il faut remplir une  structure tm avec les valeurs dans sResults
	// puis la convertir en time_t et enfin faire un appel a stime.
	loc_s_tm.tm_year= atoi(s_Results->ps8_Year)-1900;//arrive sous la forme 2005 par exemple, il faut stocker 105!
	loc_s_tm.tm_mon = atoi(s_Results->ps8_Month)-1; // dans la structure tm, month commence a 0 d'ou le -1
	loc_s_tm.tm_mday= atoi(s_Results->ps8_Day) ;
	loc_s_tm.tm_hour= atoi(s_Results->ps8_Hour);
	loc_s_tm.tm_min = atoi(s_Results->ps8_Min);
	loc_s_tm.tm_sec = atoi(s_Results->ps8_Sec);
	
	loc_s_time_t = mktime(&loc_s_tm);
	
	stime(&loc_s_time_t);

#if 0
	//date reconnait les formats suivant:
	//	hh:mm[:ss]                                                              
	//	[YYYY.]MM.DD-hh:mm[:ss]                                                 
	//	YYYY-MM-DD hh:mm[:ss]                                                   
	//	MMDDhhmm[[YY]YY][.ss]
	S_STRUCT_DATE loc_s_date;

	loc_s_date = sConvertTimeToDate(loc_s_time_t);
	CmdSysteme_MiseAHeure(&loc_s_date);

#endif
			
	
}/*proc_SetTime*/


//=====================================================================================
// Fonction	: TimerHourSelectList
// Entrees	: <loc_s32_Hour>
//			  <loc_ps8_namep<
// Sortie	: rien
// Description	: Affiche la select List pour Heure
//=====================================================================================
void TimerHourSelectList(s32sod loc_s32_Hour, s8sod *loc_ps8_namep)
{
	s16sod loc_s16_i;
	
	html_tag("      <td><select name=\"%s\" size=\"1\"> \n",
			 loc_ps8_namep);
	
	for(loc_s16_i=0; loc_s16_i<24; loc_s16_i++)
	{	
		html_tag("<OPTION");
		if((s32sod)loc_s16_i == loc_s32_Hour)
		{
			html_tag(" SELECTED VALUE='%d'>", loc_s16_i);
		}
		else
		{
			html_tag(" VALUE='%d'>", loc_s16_i);
		}
		
		html_tag("%02d",loc_s16_i);
	}
	
	html_tag("</select></td> \n");
	
}/*TimerHourSelectList*/ 

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUTime
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de sutime
//=====================================================================================
void InitModule_SUTime(void)
{
}/*InitModule_SUTime*/
