/*========================================================================*/
/* NOM DU FICHIER  : vhomeA.c       									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML homeA							  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE055 17/01/2011 CM
// - Ajout information "Debug Activé" sur frame A
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _VHOMEA

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: JavaScript_HomeA
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/03/2004 -
// Description	: code de javascript de la page HomeA
//=====================================================================================
void JavaScript_HomeA(void)
{
	s8sod		loc_ps8_Date[10 + 1];
	s8sod		loc_ps8_Heure[11 + 1];
	s32sod		loc_s32_i;
	time_t		loc_s_time_t;
	struct tm	loc_s_tm;
	s32sod		loc_s32_sem;
	
	
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
	
	loc_s32_i = 0;	//INIT
	
	time(&loc_s_time_t);
	loc_s_tm = *localtime((const time_t *)(&loc_s_time_t));

	if (MODE_DATE_HEURE_24H == s_html_cfg_eqpmt.s_admin.u8_mode_date_heure)	//CONDITION: MODE_DATE_HEURE_24H
	{
		loc_s32_i  = sprintf( loc_ps8_Date,				"%02d/", loc_s_tm.tm_mday );
		loc_s32_i += sprintf( loc_ps8_Date + loc_s32_i, "%02d/", (loc_s_tm.tm_mon+1) );
		loc_s32_i += sprintf( loc_ps8_Date + loc_s32_i, "%02d",  (loc_s_tm.tm_year%100) );

		loc_s32_i  = sprintf( loc_ps8_Heure,			 "%02d:", loc_s_tm.tm_hour );
		loc_s32_i += sprintf( loc_ps8_Heure + loc_s32_i, "%02d:", loc_s_tm.tm_min );
		loc_s32_i += sprintf( loc_ps8_Heure + loc_s32_i, "%02d",  loc_s_tm.tm_sec );	
	}
	else	//MODE_DATE_HEURE_12H
	{
		loc_s32_i  = sprintf( loc_ps8_Date + loc_s32_i, "%02d/", loc_s_tm.tm_mday );
		loc_s32_i += sprintf( loc_ps8_Date,				"%02d/", (loc_s_tm.tm_mon+1) );
		loc_s32_i += sprintf( loc_ps8_Date + loc_s32_i, "%04d",  (loc_s_tm.tm_year%100) );

		loc_s32_i  = sprintf( loc_ps8_Heure,			 "%02d:", ( loc_s_tm.tm_hour<13 ? ( loc_s_tm.tm_hour==0 ? 12 : loc_s_tm.tm_hour ) : loc_s_tm.tm_hour-12 ) );
		loc_s32_i += sprintf( loc_ps8_Heure + loc_s32_i, "%02d:", loc_s_tm.tm_min );
		loc_s32_i += sprintf( loc_ps8_Heure + loc_s32_i, "%02d",  loc_s_tm.tm_sec );	
		loc_s32_i += sprintf( loc_ps8_Heure + loc_s32_i, " %s",  ( loc_s_tm.tm_hour<13 ? ( loc_s_tm.tm_hour==0 ? "PM" : "AM" ) : "PM" ) );	
	}
	
	html_tag("<script language=\"javascript\">\n");	
	if (MODE_DATE_HEURE_24H == s_html_cfg_eqpmt.s_admin.u8_mode_date_heure)	//CONDITION: MODE_DATE_HEURE_24H
	{
		html_tag("var i_systeme_24h = true;\n");	//true:mode 24H    false: mode 12H
	}
	else	//MODE_DATE_HEURE_12H
	{
		html_tag("var i_systeme_24h = false;\n");	//true:mode 24H    false: mode 12H
	}

	//heure de référence de l'équipement  = new Date(year, month, date[, hours[, minutes[, seconds[,ms]]]]) 
	html_tag("var TempsEquipementReference = new Date(%d,%d,%d,%d,%d,%d);\n" ,(loc_s_tm.tm_year+1900)
																			 ,loc_s_tm.tm_mon
																			 ,loc_s_tm.tm_mday
																			 ,loc_s_tm.tm_hour
																			 ,loc_s_tm.tm_min
																			 ,loc_s_tm.tm_sec);	
	html_tag("var TempsEquipementReferenceMs = TempsEquipementReference.getTime();\n");	//en millisecondes

    html_tag("	var TempsPCReference = new Date();\n");	//heure de référence du PC (au chargement de la frame A)
	html_tag("	var TempsPCReferenceMs =  TempsPCReference.getTime();\n"); //en millisecondes
	html_tag("\n");


	html_tag("function voir_heure(valeur)\n");
	html_tag("{\n");
	html_tag("	if ((i_systeme_24h == true) || (valeur>0 && valeur<13))\n");
	html_tag("	{\n");
	html_tag("		return (valeur);\n");
	html_tag("	}\n");
	html_tag("	if (valeur == 0)\n");
	html_tag("	{\n");
	html_tag("		return (12);\n");
	html_tag("	}\n");
	html_tag("	return (valeur-12);\n");
	html_tag("}\n");
	html_tag("\n");
	
	html_tag("function voir_zero(valeur)\n");
	html_tag("{\n");
	html_tag("	if (valeur > 9)\n");
	html_tag("	{\n");
	html_tag("		return (\"\" + valeur);\n");
	html_tag("	}\n");
	html_tag("	return (\"0\" + valeur);\n");
	html_tag("}\n");
	html_tag("\n");
	
	html_tag("function voir_ampm(TempsNow)\n");
	html_tag("{\n");
	html_tag("	if (i_systeme_24h == true)\n");
	html_tag("	{\n");
	html_tag("		return (\"\");\n");
	html_tag("	}\n");
	html_tag("	if (TempsNow.getHours() < 12)\n");
	html_tag("	{\n");
	html_tag("		return (\"AM\");\n");
	html_tag("	} \n");
	html_tag("	return (\"PM\"); \n");
	html_tag("}\n");
	html_tag("\n");

	html_tag("function affiche_heure(formulaire)\n");
	html_tag("{\n");
	html_tag("	var diff;\n");
	html_tag("	var TempsNow = new Date();\n");	//heure actuelle
	html_tag("	var TempsNowMs= TempsNow.getTime();\n");	//en millisecondes
	html_tag("	if (TempsEquipementReferenceMs >= TempsPCReferenceMs)\n");	//Comparaison Temps PC ref et Equipement Ref
	html_tag("	{\n");
	html_tag("		diff = Math.round(TempsEquipementReferenceMs - TempsPCReferenceMs);\n");
	html_tag("		TempsNow.setTime(TempsNowMs+diff);\n");
	html_tag("	}\n");
	html_tag("	else\n");
	html_tag("	{\n");
	html_tag("		diff = Math.round(TempsPCReferenceMs - TempsEquipementReference);\n");
	html_tag("		TempsNow.setTime(TempsNowMs-diff);\n");
	html_tag("	}\n");
	html_tag("\n");
	html_tag("		document.formulaire.temps.value =  voir_zero(TempsNow.getDate())\n");
	html_tag("									   + \"/\" + voir_zero(TempsNow.getMonth() + 1)\n");
	html_tag("									   + \"/\" + TempsNow.getFullYear()\n");
	html_tag("									   + \"  \"\n");
	html_tag("									   + voir_heure(TempsNow.getHours())\n");
	html_tag("									   + \":\" + voir_zero(TempsNow.getMinutes())\n");
	html_tag("									   + \":\" + voir_zero(TempsNow.getSeconds())\n");
	html_tag("									   + \" \" + voir_ampm(TempsNow)\n");
	html_tag("									   setTimeout(\"affiche_heure('formulaire')\",1000);\n");
	html_tag("}\n");
	html_tag("\n");

	html_tag("function printHtml()\n");
	html_tag("{\n");
	html_tag("	if ((navigator.appName==\"Netscape\") && (parseInt(navigator.appVersion) == 4))\n");
	html_tag("	{\n");
	html_tag("		document.writeln('<input class=Time type=\"text\" name=\"temps\" size=\"14\" maxlength=\"14\">');\n");
	html_tag("	}\n");
	html_tag("	else\n");
	html_tag("	{\n");
	html_tag("		document.writeln('<input class=Time type=\"text\" name=\"temps\" size=\"25\" maxlength=\"25\" readonly>');\n");
	html_tag("	}\n");
	html_tag("}\n");
	html_tag("\n");

	html_tag("</script>\n");
	
}/*JavaScript_HomeA*/

//=====================================================================================
// Fonction		: HomeA_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 29/05/2008
// Description	: Page rafraichissement page HomeA
//				"URL=HomeA_Dyn
//=====================================================================================
void HomeA_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	s8sod	loc_ps8_chaine[50];

	strcpy(loc_ps8_chaine, (const s8sod*)"");

//	printf("Content-type: text/html\n\n");/* Mandatory */
	printf("Content-type: text/plain\n\n");/* Mandatory */

	if(FALSE == TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE&&&");
		html_tag("|");
	}
	else
	{
		s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt))
		{
			;
		}
		s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

		s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
		if(TRUE == u8FillExploitStationFile(&s_html_exploit.s_station))
		{
			;
		}
		s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
		
		html_tag("|");
		html_tag("&&&id:SPAN_INFO_SUP&&&innerHTML:");
		//Ligne 1
		sprintf(ps8_html_string,"<B>%s</B>: %s / %s ",
				pt_tb_msg[u8_html_langue].ps8_msg_mode_M,
				pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_radio_M[s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem],
				pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_reseau[s_html_cfg_eqpmt.s_gene.u8_mode_network]);
		html_tag("%s",ps8ConvertChaineToHtml(ps8_html_string));
		html_tag("<BR>");
		//Ligne 2
		switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_STATION:
				if(STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_statut_connexion)
				{
					html_tag("&nbsp;&nbsp;&nbsp;%s",
							 pt_tb_msg[u8_html_langue].ps8_msg_connectee_M);
				}
				else
				{
					html_tag("&nbsp;&nbsp;&nbsp;%s",
							 pt_tb_msg[u8_html_langue].ps8_msg_non_connectee_M);
				}
				break;
			default:
			case MODE_RADIO_MODEM_ACCESS_POINT:
			case MODE_RADIO_MODEM_MONITOR:
				html_tag("&nbsp;");
				break;
		}
		html_tag("<BR>");
		//Ligne 3
		html_tag("&nbsp;");
		html_tag("&&&");
		html_tag("|");
	}
}/*HomeA_Dyn*/

//=====================================================================================
// Fonction		: HomeA
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: cadre supérieure du site HTML
//=====================================================================================
void HomeA(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
#if HOMEA_LOGO_SODIEL_PLUS_CLIENT
	FILE *loc_handle;
#endif
	u8sod	loc_u8_type_equipement;
#if AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA
	s8sod	loc_ps8_chaine[50];

	strcpy(loc_ps8_chaine, (const s8sod*)"");
#endif
			
	loc_u8_type_equipement = EQUIPEMENT_INCONNU; //INIT
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(TRUE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		loc_u8_type_equipement = s_html_exploit.s_general.u8_type_equipement;
	}
	if(TRUE == u8FillExploitStationFile(&s_html_exploit.s_station))
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(
#if AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA
	   (TRUE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) &&
#endif
		(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
	  )
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillDebugFile(&s_html_debug_global))
	{
		;
	}
	s32Lock_Release(SEMAPHORE_BDD_DEBUGINI, &loc_s32_sem);	//on relache le sem
	
	// Open an empty HTML document first
	printf("Content-type: text/html\n\n");/* Mandatory */
	html_tag("<HTML>\n");

	// Header
	html_tag("<HEAD>\n");	
	html_tag("<TITLE>FRAME_A</TITLE>");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("TD.TitreHomeA {\n");
	html_tag("	FONT-SIZE: 24pt; FONT-FAMILY: verdana, arial, helvetica; TEXT-ALIGN: center\n"); 
	html_tag("}\n");
	html_tag("TD.TimeHomeA {\n");
	html_tag("	FONT-SIZE: 10pt; FONT-WEIGHT: bold; FONT-FAMILY: verdana, arial, helvetica; TEXT-ALIGN: left\n");
	html_tag("}\n");
	html_tag("TD.InfoHomeA {\n");
	html_tag("	FONT-SIZE: 10pt; FONT-WEIGHT: bold; FONT-FAMILY: Prestige, monospace; TEXT-ALIGN: left\n");
	html_tag("}\n");
	html_tag("TD.InfoHomeASup {\n");
	html_tag("	BORDER-RIGHT: 1px solid; PADDING-RIGHT: 0px; BORDER-TOP: 1px solid; PADDING-LEFT: 1px; PADDING-BOTTOM: 1px; BORDER-LEFT: 1px solid; PADDING-TOP: 1px; BORDER-BOTTOM: 1px solid; FONT-SIZE: 9pt; FONT-FAMILY: Prestige, monospace; TEXT-ALIGN: left\n");
	html_tag("}\n");
	html_tag("INPUT.Time {\n");
	html_tag("	FONT-SIZE: 10pt; FONT-WEIGHT: bold; FONT-FAMILY: verdana, arial, helvetica; BACKGROUND: #FFFFF0; BORDER-TOP: #FFFFF0 0px ; BORDER-RIGHT: #FFFFF0 0px ; BORDER-LEFT: #FFFFF0 0px ; BORDER-BOTTOM: #FFFFF0 0px ;\n");
	html_tag("}\n");
	html_tag("</STYLE>\n");
	html_tag("\n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</HEAD>\n");

	JavaScript_HomeA();
	
	// Javascript pour afficher toujours le meme message dans la barre de statut
	html_tag("<SCRIPT LANGUAGE=\"JavaScript\">");
	html_tag("	window.status = \"%s\";",
			 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue]);
	html_tag ("</SCRIPT>");

#if AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA
	//on rafraichie la page Home A uniquement si on est connecté
	if(TRUE == TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=HomeA_Dyn", (u32sod)u16GetTpsRefreshHtml()*1000);
	}
#endif
	
	html_tag("<body onload=\"affiche_heure('formulaire')\">\n");
	html_tag("<form name=\"formulaire\">\n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"900\">\n");
	html_tag("	<tr>\n");
	html_tag("		<td width=350>\n");
	html_tag("			<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
#if ACTIVATION_MISE_A_L_HEURE_HTTP
#else
	html_tag("			<tr>\n");
	html_tag("				<td class=TimeHomeA>%s</td>	\n",pt_tb_msg[u8_html_langue].ps8_msg_date_et_heure_ut);
	html_tag("			</tr>\n");
#endif
	html_tag("			<tr>\n");
	html_tag("				<td class=TimeHomeA>	\n");
	html_tag("			    <SCRIPT language=JavaScript>printHtml()</script></td>\n");
	html_tag("			</tr>\n");
#if AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA
	//on rafraichie la page Home A uniquement si on est connecté
	if(FALSE == TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS)) //CONDITION: non connecté
	{
		html_tag("			<tr><td nowrap>&nbsp;</td></tr> \n");
	}
	else//CONDITION: connecté
	{
		//On récupère la valeur du TSID paramétré 
		html_tag("			<tr><td class=InfoHomeASup nowrap><span id=SPAN_INFO_SUP>");
		sprintf(ps8_html_string,"<B>%s</B>: %s / %s ",
				pt_tb_msg[u8_html_langue].ps8_msg_mode_M,
				pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_radio_M[s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem],
				pt_tb_msg[u8_html_langue].ps8_msg_choix_mode_reseau[s_html_cfg_eqpmt.s_gene.u8_mode_network]);
		html_tag("%s \n",ps8ConvertChaineToHtml(ps8_html_string));
		html_tag("<BR>\n");
		//Ligne 2
		switch(s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem)
		{
			case MODE_RADIO_MODEM_STATION:
				if(STATUT_CONNEXION__ASSOCIATED == s_html_exploit.s_station.u8_statut_connexion)
				{
					html_tag("&nbsp;&nbsp;&nbsp;%s",
							 pt_tb_msg[u8_html_langue].ps8_msg_connectee_M);
				}
				else
				{
					html_tag("&nbsp;&nbsp;&nbsp;%s",
							 pt_tb_msg[u8_html_langue].ps8_msg_non_connectee_M);
				}
				break;
			default:
			case MODE_RADIO_MODEM_ACCESS_POINT:
			case MODE_RADIO_MODEM_MONITOR:
				html_tag("&nbsp;");
				break;
		}
		html_tag("<BR>\n");
		//Ligne 3
		html_tag("&nbsp;\n");
		html_tag("</span></td></tr> \n");
	}
#endif
	html_tag("			</table>\n");
	html_tag("	   </td>	\n");
	html_tag("	   <td>&nbsp;&nbsp;&nbsp;&nbsp;</td> \n");
	html_tag("     <td>\n");
	html_tag("		   <table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
	html_tag("				<tr>\n");
	if(TRUE == u8TestDebugActive(&s_html_debug_global))
	{
		html_tag("					<td class=TitreHomeA>%s<span style=\"color:red\"><B> * DEBUG * </B></span></td>\n",
				 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue]);
	}
	else
	{
		html_tag("					<td class=TitreHomeA>%s</td>\n",
				 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue]);
	}
	html_tag("			    </tr>\n");
	html_tag("			    <tr>\n");
	html_tag("					<td class=InfoHomeA>%s<BR>%s</td>\n",
			 s_html_cfg_eqpmt.s_admin.ps8_identifiant,
			 s_html_cfg_eqpmt.s_admin.ps8_localisation);
	html_tag("				</tr>\n");
	html_tag("		   </table>\n");
	html_tag("     </td>\n");
	html_tag("	   <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td> \n");
#if HOMEA_LOGO_SODIEL_PLUS_CLIENT
//	html_tag("		<td align=\"right\" width=\"130\"><a href=\"http://%s\" target=\"_new\"><img src=\"../logo.gif\" alt=\"%s\" align=\"right\" hspace=\"0\" width=\"74\" height=\"70\"></a> </td>\n", 
//			 s_html_constructeur.ps8_site_web, s_html_constructeur.ps8_nom);
//	if(NULL != (loc_handle = fopen(LOGO_CLIENT, "r" )))//CONDITION: LOGO CLIENT DETECTE
//	{
//		fclose(loc_handle);
//		html_tag("<td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td> \n");
//		html_tag("<td align=\"right\" ><img src=\"../logo_client.gif\" align=\"right\" hspace=\"0\" height=\"70\" name=\"logo_client\"> </td>\n", LOGO_CLIENT);
//	}

	html_tag("		<td align=\"right\" width=\"130\"><a href=\"http://%s\" target=\"_new\"><img src=\"../logo.gif\" alt=\"%s\" align=\"right\" hspace=\"0\" height=\"70\" border=\"0\"></a> </td>\n", 
			 S_CONFIG_EQUIPEMENT_DEFAUT.s_constructeur.ps8_site_web,
			 S_CONFIG_EQUIPEMENT_DEFAUT.s_constructeur.ps8_nom);
	if(NULL != (loc_handle = fopen(FICHIER_LOGO_CLIENT, "r" )))//CONDITION: LOGO CLIENT DETECTE
	{
		fclose(loc_handle);
		html_tag("<td>&nbsp;&nbsp;</td> \n");
		html_tag("<td align=\"right\" ><img src=\"../%s\" align=\"right\" hspace=\"0\" height=\"70\" border=\"0\" name=\"logo_client\"> </td>\n",
				 NFILE_LOGO_CLIENT EXT_GIF);
	}
#else //SOIT LOGO SODIELEC (si pas de logo client), sinon LOGO CLIENT
	html_tag("		<td align=\"right\"><a href=\"http://%s\" target=\"_new\"><img src=\"../logo.gif\" alt=\"%s\" align=\"right\" hspace=\"0\" height=\"70\" border=\"0\"></a> </td>\n", 
			 S_CONFIG_EQUIPEMENT_DEFAUT.s_constructeur.ps8_site_web,
			 S_CONFIG_EQUIPEMENT_DEFAUT.s_constructeur.ps8_nom);
#endif
	html_tag("	</tr>\n");
	html_tag("</table>\n");
	html_tag("</form>\n");


	html_tag("</body>\n");
	html_tag("</html>\n");

}/*HomeA*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VHomeA
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/08/2004 -
// Description	: Initialisation du module homea
//=====================================================================================
void InitModule_VHomeA(void)
{

}/*InitModule_VHomeA*/
