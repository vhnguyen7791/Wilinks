/*========================================================================*/
/* NOM DU FICHIER  : valarme.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/03/2010                                           */
/* Libelle         : HTML CGI: page HTML exploitation alarmes			  */
/* Projet          : WRM100                                               */
/* Indice          : BE016				                                  */
/*========================================================================*/
/* Historique      :                                                      */
//BE016 11/03/2010 CM
//	- CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VALARME


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct 
{
	s8sod	ps8_parametre			[10 + 1];
	s8sod	ps8_hidden1				[20 + 1];
} S_VALARME_RESULTS;

FIELD_LIST s_VAlarmesFields[] = {
	{"param",		"%s",		offsetof(S_VALARME_RESULTS, ps8_parametre)	},
	{"hidden1",		 "%s",		offsetof(S_VALARME_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: VAlarme_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page rafraichissement page Alarme
//				"URL=VAlarme&param=<index_page_alarm>"
//=====================================================================================
void VAlarme_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod loc_s32_sem;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;
	s8sod	loc_ps8_chaineId[20+1];
	u8sod	loc_u8_parametre;
	u8sod	loc_u8_index_groupe_alarm;

	loc_u8_parametre = 0;	//INIT
	loc_u8_index_groupe_alarm = 0;	//INIT
	strcpy(loc_ps8_chaineId, "");
	loc_u16_indEvt = 0;	//INIT

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
	
	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=VAlarme_Dyn&param=<index_page_alarm>
	{
		loc_u8_parametre = (u8sod)atoi(loc_p_varlist[3]);
		if(loc_u8_parametre < NB_MAX_GROUPES)
		{
			loc_u8_index_groupe_alarm = loc_u8_parametre;
		}

		html_tag("|");
		for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
		{
			loc_u16_indEvt = loc_u16_i;
			if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
			{
				if(loc_u8_index_groupe_alarm == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_groupe)
				{
					if(TRUE == u8TestEventDisponible(loc_u16_indEvt)) //CONDITION: Disponible
					{
						sprintf(loc_ps8_chaineId, "AL_%d",S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt);
						HtmlDyn_ConvStatAlarme(u8GetEtatAlarme(&s_html_exp_events, loc_u16_indEvt),	loc_ps8_chaineId);
						html_tag("|");
					}
				}
			}
		}
		
	}
	
}/*VAlarme_Dyn*/

//=====================================================================================
// Fonction		: VAlarme
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 26/07/2007
// Description	: Page HTML Exploitation: Alarme
//				"URL=VAlarme&param=<index_page_alarm>"
//=====================================================================================
void VAlarme(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod loc_s32_sem;
	S_VALARME_RESULTS		loc_s_results;
	s8sod					loc_ps8_emsg[50];
	u8sod	loc_u8_parametre;
	u8sod	loc_u8_index_groupe_alarm;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;
	s8sod	loc_ps8_chaineId[20+1];

	loc_u8_parametre = 0;	//INIT
	loc_u8_index_groupe_alarm = 0;	//INIT
	strcpy(loc_ps8_chaineId, "");
	loc_u16_indEvt = 0;	//INIT

	printf("Content-type: text/html\n\n");/* Mandatory */


	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=VAlarme&param=<index_page_alarm>
	{
		loc_u8_parametre = (u8sod)atoi(loc_p_varlist[3]);
		if(loc_u8_parametre < NB_MAX_GROUPES)
		{
			loc_u8_index_groupe_alarm = loc_u8_parametre;
		}
		else//CONDITION: page KO
		{
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return;
		}
	}
	else
	{
		PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		return;
	}

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		sprintf(ps8_pageHtmlEnCours,"VAlarme&param=%d",
				loc_u8_index_groupe_alarm);
		PreparePagePswd(ps8_pageHtmlEnCours);
		return;
	}
	

	if (s32GetArgNb(loc_p_varlist) > 4)  //deja 5 utilise pour URL=VAlarme&param=<index_page_alarm>&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_VALARME_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_VAlarmesFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			//On recharge la page pour re-initialiser les champs "objets" HTML
			sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VAlarme&param=%d",
					loc_u8_index_groupe_alarm);
			Html_GotoPage(ps8_pageHtmlEnCours);
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
	html_tag("<title>%s: %s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_alarmes,
			 pt_tb_msg[u8_html_langue].ps8_msg_lib_groupe_alarmes[loc_u8_index_groupe_alarm]);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VAlarme&param=%d",
		   loc_u8_index_groupe_alarm);
	JSActualiser(ps8_pageHtmlEnCours);	//pour la fonction Actualiser
	sprintf(ps8_html_string,"/cgi-bin/cgi_fh?URL=VAlarme_Dyn&param=%d",
			loc_u8_index_groupe_alarm);
	RefreshContentsOfFrame(ps8_html_string, (u32sod)u16GetTpsRefreshHtml()*1000);

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_alarmes,
			 pt_tb_msg[u8_html_langue].ps8_msg_lib_groupe_alarmes[loc_u8_index_groupe_alarm]);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_Vliste_groupe_alarmes[loc_u8_index_groupe_alarm]);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VListeAlarme\" target=\"frame_c\">%s %s</a></li></ul></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_retours_a_la_page,
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_alarmes);

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table>\n");

	html_tag("	<tr>\n");
	html_tag("		<td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">\n");
	html_tag("			<tr>\n");
	html_tag("				<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_description);
	html_tag("				<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_statut);
	html_tag("			</tr>\n");
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{
			if(loc_u8_index_groupe_alarm == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_groupe)
			{
				if(TRUE == u8TestEventDisponible(loc_u16_indEvt)) //CONDITION: Disponible
				{
					html_tag("			<tr>\n");
					html_tag("				<td nowrap>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_lib_evenement[loc_u16_indEvt]);
					sprintf(loc_ps8_chaineId, "AL_%d",S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt);
					HtmlTD_ConvStatAlarme(u8GetEtatAlarme(&s_html_exp_events, loc_u16_indEvt),	loc_ps8_chaineId,	0);
					html_tag("			</tr>\n");
				}
			}
		}
	}
	html_tag("		</table></td>\n");

	html_tag("		<td>&nbsp;&nbsp;</td> \n");
	
	switch(loc_u8_index_groupe_alarm)
	{
#if 0
		case GROUPE_AL_RF:
			html_tag("<td><table>\n");
			html_tag("	<tr>\n");
			html_tag("		<td nowrap><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VExploitRF\" target=\"frame_c\">%s %s:%s</a></li></ul></td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_voir,
					 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
					 pt_tb_msg[u8_html_langue].ps8_msg_entree_syst_minuscule[SYST_ENTREE_RF]);
			html_tag("	</tr>\n");
			if(TRUE == u8TestPresenceOption(XXXXXXXXXXX))
			{
				html_tag("	<tr>\n");
				html_tag("		<td nowrap><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VExploitImpulseResponse\" target=\"frame_c\">%s %s:%s</a></li></ul></td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_voir,
						 pt_tb_msg[u8_html_langue].ps8_msg_exploitation,
						 pt_tb_msg[u8_html_langue].ps8_msg_reponse_impulsionnelle);
				html_tag("	</tr>\n");
			}
			html_tag("</table></td>\n");
			break;
#endif
		default:
			html_tag("		<td>&nbsp;&nbsp;</td> \n");
			break;
	}

	
	html_tag("	</tr>\n");
	html_tag("</table></td></tr>\n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("</table></td></tr>\n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*VAlarme*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VAlarme
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/07/2007
// Description	: Initialisation du module de VAlarme
//=====================================================================================
void InitModule_VAlarme(void)
{
}/*InitModule_VAlarme*/
