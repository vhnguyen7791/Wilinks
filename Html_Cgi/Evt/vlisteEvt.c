/*========================================================================*/
/* NOM DU FICHIER  : vlisteEvt.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 26/02/2010                                           */
/* Libelle         : HTML CGI: page HTML Evenements - liste				  */
/* Projet          : WRM100                                               */
/* Indice          : BE051												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE051 13/12/2010 CM
// - Correction page liste des évènements
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _VLISTEEVT

enum LISTE_FORM_VLISTEEVT
{
	FORM_VALID_ALL = 1,
	FORM_VALID_NONE,
	FORM_LOG_ALL,
	FORM_LOG_NONE,
	FORM_TRAP_ALL,
	FORM_TRAP_NONE,
	FORM_SYNTHESE_1_ALL,
	FORM_SYNTHESE_1_NONE,
	NB_MAX_FORM_VLISTEEVT
};

//Définition de la page VlistEvt
#define PLUSIEURS_PAGE_VLISTEVT	0	//0: UNE seule page	1: plusieurs pages

#define NB_EVTS_TRIES_PAR_TABLE	50

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct 
{
	s8sod	ps8_parametre				[10 + 1];
	s8sod	ps8_hidden1					[20 + 1];
} S_CONFIG_VLISTEEVT_RESULTS;

FIELD_LIST s_ConfigVListEvtFields[] = {
	{"param",			"%s",		offsetof(S_CONFIG_VLISTEEVT_RESULTS, ps8_parametre)	},
	{"hidden1",			"%s",		offsetof(S_CONFIG_VLISTEEVT_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/


//=====================================================================================
// Fonction		: proc_JavaScript_VListeEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/06/2007
// Description	: code de javascript de la page HTML VListeEvt
//=====================================================================================
void proc_JavaScript_VListeEvt(void);

//=====================================================================================
// Fonction		: proc_JavaScript_VListeEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/06/2007
// Description	: code de javascript de la page HTML VListeEvt
//=====================================================================================
void proc_JavaScript_VListeEvt(void)
{
	
	html_tag("<SCRIPT language=\"javascript\">\n");

					   
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{ \n"
			 "	form.hidden1.value = i_numForm;\n"
			 "	form.submit();\n"
			 "} \n");	
	
	
	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_VListeEvt*/

//=====================================================================================
// Fonction		: VListeEvt
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 29/06/2007
// Description	: Page HTML Liste des évènements
//				"URL=VListeEvt&param=<num_page_html>&hidden1=<numForm>"
//					<num_page_html> : numéro page HTML
//					<numForm> : suite action boutons
//=====================================================================================
void VListeEvt(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_VLISTEEVT_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;
	u8sod	loc_u8_numero_page;
	u32sod  loc_u32_NumeroForm;
	u8sod	loc_u8_nbLignes;
	u16sod	loc_u16_cpt_pour_bouton;
	s8sod	loc_ps8_chaine_niveau_gravite[UI_TAILLE_MAX_MESSAGE];
	s8sod	loc_ps8_chaine_libelle[UI_TAILLE_MAX_MESSAGE];
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;
	u8sod	loc_u8_result_test;

	loc_u16_cpt_pour_bouton = 0;	//INIT
	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=VListeEvt&param=<num_page_html>
	{
		loc_u8_numero_page = atoi(loc_p_varlist[3]);
		if(loc_u8_numero_page < NB_MAX_PAGES_HTML_VLISTEEVT)
		{
			;	//page ok
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
	

	if (s32GetArgNb(loc_p_varlist) > 4)  //URL=VListeEvt&param=<num_page_html>&hidden1=<numForm>"
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_VLISTEEVT_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigVListEvtFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{	//on sort a 0 : pb dans decodage
			//on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			loc_u32_NumeroForm = (u32sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u32_NumeroForm < NB_MAX_FORM_VLISTEEVT)
			{
				if(FORM_VALID_ALL == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						SetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_VALIDE);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_VALID_NONE == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						ResetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_VALIDE);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_LOG_ALL == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						SetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_JDB);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_LOG_NONE == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						ResetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_JDB);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_TRAP_ALL == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						SetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_TRAP);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_TRAP_NONE == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						ResetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_TRAP);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_SYNTHESE_1_ALL == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						SetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_SYNTHESE_1);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_SYNTHESE_1_NONE == loc_u32_NumeroForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						ResetAllEventsAction(&s_html_cfg_eqpmt, ACTION_EVT_SYNTHESE_1);
						if(TRUE==u8TestConfigTabEvt(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigTabEvt(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				

				//On recharge la page pour re-initialiser les champs "objets" HTML
				sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d",
						loc_u8_numero_page);
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

	
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		sprintf(ps8_pageHtmlEnCours,"VListeEvt&param=%d",
				loc_u8_numero_page);
		
		PreparePagePswd(ps8_pageHtmlEnCours);
		return;
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

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
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_evenements);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d",
			loc_u8_numero_page);
	JSActualiser(ps8_pageHtmlEnCours);	//pour la fonction Actualiser

	proc_JavaScript_VListeEvt();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","VListeEvt");//permet d'avoir la bonne page de rafraichit!!
	html_tag("<INPUT TYPE=\"HIDDEN\" NAME=\"param\" VALUE=\"%d\"> \n",
			 loc_u8_numero_page);
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"600\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_evenements);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_VListeEvt);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

#if PLUSIEURS_PAGE_VLISTEVT
	switch(loc_u8_numero_page)
	{
		case PAGE_VLISTEVT_NUM_1:
			html_tag("<tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"> \n"
					 "			<tr> \n"
					 "				<td><ul><li><B>%s</B></li></ul></td> \n"
					 "				<td>&nbsp;&nbsp;</td> \n"
					 "				<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d\" target=\"frame_c\">%s</a></li></ul></td> \n"
					 "			</tr> \n"
					 "</table></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_validation_jdb_trap,
					 PAGE_VLISTEVT_NUM_2,
					 pt_tb_msg[u8_html_langue].ps8_msg_synthese_1_a_3);
			break;
		case PAGE_VLISTEVT_NUM_2:
			html_tag("<tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\"> \n"
					 "			<tr> \n"
					 "				<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d\" target=\"frame_c\">%s</a></li></ul></td> \n"
					 "				<td>&nbsp;&nbsp;</td> \n"
					 "				<td><ul><li><B>%s</B></li></ul></td> \n"
					 "			</tr> \n"
					 "</table></td></tr> \n",
					 PAGE_VLISTEVT_NUM_1,
					 pt_tb_msg[u8_html_langue].ps8_msg_validation_jdb_trap,
					 pt_tb_msg[u8_html_langue].ps8_msg_synthese_1_a_3);
			break;
		default:
			break;
	}
#endif
	
					
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td> \n");
	loc_u8_nbLignes = 0;	//INIT
	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{
			if (0 == (loc_u8_nbLignes % NB_EVTS_TRIES_PAR_TABLE))
			{
				html_tag("<table border=\"1\" cellpadding=\"1\" cellspacing=\"1\"> \n");
				html_tag("		<tr> \n");
				html_tag("			<th width=\"10\">%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_code);
				html_tag("			<th width=\"80\">%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_niveau_de_gravite);
				html_tag("			<th width=\"250\">%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_libelle);
				html_tag("			<th width=\"50\">%s</th> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_disponible_M);
				
				switch(loc_u8_numero_page)
				{
					case PAGE_VLISTEVT_NUM_1:
						html_tag("			<th width=\"50\">%s</th> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_validation);
						html_tag("			<th width=\"50\">%s</th> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_jdb);
						html_tag("			<th width=\"50\">%s</th> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_TRAP);
						html_tag("			<th nowrap width=\"60\">%s</th> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_synthese);
						break;
					case PAGE_VLISTEVT_NUM_2:
					default:
						break;
				}
				html_tag("		</tr> \n");
			}

			if(		(TRUE == TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
				&&	(0 == loc_u16_cpt_pour_bouton)
			  )//CONDITION: on affiche les 2 lignes de boutons
			{
				switch(loc_u8_numero_page)
				{
					case PAGE_VLISTEVT_NUM_1:
						html_tag("		<tr> \n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td>&nbsp;</td>\n");
						
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_tous,
								 FORM_VALID_ALL);
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_tous,
								 FORM_LOG_ALL);
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_tous,
								 FORM_TRAP_ALL);
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_tous,
								 FORM_SYNTHESE_1_ALL);
						html_tag("		</tr> \n");
						html_tag("		<tr> \n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td>&nbsp;</td>\n");
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_aucun,
								 FORM_VALID_NONE);
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_aucun,
								 FORM_LOG_NONE);
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_aucun,
								 FORM_TRAP_NONE);
						html_tag("			<td><input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
								 pt_tb_msg[u8_html_langue].ps8_msg_aucun,
								 FORM_SYNTHESE_1_NONE);
						html_tag("		</tr> \n");
						break;
					case PAGE_VLISTEVT_NUM_2:
					default:
						break;
				}
			}

			//Lecture de la configuration d'un évènemnt
			loc_s_cfg_evt = s_html_cfg_eqpmt.s_tabevt.s_event[loc_u16_indEvt];
			
			html_tag("		<tr> \n");
			//code
			html_tag("			<td>%d</td> \n",
					 S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt);
			//Niveau de gravité
			ChNiveauGravite(loc_ps8_chaine_niveau_gravite, loc_s_cfg_evt.u8_niveau_gravite, u8_html_langue);
			html_tag("			<td>%s</td> \n",
					 loc_ps8_chaine_niveau_gravite);
			//Libellé
			strcpy(loc_ps8_chaine_libelle, pt_tb_msg[u8_html_langue].ps8_msg_lib_evenement[loc_u16_indEvt]);
			html_tag("	<td><a href=\"/cgi-bin/cgi_fh?URL=SUConfigEvt&param=%lu\" target=\"frame_c\">%s</td> \n",
					 (u32sod)S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt + (u32sod)(loc_u8_numero_page<<14),
					 loc_ps8_chaine_libelle);

			//Disponibilité
			if(TRUE == u8TestEventDisponible(loc_u16_indEvt)) //CONDITION: Disponible
			{
				html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_oui);
			}
			else
			{
				html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_non);
			}

			switch(loc_u8_numero_page)
			{
				case PAGE_VLISTEVT_NUM_1:
					if(TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					{
						//Validation
						if (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_VALIDE))
						{
							html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_oui);
						}
						else
						{
							html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_non);
						}
					}
					else
					{
						html_tag("	<td>&nbsp;</td> \n");
					}
					if(		(TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
						||	(TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					  )
					{
						//JDB
						if (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_JDB))
						{
							html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_oui);
						}
						else
						{
							html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_non);
						}
					}
					else
					{
						html_tag("	<td>&nbsp;</td> \n");
					}
					//TRAP
					if (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_TRAP))
					{
						html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_oui);
					}
					else
					{
						html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_non);
					}
					if(TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					{
						if((EVT000_AL_SYNTHESE_1 == loc_u16_indEvt)
						  ) //CONDITION: alarmes de synhèse
						{
							html_tag("	<td>&nbsp;</td> \n");
						}
						else  //CONDITION: autres alarmes
						{
							if (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_SYNTHESE_1))
							{
								html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_oui);
							}
							else
							{
								html_tag("	<td>%s</td> \n",pt_tb_msg[u8_html_langue].ps8_msg_non);
							}
						}
					}
					else
					{
						html_tag("	<td>&nbsp;</td> \n");
					}
					break;
				case PAGE_VLISTEVT_NUM_2:
				default:
					break;
			}
			html_tag("		</tr> \n");

			if ((NB_EVTS_TRIES_PAR_TABLE-1) == (loc_u8_nbLignes % NB_EVTS_TRIES_PAR_TABLE))
			{
				html_tag("</table><P> \n");
				loc_u8_nbLignes = 0;	//Mise à 0
			}
			else
			{
				loc_u8_nbLignes ++;
			}
		}
		loc_u16_cpt_pour_bouton++;
	}

	if (loc_u8_nbLignes != NB_EVTS_TRIES_PAR_TABLE)
	{
		html_tag("</table> \n");
	}
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");
}/*VListeEvt*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VListeEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de VListeEvt
//=====================================================================================
void InitModule_VListeEvt(void)
{
}/*InitModule_VListeEvt*/
