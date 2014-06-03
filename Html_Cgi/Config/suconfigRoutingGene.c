/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingGene.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 15/04/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing / General*/
/* Projet          : WRM100                                               */
/* Indice          : BE049                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 15/04/2010 CM
// - CREATION
//BE026 26/04/2010 CM
// - Correction lecture /proc/net/route
//	il faut comptabiliser les routes statiques, dynamiques 
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE049 08/12/2010 CM
// - Ajout affichage des commandes dans la page de Configuration - Routage Ip - Général
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGROUTINGGENE


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGROUTINGGENE
{
	FORM_SUCONFIGROUTINGGENE_NULL = 0,	//à ne pas utiliser
	NB_MAX_FORM_SUCONFIGROUTINGGENE
};

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_ROUTINGGENE_RESULTS;

FIELD_LIST s_FormConfigRoutingGeneFields[] = {
	
	{"hidden1",		"%s",		offsetof(S_FORM_CONFIG_ROUTINGGENE_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingGene
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: code de javascript de la page HTML SUConfigRoutingGene
//=====================================================================================
void proc_JavaScript_SUConfigRoutingGene(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingGene
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: code de javascript de la page HTML SUConfigRoutingGene
//=====================================================================================
void proc_JavaScript_SUConfigRoutingGene(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{ \n");
	html_tag("} \n");

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("		with(document) \n");
	html_tag("		{  \n");
	html_tag("			switch(i_numForm)  \n");
	html_tag("			{  \n");
	html_tag("				default:  \n");
	html_tag("					loc_result = true; \n");
	html_tag("					break;	  \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag( "	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigRoutingGene*/

//=====================================================================================
// Fonction		: SUConfigRoutingGene
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/04/2010
// Description	: Page HTML Configuration: IP Routing 
//				"URL=SUConfigRoutingGene"
//=====================================================================================
void SUConfigRoutingGene(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_ROUTINGGENE_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigRoutingGene");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigRoutingGene&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_ROUTINGGENE_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigRoutingGeneFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGROUTINGGENE)
			{
				if(FALSE == loc_u8_result_test)
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_CONFIG_KO);
					Html_GotoPage(ps8_pageHtmlRetour);
					return;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				PreparePageCfgInProgress("SUConfigRoutingGene");
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
	if( (FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) ||
		(FALSE == u8FillConfigRouting(&s_html_cfg_eqpmt))
	  )
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	//Page accéssible uniquement en mode STATION / router
	if((MODE_RADIO_MODEM_STATION != s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem) ||
	   (MODE_NETWORK_ROUTER != s_html_cfg_eqpmt.s_gene.u8_mode_network)
	  )//CONDITION: STATION / router
	{
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_MODE_ONLY_STATION_ROUTER);
		Html_GotoPage(ps8_pageHtmlRetour);
		return;
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigRoutingGene");	//pour la fonction Actualiser

	JSIPCheck();
	JSNumCheck();

	proc_JavaScript_SUConfigRoutingGene();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigRoutingGene");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigRouting);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//ONGLET
	HtmlPrint_OngletRouting(PAGE_HTML_SUCONFIGROUTING__GENE);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_detail_onglet_SUConfigRoutingGene);

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_routes_actives);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>\n");
	html_tag("<pre>");
	HtmlPrint_TableRoutageActive();
	html_tag("</pre>\n");
	html_tag("</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_routes_politiques_actives);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>\n");
	html_tag("<pre>");
	if(TRUE == u8TestAllRoutePoliticFree(&s_html_cfg_eqpmt)) //CONDITION: Aucune route politique configurée
	{
		html_tag("  <B>%s</B>\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_aucune_route_politique_activee);
	}
	else
	{
		html_tag("---------------------------------------------------------------------------------------------------------\n");
		HtmlPrint_TableRulesMangleActive();
		html_tag("---------------------------------------------------------------------------------------------------------\n");
		HtmlPrint_IpRuleInfo();
		html_tag("---------------------------------------------------------------------------------------------------------\n");
		HtmlPrint_IpRoutePolicyInfo();
		html_tag("---------------------------------------------------------------------------------------------------------\n");
	}
	html_tag("\n");
	html_tag("</pre>\n");
	html_tag("</td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigRoutingGene*/

//=====================================================================================
// Fonction		: HtmlPrint_OngletRouting
// Entrees		: <loc_u8_idx_html> : index page HTML active
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: Code HTML des onglets des pages HTML de routing
//=====================================================================================
void HtmlPrint_OngletRouting(u8sod loc_u8_idx_html)
{
	
	html_tag("<tr><td><table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("	<tr> \n");
	if(PAGE_HTML_SUCONFIGROUTING__GENE == loc_u8_idx_html)	//CONDITION: page identique
	{
		html_tag("	<td><ul><li><B>%s</B></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_routage_general);
	}
	else
	{
		html_tag("	<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=SUConfigRoutingGene\" target=\"frame_c\">%s</a></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_routage_general);
	}
	html_tag("	<td>&nbsp;&nbsp;</td> \n");
	if(PAGE_HTML_SUCONFIGROUTING__STATIC == loc_u8_idx_html)	//CONDITION: page identique
	{
		html_tag("	<td><ul><li><B>%s</B></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_routage_statique);
	}
	else
	{
		html_tag("	<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=SUConfigRoutingStatic\" target=\"frame_c\">%s</a></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_routage_statique);
	}
	html_tag("	<td>&nbsp;&nbsp;</td> \n");
	if(PAGE_HTML_SUCONFIGROUTING__POLITIC == loc_u8_idx_html)	//CONDITION: page identique
	{
		html_tag("	<td><ul><li><B>%s</B></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_politique_routage);
	}
	else
	{
		html_tag("	<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=SUConfigRoutingPolitic&param=%d\" target=\"frame_c\">%s</a></li></ul></td> \n",
				 PARAM_SUCONFIGROUTINGPOLITIC_NULL,
				 pt_tb_msg[u8_html_langue].ps8_msg_politique_routage);
	}
	html_tag("	<td>&nbsp;&nbsp;</td> \n");
	if(PAGE_HTML_SUCONFIGROUTING__RIP == loc_u8_idx_html)	//CONDITION: page identique
	{
		html_tag("	<td><ul><li><B>%s</B></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_routage_rip);
	}
	else
	{
		html_tag("	<td><ul><li><a href=\"/cgi-bin/cgi_fh?URL=SUConfigRoutingRip\" target=\"frame_c\">%s</a></li></ul></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_routage_rip);
	}
	html_tag("	<td>&nbsp;&nbsp;</td> \n");
		
	html_tag("	</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");
		
}/*HtmlPrint_OngletRouting*/

//=====================================================================================
// Fonction		: HtmlPrint_TableRoutageActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: Code HTML de la table de routage active
//=====================================================================================
void HtmlPrint_TableRoutageActive(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	S_STRUCT_IP_ROUTE_STATIC	loc_s_route;	//une route
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_PROCNETROUTE+1];
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	memset(&loc_s_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT

	if(NULL == (loc_p_handle = fopen( FICHIER_PROC_NET_ROUTE, "rt" )))
	{
		html_tag("  <B>%s</B> (%s)\n",
				pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible,
				FICHIER_PROC_NET_ROUTE);
	}
	else
	{
		html_tag("<B>%-20s%-30s%-20s%-20s</B>\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_destination,
				 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau,
				 pt_tb_msg[u8_html_langue].ps8_msg_passerelle,
				 pt_tb_msg[u8_html_langue].ps8_msg_interface);
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_PROCNETROUTE,loc_p_handle);
			if((0 != loc_u16_cpt)&&(NULL != loc_ps8_result_fgets)) //CONDITION: ligne lue et ce n'est pas la première
			{
				if(TRUE == u8ProcNetRoute_DecodeLine(loc_ps8_ligne, &loc_s_route))
				{
					html_tag("%-20s",
							 ps8GetStringIp(loc_s_route.u32_destination_ip));
					html_tag("%-30s",
							 ps8GetStringIp(loc_s_route.u32_destination_mask));
					html_tag("%-20s",
							 ps8GetStringIp(loc_s_route.u32_gateway_ip));
					html_tag("%-20s \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_choix_interfaces_ip[loc_s_route.u8_interface]);
				}
				else
				{
					html_tag("  <B>%s</B>\n",
							 pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible);
					loc_u8_resultat = FALSE;
				}
			}

			loc_u16_cpt ++;


		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < NB_MAX_ROUTES_IP_TOTAL) &&
			   (TRUE == loc_u8_resultat)
			  );

		fclose (loc_p_handle);
	}
	
}/*HtmlPrint_TableRoutageActive*/

//=====================================================================================
// Fonction		: HtmlPrint_TableRulesMangleActive
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 18/04/2010
// Description	: Code HTML de la liste des règles MANGLE actives
//=====================================================================================
void HtmlPrint_TableRulesMangleActive(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_TABLE_MANGLE+1];
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT

	if(NULL == (loc_p_handle = fopen( FICHIER_TABLE_MANGLE_ACTIVE, "rt" )))
	{
		html_tag("  <B>%s</B> (%s)\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible,
				 FICHIER_TABLE_MANGLE_ACTIVE);
	}
	else
	{
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_TABLE_MANGLE,loc_p_handle);
			if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue 
			{
				if((NULL != strstr(loc_ps8_ligne, "Chain"))||
				   (NULL != strstr(loc_ps8_ligne, "target"))||
				   (NULL != strstr(loc_ps8_ligne, "#iptables"))
				  )
				{
					html_tag("<B>%s</B>",loc_ps8_ligne);
				}
				else
				{
					html_tag("%s",loc_ps8_ligne);
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
			}

			loc_u16_cpt ++;

		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < (NB_MAX_POLICY_ROUTING*4)) &&
			   (TRUE == loc_u8_resultat)
			  );
		fclose (loc_p_handle);
	}

}/*HtmlPrint_TableRulesMangleActive*/

//=====================================================================================
// Fonction		: HtmlPrint_IpRuleInfo
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/04/2010
// Description	: Code HTML de la liste des règles Ip
//=====================================================================================
void HtmlPrint_IpRuleInfo(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_FICHIER_IP_RULE_SHOW+1];
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT

	if(NULL == (loc_p_handle = fopen( FICHIER_IP_RULE_SHOW, "rt" )))
	{
		html_tag("  <B>%s</B> (%s)\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible,
				 FICHIER_IP_ROUTE_SHOW);
	}
	else
	{
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_FICHIER_IP_RULE_SHOW,loc_p_handle);
			if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue 
			{
				if(NULL != strstr(loc_ps8_ligne, "#ip rule"))
				{
					html_tag("<B>%s</B>",loc_ps8_ligne);
				}
				else
				{
					html_tag("%s",loc_ps8_ligne);
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
			}

			loc_u16_cpt ++;

		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < (NB_MAX_POLICY_ROUTING*4)) &&
			   (TRUE == loc_u8_resultat)
			  );
		fclose (loc_p_handle);
	}

}/*HtmlPrint_IpRuleInfo*/

//=====================================================================================
// Fonction		: HtmlPrint_IpRoutePolicyInfo
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/04/2010
// Description	: Code HTML de la liste des routes Ip politiques
//=====================================================================================
void HtmlPrint_IpRoutePolicyInfo(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_FICHIER_IP_ROUTE_SHOW+1];
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT

	if(NULL == (loc_p_handle = fopen( FICHIER_IP_ROUTE_SHOW, "rt" )))
	{
		html_tag("  <B>%s</B> (%s)\n",
				 pt_tb_msg[u8_html_langue].ps8_msg_acces_base_donnees_impossible,
				 FICHIER_IP_ROUTE_SHOW);
	}
	else
	{
		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_FICHIER_IP_ROUTE_SHOW,loc_p_handle);
			if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue 
			{
				if(NULL != strstr(loc_ps8_ligne, "ip route show table"))
				{
					html_tag("<B>%s</B>",loc_ps8_ligne);
				}
				else
				{
					html_tag("%s",loc_ps8_ligne);
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
			}

			loc_u16_cpt ++;

		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < (NB_MAX_POLICY_ROUTING*4)) &&
			   (TRUE == loc_u8_resultat)
			  );
		fclose (loc_p_handle);
	}

}/*HtmlPrint_IpRoutePolicyInfo*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingGene
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingGene
//=====================================================================================
void InitModule_SUConfigRoutingGene(void)
{
}/*InitModule_SUConfigRoutingGene*/
