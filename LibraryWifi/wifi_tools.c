/*========================================================================*/
/* NOM DU FICHIER  : wifi_tools.c  	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : Module commun à plusieurs process (gérant le Wifi)   */
/* Projet          : WRM100		                                          */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
// - CREATION
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE031.3 08/06/2010 JP
// - dans la page test production final, l'etat de la connexion de la station est memorise avec code couleur (rouge, orange,vert)
//BE040 13/09/2010 CM
// - Suppresion code inutile
// - Nouveaux projets WRM100
//BE047 29/11/2010 CM
// - Gestion mode dégradé - connection à AP impossible en permanence suite à configuration wifi 
//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
//BE058 21/01/2011 CM
// - Modification gestion exploitation wifi
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//WIFI du sous-traitant du driver

/*_____II - DEFINE SBIT __________________________________________________*/

#define _WIFI_TOOLS


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8GetWifiBSSID_Ioctl
// Entrees		: <loc_ps_exp_station<: pointeur sur l'exploitation de la station
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 09/09/2009 -
// Description	: Extraction info BSSID
//=====================================================================================
u8sod u8GetWifiBSSID_Ioctl(S_STRUCT_EXP_STATION *loc_ps_exp_station)
{
	const struct ether_addr ether_zero = {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }};
	const struct ether_addr ether_bcast = {{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }};
	const struct ether_addr ether_hack = {{ 0x44, 0x44, 0x44, 0x44, 0x44, 0x44 }};
	
	u8sod loc_u8_resultat;
	u8sod loc_u8_cpt_essai;
	u8sod loc_u8_i;
	
	s32sod loc_s32_sockfd;
	struct iwreq loc_t_req;

	struct sockaddr	loc_t_ap_addr;
	struct ether_addr *loc_pt_ether_wap;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0; //INIT
	loc_u8_i = 0; //INIT
	
	memset(&loc_t_req, 0, sizeof(struct iwreq)); //INIT
	memset(&loc_t_ap_addr, 0, sizeof(struct sockaddr)); //INIT
	loc_pt_ether_wap = NULL; //INIT

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);

	do{

		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("u8GetWifiBSSID_Ioctl: Could not create simple datagram socket \n");
		}
		else
		{
			/* Perform the ioctl */
			if(ioctl(loc_s32_sockfd, SIOCGIWAP, &loc_t_req) < 0)
			{
				perror("u8GetWifiBSSID_Ioctl: Error performing SIOCGIWAP \n");
				close(loc_s32_sockfd);
			}
			else
			{
				close(loc_s32_sockfd);

				loc_u8_resultat = TRUE;
				
				/* Get AP address */
				memcpy(&loc_t_ap_addr, &(loc_t_req.u.ap_addr), sizeof (struct sockaddr));

				loc_pt_ether_wap = (struct ether_addr *) loc_t_ap_addr.sa_data;

				for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
				{
					loc_ps_exp_station->pu8_bssid_add_mac[loc_u8_i] = loc_pt_ether_wap->ether_addr_octet[loc_u8_i];
				}

				if(!s32Ether_cmp(loc_pt_ether_wap, (struct ether_addr *)&ether_zero))
				{
					loc_ps_exp_station->u8_statut_connexion = STATUT_CONNEXION__NOT_ASSOCIATED;
					loc_ps_exp_station->u8_old_statut_connexion = STATUT_CONNEXION__NOT_ASSOCIATED;
//					printf("u8GetWifiBSSID_Ioctl = Not-Associated\n");
				}
				else
				{
					if(!s32Ether_cmp(loc_pt_ether_wap, (struct ether_addr *)&ether_bcast))
					{
						loc_ps_exp_station->u8_statut_connexion = STATUT_CONNEXION__INVALID;
						loc_ps_exp_station->u8_old_statut_connexion = STATUT_CONNEXION__INVALID;
//						printf("u8GetWifiBSSID_Ioctl = Invalid\n");
					}
					else
					{
						if(!s32Ether_cmp(loc_pt_ether_wap, (struct ether_addr *)&ether_hack))
						{
							loc_ps_exp_station->u8_statut_connexion = STATUT_CONNEXION__NONE;
							loc_ps_exp_station->u8_old_statut_connexion = STATUT_CONNEXION__NONE;
//							printf("u8GetWifiBSSID_Ioctl = None\n");
						}
						else
						{
							loc_ps_exp_station->u8_statut_connexion = STATUT_CONNEXION__ASSOCIATED;
//							printf("u8GetWifiBSSID_Ioctl = %02X:%02X:%02X:%02X:%02X:%02X\n",
//								   loc_pt_ether_wap->ether_addr_octet[0], loc_pt_ether_wap->ether_addr_octet[1],
//								   loc_pt_ether_wap->ether_addr_octet[2], loc_pt_ether_wap->ether_addr_octet[3],
//								   loc_pt_ether_wap->ether_addr_octet[4], loc_pt_ether_wap->ether_addr_octet[5]);
						}
					}
				}
			}
		}
		
		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));
	
	return loc_u8_resultat;

}/*u8GetWifiBSSID_Ioctl*/

//=====================================================================================
// Fonction		: u8GetWifiESSID_Ioctl
// Entrees		: <loc_ps_exp_station<: pointeur sur l'exploitation de la station
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 13/12/2010 -
// Description	: Extraction info nom du SSID
//=====================================================================================
u8sod u8GetWifiESSID_Ioctl(S_STRUCT_EXP_STATION *loc_ps_exp_station)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_cpt_essai;
	u8sod loc_u8_i;

	s32sod loc_s32_sockfd;
	struct iwreq loc_t_req;
	s8sod	loc_ps8_buffer[NB_MAX_CHAINE_SSID+1];

	struct iw_point loc_t_data;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0; //INIT
	loc_u8_i = 0; //INIT

	memset(&loc_t_req, 0, sizeof(struct iwreq)); //INIT
	memset(&loc_t_data, 0, sizeof(struct iw_point)); //INIT
	memset(loc_ps8_buffer, 0, NB_MAX_CHAINE_SSID); //INIT

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_req.ifr_name, NOM_INTERFACE_WIFI);
	loc_t_req.u.essid.pointer = loc_ps8_buffer;
	loc_t_req.u.essid.length = NB_MAX_CHAINE_SSID;

	do{

		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("u8GetWifiESSID_Ioctl: Could not create simple datagram socket \n");
		}
		else
		{
			/* Perform the ioctl */
			if(ioctl(loc_s32_sockfd, SIOCGIWESSID, &loc_t_req) < 0)
			{
				perror("u8GetWifiESSID_Ioctl: Error performing SIOCGIWESSID \n");
			}
			else
			{
				loc_u8_resultat = TRUE;

				if(NULL != loc_t_req.u.essid.pointer)
				{
					if(loc_t_req.u.essid.length <= NB_MAX_CHAINE_SSID)
					{
						memcpy(loc_ps_exp_station->ps8_ssid_inprogress, loc_t_req.u.essid.pointer, loc_t_req.u.essid.length);
						loc_ps_exp_station->ps8_ssid_inprogress[loc_t_req.u.essid.length] = 0;	//fin de chaine
					}
				}
				else
				{
					perror("u8GetWifiESSID_Ioctl: essid is NULL \n");
				}

			}

			//Fermeture du socket
			close(loc_s32_sockfd);
		}

		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));

	return loc_u8_resultat;

}/*u8GetWifiESSID_Ioctl*/

//=====================================================================================
// Fonction		: s32Ether_cmp
// Entrees		: <loc_pt_eth1<: adresse ethernet 1
//				: <loc_pt_eth2<: adresse ethernet 2
// Sortie		: <resultat>: 0:si identique, sinon !=0
// Auteur		: CM - 09/09/2009 -
// Description	: Compare two ethernet addresses
//=====================================================================================
s32sod s32Ether_cmp(struct ether_addr* loc_pt_eth1, struct ether_addr* loc_pt_eth2)
{
	return memcmp(loc_pt_eth1, loc_pt_eth2, sizeof(*loc_pt_eth1));
}/*s32Ether_cmp*/



/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Wifi_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de wifi_tools
//=====================================================================================
void InitModule_Wifi_Tools(void)
{
	
}/*InitModule_Wifi_Tools*/

