/*========================================================================*/
/* NOM DU FICHIER  : wifi_ABG_tools.c                                     */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 14/09/2010                                           */
/* Libelle         : Module commun à plusieurs process (gérant Wifi ABG)  */
/* Projet          : WRM100		                                          */
/* Indice          : BE041                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE040 14/09/2010 CM
// - CREATION
//BE041 22/09/2010 CM
// - Ajout IOCTL_GETUSERINFO entre nos applis et driver-N
//	afin de récupérer rssi filter/raw 
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//WIFI du sous-traitant du driver

/*_____II - DEFINE SBIT __________________________________________________*/

#define _WIFI_ABG_TOOLS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

#ifdef _WRM100_ABG_SELECT //necessaire pour la compilation de net-snmp

//=====================================================================================
// Fonction		: u8WlanABG_SetWifiTypePreambule
// Entrees		: <loc_u8_valeur> : valeur du preambule (WF_TYPE_PREAMBULE_SHORT ou WF_TYPE_PREAMBULE_LONG)
// Sortie		: <loc_u8_resultat>: TRUE,si set réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Configure le preamble
//=====================================================================================
u8sod u8WlanABG_SetWifiTypePreambule(u8sod loc_u8_valeur)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_cpt_essai;
	struct iwreq loc_t_req;
	s32sod	loc_s32_sockfd;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0; //INIT
	memset(&loc_t_req, 0, sizeof(struct iwreq)); //INIT

	if(loc_u8_valeur < NB_MAX_WF_TYPE_PREAMBULE)
	{
		//Mise à jour des données nécessaires à la requete
		sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);
		loc_t_req.u.data.length = 1;
		loc_t_req.u.mode = IEEE80211_PARAM_SHPREAMBLE;
		switch(loc_u8_valeur)
		{
			case WF_TYPE_PREAMBULE_SHORT:
				*(loc_t_req.u.name + sizeof(__u32)) = 1; 
				break;
			case WF_TYPE_PREAMBULE_LONG:
				*(loc_t_req.u.name + sizeof(__u32)) = 0; 
				break;
			default:
				break;
		}

		do{
			/* Any old socket will do, and a datagram socket is pretty cheap */
			if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
			{
				perror("u8WlanABG_SetWifiTypePreambule: Could not create simple datagram socket");
			}
			else
			{
				if(ioctl(loc_s32_sockfd, IEEE80211_IOCTL_SETPARAM, &loc_t_req) < 0)
				{
					perror("u8WlanABG_SetWifiTypePreambule: ioctl failed");
				}
				else
				{
					loc_u8_resultat = TRUE;
				}

				close(loc_s32_sockfd);
			}
			loc_u8_cpt_essai ++;
		}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));
	}

	return loc_u8_resultat;
}/*u8WlanABG_SetWifiTypePreambule*/

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiFilterRSSI
// Entrees		: <loc_s32_sockfd> : open file descriptor
//				: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction info RSSI filtrée du driver wifi
//=====================================================================================
u8sod u8WlanABG_GetWifiFilterRSSI(s32sod loc_s32_sockfd, s32sod *loc_ps32_rssi_value)
{
	u8sod loc_u8_resultat;
	struct iwreq loc_t_req;

	loc_u8_resultat = FALSE; //INIT
	memset(&loc_t_req, 0, sizeof(struct iwreq)); //INIT

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);

	if(ioctl(loc_s32_sockfd, IEEE80211_IOCTL_GETRSSI, &loc_t_req) < 0)
	{
		perror("u8WlanABG_GetWifiFilterRSSI: ioctl failed \n");
	}
	else
	{
		*loc_ps32_rssi_value = (s32sod)*((__s32 *)loc_t_req.u.name);
		loc_u8_resultat = TRUE;
	}

	return loc_u8_resultat;
}/*u8WlanABG_GetWifiFilterRSSI*/

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiRawRSSI
// Entrees		: <loc_s32_sockfd> : open file descriptor
//				: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: get rssi of last packet (better beacon?)
//=====================================================================================
u8sod u8WlanABG_GetWifiRawRSSI(s32sod loc_s32_sockfd, s32sod *loc_ps32_rssi_value)
{
	u8sod loc_u8_resultat;
	struct iwreq loc_t_req;

	loc_u8_resultat = FALSE; //INIT
	memset(&loc_t_req, 0, sizeof(struct iwreq)); //INIT

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);

	if(ioctl(loc_s32_sockfd, IEEE80211_IOCTL_GETRAWRSSI, &loc_t_req) < 0)
	{
		perror("u8WlanABG_GetWifiRawRSSI: ioctl failed \n");
	}
	else
	{
		*loc_ps32_rssi_value = (s32sod)*((__s32 *)loc_t_req.u.name);
		loc_u8_resultat = TRUE;
	}

	return loc_u8_resultat;
}/*u8GetWifiInfoRSSI*/

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiRSSIFilter_Ioctl
// Entrees		: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction du paramètre d'exploitation RSSI "Filtré" du driver Wifi
//=====================================================================================
u8sod u8WlanABG_GetWifiRSSIFilter_Ioctl(s32sod *loc_ps32_rssi_value)
{
	u8sod	loc_u8_resultat;
	u8sod loc_u8_cpt_essai;
	s32sod	loc_s32_sockfd;
	u16sod	loc_u16_valeur;
	s32sod	loc_s32_valeur;

	loc_u8_resultat = FALSE; //INIT
	loc_u16_valeur = 0;	//INIT
	loc_u8_cpt_essai = 0; //INIT

	do{
		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("u8WlanABG_GetWifiRSSIFilter_Ioctl: Could not create simple datagram socket \n");
		}
		else
		{
			//Perform IOCTL
			if(TRUE == u8WlanABG_GetWifiFilterRSSI(loc_s32_sockfd, &loc_s32_valeur))
			{
//				printf("FilterRSSI: %d \n",loc_s32_valeur);
				*loc_ps32_rssi_value = loc_s32_valeur;
				loc_u8_resultat = TRUE;
			}
			close(loc_s32_sockfd);
		}
		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));

	return loc_u8_resultat;
}/*u8WlanABG_GetWifiRSSIFilter_Ioctl*/

//=====================================================================================
// Fonction		: u8WlanABG_GetWifiRSSIRaw_Ioctl
// Entrees		: <loc_ps32_rssi_value< : pointeur sur valeur info RSSI
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction du paramètre d'exploitation RSSI "brute" du driver Wifi
//=====================================================================================
u8sod u8WlanABG_GetWifiRSSIRaw_Ioctl(s32sod *loc_ps32_rssi_value)
{
	u8sod	loc_u8_resultat;
	u8sod loc_u8_cpt_essai;
	s32sod	loc_s32_sockfd;
	u16sod	loc_u16_valeur;
	s32sod	loc_s32_valeur;

	loc_u8_resultat = FALSE; //INIT
	loc_u16_valeur = 0;	//INIT
	loc_u8_cpt_essai = 0; //INIT

	do{
		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("u8WlanABG_GetWifiRSSIRaw_Ioctl: Could not create simple datagram socket \n");
		}
		else
		{
			//Perform IOCTL
			if(TRUE == u8WlanABG_GetWifiRawRSSI(loc_s32_sockfd, &loc_s32_valeur))
			{
//				printf("RawRSSI: %d \n",loc_s32_valeur);
				*loc_ps32_rssi_value = loc_s32_valeur;
				loc_u8_resultat = TRUE;
			}

			close(loc_s32_sockfd);
		}
		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));


	return loc_u8_resultat;
}/*u8WlanABG_GetWifiRSSIRaw_Ioctl*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Wifi_ABG_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 14/09/2010 -
// Description	: Initialisation du module de wifi_ABG_tools
//=====================================================================================
void InitModule_Wifi_ABG_Tools(void)
{
}/*InitModule_Wifi_ABG_Tools*/

#endif