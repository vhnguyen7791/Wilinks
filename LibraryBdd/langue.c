/*========================================================================*/
/* NOM DU FICHIER  : langue.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/06/2007                                           */
/* Libelle         : Base de donn�es: langue							  */
/* Projet          : WRM100                                               */
/* Indice	       : BE065												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Modification javascript isValidText
// - Int�gration configuration hostname
// - Ajout exploitation adresse IP/Mask des interfaces
//BE005 14/01/2010 CM
// - Int�gration serveur DHCP + relai DHCP
//BE007 25/01/2010 CM
// - Ajout exploitation de l'ACCESS POINT
// - Modification gestion routage statique
//BE008 28/01/2010 CM
// - Modification page HTML langue (+g�n�rique)
// - Ajout syslog: journalisation du syst�me
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
// - Correction test configuration des adresses IP des interfaces
// - Ajout information statut IP des interfaces
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE018 15/03/2010 CM
// - Correction libell� page HTML Configuration - Mode
// - Correction libell� page HTML Configuration - DHCP
//BE019 16/03/2010 CM
// - Correction libell�s page HTML Configuration - SNMP
// - Autorisation de passer la station en bridge
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE032 16/06/2010 CM
// - Correction libell� du bouton "Valider" sur la page HTML password
// - Ajout gestion Radius / WPA - EAP
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
// - Ajout gestion des �v�nements sp�cifiques � l'�quipement
// - Ajout exploitation temperature 
// - Modification page HTML Admin - Controle pour red�marrer �quipement
// - Modification page HTML Admin - Controle pour raz g�n�rale
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
// - Correction libell� seuil niveau rx
//		"Seuil de l'alarme niveau re�u"
//BE040 13/09/2010 CM
// - Ajout des param�tres de configuration hand-off
// - Integration de la gestion du wifi pour la carte compatible � 802.11n
//BE042 07/10/2010 CM
// - Ajout param�tre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
// - Correction libell� fr diversite + relais
// - Correction configuration mode 802.11 (associ� au driver-N)
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque acc�s
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non valid�e par d�faut
//	+ aussi disponible sur ACCESS POINT
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE048 29/11/2010 CM
// - Correction libell� fr erron� 
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
// - Modification mode scanning (handoff)
// - Correction libell� handoff
// - Correction libell� javascript avertissement chaine vide
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
// - Ajout valeur PEAP/MSCHAPv2 dans authentification EAP (Radius)
// - Modification valeur antennes TX / RX
//		"antennes 1 & 2" au lieu de "antennes 1 & 3" 
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activ�)
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
//BE054 11/01/2011 CM
// - Ajout gestion mode monitor
// - Correction libelle gb alarms list avec s
// - Correction libelle tiroir --> equipement
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout dans exploitation du canal en cours (sur AP et STA)
// - Ajout nouveaux �v�nements li�s au DFS
// - Ajout configuration "desactivation DFS" (WRM100-N)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout des �venements de connexion et d�connexion d'une STATION
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout configuration date/heure au d�marrage de l'�quipement
//BE065.0 14/03/2012 (CM)
// - Correction bug libell� "LAN Ethernet 1/2 alarm" (GB)
//BE065.1 02/05/2012 (CM)
// - Correction libell� GB HTML
//		->	"ou" � la place de "or" (dans page Configuration - Network)
//		->	Majuscule pour "Filter type" (dans page Configuration - Hand-off)
// - Correction libell� dans page Html Administration - S�curit�
// - Correction libell� dans page Html Administration - Controle
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define	_LANGUE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/


// Initialisation des variables contenant les messages en Fran�ais et Anglais
//   STOCKEE EN RAM !!
S_TYPE_MESSAGE t_tb_msg [NB_MAX_LANGUES] =	
{
// Messages en Fran�ais:

	//********************************************************************
	/////////////////////////rep�re : debut fran�ais
	//********************************************************************
	
	{
		//HOMEB - Accueil + Actualiser
		"Accueil",																		/*ps8_msg_accueil*/
		"Page d\\'accueil",																/*ps8_msg_show_accueil*/
		"Actualiser",																	/*ps8_msg_actualiser*/
		"Actualiser la page courante",													/*ps8_msg_show_actualiser*/
		//HOMEB - Menu Administration
		"Administration",																/*ps8_msg_administration*/
		"Identification",																/*ps8_msg_identification*/
		"Page d\\'Identification de l\\'�quipement",											/*ps8_msg_show_identification*/
		"Contr�le",																		/*ps8_msg_controle*/
		"Red�marrage de l\\'�quipement et Mode de pilotage (local ou distant)",			/*ps8_msg_show_controle*/
		"S�curit�",																		/*ps8_msg_securite*/
		"Page pour s�curiser l\\'acc�s � l\\'�quipement",								/*ps8_msg_show_securite*/
		"Mise � l'heure",																/*ps8_msg_mise_a_heure*/
		"Mise � l\\'heure de l\\'�quipement",													/*ps8_msg_show_mise_a_heure*/
		"Versions Logicielles",															/*ps8_msg_versions_logicielles*/
		"Informations sur les versions logicielles de l\\'�quipement",					/*ps8_msg_show_versions_logicielles*/
		"Versions Logicielles / Options",												/*ps8_msg_versions_logicielles_et_options*/
		"Informations sur les versions logicielles et les options de l\\'�quipement",	/*ps8_msg_show_versions_logicielles_et_options*/
		"T�l�chargement",																/*ps8_msg_telechargement*/
		"Statut du t�l�chargement",														/*ps8_msg_show_telechargement*/
		//HOMEB - Menu R�seau
		"R�seau de supervision",														/*ps8_msg_reseau_de_supervision*/
		"Etat de configuration",														/*ps8_msg_etat_de_configuration*/
		"Visualisation de l\\'�tat de configuration de l\\'�quipement",					/*ps8_msg_show_modification_de_configuration*/
		"Modification de configuration",												/*ps8_msg_modification_de_configuration*/
		"Modification de la configuration de l\\'�quipement",							/*ps8_msg_show_etat_de_configuration*/
		"Adresses IP",																	/*ps8_msg_Adresses_Ip*/
		"Configuration des adresses IP",												/*ps8_msg_show_Adresses_Ip*/
		"Adresse IP",																	/*ps8_msg_Adresse_Ip*/
		"Configuration de l\\'adresse IP",												/*ps8_msg_show_Adresse_Ip*/
		"Routage IP",																	/*ps8_msg_Routage_Ip*/
		"Configuration du routage IP",													/*ps8_msg_show_Routage_Ip*/
		"SNMP",																			/*ps8_msg_SNMP*/
		"Configuration SNMP",															/*ps8_msg_show_SNMP*/
		//HOMEB - Menu Exploitation
		"Exploitation",																	/*ps8_msg_exploitation*/
		//HOMEB - Menu Alarmes
		"Alarmes",																		/*ps8_msg_alarmes*/
		"Liste des alarmes",															/*ps8_msg_liste_alarmes*/
		"Consultation des alarmes",														/*ps8_msg_show_liste_alarmes*/
		//HOMEB - Menu Evenements
		"Ev�nements",																	/*ps8_msg_evenements*/
		"Liste des �v�nements",															/*ps8_msg_list_evenements*/
		"Configuration des �v�nements (niveau de gravit�, TRAP, ..)",					/*ps8_msg_show_list_evenements*/
		"Param�trage",																	/*ps8_msg_parametrage_evenements*/
		"Param�trage des �v�nements (niveau de gravit�, TRAP, ..)",						/*ps8_msg_show_parametrage_evenements*/
		//HOMEB - Contact
		"Contact",																		/*ps8_msg_contact*/

		//DICTIONNAIRE
		"Param�tre",													/*ps8_msg_parametre*/
		"Valeur",														/*ps8_msg_valeur*/
		"Oui",															/*ps8_msg_oui*/
		"Non",															/*ps8_msg_non*/
		"Code",															/*ps8_msg_code*/
		"Niveau de gravit�",											/*ps8_msg_niveau_de_gravite*/
		"Libell�",														/*ps8_msg_libelle*/
		"Ind�termin�",													/*ps8_msg_indetermine*/
		"Critique",														/*ps8_msg_critique*/
		"Majeur",														/*ps8_msg_majeur*/
		"Mineur",														/*ps8_msg_mineur*/
		"Avertissement",												/*ps8_msg_avertissement*/
		"Configuration",												/*ps8_msg_configuration*/
		"Off",															/*ps8_msg_off*/
		"On",															/*ps8_msg_on*/
		"Retour � la page des liens d'Etat de configuration",			/*ps8_msg_retours_liens_etat_cfg*/
		"Retour � la page des liens de Modification de configuration",	/*ps8_msg_retours_liens_modif_cfg*/
		"Alarme",														/*ps8_msg_alarme_majuscule*/
		"alarme",														/*ps8_msg_alarme_minuscule*/
		"Erreur",														/*ps8_msg_erreur*/
		"Statut",														/*ps8_msg_statut*/
		"Statut historique",											/*ps8_msg_statut_historique*/
		{//ps8_msg_choix_langue[NB_MAX_LANGUES]
			"francais",	//LANGUE_FRANCAIS
			"anglais",	//LANGUE_ANGLAIS
		},
		"Indisponible",													/*ps8_msg_indisponible*/
		"Syst�me",														/*ps8_msg_systeme*/
		"Page",															/*ps8_msg_page*/
		"Manuel",														/*ps8_msg_manuel*/
		"Manuelle",														/*ps8_msg_manuelle*/
		"Automatique",													/*ps8_msg_automatique*/
		"Canalisation",													/*ps8_msg_canalisation*/
		"Activation",													/*ps8_msg_activation*/
		"S�lection",													/*ps8_msg_selection*/
		"Pr�sent",														/*ps8_msg_present*/
		"Absent",														/*ps8_msg_absent*/
		"Pr�sente",														/*ps8_msg_presente*/
		"Absente",														/*ps8_msg_absente*/
		"G�n�rale",														/*ps8_msg_generale*/
		"Num�ro",														/*ps8_msg_numero*/
		"Configuration non autoris�e!",									/*ps8_msg_alert_configuration_non_autorisee*/
		"Non utilis�",													/*ps8_msg_non_utilise_M*/
		"non utilis�",													/*ps8_msg_non_utilise_m*/
		"utilis�",														/*ps8_msg_utilise_m*/
		"Haut",															/*ps8_msg_haut*/
		"Bas",															/*ps8_msg_bas*/
		"Option indisponible",											/*ps8_msg_option_indisponible*/
		"en cours",														/*ps8_msg_en_cours*/
		"Inst",															/*ps8_msg_Inst*/
		"Min",															/*ps8_msg_Min*/
		"Max",															/*ps8_msg_Max*/
		"(inst.)",														/*ps8_msg_p_inst_p*/
		"(min.)",														/*ps8_msg_p_min_p*/
		"(max.)",														/*ps8_msg_p_max_p*/
		"inst",															/*ps8_msg_inst*/
		"min",															/*ps8_msg_min*/
		"max",															/*ps8_msg_max*/
		"Tous",															/*ps8_msg_tous*/
		"Aucun",														/*ps8_msg_aucun*/
		"Action",														/*ps8_msg_action*/
		"INACTIF",														/*ps8_msg_inactif_M*/
		"ACTIF",														/*ps8_msg_actif_M*/
		"Inactif",														/*ps8_msg_inactif_m*/
		"Actif",														/*ps8_msg_actif_m*/
		"Nom",															/*ps8_msg_nom*/
		"Equipement non connect�. R�actualiser",						/*ps8_msg_equipement_non_connecter_reactualiser*/
		"Programme",													/*ps8_msg_programme*/
		"R�seau",														/*ps8_msg_reseau*/
		"Commande",														/*ps8_msg_commande*/
		"D�signation",													/*ps8_msg_designation*/
		"R�f�rence commerciale",										/*ps8_msg_reference_commerciale*/
		"Mat�rielle",													/*ps8_msg_materielle*/
		"Logicielle",													/*ps8_msg_logicielle*/
		"Disponible",													/*ps8_msg_disponible_M*/
		"Erreur de configuration",										/*ps8_msg_erreur_configuration*/
		"Depuis",														/*ps8_msg_depuis*/
		"en secondes",													/*ps8_msg_en_secondes*/
		"Normale",														/*ps8_msg_normale_m*/
		"Secours",														/*ps8_msg_secours_m*/
		"NORMALE",														/*ps8_msg_normale_M*/
		"SECOURS",														/*ps8_msg_secours_M*/
		"Entr�e",														/*ps8_msg_entree*/
		"Superviser",													/*ps8_msg_superviser*/
		"Configuration auto",											/*ps8_msg_configuration_automatique*/
		"Niveau",														/*ps8_msg_niveau*/
		"Analyse",														/*ps8_msg_analyse*/
		"octets",														/*ps8_msg_octets*/
		"d�bits",														/*ps8_msg_debits*/
		"Pour effacer les alarmes",										/*ps8_msg_pour_effacer_les_alarmes*/
		"cliquer ici",													/*ps8_msg_cliquer_ici*/
		"standard",														/*ps8_msg_standard*/
		"secondes",
		"Mode",
		"MODE",
		"Supprimer",
		"Ajouter",
		"Effacer",
		"CONNECTEE",
		"NON CONNECTEE",
		"Adresse MAC",
		"de",
		"�",
		"Autoris�",
		"Commentaire",
		"Date du dernier RAZ",
		"Crit�re",
		"Non",
		"Modifier",

		//BOITES
		"     Valider     ",													/*ps8_msg_valider*/
		"Valider",																/*ps8_msg_valider_court*/
		"     Annuler     ",													/*ps8_msg_annuler*/
		"  Valider Formulaire  ",												/*ps8_msg_valider_formulaire*/
		"     Valider     ",													/*ps8_msg_ok*/
		"<- pr�c�dent",															/*ps8_msg_bouton_precedent*/
		"Valider et suivant ->",												/*ps8_msg_valider_et_suivant*/
		"suivant ->",															/*ps8_msg_bouton_suivant*/
		"Executer",																/*ps8_msg_executer*/
		"  Stopper   ",															/*ps8_msg_stopper*/
		"  D�marrer  ",															/*ps8_msg_demarrer*/
		"   Se connecter   ",													/*ps8_msg_valider*/

		//Pages d'info
		"Mise � jour des informations en cours ...",							/*ps8_msg_maj_info_en_cours*/
		"Erreur dans la requ�te",												/*ps8_msg_error_query*/
		"L'appareil est maintenant configur� avec les nouveaux param�tres",		/*ps8_msg_config_ok*/
		"Les param�tres de configuration saisis sont incorrects!",				/*ps8_msg_config_ko*/
		"mode actif = LOCAL EQUIPMENT, pas de modification autoris�e",			/*ps8_msg_actif_mode*/
		"Pas d'information",													/*ps8_msg_pas_information*/
		"Page Indisponible (param�tre inconnu) !",								/*ps8_msg_page_indisponible*/
		"R�actualiser la page!",												/*ps8_msg_reactualiser_page*/
		"Red�marrage de l'�quipement en cours ...",											/*ps8_msg_reset_equipement_en_cours*/
		"Chargement en cours ...",												/*ps8_msg_chargement_en_cours*/
		"Chargement termin� !",													/*ps8_msg_chargement_termine*/
		"Page indisponible en mode local !",									/*ps8_msg_page_indisponible_en_mode_local*/
		"Acc�s � la base de donn�es impossible !",
		"Seulement en STATION / ROUTER !",
		"Seulement en mode STATION !",
		"Configuration en cours.",
		"Veuillez patienter.",
		"Page indisponible en mode MONITOR !",

		//Javascript
		"Cette valeur doit �tre un nombre.",								/*ps8_msg_cette_valeur_dt_etre_nombre*/
		"Cette valeur doit �tre sup�rieure ou �gale �",						/*ps8_msg_cette_valeur_dt_etre_sup_egale*/
		"Cette valeur doit �tre inf�rieure ou �gale �",						/*ps8_msg_cette_valeur_dt_etre_inf_egale*/
		"Cette valeur doit �tre un entier.",								/*ps8_msg_cette_valeur_dt_etre_entier*/
		"n'est pas une adresse valide.",									/*ps8_msg_n_est_pas_adresse_valide*/
		"n'est pas un masque valide.",										/*ps8_msg_n_est_pas_masque_valide*/
		"Interdiction d\\'utiliser le signe",								/*ps8_msg_js_interdiction_utiliser_signe*/
		"dans le texte",													/*ps8_msg_js_dans_texte*/
		"Ce champs ne peut �tre laiss� vide.",								/*ps8_msg_js_champs_ne_pt_etre_laisse_vide*/
		"pas d\\'alarme",													/*ps8_msg_js_pas_d_alarme*/
		"pas d'alarme",														/*ps8_msg_pas_d_alarme*/
		"Cette valeur doit �tre un nombre avec un pas de",					/*ps8_msg_cette_valeur_dt_etre_nombre_avec_pas_de*/
		"n'est pas une adresse multicast valide.",							/*ps8_msg_n_est_pas_adresse_multicast_valide*/
		"Cette valeur doit prendre les valeurs suivantes:",					/*ps8_msg_cette_valeur_prendre_les_valeurs_suivantes*/
		"pas valid�e",														/*ps8_msg_non_valide*/
		"Ce texte contient un caract�re non valide.",						/*ps8_msg_js_caractere_non_valide*/
		"Cette valeur n\\'est pas autoris�e.",								/*ps8_msg_js_cette_valeur_n_est_pas_autorisee*/
		"n'est pas une adresse MAC valide.",								/*ps8_msg_n_est_pas_adresse_mac_valide*/
		"La passerelle n'est pas dans le sous-r�seau de l'interface.",
		"Adresse IP ou masque de sous-r�seau ou passerelle est invalide.",
		"Ce texte contient le caract�re \\'espace\\' non valide.",						/*ps8_msg_js_caractere_non_valide*/
		"Adresse IP ou masque de sous-r�seau est invalide.",
		"Les sous-r�seaux du LAN et du WLAN doivent �tre diff�rents.",
		
		//Page d'Accueil
		"Bienvenue sur le serveur WEB. Pour naviguer sur toutes les pages, utiliser le menu � gauche.",	/*ps8_msg_sous_titre_accueil*/
		"Description",											/*ps8_msg_description*/
		"Type d'�quipement",									/*ps8_msg_type_d_equipement*/
		"Identifiant de l'�quipement",							/*ps8_msg_identifiant_equipement*/
		"Localisation de l'�quipement",							/*ps8_msg_localisation_equipement*/
		"Configuration g�n�rale",								/*ps8_msg_configuration_generale*/
		"Liste des alarmes activ�es",							/*ps8_msg_liste_alarmes_activees*/
		"Aucune alarme activ�e",								/*ps8_msg_aucune_alarme_activee*/

		//Page Menu Administration - S�curit� 
		"Mot de passe",											/*ps8_msg_mot_passe*/
//d: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - S�curit�
//		"Cette page permet de modifier les mots de passe, la dur�e maximum de connexion sans activit� HTTP, le nombre maximum de clients et de s�curiser le serveur SNMP",	/*ps8_msg_sous_titre_adm_securite*/
		"Cette page permet de modifier les mots de passe, la dur�e maximum de connexion sans activit� HTTP et le nombre maximum de clients",	/*ps8_msg_sous_titre_adm_securite*/
//f: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - S�curit�
		"Ancien mot de passe",									/*ps8_msg_ancien_mot_passe*/
		"Nouveau mot de passe",									/*ps8_msg_nouveau_mot_passe*/
		"Confirmer le nouveau mot de passe",					/*ps8_msg_confirmer_mot_passe*/
		"Modification de mot de passe",							/*ps8_msg_modification_mot_passe*/
		"Valider mot de passe",									/*ps8_msg_valider_mot_de_passe*/
		"Dur�e maximum de connexion sans activit� HTTP",		/*ps8_msg_duree_max_connexion*/
		"Lorsque le temps de connexion sans activit� HTTP est atteint, l'acc�s au serveur WEB necessitera de saisir le mot de passe.",	/*ps8_msg_sous_titre_duree_max_cx*/
		"Dur�e",												/*ps8_msg_duree*/
		"Nombre maximum de clients",							/*ps8_msg_nombre_max_clients*/
		"minutes",												/*ps8_msg_minutes*/
		"Nombre maximum de clients invalide",					/*ps8_msg_nombre_invalide*/
		"Dur�e invalide",										/*ps8_msg_duree_invalide*/
		"Le nouveau mot de passe et la confirmation sont diff�rents",	/*ps8_msg_confirmation_differents*/
		"Mauvais mot de passe",									/*ps8_msg_mauvais_mot_passe*/
		"S�curisation du serveur SNMP",							/*ps8_msg_securisation_snmp*/
		"La configuration (SET) � partir d'un manager SNMP peut �tre s�curis�e.",	/*ps8_msg_sous_titre_securisation_snmp1*/
		"Si la s�curisation est valid�e, toute configuration (SET) n�cessitera la connexion au serveur HTTP.",	/*ps8_msg_sous_titre_securisation_snmp2*/
		"Configuration s�curis�e par SET",						/*ps8_msg_configuration_securise_SET*/
		"Droits d'acc�s insuffisants",							/*ps8_msg_droits_insuffisants*/
		"Trop de clients",										/*ps8_msg_trop_clients*/
		
		//Page Menu Administration - SUTime
		"Configuration Date et Heure",								/*ps8_msg_configuration_date*/
		"Cette page permet de mettre � l'heure l'�quipement.",		/*ps8_msg_sous_titre_mise_a_heure*/
		"Mise � l'heure de l'�quipement au syst�me PC",				/*ps8_msg_mah_systeme_PC*/
		"Heure",													/*ps8_msg_heure*/
		"Date",														/*ps8_msg_date*/
		"Heures",													/*ps8_msg_heures*/
		"Ann�e",													/*ps8_msg_annee*/
		"Mois",														/*ps8_msg_mois*/
		"Jour",														/*ps8_msg_jour*/
		"Minute",													/*ps8_msg_minute*/
		"Seconde",													/*ps8_msg_seconde*/
		"Une mise � l'heure entra�ne un reset de la carte",			/*ps8_msg_heure_reset*/
		"Attention",												/*ps8_msg_attention*/
		"JJ/MM/AAAA HH:MM:SS",										/*ps8_msg_date_heure_format*/
		"Date et heure UT : ",										/*ps8_msg_date_et_heure_ut*/
		"R�glage manuel",											/*ps8_msg_mah_manuel*/
		"Le r�glage manuel n'est utile que quand le serveur NTP est d�sactiv�.",	/*ps8_msg_mah_manuel_sous_titre*/
		"S�lection de la mise � l'heure",
		"Mode de la mise � l'heure",
		{//ps8_msg_choix_mah[NB_MAX_MODES_MAH]
			"Manuel",	 //MODE_MAH_MANUELLE
			"NTP",		//MODE_MAH_NTP
			"SNTP",		//MODE_MAH_SNTP
		},
		"Adresse du serveur NTP",									/*ps8_msg_adresse_serveur_ntp*/
		"Adresse du serveur NTP de secours",
		"Fuseau horaire",											/*ps8_msg_fuseau_horaire*/
		"R�glage manuel non autoris�, si le mode de mise � l'heure n'est pas manuel.",			/*ps8_msg_error_mah_manuel*/
		"Aucun serveur NTP n'a r�pondu",				/*ps8_msg_aucun_serveur_NTP*/
		"Notation de l'heure",										/*ps8_msg_notation_heure*/
		"Fr�quence de mise � jour SNTP [h]",								/*ps8_msg_freq_mah_sntp*/
		"Configuration de la date de d�marrage de l'�quipement",
		"La date et l'heure ne sont pas conserv�es sur Arr�t/Marche de l'�quipement.<BR>Il est possible de configurer la date de d�marrage.",

		//Page Menu Administration - Identification (SUAdmIdentification)
		"Cette page affiche les informations pour identifier l'�quipement.",	/*ps8_msg_sous_titre_identification*/

		//Page Menu Administration - Controle (SUAdmControle)
		"Cette page permet:<BR>  - d'effectuer un red�marrage de l'�quipement,<BR>  - d'effectuer un RAZ g�n�ral<BR>  - de restaurer la configuration par d�faut (uniquement en mode Super Utilisateur).",
		"Un red�marrage peut perturber la fonctionnalit� de l'�quipement",
		"Red�marrage de l'�quipement",
		"Etes-vous s�r de vouloir red�marrer l\'�quipement?",
		{//ps8_msg_choix_mode_pilotage[]
			"Mode Local",	//MODE_LOCAL,
			"Mode Distant",	//MODE_DISTANT,
		},
		"Mode de pilotage",
		"Verrouillage clavier",
		"Restaurer la configuration par d�faut",
		"sauf les param�tres IP et de la passerelle",
		"Etes-vous s�r de restaurer la configuration par d�faut de l'�quipement ?",
		"<B>Avertissement!</B> La restauration de la configuration par d�faut entra�ne un red�marrage de l'�quipement",
//d: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - Controle
//		"Avertissement! Les mots de passe seront reconfigur�s avec ceux par d�faut : low, middle, high!",
		"Tous les param�tres r�seaux et mots de passe seront r�initialis�s!",
//f: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - Controle
		"Etes-vous s�r de vouloir effectuer un RAZ g�n�ral?",

		//Page Menu Administration - Langue (SUAdmlangue)
		"Cette page permet de s�lectionner la langue de l'interface utilisateur.",

		//Page Menu Administration - Rafraichissement (SUAdmRefresh)
		"Cette page permet de configurer le rafra�chissement du contenu des pages HTML dynamiques.",
		"Temps de rafra�chissement minimum",

		//Page Menu Administration - Systemlog (SUAdmSystemLog)
		"Journal du syst�me",
		"Configuration du journal du syst�me",
		"Cette page permet de configurer la journalisation des messages du syst�me",
		"Activation du journal du syst�me",
		"Activation du mode RSSI",
		"Adresse IP distant", 
		"Port distant", 
		"Mode RSSI non fonctionnel avec aucune s�curit� Wifi.", 
		"L\'adresse IP distant ne doit pas �tre nulle en mode RSSI.", 
		
		//Page Menu Administration - Versions Logicielles (VAdmVersionsLogicielles)
		"Cette page permet de conna�tre les versions logicielles de l'�quipement.",
		"Cette page permet de conna�tre les versions logicielles et les options de l'�quipement.",
		"Version Logicielle",
		{//ps8_msg_nom_logiciel[]
			"Logiciel APPLI carte CPU",		//VERSION_LOGICIELLE_APPLI_CPU,
			"Logiciel BOOT carte CPU",		//VERSION_LOGICIELLE_BOOT_CPU,
		},
		"Boot",
		"Liste des options",
		"Type de l'option",
		{//ps8_msg_nom_option[]
			"",			//OPTION_AUCUNE
		},

		//Page Events - SUEvt
		"Cette page affiche les param�tres de configuration des �v�nements",
		"TRAP",
		"Cette page permet la configuration de l'�v�nement.",
		"Choix des actions",
		"SNMP TRAP",
		"Retour � la page",
		"Cet �v�nement est indisponible!",

		//Msg Console pour Telechargement
		"Logiciel d�tect�!",
		"Effacement flash impossible!",
		"Effacement flash ko: time out expir�!",
		"Ecriture flash ko: time out expir�!",
		"Ecriture flash ko: code 1!",
		"Ecriture flash ko: code 2!",
		"Ent�te fichier KO!",
		
		//Equipement
		"Radio modem",
		"Configuration",

		//page HomeB - navigation
		"Synoptique",
		"Visualisation du syst�me",
		"Param�tres RF",
		"Configuration des param�tres RF",
		"Param�tres ASI",
		"Configuration des param�tres ASI",
		"Entr�es/Sorties MPEG-2 TS",
		"Configuration des entr�es et des sorties MPEG-2 TS",
		"Limites DVB",
		"Profils DVB",						//ps8_msg_profils_dvb		
		"Configuration des limites DVB",								
		"Configuration des profils DVB",	//ps8_msg_show_profils_dvb	
		"DVB-H",
		"Configuration des param�tres DVB-H",
		"Multiplex",
		"Configuration du multiplex",
		"Qualit� du service",
		"Configuration pour la mesure des param�tres de synth�se de la qualit� du service",
		"Marquage",
		"Configuration pour l\\'analyse du marquage des PIDs",
		"SFN",
		"Coniguration du SFN",
		"Configuration de la carte Video",
		"Consultation des param�tres d\\'exploitation de l\\'entr�e RF",
		"Consultation des param�tres d\\'exploitation de l�\\'entr�e ASI",
		"Consultation des param�tres SFN mesur�s",
		"Consultation de l\\'analyse DVB-H",
		"Sorties ASI",
		"Consultation des param�tres d\\'exploitation des sorties ASI",
		"Scanning RF",
		"Consultation des mesures effectu�es pendant le scanning de l\\'entr�e RF",
		"Analyse MPEG-2 TS",
		"Analyse des mesures sur le multiplex",
		"Analyse simplifi�e des mesures sur le multiplex",
		"Services",
		"Analyse des mesures sur les services du multiplex",
		"PIDs",
		"Analyse des mesures sur les PIDs",
		"Tables",
		"Analyse des mesures sur les tables",
		"PCR",
		"Analyse des mesures sur les PCR",
		"ECM/EMM",
		"Analyse des mesures sur les ECM/EMM",
		"TR101290",
		"Analyse des alarmes TR101290 de l\\'analyse compl�te",
		"Analyse des alarmes TR101290 de l\\'analyse simplifi�e",
		"Analyse des mesures sur les param�tres de synth�se de la qualit� du service",
		"Contr�le marquage",
		"Analyse du marquage des PID",
		"DVB-H",
		"Analyse des mesures DVB-H",
		"Langue",
		"S�lection de la langue",
		"Rafra�chissement",
		"Configuration du rafra�chissement du contenu des pages HTML dynamiques",
		"Traps",
		"Consultation des �v�nements en cours ayant provoqu�s un TRAP",
		"Table des alarmes",
		"Consultation de la table des alarmes (tous les �v�nements en cours ayant provoqu�s un TRAP)",

		//Page Menu Configuration - Param�tres RF
		"Cette page permet de configurer les param�tres de l'entr�e RF.",
		
		//page menu Exploitation - Etat de configuration
		"Cette page permet d'acc�der aux pages d'�tat de configuration de l'�quipement.",

		//page menu Exploitation - Param�tres RF
		"Cette page affiche les param�tres d'exploitation du signal d'entr�e RF.",

		//page menu Evenements - Journal de bord
		"Journal de bord",
		"Consultation du Journal de bord",
		"Nombre d'�v�nements � purger si Journal de bord plein",
		"Effacer journal de bord des �v�nements",
		"Souhaitez - vous vraiment effacer le Journal de Bord?",
		"Type",
		"D�but",
		"Fin",
		"Info",
		"Nombre d'�v�nements dans le journal de bord",
		"Nombre d'�v�nements affich�s sur le journal de bord",
		"Cette page permet de configurer, d'effacer et d'afficher le journal de bord (1000 �v�nements maximum)",
		"Nombre d'�v�nements maximum par page",
		"Actions sur le fichier jdb",
		"G�n�rer fichier du journal de bord",
		"Souhaitez - vous vraiment g�n�rer le fichier jdb.log?",
		"Affichage dans le journal de bord",
		"Avertissement! Filtre du journal de bord actif.",
		"Affichage des �v�nements",
		"Affichage des �v�nements avec valeur TSID",
		"Affichage des �v�nements en fonction du type d'entr�e",

		//TRAPs
		"Cette page permet de consulter les �v�nements en cours ayant provoqu�s un TRAP.<BR>Cette table correspond � la table <B>alarmeV1Table</B> d�finie dans <B>SODIELECV2-ADMINISTRATION-V1-MIB</B>.",
		"Index",
		"Id",
		"Valeur",
		"Statut",
		"Date",
		"Heure",
		"Acquit",
		"alarme-on",
		"alarme-off",
		"info",
		"non-acquitt�",
		"acquitt�",
		"supprim�",
		"Acquitter tous les traps",

		//Divers
		"Commande g�n�rale RAZ:",
		"RAZ du jdb des param�tres de synth�se de la qualit� du service",

		//FTP
		"Erreur FTP longueur chaine de caract�res incorrecte.",
		"Erreur FTP configuration impossible en mode local.",
		"Erreur FTP valeur incorrecte.",
		"Erreur FTP configuration impossible en mode regulation automatique.",
		"Erreur FTP configuration impossible en 1+1.",
		"Erreur FTP adresse IP incorrecte.",
		"Erreur FTP configuration de l'alarme ROS incorrecte.",
		"Erreur FTP configuration sur le nombre STS-ID par pipe.",
		"Configuration FTP appliqu�e",
		"Configuration FTP KO",
		"Configuration FTP en cours",
		"T�l�chargement de",
		"Checksum fichier KO",

		//Page menu configuration - Mode
		"Configuration du mode du modem radio",
		"Mode modem radio",
		"Cette page permet de configurer le mode dans lequel le modem radio fonctionnera.",
		{//ps8_msg_choix_mode_radio_m[NB_MAX_MODES_RADIO_MODEM]
			"Access Point",	//MODE_RADIO_MODEM_ACCESS_POINT
			"Station",		//MODE_RADIO_MODEM_STATION
			"Monitor",		//MODE_RADIO_MODEM_MONITOR
		},
		{//ps8_msg_choix_mode_radio_M[NB_MAX_MODES_RADIO_MODEM]
			"ACCESS POINT",	//MODE_RADIO_MODEM_ACCESS_POINT
			"STATION",		//MODE_RADIO_MODEM_STATION
			"MONITOR",		//MODE_RADIO_MODEM_MONITOR
		},
		"Confirmez-vous le nouveau mode s�lectionn�?",
		"Changement du mode radio modem non autoris�. Vous devez configurer l\\'�quipement en mode bridge!",

		//Page menu configuration - Network
		"Configuration du r�seau",
		"Cette page permet de configurer le r�seau.",
		"<B>Access Point</B> fonctionne uniquement en mode bridge.",
		"<B>Station</B> fonctionne  en mode bridge ou router.",
		"<B>Monitor</B> fonctionne uniquement en mode bridge.",
		"Param�trage du mode r�seau",
		"Mode r�seau",
		{//ps8_msg_choix_mode_reseau[NB_MAX_MODES_NETWORK]
			"Bridge", //MODE_NETWORK_BRIDGE
			"Router", //MODE_NETWORK_ROUTER
		},
		"Param�trage r�seau du bridge",
		"Param�trage r�seau du LAN",
		"Param�trage r�seau du WLAN",
		"Adresse MAC Ethernet",
		"Adresse MAC Wifi",
		"Adresse IP Ethernet",
		"Adresse IP Wifi",
		"Mode IP",
		{//ps8_msg_choix_mode_ip[NB_MAX_MODES_IP]
			"Statique",		//MODE_IP_STATIQUE
			"DHCP client",	//MODE_IP_DHCP_CLIENT
		},
		"Adresse IP",
		"Masque du sous-r�seau",
		"Passerelle",
		"Erreur lors du changement de configuration",
		"Configurer maintenant correctement votre �quipement",
		"Adresse",
		"Si vous modifiez des param�tres IP ici, il sera peut-�tre n�cessaire d'adapter les param�tres r�seaux de votre PC pour acc�der de nouveau au r�seau.",
		{//ps8_msg_choix_interface_non_detecte[NB_MAX_INTERFACES]
			"",	//INTERFACE_AUTOMATIQUE
			"Interface LAN non d�tect�",				//INTERFACE_LAN
			"Interface WLAN non d�tect�",				//INTERFACE_WLAN
		},
		"Param�trage du host name",
		"Host name",
		"IP de repli en cas d'�chec DHCP",
		"IP de repli en cas d'�chec DHCP est invalide.",
		"Param�trage du VLAN",
		"Activation VLAN",
		"Nom du VLAN",
		"VLAN ID",
		"Conserver un acc�s LAN non tagg�",
		"Spanning Tree Protocol (STP)",

		//Page menu configuration - Wifi (Basic)
		"Wifi",
		"Configuration de l\\'acc�s Wifi",
		"Cette page permet de configurer les param�tres de l'acc�s Wifi",
		"Param�trage basique du Wifi",
		"Param�trage avanc� du Wifi",
		"Param�trage des antennes",
		"SSID",
		"Activation SSID secondaire",
		"SSID secondaire",
		"Masquer SSID",
		"Mode 802.11",
		"Intervalle de garde",
		{//ps8_msg_choix_intervalle_garde[NB_MAX_TYPE_GUARD_INTERVAL]
			"long",		//GUARD_INTERVAL_LONG
			"court",	//GUARD_INTERVAL_SHORT
		},
		"Largeur du spectre du canal",
		"Mode canal",
		"Canal",
		{//ps8_msg_choix_mode_canal[NB_MAX_TYPE_SELECTION_CANAL]
			"iso-fr�quence",	//TYPE_SELECTION_CANAL_ISO
			"multi-fr�quence",	//TYPE_SELECTION_CANAL_MULTI
			"automatique",		//TYPE_SELECTION_CANAL_AUTO
		},
		"Puissance de l'�metteur",
		"D�bit des donn�es",
		"Seuil de l'alarme niveau re�u",
		"Nombre maximum de stations associ�es",
		"Mode de s�curit� Wifi",
		"Mode de s�curit�",
		{//ps8_msg_choix_mode_securite_wifi[NB_MAX_MODES_SECURITE_WIFI]
			"Aucun", //MODE_SECURITE_WIFI_AUCUN
			"WEP", //MODE_SECURITE_WIFI_WEP
			"WPA", //MODE_SECURITE_WIFI_WPA
			"WPA-TKIP", //MODE_SECURITE_WIFI_WPA_TKIP
			"WPA-AES", //MODE_SECURITE_WIFI_WPA_AES
			"WPA2", //MODE_SECURITE_WIFI_WPA2
			"WPA2-TKIP", //MODE_SECURITE_WIFI_WPA2_TKIP
			"WPA2-AES", //MODE_SECURITE_WIFI_WPA2_AES
		},
		"WEP",
		"Longueur de la cl� WEP",
		{//ps8_msg_choix_longueur_cle_WEP[NB_MAX_WEP_KEY_LENGTH]
			"64 bit",	//WEP_KEY_LENGTH_64BIT
			"128 bit",	//WEP_KEY_LENGTH_128BIT
		},
		"Type de la cl� WEP",
		{//ps8_msg_choix_type_cle_WEP[NB_MAX_KEY_TYPE]
			"HEXA",		//KEY_TYPE_HEXA
			"ASCII",	//KEY_TYPE_ASCII
		},
		{//ps8_msg_info_saisie_cle_WEP[NB_MAX_WEP_KEY_LENGTH][NB_MAX_KEY_TYPE]
			{//WEP_KEY_LENGTH_64BIT
				"10 codes HEXA",		//KEY_TYPE_HEXA
				"5 caract�res ASCII",	//KEY_TYPE_ASCII
			},
			{//WEP_KEY_LENGTH_128BIT
				"26 codes HEXA",		//KEY_TYPE_HEXA
				"13 caract�res ASCII",	//KEY_TYPE_ASCII
			},
		},
		"Cl� WEP",
		"La valeur de la cl� est invalide.",
		"longueur appliqu�e � toutes les cl�s",
		"type appliqu�e � toutes les cl�s",
		"Afficher toutes les cl�s WEP",
		"Cl� WEP par d�faut",
		"Authentification",
		{//ps8_msg_choix_authentification_WEP[NB_MAX_WEP_AUTHENTIFICATION]
			"Syst�me ouvert",	//WEP_AUTHENTIFICATION_OPEN
			"A cl� partag�e",	//WEP_AUTHENTIFICATION_SHARED_KEY
		},
		"WPA",
		{//ps8_msg_choix_authentification_WPA[NB_MAX_WPA_AUTHENTIFICATION]
			"PSK",	//WPA_AUTHENTIFICATION_PSK
			"EAP",	//WPA_AUTHENTIFICATION_EAP
		},
		"Intervalle de mise � jour de la cl� temporaire de groupe (GTK)",
		"Type de la cl� PSK",
		"PSK",
		"EAP",
		{//ps8_msg_info_saisie_PSK[NB_MAX_KEY_TYPE]
			"64 codes HEXA",		  //KEY_TYPE_HEXA
			"8 � 63 caract�res ASCII",//KEY_TYPE_ASCII
		},
		"Cl� pr�-partag�e",
		"Afficher la cl� PSK",
		"Configurez un canal valide!",
		"P�riode de reauthentification EAP",
		"0 pour d�sactiver",
		"Adresse IP du serveur RADIUS",
		"Port UDP du serveur RADIUS",
		"Cl� du serveur RADIUS",
		"M�thode EAP",
		{//ps8_msg_choix_EAP_methode[NB_MAX_EAP_METHOD]
			"TTLS/PAP",		//EAP_METHOD__TTLS_PAP
			"TTLS/CHAP",	//EAP_METHOD__TTLS_CHAP
			"TTLS/EAP-MD5", //EAP_METHOD__TTLS_EAP_MD5
			"PEAP/MSCHAPv2",	//EAP_METHOD__PEAP_MSCHAPV2,
			"TLS",			//EAP_METHOD__TLS,
		},
		"Identit� EAP",
		"Nom de l'utilisateur EAP",
		"Mot de passe de l'utilisateur EAP",
		"Nom du certificat d'autorit� (EAP-TLS)",
		"Nom du certificat du client (EAP-TLS)",
		"Mot de passe de la cl� priv�e (EAP-TLS)",
		"Supprimer un certificat",
		"Aucun certificat s�lectionn�",
		"Etes-vous s�r de vouloir supprimer ce certificat?",
		"La m�thode d'authentification EAP-TLS n'est pas fonctionnelle.<BR>Au moins un des certificats n'est pas accessible.",
		"Afficher la cl� EAP",
		"La puissance de l\\'�metteur est configur�e � la valeur minimum.",
		"Le d�bit des donn�es est configur�e en automatique.",

		//Page menu configuration - Wifi (Avanc�)
		"Timeout ACK",
		"Type de preambule",
		{//ps8_msg_choix_type_preambule[NB_MAX_WF_TYPE_PREAMBULE]
			"Short",	//WF_TYPE_PREAMBULE_SHORT
			"Long",		//WF_TYPE_PREAMBULE_LONG
		},
		"Seuil fragmentation",
		"Seuil RTS/CTS",
		"Limitation retransmission RTS",
		"P�riode de la balise",
		"Activation WMM",
		"D�sactivation DFS",
		"Code pays",
		{//ps8_msg_choix_country_id[NB_MAX_COUNTRY_ID]
			"FRANCE",				//COUNTRY_ID_FRANCE
			"AUTRICHE",				//COUNTRY_ID_AUSTRIA
			"BELGIQUE",				//COUNTRY_ID_BELGIUM
			"BULGARIE",				//COUNTRY_ID_BULGARIA
			"CHYPRE",				//COUNTRY_ID_CYPRUS
			"REPUBLIQUE TCHEQUE",	//COUNTRY_ID_CZECH_REPUBLIC
			"DANEMARK",				//COUNTRY_ID_DENMARK
			"ESTONIE",				//COUNTRY_ID_ESTONIA
			"FINLANDE",				//COUNTRY_ID_FINLAND
			"ALLEMAGNE",			//COUNTRY_ID_GERMANY
			"GRECE",				//COUNTRY_ID_GREECE
			"ISLANDE",				//COUNTRY_ID_ICELAND
			"IRLANDE",				//COUNTRY_ID_IRELAND
			"ITALIE",				//COUNTRY_ID_ITALY
			"LETTONIE",				//COUNTRY_ID_LATVIA
			"LITUANIE",				//COUNTRY_ID_LITHUANIA
			"LUXEMBOURG",			//COUNTRY_ID_LUXEMBOURG
			"MALTE",				//COUNTRY_ID_MALTA
			"PAYS BAS",				//COUNTRY_ID_NETHERLANDS
			"NORVEGE",				//COUNTRY_ID_NORWAY
			"POLOGNE",				//COUNTRY_ID_POLAND
			"PORTUGAL",				//COUNTRY_ID_PORTUGAL
			"ROUMANIE",				//COUNTRY_ID_ROMANIA
			"SLOVAQUIE",			//COUNTRY_ID_SLOVAKIA
			"SLOVENIE",				//COUNTRY_ID_SLOVENIA
			"ESPAGNE",				//COUNTRY_ID_SPAIN
			"SUEDE",				//COUNTRY_ID_SWEDEN,
			"SUISSE",				//COUNTRY_ID_SWITZERLAND
			"ROYAUME-UNI",			//COUNTRY_ID_UNITED_KINGDOM
			"USA",					//COUNTRY_ID_USA
			"USA PUBLIC SAFETY",	//COUNTRY_ID_PUBLIC_SAFETY
		},
		"Avertissement! Un nouveau code pays entra�ne des changements dans les param�tres wifi:<BR> en mode 802.11g / canal 1 / antenne 1.",
		"Etes-vous s�r de vouloir configurer un nouveau code pays ?",

		//Page menu configuration - Wifi (Antennes)
		"S�lection antenne",
		"S�lection antenne d'�mission",
		{//ps8_msg_ABG_choix_antenne_tx[NB_MAX_ABG_SELECT_ANT_TX]
			"Antenne 1", //ABG_SELECT_TX_ANTENNE_1
			"Antenne 2", //ABG_SELECT_TX_ANTENNE_2
		},
		"S�lection antenne de r�ception",
		{//ps8_msg_ABG_choix_antenne_rx[NB_MAX_ABG_SELECT_ANT_RX]
			"Antenne 1",	//ABG_SELECT_RX_ANTENNE_1
			"Antenne 2",	//ABG_SELECT_RX_ANTENNE_2
			"Diversit�",	//ABG_SELECT_RX_DIVERSITY
		},
		{//ps8_msg_N_choix_antenne[NB_MAX_N_SELECT_ANTENNES]
			"Antenne 1",			//N_SELECT_ANTENNE_1
			"Antennes 1 & 2",		//N_SELECT_ANTENNES_1_ET_2
			"Antennes 1 & 2 & 3",	//N_SELECT_ANTENNES_1_ET_2_ET_3
		},
		"S�lection de l\\'antenne non autoris�e",
		"L'antenne 1 est forc�e dans ce mode 802.11.",

		//Page menu configuration - Hand-Off
		"Hand-Off",
		"Configuration du hand-off",
		"Cette page permet la configuration de la fonction hand-off, seulement si le produit est s�lectionn� en mode <B>station</B>.",
		"Mode du scanning",
		{//ps8_msg_choix_mode_scanning[NB_MAX_HO_MODES_SCANNING]
			"Automatique",	//HO_MODE_SCANNING_AUTO
			"Actif",		//HO_MODE_SCANNING_ACTIVE,
			"Passif",		//HO_MODE_SCANNING_PASSIVE,
		},
		"Param�trage du background scanning",
		"Activation du background scanning",
		"P�riode de r�currence du background scanning",
		"Seuil du niveau re�u d�clenchant un background scanning",
		"Param�trage du foreground scanning",
		"Seuil du niveau re�u d�clenchant un foreground scanning",
		"Seuil du nombre de balises perdues",
		"Param�trage du hand-off en iso-fr�quence",
		"Seuil du niveau re�u minimum pour le nouvel AP",
		"Seuil du nombre de balises re�ues pour le prochain AP<BR>avec un niveau re�u suffisant",
		"Intervalle de temps entre 2 hand-off cons�cutifs",
		"Param�trage du filtrage RSSI",
		"Type de filtre",
		//ps8_msg_choix_type_filtre[NB_MAX_TYPES_FILTRAGE_RSSI]
		{
			"Filtre 1", //FILTR_RSSI_1
			"Filtre 2", //FILTR_RSSI_2
			"Filtre 3", //FILTR_RSSI_3
			"Filtre 4", //FILTR_RSSI_4
		},
		//ps8_msg_intervalle_temps_entre_2_beacon
		"Intervalle d'�mission de la balise par les APs",
		
		//Page menu configuration - IP routing
		"Routage IP",
		"Configuration du routage IP",
		"Cette page permet la configuration du routage IP, seulement si le produit est s�lectionn� en mode <B>station</B> (mode r�seau router).",
		"Cet onglet permet d'afficher les routes actives.",
		"Cet onglet permet de configurer la table de routage statique (20 routes maximum).",
		"Cet onglet permet de configurer la table de politique de routage (10 routes maximum).",
		"La table de routage IP statique est",
		"Liste des routes activ�es",
		"Table de routage IP statique",
		"Ajouter une route",
		"Destination",
		"Metric",
		"Interface",
		{//ps8_msg_choix_interfaces_ip[NB_MAX_INTERFACES]
			"Automatique",		//INTERFACE_AUTOMATIQUE
			"LAN",				//INTERFACE_LAN
			"WLAN",				//INTERFACE_WLAN
		},
		"Il faut s�lectionner une interface pour ajouter la route.",
		"Table de routage IP statique <B>compl�te<B>.",
		"Route vers un host invalide.",
		"Route vers un sous-r�seau invalide.",
		"Liste des politiques de routage activ�es",
		"Aucune politique de routage activ�e.",
		"G�n�ral",
		"Routage statique",
		"Politique de routage",
		"Table des politiques de routage IP",
		"Ajouter une politique de routage IP",
		"Modifier une politique de routage IP",
		"Table des politiques de routage IP <B>compl�te<B>.",
		"Nom de la politique",
		"Source IP",
		"Destination IP",
		"Longueur du paquet",
		"Protocole IP",
		"Source port",
		"Destination port",
		"Class selector",
		"Nouvelle passerelle",
		"Nouvelle class selector",
		{//ps8_msg_choix_routepolicy_protocole[NB_MAX_POLICYROUTE_PROTOCOLES]
			"UDP",	//POLICYROUTE_PROTOCOLE_UDP
			"TCP",	//POLICYROUTE_PROTOCOLE_TCP
			"ICMP",	//POLICYROUTE_PROTOCOLE_ICMP
		},
		{//ps8_msg_choix_class_selector[NB_MAX_CLASSSELECTOR]
			"CS0",	//CLASSSELECTOR_CS0
			"CS1",	//CLASSSELECTOR_CS1
			"CS2",	//CLASSSELECTOR_CS2
			"CS3",	//CLASSSELECTOR_CS3
			"CS4",	//CLASSSELECTOR_CS4
			"CS5",	//CLASSSELECTOR_CS5
			"CS6",	//CLASSSELECTOR_CS6
			"CS7",	//CLASSSELECTOR_CS7
		},
		{//ps8_msg_erreur_saisie_critere[NB_MAX_CRITERIA_POLICY]
			"Erreur saisie de la plage d'adresses de la source IP.",	//CRITERIAPOLICY_SRC_IP
			"Erreur saisie de la plage d'adresses de la destination IP.",	//CRITERIAPOLICY_DST_IP
			"Erreur saisie de la plage des longueurs de paquet.",	//CRITERIAPOLICY_LENGTH_PACKET
			"Erreur saisie du protocole.",							//CRITERIAPOLICY_IP_PROTOCOL
			"Erreur saisie de la plage de ports de source.",		//CRITERIAPOLICY_SRC_PORT
			"Erreur saisie de la plage de ports de destination.",	//CRITERIAPOLICY_DST_PORT
			"Erreur saisie du class selector.",						//CRITERIAPOLICY_CLASS_SELECTOR
		},
		{//ps8_msg_erreur_saisie_action[NB_MAX_ACTIONS_POLICY]
			"Erreur saisie de la nouvelle passerelle.",			//ACTIONPOLICY_GATEWAY
			"Erreur saisie de la nouvelle class selector.",		//ACTIONPOLICY_CLASS_SELECTOR
		},
		"Au moins, un crit�re et une action doivent �tre s�lectionn�s.",
		"Liste des crit�res s�lectionn�s",
		"Liste des actions s�lectionn�es",
		"Routage RIPv2",
		"Cet onglet permet de configurer le protocole de routage dynamique RIPv2.",
		"Activation RIPv2",
		"Interfaces utilis�es par RIPv2",
		"Interfaces disponibles",
		"Interfaces RIP",
		{//ps8_msg_choix_interfaces_rip[NB_MAX_RIP_INTERFACES]
			"LAN",	//RIP_INTERF_LAN
			"WLAN",	//RIP_INTERF_WLAN
		},
		{//ps8_msg_choix_authentification_rip[NB_MAX_RIP_AUTHENTICATION]
			"Aucune",		//RIP_AUTHENTICATION_NONE
			"Plain text",	//RIP_AUTHENTICATION_PLAIN_TEXT
			"MD5",			//RIP_AUTHENTICATION_MD5
		},
		"Vous devez s�lectionner une interface disponible pour configurer RIP.",
		"Vous devez s�lectionner une interface pour la supprimer de RIP.",
		"Il faut s�lectionner au moins une interface pour configurer RIPv2.",

		//Page menu configuration - Serveur/Relai DHCP
		"Serveur / Relais DHCP",
		"Configuration du serveur / relais DHCP",
		"Cette page permet d'activer ou non la fonction DHCP (Dynamic Host Configuration Protocol) sur l'interface LAN, <BR> seulement si le produit est s�lectionn� en mode <B>station</B> (mode r�seau router).",
		"Le <B>serveur DHCP</B> permet de distribuer des adresses IP aux clients  qui se connecteront � l'interface LAN (seulement).",
		"L'<B>agent du relais DHCP</B> permet de relayer les requ�tes DHCP depuis un sous-r�seau ne comportant pas de serveur DHCP, � un serveur DHCP situ� sur un autre sous-r�seau.",
		"Fonction DHCP",
		{//ps8_msg_choix_fct_dhcp[NB_MAX_FCT_DHCP]
			"Serveur/Relais DHCP OFF",	//FCT_DHCP_NONE
			"Serveur DHCP ON",			//FCT_DHCP_SERVER
			"Relais DHCP ON",			//FCT_DHCP_RELAY
		},
		"Param�trage du serveur DHCP",
		"Plage d'adresses IP DHCP",
		"adresses dans le m�me sous-r�seau",
		"Dur�e de vie du bail DHCP",
		"Param�trage de l'agent relais DHCP",
		"Adresse IP cible du relais DHCP",
		"L'adresse IP DHCP (minimum) n\\'est pas dans le sous-r�seau LAN.",
		"L'adresse IP DHCP (maximum) n\\'est pas dans le sous-r�seau LAN.",
		"L'adresse IP DHCP (minimum) ne contient pas une valeur d\\'h�te valide.",
		"La plage d'adresses DHCP devrait �tre d�finie d'une adresse minimum � une adresse maximum, et non de maximum � minimum.",
		"La plage d'adresses DHCP ne doit pas inclure l'adresse de broadcast.",
		"Le nombre d'adresses IP dans la plage exc�de le maximum autoris�.",
		"Serveur DHCP non fonctionnel. Probl�me de configuration!",
		"Agent relais DHCP non fonctionnel. Probl�me de configuration!",

		//Page Menu Configuration - NAT
		"NAT",
		"Configuration du NAT",
		"Cette page permet de configurer la fonction NAT (Network Address Translation), <BR> seulement si le produit est s�lectionn� en mode <B>station</B> (mode r�seau router).",
		"Activation NAT",
		"Liste des r�gles NAT actives",
		"Port priv�",
		"Adresse IP priv�e",
		"Port public",
		"Adresse IP publique",
		"Adresse IP publique (par d�faut)",
		"Ajouter une nouvelle r�gle de port forwarding",
		"Ajouter une nouvelle r�gle de mapping d'adresse",
		"Port forwarding",
		"Protocole",
		{//ps8_msg_choix_nat_protocole[NB_MAX_NAT_PROTOCOLES]
			"Non s�lectionn�",	//NAT_PROTOCOLE_NON_SELECTIONNE
			"UDP",			//NAT_PROTOCOLE_UDP
			"TCP",			//NAT_PROTOCOLE_TCP
		},
		"Alias IP",
		"La Table des r�gles de port forwarding est <B>compl�te</B>",
		"La Table des r�gles de mapping d'adresses est <B>compl�te</B>",
		"Mapping d'adresses",
		"Il faut s�lectionner un protocole pour ajouter la r�gle.",
		"Configuration NAT non appliqu�e",
		"NAT non fonctionnel. Probl�me de configuration!",

		//Page Menu Configuration - Multicast
		"Multicast",
		"Configuration du Multicast",
		"Cette page permet de configurer la gestion du multicast IP, <BR> seulement si le produit est s�lectionn� en mode <B>station</B> (mode r�seau router).",
		"Activation du proxy IGMP",
		"Table des sources multicast autoris�es (au maximum 20 sources)",
		"Ajouter une source multicast",
		"La Table des sources multicast autoris�es est <B>compl�te</B>",
		"Source d'un sous-r�seau invalide.",
		"Adresse de r�seau",
		"Masque de r�seau",
		
		//Page Menu Configuration - SNMP
		"Cette page permet la configuration de l'agent SNMP.",
		"Communaut�s",
		"Managers SNMP",
		"Ce tableau permet de configurer les adresses des managers SNMP destinataires des TRAPs.",
		"Ce tableau permet de configurer les adresses des managers SNMP destinataires des TRAPs / INFORMs.",
		"Libell�s",
		"Adresse Internet (IP)",
		"Configuration �mission des TRAPs",
		"Emission des TRAPs",
		"Configuration �mission des TRAPs / INFORMs",
		"Emission des TRAPs / INFORMs",
		"Pour SNMPv2c, les traps sont �mis une seule fois.",
		"Rejouer les TRAPs pr�sents",
		"Activation signe de vie",
		"Temporisation signe de vie",
		"Protocole d'�mission des TRAPs",
		"Ce tableau permet de configurer le protocole d'�mission d'un TRAP.",
		"Protocole d'�mission des INFORMs",
		"Ces param�tres permettent de configurer le m�canisme d'�mission d'un INFORM.",
		"Nombre d'�mission",
		"Intervalle de r��mission",
		"Si la valeur est �gale � 0, alors le trap sera �mis en permanence jusqu'� l'acquittement du manager SNMP.",
		"S�lection de la version SNMP de l'agent",
		"Version SNMP",
		{//ps8_msg_choix_version_snmp[NB_MAX_VERSIONS_SNMP]
			"SNMPv1",	//VERSION_SNMPV1
			"SNMPv2c",	//VERSION_SNMPV2C
		},
		"Type de notification",
		{//ps8_msg_choix_type_notification[NB_MAX_TYPES_NOTIFICATION]
			"TRAP",		//TYPE_NOTIFICATION_TRAP
			"INFORM",	//TYPE_NOTIFICATION_INFORM
		},

		//Page Menu Exploitation - Wifi
		"Cette page affiche des param�tres d'exploitation en mode <B>station</B>.",
		"Cette page affiche des param�tres d'exploitation en mode <B>access point</B>.",
		"Consultation des param�tres d\\'exploitation de l\\'acc�s Wifi",
		"BSSID",
		"RSSI",
		{//ps8_msg_choix_station_connexion[NB_MAX_STATUT_CONNEXION]
			"Non connect�e",				//STATUT_CONNEXION__NOT_ASSOCIATED
			"Non connect�e (non valide)",	//STATUT_CONNEXION__INVALID
			"Non connect�e (aucune)",		//STATUT_CONNEXION__NONE
			"Connect�e",					//STATUT_CONNEXION__ASSOCIATED
		},
		"Liste des clients Wifi associ�s",
		"Associ�",
		"Non associ�",
		"Connexion WPA active",
		"Canal utilis�",

		//Page Menu Exploitation - G�n�rale
		"Cette page affiche les param�tres d'exploitation g�n�rale.",
		"Consultation des param�tres d\\'exploitation g�n�rale",
		"Temp�rature",
		
		//Page Menu Exploitation - R�seau
		"Cette page affiche les param�tres d'exploitation des interfaces du r�seau.",
		"Consultation des param�tres d\\'exploitation du r�seau",
		"DHCP en cours sur l'acc�s WLAN",
		"Statut IP",
		{//ps8_msg_choix_statut_ip[NB_MAX_STATUTS_IP]
			"Ind�fini",		//STATUT_IP__UNDEFINED
			"Statique",		//STATUT_IP__STATIC
			"DHCP en cours",//STATUT_IP__DHCP_IN_PROGRESS
			"Succ�s DHCP",	//STATUT_IP__SUCCESS_DHCP
			"Echec DHCP",	//STATUT_IP__FAILURE_DHCP
		},

		//Page Menu Exploitation - client DHCP
		"Clients DHCP",
		"Cette page affiche les clients DHCP sur l'interface LAN, qui ont obtenu un bail du serveur DHCP.",
		"Consultation des clients DHCP",
		"Liste des clients DHCP",
		"Dur�e du bail restant (secondes)",
		"Aucun client DHCP",
		
		//page menu Alarmes - Liste des alarmes
		{//ps8_msg_lib_groupe_alarmes[]
			"Alarmes syst�me",				//GROUPE_AL_SYSTEME
#if TEST_DEBUG_EVENT
			"Alarmes debug",				//GROUPE_AL_DEBUG
#endif
			"?",							//GROUPE_AL_NOT_USED
		},
		"Cette page affiche l'�tat des alarmes.",
		{//ps8_msg_sous_titre_Vliste_groupe_alarmes[]
			"Cette page affiche l'�tat des alarmes syst�me.",	//GROUPE_AL_SYSTEME
#if TEST_DEBUG_EVENT
			"Cette page affiche l'�tat des alarmes debug",		//GROUPE_AL_DEBUG
#endif
			"?",												//GROUPE_AL_NOT_USED
		},
		"Effacer toutes les alarmes",
		"Voir",

		//page menu Evenements - Configuration des �v�nements
		"Validation, Jdb, Trap",
		"Jdb",
		"Validation",
		"Synth�se",
		"Synth�se 1..3",
		"Synth�se 1",
		"Synth�se 2",
		"Synth�se 3",
		
		//Libell�s des Evenements
		{//ps8_msg_lib_evenement[NB_MAX_EVENEMENTS]
			"Alarme synth�se",			//EVT000_AL_SYNTHESE_1
			"D�faut �quipement",			//EVT001_DEFAUT_EQUIPEMENT
			"Alarme temp�rature",			//EVT002_AL_TEMPERATURE
			"Alarme Ethernet LAN 1",		//EVT003_AL_ETHERNET_LAN_1
			"Alarme Ethernet LAN 2",		//EVT004_AL_ETHERNET_LAN_2
			"Alarme niveau re�u",			//EVT005_AL_NIVEAU_RECU
			"Alarme station non connect�e",	//EVT006_STATION_NON_CONNECTEE
			"Probl�me de configuration",	//EVT007_PROBLEME_CONFIGURATION
			"Basculement sur SSID secondaire",	//EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE
			"Retour sur SSID primaire",			//EVT009_RETOUR_SUR_SSID_PRIMAIRE
			"Alarme aucun serveur NTP accessible",	//EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE
			"Radar d�tect� sur canal",	//EVT011_RADAR_DETECTE_SUR_CANAL
			"Basculement vers canal",	//EVT012_BASCULEMENT_VERS_CANAL
			"Connexion de la station",		//EVT013_CONNEXION_STATION
			"D�connexion de la station",	//EVT014_DECONNEXION_STATION
			"Connexion sur l'access point",	//EVT015_CONNEXION_ACCESS_POINT
			"D�connexion de l'access point",//EVT016_DECONNEXION_ACCESS_POINT
			"EVT017_RESERVE",			//EVT017_RESERVE
			"EVT018_RESERVE",			//EVT018_RESERVE
			"EVT019_RESERVE",			//EVT019_RESERVE
			"EVT020_RESERVE",			//EVT020_RESERVE
			"EVT021_RESERVE",			//EVT021_RESERVE
			"EVT022_RESERVE",			//EVT022_RESERVE
			"EVT023_RESERVE",			//EVT023_RESERVE
			"EVT024_RESERVE",			//EVT024_RESERVE
			"EVT025_RESERVE",			//EVT025_RESERVE
			"EVT026_RESERVE",			//EVT026_RESERVE
			"EVT027_RESERVE",			//EVT027_RESERVE
			"EVT028_RESERVE",					//EVT028_RESERVE
			"EVT029_RESERVE",			//EVT029_RESERVE
			"EVT030_RESERVE",			//EVT030_RESERVE
			"EVT031_RESERVE",			//EVT031_RESERVE
			"EVT032_RESERVE",			//EVT032_RESERVE
			"EVT033_RESERVE",			//EVT033_RESERVE
			"EVT034_RESERVE",			//EVT034_RESERVE
			"EVT035_RESERVE",			//EVT035_RESERVE
			"EVT036_RESERVE",			//EVT036_RESERVE
			"EVT037_RESERVE",			//EVT037_RESERVE
			"EVT038_RESERVE",			//EVT038_RESERVE
			"EVT039_RESERVE",			//EVT039_RESERVE
			"EVT040_RESERVE",			//EVT040_RESERVE
			"EVT041_RESERVE",			//EVT041_RESERVE
			"EVT042_RESERVE",			//EVT042_RESERVE
			"EVT043_RESERVE",			//EVT043_RESERVE
			"EVT044_RESERVE",			//EVT044_RESERVE
			"EVT045_RESERVE",			//EVT045_RESERVE
			"EVT046_RESERVE",			//EVT046_RESERVE
			"EVT047_RESERVE",			//EVT047_RESERVE
			"EVT048_RESERVE",			//EVT048_RESERVE
			"EVT049_RESERVE",			//EVT049_RESERVE
			"EVT050_RESERVE",			//EVT050_RESERVE
			"EVT051_RESERVE",			//EVT051_RESERVE
			"EVT052_RESERVE",			//EVT052_RESERVE
			"EVT053_RESERVE",			//EVT053_RESERVE
			"EVT054_RESERVE",			//EVT054_RESERVE
			"EVT055_RESERVE",			//EVT055_RESERVE
			"EVT056_RESERVE",			//EVT056_RESERVE
			"EVT057_RESERVE",			//EVT057_RESERVE
			"EVT058_RESERVE",			//EVT058_RESERVE
			"EVT059_RESERVE",			//EVT059_RESERVE
			"EVT060_RESERVE",			//EVT060_RESERVE
			"EVT061_RESERVE",			//EVT061_RESERVE
			"EVT062_RESERVE",			//EVT062_RESERVE
			"EVT063_RESERVE",			//EVT063_RESERVE
			"EVT064_RESERVE",			//EVT064_RESERVE
			"EVT065_RESERVE",			//EVT065_RESERVE
			"EVT066_RESERVE",			//EVT066_RESERVE
			"EVT067_RESERVE",			//EVT067_RESERVE
			"EVT068_RESERVE",			//EVT068_RESERVE
			"EVT069_RESERVE",			//EVT069_RESERVE
			"EVT070_RESERVE",			//EVT070_RESERVE
			"EVT071_RESERVE",			//EVT071_RESERVE
			"EVT072_RESERVE",			//EVT072_RESERVE
			"EVT073_RESERVE",			//EVT073_RESERVE
			"EVT074_RESERVE",			//EVT074_RESERVE
			"EVT075_RESERVE",			//EVT075_RESERVE
			"EVT076_RESERVE",			//EVT076_RESERVE
			"EVT077_RESERVE",			//EVT077_RESERVE
			"EVT078_RESERVE",			//EVT078_RESERVE
			"EVT079_RESERVE",			//EVT079_RESERVE
			"EVT080_RESERVE",			//EVT080_RESERVE
			"EVT081_RESERVE",			//EVT081_RESERVE
			"EVT082_RESERVE",			//EVT082_RESERVE
			"EVT083_RESERVE",			//EVT083_RESERVE
			"EVT084_RESERVE",			//EVT084_RESERVE
			"EVT085_RESERVE",			//EVT085_RESERVE
			"EVT086_RESERVE",			//EVT086_RESERVE
			"EVT087_RESERVE",			//EVT087_RESERVE
			"EVT088_RESERVE",			//EVT088_RESERVE
			"EVT089_RESERVE",			//EVT089_RESERVE
			"EVT090_RESERVE",			//EVT090_RESERVE
			"EVT091_RESERVE",			//EVT091_RESERVE
			"EVT092_RESERVE",			//EVT092_RESERVE
			"EVT093_RESERVE",			//EVT093_RESERVE
			"EVT094_RESERVE",			//EVT094_RESERVE
			"EVT095_RESERVE",			//EVT095_RESERVE
			"EVT096_RESERVE",			//EVT096_RESERVE
			"EVT097_RESERVE",			//EVT097_RESERVE
			"EVT098_RESERVE",			//EVT098_RESERVE
			"EVT099_RESERVE",			//EVT099_RESERVE
			"EVT100_RESERVE",			//EVT100_RESERVE
			"EVT101_RESERVE",			//EVT101_RESERVE
			"EVT102_RESERVE",			//EVT102_RESERVE
			"EVT103_RESERVE",			//EVT103_RESERVE
			"EVT104_RESERVE",			//EVT104_RESERVE
			"EVT105_RESERVE",			//EVT105_RESERVE
			"EVT106_RESERVE",			//EVT106_RESERVE
			"EVT107_RESERVE",			//EVT107_RESERVE
			"EVT108_RESERVE",			//EVT108_RESERVE
			"EVT109_RESERVE",			//EVT109_RESERVE
			"Journal de bord effac�",					//EVT110_JOURNAL_BORD_EFFACE
			"Effacement historique des alarmes",		//EVT111_INF_RAZ_ALARMES_MEMO
			"Evolution de la configuration",			//EVT112_EVOLUTION_CONFIGURATION
			"Red�marrage t�l�command� de l'�quipement",	//EVT113_ORDRE_RESET_TELECOMMANDE
			"EVT114_RESERVE",			//EVT114_RESERVE
			"EVT115_RESERVE",			//EVT115_RESERVE
			"EVT116_RESERVE",			//EVT116_RESERVE
			"EVT117_RESERVE",			//EVT117_RESERVE
			"EVT118_RESERVE",			//EVT118_RESERVE
			"EVT119_RESERVE",			//EVT119_RESERVE
			"EVT120_RESERVE",			//EVT120_RESERVE
			"EVT121_RESERVE",			//EVT121_RESERVE
			"EVT122_RESERVE",			//EVT122_RESERVE
			"EVT123_RESERVE",			//EVT123_RESERVE
			"EVT124_RESERVE",			//EVT124_RESERVE
			"EVT125_RESERVE",			//EVT125_RESERVE
			"EVT126_RESERVE",			//EVT126_RESERVE
			"EVT127_RESERVE",			//EVT127_RESERVE
			"EVT128_RESERVE",			//EVT128_RESERVE
			"EVT129_RESERVE",			//EVT129_RESERVE
			"EVT130_RESERVE",			//EVT130_RESERVE
			"EVT131_RESERVE",			//EVT131_RESERVE
			"EVT132_RESERVE",			//EVT132_RESERVE
			"EVT133_RESERVE",			//EVT133_RESERVE
			"EVT134_RESERVE",			//EVT134_RESERVE
			"EVT135_RESERVE",			//EVT135_RESERVE
			"EVT136_RESERVE",			//EVT136_RESERVE
			"EVT137_RESERVE",			//EVT137_RESERVE
			"EVT138_RESERVE",			//EVT138_RESERVE
			"EVT139_RESERVE",			//EVT139_RESERVE
			"EVT140_RESERVE",			//EVT140_RESERVE
			"EVT141_RESERVE",			//EVT141_RESERVE
			"EVT142_RESERVE",			//EVT142_RESERVE
			"EVT143_RESERVE",			//EVT143_RESERVE
			"EVT144_RESERVE",			//EVT144_RESERVE
			"EVT145_RESERVE",			//EVT145_RESERVE
			"EVT146_RESERVE",			//EVT146_RESERVE
			"EVT147_RESERVE",			//EVT147_RESERVE
			"EVT148_RESERVE",			//EVT148_RESERVE
			"EVT149_RESERVE",			//EVT149_RESERVE
			"EVT150_RESERVE",			//EVT150_RESERVE
			"EVT151_RESERVE",			//EVT151_RESERVE
			"EVT152_RESERVE",			//EVT152_RESERVE
			"EVT153_RESERVE",			//EVT153_RESERVE
			"EVT154_RESERVE",			//EVT154_RESERVE
			"EVT155_RESERVE",			//EVT155_RESERVE
			"EVT156_RESERVE",			//EVT156_RESERVE
			"EVT157_RESERVE",			//EVT157_RESERVE
			"EVT158_RESERVE",			//EVT158_RESERVE
			"EVT159_RESERVE",			//EVT159_RESERVE
			"EVT160_RESERVE",			//EVT160_RESERVE
			"EVT161_RESERVE",			//EVT161_RESERVE
			"EVT162_RESERVE",			//EVT162_RESERVE
			"EVT163_RESERVE",			//EVT163_RESERVE
			"EVT164_RESERVE",			//EVT164_RESERVE
			"EVT165_RESERVE",			//EVT165_RESERVE
			"EVT166_RESERVE",			//EVT166_RESERVE
			"EVT167_RESERVE",			//EVT167_RESERVE
			"EVT168_RESERVE",			//EVT168_RESERVE
			"EVT169_RESERVE",			//EVT169_RESERVE
			"EVT170_RESERVE",			//EVT170_RESERVE
			"EVT171_RESERVE",			//EVT171_RESERVE
			"EVT172_RESERVE",			//EVT172_RESERVE
			"EVT173_RESERVE",			//EVT173_RESERVE
			"EVT174_RESERVE",			//EVT174_RESERVE
			"Equipement ON",			//EVT175_INF_EQUIPEMENT_ON
			"Signe de vie",				//EVT176_INF_SIGNE_DE_VIE
			"EVT177_RESERVE",			//EVT177_RESERVE
			"EVT178_RESERVE",			//EVT178_RESERVE
			"EVT179_RESERVE",			//EVT179_RESERVE
		},

		//Libell�s suppl�mentaires sur les �v�nements
		{//ps8_msg_lib_errorconfig[NB_MAX_ERRORCONFIG]
			"configuration par d�faut",		//ERRORCONFIG_PASSAGE_PAR_DEFAUT
			"non appliqu�e",				//ERRORCONFIG_INSTALLATION
		},
		

		//	
	},
// Messages en Anglais:
	
//********************************************************************
/////////////////////////rep�re : debut anglais
//********************************************************************

	{
		//HOMEB - Accueil + Actualiser
		"Main Page",
		"Main Page",
		"Refresh",
		"Refresh current Page",
		//HOMEB - Menu Administration
		"Administration",
		"Identification",
		"Identification of Terminal",
		"State control",
		"Restart",
		"Access Control",
		"Passwords",
		"Time",
		"Real Time Clock settings of equipment",
		"Software revisions",
		"Software Identities",
		"Software revisions / Options",
		"Software / Options Identities",
		"Download",
		"Download software",
		//HOMEB - Menu R�seau
		"Network",
		"Configuration state",
		"View of actual parameters of equipment",
		"Configuration setup",
		"Setup of parameterts of equipment",
		"IP Addresses",
		"IP Addresses configuration",
		"IP Address",
		"IP Address configuration",
		"IP Routing",
		"IP routing configuration",
		"SNMP",
		"SNMP configuration",
		//HOMEB - Menu Exploitation
		"Operating",
		//HOMEB - Menu Alarmes
		"Alarms",
		"Alarms List",
		"View Alarms",
		//HOMEB - Menu Evenements
		"Events",
		"Event List",
		"Events Configuration (severity, TRAP, ..)",
		"Setup",
		"Events setup (severity, TRAP, ..)",
		//HOMEB - Contact
		"Contact",

		//DICTIONNAIRE
		"Parameter",
		"Value",
		"Yes",
		"No",
		"Code",
		"Severity",
		"Text",
		"Undefined",
		"Critical",
		"Major",
		"Minor",
		"Warning",
		"Configuration",
		"Off",
		"On",
		"Return to links of configuration state",
		"Return to links of configuration setup",
		"Alarm",
		"alarm",
		"Error",
		"Status",
		"Latched status",
		{//ps8_msg_choix_langue[NB_MAX_LANGUES]
			"french",	//LANGUE_FRANCAIS
			"english",	//LANGUE_ANGLAIS
		},
		"Unavailable",
		"System",
		"Page",
		"Manual",
		"Manual",
		"Automatic",
		"Channel bandwidth",
		"Activation",
		"Selection",
		"Present",
		"Not present",
		"Present",
		"Not present",
		"General",
		"Number",
		"Configuration not allowed!",
		"Not used",
		"unused",
		"used",
		"High",
		"Low",
		"Disabled option",
		"in progress",
		"Inst",
		"Min",
		"Max",
		"(inst.)",
		"(min.)",
		"(max.)",
		"inst",
		"min",
		"max",
		"All",
		"None",
		"Action",
		"DISABLED",
		"ENABLED",
		"Disabled",
		"Enabled",
		"Name",
		"Equipment not connected. Refresh",
		"Program",
		"Network",
		"Command",
		"Label",
		"Reference",
		"Hardware",
		"Software",
		"Available",
		"Configuration error",
		"During",
		"in seconds",
		"Normal",
		"Standby",
		"NORMAL",
		"STANDBY",
		"Input",
		"Monitor",
		"Auto setup",
		"Level",
		"Analysis",
		"bytes",
		"rates",
		"To clear lachted alarms",
		"click here",
		"standard",
		"seconds",
		"Mode",
		"MODE",
		"Delete",
		"Add",
		"Clear",
		"CONNECTED",
		"NO CONNECTED",
		"MAC address",
		"from",
		"to",
		"Enabled",
		"Comment",
		"Date of last cleaning",
		"Criteria",
		"Not",
		"Change",

		//BOITES
		"Accept changes",
		"Accept changes",
		"    Cancel    ",
		"  Accept all changes  ",
		"      OK      ",
		" <- Previous event    ",
		" Accept changes and next -> ",
		"    Next event ->    ",
		"Execute",
		"    Stop   ",
		"    Start  ",
		"      Log in      ",													/*ps8_msg_valider*/

		//Pages d'info
		"Download new Informations ...",
		"Error in the request",
		"The equipment is now set with new parameters",
		"The configured parameters are invalid!",
		"active mode = LOCAL EQUIPMENT, changes not allowed",
		"No information",
		"Page not allowed (unknown parameter) !",
		"Refresh the page!",
		"Restarting of equipment in progress ...",
		"Download in progress ...",
		"Download ok !",
		"Page not allowed in local mode !",
		"Database access impossible !",
		"Only in STATION / ROUTER !",
		"Only in STATION mode !",
		"Configuration in progress.",
		"Please wait.",
		"Page not allowed in MONITOR mode !",

		//Javascript
		"This value must be a number.",
		"This value must be greater than or equal to",
		"This value must be less than or equal to",
		"This value must be an integer.",
		"is not a valid address.",
		"is not a valid mask.",
		"You are not allowed to use",
		"in the text",
		"This field may not be left empty.",
		"no alarm",
		"no alarm",
		"This value must be a number with a step of",
		"is not a valid multicast address.",
		"This value must be in range or equal to : ",
		"no validate",
		"This text contains a not valid character.",
		"This value is not allowed.",
		"is not a valid MAC address.",
		"The gateway address is not in the subnet of this interface.",
		"IP address or subnet mask or gateway is not valid.",
		"This text contains the not valid character \\'space\\'.",
		"IP address or subnet mask is not valid.",
		"LAN and WLAN subnet must be different.",
		
		//Page d'Accueil
		"Welcome to the WEB server. Use the menu on the left to navigate through the pages.",
		"Description",
		"Equipment Type",
		"ID of Equipment",
		"Location of Equipment",
		"General configuration",
		"Active Alarms",
		"None alarm",
		
		//Page Menu Administration - S�curit�
		"Password",
//d: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - S�curit�
//		"This page can modify the access level passwords, the maximum connection delay without HTTP activity and the maximum clients IP number. It can also secure SNMP server.",
		"This page can modify the access level passwords, the maximum connection delay without HTTP activity and the maximum clients IP number.",
//f: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - S�curit�
		"Old password",
		"New password",
		"Confirm password",
		"Change password",
		"Set password",
		"Maximum connection delay without HTTP activity",
		"When the connection delay without HTTP activity is effective, password will be required for connection with WEB server.",
		"Delay",
		"Maximum clients",
		"minutes",
		"Invalid maximum customers number",
		"Invalid maximum delay",
		"Confirm and new password are different",
		"Bad password",
		"Security of SNMP server",
		"Configuration (SET) with a SNMP manager can be secured.",
		"If SNMP server is secured, all configuration will require connection.",
		"Secured Configuration with SET",
		"Insufficient privileges",
		"Invalid max customers number",

		//Page Menu Administration - SUTime
		"Date and Time Configuration",
		"This page contains settings for the real time clock function.",
		"Retrieve current time from local computer",
		"Hour",
		"Date",
		"Hours",
		"Year",
		"Month",
		"Day",
		"Minute",
		"Second",
		"A change of time will restart the SNMP board",
		"Be carefull",
		"DD/MM/YYYY HH:MM:SS",
		"Date and time UT : ",
		"Manual Time Setting",
		"Manual time may only be set when NTP is DISABLED.",
		"Time setting selection",
		"Time setting mode",
		{//ps8_msg_choix_mah[NB_MAX_MODES_MAH]
			"Manual", //MODE_MAH_MANUELLE
			"NTP",		//MODE_MAH_NTP
			"SNTP",		//MODE_MAH_SNTP
		},
		"NTP server",
		"NTP fallback server",
		"Time Zone",
		"You can't submit your own time when time setting mode is not manual.",
		"No NTP server did not respond",
		"Time notation",
		"SNTP Update Frequency [h]",
		"Configuration of the starting date of the equipment",
		"The date and time are not stored on OFF/ON of the equipment.<BR>It is possible to configure the starting date.",

		//Page Menu Administration - Identification (SUAdmIdentification)
		"This page displays informations about the identification of the equipment.",

		//Page Menu Administration - Controle (SUAdmControle)
		"This page can:<BR>  - execute a restart of equipment,<BR>  - clear all measures<BR>  - set the default configuration (only for Super User mode).",
		"Warning! A restart of equipment software can disturb the fonctionnality of the equipment",
		"Restart equipment",
		"Are you sure to restart equipment?",
		{//ps8_msg_choix_mode_pilotage[]
			"Local Mode",	//MODE_LOCAL,
			"Remote Mode",	//MODE_DISTANT,
		},
		"Control Mode",
		"Keyboard locked",
		"Set the default configuration",
		"without IP and gateway parameters",
		"Are you sure you want to set the default configuration of this equipment ?",
		"<B>Warning!</B> Set the default configuration restarts the equipment",
//d: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - Controle
//		"Warning! The passwords will be applied with default values: low, middle, high!",
		"All the network settings and passwords will be applied with default values!",
//f: BE065.1 02/05/2012 (CM) - Correction libell� dans page Html Administration - Controle
		"Are you sure to clear all measures?",

		//Page Menu Administration - Langue (SUAdmlangue)
		"This page can select language of user interface.",

		//Page Menu Administration - Rafraichissement (SUAdmRefresh)
		"This page can configure refresh of content for dynamic HTML pages.",
		"Refresh time minimum",

		//Page Menu Administration - Systemlog (SUAdmSystemLog)
		"Log system",
		"Log system configuration",
		"This page can configure the registration routine of the system log messages",
		"Enable system log",
		"Enable RSSI mode",
		"Remote IP address", 
		"Remote port", 
		"RSSI mode not functional with none wireless security.", 
		"Remote IP address must not be null in RSSI mode.", 
		
		//Page Menu Administration - Versions Logicielles (VAdmVersionsLogicielles)
		"This page displays the software revisions of the equipment.",
		"This page displays the software revisions and the options of the equipment.",
		"Software revision",
		{//ps8_msg_nom_logiciel[]
			"CPU board APPLI software",		//VERSION_LOGICIELLE_APPLI_CPU,
			"CPU board BOOT software",		//VERSION_LOGICIELLE_BOOT_CPU,
		},
		"Boot",
		"Options list",
		"Option type",
		{//ps8_msg_nom_option[]
			"",				//OPTION_AUCUNE
		},
		
		//Page Events - SUEvt
		"This page displays parameters of configuration events.",
		"TRAP",
		"This page can configure event.",
		"Actions choice",
		"SNMP TRAP",
		"Return to the page",
		"This event is not available!",

		//Msg Console pour Telechargement
		"Software detected!",
		"Erase flash not allowed!",
		"Erase flash ko: time out expired!",
		"Write flash ko: time out expired!",
		"Write flash ko: code 1!",
		"Write flash ko: code 2!",
		"Header file ko!",
		
		//Equipement
		"Radio modem",
		"Configuration",

		//page HomeB - navigation
		"Block Diagram",
		"Block diagram view",
		"RF parameters",
		"RF parameters configuration",
		"ASI parameters",
		"ASI parameters configuration",
		"Inputs/Outputs MPEG-2 TS",
		"I/O MPEG-2 TS configuration",
		"DVB Limits",
		"DVB Profiles",							//ps8_msg_profils_dvb
		"DVB limits configuration",				
		"DVB Profiles configuration",			//ps8_msg_show_profils_dvb
		"DVB-H",
		"DVB-H configuration",
		"Multiplex",
		"Multiplex configuration",
		"Service quality",
		"Synthesis parameters configuration of service quality",
		"Stamping",
		"Stamping configuration",
		"SFN",
		"SFN configuration",
		"Video board configuration",
		"View RF input parameters",
		"View ASI input parameters",
		"View SFN parameters",
		"View DVB-H analysis",
		"ASI outputs",
		"View ASI outputs parameters",
		"RF scanning",
		"View RF scanning parameters",
		"MPEG-2 TS analysis",
		"Multiplex analysis",
		"Multiplex simplified analysis",
		"Services",
		"Services analysis",
		"PIDs",
		"PIDs analysis",
		"Tables",
		"Tables analysis",
		"PCR",
		"PCR analysis",
		"ECM/EMM",
		"ECM/EMM analysis",
		"TR101290",
		"TR101290 alarms complete analysis",
		"TR101290 alarms simplified analysis",
		"Synthesis parameters analysis of service quality",
		"Stamping control",
		"Stamping of PID analysis",
		"DVB-H",
		"DVB-H analysis",
		"Language",
		"Language selection",
		"Refresh",
		"Refresh configuration of contents for dynamic HTML pages",
		"Traps",
		"View of current events which caused a TRAP",
		"Alarms table",
		"View of alarms table (current events which caused a TRAP)",

		//Page Menu Configuration - Param�tres RF
		"This page can configure parameters of RF input.",
		
		//page menu Exploitation - Etat de configuration
		"This page displays links to reach the configuration state of equipment.",

		//page menu Exploitation - Param�tres RF
		"This page displays parameters of RF input signal.",

		//page menu Evenements - Journal de bord
		"Events Log",
		"View events Log",
		"Number of events to purge if Log is full",
		"Clear events log",
		"Are - you sure to clear events log?",
		"Type",
		"Starting",
		"Ceasing",
		"Single",
		"Number of events in log file",
		"Number of events displayed in log file",
		"This page can configure, clear and display events log (limitation 1000 maximum events)",
		"Number maximum of events on each page",
		"Actions on log file",
		"Generate log file",
		"Are - you sure to generate log file?",
		"Log file displaying",
		"Warning! Log filter ON.",
		"Displaying of events",
		"Displaying of events with TSID value",
		"Displaying of events according with input type",

		//TRAPs
		"This page displays current events which caused a TRAP.<BR>This table is identical to <B>alarmeV1Table</B> defined in <B>SODIELECV2-ADMINISTRATION-V1-MIB</B>.",
		"Index",
		"Id",
		"Value",
		"Status",
		"Date",
		"Hour",
		"Acquit",
		"alarm-on",
		"alarm-off",
		"info",
		"no-acquit",
		"acquit",
		"destroy",
		"Acknowledge all traps",

		//Divers
		"Clearing command:",
		"Clear of synthesis parameters of service quality Log",

		//FTP
		"Error FTP length of string not allowed.",
		"Error FTP configuration not allowed in local mode.",
		"Error FTP value not allowed.",
		"Error FTP configuration not allowed in Power regulation.",
		"Error FTP configuration not allowed in 1+1 system.",
		"Error FTP configuration IP address not allowed.",
		"Error FTP configuration SWR alarm  not allowed.",
		"Error FTP configuration number of STS-ID for each pipe.",
		"Succeed configuration FTP",
		"Failed configuration FTP",
		"Configuration FTP ...",
		"Download of",
		"Checksum file KO",

		//Page menu configuration - Mode
		"Modem radio mode configuration",
		"Modem radio mode",
		"This page can configure mode in which radio modem will work..",
		{//ps8_msg_choix_mode_radio_m[NB_MAX_MODES_RADIO_MODEM]
			"Access Point",	//MODE_RADIO_MODEM_ACCESS_POINT
			"Station",		//MODE_RADIO_MODEM_STATION
			"Monitor",		//MODE_RADIO_MODEM_MONITOR
		},
		{//ps8_msg_choix_mode_radio_M[NB_MAX_MODES_RADIO_MODEM]
			"ACCESS POINT",	//MODE_RADIO_MODEM_ACCESS_POINT
			"STATION",		//MODE_RADIO_MODEM_STATION
			"MONITOR",		//MODE_RADIO_MODEM_MONITOR
		},
		"Do you confirm new mode selected?",
		"Choice of modem radio not allowed. You must configure equipment in bridge mode!",

		//Page menu configuration - Network
		"Network configuration",
		"This page can configure network.",
		"<B>Access Point</B> supports only bridge mode.",
//d: BE065.1 02/05/2012 (CM) - Correction libell� GB HTML
//		"<B>Station</B> supports bridge ou router mode.",
		"<B>Station</B> supports bridge or router mode.",
//f: BE065.1 02/05/2012 (CM) - Correction libell� GB HTML
		"<B>Monitor</B> supports only bridge mode.",
		"Network mode setting",
		"Network mode",
		{//ps8_msg_choix_mode_reseau[NB_MAX_MODES_NETWORK]
			"Bridge", //MODE_NETWORK_BRIDGE
			"Router", //MODE_NETWORK_ROUTER
		},
		"Bridge network setting",
		"LAN network setting",
		"WLAN network setting",
		"Ethernet MAC address",
		"Wireless MAC address",
		"Ethernet IP address",
		"Wireless IP address",
		"IP mode",
		{//ps8_msg_choix_mode_ip[NB_MAX_MODES_IP]
			"Static",		//MODE_IP_STATIQUE
			"DHCP client",	//MODE_IP_DHCP_CLIENT
		},
		"IP address",
		"Network mask",
		"Gateway",
		"Error during configuration",
		"Now, Configure correctly your equipment",
		"Address",
		"If you change IP parameters here, you may need to adjust your PC's network settings to access the network again.",
		{//ps8_msg_choix_interface_non_detecte[NB_MAX_INTERFACES]
			"",	//INTERFACE_AUTOMATIQUE
			"LAN interface no detected",				//INTERFACE_LAN
			"WLAN interface no detected",				//INTERFACE_WLAN
		},
		"Host name setting",
		"Host name",
		"DHCP fallback IP",
		"DHCP fallback IP is invalid.",
		"VLAN setting",
		"VLAN support",
		"VLAN name",
		"VLAN ID",
		"Reserve an no tagged LAN access",
		"Spanning Tree Protocol (STP)",

		//Page menu configuration - Wifi (Basic)
		"Wireless",
		"Wireless configuration",
		"This page can configure the wireless settings of this access.",
		"Basic wireless settings",
		"Advanced wireless settings",
		"Antenna settings",
		"SSID",
		"Enable secondary SSID",
		"Secondary SSID",
		"SSID mask",
		"802.11 mode",
		"Guard interval",
		{//ps8_msg_choix_intervalle_garde[NB_MAX_TYPE_GUARD_INTERVAL]
			"long",		//GUARD_INTERVAL_LONG
			"short",	//GUARD_INTERVAL_SHORT
		},
		"Channel spectrum width",
		"Channel mode",
		"Channel",
		{//ps8_msg_choix_mode_canal[NB_MAX_TYPE_SELECTION_CANAL]
			"iso-frequency",	//TYPE_SELECTION_CANAL_ISO
			"multi-frequency",	//TYPE_SELECTION_CANAL_MULTI
			"automatic",		//TYPE_SELECTION_CANAL_AUTO
		},
		"Transmitter power",
		"Data rate",
		"Received level alarm threshold",
		"Maximum associated stations number",
		"Wireless security mode",
		"Security mode",
		{//ps8_msg_choix_mode_securite_wifi[NB_MAX_MODES_SECURITE_WIFI]
			"None", //MODE_SECURITE_WIFI_AUCUN
			"WEP", //MODE_SECURITE_WIFI_WEP
			"WPA", //MODE_SECURITE_WIFI_WPA
			"WPA-TKIP", //MODE_SECURITE_WIFI_WPA_TKIP
			"WPA-AES", //MODE_SECURITE_WIFI_WPA_AES
			"WPA2", //MODE_SECURITE_WIFI_WPA2
			"WPA2-TKIP", //MODE_SECURITE_WIFI_WPA2_TKIP
			"WPA2-AES", //MODE_SECURITE_WIFI_WPA2_AES
		},
		"WEP",
		"WEP key length",
		{//ps8_msg_choix_longueur_cle_WEP[NB_MAX_WEP_KEY_LENGTH]
			"64 bit",	//WEP_KEY_LENGTH_64BIT
			"128 bit",	//WEP_KEY_LENGTH_128BIT
		},
		"WEP key type",
		{//ps8_msg_choix_type_cle_WEP[NB_MAX_KEY_TYPE]
			"HEXA",		//KEY_TYPE_HEXA
			"ASCII",	//KEY_TYPE_ASCII
		},
		{//ps8_msg_info_saisie_cle_WEP[NB_MAX_WEP_KEY_LENGTH][NB_MAX_KEY_TYPE]
			{//WEP_KEY_LENGTH_64BIT
				"10 HEXA digits",		//KEY_TYPE_HEXA
				"5 characters ASCII",	//KEY_TYPE_ASCII
			},
			{//WEP_KEY_LENGTH_128BIT
				"26 HEXA digits",		//KEY_TYPE_HEXA
				"13 characters ASCII",	//KEY_TYPE_ASCII
			},
		},
		"WEP key",
		"The key value is invalid.",
		"length applies to all keys",
		"type applies to all keys",
		"Display all WEP keys",
		"Default WEP Key",
		"Authentication",
		{//ps8_msg_choix_authentification_WEP[NB_MAX_WEP_AUTHENTIFICATION]
			"Open",			//WEP_AUTHENTIFICATION_OPEN
			"Shared key",	//WEP_AUTHENTIFICATION_SHARED_KEY
		},
		"WPA",
		{//ps8_msg_choix_authentification_WPA[NB_MAX_WPA_AUTHENTIFICATION]
			"PSK",	//WPA_AUTHENTIFICATION_PSK
			"EAP",	//WPA_AUTHENTIFICATION_EAP
		},
		"Group key update interval (GTK)",
		"PSK Key type",
		"PSK",
		"EAP",
		{//ps8_msg_info_saisie_PSK[NB_MAX_KEY_TYPE]
			"64 HEXA digits",		  //KEY_TYPE_HEXA
			"8 to 63 characters ASCII",//KEY_TYPE_ASCII
		},
		"Pre-shared key",
		"Display PSK key",
		"Configure a valid channel!",
		"EAP reauthentication period",
		"0 in order to disable",
		"RADIUS server IP address",
		"RADIUS server UDP port",
		"RADIUS server key",
		"EAP method",
		{//ps8_msg_choix_EAP_methode[NB_MAX_EAP_METHOD]
			"TTLS/PAP",		//EAP_METHOD__TTLS_PAP
			"TTLS/CHAP",	//EAP_METHOD__TTLS_CHAP
			"TTLS/EAP-MD5", //EAP_METHOD__TTLS_EAP_MD5
			"PEAP/MSCHAPv2",	//EAP_METHOD__PEAP_MSCHAPV2,
			"TLS",			//EAP_METHOD__TLS,
		},
		"EAP identity",
		"EAP user name",
		"EAP user password",
		"Certificate authority name (EAP-TLS)",
		"Certificate client name (EAP-TLS)",
		"Private key password (EAP-TLS)",
		"Remove a certificate",
		"None selected certificate",
		"Are you sure to remove this certificate?",
		"The EAP-TLS authentication is not functional.<BR>At least one of the certificates is not available.",
		"Display EAP key",
		"Transmitter power is configured with minimum value.",
		"Data rate is configured with automatic value.",

		//Page menu configuration - Wifi (Avanc�)
		"ACK timeout",
		"Preambule type",
		{//ps8_msg_choix_type_preambule[NB_MAX_WF_TYPE_PREAMBULE]
			"Short",	//WF_TYPE_PREAMBULE_SHORT
			"Long",		//WF_TYPE_PREAMBULE_LONG
		},
		"Fragmentation threshold",
		"RTS/CTS threshold",
		"RTS retry limit",
		"Beacon period",
		"WMM enabled",
		"DFS disabled",
		"Country code",
		{//ps8_msg_choix_country_id[NB_MAX_COUNTRY_ID]
			"FRANCE",				//COUNTRY_ID_FRANCE
			"AUSTRIA",				//COUNTRY_ID_AUSTRIA
			"BELGIUM",				//COUNTRY_ID_BELGIUM
			"BULGARIA",				//COUNTRY_ID_BULGARIA
			"CYPRUS",				//COUNTRY_ID_CYPRUS
			"CZECH REPUBLIC",		//COUNTRY_ID_CZECH_REPUBLIC
			"DENMARK",				//COUNTRY_ID_DENMARK
			"ESTONIA",				//COUNTRY_ID_ESTONIA
			"FINLAND",				//COUNTRY_ID_FINLAND
			"GERMANY",				//COUNTRY_ID_GERMANY
			"GREECE",				//COUNTRY_ID_GREECE
			"ICELAND",				//COUNTRY_ID_ICELAND
			"IRELAND",				//COUNTRY_ID_IRELAND
			"ITALY",				//COUNTRY_ID_ITALY
			"LATVIA",				//COUNTRY_ID_LATVIA
			"LITHUANIA",			//COUNTRY_ID_LITHUANIA
			"LUXEMBOURG",			//COUNTRY_ID_LUXEMBOURG
			"MALTA",				//COUNTRY_ID_MALTA
			"NETHERLANDS",			//COUNTRY_ID_NETHERLANDS
			"NORWAY",				//COUNTRY_ID_NORWAY
			"POLAND",				//COUNTRY_ID_POLAND
			"PORTUGAL",				//COUNTRY_ID_PORTUGAL
			"ROMANIA",				//COUNTRY_ID_ROMANIA
			"SLOVAKIA",				//COUNTRY_ID_SLOVAKIA
			"SLOVENIA",				//COUNTRY_ID_SLOVENIA
			"SPAIN",				//COUNTRY_ID_SPAIN
			"SWEDEN",				//COUNTRY_ID_SWEDEN
			"SWITZERLAND",			//COUNTRY_ID_SWITZERLAND
			"UNITED KINGDOM",		//COUNTRY_ID_UNITED_KINGDOM
			"USA",					//COUNTRY_ID_USA
			"USA PUBLIC SAFETY",	//COUNTRY_ID_PUBLIC_SAFETY
		},
		"Warning! A new country code causes changes in wireless settings:<BR> with mode 802.11g / channel 1 / antenna 1.",
		"Are you sure you want to configure a new country code ?",

		//Page menu configuration - Wifi (Antennes)
		"Antenna selection",
		"Transmitter antenna selection",
		{//ps8_msg_ABG_choix_antenne_tx[NB_MAX_ABG_SELECT_ANT_TX]
			"Antenna 1", //ABG_SELECT_TX_ANTENNE_1
			"Antenna 2", //ABG_SELECT_TX_ANTENNE_2
		},
		"Receiver antenna selection",
		{//ps8_msg_ABG_choix_antenne_rx[NB_MAX_ABG_SELECT_ANT_RX]
			"Antenna 1",	//ABG_SELECT_RX_ANTENNE_1
			"Antenna 2",	//ABG_SELECT_RX_ANTENNE_2
			"Diversity",	//ABG_SELECT_RX_DIVERSITY
		},
		{//ps8_msg_N_choix_antenne[NB_MAX_N_SELECT_ANTENNES]
			"Antenna 1",			//N_SELECT_ANTENNE_1
			"Antennas 1 & 2",		//N_SELECT_ANTENNES_1_ET_2
			"Antennas 1 & 2 & 3",	//N_SELECT_ANTENNES_1_ET_2_ET_3
		},
		"Antenna selection not allowed",
		"Antenna 1 is forced in this 802.11 mode.",

		//Page menu configuration - Hand-Off
		"Hand-Off",
		"Hand-off configuration",
		"This page allows hand-off function setting, only if the product is operating in <B>station</B>.",
		"Scanning mode",
		{//ps8_msg_choix_mode_scanning[NB_MAX_HO_MODES_SCANNING]
			"Automatic",	//HO_MODE_SCANNING_AUTO
			"Active",		//HO_MODE_SCANNING_ACTIVE,
			"Passive",		//HO_MODE_SCANNING_PASSIVE,
		},
		"Background scanning settings",
		"Enabled background scanning",
		"Background scanning recurrence period",
		"Level threshold for background scanning",
		"Foreground scanning settings",
		"Level threshold for foreground scanning",
		"Beacon missed threshold",
		"Hand-off in iso-frequency settings",
		"Minimum level threshold for new AP",
		"Beacon received threshold for next AP,<BR>with received level sufficient",
		"Minimum delay between two successive hand-off",
		"RSSI filtering setting",
//d: BE065.1 02/05/2012 (CM) - Correction libell� GB HTML
//		"filter type",
		"Filter type",
//f: BE065.1 02/05/2012 (CM) - Correction libell� GB HTML
		//ps8_msg_choix_type_filtre[NB_MAX_TYPES_FILTRAGE_RSSI]
		{
			"Filter 1", //FILTR_RSSI_1
			"Filter 2", //FILTR_RSSI_2
			"Filter 3", //FILTR_RSSI_3
			"Filter 4", //FILTR_RSSI_4
		},
		"Beacon interval configured on APs",
		
		//Page menu configuration - IP routing
		"IP routing",
		"IP routing configuration",
		"This page allows routing IP setting, only if the product is operating in <B>station</B> mode (router network mode).",
		"This tab can display active routing.",
		"This tab can configure static routing table setting (20 routes maximum).",
		"This tab can configure routing policy table setting (10 routes maximum).",
		"Static IP routing is currently",
		"Active routing",
		"Static IP routing table",
		"Add route",
		"Destination",
		"Metric",
		"Interface",
		{//ps8_msg_choix_interfaces_ip[NB_MAX_INTERFACES]
			"Automatic",	//INTERFACE_AUTOMATIQUE
			"LAN",			//INTERFACE_LAN
			"WLAN",			//INTERFACE_WLAN
		},
		"You must select one interface in order to add route.",
		"Static IP routing table is <B>complete<B>.",
		"Invalid host route.",
		"Invalid netmask route.",
		"Active routing policy",
		"None routing policy enabled.",
		"General",
		"Static routing",
		"Routing policy",
		"IP routing policy table",
		"Add a IP routing policy",
		"Modify a IP routing policy",
		"IP routing policy table is <B>complete<B>.",
		"Policy name",
		"IP source",
		"IP destination",
		"Packet length",
		"IP protocol",
		"Port source",
		"Port destination",
		"Class selector",
		"New gateway",
		"New class selector",
		{//ps8_msg_choix_routepolicy_protocole[NB_MAX_POLICYROUTE_PROTOCOLES]
			"UDP",	//POLICYROUTE_PROTOCOLE_UDP
			"TCP",	//POLICYROUTE_PROTOCOLE_TCP
			"ICMP",	//POLICYROUTE_PROTOCOLE_ICMP
		},
		{//ps8_msg_choix_class_selector[NB_MAX_CLASSSELECTOR]
			"CS0",	//CLASSSELECTOR_CS0
			"CS1",	//CLASSSELECTOR_CS1
			"CS2",	//CLASSSELECTOR_CS2
			"CS3",	//CLASSSELECTOR_CS3
			"CS4",	//CLASSSELECTOR_CS4
			"CS5",	//CLASSSELECTOR_CS5
			"CS6",	//CLASSSELECTOR_CS6
			"CS7",	//CLASSSELECTOR_CS7
		},
		{//ps8_msg_erreur_saisie_critere[NB_MAX_CRITERIA_POLICY]
			"IP source addresses range is not valid.",	//CRITERIAPOLICY_SRC_IP
			"IP destination addresses range is not valid.",	//CRITERIAPOLICY_DST_IP
			"Packet length range is not valid.",	//CRITERIAPOLICY_LENGTH_PACKET
			"Protocol is not valid.",				//CRITERIAPOLICY_IP_PROTOCOL
			"Port source range is not valid.",		//CRITERIAPOLICY_SRC_PORT
			"Port destination range is not valid.",	//CRITERIAPOLICY_DST_PORT
			"Class selector is not valid.",			//CRITERIAPOLICY_CLASS_SELECTOR
		},
		{//ps8_msg_erreur_saisie_action[NB_MAX_ACTIONS_POLICY]
			"New gateway is not valid.",	//ACTIONPOLICY_GATEWAY
			"New class selector is not valid.",	//ACTIONPOLICY_CLASS_SELECTOR
		},
		"At least, one criteria and one action must be selected.",
		"Criterias selected list",
		"Actions selected list",
		"RIPv2 routing",
		"This tab can configure protocol of RIPv2 dynamic routing.",
		"RIPv2 activation",
		"Used interfaces by RIPv2",
		"Availables interfaces",
		"RIP interfaces",
		{//ps8_msg_choix_interfaces_rip[NB_MAX_RIP_INTERFACES]
			"LAN",	//RIP_INTERF_LAN
			"WLAN",	//RIP_INTERF_WLAN
		},
		{//ps8_msg_choix_authentification_rip[NB_MAX_RIP_AUTHENTICATION]
			"None",			//RIP_AUTHENTICATION_NONE
			"Plain text",	//RIP_AUTHENTICATION_PLAIN_TEXT
			"MD5",			//RIP_AUTHENTICATION_MD5
		},
		"You have to select an available interface to configure for RIP.",
		"You have to select an interface to remove from RIP.",
		"You must select at least one interface in order to configure RIPv2.",

		//Page menu configuration - Serveur/Relai DHCP
		"DHCP server / relay",
		"DHCP server / relay configuration",
		"This page enables or disables DHCP function (Dynamic Host Configuration Protocol) on LAN interface, <BR> only if the product is operating in <B>station</B> mode (router network mode).",
		"<B>DHCP server</B> assigns IP adresses to clients which will connect to the LAN interface (only).",
		"<B>DHCP relay agent</B> relays DHCP requests from the LAN, which does not include a DHCP server, to a server DHCP located in an another network.",
		"DHCP function",
		{//ps8_msg_choix_fct_dhcp[NB_MAX_FCT_DHCP]
			"DHCP server/Relay OFF",	//FCT_DHCP_NONE
			"DHCP server ON",			//FCT_DHCP_SERVER
			"DHCP relay ON",			//FCT_DHCP_RELAY
		},
		"DHCP server settings",
		"DHCP IP address range",
		"addresses within the network mask",
		"DHCP lease time",
		"DHCP relay settings",
		"DHCP relay target IP",
		"The DHCP IP address (minimum) is not in the LAN subnet.",
		"The DHCP IP address (maximum) is not in the LAN subnet.",
		"The DHCP IP address (maximum) does not contain a valid host starting value.",
		"The DHCP address range should go from a minimum address to a maximum address, not maximum to minimum.",
		"The DHCP address range must not include the subnet broadcast address.",
		"The number of IP addresses in the range exceeds a maximum limit allowed.",
		"DHCP server no functional. Problem configuration!",
		"DHCP relay no functional. Problem configuration!",

		//Page Menu Configuration - NAT
		"NAT",
		"NAT configuration",
		"This page can configure NAT (Network Address Translation), <BR> only if the product is operating in <B>station</B> mode (router network mode).",
		"NAT enabled",
		"Actives NAT rules",
		"Private port",
		"Private IP address",
		"Public port",
		"Public IP address",
		"Public IP address (default)",
		"Add a new rule for port forwarding",
		"Add a new rule for adresses mapping",
		"Port forwarding",
		"Protocol",
		{//ps8_msg_choix_nat_protocole[NB_MAX_NAT_PROTOCOLES]
			"No selected",	//NAT_PROTOCOLE_NON_SELECTIONNE
			"UDP",			//NAT_PROTOCOLE_UDP
			"TCP",			//NAT_PROTOCOLE_TCP
		},
		"Alias IP",
		"Table of port forwarding rules is <B>complete</B>.",
		"Table of adresses mapping rules is <B>complete</B>.",
		"Addresses mapping",
		"You must select one protocol in order to add rule.",
		"NAT configuration not applied",
		"NAT no functional. Problem configuration!",

		//Page Menu Configuration - Multicast
		"Multicast",
		"Multicast configuration",
		"This page can configure IP multicast, <BR> only if the product is operating in <B>station</B> mode (router network mode).",
		"IGMP proxy enabled",
		"Table of enabled multicast sources (20 sources maximum)",
		"Add a new multicast source",
		"Table of enabled multicast sources is <B>complete</B>.",
		"Invalid netmask source.",
		"Network address",
		"Network mask",
		
		//Page Menu Configuration - SNMP
		"This page can configure the SNMP server.",
		"Community",
		"SNMP Managers",
		"This table can configure the IP Address of the SNMP managers (destination of TRAPs).",
		"This table can configure the IP Address of the SNMP managers (destination of TRAPs / INFORMs).",
		"Name",
		"Internet Address (IP)",
		"Settings of TRAPs",
		"Send TRAPs",
		"Settings of TRAPs / INFORMs",
		"Send TRAPs / INFORMs",
		"For SNMPv2c, traps are sent only once.",
		"Replay TRAPs",
		"Enable Sign of Life",
		"Cycle of Sign of Life",
		"TRAP emission Protocol",
		"This table can configure TRAP emission protocol.",
		"INFORM emission Protocol",
		"These settings can configure INFORM emission protocol.",
		"Number of send",
		"Cycle",
		"If the value is zero, the TRAP is sent until the SNMP manager acknowledges SNMP server.",
		"SNMP version selection",
		"SNMP version",
		{//ps8_msg_choix_version_snmp[NB_MAX_VERSIONS_SNMP]
			"SNMPv1",	//VERSION_SNMPV1
			"SNMPv2c",	//VERSION_SNMPV2C
		},
		"Notification type",
		{//ps8_msg_choix_type_notification[NB_MAX_TYPES_NOTIFICATION]
			"TRAP",		//TYPE_NOTIFICATION_TRAP
			"INFORM",	//TYPE_NOTIFICATION_INFORM
		},

		//Page Menu Exploitation - Wifi
		"This page displays parameters in <B>station</B> mode.",
		"This page displays parameters in <B>access point</B> mode.",
		"View wireless parameters",
		"BSSID",
		"RSSI",
		{//ps8_msg_choix_station_connexion[NB_MAX_STATUT_CONNEXION]
			"No connected",				//STATUT_CONNEXION__NOT_ASSOCIATED
			"No connected (invalid)",	//STATUT_CONNEXION__INVALID
			"No connected (none)",		//STATUT_CONNEXION__NONE
			"Connected",				 //STATUT_CONNEXION__ASSOCIATED
		},
		"Associated wireless clients list",
		"Associated",
		"No associated",
		"Activated WPA connection",
		"Channel in use",

		//Page Menu Exploitation - G�n�rale
		"This page displays general parameters.",
		"View general parameters",
		"Temperature",
		
		//Page Menu Exploitation - R�seau
		"This page displays network parameters.",
		"View network parameters",
		"DHCP in progress on WLAN access",
		"IP status",
		{//ps8_msg_choix_statut_ip[NB_MAX_STATUTS_IP]
			"Undefined",		//STATUT_IP__UNDEFINED
			"Static",			//STATUT_IP__STATIC
			"DHCP in progress",	//STATUT_IP__DHCP_IN_PROGRESS
			"DHCP success",		//STATUT_IP__SUCCESS_DHCP
			"DHCP failure",		//STATUT_IP__FAILURE_DHCP
		},

		//Page Menu Exploitation - client DHCP
		"DHCP clients",
		"This page displays DHCP clients on LAN interface, what are currently leasing IP addresses of DHCP server.",
		"View DHCP clients",
		"DHCP clients list",
		"Remaining lease (seconds)",
		"None DHCP client",
		
		//page menu Alarmes - Liste des alarmes
		{//ps8_msg_lib_groupe_alarmes[]
			"System alarms",				//GROUPE_AL_SYSTEME
#if TEST_DEBUG_EVENT
			"Debug alarms",					//GROUPE_AL_DEBUG
#endif
			"?",							//GROUPE_AL_NOT_USED
		},
		"This page displays alarms status.",
		{//ps8_msg_sous_titre_Vliste_groupe_alarmes[]
			"This page displays status of system alarms.",		//GROUPE_AL_SYSTEME
#if TEST_DEBUG_EVENT
			"This page displays status of debug alarms.",		//GROUPE_AL_DEBUG
#endif
			"?",												//GROUPE_AL_NOT_USED
		},
		"Clear all latched alarms",
		"See",

		//page menu Evenements - Configuration des �v�nements
		"Used, Log, Trap",
		"Log",
		"Used",
		"Synthesis",
		"Synthesis 1..3",
		"Synthesis 1",
		"Synthesis 2",
		"Synthesis 3",
		
		//Libell�s des Evenements
		{//ps8_msg_lib_evenement[NB_MAX_EVENEMENTS]
			"Synthesis alarm",		//EVT000_AL_SYNTHESE_1
			"Equipment fault",				//EVT001_DEFAUT_EQUIPEMENT
			"Temperature alarm",			//EVT002_AL_TEMPERATURE
//d: BE065.0 14/03/2012 (CM) - Correction bug libell� "LAN Ethernet 1/2 alarm" (GB)
//			"LAN Ethernet 2 alarm",			//EVT003_AL_ETHERNET_LAN_1
//			"LAN Ethernet 1 alarm",			//EVT004_AL_ETHERNET_LAN_2
			"LAN Ethernet 1 alarm",			//EVT003_AL_ETHERNET_LAN_1
			"LAN Ethernet 2 alarm",			//EVT004_AL_ETHERNET_LAN_2
//f: BE065.0 14/03/2012 (CM) - Correction bug libell� "LAN Ethernet 1/2 alarm" (GB)
			"Received level alarm",			//EVT005_AL_NIVEAU_RECU
			"No connected station alarm",	//EVT006_STATION_NON_CONNECTEE
			"Configuration error",			//EVT007_PROBLEME_CONFIGURATION
			"Switching to secondary SSID",		//EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE
			"Return to primary SSID",			//EVT009_RETOUR_SUR_SSID_PRIMAIRE
			"No NTP server available alarm",	//EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE
			"Radar detected on channel",//EVT011_RADAR_DETECTE_SUR_CANAL
			"Switching to channel",		//EVT012_BASCULEMENT_VERS_CANAL
			"Connection of the station",	//EVT013_CONNEXION_STATION
			"Disconnection of the station",	//EVT014_DECONNEXION_STATION
			"Connection on the access point",		//EVT015_CONNEXION_ACCESS_POINT
			"Disconnection of the access point",	//EVT016_DECONNEXION_ACCESS_POINT
			"EVT017_RESERVE",			//EVT017_RESERVE
			"EVT018_RESERVE",			//EVT018_RESERVE
			"EVT019_RESERVE",			//EVT019_RESERVE
			"EVT020_RESERVE",			//EVT020_RESERVE
			"EVT021_RESERVE",			//EVT021_RESERVE
			"EVT022_RESERVE",			//EVT022_RESERVE
			"EVT023_RESERVE",			//EVT023_RESERVE
			"EVT024_RESERVE",			//EVT024_RESERVE
			"EVT025_RESERVE",			//EVT025_RESERVE
			"EVT026_RESERVE",			//EVT026_RESERVE
			"EVT027_RESERVE",			//EVT027_RESERVE
			"EVT028_RESERVE",			//EVT028_RESERVE
			"EVT029_RESERVE",			//EVT029_RESERVE
			"EVT030_RESERVE",			//EVT030_RESERVE
			"EVT031_RESERVE",			//EVT031_RESERVE
			"EVT032_RESERVE",			//EVT032_RESERVE
			"EVT033_RESERVE",			//EVT033_RESERVE
			"EVT034_RESERVE",			//EVT034_RESERVE
			"EVT035_RESERVE",			//EVT035_RESERVE
			"EVT036_RESERVE",			//EVT036_RESERVE
			"EVT037_RESERVE",			//EVT037_RESERVE
			"EVT038_RESERVE",			//EVT038_RESERVE
			"EVT039_RESERVE",			//EVT039_RESERVE
			"EVT040_RESERVE",			//EVT040_RESERVE
			"EVT041_RESERVE",			//EVT041_RESERVE
			"EVT042_RESERVE",			//EVT042_RESERVE
			"EVT043_RESERVE",			//EVT043_RESERVE
			"EVT044_RESERVE",			//EVT044_RESERVE
			"EVT045_RESERVE",			//EVT045_RESERVE
			"EVT046_RESERVE",			//EVT046_RESERVE
			"EVT047_RESERVE",			//EVT047_RESERVE
			"EVT048_RESERVE",			//EVT048_RESERVE
			"EVT049_RESERVE",			//EVT049_RESERVE
			"EVT050_RESERVE",			//EVT050_RESERVE
			"EVT051_RESERVE",			//EVT051_RESERVE
			"EVT052_RESERVE",			//EVT052_RESERVE
			"EVT053_RESERVE",			//EVT053_RESERVE
			"EVT054_RESERVE",			//EVT054_RESERVE
			"EVT055_RESERVE",			//EVT055_RESERVE
			"EVT056_RESERVE",			//EVT056_RESERVE
			"EVT057_RESERVE",			//EVT057_RESERVE
			"EVT058_RESERVE",			//EVT058_RESERVE
			"EVT059_RESERVE",			//EVT059_RESERVE
			"EVT060_RESERVE",			//EVT060_RESERVE
			"EVT061_RESERVE",			//EVT061_RESERVE
			"EVT062_RESERVE",			//EVT062_RESERVE
			"EVT063_RESERVE",			//EVT063_RESERVE
			"EVT064_RESERVE",			//EVT064_RESERVE
			"EVT065_RESERVE",			//EVT065_RESERVE
			"EVT066_RESERVE",			//EVT066_RESERVE
			"EVT067_RESERVE",			//EVT067_RESERVE
			"EVT068_RESERVE",			//EVT068_RESERVE
			"EVT069_RESERVE",			//EVT069_RESERVE
			"EVT070_RESERVE",			//EVT070_RESERVE
			"EVT071_RESERVE",			//EVT071_RESERVE
			"EVT072_RESERVE",			//EVT072_RESERVE
			"EVT073_RESERVE",			//EVT073_RESERVE
			"EVT074_RESERVE",			//EVT074_RESERVE
			"EVT075_RESERVE",			//EVT075_RESERVE
			"EVT076_RESERVE",			//EVT076_RESERVE
			"EVT077_RESERVE",			//EVT077_RESERVE
			"EVT078_RESERVE",			//EVT078_RESERVE
			"EVT079_RESERVE",			//EVT079_RESERVE
			"EVT080_RESERVE",			//EVT080_RESERVE
			"EVT081_RESERVE",			//EVT081_RESERVE
			"EVT082_RESERVE",			//EVT082_RESERVE
			"EVT083_RESERVE",			//EVT083_RESERVE
			"EVT084_RESERVE",			//EVT084_RESERVE
			"EVT085_RESERVE",			//EVT085_RESERVE
			"EVT086_RESERVE",			//EVT086_RESERVE
			"EVT087_RESERVE",			//EVT087_RESERVE
			"EVT088_RESERVE",			//EVT088_RESERVE
			"EVT089_RESERVE",			//EVT089_RESERVE
			"EVT090_RESERVE",			//EVT090_RESERVE
			"EVT091_RESERVE",			//EVT091_RESERVE
			"EVT092_RESERVE",			//EVT092_RESERVE
			"EVT093_RESERVE",			//EVT093_RESERVE
			"EVT094_RESERVE",			//EVT094_RESERVE
			"EVT095_RESERVE",			//EVT095_RESERVE
			"EVT096_RESERVE",			//EVT096_RESERVE
			"EVT097_RESERVE",			//EVT097_RESERVE
			"EVT098_RESERVE",			//EVT098_RESERVE
			"EVT099_RESERVE",			//EVT099_RESERVE
			"EVT100_RESERVE",			//EVT100_RESERVE
			"EVT101_RESERVE",			//EVT101_RESERVE
			"EVT102_RESERVE",			//EVT102_RESERVE
			"EVT103_RESERVE",			//EVT103_RESERVE
			"EVT104_RESERVE",			//EVT104_RESERVE
			"EVT105_RESERVE",			//EVT105_RESERVE
			"EVT106_RESERVE",			//EVT106_RESERVE
			"EVT107_RESERVE",			//EVT107_RESERVE
			"EVT108_RESERVE",			//EVT108_RESERVE
			"EVT109_RESERVE",			//EVT109_RESERVE
			"Clear events log",			//EVT110_JOURNAL_BORD_EFFACE
			"Clear all latched alarms",	//EVT111_INF_RAZ_ALARMES_MEMO
			"New configuration",		//EVT112_EVOLUTION_CONFIGURATION
			"Remote restart equipment",	//EVT113_ORDRE_RESET_TELECOMMANDE
			"EVT114_RESERVE",			//EVT114_RESERVE
			"EVT115_RESERVE",			//EVT115_RESERVE
			"EVT116_RESERVE",			//EVT116_RESERVE
			"EVT117_RESERVE",			//EVT117_RESERVE
			"EVT118_RESERVE",			//EVT118_RESERVE
			"EVT119_RESERVE",			//EVT119_RESERVE
			"EVT120_RESERVE",			//EVT120_RESERVE
			"EVT121_RESERVE",			//EVT121_RESERVE
			"EVT122_RESERVE",			//EVT122_RESERVE
			"EVT123_RESERVE",			//EVT123_RESERVE
			"EVT124_RESERVE",			//EVT124_RESERVE
			"EVT125_RESERVE",			//EVT125_RESERVE
			"EVT126_RESERVE",			//EVT126_RESERVE
			"EVT127_RESERVE",			//EVT127_RESERVE
			"EVT128_RESERVE",			//EVT128_RESERVE
			"EVT129_RESERVE",			//EVT129_RESERVE
			"EVT130_RESERVE",			//EVT130_RESERVE
			"EVT131_RESERVE",			//EVT131_RESERVE
			"EVT132_RESERVE",			//EVT132_RESERVE
			"EVT133_RESERVE",			//EVT133_RESERVE
			"EVT134_RESERVE",			//EVT134_RESERVE
			"EVT135_RESERVE",			//EVT135_RESERVE
			"EVT136_RESERVE",			//EVT136_RESERVE
			"EVT137_RESERVE",			//EVT137_RESERVE
			"EVT138_RESERVE",			//EVT138_RESERVE
			"EVT139_RESERVE",			//EVT139_RESERVE
			"EVT140_RESERVE",			//EVT140_RESERVE
			"EVT141_RESERVE",			//EVT141_RESERVE
			"EVT142_RESERVE",			//EVT142_RESERVE
			"EVT143_RESERVE",			//EVT143_RESERVE
			"EVT144_RESERVE",			//EVT144_RESERVE
			"EVT145_RESERVE",			//EVT145_RESERVE
			"EVT146_RESERVE",			//EVT146_RESERVE
			"EVT147_RESERVE",			//EVT147_RESERVE
			"EVT148_RESERVE",			//EVT148_RESERVE
			"EVT149_RESERVE",			//EVT149_RESERVE
			"EVT150_RESERVE",			//EVT150_RESERVE
			"EVT151_RESERVE",			//EVT151_RESERVE
			"EVT152_RESERVE",			//EVT152_RESERVE
			"EVT153_RESERVE",			//EVT153_RESERVE
			"EVT154_RESERVE",			//EVT154_RESERVE
			"EVT155_RESERVE",			//EVT155_RESERVE
			"EVT156_RESERVE",			//EVT156_RESERVE
			"EVT157_RESERVE",			//EVT157_RESERVE
			"EVT158_RESERVE",			//EVT158_RESERVE
			"EVT159_RESERVE",			//EVT159_RESERVE
			"EVT160_RESERVE",			//EVT160_RESERVE
			"EVT161_RESERVE",			//EVT161_RESERVE
			"EVT162_RESERVE",			//EVT162_RESERVE
			"EVT163_RESERVE",			//EVT163_RESERVE
			"EVT164_RESERVE",			//EVT164_RESERVE
			"EVT165_RESERVE",			//EVT165_RESERVE
			"EVT166_RESERVE",			//EVT166_RESERVE
			"EVT167_RESERVE",			//EVT167_RESERVE
			"EVT168_RESERVE",			//EVT168_RESERVE
			"EVT169_RESERVE",			//EVT169_RESERVE
			"EVT170_RESERVE",			//EVT170_RESERVE
			"EVT171_RESERVE",			//EVT171_RESERVE
			"EVT172_RESERVE",			//EVT172_RESERVE
			"EVT173_RESERVE",			//EVT173_RESERVE
			"EVT174_RESERVE",			//EVT174_RESERVE
			"Equipment ON",				//EVT175_INF_EQUIPEMENT_ON
			"Sign of life",				//EVT176_INF_SIGNE_DE_VIE
			"EVT177_RESERVE",			//EVT177_RESERVE
			"EVT178_RESERVE",			//EVT178_RESERVE
			"EVT179_RESERVE",			//EVT179_RESERVE
		},

		//Libell�s suppl�mentaires sur les �v�nements
		{//ps8_msg_lib_errorconfig[NB_MAX_ERRORCONFIG]
			"setup default",		//ERRORCONFIG_PASSAGE_PAR_DEFAUT
			"no applied",	//ERRORCONFIG_INSTALLATION
		},
		
	},
};

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


//=====================================================================================
// Fonction		: InitModule_Langue
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/07/2007 -
// Description	: Initialisation du module Langue
//=====================================================================================
void InitModule_Langue(void)
{
	pt_tb_msg = &t_tb_msg [0]; //INIT	
}/*InitModule_Langue*/

