/*========================================================================*/
/* NOM DU FICHIER  : suadmcontrol.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML Administration - Control		  */
/* Projet          : WRM100                                               */
/* Indice          : BE065                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE037 06/07/2010 CM
// - Modification page HTML Admin - Controle pour redémarrer équipement
//		afin de confirmer un redémarrage par javascript
// - Modification page HTML Admin - Controle pour raz générale
//		afin de confirmer le raz par javascript
//BE051 13/12/2010 CM
// - Probleme horodatage de l'évènement JDB lors d'un RAZ général
//BE065.1 02/05/2012 (CM)
// - Correction libellé dans page Html Administration - Controle
//		-> correction warning sur restauration config par défaut
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUADMCONTROL

enum LISTE_DES_FORM_SUADMCONTROL
{
	FORM_SUADMCONTROL_RESTART_EQUIPMENT = 1,
	FORM_SUADMCONTROL_RAZ_TOUTES_MESURES,
	FORM_SUADMCONTROL_PASSAGE_CONFIG_DEFAUT,
	NB_MAX_FORM_SUADMCONTROL
};

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_hidden1					[20 + 1];
} S_CONFIG_ADMINCONTROL_RESULTS;

FIELD_LIST s_ConfigAdmControlFields[] = {
	{"hidden1",					"%s",		offsetof(S_CONFIG_ADMINCONTROL_RESULTS, ps8_hidden1)					},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_AdminControl
// Entrees		: rien
// Sortie		: rien
// Description	: code de javascript des pages Adminsitration
//=====================================================================================
void proc_JavaScript_AdminControl(void)
{
	html_tag("<SCRIPT language=\"javascript\">\n");
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
			 FORM_SUADMCONTROL_RESTART_EQUIPMENT,
			 pt_tb_msg[u8_html_langue].ps8_msg_confirmer_redemarrage_equipement);

	html_tag("		case %d: \n"
			 "			if ( confirm(\"%s\") )\n"
			 "			{ \n"
			 "				loc_result = true;\n"
			 "			} \n"
			 "		break; \n",
			 FORM_SUADMCONTROL_RAZ_TOUTES_MESURES,
			 pt_tb_msg[u8_html_langue].ps8_msg_confirmer_raz_generale);
	
	html_tag("		case %d: \n"
			 "			if ( confirm(\"%s\") )\n"
			 "			{ \n"
			 "				loc_result = true;\n"
			 "			} \n"
			 "		break; \n",
			 FORM_SUADMCONTROL_PASSAGE_CONFIG_DEFAUT,
			 pt_tb_msg[u8_html_langue].ps8_msg_etes_vous_sur_de_restaurer_configuration_par_defaut);
	
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

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_AdminControl*/

//=====================================================================================
// Fonction		: SUAdmControle
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: 
// Description	: Page HTML Administration: Controle
//=====================================================================================
void SUAdmControle(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_CONFIG_ADMINCONTROL_RESULTS loc_s_results;
	s8sod loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	S_STRUCT_CIP_MONITOR loc_s_cip_monitor_tempo;

	memset(&loc_s_cip_monitor_tempo, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUAdmControle");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_CONFIG_ADMINCONTROL_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_ConfigAdmControlFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage
			//on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			if (atoi(loc_s_results.ps8_hidden1) < NB_MAX_FORM_SUADMCONTROL)
			{
				switch(atoi(loc_s_results.ps8_hidden1))
				{
					case FORM_SUADMCONTROL_RESTART_EQUIPMENT:
						//On signale le redémarrage de l'équipement
						s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillCipMonitor(&loc_s_cip_monitor_tempo))
						{
							loc_s_cip_monitor_tempo.u8_restart_equipment = TRUE;
							u8EditCipMonitor(&loc_s_cip_monitor_tempo);
						}
						s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
						
						OrdreResetUc();
						sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_RESET_EQUIPEMENT_EN_COURS);
						Html_GotoPage(ps8_pageHtmlRetour);
						break;

					case FORM_SUADMCONTROL_RAZ_TOUTES_MESURES:
						//On signale le RAZ du journal de bord au processus jdb
						s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillCipJdb(&s_cip_jdb_from_html))
						{
							s_cip_jdb_from_html.u8_effacer_jdb = TRUE;
							u8EditCipJdb(&s_cip_jdb_from_html);
						}
						s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
						
						//On signale le RAZ des alarmes mémorisées au processus monitor
						s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
						if(TRUE == u8FillCipMonitor(&loc_s_cip_monitor_tempo))
						{
							loc_s_cip_monitor_tempo.u8_raz_general = TRUE;
							u8EditCipMonitor(&loc_s_cip_monitor_tempo);
						}
						s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
						break;
					case FORM_SUADMCONTROL_PASSAGE_CONFIG_DEFAUT:
						s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
						memset(&s_html_cfg_eqpmt,'\0',sizeof(S_STRUCT_CONFIGURATION)); //RAZ
						PassageConfigDefaut(&s_html_cfg_eqpmt, MODE_PASSAGECONFIGDEFAUT_TOTAL);
						s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
						
						//Puis on reset l'équipement
						OrdreResetUc();

						
						sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
								WARNING_RESET_EQUIPEMENT_EN_COURS);
						Html_GotoPage(ps8_pageHtmlRetour);
						break;
					default:
						break;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				Html_GotoPage("/cgi-bin/cgi_fh?URL=SUAdmControle");
				return; // on sort!
			}
			else
			{
				//on fait une page pour le debug
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return; // on sort!
			}
		}
	}

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_controle);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUAdmControle");	//pour la fonction Actualiser
	proc_JavaScript_AdminControl();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"formControle\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmControle");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_controle);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_controle);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Table
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");

	//Redémarrage de l'équipement
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_redemarrage_equipement);
	html_tag("			<td><input type=\"button\"  value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_executer,
			 FORM_SUADMCONTROL_RESTART_EQUIPMENT);
	html_tag("		</tr> \n");


	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//Table
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_action);
	html_tag("		</tr> \n");
	//Remise à zéro (JDB, mesures, alarmes mémorisées)
	html_tag("		<tr> \n");
	html_tag("			<td>");
	html_tag("%s<BR>", //VIRGULE
			 pt_tb_msg[u8_html_langue].ps8_msg_commande_raz_generale);
	
	html_tag("- %s<BR>"
			 "- %s<BR>", //VIRGULE
			 pt_tb_msg[u8_html_langue].ps8_msg_effacer_toutes_les_alarmes,
			 pt_tb_msg[u8_html_langue].ps8_msg_effacer_jdb);
	html_tag("- %s<BR>",//VIRGULE
			 pt_tb_msg[u8_html_langue].ps8_msg_acquitter_tous_les_traps);
	html_tag("			</td> \n");
	html_tag("			<td><input type=\"button\"  value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_executer,
			 FORM_SUADMCONTROL_RAZ_TOUTES_MESURES);
	html_tag("		</tr> \n");

	html_tag("</table></td></tr> \n");

	//Passage en configuration par défaut sauf adresse IP, mask + GW
	if(TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
	{
		html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
//d: BE065.1 02/05/2012 (CM) - Correction libellé dans page Html Administration - Controle
//		html_tag("<tr><td><P class=warning>%s</td></tr> \n",
//				 pt_tb_msg[u8_html_langue].ps8_avertissement_restauration_config_defaut);
		html_tag("<tr><td><P class=warning>%s<BR>%s</td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_avertissement_restauration_config_defaut,
				 pt_tb_msg[u8_html_langue].ps8_msg_information_config_par_defaut);
//f: BE065.1 02/05/2012 (CM) - Correction libellé dans page Html Administration - Controle
		html_tag("<tr><td>&nbsp;</td></tr> \n");

		//Table
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"250\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"100\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_action);
		html_tag("		</tr> \n");
		html_tag("		<tr> \n");
		html_tag("			<td>%s &nbsp;<SUP>1)</SUP></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_restaurer_configuration_par_defaut);
		html_tag("			<td><input type=\"button\"  value=\"%s\" onclick=\"return SelectFormulaire(%d,form);\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_executer,
				 FORM_SUADMCONTROL_PASSAGE_CONFIG_DEFAUT);
		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");
//		html_tag("<tr><td><SUP>1)</SUP>%s</td></tr> \n",
//				 pt_tb_msg[u8_html_langue].ps8_msg_sauf_adresse_ip_masque_et_passerelle);
//d: BE065.1 02/05/2012 (CM) - Correction libellé dans page Html Administration - Controle
//		html_tag("<tr><td><SUP>1)</SUP>%s</td></tr> \n",
//				 pt_tb_msg[u8_html_langue].ps8_msg_information_mots_de_passes_par_defaut);
//f: BE065.1 02/05/2012 (CM) - Correction libellé dans page Html Administration - Controle
	}
	
	
	html_tag("</table> \n");
	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUAdmControle*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUAdmControl
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de suadmcontrol
//=====================================================================================
void InitModule_SUAdmControl(void)
{
}/*InitModule_SUAdmControl*/
