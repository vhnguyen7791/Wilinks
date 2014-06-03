/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingStatic.c							  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 16/10/2009                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing / Static */
/* Projet          : WRM100                                               */
/* Indice          : BE048                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE006 20/01/2010 CM
// - Correction page HTML Configuration - Routage
//	ne pas autoriser l'ajout d'une route lorsque la table est pleine
//BE007 25/01/2010 CM
// - Modification gestion routage statique
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Modification gestion routage par le processus bird
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE048 29/11/2010 CM
// - Correction routage statique vers un HOST
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGROUTINGSTATIC


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGROUTINGSTATIC
{
	FORM_SUCONFIGROUTINGSTATIC_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGROUTINGSTATIC_AJOUTER,
	FORM_SUCONFIGROUTINGSTATIC_EFFACER,
	FORM_SUCONFIGROUTINGSTATIC_DELETE_MIN,
	FORM_SUCONFIGROUTINGSTATIC_DELETE_MAX = (FORM_SUCONFIGROUTINGSTATIC_DELETE_MIN + NB_MAX_ROUTES_IP_STATIC),
	NB_MAX_FORM_SUCONFIGROUTINGSTATIC
};

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_adrIp		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_maskIp		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_adrGw		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_interface	[10 + 1];
	
	s8sod	ps8_hidden1			[10 + 1];
} S_FORM_CONFIG_ROUTINGSTATIC_RESULTS;

FIELD_LIST s_FormConfigRoutingStaticFields[] = {
	{"adrIp",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGSTATIC_RESULTS, ps8_adrIp)		},
	{"maskIp",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGSTATIC_RESULTS, ps8_maskIp)		},
	{"adrGw",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGSTATIC_RESULTS, ps8_adrGw)		},
	{"interf",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGSTATIC_RESULTS, ps8_interface)	},
	
	{"hidden1",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGSTATIC_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingStatic
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigRoutingStatic
//=====================================================================================
void proc_JavaScript_SUConfigRoutingStatic(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingStatic
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009
// Description	: code de javascript de la page HTML SUConfigRoutingStatic
//=====================================================================================
void proc_JavaScript_SUConfigRoutingStatic(void)
{

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	html_tag("		JSChangeInterface(); \n");
	html_tag("	}  \n");
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
	html_tag("				case %d: \n",
			 FORM_SUCONFIGROUTINGSTATIC_AJOUTER);
	html_tag("					if((false == validAddr(form.adrIp, true))|| \n");
	html_tag("					   (false == validMask(form.maskIp, false)) \n");
	html_tag("					  ) \n");
	html_tag("					{  \n");
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("					if(%d == Number(form.interf.value))  \n",INTERFACE_AUTOMATIQUE);
	html_tag("					{  \n");
	html_tag("					   if(false == validAddr(form.adrGw, true)) \n");
	html_tag("						{  \n");
	html_tag("							loc_result = false;  \n");
	html_tag("						}  \n");
	html_tag("					}  \n");
	html_tag("					if(true == loc_result) \n"); //CONDITION: tests préliminaires réussis
	html_tag("					{\n");
	html_tag("						var loc_ip_adr_dest = IPAddressToUnsignedInteger(form.adrIp.value); \n");
	html_tag("						var loc_subnet_mask = IPAddressToUnsignedInteger(form.maskIp.value); \n");
	html_tag("						var loc_host_mask = (~loc_subnet_mask) & 0xffffffff; \n");
	html_tag("						if(0xffffffff != loc_subnet_mask) \n"); //CONDITION: route vers un sous réseau valide
	html_tag("						{\n");
	html_tag("							if ((loc_ip_adr_dest & loc_host_mask) != 0) \n"); //CONDITION: route vers sous-réseau invalide
	html_tag("							{\n");
	html_tag("								alert(\"%s\"); \n",
			pt_tb_msg[u8_html_langue].ps8_msg_route_vers_sous_reseau_invalide);
	html_tag("								loc_result = false; \n");
	html_tag("							} \n");
	html_tag("						}\n");
	html_tag("					}\n");
	html_tag("					break;  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGROUTINGSTATIC_EFFACER);
	html_tag("					form.adrIp.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("					form.maskIp.value = \"%s\";  \n",ps8GetStringIp(MASK_RESEAU_SUR_24));
	html_tag("					form.adrGw.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("					form.interf.value = %d;  \n",INTERFACE_AUTOMATIQUE);
	html_tag("					loc_result = false;  \n");
	html_tag("					break;  \n");
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

	//Fonction javascript : JSChangeInterface
	//*************************************
	html_tag("function JSChangeInterface() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if(%d == Number(form.interf.value)) \n",INTERFACE_AUTOMATIQUE);
	html_tag("		{ \n");
	html_tag("			form.adrGw.disabled = false;  \n");
	html_tag("		} \n");
	html_tag("		else \n"); //CONDITION: interface sélectionné
	html_tag("		{ \n");
	html_tag("			form.adrGw.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("			form.adrGw.disabled = true;  \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeInterface*/
	
	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigRoutingStatic*/

//=====================================================================================
// Fonction		: SUConfigRoutingStatic
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 16/10/2009
// Description	: Page HTML Configuration: IP Routing 
//				"URL=SUConfigRoutingStatic"
//=====================================================================================
void SUConfigRoutingStatic(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_ROUTINGSTATIC_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_i;
	u16sod	loc_u16_i;
	u16sod	loc_u16_route_a_supprimer;
	S_STRUCT_IP_ROUTE_STATIC	loc_s_route;	//une route
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;			/* Init loc */

	loc_u8_result_test = FALSE; //INIT
	memset(&loc_s_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigRoutingStatic");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigRoutingStatic&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_ROUTINGSTATIC_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigRoutingStaticFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGROUTINGSTATIC)
			{
				if(FORM_SUCONFIGROUTINGSTATIC_AJOUTER == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigRouting(&s_html_cfg_eqpmt))
					{
						loc_s_route.u32_destination_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrIp, &loc_u8_ret);
						loc_s_route.u32_destination_mask = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_maskIp, &loc_u8_ret);
						loc_s_route.u8_interface = (u8sod)atoi(loc_s_results.ps8_interface);
						if(INTERFACE_AUTOMATIQUE == loc_s_route.u8_interface)
						{
							loc_s_route.u32_gateway_ip = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_adrGw, &loc_u8_ret);
						}
						else
						{
							loc_s_route.u32_gateway_ip = ADRESSE_IP_NULLE;
						}
						if(TRUE == u8AddRouteStatic(&s_html_cfg_eqpmt, &loc_s_route))
						{
							if(TRUE==u8TestConfigRouting(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigRouting(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if((FORM_SUCONFIGROUTINGSTATIC_DELETE_MIN <= loc_u8_numForm)&&
				   (loc_u8_numForm <= FORM_SUCONFIGROUTINGSTATIC_DELETE_MAX)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigRouting(&s_html_cfg_eqpmt))
					{
						loc_u16_route_a_supprimer = (u16sod)loc_u8_numForm - FORM_SUCONFIGROUTINGSTATIC_DELETE_MIN;
						if(loc_u16_route_a_supprimer < NB_MAX_ROUTES_IP_STATIC)
						{
							s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_route_a_supprimer].u8_enabled = FALSE; //RAZ
							s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_route_a_supprimer].u8_interface = INTERFACE_AUTOMATIQUE; //RAZ
							s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_route_a_supprimer].u32_destination_ip = ADRESSE_IP_NULLE; //RAZ
							s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_route_a_supprimer].u32_destination_mask = MASK_RESEAU_SUR_24; //RAZ
							s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_route_a_supprimer].u32_gateway_ip = ADRESSE_IP_NULLE; //RAZ
							if(TRUE==u8TestConfigRouting(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigRouting(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
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
				PreparePageCfgInProgress("SUConfigRoutingStatic");
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

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigRoutingStatic");	//pour la fonction Actualiser

	JSIPCheck();
	JSNumCheck();

	proc_JavaScript_SUConfigRoutingStatic();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigRoutingStatic");//permet d'avoir la bonne page de rafraichit!!
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
	HtmlPrint_OngletRouting(PAGE_HTML_SUCONFIGROUTING__STATIC);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_detail_onglet_SUConfigRoutingStatic);
	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_table_routage_ip_statique);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_destination);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_passerelle);
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_interface);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_action);
	html_tag("		</tr> \n");
	for(loc_u16_i=0;loc_u16_i<NB_MAX_ROUTES_IP_STATIC;loc_u16_i++)
	{
		if(TRUE == s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
		{
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 ps8GetStringIp(s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_ip));
			html_tag("			<td>%s</td> \n",
					 ps8GetStringIp(s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_mask));
			html_tag("			<td>%s</td> \n",
					 ps8GetStringIp(s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_i].u32_gateway_ip));
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_interfaces_ip[s_html_cfg_eqpmt.s_ip_routing.ps_route_ip_static[loc_u16_i].u8_interface]);
			html_tag("			<td>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_supprimer,
					 (FORM_SUCONFIGROUTINGSTATIC_DELETE_MIN+loc_u16_i));
			html_tag("		</tr> \n");
		}
	}
	html_tag("</table></td></tr> \n");

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_ajouter_route);
	if(FALSE == u8TestRouteStaticFree(&s_html_cfg_eqpmt))
	{
		html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_attention,
				 pt_tb_msg[u8_html_langue].ps8_msg_table_routage_statique_complete);
	}
	else
	{
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_destination);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_masque_sous_reseau);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_passerelle);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_interface);
		html_tag("		</tr> \n");
		html_tag("		<tr> \n");
		//Destination
		html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrIp\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
				ps8GetStringIp(ADRESSE_IP_NULLE));
		//Masque de sous-reseau
		html_tag("			<td><input type=\"text\" size=\"15\" name=\"maskIp\" value=\"%s\" width=\"15\" onchange=\"return(validMask(this, false))\"></td> \n",
				 ps8GetStringIp(MASK_RESEAU_SUR_24));
		//Passerelle
		html_tag("			<td><input type=\"text\" size=\"15\" name=\"adrGw\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
				ps8GetStringIp(ADRESSE_IP_NULLE));
		//Interface
		html_tag("			<td><SELECT name=\"interf\" size=\"1\" onchange=\"return(JSChangeInterface())\"> \n");
		for(loc_u8_i=0;loc_u8_i<NB_MAX_INTERFACES;loc_u8_i++)
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((INTERFACE_AUTOMATIQUE == loc_u8_i) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_interfaces_ip[loc_u8_i]);
		}
		html_tag("				  </select></td> \n");

		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"> \n",
				pt_tb_msg[u8_html_langue].ps8_msg_ajouter,
				FORM_SUCONFIGROUTINGSTATIC_AJOUTER);
		html_tag("&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_effacer,
				FORM_SUCONFIGROUTINGSTATIC_EFFACER);
	}

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigRoutingStatic*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingStatic
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingStatic
//=====================================================================================
void InitModule_SUConfigRoutingStatic(void)
{
}/*InitModule_SUConfigRoutingStatic*/
