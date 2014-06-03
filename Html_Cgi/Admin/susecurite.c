/*========================================================================*/
/* NOM DU FICHIER  : susecurite.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML sécurité						  */
/* Projet          : WRM100                                               */
/* Indice          : BE024                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Correction problème accès au serveur HTTP (dernière un serveur NAT, avec port forwarding)
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _SUSECURITE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include <ctype.h>
#include "../services.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

// Structure Résultat pour le changement du Password
typedef struct {
	s8sod	ps8_ind[6];
	s8sod	ps8_OldPassword		[LG_NOM_PWD + 1];		
	s8sod	ps8_NewPassword		[LG_NOM_PWD + 1];		
	s8sod	ps8_ConfirmPassword	[LG_NOM_PWD + 1];	
	s8sod	ps8_TimeMax			[5 + 1];
	s8sod	ps8_ClientMax		[5 + 1];
	s8sod	ps8_SecureSET		[5 + 1];
	
} S_STRUCT_SECURITE_RESULTS;


FIELD_LIST s_SecuriteFields[] = {
	// Change Passwords
	{"ind",			"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_ind)			},
	{"oldpwd",		"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_OldPassword)	},
	{"newpwd",		"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_NewPassword)	},
	{"confpwd",		"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_ConfirmPassword)},
	
	// Change Time Max
	{"timemax",		"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_TimeMax)	},
	
	// Change Client Max
	{"clientmax",	"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_ClientMax)	},
	
	//Sécurisation SNMP
	{"secureSET",	"%s",	offsetof(S_STRUCT_SECURITE_RESULTS, ps8_SecureSET)	},
	{NULL	}
	
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: SUAdmSecurite
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: Page permet de configurer les paramètres de sécurité des serveurs HTTP,SNMP,FTP
//=====================================================================================
void SUAdmSecurite(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_STRUCT_SECURITE_RESULTS loc_s_results;
	s32sod	loc_s32_sem;
	s8sod	loc_ps8_emsg[50];
	u16sod	loc_u16_NumeroForm, loc_u16_i;
	u8sod	loc_u8_result_test;

	loc_u8_result_test = FALSE; //INIT
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), HIGH_LEVEL_ACCESS))
	{
		PreparePagePswd("SUAdmSecurite");
		return;  
	}
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_STRUCT_SECURITE_RESULTS));
		
		// Décodage de la requête
		if (!form_decode(s_SecuriteFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
			//on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
			if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
			{
				;
			}
			s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
			
			loc_u16_NumeroForm = (u16sod)atoi(loc_s_results.ps8_ind);
			// Change Passwords
			if(1 == loc_u16_NumeroForm)
			{
				// Test du mot de passe
				if(		strcmp(loc_s_results.ps8_OldPassword, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_low) 
				   &&	strcmp(loc_s_results.ps8_OldPassword, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_middle)
				   &&	strcmp(loc_s_results.ps8_OldPassword, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_high)
				  )//CONDITION : mot de passe saisie KO 
				{
					html_tag("<HTML><HEAD>\n");	
					html_tag("<SCRIPT language=\"javascript\">\n");
					html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_mauvais_mot_passe);
					html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
					html_tag("</SCRIPT>\n");
					html_tag("</HEAD></HTML>"); 
					return ;
				}	
				// Compatibilité NewPassword et ConfirmPassword
				if(strcmp(loc_s_results.ps8_NewPassword, loc_s_results.ps8_ConfirmPassword)) 
				{
					html_tag("<HTML><HEAD>\n");	
					html_tag("<SCRIPT language=\"javascript\">\n");
					html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_confirmation_differents);
					html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
					html_tag("</SCRIPT>\n");
					html_tag("</HEAD></HTML>"); 
					return;
				}
				
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
				{
					// Modification du Password selon le Niveau d'Accès
					if (!strcmp(loc_s_results.ps8_OldPassword, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_low))
					{
						strcpy(s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_low, loc_s_results.ps8_NewPassword);
					}
					else if(!strcmp(loc_s_results.ps8_OldPassword,s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_middle))
					{
						strcpy(s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_middle, loc_s_results.ps8_NewPassword);
					}
					else if(!strcmp(loc_s_results.ps8_OldPassword, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_high))
					{
						strcpy(s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_high, loc_s_results.ps8_NewPassword);
					}
					if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
					{
						if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
						{
							loc_u8_result_test = TRUE;
						}
					}
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
			}
			
			// Change Time Max
			if(2 == loc_u16_NumeroForm)
			{
				for(loc_u16_i=0; loc_s_results.ps8_TimeMax[loc_u16_i]!='\0'; loc_u16_i++)
				{
					if(!isdigit(loc_s_results.ps8_TimeMax[loc_u16_i]) )
					{	
						html_tag("<HTML><HEAD>\n");	
						html_tag("<SCRIPT language=\"javascript\">\n");
						html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_duree_invalide);
						html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
						html_tag("</SCRIPT>\n");
						html_tag("</HEAD></HTML>"); 
						return;
					}
				}
				
				if(0 == atoi(loc_s_results.ps8_TimeMax))
				{	
					html_tag("<HTML><HEAD>\n");	
					html_tag("<SCRIPT language=\"javascript\">\n");
					html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_duree_invalide);
					html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
					html_tag("</SCRIPT>\n");
					html_tag("</HEAD></HTML>"); 
					return;
				}
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
				{
					s_html_cfg_eqpmt.s_admin.u16_duree_inactivite_http = (u16sod)(atoi(loc_s_results.ps8_TimeMax));//on stocke en secondes
					if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
					{
						if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
						{
							loc_u8_result_test = TRUE;
						}
					}
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
			}
			
			// Change Client Max
			if(3 == loc_u16_NumeroForm)
			{
				for(loc_u16_i=0; loc_s_results.ps8_ClientMax[loc_u16_i]!='\0'; loc_u16_i++)
				{
					if(!isdigit(loc_s_results.ps8_ClientMax[loc_u16_i]))
					{
						html_tag("<HTML><HEAD>\n");	
						html_tag("<SCRIPT language=\"javascript\">\n");
						html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_nombre_invalide);
						html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
						html_tag("</SCRIPT>\n");
						html_tag("</HEAD></HTML>"); 
						return;
					}
				}
				if(0 == atoi(loc_s_results.ps8_ClientMax))
				{
					html_tag("<HTML><HEAD>\n");	
					html_tag("<SCRIPT language=\"javascript\">\n");
					html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_nombre_invalide);
					html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
					html_tag("</SCRIPT>\n");
					html_tag("</HEAD></HTML>"); 
					return;
				}
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
				{
					s_html_cfg_eqpmt.s_admin.u8_max_client_ip = (u8sod)atoi(loc_s_results.ps8_ClientMax);
					if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
					{
						if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
						{
							loc_u8_result_test = TRUE;
						}
					}
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
			}
			
			// Change Securite SNMP
			if(4 == loc_u16_NumeroForm)
			{
				for(loc_u16_i=0; loc_s_results.ps8_SecureSET[loc_u16_i]!='\0'; loc_u16_i++)
				{
					if(!isdigit(loc_s_results.ps8_SecureSET[loc_u16_i]))
					{
						html_tag("<HTML><HEAD>\n");	
						html_tag("<SCRIPT language=\"javascript\">\n");
						html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_nombre_invalide);
						html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=SUAdmSecurite\");");
						html_tag("</SCRIPT>\n");
						html_tag("</HEAD></HTML>"); 
						return;
					}
				}
				
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
				{
					s_html_cfg_eqpmt.s_admin.u8_securisation_snmp = (u8sod)atoi(loc_s_results.ps8_SecureSET);
					if(TRUE==u8TestConfigAdmin(&s_html_cfg_eqpmt))
					{
						if(TRUE == u8EditConfigAdmin(&s_html_cfg_eqpmt))
						{
							loc_u8_result_test = TRUE;
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
			Html_GotoPage("/cgi-bin/cgi_fh?URL=SUAdmSecurite");
			return; // on sort!
		}						
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_securite);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");
	
	
	JSActualiser("/cgi-bin/cgi_fh?URL=SUAdmSecurite");	//pour la fonction Actualiser
	JSNumCheck();
	JSTextCheck();
	
	html_tag("<BODY> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_securite);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_adm_securite);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();



	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_modification_mot_passe);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmSecurite");
	form_hidden("ind","1");
	html_tag("\n");
	
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("	<tr> \n");
	html_tag("	  <th width=\"200\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("	  <th width=\"100\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("	</tr> \n");
	//ancien Mot de passe
	html_tag("	<tr> \n");
	html_tag("	  <td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_ancien_mot_passe);
	html_tag("	  <td><p><input type=\"password\" size=\"12\" maxlength=\"12\" name=\"oldpwd\" onchange=\"return(isValidText(this,false,true))\"></p></td> \n");
	html_tag("	</tr>\n");
	//Nouveau Mot de passe
	html_tag("	<tr> \n");
	html_tag("	  <td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_nouveau_mot_passe);
	html_tag("	  <td><p><input type=\"password\" size=\"12\" maxlength=\"12\" name=\"newpwd\" onchange=\"return(isValidText(this,false,true))\"></p></td> \n");
	html_tag("	</tr>\n");
	//Confirmer Nouveau Mot de passe
	html_tag("	<tr> \n");
	html_tag("	  <td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_confirmer_mot_passe);
	html_tag("	  <td><p><input type=\"password\" size=\"12\" maxlength=\"12\" name=\"confpwd\" onchange=\"return(isValidText(this,false,true))\"></p></td> \n");
	html_tag("	</tr>\n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"submit\" value=\"%s\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider_mot_de_passe);
	html_tag("</FORM>");
	
	
	//FORM :Durée maximum de connexion sans activité HTTP
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form2\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmSecurite");
	form_hidden("ind","2");
	html_tag("\n");
	
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_duree_max_connexion);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"100\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Durée
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_duree);
	html_tag("			<td><input type=\"text\" size=\"4\" maxlength=\"4\" name=\"timemax\" value=\"%d\" \n",
			 (s_html_cfg_eqpmt.s_admin.u16_duree_inactivite_http));
	html_tag("			onchange=\"return(isInteger(this,%d,%d))\">%s</td> \n",
			 DUREE_INACTIVITE_HTTP_MIN,
			 DUREE_INACTIVITE_HTTP_MAX,
			 pt_tb_msg[u8_html_langue].ps8_msg_minutes);
	html_tag("		</tr>\n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"submit\" value=\"%s\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider);
	html_tag("</FORM>");
	
	//FORM :Nombre Maximum de clients
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form3\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmSecurite");
	form_hidden("ind","3");
	html_tag("\n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_nombre_max_clients);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"100\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	//Nombre max clients
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_nombre_max_clients);
	html_tag("			<td><input type=\"text\" size=\"3\" maxlength=\"3\" name=\"clientmax\" value=\"%d\" \n",
			 s_html_cfg_eqpmt.s_admin.u8_max_client_ip);
	html_tag("			onchange=\"return(isInteger(this,%d,%d))\"></td> \n",
			 NB_CLIENT_IP_MIN,
			 NB_CLIENT_IP_MAX);
	html_tag("		</tr>\n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"submit\" value=\"%s\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider);
	html_tag("</FORM>");
	
#if VERSION_WRM100_DEMO
#else
	//FORM :Sécurisation du serveur SNMP
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form4\" target=\"frame_c\"> \n");
	form_hidden("URL","SUAdmSecurite");
	form_hidden("ind","4");
	html_tag("\n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_securisation_snmp);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P>%s<BR>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_securisation_snmp1,
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_securisation_snmp2);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"200\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"100\" >%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	
	html_tag("		<tr> \n");
	html_tag("			<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration_securise_SET);
	html_tag("			<td><SELECT name=secureSET> \n");
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((MODE_SECURISATION_SNMP_INACTIF == s_html_cfg_eqpmt.s_admin.u8_securisation_snmp) ? "selected" : ""),
			 MODE_SECURISATION_SNMP_INACTIF,
			 pt_tb_msg[u8_html_langue].ps8_msg_non);
	html_tag("			<option %s value=\"%d\">%s</option> \n",
			 ((MODE_SECURISATION_SNMP_SET == s_html_cfg_eqpmt.s_admin.u8_securisation_snmp) ? "selected" : ""),
			 MODE_SECURISATION_SNMP_SET,
			 pt_tb_msg[u8_html_langue].ps8_msg_oui);
	html_tag("			 </select></td> \n");
	html_tag("		</tr>\n");
	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><input type=\"submit\" value=\"%s\"></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valider);
	html_tag("</FORM>");
#endif
	
	html_tag("</table> \n");
	
	// Curseur dans le premier champ
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("document.forms[0].elements[2].focus();");
	html_tag("</SCRIPT>\n");
	
	// Return the completed HTML document
	html_tag("</BODY> \n");
	html_tag("</HTML> \n"); 
	
}/*SUAdmSecurite*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUSecurite
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de susecurite
//=====================================================================================
void InitModule_SUSecurite(void)
{
}/*InitModule_SUSecurite*/
