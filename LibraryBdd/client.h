/*========================================================================*/
/* NOM DU FICHIER  : client.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 25/09/2007											  */
/* Libelle         : Password: gestion des clients pour SNMP, HTTP		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//[AUDIT X251231 Ind 0] MS 23/10/2008
//BE000 24/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère les passwords des clients HTTP, SNMP

/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CLIENT
#define _CLIENT_EXT
#else
#define _CLIENT_EXT	extern
#endif

#define PROTOCOLE_HTTP	0
#define PROTOCOLE_SNMP	1

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

// -------------------------------------------------------------
// Fonction    : TestClientIpConnecte
// Entrees     : <loc_ps8_addrIP> : adresse IP du client
// Sortie      : <loc_u8_connecte> : TRUE ou FALSE
// Description : 
//		Teste si le client est connecté
//		Si c'est le cas return TRUE
//		Sinon FALSE.
// -------------------------------------------------------------
u8sod TestClientIpConnecte(s8sod* loc_ps8_addrIP);

// -------------------------------------------------------------
// Fonction    : TestPassword
// Entrees     : <loc_ps8_addrIP> : adresse IP du client
//				 <loc_s32_AccessLevel> : niveau minimum d'acces
// Sortie      : <TRUE ou FALSE>
// Description : 
//		Teste si le client est recensé dans le fichier CLIENT.INI
//		Si c'est le cas return TRUE avec Renouvellement de son tps d'accès.
//		Sinon FALSE.
// -------------------------------------------------------------
u8sod TestPassword(char* loc_ps8_addrIP, s32sod loc_s32_AccessLevel);

// -------------------------------------------------------------
// Fonction    : AddClient
// Entrees     : <loc_ps8_addrIP> : adresse IP du client
//				 <loc_s32_AccessLevel> : niveau minimum d'acces
// Sortie      : <TRUE ou FALSE>
// Description : 
//		Ajoute un client dans la table d'accès cad le fichier CLIENT.INI
//		return TRUE si effectué
//		FALSE si non effectué car TOO MANY LOGGED CLIENTS
//		ou erreur.
// Historique  :
// -------------------------------------------------------------
u8sod AddClient(s8sod* loc_ps8_addrIP, s32sod loc_s32_AccessLevel);

//=====================================================================================
// Fonction		: u8GestionDeconnexionClient
// Entrees		: rien
// Sortie		: TRUE ou FALSE
// Description	: Gestion de déconnexion des clients
//=====================================================================================
u8sod u8GestionDeconnexionClient(void);

//=====================================================================================
// Fonction		: SetConfig_ModuleClient
// Entrees		: <loc_u8_max_client>	: paramètre de config nb max client
//				: <loc_u16_duree_inactivite_http>	: paramètre de config durée max iniactivite http
// Sortie		: rien
// Auteur		: CM - 01/10/2009 -
// Description	: Configure le module de Client en fonction de la configuration
//=====================================================================================
void SetConfig_ModuleClient(u8sod loc_u8_max_client, u16sod loc_u16_duree_inactivite_http);

//=====================================================================================
// Fonction		: InitModule_Client
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/09/2007 -
// Description	: Initialisation du module de Client
//=====================================================================================
void InitModule_Client(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

