/*========================================================================*/
/* NOM DU FICHIER  : api_network.c		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 13/10/2011                                           */
/* Libelle         : Base de données: API liés aux données réseau		  */
/* Projet          : STREAMEASY                                           */
/* Indice          : BE086                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 13/10/2011 CM
// - CREATION
//BE014 02/01/2012 CM
// - Correction bug fonction u32DecodageAdresseReseau (KO sur carte NH4)
//BE086 CM 07/09/2012
// - Ajout fonction test adresse MAC
// - Ajout definition adresse MAC ACTIA SODIELEC
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _API_NETWORK

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//============================================================================
// Fonction		: ps8GetStringIp
// Entrees		: <loc_u32_adresse_ip> : adresse IP
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 12/07/2007 -
// Description	: convertit un entier en chaine de caratctere 
//                type adresse IP : XXX.YYY.ZZZ.WWW
//                utilise la variable static loc_ps8_chaine[30]
//============================================================================
/*s8sod* ps8GetStringIp(u32sod loc_u32_adresse_ip)
{
	static s8sod loc_ps8_chaine[30];

	loc_ps8_chaine[0] = 0;	//INIT

#ifdef __LITTLE_ENDIAN__
#else
#ifdef __BIG_ENDIAN
#else
#error "ERROR  LITTLE ou BIG ENDIAN IN MODULE [config.c]"
#endif
#endif

	sprintf(loc_ps8_chaine,"%lu.%lu.%lu.%lu",
			((loc_u32_adresse_ip>>24)&0x00FF),
			((loc_u32_adresse_ip>>16)&0x00FF),
			((loc_u32_adresse_ip>>8)&0x00FF),
			(loc_u32_adresse_ip&0x00FF));
	loc_ps8_chaine[15]=0; // pour etre sur!

	return (&loc_ps8_chaine[0]);
}*//*ps8GetStringIp*/


//============================================================================
// Fonction		: ps8GetChAddressMac
// Entrees		: <loc_pu8_adr_mac< : pointeur sur tableau adresse MAC
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 26/09/2011 -
// Description	: renvoie la chaîne à afficher de l'adresse MAC
//============================================================================
/*s8sod* ps8GetChAddressMac(u8sod *loc_pu8_adr_mac)
{
	static s8sod loc_ps8_chaine[UI_TAILLE_MAX_MESSAGE];

	loc_ps8_chaine[0] = 0;	//INIT

	sprintf(loc_ps8_chaine,"%02X:%02X:%02X:%02X:%02X:%02X",
			loc_pu8_adr_mac[0], loc_pu8_adr_mac[1],
			loc_pu8_adr_mac[2], loc_pu8_adr_mac[3],
			loc_pu8_adr_mac[4], loc_pu8_adr_mac[5]);

	return (&loc_ps8_chaine[0]);
}*//*ps8GetChAddressMac*/


//=====================================================================================
// Fonction		: u8TestConfigIP_Unicast
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 14/10/2011 -
// Description	: Test si adresse IP unicast
//=====================================================================================
/*u8sod u8TestConfigIP_Unicast(u32sod loc_u32_adresse_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if((ADRESSE_IP_NULLE == loc_u32_adresse_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_adresse_ip)
	  )//CONDITION: adresse IP KO
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Unicast: 1) loc_u32_adresse_ip KO :0x%lx \n",
					  loc_u32_adresse_ip);
		loc_u8_resultat = FALSE;
	}

	if(TRUE == u8TestConfigIP_Multicast(loc_u32_adresse_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Unicast: 2) loc_u32_adresse_ip KO :0x%lx \n",
					  loc_u32_adresse_ip);
		loc_u8_resultat = FALSE;
	}
	
	return loc_u8_resultat;
}*//*u8TestConfigIP_Unicast*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Multicast
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 14/10/2011 -
// Description	: Test si adresse IP multicast
//=====================================================================================
/*u8sod u8TestConfigIP_Multicast(u32sod loc_u32_adresse_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if ( (ADRESSE_MULTICAST_MIN > loc_u32_adresse_ip)
	  || (loc_u32_adresse_ip > ADRESSE_MULTICAST_MAX)
	  )//CONDITION: adresse non multicast
	{
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}*//*u8TestConfigIP_Multicast*/

//=====================================================================================
// Fonction		: u8TestConfigIP_ReservedMulticast
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 14/10/2011 -
// Description	: Test si adresse IP multicast (dans plage réservée)
//=====================================================================================
/*u8sod u8TestConfigIP_ReservedMulticast(u32sod loc_u32_adresse_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if ( (ADRESSE_MULTICAST_RESERVED_MIN > loc_u32_adresse_ip)
	 ||  (loc_u32_adresse_ip > ADRESSE_MULTICAST_RESERVED_MAX)
	  )//CONDITION: adresse non multicast réservée
	{
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}*//*u8TestConfigIP_ReservedMulticast*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Host
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2009 -
// Description	: Test si masque et adresse IP forme une adresse de type HOST
//=====================================================================================
/*u8sod u8TestConfigIP_Host(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(FALSE == u8TestConfigIP_Unicast(loc_u32_adresse_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Host: loc_u32_adresse_ip KO :0x%0lx \n",
					  loc_u32_adresse_ip);
		loc_u8_resultat = FALSE;
	}	

	if((ADRESSE_IP_NULLE == loc_u32_masque_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_masque_ip)
	  )//CONDITION: masque sous-réseau KO
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Host: loc_u32_masque_ip 1 KO :0x%0lx \n",
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == u8TestConfigMask(loc_u32_masque_ip))
		{
			MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Host: loc_u32_masque_ip 2. KO :0x%08lX \n",
						  loc_u32_masque_ip);
			loc_u8_resultat = FALSE;
		}
	}

	//On vérifie que l'adresse IP et le mask définissent un sous-reseau non nul
	if(0 == (loc_u32_adresse_ip & loc_u32_masque_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Host: loc_u32_adresse_ip=0x%0lx, loc_u32_masque_ip=0x%0lx KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}

	//  --> vérification que l'adresse IP n'est pas une adresse nulle pour le masque de sous-réseau défini
	if(0 == (loc_u32_adresse_ip & (u32sod)(~loc_u32_masque_ip)))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Host: loc_u32_adresse_ip=0x%0lx, loc_u32_masque_ip=0x%0lx KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}
	//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
	if(MASK_RESEAU_SUR_32 == (loc_u32_adresse_ip | loc_u32_masque_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Host: loc_u32_adresse_ip=0x%0lx, loc_u32_masque_ip=0x%0lx KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}*//*u8TestConfigIP_Host*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Net
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si masque et adresse IP forme un adresse de type NETWORK
//=====================================================================================
/*u8sod u8TestConfigIP_Net(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(FALSE == u8TestConfigIP_Unicast(loc_u32_adresse_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Net: loc_u32_adresse_ip KO :0x%0lx \n",
					  loc_u32_adresse_ip);
		loc_u8_resultat = FALSE;
	}	

	if((ADRESSE_IP_NULLE == loc_u32_masque_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_masque_ip)
	  )//CONDITION: masque sous-réseau KO
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Net: loc_u32_masque_ip KO :0x%0lx \n",
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == u8TestConfigMask(loc_u32_masque_ip))
		{
			MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Net: loc_u32_masque_ip KO :0x%0lx \n",
						  loc_u32_masque_ip);
			loc_u8_resultat = FALSE;
		}
	}

	//On vérifie que l'adresse IP et le mask définissent un sous-reseau non nul
	if(0 == (loc_u32_adresse_ip & loc_u32_masque_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Net: loc_u32_adresse_ip=0x%0lx, loc_u32_masque_ip=0x%0lx KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}

	//  --> vérification que l'adresse IP est une adresse nulle pour le masque de sous-réseau défini
	if(0 != (loc_u32_adresse_ip & (u32sod)(~loc_u32_masque_ip)))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Net: loc_u32_adresse_ip=0x%0lx, loc_u32_masque_ip=0x%0lx KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}
	//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
	if(MASK_RESEAU_SUR_32 == (loc_u32_adresse_ip | loc_u32_masque_ip))
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Net: loc_u32_adresse_ip=0x%0lx, loc_u32_masque_ip=0x%0lx KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip);
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}*//*u8TestConfigIP_Net*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Subnet
// Entrees		: <loc_u32_subnet_ip>	: adresse IP 
//				: <loc_u32_subnet_mask> : masque sous-reseau
//				: <loc_u32_ip_a_tester> : IP à tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2010 -
// Description	: Test si l'adresse IP à tester est dans le sous réseau
//=====================================================================================
/*u8sod u8TestConfigIP_Subnet(u32sod loc_u32_subnet_ip, u32sod loc_u32_subnet_mask, u32sod loc_u32_ip_a_tester)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	//On vérifie que l'adresse IP à tester est dans le meme sous-reseau (définie par IP/mask subnet)
	if((loc_u32_subnet_ip & loc_u32_subnet_mask) != (loc_u32_ip_a_tester & loc_u32_subnet_mask)) //CONDITION: pas de le meme sous-réseau
	{
		MACRO_DPRINTF(LOG_ERR, "u8TestConfigIP_Subnet: loc_u32_subnet_ip=0x%0lx, loc_u32_subnet_mask=0x%0lx, loc_u32_ip_a_tester=0x%0lx KO \n",
					  loc_u32_subnet_ip,
					  loc_u32_subnet_mask,
					  loc_u32_ip_a_tester);
		loc_u8_resultat = FALSE;
	}


	return loc_u8_resultat;
}*//*u8TestConfigIP_Subnet*/

//=====================================================================================
// Fonction		: u8TestConfigMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si le masque de sous réseau est valide
//=====================================================================================
/*u8sod u8TestConfigMask(u32sod loc_u32_subnet_mask)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u8sod	loc_u8_flag_bit_nul;

	loc_u8_resultat = TRUE;	//INIT
	loc_u8_flag_bit_nul = FALSE;	//INIT

	//on test si le masque de sous-réseau est bien construit
	loc_u8_flag_bit_nul = FALSE;	//RAZ
	for(loc_u16_i=0;loc_u16_i<NB_BITS_DANS_U32;loc_u16_i++)
	{
		if(loc_u32_subnet_mask & (1<<((NB_BITS_DANS_U32-1)-(u32sod)loc_u16_i)))
		{
			if(TRUE == loc_u8_flag_bit_nul)	//CONDITION: bit nul déjà détecté
			{
				//masque sous-réseau KO
				loc_u16_i = NB_BITS_DANS_U32+1;	//on sort
				loc_u8_resultat = FALSE;
				MACRO_DPRINTF(LOG_ERR, "u8TestConfigMask: loc_u32_subnet_mask KO :0x%0lx \n",
							  loc_u32_subnet_mask);
			}
		}
		else
		{
			loc_u8_flag_bit_nul = TRUE;
		}
	}

	return loc_u8_resultat;
}*//*u8TestConfigMask*/

//=====================================================================================
// Fonction		: u8GetNumberMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_numbermask>  : 
// Auteur		: CM - 30/03/2010 -
// Description	: Retourne la valeur numérique du masque de sous-réseau
//=====================================================================================
/*u8sod u8GetNumberMask(u32sod loc_u32_subnet_mask)
{
	u16sod	loc_u16_i;
	u8sod	loc_u8_flag_bit_nul;
	u8sod	loc_u8_numbermask;
	
	loc_u8_numbermask = 0;	//INIT

	loc_u8_flag_bit_nul = FALSE;	//INIT

	//on test si le masque de sous-réseau est bien construit
	loc_u8_flag_bit_nul = FALSE;	//RAZ
	for(loc_u16_i=0;loc_u16_i<NB_BITS_DANS_U32;loc_u16_i++)
	{
		if(loc_u32_subnet_mask & (1<<((NB_BITS_DANS_U32-1)-loc_u16_i)))
		{
			loc_u8_numbermask ++;
			if(TRUE == loc_u8_flag_bit_nul)	//CONDITION: bit nul déjà détecté
			{
				//masque sous-réseau KO
				loc_u16_i = NB_BITS_DANS_U32+1;	//on sort
			}
		}
		else
		{
			loc_u8_flag_bit_nul = TRUE;
		}
	}

	return loc_u8_numbermask;
}*//*u8GetNumberMask*/

//============================================================================
// Fonction		: u32DecodageAdresseReseau
// Entrees		: La chaîne de caractères et une variable de bon fonctionnement de la fonction
// Sortie		: L'adresse réseau décodée
// Auteur		: CaF
// Description	: Permet de décoder l'adresse réseau d'une chaîne de
//				caractères de la forme "XXX.XXX.XXX.XXX"
//============================================================================
u32sod u32DecodageAdresseReseau (s8sod	ps8_ligne[30 + 1], u8sod *pu8_retour)
{
	typedef	union 
	{
		u8sod			u8_champ[4];
		u32sod			u32_champ;
	}U_UNION_ADRESSE;

	U_UNION_ADRESSE	loc_u_adresse_IP;
	s32sod			loc_s32_sscanf;
	u32sod			loc_u32_tempo[4];
	u32sod			loc_u32_adresse_decodee;

	//Initialisation
	*pu8_retour = FALSE;

	//On lit a part les infos de route et d'interface, car interface mal décodée par sscanf
	loc_s32_sscanf = sscanf(ps8_ligne, "%lu.%lu.%lu.%lu",
							(u32sod *) &loc_u32_tempo[0],
							(u32sod *) &loc_u32_tempo[1],
							(u32sod *) &loc_u32_tempo[2],
							(u32sod *) &loc_u32_tempo[3]);

	loc_u_adresse_IP.u8_champ[0] = (u8sod)loc_u32_tempo[3];
	loc_u_adresse_IP.u8_champ[1] = (u8sod)loc_u32_tempo[2];
	loc_u_adresse_IP.u8_champ[2] = (u8sod)loc_u32_tempo[1];
	loc_u_adresse_IP.u8_champ[3] = (u8sod)loc_u32_tempo[0];

	if(4 == loc_s32_sscanf)
	{
		loc_u32_adresse_decodee = (loc_u_adresse_IP.u32_champ & 0xFFFFFFFF);
		
		//Tout s'est bien passé
		*pu8_retour = TRUE;
	}

	return loc_u32_adresse_decodee;

}// u32DecodageAdresseReseau

//=====================================================================================
// Fonction		: u8TestValidString_MACAddress
// Entrees		: <loc_ps8_string_mac>	: chaine adresse mac à tester 
//				: <loc_pu8_tab_mac<	: resultat adresse mac (tableau de taille ETHER_ADDR_LEN)
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 07/07/2012 -
// Description	: Test adresse MAC
//=====================================================================================
/*u8sod u8TestValidString_MACAddress(s8sod *loc_ps8_string_mac, u8sod *loc_pu8_tab_mac)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_i;
	u32sod	loc_pu32_valsscanf[ETHER_ADDR_LEN];

	loc_u8_resultat = TRUE;	//INIT

	if(ETHER_ADDR_LEN !=  sscanf(loc_ps8_string_mac,"%02lX:%02lX:%02lX:%02lX:%02lX:%02lX",
								 &loc_pu32_valsscanf[0],
								 &loc_pu32_valsscanf[1],
								 &loc_pu32_valsscanf[2],
								 &loc_pu32_valsscanf[3],
								 &loc_pu32_valsscanf[4],
								 &loc_pu32_valsscanf[5])
	  )//CONDITION: lecture adresse MAC KO
	{
		loc_u8_resultat = FALSE;
		MACRO_DPRINTF(LOG_ERR, "u8TestValidString_MACAddress: (%s) format KO\n",loc_ps8_string_mac);
	}
	else//CONDITION: lecture adresse MAC OK
	{
		//test chaque octet
		for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
		{
			if(loc_pu32_valsscanf[loc_u8_i] > 0xFF)
			{
				loc_u8_resultat = FALSE;
				MACRO_DPRINTF(LOG_ERR, "u8TestValidString_MACAddress: (%s) idx=%lu KO\n",loc_ps8_string_mac,loc_pu32_valsscanf[loc_u8_i]);
				loc_u8_i = ETHER_ADDR_LEN+1; //KO
			}
		}

		if(TRUE == loc_u8_resultat)
		{
			for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
			{
				loc_pu8_tab_mac[loc_u8_i] = (u8sod)loc_pu32_valsscanf[loc_u8_i];
			}
		}
	}

	return loc_u8_resultat;
}*//*u8TestValidString_MACAddress*/

//=====================================================================================
// Fonction		: u8TestValidMACAddress_ACTIASODIELEC
// Entrees		: <loc_pu8_tab_mac<	: adresse mac (tableau de taille ETHER_ADDR_LEN)
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/09/2012 -
// Description	: Test adresse MAC (ACTIA SODIELEC)
//=====================================================================================
/*u8sod u8TestValidMACAddress_ACTIASODIELEC(u8sod *loc_pu8_tab_mac)
{
	u8sod loc_u8_resultat;
	u32sod loc_u32_word;

	loc_u8_resultat = TRUE;	//INIT

	if((BYTE0_MAC_SODIELEC != loc_pu8_tab_mac[0])||
	   (BYTE1_MAC_SODIELEC != loc_pu8_tab_mac[1])||
	   (BYTE2_MAC_SODIELEC != loc_pu8_tab_mac[2])
	  )
	{
		loc_u8_resultat = FALSE;
	}

	loc_u32_word = (u32sod)loc_pu8_tab_mac[3] << 16;
	loc_u32_word |= (u32sod)loc_pu8_tab_mac[4] << 8;
	loc_u32_word |= (u32sod)loc_pu8_tab_mac[5];
	
	if((WORD_MAC_SODIELEC_MIN > loc_u32_word)||
	   (loc_u32_word > WORD_MAC_SODIELEC_MAX)
	  )
	{
		loc_u8_resultat = FALSE;
	}
	
	return loc_u8_resultat;
}*//*u8TestValidMACAddress_ACTIASODIELEC*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Api_Network
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/10/2011 -
// Description	: Initialisation du module de api_network
//=====================================================================================
void InitModule_Api_Network(void)
{

}/*InitModule_Api_Network*/

