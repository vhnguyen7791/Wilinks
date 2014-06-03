/*========================================================================*/
/* NOM DU FICHIER  : refresh.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: fonctions javascript / Html pour
 *					rafraichir le contenu de la page HTML sans la
 *					recharger											  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _REFRESH
#define _REFRESH_EXT
#else
#define _REFRESH_EXT	extern
#endif

#define NB_ECHEC_REFRESH_AVANT_ALERT		2
#define TIME_MAX_AVANT_REPONSE_REFRESH		60000	//60 secondes

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=========================================================================
// Procedure	: HtmlDyn_SpanAlarm
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne ID de la balise <span>
// Sortie		: Rien
// Auteur		: CM - 23/03/2009
// Description	: fonction HTML pour afficher avec la couleur dans la cellule SPAN via requete Dynamique
//=========================================================================
void HtmlDyn_SpanAlarm(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId);

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
void HtmlDyn_ChaineWithAlarm(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId, s8sod *loc_ps8_fmtp, ...);

//=========================================================================
//Procedure	 : HtmlTD_ChaineWithAlarm
// Entrees		: <loc_u8_etat_alarme> : etat de l'alarme
//				  <loc_ps8_chaineId< : chaîne "générique" ID de la
//				  <loc_ps8_fmtp< : chaîne formatée
//Sortie	 : Rien
//Auteur	 : CM - 11/07/2007
//Description: Affiche une chaîne dans une cellule TD fonction de
//				l'état d'une alarme
//=========================================================================
void HtmlTD_ChaineWithAlarm(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId, s8sod *loc_ps8_fmtp, ...);

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
void HtmlDyn_ConvStatAlarme(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId);

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
void HtmlTD_ConvStatAlarme(u8sod loc_u8_etat_alarme, s8sod *loc_ps8_chaineId, u16sod loc_u16_width_td);

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: RefreshContentsOfFrame
//	Entrées		: <loc_ps8_nom_page< : nom de la page HTML utilisée	pour rafraichir le contenu de la page
//                <loc_u32_timeout>  : time out en ms
//	Sortie 		: rien
//	Auteur		: CM - 11/07/2007
//	Description : création du handlerResponse de la page HTML
// -------------------------------------------------------------------------------------------------------- //
void RefreshContentsOfFrame(s8sod *loc_ps8_nom_page, u32sod	loc_u32_timeout);

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: ps8ConvertChaineToHtml
//	Entrées		: <loc_ps8_chaine_initiale< : chaîne à converir
//	Sortie		: <ps8_chaine_convertie< : chaîne modifiée (variable globale)
//	Auteur		: CM - 11/07/2007
//	Description : Conversion d'une chaîne de caractères adaptée au html
//	(xmlHttprequest)
// -------------------------------------------------------------------------------------------------------- //
s8sod *ps8ConvertChaineToHtml(s8sod *loc_ps8_chaine_initiale);

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: ps8ConvertSansEspaceChaineToHtml
//	Entrées		: <loc_ps8_chaine_initiale< : chaîne à converir
//	Sortie		: <ps8_chaine_convertie< : chaîne modifiée (variable globale)
//	Auteur		: CM - 28/04/2009
//	Description : Conversion d'une chaîne de caractères adaptée au html
//					(xmlHttprequest)
//				Pour résoudre les problèmes sur les caractères avec accents mais laisse les espaces
// -------------------------------------------------------------------------------------------------------- //
s8sod *ps8ConvertSansEspaceChaineToHtml(s8sod *loc_ps8_chaine_initiale);

//=====================================================================================
// Fonction		: InitModule_Refresh
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 10/07/2007 -
// Description	: Initialisation du module de Refresh
//=====================================================================================
void InitModule_Refresh(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

