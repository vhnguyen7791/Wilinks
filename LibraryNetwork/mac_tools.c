/*========================================================================*/
/* NOM DU FICHIER  : mac_tools.c  	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Module commun à plusieurs process (gérant adr MAC)   */
/* Projet          : WRM100		                                          */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _MAC_TOOLS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8GetMacAddress
// Entrees		: <loc_ps8_nom_interface< : nom de l'interface
//				: >loc_pu8_adr_mac< : adresse MAC retournée (si TRUE)
// Sortie		: <loc_u8_resultat>: TRUE,si get réussi, sinon FALSE
// Auteur		: CM - 26/10/2009 -
// Description	: Extraction adresse MAC de l'interface
//=====================================================================================
u8sod u8GetMacAddress(s8sod *loc_ps8_nom_interface, u8sod *loc_pu8_adr_mac)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_cpt_essai;
	u8sod loc_u8_i;

	s32sod loc_s32_sockfd;
	struct ifreq loc_t_ifreq;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_cpt_essai = 0; //INIT
	for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
	{
		loc_pu8_adr_mac[loc_u8_i] = 0x00; //INIT
	}

	memset(&loc_t_ifreq, 0, sizeof(struct ifreq)); //INIT

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_ifreq.ifr_name, loc_ps8_nom_interface);

	do{
		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("u8GetMacAddress: Could not create simple datagram socket");
		}
		else
		{
			/* Perform the ioctl */
			if(ioctl(loc_s32_sockfd, SIOCGIFHWADDR, &loc_t_ifreq) == -1)
			{
				perror("u8GetMacAddress: Error performing SIOCGIFHWADDR");
				close(loc_s32_sockfd);
			}
			else
			{
				close(loc_s32_sockfd);

				loc_u8_resultat = TRUE;

				for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
				{
					loc_pu8_adr_mac[loc_u8_i] = (u8sod)loc_t_ifreq.ifr_hwaddr.sa_data[loc_u8_i];
				}
			}
		}
		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));

	return loc_u8_resultat;

}/*u8GetMacAddress*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Mac_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de mac_tools
//=====================================================================================
void InitModule_Mac_Tools(void)
{
}/*InitModule_Mac_Tools*/

