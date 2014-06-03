/*========================================================================*/
/* NOM DU FICHIER  : config.h		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 25/09/2009											  */
/* Libelle         : Base de donn�es: configuration de l'�quipement		  */
/* Projet          : WRM100                                               */
/* Indice          : BE064                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 25/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Int�gration configuration hostname
// - Int�gration configuration par DHCP client
//BE005 14/01/2010 CM
// - Int�gration serveur DHCP + relai DHCP
//BE006 20/01/2010 CM
// - Modification d�finition de certains fichiers de la base de donn�es
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du syst�me
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
// - Correction configuration / defaut de la station (champs: u8_type_selection_canal)
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE013 26/02/2010 CM
// - Int�gration gestion des �v�nements
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
// - Ajout fonction g�n�rique test masque sous-r�seau
// - Ajout fonction g�n�rique test ip de type NET
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE034 28/06/2010 CM
// - Correction configuration par d�faut suite modif BE032
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		userhigh / usermiddle / userlow
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE039 26/08/2010 CM
// - Int�gration des modifications release_v2
//BE040 13/09/2010 CM
// - Ajout des param�tres de configuration hand-off
// - Integration de la gestion du wifi pour la carte compatible � 802.11n
//BE042 07/10/2010 CM
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
// - Correction configuration mode 802.11 (associ� au driver-N)
// - Ajout gestion liste des fr�quences r�glementaires
// - Ajout param�tre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
// - Integration des param�tres handoff
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque acc�s
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non valid�e par d�faut
//	+ aussi disponible sur ACCESS POINT
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activ�)
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification une seule antenne autoris�e dans les modes 802.11abg (Driver-N)
// - Modification plage de timeout ACK (Driver-N)
//BE054 11/01/2011 CM
// - Suppression du fichier de configuration advwf
// - Modification d�bit emission MCS0 � MCS15 autoris� quelque soit nb antennes
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE058 21/01/2011 CM
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout nouveaux �v�nements li�s au DFS
// - Ajout configuration "desactivation DFS" (WRM100-N)
// - Correction bug incoh�rence dans configuration par d�faut
//		canal iso: 1 (non valid) --> 36 (valid) en mode 11a
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout des �venements de connexion et d�connexion d'une STATION
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout fonction impose config au d�marrage (pour chaque bdd de config)
// - Ajout configuration date/heure au d�marrage de l'�quipement
//BE061 10/05/2011
// - Ajout fonction ImposeInitConfigXXXX si configuration incoh�rente pour �viter de passer en configuration par d�faut
//		si par exemple on vient du logiciel WRM100-MESH
// - Ajout restauration de la configuration  par d�faut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
// - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//BE064.0 25/11/2011 (CM)
// - Correction bug de la configuration par sFTP (lors changement countryId)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CONFIG
#define _CONFIG_EXT
#else
#define _CONFIG_EXT extern
#endif

//Fonction: PassageConfigDefaut
#define MODE_PASSAGECONFIGDEFAUT_TOTAL		0
#define MODE_PASSAGECONFIGDEFAUT_SANS_IP	1

/*_____III - DEFINITIONS DE TYPES_________________________________________*/


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//d: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//=====================================================================================
// Fonction		: OrderSetNewEquipment
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 23/05/2011 -
// Description	: Ordre signalisation nouveau equipement
//=====================================================================================
void OrderSetNewEquipment(void);

//=====================================================================================
// Fonction		: u8TestNewEquipment
// Entrees		: rien
// Sortie		: <loc_u8_resultat>: TRUE pr�sent, sinon FALSE
// Auteur		: CM - 23/05/2011 -
// Description	: Test si nouvel equipement d�tect�
//=====================================================================================
u8sod u8TestNewEquipment(void);
//f: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

//d: BE061 10/05/2011 - Ajout restauration de la configuration  par d�faut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//=====================================================================================
// Fonction		: OrderSetConfigDefaut
// Entrees		: <loc_u8_idx_cfgfile> : index de la configuration � forcer par d�faut
// Sortie		: rien
// Auteur		: CM - 11/05/2011 -
// Description	: Ordre de forcer configuration par d�faut
//=====================================================================================
void OrderSetConfigDefaut(u8sod loc_u8_idx_cfgfile);

//=====================================================================================
// Fonction		: ClearSetConfigDefaut
// Entrees		: <loc_u8_idx_cfgfile> : index de la configuration � forcer par d�faut
// Sortie		: rien
// Auteur		: CM - 11/05/2011 -
// Description	: Suppression du fichier qui donne l'ordre de passer en configuration par d�faut
//=====================================================================================
void ClearSetConfigDefaut(u8sod loc_u8_idx_cfgfile);

//=====================================================================================
// Fonction		: u8TestSetConfigDefaut
// Entrees		: <loc_u8_idx_cfgfile> : index de la configuration � forcer par d�faut
// Sortie		: <loc_u8_resultat>: TRUE pr�sent, sinon FALSE
// Auteur		: CM - 11/05/2011 -
// Description	: Test si si ordre de forcer la config par d�faut
//=====================================================================================
u8sod u8TestSetConfigDefaut(u8sod loc_u8_idx_cfgfile);
//f: BE061 10/05/2011 - Ajout restauration de la configuration  par d�faut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).


//=====================================================================================
// Fonction		: SignalNewConfig
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
// Sortie		: rien
// Auteur		: CM - 28/09/2009 -
// Description	: Signale une �volution susceptible de la configuration d�fini par son index
//=====================================================================================
void SignalNewConfig(u8sod loc_u8_idx_cfgfile);

//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
//=====================================================================================
// Fonction		: SignalNewCfgFTP
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/11/2011 -
// Description	: Signale une configuration par FTP
//=====================================================================================
void SignalNewCfgFTP(void);
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)

//=====================================================================================
// Fonction		: u8FillConfigFile
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigFile(u8sod loc_u8_idx_cfgfile, S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigFile
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigFile(u8sod loc_u8_idx_cfgfile, S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigFile
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Test des donn�es de la structure S_STRUCT_CONFIGURATION pour le fichier d�fini par son index
//=====================================================================================
u8sod u8TestConfigFile(u8sod loc_u8_idx_cfgfile, S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigChaineSansEspace
// Entrees		: <loc_ps8_chaine< : pointeur sur la chaine de caract�res � tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 06/01/2010 -
// Description	: Test si la chaine contient ou non des espaces (ou tabulation)
//=====================================================================================
u8sod u8TestConfigChaineSansEspace(s8sod *loc_ps8_chaine);

//=====================================================================================
// Fonction		: u8TestConfigChaineValide
// Entrees		: <loc_ps8_chaine< : pointeur sur la chaine de caract�res � tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 03/10/2008 -
// Description	: Test la validit� des caract�res dans la chaine
//=====================================================================================
u8sod u8TestConfigChaineValide(s8sod *loc_ps8_chaine);

//=====================================================================================
// Fonction		: SignalConfig_InProgress
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Signale une configuration en cours
//=====================================================================================
void SignalConfig_InProgress(void);

//=====================================================================================
// Fonction		: ClearConfig_InProgress
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Annule la configuration en cours
//=====================================================================================
void ClearConfig_InProgress(void);

//=====================================================================================
// Fonction		: u8TestConfig_InProgress
// Entrees		: rien
// Sortie		: <loc_u8_resultat>  : configuration en cours alors TRUE sinon FALSE
// Auteur		: CM - 02/12/2010 -
// Description	: Test la validit� des caract�res dans la chaine
//=====================================================================================
u8sod u8TestConfig_InProgress(void);

//=====================================================================================
// Fonction		: u8DiffConfig
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: GT - 25/09/2007 -
// Description	: V�rifie si les config en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfig(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8FillConfigAdmin
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Admin du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigAdmin
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Admin dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigAdmin
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des donn�es Administration de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigAdmin
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Admin SRC==>DST
//=====================================================================================
void CopyConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigAdmin
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 11/10/2010 -
// Description	: V�rifie si les config Admin en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigAdmin(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigSyslog
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 28/01/2010 -
// Description	: V�rifie si les config system log en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigSyslog(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigModeRSSI
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 16/02/2011 -
// Description	: V�rifie si les config mode RSSI en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigModeRSSI(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigNtp
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 01/02/2010 -
// Description	: V�rifie si les config client NTP en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigNtp(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigPassword
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 02/07/2010 -
// Description	: V�rifie si les config password en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigPassword(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8FillConfigConstructeur
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Constructeur du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigConstructeur
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Constructeur dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigConstructeur
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des donn�es Constructeur de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigConstructeur
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration constructeur SRC==>DST
//=====================================================================================
void CopyConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigConstructeur
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 11/10/2010 -
// Description	: V�rifie si les config Constructeur en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigConstructeur(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8FillConfigSnmp
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration SNMP du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigSnmp
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Snmp dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigSnmp
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des donn�es Snmp de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigSnmp
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Snmp SRC==>DST
//=====================================================================================
void CopyConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigSnmp
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 19/10/2007 -
// Description	: V�rifie si les config SNMP en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigSnmp(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);


//=====================================================================================
// Fonction		: u8FillConfigGeneral
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration G�n�rale du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigGeneral
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration G�n�rale dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigGeneral
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des donn�es G�n�ral de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigGeneral
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration G�n�ral SRC==>DST
//=====================================================================================
void CopyConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigGeneral
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config General en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigGeneral(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigGene_NetworkBridge
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config General (network bridge) en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigGene_NetworkBridge(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigGene_NetworkRouter
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config General (network router) en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigGene_NetworkRouter(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigGene_FctDHCP
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 15/01/2010 -
// Description	: V�rifie si les config General (dhcp) en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigGene_FctDHCP(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8TestFctDHCP_Fonctionnelle
// Entrees		: <loc_ps_config> config de l'�quipement � tester
// Sortie		: <loc_u8_return> TRUE si OK ou FALSE sinon 
// Auteur		: CM - 15/01/2010 -
// Description	: Test si la configuration DHCP est fonctionnelle
//=====================================================================================
u8sod u8TestFctDHCP_Fonctionnelle(S_STRUCT_CONFIGURATION * loc_ps_config);

//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incoh�rente pour �viter de passer en configuration par d�faut
//=====================================================================================
// Fonction		: u8ImposeInitConfigGeneral
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: nouvelle config (si TRUE), sinon FALSE
// Auteur		: CM - 10/05/2011 -
// Description	: impose configuration au d�marrage (config g�n�rale)
//=====================================================================================
u8sod u8ImposeInitConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config);
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incoh�rente pour �viter de passer en configuration par d�faut




//=====================================================================================
// Fonction		: u8FillConfigWifi
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Wifi du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigWifi
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Wifi dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ImposeConfigWifiSiIncoherente
// Entrees		: <loc_ps_config> : config qu'il faut mettre � jour
// Sortie		: rien
// Auteur		: CM - 28/09/2009 -
// Description	: Impose certains param�tres si config Wifi incoh�rente
//=====================================================================================
void ImposeConfigWifiSiIncoherente(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigWifi
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 28/28/2009 -
// Description	: Test des donn�es Wifi de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigWifi
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Wifi SRC==>DST
//=====================================================================================
void CopyConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigWifi
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config advWifi en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigWifi(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigFrequence
// Entrees		: <loc_ps_config1> config n�1 � comparer (courante)
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config frequence (Wifi) en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigFrequence(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8DiffConfigModeSecuWifi
// Entrees		: <loc_ps_config1> config n�1 � comparer (courante)
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config Wifi en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigModeSecuWifi(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incoh�rente pour �viter de passer en configuration par d�faut
//=====================================================================================
// Fonction		: u8ImposeInitConfigWifi
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: nouvelle config (si TRUE), sinon FALSE
// Auteur		: CM - 10/05/2011 -
// Description	: impose configuration au d�marrage (config wifi)
//=====================================================================================
u8sod u8ImposeInitConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config);
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incoh�rente pour �viter de passer en configuration par d�faut

//=====================================================================================
// Fonction		: u8IsMode80211ag
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode est 802.11a ou 802.11g
//=====================================================================================
u8sod u8IsMode80211ag(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211b
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode est 802.11b
//=====================================================================================
u8sod u8IsMode80211b(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211n
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode est 802.11n
//=====================================================================================
u8sod u8IsMode80211n(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211ng
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: VuHai - 13/05/2014 -
// Description	: Test si configuration du mode est 802.11na
//=====================================================================================
u8sod u8IsMode80211ng(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211na
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: VuHai - 13/05/2014 -
// Description	: Test si configuration du mode est 802.11ng
//=====================================================================================
u8sod u8IsMode80211na(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211nHT20
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 14/01/2010 -
// Description	: Test si configuration du mode est 802.11nHT20
//=====================================================================================
u8sod u8IsMode80211nHT20(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211nHT40
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 16/12/2010 -
// Description	: Test si configuration du mode est 802.11nHT40
//=====================================================================================
u8sod u8IsMode80211nHT40(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211ac
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: VuHai - 23/05/2014 -
// Description	: Test si configuration du mode est 802.11ac
//=====================================================================================
u8sod u8IsMode80211ac(u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8IsMode80211Valid_ForAntennaTX
// Entrees		: <loc_u8_mode_802_11x> : mode
//				: <loc_u8_nb_antenne_tx> : nombre d'antennes TX
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode 802.11 est valide en fonction de l'antenne configur�e
//=====================================================================================
u8sod u8IsMode80211Valid_ForAntennaTX(u8sod loc_u8_mode_802_11x, u8sod loc_u8_nb_antenne_tx);

//=====================================================================================
// Fonction		: u8Test_ABG_ConfigDataRate
// Entrees		: <loc_u8_data_rate> : debit
//				  <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_resultat> TRUE si ok ou FALSE sinon 
// Auteur		: CM - 14/01/2011 -
// Description	: Test si configuration du d�bit valide (WRM100_ABG)
//=====================================================================================
u8sod u8Test_ABG_ConfigDataRate(u8sod loc_u8_data_rate, u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8Test_N_ConfigDataRate
// Entrees		: <loc_u8_data_rate> : debit
//				  <loc_u8_mode_802_11x> : mode
//				: <loc_u8_nb_antennes_tx> : nombre d'antennes TX
// Sortie		: <loc_u8_resultat> TRUE si ok ou FALSE sinon 
// Auteur		: CM - 14/01/2011 -
// Description	: Test si configuration du d�bit valide (WRM100_N)
//=====================================================================================
u8sod u8Test_N_ConfigDataRate(u8sod loc_u8_data_rate, u8sod loc_u8_mode_802_11x, u8sod loc_u8_nb_antennes_tx);

//=====================================================================================
// Fonction		: u8TestCfg_N_AckTimeout
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 28/28/2009 -
// Description	: Test des donn�es Wifi ack timeout (Driver-N) de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestCfg_N_AckTimeout(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8GetNbStream
// Entrees		: <loc_u8_ant_N_selection> : config d'antenne
// Sortie		: <loc_u8_nb_stream> : nombre de stream associe � la config 
// Auteur		: CM - 08/10/2010 -
// Description	: D�termine le nombre de stream en fonction de la configuration d'antenne
//=====================================================================================
u8sod u8GetNbStream(u8sod loc_u8_ant_N_selection);

//=====================================================================================
// Fonction		: u8FillConfigRouting
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Routing du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigRouting
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Routing dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ImposeConfigRoutingSiIncoherente
// Entrees		: <loc_ps_config> : config qu'il faut mettre � jour
// Sortie		: rien
// Auteur		: CM - 24/09/2008 -
// Description	: Impose certains param�tres si config Routing incoh�rente
//=====================================================================================
void ImposeConfigRoutingSiIncoherente(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigRouting
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des donn�es Routing de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigRouting
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration G�n�ral SRC==>DST
//=====================================================================================
void CopyConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigRouting
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: V�rifie si les config routing en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigRouting(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8FillConfigNAT
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Lecture de la configuration NAT du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigNAT
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Ecriture de la configuration NAT dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigNAT
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Test de la configuration NAT de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigNAT
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 10/02/2010 -
// Description	: Copier configuration NAT SRC==>DST
//=====================================================================================
void CopyConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigNAT
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 10/02/2010 -
// Description	: V�rifie si les config NAT en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigNAT(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8TestNAT_Fonctionnelle
// Entrees		: <loc_ps_config> config de l'�quipement � tester
//				: <loc_u32_adr_ip_public_default> : adresse IP publique par d�faut
//				: <loc_u32_mask_ip_public_default> : adresse IP publique par d�faut
// Sortie		: <loc_u8_return> TRUE si OK ou FALSE sinon 
// Auteur		: CM - 15/02/2010 -
// Description	: Test si la configuration NAT est fonctionnelle
//=====================================================================================
u8sod u8TestNAT_Fonctionnelle(S_STRUCT_CONFIGURATION * loc_ps_config, u32sod loc_u32_adr_ip_public_default, u32sod loc_u32_mask_ip_public_default);

//=====================================================================================
// Fonction		: u8FillConfigMulticast
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Lecture de la configuration Multicast du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigMulticast
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Ecriture de la configuration Multicast dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigMulticast
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test de la configuration Multicast de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigMulticast
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Copier configuration Multicast SRC==>DST
//=====================================================================================
void CopyConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigMulticast
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 30/03/2010 -
// Description	: V�rifie si les config Multicast en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigMulticast(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8FillConfigTabEvt
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 26/02/2010 -
// Description	: Lecture de la configuration du tableau des �v�nements du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigTabEvt
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 26/02/2010 -
// Description	: Ecriture de la configuration du tableau des �v�nements dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigTabEvt
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 26/02/2010 -
// Description	: Test de la configuration du tableau des �v�nements de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigTabEvt
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 26/02/2010 -
// Description	: Copier configuration du tableau des �v�nements  SRC==>DST
//=====================================================================================
void CopyConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigTabEvt
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 26/02/2010 -
// Description	: V�rifie si les config du tableau des �v�nements  en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigTabEvt(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8ImposeInitConfigTabEvt
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: nouvelle config (si TRUE), sinon FALSE
// Auteur		: CM - 25/03/2011 -
// Description	: impose configuration au d�marrage (config du tableau des �v�nements)
//=====================================================================================
u8sod u8ImposeInitConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8GetEventAction
// Entrees		: <loc_u16_valeur_action>
//				  <loc_u8_index_action>
// Sortie		: <loc_i_resultat> : TRUE valide / FALSE non valide
// Auteur		: CM - 29/06/2007 -
// Description	: retourne si action de l'evt valide
//=====================================================================================
u8sod u8GetEventAction(u16sod loc_u16_valeur_action, u8sod	loc_u8_index_action);

//=====================================================================================
// Fonction		: SetEventAction
// Entrees		: <loc_u16_valeur_action< : valeur action de l'�vt � modifier
//				  <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 29/06/2007 -
// Description	: Force action de l'evt valide
//=====================================================================================
void SetEventAction(u16sod *loc_pu16_valeur_action, u8sod	loc_u8_index_action);

//=====================================================================================
// Fonction		: ResetEventAction
// Entrees		: <loc_u16_valeur_action< : valeur action de l'�vt � modifier
//				  <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 29/06/2007 -
// Description	: Reset action de l'evt valide
//=====================================================================================
void ResetEventAction(u16sod *loc_pu16_valeur_action, u8sod	loc_u8_index_action);

//=====================================================================================
// Fonction		: SetAllEventsAction
// Entrees		: <loc_ps_config< : config de l'�quipement
//				: <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 26/02/2010
// Description	: Force tous les �v�nements � une action
//=====================================================================================
void SetAllEventsAction(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_index_action);

//=====================================================================================
// Fonction		: ResetAllEventsAction
// Entrees		: <loc_ps_config< : config de l'�quipement
//				: <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 26/02/2010
// Description	: Reset tous les �v�nements � une action
//=====================================================================================
void ResetAllEventsAction(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_index_action);

//=====================================================================================
// Fonction		: u8FillConfigHandoff
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 15/09/2010 -
// Description	: Lecture de la configuration Handoff du fichier d�fini par son index
//=====================================================================================
u8sod u8FillConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigHandoff
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 15/09/2010 -
// Description	: Ecriture de la configuration Handoff dans le fichier d�fini par son index
//=====================================================================================
u8sod u8EditConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: ImposeConfigHandoffSiIncoherente
// Entrees		: <loc_ps_config> : config qu'il faut mettre � jour
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Impose certains param�tres si config Handoff incoh�rente
//=====================================================================================
void ImposeConfigHandoffSiIncoherente(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigHandoff
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/09/2010 -
// Description	: Test des donn�es Handoff de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: CopyConfigHandoff
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Copier configuration Handoff SRC==>DST
//=====================================================================================
void CopyConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst);

//=====================================================================================
// Fonction		: u8DiffConfigHandoff
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 15/09/2010 -
// Description	: V�rifie si les config Handoff en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigHandoff(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: u8AddRouteStatic
// Entrees		: <loc_ps_config< : config de l'�quipement
//				  <loc_ps_route<: route � ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Ajout d'une route statique
//=====================================================================================
u8sod u8AddRouteStatic(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_IP_ROUTE_STATIC *loc_ps_route);

//=====================================================================================
// Fonction		: u8TestConfigRouteStatic
// Entrees		: <loc_ps_route< : route IP
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 16/10/2009 -
// Description	: Test ces param�tres IP d'une route
//=====================================================================================
u8sod u8TestConfigRouteStatic(S_STRUCT_IP_ROUTE_STATIC *loc_ps_route);

//=====================================================================================
// Fonction		: u8TestRouteStaticFree
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test si une route est disponible
//=====================================================================================
u8sod u8TestRouteStaticFree(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8AddRoutePolitic
// Entrees		: <loc_ps_config< : config de l'�quipement
//				  <loc_ps_route<: route � ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Ajout d'une politique de routage
//=====================================================================================
u8sod u8AddRoutePolitic(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_ROUTE_POLICY *loc_ps_route);

//=====================================================================================
// Fonction		: u8TestConfigRoutePolitic
// Entrees		: <loc_ps_route< : route IP
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Test ces param�tres IP d'une route
//=====================================================================================
u8sod u8TestConfigRoutePolitic(S_STRUCT_ROUTE_POLICY *loc_ps_route);

//=====================================================================================
// Fonction		: u8TestRoutePoliticFree
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Test si une route est disponible
//=====================================================================================
u8sod u8TestRoutePoliticFree(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestAllRoutePoliticFree
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 23/04/2010 -
// Description	: Test si toutes les routes sont diponibles
//=====================================================================================
u8sod u8TestAllRoutePoliticFree(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestPolicyCriteriaPort_Allowed
// Entrees		: <loc_ps_route< : route IP
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 23/04/2010 -
// Description	: Test si les crit�res de port (source / destination) sont autoris�s (de la route politique)
//=====================================================================================
u8sod u8TestPolicyCriteriaPort_Allowed(S_STRUCT_ROUTE_POLICY *loc_ps_route);

//=====================================================================================
// Fonction		: u8AddRuleNatPortFwdFree
// Entrees		: <loc_ps_config< : config de l'�quipement
//				  <loc_ps_rule_port_fwd<: r�gle � ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Ajout d'une r�gle NAT Port forwarding
//=====================================================================================
u8sod u8AddRuleNatPortFwdFree(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_NAT_RULE_PORT_FORWARDING *loc_ps_rule_port_fwd);

//=====================================================================================
// Fonction		: u8TestRuleNatPortFwdFree
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Test si une r�gle Port forwarding est disponible
//=====================================================================================
u8sod u8TestRuleNatPortFwdFree(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8AddRuleNatMapAdrFree
// Entrees		: <loc_ps_config< : config de l'�quipement
//				  <loc_ps_rule_map_adr<: r�gle � ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Ajout d'une r�gle NAT Mapping d'adresses
//=====================================================================================
u8sod u8AddRuleNatMapAdrFree(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_NAT_RULE_MAP_ADRESSES *loc_ps_rule_map_adr);

//=====================================================================================
// Fonction		: u8TestRuleNatMapAdrFree
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Test si une r�gle Mapping d'adresses est disponible
//=====================================================================================
u8sod u8TestRuleNatMapAdrFree(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestSrcMulticastFree
// Entrees		: <loc_ps_config< : config de l'�quipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si une source multicast est disponible
//=====================================================================================
u8sod u8TestSrcMulticastFree(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8AddSrcMulticastFree
// Entrees		: <loc_ps_config< : config de l'�quipement
//				  <loc_ps_src_multicast<: source multicast � ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Ajout d'une source multicast
//=====================================================================================
u8sod u8AddSrcMulticastFree(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_SRC_MULTICAST *loc_ps_src_multicast);

//============================================================================
// Fonction		: ps8GetStringIp
// Entrees		: <loc_u32_adresse_ip> : adresse IP
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 12/07/2007 -
// Description	: convertit un entier en chaine de caratctere 
//                type adresse IP : XXX.YYY.ZZZ.WWW
//                utilise la variable static loc_ps8_chaine[30]
//============================================================================
s8sod* ps8GetStringIp(u32sod loc_u32_adresse_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_Host
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2009 -
// Description	: Test si masque et adresse IP forme une adresse de type HOST
//=====================================================================================
u8sod u8TestConfigIP_Host(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_Net
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si masque et adresse IP forme un adresse de type NETWORK
//=====================================================================================
u8sod u8TestConfigIP_Net(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip);

///=====================================================================================
// Fonction		: u8TestConfigIP_Subnet
// Entrees		: <loc_u32_subnet_ip>	: adresse IP 
//				: <loc_u32_subnet_mask> : masque sous-reseau
//				: <loc_u32_ip_a_tester> : IP � tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2010 -
// Description	: Test si l'adresse IP � tester est dans le sous r�seau
//=====================================================================================
u8sod u8TestConfigIP_Subnet(u32sod loc_u32_subnet_ip, u32sod loc_u32_subnet_mask, u32sod loc_u32_ip_a_tester);

//=====================================================================================
// Fonction		: u8TestConfigMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si le masque de sous r�seau est valide
//=====================================================================================
u8sod u8TestConfigMask(u32sod loc_u32_subnet_mask);

//=====================================================================================
// Fonction		: u8GetNumberMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_numbermask>  : 
// Auteur		: CM - 30/03/2010 -
// Description	: Retourne la valeur num�rique du masque de sous-r�seau
//=====================================================================================
u8sod u8GetNumberMask(u32sod loc_u32_subnet_mask);

#ifdef _WRM100_ABG_SELECT
//=====================================================================================
// Fonction		: u8Test_ABG_ConfigPowerTx
// Entrees		: <loc_u8_power_tx> : power tx 
//				: <loc_u8_mode_802_11x> : mode 802.11
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 16/10/2009 -
// Description	: Test la valeur power_tx (Driver-ABG)
//=====================================================================================
u8sod u8Test_ABG_ConfigPowerTx(u8sod loc_u8_power_tx, u8sod loc_u8_mode_802_11x);

//=====================================================================================
// Fonction		: u8Get_ABG_PowerTxMax
// Entrees		: <loc_u8_mode_802_11x> : mode 802.11
// Sortie		: <loc_u8_powermax>  : puissance max en dBm (valeur
// Auteur		: CM - 15/12/2010 -
// Description	: retourne valeur max de puissance tx pour config donn�e (pour Driver-ABG)
//=====================================================================================
u8sod u8Get_ABG_PowerTxMax(u8sod loc_u8_mode_802_11x);
#endif

#ifdef _WRM100_N_SELECT
//=====================================================================================
// Fonction		: u8Test_N_ConfigPowerTx
// Entrees		: <loc_u8_power_tx> : power tx 
//				: <loc_u8_mode_802_11x> : mode 802.11
//				: <loc_u8_data_rate> : data rate
//				: <loc_u8_nb_antennes_tx> : nombre d'antennes tx
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/12/2010 -
// Description	: Test la valeur power_tx (Driver-N)
//=====================================================================================
u8sod u8Test_N_ConfigPowerTx(u8sod loc_u8_power_tx, u8sod loc_u8_mode_802_11x, u8sod loc_u8_data_rate, u8sod loc_u8_nb_antennes_tx);

//=====================================================================================
// Fonction		: u8Get_N_PowerTxMax
// Entrees		: <loc_u8_mode_802_11x> : mode 802.11
//				: <loc_u8_data_rate> : data rate
//				: <loc_u8_nb_antennes_tx> : nombre d'antennes tx
// Sortie		: <loc_u8_powermax>  : puissance max en dBm (valeur
// Auteur		: CM - 15/12/2010 -
// Description	: retourne valeur max de puissance tx pour config donn�e (pour Driver-N)
//					donn�es fonction de la "data-sheet du DNMA-H5"
//=====================================================================================
u8sod u8Get_N_PowerTxMax(u8sod loc_u8_mode_802_11x, u8sod loc_u8_data_rate, u8sod loc_u8_nb_antennes_tx);
#endif

//=====================================================================================
// Fonction		: u8FillConfigEquipement
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: rien
// Auteur		: CM - 18/11/2009 -
// Description	: Lecture de la configuration (copie dans *loc_ps_config) 
//=====================================================================================
u8sod u8FillConfigEquipement(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8EditConfigEquipement
// Entrees		: <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: rien
// Auteur		: CM - 18/11/2009 -
// Description	: Ecriture de la configuration de l'�quipement (copie de loc_s_config) 
//=====================================================================================
u8sod u8EditConfigEquipement(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8TestConfigEquipement
// Entrees		: <loc_ps_config<	: structure concernant la configuration de l'�quipement
// Sortie		: rien
// Auteur		: CM - 18/01/2011 -
// Description	: Test de la configuration de l'�quipement (copie de loc_s_config) 
//=====================================================================================
u8sod u8TestConfigEquipement(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8DiffConfigEquipement
// Entrees		: <loc_ps_config1> config n�1 � comparer
//				  <loc_ps_config2> config n�2 � comparer
// Sortie		: <loc_u8_return> TRUE si diff�rente ou FALSE sinon 
// Auteur		: CM - 21/01/2011 -
// Description	: V�rifie si les configurations de l'�quipement en arguments sont diff�rentes
//=====================================================================================
u8sod u8DiffConfigEquipement(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2);

//=====================================================================================
// Fonction		: PassageConfigDefaut
// Entrees		: <loc_ps_config< : config de l'�quipement
//				: <loc_u8_mode> : mode de passage en config/defaut
//							MODE_PASSAGECONFIGDEFAUT_TOTAL
//							MODE_PASSAGECONFIGDEFAUT_SANS_IP
// Sortie		: rien
// Auteur		: CM - 18/11/2009 -
// Description	: passage en config par d�faut
//=====================================================================================
void PassageConfigDefaut(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_mode);


//=====================================================================================
// Fonction		: InitBDD_Config
// Entrees		: <loc_ps_config< : configuration de l'�quipement
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Initialisation de la base de donn�es de la configuration
//=====================================================================================
void InitBDD_Config(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Config
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Initialisation du module de Config de l'�quipement
//=====================================================================================
void InitModule_Config(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

//*******************************
// CONFIGURATION PAR DEFAUT     *
//*******************************

#ifdef _CONFIG
const S_STRUCT_CONFIGURATION S_CONFIG_EQUIPEMENT_DEFAUT =
{
	//Entete
	0x0000,	//u16_checksum_file
	0x5A,	//u8_start

	// Param�tres CONSTRUCTEUR
	{//s_constructeur
		0x5A,	//u8_start
		NOM_DU_CONSTRUCTEUR,		//ps8_nom
		TELEPHONE_DU_CONSTRUCTEUR,	//ps8_numero_telephone
		FAX_DU_CONSTRUCTEUR,		//ps8_numero_fax
		ADRESSE_DU_CONSTRUCTEUR_L1,	//ps8_adresse_ligne1
		ADRESSE_DU_CONSTRUCTEUR_L2,	//ps8_adresse_ligne2
		SITE_DU_CONSTRUCTEUR,		//ps8_site_web
	},
	
	// Param�tres Administration
	{//s_admin
		0x5A,	//u8_start
		// Param�tres Administration : g�n�ral
		{'i','d','e','n','t','i','f','i','a','n','t','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
		'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}, //ps8_identifiant[LG_NOM_IDENTIFIANT+1]
		{'l','o','c','a','l','i','s','a','t','i','o','n','\0','\0','\0','\0','\0','\0','\0','\0','\0',
		'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}, //ps8_localisation[LG_NOM_LOCALISATION+1]
		{'l','o','w','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},//ps8_mot_de_passe_low[LG_NOM_PWD+1]
		{'m','i','d','d','l','e','\0','\0','\0','\0','\0','\0','\0'},//ps8_mot_de_passe_middle[LG_NOM_PWD+1]
		{'h','i','g','h','\0','\0','\0','\0','\0','\0','\0','\0','\0'},//ps8_mot_de_passe_high[LG_NOM_PWD+1]
		10,	//u16_duree_inactivite_http
		5,	//u8_max_client_ip
		MODE_SECURISATION_SNMP_INACTIF,	//u8_securisation_snmp
		LANGUE_PAR_DEFAUT,				//u8_langue
		TPS_REFRESH_HTML_MIN,			//u16_tps_refresh_html
		
		// Param�tres Administration : dateHeure / NTP
		{//s_date_demarrage
			ANNEE_PAR_DEFAUT,	//u16_annee
			MOIS_PAR_DEFAUT,	//u8_mois
			JOUR_PAR_DEFAUT,	//u8_jour
			HEURE_PAR_DEFAUT,	//u8_heure
			MINUTE_PAR_DEFAUT,	//u8_minute
			SECONDE_PAR_DEFAUT,	//u8_seconde
		},
		MODE_DATE_HEURE_24H,			//u8_mode_date_heure
		MODE_MAH_MANUELLE,				//u8_mode_mah
		{//s_client_ntp
			{//s_client_ntp.pu32_adresse_serveur[NB_MAX_SERVEURS_NTP]
				ADRESSE_IP_NULLE,			//pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL]
				ADRESSE_IP_NULLE,			//pu32_adresse_serveur[SERVEUR_NTP_SECOURS]
			},
			1,							//s8_fuseau_horaire
			VALEUR_MIN_FREQ_MAJ_HEURE_SNTP,	//u16_freq_maj_sntp
		},

		// Param�tres Administration : Syslog
		FALSE,				//u8_syslog_activation
		FALSE,				//u8_mode_RSSI
		ADRESSE_IP_NULLE,	//u32_syslog_adresse_IP
		PORT_UDP__SYSLOG,	//u16_syslog_port
	},
	
	// Param�tres SNMP
	{//s_snmp
		0x5A,	//u8_start
		VERSION_SNMPV1,	//u8_version_snmp
		{'p','u','b','l','i','c','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},	//ps8_nom_communaute_get[LG_MAX_NOM_COMMUNAUTE_SNMP+1]
		{'p','r','i','v','a','t','e','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},	//ps8_nom_communaute_set[LG_MAX_NOM_COMMUNAUTE_SNMP+1]
		{'p','u','b','l','i','c','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},	//ps8_nom_communaute_trap[LG_MAX_NOM_COMMUNAUTE_SNMP+1]
		EMISSION_TRAP_ACTIVE,	//u8_emission_trap;				// Activation / D�sactivation �mission des TRAPs
		//S_STRUCT_MANAGER_SNMP s_manager_snmp[NB_MANAGER_SNMP_MAX];
		{//s_manager_snmp[NB_MANAGER_SNMP_MAX]
			{{'m','a','n','a','g','e','r','1',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[0]
			{{'m','a','n','a','g','e','r','2',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[1]
			{{'m','a','n','a','g','e','r','3',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[2]
			{{'m','a','n','a','g','e','r','4',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP},//s_manager_snmp[3]
			{{'m','a','n','a','g','e','r','5',0,0,0,0,0,0,0,0,0,0,0,0,0}, ADRESSE_IP_NULLE, MANAGER_SNMP_ABSENT, TYPE_NOTIFICATION_TRAP} //s_manager_snmp[4]
		},
		{//s_trap_SNMPv1[NIV_GRAVITE_MAX]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_INDETERMINE]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_CRITIQUE]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_MAJEUR]
			{20,180},	//s_trap_SNMPv1[NIV_GRAVITE_MINEUR]
			{20,180}	//s_trap_SNMPv1[NIV_GRAVITE_AVERTISSEMENT]
		},
		{REEMISSION_INFORM_MIN, INTERVAL_INFORM_MIN},	//s_inform_SNMPv2c
		{FALSE,	VALEUR_MIN_CYCLE_VIE},// s_trap_signevie
	},


	// Param�tres sp�cifiques au produit
	//===================================

	//param�tres g�n�rales
	{//s_gene
		0x5A,	//u8_start
		//Param�tres de configuration des modes
		MODE_RADIO_MODEM_STATION,		//u8_mode_radio_modem
		MODE_NETWORK_ROUTER,			//u8_mode_network
		"wrm100",						//ps8_hostname[]
		//Param�tres de configuration r�seau du bridge
		MODE_IP_STATIQUE,				//u8_bridge_mode_ip
		0xC0A80101,			//u32_bridge_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_bridge_masque_reseau
		ADRESSE_IP_NULLE,	//u32_bridge_gateway
		ADRESSE_IP_NULLE,	//u32_bridge_dhcp_fallback_ip
		FALSE,				//u8_bridge_stp

		//Param�tres de configuration r�seau du routeur (Valable pour STATION uniquement)
		// --> Interface LAN (en mode static forc�)
	0xC05D7922,			//u32_lan_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_lan_masque_reseau
		// --> Interface WLAN
		MODE_IP_STATIQUE,	//u8_wlan_mode_ip
		0xC0A80102,			//u32_wlan_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_wlan_masque_reseau
		ADRESSE_IP_NULLE,	//u32_wlan_gateway
		ADRESSE_IP_NULLE,	//u32_wlan_dhcp_fallback_ip

		//Param�tres de configuration du serveur/relai DHCP
		FCT_DHCP_NONE,		//u8_lan_fonction_dhcp
		ADRESSE_IP_NULLE,	//u32_lan_dhcpsrv_ip_min
		ADRESSE_IP_NULLE,	//u32_lan_dhcpsrv_ip_max
		DHCP_DUREE_VIE_BAIL_DEFAUT,	//u32_lan_dhcpsrv_duree_vie_bail
		ADRESSE_IP_NULLE,	//u32_lan_dhcprelay_ip

		//Param�tres de configuration du VLAN
		FALSE,			//u8_vlan_autoriser
		"",				//ps8_vlan_nom[]
		VLAN_ID_MIN,	//u16_vlan_id		TRUE,			//u8_vlan_interface_notag
		ADRESSE_IP_NULLE,	//u32_vlan_notag_adresse_ip
		MASK_RESEAU_SUR_24,	//u32_vlan_notag_masque_reseau
	},

	//param�tres wifi
	{//s_wifi
		0x5A,	//u8_start
		MODE_WIFI_802_11A,	//u8_mode_802_11x
		"wrm100",		//ps8_ssid_primary[NB_MAX_CHAINE_SSID + 1]
		FALSE,			//u8_dual_ssid
		"wrm100_secondary",		//ps8_ssid_secondary[NB_MAX_CHAINE_SSID + 1]
		FALSE,			//u8_masquage_ssid
		GUARD_INTERVAL_LONG,	//u8_11n_guard_interval
		CHANNEL_SPECTRUM_WIDTH_20_MHZ,	//u8_channel_spectrum_width
		TYPE_SELECTION_CANAL_AUTO,	//u8_type_selection_canal
		CHANNEL_DEFAULT_11A_FR,	//u16_iso_canal_radio
		{//pu16_multi_canal_radio[NB_MAX_MULTI_CANAUX]
			CHANNEL_RADIO_DISABLED, //[0]
			CHANNEL_RADIO_DISABLED, //[1]
			CHANNEL_RADIO_DISABLED, //[2]
			CHANNEL_RADIO_DISABLED, //[3]
			CHANNEL_RADIO_DISABLED, //[4]
		},
		POWER_TX_802_11X_DEFAULT,	//u8_power_tx
		DATA_RATE_AUTOMATIC,		//u8_data_rate
		SEUIL_RX_MIN,	//s8_seuil_rx
		NB_ASSOCIATED_STATIONS_MAX,	//u16_nb_max_associated_stations
		MODE_SECURITE_WIFI_AUCUN,	//u8_mode_securite_wifi

		{//s_wep_security
			WEP_KEY_LENGTH_64BIT,	//u8_key_length
			KEY_TYPE_ASCII,			//u8_wep_key_type
			{//ps8_key_value[NB_MAX_IDX_WEP_KEY][KEY_WEP_VALUE_LENGTH_MAX+1]
				{"actia"}, //[IDX_WEP_KEY_1]
				{"actia"}, //[IDX_WEP_KEY_2]
				{"actia"}, //[IDX_WEP_KEY_3]
				{"actia"}, //[IDX_WEP_KEY_4]
			},
			IDX_WEP_KEY_1,	//u8_index_key_default
			WEP_AUTHENTIFICATION_OPEN,	//u8_authentification
		},
		{//s_wpa_security
			WPA_AUTHENTIFICATION_PSK,	//u8_authentification
			GP_KEY_UPDATE_INTERVAL_MAX,	//u32_gp_key_update_interval
			KEY_TYPE_ASCII,		//u8_wpa_key_type
			{"actiasodielec"},	//ps8_pre_shared_key[LG_MAX_PRESHARED_WPA_TOTAL+1]
			{//s_server_radius
				ADRESSE_IP_NULLE,		//u32_radius_adresse_ip
				PORT_UDP__AUTH_RADIUS,	//u16_radius_port
				"actiasodielec",		//ps8_radius_shared[LG_MAX_SHARED_RADIUS + 1]
			},
			EAP_REAUTH_PERIOD_DISABLED, //u32_eap_reauth_period
			EAP_METHOD__TTLS_PAP, //u8_eap_method
			"wrm100", //ps8_identity[LG_MAX_EAP_IDENTITY + 1]
#if PARAMETERS_RADIUS_NOT_USED
			"anonymous@example.com", //ps8_user_name[LG_MAX_EAP_USER_NAME + 1]
#endif
			"actia", //ps8_user_password[LG_MAX_EAP_USER_PASSWORD + 1]
			"",			//ps8_file_certificat_authority[LG_MAX_NOM_CERTIFICAT + 1]
			"",			//ps8_file_certificat_client[LG_MAX_NOM_CERTIFICAT + 1]
			"whatever",	//ps8_private_key_password[LG_MAX_PRIVATE_KEY_PWD + 1]
		},
		//Protocole wifi
		WF_ABG_ACK_TIMEOUT_DEFAULT,		//u16_protcl_ABG_ACK_timeout
		WF_N_ACK_TIMEOUT_DEFAULT,	//u16_protcl_N_ACK_timeout
		WF_TYPE_PREAMBULE_LONG,	//u8_protcl_type_preambule
		WF_FRAGMENT_THRESHOLD_MAX,	//u16_protcl_fragment_threshold
		WF_RTS_CTS_THRESHOLD_MAX,	//u16_protcl_RTS_CTS_threshold
		WF_RTS_RETRY_LIMIT_MAX, //u16_protcl_RTS_retry_limit
		100,			//u16_protcl_beacon_period
		TRUE,	//u8_activation_WMM
		COUNTRY_ID_FRANCE,	//u8_countryID
		FALSE,	//u8_desactivation_DFS
		
		//Antennes
		ABG_SELECT_TX_ANTENNE_1,	//u8_ant_ABG_tx_selection
		ABG_SELECT_RX_ANTENNE_1,	//u8_ant_ABG_rx_selection
		N_SELECT_ANTENNE_1,			//u8_ant_N_selection
	},

	//param�tres du routage
	{//s_ip_routing
		0x5A,	//u8_start
		{//s_ip_routing.ps_route_ip_static[NB_MAX_ROUTES_IP_STATIC]
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //0
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //1
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //2
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //3
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //4
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //5
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //6
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //7
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //8
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //9
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //10
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //11
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //12
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //13
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //14
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //15
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //16
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //17
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //18
			{FALSE, ADRESSE_IP_NULLE,	MASK_RESEAU_SUR_24, ADRESSE_IP_NULLE, INTERFACE_AUTOMATIQUE}, //19
		},
		{//s_ip_routing.ps_route_policy[NB_MAX_POLICY_ROUTING]
			{//ps_route_policy[0]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[1]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[2]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[3]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[4]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[5]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[6]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[7]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[8]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
			{//ps_route_policy[9]
				FALSE,	//u8_enabled
				"",	//ps8_policy_name
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_valid_critere[NB_MAX_CRITERIA_POLICY]
				{FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,}, //pu8_not_critere[NB_MAX_CRITERIA_POLICY]
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_src_ip_start, u32_critere_src_ip_end
				ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, //u32_critere_dst_ip_start, u32_critere_dst_ip_end
				LEN_PACKET_MIN, LEN_PACKET_MAX, //u16_critere_len_packet_min, u16_critere_len_packet_max
				POLICYROUTE_PROTOCOLE_UDP, //u8_critere_ip_protocol
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_src_port_start, u16_critere_src_port_end
				PORT_UDP_TCP_MIN, PORT_UDP_TCP_MAX,	//u16_critere_dst_port_start,u16_critere_dst_port_end
				CLASSSELECTOR_CS0,	//u8_critere_class_selector
				{FALSE,FALSE,},	//pu8_valid_action[NB_MAX_ACTIONS_POLICY]
				ADRESSE_IP_NULLE,	//u32_new_gateway
				CLASSSELECTOR_CS0,	//u8_new_class_selector
			},				
		},
		//param�tres routage dynamique RIPv2
		FALSE,	//u8_ripv2_activation
		{//pu8_rip_interface_used[NB_MAX_RIP_INTERFACES]
			FALSE,	//RIP_INTERF_LAN
			FALSE,	//RIP_INTERF_WLAN
		},
		RIP_AUTHENTICATION_NONE, //u8_rip_authentification
		"actia sodielec",	//ps8_rip_password[TAILLE_MAX_RIP_PASSWORD+1]
	},

	//param�tres du NAT
	{//s_nat
		0x5A,	//u8_start
		FALSE,	//u8_nat_activation
		{//s_nat.ps_rule_port_forwarding[NB_MAX_RULES_PORT_FORWARDING]
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //0
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //1
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //2
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //3
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //4
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //5
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //6
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //7
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //8
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //9
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //10
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //11
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //12
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //13
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //14
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //15
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //16
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //17
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //18
			{FALSE,	ADRESSE_IP_NULLE, PORT_UDP_TCP_MIN, NAT_PROTOCOLE_NON_SELECTIONNE, PORT_UDP_TCP_MIN, ""}, //19
		},
		{//s_nat.ps_rule_mapping_adresse[NB_MAX_NAT_ALIAS_IP]
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //0
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //1
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //2
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //3
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //4
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //5
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //6
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //7
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //8
			{FALSE,	ADRESSE_IP_NULLE, ADRESSE_IP_NULLE, ""}, //9
		},
	},

	//param�tres du multicast
	{//s_multicast
		0x5A,	//u8_start
		FALSE,	//u8_proxy_igmp_activation
		{//ps_source_multicast[NB_MAX_SRC_MULTICAST]
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //0
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //1
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //2
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //3
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //4
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //5
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //6
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //7
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //8
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //9
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //10
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //11
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //12
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //13
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //14
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //15
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //16
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //17
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //18
			{FALSE,	ADRESSE_IP_NULLE, MASK_RESEAU_SUR_24}, //19
		},
	},
	
	{//s_tabevt
		0x5A,	//u8_start
		{//s_event[NB_MAX_EVENEMENTS]
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT000_AL_SYNTHESE_1
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT001_DEFAUT_EQUIPEMENT
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT002_AL_TEMPERATURE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT003_AL_ETHERNET_LAN_1
			{0xFFFD, NIV_GRAVITE_INDETERMINE},	//EVT004_AL_ETHERNET_LAN_2 : alarme non valid�e par d�faut
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT005_AL_NIVEAU_RECU
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT006_STATION_NON_CONNECTEE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT007_PROBLEME_CONFIGURATION
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT008_BASCULEMENT_SUR_SSID_SECONDAIRE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT009_RETOUR_SUR_SSID_PRIMAIRE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT010_AL_AUCUN_SERVEUR_NTP_ACCESSIBLE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT011_RADAR_DETECTE_SUR_CANAL
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT012_BASCULEMENT_VERS_CANAL
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT013_CONNEXION_STATION
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT014_DECONNEXION_STATION
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT015_CONNEXION_ACCESS_POINT
			{0x7FF0, NIV_GRAVITE_INDETERMINE},	//EVT016_DECONNEXION_ACCESS_POINT
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT017_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT018_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT019_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT020_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT021_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT022_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT023_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT024_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT025_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT026_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT027_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT028_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT029_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT030_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT031_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT032_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT033_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT034_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT035_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT036_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT037_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT038_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT039_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT040_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT041_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT042_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT043_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT044_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT045_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT046_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT047_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT048_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT049_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT050_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT051_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT052_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT053_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT054_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT055_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT056_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT057_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT058_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT059_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT060_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT061_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT062_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT063_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT064_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT065_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT066_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT067_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT068_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT069_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT070_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT071_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT072_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT073_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT074_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT075_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT076_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT077_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT078_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT079_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT080_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT081_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT082_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT083_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT084_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT085_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT086_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT087_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT088_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT089_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT090_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT091_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT092_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT093_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT094_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT095_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT096_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT097_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT098_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT099_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT100_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT101_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT102_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT103_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT104_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT105_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT106_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT107_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT108_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT109_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT110_JOURNAL_BORD_EFFACE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT111_INF_RAZ_ALARMES_MEMO
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT112_EVOLUTION_CONFIGURATION
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT113_ORDRE_RESET_TELECOMMANDE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT114_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT115_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT116_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT117_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT118_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT119_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT120_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT121_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT122_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT123_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT124_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT125_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT126_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT127_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT128_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT129_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT130_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT131_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT132_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT133_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT134_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT135_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT136_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT137_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT138_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT139_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT140_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT141_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT142_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT143_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT144_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT145_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT146_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT147_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT148_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT149_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT150_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT151_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT152_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT153_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT154_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT155_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT156_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT157_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT158_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT159_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT160_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT161_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT162_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT163_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT164_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT165_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT166_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT167_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT168_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT169_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT170_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT171_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT172_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT173_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT174_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT175_INF_EQUIPEMENT_ON
			{(0xFFFF & (u16sod)(~(1<<ACTION_EVT_JDB))), NIV_GRAVITE_INDETERMINE},	//EVT176_INF_SIGNE_DE_VIE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT177_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT178_RESERVE
			{0xFFFF, NIV_GRAVITE_INDETERMINE},	//EVT179_RESERVE
		},
	},

	//Param�tres de configuration de la fonction hand-off
	{//s_handoff
		0x5A,	//u8_start
		HO_MODE_SCANNING_AUTO,	//u8_scanning_mode
		HO_TIME_BETW_HANDOFF_DEFAULT,	//u16_time_between_hand_off
		FALSE,	//u8_bgscan_activation
		HO_BGSCAN_PERIOD_MAX,	//u16_bgscan_recurrence_period
		MACRO_RSSI2DBM(20),	//s32_bgscan_detection_level
		MACRO_RSSI2DBM(15),	//s32_fgscan_detection_level
		HO_FGSCAN_BEACON_MISSED_THRESH_MIN,	//u16_fgscan_beacon_missed_threshold
		MACRO_RSSI2DBM(20),	//s32_iso_detection_level
		HO_ISO_RELEVANT_BEACON_THRESH_MAX,	//u16_iso_relevant_beacon_threshold
		FILTR_RSSI_1,	//u8_type_filtrage_rssi
		MINDWELL_TIME_DEFAULT, //u16_time_between_2_beacon
	},
	
};
#else
extern const S_STRUCT_CONFIGURATION S_CONFIG_EQUIPEMENT_DEFAUT;
#endif


#ifdef _CONFIG
//Adresse MAC NULL
const u8sod	PU8_ADD_MAC_NULL[ETHER_ADDR_LEN]={0x00,0x00,0x00,0x00,0x00,0x00};
#else
extern const u8sod PU8_ADD_MAC_NULL[ETHER_ADDR_LEN];
#endif
