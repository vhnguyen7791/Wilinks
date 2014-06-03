/*========================================================================*/
/* NOM DU FICHIER  : valeurs.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : Base de données: valeurs							  */
/* Projet          : WRM100                                               */
/* Indice	       : BE057												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE042 07/10/2010 CM
// - Correction configuration mode 802.11 (associé au driver-N)
// - Ajout gestion debit MCS pour 802.11n
//BE049 08/12/2010 CM
// - Modification mode scanning (handoff)
//BE052 15/12/2010 CM
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE056 18/01/2011 CM
// - Correction puissance maximum en fonction config mode 802.11/debit/antenne
//	pour éviter sur-consommation de l'équipement
//BE057 20/01/2011 CM
// - Désactivation du mode monitor en WRM100-ABG
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/


#define UI_TAILLE_MAX_VALEUR	40

//Variable : S_STRUCT_VAL_OPTION
//Champs : ps_options[].u8_type_option
#define TYPE_OPTION_HARD	0
#define TYPE_OPTION_SOFT	1

//Variable : S_STRUCT_VAL_OPTION
//Champs : pt_definition_mode_securite_wifi[].u8_groupe
enum LISTE_GROUP_MODE_SECU_WIFI
{
	GROUPE_SECU_WIFI_NULL = 0,
	GROUPE_SECU_WIFI_WEP,
	GROUPE_SECU_WIFI_WPA,
	NB_MAX_GROUPES_SECU_WIFI
};

//Variable : S_STRUCT_VAL_OPTION
//Champs : pt_definition_rate[].u8_mode80211_valid
#define M80211_VALID_11B	0x01
#define M80211_VALID_11AG	0x02
#define M80211_VALID_11N	0x04
#define M80211_VALID_11AC	0x08 //Add by VuHai

#define M80211V_ALL (M80211_VALID_11B | M80211_VALID_11AG | M80211_VALID_11N | M80211_VALID_11AC)


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

//Définition des constantes
//*****************************
typedef struct 
{
	u8sod		u8_flag;	//true ou false
	s8sod		ps8_message[10+1];
}S_STRUCT_VAL10MAX;

typedef struct 
{
	u8sod		u8_flag;	//true ou false
	s8sod		ps8_message[10+1];
	f32sod		f32_valeur;
}S_STRUCT_VAL10MAXETVALF32;

typedef struct 
{
	u8sod		u8_flag;	//true ou false
	s8sod		ps8_message[20+1];
}S_STRUCT_VAL20MAX;

typedef struct 
{
	u8sod		u8_flag;	//true ou false
	s8sod		ps8_message[20+1];
	f32sod		f32_valeur;
}S_STRUCT_VAL20MAXETVALF32;

typedef struct 
{
	u8sod		u8_flag;	//true ou false
	s8sod		ps8_message[20+1];
	u16sod		u16_valeur;
}S_STRUCT_VAL20MAXETVALU16;

typedef struct 
{
	u8sod		u8_flag;	//true ou false
	u16sod		u16_valeur;
}S_STRUCT_VALU16;

typedef struct 
{
	u8sod		u8_flag;		//true ou false
	f32sod		f32_valeur;
}S_STRUCT_VALF32;


typedef struct 
{
	u8sod		u8_flag_affichage;	//true ou false
	s8sod		ps8_nom_architecture[30+1];
	u8sod		u8_type_option;	//TYPE_OPTION_HARD ou TYPE_OPTION_SOFT
}S_STRUCT_VAL_OPTION;

//définition configuration du radio modem
//*******************************
typedef struct 
{
	u8sod	u8_flag_affichage;	// flag d'affichage
	u8sod	pu8_flag_mode_reseau[NB_MAX_MODES_NETWORK];			// Indique si le mode réseau est valide pour ce type de radio modem
	u8sod	pu8_flag_mode_canal[NB_MAX_TYPE_SELECTION_CANAL];	// Indique si le mode canal est valide pour ce type de radio modem
	u8sod	pu8_flag_mode_80211x[NB_MAX_MODES_WIFI_802_11];	// Indique si le mode 802.11x est valide pour ce type de radio modem
}S_STRUCT_DEFINITION_RADIO_MODEM;

//définition configuration du radio modem
//*******************************
typedef struct 
{
	u8sod	u8_flag;	// flag d'affichage
	u8sod	u8_groupe;	// groupe d'appartenance le mode de sécurite
}S_STRUCT_DEFINITION_MODE_SECU_WIFI;

//définition configuration du mode wifi
//*******************************
typedef struct 
{
	s8sod				ps8_message[20+1];
	u8sod				u8_channelspectrumwidth;
}S_STRUCT_DEFINITION_MODE_WIFI;

typedef struct
{
	u8sod	u8_mode80211_valid;
	u32sod	u32_rateKbps_basic;
	u8sod	u8_codeRate;
	s8sod	ps8_chain[14+1];
	u8sod	u8_nbstream;
	u32sod	u32_rateKbps_HT20_longGI;
	u32sod	u32_rateKbps_HT20_shortGI;
	u32sod	u32_rateKbps_HT40_longGI;
	u32sod	u32_rateKbps_HT40_shortGI;
	u32sod	u32_rateKbps_HT80_longGI;
	u32sod	u32_rateKbps_HT80_shortGI;
}STRUCT_DEFINITION_RATE;

typedef struct
{
	S_STRUCT_VAL_OPTION	ps_options[NB_MAX_OPTIONS];
	u8sod				pu8_flag_affichage_version[NB_MAX_VERSIONS_LOGICIELLES];

	//configuration wifi
	S_STRUCT_DEFINITION_RADIO_MODEM		pt_definition_radio_modem[NB_MAX_MODES_RADIO_MODEM];
	S_STRUCT_DEFINITION_MODE_WIFI		pt_definition_mode_wifi[NB_MAX_MODES_WIFI_802_11];
	S_STRUCT_DEFINITION_MODE_SECU_WIFI	pt_definition_mode_securite_wifi[NB_MAX_MODES_SECURITE_WIFI];
	S_STRUCT_VAL20MAXETVALU16	ps_channel_spectrum_width[NB_MAX_CHANNEL_SPECTRUM_WIDTH];
	u8sod				pu8_flag_affichage_wpa_authentification[NB_MAX_WPA_AUTHENTIFICATION];
	u8sod				pu8_lg_wep_key[NB_MAX_WEP_KEY_LENGTH][NB_MAX_KEY_TYPE];
	STRUCT_DEFINITION_RATE	pt_definition_rate[NB_MAX_DATA_RATE];
	u8sod				pu8_flag_affichage_mode_scanning_handoff[NB_MAX_HO_MODES_SCANNING];
#ifdef _WRM100_N_SELECT
	u8sod	pu8_N_powerTxMax_11g[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11b[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11a[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11nght20[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11nght40[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11naht20[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11naht40[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11acht20[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11acht40[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
	u8sod	pu8_N_powerTxMax_11acht80[NB_MAX_DATA_RATE][NB_MAX_N_SELECT_ANTENNES];
#endif

} S_STRUCT_TAB_VALEURS;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

