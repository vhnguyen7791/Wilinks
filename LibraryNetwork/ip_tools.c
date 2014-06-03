/*========================================================================*/
/* NOM DU FICHIER  : ip_tools.c  	                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/01/2010                                           */
/* Libelle         : Module commun à plusieurs process (gérant adr IP)	  */
/* Projet          : WRM100		                                          */
/* Indice          : BE024                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE003 07/01/10 CM
// - CREATION
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _IP_TOOLS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8GetIPAddress
// Entrees		: <loc_ps8_nom_interface< : nom de l'interface
//				: >loc_ps8_adr_ip< : adresse IP retournée (si TRUE)
//				: >loc_ps8_mask_ip< : masque IP retourné (si TRUE)
// Sortie		: <loc_u8_resultat>: TRUE, si get réussi, sinon FALSE
// Auteur		: CM - 07/01/2010 -
// Description	: Extraction adresse IP / Mask de l'interface
//=====================================================================================
u8sod u8GetIPAddress(s8sod *loc_ps8_nom_interface, s8sod *loc_ps8_adr_ip, s8sod *loc_ps8_mask_ip)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_result_adr;
	u8sod loc_u8_result_mask;
	u8sod loc_u8_cpt_essai;

	s32sod loc_s32_sockfd;
	struct ifreq loc_t_ifreq;

	loc_u8_resultat = FALSE; //INIT
	loc_u8_result_adr = FALSE; //INIT
	loc_u8_result_mask = FALSE; //INIT
	loc_u8_cpt_essai = 0; //INIT

	memset(&loc_t_ifreq, 0, sizeof(struct ifreq)); //INIT
	strcpy(loc_ps8_adr_ip, ""); //INIT
	strcpy(loc_ps8_mask_ip, ""); //INIT

	//Mise à jour des données nécessaires à la requete
	sprintf(loc_t_ifreq.ifr_name, loc_ps8_nom_interface);
	loc_t_ifreq.ifr_addr.sa_family = AF_INET;

	do{
		loc_u8_result_adr = FALSE; //RAZ
		loc_u8_result_mask = FALSE; //RAZ
		
		/* Any old socket will do, and a datagram socket is pretty cheap */
		if((loc_s32_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("u8GetIPAddress: Could not create simple datagram socket");
		}
		else
		{
			// Perform the ioctl: lecture adresse IP
			if(ioctl(loc_s32_sockfd, SIOCGIFADDR, &loc_t_ifreq) < 0)
			{
//				perror("u8GetIPAddress: Error performing SIOCGIFADDR");
			}
			else
			{
				loc_u8_result_adr = TRUE;

				strcpy(loc_ps8_adr_ip, inet_ntoa( ((struct sockaddr_in *)&loc_t_ifreq.ifr_addr)->sin_addr ));
			}

			// Perform the ioctl: lecture masque sous réseau
			if(ioctl(loc_s32_sockfd, SIOCGIFNETMASK, &loc_t_ifreq) < 0)
			{
//				perror("u8GetIPAddress: Error performing SIOCGIFNETMASK");
			}
			else
			{
				loc_u8_result_mask = TRUE;

				strcpy(loc_ps8_mask_ip, inet_ntoa( ((struct sockaddr_in *)&loc_t_ifreq.ifr_addr)->sin_addr ));
			}

			if((TRUE == loc_u8_result_adr)&&
			   (TRUE == loc_u8_result_mask)
			  ) //CONDITION: lecture OK du mask + adresse IP 
			{
				loc_u8_resultat = TRUE;
			}
			
			close(loc_s32_sockfd);
		}
		loc_u8_cpt_essai ++;
	}while((loc_u8_cpt_essai<3)&&(FALSE == loc_u8_resultat));

	return loc_u8_resultat;

}/*u8GetIPAddress*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Ip_Tools
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 07/01/2010 -
// Description	: Initialisation du module de ip_tools
//=====================================================================================
void InitModule_Ip_Tools(void)
{
}/*InitModule_Ip_Tools*/

