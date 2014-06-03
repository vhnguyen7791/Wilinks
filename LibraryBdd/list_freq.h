/*========================================================================*/
/* NOM DU FICHIER  : list_freq.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010                                           */
/* Libelle         : Base de données: liste des fréquences réglementaires */
/* Projet          : WRM100                                               */
/* Indice	       : BE056												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 11/10/2010 CM
// - CREATION
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _LIST_FREQ
#define _LIST_FREQ_EXT
#else
#define _LIST_FREQ_EXT extern
#endif

#define IDX_CHANNEL_UNKNOWN	0xFFFF

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillListFreqFile
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillListFreqFile(S_STRUCT_LIST_FREQ *loc_ps_list_freq);

//=====================================================================================
// Fonction		: u8EditListFreqFile
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditListFreqFile(S_STRUCT_LIST_FREQ *loc_ps_list_freq);

//=====================================================================================
// Fonction		: u16GetIdx_ForChannelAndMode
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
//				: <loc_u16_numero_canal> : numero de canal
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u16_x_index>	: index dans s_channel[] si trouvé, sinon IDX_CHANNEL_UNKNOWN
// Auteur		: CM - 11/10/2010 -
// Description	: Retourne index dans s_channel[] du numéro canal et mode 802.11
//=====================================================================================
u16sod u16GetIdx_ForChannelAndMode(S_STRUCT_LIST_FREQ *loc_ps_list_freq, u16sod loc_u16_numero_canal, u8sod loc_u8_mode80211);

//=====================================================================================
// Fonction		: u16GetIdx_Min_ForMode
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u16_x_index>	: index dans s_channel[] si trouvé, sinon IDX_CHANNEL_UNKNOWN
// Auteur		: CM - 11/10/2010 -
// Description	: Retourne index du canal minimum défini dans  s_channel[] pour mode 802.11
//=====================================================================================
u16sod u16GetIdx_Min_ForMode(S_STRUCT_LIST_FREQ *loc_ps_list_freq, u8sod loc_u8_mode80211);

//=====================================================================================
// Fonction		: u16GetIdx_Max_ForMode
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u16_x_index>	: index dans s_channel[] si trouvé, sinon IDX_CHANNEL_UNKNOWN
// Auteur		: CM - 11/10/2010 -
// Description	: Retourne index du canal maximum défini dans s_channel[] pour mode 802.11
//=====================================================================================
u16sod u16GetIdx_Max_ForMode(S_STRUCT_LIST_FREQ *loc_ps_list_freq, u8sod loc_u8_mode80211);

//=====================================================================================
// Fonction		: u8IsChannelForMode80211
// Entrees		: <loc_ps_channel< : pointeur sur canal
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Test si canal est valide pour mode 802.11 
//=====================================================================================
u8sod u8IsChannelForMode80211(S_STRUCT_CHANNEL *loc_ps_channel, u8sod loc_u8_mode80211);

//=====================================================================================
// Fonction		: u16IeeeToMhz
// Entrees		: <loc_u16_ieee> : numéro de canal
// Sortie		: <loc_u16_frequence> : fréquence en MHz
// Auteur		: CM - 25/01/2011 -
// Description	: Retourne la fréquence associée au numéro du canal
//=====================================================================================
u16sod u16IeeeToMhz(u16sod loc_u16_ieee);

//=====================================================================================
// Fonction		: u16MhzToIeee
// Entrees		: <loc_u16_frequence> : fréquence en MHz
// Sortie		: <loc_u16_ieee> : numéro de canal, sinon si freq invalid, CHANNEL_RADIO_DISABLED
// Auteur		: CM - 25/01/2011 -
// Description	: Retourne numéro du canal associé à la fréquence
//=====================================================================================
u16sod u16MhzToIeee(u16sod loc_u16_frequence);

//=====================================================================================
// Fonction		: BuildListFreq
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données à initialiser
//				: <loc_pt_req_listchans< : pointeur sur requete listchan (réponse du driver)
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Construction de la base de données de la liste des frequences pour driver-N
//=====================================================================================
void BuildListFreq(S_STRUCT_LIST_FREQ *loc_ps_list_freq, struct ieee80211req_chaninfo *loc_pt_req_listchans);

//=====================================================================================
// Fonction		: InitBDD_ListFreq
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation de la base de données de la liste des frequences
//=====================================================================================
void InitBDD_ListFreq(S_STRUCT_LIST_FREQ *loc_ps_list_freq);

//=====================================================================================
// Fonction		: InitModule_ListFreq
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation du module de listfreq de l'équipement
//=====================================================================================
void InitModule_ListFreq(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


#ifdef _LIST_FREQ
#else
_LIST_FREQ_EXT T_STRUCT_FILE_FIELD PT_DEF_STRUCT_CHANNEL[];
//Contenu du fichier listfreq.ini
_LIST_FREQ_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_LISTFREQ_INI[];
//Définition du fichier listfreq.ini
_LIST_FREQ_EXT T_STRUCT_DEFINITION_FILE_FS	T_DEF_FILE_LISTFREQ_INI;
//Définition du fichier iwlistfreq Add by VuHai 
_LIST_FREQ_EXT T_STRUCT_DEFINITION_FILE_FS	T_DEF_FILE_IWLISTFREQ;
//Définition du fichier ht40_allow_map Add by VuHai 
_LIST_FREQ_EXT T_STRUCT_DEFINITION_FILE_FS	T_DEF_FILE_HT40_ALLOW_MAP;

#endif
