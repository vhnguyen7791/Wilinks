/*========================================================================*/
/* NOM DU FICHIER  : bdd_snmp.c			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009											  */
/* Libelle         : SNMP CGI: Base de données pour le serveur SNMP       */
/* Projet          : WRM100                                               */
/* Indice          : BE053                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
// - CREATION
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE019 16/03/2010 CM
// - Ajout MIB wrm100 dans agent SNMP
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE040 13/09/2010 CM
// - Nouveaux projets WRM100
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE053 16/12/2010 CM
// - Modification de la MIB / agent SNMP (suite integration Driver-N)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _BDD_SNMP


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"
#define SNMP_API_GET_IP_ADDRESS_H
#include <net-snmp/library/snmp_api.h>

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//pour fonction ps8ConvertChaineToSnmp
#define TAILLE_MAX_CHAINE_CONVERTIE_SNMP	1000
static s8sod	ps8_chaine_convertie_snmp[TAILLE_MAX_CHAINE_CONVERTIE_SNMP+1];

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8CheckClientSnmpAllowed
// Entrees		: rien
// Sortie		: <loc_u8_result< : TRUE si autorisée, FALSE sinon
// Auteur		: CM - 25/09/2007 -
// Description	: Fonction qui test si accès en écriture est autorisée
//=====================================================================================
u8sod u8CheckClientSnmpAllowed(void)
{
	u8sod	loc_u8_result;
#if 0
	FILE	*loc_pt_file_pwd;
#endif

	loc_u8_result = TRUE;
	
#if 0
	if(MODE_SECURISATION_SNMP_SET == ps_config_equipement->s_admin.u8_securisation_snmp)
	{
		//on vérifie si le fichier passwd est présent
		loc_pt_file_pwd = fopen("/var/passwd", "r");

		if(NULL != loc_pt_file_pwd) //CONDITION: fichier présent
		{
			fclose(loc_pt_file_pwd);
			
			loc_u8_result = TestPassword(get_ip_address(), MIDDLE_LEVEL_ACCESS);
		}
	}
#endif
	
	return loc_u8_result;
}/*u8CheckClientSnmpAllowed*/

// -------------------------------------------------------------------------------------------------------- //
//	Fonction	: ps8ConvertChaineToSnmp
//	Entrées		: <loc_ps8_chaine_initiale< : chaîne à converir
//	Sortie		: <ps8_chaine_convertie_snmp< : chaîne modifiée (variable globale)
//	Auteur		: CM - 04/09/2007
//	Description : Conversion d'une chaîne de caractères adaptée pour
//	snmp
//	Seuls les caractères suivants sont autorisés au niveau SNMP:
//		- A to Z
//		- a to z
//		- 0 to 9
//		- :;|=,{}<.()[]-'"
// -------------------------------------------------------------------------------------------------------- //
s8sod *ps8ConvertChaineToSnmp(s8sod *loc_ps8_chaine_initiale)
{
	s8sod	loc_ps8_ch_a_convertir[] = {"àâäéèêëîïôùûüµ°ç"};
	s8sod	loc_ps8_ch_a_correspon[] = {"aaaeeeeiiouuuu c"};
	u16sod	loc_u16_i;
	u16sod	loc_u16_k;
	s8sod	loc_ps8_code[10];

	strcpy(ps8_chaine_convertie_snmp,"");	//INIT

	for (loc_u16_i = 0; loc_u16_i<strlen(loc_ps8_chaine_initiale);loc_u16_i++)
	{
		for (loc_u16_k=0 ; (loc_u16_k<strlen((s8sod *)loc_ps8_ch_a_convertir))&&(loc_ps8_chaine_initiale[loc_u16_i]!=loc_ps8_ch_a_convertir[loc_u16_k]); loc_u16_k++)
		{
		}
		if (loc_u16_k<strlen((s8sod *)loc_ps8_ch_a_convertir)) //CONDITION: caractère non autorisé
		{
			sprintf(loc_ps8_code,"%c",loc_ps8_ch_a_correspon[loc_u16_k]);
		}
		else
		{
			sprintf(loc_ps8_code,"%c",loc_ps8_chaine_initiale[loc_u16_i]);
		}
		strcat(ps8_chaine_convertie_snmp, loc_ps8_code);
		if(strlen(ps8_chaine_convertie_snmp) > (TAILLE_MAX_CHAINE_CONVERTIE_SNMP-6))
		{
			loc_u16_i = 0xFFF0;	//on sort
		}
	}

	return(ps8_chaine_convertie_snmp);
}/*ps8ConvertChaineToSnmp*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_Bdd_Snmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/06/2007 -
// Description	: Initialisation du module Bdd_snmp
//=====================================================================================
void InitModule_Bdd_Snmp(void)
{
	s32sod loc_s32_sem;
	
	memset(&s_config_process_snmpd,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	memset(&s_cfg_tempo_snmpd,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT
	
	memset(&s_exploit_process_snmpd, 0, sizeof(S_STRUCT_EXPLOITATION)); //INIT
	memset(&s_exp_events_process_snmpd, 0, sizeof(S_STRUCT_EXPLOIT_EVENTS)); //INIT

	pt_eventsystem_process_snmpd = ptGetPtrEventSystem();; //INIT

	memset(&s_list_freq_process_snmpd,0xFF,sizeof(S_STRUCT_LIST_FREQ)); //INIT
	
	u8_snmp_langue = LANGUE_FRANCAIS; //INIT
	u8_snmp_type_equipement = EQUIPEMENT_INCONNU; //INIT

	//Gestion CIP
	memset(&s_cip_monitor_from_snmpd, 0, sizeof(S_STRUCT_CIP_MONITOR)); //INIT
	memset(&s_cip_jdb_from_snmpd, 0, sizeof(S_STRUCT_CIP_JDB)); //INIT

	//Gestion du journal de bord
	memset(&s_statutjdb_from_snmpd, 0, sizeof(S_STRUCT_STATUTJDB)); //INIT

	
	strcpy(ps8_data_a_tout_faire, ""); //INIT

	//-----------------------------------------------
	//Modules propres au processus
	//-----------------------------------------------
	InitModule_ExecTrap();
	InitModule_StatusTrap();

	//-----------------------------------------------
	//Initialisation des modules de la librairie system
	//-----------------------------------------------
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(AddMsgDbgLog);
	
	//-----------------------------------------------
	//Initialisation des modules de la librairie bdd
	//-----------------------------------------------
	InitModule_LibraryBdd();

	//-----------------------------------------------
	//Initialisation des modules de la librairie Wifi
	//-----------------------------------------------
	InitModule_LibraryWifi();

	//---------------------------------------------
	//Lecture de la configuration POUR PROCESSUS SNMPD
	//---------------------------------------------
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillConfigEquipement(&s_config_process_snmpd)) //INIT
	{
		MACRO_PRINTF(("InitModule_Bdd_Snmp: Problème lecture configuration \n"));
	}
	else
	{
		//Langue
		u8_snmp_langue = s_config_process_snmpd.s_admin.u8_langue; //INIT
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem


	//Type d'équipement
	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitGeneralFile(&s_exploit_process_snmpd.s_general))
	{
		MACRO_PRINTF(("InitModule_Bdd_Snmp: Erreur lecture exploit general \n"));
	}
	else
	{
		u8_snmp_type_equipement = s_exploit_process_snmpd.s_general.u8_type_equipement; //MAJ
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillEventSystemFile(pt_eventsystem_process_snmpd))
	{
		MACRO_PRINTF(("InitModule_Bdd_Snmp: Erreur lecture eventsystem \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillStatutJdb(&s_statutjdb_from_snmpd, IDXSTATUTJDB_RAM)) 
	{
		MACRO_PRINTF(("InitModule_Bdd_Snmp: Erreur lecture statutjdb \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_JDB, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on leve le semaphore
	if(FALSE == u8FillListFreqFile(&s_list_freq_process_snmpd))
	{
		MACRO_PRINTF(("InitModule_Bdd_Snmp: Erreur lecture LIST FREQ \n"));
	}
	s32Lock_Release(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on relache le sem
	
	
}/*InitModule_Bdd_Snmp*/

