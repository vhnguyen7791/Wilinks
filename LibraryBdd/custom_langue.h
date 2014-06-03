/*========================================================================*/
/* NOM DU FICHIER  : custom_langue.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Base de donn�es: personalisation de libell�s langue  */
/* Projet          : WRM100                                               */
/* Indice	       : BE060												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/2009 CM
// - CREATION
//BE007 25/01/2010 CM
// - Ajout exploitation de l'ACCESS POINT
//BE042 07/10/2010 CM
// - Ajout gestion debit MCS pour 802.11n
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/


#ifdef _CUSTOM_LANGUE
#define _CUSTOM_LANGUE_EXT
#else
#define _CUSTOM_LANGUE_EXT extern
#endif

//define pour fonction ps8ChLibelleEvt
#define MODE_AFF_LIB_EVT_POUR_HTML			0
#define MODE_AFF_LIB_EVT_POUR_FICHIER		1

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//============================================================================
// Fonction		: ps8GetChAddressMac
// Entrees		: <loc_pu8_adr_mac< : pointeur sur tableau adresse MAC
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 26/10/2009 -
// Description	: renvoie la cha�ne � afficher de l'adresse MAC
//============================================================================
s8sod* ps8GetChAddressMac(u8sod *loc_pu8_adr_mac);

//============================================================================
// Fonction		: ps8GetChBssid
// Entrees		: <loc_ps_exploit_gene> : pointeur sur exploit g�n�rale
//				 <loc_u8_index_langue> : index de la langue � afficher
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 26/10/2009 -
// Description	: renvoie la cha�ne � afficher de l'�tat de la connexion BSSID
//============================================================================
s8sod* ps8GetChBssid(S_STRUCT_EXP_STATION *loc_ps_exploit_station, u8sod loc_u8_index_langue);

//============================================================================
// Fonction		: ps8GetChStatutClientWifi
// Entrees		: <loc_u8_cfg_mode_securite_wifi> : mode de s�curit� wifi configur�
//		  		  <loc_u32_exp_statut_client_wifi> : statut client wifi
//		  		  <loc_u8_index_langue> : index de la langue � afficher
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 26/01/2010 -
// Description	: renvoie la cha�ne � afficher du statut du client Wifi
//============================================================================
s8sod* ps8GetChStatutClientWifi(u8sod loc_u8_cfg_mode_securite_wifi, u32sod loc_u32_exp_statut_client_wifi, u8sod loc_u8_index_langue);

//============================================================================
// Fonction    : ChNiveauGravite
// Entrees     : <loc_u8_niveauGravite> : niveau de gravit�
//				 <loc_ps8_chaine<	: chaine retourn�e
//				 <loc_u8_index_langue> : index de la langue � afficher
// Sortie      : rien
// Auteur	   : CM - 26/10/2009 -
// Description : Procedure qui retourne en chaine de caract�re le niveau de gravit�
// Historique  : 
//============================================================================
void ChNiveauGravite(s8sod *loc_ps8_chaine, u8sod loc_u8_niveauGravite, u8sod	loc_u8_index_langue);

//============================================================================
// Fonction		: ps8ChLibelleEvt
// Entrees		: <loc_u16_indice_evt> : indice evt
//				 <loc_t_valeur_evt> : valeur evt
//				 <loc_u32_info_sup1> : info suppl�mentaire 1 de l'evt
//				 <loc_u8_info_sup2> : info suppl�mentaire 2 de l'evt
//				 <loc_pu8_info_sup3> : info suppl�mentaire 3 de l'evt
//				 <loc_u8_etat_evt> : �tat evt
//				 <loc_u8_index_langue> : index de la langue � afficher
//				 <loc_u8_mode_affichage> : mode d'affichage pour HTML ou fichier log
// Sortie	    : <ps8_chaine_libelle_evt_detaille< : cha�ne retourn�e
// Auteur		: CM - 26/10/2009 -
// Description	: Procedure qui retourne en chaine de caract�re le libell� des �v�nements
// Historique	: 
//============================================================================
s8sod* ps8ChLibelleEvt(u16sod			 loc_u16_indice_evt,
					   T_SIZE_VALEUR_EVT loc_t_valeur_evt,
					   u32sod			 loc_u32_info_sup1,
					   u8sod			 loc_u8_info_sup2,
					   u8sod			 *loc_pu8_info_sup3,
					   u8sod			 loc_u8_etat_evt,
					   u8sod			 loc_u8_index_langue,
					   u8sod			 loc_u8_mode_affichage);

//============================================================================
// Fonction		: ps8GetChEtatAlarme
// Entrees		: <loc_u8_etat_alarme> : �tat de l'alarme
//				  <loc_u8_index_langue> : index de la langue � afficher
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 26/10/2009 -
// Description	: renvoie la cha�ne � afficher de l'�tat en cours de l'alarme
//============================================================================
s8sod* ps8GetChEtatAlarme(u8sod loc_u8_etat_alarme, u8sod loc_u8_index_langue);

//============================================================================
// Fonction		: ps8GetChDataRate
// Entrees		: <loc_u8_idxrate> : index du d�bit � afficher
//				: <loc_u8_index_langue> : index de la langue � afficher
//				: <loc_u8_mode80211> : mode 802.11
//				: <loc_u8_guard_interval> : type intervalle de garde
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 11/10/2010 -
// Description	: renvoie la cha�ne � afficher du d�bit de donn�es
//============================================================================
s8sod* ps8GetChDataRate(u8sod loc_u8_idxrate, u8sod loc_u8_index_langue, u8sod loc_u8_mode80211, u8sod loc_u8_guard_interval);

//=====================================================================================
// Fonction		: InitModule_Custom_Langue
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Initialisation du module custom_Langue
//=====================================================================================
void InitModule_Custom_Langue(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

