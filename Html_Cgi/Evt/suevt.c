/*========================================================================*/
/* NOM DU FICHIER  : suevt.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 26/02/2010                                           */
/* Libelle         : HTML CGI: page HTML Evenements - config UN EVT		  */
/* Projet          : WRM100	                                              */
/* Indice          : BE014												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 26/02/2010 CM
//	- CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUEVT

enum LISTE_DES_FORM_SUEVT
{
	FORM_SUEVT_PREVIOUS_EVENT = 1,
	FORM_SUEVT_VALID_EVENT,
	FORM_SUEVT_VALID_AND_NEXT_EVENT,
	FORM_SUEVT_NEXT_EVENT,
	NB_MAX_FORM_SUEVT
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct 
{
	s8sod	ps8_niveauGravite				[20 + 1];
	s8sod	ps8_actionEvt[NB_MAX_ACTION_EVT][20 + 1];
	s8sod	ps8_parametre					[10 + 1];
	s8sod	ps8_hidden1						[20 + 1];
} S_CONFIG_SUEVT_RESULTS;

FIELD_LIST s_ConfigSUEvtFields[] = {
	{"niveauGravite",	"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_niveauGravite)						},
	{"actionEvt0",		"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_actionEvt[ACTION_EVT_SYNTHESE_1])	},
	{"actionEvt3",		"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_actionEvt[ACTION_EVT_VALIDE])		},
	{"actionEvt4",		"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_actionEvt[ACTION_EVT_JDB])			},
	{"actionEvt5",		"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_actionEvt[ACTION_EVT_TRAP])		},
	{"param",			"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_parametre)							},
	{"hidden1",			"%s",				offsetof(S_CONFIG_SUEVT_RESULTS, ps8_hidden1)							},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_ConfigEvtEvenementResultsToStruct
// Entrees		: <loc_u16_indice>
//				  >ps_cfg_evt<	: structure de la config base de données
//				  <loc_ps_results>	: structure renseignée dans la page HTML de modification de configuration
// Sortie		: rien
// Auteur		: CM - 21/04/2004 -
// Description	: Conversion d'une structure S_CONFIG_SUEVT_RESULTS vers S_STRUCT_CONFIG_EVT 
//=====================================================================================
void proc_ConfigEvtEvenementResultsToStruct(u16sod loc_u16_indice, S_STRUCT_CFG_EVENT *ps_cfg_evt, S_CONFIG_SUEVT_RESULTS *loc_ps_results);


//=====================================================================================
// Fonction		: proc_JavaScript_SUConfig_Evt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 19/09/2005 -
// Description	: code de javascript de la page SUConfigEvt
//=====================================================================================
void proc_JavaScript_SUConfig_Evt(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfig_Evt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 19/09/2005 -
// Description	: code de javascript de la page SUConfigEvt
//=====================================================================================
void proc_JavaScript_SUConfig_Evt(void)
{
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{ \n"
			 "	form.hidden1.value = i_numForm;\n"
			 "	form.submit();\n"
			 "} \n");	

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfig_Evt*/

//=====================================================================================
// Fonction		: SUConfigEvt
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 24/06/2007
// Description	: Page HTML Configuration: configuration d'UN EVT
//				"URL=SUConfigEvt&param=<parametre>&hidden1=<numForm>"
//					<parametre> : numeroEvt + Page ListeEvt
//					<numForm> : suite action boutons
//=====================================================================================
void SUConfigEvt(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_SUEVT_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u32sod  loc_u32_NumeroForm;
	u16sod  loc_u16_indice_courant;
	u16sod  loc_u16_indice_precedent;
	u16sod  loc_u16_indice_prochain;
	u16sod	loc_u16_page_Vliste;
	u16sod	loc_u16_numero;
	u16sod	loc_u16_parametre;
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;
	u8sod	loc_u8_niveau_gravite;
	s8sod	loc_ps8_chaine_libelle[UI_TAILLE_MAX_MESSAGE];
	u8sod	loc_u8_result_test;

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 4 utilise pour URL=SUConfigEvt&param=<parametre>
	{
		loc_u16_parametre = (u16sod)atoi(loc_p_varlist[3]);
		loc_u16_numero = (u16sod)(loc_u16_parametre & 0x3FFF);
		loc_u16_page_Vliste = (u16sod)((loc_u16_parametre & 0xC000) >> 14); //on récupère la page source
		
		if(		(loc_u16_page_Vliste < NB_MAX_PAGES_HTML_VLISTEEVT)
			||	(US_INDICE_NON_TROUVE != u16RechercheIndiceEvt(loc_u16_numero))
		  )//CONDITION: paramètres OK
		{
			loc_u16_indice_courant = (u16sod)u16RechercheIndiceEvt(loc_u16_numero);
			if(US_INDICE_NON_TROUVE != loc_u16_indice_courant)
			{
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(FALSE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
				{
					u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
				}
				else
				{
					loc_s_cfg_evt = s_html_cfg_eqpmt.s_tabevt.s_event[loc_u16_indice_courant];
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				//Test si accès au contenu page 
				if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
				{
					return; // on sort!
				}
			}
			else//CONDITION: page KO
			{
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return;
			}
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
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		sprintf(ps8_pageHtmlEnCours,"SUConfigEvt&param=%d",
				loc_u16_parametre);

		PreparePagePswd(ps8_pageHtmlEnCours);
		return;
	}
	

	if (s32GetArgNb(loc_p_varlist) > 4)  //URL=SUConfigEvt&param=<parametre>&hidden1=<numForm>"
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_SUEVT_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigSUEvtFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u32_NumeroForm = (u32sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u32_NumeroForm < NB_MAX_FORM_SUEVT)
			{
				//Détermination numéro précédent et suivant
				loc_u16_indice_precedent = u16GetPreviousIndiceEvenementValide(loc_u16_indice_courant);
				loc_u16_indice_prochain = u16GetNextIndiceEvenementValide(loc_u16_indice_courant);

				if(		(FORM_SUEVT_VALID_EVENT == loc_u32_NumeroForm)
					||	(FORM_SUEVT_VALID_AND_NEXT_EVENT == loc_u32_NumeroForm)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_html_cfg_eqpmt))
					{
						proc_ConfigEvtEvenementResultsToStruct(loc_u16_indice_courant, &s_html_cfg_eqpmt.s_tabevt.s_event[loc_u16_indice_courant], &loc_s_results);
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
				else
				{
					loc_u8_result_test = TRUE;
				}

				switch(loc_u32_NumeroForm)
				{
					case FORM_SUEVT_PREVIOUS_EVENT:
						if(US_INDICE_NON_TROUVE != loc_u16_indice_precedent)
						{
							sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=SUConfigEvt&param=%lu",
									(u32sod)S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice_precedent].u16_numero_evt + (u32sod)(loc_u16_page_Vliste<<14));
						}
						else
						{
							sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=SUConfigEvt&param=%d",loc_u16_page_Vliste);
						}
						break;
					case FORM_SUEVT_VALID_EVENT:
						sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d",loc_u16_page_Vliste);
						break;
					case FORM_SUEVT_VALID_AND_NEXT_EVENT:
					case FORM_SUEVT_NEXT_EVENT:
						if(US_INDICE_NON_TROUVE != loc_u16_indice_prochain)
						{
							sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=SUConfigEvt&param=%lu",
									(u32sod)S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice_prochain].u16_numero_evt + (u32sod)(loc_u16_page_Vliste<<14));
						}
						else
						{
							sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d",loc_u16_page_Vliste);
						}
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
				Html_GotoPage(ps8_pageHtmlRetour);
				return;
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

	//Lecture de la configuration de l'évènement
	loc_s_cfg_evt  = s_html_cfg_eqpmt.s_tabevt.s_event[loc_u16_indice_courant];
	
	strcpy(loc_ps8_chaine_libelle,pt_tb_msg[u8_html_langue].ps8_msg_lib_evenement[loc_u16_indice_courant]);
	loc_u8_niveau_gravite = loc_s_cfg_evt.u8_niveau_gravite;
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_evenements,
			 loc_ps8_chaine_libelle);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=SUConfigEvt&param=%d",
			loc_u16_parametre);
	JSActualiser(ps8_pageHtmlEnCours);	//pour la fonction Actualiser

	proc_JavaScript_SUConfig_Evt();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigEvt");//permet d'avoir la bonne page de rafraichit!!
	html_tag("<INPUT TYPE=\"HIDDEN\" NAME=\"param\" VALUE=\"%d\"> \n",
			 loc_u16_parametre);
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_evenements,
			 loc_ps8_chaine_libelle);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigEvt);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=VListeEvt&param=%d\" target=\"frame_c\">%s %s</a></li></ul></td></tr> \n",
			 loc_u16_page_Vliste,
			 pt_tb_msg[u8_html_langue].ps8_msg_retours_a_la_page,
			 pt_tb_msg[u8_html_langue].ps8_msg_parametrage_evenements);

	if(FALSE == u8TestEventDisponible(loc_u16_indice_courant)) //CONDITION: Disponible
	{
		html_tag("<TR><TD>&nbsp;<P class=warning>%s</P></TD></TR> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_evenement_indisponible);
	}
	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	
	//Table Niveau gravite
	html_tag("<tr><td><table width=\"440\" border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"20\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_code);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_niveau_de_gravite);
	html_tag("			<th width=\"270\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_libelle);
	html_tag("		</tr> \n");

	html_tag("		<tr> \n");
	//Code
	html_tag("			<td>%d</td> \n",
			 loc_u16_numero);
	//Niveau de gravité
	html_tag("		   <td><select name=\"niveauGravite\"> \n");
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((NIV_GRAVITE_INDETERMINE == loc_u8_niveau_gravite) ? "selected" : ""),
			 NIV_GRAVITE_INDETERMINE,
			 pt_tb_msg[u8_html_langue].ps8_msg_indetermine);
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((NIV_GRAVITE_CRITIQUE == loc_u8_niveau_gravite) ? "selected" : ""),
			 NIV_GRAVITE_CRITIQUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_critique);
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((NIV_GRAVITE_MAJEUR == loc_u8_niveau_gravite) ? "selected" : ""),
			 NIV_GRAVITE_MAJEUR,
			 pt_tb_msg[u8_html_langue].ps8_msg_majeur);
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((NIV_GRAVITE_MINEUR == loc_u8_niveau_gravite) ? "selected" : ""),
			 NIV_GRAVITE_MINEUR,
			 pt_tb_msg[u8_html_langue].ps8_msg_mineur);
	html_tag("		   <option %s value=\"%d\">%s</option>	\n",
			 ((NIV_GRAVITE_AVERTISSEMENT == loc_u8_niveau_gravite) ? "selected" : ""),
			 NIV_GRAVITE_AVERTISSEMENT,
			 pt_tb_msg[u8_html_langue].ps8_msg_avertissement);
	html_tag("			 </select></td> \n");
	//Libellé
	html_tag("			<td>%s</td> \n",
			 loc_ps8_chaine_libelle);
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Table Choix des Actions
	html_tag("<tr><td><table width=\"440\" border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th colspan=\"4\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_choix_actions);
	html_tag("		</tr> \n");
	if(TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice_courant].u8_type_evt)//CONDITION: Evts communs à tous les équipements
	{
		//On affiche que la configuration TRAP
		html_tag("		<tr> \n");
		html_tag("			<td colspan=\"2\" width=\"190\">%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_SNMP_TRAP);
		html_tag("			<td colspan=\"2\" width=\"250\"><input %s name=\"actionEvt5\" type=\"checkbox\"></td> \n",
				 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_TRAP)) ? " CHECKED" : "");
		html_tag("		</tr> \n");
	}
	else
	{
		if(		(TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice_courant].u8_type_evt)
		  )//CONDITION: evt de type info ou alarme instable
		{
			//On affiche que la configuration TRAP et JDB
			html_tag("		<tr> \n");
			html_tag("			<td width=\"190\">%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_jdb);
			html_tag("			<td width=\"30\"><input %s name=\"actionEvt4\" type=\"checkbox\"></td> \n",
					 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_JDB)) ? " CHECKED" : "");
			html_tag("			<td width=\"190\">%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_SNMP_TRAP);
			html_tag("			<td width=\"30\"><input %s name=\"actionEvt5\" type=\"checkbox\"></td> \n",
					 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_TRAP)) ? " CHECKED" : "");
			html_tag("		</tr> \n");
		}
		else	//CONDITION: TYPE_EVT_ALARME Evts de type alarme "stable"
		{
			if(		(EVT000_AL_SYNTHESE_1 == loc_u16_indice_courant)
			  ) //CONDITION: alarmes de synhèse
			{
				; //
			}
			else
			{
				html_tag("		<tr> \n");
				html_tag("			<td>%s</td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_synthese);
				html_tag("			<td><input %s name=\"actionEvt0\" type=\"checkbox\"></td> \n",
						 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_SYNTHESE_1)) ? " CHECKED" : "");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("		</tr> \n");

				html_tag("		<tr> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("			<td>&nbsp;</td> \n");
				html_tag("		</tr> \n");
			}
			
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_validation);
			html_tag("			<td><input %s name=\"actionEvt3\" type=\"checkbox\"></td> \n",
					 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_VALIDE)) ? " CHECKED" : "");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("			<td>&nbsp;</td> \n");
			html_tag("		</tr> \n");

			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_jdb);
			html_tag("			<td><input %s name=\"actionEvt4\" type=\"checkbox\"></td> \n",
					 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_JDB)) ? " CHECKED" : "");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_SNMP_TRAP);
			html_tag("			<td><input %s name=\"actionEvt5\" type=\"checkbox\"></td> \n",
					 (TRUE == u8GetEventAction(loc_s_cfg_evt.u16_action, ACTION_EVT_TRAP)) ? " CHECKED" : "");
			html_tag("		</tr> \n");
		}
	}
	html_tag("</table></td></tr> \n");

	html_tag("<TR><TD>&nbsp;</TD></TR>\n");
	//Détermination numéro précédent et suivant
	loc_u16_indice_precedent = u16GetPreviousIndiceEvenementValide(loc_u16_indice_courant);
	loc_u16_indice_prochain = u16GetNextIndiceEvenementValide(loc_u16_indice_courant);

	//Boutons
	html_tag("<tr><td><table><tr>");
	if(US_INDICE_NON_TROUVE != loc_u16_indice_precedent)
	{
		html_tag("<td><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_bouton_precedent,
				FORM_SUEVT_PREVIOUS_EVENT);
	}
	else
	{
		html_tag("<td width=111>&nbsp;</td> \n");
	}
	html_tag("<td><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			FORM_SUEVT_VALID_EVENT);
	if(US_INDICE_NON_TROUVE != loc_u16_indice_prochain)
	{
		html_tag("<td><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valider_et_suivant,
				 FORM_SUEVT_VALID_AND_NEXT_EVENT);
		html_tag("<td><input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_bouton_suivant,
				 FORM_SUEVT_NEXT_EVENT);
	}
	html_tag("</table></td></tr> \n");

	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigEvt*/

//=====================================================================================
// Fonction		: proc_ConfigEvtEvenementResultsToStruct
// Entrees		: <loc_u16_indice>
//				  >ps_cfg_evt<	: structure de la config base de données
//				  <loc_ps_results>	: structure renseignée dans la page HTML de modification de configuration
// Sortie		: rien
// Auteur		: CM - 21/04/2004 -
// Description	: Conversion d'une structure S_CONFIG_SUEVT_RESULTS vers S_STRUCT_CONFIG_EVT 
//=====================================================================================
void proc_ConfigEvtEvenementResultsToStruct(u16sod loc_u16_indice, S_STRUCT_CFG_EVENT *ps_cfg_evt, S_CONFIG_SUEVT_RESULTS *loc_ps_results)
{
	u16sod	loc_u16_i;
			
	ps_cfg_evt->u8_niveau_gravite = (u8sod)atoi(loc_ps_results->ps8_niveauGravite);

	if(TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice].u8_type_evt)//CONDITION: Evts communs à tous les équipements
	{
		if (0 == strcmp(&loc_ps_results->ps8_actionEvt[ACTION_EVT_TRAP][0], "on"))
		{	
			SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
		}
		else
		{
			ResetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
		}
	}
	else
	{
		if(TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indice].u8_type_evt)//CONDITION: Evts communs à tous les équipements
		{
			SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_VALIDE);

			if (0 == strcmp(&loc_ps_results->ps8_actionEvt[ACTION_EVT_TRAP][0], "on"))
			{	
				SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
			}
			else
			{
				ResetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
			}
			
			if (0 == strcmp(&loc_ps_results->ps8_actionEvt[ACTION_EVT_JDB][0], "on"))
			{	
				SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_JDB);
			}
			else
			{
				ResetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_JDB);
			}
			
		}
		else	//CONDITION: TYPE_EVT_ALARME Evts de type alarme
		{
			if(		(EVT000_AL_SYNTHESE_1 == loc_u16_indice)
			  ) //CONDITION: alarmes de synhèse
			{
				if (0 == strcmp(&loc_ps_results->ps8_actionEvt[ACTION_EVT_VALIDE][0], "on"))
				{	
					SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_VALIDE);
				}
				else
				{
					ResetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_VALIDE);
				}
				
				if (0 == strcmp(&loc_ps_results->ps8_actionEvt[ACTION_EVT_TRAP][0], "on"))
				{	
					SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
				}
				else
				{
					ResetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
				}

				if (0 == strcmp(&loc_ps_results->ps8_actionEvt[ACTION_EVT_JDB][0], "on"))
				{	
					SetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_JDB);
				}
				else
				{
					ResetEventAction(&ps_cfg_evt->u16_action, ACTION_EVT_JDB);
				}
			}
			else
			{
				for(loc_u16_i=0;loc_u16_i<NB_MAX_ACTION_EVT;loc_u16_i++)
				{
					if (0 == strcmp(&loc_ps_results->ps8_actionEvt[loc_u16_i][0], "on"))
					{	
						SetEventAction(&ps_cfg_evt->u16_action, (u8sod)loc_u16_i);
					}
					else
					{
						ResetEventAction(&ps_cfg_evt->u16_action, (u8sod)loc_u16_i);
					}
				}
			}
		}
	}

}/*proc_ConfigEvtEvenementResultsToStruct*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUEvt
//=====================================================================================
void InitModule_SUEvt(void)
{
}/*InitModule_SUEvt*/
