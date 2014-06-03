/*========================================================================*/
/* NOM DU FICHIER  : procfile.c   		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: gestion des fichiers sous /proc	  */
/* Projet          : WRM100                                               */
/* Indice          : BE025                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE025 15/04/2010 CM
// - Modification gestion routage par le processus bird
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _PROCFILE

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/


//=====================================================================================
// Fonction		: u8ProcNetRoute_DecodeLine
// Entrees		: <loc_ps8_ligne_code<	: ligne du fichier
//				  <loc_pt_route<: pointeur sur route
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Decode ligne du fichier /proc/net/route (liste des routes actives)
//=====================================================================================
u8sod u8ProcNetRoute_DecodeLine(s8sod *loc_ps8_ligne_code, S_STRUCT_IP_ROUTE_STATIC *loc_pt_route)
{
	u8sod	loc_u8_resultat;
	s32sod	loc_s32_sscanf_route;
	s8sod	loc_ps8_nom_interface[16];

	loc_u8_resultat = TRUE; //INIT

	loc_s32_sscanf_route = 0; //INIT
	memset(loc_pt_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //RAZ
	strcpy(loc_ps8_nom_interface,""); //RAZ

	loc_s32_sscanf_route = sscanf(loc_ps8_ligne_code, "%s\t%08lX\t%08lX\t%*04X\t%*d\t%*u\t%*d\t%08lX\t%*d\t%*u\t%*u",
								  loc_ps8_nom_interface,
								  &loc_pt_route->u32_destination_ip,
								  &loc_pt_route->u32_gateway_ip,
								  &loc_pt_route->u32_destination_mask);

	if(4 == loc_s32_sscanf_route)//CONDITION: lecture de 4 valeurs
	{
		if(0==strcmp(loc_ps8_nom_interface, "*"))//CONDITION: PAS D'INTERFACE CONNU
		{
			loc_pt_route->u8_interface = INTERFACE_AUTOMATIQUE;
		}
		else
		{
			if(0==strcmp(loc_ps8_nom_interface, NOM_INTERFACE_ETHERNET))//CONDITION: INTERFACE LAN
			{
				loc_pt_route->u8_interface = INTERFACE_LAN;
			}
			else
			{
				if(0==strcmp(loc_ps8_nom_interface, NOM_INTERFACE_WIFI))//CONDITION: INTERFACE WLAN
				{
					loc_pt_route->u8_interface = INTERFACE_WLAN;
				}
				else
				{
					loc_u8_resultat = FALSE; //Interface inconnu
					MACRO_PRINTF(("u8ProcNetRoute_DecodeLine: KO Interface inconnu:%s !!!\n",
								  loc_ps8_nom_interface));
				}
			}
		}
	}
	else
	{
		loc_u8_resultat = FALSE; //Interface inconnu
		MACRO_PRINTF(("u8ProcNetRoute_DecodeLine: KO decodage ligne (%d) :%s !!!\n",
			   loc_s32_sscanf_route,
			   loc_ps8_ligne_code));
	}
	

	return loc_u8_resultat;
}/*u8ProcNetRoute_DecodeLine*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_ProcFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de procFile
//=====================================================================================
void InitModule_ProcFile(void)
{
	
}/*InitModule_ProcFile*/

