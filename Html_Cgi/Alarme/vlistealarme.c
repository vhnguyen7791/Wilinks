/*========================================================================*/
/* NOM DU FICHIER  : vlistealarme.c	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : HTML CGI: page HTML exploitation Liste alarmes		  */
/* Projet          : WRM100                                               */
/* Indice          : BE037				                                  */
/*========================================================================*/
/* Historique      :                                                      */
//BE016 11/03/2010 CM
//	- CREATION
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VLISTEALARME


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct 
{
	s8sod	ps8_ackAlarme			[20 + 1];

	s8sod	ps8_parametre			[10 + 1];
	s8sod	ps8_hidden1				[20 + 1];
} S_VLISTEALARME_RESULTS;

FIELD_LIST s_VListeAlarmesFields[] = {
	{"ackAlarme",	"%s",		offsetof(S_VLISTEALARME_RESULTS, ps8_ackAlarme)	},

	{"hidden1",		 "%s",		offsetof(S_VLISTEALARME_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_VListeAlarme
// Entrees		: rien
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: javascript page "URL=VListeAlarme"
//=====================================================================================
void proc_JavaScript_VListeAlarme(void);

//=====================================================================================
// Fonction		: VListeAlarme_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page rafraichissement page Alarme
//				"URL=VListeAlarme_Dyn
//=====================================================================================
void VListeAlarme_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod loc_s32_sem;
	u16sod	loc_u16_indGroupe;
	u16sod	loc_u16_i;
	s8sod	loc_ps8_chaineId[20+1];

	loc_u16_indGroupe = 0;	//INIT
	strcpy(loc_ps8_chaineId, ""); //INIT
	
//	printf("Content-type: text/html\n\n");/* Mandatory */
	printf("Content-type: text/plain\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillExploitEventsGlobalFile(&s_html_exp_events))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillEventSystemFile(pt_html_eventsystem))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem
	
	
	html_tag("|");
	//Alarme synthèse n°1
	sprintf(loc_ps8_chaineId, "AL_%d",S_DESCRIPTION_EVENT_PAR_DEFAUT[EVT000_AL_SYNTHESE_1].u16_numero_evt);
	HtmlDyn_ConvStatAlarme(u8GetEtatAlarme(&s_html_exp_events, EVT000_AL_SYNTHESE_1),	loc_ps8_chaineId);
	html_tag("|");

	//autres alarmes
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if((EVT000_AL_SYNTHESE_1 != loc_u16_i)&&
		   (TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u8_type_evt)
		  )
		{
			if(TRUE == u8TestEventDisponible(loc_u16_i))
			{
				sprintf(loc_ps8_chaineId, "AL_%d",S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u16_numero_evt);
				HtmlDyn_ConvStatAlarme(u8GetEtatAlarme(&s_html_exp_events, loc_u16_i),	loc_ps8_chaineId);
				html_tag("|");
			}
		}
	}	
	
#if 0
	for(loc_u16_i=0;loc_u16_i<NB_MAX_GROUPES;loc_u16_i++)
	{
		loc_u16_indGroupe = loc_u16_i;
		if(TRUE == u8TestGroupeEvtDisponible(loc_u16_indGroupe))
		{
			sprintf(loc_ps8_chaineId, "GRP_%d",loc_u16_indGroupe);
			HtmlDyn_ConvStatAlarme(u8GetEtatGroupeAlarme(&s_html_exp_events, loc_u16_indGroupe),	loc_ps8_chaineId);
			html_tag("|");
			
		}
	}
#endif
	
}/*VListeAlarme_Dyn*/

//=====================================================================================
// Fonction		: proc_JavaScript_VListeAlarme
// Entrees		: rien
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: javascript page "URL=VListeAlarme"
//=====================================================================================
void proc_JavaScript_VListeAlarme(void)
{
	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : AckFormulaire
	//*************************************
	html_tag("function AckFormulaire(form) \n"
			 "{ \n"
			 "	form.ackAlarme.value = 1;\n"
			 "	form.submit();\n"
			 "} \n");	
	

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_VListeAlarme*/

//=====================================================================================
// Fonction		: VListeAlarme
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page HTML Exploitation: Alarme
//				"URL=VListeAlarme"
//=====================================================================================
void VListeAlarme(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod loc_s32_sem;
	S_VLISTEALARME_RESULTS		loc_s_results;
	s8sod						loc_ps8_emsg[50];
	u16sod	loc_u16_i;
	u16sod	loc_u16_indGroupe;
	s8sod	loc_ps8_chaineId[20+1];
	S_STRUCT_CIP_MONITOR loc_s_cip_monitor_tempo;

	loc_u16_indGroupe = 0;	//INIT
	strcpy(loc_ps8_chaineId, ""); //INIT
	memset(&loc_s_cip_monitor_tempo, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT


	printf("Content-type: text/html\n\n");/* Mandatory */


	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		PreparePagePswd("VListeAlarme");
		return;
	}
	

	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=VListeAlarme&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_VLISTEALARME_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_VListeAlarmesFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			if(1 == atoi(loc_s_results.ps8_ackAlarme)) //CONDITION : reset alarmes mémorisées du groupe
			{
				//On signale le RAZ des alarmes mémorisées au processus monitor
				s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillCipMonitor(&loc_s_cip_monitor_tempo))
				{
					loc_s_cip_monitor_tempo.u8_raz_alarmes_memorisees = TRUE;
					u8EditCipMonitor(&loc_s_cip_monitor_tempo);
				}
				s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
			}
			//On recharge la page pour re-initialiser les champs "objets" HTML
			Html_GotoPage("/cgi-bin/cgi_fh?URL=VListeAlarme");
			return; // on sort!
		}
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillExploitEventsGlobalFile(&s_html_exp_events))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillEventSystemFile(pt_html_eventsystem))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem
	
	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_alarmes);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VListeAlarme");	//pour la fonction Actualiser
	RefreshContentsOfFrame("/cgi-bin/cgi_fh?URL=VListeAlarme_Dyn", (u32sod)u16GetTpsRefreshHtml()*1000);
	proc_JavaScript_VListeAlarme();

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_alarmes);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_Vliste_alarmes);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();
	
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">\n");
	html_tag("		<tr>\n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_description);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_statut);
	html_tag("		</tr>\n");

	//Alarme synthèse n°1
	html_tag("		<tr height=20>\n");
	html_tag("			<td>%s</th> \n",
			pt_tb_msg[u8_html_langue].ps8_msg_lib_evenement[EVT000_AL_SYNTHESE_1]);
	sprintf(loc_ps8_chaineId, "AL_%d",S_DESCRIPTION_EVENT_PAR_DEFAUT[EVT000_AL_SYNTHESE_1].u16_numero_evt);
	HtmlTD_ConvStatAlarme(u8GetEtatAlarme(&s_html_exp_events, EVT000_AL_SYNTHESE_1),	loc_ps8_chaineId,	0);
	html_tag("		</tr>\n");

	//autres alarmes
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if((EVT000_AL_SYNTHESE_1 != loc_u16_i)&&
		   (TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u8_type_evt)
		  )
		{
			if(TRUE == u8TestEventDisponible(loc_u16_i))
			{
				html_tag("		<tr>\n");
				html_tag("			<td>%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_lib_evenement[loc_u16_i]);
				sprintf(loc_ps8_chaineId, "AL_%d",S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_i].u16_numero_evt);
				HtmlTD_ConvStatAlarme(u8GetEtatAlarme(&s_html_exp_events, loc_u16_i),	loc_ps8_chaineId,	0);
				html_tag("		</tr>\n");
			}
		}
	}	

#if 0
	//Groupe des alarmes
	for(loc_u16_i=0;loc_u16_i<NB_MAX_GROUPES;loc_u16_i++)
	{
		loc_u16_indGroupe = loc_u16_i;
		if(TRUE == u8TestGroupeEvtDisponible(loc_u16_indGroupe)) 
		{
			html_tag("		<tr>\n");
			html_tag("			<td><a href=\"/cgi-bin/cgi_fh?URL=VAlarme&param=%d\" target=\"frame_c\">%s</a></td> \n",
					 loc_u16_indGroupe,
					 pt_tb_msg[u8_html_langue].ps8_msg_lib_groupe_alarmes[loc_u16_indGroupe]);
			sprintf(loc_ps8_chaineId, "GRP_%d",loc_u16_indGroupe);
			HtmlTD_ConvStatAlarme(u8GetEtatGroupeAlarme(&s_html_exp_events, loc_u16_indGroupe),	loc_ps8_chaineId,	0);
			html_tag("		</tr>\n");
		}
	}
#endif

	html_tag("</table></td></tr>\n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td><table align=center border=0> \n");
	html_tag("	<tr> \n");
	html_tag("		<td><B>%s</B></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_date_dernier_reset);
	html_tag("		<td><B>:</B></td> \n");
	html_tag("		<td>%s</td> \n",
			 ps8GetChDate(&s_html_exp_events.s_date_dernier_reset));
	html_tag("		<td>&nbsp;&nbsp;&nbsp;&nbsp;</td> \n");
	if(TRUE == TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		//bouton RESET alarmes
		html_tag("		<td><form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
		form_hidden("URL","VListeAlarme");
		form_hidden("ackAlarme","0");
		html_tag("			<input type=\"button\" value=\"%s\" onClick= \"return AckFormulaire(form)\"> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_effacer_toutes_les_alarmes);
		html_tag("		</form></td>\n");
	}
	html_tag("	</tr>\n");
	html_tag("</table></td></tr>\n");
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
	
}/*VListeAlarme*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VListeAlarme
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/07/2007
// Description	: Initialisation du module de VListeAlarme
//=====================================================================================
void InitModule_VListeAlarme(void)
{
}/*InitModule_VListeAlarme*/
