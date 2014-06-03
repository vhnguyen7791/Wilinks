/*========================================================================*/
/* NOM DU FICHIER  : ksz8893.c	 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 06/07/2010                                           */
/* Libelle         : Base de données: controle du switch KSZ8893		  */
/* Projet          : WRM100                                               */
/* Indice          : BE046                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE037 06/07/2010 CM
// - CREATION
//BE046 17/11/2010 CM
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _KSZ8893

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"


//Définition sur le statut des ports du switch KSZ8893
#define FICHIER__SYS_SMI_PORT1_LINK_STATUS PATH_DIR_PROC "sys/smi/port1_link_status"
#define FICHIER__SYS_SMI_PORT2_LINK_STATUS PATH_DIR_PROC "sys/smi/port2_link_status"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8GetPortLinkStatus
// Entrees		: <loc_ps8_path_link_status< : chemin vers statut du port
// Sortie		: <loc_u8_resultat>: TRUE si connecté, sinon FALSE
// Auteur		: CM - 06/07/2010 -
// Description	: Test de lecture de /proc/sys/smi/portX_link_status
//=====================================================================================
u8sod u8GetPortLinkStatus(s8sod *loc_ps8_path_link_status)
{
	u8sod loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	loc_ps8_chaine10[10+1];	//au max 2 caractères
	u32sod	loc_u32_valeur;

	loc_u8_resultat = FALSE;	//INIT
	loc_p_handle = NULL;	//INIT
	strcpy(loc_ps8_chaine10, "");	//INIT
	loc_u32_valeur = 0;	//INIT

	if(NULL != (loc_p_handle = fopen( loc_ps8_path_link_status, "rt" )))
	{
		//Lecture de la ligne
		if (NULL != fgets(loc_ps8_chaine10,5,loc_p_handle))
		{
			loc_u32_valeur = atoi(loc_ps8_chaine10);
			if(1 == loc_u32_valeur)//CONDITION: link up
			{
				loc_u8_resultat = TRUE;	 //connecté
			}
		}
		//fermeture du fichier
		fclose (loc_p_handle);
	}

	return loc_u8_resultat;
}/*u8GetPortLinkStatus*/

//=====================================================================================
// Fonction		: u8GetEthernetLinkStatus
// Entrees		: <loc_u8_ixd_port> : PORT_ETHERNET_1 ou PORT_ETHERNET_2
// Sortie		: <loc_u8_resultat>: TRUE si connecté, sinon FALSE
// Auteur		: CM - 06/07/2010 -
// Description	: Test le port ethernet
//=====================================================================================
u8sod u8GetEthernetLinkStatus(u8sod loc_u8_ixd_port)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	switch(loc_u8_ixd_port)
	{
		case PORT_ETHERNET_1:
			//Test port 1
			if(TRUE==u8GetPortLinkStatus(FICHIER__SYS_SMI_PORT1_LINK_STATUS))
			{
				loc_u8_resultat = TRUE;	 //connecté
			}
			break;

		case PORT_ETHERNET_2:
			//Test port 2
			if(TRUE==u8GetPortLinkStatus(FICHIER__SYS_SMI_PORT2_LINK_STATUS))
			{
				loc_u8_resultat = TRUE;	 //connecté
			}
			break;
		default:
			printf("u8GetEthernetLinkStatus: loc_u8_ixd_port=%d KO\n",loc_u8_ixd_port);
			break;
	}

	return loc_u8_resultat;	
}/*u8GetEthernetLinkStatus*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_Ksz8893
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 06/07/2010 -
// Description	: Initialisation du module de ksz8893
//=====================================================================================
void InitModule_Ksz8893(void)
{
	
}/*InitModule_Ksz8893*/

