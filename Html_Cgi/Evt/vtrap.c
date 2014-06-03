/*========================================================================*/
/* NOM DU FICHIER  : vtrap.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/02/2010                                           */
/* Libelle         : HTML CGI: page HTML TRAPs							  */
/* Projet          : WRM100                                               */
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

#define _VTRAP

enum LISTE_DES_FORM_VTRAP
{
	FORM_VTRAP_ACQUITTER = 1,
	NB_MAX_FORM_VTRAP
};


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_hidden1				[20 + 1];
} S_VTRAP_RESULTS;

FIELD_LIST s_vtrapFields[] = {
	{"hidden1",		  "%s",		offsetof(S_VTRAP_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_VTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: code de javascript de la page Vtrap
//=====================================================================================
void proc_JavaScript_VTrap(void)
{
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("function SelectFormulaire(i_numForm,form) \n"
			 "{ \n"
			 "	form.hidden1.value = i_numForm;\n"
			 "	form.submit();\n"
			 "} \n");	

	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_VTrap*/


//=====================================================================================
// Fonction		: VTrap
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 19/11/2007
// Description	: Page HTML Evenement: TRAPs
//				"URL=VTrap"
//=====================================================================================
void VTrap(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	s8sod				loc_ps8_emsg[50];
	S_VTRAP_RESULTS		loc_s_results;
	s32sod				loc_s32_sem;
	s32sod				loc_s32_NumeroForm;

	printf("Content-type: text/html\n\n");/* Mandatory */

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		PreparePagePswd("VTrap");
		return;
	}

	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_VTRAP_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_vtrapFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			loc_s32_NumeroForm = atoi(loc_s_results.ps8_hidden1);

			// Acquitter
			if(FORM_VTRAP_ACQUITTER == loc_s32_NumeroForm)
			{
				s32Lock_Get(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillCipSnmpd(&s_cip_snmpd_from_html))
				{
					s_cip_snmpd_from_html.u8_acquit_all_traps = TRUE;
					u8EditCipSnmpd(&s_cip_snmpd_from_html);
				}
				s32Lock_Release(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on relache le sem
			}
			//On recharge la page pour re-initialiser les champs "objets" HTML
			Html_GotoPage("/cgi-bin/cgi_fh?URL=VTrap");
			return; // on sort!
		}
	}

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(TRUE == u8FillConfigSnmp(&s_html_cfg_eqpmt))
	{
		;
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
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_table_alarmes);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");

	html_tag("<body> \n");

	JSActualiser("/cgi-bin/cgi_fh?URL=VTrap");	//pour la fonction Actualiser
	proc_JavaScript_VTrap();

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_evenements,
			 pt_tb_msg[u8_html_langue].ps8_msg_table_alarmes);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_Vtrap);
	html_tag("<tr><td>&nbsp;</td></tr> \n");

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>&nbsp;</P></td></tr> \n");

	s32Lock_Get(SEMAPHORE_BDD_CIP_STATUSTRAP, &loc_s32_sem);	//on lève le sem
	

	html_tag("<tr><td><table border=0> \n");
		//1ère ligne
	html_tag("<tr> \n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Index);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Id);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_libelle);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Valeur);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Statut);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Date);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Heure);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td><B><u>%s</u></B></td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_alarmeV1Acquit);
	html_tag("</tr> \n");

	if(FALSE == u8ReadCipStatusTrap(&T_DEF_FILE_CIP_STATUSTRAP_INI, u8Html_StatusTrap))
	{
		;
	}

	html_tag("</table></td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	if(VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
	{
		//bouton
		if(TRUE == TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
		{
			html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
			form_hidden("URL","VTrap");
			form_hidden("hidden1","0");
			html_tag("<tr><td> \n");
			html_tag("&nbsp;<input type=\"button\" value=\"%s\" onClick= \"return SelectFormulaire(%d, form)\"> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_acquitter_tous_les_traps,
					 FORM_VTRAP_ACQUITTER);
			html_tag("</td></tr> \n");
			html_tag("</form> \n");
		}
	}
	
	html_tag("</table> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

	s32Lock_Release(SEMAPHORE_BDD_CIP_STATUSTRAP, &loc_s32_sem);	//on relache le sem
	
}/*VTrap*/

//=====================================================================================
// Fonction		: u8Html_StatusTrap
// Entrees		: <loc_ps_elt_statustrap< : statut trap à afficher
// Sortie		: <loc_u8_return>
// Auteur		: CM - 03/03/2010
// Description	: Affichage d'une ligne de statut trap
//=====================================================================================
u8sod u8Html_StatusTrap(S_STRUCT_CIP_ELEMENT_STATUSTRAP *loc_ps_elt_statustrap)
{
	u8sod loc_u8_return;

	loc_u8_return = TRUE; //INIT
	
	html_tag("<tr> \n");
	html_tag("	<td>%d</td>\n",
			 loc_ps_elt_statustrap->u16_idx_table+1);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>%d</td>\n",
			 S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_ps_elt_statustrap->u16_index_evt].u16_numero_evt);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td nowrap>%s</td>\n",
			 pt_tb_msg[u8_html_langue].ps8_msg_lib_evenement[loc_ps_elt_statustrap->u16_index_evt]);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>%lu</td>\n",
			 loc_ps_elt_statustrap->t_valeur_evt);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	switch(loc_ps_elt_statustrap->u8_etat_evt)
	{
		case ETAT_EVT_DEBUT:
			html_tag("	<td nowrap>%s</td>\n",
					 pt_tb_msg[u8_html_langue].ps8_msg_statut_alarme_on);
			break;
		case ETAT_EVT_FIN:
			html_tag("	<td nowrap>%s</td>\n",
					 pt_tb_msg[u8_html_langue].ps8_msg_statut_alarme_off);
			break;
		case ETAT_EVT_INFO:
			html_tag("	<td nowrap>%s</td>\n",
					 pt_tb_msg[u8_html_langue].ps8_msg_statut_info);
			break;
		default:
			html_tag("	<td>?</td>\n");
			break;
	}
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>%04d%02d%02d</td>\n",
			 loc_ps_elt_statustrap->s_date.u16_annee,loc_ps_elt_statustrap->s_date.u8_mois,loc_ps_elt_statustrap->s_date.u8_jour);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>%02d%02d%02d</td>\n",
			 loc_ps_elt_statustrap->s_date.u8_heure,loc_ps_elt_statustrap->s_date.u8_minute,loc_ps_elt_statustrap->s_date.u8_seconde);
	html_tag("	<td>&nbsp;</td>\n");
	html_tag("	<td>&nbsp;</td>\n");
	if(VERSION_SNMPV1 == s_html_cfg_eqpmt.s_snmp.u8_version_snmp)
	{
		switch(loc_ps_elt_statustrap->u8_val_snmp)
		{
			case VAL_SNMP_NON_ACQUITTER:
				html_tag("	<td nowrap>%s</td>\n",
						 pt_tb_msg[u8_html_langue].ps8_msg_val_non_acquitter);
				break;
			case VAL_SNMP_ACQUITTER:
				html_tag("	<td nowrap>%s</td>\n",
						 pt_tb_msg[u8_html_langue].ps8_msg_val_acquitter);
				break;
			case VAL_SNMP_SUPPRIMER:
				html_tag("	<td nowrap>%s</td>\n",
						 pt_tb_msg[u8_html_langue].ps8_msg_val_supprimer);
				break;
			default:
				html_tag("	<td>?</td>\n");
				break;
		}
	}
	else //VERSION_SNMPV2C
	{
		html_tag("	<td> --- </td>\n");
	}
	html_tag("</tr> \n");

	return loc_u8_return;
}/*u8Html_StatusTrap*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_VTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/07/2007
// Description	: Initialisation du module de VTrap
//=====================================================================================
void InitModule_VTrap(void)
{
}/*InitModule_VTrap*/
