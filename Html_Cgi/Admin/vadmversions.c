/*========================================================================*/
/* NOM DU FICHIER  : vadmversions.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML administration - Versions		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VADMVERSIONS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: VAdmVersionsLogicielles
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: rien
// Auteur		: 
// Description	: Page HTML: Administration: Versions Logicielles
//=====================================================================================
void VAdmVersionsLogicielles(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s32sod	loc_s32_sem;
	u8sod	loc_u8_type_equipement;
	u8sod	loc_u8_i;
	
	loc_u8_type_equipement = EQUIPEMENT_INCONNU; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		PreparePagePswd("Adm_Versions");
		return;  
	}
	
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
		

	html_tag("<html> \n");
	// Header
	html_tag("<head> \n");
#if AFFICHAGE_HTML_VERSIONS_LOGICIELLES_ONLY
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles);
#else
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles_et_options);
#endif
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");
	html_tag("<body> \n");
	
	JSActualiser("/cgi-bin/cgi_fh?URL=Adm_Versions");	//pour la fonction Actualiser
	
	
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
#if AFFICHAGE_HTML_VERSIONS_LOGICIELLES_ONLY
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_versions_logicielles);
#else
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_administration,
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles_et_options);
	html_tag("<tr><td><P>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_versions_logicielles_et_options);
#endif
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//NOM EQUIPEMENT : Versions logicielles
	html_tag("<tr><td><P class=undermenu>%s: %s</P></td></tr> \n",
			 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue],
			 pt_tb_msg[u8_html_langue].ps8_msg_versions_logicielles);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");

	//Version Logicielle
	for(loc_u8_i=0;loc_u8_i<NB_MAX_VERSIONS_LOGICIELLES;loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pu8_flag_affichage_version[loc_u8_i])
		{
			html_tag("		<tr> \n");
			html_tag("			<td>%s</td> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_nom_logiciel[loc_u8_i]);
#if AFFICHAGE_NUMERO_PROGRAMME_VERSION_LOGICIELLE
			if(INFO_VERSION_PROG_NUMERO_1 == s_html_exploit.s_general.s_version[loc_u8_i].u8_info_suppl)
			{
				html_tag("			<td>%s (%s n°1)</td> \n",
						 s_html_exploit.s_general.s_version[loc_u8_i].ps8_message,
						 pt_tb_msg[u8_html_langue].ps8_msg_programme);
			}
			else
			{
				if(INFO_VERSION_PROG_NUMERO_2 == s_html_exploit.s_general.s_version[loc_u8_i].u8_info_suppl)
				{
					html_tag("			<td>%s (%s n°2)</td> \n",
							 s_html_exploit.s_general.s_version[loc_u8_i].ps8_message,
							 pt_tb_msg[u8_html_langue].ps8_msg_programme);
				}
				else
				{
					html_tag("			<td>%s (%s n°?)</td> \n",
							 s_html_exploit.s_general.s_version[loc_u8_i].ps8_message,
							 pt_tb_msg[u8_html_langue].ps8_msg_programme);
				}
			}
#else
			html_tag("			<td>%s &nbsp;</td> \n",
					 s_html_exploit.s_general.s_version[loc_u8_i].ps8_message);
#endif
			html_tag("		</tr> \n");
		}
	}
	
	html_tag("		</table></td></tr>\n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");

#if AFFICHAGE_HTML_VERSIONS_LOGICIELLES_ONLY
#else
	//NOM EQUIPEMENT : Liste des options
	html_tag("<tr><td><P class=undermenu>%s: %s</P></td></tr> \n",
			 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue],
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_des_options);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"> \n");
	html_tag("		<tr> \n");
	html_tag("			<th width=\"150\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_designation);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_reference_commerciale);
	html_tag("			<th width=\"100\" nowrap>%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_type_option);
	html_tag("			<th width=\"100\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("		</tr> \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_OPTIONS;loc_u8_i++)
	{
		if(TRUE == pt_tb_val->ps_options[loc_u8_i].u8_flag_affichage)
		{
			html_tag("		<tr> \n");
			switch(loc_u8_i)
			{
				default:
					//Nom option
					html_tag("			<td nowrap>%s</td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_nom_option[loc_u8_i]);
					//Nom architecture
					html_tag("			<td nowrap>%s</td> \n",
							 pt_tb_val->ps_options[loc_u8_i].ps8_nom_architecture);
					break;
			}

			//Type option
			switch(pt_tb_val->ps_options[loc_u8_i].u8_type_option)
			{
				case TYPE_OPTION_HARD:
					html_tag("			<td><em>%s</em></td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_materielle);
					break;
				case TYPE_OPTION_SOFT:
					html_tag("			<td><em>%s</em></td> \n",
							 pt_tb_msg[u8_html_langue].ps8_msg_logicielle);
					break;
				default:
					html_tag("			<td>?</td> \n");
					break;
			}

			//Valeur
			if(TRUE == u8TestPresenceOption(loc_u8_i))
			{
				html_tag("			<td><B>%s</B></td> \n",
						pt_tb_msg[u8_html_langue].ps8_msg_presente);
			}
			else
			{
				html_tag("			<td><B>%s</B></td> \n",
						pt_tb_msg[u8_html_langue].ps8_msg_absente);
			}
			html_tag("		</tr> \n");
		}		
	}
	html_tag("		</table></td></tr>\n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
#endif
	
	
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*VAdmVersionsLogicielles*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VAdmVersions
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de vadmversions
//=====================================================================================
void InitModule_VAdmVersions(void)
{
	
}/*InitModule_VAdmVersions*/
