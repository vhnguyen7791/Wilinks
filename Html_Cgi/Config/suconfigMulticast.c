/*========================================================================*/
/* NOM DU FICHIER  : suconfigMulticast.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 30/03/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Multicast		  */
/* Projet          : WRM100                                               */
/* Indice          : BE047                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE022 30/03/2010 CM
// - CREATION
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGMULTICAST


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGMULTICAST
{
	FORM_SUCONFIGMULTICAST_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGMULTICAST_VALID_1,
	FORM_SUCONFIGMULTICAST_SRC_AJOUTER,
	FORM_SUCONFIGMULTICAST_SRC_EFFACER,
	FORM_SUCONFIGMULTICAST_SRC_DELETE_MIN,
	FORM_SUCONFIGMULTICAST_SRC_DELETE_MAX = (FORM_SUCONFIGMULTICAST_SRC_DELETE_MIN + NB_MAX_SRC_MULTICAST),
	NB_MAX_FORM_SUCONFIGMULTICAST
};

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_igmp_proxy_enable	[10 + 1];

	//Source multicast
	s8sod	ps8_src_adr		[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_src_mask	[MAX_LG_FORMAT_ADRESSE_IP + 1];

	s8sod	ps8_hidden1			[10 + 1];
}S_FORM_CONFIG_MULTICAST_RESULTS;

FIELD_LIST s_FormConfigMulticastFields[] = {
	{"igmpEnable",	"%s",	offsetof(S_FORM_CONFIG_MULTICAST_RESULTS, ps8_igmp_proxy_enable)	},

	//Source multicast
	{"srcAddr",	"%s",	offsetof(S_FORM_CONFIG_MULTICAST_RESULTS, ps8_src_adr)	},
	{"srcMask",	"%s",	offsetof(S_FORM_CONFIG_MULTICAST_RESULTS, ps8_src_mask)	},
	
	{"hidden1",		"%s",	offsetof(S_FORM_CONFIG_MULTICAST_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigMulticast
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/03/2010
// Description	: code de javascript de la page HTML SUConfigMulticast
//=====================================================================================
void proc_JavaScript_SUConfigMulticast(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigMulticast
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/03/2010
// Description	: code de javascript de la page HTML SUConfigMulticast
//=====================================================================================
void proc_JavaScript_SUConfigMulticast(void)
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
	html_tag("				case %d: \n",
			 FORM_SUCONFIGMULTICAST_SRC_AJOUTER);
	html_tag("					if((false == validAddr(form.srcAddr, true))|| \n");
	html_tag("					   (false == validMask(form.srcMask, false)) \n");
	html_tag("					  ) \n");
	html_tag("					{  \n");
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("					if(true == loc_result) \n"); //CONDITION: tests préliminaires réussis
	html_tag("					{\n");
	html_tag("						var loc_ip_adr_dest = IPAddressToUnsignedInteger(form.srcAddr.value); \n");
	html_tag("						var loc_subnet_mask = IPAddressToUnsignedInteger(form.srcMask.value); \n");
	html_tag("						var loc_host_mask = (~loc_subnet_mask) & 0xffffffff; \n");
	html_tag("						if(0xffffffff == loc_subnet_mask) \n"); //CONDITION: masque à 255.255.255.255 (donc source vers un host)
	html_tag("						{\n");
	html_tag("							alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_source_invalide);
	html_tag("						}\n");
	html_tag("						else\n");//CONDITION: source vers un sous réseau valide
	html_tag("						{\n");
	html_tag("							if ((loc_ip_adr_dest & loc_host_mask) != 0) \n"); //CONDITION: source vers sous-réseau invalide
	html_tag("							{\n");
	html_tag("								alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_source_invalide);
	html_tag("								loc_result = false; \n");
	html_tag("							} \n");
	html_tag("						}\n");
	html_tag("					}\n");
	html_tag("					break;  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGMULTICAST_SRC_EFFACER);
	html_tag("					form.srcAddr.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("					form.srcMask.value = \"%s\";  \n",ps8GetStringIp(MASK_RESEAU_SUR_24));
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

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigMulticast*/


//=====================================================================================
// Fonction		: SUConfigMulticast
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 30/03/2010
// Description	: Page HTML Configuration: Multicast
//				"URL=SUConfigMulticast"
//=====================================================================================
void SUConfigMulticast(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_MULTICAST_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u16sod	loc_u16_numForm;
	u16sod	loc_u16_i;
	u16sod	loc_u16_idx_src_to_delete;
	S_STRUCT_SRC_MULTICAST loc_s_src_multicast;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;

	loc_u8_result_test = FALSE; //INIT
	loc_u16_idx_src_to_delete = 0;	//INIT
	memset(&loc_s_src_multicast, 0, sizeof(S_STRUCT_SRC_MULTICAST)); //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		PreparePagePswd("SUConfigMulticast");
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //URL=SUConfigMulticast&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_MULTICAST_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigMulticastFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u16_numForm =  (u16sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u16_numForm < NB_MAX_FORM_SUCONFIGMULTICAST)
			{
				if(FORM_SUCONFIGMULTICAST_VALID_1 == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigMulticast(&s_html_cfg_eqpmt))
					{
						s_html_cfg_eqpmt.s_multicast.u8_proxy_igmp_activation = (u8sod)atoi(loc_s_results.ps8_igmp_proxy_enable);
						if(TRUE==u8TestConfigMulticast(&s_html_cfg_eqpmt))
						{
							if(TRUE == u8EditConfigMulticast(&s_html_cfg_eqpmt))
							{
								loc_u8_result_test = TRUE;
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FORM_SUCONFIGMULTICAST_SRC_AJOUTER == loc_u16_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigMulticast(&s_html_cfg_eqpmt))
					{
						loc_s_src_multicast.u32_adresse_reseau = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_src_adr, &loc_u8_ret);
						loc_s_src_multicast.u32_masque_reseau = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_src_mask, &loc_u8_ret);
						loc_s_src_multicast.u8_enable = TRUE;
						if(TRUE == u8AddSrcMulticastFree(&s_html_cfg_eqpmt, &loc_s_src_multicast))
						{
							if(TRUE==u8TestConfigMulticast(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigMulticast(&s_html_cfg_eqpmt))
								{
									loc_u8_result_test = TRUE;
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if((FORM_SUCONFIGMULTICAST_SRC_DELETE_MIN <= loc_u16_numForm)&&
				   (loc_u16_numForm <= FORM_SUCONFIGMULTICAST_SRC_DELETE_MAX)
				  )
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigMulticast(&s_html_cfg_eqpmt))
					{
						loc_u16_idx_src_to_delete = loc_u16_numForm - FORM_SUCONFIGMULTICAST_SRC_DELETE_MIN;
						if(loc_u16_idx_src_to_delete < NB_MAX_SRC_MULTICAST)
						{
							s_html_cfg_eqpmt.s_multicast.ps_source_multicast[loc_u16_idx_src_to_delete].u8_enable = FALSE; //RAZ
							s_html_cfg_eqpmt.s_multicast.ps_source_multicast[loc_u16_idx_src_to_delete].u32_adresse_reseau = ADRESSE_IP_NULLE; //RAZ
							s_html_cfg_eqpmt.s_multicast.ps_source_multicast[loc_u16_idx_src_to_delete].u32_masque_reseau = MASK_RESEAU_SUR_24; //RAZ
							if(TRUE==u8TestConfigMulticast(&s_html_cfg_eqpmt))
							{
								if(TRUE == u8EditConfigMulticast(&s_html_cfg_eqpmt))
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
				PreparePageCfgInProgress("SUConfigMulticast");
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
		(FALSE == u8FillConfigMulticast(&s_html_cfg_eqpmt))
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
			 pt_tb_msg[u8_html_langue].ps8_msg_Multicast);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=SUConfigMulticast");	//pour la fonction Actualiser

	JSIPCheck();

	proc_JavaScript_SUConfigMulticast();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigMulticast");//permet d'avoir la bonne page de rafraichit!!
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_Multicast);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigMulticast);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Activation proxy IGMP
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_activation_proxy_igmp);
	html_tag("			<td><SELECT name=igmpEnable> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((FALSE == s_html_cfg_eqpmt.s_multicast.u8_proxy_igmp_activation) ? "selected" : ""),
			 FALSE,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((TRUE == s_html_cfg_eqpmt.s_multicast.u8_proxy_igmp_activation) ? "selected" : ""),
			 TRUE,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("				  </select></td> \n");
	html_tag("		</tr> \n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d,form)\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider,
			 FORM_SUCONFIGMULTICAST_VALID_1);

	if(TRUE == s_html_cfg_eqpmt.s_multicast.u8_proxy_igmp_activation)
	{
		//**********************************************
		//**** TABLE SOURCES MULTICAST AUTORISEES  *****
		//**********************************************
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_table_sources_multicast_autorisees);
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th nowrap width=\"100\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_adresse_reseau);
		html_tag("			<th nowrap width=\"100\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_masque_reseau);
		html_tag("			<th nowrap width=\"100\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_action);
		html_tag("		</tr> \n");
		for(loc_u16_i=0;loc_u16_i<NB_MAX_SRC_MULTICAST;loc_u16_i++)
		{
			if(TRUE == s_html_cfg_eqpmt.s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
			{
				html_tag("		<tr> \n");
				//Adresse de réseau
				html_tag("			<td>%s</td> \n",
						 ps8GetStringIp(s_html_cfg_eqpmt.s_multicast.ps_source_multicast[loc_u16_i].u32_adresse_reseau));
				//Masque de réseau
				html_tag("			<td>%s</td> \n",
						 ps8GetStringIp(s_html_cfg_eqpmt.s_multicast.ps_source_multicast[loc_u16_i].u32_masque_reseau));
				//Action
				html_tag("			<td nowrap>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_supprimer,
						 (FORM_SUCONFIGMULTICAST_SRC_DELETE_MIN+loc_u16_i));
				html_tag("		</tr> \n");
			}
		}
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_ajouter_source_multicast_autorisee);
		if(FALSE == u8TestSrcMulticastFree(&s_html_cfg_eqpmt))
		{
			html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_attention,
					 pt_tb_msg[u8_html_langue].ps8_msg_table_source_multicast_complete);
		}
		else
		{
			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
			html_tag("		<tr> \n");
			html_tag("			<th nowrap width=\"100\">%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_adresse_reseau);
			html_tag("			<th nowrap width=\"100\">%s</th> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_masque_reseau);
			html_tag("		<tr> \n");
			//Adresse de réseau
			html_tag("			<td><input type=\"text\" size=\"15\" name=\"srcAddr\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"></td> \n",
					ps8GetStringIp(ADRESSE_IP_NULLE));
			//Masque de réseau
			html_tag("			<td><input type=\"text\" size=\"15\" name=\"srcMask\" value=\"%s\" width=\"15\" onchange=\"return(validMask(this, false))\"></td> \n",
					 ps8GetStringIp(MASK_RESEAU_SUR_24));
			html_tag("		</tr> \n");
			html_tag("</table></td></tr> \n");

			html_tag("<tr><td>&nbsp;</td></tr> \n");
			html_tag("<tr><td>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\" > \n",
					pt_tb_msg[u8_html_langue].ps8_msg_ajouter,
					FORM_SUCONFIGMULTICAST_SRC_AJOUTER);
			html_tag("&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_effacer,
					FORM_SUCONFIGMULTICAST_SRC_EFFACER);
		}
	}/*if(TRUE == s_html_cfg_eqpmt.s_multicast.u8_proxy_igmp_activation)*/

	
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigMulticast*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigMulticast
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/03/2010
// Description	: Initialisation du module de SUConfigMulticast
//=====================================================================================
void InitModule_SUConfigMulticast(void)
{
}/*InitModule_SUConfigMulticast*/
