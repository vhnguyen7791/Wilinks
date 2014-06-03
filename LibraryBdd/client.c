/*========================================================================*/
/* NOM DU FICHIER  : client.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 07/06/2007                                           */
/* Libelle         : Password: gestion des clients pour SNMP, HTTP		  */
/* Projet          : WRM100                                               */
/* Indice          : BE014                                                */
/*========================================================================*/
/* Historique      :                                                      */
//[AUDIT X251231 Ind 0] MS 23/10/2008
//BE000 24/09/09 CM
// - CREATION
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère les passwords des clients HTTP, SNMP


/*_____II - DEFINE SBIT __________________________________________________*/

#define	_CLIENT	1

#define DEBUG_PASSWORD	0	//0: inactif 1: actif

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

static S_STRUCT_HTTP_GLOBAL s_http_global;
static u8sod	u8_modclient__max_client_ip;
static u16sod	u16_modclient__duree_inactivite_http;

/*_____V - PROCEDURES ____________________________________________________*/

// -------------------------------------------------------------
// Fonction    : TestClientIpConnecte
// Entrees     : <loc_ps8_addrIP> : adresse IP du client
// Sortie      : <loc_u8_connecte> : TRUE ou FALSE
// Description : 
//		Teste si le client est connecté
//		Si c'est le cas return TRUE
//		Sinon FALSE.
// -------------------------------------------------------------
u8sod TestClientIpConnecte(s8sod* loc_ps8_addrIP)
{	
	u8sod	loc_u8_i;
	u8sod  loc_u8_connecte = FALSE;	//INIT
	s32sod	loc_s32_sem;

	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore

	if(TRUE == u8FillHttpFile(&s_http_global))
	{
		for(loc_u8_i=0;loc_u8_i<NB_CLIENT_IP_MAX;loc_u8_i++)
		{
			if(TRUE == s_http_global.s_client[loc_u8_i].u8_flag_connecte)
			{
				// Client recensé, on vérifie les droits d'accès
				if( !strcmp(s_http_global.s_client[loc_u8_i].ps8_addrIP ,loc_ps8_addrIP) )
				{
					loc_u8_connecte = TRUE;
					loc_u8_i = NB_CLIENT_IP_MAX + 1;	//on sort
				}
			}
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem
	return loc_u8_connecte;
}/*TestClientIpConnecte*/

// -------------------------------------------------------------
// Fonction    : TestPassword
// Entrees     : <loc_ps8_addrIP> : adresse IP du client
//				 <loc_s32_AccessLevel> : niveau minimum d'acces
// Sortie      : <loc_u8_AccessAllowed> : TRUE ou FALSE
// Description : 
//		Teste si le client est recensé dans le fichier CLIENT.INI
//		Si c'est le cas return TRUE avec Renouvellement de son tps d'accès.
//		Sinon FALSE.
// -------------------------------------------------------------
u8sod TestPassword(char* loc_ps8_addrIP, s32sod loc_s32_AccessLevel)
{	
	S_STRUCT_CLIENT_CONNECTE loc_s_client; 
	u8sod	loc_u8_i;
	time_t loc_u32_ElapsedTime = 0; //INIT
	u8sod  loc_u8_AccessAllowed = FALSE;	//INIT
	s32sod	loc_s32_sem;
	u8sod	loc_u8_edit_a_faire;

	loc_u8_edit_a_faire = FALSE; //INIT

	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore

	if(TRUE == u8FillHttpFile(&s_http_global))
	{
		for(loc_u8_i=0;loc_u8_i<NB_CLIENT_IP_MAX;loc_u8_i++)
		{
			if(TRUE == s_http_global.s_client[loc_u8_i].u8_flag_connecte)
			{
				loc_s_client = s_http_global.s_client[loc_u8_i];
				// Client recensé, on vérifie les droits d'accès
				if( !strcmp(loc_s_client.ps8_addrIP ,loc_ps8_addrIP) && (loc_s_client.s32_AccessLevel >= loc_s32_AccessLevel) )
				{
					time(&loc_u32_ElapsedTime);

					// Temps de connexion non écoulé
					//[AUDIT X251231 Ind 0] MS 23/10/2008	[Verifier avant de faire la soustraction qu'elle a un sens]
					if( (loc_u32_ElapsedTime - loc_s_client.u32_time) < ((u32sod)u16_modclient__duree_inactivite_http * 60) )
					{
						// Renouvellement du temps de connexion
						s_http_global.s_client[loc_u8_i].u32_time = loc_u32_ElapsedTime;

						// Accès autorisé au domaine protégé
						loc_u8_AccessAllowed = TRUE;

					}
					else
					{
						//Temps de connexion écoulé
						//On supprime le client
						s_http_global.s_client[loc_u8_i].u8_flag_connecte = FALSE; //DECONNECTION
					}
					
					loc_u8_edit_a_faire = TRUE;
				}
			}
		}

		if(TRUE == loc_u8_edit_a_faire)
		{
			u8EditHttpFile(&s_http_global);
		}
	}
	else
	{
		MACRO_PRINTF(("TestPassword: Probleme lecture Fichier\n"));
	}
	
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem
	
	return loc_u8_AccessAllowed;
	
}/*TestPassword*/

// -------------------------------------------------------------
// Fonction    : AddClient
// Entrees     : <loc_ps8_addrIP> : adresse IP du client
//				 <loc_s32_AccessLevel> : niveau minimum d'acces
// Sortie      : <loc_u8_resultat> : TRUE ou FALSE
// Description : 
//		Ajoute un client dans la table d'accès cad le fichier CLIENT.INI
//		return TRUE si effectué
//		FALSE si non effectué car TOO MANY LOGGED CLIENTS
//		ou erreur.
// Historique  :
// -------------------------------------------------------------
u8sod AddClient(s8sod* loc_ps8_addrIP, s32sod loc_s32_AccessLevel)
{
	u8sod	loc_u8_resultat;
	S_STRUCT_CLIENT_CONNECTE loc_s_client; 
	u8sod	loc_u8_i;
	u8sod	loc_u8_nbr_clients=0; //INIT
	u8sod	loc_u8_INFILE = FALSE;
	time_t loc_u32_ElapsedTime = 0;
	s32sod	loc_s32_sem;
	u8sod	loc_u8_edit_a_faire;

	loc_u8_resultat = TRUE;	//INIT
	loc_u8_edit_a_faire = FALSE; //INIT

	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore

	//On recherche si déjà présent
	if(TRUE == u8FillHttpFile(&s_http_global))
	{
		for(loc_u8_i=0;loc_u8_i<NB_CLIENT_IP_MAX;loc_u8_i++)
		{
			if(TRUE == s_http_global.s_client[loc_u8_i].u8_flag_connecte)
			{
				time(&loc_u32_ElapsedTime);

				memset(&loc_s_client,'\0',sizeof(S_STRUCT_CLIENT_CONNECTE));

				loc_s_client = s_http_global.s_client[loc_u8_i];

				// Client recensé, les nouveaux droits d'accès écrasent les précédents
				if( !strcmp(loc_s_client.ps8_addrIP ,loc_ps8_addrIP) )
				{
					// Mise à jour heure de connexion
					loc_s_client.u32_time = loc_u32_ElapsedTime;
					// Ecrasent les anciens droits d'accès
					loc_s_client.s32_AccessLevel = loc_s32_AccessLevel;
					// Le client est déjà recensé
					loc_u8_INFILE = TRUE;
				}

				// Permet de purger les clients sur test TIME OUT
				//[AUDIT X251231 Ind 0] MS 23/10/2008	[Verifier avant de faire la soustraction qu'elle a un sens]
				if( (loc_u32_ElapsedTime - loc_s_client.u32_time) < ((u32sod)u16_modclient__duree_inactivite_http * 60) )		
				{
					loc_u8_nbr_clients++; //==> on garde tous les clients déjà connectés même si loc_u8_nbr_clients > ClientNumberMax
					s_http_global.s_client[loc_u8_i] = loc_s_client;
				}
				else // time_out
				{
					s_http_global.s_client[loc_u8_i].u8_flag_connecte = FALSE;	//DECONNECTION
					MACRO_PRINTF(("AddClient: time out\n"));
				}
				loc_u8_edit_a_faire = TRUE;
			}
		}

		// Le client n'était pas dans 'CLIENT.INI'
		if(!loc_u8_INFILE)
		{
			// Test si pas trop de clients
			if( loc_u8_nbr_clients < u8_modclient__max_client_ip )
			{
				// Temps de connexion
				time(&loc_u32_ElapsedTime);

				loc_u8_nbr_clients++;

				//On recherche place pour nouveau client
				for(loc_u8_i=0;loc_u8_i<NB_CLIENT_IP_MAX;loc_u8_i++)
				{
					if(FALSE == s_http_global.s_client[loc_u8_i].u8_flag_connecte)
					{
						s_http_global.s_client[loc_u8_i].u8_flag_connecte = TRUE;			//CONNECTION
						strcpy(s_http_global.s_client[loc_u8_i].ps8_addrIP,  loc_ps8_addrIP);
						s_http_global.s_client[loc_u8_i].s32_AccessLevel = loc_s32_AccessLevel;
						s_http_global.s_client[loc_u8_i].u32_time = loc_u32_ElapsedTime;

						loc_u8_edit_a_faire = TRUE;
						
						//on sort
						loc_u8_i = NB_CLIENT_IP_MAX+1;
					}
				}
			}
			else	// Too Many Clients
			{ 
//				MACRO_PRINTF(("AddClient:Too Many Clients (%d >= %d)\n",loc_u8_nbr_clients,u8_modclient__max_client_ip));
				loc_u8_resultat = FALSE;
			} 
		}

		if(TRUE == loc_u8_edit_a_faire)
		{
			u8EditHttpFile(&s_http_global);
		}
	}
		
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem
	return loc_u8_resultat;
	
}/*AddClient*/

//=====================================================================================
// Fonction		: u8GestionDeconnexionClient
// Entrees		: rien
// Sortie		: TRUE ou FALSE
// Description	: Gestion de déconnexion des clients
//=====================================================================================
u8sod u8GestionDeconnexionClient(void)
{	
	time_t	loc_u32_ElapsedTime = 0;  
	s32sod	loc_s32_sem;
	u8sod	loc_u8_i;
	u8sod	loc_u8_edit_a_faire;

	loc_u8_edit_a_faire = FALSE; //INIT
	
	s32Lock_Get(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on lève le sémaphore

	if(TRUE == u8FillHttpFile(&s_http_global))
	{
		//on parcourt la liste des clients connectés
		for(loc_u8_i=0;loc_u8_i<NB_CLIENT_IP_MAX;loc_u8_i++)
		{
			if(TRUE == s_http_global.s_client[loc_u8_i].u8_flag_connecte)
			{
				time(&loc_u32_ElapsedTime);

				// Temps de connexion écoulé
				if( (loc_u32_ElapsedTime - s_http_global.s_client[loc_u8_i].u32_time) >= ((u32sod)u16_modclient__duree_inactivite_http * 60) )
				{
					s_http_global.s_client[loc_u8_i].u8_flag_connecte = FALSE;	//DECONNECTION
//					RegisterEvent(INF_LOGOUT_HTTP, 0, 0, 0, ETAT_EVT_INFO);
					printf("u8GestionDeconnexionClient: Deconnexion client %s (%lu -> %lu) \n",
						  s_http_global.s_client[loc_u8_i].ps8_addrIP,loc_u32_ElapsedTime,s_http_global.s_client[loc_u8_i].u32_time);
					loc_u8_edit_a_faire = TRUE;
				}
			}
		}

		if(TRUE == loc_u8_edit_a_faire)
		{
			u8EditHttpFile(&s_http_global);
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_PASSWORD, &loc_s32_sem);	//on relache le sem

	return TRUE;
}/*u8GestionDeconnexionClient*/

//=====================================================================================
// Fonction		: SetConfig_ModuleClient
// Entrees		: <loc_u8_max_client>	: paramètre de config nb max client
//				: <loc_u16_duree_inactivite_http>	: paramètre de config durée max iniactivite http
// Sortie		: rien
// Auteur		: CM - 01/10/2009 -
// Description	: Configure le module de Client en fonction de la configuration
//=====================================================================================
void SetConfig_ModuleClient(u8sod loc_u8_max_client, u16sod loc_u16_duree_inactivite_http)
{
	u8_modclient__max_client_ip = loc_u8_max_client; //MAJ
	u16_modclient__duree_inactivite_http = loc_u16_duree_inactivite_http; //MAJ
}/*SetConfig_ModuleClient*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Client
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/09/2007 -
// Description	: Initialisation du module de Client
//=====================================================================================
void InitModule_Client(void)
{
	memset(&s_http_global,'\0',sizeof(S_STRUCT_HTTP_GLOBAL)); //INIT
	u8_modclient__max_client_ip = NB_CLIENT_IP_MAX; //INIT
	u16_modclient__duree_inactivite_http = DUREE_INACTIVITE_HTTP_MIN; //INIT
	
}/*InitModule_Client*/

