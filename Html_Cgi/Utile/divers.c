/*========================================================================*/
/* NOM DU FICHIER  : divers.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: fonctions diverse génériques				  */
/* Projet          : WRM100                                               */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Correction problème accès au serveur HTTP (dernière un serveur NAT, avec port forwarding)
/*========================================================================*/


/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES _______________________*/

/*_______II - DEFINE ______________________________________________________*/

#define	_DIVERS

/*_______III - INCLUDES - DIRECTIVES ______________________________________*/
#include "../services.h"

/*_______IV  - PROTOTYPES IMPORTES _____________________MODULE______________*/

/*_______V   - VARIABLES GLOBALES __________________________________________*/

/*_______VI  - PROCEDURES __________________________________________________*/

//=====================================================================================
// Fonction		: ps8EncadreText
// Entrees		: <loc_ps8_balise_debut< : balise HTML début
//				: <loc_ps8_name_html< : texte à cadrer par les balises HTML
//				: <loc_ps8_balise_fin< : balise HTML fin
// Sortie		: rien
// Auteur		: CM - 25/07/2007 -
// Description	: Encadre le texte des balises
//=====================================================================================
s8sod* ps8EncadreText(s8sod *loc_ps8_balise_debut, s8sod *loc_ps8_text, s8sod *loc_ps8_balise_fin)
{
	static s8sod loc_ps8_chaine[300];

	loc_ps8_chaine[0] = 0;	//INIT

	sprintf(loc_ps8_chaine, "%s%s%s",
			 loc_ps8_balise_debut,
			 loc_ps8_text,
			 loc_ps8_balise_fin);
	
	return(&loc_ps8_chaine[0]);
}/*ps8EncadreText*/

//=====================================================================================
// Fonction		: Html_GotoPage
// Entrees		: <loc_ps8_name_html< : Nom de la page HTML à charger
// Sortie		: rien
// Auteur		: CM - 31/08/2006 -
// Description	: Gère retours à une page HTML (suite validation)
//=====================================================================================
void Html_GotoPage(s8sod *loc_ps8_name_html)
{
	html_tag("<HTML><HEAD>\n");
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("self.location.replace(\"%s\");", loc_ps8_name_html);
	html_tag("</SCRIPT>\n");
	html_tag("</HEAD></HTML>");
}/*Html_GotoPage*/

//============================================================================
// Fonction		: form_hidden
// Entrees		: <loc_ps8_namep< : nom de la variable cree
// Entrees		: <loc_ps8_valuep< : valeur init
// Sortie		: rien
// Description	: declare une variable cachee dans un form
//============================================================================
void form_hidden(s8sod *loc_ps8_namep, s8sod *loc_ps8_valuep)
{
	html_tag("<input type=\"hidden\"  name=\"%s\"  value=\"%s\" >",
			 loc_ps8_namep,
			 loc_ps8_valuep);
}/*form_hidden*/


//============================================================================
// Fonction	: form_decode 
// Entrees	: <loc_t_ftp< : pointeur sur la structure type de la form
//            <loc_t_structp< : pointeur sur la structure de sortie (la ou va etre mis la recuperation)
//            <loc_p_varlist< : la liste des parametres d'entree de la form
//            <loc_ps8_emsgp< : pointeur sur une chaine de caractere : si erreur lors de la recup, contient la cause de l'erreur
// Sortie	: 1 ou 0 suivant le succes ou non de la recuperation
// Description	: recupere les parametres d'un form dans la structure 
//                passee en parametre
//============================================================================
s32sod form_decode (FIELD_LIST *loc_t_ftp, 
					void	*loc_t_structp, 
					s8sod	**loc_p_varlist, 
					s8sod	*loc_ps8_emsgp)
{
	u16sod loc_u16_nb_param,loc_u16_i,loc_u16_indice_param;
	FIELD_LIST * loc_ps_field;
	s8sod * loc_ps8_name;
	
	if (loc_p_varlist)
	{
		loc_u16_nb_param = s32GetArgNb(loc_p_varlist);
		if (loc_u16_nb_param < 4)
		{
			sprintf(loc_ps8_emsgp,"pas de parametres");
			return (0);
		}
		loc_u16_nb_param -=2; // on ne tient pas compte de URL et du nom de la page
		loc_u16_indice_param = 2;
		for (loc_u16_i=0;loc_u16_i<(loc_u16_nb_param/2);loc_u16_i++)
		{
			//recherche dans la liste des noms de variable
			loc_ps_field = loc_t_ftp;
			while (1)
			{
				loc_ps8_name = loc_ps_field->namep;
				if (NULL == loc_ps8_name)
				{ // pas trouve!!
					sprintf(loc_ps8_emsgp,"champ inconnu");
					return(0);
				}
				if (!strcmp(loc_ps_field->namep,loc_p_varlist[loc_u16_indice_param]))
				{// on a trouve le champ!
					//recopie de la valeur contenu dans le champ suivant de Varlist
					strcpy((s8sod *)(loc_t_structp + loc_ps_field->moffset), loc_p_varlist[loc_u16_indice_param+1]);
					break; // pour sortir du while (1)
				}
				loc_ps_field++;
			}
			loc_u16_indice_param+=2;
		}
		return(1); //sortie sans erreur
	}
	else
	{ // pas de parametre!
		sprintf(loc_ps8_emsgp,"pas de parametres");
		return(0);
	}
	
}/*form_decode*/




//============================================================================
// Fonction	: PagePbdebug 
// Entrees	: tableau de pointeur sur les parametres de la page
//            <loc_ps8_emsgp< : pointeur sur une chaine de caractere : si erreur lors de la recup, contient la cause de l'erreur
// Sortie	: Rien
// Description	: recupere les parametres d'un form dans la structure 
//                passee en parametre
//============================================================================
void PagePbdebug (s8sod **loc_p_varlist, 
				  s8sod *loc_ps8_emsgp)
{
	u16sod loc_u16_i,loc_u16_nb_arg;
	
	html_tag("<HTML><HEAD>\n");		
	html_tag("<TITLE>Warning</TITLE>");
	html_tag("<LINK href=""../style.css"" type=text/css rel=stylesheet></LINK>\n");
	html_tag("<STYLE> \n");
	html_tag("	TD.warning { \n");
	html_tag("		font-size: 12pt; \n");
	html_tag("		font-weight: bold; \n");
	html_tag("		text-align: center; \n");
	html_tag("} \n");
	html_tag("</STYLE> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("</HEAD>");
	html_tag("<body> \n");
	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("	<TR><TD vAlign=top height=40><P class=header>%s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_avertissement);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("	<TR><TD align=center class=warning>%s</TD></TR> \n",pt_tb_msg[u8_html_langue].ps8_msg_page_indisponible);
	loc_u16_nb_arg = s32GetArgNb(loc_p_varlist);
	for (loc_u16_i=0;loc_u16_i<loc_u16_nb_arg;loc_u16_i++)
	{
		html_tag("	<TR><TD>argument%d : %s</TD></TR> \n",loc_u16_i,loc_p_varlist[loc_u16_i]);
	}
	
	html_tag("	<TR><TD>retour de form_decode :%s</TD></TR> \n",loc_ps8_emsgp);
	html_tag("</table> \n");
	html_tag("</body>\n");
	html_tag("</html>\n");
}


//============================================================================
// Fonction		: PreparePagePswd
// Entrees		: une chaine de cractere contenant l'adresse de la page demandee
// Sortie		: Rien
// Auteur		: 
// Description	: on sauve  la page à accéder et on charge la page HTML enter_pwd
//============================================================================
void PreparePagePswd (const s8sod *loc_ps8_adresse)
{
	s32sod	loc_s32_sem;

	
	html_tag("<html> \n");
	html_tag("<head> \n");
	
	// on recharge la page cachee pour sauvegarder la page demandee
	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore
	//On recherche si déjà présent
	if(TRUE == u8FillHttpFile(&s_html_global))
	{
		strcpy(s_html_global.ps8_nom_page_html_enter_pwd, "/cgi-bin/cgi_fh?URL=");
		strcat(s_html_global.ps8_nom_page_html_enter_pwd, loc_ps8_adresse);
		u8EditHttpFile(&s_html_global);
	}
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem

//	html_tag("<script language=\"JavaScript\">\n");
//	html_tag("parent.frame_d.document.location.replace(\"/cgi-bin/cgi_fh?URL=FRAMED&Adres=%s\");\n",loc_ps8_adresse);
//	html_tag("</script>\n");
	
	//on passe a la page de saisie du mot de passe
	html_tag("<title>%s</title> \n",pt_tb_msg[u8_html_langue].ps8_msg_mot_passe);
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag("self.location.replace(\"/cgi-bin/cgi_fh?URL=enter_pwd\");");
	html_tag("</SCRIPT>\n");
	html_tag("</HEAD></HTML>");
	
}/*PreparePagePswd*/

//============================================================================
// Fonction		: AfficheDansToutesLesPages
// Entrees		: Rien
// Sortie		: Rien
// Auteur		: MS
// Description	: permet d'afficher un message commun à toutes les pages
//				  attention : à chaque création de pages HTML, il faut appeler cette
//				  fonction
//============================================================================
void AfficheDansToutesLesPages ()
{
}//AfficheDansToutesLesPages


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Divers
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de divers
//=====================================================================================
void InitModule_Divers(void)
{
}/*InitModule_Divers*/


