/*========================================================================*/
/* NOM DU FICHIER  : api_network.h			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/10/2011                                           */
/* Libelle         : Base de donn�es: API li�s aux donn�es r�seau		  */
/* Projet          : STREAMEASY                                           */
/* Indice          : BE086                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 13/10/2011 CM
// - CREATION
//BE086 CM 07/09/2012
// - Ajout fonction test adresse MAC
// - Ajout definition adresse MAC ACTIA SODIELEC
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ______________________*/

/*_______II - DEFINE _____________________________________________________*/

#ifdef _API_NETWORK
#define _API_NETWORK_EXT
#else
#define _API_NETWORK_EXT	extern
#endif

//--------------------------------------------------------
//D�finition plage des adresses MAC SODIELEC
//--------------------------------------------------------
#define BYTE0_MAC_SODIELEC 0x00
#define BYTE1_MAC_SODIELEC 0x10
#define BYTE2_MAC_SODIELEC 0x02
#define WORD_MAC_SODIELEC_MIN 0x0FC500
#define WORD_MAC_SODIELEC_MAX 0x0FD4FF


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_______IV - PROTOTYPES DEFINIS__________________________________________*/

//============================================================================
// Fonction		: ps8GetStringIp
// Entrees		: <loc_u32_adresse_ip> : adresse IP
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 12/07/2007 -
// Description	: convertit un entier en chaine de caratctere 
//                type adresse IP : XXX.YYY.ZZZ.WWW
//                utilise la variable static loc_ps8_chaine[30]
//============================================================================
//s8sod* ps8GetStringIp(u32sod loc_u32_adresse_ip);

//============================================================================
// Fonction		: ps8GetChAddressMac
// Entrees		: <loc_pu8_adr_mac< : pointeur sur tableau adresse MAC
// Sortie		: <loc_ps8_chaine< : chaine � afficher
// Auteur		: CM - 26/09/2011 -
// Description	: renvoie la cha�ne � afficher de l'adresse MAC
//============================================================================
//s8sod* ps8GetChAddressMac(u8sod *loc_pu8_adr_mac);

//=====================================================================================
// Fonction		: u8TestConfigIP_Unicast
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 14/10/2011 -
// Description	: Test si adresse IP unicast
//=====================================================================================
//u8sod u8TestConfigIP_Unicast(u32sod loc_u32_adresse_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_Multicast
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 14/10/2011 -
// Description	: Test si adresse IP multicast
//=====================================================================================
//u8sod u8TestConfigIP_Multicast(u32sod loc_u32_adresse_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_ReservedMulticast
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 14/10/2011 -
// Description	: Test si adresse IP multicast (dans plage r�serv�e)
//=====================================================================================
//u8sod u8TestConfigIP_ReservedMulticast(u32sod loc_u32_adresse_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_Host
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2009 -
// Description	: Test si masque et adresse IP forme une adresse de type HOST
//=====================================================================================
//u8sod u8TestConfigIP_Host(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_Net
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si masque et adresse IP forme un adresse de type NETWORK
//=====================================================================================
//u8sod u8TestConfigIP_Net(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip);

//=====================================================================================
// Fonction		: u8TestConfigIP_Subnet
// Entrees		: <loc_u32_subnet_ip>	: adresse IP 
//				: <loc_u32_subnet_mask> : masque sous-reseau
//				: <loc_u32_ip_a_tester> : IP � tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2010 -
// Description	: Test si l'adresse IP � tester est dans le sous r�seau
//=====================================================================================
//u8sod u8TestConfigIP_Subnet(u32sod loc_u32_subnet_ip, u32sod loc_u32_subnet_mask, u32sod loc_u32_ip_a_tester);

//=====================================================================================
// Fonction		: u8TestConfigMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si le masque de sous r�seau est valide
//=====================================================================================
//u8sod u8TestConfigMask(u32sod loc_u32_subnet_mask);

//=====================================================================================
// Fonction		: u8GetNumberMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_numbermask>  : 
// Auteur		: CM - 30/03/2010 -
// Description	: Retourne la valeur num�rique du masque de sous-r�seau
//=====================================================================================
//u8sod u8GetNumberMask(u32sod loc_u32_subnet_mask);

//============================================================================
// Fonction		: u32DecodageAdresseReseau
// Entrees		: La cha�ne de caract�res et une variable de bon fonctionnement de la fonction
// Sortie		: L'adresse r�seau d�cod�e
// Auteur		: CaF
// Description	: Permet de d�coder l'adresse r�seau d'une cha�ne de
//				caract�res de la forme "XXX.XXX.XXX.XXX"
//============================================================================
u32sod u32DecodageAdresseReseau (s8sod	ps8_ligne[30 + 1], u8sod *pu8_retour);

//=====================================================================================
// Fonction		: u8TestValidString_MACAddress
// Entrees		: <loc_ps8_string_mac>	: chaine adresse mac � tester 
//				: <loc_pu8_tab_mac<	: resultat adresse mac (tableau de taille ETHER_ADDR_LEN)
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 07/07/2012 -
// Description	: Test adresse MAC
//=====================================================================================
//u8sod u8TestValidString_MACAddress(s8sod *loc_ps8_string_mac, u8sod *loc_pu8_tab_mac);

//=====================================================================================
// Fonction		: u8TestValidMACAddress_ACTIASODIELEC
// Entrees		: <loc_pu8_tab_mac<	: adresse mac (tableau de taille ETHER_ADDR_LEN)
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/09/2012 -
// Description	: Test adresse MAC (ACTIA SODIELEC)
//=====================================================================================
//u8sod u8TestValidMACAddress_ACTIASODIELEC(u8sod *loc_pu8_tab_mac);

//=====================================================================================
// Fonction		: InitModule_Api_Network
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/10/2011 -
// Description	: Initialisation du module de api_network
//=====================================================================================
//void InitModule_Api_Network(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _API_NETWORK
const u8sod	PU8_ADRESSE_MAC_SODIELEC_MIN[ETHER_ADDR_LEN] =
{
	BYTE0_MAC_SODIELEC,
	BYTE1_MAC_SODIELEC,
	BYTE2_MAC_SODIELEC,
	(u8sod)(WORD_MAC_SODIELEC_MIN >> 16),
	(u8sod)(WORD_MAC_SODIELEC_MIN >> 8),
	(u8sod)(WORD_MAC_SODIELEC_MIN)
};

const u8sod	PU8_ADRESSE_MAC_SODIELEC_MAX[ETHER_ADDR_LEN] =
{
	BYTE0_MAC_SODIELEC,
	BYTE1_MAC_SODIELEC,
	BYTE2_MAC_SODIELEC,
	(u8sod)(WORD_MAC_SODIELEC_MAX >> 16),
	(u8sod)(WORD_MAC_SODIELEC_MAX >> 8),
	(u8sod)(WORD_MAC_SODIELEC_MAX)
};
#else
extern const u8sod	PU8_ADRESSE_MAC_SODIELEC_MIN[ETHER_ADDR_LEN];
extern const u8sod	PU8_ADRESSE_MAC_SODIELEC_MAX[ETHER_ADDR_LEN];
#endif

