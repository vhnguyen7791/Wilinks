/*========================================================================*/
/* NOM DU FICHIER  : suconfigHandoff.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 15/09/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Handoff		  */
/* Projet          : WRM100                                               */
/* Indice          : BE059                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 15/09/2010 CM
// - CREATION
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE049 08/12/2010 CM
// - Modification mode scanning (handoff)
// - Correction libellé handoff
//BE059 16/02/2011 CM/JP
// - Ajout filtrage rssi pour fast roaming
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGHANDOFF

enum LISTE_DES_FORM_SUCONFIGHANDOFF
{
	FORM_SUCONFIGHANDOFF_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGHANDOFF_VALID_1,
	NB_MAX_FORM_SUCONFIGHANDOFF
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_mode_scanning			[10 + 1];
	s8sod	ps8_time_between_hand_off	[10 + 1];
	s8sod	ps8_bgscan_activation		[10 + 1];
	s8sod	ps8_bgscan_periode			[10 + 1];
	s8sod	ps8_bgscan_level			[10 + 1];
	s8sod	ps8_fgscan_level			[10 + 1];
	s8sod	ps8_fgscan_beacon_missed	[10 + 1];
	s8sod	ps8_isohandoff_level		[10 + 1];
	s8sod	ps8_isohandoff_beacon		[10 + 1];
	s8sod	ps8_type_filtrage			[10 + 1];
	s8sod	ps8_interval_beacon			[10 + 1];

	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_HANDOFF_RESULTS;

FIELD_LIST s_FormConfigHandoffFields[] = {
	{"mode_scan",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_mode_scanning)		},
	{"timeBetweenHO",		"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_time_between_hand_off)		},
	{"bgscanAct",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_bgscan_activation)	},
	{"bgscanPeriod",		"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_bgscan_periode)		},
	{"bgscanLevel",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_bgscan_level)		},
	{"fgscanLevel",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_fgscan_level)		},
	{"fgscanBeaconMissed",	"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_fgscan_beacon_missed)	},
	{"isoHoLevel",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_isohandoff_level)		},
	{"isoHoBeacon",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_isohandoff_beacon)		},
	{"typefiltre",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_type_filtrage)		},
	{"interbeacon",			"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_interval_beacon)		},
	
	{"hidden1",		"%s",		offsetof(S_FORM_CONFIG_HANDOFF_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigHandoff
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010
// Description	: code de javascript de la page HTML SUConfigHandoff
//=====================================================================================
void proc_JavaScript_SUConfigHandoff(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigHandoff
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010
// Description	: code de javascript de la page HTML SUConfigHandoff
//=====================================================================================
void proc_JavaScript_SUConfigHandoff(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{\n"
			 "	var	loc_result = true;\n"
			 "	if(true == loc_result) \n"
			 "	{\n"
			 "		form.hidden1.value = i_numForm; \n"
			 "		form.submit(); \n"
			 "	}\n"
			 "}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigHandoff*/

//=====================================================================================
// Fonction		: SUConfigHandoff
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/09/2010
// Description	: Page HTML Configuration: Handoff
//				"URL=SUConfigHandoff"
//=====================================================================================
void SUConfigHandoff(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_HANDOFF_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_i;

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigHandoff");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigHandoff&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_HANDOFF_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigHandoffFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGHANDOFF)
			{
				if(FORM_SUCONFIGHANDOFF_VALID_1 == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if((TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))&&
					   (TRUE == u8FillConfigHandoff(&s_html_cfg_eqpmt))
					  )
					{
						if(MODE_RADIO_MODEM_STATION == s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
						{
							//paramétrage générale
							s_html_cfg_eqpmt.s_handoff.u8_scanning_mode = (u8sod)atoi(loc_s_results.ps8_mode_scanning);
							s_html_cfg_eqpmt.s_handoff.u16_time_between_hand_off = (u16sod)atoi(loc_s_results.ps8_time_between_hand_off);
							s_html_cfg_eqpmt.s_handoff.u16_time_between_2_beacon = (u16sod)atoi(loc_s_results.ps8_interval_beacon);
							//paramétrage du scanning background
							s_html_cfg_eqpmt.s_handoff.u8_bgscan_activation = (u8sod)atoi(loc_s_results.ps8_bgscan_activation);
							s_html_cfg_eqpmt.s_handoff.u16_bgscan_recurrence_period = (u16sod)atoi(loc_s_results.ps8_bgscan_periode);
							s_html_cfg_eqpmt.s_handoff.s32_bgscan_detection_level = (s32sod)atoi(loc_s_results.ps8_bgscan_level);
							
							//paramétrage du scanning foreground
							s_html_cfg_eqpmt.s_handoff.s32_fgscan_detection_level = (s32sod)atoi(loc_s_results.ps8_fgscan_level);
							s_html_cfg_eqpmt.s_handoff.u16_fgscan_beacon_missed_threshold = (u16sod)atoi(loc_s_results.ps8_fgscan_beacon_missed);

							//paramétrage du hand-off sur le meme canal
							s_html_cfg_eqpmt.s_handoff.s32_iso_detection_level = (s32sod)atoi(loc_s_results.ps8_isohandoff_level);
#if VERSION_WRM100_DEMO
#else
							s_html_cfg_eqpmt.s_handoff.u16_iso_relevant_beacon_threshold = (u16sod)atoi(loc_s_results.ps8_isohandoff_beacon);
#endif
							s_html_cfg_eqpmt.s_handoff.u8_type_filtrage_rssi = (u8sod)atoi(loc_s_results.ps8_type_filtrage);
							

							if(TRUE==u8TestConfigHandoff(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigHandoff(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
						else //MODE_RADIO_MODEM_ACCESS_POINT ou MODE_RADIO_MODEM_MONITOR
						{
							loc_u8_result_test = TRUE;
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
				PreparePageCfgInProgress("SUConfigHandoff");
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
	if((FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt))||
	   (FALSE == u8FillConfigHandoff(&s_html_cfg_eqpmt))
	  )
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Page accéssible uniquement en mode STATION
	if(MODE_RADIO_MODEM_STATION != s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)//CONDITION: STATION
	{
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_MODE_ONLY_STATION);
		Html_GotoPage(ps8_pageHtmlRetour);
		return;
	}
	
	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_hand_off);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigHandoff");	//pour la fonction Actualiser

	JSNumCheck();
	proc_JavaScript_SUConfigHandoff();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigHandoff");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_hand_off);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigHandoff);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//------------------------
	//paramétrage général
	//------------------------
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"300\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Mode du scanning
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_mode_scanning);
	html_tag("			<td><SELECT name=\"mode_scan\" size=\"1\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_HO_MODES_SCANNING;loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pu8_flag_affichage_mode_scanning_handoff[loc_u8_i])
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_u8_i == s_html_cfg_eqpmt.s_handoff.u8_scanning_mode) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_scanning[loc_u8_i]);
		}
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");

	//Intervalle de temps entre 2 hand-off consécutifs
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_intervalle_temps_entre_2_handoff);
	html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"timeBetweenHO\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;&nbsp;ms</td> \n",
			 s_html_cfg_eqpmt.s_handoff.u16_time_between_hand_off,
			 HO_TIME_BETW_HANDOFF_MIN,
			 HO_TIME_BETW_HANDOFF_MAX);
	html_tag("		</tr> \n");


	//Intervalle de temps entre 2 beacons
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_intervalle_temps_entre_2_beacon);
	html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"interbeacon\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;&nbsp;ms</td> \n",
			 s_html_cfg_eqpmt.s_handoff.u16_time_between_2_beacon,
			 WF_BEACON_PERIOD_MIN,
			 WF_BEACON_PERIOD_MAX);
	html_tag("		</tr> \n");


	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//------------------------
	//paramétrage du scanning background
	//------------------------
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_du_scanning_background);

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"300\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Activation du background scanning
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_scanning_background);
	html_tag("			<td><SELECT name=bgscanAct> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_handoff.u8_bgscan_activation) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_handoff.u8_bgscan_activation) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	//Période de récurrence du background scanning
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_periode_scanning_background);
	html_tag("			<td><input type=\"text\" size=\"5\" maxlength=5 name=\"bgscanPeriod\" value=%d onchange=\"return(isInteger(this,%d,%d))\">&nbsp;%s</td> \n",
			 s_html_cfg_eqpmt.s_handoff.u16_bgscan_recurrence_period,
			 HO_BGSCAN_PERIOD_MIN,
			 HO_BGSCAN_PERIOD_MAX,
			 pt_tb_msg[u8_html_langue].ps8_msg_secondes);
	html_tag("		</tr> \n");
	//Seuil du niveau reçu déclenchant un background scanning
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_seuil_niveau_rx_declenchant_scan_bg);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"bgscanLevel\" value=%ld onchange=\"return(isInteger(this,%d,%d))\">&nbsp;dBm</td> \n",
			 s_html_cfg_eqpmt.s_handoff.s32_bgscan_detection_level,
			 SEUIL_RX_MIN,
			 SEUIL_RX_MAX);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//------------------------
	//paramétrage du scanning foreground
	//------------------------
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_du_scanning_foreground);

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"300\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Seuil du niveau reçu déclenchant un foreground scanning
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_seuil_niveau_rx_declenchant_scan_fg);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"fgscanLevel\" value=%ld onchange=\"return(isInteger(this,%d,%d))\">&nbsp;dBm</td> \n",
			 s_html_cfg_eqpmt.s_handoff.s32_fgscan_detection_level,
			 SEUIL_RX_MIN,
			 SEUIL_RX_MAX);
	//Seuil de nombre de balises perdues
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_seuil_de_nb_beacon_rx_perdus_declenchant_scan_fg);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"fgscanBeaconMissed\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
			 s_html_cfg_eqpmt.s_handoff.u16_fgscan_beacon_missed_threshold,
			 HO_FGSCAN_BEACON_MISSED_THRESH_MIN,
			 HO_FGSCAN_BEACON_MISSED_THRESH_MAX);
	html_tag("		</tr> \n");
	//Seuil du niveau minimum pour un nouvel AP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_seuil_niveau_rx_iso_declenchant_handoff);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"isoHoLevel\" value=%ld onchange=\"return(isInteger(this,%d,%d))\">&nbsp;dBm</td> \n",
			 s_html_cfg_eqpmt.s_handoff.s32_iso_detection_level,
			 SEUIL_RX_MIN,
			 SEUIL_RX_MAX);
#if VERSION_WRM100_DEMO
#else
	//Seuil de nombre de balises recues
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_seuil_de_nb_beacon_rx_declenchant_handoff);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=3 name=\"isoHoBeacon\" value=%d onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
			 s_html_cfg_eqpmt.s_handoff.u16_iso_relevant_beacon_threshold,
			 HO_ISO_RELEVANT_BEACON_THRESH_MIN,
			 HO_ISO_RELEVANT_BEACON_THRESH_MAX);
	html_tag("		</tr> \n");
#endif
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//------------------------
	//paramétrage du filtrage RSSI
	//------------------------
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_filtrage_rssi);

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"300\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Type de filtre
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_type_filtre);
	html_tag("			<td><SELECT name=\"typefiltre\" size=\"1\"> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_TYPES_FILTRAGE_RSSI;loc_u8_i++)
	{
		html_tag("		   <option %s value=\"%d\">%s</option>	\n",
				 ((loc_u8_i == s_html_cfg_eqpmt.s_handoff.u8_type_filtrage_rssi) ? "selected" : ""),
				 loc_u8_i,
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_type_filtre[loc_u8_i]);
	}
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGHANDOFF_VALID_1);
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigHandoff*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigHandoff
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/09/2010
// Description	: Initialisation du module de SUConfigHandoff
//=====================================================================================
void InitModule_SUConfigHandoff(void)
{
}/*InitModule_SUConfigHandoff*/
