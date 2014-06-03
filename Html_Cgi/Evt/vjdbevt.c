/*========================================================================*/
/* NOM DU FICHIER  : vjdbevt.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 11/03/2010                                           */
/* Libelle         : HTML CGI: page HTML Evenements - Journal de bord	  */
/* Projet          : WRM100                                               */
/* Indice          : BE060												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 10/03/2010 CM
//	- CREATION
//BE029 10/05/2010 CM
// - Correction plantage page HTML Journal de bord (lors de plusieurs actualisations de la plage)
//	=> conséquences sémaphore SEMAPHORE_BDD_JDB bloqué, et jdb bloqué...
//	il semble que le le processus plante lors du html_tag (printf) raison ????
//	solution: on copie tout le jdb dans la RAM pour l'afficher
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VJDBEVT

enum LISTE_DES_FORM_VJDBEVT
{
	FORM_VJDBEVT_NULL = 0,
	FORM_VJDBEVT_CLEAR,
	FORM_VJDBEVT_GENERATE_FILE,
	NB_MAX_FORM_VJDVBEVT
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Fifo jdb evt HTML
static S_STRUCT_JDBEVT ps_fifoHtmlJdb[NB_MAX_EVT_PAR_JDBPART];
static u16sod u16_wr_fifohtmljdb;
//Jdb complet
static S_STRUCT_JDBEVT ps_completjdb_from_html[TAILLE_MAX_JDBEVT];
static u16sod u16_wr_completjdb;

/* Structures pour la modificaton de la configuration */
typedef struct 
{
	s8sod	ps8_parametre				[10 + 1];
	s8sod	ps8_hidden1					[20 + 1];
} S_CONFIG_JDB_EVTS_RESULTS;

FIELD_LIST s_ConfigJdbEvtFields[] = {
	{"param",					"%s",		offsetof(S_CONFIG_JDB_EVTS_RESULTS, ps8_parametre)			},
	{"hidden1",					"%s",		offsetof(S_CONFIG_JDB_EVTS_RESULTS, ps8_hidden1)			},

	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_VJdbEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: java script pour JDB
//=====================================================================================
void proc_JavaScript_VJdbEvt(void);

//=====================================================================================
// Fonction		: proc_JavaScript_VJdbEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010 -
// Description	: java script pour JDB
//=====================================================================================
void proc_JavaScript_VJdbEvt(void)
{
	html_tag("<SCRIPT language=JavaScript> \n");	//Pour la fonction Actualiser

	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{ \n"
			 "	var	loc_result = false; \n"
			 "	switch(i_numForm) \n"
			 "	{ \n");
	html_tag("		case %d: \n"
			 "			if ( confirm(\"%s\") )\n"
			 "			{ \n"
			 "				loc_result = true;\n"
			 "			} \n"
			 "		break; \n",
			 FORM_VJDBEVT_CLEAR,
			 pt_tb_msg[u8_html_langue].ps8_msg_est_tu_sur_effacer_jdb);
	html_tag("		case %d: \n"
			 "			if ( confirm(\"%s\") )\n"
			 "			{ \n"
			 "				loc_result = true;\n"
			 "			} \n"
			 "		break; \n",
			 FORM_VJDBEVT_GENERATE_FILE,
			 pt_tb_msg[u8_html_langue].ps8_msg_est_tu_sur_generer_jdb);

	html_tag("		default:	 \n"
			 "			loc_result = true;\n"
			 "			break;	 \n"
			 "	} \n"
			 "	if(true == loc_result) \n"
			 "	{ \n"
			 "		form.hidden1.value = i_numForm;\n"
			 "		form.submit();\n"
			 "	} \n"
			 "} \n");	

	html_tag("</SCRIPT> \n");

}/*proc_JavaScript_VJdbEvt*/

//=====================================================================================
// Fonction		: VJDBEvenement_Dyn
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 11/03/2010
// Description	: Page rafraichissement page configuration VJDBEvenement
//				"URL=VJDBEvenement_Dyn&param=<numpage>
//					<numpage> : numéro de la page
//=====================================================================================
void VJDBEvenement_Dyn(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	u16sod	loc_u16_page;
	s32sod	loc_s32_sem;

//	printf("Content-type: text/html\n\n");/* Mandatory */
	printf("Content-type: text/plain\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestClientIpConnecte(getenv("REMOTE_ADDR")))
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	
	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=VJDBEvenement_Dyn&param=<numpage>
	{
		loc_u16_page = (u16sod)atoi(loc_p_varlist[3]);

		
		if(	(loc_u16_page < NB_MAX_PAGES_HTML_JDB)
		  )//CONDITION: paramètres OK
		{
			;	//OK
		}
		else//CONDITION: page KO
		{
			return;
		}
	}
	else
	{
		return;
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillStatutJdb(&s_statutjdb_from_html, IDXSTATUTJDB_RAM)) //INIT
	{
		html_tag("|");
		html_tag("&&&id:RECHARGER_PAGE_HTML&&&"); //id inconnu donc recharge de la page
	}
	s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
	
	
	html_tag("|");
	if(PAGE_HTML_JDB_CONFIG == loc_u16_page)
	{
		html_tag("&&&id:DIV_NBEVTSJDB&&&innerHTML:%d&&&",
				 s_statutjdb_from_html.u16_nb_total_evt);
		html_tag("|");
	}
	
	
}/*VJDBEvenement_Dyn*/

//=====================================================================================
// Fonction		: VJDBEvenement
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 11/03/2010
// Description	: Page HTML Configuration: JDB des évènements
//				"URL=VJDBEvenement&param=<numpage>&hidden1=<numForm>"
//					<numpage> : numéro de la page
//					<numForm> : suite action boutons
//=====================================================================================
void VJDBEvenement(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_JDB_EVTS_RESULTS	loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;

	u32sod	loc_u32_NumeroForm;
	u16sod	loc_u16_page;
	u16sod	loc_u16_nb_pages_max;
	u16sod	loc_u16_i;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_type_equipement;

	loc_u32_NumeroForm = 0;	//INIT
	loc_u16_page = PAGE_HTML_JDB_CONFIG; //INIT
	loc_u16_nb_pages_max = (NB_MAX_PAGES_HTML_JDB - PAGE_HTML_JDB_1);	//INIT
	loc_u8_type_equipement = EQUIPEMENT_INCONNU; //INIT

	loc_u8_result_test = FALSE; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */

	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=VJDBEvenement&param=<parametre>
	{
		loc_u16_page = (u16sod)atoi(loc_p_varlist[3]);
		
		if(		(loc_u16_page < NB_MAX_PAGES_HTML_JDB)
		  )//CONDITION: paramètres OK
		{
			;	//OK
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
		sprintf(ps8_pageHtmlEnCours,"VJDBEvenement&param=%d",
				loc_u16_page);

		PreparePagePswd(ps8_pageHtmlEnCours);
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 4)  //URL=VJDBEvenement&param=<parametre>&hidden1=<numForm>"
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_JDB_EVTS_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigJdbEvtFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u32_NumeroForm = (u32sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u32_NumeroForm < NB_MAX_FORM_VJDVBEVT)
			{
				switch(loc_u32_NumeroForm)
				{
					case FORM_VJDBEVT_CLEAR:
						s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillCipJdb(&s_cip_jdb_from_html))
						{
							s_cip_jdb_from_html.u8_effacer_jdb = TRUE;
							if(TRUE == u8EditCipJdb(&s_cip_jdb_from_html))
							{
								loc_u8_result_test = TRUE;
							}
						}
						s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
						break;
						
					case FORM_VJDBEVT_GENERATE_FILE:
						s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillCipJdb(&s_cip_jdb_from_html))
						{
							s_cip_jdb_from_html.u8_generer_jdb = TRUE;
							if(TRUE == u8EditCipJdb(&s_cip_jdb_from_html))
							{
								loc_u8_result_test = TRUE;
							}
						}
						s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
						break;
						
					default:
						break;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VJDBEvenement&param=%d",
						loc_u16_page);
				Html_GotoPage(ps8_pageHtmlEnCours);
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
	if((FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))||
	   (FALSE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
	  )
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(TRUE == u8FillExploitGeneralFile(&s_html_exploit.s_general))
	{
		loc_u8_type_equipement = s_html_exploit.s_general.u8_type_equipement;
	}
	else
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	

	s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore

	if(FALSE == u8FillStatutJdb(&s_statutjdb_from_html, IDXSTATUTJDB_RAM)) //INIT
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	if(PAGE_HTML_JDB_CONFIG != loc_u16_page)
	{
		//Lecture complète du journal de bord (de l'évènement du plus récent au plus ancien)
		LectureCompleteJDB();
	}
	
	s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem
	
	
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_journal_de_bord);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VJDBEvenement&param=%d",
			loc_u16_page);
	JSActualiser(ps8_pageHtmlEnCours);	//pour la fonction Actualiser

	if(PAGE_HTML_JDB_CONFIG == loc_u16_page)
	{
		JSNumCheck();
		proc_JavaScript_VJdbEvt();
	}
	sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VJDBEvenement_Dyn&param=%d",
			loc_u16_page);
	RefreshContentsOfFrame(ps8_pageHtmlEnCours, (u32sod)u16GetTpsRefreshHtml()*1000);

	html_tag("<body> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_journal_de_bord);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_VJdbEvt_avec_liens_1000_evts);

	html_tag("<tr><td>&nbsp;</td></tr> \n");



	//LIENS
	html_tag("<tr><td><span id=LIENS_ENTETE_PAGE><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n"
			 "			<tr> \n");
	if(PAGE_HTML_JDB_CONFIG == loc_u16_page)
	{
		html_tag("				<td><ul><li><B>%s</B></li></ul></td> \n"
				 "				<td>&nbsp;&nbsp;</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_configuration);
	}
	else
	{
		html_tag("				<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VJDBEvenement&param=%d\" target=\"frame_c\">%s</a></li></ul></td> \n"
				 "				<td>&nbsp;&nbsp;</td> \n",
				 PAGE_HTML_JDB_CONFIG,
				 pt_tb_msg[u8_html_langue].ps8_msg_configuration);
	}

	if(PAGE_HTML_JDB_CONFIG == loc_u16_page)
	{
		html_tag("				<td><ul><li>%s  \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_page);
	}
	else
	{
		html_tag("				<td><ul><li><B>%s</B>  \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_page);
	}

	for(loc_u16_i=0;loc_u16_i<(NB_MAX_PAGES_HTML_JDB-1);loc_u16_i++)
	{
		if(loc_u16_i < loc_u16_nb_pages_max)
		{
			if((loc_u16_i+1) == loc_u16_page)	//CONDITION: page identique
			{
				html_tag("&nbsp;&nbsp;<B>%d</B>",
						 (loc_u16_i+1));
			}
			else
			{
				html_tag("&nbsp;&nbsp;<a href=\"/cgi-bin/cgi_fh?URL=VJDBEvenement&param=%d\" target=\"frame_c\">%d</a>",
						 (loc_u16_i+1),
						 (loc_u16_i+1));
			}
		}
	}
	html_tag("				</B></li></ul></td> \n");
	html_tag("			</tr> \n"
			 "</table></span></td></tr> \n");

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	
	switch(loc_u16_page)
	{
		case PAGE_HTML_JDB_CONFIG:
			html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
			html_tag("<tr><td>&nbsp;</td></tr> \n");
			//Date dernier reset jdb
			html_tag("<tr><td><B>%s:</B> %s</td></tr>\n",
					 pt_tb_msg[u8_html_langue].ps8_msg_date_dernier_reset,
					 ps8GetChDate(&s_statutjdb_from_html.s_date_dernier_reset));
			//Nombre d'évts stockés dans le jdb
			html_tag("<tr><td><B>%s:</B> <span id=DIV_NBEVTSJDB>%d</span></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_nombre_d_evenements_dans_jdb,
					 s_statutjdb_from_html.u16_nb_total_evt);
			
			HtmlJdb_Configuration();
			
			break;

		default:
			html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
			html_tag("<tr><td>&nbsp;&nbsp;&nbsp;<B>%s (%s / %s)</B></td></tr>\n",
					 S_DESCRIPT_EQUIPEMENT[ loc_u8_type_equipement ].ps8_nom[u8_html_langue],
					 s_html_cfg_eqpmt.s_admin.ps8_identifiant,
					 s_html_cfg_eqpmt.s_admin.ps8_localisation);
			html_tag("<tr><td>&nbsp;</td></tr> \n");

			if(s_statutjdb_from_html.u16_nb_total_evt!=0)	//CONDITION: JDB non vide
			{
				HtmlJdb_PageDetail();
			}

			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td>&nbsp;</td></tr> \n");

			break;

	}
	
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");


}/*VJDBEvenement*/

//=====================================================================================
// Fonction		: HtmlJdb_Configuration
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: partie config jdb
//=====================================================================================
void HtmlJdb_Configuration(void)
{
	// Entrée au setup par mot de passe
	if(TRUE == TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form0\" target=\"frame_c\"> \n");
		form_hidden("URL","VJDBEvenement");
		html_tag("<input type=\"hidden\" name=\"param\" value=\"%d\"> \n",PAGE_HTML_JDB_CONFIG);
		form_hidden("hidden1","0");
		
		//Actions sur le jdb
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_actions_sur_fichier_jdb);
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><table border=\"1\" cellspacing=\"1\"> \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"200\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"80\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_action);
		html_tag("		</tr> \n");
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_effacer_jdb);
		html_tag("			<td><input type=\"button\"  value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_executer,
				 FORM_VJDBEVT_CLEAR);
		html_tag("		</tr> \n");
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_generer_jdb);
		html_tag("			<td><input type=\"button\"  value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_executer,
				 FORM_VJDBEVT_GENERATE_FILE);
		html_tag("		</tr> \n");
		html_tag("	</table></td></tr>\n");
		html_tag("</form> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td>&nbsp;</td></tr> \n");

	}


	html_tag("<tr><td>&nbsp;</td></tr> \n");

}/*HtmlJdb_Configuration*/

//=====================================================================================
// Fonction		: HtmlJdb_PageDetail
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: partie page jdb détaillé
//=====================================================================================
void HtmlJdb_PageDetail(void)
{
	u16sod loc_u16_idx;

	loc_u16_idx = 0;	//INIT	
	
	html_tag("<tr><td>\n");
	html_tag("<pre>");
	html_tag("<B>%-23s%-10s%s </B>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_date,
			 pt_tb_msg[u8_html_langue].ps8_msg_type,
			 pt_tb_msg[u8_html_langue].ps8_msg_libelle);
	html_tag("<B>%-22s </B>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_date_heure_format);

	//Parcours le JDB de l'évènement le plus récent à l'évènement le plus ancien
	for(loc_u16_idx=0;((loc_u16_idx<s_statutjdb_from_html.u16_nb_total_evt)&&(loc_u16_idx<s_statutjdb_from_html.u16_nb_total_evt));loc_u16_idx++)
	{
		HtmlAffiche_EvtJdb(&ps_completjdb_from_html[loc_u16_idx]);
	}

	html_tag("</pre>");
	html_tag("</td></tr>\n");
	
}/*HtmlJdb_PageDetail*/

//=====================================================================================
// Fonction		: HtmlAffiche_JdbPart
// Entrees		: <loc_u16_nb_evt_lus> : nombre d'évènements lus du fichier jdbpart
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Affichage de tous les évènements du fichier jdbpart
//=====================================================================================
void HtmlAffiche_JdbPart(u16sod loc_u16_nb_evt_lus)
{
	u8sod loc_u8_resultat;
	u16sod loc_u16_idx;
	u16sod loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_u16_idx = 0;	//INIT
	loc_u16_cpt = 0;	//INIT

	if(loc_u16_nb_evt_lus > 0)
	{
		//On lit la fifo à l'envers (du plus récent au plus ancient)
		loc_u16_idx = (loc_u16_nb_evt_lus-1);
		loc_u16_cpt = 0;
		do{
			HtmlAffiche_EvtJdb(&ps_fifoHtmlJdb[loc_u16_idx]);
			if(0 == loc_u16_idx) //CONDITION: dernier évt
			{
				loc_u8_resultat = FALSE; //on sort
			}
			else
			{
				loc_u16_idx--;
			}
			loc_u16_cpt++;
		}while((TRUE == loc_u8_resultat)&&
			   (loc_u16_cpt < NB_MAX_EVT_PAR_JDBPART)
			  );
	}
	
}/*HtmlAffiche_JdbPart*/

//=====================================================================================
// Fonction		: HtmlAffiche_EvtJdb
// Entrees		: <loc_ps_evt<	: element qui doit etre affiché
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Affichage d'un évènement du journal de bord
//=====================================================================================
void HtmlAffiche_EvtJdb(S_STRUCT_JDBEVT *loc_ps_evt)
{
	u16sod	loc_u16_indEvt;
	s8sod	loc_ps8_date[UI_TAILLE_MAX_MESSAGE+1];
	s8sod	loc_ps8_chaine_type_evt[UI_TAILLE_MAX_MESSAGE+1];
	s8sod	*loc_ps8_chaine_libelle;
	
	loc_u16_indEvt = loc_ps_evt->u16_index_evt; //MAJ
	strcpy(loc_ps8_date, "");	//INIT
	strcpy(loc_ps8_chaine_type_evt, "");	//INIT
	loc_ps8_chaine_libelle = NULL;	//INIT

	
	if(loc_u16_indEvt < NB_MAX_EVENEMENTS) //CONDITION: evt valide
	{
		//Date
		strcpy(loc_ps8_date, ps8GetChDate(&loc_ps_evt->s_date));

		//Type
		switch(loc_ps_evt->u8_etat_evt)
		{
			case ETAT_EVT_DEBUT:
				strcpy(loc_ps8_chaine_type_evt, pt_tb_msg[u8_html_langue].ps8_msg_debut);
				break;
			case ETAT_EVT_FIN:
				strcpy(loc_ps8_chaine_type_evt, pt_tb_msg[u8_html_langue].ps8_msg_fin);
				break;
			case ETAT_EVT_INFO:
				strcpy(loc_ps8_chaine_type_evt, pt_tb_msg[u8_html_langue].ps8_msg_info);
				break;
			default:
				strcpy(loc_ps8_chaine_type_evt, "?");
				break;
		}

		loc_ps8_chaine_libelle = ps8ChLibelleEvt(loc_u16_indEvt,
												loc_ps_evt->t_valeur_evt,
												loc_ps_evt->u_info_sup1.u32_term,
												loc_ps_evt->u8_info_sup2,
												loc_ps_evt->pu8_tab_info_sup3,
												loc_ps_evt->u8_etat_evt,
												u8_html_langue,
												MODE_AFF_LIB_EVT_POUR_HTML);

		html_tag("%-23s%-10s%s \n",
				 loc_ps8_date,
				 loc_ps8_chaine_type_evt,
				 loc_ps8_chaine_libelle);
	}
	
}/*HtmlAffiche_EvtJdb*/

//=====================================================================================
// Fonction		: u8AjouteEvtFifoHtmlJdb
// Entrees		: <loc_ps_evt<	: element qui doit etre ajouté
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 11/03/2010 -
// Description	: Ajoute element jdb dans la fifo html
//=====================================================================================
u8sod u8AjouteEvtFifoHtmlJdb(S_STRUCT_JDBEVT *loc_ps_evt)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = TRUE; //INIT

	if(u16_wr_fifohtmljdb < NB_MAX_EVT_PAR_JDBPART)
	{
		//Copie du contenu de l'élément du fichier jdbpart dans la fifoHtmljdb (ram)
		ps_fifoHtmlJdb[u16_wr_fifohtmljdb] = (*loc_ps_evt);

		//Puis on incrémente le pointeur d'écriture
		u16_wr_fifohtmljdb ++;		
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8AjouteEvtFifoHtmlJdb: Erreur pointeur d'écriture FifoHtmlJdb => %d \n",
					  u16_wr_fifohtmljdb));
	}

	return loc_u8_resultat;
}/*u8AjouteEvtFifoHtmlJdb*/

//=====================================================================================
// Fonction		: LectureCompleteJDB
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/05/2010
// Description	: lecture complète du journal de bord  (de l'évènement du plus récent au plus ancien)
//=====================================================================================
void LectureCompleteJDB(void)
{
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_numid_jdbpart;
	u16sod	loc_u16_nb_evt_lus;

	loc_u16_cpt = 0;	//INIT
	loc_u8_numid_jdbpart = 0;	//INIT
	loc_u16_nb_evt_lus = 0;	//INIT

	//Parcours le JDB de l'évènement le plus récent à l'évènement le plus ancien
	loc_u16_cpt = 0;	//RAZ
	loc_u8_numid_jdbpart = s_statutjdb_from_html.u8_numwr_jdbpart; //RAZ: du dernier fichier en cours d'écriture
	while(loc_u16_cpt < NB_MAX_JDBPART)
	{
		InitFifoHtmlJdb();	//RAZ
		//Lecture total d'un fihier jdbpart
		if(FALSE == u8ReadEvtJdbPart(&T_DEF_FILE_JDBPART, loc_u8_numid_jdbpart, u8AjouteEvtFifoHtmlJdb, &loc_u16_nb_evt_lus))
		{
			loc_u16_cpt = NB_MAX_JDBPART+1; //on sort
			MACRO_PRINTF(("LectureCompleteJDB: Erreur lecture %s \n",
						  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
		}
		else
		{
			if(loc_u16_nb_evt_lus > NB_MAX_EVT_PAR_JDBPART)
			{
				loc_u16_cpt = NB_MAX_JDBPART+1; //on sort
				MACRO_PRINTF(("LectureCompleteJDB: Erreur nb_evt_lus=%d dans %s KO \n",
							  loc_u16_nb_evt_lus,
							  ps8GetChNomFileJdbPart(loc_u8_numid_jdbpart)));
			}
			else //CONDITION: lecture OK
			{
				CopyPartToCompletJdb(loc_u16_nb_evt_lus);
			}
		}

		loc_u16_cpt ++;
		if(loc_u8_numid_jdbpart == s_statutjdb_from_html.u8_numrd_jdbpart) //CONDITION: on a tout lu
		{
			loc_u16_cpt = NB_MAX_JDBPART+1;	//on sort
		}
		else
		{
			//on passe à un autre fichier jdbpart
			if(loc_u8_numid_jdbpart > 0)
			{
				loc_u8_numid_jdbpart --;
			}
			else
			{
				loc_u8_numid_jdbpart = (NB_MAX_JDBPART-1);	//RAZ
			}
		}
	}

}/*LectureCompleteJDB*/

//=====================================================================================
// Fonction		: CopyPartToCompletJdb
// Entrees		: <loc_u16_nb_evt_lus> : nombre d'évènements lus du fichier jdbpart
// Sortie		: rien
// Auteur		: CM - 11/05/2010
// Description	: Lecture de tous les évènements du fichier jdbpart et on copie dans jdb complet
//=====================================================================================
void CopyPartToCompletJdb(u16sod loc_u16_nb_evt_lus)
{
	u8sod loc_u8_resultat;
	u16sod loc_u16_idx;
	u16sod loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_u16_idx = 0;	//INIT
	loc_u16_cpt = 0;	//INIT

	if(loc_u16_nb_evt_lus > 0)
	{
		//On lit la fifo à l'envers (du plus récent au plus ancient)
		loc_u16_idx = (loc_u16_nb_evt_lus-1);
		loc_u16_cpt = 0;
		do{
			//on copie dans jdb complet
			ps_completjdb_from_html[u16_wr_completjdb] = ps_fifoHtmlJdb[loc_u16_idx];
			u16_wr_completjdb++;
			if(0 == loc_u16_idx) //CONDITION: dernier évt
			{
				loc_u8_resultat = FALSE; //on sort
			}
			else
			{
				loc_u16_idx--;
			}
			loc_u16_cpt++;
		}while((TRUE == loc_u8_resultat)&&
			   (loc_u16_cpt < NB_MAX_EVT_PAR_JDBPART)
			  );
	}

}/*CopyPartToCompletJdb*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitCompletHtmlJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/05/2010
// Description	: Initialisation du jdb complet utilisée pour construire la page HTML
//=====================================================================================
void InitCompletHtmlJdb(void)
{
	u16sod loc_u16_i;

	u16_wr_completjdb = 0;	//INIT
	for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_JDBEVT;loc_u16_i++)
	{
		InitEvtJdb(&ps_completjdb_from_html[loc_u16_i]); //INIT
	}
}/*InitCompletHtmlJdb*/

//=====================================================================================
// Fonction		: InitFifoHtmlJdb
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/03/2010
// Description	: Initialisation de la fifo utilisée pour construire la page HTML
//=====================================================================================
void InitFifoHtmlJdb(void)
{
	u16sod loc_u16_i;

	u16_wr_fifohtmljdb = 0;	//INIT
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVT_PAR_JDBPART;loc_u16_i++)
	{
		InitEvtJdb(&ps_fifoHtmlJdb[loc_u16_i]); //INIT
	}
}/*InitFifoHtmlJdb*/

//=====================================================================================
// Fonction		: InitModule_VJdbEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de vjdbevt
//=====================================================================================
void InitModule_VJdbEvt(void)
{
	InitFifoHtmlJdb(); //INIT
	InitCompletHtmlJdb(); //INIT
	
}/*InitModule_VJdbEvt*/
