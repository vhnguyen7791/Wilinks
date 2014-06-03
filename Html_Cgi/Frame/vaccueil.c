/*========================================================================*/
/* NOM DU FICHIER  : vaccueil.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/06/2007                                           */
/* Libelle         : HTML CGI: pages HTML d' accueil					  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _VACCUEIL

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: Vaccueil
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: 
// Description	: page HTML d'accueil
//=====================================================================================
void Vaccueil(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{	
	s32sod	loc_s32_sem;
	u8sod	loc_u8_type_equipement;

	loc_u8_type_equipement = EQUIPEMENT_INCONNU; //INIT

	printf("Content-type: text/html\n\n");/* Mandatory */
	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), LOW_LEVEL_ACCESS))
	{
		PreparePagePswd("Vaccueil");
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
	
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if((FALSE == u8FillConfigConstructeur(&s_html_cfg_eqpmt))||
	   (FALSE == u8FillConfigAdmin(&s_html_cfg_eqpmt))
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
	
	html_tag("<HTML>\n");
	// Header
	html_tag("<HEAD>\n");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("p.header { \n");
	html_tag("	font-size: 15pt; \n");
	html_tag("	font-weight: normal; \n");
	html_tag("} \n");
	html_tag("</STYLE> \n");
	html_tag("<TITLE>Accueil</TITLE>");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head>\n");

	JSActualiser("/cgi-bin/cgi_fh?URL=Vaccueil");	//pour la fonction Actualiser

	html_tag("<body> \n");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><TD vAlign=top height=52><P class=header>%s: %s</P></TD></tr> \n",
			 s_html_cfg_eqpmt.s_constructeur.ps8_nom,
			 pt_tb_msg[u8_html_langue].ps8_msg_accueil);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_accueil);

	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_description);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\" width=\"500\" > \n");
	html_tag("<tr> \n");
	html_tag("	<TH width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
	html_tag("  <TH width=\"250\">%s</th> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
	html_tag("</tr> \n");
	html_tag("<tr> \n");
	html_tag("	<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_type_d_equipement);
	html_tag("	<td>%s</td> \n",
			 S_DESCRIPT_EQUIPEMENT[loc_u8_type_equipement].ps8_nom[u8_html_langue]);
	html_tag("</tr> \n");
	html_tag("<tr> \n");
	html_tag("	<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_identifiant_equipement);
	html_tag("	<td>%s</td> \n",
			 s_html_cfg_eqpmt.s_admin.ps8_identifiant);
	html_tag("</tr> \n");
	html_tag("<tr> \n");
	html_tag("	<td>%s</td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_localisation_equipement);
	html_tag("	<td>%s</td> \n",
			 s_html_cfg_eqpmt.s_admin.ps8_localisation);
	html_tag("</tr> \n");
	html_tag("</table> \n");
	html_tag("</td> \n");
	html_tag("</tr> \n");

//	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_configuration_generale);
//	html_tag("<tr><td>&nbsp;</td></tr> \n");
//	html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\"  width=\"500\" > \n");
//	html_tag("	   	<tr> \n");
//	html_tag("			<th width=\"250\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_parametre);
//	html_tag("			<th width=\"250\">%s</th> \n",pt_tb_msg[u8_html_langue].ps8_msg_valeur);
//	html_tag("		</tr> \n");
//	html_tag("</table></td></tr> \n");
//	html_tag("<tr><td>&nbsp;</td></tr> \n");

	html_tag("</table> \n");


	html_tag("</BODY>\n");
	html_tag("</HTML>\n");

}/*Vaccueil*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


//=====================================================================================
// Fonction		: InitModule_VAccueil
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation du module Vaccueil
//=====================================================================================
void InitModule_VAccueil(void)
{

}/*InitModule_VAccueil*/
