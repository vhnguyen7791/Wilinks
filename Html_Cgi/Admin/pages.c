/*========================================================================*/
/* NOM DU FICHIER  : pages.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 07/06/2007                                           */
/* Libelle         : HTML CGI : page HTML Password						  */
/* Projet          : WRM100                                               */
/* Indice          : BE032                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Correction problème accès au serveur HTTP (dernière un serveur NAT, avec port forwarding)
//BE032 16/06/2010 CM
// - Correction libellé du bouton "Valider" sur la page HTML password
//		-> "Valider" remplacé par "Se connecter"
//		-> "Accept changes" remplacé par "Log in"
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define	_PAGES	1

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

// STRUCTURE RESULTAT POUR LE MOT DE PASSE
typedef struct {
	
	s8sod	ps8_Password[LG_NOM_PWD + 1];		// mot de passe saisi
	
} PASS_RESULTS;

FIELD_LIST PassFields[] = {
	{"password",	"%s",	offsetof(PASS_RESULTS, ps8_Password)	},
	{NULL	}
	
};

/*_____V - PROCEDURES ____________________________________________________*/

// -------------------------------------------------------------
// Fonction    : enter_pwd
// Entrees     :
// Sortie      : rien
// Description : page de saisie du mot de passe
// -------------------------------------------------------------
void enter_pwd(s8sod **loc_p_varlist, s32sod form_method)
{
	s32sod	loc_s32_sem;
	PASS_RESULTS loc_s_Results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_AccessLevel=0;

	printf("Content-type: text/html\n\n");/* Mandatory */
	
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
	
	
	
	html_tag("<HTML>\n");
	
	
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 2 utilise pour URL=...
	{ 
		// Initialisation
		memset(&loc_s_Results,'\0',sizeof(PASS_RESULTS));
		
		// Décodage du Query
		if (!form_decode(PassFields, &loc_s_Results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
			//on fait une page pour le debug
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return; // on sort!
		}
		else
		{
			// Test du mot de passe
			if(		 strcmp(loc_s_Results.ps8_Password, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_low) 
				  && strcmp(loc_s_Results.ps8_Password, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_middle)
				  && strcmp(loc_s_Results.ps8_Password, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_high)
				  && strcmp(loc_s_Results.ps8_Password, MOT_DE_PASSE_SODIELEC)   
			  ) //CONDITION: MOT DE PASSE KO
			{
				//petite page pour signaler mauvais mot de passe
				html_tag("<html> \n");
				html_tag("<head> \n");
				html_tag("<title>%s</title> \n",pt_tb_msg[u8_html_langue].ps8_msg_mot_passe);
				html_tag("<SCRIPT language=\"javascript\">\n");
				html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_mauvais_mot_passe);
				html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=enter_pwd\");");
				html_tag("</SCRIPT>\n");
				html_tag("</HEAD></HTML>");
				
				//evt login echoue 
//				RegisterEvent(INF_LOGIN_HTTP_KO, 0, 0, 0, ETAT_EVT_INFO);
				
				return;
			}
			
			
			// On détermine le Niveau d'Accès
			if(!strcmp(loc_s_Results.ps8_Password, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_low))
			{
				loc_s32_AccessLevel = LOW_LEVEL_ACCESS;
			}
			if(!strcmp(loc_s_Results.ps8_Password, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_middle))
			{
				loc_s32_AccessLevel = MIDDLE_LEVEL_ACCESS;
			}
			if(!strcmp(loc_s_Results.ps8_Password, s_html_cfg_eqpmt.s_admin.ps8_mot_de_passe_high))
			{
				loc_s32_AccessLevel = HIGH_LEVEL_ACCESS;
			}
			
			//Pour accéder au mot de passe des pages de debug de SODIELEC
			if(!strcmp(loc_s_Results.ps8_Password, MOT_DE_PASSE_SODIELEC))//CONDITION : mot de passe SODIELEC OK
			{
				loc_s32_AccessLevel = HIGH_LEVEL_ACCESS;
				s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillHttpFile(&s_html_global))
				{
					s_html_global.u8_connexion_prioritaire_http = TRUE;	//on se connecte
					u8EditHttpFile(&s_html_global);
				}
				s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem
			} 
			
			// Inscription du client dans 'CLIENT.INI'
			
			if(!AddClient(getenv("REMOTE_ADDR"), loc_s32_AccessLevel))
			{
				html_tag("<SCRIPT language=\"javascript\">\n");
				html_tag("alert(\"%s\");", pt_tb_msg[u8_html_langue].ps8_msg_trop_clients);
				//on va a la page d'acceuil qd meme!
				html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=Vaccueil\");");
				html_tag("</SCRIPT>\n");
				html_tag("</HEAD></HTML>"); 
				//evt login echoue 
//				RegisterEvent(INF_LOGIN_HTTP_KO, 0, 0, 0, ETAT_EVT_INFO);
				
				return;
			}
			
			// Redirection vers la page voulue
			html_tag("<SCRIPT language=\"javascript\">\n");
			html_tag("self.location.replace(\"%s\");",s_html_global.ps8_nom_page_html_enter_pwd);
			if(TRUE == s_html_global.u8_connexion_prioritaire_http)
			{
				html_tag("parent.frame_b.document.location.reload(); \n");
			}
#if ACTIVATION_CONSOLE_HTML
			html_tag("parent.frame_console.document.location.reload(); \n");
#endif
#if AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA
			html_tag("parent.frame_a.document.location.reload(); \n");
#endif
			html_tag("</SCRIPT>\n");
			
			html_tag("</HEAD></HTML>"); 
			
			//evt login reussi
//			RegisterEvent(INF_LOGIN_HTTP_OK, 0, 0, 0, ETAT_EVT_INFO);
			
			return ;
		}
	}
	
	// Header
	html_tag("<head> \n");
	html_tag("<title>%s</title> \n",pt_tb_msg[u8_html_langue].ps8_msg_mot_passe);
	//sous netscape le style.css n'est pas détecté au chemin password/style.css
	//	html_tag("<LINK href=\"style.css\" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE> \n");
	html_tag("BODY { \n"
			 "	FONT-SIZE: 8pt; BACKGROUND: #FFFFF0; COLOR: #003300; MARGIN-LEFT: 10pt; FONT-FAMILY: verdana, arial, helvetica, sans-serif \n"
			 "} \n"
			 "INPUT { \n"
			 "	FONT-SIZE: 8pt; FONT-FAMILY: verdana, arial, helvetica \n"
			 "} \n"
			 "TABLE { \n"
			 "	FONT-SIZE: 8pt; FONT-FAMILY: verdana, arial, helvetica, sans-serif \n"
			 "} \n"
			 "TD { \n"
			 "	FONT-SIZE: 8pt; FONT-FAMILY: verdana, arial, helvetica; TEXT-ALIGN: left \n"
			 "} \n"
			 "TR { \n"
			 "	FONT-SIZE: 8pt; FONT-FAMILY: verdana, arial, helvetica; TEXT-ALIGN: left \n"
			 "} \n"
			 "P { \n"
			 "	FONT-SIZE: 8pt; COLOR: #000000; FONT-FAMILY: verdana, arial, helvetica, sans-serif \n"
			 "} \n"
			 "P.header { \n"
			 "	BORDER-RIGHT: #000000 0px solid; BORDER-TOP: #000000 0px solid; FONT-WEIGHT: bold; FONT-SIZE: 11pt; MARGIN: 0px; BORDER-LEFT: #000000 0px solid; COLOR: #000000; BORDER-BOTTOM: #000000 2px solid \n"
			 "} \n");
	html_tag("</STYLE> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</head> \n");
	
	html_tag("<body> \n");
	
	JSActualiser("/cgi-bin/cgi_fh?URL=enter_pwd");	//pour la fonction Actualiser
	
	//Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","enter_pwd");//permet d'avoir la bonne page de rafraichit!!
	html_tag("\n");	
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s</P></TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_mot_passe);
	html_tag("<tr><td><P>&nbsp;\n");
	
	if(TRUE == TestClientIpConnecte(getenv("REMOTE_ADDR"))) //CONDITION: client déjà connecté
	{
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",pt_tb_msg[u8_html_langue].ps8_msg_droits_insuffisants);
	}
	else
	{
		html_tag("<tr><td>&nbsp;</td></tr> \n");
	}
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("	<table border=\"0\"> \n");
	html_tag("	<tr> \n");
	html_tag("	  <td width=\"150\">&nbsp;</td> \n");
	html_tag("	  <td>&nbsp;</td> \n");
	html_tag("	  <td align=\"center\" colspan=\"2\"><p align=\"center\"><input type=\"password\" size=\"10\" maxlength=\"10\" name=\"password\"></p></td> \n");
	html_tag("	</tr> \n");
	html_tag("	<tr> \n");
	html_tag("	  <td width=\"150\">&nbsp;</td> \n");
	html_tag("	  <td>&nbsp;</td> \n");
	// OK
	html_tag("	  <td><input type=\"button\" value=\"%s\"  onclick=\"form.submit()\"></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_se_connecter);
	
	// CANCEL	
	//  html_tag("	  <td><input type=\"button\" value=\"%s\" onclick=\"submit()\"></td> \n",
	//	   pt_tb_msg[u8_html_langue].ps8_msg_annuler);
	
	html_tag("	</tr> \n");
	html_tag("	</table> \n");
	html_tag("</td></tr> \n");
	html_tag("</table> \n");
	html_tag("</form> \n");
	
	// Curseur dans le premier champ
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("document.forms[0].elements[1].focus();");//attention, on a un hidden
	html_tag("</SCRIPT>\n");
	
	html_tag("</BODY> \n"); 
	html_tag("</HTML> \n"); 
	
}/*enter_pwd*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Pages
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de pages
//=====================================================================================
void InitModule_Pages(void)
{
}/*InitModule_Pages*/
