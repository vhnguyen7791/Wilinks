/*========================================================================*/
/* NOM DU FICHIER  : wifi_N_tools.c	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 22/09/2010                                           */
/* Libelle         : Module commun à plusieurs process (gérant Wifi N)	  */
/* Projet          : WRM100		                                          */
/* Indice          : BE041                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE041 22/09/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _WIFI_N_TOOLS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

#ifdef _WRM100_N_SELECT //necessaire pour la compilation de net-snmp


//=====================================================================================
// Fonction		: u8WlanN_GetWifiUserInfo
// Entrees		: <loc_s32_sockfd> : open file descriptor
//				: <loc_pt_userinfo_value< : pointeur sur structure userinfo
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 23/09/2010 -
// Description	: get rssi of last packet (better beacon?)
//=====================================================================================
u8sod u8WlanN_GetWifiUserInfo(s32sod loc_s32_sockfd, struct ieee80211req_get_userinfo *loc_pt_userinfo_value)
{
	u8sod loc_u8_resultat;
	struct iwreq loc_t_req;

	loc_u8_resultat = FALSE; //INIT
	memset(&loc_t_req, 0, sizeof(struct iwreq)); //INIT

	//On indique où les données doivent etre stockées
	loc_t_req.u.data.pointer = loc_pt_userinfo_value;
	loc_t_req.u.data.length = sizeof(struct ieee80211req_get_userinfo);

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);

	if(ioctl(loc_s32_sockfd, IEEE80211_IOCTL_GETUSERINFO, &loc_t_req) < 0)
	{
		perror("u8WlanN_GetWifiUserInfo: ioctl failed \n");
	}
	else
	{
		if(loc_t_req.u.data.length == sizeof(struct ieee80211req_get_userinfo))
		{
			*loc_pt_userinfo_value = *((struct ieee80211req_get_userinfo*)loc_t_req.u.data.pointer);
			loc_u8_resultat = TRUE;
		}
		else
		{
			perror("u8WlanN_GetWifiUserInfo: length ko \n");
		}
	}

	return loc_u8_resultat;
}/*u8WlanN_GetWifiUserInfo*/

//=====================================================================================
// Fonction		: u8WlanN_GetWifiUserInfo_Ioctl
//				: <loc_pt_userinfo_value< : pointeur sur structure userinfo
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 23/09/2010 -
// Description	: Extraction du paramètre d'exploitation "userinfo" du driver Wifi
//=====================================================================================
u8sod u8WlanN_GetWifiUserInfo_Ioctl(struct ieee80211req_get_userinfo *loc_pt_userinfo_value)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_cpt_essai;
	s32sod	loc_s32_sockfd;
	struct ieee80211req_get_userinfo loc_t_userinfo_tempo;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0; //INIT
	memset(&loc_t_userinfo_tempo, 0, sizeof(struct ieee80211req_get_userinfo)); //INIT

	do{
		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("u8WlanN_GetWifiUserInfo_Ioctl: Could not create simple datagram socket \n");
		}
		else
		{
			//Perform IOCTL
			/*if(TRUE == u8WlanN_GetWifiUserInfo(loc_s32_sockfd, &loc_t_userinfo_tempo))
			{
				*loc_pt_userinfo_value = loc_t_userinfo_tempo;
				loc_u8_resultat = TRUE;
			}*///Modif by VuHai to ignore error used by
				// driver Aquila

			close(loc_s32_sockfd);
		}
		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));


	return loc_u8_resultat;
}/*u8WlanN_GetWifiUserInfo_Ioctl*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Wifi_N_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 22/09/2010 -
// Description	: Initialisation du module de wifi_N_tools
//=====================================================================================
void InitModule_Wifi_N_Tools(void)
{
}/*InitModule_Wifi_N_Tools*/

#endif