/*========================================================================*/
/* NOM DU FICHIER  : config.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 25/09/2009                                           */
/* Libelle         : Base de données: configuration de l'équipement		  */
/* Projet          : WRM100                                               */
/* Indice          : BE064                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 25/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration hostname
// - Intégration configuration par DHCP client
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du système
//BE009 01/02/2010 CM
// - Ajout client NTP
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
// - Correction test configuration des adresses IP des interfaces
//  --> vérification que l'adresse IP n'est pas une adresse nulle pour le masque de sous-réseau défini
//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
//BE012 24/02/2010 CM
// - Integration SNMPv1/SNMPv2c
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE019 16/03/2010 CM
// - Autorisation de passer la station en bridge
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
// - Ajout fonction générique test masque sous-réseau
// - Ajout fonction générique test ip de type NET
//BE024 03/04/2010 CM
// - Correction test config Multicast
// - Correction suite revue de codage de Caf (sur BE023)
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE031 07/06/2010 JP
// - ajout du test de la configuration complete avant application
//BE032 16/06/2010 CM
// - Ajout gestion Radius / WPA - EAP
//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		userhigh / usermiddle / userlow
//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
//BE038 09/07/2010 CM
// - Ajout configuration STP pour bridge
//BE039 26/08/2010 CM
// - Correction bug test configuration (pb canal fonction si AP ou STA)
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//BE042 07/10/2010 CM
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
// - Correction configuration mode 802.11 (associé au driver-N)
// - Ajout gestion liste des fréquences réglementaires
// - Ajout paramètre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE048 29/11/2010 CM
// - Correction routage statique vers un HOST
// - Correction bug sur configuration du serveur DHCP 
//BE049 08/12/2010 CM
// - Ajout gestion du SSID secondaire
// - Modification mode scanning (handoff)
// - Correction test valeur SSID (champs vide non autorisé)
//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//BE052 15/12/2010 CM
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//BE053 16/12/2010 CM
// - Modification plage de timeout ACK (Driver-N)
//BE054 17/12/2010 CM
// - Correction driver-ABG
// - Suppression du fichier de configuration advwf
// - Modification débit emission MCS0 à MCS15 autorisé quelque soit nb antennes
//BE055 17/01/2011 CM
// - Modification configuration des antennes
// - Ajout configuration Country ID pour le client
//BE056 18/01/2011 CM
// - Correction puissance maximum en fonction config mode 802.11/debit/antenne
//	pour éviter sur-consommation de l'équipement
//BE057 20/01/2011 CM
// - Modification test vlan config pour éviter de passer en config/defaut sur config generale du WRM100-ABG
// - Désactivation du mode monitor en WRM100-ABG
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
// - Ajout filtrage rssi pour fast roaming
//BE060 16/03/2011
// - DEP: Ajout du mode d'Authentification EAP-TLS
// - Ajout configuration date/heure au démarrage de l'équipement
// - Ajout fonction impose config au démarrage (pour chaque bdd de config)
//BE061 10/05/2011
// - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//		si par exemple on vient du logiciel WRM100-MESH
// - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
// - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//BE064.0 25/11/2011 (CM)
// - Correction bug de la configuration par sFTP (lors changement countryId)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#define _CONFIG

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//***************************************************************************
//**************** PROCEDURES GENERIQUES
//***************************************************************************

//d: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//=====================================================================================
// Fonction		: OrderSetNewEquipment
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 23/05/2011 -
// Description	: Ordre signalisation nouveau equipement
//=====================================================================================
void OrderSetNewEquipment(void)
{
	FILE	*loc_p_handle;

	loc_p_handle = NULL;	//INIT

	if(NULL != (loc_p_handle = fopen(FICHIER_NEW_EQUIPMENT, "wt" ))) //CONDITION: fichier présent
	{
		fclose (loc_p_handle);
	}
	else
	{
		printf("OrderSetNewEquipment: Creation impossible %s \n",
			   FICHIER_NEW_EQUIPMENT);
	}

}/*OrderSetNewEquipment*/

//=====================================================================================
// Fonction		: u8TestNewEquipment
// Entrees		: rien
// Sortie		: <loc_u8_resultat>: TRUE présent, sinon FALSE
// Auteur		: CM - 23/05/2011 -
// Description	: Test si nouvel equipement détecté
//=====================================================================================
u8sod u8TestNewEquipment(void)
{
	u8sod loc_u8_resultat;
	FILE	*loc_p_handle;

	loc_u8_resultat = FALSE;	//INIT

	loc_p_handle = NULL;	//INIT

	if(NULL != (loc_p_handle = fopen(FICHIER_NEW_EQUIPMENT, "rt" ))) //CONDITION: fichier présent
	{
		loc_u8_resultat = TRUE;
		fclose (loc_p_handle);
	}

	return loc_u8_resultat;
}/*u8TestNewEquipment*/
//f: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

//d: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
//=====================================================================================
// Fonction		: OrderSetConfigDefaut
// Entrees		: <loc_u8_idx_cfgfile> : index de la configuration à forcer par défaut
// Sortie		: rien
// Auteur		: CM - 11/05/2011 -
// Description	: Ordre de forcer configuration par défaut
//=====================================================================================
void OrderSetConfigDefaut(u8sod loc_u8_idx_cfgfile)
{
	FILE	*loc_p_handle;
	static s8sod loc_ps8_nomFile[100+1];

	loc_p_handle = NULL;	//INIT

	if(loc_u8_idx_cfgfile < NB_MAX_IDXCONFIG) //CONDITION: index fichier de config
	{
		sprintf(loc_ps8_nomFile, "%s%d",
				FICHIER_SETCONFIGDEFAULT,
				loc_u8_idx_cfgfile);

		if(NULL != (loc_p_handle = fopen(loc_ps8_nomFile, "wt" ))) //CONDITION: fichier présent
		{
			fclose (loc_p_handle);
		}
		else
		{
			printf("OrderSetConfigDefaut: Creation impossible %s%d \n",
				   FICHIER_SETCONFIGDEFAULT,
				   loc_u8_idx_cfgfile);
		}
	}

}/*OrderSetConfigDefaut*/

//=====================================================================================
// Fonction		: ClearSetConfigDefaut
// Entrees		: <loc_u8_idx_cfgfile> : index de la configuration à forcer par défaut
// Sortie		: rien
// Auteur		: CM - 11/05/2011 -
// Description	: Suppression du fichier qui donne l'ordre de passer en configuration par défaut
//=====================================================================================
void ClearSetConfigDefaut(u8sod loc_u8_idx_cfgfile)
{
	static s8sod loc_ps8_nomFile[100+1];

	if(loc_u8_idx_cfgfile < NB_MAX_IDXCONFIG) //CONDITION: index fichier de config
	{
		sprintf(loc_ps8_nomFile, "%s%d",
				FICHIER_SETCONFIGDEFAULT,
				loc_u8_idx_cfgfile);
		u8CmdSystem_RemoveFile(loc_ps8_nomFile);
	}

}/*ClearSetConfigDefaut*/

//=====================================================================================
// Fonction		: u8TestSetConfigDefaut
// Entrees		: <loc_u8_idx_cfgfile> : index de la configuration à forcer par défaut
// Sortie		: <loc_u8_resultat>: TRUE présent, sinon FALSE
// Auteur		: CM - 11/05/2011 -
// Description	: Test si si ordre de forcer la config par défaut
//=====================================================================================
u8sod u8TestSetConfigDefaut(u8sod loc_u8_idx_cfgfile)
{
	u8sod loc_u8_resultat;
	FILE	*loc_p_handle;
	static s8sod loc_ps8_nomFile[100+1];

	loc_u8_resultat = FALSE;	//INIT

	loc_p_handle = NULL;	//INIT

	if(loc_u8_idx_cfgfile < NB_MAX_IDXCONFIG) //CONDITION: index fichier de config
	{
		sprintf(loc_ps8_nomFile, "%s%d",
				FICHIER_SETCONFIGDEFAULT,
				loc_u8_idx_cfgfile);

		if(NULL != (loc_p_handle = fopen(loc_ps8_nomFile, "rt" ))) //CONDITION: fichier présent
		{
			loc_u8_resultat = TRUE;
			fclose (loc_p_handle);
		}
	}

	return loc_u8_resultat;
}/*u8TestSetConfigDefaut*/
//f: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

//=====================================================================================
// Fonction		: SignalNewConfig
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
// Sortie		: rien
// Auteur		: CM - 28/09/2009 -
// Description	: Signale une évolution susceptible de la configuration défini par son index
//=====================================================================================
void SignalNewConfig(u8sod loc_u8_idx_cfgfile)
{
	T_STRUCT_OF_FILE_NEWCFG_INI loc_t_newcfgini;

	memset(&loc_t_newcfgini,'\0',sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //INIT
	
	if(loc_u8_idx_cfgfile < NB_MAX_IDXCONFIG)
	{
		u8Transfert_FileToStruct(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
		loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile] = TRUE;
		u8Transfert_StructToFile(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
	}
}/*SignalNewConfig*/

//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
//=====================================================================================
// Fonction		: SignalNewCfgFTP
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/11/2011 -
// Description	: Signale une configuration par FTP
//=====================================================================================
void SignalNewCfgFTP(void)
{
	T_STRUCT_OF_FILE_NEWCFG_INI loc_t_newcfgini;

	memset(&loc_t_newcfgini,'\0',sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //INIT

	u8Transfert_FileToStruct(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
	loc_t_newcfgini.u8_change_cfg_FTP = TRUE;
	u8Transfert_StructToFile(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
}/*SignalNewCfgFTP*/
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)

//=====================================================================================
// Fonction		: u8FillConfigFile
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigFile(u8sod loc_u8_idx_cfgfile, S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;
	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillConfigFile(%s) => %d \n",
					   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom,
					   loc_u8_resultat));
	}

	return loc_u8_resultat;
}/*u8FillConfigFile*/

//=====================================================================================
// Fonction		: u8EditConfigFile
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigFile(u8sod loc_u8_idx_cfgfile, S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_StructToFile(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]);

	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8EditConfigFile(%s) => %d \n",
					   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom,
					   loc_u8_resultat));
	}

	SignalNewConfig(loc_u8_idx_cfgfile);
			
	return loc_u8_resultat;
}/*u8EditConfigFile*/

//=====================================================================================
// Fonction		: u8TestConfigFile
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Test des données de la structure S_STRUCT_CONFIGURATION pour le fichier défini par son index
//=====================================================================================
u8sod u8TestConfigFile(u8sod loc_u8_idx_cfgfile, S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8TestConfig(loc_ps_config);
	MACRO_PRINTF(("u8TestConfigFile(%s) => %d \n",
				  PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom,
				  loc_u8_resultat));

	return loc_u8_resultat;
}/*u8TestConfigFile*/

//=====================================================================================
// Fonction		: u8TestConfigChaineSansEspace
// Entrees		: <loc_ps8_chaine< : pointeur sur la chaine de caractères à tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 06/01/2010 -
// Description	: Test si la chaine contient ou non des espaces (ou tabulation)
//=====================================================================================
u8sod u8TestConfigChaineSansEspace(s8sod *loc_ps8_chaine)
{
	u8sod	loc_u8_resultat;
	s8sod	*loc_ps8_dest;

	loc_u8_resultat = TRUE;	//INIT
	loc_ps8_dest = NULL;	//INIT
	
	if(NULL != loc_ps8_chaine)
	{
		//Recherche si dans la chaine, il y a des espaces et des tabulations
		loc_ps8_dest = strchr(loc_ps8_chaine, (int)' ');
		if(NULL != loc_ps8_dest)//CONDITION: ' ' est trouvé, donc erreur
		{
			loc_u8_resultat = FALSE;
		}
		
		loc_ps8_dest = strchr(loc_ps8_chaine, (int)'\t');
		if(NULL != loc_ps8_dest)//CONDITION: ' ' est trouvé, donc erreur
		{
			loc_u8_resultat = FALSE;
		}
	}

	return loc_u8_resultat;	
}/*u8TestConfigChaineSansEspace*/

//=====================================================================================
// Fonction		: u8TestConfigChaineValide
// Entrees		: <loc_ps8_chaine< : pointeur sur la chaine de caractères à tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 03/10/2008 -
// Description	: Test la validité des caractères dans la chaine
//=====================================================================================
u8sod u8TestConfigChaineValide(s8sod *loc_ps8_chaine)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u32sod	loc_u32_longueur;
	u8sod	loc_u8_caract;

	loc_u8_resultat = TRUE;	//INIT

	loc_u32_longueur = (u32sod)strlen(loc_ps8_chaine);
	for(loc_u16_i=0;((loc_u16_i<(u16sod)loc_u32_longueur)&&(loc_u16_i<U16_LG_MAX_CHAINE_VALIDE));loc_u16_i++)
	{
		loc_u8_caract = (u8sod)loc_ps8_chaine[loc_u16_i];
		if(
			    (U8_CARACT_ASCII_AUTORISE_MIN<=loc_u8_caract)
		   &&	(U8_CARACT_ASCII_INTERDIT_GUILLEMENT != loc_u8_caract)  
		   &&	(U8_CARACT_ASCII_INTERDIT_POURCENTAGE != loc_u8_caract)  
		   &&	(U8_CARACT_ASCII_INTERDIT_ETNUMERIC != loc_u8_caract)  
		   &&	(U8_CARACT_ASCII_INTERDIT_APOSTROPHE != loc_u8_caract)  
		   &&	(U8_CARACT_ASCII_INTERDIT_BACKSLASH != loc_u8_caract)
		   &&	(U8_CARACT_ASCII_INTERDIT_PIPE != loc_u8_caract)
		   &&	(!((U8_CARACT_ASCII_INTERDIT_MIN<=loc_u8_caract)&&(loc_u8_caract<=U8_CARACT_ASCII_INTERDIT_MAX)))
		  )	//CONDITION: caractère autorisé
		{
			;	//OK
		}
		else	//CONDITION: caractère interdit
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigChaineValide(0x%X): %s \n",
						 loc_u8_caract,
						 loc_ps8_chaine));
			loc_u16_i = U16_LG_MAX_CHAINE_VALIDE + 1;	//on sort
		}
	}


	return loc_u8_resultat;
}/*u8TestConfigChaineValide*/


//=====================================================================================
// Fonction		: SignalConfig_InProgress
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Signale une configuration en cours
//=====================================================================================
void SignalConfig_InProgress(void)
{
	FILE	*loc_p_handle;
	loc_p_handle = NULL;	//INIT
	if(NULL != (loc_p_handle = fopen(FICHIER_CONFIG_INPROGRESS, "wt" ))) //CONDITION: fichier présent
	{
		fclose (loc_p_handle);
	}
	else
	{
		printf("SignalConfig_InProgress: Creation impossible %s \n",FICHIER_CONFIG_INPROGRESS);
	}
}/*SignalConfig_InProgress*/

//=====================================================================================
// Fonction		: ClearConfig_InProgress
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/12/2010 -
// Description	: Annule la configuration en cours
//=====================================================================================
void ClearConfig_InProgress(void)
{
	u8CmdSystem_RemoveFile(FICHIER_CONFIG_INPROGRESS);
}/*ClearConfig_InProgress*/

//=====================================================================================
// Fonction		: u8TestConfig_InProgress
// Entrees		: rien
// Sortie		: <loc_u8_resultat>  : configuration en cours alors TRUE sinon FALSE
// Auteur		: CM - 02/12/2010 -
// Description	: Test la validité des caractères dans la chaine
//=====================================================================================
u8sod u8TestConfig_InProgress(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;

	loc_u8_resultat = FALSE;	//INIT
	loc_p_handle = NULL;	//INIT

	if(NULL != (loc_p_handle = fopen(FICHIER_CONFIG_INPROGRESS, "rt" ))) //CONDITION: fichier présent
	{
		loc_u8_resultat = TRUE;
		fclose (loc_p_handle);
	}

	return loc_u8_resultat;
}/*u8TestConfig_InProgress*/


//=====================================================================================
// Fonction		: u8DiffConfig
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: GT - 25/09/2007 -
// Description	: Vérifie si les config en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfig(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE; //INIT

	loc_pu8_conf1 = (u8sod *)(loc_ps_config1);
	loc_pu8_conf2 = (u8sod *)(loc_ps_config2);

	// On compare les différents champs
//	MACRO_PRINTF(("u8DiffConfig: =>u8_start= %lu \n", MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u8_start)));
	for(loc_u16_i=(u16sod)MACRO_OFFSETOF(S_STRUCT_CONFIGURATION, u8_start); (loc_u16_i < (u16sod)sizeof(S_STRUCT_CONFIGURATION)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CONFIGURATION)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfig*/


//***************************************************************************
//**************** PROCEDURES CONFIGURATION ADMIN
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigAdmin
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Admin du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_ADMIN, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigAdmin*/

//=====================================================================================
// Fonction		: u8EditConfigAdmin
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Admin dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_ADMIN, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigAdmin*/

//=====================================================================================
// Fonction		: u8TestConfigAdmin
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des données Administration de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(	(strlen(loc_ps_config->s_admin.ps8_identifiant) > LG_NOM_IDENTIFIANT) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_admin.ps8_identifiant))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: ps8_identifiant KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_admin.ps8_localisation) > LG_NOM_LOCALISATION) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_admin.ps8_localisation))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: ps8_localisation KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_admin.ps8_mot_de_passe_low) > LG_NOM_PWD) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_admin.ps8_mot_de_passe_low))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: ps8_mot_de_passe_low KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_admin.ps8_mot_de_passe_middle) > LG_NOM_PWD) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_admin.ps8_mot_de_passe_middle))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: ps8_mot_de_passe_middle KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_admin.ps8_mot_de_passe_high) > LG_NOM_PWD) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_admin.ps8_mot_de_passe_high))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: ps8_mot_de_passe_high KO  \n"));
	}
	if(	(DUREE_INACTIVITE_HTTP_MIN <= loc_ps_config->s_admin.u16_duree_inactivite_http)	&&
		(loc_ps_config->s_admin.u16_duree_inactivite_http <= DUREE_INACTIVITE_HTTP_MAX)
	  )
	{
		; //OK
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u16_duree_inactivite_http KO : %d  \n",
					  loc_ps_config->s_admin.u16_duree_inactivite_http));
	}

	if(		(NB_CLIENT_IP_MIN <= loc_ps_config->s_admin.u8_max_client_ip)
		&&	(loc_ps_config->s_admin.u8_max_client_ip <= NB_CLIENT_IP_MAX)
	  )
	{
		; //OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigAdmin: u8_max_client_ip KO : %d  \n",
					  loc_ps_config->s_admin.u8_max_client_ip));
		loc_u8_resultat = FALSE;
	}

	if(		(MODE_SECURISATION_SNMP_INACTIF != loc_ps_config->s_admin.u8_securisation_snmp)
		&&	(MODE_SECURISATION_SNMP_SET != loc_ps_config->s_admin.u8_securisation_snmp)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u8_securisation_snmp KO : %d  \n",
					  loc_ps_config->s_admin.u8_securisation_snmp));
	}

	if(loc_ps_config->s_admin.u8_langue < NB_MAX_LANGUES)
	{
		;	//OK
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u8_langue KO : %d  \n",
					 loc_ps_config->s_admin.u8_langue));
	}

	if(		(TPS_REFRESH_HTML_MIN <= loc_ps_config->s_admin.u16_tps_refresh_html)
		&&	(loc_ps_config->s_admin.u16_tps_refresh_html <= TPS_REFRESH_HTML_MAX)
	  )
	{
		; //OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigAdmin: u16_tps_refresh_html KO : %d  \n",
					 loc_ps_config->s_admin.u16_tps_refresh_html));
		loc_u8_resultat = FALSE;
	}

	if(FALSE == u8TestDate_Valide(&loc_ps_config->s_admin.s_date_demarrage))
	{
		MACRO_PRINTF(("u8TestConfigAdmin: s_date_demarrage KO : %s  \n",
					  ps8GetChDate(&loc_ps_config->s_admin.s_date_demarrage)));
		loc_u8_resultat = FALSE;
	}
	
	if(		(MODE_DATE_HEURE_24H != loc_ps_config->s_admin.u8_mode_date_heure)
		&&	(MODE_DATE_HEURE_12H != loc_ps_config->s_admin.u8_mode_date_heure)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u8_mode_date_heure KO : %d  \n",
					  loc_ps_config->s_admin.u8_mode_date_heure));
	}

	if(loc_ps_config->s_admin.u8_mode_mah < NB_MAX_MODES_MAH)
	{
		;	//OK
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u8_mode_mah KO : %d  \n",
					  loc_ps_config->s_admin.u8_mode_mah));
	}

	switch(loc_ps_config->s_admin.u8_mode_mah)
	{
		case MODE_MAH_NTP:
		case MODE_MAH_SNTP:
			if((ADRESSE_IP_NULLE == loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])||
			   (MASK_RESEAU_SUR_32 == loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])
			  )
			{
				MACRO_PRINTF(("u8TestConfigAdmin: s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL] KO : %08X  \n",
							  loc_ps_config->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL]));
				loc_u8_resultat = FALSE;
			}
		break;
		case MODE_MAH_MANUELLE:
		default:
			break;
	}
	
	if((VALEUR_MIN_FUSEAU_HORAIRE <= loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire)&&
	   (loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire <= VALEUR_MAX_FUSEAU_HORAIRE)
	  )
	{
		; //OK
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: s_client_ntp.s8_fuseau_horaire KO : %d  \n",
					  loc_ps_config->s_admin.s_client_ntp.s8_fuseau_horaire));
	}

	if((VALEUR_MIN_FREQ_MAJ_HEURE_SNTP <= loc_ps_config->s_admin.s_client_ntp.u16_freq_maj_sntp)&&
	   (loc_ps_config->s_admin.s_client_ntp.u16_freq_maj_sntp <= VALEUR_MAX_FREQ_MAJ_HEURE_SNTP)
	  )
	{
		; //OK
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: s_client_ntp.u16_freq_maj_sntp KO : %d  \n",
					  loc_ps_config->s_admin.s_client_ntp.u16_freq_maj_sntp));
	}
	
	if((FALSE != loc_ps_config->s_admin.u8_syslog_activation)&&
	   (TRUE != loc_ps_config->s_admin.u8_syslog_activation)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u8_syslog_activation KO : %d  \n",
					  loc_ps_config->s_admin.u8_syslog_activation));
	}

	if((FALSE != loc_ps_config->s_admin.u8_mode_RSSI)&&
	   (TRUE != loc_ps_config->s_admin.u8_mode_RSSI)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigAdmin: u8_mode_RSSI KO : %d  \n",
					  loc_ps_config->s_admin.u8_mode_RSSI));
	}

	if((PORT_UDP_TCP_MIN <= loc_ps_config->s_admin.u16_syslog_port)&&
	   (loc_ps_config->s_admin.u16_syslog_port <= PORT_UDP_TCP_MAX)
	  )
	{
		; //OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigAdmin: u16_syslog_port KO : %d  \n",
					  loc_ps_config->s_admin.u16_syslog_port));
		loc_u8_resultat = FALSE;
	}
	
	return loc_u8_resultat;
}/*u8TestConfigAdmin*/

//=====================================================================================
// Fonction		: CopyConfigAdmin
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Admin SRC==>DST
//=====================================================================================
void CopyConfigAdmin(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_admin = loc_ps_cfg_src->s_admin;

}/*CopyConfigAdmin*/

//=====================================================================================
// Fonction		: u8DiffConfigAdmin
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 11/10/2010 -
// Description	: Vérifie si les config Admin en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigAdmin(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_admin.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_admin.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_ADMIN)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_ADMIN)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigAdmin*/

//=====================================================================================
// Fonction		: u8DiffConfigSyslog
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 28/01/2010 -
// Description	: Vérifie si les config system log en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigSyslog(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT

	if((loc_ps_config1->s_admin.u8_syslog_activation != loc_ps_config2->s_admin.u8_syslog_activation)||
	   (loc_ps_config1->s_admin.u32_syslog_adresse_IP != loc_ps_config2->s_admin.u32_syslog_adresse_IP)||
	   (loc_ps_config1->s_admin.u16_syslog_port != loc_ps_config2->s_admin.u16_syslog_port)
	  )//CONDITION: paramètres de configuration syslog à évoluer
	{
		loc_u8_return = TRUE;
	}

	return loc_u8_return;
}/*u8DiffConfigSyslog*/

//=====================================================================================
// Fonction		: u8DiffConfigModeRSSI
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 16/02/2011 -
// Description	: Vérifie si les config mode RSSI en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigModeRSSI(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT

	if(loc_ps_config1->s_admin.u8_mode_RSSI != loc_ps_config2->s_admin.u8_mode_RSSI)
	{
		loc_u8_return = TRUE;
	}
	else
	{
		if(TRUE == loc_ps_config1->s_admin.u8_mode_RSSI) //CONDITION: mode RSSI activé
		{
			if((loc_ps_config1->s_admin.u32_syslog_adresse_IP != loc_ps_config2->s_admin.u32_syslog_adresse_IP)||
			   (loc_ps_config1->s_admin.u16_syslog_port != loc_ps_config2->s_admin.u16_syslog_port)
			  )//CONDITION: paramètres de configuration syslog à évoluer
			{
				loc_u8_return = TRUE;
			}
		}
	}

	return loc_u8_return;
}/*u8DiffConfigModeRSSI*/

//=====================================================================================
// Fonction		: u8DiffConfigNtp
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 01/02/2010 -
// Description	: Vérifie si les config client NTP en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigNtp(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT

	if((loc_ps_config1->s_admin.u8_mode_mah != loc_ps_config2->s_admin.u8_mode_mah)||
	   (loc_ps_config1->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL] != loc_ps_config2->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_PRINCIPAL])||
	   (loc_ps_config1->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS] != loc_ps_config2->s_admin.s_client_ntp.pu32_adresse_serveur[SERVEUR_NTP_SECOURS])||
	   (loc_ps_config1->s_admin.s_client_ntp.s8_fuseau_horaire != loc_ps_config2->s_admin.s_client_ntp.s8_fuseau_horaire)||
	   (loc_ps_config1->s_admin.s_client_ntp.u16_freq_maj_sntp != loc_ps_config2->s_admin.s_client_ntp.u16_freq_maj_sntp)
	  )//CONDITION: paramètres de configuration syslog à évoluer
	{
		loc_u8_return = TRUE;
	}

	return loc_u8_return;
}/*u8DiffConfigNtp*/

//=====================================================================================
// Fonction		: u8DiffConfigPassword
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 02/07/2010 -
// Description	: Vérifie si les config password en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigPassword(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT

	if((0 != strcmp(loc_ps_config1->s_admin.ps8_mot_de_passe_low, loc_ps_config2->s_admin.ps8_mot_de_passe_low))||
	   (0 != strcmp(loc_ps_config1->s_admin.ps8_mot_de_passe_middle, loc_ps_config2->s_admin.ps8_mot_de_passe_middle))||
	   (0 != strcmp(loc_ps_config1->s_admin.ps8_mot_de_passe_high, loc_ps_config2->s_admin.ps8_mot_de_passe_high))
	  )//CONDITION: paramètres de configuration password à évoluer
	{
		loc_u8_return = TRUE;
	}

	return loc_u8_return;
}/*u8DiffConfigPassword*/


//***************************************************************************
//**************** PROCEDURES CONFIGURATION CONSTRUCTEUR
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigConstructeur
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Constructeur du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_CONSTRUCTEUR, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigConstructeur*/

//=====================================================================================
// Fonction		: u8EditConfigConstructeur
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Constructeur dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_CONSTRUCTEUR, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigConstructeur*/

//=====================================================================================
// Fonction		: u8TestConfigConstructeur
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des données Constructeur de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(	(strlen(loc_ps_config->s_constructeur.ps8_nom) > LG_NOM_CONSTRUCTEUR) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_constructeur.ps8_nom))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigConstructeur: ps8_nom KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_constructeur.ps8_numero_telephone) > LG_NUMERO_TELEPHONE_FAX) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_constructeur.ps8_numero_telephone))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigConstructeur: ps8_numero_telephone KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_constructeur.ps8_numero_fax) > LG_NUMERO_TELEPHONE_FAX) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_constructeur.ps8_numero_fax))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigConstructeur: ps8_numero_fax KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_constructeur.ps8_adresse_ligne1) > LG_ADRESSE) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_constructeur.ps8_adresse_ligne1))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigConstructeur: ps8_adresse_ligne1 KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_constructeur.ps8_adresse_ligne2) > LG_ADRESSE) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_constructeur.ps8_adresse_ligne2))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigConstructeur: ps8_adresse_ligne2 KO  \n"));
	}
	if(	(strlen(loc_ps_config->s_constructeur.ps8_site_web) > LG_SITE_WEB) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_constructeur.ps8_site_web))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigConstructeur: ps8_site_web KO  \n"));
	}

	return loc_u8_resultat;
}/*u8TestConfigConstructeur*/

//=====================================================================================
// Fonction		: CopyConfigConstructeur
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration constructeur SRC==>DST
//=====================================================================================
void CopyConfigConstructeur(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_constructeur = loc_ps_cfg_src->s_constructeur;

}/*CopyConfigConstructeur*/

//=====================================================================================
// Fonction		: u8DiffConfigConstructeur
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 11/10/2010 -
// Description	: Vérifie si les config Constructeur en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigConstructeur(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_constructeur.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_constructeur.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CONSTRUCTEUR)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CONSTRUCTEUR)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigConstructeur*/

//***************************************************************************
//**************** PROCEDURES CONFIGURATION SNMP
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigSnmp
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration SNMP du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_SNMP, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigSnmp*/

//=====================================================================================
// Fonction		: u8EditConfigSnmp
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Snmp dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_SNMP, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigSnmp*/

//=====================================================================================
// Fonction		: u8TestConfigSnmp
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des données Snmp de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = TRUE;	//INIT

	if(loc_ps_config->s_snmp.u8_version_snmp <= NB_MAX_VERSIONS_SNMP)
	{
		; //OK
	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigSnmp: u8_version_snmp KO : %d  \n",
					  loc_ps_config->s_snmp.u8_version_snmp));
	}
	
	if(	(strlen(loc_ps_config->s_snmp.ps8_nom_communaute_get) > LG_MAX_NOM_COMMUNAUTE_SNMP) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_snmp.ps8_nom_communaute_get))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigSnmp: ps8_nom_communaute_get KO  \n"));
	}
	
	if(	(strlen(loc_ps_config->s_snmp.ps8_nom_communaute_set) > LG_MAX_NOM_COMMUNAUTE_SNMP) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_snmp.ps8_nom_communaute_set))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigSnmp: ps8_nom_communaute_get KO  \n"));
	}

	if((strlen(loc_ps_config->s_snmp.ps8_nom_communaute_trap) > LG_MAX_NOM_COMMUNAUTE_SNMP) ||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_snmp.ps8_nom_communaute_trap))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigSnmp: ps8_nom_communaute_trap KO  \n"));
	}
	
	if(		(EMISSION_TRAP_INACTIVE != loc_ps_config->s_snmp.u8_emission_trap)
		&&	(EMISSION_TRAP_ACTIVE != loc_ps_config->s_snmp.u8_emission_trap)
	  )
	{
		MACRO_PRINTF(("u8TestConfigSnmp: u8_emission_trap KO :%d \n",
					  loc_ps_config->s_snmp.u8_emission_trap));
		loc_u8_resultat = FALSE;
	}


	for(loc_u16_i=0;loc_u16_i<NB_MANAGER_SNMP_MAX;loc_u16_i++)
	{
		if(	(strlen(loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].ps8_nom) > LG_NOM_MANAGER_SNMP) ||
			  (FALSE == u8TestConfigChaineValide(loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].ps8_nom))
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigSnmp: s_manager_snmp[%d].ps8_nom KO \n",
						  loc_u16_i));
		}
		
		if(		(MANAGER_SNMP_ABSENT != loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_presence)
			&&	(MANAGER_SNMP_PRESENT != loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_presence)
		  )
		{
			MACRO_PRINTF(("u8TestConfigSnmp: s_manager_snmp[%d].u8_presence KO :%d \n",
						  loc_u16_i,
						  loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_presence));
			loc_u8_resultat = FALSE;
			loc_u16_i = NB_MANAGER_SNMP_MAX+1;	//on sort
		}
		
		if((TYPE_NOTIFICATION_TRAP != loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_type_notification) &&
		   (TYPE_NOTIFICATION_INFORM != loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_type_notification)
		  )
		{
			MACRO_PRINTF(("u8TestConfigSnmp: s_manager_snmp[%d].u8_type_notification KO :%d \n",
						  loc_u16_i,
						  loc_ps_config->s_snmp.s_manager_snmp[loc_u16_i].u8_type_notification));
			loc_u8_resultat = FALSE;
			loc_u16_i = NB_MANAGER_SNMP_MAX+1;	//on sort
		}
		
	}

	for(loc_u16_i=0;loc_u16_i<NIV_GRAVITE_MAX;loc_u16_i++)
	{
		if(		(INTERVAL_TRAPV1_MIN <= loc_ps_config->s_snmp.s_trap_SNMPv1[loc_u16_i].u16_interval)
#if 0 //pour éviter w@rning
			&&	(loc_ps_config->s_snmp.s_trap_SNMPv1[loc_u16_i].u16_interval <= INTERVAL_TRAPV1_MAX)
#endif
		  )
		{
			;	//OK
		}
		else
		{
			MACRO_PRINTF(("u8TestConfigSnmp: s_trap_SNMPv1[%d].u16_interval KO :%d \n",
						  loc_u16_i,
						  loc_ps_config->s_snmp.s_trap_SNMPv1[loc_u16_i].u16_interval));
			loc_u8_resultat = FALSE;
			loc_u16_i = NIV_GRAVITE_MAX+1;	//on sort
		}
	}

	if((REEMISSION_INFORM_MIN <= loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_nb_emission) &&
	   (loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_nb_emission <= REEMISSION_INFORM_MAX)
	  )
	{
		;	//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigSnmp: s_inform_SNMPv2c.u16_nb_emission KO :%d \n",
					  loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_nb_emission));
		loc_u8_resultat = FALSE;
	}
	
	if((INTERVAL_INFORM_MIN <= loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_interval) &&
	   (loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_interval <= INTERVAL_INFORM_MAX)
	  )
	{
		;	//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigSnmp: s_inform_SNMPv2c.u16_interval KO :%d \n",
					  loc_ps_config->s_snmp.s_inform_SNMPv2c.u16_interval));
		loc_u8_resultat = FALSE;
	}
	
	return loc_u8_resultat;
}/*u8TestConfigSnmp*/

//=====================================================================================
// Fonction		: CopyConfigSnmp
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Snmp SRC==>DST
//=====================================================================================
void CopyConfigSnmp(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_snmp = loc_ps_cfg_src->s_snmp;

}/*CopyConfigSnmp*/

//=====================================================================================
// Fonction		: u8DiffConfigSnmp
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 19/10/2007 -
// Description	: Vérifie si les config SNMP en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigSnmp(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_snmp.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_snmp.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_SNMP)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_SNMP)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigSnmp*/







//***************************************************************************
//**************** PROCEDURES CONFIGURATION GENERALE
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigGeneral
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Générale du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_GENERAL, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigGeneral*/

//=====================================================================================
// Fonction		: u8EditConfigGeneral
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Générale dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_GENERAL, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigGeneral*/

//=====================================================================================
// Fonction		: u8TestConfigGeneral
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des données Général de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	//Paramètres de configuration des modes
	if(loc_ps_config->s_gene.u8_mode_radio_modem >= NB_MAX_MODES_RADIO_MODEM)
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_mode_radio_modem KO :%d \n",
					  loc_ps_config->s_gene.u8_mode_radio_modem));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == T_TB_VAL.pt_definition_radio_modem[loc_ps_config->s_gene.u8_mode_radio_modem].u8_flag_affichage)
		{
			MACRO_PRINTF(("u8TestConfigGeneral: u8_mode_radio_modem flag KO : %d \n",
						  loc_ps_config->s_gene.u8_mode_radio_modem));
			loc_u8_resultat = FALSE;
		}
		else
		{
			if(loc_ps_config->s_gene.u8_mode_network >= NB_MAX_MODES_NETWORK)
			{
				MACRO_PRINTF(("u8TestConfigGeneral: u8_mode_network KO :%d \n",
							  loc_ps_config->s_gene.u8_mode_network));
				loc_u8_resultat = FALSE;
			}
			else
			{
				if(FALSE == T_TB_VAL.pt_definition_radio_modem[loc_ps_config->s_gene.u8_mode_radio_modem].pu8_flag_mode_reseau[loc_ps_config->s_gene.u8_mode_network])
				{
					MACRO_PRINTF(("u8TestConfigGeneral: u8_mode_radio_modem / u8_mode_network KO : %d / %d \n",
								  loc_ps_config->s_gene.u8_mode_radio_modem,
								  loc_ps_config->s_gene.u8_mode_network));
					loc_u8_resultat = FALSE;
				}
			}
		}
	}

	//hostname
	if((strlen(loc_ps_config->s_gene.ps8_hostname) < LG_MIN_HOSTNAME)||
	   (strlen(loc_ps_config->s_gene.ps8_hostname) > LG_MAX_HOSTNAME)||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_gene.ps8_hostname))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_gene.ps8_hostname))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigGeneral: ps8_hostname KO  \n"));
	}
	
	//Paramètres de configuration réseau du bridge
	if(loc_ps_config->s_gene.u8_bridge_mode_ip >= NB_MAX_MODES_IP)
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_bridge_mode_ip KO :%d \n",
					  loc_ps_config->s_gene.u8_bridge_mode_ip));
		loc_u8_resultat = FALSE;
	}

	//On vérifie que l'adresse IP, le mask et la passerelle
	if(FALSE == u8TestConfigIP_Host(loc_ps_config->s_gene.u32_bridge_adresse_ip,
									loc_ps_config->s_gene.u32_bridge_masque_reseau))
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u32_bridge_adresse_ip=0x%08X, u32_bridge_masque_reseau=0x%08X KO \n",
					  loc_ps_config->s_gene.u32_bridge_adresse_ip,
					  loc_ps_config->s_gene.u32_bridge_masque_reseau,
					  loc_ps_config->s_gene.u32_bridge_gateway));
		loc_u8_resultat = FALSE;
	}
	if(loc_ps_config->s_gene.u32_bridge_gateway != 0) //CONDITION: passerelle activée
	{
		if(FALSE == u8TestConfigIP_Subnet(loc_ps_config->s_gene.u32_bridge_adresse_ip,
										   loc_ps_config->s_gene.u32_bridge_masque_reseau,
										   loc_ps_config->s_gene.u32_bridge_gateway))
		{
			MACRO_PRINTF(("u8TestConfigGeneral: u32_bridge_adresse_ip=0x%08X, u32_bridge_masque_reseau=0x%08X, u32_bridge_gateway=0x%08X KO \n",
						  loc_ps_config->s_gene.u32_bridge_adresse_ip,
						  loc_ps_config->s_gene.u32_bridge_masque_reseau,
						  loc_ps_config->s_gene.u32_bridge_gateway));
			loc_u8_resultat = FALSE;
		}
	}

	//On vérifie que l'adresse IP fallback DHCP
	if(ADRESSE_IP_NULLE != loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip) //CONDITION: adresse IP non nulle à tester (car ip nulle valide)
	{
		if(FALSE == u8TestConfigIP_Host(loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip,
										MASK_RESEAU_SUR_24)) //mask 255.255.255.0
		{
			MACRO_PRINTF(("u8TestConfigGeneral: u32_bridge_dhcp_fallback_ip=0x%08X KO \n",
						  loc_ps_config->s_gene.u32_bridge_dhcp_fallback_ip));
			loc_u8_resultat = FALSE;
		}
	}

	if((FALSE != loc_ps_config->s_gene.u8_bridge_stp)&&
	   (TRUE != loc_ps_config->s_gene.u8_bridge_stp)
	  )
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_bridge_stp=%d KO \n",
					  loc_ps_config->s_gene.u8_bridge_stp));
		loc_u8_resultat = FALSE;
	}
	

	//Paramètres de configuration réseau du routeur (Valable pour STATION uniquement)
	// --> Interface LAN  (en mode static forcé)
	if(FALSE == u8TestConfigIP_Host(loc_ps_config->s_gene.u32_lan_adresse_ip,
									loc_ps_config->s_gene.u32_lan_masque_reseau))
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u32_lan_adresse_ip=0x%08X, u32_lan_masque_reseau=0x%08X KO \n",
					  loc_ps_config->s_gene.u32_lan_adresse_ip,
					  loc_ps_config->s_gene.u32_lan_masque_reseau));
		loc_u8_resultat = FALSE;
	}
	
	// --> Interface WLAN
	if(loc_ps_config->s_gene.u8_wlan_mode_ip >= NB_MAX_MODES_IP)
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_wlan_mode_ip KO :%d",
					  loc_ps_config->s_gene.u8_wlan_mode_ip));
		loc_u8_resultat = FALSE;
	}

	if(FALSE == u8TestConfigIP_Host(loc_ps_config->s_gene.u32_wlan_adresse_ip,
									loc_ps_config->s_gene.u32_wlan_masque_reseau))
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u32_wlan_adresse_ip=0x%08X, u32_wlan_masque_reseau=0x%08X KO \n",
					  loc_ps_config->s_gene.u32_wlan_adresse_ip,
					  loc_ps_config->s_gene.u32_wlan_masque_reseau));
		loc_u8_resultat = FALSE;
	}

	if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip) //CONDITION: en mode statique
	{
		//  --> vérification que le sous-réseau du LAN soit différent du sous-réseau du WLAN / ip statique (mode router)
		if( (loc_ps_config->s_gene.u32_wlan_adresse_ip & loc_ps_config->s_gene.u32_wlan_masque_reseau) ==
			  (loc_ps_config->s_gene.u32_lan_adresse_ip & loc_ps_config->s_gene.u32_lan_masque_reseau)
		  ) //CONDITION: sous-réseau LAN identique sous-réseau WLAN
		{
			MACRO_PRINTF(("u8TestConfigGeneral: WLAN:ip=0x%08X/0x%08X LAN:ip=0x%08X/0x%08X KO \n",
						  loc_ps_config->s_gene.u32_wlan_adresse_ip,
						  loc_ps_config->s_gene.u32_wlan_masque_reseau,
						  loc_ps_config->s_gene.u32_lan_adresse_ip,
						  loc_ps_config->s_gene.u32_lan_masque_reseau));
			loc_u8_resultat = FALSE;
		}
	}
	

	if(loc_ps_config->s_gene.u32_wlan_gateway != 0) //CONDITION: passerelle activée
	{
		if(FALSE == u8TestConfigIP_Subnet(loc_ps_config->s_gene.u32_wlan_adresse_ip,
										   loc_ps_config->s_gene.u32_wlan_masque_reseau,
										   loc_ps_config->s_gene.u32_wlan_gateway))
		{
			MACRO_PRINTF(("u8TestConfigGeneral: u32_wlan_adresse_ip=0x%08X, u32_wlan_masque_reseau=0x%08X, u32_wlan_gateway=0x%08X KO \n",
						  loc_ps_config->s_gene.u32_wlan_adresse_ip,
						  loc_ps_config->s_gene.u32_wlan_masque_reseau,
						  loc_ps_config->s_gene.u32_wlan_gateway));
			loc_u8_resultat = FALSE;
		}
	}

	//On vérifie que l'adresse IP fallback DHCP
	if(0 != loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip) //CONDITION: adresse IP non nulle à tester (car ip nulle valide)
	{
		//  --> vérification que l'adresse IP de repli est valide
		if(FALSE == u8TestConfigIP_Host(loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip,
										MASK_RESEAU_SUR_24)) //mask 255.255.255.0
		{
			MACRO_PRINTF(("u8TestConfigGeneral: u32_wlan_dhcp_fallback_ip=0x%08X KO \n",
						  loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip));
			loc_u8_resultat = FALSE;
		}

		//  --> vérification que l'adresse IP de repli doit etre différente du sous-réseau du LAN (mode router)
		if(MODE_IP_DHCP_CLIENT == loc_ps_config->s_gene.u8_wlan_mode_ip) //CONDITION: en mode DHCP client
		{
			if( (loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip & MASK_RESEAU_SUR_24) ==
				  (loc_ps_config->s_gene.u32_lan_adresse_ip & loc_ps_config->s_gene.u32_lan_masque_reseau)
			  ) //CONDITION: sous-réseau LAN identique sous-réseau WLAN
			{
				MACRO_PRINTF(("u8TestConfigGeneral: u32_wlan_dhcp_fallback_ip=0x%08X/0x%08X  LAN:ip=0x%08X/0x%08X KO \n",
							  loc_ps_config->s_gene.u32_wlan_dhcp_fallback_ip,
							  MASK_RESEAU_SUR_24,
							  loc_ps_config->s_gene.u32_lan_adresse_ip,
							  loc_ps_config->s_gene.u32_lan_masque_reseau));
				loc_u8_resultat = FALSE;
			}
		}
	}

	//Paramètres de configuration du serveur/relai DHCP
	if(loc_ps_config->s_gene.u8_lan_fonction_dhcp >= NB_MAX_FCT_DHCP)
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_lan_fonction_dhcp KO :%d",
					  loc_ps_config->s_gene.u8_lan_fonction_dhcp));
		loc_u8_resultat = FALSE;
	}

	if((DHCP_DUREE_VIE_BAIL_MIN <= loc_ps_config->s_gene.u32_lan_dhcpsrv_duree_vie_bail)&&
	   (loc_ps_config->s_gene.u32_lan_dhcpsrv_duree_vie_bail <= DHCP_DUREE_VIE_BAIL_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u32_lan_dhcpsrv_duree_vie_bail KO :%d \n",
					  loc_ps_config->s_gene.u32_lan_dhcpsrv_duree_vie_bail));
		loc_u8_resultat = FALSE;
	}

	//Paramètres de configuration du VLAN
	if((FALSE != loc_ps_config->s_gene.u8_vlan_autoriser)&&
	   (TRUE != loc_ps_config->s_gene.u8_vlan_autoriser)
	  )
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_vlan_autoriser KO :%d \n",
					  loc_ps_config->s_gene.u8_vlan_autoriser));
		loc_u8_resultat = FALSE;
	}

	if(strlen(loc_ps_config->s_gene.ps8_vlan_nom) > TAILLE_MAX_VLAN)
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigGeneral: ps8_vlan_nom KO  \n"));
	}

	
	if(((VLAN_ID_MIN <= loc_ps_config->s_gene.u16_vlan_id)&&
		(loc_ps_config->s_gene.u16_vlan_id <= VLAN_ID_MAX))
#ifdef _WRM100_ABG_SELECT
	   ||(FALSE == loc_ps_config->s_gene.u8_vlan_autoriser)
#endif
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u16_vlan_id KO :%d \n",
					  loc_ps_config->s_gene.u16_vlan_id));
		loc_u8_resultat = FALSE;
	}

	if((FALSE != loc_ps_config->s_gene.u8_vlan_interface_notag)&&
	   (TRUE != loc_ps_config->s_gene.u8_vlan_interface_notag)
	  )
	{
		MACRO_PRINTF(("u8TestConfigGeneral: u8_vlan_interface_notag KO :%d \n",
					  loc_ps_config->s_gene.u8_vlan_interface_notag));
		loc_u8_resultat = FALSE;
	}

	if((TRUE == loc_ps_config->s_gene.u8_vlan_autoriser)&&
	   (TRUE == loc_ps_config->s_gene.u8_vlan_interface_notag)
	  )
	{
		//Pour un interface non taggé vlan
		if(FALSE == u8TestConfigIP_Host(loc_ps_config->s_gene.u32_vlan_notag_adresse_ip,
										loc_ps_config->s_gene.u32_wlan_masque_reseau))
		{
			MACRO_PRINTF(("u8TestConfigGeneral: u32_vlan_notag_adresse_ip=0x%08X, u32_vlan_notag_masque_reseau=0x%08X KO \n",
						  loc_ps_config->s_gene.u32_vlan_notag_adresse_ip,
						  loc_ps_config->s_gene.u32_vlan_notag_masque_reseau));
			loc_u8_resultat = FALSE;
		}
	}
	
	return loc_u8_resultat;
}/*u8TestConfigGeneral*/

//=====================================================================================
// Fonction		: CopyConfigGeneral
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Général SRC==>DST
//=====================================================================================
void CopyConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_gene = loc_ps_cfg_src->s_gene;

}/*CopyConfigGeneral*/

//=====================================================================================
// Fonction		: u8DiffConfigGeneral
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config General en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigGeneral(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_gene.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_gene.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_GENERAL)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_GENERAL)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigGeneral*/

//=====================================================================================
// Fonction		: u8DiffConfigGene_NetworkBridge
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config General (network bridge) en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigGene_NetworkBridge(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT
	
	if((loc_ps_config1->s_gene.u8_bridge_mode_ip != loc_ps_config2->s_gene.u8_bridge_mode_ip) ||
	   (loc_ps_config1->s_gene.u32_bridge_adresse_ip != loc_ps_config2->s_gene.u32_bridge_adresse_ip) ||
	   (loc_ps_config1->s_gene.u32_bridge_masque_reseau != loc_ps_config2->s_gene.u32_bridge_masque_reseau) ||
	   (loc_ps_config1->s_gene.u32_bridge_gateway != loc_ps_config2->s_gene.u32_bridge_gateway) ||
	   (loc_ps_config1->s_gene.u32_bridge_dhcp_fallback_ip != loc_ps_config2->s_gene.u32_bridge_dhcp_fallback_ip) ||
	   (loc_ps_config1->s_gene.u8_bridge_stp != loc_ps_config2->s_gene.u8_bridge_stp) ||
	   (0 != strcmp(loc_ps_config1->s_gene.ps8_hostname, loc_ps_config2->s_gene.ps8_hostname)) ||
	   (loc_ps_config1->s_gene.u8_vlan_autoriser != loc_ps_config2->s_gene.u8_vlan_autoriser) ||
	   (0 != strcmp(loc_ps_config1->s_gene.ps8_vlan_nom, loc_ps_config2->s_gene.ps8_vlan_nom)) ||
	   (loc_ps_config1->s_gene.u16_vlan_id != loc_ps_config2->s_gene.u16_vlan_id) ||
	   (loc_ps_config1->s_gene.u8_vlan_interface_notag != loc_ps_config2->s_gene.u8_vlan_interface_notag) ||
	   (loc_ps_config1->s_gene.u32_vlan_notag_adresse_ip != loc_ps_config2->s_gene.u32_vlan_notag_adresse_ip) ||
	   (loc_ps_config1->s_gene.u32_vlan_notag_masque_reseau != loc_ps_config2->s_gene.u32_vlan_notag_masque_reseau)
	  )
	{
		loc_u8_return = TRUE;
	}
	   
	return loc_u8_return;
}/*u8DiffConfigGene_NetworkBridge*/

//=====================================================================================
// Fonction		: u8DiffConfigGene_NetworkRouter
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config General (network router) en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigGene_NetworkRouter(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT

	if((loc_ps_config1->s_gene.u32_lan_adresse_ip != loc_ps_config2->s_gene.u32_lan_adresse_ip) ||
	   (loc_ps_config1->s_gene.u32_lan_masque_reseau != loc_ps_config2->s_gene.u32_lan_masque_reseau) ||
	   (loc_ps_config1->s_gene.u8_wlan_mode_ip != loc_ps_config2->s_gene.u8_wlan_mode_ip) ||
	   (loc_ps_config1->s_gene.u32_wlan_adresse_ip != loc_ps_config2->s_gene.u32_wlan_adresse_ip) ||
	   (loc_ps_config1->s_gene.u32_wlan_masque_reseau != loc_ps_config2->s_gene.u32_wlan_masque_reseau) ||
	   (loc_ps_config1->s_gene.u32_wlan_gateway != loc_ps_config2->s_gene.u32_wlan_gateway) ||
	   (loc_ps_config1->s_gene.u32_wlan_dhcp_fallback_ip != loc_ps_config2->s_gene.u32_wlan_dhcp_fallback_ip) ||
	   (0 != strcmp(loc_ps_config1->s_gene.ps8_hostname, loc_ps_config2->s_gene.ps8_hostname))
	  )
	{
		loc_u8_return = TRUE;
	}

	return loc_u8_return;
}/*u8DiffConfigGene_NetworkRouter*/

//=====================================================================================
// Fonction		: u8DiffConfigGene_FctDHCP
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 15/01/2010 -
// Description	: Vérifie si les config General (dhcp) en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigGene_FctDHCP(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return;
	loc_u8_return = FALSE;//INIT

	if(loc_ps_config1->s_gene.u8_lan_fonction_dhcp != loc_ps_config2->s_gene.u8_lan_fonction_dhcp)
	{
		loc_u8_return = TRUE;
	}
	else
	{
		switch(loc_ps_config1->s_gene.u8_lan_fonction_dhcp)
		{
			case FCT_DHCP_NONE:
				break;
			case FCT_DHCP_SERVER:
				if((loc_ps_config1->s_gene.u32_lan_dhcpsrv_ip_min != loc_ps_config2->s_gene.u32_lan_dhcpsrv_ip_min) ||
				   (loc_ps_config1->s_gene.u32_lan_dhcpsrv_ip_max != loc_ps_config2->s_gene.u32_lan_dhcpsrv_ip_max) ||
				   (loc_ps_config1->s_gene.u32_lan_dhcpsrv_duree_vie_bail != loc_ps_config2->s_gene.u32_lan_dhcpsrv_duree_vie_bail)
				  )
				{
					loc_u8_return = TRUE;
				}
				break;
			case FCT_DHCP_RELAY:
				if(loc_ps_config1->s_gene.u32_lan_dhcprelay_ip != loc_ps_config2->s_gene.u32_lan_dhcprelay_ip)
				{
					loc_u8_return = TRUE;
				}
				break;
			default:
				break;
		}
	}

	return loc_u8_return;
}/*u8DiffConfigGene_FctDHCP*/

//=====================================================================================
// Fonction		: u8TestFctDHCP_Fonctionnelle
// Entrees		: <loc_ps_config> config de l'équipement à tester
// Sortie		: <loc_u8_return> TRUE si OK ou FALSE sinon 
// Auteur		: CM - 15/01/2010 -
// Description	: Test si la configuration DHCP est fonctionnelle
//=====================================================================================
u8sod u8TestFctDHCP_Fonctionnelle(S_STRUCT_CONFIGURATION * loc_ps_config)
{
	u8sod loc_u8_return;
	u32sod	loc_u32_subnet;
	u32sod	loc_u32_host_mask;
	
	loc_u8_return = TRUE;//INIT
	loc_u32_subnet = (loc_ps_config->s_gene.u32_lan_masque_reseau & loc_ps_config->s_gene.u32_lan_adresse_ip);
	loc_u32_host_mask = (u32sod)(~loc_u32_subnet) & MASK_RESEAU_SUR_32;

	switch(loc_ps_config->s_gene.u8_lan_fonction_dhcp)
	{
		case FCT_DHCP_NONE:
			break;
		case FCT_DHCP_SERVER:
			//On teste si l'adresse min est dans le sous réseau du LAN
			if((loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_min & loc_ps_config->s_gene.u32_lan_masque_reseau) != loc_u32_subnet)
			{
				loc_u8_return = FALSE;
			}
			//On teste si l'adresse max est dans le sous réseau du LAN
			if((loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_max & loc_ps_config->s_gene.u32_lan_masque_reseau) != loc_u32_subnet)
			{
				loc_u8_return = FALSE;
			}
			//On teste si l'adresse min est bien une adresse HOST
			if(0 == (loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_min & loc_u32_host_mask))
			{
				loc_u8_return = FALSE;
			}
			//On teste si l'adresse max > adresse min
			if(loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_min > loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_max)
			{
				loc_u8_return = FALSE;
			}
			//On teste si la plage d'adresse est valide (pas d'adresse de broadcast)
			if((loc_u32_host_mask == (loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_min & loc_u32_host_mask))||
			   (loc_u32_host_mask == (loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_max & loc_u32_host_mask))
			  )
			{
				loc_u8_return = FALSE;
			}
			//On teste si le nombre d'adresses IP n'excedent pas la limite autorisée
			if((loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_max - loc_ps_config->s_gene.u32_lan_dhcpsrv_ip_min) > (NB_MAX_CLIENTS_DHCP))
			{
				loc_u8_return = FALSE;
			}
			break;
		case FCT_DHCP_RELAY:
			if((ADRESSE_IP_NULLE == loc_ps_config->s_gene.u32_lan_dhcprelay_ip)||
			   (MASK_RESEAU_SUR_32 == loc_ps_config->s_gene.u32_lan_dhcprelay_ip)
			  )
			{
				loc_u8_return = FALSE;
			}
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8TestFctDHCP_Fonctionnelle*/

//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//=====================================================================================
// Fonction		: u8ImposeInitConfigGeneral
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: nouvelle config (si TRUE), sinon FALSE
// Auteur		: CM - 10/05/2011 -
// Description	: impose configuration au démarrage (config générale)
//=====================================================================================
u8sod u8ImposeInitConfigGeneral(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(MODE_RADIO_MODEM_MESH_POINT == loc_ps_config->s_gene.u8_mode_radio_modem)
	{
		loc_ps_config->s_gene.u8_mode_radio_modem = MODE_RADIO_MODEM_ACCESS_POINT;
		loc_u8_resultat = TRUE;	//nouvelle config
		
//d: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
		//La configuration Wifi doit etre forcé par défaut
		OrderSetConfigDefaut(IDXCFG_WIFI);		
//f: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

//d: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
		//On signale la détection d'un nouvel équipement
		OrderSetNewEquipment();
//f: BE061 10/05/2011 - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
	}

	return loc_u8_resultat;
}/*u8ImposeInitConfigGeneral*/
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut


//***************************************************************************
//**************** PROCEDURES CONFIGURATION WIFI
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigWifi
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Wifi du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_WIFI, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigWifi*/

//=====================================================================================
// Fonction		: u8EditConfigWifi
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Wifi dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_WIFI, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigWifi*/

//=====================================================================================
// Fonction		: ImposeConfigWifiSiIncoherente
// Entrees		: <loc_ps_config> : config qu'il faut mettre à jour
// Sortie		: rien
// Auteur		: CM - 28/09/2009 -
// Description	: Impose certains paramètres si config Wifi incohérente
//=====================================================================================
void ImposeConfigWifiSiIncoherente(S_STRUCT_CONFIGURATION *loc_ps_config)
{
}/*ImposeConfigWifiSiIncoherente*/

//=====================================================================================
// Fonction		: u8TestConfigWifi
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 28/28/2009 -
// Description	: Test des données Wifi de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_i;

	loc_u8_resultat = TRUE;	//INIT

	//Paramètres de configuration
	if(loc_ps_config->s_wifi.u8_mode_802_11x >= NB_MAX_MODES_WIFI_802_11)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_mode_802_11x KO :%d \n",
					  loc_ps_config->s_wifi.u8_mode_802_11x));
		loc_u8_resultat = FALSE;
	}

	   if((strlen(loc_ps_config->s_wifi.ps8_ssid_primary) < NB_MIN_CHAINE_SSID)||
		  (strlen(loc_ps_config->s_wifi.ps8_ssid_primary) > NB_MAX_CHAINE_SSID) ||
		  (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.ps8_ssid_primary))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: ps8_ssid_primary KO  \n"));
	}

	if((FALSE != loc_ps_config->s_wifi.u8_dual_ssid) &&
	   (TRUE != loc_ps_config->s_wifi.u8_dual_ssid)
	  )
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_dual_ssid KO :%d \n",
					  loc_ps_config->s_wifi.u8_dual_ssid));
		loc_u8_resultat = FALSE;
	}

	if((strlen(loc_ps_config->s_wifi.ps8_ssid_secondary) < NB_MIN_CHAINE_SSID)||
	   (strlen(loc_ps_config->s_wifi.ps8_ssid_secondary) > NB_MAX_CHAINE_SSID)||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.ps8_ssid_secondary))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: ps8_ssid_secondary KO  \n"));
	}
	
	if((FALSE != loc_ps_config->s_wifi.u8_masquage_ssid) &&
	   (TRUE != loc_ps_config->s_wifi.u8_masquage_ssid)
	  )
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_masquage_ssid KO :%d \n",
					  loc_ps_config->s_wifi.u8_masquage_ssid));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_wifi.u8_11n_guard_interval >= NB_MAX_TYPE_GUARD_INTERVAL)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_11n_guard_interval KO :%d \n",
					  loc_ps_config->s_wifi.u8_11n_guard_interval));
		loc_u8_resultat = FALSE;
	}
	
	if(loc_ps_config->s_wifi.u8_type_selection_canal >= NB_MAX_TYPE_SELECTION_CANAL)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_type_selection_canal KO :%d \n",
					  loc_ps_config->s_wifi.u8_type_selection_canal));
		loc_u8_resultat = FALSE;
	}

#warning "DOIT-ON TESTER LA COHERENCE DES CANAUX"
#warning "DOIT-ON TESTER LA COHERENCE DES CANAUX"
#warning "DOIT-ON TESTER LA COHERENCE DES CANAUX"

#ifdef _WRM100_ABG_SELECT
	if(FALSE == u8Test_ABG_ConfigPowerTx(loc_ps_config->s_wifi.u8_power_tx,
									loc_ps_config->s_wifi.u8_mode_802_11x)
	  )
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8Test_ABG_ConfigPowerTx KO : u8_power_tx=%d u8_mode_802_11x=%d \n",
					  loc_ps_config->s_wifi.u8_power_tx,
					  loc_ps_config->s_wifi.u8_mode_802_11x));
		loc_u8_resultat = FALSE;
	}
#endif
	
#ifdef _WRM100_N_SELECT
	if(FALSE == u8Test_N_ConfigPowerTx(loc_ps_config->s_wifi.u8_power_tx,
										loc_ps_config->s_wifi.u8_mode_802_11x,
										loc_ps_config->s_wifi.u8_data_rate,
										loc_ps_config->s_wifi.u8_ant_N_selection)
	  )
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8Test_N_ConfigPowerTx KO : u8_power_tx=%d u8_mode_802_11x=%d u8_data_rate=%d u8_ant_N_selection=%d\n",
					  loc_ps_config->s_wifi.u8_power_tx,
					  loc_ps_config->s_wifi.u8_mode_802_11x,
					  loc_ps_config->s_wifi.u8_data_rate,
					  loc_ps_config->s_wifi.u8_ant_N_selection));
		loc_u8_resultat = FALSE;
	}
#endif
	
	if(loc_ps_config->s_wifi.u8_data_rate >= NB_MAX_DATA_RATE)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_data_rate KO 1) :%d \n",
					  loc_ps_config->s_wifi.u8_data_rate));
		loc_u8_resultat = FALSE;
	}
	else
	{
#ifdef _WRM100_ABG_SELECT
		if(FALSE == u8Test_ABG_ConfigDataRate(loc_ps_config->s_wifi.u8_data_rate,
											  loc_ps_config->s_wifi.u8_mode_802_11x)
		  )
		{
			MACRO_PRINTF(("u8TestConfigWifi: u8_data_rate KO 2) :%d \n",
						  loc_ps_config->s_wifi.u8_data_rate));
			loc_u8_resultat = FALSE;
		}
#endif
#ifdef _WRM100_N_SELECT
		if(FALSE == u8Test_N_ConfigDataRate(loc_ps_config->s_wifi.u8_data_rate,
											loc_ps_config->s_wifi.u8_mode_802_11x,
											loc_ps_config->s_wifi.u8_ant_N_selection)
		  )
		{
			MACRO_PRINTF(("u8TestConfigWifi: u8_data_rate KO 3) :%d \n",
						  loc_ps_config->s_wifi.u8_data_rate));
			loc_u8_resultat = FALSE;
		}
#endif
	}

	if((SEUIL_RX_MIN <= loc_ps_config->s_wifi.s8_seuil_rx)&&
	   (loc_ps_config->s_wifi.s8_seuil_rx <= SEUIL_RX_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigWifi: s8_seuil_rx=%d KO) :%d \n",
					  loc_ps_config->s_wifi.s8_seuil_rx));
		loc_u8_resultat = FALSE;
	}
	
	if((NB_ASSOCIATED_STATIONS_MIN <= loc_ps_config->s_wifi.u16_nb_max_associated_stations)&&
	   (loc_ps_config->s_wifi.u16_nb_max_associated_stations <= NB_ASSOCIATED_STATIONS_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigWifi: u16_nb_max_associated_stations KO :%d \n",
					  loc_ps_config->s_wifi.u16_nb_max_associated_stations));
		loc_u8_resultat = FALSE;
	}
	
	if(loc_ps_config->s_wifi.u8_mode_securite_wifi >= NB_MAX_MODES_SECURITE_WIFI)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_mode_securite_wifi KO :%d \n",
					  loc_ps_config->s_wifi.u8_mode_securite_wifi));
		loc_u8_resultat = FALSE;
	}

	//Paramètres de configuration du WEP (Wired Equivalent Privacy)
	if(loc_ps_config->s_wifi.s_wep_security.u8_key_length >= NB_MAX_WEP_KEY_LENGTH)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.u8_key_length KO :%d \n",
					  loc_ps_config->s_wifi.s_wep_security.u8_key_length));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_wifi.s_wep_security.u8_wep_key_type >= NB_MAX_KEY_TYPE)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.u8_wep_key_type KO :%d \n",
					  loc_ps_config->s_wifi.s_wep_security.u8_wep_key_type));
		loc_u8_resultat = FALSE;
	}

	for(loc_u8_i=0;loc_u8_i<NB_MAX_IDX_WEP_KEY;loc_u8_i++)
	{
		if((strlen(loc_ps_config->s_wifi.s_wep_security.ps8_key_value[loc_u8_i]) > KEY_WEP_VALUE_LENGTH_MAX) ||
		   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wep_security.ps8_key_value[loc_u8_i]))
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.ps8_key_value[%d] KO 1) \n",
						 loc_u8_i));
		}
#if 0
		//on ne teste pas chaque clé uniquement la clé par défaut
		else
		{
			//on teste les clés en fonction de la longueur et du type sélectionné
			if((u8sod)strlen(loc_ps_config->s_wifi.s_wep_security.ps8_key_value[loc_u8_i]) !=
			   T_TB_VAL.pu8_lg_wep_key[loc_ps_config->s_wifi.s_wep_security.u8_key_length][loc_ps_config->s_wifi.s_wep_security.u8_wep_key_type])
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.ps8_key_value[%d] KO 2) lg=%d != %d \n",
							  loc_u8_i,
							  strlen(loc_ps_config->s_wifi.s_wep_security.ps8_key_value[loc_u8_i]),
							  T_TB_VAL.pu8_lg_wep_key[loc_ps_config->s_wifi.s_wep_security.u8_key_length][loc_ps_config->s_wifi.s_wep_security.u8_wep_key_type]));
			}
		}
#endif
	}

	if(loc_ps_config->s_wifi.s_wep_security.u8_index_key_default >= NB_MAX_IDX_WEP_KEY)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.u8_index_key_default KO :%d \n",
					  loc_ps_config->s_wifi.s_wep_security.u8_index_key_default));
		loc_u8_resultat = FALSE;
	}
	else
	{
		//on teste la clé sélectionnée en fonction de la longueur et du type sélectionné
		if((u8sod)strlen(loc_ps_config->s_wifi.s_wep_security.ps8_key_value[loc_ps_config->s_wifi.s_wep_security.u8_index_key_default]) !=
		   T_TB_VAL.pu8_lg_wep_key[loc_ps_config->s_wifi.s_wep_security.u8_key_length][loc_ps_config->s_wifi.s_wep_security.u8_wep_key_type])
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.ps8_key_value[u8_index_key_default=%d] KO 2) lg=%d != %d \n",
						  loc_ps_config->s_wifi.s_wep_security.u8_index_key_default,
						  strlen(loc_ps_config->s_wifi.s_wep_security.ps8_key_value[loc_ps_config->s_wifi.s_wep_security.u8_index_key_default]),
						  T_TB_VAL.pu8_lg_wep_key[loc_ps_config->s_wifi.s_wep_security.u8_key_length][loc_ps_config->s_wifi.s_wep_security.u8_wep_key_type]));
		}
	}

	if(loc_ps_config->s_wifi.s_wep_security.u8_authentification >= NB_MAX_WEP_AUTHENTIFICATION)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wep_security.u8_authentification KO :%d \n",
					  loc_ps_config->s_wifi.s_wep_security.u8_authentification));
		loc_u8_resultat = FALSE;
	}
	
	//Paramètres de configuration du WPA (Wi-Fi Protected Access)
	if(loc_ps_config->s_wifi.s_wpa_security.u8_authentification >= NB_MAX_WPA_AUTHENTIFICATION)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.u8_authentification KO :%d \n",
					  loc_ps_config->s_wifi.s_wpa_security.u8_authentification));
		loc_u8_resultat = FALSE;
	}

	if((GP_KEY_UPDATE_INTERVAL_MIN <= loc_ps_config->s_wifi.s_wpa_security.u32_gp_key_update_interval)&&
	   (loc_ps_config->s_wifi.s_wpa_security.u32_gp_key_update_interval <= GP_KEY_UPDATE_INTERVAL_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.u32_gp_key_update_interval KO :%d \n",
					  loc_ps_config->s_wifi.s_wpa_security.u32_gp_key_update_interval));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_wifi.s_wpa_security.u8_wpa_key_type >= NB_MAX_KEY_TYPE)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.u8_wpa_key_type KO :%d \n",
					  loc_ps_config->s_wifi.s_wpa_security.u8_wpa_key_type));
		loc_u8_resultat = FALSE;
	}

	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key) > LG_MAX_PRESHARED_WPA_TOTAL) ||
		(FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_pre_shared_key KO  \n"));
	}
	else
	{
		//on teste la clé en fonction du type sélectionné
		switch(loc_ps_config->s_wifi.s_wpa_security.u8_wpa_key_type)
		{
			case KEY_TYPE_HEXA:
				if((u8sod)strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key) != LG_MAX_PRESHARED_KEY_WPA_HEXA)
				{
					loc_u8_resultat = FALSE;
					MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_pre_shared_key KO 2) lg=%d HEXA \n",
								  strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key)));
				}
				break;
			case KEY_TYPE_ASCII:
				if((LG_MIN_PRESHARED_KEY_WPA <= strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key))&&
				   (strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key) <= LG_MAX_PRESHARED_KEY_WPA_ASCII)
				  )
				{
					;//OK
				}
				else
				{
					loc_u8_resultat = FALSE;
					MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_pre_shared_key KO 2) lg=%d ASCII \n",
								  strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_pre_shared_key)));
				}
				break;
			default:
				break;
		}
	}

	//serveur radius
	if((strlen(loc_ps_config->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared) > LG_MAX_SHARED_RADIUS) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.s_server_radius.ps8_radius_shared KO  \n"));
	}
	
	if(loc_ps_config->s_wifi.s_wpa_security.u8_eap_method >= NB_MAX_EAP_METHOD)
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.u8_eap_method KO :%d \n",
					  loc_ps_config->s_wifi.s_wpa_security.u8_eap_method));
		loc_u8_resultat = FALSE;
	}

	if(((EAP_REAUTH_PERIOD_MIN <= loc_ps_config->s_wifi.s_wpa_security.u32_eap_reauth_period)&&
	   (loc_ps_config->s_wifi.s_wpa_security.u32_eap_reauth_period <= EAP_REAUTH_PERIOD_MAX)
	   )||
	   (EAP_REAUTH_PERIOD_DISABLED == loc_ps_config->s_wifi.s_wpa_security.u32_eap_reauth_period)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.u32_eap_reauth_period KO :%d \n",
					  loc_ps_config->s_wifi.s_wpa_security.u32_eap_reauth_period));
		loc_u8_resultat = FALSE;
	}
	

	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_identity) > LG_MAX_EAP_IDENTITY) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.ps8_identity))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_identity))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_identity KO  \n"));
	}

#if PARAMETERS_RADIUS_NOT_USED
	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_user_name) > LG_MAX_EAP_USER_NAME) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.ps8_user_name))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_user_name))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_user_name KO  \n"));
	}
#endif

	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_user_password) > LG_MAX_EAP_USER_PASSWORD) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.ps8_user_password))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_user_password))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_user_password KO  \n"));
	}

	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_authority) > LG_MAX_NOM_CERTIFICAT) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_authority))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_authority))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_file_certificat_authority KO  \n"));
	}

	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_client) > LG_MAX_NOM_CERTIFICAT) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_client))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_file_certificat_client))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_file_certificat_client KO  \n"));
	}

	if((strlen(loc_ps_config->s_wifi.s_wpa_security.ps8_private_key_password) > LG_MAX_PRIVATE_KEY_PWD) ||
	   (FALSE == u8TestConfigChaineSansEspace(loc_ps_config->s_wifi.s_wpa_security.ps8_private_key_password))||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_wifi.s_wpa_security.ps8_private_key_password))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigWifi: s_wpa_security.ps8_private_key_password KO  \n"));
	}
	

#ifdef _WRM100_N_SELECT
	if(loc_ps_config->s_wifi.u8_ant_N_selection >= NB_MAX_N_SELECT_ANTENNES)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_ant_N_selection KO :%d \n",
					  loc_ps_config->s_wifi.u8_ant_N_selection));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if((TRUE == u8IsMode80211ag(loc_ps_config->s_wifi.u8_mode_802_11x))||
		   (TRUE == u8IsMode80211b(loc_ps_config->s_wifi.u8_mode_802_11x))
		  )
		{
			if(N_SELECT_ANTENNE_1 != loc_ps_config->s_wifi.u8_ant_N_selection)
			{
				MACRO_PRINTF(("u8TestConfigWifi: u8_ant_N_selection KO:%d pour u8_mode_802_11=%d \n",
							  loc_ps_config->s_wifi.u8_ant_N_selection,
							  loc_ps_config->s_wifi.u8_mode_802_11x));
				loc_u8_resultat = FALSE;
			}
		}

		if(TRUE == u8IsMode80211nHT40(loc_ps_config->s_wifi.u8_mode_802_11x))
		{
			switch(loc_ps_config->s_wifi.u8_data_rate)
			{
				case DATA_RATE_MCS8:
				case DATA_RATE_MCS9:
				case DATA_RATE_MCS10:
				case DATA_RATE_MCS11:
				case DATA_RATE_MCS12:
				case DATA_RATE_MCS13:
				case DATA_RATE_MCS14:
				case DATA_RATE_MCS15:
					if(N_SELECT_ANTENNE_1 == loc_ps_config->s_wifi.u8_ant_N_selection)
					{
						MACRO_PRINTF(("u8TestConfigWifi: u8_ant_N_selection KO:%d pour u8_mode_802_11x=%d et u8_data_rate=%d \n",
									  loc_ps_config->s_wifi.u8_ant_N_selection,
									  loc_ps_config->s_wifi.u8_mode_802_11x,
									  loc_ps_config->s_wifi.u8_data_rate));
						loc_u8_resultat = FALSE;
					}
					break;
				case DATA_RATE_MCS16:
				case DATA_RATE_MCS17:
				case DATA_RATE_MCS18:
				case DATA_RATE_MCS19:
				case DATA_RATE_MCS20:
				case DATA_RATE_MCS21:
				case DATA_RATE_MCS22:
				case DATA_RATE_MCS23:
					if((N_SELECT_ANTENNE_1 == loc_ps_config->s_wifi.u8_ant_N_selection)||(N_SELECT_ANTENNES_1_ET_2==loc_ps_config->s_wifi.u8_ant_N_selection))
					{
						MACRO_PRINTF(("u8TestConfigWifi: u8_ant_N_selection KO:%d pour u8_mode_802_11x=%d et u8_data_rate=%d \n",
							loc_ps_config->s_wifi.u8_ant_N_selection,
							loc_ps_config->s_wifi.u8_mode_802_11x,
							loc_ps_config->s_wifi.u8_data_rate));
						loc_u8_resultat = FALSE;
					}
					break;				
				default:
					break;
			}
		}
	}
#endif

#ifdef _WRM100_N_SELECT
	if(FALSE == u8TestCfg_N_AckTimeout(loc_ps_config))
	{
		MACRO_PRINTF(("u8TestConfigWifi: : u8TestCfg_N_AckTimeout KO \n"));
		loc_u8_resultat = FALSE;
	}
#endif

	//Paramètres de configuration
	if((WF_ABG_ACK_TIMEOUT_MIN <= loc_ps_config->s_wifi.u16_protcl_ABG_ACK_timeout)&&
	   (loc_ps_config->s_wifi.u16_protcl_ABG_ACK_timeout <= WF_ABG_ACK_TIMEOUT_MAX)
	  )
	{
		; //OK
	}
	else			
	{
		MACRO_PRINTF(("u8TestConfigWifi: u16_protcl_ABG_ACK_timeout KO :%d \n",
					  loc_ps_config->s_wifi.u16_protcl_ABG_ACK_timeout));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_wifi.u8_protcl_type_preambule >= NB_MAX_WF_TYPE_PREAMBULE)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_protcl_type_preambule KO :%d \n",
					  loc_ps_config->s_wifi.u8_protcl_type_preambule));
		loc_u8_resultat = FALSE;
	}

	if((WF_FRAGMENT_THRESHOLD_MIN <= loc_ps_config->s_wifi.u16_protcl_fragment_threshold)&&
	   (loc_ps_config->s_wifi.u16_protcl_fragment_threshold <= WF_FRAGMENT_THRESHOLD_MAX)
	  )
	{
		; //OK
	}
	else			
	{
		MACRO_PRINTF(("u8TestConfigWifi: u16_protcl_fragment_threshold KO :%d \n",
					  loc_ps_config->s_wifi.u16_protcl_fragment_threshold));
		loc_u8_resultat = FALSE;
	}

	if((WF_RTS_CTS_THRESHOLD_MIN <= loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold)&&
	   (loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold <= WF_RTS_CTS_THRESHOLD_MAX)
	  )
	{
		; //OK
	}
	else			
	{
		MACRO_PRINTF(("u8TestConfigWifi: u16_protcl_RTS_CTS_threshold KO :%d \n",
					  loc_ps_config->s_wifi.u16_protcl_RTS_CTS_threshold));
		loc_u8_resultat = FALSE;
	}

	if((WF_RTS_RETRY_LIMIT_MIN <= loc_ps_config->s_wifi.u16_protcl_RTS_retry_limit)&&
	   (loc_ps_config->s_wifi.u16_protcl_RTS_retry_limit <= WF_RTS_RETRY_LIMIT_MAX)
	  )
	{
		; //OK
	}
	else			
	{
		MACRO_PRINTF(("u8TestConfigWifi: u16_protcl_RTS_retry_limit KO :%d \n",
					  loc_ps_config->s_wifi.u16_protcl_RTS_retry_limit));
		loc_u8_resultat = FALSE;
	}

	if((WF_BEACON_PERIOD_MIN <= loc_ps_config->s_wifi.u16_protcl_beacon_period)&&
	   (loc_ps_config->s_wifi.u16_protcl_beacon_period <= WF_BEACON_PERIOD_MAX)
	  )
	{
		; //OK
	}
	else			
	{
		MACRO_PRINTF(("u8TestConfigWifi: u16_protcl_beacon_period KO :%d \n",
					  loc_ps_config->s_wifi.u16_protcl_beacon_period));
		loc_u8_resultat = FALSE;
	}

	if((FALSE != loc_ps_config->s_wifi.u8_activation_WMM)&&
	   (TRUE != loc_ps_config->s_wifi.u8_activation_WMM)
	  )
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_activation_WMM KO :%d \n",
					  loc_ps_config->s_wifi.u8_activation_WMM));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_wifi.u8_countryID >= NB_MAX_COUNTRY_ID)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_countryID KO :%d \n",
					  loc_ps_config->s_wifi.u8_countryID));
		loc_u8_resultat = FALSE;
	}

	if((FALSE != loc_ps_config->s_wifi.u8_desactivation_DFS)&&
	   (TRUE != loc_ps_config->s_wifi.u8_desactivation_DFS)
	  )
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_desactivation_DFS KO :%d \n",
					  loc_ps_config->s_wifi.u8_desactivation_DFS));
		loc_u8_resultat = FALSE;
	}
	
#ifdef _WRM100_ABG_SELECT
	if(loc_ps_config->s_wifi.u8_ant_ABG_tx_selection >= NB_MAX_ABG_SELECT_ANT_TX)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_ant_ABG_tx_selection KO :%d \n",
					  loc_ps_config->s_wifi.u8_ant_ABG_tx_selection));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_wifi.u8_ant_ABG_rx_selection >= NB_MAX_ABG_SELECT_ANT_RX)
	{
		MACRO_PRINTF(("u8TestConfigWifi: u8_ant_ABG_rx_selection KO :%d \n",
					  loc_ps_config->s_wifi.u8_ant_ABG_rx_selection));
		loc_u8_resultat = FALSE;
	}
#endif
	
	return loc_u8_resultat;
}/*u8TestConfigWifi*/

//=====================================================================================
// Fonction		: CopyConfigWifi
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Wifi SRC==>DST
//=====================================================================================
void CopyConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_wifi = loc_ps_cfg_src->s_wifi;

}/*CopyConfigWifi*/

//=====================================================================================
// Fonction		: u8DiffConfigWifi
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config Wifi en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigWifi(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_wifi.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_wifi.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_WIFI)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_WIFI)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigWifi*/

//=====================================================================================
// Fonction		: u8DiffConfigFrequence
// Entrees		: <loc_ps_config1> config n°1 à comparer (courante)
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config frequence (Wifi) en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigFrequence(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return = FALSE; //INIT
	u8sod  loc_u8_i;

	if((loc_ps_config1->s_wifi.u8_type_selection_canal != loc_ps_config2->s_wifi.u8_type_selection_canal) ||
	   (loc_ps_config1->s_wifi.u16_iso_canal_radio != loc_ps_config2->s_wifi.u16_iso_canal_radio)
	  )
	{
		loc_u8_return = TRUE;
	}

	for(loc_u8_i=0;loc_u8_i<NB_MAX_MULTI_CANAUX;loc_u8_i++)
	{
		if(loc_ps_config1->s_wifi.pu16_multi_canal_radio[loc_u8_i] != loc_ps_config2->s_wifi.pu16_multi_canal_radio[loc_u8_i])
		{
			loc_u8_return = TRUE;
		}
	}
	

	return loc_u8_return;
}/*u8DiffConfigFrequence*/

//=====================================================================================
// Fonction		: u8DiffConfigModeSecuWifi
// Entrees		: <loc_ps_config1> config n°1 à comparer (courante)
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config sécurité (Wifi) en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigModeSecuWifi(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod loc_u8_return = FALSE; //INIT

	if(loc_ps_config1->s_wifi.u8_mode_securite_wifi != loc_ps_config2->s_wifi.u8_mode_securite_wifi)
	{
		loc_u8_return = TRUE;
	}
	
	switch(loc_ps_config1->s_wifi.u8_mode_securite_wifi)
	{
		case MODE_SECURITE_WIFI_AUCUN:
			break;
		case MODE_SECURITE_WIFI_WEP:
			break;
		case MODE_SECURITE_WIFI_WPA:
		case MODE_SECURITE_WIFI_WPA_TKIP:
		case MODE_SECURITE_WIFI_WPA_AES:
		case MODE_SECURITE_WIFI_WPA2:
		case MODE_SECURITE_WIFI_WPA2_TKIP:
		case MODE_SECURITE_WIFI_WPA2_AES:
			if((loc_ps_config1->s_wifi.s_wpa_security.u8_authentification != loc_ps_config2->s_wifi.s_wpa_security.u8_authentification)||
			   (loc_ps_config1->s_wifi.s_wpa_security.u32_gp_key_update_interval != loc_ps_config2->s_wifi.s_wpa_security.u32_gp_key_update_interval)||  
			   (loc_ps_config1->s_wifi.s_wpa_security.u8_wpa_key_type != loc_ps_config2->s_wifi.s_wpa_security.u8_wpa_key_type)||
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_pre_shared_key, loc_ps_config2->s_wifi.s_wpa_security.ps8_pre_shared_key)) ||
			   (loc_ps_config1->s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip != loc_ps_config2->s_wifi.s_wpa_security.s_server_radius.u32_radius_adresse_ip)||
			   (loc_ps_config1->s_wifi.s_wpa_security.s_server_radius.u16_radius_port != loc_ps_config2->s_wifi.s_wpa_security.s_server_radius.u16_radius_port)||
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared, loc_ps_config2->s_wifi.s_wpa_security.s_server_radius.ps8_radius_shared)) ||
			   (loc_ps_config1->s_wifi.s_wpa_security.u32_eap_reauth_period != loc_ps_config2->s_wifi.s_wpa_security.u32_eap_reauth_period)||
			   (loc_ps_config1->s_wifi.s_wpa_security.u8_eap_method != loc_ps_config2->s_wifi.s_wpa_security.u8_eap_method)||
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_identity, loc_ps_config2->s_wifi.s_wpa_security.ps8_identity)) ||
#if PARAMETERS_RADIUS_NOT_USED
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_user_name, loc_ps_config2->s_wifi.s_wpa_security.ps8_user_name)) ||
#endif											
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_user_password, loc_ps_config2->s_wifi.s_wpa_security.ps8_user_password)) ||
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_file_certificat_authority, loc_ps_config2->s_wifi.s_wpa_security.ps8_file_certificat_authority)) ||
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_file_certificat_client, loc_ps_config2->s_wifi.s_wpa_security.ps8_file_certificat_client)) ||
			   (0 != strcmp(loc_ps_config1->s_wifi.s_wpa_security.ps8_private_key_password, loc_ps_config2->s_wifi.s_wpa_security.ps8_private_key_password)) ||
			   (TRUE == u8DiffConfigFrequence(loc_ps_config1, loc_ps_config2)) ||
			   (0 != strcmp(loc_ps_config1->s_wifi.ps8_ssid_primary, loc_ps_config2->s_wifi.ps8_ssid_primary))||
			   (loc_ps_config1->s_wifi.u8_dual_ssid != loc_ps_config2->s_wifi.u8_dual_ssid)||
			   (0 != strcmp(loc_ps_config1->s_wifi.ps8_ssid_secondary, loc_ps_config2->s_wifi.ps8_ssid_secondary))
			  )
			{
				loc_u8_return = TRUE;
			}
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8DiffConfigModeSecuWifi*/

//d: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//=====================================================================================
// Fonction		: u8ImposeInitConfigWifi
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: nouvelle config (si TRUE), sinon FALSE
// Auteur		: CM - 10/05/2011 -
// Description	: impose configuration au démarrage (config wifi)
//=====================================================================================
u8sod u8ImposeInitConfigWifi(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

//d: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
	if(TRUE == u8TestSetConfigDefaut(IDXCFG_WIFI)) //CONDITION: ordre de passer en configuration par défaut
	{
		loc_ps_config->s_wifi = S_CONFIG_EQUIPEMENT_DEFAUT.s_wifi; //forcer configuration (au démarrage)
		ClearSetConfigDefaut(IDXCFG_WIFI); //on acquitte
		loc_u8_resultat = TRUE;	//nouvelle config
	}
//f: BE061 10/05/2011 - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).

	return loc_u8_resultat;
}/*u8ImposeInitConfigWifi*/
//f: BE061 10/05/2011 - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut

//=====================================================================================
// Fonction		: u8IsMode80211ag
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode est 802.11a ou 802.11g
//=====================================================================================
u8sod u8IsMode80211ag(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11G:
		case MODE_WIFI_802_11A:
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211ag*/

//=====================================================================================
// Fonction		: u8IsMode80211b
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode est 802.11b
//=====================================================================================
u8sod u8IsMode80211b(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11B:
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211b*/

//=====================================================================================
// Fonction		: u8IsMode80211n
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode est 802.11n
//=====================================================================================
u8sod u8IsMode80211n(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	if((TRUE == u8IsMode80211nHT20(loc_u8_mode_802_11x))||
	   (TRUE == u8IsMode80211nHT40(loc_u8_mode_802_11x))
	  )
	{
		loc_u8_return = TRUE;
	}

	return loc_u8_return;
}/*u8IsMode80211n*/

//=====================================================================================
// Fonction		: u8IsMode80211nHT20
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 14/01/2010 -
// Description	: Test si configuration du mode est 802.11nHT20
//=====================================================================================
u8sod u8IsMode80211nHT20(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11NGHT20:
		case MODE_WIFI_802_11NAHT20:
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211nHT20*/

//=====================================================================================
// Fonction		: u8IsMode80211nHT40
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 16/12/2010 -
// Description	: Test si configuration du mode est 802.11nHT40
//=====================================================================================
u8sod u8IsMode80211nHT40(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11NGHT40PLUS:
		case MODE_WIFI_802_11NGHT40MINUS:
		case MODE_WIFI_802_11NGHT40:
		case MODE_WIFI_802_11NAHT40PLUS:
		case MODE_WIFI_802_11NAHT40MINUS:
		case MODE_WIFI_802_11NAHT40:
		case MODE_WIFI_802_11ACHT80: //VuHai FixMe
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211nHT40*/

//=====================================================================================
// Fonction		: u8IsMode80211ng
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: VuHai - 13/05/2014 -
// Description	: Test si configuration du mode est 802.11ng
//=====================================================================================
u8sod u8IsMode80211ng(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11NGHT20:
		case MODE_WIFI_802_11NGHT40PLUS:
		case MODE_WIFI_802_11NGHT40MINUS:
		case MODE_WIFI_802_11NGHT40:
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211ng*/

//=====================================================================================
// Fonction		: u8IsMode80211na
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: VuHai - 13/05/2014 -
// Description	: Test si configuration du mode est 802.11na
//=====================================================================================
u8sod u8IsMode80211na(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11NAHT20:
		case MODE_WIFI_802_11NAHT40PLUS:
		case MODE_WIFI_802_11NAHT40MINUS:
		case MODE_WIFI_802_11NAHT40:
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211na*/

//=====================================================================================
// Fonction		: u8IsMode80211ac
// Entrees		: <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: VuHai - 23/05/2014 -
// Description	: Test si configuration du mode est 802.11ac
//=====================================================================================
u8sod u8IsMode80211ac(u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_return; 

	loc_u8_return = FALSE; //INIT

	switch(loc_u8_mode_802_11x)
	{
		case MODE_WIFI_802_11ACHT20:
		case MODE_WIFI_802_11ACHT40:
		case MODE_WIFI_802_11ACHT80:
			loc_u8_return = TRUE;
			break;
		default:
			break;
	}

	return loc_u8_return;
}/*u8IsMode80211ac*/

//=====================================================================================
// Fonction		: u8IsMode80211Valid_ForAntennaTX
// Entrees		: <loc_u8_mode_802_11x> : mode
//				: <loc_u8_nb_antenne_tx> : nombre d'antennes TX
// Sortie		: <loc_u8_return> TRUE si mode ok ou FALSE sinon 
// Auteur		: CM - 08/10/2010 -
// Description	: Test si configuration du mode 802.11 est valide en fonction de l'antenne configurée
//=====================================================================================
u8sod u8IsMode80211Valid_ForAntennaTX(u8sod loc_u8_mode_802_11x, u8sod loc_u8_nb_antenne_tx)
{
	u8sod loc_u8_return; 

	loc_u8_return = TRUE; //INIT

#ifdef _WRM100_N_SELECT
	if((TRUE == u8IsMode80211ag(loc_u8_mode_802_11x))||
	   (TRUE == u8IsMode80211b(loc_u8_mode_802_11x))
	  )
	{
		if(N_SELECT_ANTENNE_1 != loc_u8_nb_antenne_tx)
		{
			loc_u8_return = FALSE;
		}
	}
#endif

	return loc_u8_return;
}/*u8IsMode80211Valid_ForAntennaTX*/

#ifdef _WRM100_ABG_SELECT
//=====================================================================================
// Fonction		: u8Test_ABG_ConfigDataRate
// Entrees		: <loc_u8_data_rate> : debit
//				  <loc_u8_mode_802_11x> : mode
// Sortie		: <loc_u8_resultat> TRUE si ok ou FALSE sinon 
// Auteur		: CM - 14/01/2011 -
// Description	: Test si configuration du débit valide (WRM100_ABG)
//=====================================================================================
u8sod u8Test_ABG_ConfigDataRate(u8sod loc_u8_data_rate, u8sod loc_u8_mode_802_11x)
{
	u8sod loc_u8_resultat; 

	loc_u8_resultat = TRUE; //INIT

	if((loc_u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)&&
	   (loc_u8_data_rate < NB_MAX_DATA_RATE)
	  )
	{
		//test fonction du mode
		if(((T_TB_VAL.pt_definition_rate[loc_u8_data_rate].u8_mode80211_valid & M80211_VALID_11AG)&&(TRUE == u8IsMode80211ag(loc_u8_mode_802_11x)))||
		   ((T_TB_VAL.pt_definition_rate[loc_u8_data_rate].u8_mode80211_valid & M80211_VALID_11B)&&(TRUE == u8IsMode80211b(loc_u8_mode_802_11x)))
		  )
		{
			;//OK
		}
		else
		{
			MACRO_PRINTF(("u8Test_ABG_ConfigDataRate: data_rate KO 1) :%d pour mode_802_11x=%d\n",
						  loc_u8_data_rate,
						 loc_u8_mode_802_11x));
			loc_u8_resultat = FALSE;
		}
	}
	else
	{
		MACRO_PRINTF(("u8Test_ABG_ConfigDataRate: data_rate KO 2) :%d pour mode_802_11x=%d \n",
					  loc_u8_data_rate,
					  loc_u8_mode_802_11x));
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;		
}/*u8Test_ABG_ConfigDataRate*/
#endif

#ifdef _WRM100_N_SELECT
//=====================================================================================
// Fonction		: u8Test_N_ConfigDataRate
// Entrees		: <loc_u8_data_rate> : debit
//				  <loc_u8_mode_802_11x> : mode
//				: <loc_u8_nb_antennes_tx> : nombre d'antennes TX
// Sortie		: <loc_u8_resultat> TRUE si ok ou FALSE sinon 
// Auteur		: CM - 14/01/2011 -
// Description	: Test si configuration du débit valide (WRM100_N)
//=====================================================================================
u8sod u8Test_N_ConfigDataRate(u8sod loc_u8_data_rate, u8sod loc_u8_mode_802_11x, u8sod loc_u8_nb_antennes_tx)
{
	u8sod loc_u8_resultat; 

	loc_u8_resultat = TRUE; //INIT

	if((loc_u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)&&
	   (loc_u8_data_rate < NB_MAX_DATA_RATE)&&
	   (loc_u8_nb_antennes_tx < NB_MAX_N_SELECT_ANTENNES)
	  )
	{
		//test fonction du mode
		if(((T_TB_VAL.pt_definition_rate[loc_u8_data_rate].u8_mode80211_valid & M80211_VALID_11AG)&&(TRUE == u8IsMode80211ag(loc_u8_mode_802_11x)))||
		   ((T_TB_VAL.pt_definition_rate[loc_u8_data_rate].u8_mode80211_valid & M80211_VALID_11B)&&(TRUE == u8IsMode80211b(loc_u8_mode_802_11x)))||
		   ((T_TB_VAL.pt_definition_rate[loc_u8_data_rate].u8_mode80211_valid & M80211_VALID_11N)&&(TRUE == u8IsMode80211n(loc_u8_mode_802_11x)))||
		   ((T_TB_VAL.pt_definition_rate[loc_u8_data_rate].u8_mode80211_valid & M80211_VALID_11AC)&&(TRUE == u8IsMode80211ac(loc_u8_mode_802_11x)))
		  )
		{
			if(TRUE == u8IsMode80211nHT20(loc_u8_mode_802_11x))
			{
				switch(loc_u8_data_rate)
				{
					case DATA_RATE_AUTOMATIC:
					case DATA_RATE_MCS0:
					case DATA_RATE_MCS1:
					case DATA_RATE_MCS2:
					case DATA_RATE_MCS3:
					case DATA_RATE_MCS4:
					case DATA_RATE_MCS5:
					case DATA_RATE_MCS6:
					case DATA_RATE_MCS7:
					case DATA_RATE_MCS8://Add by VuHai from 8to 23
					case DATA_RATE_MCS9:
					case DATA_RATE_MCS10:
					case DATA_RATE_MCS11:
					case DATA_RATE_MCS12:
					case DATA_RATE_MCS13:
					case DATA_RATE_MCS14:
					case DATA_RATE_MCS15:
					case DATA_RATE_MCS16:
					case DATA_RATE_MCS17:
					case DATA_RATE_MCS18:
					case DATA_RATE_MCS19:
					case DATA_RATE_MCS20:
					case DATA_RATE_MCS21:
					case DATA_RATE_MCS22:
					case DATA_RATE_MCS23:		
						break;
					default:
						MACRO_PRINTF(("u8Test_N_ConfigDataRate: data_rate KO 0) :%d avec mode_802_11x=%d\n",
									  loc_u8_data_rate,
									  loc_u8_mode_802_11x));
						loc_u8_resultat = FALSE;
						break;
				}
			}
			if(TRUE == u8IsMode80211nHT40(loc_u8_mode_802_11x))
			{
				switch(loc_u8_data_rate)
				{
					case DATA_RATE_AUTOMATIC:
						break;
					case DATA_RATE_MCS0:
					case DATA_RATE_MCS1:
					case DATA_RATE_MCS2:
					case DATA_RATE_MCS3:
					case DATA_RATE_MCS4:
					case DATA_RATE_MCS5:
					case DATA_RATE_MCS6:
					case DATA_RATE_MCS7:
						break;
					case DATA_RATE_MCS8:
					case DATA_RATE_MCS9:
					case DATA_RATE_MCS10:
					case DATA_RATE_MCS11:
					case DATA_RATE_MCS12:
					case DATA_RATE_MCS13:
					case DATA_RATE_MCS14:
					case DATA_RATE_MCS15:
						if(N_SELECT_ANTENNE_1 == loc_u8_nb_antennes_tx)
						{
							MACRO_PRINTF(("u8Test_N_ConfigDataRate: data_rate KO 1) :%d avec mode_802_11x=%d et nb_antennes_tx=%d\n",
										  loc_u8_data_rate,
										  loc_u8_mode_802_11x,
										  loc_u8_nb_antennes_tx));
							loc_u8_resultat = FALSE;
						}
						break;
					case DATA_RATE_MCS16:
					case DATA_RATE_MCS17:
					case DATA_RATE_MCS18:
					case DATA_RATE_MCS19:
					case DATA_RATE_MCS20:
					case DATA_RATE_MCS21:
					case DATA_RATE_MCS22:
					case DATA_RATE_MCS23:
						if((N_SELECT_ANTENNE_1 == loc_u8_nb_antennes_tx)||(N_SELECT_ANTENNES_1_ET_2==loc_u8_nb_antennes_tx))
						{
							MACRO_PRINTF(("u8Test_N_ConfigDataRate: data_rate KO 1) :%d avec mode_802_11x=%d et nb_antennes_tx=%d\n",
										  loc_u8_data_rate,
										  loc_u8_mode_802_11x,
										  loc_u8_nb_antennes_tx));
							loc_u8_resultat = FALSE;
						}
						break;
					default:
						break;
				}
			}
			if(TRUE == u8IsMode80211ac(loc_u8_mode_802_11x))
			{
				switch(loc_u8_data_rate)
				{
					case DATA_RATE_AUTOMATIC:
						break;
					case DATA_RATE_NSS1_MCS0:
					case DATA_RATE_NSS1_MCS1:
					case DATA_RATE_NSS1_MCS2:
					case DATA_RATE_NSS1_MCS3:
					case DATA_RATE_NSS1_MCS4:
					case DATA_RATE_NSS1_MCS5:
					case DATA_RATE_NSS1_MCS6:
					case DATA_RATE_NSS1_MCS7:
					case DATA_RATE_NSS1_MCS8:
					case DATA_RATE_NSS1_MCS9:
						break;
				
					case DATA_RATE_NSS2_MCS0:
					case DATA_RATE_NSS2_MCS1:
					case DATA_RATE_NSS2_MCS2:
					case DATA_RATE_NSS2_MCS3:
					case DATA_RATE_NSS2_MCS4:
					case DATA_RATE_NSS2_MCS5:
					case DATA_RATE_NSS2_MCS6:
					case DATA_RATE_NSS2_MCS7:
					case DATA_RATE_NSS2_MCS8:
					case DATA_RATE_NSS2_MCS9:
						if(N_SELECT_ANTENNE_1 == loc_u8_nb_antennes_tx)
						{
							MACRO_PRINTF(("u8Test_N_ConfigDataRate: data_rate KO 1) :%d avec mode_802_11x=%d et nb_antennes_tx=%d\n",
								loc_u8_data_rate,
								loc_u8_mode_802_11x,
								loc_u8_nb_antennes_tx));
							loc_u8_resultat = FALSE;
						}
						break;
					case DATA_RATE_NSS3_MCS0:
					case DATA_RATE_NSS3_MCS1:
					case DATA_RATE_NSS3_MCS2:
					case DATA_RATE_NSS3_MCS3:
					case DATA_RATE_NSS3_MCS4:
					case DATA_RATE_NSS3_MCS5:
					case DATA_RATE_NSS3_MCS6:
					case DATA_RATE_NSS3_MCS7:
					case DATA_RATE_NSS3_MCS8:
					case DATA_RATE_NSS3_MCS9:
						if((N_SELECT_ANTENNE_1 == loc_u8_nb_antennes_tx)||(N_SELECT_ANTENNES_1_ET_2==loc_u8_nb_antennes_tx))
						{
							MACRO_PRINTF(("u8Test_N_ConfigDataRate: data_rate KO 1) :%d avec mode_802_11x=%d et nb_antennes_tx=%d\n",
								loc_u8_data_rate,
								loc_u8_mode_802_11x,
								loc_u8_nb_antennes_tx));
							loc_u8_resultat = FALSE;
						}
						break;
					default:
						break;
				}
			}
		}
		else
		{
			MACRO_PRINTF(("u8Test_N_ConfigDataRate: u8_data_rate KO 2) :%d avec u8_mode_802_11x=%d\n",
						loc_u8_data_rate,
						loc_u8_mode_802_11x));
			loc_u8_resultat = FALSE;
		}
	}
	else
	{
		MACRO_PRINTF(("u8Test_N_ConfigDataRate: data_rate KO 3) :%d avec mode_802_11x=%d et nb_antennes_tx=%d\n",
					  loc_u8_data_rate,
					  loc_u8_mode_802_11x,
					  loc_u8_nb_antennes_tx));
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}/*u8Test_N_ConfigDataRate*/
#endif

//=====================================================================================
// Fonction		: u8TestCfg_N_AckTimeout
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 28/28/2009 -
// Description	: Test des données Wifi ack timeout (Driver-N) de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestCfg_N_AckTimeout(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT
	
	if(TRUE == u8IsMode80211nHT40(loc_ps_config->s_wifi.u8_mode_802_11x))
	{
		if((WF_N_ACK_TIMEOUT_MIN <= loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout)&&
		   (loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout <= WF_N_ACK_TIMEOUT_11NHT40_MAX)
		  )
		{
			; //OK
		}
		else			
		{
			MACRO_PRINTF(("u8TestCfg_N_AckTimeout: u16_protcl_N_ACK_timeout KO :%d et u8_mode_802_11x=%d \n",
						  loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout,
						  loc_ps_config->s_wifi.u8_mode_802_11x));
			loc_u8_resultat = FALSE;
		}
	}
	else //CONDITION: autres modes
	{
		if((WF_N_ACK_TIMEOUT_MIN <= loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout)&&
		   (loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout <= WF_N_ACK_TIMEOUT_11OTHER_MAX)
		  )
		{
			; //OK
		}
		else			
		{
			MACRO_PRINTF(("u8TestCfg_N_AckTimeout: u16_protcl_N_ACK_timeout KO :%d et u8_mode_802_11x=%d \n",
						  loc_ps_config->s_wifi.u16_protcl_N_ACK_timeout,
						  loc_ps_config->s_wifi.u8_mode_802_11x));
			loc_u8_resultat = FALSE;
		}
	}

	return loc_u8_resultat;
}/*u8TestCfg_N_AckTimeout*/

//=====================================================================================
// Fonction		: u8GetNbStream
// Entrees		: <loc_u8_ant_N_selection> : config d'antenne
// Sortie		: <loc_u8_nb_stream> : nombre de stream associe à la config 
// Auteur		: CM - 08/10/2010 -
// Description	: Détermine le nombre de stream en fonction de la configuration d'antenne
//=====================================================================================
u8sod u8GetNbStream(u8sod loc_u8_ant_N_selection)
{
	u8sod loc_u8_nb_stream; 

	loc_u8_nb_stream = ZERO_STREAM; //INIT

	switch(loc_u8_ant_N_selection)
	{
		case N_SELECT_ANTENNE_1:
			loc_u8_nb_stream = UN_STREAM;
			break;
		case N_SELECT_ANTENNES_1_ET_2:
			loc_u8_nb_stream = DEUX_STREAM;
			break;
		case N_SELECT_ANTENNES_1_ET_2_ET_3:
			loc_u8_nb_stream = TROIS_STREAM;
			break;
		default:
			break;
	}

	return loc_u8_nb_stream;
}/*u8GetNbStream*/




//***************************************************************************
//**************** PROCEDURES CONFIGURATION ROUTING
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigRouting
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Lecture de la configuration Routing du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_ROUTING, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigRouting*/

//=====================================================================================
// Fonction		: u8EditConfigRouting
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/09/2009 -
// Description	: Ecriture de la configuration Routing dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_ROUTING, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigRouting*/

//=====================================================================================
// Fonction		: ImposeConfigRoutingSiIncoherente
// Entrees		: <loc_ps_config> : config qu'il faut mettre à jour
// Sortie		: rien
// Auteur		: CM - 24/09/2008 -
// Description	: Impose certains paramètres si config Routing incohérente
//=====================================================================================
void ImposeConfigRoutingSiIncoherente(S_STRUCT_CONFIGURATION *loc_ps_config)
{
}/*ImposeConfigRoutingSiIncoherente*/

//=====================================================================================
// Fonction		: u8TestConfigRouting
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test des données Routing de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_i;
	u8sod	loc_u8_cpt;
	u16sod	loc_u16_i;

	loc_u8_resultat = TRUE;	//INIT
	loc_u8_cpt = 0;	//INIT

	//table de routage statique
	for(loc_u16_i=0;loc_u16_i<NB_MAX_ROUTES_IP_STATIC;loc_u16_i++)
	{
		if((FALSE != loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)&&
		   (TRUE != loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
		  )
		{
			MACRO_PRINTF(("u8TestConfigRouting: ps_route_ip_static[%d].u8_enabled KO :%d \n",
						  loc_u16_i,
						  loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled));
			loc_u8_resultat = FALSE;
		}
		else
		{
			if(TRUE == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
			{
				if(FALSE == u8TestConfigRouteStatic(&loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i]))
				{
					MACRO_PRINTF(("u8TestConfigRouting: ps_route_ip_static[%d] u32_destination_ip=0x%08X, u32_destination_mask=0x%08X u32_gateway_ip=0x%08X KO \n",
								  loc_u16_i,
								  loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_ip,
								  loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_mask,
								  loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_gateway_ip));
					loc_u8_resultat = FALSE;
				}
			}
		}
	}

	//Table des politiques de routage
	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(FALSE == u8TestConfigRoutePolitic(&loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i]))
		{
			MACRO_PRINTF(("u8TestConfigRouting: ps_route_policy[%d]  KO \n",
						  loc_u16_i));
			loc_u8_resultat = FALSE;
		}
	}

	//paramètres routage dynamique RIPv2
	if((FALSE != loc_ps_config->s_ip_routing.u8_ripv2_activation)&&
	   (TRUE != loc_ps_config->s_ip_routing.u8_ripv2_activation)
	  )
	{
		MACRO_PRINTF(("u8TestConfigRouting: u8_ripv2_activation KO :%d \n",
					  loc_ps_config->s_ip_routing.u8_ripv2_activation));
		loc_u8_resultat = FALSE;
	}
	
	for(loc_u8_i=0;loc_u8_i<NB_MAX_RIP_INTERFACES;loc_u8_i++)
	{
		if((FALSE != loc_ps_config->s_ip_routing.pu8_rip_interface_used[loc_u8_i])&&
		   (TRUE != loc_ps_config->s_ip_routing.pu8_rip_interface_used[loc_u8_i])
		  )
		{
			MACRO_PRINTF(("u8TestConfigRouting: pu8_rip_interface_used[%d] KO :%d \n",
						  loc_u8_i,
						  loc_ps_config->s_ip_routing.pu8_rip_interface_used[loc_u8_i]));
			loc_u8_resultat = FALSE;
		}
	}

	if(TRUE == loc_ps_config->s_ip_routing.u8_ripv2_activation)
	{
		//si routage activé, il faut au moins une interface sélectionnée
		loc_u8_cpt = 0;	//RAZ
		for(loc_u8_i=0;loc_u8_i<NB_MAX_RIP_INTERFACES;loc_u8_i++)
		{
			if (TRUE == loc_ps_config->s_ip_routing.pu8_rip_interface_used[loc_u8_i])
			{
				loc_u8_cpt++;
			}
		}

		if(0==loc_u8_cpt) //CONDITION: aucune interface sélectionnée pour RIP
		{
			MACRO_PRINTF(("u8TestConfigRouting: Aucune interface RIP sélectionnée pu8_rip_interface_used[all]=FALSE KO \n"));
			loc_u8_resultat = FALSE;
		}
	}
	
	if(loc_ps_config->s_ip_routing.u8_rip_authentification >= NB_MAX_RIP_AUTHENTICATION)
	{
		MACRO_PRINTF(("u8TestConfigRouting: u8_rip_authentification KO :%d \n",
					  loc_ps_config->s_ip_routing.u8_rip_authentification));
		loc_u8_resultat = FALSE;
	}

	if((strlen(loc_ps_config->s_ip_routing.ps8_rip_password) > TAILLE_MAX_RIP_PASSWORD)||
	   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_ip_routing.ps8_rip_password))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigRouting: ps8_rip_password KO  \n"));
	}
	

	return loc_u8_resultat;
}/*u8TestConfigRouting*/

//=====================================================================================
// Fonction		: CopyConfigRouting
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Copier configuration Routage SRC==>DST
//=====================================================================================
void CopyConfigRouting(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_ip_routing = loc_ps_cfg_src->s_ip_routing;

}/*CopyConfigRouting*/

//=====================================================================================
// Fonction		: u8DiffConfigRouting
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 06/11/2009 -
// Description	: Vérifie si les config routing en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigRouting(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_ip_routing.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_ip_routing.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_IP_ROUTING)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_IP_ROUTING)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigRouting*/





//***************************************************************************
//**************** PROCEDURES CONFIGURATION NAT
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigNAT
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Lecture de la configuration NAT du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_NAT, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigNAT*/

//=====================================================================================
// Fonction		: u8EditConfigNAT
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Ecriture de la configuration NAT dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_NAT, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigNAT*/

//=====================================================================================
// Fonction		: u8TestConfigNAT
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Test de la configuration NAT de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_k;

	loc_u8_resultat = TRUE;	//INIT

	if((FALSE != loc_ps_config->s_nat.u8_nat_activation)&&
	   (TRUE != loc_ps_config->s_nat.u8_nat_activation)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigNAT: s_nat.u8_nat_activation KO : %d  \n",
					  loc_ps_config->s_nat.u8_nat_activation));
	}

	

	//table des règles NAT Port forwarding
	for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
	{
		if((FALSE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable)&&
		   (TRUE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable)
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_port_forwarding[%d].u8_enable=%d KO  \n",
						  loc_u16_i,
						  loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable));
		}

		if(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole >= NB_MAX_NAT_PROTOCOLES)
		{
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_port_forwarding[%d].u8_protocole=%d KO \n",
						  loc_u16_i,
						  loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole));
			loc_u8_resultat = FALSE;
		}

		if((strlen(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].ps8_commentaire) > TAILLE_MAX_COMMENT_NAT_PFWD) ||
		   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].ps8_commentaire))
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_port_forwarding[%d].ps8_commentaire KO  \n",
						 loc_u16_i));
		}

		if((PORT_UDP_TCP_MIN <= loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port)&&
		   (loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port <= PORT_UDP_TCP_MAX)
		  )
		{
			; //OK
		}
		else
		{
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_port_forwarding[%d].u16_private_port=%d KO  \n",
						  loc_u16_i,
						  loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port));
			loc_u8_resultat = FALSE;
		}

		if((PORT_UDP_TCP_MIN <= loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port)&&
		   (loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port <= PORT_UDP_TCP_MAX)
		  )
		{
			; //OK
		}
		else
		{
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_port_forwarding[%d].u16_public_port=%d KO  \n",
						  loc_u16_i,
						  loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port));
			loc_u8_resultat = FALSE;
		}
		
		//On vérifie que le port publique est unique (meme si la règle n'est pas permise)
		if(NAT_PROTOCOLE_NON_SELECTIONNE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)//CONDITION: règle présente
		{
			for(loc_u16_k=0;loc_u16_k<NB_MAX_RULES_PORT_FORWARDING;loc_u16_k++)
			{
				if(loc_u16_i != loc_u16_k)
				{
				   if(NAT_PROTOCOLE_NON_SELECTIONNE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_k].u8_protocole)
				   {
					   if((loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port == loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_k].u16_public_port) &&
						  (0 != (loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole & loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_k].u8_protocole))
						 )//CONDITION: Port publique identique pour un protocole identique (astuce & binaire permet de gérer le cas où le protocole est udp et tcp)
					   {
						   loc_u8_resultat = FALSE;
						   MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_port_forwarding[%d] identique à s_nat.ps_rule_port_forwarding[%d] KO  \n",
										 loc_u16_i,loc_u16_k));
					   }
				   }
				}
			}
		}
	}

	//table des règles NAT Mapping d'adresses
	for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
	{
		if((FALSE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)&&
		   (TRUE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_mapping_adresse[%d].u8_enable=%d KO  \n",
						  loc_u16_i,
						  loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable));
		}


		if((strlen(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].ps8_commentaire) > TAILLE_MAX_COMMENT_NAT_MPADR) ||
		   (FALSE == u8TestConfigChaineValide(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].ps8_commentaire))
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_mapping_adresse[%d].ps8_commentaire KO  \n",
						  loc_u16_i));
		}

		//On vérifie que l'adresse alias est unique (meme si la règle n'est pas permise)
		if(ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip) //CONDITION: règle présente
		{
			for(loc_u16_k=0;loc_u16_k<NB_MAX_NAT_ALIAS_IP;loc_u16_k++)
			{
				if(loc_u16_i != loc_u16_k)
				{
					if(ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_k].u32_public_alias_ip)
					{
						if(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_k].u32_public_alias_ip)
						{
							loc_u8_resultat = FALSE;
							MACRO_PRINTF(("u8TestConfigNAT: s_nat.ps_rule_mapping_adresse[%d] identique à s_nat.ps_rule_mapping_adresse[%d]  KO  \n",
										  loc_u16_i, loc_u16_k));
						}
					}
				}
			}
		}
	}
	
	return loc_u8_resultat;
}/*u8TestConfigNAT*/

//=====================================================================================
// Fonction		: CopyConfigNAT
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 10/02/2010 -
// Description	: Copier configuration NAT SRC==>DST
//=====================================================================================
void CopyConfigNAT(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_nat = loc_ps_cfg_src->s_nat;

}/*CopyConfigNAT*/

//=====================================================================================
// Fonction		: u8DiffConfigNAT
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 10/02/2010 -
// Description	: Vérifie si les config NAT en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigNAT(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_nat.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_nat.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_NAT)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_NAT)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigNAT*/

//=====================================================================================
// Fonction		: u8TestNAT_Fonctionnelle
// Entrees		: <loc_ps_config> config de l'équipement à tester
//				: <loc_u32_adr_ip_public_default> : adresse IP publique par défaut
//				: <loc_u32_mask_ip_public_default> : adresse IP publique par défaut
// Sortie		: <loc_u8_return> TRUE si OK ou FALSE sinon 
// Auteur		: CM - 15/02/2010 -
// Description	: Test si la configuration NAT est fonctionnelle
//=====================================================================================
u8sod u8TestNAT_Fonctionnelle(S_STRUCT_CONFIGURATION * loc_ps_config, u32sod loc_u32_adr_ip_public_default, u32sod loc_u32_mask_ip_public_default)
{
	u8sod loc_u8_return;
	u16sod loc_u16_i;

	loc_u8_return = TRUE;//INIT

	if(TRUE == loc_ps_config->s_nat.u8_nat_activation)
	{
		//table des règles NAT Port forwarding
		for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
		{
			if((NAT_PROTOCOLE_NON_SELECTIONNE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)&&
			   (TRUE == loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable)
			  )//CONDITION:
			{
				//On vérifie que l'adresse IP privée de chaque règle n'est pas dans le sous réseau WLAN (sinon erreur)
				if((loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip & loc_u32_mask_ip_public_default) ==
				   (loc_u32_adr_ip_public_default & loc_u32_mask_ip_public_default)
				  )
				{
					MACRO_PRINTF(("u8TestNAT_Fonctionnelle: ps_rule_port_forwarding[%d] Erreur 1  \n", loc_u16_i));
					loc_u8_return = FALSE;
				}
				//On vérifie que l'adresse IP privée est différent de l'adresse IP sur le LAN (sinon erreur)
				if(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip == loc_ps_config->s_gene.u32_lan_adresse_ip)
				{
					MACRO_PRINTF(("u8TestNAT_Fonctionnelle: ps_rule_port_forwarding[%d] Erreur 2  \n", loc_u16_i));
					loc_u8_return = FALSE;
				}
			}
		}

		if(MODE_IP_STATIQUE == loc_ps_config->s_gene.u8_wlan_mode_ip)
		{
			for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
			{
				if((ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)&&
				   (TRUE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable)
				   )
				{
					//On vérifie que l'adresse IP publique de chaque règle est dans le sous réseau WLAN (sinon erreur)
					if((loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip & loc_u32_mask_ip_public_default) !=
					   (loc_ps_config->s_gene.u32_wlan_adresse_ip & loc_u32_mask_ip_public_default)
					  )
					{
						MACRO_PRINTF(("u8TestNAT_Fonctionnelle: ps_rule_mapping_adresse[%d] Erreur 1  \n", loc_u16_i));
						loc_u8_return = FALSE;
					}
					//On vérifie que l'adresse IP publique de chaque règle est différente de l'adresse IP publique par défaut (sinon erreur)
					if(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip == loc_u32_adr_ip_public_default)
					{
						MACRO_PRINTF(("u8TestNAT_Fonctionnelle: ps_rule_mapping_adresse[%d] Erreur 2  \n", loc_u16_i));
						loc_u8_return = FALSE;
					}

					//On vérifie que l'adresse IP privée de chaque règle n'est pas dans le sous réseau WLAN (sinon erreur)
					if((loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip & loc_u32_mask_ip_public_default) ==
					   (loc_u32_adr_ip_public_default & loc_u32_mask_ip_public_default)
					  )
					{
						MACRO_PRINTF(("u8TestNAT_Fonctionnelle: ps_rule_mapping_adresse[%d] Erreur 3  \n", loc_u16_i));
						loc_u8_return = FALSE;
					}

					//On vérifie que l'adresse IP privée est différent de l'adresse IP sur le LAN (sinon erreur)
					if(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip == loc_ps_config->s_gene.u32_lan_adresse_ip)
					{
						MACRO_PRINTF(("u8TestNAT_Fonctionnelle: ps_rule_mapping_adresse[%d] Erreur 4  \n", loc_u16_i));
						loc_u8_return = FALSE;
					}
				}
			}
		}
	}
	
	return loc_u8_return;
}/*u8TestNAT_Fonctionnelle*/





//***************************************************************************
//**************** PROCEDURES CONFIGURATION MULTICAST
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigMulticast
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Lecture de la configuration Multicast du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_MULTICAST, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigMulticast*/

//=====================================================================================
// Fonction		: u8EditConfigMulticast
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Ecriture de la configuration Multicast dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_MULTICAST, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigMulticast*/

//=====================================================================================
// Fonction		: u8TestConfigMulticast
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test de la configuration Multicast de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = TRUE;	//INIT

	if((FALSE != loc_ps_config->s_multicast.u8_proxy_igmp_activation)&&
	   (TRUE != loc_ps_config->s_multicast.u8_proxy_igmp_activation)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigMulticast: s_multicast.u8_proxy_igmp_activation KO : %d  \n",
					  loc_ps_config->s_multicast.u8_proxy_igmp_activation));
	}



	//table des sources multicast
	for(loc_u16_i=0;loc_u16_i<NB_MAX_SRC_MULTICAST;loc_u16_i++)
	{
		if((FALSE != loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable)&&
		   (TRUE != loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigMulticast: s_multicast.ps_source_multicast[%d].u8_enable=%d KO  \n",
						  loc_u16_i,
						  loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable));
		}

		if(TRUE == loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
		{
			if(FALSE == u8TestConfigIP_Net(loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_adresse_reseau, loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_masque_reseau))
			{
				MACRO_PRINTF(("u8TestConfigMulticast: s_multicast.ps_source_multicast[%d] u32_adresse_reseau:0x%08X u32_masque_reseau:0x%08X KO  \n",
							  loc_u16_i,
							  loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_adresse_reseau,
							  loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_masque_reseau));
			}
		}
	}

	return loc_u8_resultat;
}/*u8TestConfigMulticast*/

//=====================================================================================
// Fonction		: CopyConfigMulticast
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 30/03/2010 -
// Description	: Copier configuration Multicast SRC==>DST
//=====================================================================================
void CopyConfigMulticast(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_multicast = loc_ps_cfg_src->s_multicast;

}/*CopyConfigMulticast*/

//=====================================================================================
// Fonction		: u8DiffConfigMulticast
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 30/03/2010 -
// Description	: Vérifie si les config Multicast en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigMulticast(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_multicast.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_multicast.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_MULTICAST)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_MULTICAST)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigMulticast*/






//***************************************************************************
//**************** PROCEDURES CONFIGURATION DU TABLEAU DES EVENEMENTS
//***************************************************************************
//=====================================================================================
// Fonction		: u8FillConfigTabEvt
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 26/02/2010 -
// Description	: Lecture de la configuration du tableau des évènements du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_TABEVT, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigTabEvt*/

//=====================================================================================
// Fonction		: u8EditConfigTabEvt
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 26/02/2010 -
// Description	: Ecriture de la configuration du tableau des évènements dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_TABEVT, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigTabEvt*/

//=====================================================================================
// Fonction		: u8TestConfigTabEvt
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 26/02/2010 -
// Description	: Test de la configuration du tableau des évènements de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = TRUE;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		if(loc_ps_config->s_tabevt.s_event[loc_u16_i].u8_niveau_gravite >= NIV_GRAVITE_MAX)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigTabEvt: s_tabevt.s_event[%d].u8_niveau_gravite KO %d\n",
						  loc_u16_i,
						  loc_ps_config->s_tabevt.s_event[loc_u16_i].u8_niveau_gravite));
			loc_u16_i = NB_MAX_EVENEMENTS+1;	//on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestConfigTabEvt*/

//=====================================================================================
// Fonction		: CopyConfigTabEvt
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 26/02/2010 -
// Description	: Copier configuration du tableau des évènements  SRC==>DST
//=====================================================================================
void CopyConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_tabevt = loc_ps_cfg_src->s_tabevt;

}/*CopyConfigTabEvt*/

//=====================================================================================
// Fonction		: u8DiffConfigTabEvt
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 26/02/2010 -
// Description	: Vérifie si les config du tableau des évènements  en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigTabEvt(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_tabevt.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_tabevt.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_TABLE_EVT)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_TABLE_EVT)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigTabEvt*/

//=====================================================================================
// Fonction		: u8ImposeInitConfigTabEvt
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: nouvelle config (si TRUE), sinon FALSE
// Auteur		: CM - 25/03/2011 -
// Description	: impose configuration au démarrage (config du tableau des évènements)
//=====================================================================================
u8sod u8ImposeInitConfigTabEvt(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;
	S_STRUCT_CFG_EVENT *loc_ps_cfg_evt;

	loc_u8_resultat = FALSE;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{
			loc_ps_cfg_evt = &loc_ps_config->s_tabevt.s_event[loc_u16_indEvt];
			switch(loc_u16_indEvt)
			{
				case EVT013_CONNEXION_STATION:
				case EVT014_DECONNEXION_STATION:
				case EVT015_CONNEXION_ACCESS_POINT:
				case EVT016_DECONNEXION_ACCESS_POINT:
					//Si ce bit est positionné, alors on dévalide l'envoi des traps et jdb
					if(TRUE == u8GetEventAction(loc_ps_cfg_evt->u16_action, ACTION_EVT_PHASE_INIT))
					{
						ResetEventAction(&loc_ps_cfg_evt->u16_action, ACTION_EVT_JDB);
						ResetEventAction(&loc_ps_cfg_evt->u16_action, ACTION_EVT_TRAP);
						ResetEventAction(&loc_ps_cfg_evt->u16_action, ACTION_EVT_PHASE_INIT);
						loc_u8_resultat = TRUE;	//nouvelle config
					}
					break;
				default:
					break;
			}
		}
	}

	return loc_u8_resultat;
}/*u8ImposeInitConfigTabEvt*/

//=====================================================================================
// Fonction		: u8GetEventAction
// Entrees		: <loc_u16_valeur_action>
//				  <loc_u8_index_action>
// Sortie		: <loc_i_resultat> : TRUE valide / FALSE non valide
// Auteur		: CM - 29/06/2007 -
// Description	: retourne si action de l'evt valide
//=====================================================================================
u8sod u8GetEventAction(u16sod loc_u16_valeur_action, u8sod	loc_u8_index_action)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(0 != (loc_u16_valeur_action & (0x0001 << loc_u8_index_action)))//CONDITION:action valide	
	{
		loc_u8_resultat = TRUE;
	}	

	return(loc_u8_resultat);		
}/*u8GetEventAction*/

//=====================================================================================
// Fonction		: SetEventAction
// Entrees		: <loc_u16_valeur_action< : valeur action de l'évt à modifier
//				  <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 29/06/2007 -
// Description	: Force action de l'evt valide
//=====================================================================================
void SetEventAction(u16sod *loc_pu16_valeur_action, u8sod	loc_u8_index_action)
{

	*loc_pu16_valeur_action |= (0x0001 << loc_u8_index_action);

}/*SetEventAction*/

//=====================================================================================
// Fonction		: ResetEventAction
// Entrees		: <loc_u16_valeur_action< : valeur action de l'évt à modifier
//				  <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 29/06/2007 -
// Description	: Reset action de l'evt valide
//=====================================================================================
void ResetEventAction(u16sod *loc_pu16_valeur_action, u8sod	loc_u8_index_action)
{

	*loc_pu16_valeur_action &= (u16sod)(~(0x0001 << loc_u8_index_action));

}/*ResetEventAction*/

//=====================================================================================
// Fonction		: SetAllEventsAction
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 26/02/2010
// Description	: Force tous les évènements à une action
//=====================================================================================
void SetAllEventsAction(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_index_action)
{
	u8sod	loc_u8_type_evt_valide;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{

			loc_u8_type_evt_valide = FALSE;	//INIT
			switch(loc_u8_index_action)
			{
				case ACTION_EVT_SYNTHESE_1:
				case ACTION_EVT_VALIDE:
					if(TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					{
						loc_u8_type_evt_valide = TRUE;
					}
					break;
				case ACTION_EVT_JDB:
				case ACTION_EVT_FILTRE_JDB:
					if((TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
					   (TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					  )
					{
						loc_u8_type_evt_valide = TRUE;
					}
					break;
				case ACTION_EVT_TRAP:
					if((TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
					   (TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
					   (TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					  )
					{
						loc_u8_type_evt_valide = TRUE;
					}
					break;
				default:
					break;
			}

			if(TRUE == loc_u8_type_evt_valide) //CONDITION: type evt valide
			{
				SetEventAction(&loc_ps_config->s_tabevt.s_event[loc_u16_indEvt].u16_action, loc_u8_index_action);
			}
		}
	}

}/*SetAllEventsAction*/

//=====================================================================================
// Fonction		: ResetAllEventsAction
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u8_index_action>
// Sortie		: rien
// Auteur		: CM - 26/02/2010
// Description	: Reset tous les évènements à une action
//=====================================================================================
void ResetAllEventsAction(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_index_action)
{
	u8sod	loc_u8_type_evt_valide;
	u16sod	loc_u16_i;
	u16sod	loc_u16_indEvt;

	for(loc_u16_i=0;loc_u16_i<NB_MAX_EVENEMENTS;loc_u16_i++)
	{
		loc_u16_indEvt = loc_u16_i;
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))//CONDITION: Evt OK
		{

			loc_u8_type_evt_valide = FALSE;	//INIT
			switch(loc_u8_index_action)
			{
				case ACTION_EVT_SYNTHESE_1:
				case ACTION_EVT_VALIDE:
					if(TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					{
						loc_u8_type_evt_valide = TRUE;
					}
					break;
				case ACTION_EVT_JDB:
				case ACTION_EVT_FILTRE_JDB:
					if((TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
					   (TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					  )
					{
						loc_u8_type_evt_valide = TRUE;
					}
					break;
				case ACTION_EVT_TRAP:
					if((TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
					   (TYPE_EVT_INFO == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)||
					   (TYPE_EVT_GENERIQUE == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
					  )
					{
						loc_u8_type_evt_valide = TRUE;
					}
					break;
				default:
					break;
			}

			if(TRUE == loc_u8_type_evt_valide) //CONDITION: type evt valide
			{
				ResetEventAction(&loc_ps_config->s_tabevt.s_event[loc_u16_indEvt].u16_action, loc_u8_index_action);
			}
		}
	}

}/*ResetAllEventsAction*/





//***************************************************************************
//**************** PROCEDURES CONFIGURATION HANDOFF
//***************************************************************************

//=====================================================================================
// Fonction		: u8FillConfigHandoff
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 15/09/2010 -
// Description	: Lecture de la configuration Handoff du fichier défini par son index
//=====================================================================================
u8sod u8FillConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8FillConfigFile(IDXCFG_HANDOFF, loc_ps_config);

	return loc_u8_resultat;
}/*u8FillConfigHandoff*/

//=====================================================================================
// Fonction		: u8EditConfigHandoff
// Entrees		: <loc_u8_idx_cfgfile> : index du fichier de configuration
//				  <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 15/09/2010 -
// Description	: Ecriture de la configuration Handoff dans le fichier défini par son index
//=====================================================================================
u8sod u8EditConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8EditConfigFile(IDXCFG_HANDOFF, loc_ps_config);

	return loc_u8_resultat;
}/*u8EditConfigHandoff*/

//=====================================================================================
// Fonction		: ImposeConfigHandoffSiIncoherente
// Entrees		: <loc_ps_config> : config qu'il faut mettre à jour
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Impose certains paramètres si config Handoff incohérente
//=====================================================================================
void ImposeConfigHandoffSiIncoherente(S_STRUCT_CONFIGURATION *loc_ps_config)
{
}/*ImposeConfigHandoffSiIncoherente*/

//=====================================================================================
// Fonction		: u8TestConfigHandoff
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/09/2010 -
// Description	: Test des données Handoff de la structure S_STRUCT_CONFIGURATION
//=====================================================================================
u8sod u8TestConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	//Paramètres de configuration
	if(loc_ps_config->s_handoff.u8_scanning_mode >= NB_MAX_HO_MODES_SCANNING)
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u8_scanning_mode KO :%d \n",
					  loc_ps_config->s_handoff.u8_scanning_mode));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == T_TB_VAL.pu8_flag_affichage_mode_scanning_handoff[loc_ps_config->s_handoff.u8_scanning_mode])
		{
			MACRO_PRINTF(("u8TestConfigHandoff: u8_scanning_mode KO :%d via flag\n",
						  loc_ps_config->s_handoff.u8_scanning_mode));
		}
	}


	if((HO_TIME_BETW_HANDOFF_MIN <= loc_ps_config->s_handoff.u16_time_between_hand_off)&&
	   (loc_ps_config->s_handoff.u16_time_between_hand_off <= HO_TIME_BETW_HANDOFF_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u16_time_between_hand_off KO :%d \n",
					  loc_ps_config->s_handoff.u16_time_between_hand_off));
		loc_u8_resultat = FALSE;
	}
	
	if((FALSE != loc_ps_config->s_handoff.u8_bgscan_activation)&&
	   (TRUE != loc_ps_config->s_handoff.u8_bgscan_activation)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigHandoff: s_handoff.u8_bgscan_activation=%d KO  \n",
					  loc_ps_config->s_handoff.u8_bgscan_activation));
	}

	if((HO_BGSCAN_PERIOD_MIN <= loc_ps_config->s_handoff.u16_bgscan_recurrence_period)&&
	   (loc_ps_config->s_handoff.u16_bgscan_recurrence_period <= HO_BGSCAN_PERIOD_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u16_bgscan_recurrence_period KO :%d \n",
					  loc_ps_config->s_handoff.u16_bgscan_recurrence_period));
		loc_u8_resultat = FALSE;
	}

	if((SEUIL_RX_MIN <= loc_ps_config->s_handoff.s32_fgscan_detection_level)&&
	   (loc_ps_config->s_handoff.s32_fgscan_detection_level <= SEUIL_RX_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: s32_fgscan_detection_level=%d KO) :%d \n",
					  loc_ps_config->s_handoff.s32_fgscan_detection_level));
		loc_u8_resultat = FALSE;
	}

	if((SEUIL_RX_MIN <= loc_ps_config->s_handoff.s32_bgscan_detection_level)&&
	   (loc_ps_config->s_handoff.s32_bgscan_detection_level <= SEUIL_RX_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: s32_bgscan_detection_level=%d KO) :%d \n",
					  loc_ps_config->s_handoff.s32_bgscan_detection_level));
		loc_u8_resultat = FALSE;
	}

	if((HO_FGSCAN_BEACON_MISSED_THRESH_MIN <= loc_ps_config->s_handoff.u16_fgscan_beacon_missed_threshold)&&
	   (loc_ps_config->s_handoff.u16_fgscan_beacon_missed_threshold <= HO_FGSCAN_BEACON_MISSED_THRESH_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u16_fgscan_beacon_missed_threshold KO :%d \n",
					  loc_ps_config->s_handoff.u16_fgscan_beacon_missed_threshold));
		loc_u8_resultat = FALSE;
	}
	
	if((SEUIL_RX_MIN <= loc_ps_config->s_handoff.s32_iso_detection_level)&&
	   (loc_ps_config->s_handoff.s32_iso_detection_level <= SEUIL_RX_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: s32_iso_detection_level=%d KO) :%d \n",
					  loc_ps_config->s_handoff.s32_iso_detection_level));
		loc_u8_resultat = FALSE;
	}

	if((HO_ISO_RELEVANT_BEACON_THRESH_MIN <= loc_ps_config->s_handoff.u16_iso_relevant_beacon_threshold)&&
	   (loc_ps_config->s_handoff.u16_iso_relevant_beacon_threshold <= HO_ISO_RELEVANT_BEACON_THRESH_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u16_iso_relevant_beacon_threshold KO :%d \n",
					  loc_ps_config->s_handoff.u16_iso_relevant_beacon_threshold));
		loc_u8_resultat = FALSE;
	}

	if(loc_ps_config->s_handoff.u8_type_filtrage_rssi >= NB_MAX_TYPES_FILTRAGE_RSSI)
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u8_type_filtrage_rssi KO :%d \n",
					  loc_ps_config->s_handoff.u8_type_filtrage_rssi));
		loc_u8_resultat = FALSE;
	}


	if((WF_BEACON_PERIOD_MIN <= loc_ps_config->s_handoff.u16_time_between_2_beacon)&&
	   (loc_ps_config->s_handoff.u16_time_between_2_beacon <= WF_BEACON_PERIOD_MAX)
	  )
	{
		;//OK
	}
	else
	{
		MACRO_PRINTF(("u8TestConfigHandoff: u16_time_between_2_beacon KO :%d \n",
					  loc_ps_config->s_handoff.u16_time_between_2_beacon));
		loc_u8_resultat = FALSE;
	}
	
	return loc_u8_resultat;
}/*u8TestConfigHandoff*/

//=====================================================================================
// Fonction		: CopyConfigHandoff
// Entrees		: <loc_ps_cfg_src<: structure concernant la configuration source
//				  <loc_ps_cfg_dst<: structure concernant la configuration destination
// Sortie		: rien
// Auteur		: CM - 15/09/2010 -
// Description	: Copier configuration Handoff SRC==>DST
//=====================================================================================
void CopyConfigHandoff(S_STRUCT_CONFIGURATION *loc_ps_cfg_src, S_STRUCT_CONFIGURATION *loc_ps_cfg_dst)
{
	loc_ps_cfg_dst->s_handoff = loc_ps_cfg_src->s_handoff;

}/*CopyConfigHandoff*/

//=====================================================================================
// Fonction		: u8DiffConfigHandoff
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 15/09/2010 -
// Description	: Vérifie si les config Handoff en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigHandoff(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->s_handoff.u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->s_handoff.u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CFG_HANDOFF)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CFG_HANDOFF)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigHandoff*/



//***************************************************************************
//**************** PROCEDURES DIVERSES
//***************************************************************************

//=====================================================================================
// Fonction		: u8AddRouteStatic
// Entrees		: <loc_ps_config< : config de l'équipement
//				  <loc_ps_route<: route à ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Ajout d'une route statique
//=====================================================================================
u8sod u8AddRouteStatic(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_IP_ROUTE_STATIC *loc_ps_route)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_k;
	u8sod	loc_u8_add_route;

	loc_u8_resultat = FALSE;	//INIT
	loc_u8_add_route = TRUE;	//INIT


	//On vérifie qu'il y a une route disponible
	for(loc_u16_i=0;loc_u16_i<NB_MAX_ROUTES_IP_STATIC;loc_u16_i++)
	{
		if(FALSE == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
		{
			//On a une route disponible
			//maintenant on vérifie que la route n'a pas été déjà enregistrée
			for(loc_u16_k=0;loc_u16_k<NB_MAX_ROUTES_IP_STATIC;loc_u16_k++)
			{
				if(loc_u16_k != loc_u16_i)
				{
					if(((loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_k].u32_destination_ip & loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_k].u32_destination_mask) ==
					    (loc_ps_route->u32_destination_ip & loc_ps_route->u32_destination_mask)) &&
					   (TRUE == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_k].u8_enabled)
					  )
					{
						loc_u8_add_route = FALSE;
					}
				}
			}

			if(TRUE == loc_u8_add_route)//CONDITION: On peut ajouter la route
			{
				loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled = TRUE;
				loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_ip = loc_ps_route->u32_destination_ip;
				loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_destination_mask = loc_ps_route->u32_destination_mask;
				loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u32_gateway_ip = loc_ps_route->u32_gateway_ip;
				loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_interface = loc_ps_route->u8_interface;
				loc_u8_resultat = TRUE;	//AJOUTER
				loc_u16_i = NB_MAX_ROUTES_IP_STATIC + 1; //on sort
			}
		}
	}

	return loc_u8_resultat;
}/*u8AddRouteStatic*/

//=====================================================================================
// Fonction		: u8TestConfigRouteStatic
// Entrees		: <loc_ps_route< : route IP
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 16/10/2009 -
// Description	: Test ces paramètres IP d'une route
//=====================================================================================
u8sod u8TestConfigRouteStatic(S_STRUCT_IP_ROUTE_STATIC *loc_ps_route)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if(loc_ps_route->u8_interface >= NB_MAX_INTERFACES)
	{
		MACRO_PRINTF(("u8TestConfigRouteStatic: u8_interface KO :%d \n",
					  loc_ps_route->u8_interface));
		loc_u8_resultat = FALSE;
	}
	
	if(		(ADRESSE_IP_NULLE == loc_ps_route->u32_destination_ip)
		||	(MASK_RESEAU_SUR_32 == loc_ps_route->u32_destination_ip)
	  )//CONDITION: adresse IP KO
	{
		MACRO_PRINTF(("u8TestConfigRouteStatic: u32_destination_ip KO :0x%08X \n",
					  loc_ps_route->u32_destination_ip));
		loc_u8_resultat = FALSE;
	}

	if(ADRESSE_IP_NULLE == loc_ps_route->u32_destination_mask)//CONDITION: masque sous-réseau KO
	{
		MACRO_PRINTF(("u8TestConfigRouteStatic: u32_destination_mask KO :0x%08X \n",
					  loc_ps_route->u32_destination_mask));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == u8TestConfigMask(loc_ps_route->u32_destination_mask))
		{
			MACRO_PRINTF(("u8TestConfigRouteStatic: u32_destination_mask KO :0x%08X \n",
						  loc_ps_route->u32_destination_mask));
		}
	}

	if(MASK_RESEAU_SUR_32 != loc_ps_route->u32_destination_mask) //CONDITION: route vers un sous-réseau
	{
		//On vérifie que l'adresse IP et le mask définissent un sous-reseau non nul
		if(0 != (loc_ps_route->u32_destination_ip & (u32sod)(~loc_ps_route->u32_destination_mask))) //CONDITION: route vers sous-réseau invalide
		{
			MACRO_PRINTF(("u8TestConfigRouteStatic: NETMASK u32_destination_ip=0x%08X, u32_destination_mask=0x%08X KO \n",
						  loc_ps_route->u32_destination_ip,
						  loc_ps_route->u32_destination_mask));
			loc_u8_resultat = FALSE;
		}
	}

	if(INTERFACE_AUTOMATIQUE == loc_ps_route->u8_interface)
	{
		if(MASK_RESEAU_SUR_32 == loc_ps_route->u32_gateway_ip)
		{
			MACRO_PRINTF(("u8TestConfigRouteStatic: u32_gateway_ip :0x%08X \n",
						  loc_ps_route->u32_gateway_ip));
			loc_u8_resultat = FALSE;
		}
	}

	return loc_u8_resultat;
}/*u8TestConfigRouteStatic*/

//=====================================================================================
// Fonction		: u8TestRouteStaticFree
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 20/06/2006 -
// Description	: Test si une route est disponible
//=====================================================================================
u8sod u8TestRouteStaticFree(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = FALSE;	//INIT


	//table de routage statique
	for(loc_u16_i=0;loc_u16_i<NB_MAX_ROUTES_IP_STATIC;loc_u16_i++)
	{
		if(FALSE == loc_ps_config->s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
		{
			loc_u8_resultat = TRUE;	//AJOUTER
			loc_u16_i = NB_MAX_ROUTES_IP_STATIC + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestRouteStaticFree*/

//=====================================================================================
// Fonction		: u8AddRoutePolitic
// Entrees		: <loc_ps_config< : config de l'équipement
//				  <loc_ps_route<: route à ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Ajout d'une politique de routage
//=====================================================================================
u8sod u8AddRoutePolitic(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_ROUTE_POLICY *loc_ps_route)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = FALSE;	//INIT

	//On vérifie qu'il y a une route disponible
	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(FALSE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled)
		{
			//On a une route disponible
			loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i] = *loc_ps_route;
			loc_u8_resultat = TRUE;	//AJOUTER
			loc_u16_i = NB_MAX_POLICY_ROUTING + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8AddRoutePolitic*/

//=====================================================================================
// Fonction		: u8TestConfigRoutePolitic
// Entrees		: <loc_ps_route< : route IP
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Test ces paramètres IP d'une route
//=====================================================================================
u8sod u8TestConfigRoutePolitic(S_STRUCT_ROUTE_POLICY *loc_ps_route)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_k;

	loc_u8_resultat = TRUE;	//INIT

	if((FALSE != loc_ps_route->u8_enabled)&&
	   (TRUE != loc_ps_route->u8_enabled)
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigRoutePolitic: u8_enabled = %d KO  \n",
					  loc_ps_route->u8_enabled));
	}			   

	if((strlen(loc_ps_route->ps8_policy_name) > LG_NOM_CONSTRUCTEUR) ||
	   (FALSE == u8TestConfigChaineValide(loc_ps_route->ps8_policy_name))
	  )
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8TestConfigRoutePolitic: ps8_policy_name KO  \n"));
	}

	for(loc_u16_k=0;loc_u16_k<NB_MAX_CRITERIA_POLICY;loc_u16_k++)
	{
		if((FALSE != loc_ps_route->pu8_valid_critere[loc_u16_k])&&
		   (TRUE != loc_ps_route->pu8_valid_critere[loc_u16_k])
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: pu8_valid_critere[%d] = %d KO  \n",
						  loc_u16_k,
						  loc_ps_route->pu8_valid_critere[loc_u16_k]));
		}			   
		if((FALSE != loc_ps_route->pu8_not_critere[loc_u16_k])&&
		   (TRUE != loc_ps_route->pu8_not_critere[loc_u16_k])
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: pu8_not_critere[%d] = %d KO  \n",
						  loc_u16_k,
						  loc_ps_route->pu8_not_critere[loc_u16_k]));
		}			   
	}

	//On vérifie les valeurs des critères si validés
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_SRC_IP])
	{
		if(loc_ps_route->u32_critere_src_ip_start > loc_ps_route->u32_critere_src_ip_end)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: u32_critere_src_i start=0x%08X end=0x%08X  KO  \n",
						  loc_ps_route->u32_critere_src_ip_start,
						  loc_ps_route->u32_critere_src_ip_end));
		}
	}
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_DST_IP])
	{
		if(loc_ps_route->u32_critere_dst_ip_start > loc_ps_route->u32_critere_dst_ip_end)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: critere_dst_ip_end start=0x%08X end=0x%08X  KO  \n",
						  loc_ps_route->u32_critere_dst_ip_start,
						  loc_ps_route->u32_critere_dst_ip_end));
		}
	}
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])
	{
		if(loc_ps_route->u16_critere_len_packet_min > loc_ps_route->u16_critere_len_packet_max)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: u16_critere_len_packet min=%d max=%d  KO  \n",
						  loc_ps_route->u16_critere_len_packet_min,
						  loc_ps_route->u16_critere_len_packet_max));
		}
	}
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])
	{
		if(loc_ps_route->u8_critere_ip_protocol >= NB_MAX_POLICYROUTE_PROTOCOLES)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: u8_critere_ip_protocol=%d  KO  \n",
						  loc_ps_route->u8_critere_ip_protocol));
		}
	}
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])
	{
		if(loc_ps_route->u16_critere_src_port_start > loc_ps_route->u16_critere_src_port_end)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: critere_src_port start=%d end=%d  KO  \n",
						  loc_ps_route->u16_critere_src_port_start,
						  loc_ps_route->u16_critere_src_port_end));
		}
	}
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_DST_PORT])
	{
		if(loc_ps_route->u16_critere_dst_port_start > loc_ps_route->u16_critere_dst_port_end)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: critere_src_port start=%d end=%d  KO  \n",
						  loc_ps_route->u16_critere_dst_port_start,
						  loc_ps_route->u16_critere_dst_port_end));
		}
	}
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])
	{
		if(loc_ps_route->u8_critere_class_selector >= NB_MAX_CLASSSELECTOR)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: u8_critere_class_selector=%d  KO  \n",
						  loc_ps_route->u8_critere_class_selector));
		}
	}

	for(loc_u16_k=0;loc_u16_k<NB_MAX_ACTIONS_POLICY;loc_u16_k++)
	{
		if((FALSE != loc_ps_route->pu8_valid_action[loc_u16_k])&&
		   (TRUE != loc_ps_route->pu8_valid_action[loc_u16_k])
		  )
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: pu8_valid_action[%d] = %d KO  \n",
						  loc_u16_k,
						  loc_ps_route->pu8_valid_action[loc_u16_k]));
		}			   
	}

	if(TRUE == loc_ps_route->pu8_valid_action[ACTIONPOLICY_GATEWAY])
	{
		if(ADRESSE_IP_NULLE == loc_ps_route->u32_new_gateway)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: u32_new_gateway=0x%08X  KO  \n",
						  loc_ps_route->u32_new_gateway));
		}
	}

	if(TRUE == loc_ps_route->pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])
	{
		if(loc_ps_route->u8_new_class_selector >= NB_MAX_CLASSSELECTOR)
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8TestConfigRoutePolitic: u8_new_class_selector=%d  KO  \n",
						  loc_ps_route->u8_new_class_selector));
		}
	}

	return loc_u8_resultat;
}/*u8TestConfigRoutePolitic*/

//=====================================================================================
// Fonction		: u8TestRoutePoliticFree
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Test si une route est disponible
//=====================================================================================
u8sod u8TestRoutePoliticFree(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = FALSE;	//INIT

	//table de routage
	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(FALSE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled)
		{
			loc_u8_resultat = TRUE;	//AJOUTER
			loc_u16_i = NB_MAX_POLICY_ROUTING + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestRoutePoliticFree*/

//=====================================================================================
// Fonction		: u8TestAllRoutePoliticFree
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 23/04/2010 -
// Description	: Test si toutes les routes sont diponibles
//=====================================================================================
u8sod u8TestAllRoutePoliticFree(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = TRUE;	//INIT

	//table de routage
	for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
	{
		if(TRUE == loc_ps_config->s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled)
		{
			loc_u8_resultat = FALSE;
			loc_u16_i = NB_MAX_POLICY_ROUTING + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestAllRoutePoliticFree*/

//=====================================================================================
// Fonction		: u8TestPolicyCriteriaPort_Allowed
// Entrees		: <loc_ps_route< : route IP
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 23/04/2010 -
// Description	: Test si les critères de port (source / destination) sont autorisés (de la route politique)
//=====================================================================================
u8sod u8TestPolicyCriteriaPort_Allowed(S_STRUCT_ROUTE_POLICY *loc_ps_route)
{
	u8sod	loc_u8_resultat;
	
	loc_u8_resultat = FALSE;	//INIT

	if((TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])&&
	   (FALSE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL])&&
	   ((POLICYROUTE_PROTOCOLE_UDP == loc_ps_route->u8_critere_ip_protocol)||
		(POLICYROUTE_PROTOCOLE_TCP == loc_ps_route->u8_critere_ip_protocol)
	   )
	  )//CONDITION: critère protocole validé (ET non inversé) ET (protocole TCP ou UDP)
	{
		loc_u8_resultat = TRUE;
	}

	return loc_u8_resultat;
}/*u8TestPolicyCriteriaPort_Allowed*/

//=====================================================================================
// Fonction		: u8AddRuleNatPortFwdFree
// Entrees		: <loc_ps_config< : config de l'équipement
//				  <loc_ps_rule_port_fwd<: règle à ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Ajout d'une règle NAT Port forwarding
//=====================================================================================
u8sod u8AddRuleNatPortFwdFree(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_NAT_RULE_PORT_FORWARDING *loc_ps_rule_port_fwd)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_k;
	u8sod	loc_u8_add_rule;

	loc_u8_resultat = FALSE;	//INIT
	loc_u8_add_rule = TRUE;	//INIT

	//On vérifie qu'il y a une règle disponible
	for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
	{
		if(NAT_PROTOCOLE_NON_SELECTIONNE == loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
		{
			//On a une règle disponible
			//maintenant on vérifie que la règle n'a pas été déjà enregistrée
			for(loc_u16_k=0;loc_u16_k<NB_MAX_RULES_PORT_FORWARDING;loc_u16_k++)
			{
				if(loc_u16_k != loc_u16_i)
				{
					if((loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip == loc_ps_rule_port_fwd->u32_private_ip) &&
					   (loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port == loc_ps_rule_port_fwd->u16_private_port) &&
					   (loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole == loc_ps_rule_port_fwd->u8_protocole) &&
					   (loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port == loc_ps_rule_port_fwd->u16_public_port) &&
					   (NAT_PROTOCOLE_NON_SELECTIONNE != loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
					  )
					{
						loc_u8_add_rule = FALSE;
					}
				}
			}

			if(TRUE == loc_u8_add_rule)//CONDITION: On peut ajouter la règle
			{
				loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_enable = loc_ps_rule_port_fwd->u8_enable;
				loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u32_private_ip = loc_ps_rule_port_fwd->u32_private_ip;
				loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_private_port = loc_ps_rule_port_fwd->u16_private_port;
				loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole = loc_ps_rule_port_fwd->u8_protocole;
				loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u16_public_port = loc_ps_rule_port_fwd->u16_public_port;
				strcpy(loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].ps8_commentaire, loc_ps_rule_port_fwd->ps8_commentaire);
				loc_u8_resultat = TRUE;	//AJOUTER
				loc_u16_i = NB_MAX_RULES_PORT_FORWARDING + 1; //on sort
			}
		}
	}

	return loc_u8_resultat;
}/*u8AddRuleNatPortFwdFree*/

//=====================================================================================
// Fonction		: u8TestRuleNatPortFwdFree
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Test si une règle Port forwarding est disponible
//=====================================================================================
u8sod u8TestRuleNatPortFwdFree(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = FALSE;	//INIT

	//table des règles NAT Port forwarding
	for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
	{
		if(NAT_PROTOCOLE_NON_SELECTIONNE == loc_ps_config->s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
		{
			loc_u8_resultat = TRUE;	//AJOUTER
			loc_u16_i = NB_MAX_RULES_PORT_FORWARDING + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestRuleNatPortFwdFree*/

//=====================================================================================
// Fonction		: u8AddRuleNatMapAdrFree
// Entrees		: <loc_ps_config< : config de l'équipement
//				  <loc_ps_rule_map_adr<: règle à ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Ajout d'une règle NAT Mapping d'adresses
//=====================================================================================
u8sod u8AddRuleNatMapAdrFree(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_NAT_RULE_MAP_ADRESSES *loc_ps_rule_map_adr)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_k;
	u8sod	loc_u8_add_rule;

	loc_u8_resultat = FALSE;	//INIT
	loc_u8_add_rule = TRUE;	//INIT

	//On vérifie qu'il y a une règle disponible
	for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
	{
		if(ADRESSE_IP_NULLE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)
		{
			//On a une règle disponible
			//maintenant on vérifie que la règle n'a pas été déjà enregistrée
			for(loc_u16_k=0;loc_u16_k<NB_MAX_RULES_PORT_FORWARDING;loc_u16_k++)
			{
				if(loc_u16_k != loc_u16_i)
				{
					if((loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip == loc_ps_rule_map_adr->u32_private_ip) &&
					   (loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip == loc_ps_rule_map_adr->u32_public_alias_ip) &&
					   (ADRESSE_IP_NULLE != loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)
					  )
					{
						loc_u8_add_rule = FALSE;
					}
				}
			}

			if(TRUE == loc_u8_add_rule)//CONDITION: On peut ajouter la règle
			{
				loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u8_enable = loc_ps_rule_map_adr->u8_enable;
				loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_private_ip = loc_ps_rule_map_adr->u32_private_ip;
				loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip = loc_ps_rule_map_adr->u32_public_alias_ip;
				strcpy(loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].ps8_commentaire, loc_ps_rule_map_adr->ps8_commentaire);
				loc_u8_resultat = TRUE;	//AJOUTER
				loc_u16_i = NB_MAX_NAT_ALIAS_IP + 1; //on sort
			}
		}
	}

	return loc_u8_resultat;
}/*u8AddRuleNatMapAdrFree*/

//=====================================================================================
// Fonction		: u8TestRuleNatMapAdrFree
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 10/02/2010 -
// Description	: Test si une règle Mapping d'adresses est disponible
//=====================================================================================
u8sod u8TestRuleNatMapAdrFree(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = FALSE;	//INIT

	//table des règles NAT Port forwarding
	for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
	{
		if(ADRESSE_IP_NULLE == loc_ps_config->s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)
		{
			loc_u8_resultat = TRUE;	//AJOUTER
			loc_u16_i = NB_MAX_NAT_ALIAS_IP + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestRuleNatMapAdrFree*/

//=====================================================================================
// Fonction		: u8TestSrcMulticastFree
// Entrees		: <loc_ps_config< : config de l'équipement
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si une source multicast est disponible
//=====================================================================================
u8sod u8TestSrcMulticastFree(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;

	loc_u8_resultat = FALSE;	//INIT

	//table de sources multicast
	for(loc_u16_i=0;loc_u16_i<NB_MAX_SRC_MULTICAST;loc_u16_i++)
	{
		if(FALSE == loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
		{
			loc_u8_resultat = TRUE;	//AJOUTER
			loc_u16_i = NB_MAX_SRC_MULTICAST + 1; //on sort
		}
	}

	return loc_u8_resultat;
}/*u8TestSrcMulticastFree*/

//=====================================================================================
// Fonction		: u8AddSrcMulticastFree
// Entrees		: <loc_ps_config< : config de l'équipement
//				  <loc_ps_src_multicast<: source multicast à ajouter
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Ajout d'une source multicast
//=====================================================================================
u8sod u8AddSrcMulticastFree(S_STRUCT_CONFIGURATION *loc_ps_config, S_STRUCT_SRC_MULTICAST *loc_ps_src_multicast)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_i;
	u16sod	loc_u16_k;
	u8sod	loc_u8_add_src;

	loc_u8_resultat = FALSE;	//INIT
	loc_u8_add_src = TRUE;	//INIT


	//On vérifie qu'il y a une source disponible
	for(loc_u16_i=0;loc_u16_i<NB_MAX_SRC_MULTICAST;loc_u16_i++)
	{
		if(FALSE == loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
		{
			//On a une source disponible
			//maintenant on vérifie que la source n'a pas été déjà enregistrée
			for(loc_u16_k=0;loc_u16_k<NB_MAX_SRC_MULTICAST;loc_u16_k++)
			{
				if(loc_u16_k != loc_u16_i)
				{
					if(((loc_ps_config->s_multicast.ps_source_multicast[loc_u16_k].u32_adresse_reseau & loc_ps_config->s_multicast.ps_source_multicast[loc_u16_k].u32_masque_reseau) ==
						  (loc_ps_src_multicast->u32_adresse_reseau & loc_ps_src_multicast->u32_masque_reseau)) &&
					   (FALSE != loc_ps_config->s_multicast.ps_source_multicast[loc_u16_k].u8_enable)
					  )
					{
						loc_u8_add_src = FALSE;
					}
				}
			}

			if(TRUE == loc_u8_add_src)//CONDITION: On peut ajouter la source
			{
				loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u8_enable = loc_ps_src_multicast->u8_enable;
				loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_adresse_reseau = loc_ps_src_multicast->u32_adresse_reseau;
				loc_ps_config->s_multicast.ps_source_multicast[loc_u16_i].u32_masque_reseau = loc_ps_src_multicast->u32_masque_reseau;
				loc_u8_resultat = TRUE;	//AJOUTER
				loc_u16_i = NB_MAX_SRC_MULTICAST + 1; //on sort
			}
		}
	}

	return loc_u8_resultat;
}/*u8AddSrcMulticastFree*/

//============================================================================
// Fonction		: ps8GetStringIp
// Entrees		: <loc_u32_adresse_ip> : adresse IP
// Sortie		: <loc_ps8_chaine< : chaine à afficher
// Auteur		: CM - 12/07/2007 -
// Description	: convertit un entier en chaine de caratctere 
//                type adresse IP : XXX.YYY.ZZZ.WWW
//                utilise la variable static loc_ps8_chaine[30]
//============================================================================
s8sod* ps8GetStringIp(u32sod loc_u32_adresse_ip)
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
}/*ps8GetStringIp*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Host
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2009 -
// Description	: Test si masque et adresse IP forme une adresse de type HOST
//=====================================================================================
u8sod u8TestConfigIP_Host(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if((ADRESSE_IP_NULLE == loc_u32_adresse_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_adresse_ip)
	  )//CONDITION: adresse IP KO
	{
		MACRO_PRINTF(("u8TestConfigIP_Host: loc_u32_adresse_ip KO :0x%08X \n",
					  loc_u32_adresse_ip));
		loc_u8_resultat = FALSE;
	}

	if((ADRESSE_IP_NULLE == loc_u32_masque_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_masque_ip)
	  )//CONDITION: masque sous-réseau KO
	{
		MACRO_PRINTF(("u8TestConfigIP_Host: loc_u32_masque_ip KO :0x%08X \n",
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == u8TestConfigMask(loc_u32_masque_ip))
		{
			MACRO_PRINTF(("u8TestConfigIP_Host: loc_u32_masque_ip KO :0x%08X \n",
						  loc_u32_masque_ip));
		}
	}

	//On vérifie que l'adresse IP et le mask définissent un sous-reseau non nul
	if(0 == (loc_u32_adresse_ip & loc_u32_masque_ip))
	{
		MACRO_PRINTF(("u8TestConfigIP_Host: loc_u32_adresse_ip=0x%08X, loc_u32_masque_ip=0x%08X KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}

	//  --> vérification que l'adresse IP n'est pas une adresse nulle pour le masque de sous-réseau défini
	if(0 == (loc_u32_adresse_ip & (u32sod)(~loc_u32_masque_ip)))
	{
		MACRO_PRINTF(("u8TestConfigIP_Host: loc_u32_adresse_ip=0x%08X, loc_u32_masque_ip=0x%08X KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}
	//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
	if(MASK_RESEAU_SUR_32 == (loc_u32_adresse_ip | loc_u32_masque_ip))
	{
		MACRO_PRINTF(("u8TestConfigIP_Host: loc_u32_adresse_ip=0x%08X, loc_u32_masque_ip=0x%08X KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}/*u8TestConfigIP_Host*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Net
// Entrees		: <loc_u32_adresse_ip> : adresse IP 
//				: <loc_u32_masque_ip> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si masque et adresse IP forme un adresse de type NETWORK
//=====================================================================================
u8sod u8TestConfigIP_Net(u32sod loc_u32_adresse_ip, u32sod loc_u32_masque_ip)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	if((ADRESSE_IP_NULLE == loc_u32_adresse_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_adresse_ip)
	  )//CONDITION: adresse IP KO
	{
		MACRO_PRINTF(("u8TestConfigIP_Net: loc_u32_adresse_ip KO :0x%08X \n",
					  loc_u32_adresse_ip));
		loc_u8_resultat = FALSE;
	}

	if((ADRESSE_IP_NULLE == loc_u32_masque_ip)||
	   (MASK_RESEAU_SUR_32 == loc_u32_masque_ip)
	  )//CONDITION: masque sous-réseau KO
	{
		MACRO_PRINTF(("u8TestConfigIP_Net: loc_u32_masque_ip KO :0x%08X \n",
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(FALSE == u8TestConfigMask(loc_u32_masque_ip))
		{
			MACRO_PRINTF(("u8TestConfigIP_Net: loc_u32_masque_ip KO :0x%08X \n",
						  loc_u32_masque_ip));
		}
	}

	//On vérifie que l'adresse IP et le mask définissent un sous-reseau non nul
	if(0 == (loc_u32_adresse_ip & loc_u32_masque_ip))
	{
		MACRO_PRINTF(("u8TestConfigIP_Net: loc_u32_adresse_ip=0x%08X, loc_u32_masque_ip=0x%08X KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}

	//  --> vérification que l'adresse IP est une adresse nulle pour le masque de sous-réseau défini
	if(0 != (loc_u32_adresse_ip & (u32sod)(~loc_u32_masque_ip)))
	{
		MACRO_PRINTF(("u8TestConfigIP_Net: loc_u32_adresse_ip=0x%08X, loc_u32_masque_ip=0x%08X KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}
	//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
	if(MASK_RESEAU_SUR_32 == (loc_u32_adresse_ip | loc_u32_masque_ip))
	{
		MACRO_PRINTF(("u8TestConfigIP_Net: loc_u32_adresse_ip=0x%08X, loc_u32_masque_ip=0x%08X KO \n",
					  loc_u32_adresse_ip,
					  loc_u32_masque_ip));
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}/*u8TestConfigIP_Net*/

//=====================================================================================
// Fonction		: u8TestConfigIP_Subnet
// Entrees		: <loc_u32_subnet_ip>	: adresse IP 
//				: <loc_u32_subnet_mask> : masque sous-reseau
//				: <loc_u32_ip_a_tester> : IP à tester
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/02/2010 -
// Description	: Test si l'adresse IP à tester est dans le sous réseau
//=====================================================================================
u8sod u8TestConfigIP_Subnet(u32sod loc_u32_subnet_ip, u32sod loc_u32_subnet_mask, u32sod loc_u32_ip_a_tester)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = TRUE;	//INIT

	//On vérifie que l'adresse IP à tester est dans le meme sous-reseau (définie par IP/mask subnet)
	if((loc_u32_subnet_ip & loc_u32_subnet_mask) != (loc_u32_ip_a_tester & loc_u32_subnet_mask)) //CONDITION: pas de le meme sous-réseau
	{
		MACRO_PRINTF(("u8TestConfigIP_Subnet: loc_u32_subnet_ip=0x%08X, loc_u32_subnet_mask=0x%08X, loc_u32_ip_a_tester=0x%08X KO \n",
					  loc_u32_subnet_ip,
					  loc_u32_subnet_mask,
					  loc_u32_ip_a_tester));
		loc_u8_resultat = FALSE;
	}


	return loc_u8_resultat;
}/*u8TestConfigIP_Subnet*/

//=====================================================================================
// Fonction		: u8TestConfigMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 30/03/2010 -
// Description	: Test si le masque de sous réseau est valide
//=====================================================================================
u8sod u8TestConfigMask(u32sod loc_u32_subnet_mask)
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
				MACRO_PRINTF(("u8TestConfigMask: loc_u32_subnet_mask KO :0x%08X \n",
							  loc_u32_subnet_mask));
			}
		}
		else
		{
			loc_u8_flag_bit_nul = TRUE;
		}
	}

	return loc_u8_resultat;
}/*u8TestConfigMask*/

//=====================================================================================
// Fonction		: u8GetNumberMask
// Entrees		: <loc_u32_subnet_mask> : masque sous-reseau
// Sortie		: <loc_u8_numbermask>  : 
// Auteur		: CM - 30/03/2010 -
// Description	: Retourne la valeur numérique du masque de sous-réseau
//=====================================================================================
u8sod u8GetNumberMask(u32sod loc_u32_subnet_mask)
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
}/*u8GetNumberMask*/

#ifdef _WRM100_ABG_SELECT
//=====================================================================================
// Fonction		: u8Test_ABG_ConfigPowerTx
// Entrees		: <loc_u8_power_tx> : power tx 
//				: <loc_u8_mode_802_11x> : mode 802.11
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 16/10/2009 -
// Description	: Test la valeur power_tx (Driver-ABG)
//=====================================================================================
u8sod u8Test_ABG_ConfigPowerTx(u8sod loc_u8_power_tx, u8sod loc_u8_mode_802_11x)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_powermax;

	loc_u8_resultat = FALSE;	//INIT
	loc_u8_powermax = 0;	//INIT

	if(loc_u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)
	{
		loc_u8_powermax = u8Get_ABG_PowerTxMax(loc_u8_mode_802_11x);
		switch(loc_u8_mode_802_11x)
		{
			case MODE_WIFI_802_11G:
			case MODE_WIFI_802_11B:
				if((POWER_TX_802_11ABG_MIN <= loc_u8_power_tx)&&
				   (loc_u8_power_tx <= loc_u8_powermax)
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11A:
				if((POWER_TX_802_11ABG_MIN <= loc_u8_power_tx)&&
				   (loc_u8_power_tx <= loc_u8_powermax)
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			default:
				break;
		}
	}

	return loc_u8_resultat;
}/*u8Test_ABG_ConfigPowerTx*/

//=====================================================================================
// Fonction		: u8Get_ABG_PowerTxMax
// Entrees		: <loc_u8_mode_802_11x> : mode 802.11
// Sortie		: <loc_u8_powermax>  : puissance max en dBm (valeur
// Auteur		: CM - 15/12/2010 -
// Description	: retourne valeur max de puissance tx pour config donnée (pour Driver-ABG)
//=====================================================================================
u8sod u8Get_ABG_PowerTxMax(u8sod loc_u8_mode_802_11x)
{
	u8sod	loc_u8_powermax;

	loc_u8_powermax = POWER_TX_802_11ABG_MIN; //INIT
	if(loc_u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)
	{
		switch(loc_u8_mode_802_11x)
		{
			case MODE_WIFI_802_11G:
			case MODE_WIFI_802_11B:
				loc_u8_powermax = POWER_TX_802_11BG_MAX;
				break;
			case MODE_WIFI_802_11A:
				loc_u8_powermax = POWER_TX_802_11A_MAX;
				break;
			default:
				break;
		}
	}
	return loc_u8_powermax;
}/*u8Get_ABG_PowerTxMax*/

#endif

#ifdef _WRM100_N_SELECT
//=====================================================================================
// Fonction		: u8Test_N_ConfigPowerTx
// Entrees		: <loc_u8_power_tx> : power tx 
//				: <loc_u8_mode_802_11x> : mode 802.11
//				: <loc_u8_data_rate> : data rate
//				: <loc_u8_nb_antennes_tx> : nombre d'antennes tx
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/12/2010 -
// Description	: Test la valeur power_tx (Driver-N)
//=====================================================================================
u8sod u8Test_N_ConfigPowerTx(u8sod loc_u8_power_tx, u8sod loc_u8_mode_802_11x, u8sod loc_u8_data_rate, u8sod loc_u8_nb_antennes_tx)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_powermax;

	loc_u8_resultat = FALSE;	//INIT
	loc_u8_powermax = 0;	//INIT

	if((loc_u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)&&
	   (loc_u8_data_rate < NB_MAX_DATA_RATE)&&
	   (loc_u8_nb_antennes_tx < NB_MAX_N_SELECT_ANTENNES)
	  )
	{
		loc_u8_powermax = u8Get_N_PowerTxMax(loc_u8_mode_802_11x, loc_u8_data_rate, loc_u8_nb_antennes_tx);
		if((POWER_TX_802_11ABGN_MIN <= loc_u8_power_tx)&&
		   (loc_u8_power_tx <= loc_u8_powermax)
		  )
		{
			loc_u8_resultat = TRUE;
		}
	}

	return loc_u8_resultat;
}/*u8Test_N_ConfigPowerTx*/

//=====================================================================================
// Fonction		: u8Get_N_PowerTxMax
// Entrees		: <loc_u8_mode_802_11x> : mode 802.11
//				: <loc_u8_data_rate> : data rate
//				: <loc_u8_nb_antennes_tx> : nombre d'antennes tx
// Sortie		: <loc_u8_powermax>  : puissance max en dBm (valeur
// Auteur		: CM - 15/12/2010 -
// Description	: retourne valeur max de puissance tx pour config donnée (pour Driver-N)
//					données fonction de la "data-sheet du DNMA-H5" et fonction aussi de la consommation
//=====================================================================================
u8sod u8Get_N_PowerTxMax(u8sod loc_u8_mode_802_11x, u8sod loc_u8_data_rate, u8sod loc_u8_nb_antennes_tx)
{
	u8sod	loc_u8_powermax;

	loc_u8_powermax = POWER_TX_802_11ABGN_MIN;	//INIT

	if((loc_u8_mode_802_11x < NB_MAX_MODES_WIFI_802_11)&&
	   (loc_u8_data_rate < NB_MAX_DATA_RATE)&&
	   (loc_u8_nb_antennes_tx < NB_MAX_N_SELECT_ANTENNES)
	  )
	{
		switch(loc_u8_mode_802_11x)
		{
			case MODE_WIFI_802_11G:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11g[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11B:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11b[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11A:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11a[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11NGHT20:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11nght20[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11NGHT40PLUS:
			case MODE_WIFI_802_11NGHT40MINUS:
			case MODE_WIFI_802_11NGHT40:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11nght40[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11NAHT20:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11naht20[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11NAHT40PLUS:
			case MODE_WIFI_802_11NAHT40MINUS:
			case MODE_WIFI_802_11NAHT40:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11naht40[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11ACHT20:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11acht20[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11ACHT40:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11acht40[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
			case MODE_WIFI_802_11ACHT80:
				loc_u8_powermax = T_TB_VAL.pu8_N_powerTxMax_11acht80[loc_u8_data_rate][loc_u8_nb_antennes_tx];
				break;
				
			default:
				break;
		}
	}

	return loc_u8_powermax;
}/*u8Get_N_PowerTxMax*/
#endif

//=====================================================================================
// Fonction		: u8FillConfigEquipement
// Entrees		: >loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: rien
// Auteur		: CM - 18/11/2009 -
// Description	: Lecture de la configuration (copie dans *loc_ps_config) 
//=====================================================================================
u8sod u8FillConfigEquipement(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_idx_cfgfile;

	loc_u8_resultat = TRUE; //INIT
	
	for(loc_u8_idx_cfgfile=0; loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG; loc_u8_idx_cfgfile++)
	{
		if(FALSE == u8Transfert_FileToStruct(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]))
		{
			loc_u8_resultat = FALSE;
		}
	}
	
	return loc_u8_resultat;
}/*u8FillConfigEquipement*/

//=====================================================================================
// Fonction		: u8EditConfigEquipement
// Entrees		: <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: rien
// Auteur		: CM - 18/11/2009 -
// Description	: Ecriture de la configuration de l'équipement (copie de loc_s_config) 
//=====================================================================================
u8sod u8EditConfigEquipement(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_idx_cfgfile;

	loc_u8_resultat = TRUE; //INIT

	for(loc_u8_idx_cfgfile=0; loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
	{
		if(FALSE == u8EditConfigFile(loc_u8_idx_cfgfile, loc_ps_config))
		{
			loc_u8_resultat = FALSE;
		}
		else
		{
			SignalNewConfig(loc_u8_idx_cfgfile);
		}
	}

	return loc_u8_resultat;
}/*u8EditConfigEquipement*/

//=====================================================================================
// Fonction		: u8TestConfigEquipement
// Entrees		: <loc_ps_config<	: structure concernant la configuration de l'équipement
// Sortie		: rien
// Auteur		: CM - 18/01/2011 -
// Description	: Test de la configuration de l'équipement (copie de loc_s_config) 
//=====================================================================================
u8sod u8TestConfigEquipement(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_idx_cfgfile;

	loc_u8_resultat = TRUE; //INIT

	for(loc_u8_idx_cfgfile=0; loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
	{
		if(FALSE == u8TestConfigFile(loc_u8_idx_cfgfile, loc_ps_config))
		{
			loc_u8_resultat = FALSE;			
		}
	}

	return loc_u8_resultat;
}/*u8TestConfigEquipement*/

//=====================================================================================
// Fonction		: u8DiffConfigEquipement
// Entrees		: <loc_ps_config1> config n°1 à comparer
//				  <loc_ps_config2> config n°2 à comparer
// Sortie		: <loc_u8_return> TRUE si différente ou FALSE sinon 
// Auteur		: CM - 21/01/2011 -
// Description	: Vérifie si les configurations de l'équipement en arguments sont différentes
//=====================================================================================
u8sod u8DiffConfigEquipement(S_STRUCT_CONFIGURATION * loc_ps_config1, S_STRUCT_CONFIGURATION * loc_ps_config2)
{
	u8sod * loc_pu8_conf1;
	u8sod * loc_pu8_conf2;
	u16sod  loc_u16_i;
	u8sod loc_u8_return = FALSE;	//INIT

	loc_pu8_conf1 = (u8sod *)(&loc_ps_config1->u8_start);
	loc_pu8_conf2 = (u8sod *)(&loc_ps_config2->u8_start);

	// On compare les différents champs
	for(loc_u16_i=0; (loc_u16_i < (u16sod)sizeof(S_STRUCT_CONFIGURATION)); loc_u16_i++)
	{
		if(loc_pu8_conf1[loc_u16_i] != loc_pu8_conf2[loc_u16_i]) 
		{
			loc_u8_return = TRUE;
			// on sort de la boucle
			loc_u16_i = (u16sod)sizeof(S_STRUCT_CONFIGURATION)+1; //on sort
		}
	}

	return loc_u8_return;
}/*u8DiffConfigEquipement*/

//=====================================================================================
// Fonction		: PassageConfigDefaut
// Entrees		: <loc_ps_config< : config de l'équipement
//				: <loc_u8_mode> : mode de passage en config/defaut
//							MODE_PASSAGECONFIGDEFAUT_TOTAL
//							MODE_PASSAGECONFIGDEFAUT_SANS_IP
// Sortie		: rien
// Auteur		: CM - 18/11/2009 -
// Description	: passage en config par défaut
//=====================================================================================
void PassageConfigDefaut(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_mode)
{
	switch(loc_u8_mode)
	{
		case MODE_PASSAGECONFIGDEFAUT_TOTAL:
			*loc_ps_config = S_CONFIG_EQUIPEMENT_DEFAUT;
			u8EditConfigEquipement(loc_ps_config);
			break;
		default:
			break;
	}

}/*PassageConfigDefaut*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitBDD_Config
// Entrees		: <loc_ps_config< : configuration de l'équipement
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Initialisation de la base de données de la configuration
//=====================================================================================
void InitBDD_Config(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	T_STRUCT_OF_FILE_NEWCFG_INI loc_t_newcfgini;

	//bdd configuration
	memset(loc_ps_config,'\0',sizeof(S_STRUCT_CONFIGURATION));
	*loc_ps_config = S_CONFIG_EQUIPEMENT_DEFAUT;	//INIT

	//On edit le fichier (qui gère les changement de configuration)
	memset(&loc_t_newcfgini,'\0',sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //INIT
	u8Transfert_StructToFile(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
	
}/*InitBDD_Config*/


//=====================================================================================
// Fonction		: InitModule_Config
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 25/09/2009 -
// Description	: Initialisation du module de Config de l'équipement
//=====================================================================================
void InitModule_Config(void)
{
}/*InitModule_Config*/


