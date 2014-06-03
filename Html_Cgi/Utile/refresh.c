/*========================================================================*/
/* NOM DU FICHIER  : refresh.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 10/07/2007											  */
/* Libelle         : HTML CGI: fonctions javascript / Html pour
 *					rafraichir le contenu de la page HTML sans la
 *					recharger											  */
/* Projet          : WRM100                                               */
/* Indice          : BE024                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui permet le rafraichissement du contenu des frames (sans
// recharger la page HTML)

/*_____II - DEFINE SBIT __________________________________________________*/
#define _REFRESH

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//pour fonction HtmlTD_Chaine
#define TAILLE_REFRESH_VSNPRINTF	400
s8sod	ps8_refresh_vsprintbuffer	[TAILLE_REFRESH_VSNPRINTF+1];


//pour fonction ps8ConvertChaineToHtml
#define TAILLE_MAX_CHAINE_CONVERTIE	1000
s8sod	ps8_chaine_convertie[TAILLE_MAX_CHAINE_CONVERTIE+1];

/*_____V - PROCEDURES ____________________________________________________*/

//=========================================================================
// Procedure	: HtmlDyn_SpanAlarm
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne ID de la balise <span>
// Sortie		: Rien
// Auteur		: CM - 23/03/2009
// Description	: fonction HTML pour afficher avec la couleur dans la cellule SPAN via requete Dynamique
//=========================================================================
void HtmlDyn_SpanAlarm(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId)
{
	if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
	{
		if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
		{
			html_tag("&&&id:%s&&&className:rouge&&&",
					 loc_ps8_chaineId);
		}
		else
		{
			if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT2_ETAT_MEMORISE))
			{
				html_tag("&&&id:%s&&&className:orange&&&",
						 loc_ps8_chaineId);
			}
			else
			{
				html_tag("&&&id:%s&&&className:&&&",
						 loc_ps8_chaineId);
			}
		}
	}
	else
	{
		html_tag("&&&id:%s&&&className:gris&&&",
				 loc_ps8_chaineId);
	}

}/*HtmlDyn_SpanAlarm*/

//=========================================================================
// Procedure	: HtmlDyn_ChaineWithAlarm
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne "générique" ID de la
//				  <loc_ps8_fmtp< : chaîne formatée
// Sortie		: Rien
// Auteur		: CM - 11/07/2007
// Description	: fonction HTML pour afficher une chaine de caractères
//				 avec la couleur dans la cellule TD via requete Dynamique
//=========================================================================
void HtmlDyn_ChaineWithAlarm(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId, s8sod *loc_ps8_fmtp, ...)
{
	va_list loc_t_argp;
	u16sod	loc_u16_n;

	va_start(loc_t_argp, loc_ps8_fmtp);
	loc_u16_n = vsnprintf(ps8_refresh_vsprintbuffer, TAILLE_REFRESH_VSNPRINTF, loc_ps8_fmtp, loc_t_argp);

	if((0<loc_u16_n) && (loc_u16_n < TAILLE_REFRESH_VSNPRINTF))	//CONDITION: nb caractères OK
	{
		if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
		{
			if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
			{
				html_tag("&&&id:TD_%s&&&className:rouge&&&",
						 loc_ps8_chaineId);
				html_tag("|");
				html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
						 loc_ps8_chaineId,
						 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
			}
			else
			{
				if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT2_ETAT_MEMORISE))
				{
					html_tag("&&&id:TD_%s&&&className:orange&&&",
							 loc_ps8_chaineId);
					html_tag("|");
					html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
							 loc_ps8_chaineId,
							 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
				}
				else
				{
					html_tag("&&&id:TD_%s&&&className:&&&",
							 loc_ps8_chaineId);
					html_tag("|");
					html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
							 loc_ps8_chaineId,
							 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
				}
			}
		}
		else
		{
			html_tag("&&&id:TD_%s&&&className:gris&&&",
					 loc_ps8_chaineId);
			html_tag("|");
			html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
					 loc_ps8_chaineId,
					 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
		}
	}


}/*HtmlDyn_ChaineWithAlarm*/

//=========================================================================
// Procedure	: HtmlTD_ChaineWithAlarm
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne "générique" ID de la
//				  <loc_ps8_fmtp< : chaîne formatée
// Sortie		: Rien
// Auteur		: CM - 11/07/2007
// Description	: Affiche une chaîne dans une cellule TD fonction de
//				l'état d'une alarme
//=========================================================================
void HtmlTD_ChaineWithAlarm(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId, s8sod *loc_ps8_fmtp, ...)
{
	va_list loc_t_argp;
	u16sod	loc_u16_n;

	va_start(loc_t_argp, loc_ps8_fmtp);
	loc_u16_n = vsnprintf(ps8_refresh_vsprintbuffer, TAILLE_REFRESH_VSNPRINTF, loc_ps8_fmtp, loc_t_argp);

	if((0<loc_u16_n) && (loc_u16_n < TAILLE_REFRESH_VSNPRINTF))	//CONDITION: nb caractères OK
	{
		if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
		{
			if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
			{
				html_tag("<td nowrap id=TD_%s class=\"rouge\">",
						 loc_ps8_chaineId);
				html_tag("<span id=SPAN_%s>%s</span></td>",
						 loc_ps8_chaineId,
						 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
			}
			else
			{
				if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT2_ETAT_MEMORISE))
				{
					html_tag("<td nowrap id=TD_%s class=\"orange\">",
							 loc_ps8_chaineId);
					html_tag("<span id=SPAN_%s>%s</span></td>",
							 loc_ps8_chaineId,
							 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
				}
				else
				{
					html_tag("<td nowrap id=TD_%s class=\"\">",
							 loc_ps8_chaineId);
					html_tag("<span id=SPAN_%s>%s</span></td>",
							 loc_ps8_chaineId,
							 ps8ConvertChaineToHtml(ps8_refresh_vsprintbuffer));
				}
			}
		}
		else
		{
			html_tag("<td nowrap id=TD_%s class=\"gris\">",
					 loc_ps8_chaineId);
			html_tag("<span id=SPAN_%s>%s</span></td>",
					 loc_ps8_chaineId,
					 ps8_refresh_vsprintbuffer);
		}
	}

	
}/*HtmlTD_ChaineWithAlarm*/

//=====================================================================================
// Fonction		: HtmlDyn_ConvStatAlarme
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne "générique" ID de la
//				  balise ID et du texte associé
// Sortie		: rien
// Auteur		: CM - 11/07/2007 -
// Description	: fonction HTML pour afficher "alarme" ou "pas
//					 d'alarme" avec la couleur dans la cellule TD via
//					 requete Dynamique
//=====================================================================================
void HtmlDyn_ConvStatAlarme(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId)
{
	if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
	{
		if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
		{
			html_tag("&&&id:TD_%s&&&className:rouge&&&",
					loc_ps8_chaineId);
			html_tag("|");
			html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
					 loc_ps8_chaineId,
					 pt_tb_msg[u8_html_langue].ps8_msg_alarme_minuscule);
		}
		else
		{
			if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT2_ETAT_MEMORISE))
			{
				html_tag("&&&id:TD_%s&&&className:orange&&&",
						 loc_ps8_chaineId);
				html_tag("|");
				html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
						 loc_ps8_chaineId,
						 pt_tb_msg[u8_html_langue].ps8_msg_alarme_minuscule);
			}
			else
			{
				html_tag("&&&id:TD_%s&&&className:&&&",
						 loc_ps8_chaineId);
				html_tag("|");
				html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
						 loc_ps8_chaineId,
						 ps8ConvertChaineToHtml(pt_tb_msg[u8_html_langue].ps8_msg_pas_d_alarme));
			}
		}
	}
	else
	{
		html_tag("&&&id:TD_%s&&&className:gris&&&",
				 loc_ps8_chaineId);
		html_tag("|");
		html_tag("&&&id:SPAN_%s&&&innerHTML:%s&&&",
				 loc_ps8_chaineId,
				 ps8ConvertChaineToHtml(pt_tb_msg[u8_html_langue].ps8_msg_non_utilise_m));
	}
}/*HtmlDyn_ConvStatAlarme*/

//=====================================================================================
// Fonction		: HtmlTD_ConvStatAlarme
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne "générique" ID de la
//				  balise ID et du texte associé
//				  <loc_u16_width_td> : taille TD
// Sortie		: rien
// Auteur		: CM - 11/07/2007 -
// Description	: fonction HTML pour afficher "alarme" ou "pas
//					 d'alarme" avec la couleur dans la cellule TD
//=====================================================================================
void HtmlTD_ConvStatAlarme(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId, u16sod loc_u16_width_td)
{
	s8sod	loc_ps8_ch_witdh[15];

	strcpy(loc_ps8_ch_witdh, "");
	//largeur TD
	if(loc_u16_width_td != 0)
	{
		sprintf(loc_ps8_ch_witdh, "width=%d",loc_u16_width_td);
	}
	
	if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT7_ETAT_CFG_VALID))
	{
		if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT0_ETAT_COURANT))
		{
			html_tag("<td nowrap %s id=TD_%s class=\"rouge\">",
					 loc_ps8_ch_witdh,
					 loc_ps8_chaineId);
			html_tag("<span id=SPAN_%s>%s</span></td>",
					 loc_ps8_chaineId,
					 pt_tb_msg[u8_html_langue].ps8_msg_alarme_minuscule);
		}
		else
		{
			if(TRUE == u8GetU8EtatBit(loc_u8_etat_alarme, BIT2_ETAT_MEMORISE))
			{
				html_tag("<td nowrap %s id=TD_%s class=\"orange\">",
						 loc_ps8_ch_witdh,
						 loc_ps8_chaineId);
				html_tag("<span id=SPAN_%s>%s</span></td>",
						 loc_ps8_chaineId,
						 pt_tb_msg[u8_html_langue].ps8_msg_alarme_minuscule);
			}
			else
			{
				html_tag("<td nowrap %s id=TD_%s class=\"\">",
						 loc_ps8_ch_witdh,
						 loc_ps8_chaineId);
				html_tag("<span id=SPAN_%s>%s</span></td>",
						 loc_ps8_chaineId,
						 pt_tb_msg[u8_html_langue].ps8_msg_pas_d_alarme);
			}
		}
	}
	else
	{
		html_tag("<td nowrap %s id=TD_%s class=\"gris\">",
				 loc_ps8_ch_witdh,
				 loc_ps8_chaineId);
		html_tag("<span id=SPAN_%s>%s</span></td>",
				 loc_ps8_chaineId,
				 pt_tb_msg[u8_html_langue].ps8_msg_non_utilise_m);
	}
}/*HtmlTD_ConvStatAlarme*/

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: RefreshContentsOfFrame
//	Entrées		: <loc_ps8_nom_page< : nom de la page HTML utilisée	pour rafraichir le contenu de la page
//                <loc_u32_timeout>  : time out en ms
//	Sortie		: rien
//	Auteur		: CM - 11/07/2007
//	Description : création du handlerResponse de la page HTML
// -------------------------------------------------------------------------------------------------------- //
void RefreshContentsOfFrame(s8sod *loc_ps8_nom_page, u32sod	loc_u32_timeout)
{
	html_tag("<SCRIPT language=\"javascript\">\n");
	html_tag(" var http = null; \n");
	html_tag(" var cpt_echec = 0; \n" //INIT
			 " var loc_idTimeOutSndRq;\n"			//Timer pour SndRq
			 " var loc_idTimeoutPasDeReponse;\n"	//Timer pour PasDeReponse
			 " var loc_valeur_timeOutSndRq = %lu;\n", //INIT
			 loc_u32_timeout);	

	html_tag("function JsCreateRequestObject() \n"
			 "{ \n"
			 " var req = null;\n"
			 " if(window.XMLHttpRequest) \n"	// Mozilla, ...
			 " { \n"
			 "		req = new XMLHttpRequest();\n"
			 " }else if(window.ActiveXObject){ \n"	// IE
			 "  try{ \n"
			 "       req = new ActiveXObject(\"Msxm12.XMLHTTP\");\n"
			 "  }catch (e) { \n"
			 "       req = new ActiveXObject(\"Microsoft.XMLHTTP\");\n"
			 "  } \n"
			 " }else {alert(\"PB creation XMLHttpRequest\");req=false;\n"
			 " }\n"
			 " return req;\n"
			 "} \n");	

	html_tag(" http = JsCreateRequestObject();\n"
			 " loc_idTimeOutSndRq = window.setTimeout (\"JsSndReq()\",loc_valeur_timeOutSndRq);\n" //au démarrage
			 "\n");

	html_tag("function JsSndReq() \n"
			 "{ \n"
			 "	http.open(\'GET\',\'%s\'); \n"
			 "	http.setRequestHeader(\"If-Modified-Since\",\"Sat, 1 Jan 2000 00:00:00 GMT\");  \n"
			 "	http.onreadystatechange = JsHandleResponse;  \n"
			 "	http.send(null); \n"
			 "	loc_idTimeoutPasDeReponse = window.setTimeout (\"JsPasDeReponseHttp()\",%d);\n"
			 "} \n",
			 loc_ps8_nom_page,
			 TIME_MAX_AVANT_REPONSE_REFRESH);

	html_tag("function JsPasDeReponseHttp() \n"
			 "{ \n"
			 "	window.clearTimeout(loc_idTimeoutPasDeReponse); \n"
			 "	JsReponseHttpKO(); \n"
			 "	window.clearTimeout(loc_idTimeOutSndRq); \n"
			 "	loc_idTimeOutSndRq = window.setTimeout (\"JsSndReq()\",loc_valeur_timeOutSndRq);\n" //on réamorce l'envoi de la requête
			 "} \n");

	html_tag("function JsReponseHttpKO() \n"
			 "{ \n"
			 "	if(cpt_echec>=%d) \n"	//CONDITION: 2 echecs consécutif
			 "	{ \n"
			 "		alert(\"%s\");\n"
			 "		cpt_echec =0; \n"
			 "	} \n"
			 "	else \n"
			 "	{ \n"
			 "		cpt_echec +=1; \n"
			 "	} \n"
			 "} \n",
			 NB_ECHEC_REFRESH_AVANT_ALERT,
			 pt_tb_msg[u8_html_langue].ps8_msg_equipement_non_connecter_reactualiser);

	
	html_tag("function JsHandleResponse() \n" 
			 "{ \n"
			 "	var loc_reponse_ok = true; \n" //par défaut réponse OK
			 "	if((4 == http.readyState) && (200 == http.status)) \n"
			 "	{ \n"
			 "		var response = http.responseText; \n"
			 "		var loc_tab_champs = new Array(); \n"
			 "		var loc_tab_proprietes = new Array(); \n"
			 "		var loc_i_k = 1; \n"
			 "		var loc_index_champ = 1; \n"
			 "		var nouvelle_chaine = \"\"; \n"
			 "		var loc_nombre_id = 0; \n"
			 "		var champ = \"\"; \n"
			 "		var champ2 = \"\"; \n"
			 "		if(response.indexOf('|') != -1) \n"
			 "		{ \n"
			 "			cpt_echec =0; \n"	//mise à 0 du compteur d'echec
			 "			loc_tab_champs = response.split('|'); \n"
			 "			loc_nombre_id = loc_tab_champs.length-2; \n"
			 "			for (loc_index_champ = 1 ; loc_index_champ <= loc_nombre_id ; loc_index_champ++) \n"		  
			 "			{ \n"
			 "				valeur_champ_id =\"\"; \n"
			 "				champ = \"\"; \n"
			 "				champ = champ.concat(champ,loc_tab_champs[loc_index_champ]); \n"
			 "				if (champ.search(\"&&&\") != -1) \n"
			 "				{ \n"
			 "					loc_tab_proprietes = champ.split(\"&&&\"); \n"
			 "					for(loc_i_k = 1 ; loc_i_k <= (loc_tab_proprietes.length-2) ; loc_i_k++) \n"
			 "					{ \n"
			 "						champ2 = \"\"; \n"
			 "						champ2 = champ2.concat(champ2,loc_tab_proprietes[loc_i_k]); \n"
			 "						valeur_propriete = \"\" \n"
			 "						if (champ2.search(\":\") != -1) \n"
			 "						{ \n" 
			 "							if (champ2.search(\"id\") == 0) \n"
			 "							{ \n" 
			 "								valeur_champ_id= champ2.substr(3); \n"
			 "								if(null == document.getElementById(valeur_champ_id)) \n"
			 "								{ \n"
//			 "									alert(champ2.search(\"id\")+'PPPPPPP'+loc_tab_proprietes+'#########'+loc_i_k+'==>'+champ2+'   id inconnu = '+valeur_champ_id); \n"
			 "									// id inconnu -> on raffraichit la page \n"
//			 "									window.clearInterval(actif); \n"
			 "									loc_reponse_ok = true; \n" // réponse ok (c'est peut-être normal)
			 "									setTimeout('self.location.reload()',1); \n" //on charge la page HTML
			 "								} \n" 
			 "							} \n"
			 "							if (champ2.search(\"innerHTML\") == 0) \n"
			 "							{ \n" 
			 "								valeur_propriete += champ2.substr(10); \n"
			 "								document.getElementById(valeur_champ_id).innerHTML = valeur_propriete; \n"
			 "							} \n"
			 "							if (champ2.search(\"className\") == 0) \n"
			 "							{ \n" 
			 "								valeur_propriete += champ2.substr(10); \n"
			 "								document.getElementById(valeur_champ_id).className = valeur_propriete; \n"
			 "							} \n"
			 "							if (champ2.search(\"stylecolor\") == 0) \n"
			 "							{ \n" 
			 "								valeur_propriete += champ2.substr(11); \n"
			 "								document.getElementById(valeur_champ_id).style.color = valeur_propriete; \n"
			 "							} \n"
			 "							if (champ2.search(\"styledisplay\") == 0) \n"
			 "							{ \n"
			 "								valeur_propriete += champ2.substr(13); \n"
			 "								document.getElementById(valeur_champ_id).style.display = valeur_propriete; \n"
			 "							} \n"
			 "						} \n"
			 "						else \n"
			 "						{ \n"
			 "							// Syntax Error n°309 : Problème de syntaxe dans le pipe => pas : \n"
			 "							alert(\"Syntax Error n°309 : \"+champ+\" with \"+loc_tab_proprietes); \n"
//			 "							window.clearInterval(actif); \n"
			 "							loc_reponse_ok = false; \n" // réponse ko
			 "						} \n" 
			 "					} \n"
			 "				} \n"
			 "			} \n" 
			 "		} \n"
			 "		window.clearTimeout(loc_idTimeoutPasDeReponse); \n"
			 "		if(true == loc_reponse_ok) \n" //CONDITION: réponse OK
			 "		{ \n"
			 "			window.clearTimeout(loc_idTimeOutSndRq); \n"
			 "			loc_idTimeOutSndRq = window.setTimeout (\"JsSndReq()\",loc_valeur_timeOutSndRq);\n" //on réamorce l'envoi de la requête
			 "		} \n"
			 "		else \n"
			 "		{ \n"
			 "			JsReponseHttpKO(); \n"
			 "			window.clearTimeout(loc_idTimeOutSndRq); \n"
			 "			loc_idTimeOutSndRq = window.setTimeout (\"JsSndReq()\",loc_valeur_timeOutSndRq);\n" //on réamorce l'envoi de la requête
			 "		} \n"
			 "	} \n" 
			 "} \n");

	html_tag("</SCRIPT>\n");
}/*RefreshContentsOfFrame*/

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: ps8ConvertChaineToHtml
//	Entrées		: <loc_ps8_chaine_initiale< : chaîne à converir
//	Sortie		: <ps8_chaine_convertie< : chaîne modifiée (variable globale)
//	Auteur		: CM - 11/07/2007
//	Description : Conversion d'une chaîne de caractères adaptée au html
//					(xmlHttprequest)
//				Pour résoudre les problèmes sur les caractères avec accents et les ESPACES
// -------------------------------------------------------------------------------------------------------- //
s8sod *ps8ConvertChaineToHtml(s8sod *loc_ps8_chaine_initiale)
{
	u16sod	loc_u16_i;
	s8sod	loc_ps8_code[10];
	
	strcpy(ps8_chaine_convertie,"");	//INIT
	
	for (loc_u16_i = 0; loc_u16_i<strlen(loc_ps8_chaine_initiale);loc_u16_i++)
	{
		if ((u8sod)loc_ps8_chaine_initiale[loc_u16_i] > 0x7E)	//CONDITION: caractères ASCII ETENDUS
		{
			sprintf(loc_ps8_code,"&#%ld;",(s32sod)((u8sod)loc_ps8_chaine_initiale[loc_u16_i]));
		}
		else
		{
			if(' ' == loc_ps8_chaine_initiale[loc_u16_i]) //CONDITION: si espace
			{
				strcpy(loc_ps8_code, "&nbsp;");
			}
			else
			{
				sprintf(loc_ps8_code,"%c",loc_ps8_chaine_initiale[loc_u16_i]);
			}
		}
		strcat(ps8_chaine_convertie, loc_ps8_code);
		if(strlen(ps8_chaine_convertie) > (TAILLE_MAX_CHAINE_CONVERTIE-6))
		{
			loc_u16_i = 0xFFF0;	//on sort
		}
	}
	
	return(ps8_chaine_convertie);
}/*ps8ConvertChaineToHtml*/

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: ps8ConvertSansEspaceChaineToHtml
//	Entrées		: <loc_ps8_chaine_initiale< : chaîne à converir
//	Sortie		: <ps8_chaine_convertie< : chaîne modifiée (variable globale)
//	Auteur		: CM - 28/04/2009
//	Description : Conversion d'une chaîne de caractères adaptée au html
//					(xmlHttprequest)
//				Pour résoudre les problèmes sur les caractères avec accents mais laisse les espaces
// -------------------------------------------------------------------------------------------------------- //
s8sod *ps8ConvertSansEspaceChaineToHtml(s8sod *loc_ps8_chaine_initiale)
{
	u16sod	loc_u16_i;
	s8sod	loc_ps8_code[10];

	strcpy(ps8_chaine_convertie,"");	//INIT

	for (loc_u16_i = 0; loc_u16_i<strlen(loc_ps8_chaine_initiale);loc_u16_i++)
	{
		if ((u8sod)loc_ps8_chaine_initiale[loc_u16_i] > 0x7E)	//CONDITION: caractères ASCII ETENDUS
		{
			sprintf(loc_ps8_code,"&#%ld;",(s32sod)((u8sod)loc_ps8_chaine_initiale[loc_u16_i]));
		}
		else
		{
			sprintf(loc_ps8_code,"%c",loc_ps8_chaine_initiale[loc_u16_i]);
		}
		strcat(ps8_chaine_convertie, loc_ps8_code);
		if(strlen(ps8_chaine_convertie) > (TAILLE_MAX_CHAINE_CONVERTIE-6))
		{
			loc_u16_i = 0xFFF0;	//on sort
		}
	}

	return(ps8_chaine_convertie);
}/*ps8ConvertSansEspaceChaineToHtml*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Refresh
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/07/2007 -
// Description	: Initialisation du module de Refresh
//=====================================================================================
void InitModule_Refresh(void)
{
	strcpy(ps8_refresh_vsprintbuffer, ""); //INIT
	strcpy(ps8_chaine_convertie, ""); //INIT
}/*InitModule_Refresh*/

