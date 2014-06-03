/*========================================================================*/
/* NOM DU FICHIER  : evt_sta.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/01/2011                                           */
/* Libelle         : Monitor: Calcul des évènements de la STAtion		  */
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

#ifdef _EVT_STA
#define _EVT_STA_EXT
#else
#define _EVT_STA_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

typedef struct 
{
	u8sod		u8_connected;		//station connecté à l'AP (TRUE ou FALSE)
	u8sod		pu8_add_mac[ETHER_ADDR_LEN]; //Adresse MAC de l'AP
}S_STRUCT_MEMO_BSSID;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: CalculEvents_STA
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
//				: <loc_ps_exploit<: exploitation (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Gestion des évènements STATION
//=====================================================================================
void CalculEvents_STA(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_EXPLOITATION *loc_ps_exploit);

//=====================================================================================
// Fonction		: RazMemoBssidWifi
// Entrees		: <loc_ps_memo_bssidwifi< : pointeur sur AP mémorisé
// Sortie		: rien
// Auteur		: CM - 17/03/2011 -
// Description	: Raz du bssid wifi mémorisé
//=====================================================================================
void RazMemoBssidWifi(S_STRUCT_MEMO_BSSID *loc_ps_memo_bssidwifi);

//=====================================================================================
// Fonction		: InitModule_Evt_STA
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/01/2011 -
// Description	: Initialisation du module evt_sta
//=====================================================================================
void InitModule_Evt_STA(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

/*_______VII - INITIALISATIONS NON PROGRAMMEES _____________________________*/

