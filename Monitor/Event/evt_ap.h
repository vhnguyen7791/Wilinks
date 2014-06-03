/*========================================================================*/
/* NOM DU FICHIER  : evt_ap.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/01/2011                                           */
/* Libelle         : Monitor: Calcul des évènements de l'AP				  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE058 24/01/2011 CM
// - CREATION
//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EVT_AP
#define _EVT_AP_EXT
#else
#define _EVT_AP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef struct 
{
	u8sod		u8_present;		//client présent (TRUE ou FALSE)
	u8sod		u8_connected;		//client connecté (TRUE ou FALSE)
	u8sod		pu8_add_mac[ETHER_ADDR_LEN]; //Adresse MAC du client wifi
	u32sod		u32_time_reconnexion;	//Horodatage reconnexion
}S_STRUCT_MEMO_WIFI_CLIENT;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_AP
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Gestion des évènements AP
//=====================================================================================
void CalculEvents_AP(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit);

//=====================================================================================
// Fonction		: CalculEvents_ConnexionDeconnexionStations
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Gestion des évènements de connexion/deconnexion des stations sur l'AP
//=====================================================================================
void CalculEvents_ConnexionDeconnexionStations(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit);

//=====================================================================================
// Fonction		: RazMemoClientWifi
// Entrees		: <loc_ps_memo_clientwifi< : pointeur sur client mémorisé
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Raz d'un clients wifi mémorisé
//=====================================================================================
void RazMemoClientWifi(S_STRUCT_MEMO_WIFI_CLIENT *loc_ps_memo_clientwifi);

//=====================================================================================
// Fonction		: RazAllMemoClientsWifi
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Raz de tous les clients wifi mémorisés
//=====================================================================================
void RazAllMemoClientsWifi(void);

//=====================================================================================
// Fonction		: InitModule_Evt_AP
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Initialisation du module evt_AP
//=====================================================================================
void InitModule_Evt_AP(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

