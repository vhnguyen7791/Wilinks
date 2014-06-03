/*========================================================================*/
/* NOM DU FICHIER  : td_langue.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : Base de données: type def langue					  */
/* Projet          : WRM100                                               */
/* Indice	       : BE065												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Modification javascript isValidText
// - Intégration configuration hostname
// - Ajout exploitation adresse IP/Mask des interfaces
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE007 25/01/2010 CM
// - Ajout exploitation de l'ACCESS POINT
// - Modification gestion routage statique
//BE008 28/01/2010 CM
// - Modification page HTML langue (+générique)
// - Ajout syslog: journalisation du système
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
// - Correction test configuration des adresses IP des interfaces
// - Ajout information statut IP des interfaces
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE019 16/03/2010 CM
// - Autorisation de passer la station en bridge
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
//BE032 16/06/2010 CM
// - Correction libellé du bouton "Valider" sur la page HTML password
// - Ajout gestion Radius / WPA - EAP
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
// - Ajout exploitation temperature 
// - Modification page HTML Admin - Controle pour redémarrer équipement
// - Modification page HTML Admin - Controle pour raz générale
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Ajout paramètre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout dans exploitation du canal en cours (sur AP et STA)
// - Ajout configuration "desactivation DFS" (WRM100-N)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout configuration date/heure au démarrage de l'équipement
//BE065.1 02/05/2012 (CM)
// - Correction libellé dans page Html Administration - Controle
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/


#define UI_TAILLE_MAX_MESSAGE	80
#define UI_TAILLE_MAX_MESSAGE_2 300

//Liste des modes de pilotage
enum LISTE_DES_MODES_PILOTAGES
{
	MODE_LOCAL	 = 0,
	MODE_DISTANT	,
	NB_MAX_MODES_PILOTAGES
};


enum LISTE_DES_ACCES_PASERELLES
{
	ACCES_GW_INACTIF = 0,
	ACCES_GW_LAN,
	NB_MAX_ACCES_GW
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef struct {
	//HOMEB - Accueil + Actualiser
	s8sod	ps8_msg_accueil						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_accueil				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_actualiser					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_actualiser				[UI_TAILLE_MAX_MESSAGE];
	//HOMEB - Menu Administration
	s8sod	ps8_msg_administration				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_identification				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_identification			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_controle					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_controle				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_securite					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_securite				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mise_a_heure				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_mise_a_heure			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_versions_logicielles		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_versions_logicielles	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_versions_logicielles_et_options	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_versions_logicielles_et_options	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_telechargement				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_telechargement			[UI_TAILLE_MAX_MESSAGE];
	//HOMEB - Menu Réseau
	s8sod	ps8_msg_reseau_de_supervision		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_etat_de_configuration		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_modification_de_configuration	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_modification_de_configuration	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_etat_de_configuration	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_Adresses_Ip					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_Adresses_Ip			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_Adresse_Ip					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_Adresse_Ip				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_Routage_Ip					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_Routage_Ip				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_SNMP						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_SNMP					[UI_TAILLE_MAX_MESSAGE];
	//HOMEB - Menu Exploitation
	s8sod	ps8_msg_exploitation				[UI_TAILLE_MAX_MESSAGE];
	//HOMEB - Menu Alarmes
	s8sod	ps8_msg_alarmes						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_alarmes				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_liste_alarmes			[UI_TAILLE_MAX_MESSAGE];
	//HOMEB - Menu Evenements
	s8sod	ps8_msg_evenements					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_list_evenements				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_list_evenements		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_evenements		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_parametrage_evenements	[UI_TAILLE_MAX_MESSAGE];
	//HOMEB - Contact
	s8sod	ps8_msg_contact						[UI_TAILLE_MAX_MESSAGE];

	//DICTIONNAIRE
	s8sod	ps8_msg_parametre					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_valeur						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_oui							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_code						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_niveau_de_gravite			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_libelle						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_indetermine					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_critique					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_majeur						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mineur						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_avertissement				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_off							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_on							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_retours_liens_etat_cfg		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_retours_liens_modif_cfg		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarme_majuscule			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarme_minuscule			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_erreur						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_statut						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_statut_historique			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_langue[NB_MAX_LANGUES][UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_indisponible				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_systeme						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_page						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_manuel						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_manuelle					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_automatique					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_canalisation				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_selection					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_present						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_absent						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_presente					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_absente						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_generale					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_numero						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alert_configuration_non_autorisee[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_utilise_M				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_utilise_m				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_utilise_m					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_haut						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_bas							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_option_indisponible			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_en_cours					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_Inst						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_Min							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_Max							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_p_inst_p					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_p_min_p						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_p_max_p						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_inst						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_min							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_max							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_tous						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_aucun						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_action						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_inactif_M					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_actif_M						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_inactif_m					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_actif_m						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nom							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_equipement_non_connecter_reactualiser	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_programme					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_reseau						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_commande					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_designation					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_reference_commerciale		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_materielle					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_logicielle					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_disponible_M				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_erreur_configuration		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_depuis						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_en_secondes					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_normale_m					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_secours_m					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_normale_M					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_secours_M					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_entree						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_superviser					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_automatique	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_niveau						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_analyse						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_octets						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_debits						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_pour_effacer_les_alarmes	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cliquer_ici					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_standard					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_secondes					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_m						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_M						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_supprimer					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ajouter						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_effacer						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_connectee_M					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_connectee_M				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_MAC					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_from						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_to							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_autorise					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_commentaire					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_date_dernier_reset			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_critere						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_M						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_modifier					[UI_TAILLE_MAX_MESSAGE];


	//BOITES
	s8sod	ps8_msg_valider						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_valider_court				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_annuler						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_valider_formulaire			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ok							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_bouton_precedent			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_valider_et_suivant			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_bouton_suivant				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_executer					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_stopper						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_demarrer					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_se_connecter				[UI_TAILLE_MAX_MESSAGE];

	//Pages d'info
	s8sod	ps8_msg_maj_info_en_cours				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_error_query						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_config_ok						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_config_ko						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_actif_mode						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_pas_information					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_page_indisponible				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_reactualiser_page				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_reset_equipement_en_cours		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_chargement_en_cours				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_chargement_termine				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_page_indisponible_en_mode_local	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_acces_base_donnees_impossible	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seulement_mode_station_router	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seulement_mode_station			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_en_cours			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_veuillez_patienter				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_disponible_en_mode_monitor	[UI_TAILLE_MAX_MESSAGE];
	
	//Javascript
	s8sod	ps8_msg_cette_valeur_dt_etre_nombre				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cette_valeur_dt_etre_sup_egale			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cette_valeur_dt_etre_inf_egale			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cette_valeur_dt_etre_entier				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_n_est_pas_adresse_valide				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_n_est_pas_masque_valide					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_interdiction_utiliser_signe			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_dans_texte							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_champs_ne_pt_etre_laisse_vide		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_pas_d_alarme							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_pas_d_alarme							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cette_valeur_dt_etre_nombre_avec_pas_de	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_n_est_pas_adresse_multicast_valide		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cette_valeur_prendre_les_valeurs_suivantes		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_valide								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_caractere_non_valide					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_cette_valeur_n_est_pas_autorisee		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_n_est_pas_adresse_mac_valide			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_la_passerelle_n_est_pas_dans_sous_reseau[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip_ou_masque_ou_passerelle_est_invalide[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_caractere_espace_non_valide			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip_et_masque_non_valides		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_reseau_LAN_WLAN_dvt_etre_different [UI_TAILLE_MAX_MESSAGE];
	
	//Page d'Accueil
	s8sod	ps8_msg_sous_titre_accueil				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_description						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_d_equipement				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_identifiant_equipement			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_localisation_equipement			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_generale			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_alarmes_activees			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_aucune_alarme_activee			[UI_TAILLE_MAX_MESSAGE];
	
	//Page Menu Administration - Sécurité 
	s8sod	ps8_msg_mot_passe						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_adm_securite			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_ancien_mot_passe					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nouveau_mot_passe				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_confirmer_mot_passe				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_modification_mot_passe			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_valider_mot_de_passe				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_duree_max_connexion				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_duree_max_cx			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_duree							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nombre_max_clients				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_minutes							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nombre_invalide					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_duree_invalide					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_confirmation_differents			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mauvais_mot_passe				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_securisation_snmp				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_securisation_snmp1	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_sous_titre_securisation_snmp2	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_configuration_securise_SET		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_droits_insuffisants				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_trop_clients						[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Administration - SUTime
	s8sod	ps8_msg_configuration_date				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_mise_a_heure			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mah_systeme_PC					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_heure							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_date							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_heures							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_annee							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mois							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_jour							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_minute							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seconde							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_heure_reset						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_attention						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_date_heure_format				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_date_et_heure_ut				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mah_manuel						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mah_manuel_sous_titre			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_selection_mise_a_heure			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_mise_a_heure				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mah[NB_MAX_MODES_MAH]		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_serveur_ntp				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_serveur_ntp_secours		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_fuseau_horaire					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_error_mah_manuel				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_aucun_serveur_NTP				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_notation_heure					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_freq_mah_sntp					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_date_demarrage	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info_perte_heure_sur_am_equipement	[UI_TAILLE_MAX_MESSAGE_2];

	//Page Menu Administration - Identification (SUAdmIdentification)
	s8sod	ps8_msg_sous_titre_identification		[UI_TAILLE_MAX_MESSAGE_2];

	//Page Menu Administration - Controle (SUAdmControle)
	s8sod	ps8_msg_sous_titre_controle								[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_sous_titre_warning_reset_gestion				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_redemarrage_equipement							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_confirmer_redemarrage_equipement				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_pilotage		[NB_MAX_MODES_PILOTAGES][UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_pilotage									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_verrouillage_clavier							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_restaurer_configuration_par_defaut				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sauf_adresse_ip_masque_et_passerelle			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_etes_vous_sur_de_restaurer_configuration_par_defaut		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_avertissement_restauration_config_defaut			[UI_TAILLE_MAX_MESSAGE_2];
//d: BE065.1 02/05/2012 (CM) - Correction libellé dans page Html Administration - Controle
//	s8sod	ps8_msg_information_mots_de_passes_par_defaut			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_information_config_par_defaut					[UI_TAILLE_MAX_MESSAGE_2];
//f: BE065.1 02/05/2012 (CM) - Correction libellé dans page Html Administration - Controle
	s8sod	ps8_msg_confirmer_raz_generale							[UI_TAILLE_MAX_MESSAGE_2];

	//Page Menu Administration - Langue (SUAdmlangue)
	s8sod	ps8_msg_sous_titre_SUAdmLangue		[UI_TAILLE_MAX_MESSAGE_2];

	//Page Menu Administration - Rafraichissement (SUAdmRefresh)
	s8sod	ps8_msg_sous_titre_SUAdmRefresh					[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_temps_rafraichissement_minimum			[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Administration - Systemlog (SUAdmSystemLog)
	s8sod	ps8_msg_journal_system						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_adm_journal_system				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUAdmSystemLog			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_activation_journal_system			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation_mode_rssi				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip_distant_journal_system	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_distant_journal_system			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_rssi_non_fonctionnel_si_wifi_non_secu		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adress_ip_distant_doit_etre_non_nul_en_mode_rssi	[UI_TAILLE_MAX_MESSAGE];
	
	//Page Menu Administration - Versions Logicielles (VAdmVersionsLogicielles)
	s8sod	ps8_msg_sous_titre_versions_logicielles	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_sous_titre_versions_logicielles_et_options	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_version_logicielle				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nom_logiciel[NB_MAX_VERSIONS_LOGICIELLES]		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_boot							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_des_options				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_option						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nom_option[NB_MAX_OPTIONS]		[UI_TAILLE_MAX_MESSAGE];

	//Page Events - SUEvt
	s8sod	ps8_msg_sous_titre_VListeEvt				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_TRAP								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigEvt				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_choix_actions						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_SNMP_TRAP							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_retours_a_la_page					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_evenement_indisponible				[UI_TAILLE_MAX_MESSAGE];

	//Msg Console pour Telechargement
	s8sod	ps8_msg_logiciel_detecte					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_effacement_flash_impossible			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_effacement_flash_ko_time_out_expire	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ecriture_flash_ko_time_ou_expire	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ecriture_flash_ko_code_1			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ecriture_flash_ko_code_2			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_entete_fichier_ko					[UI_TAILLE_MAX_MESSAGE];

	//Equipement
	s8sod	ps8_msg_radio_modem							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_equipement			[UI_TAILLE_MAX_MESSAGE];

	//page HomeB - navigation
	s8sod	ps8_msg_synoptique						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_synoptique					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametres_RF					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_parametres_RF			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametres_ASI					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_parametres_ASI			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_entrees_sorties_mpeg_ts			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_entrees_sorties_mpeg_ts	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_limites_dvb						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_profils_dvb						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_limites_dvb				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_profils_dvb				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_DVBH							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_DVBH					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_multiplex						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_multiplex				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_qualite_service					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_qualite_service		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_marquage						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_marquage				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_SFN								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_sfn					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_video					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_parametres_rf			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_parametres_asi			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_sfn					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_DVBH					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sorties_asi						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_sorties_asi				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_scanning_rf						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_scanning_rf				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_analyse_MPEG_TS					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_multiplex				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_multiplex_simplifiee	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_services						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_services					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_PIDs							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_PIDs						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_tables							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_tables						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_pcr								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_pcr						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ecm_emm							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_ecm_emm					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_tr101290						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_tr101290_complete		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_tr101290_simplifiee	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_qualite_service		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_controle_marquage				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_controle_marquage		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_dvb_h							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_dvb_h						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_langue							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_langue						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_rafraichissement				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_rafraichissement			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_traps							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_traps						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_alarmes					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_table_alarmes				[UI_TAILLE_MAX_MESSAGE_2];

	//Page Menu Configuration - Paramètres RF
	s8sod	ps8_msg_sous_titre_SUconfigRF			[UI_TAILLE_MAX_MESSAGE_2];
	
	//page menu Exploitation - Etat de configuration
	s8sod	ps8_msg_sous_titre_etat_config_equipement		[UI_TAILLE_MAX_MESSAGE_2];

	//page menu Exploitation - Paramètres RF
	s8sod	ps8_msg_sous_titre_V_vexploitrf			[UI_TAILLE_MAX_MESSAGE_2];
	
	//page menu Evenements - Journal de bord
	s8sod	ps8_msg_journal_de_bord						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_journal_de_bord				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nb_elements_a_purger_si_jdb_plein	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_effacer_jdb							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_est_tu_sur_effacer_jdb				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_debut								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_fin									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nombre_d_evenements_dans_jdb		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nombre_d_evenements_affiches_jdb			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_VJdbEvt_avec_liens_1000_evts		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_nb_max_evts_par_page_html			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_actions_sur_fichier_jdb				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_generer_jdb							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_est_tu_sur_generer_jdb				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_affichage_jdb						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_avertissement_affichage_jdb_actif	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_affichage_des_evenements			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_affichage_evts_fonction_valeur_tsid	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_affichage_evts_fonction_entree		[UI_TAILLE_MAX_MESSAGE];

	//TRAPs
	s8sod	ps8_msg_sous_titre_Vtrap				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_alarmeV1Index					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarmeV1Id						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarmeV1Valeur					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarmeV1Statut					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarmeV1Date					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarmeV1Heure					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alarmeV1Acquit					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_statut_alarme_on				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_statut_alarme_off				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_statut_info						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_val_non_acquitter				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_val_acquitter					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_val_supprimer					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_acquitter_tous_les_traps		[UI_TAILLE_MAX_MESSAGE];

	//Divers
	s8sod	ps8_msg_commande_raz_generale			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_reset_jdb_qualite_service		[UI_TAILLE_MAX_MESSAGE];

	//FTP
	s8sod	ps8_msg_ftp_erreur_longueur					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_mode_local				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_valeur					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_mode_regul_auto			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_config_systeme_1_plus_1	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_adresse_ip				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_alarme_ros				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_erreur_nb_sts_id_par_pipe		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_configuration_ok				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_configuration_ko				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_configuration_en_cours			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_telechargement_de				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ftp_checksum_fichier_ko				[UI_TAILLE_MAX_MESSAGE];

	//Page menu configuration - Mode
	s8sod	ps8_msg_show_mode_radio_modem				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_radio_modem					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUconfigMode				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_choix_mode_radio_m[NB_MAX_MODES_RADIO_MODEM]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_radio_M[NB_MAX_MODES_RADIO_MODEM]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_confirmer_changement_radio_modem	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_changement_radio_modem_non_autorise	[UI_TAILLE_MAX_MESSAGE_2];

	//Page menu configuration - Network
	s8sod	ps8_msg_show_cfg_reseau						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigNetwork			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_infohtml_access_point_bridge		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_infohtml_station_bridge_router		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_infohtml_monitor_bridge				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_parametrage_mode_reseau				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_reseau							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_reseau[NB_MAX_MODES_NETWORK]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_reseau_bridge			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_reseau_LAN				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_reseau_WLAN				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_mac_ethernet				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_mac_wifi					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip_ethernet					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip_wifi						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_ip								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_ip[NB_MAX_MODES_IP]		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_masque_sous_reseau					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_passerelle							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_erreur_changement					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configurer_maintenant				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_avertissement_changement_adresse_ip	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_choix_interface_non_detecte[NB_MAX_INTERFACES]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_hostname				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_hostname							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ip_repli_dhcp						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ip_dhcp_repli_invalide				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_vlan					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation_vlan						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nom_vlan							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_id_vlan								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_conserver_acces_lan_non_tagge		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_spanning_tree_protocol				[UI_TAILLE_MAX_MESSAGE];

	//Page menu configuration - Wifi (Basic)
	s8sod	ps8_msg_wifi								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_wifi						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigWireless			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_parametrage_basique_wifi			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_avance_wifi				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_antennes				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_SSID								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation_ssid_secondaire			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_SSID_secondaire						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_masquer_ssid						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_802_11							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_intervalle_garde					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_intervalle_garde[NB_MAX_TYPE_GUARD_INTERVAL]					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_largeur_spectre_canal				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_canal							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_canal								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_canal[NB_MAX_TYPE_SELECTION_CANAL]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_puissance_emetteur					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_debit_donnees						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_reception						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nombre_maximum_stations_associees	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_securite_wifi					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mode_securite						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_securite_wifi[NB_MAX_MODES_SECURITE_WIFI]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_WEP									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_longueur_cle_WEP					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_longueur_cle_WEP[NB_MAX_WEP_KEY_LENGTH][UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_cle_WEP						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_type_cle_WEP[NB_MAX_KEY_TYPE]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info_saisie_cle_WEP[NB_MAX_WEP_KEY_LENGTH][NB_MAX_KEY_TYPE]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cle_WEP								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_la_valeur_de_la_cle_est_invalide	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_longueur_appliquee_a_toutes_les_cles[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_applique_a_toutes_les_cles		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_afficher_toutes_les_cles_WEP		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cle_WEP_par_defaut					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_authentification					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_authentification_WEP[NB_MAX_WEP_AUTHENTIFICATION]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_WPA									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_authentification_WPA[NB_MAX_WPA_AUTHENTIFICATION]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_intervalle_mise_a_jour_cle_wpa		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_cle_PSK						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_PSK									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_EAP									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info_saisie_PSK[NB_MAX_KEY_TYPE]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cle_pre_partagee					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_afficher_cle_PSK					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configurez_un_canal_valide			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_reauthentification_period		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info_sup_eap_reauth_period			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_ip_serveur_radius			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_serveur_radius					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_cle_serveur_radius					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_method							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_EAP_methode[NB_MAX_EAP_METHOD][UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_identity						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_user_name						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_user_password					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_certificat_autorite				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_certificat_client				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_private_key_password			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_supprimer_certificat			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_eap_aucun_certificat_selectionne			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_etes_vous_sur_de_supprimer_ce_certificat	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_avertissement_eap_tls_certificat		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_afficher_cle_EAP					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_puissance_configuree_au_minimum		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_debit_configure_en_automatique		[UI_TAILLE_MAX_MESSAGE];

	//Page menu configuration - Wifi (Avancé)
	s8sod	ps8_msg_timeout_ACK							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_preambule						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_type_preambule[NB_MAX_WF_TYPE_PREAMBULE]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_fragmentation					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_RTS_CTS						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_limitation_retransmission_RTS		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_periode_beacon						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation_wmm						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_desactivation_DFS					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_code_pays							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_country_id[NB_MAX_COUNTRY_ID]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_avertissement_modification_code_pays	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_etes_vous_sur_de_configurer_nouveau_code_pays	[UI_TAILLE_MAX_MESSAGE_2];
	
	//Page menu configuration - Wifi (Antennes)
	s8sod	ps8_msg_selection_antenne					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_selection_antenne_tx				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ABG_choix_antenne_tx[NB_MAX_ABG_SELECT_ANT_TX]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_selection_antenne_rx				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ABG_choix_antenne_rx[NB_MAX_ABG_SELECT_ANT_RX]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_N_choix_antenne[NB_MAX_N_SELECT_ANTENNES]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_antenne_non_autorisee		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_antenne_1						[UI_TAILLE_MAX_MESSAGE];

	//Page menu configuration - Hand-Off
	s8sod	ps8_msg_hand_off							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_cfg_hand_off					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigHandoff			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_mode_scanning						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_mode_scanning[NB_MAX_HO_MODES_SCANNING]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_du_scanning_background	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation_scanning_background		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_periode_scanning_background			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_niveau_rx_declenchant_scan_bg	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_du_scanning_foreground	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_niveau_rx_declenchant_scan_fg			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_de_nb_beacon_rx_perdus_declenchant_scan_fg	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_du_hand_off_sur_meme_canal	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_seuil_niveau_rx_iso_declenchant_handoff		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_seuil_de_nb_beacon_rx_declenchant_handoff	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_intervalle_temps_entre_2_handoff	[UI_TAILLE_MAX_MESSAGE];
//d: BE059 16/02/2011 CM - Ajout filtrage rssi pour fast roaming
	s8sod	ps8_msg_parametrage_filtrage_rssi			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_filtre							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_type_filtre[NB_MAX_TYPES_FILTRAGE_RSSI]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_intervalle_temps_entre_2_beacon		[UI_TAILLE_MAX_MESSAGE];
//f: BE059 16/02/2011 CM - Ajout filtrage rssi pour fast roaming
	
	//Page menu configuration - IP routing
	s8sod	ps8_msg_routage_IP							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_routage_IP						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigRouting			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_detail_onglet_SUConfigRoutingGene	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_detail_onglet_SUConfigRoutingStatic	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_detail_onglet_SUConfigRoutingPolitic[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_routage_ip_statique_est				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_routes_actives				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_routage_ip_statique			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ajouter_route						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_destination							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_metric								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_interface							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_interfaces_ip[NB_MAX_INTERFACES]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_il_faut_selectionner_interface_route[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_routage_statique_complete		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_route_vers_un_host_invalide			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_route_vers_sous_reseau_invalide		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_routes_politiques_actives		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_aucune_route_politique_activee		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_routage_general 					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_routage_statique					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_politique_routage					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_politique_routage				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ajouter_route_politique				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_modifier_route_politique			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_politique_routage_complete	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nom_route_politique					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_source_ip							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_destination_ip						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_longueur_paquet						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_protocole_ip						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_source							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_destination					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_class_selector						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nouvelle_passerelle					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_nouvelle_class_selector				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_routepolicy_protocole[NB_MAX_POLICYROUTE_PROTOCOLES]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_class_selector[NB_MAX_CLASSSELECTOR]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_erreur_saisie_critere[NB_MAX_CRITERIA_POLICY]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_erreur_saisie_action[NB_MAX_ACTIONS_POLICY]		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_selectionner_un_critere_et_une_action	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_criteres_selectionnes			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_actions_selectionnees			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_routage_rip							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_detail_onglet_SUConfigRoutingRip	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_activation_rip						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_interfaces_utilises_par_rip			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_interfaces_disponibles				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_interfaces_rip						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_interfaces_rip[NB_MAX_RIP_INTERFACES]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_authentification_rip[NB_MAX_RIP_AUTHENTICATION]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alert_add_interf					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alert_remove_interf					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_il_faut_selectionner_interface_rip	[UI_TAILLE_MAX_MESSAGE];

	//Page menu configuration - Serveur/Relai DHCP
	s8sod	ps8_msg_serveur_relai_dhcp					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_serveur_relai_dhcp				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigDHCP				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_info_sur_dhcp_serveur				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_info_sur_dhcp_relai					[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_fonction_dhcp						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_fct_dhcp[NB_MAX_FCT_DHCP]		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_serveur_dhcp			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_plage_adresse_ip_dhcp				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresses_dans_sous_reseau_lan		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_duree_bail_dhcp						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_parametrage_relai_dhcp				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_dhcp_relai_ip_cible					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_adresse_dhcp_FROM_pas_dans_LAN	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_adresse_dhcp_TO_pas_dans_LAN		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_adresse_dhcp_FROM_invalid		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_plage_adresse_dhcp_FROM_TO_invalid	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_js_plage_adresse_dhcp_broadcast_invalid	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_js_plage_adresse_dhcp_exceed_limit_max	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_serveur_DHCP_non_fonctionnel[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_relai_DHCP_non_fonctionnel[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Configuration - NAT
	s8sod	ps8_msg_NAT									[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_NAT							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigNat				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_activation_NAT						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_regles_nat_actives			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_prive							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_IP_privee					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_public							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_IP_publique					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_IP_publique_par_defaut		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ajouter_regle_NAT_port_forwarding	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ajouter_regle_NAT_mapping_adresse	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_port_forwarding						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_protocole							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_nat_protocole[NB_MAX_NAT_PROTOCOLES]		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_alias_IP								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_regles_port_forwarding_complete	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_regles_mapping_adresses_complete	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_mapping_adresses					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_il_faut_selectionner_un_protocole	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_nat_non_appliquee		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_NAT_non_fonctionnelle	[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Configuration - Multicast
	s8sod	ps8_msg_Multicast							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_Multicast						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_SUConfigMulticast		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_activation_proxy_igmp				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_sources_multicast_autorisees	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_ajouter_source_multicast_autorisee	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_table_source_multicast_complete		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_source_invalide						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_reseau						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_masque_reseau						[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Configuration - SNMP
	s8sod	ps8_msg_sous_titre_SUConfigSnmp			[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_communautes						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_managers_snmp					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_manager_snmpv1		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_sous_titre_manager_snmpv2c		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_libelles						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_adresse_internet_ip				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_emission_traps	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_emission_traps					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_configuration_emission_traps_informs	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_emission_traps_informs					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info_emission_trapv2			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_rejouer_traps_presents			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_activation_signe_vie			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_temporisation_signe_vie			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_protocole_emission_traps		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_snmp_prctl_traps		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_protocole_emission_informs		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_snmp_prtcl_inform	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_nombre_emission					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_intervalle_reemission			 [UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_info_ack_trapv1					[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_selection_version_snmp			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_version_snmp					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_version_snmp[NB_MAX_VERSIONS_SNMP]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_type_notification				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_type_notification[NB_MAX_TYPES_NOTIFICATION]	[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Exploitation - Wifi
	s8sod	ps8_msg_sous_titre_VExploitWifi_station	[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_sous_titre_VExploitWifi_ap		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_show_exp_wifi					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_BSSID							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_RSSI							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_station_connexion[NB_MAX_STATUT_CONNEXION]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_clients_wifi_associes		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_associe							[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_non_associe						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_connection_wpa_active			[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_canal_utilise					[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Exploitation - Générale
	s8sod	ps8_msg_sous_titre_VExploitGeneral		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_show_exp_general				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_temperature						[UI_TAILLE_MAX_MESSAGE];
	
	//Page Menu Exploitation - Réseau
	s8sod	ps8_msg_sous_titre_VExploitNetwork		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_show_exp_reseau					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_dhcp_en_cours_sur_acces_wlan		[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_statut_ip						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_choix_statut_ip[NB_MAX_STATUTS_IP]		[UI_TAILLE_MAX_MESSAGE];

	//Page Menu Exploitation - client DHCP
	s8sod	ps8_msg_dhcp_clients						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_VExploitDhcpClient		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_show_exp_dhcp_client				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_liste_clients_dhcp					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_bail_restant						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_aucun_client_dhcp					[UI_TAILLE_MAX_MESSAGE];
	
	
	//page menu Alarmes - Liste des alarmes
	s8sod	ps8_msg_lib_groupe_alarmes	[NB_MAX_GROUPES]	[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_sous_titre_Vliste_alarmes				[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_sous_titre_Vliste_groupe_alarmes[NB_MAX_GROUPES]		[UI_TAILLE_MAX_MESSAGE_2];
	s8sod	ps8_msg_effacer_toutes_les_alarmes				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_voir									[UI_TAILLE_MAX_MESSAGE];
	
	//page menu Evenements - Configuration des événements
	s8sod	ps8_msg_validation_jdb_trap				[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_jdb								[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_validation						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_synthese						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_synthese_1_a_3					[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_synthese_1						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_synthese_2						[UI_TAILLE_MAX_MESSAGE];
	s8sod	ps8_msg_synthese_3						[UI_TAILLE_MAX_MESSAGE];

	//Libellés des Evenements
	s8sod	ps8_msg_lib_evenement[NB_MAX_EVENEMENTS][UI_TAILLE_MAX_MESSAGE];

	//Libellés supplémentaires sur les évènements
	s8sod	ps8_msg_lib_errorconfig[NB_MAX_ERRORCONFIG][UI_TAILLE_MAX_MESSAGE];
	
} S_TYPE_MESSAGE;
/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______VI - CONSTANTES ET VARIABLES ______________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
