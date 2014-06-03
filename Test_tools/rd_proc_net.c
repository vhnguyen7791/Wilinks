/*========================================================================*/
/* NOM DU FICHIER  : rd_proc_net.c			                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/10/2009                                           */
/* Libelle         : Test lecture /proc/net/...							  */
/* Projet          : WRM100		                                          */
/* Indice          : BE040                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/09 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE025 15/04/2010 CM
// - Modification gestion routage par le processus bird
//BE026 26/04/2010 CM
// - Correction lecture /proc/net/route
//	il faut comptabiliser les routes statiques, dynamiques 
//BE040 13/09/2010 CM
// - Suppresion code inutile
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _RD_PROC_NET


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: TestLecture_ProcNetRoute
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/10/2009 -
// Description	: Teste de lecture de /proc/net/route
//=====================================================================================
void TestLecture_ProcNetRoute(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_LIGNE_PROCNETROUTE+1];
	u16sod	loc_u16_cpt;
	s32sod	loc_s32_sscanf_route;
	S_STRUCT_IP_ROUTE_STATIC	loc_s_route;
	s8sod	loc_ps8_nom_interface[16];

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL; //INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_u16_cpt = 0;	//INIT
	loc_s32_sscanf_route = 0; //INIT
	memset(&loc_s_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //INIT
	strcpy(loc_ps8_nom_interface,""); //INIT
		
	
	if(NULL == (loc_p_handle = fopen( FICHIER_PROC_NET_ROUTE, "rt" )))
	{
		printf("TestLecture_ProcNetRoute: KO lecture impossible!!!\n");
	}
	else
	{
		printf("TestLecture_ProcNetRoute: Lecture du fichier %s ...\n",FICHIER_PROC_NET_ROUTE);

		do{
			loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_LIGNE_PROCNETROUTE,loc_p_handle);
			if((0 != loc_u16_cpt)&&(NULL != loc_ps8_result_fgets)) //CONDITION: ligne lue et ce n'est pas la première
			{
				//La ligne est au format suivant:
				// "Iface\tDestination\tGateway\tFlags\tRefCnt\tUse\tMetric\tMask\t\tMTU\tWindow\tIRTT"
				memset(&loc_s_route, 0, sizeof(S_STRUCT_IP_ROUTE_STATIC)); //RAZ
				strcpy(loc_ps8_nom_interface,""); //RAZ

				//On lit a part les infos de route et d'interface, car interface mal décodée par sscanf
				loc_s32_sscanf_route = sscanf(loc_ps8_ligne, "%s\t%08lX\t%08lX\t%*04X\t%*d\t%*u\t%*d\t%08lX\t%*d\t%*u\t%*u",
											  loc_ps8_nom_interface,
											  &loc_s_route.u32_destination_ip,
											  &loc_s_route.u32_gateway_ip,
											  &loc_s_route.u32_destination_mask);
				
				if(4 == loc_s32_sscanf_route)//CONDITION: lecture de 4 valeurs
				{
					if(0==strcmp(loc_ps8_nom_interface, "*"))//CONDITION: PAS D'INTERFACE CONNU
					{
						loc_s_route.u8_interface = INTERFACE_AUTOMATIQUE;
					}
					else
					{
						if(0==strcmp(loc_ps8_nom_interface, NOM_INTERFACE_ETHERNET))//CONDITION: INTERFACE LAN
						{
							loc_s_route.u8_interface = INTERFACE_LAN;
						}
						else
						{
							if(0==strcmp(loc_ps8_nom_interface, NOM_INTERFACE_WIFI))//CONDITION: INTERFACE WLAN
							{
								loc_s_route.u8_interface = INTERFACE_WLAN;
							}
							else
							{
								loc_u8_resultat = FALSE; //Interface inconnu
								printf("TestLecture_ProcNetRoute: KO Interface inconnu:%s !!!\n",
									   loc_ps8_nom_interface);
							}
						}
					}
					if(TRUE == loc_u8_resultat)
					{
						printf("route %d: adresse=%08lX / Mask=%08lX / Gw=%08lX / Interface=%s \n",
							   (loc_u16_cpt+1),
							   loc_s_route.u32_destination_ip,
							   loc_s_route.u32_destination_mask,
							   loc_s_route.u32_gateway_ip,
							   ((INTERFACE_WLAN==loc_s_route.u8_interface)?"WLAN":((INTERFACE_LAN==loc_s_route.u8_interface)?"LAN":"Automatique")));
					}
				}
				else
				{
					loc_u8_resultat = FALSE; //Interface inconnu
					printf("TestLecture_ProcNetRoute: KO decodage ligne (%ld) :%s !!!\n",
						   loc_s32_sscanf_route,
						   loc_ps8_ligne);
				}
			}
			
			loc_u16_cpt ++;
			

		}while((NULL != loc_ps8_result_fgets) &&
			   (loc_u16_cpt < NB_MAX_ROUTES_IP_TOTAL) &&
			   (TRUE == loc_u8_resultat)
			 );
		
		//fermeture du fichier
		fclose (loc_p_handle);
	}
	
}/*TestLecture_ProcNetRoute*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_RdProcNet
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation du module de rd_proc_net
//=====================================================================================
void InitModule_RdProcNet(void)
{
}/*InitModule_RdProcNet*/

