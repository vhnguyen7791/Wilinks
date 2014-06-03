/*========================================================================*/
/* NOM DU FICHIER  : gestconfig.c 		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Principal: gestion de la configuration				  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE003 22/12/2009 CM
// - Intégration configuration par DHCP client
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE037 06/07/2010 CM
// - Ajout gestion des évènements spécifiques à l'équipement
//BE042 07/10/2010 CM
// - Correction configuration mode 802.11 (associé au driver-N)
// - Ajout possibilité de reconfigurer entierement l'équipement
//BE047 29/11/2010 CM
// - Gestion mode dégradé - connection à AP impossible en permanence suite à configuration wifi 
// - Optimisation configuration radio modem / amelioration ergonomie
//BE060 16/03/2011
// - Ajout fonction impose config au démarrage (pour chaque bdd de config)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _GESTCONFIG


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


//Configuration mémorisée
static S_STRUCT_CONFIGURATION s_config_memo;
//Flag pour reconfigurer la totalité de l'équipement
static u32sod u32_reconfiguration_total;


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: ExecuteStartConfig
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Execute les étapes suivantes (lors du démarrage):
//				-> vérification des fichiers de configuration (présents dans la mémoire non volatile)
//					(checksum + conformité)
//				-> extraction de la configuration
//				-> Vérification cohérence de la configuration
//=====================================================================================
void ExecuteStartConfig(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_idx_cfgfile;
	u8sod loc_u8_etat_base; //etat du fichier de base
	u16sod loc_u16_chk_base; //checksum du fichier de base
	u8sod loc_u8_etat_backup; //etat du fichier de backup
	u16sod loc_u16_chk_backup;//checksum du fichier de backup
	u8sod	loc_u8_cpt_essai;
	u8sod loc_u8_etat_bdd; //etat du fichier de bdd
	

	loc_u8_etat_base = FALSE; //INIT
	loc_u16_chk_base = 0 ; //INIT
	loc_u8_etat_backup = FALSE; //INIT
	loc_u16_chk_backup = 0 ; //INIT
	loc_u8_cpt_essai = 0;	//INIT
	loc_u8_etat_bdd = FALSE; //INIT

	//**Etape n°1**: Initialisation STRUCTURE (RAM)
	InitBDD_Config(loc_ps_config);
	
	for(loc_u8_idx_cfgfile=0; loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
	{
		//**Etape n°2**: Vérification présence / validité des fichiers de configuration dans la mémoire non volatile
		//on parcourt les fichiers de configuration (dans mémoire non volatile)
		loc_u8_etat_base = u8Transfert_FileToStruct(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base ]);
		loc_u16_chk_base = loc_ps_config->u16_checksum_file;
		loc_u8_etat_backup = u8Transfert_FileToStruct(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup ]);
		loc_u16_chk_backup = loc_ps_config->u16_checksum_file;

		printf("************************************************ \n");
		printf("* ExecuteStartConfig: RESULTAT CONFIG idx=%s \n",
			   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom);
		printf("*                  	BASE(STATUT=%d CHK=%d) \n",
			   loc_u8_etat_base,loc_u16_chk_base);
		printf("*                  	BACKUP(STATUT=%d CHK=%d) \n",
			   loc_u8_etat_backup,loc_u16_chk_backup);
		printf("************************************************ \n");
		
		if(TRUE == loc_u8_etat_base) //CONDITION: fichier de base OK
		{
			if(TRUE == loc_u8_etat_backup) //CONDITION: fichier de backup OK
			{
				//On vérifie qu'il y a le meme checksum
				//si différent, il faut copier le fichier de base dans backup
				if(loc_u16_chk_base != loc_u16_chk_backup)
				{
					//on copie base => backup
					u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file,
										 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file);
				}
			}
			else //CONDITION: fichier de backup KO
			{
				//on copie base => backup
				u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file,
									 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file);
			}
		}
		else  //CONDITION: fichier de base KO
		{
			if(TRUE == loc_u8_etat_backup) //CONDITION: fichier de backup OK
			{
				//on copie backup => base
				u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file,
									 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file);
			}
			else //CONDITION: fichier de backup KO
			{
				printf("ExecuteStartConfig: PASSAGE CONFIGURATION PAR DEFAUT idx=%s \n",
					   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom);
				//Les 2 fichiers sont KO
				PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].CopyConfig((S_STRUCT_CONFIGURATION*)&S_CONFIG_EQUIPEMENT_DEFAUT, loc_ps_config);
				u8Transfert_StructToFile(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base ]);
				//on copie base => backup
				u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file,
									 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file);
				//On signale un probleme de configuration
				pu8_signal_passage_config_par_defaut[loc_u8_idx_cfgfile] = TRUE; //erreur signalée
			}
		}

		loc_u8_etat_bdd = FALSE; //RAZ
		loc_u8_cpt_essai = 0;	//RAZ
		do{

			//**Etape n°3**: Copie des fichiers de configuration en RAM DISK
			//on copie base => bdd en génèrant le nouveau fichier (au cas où il y a de nouveaux paramètres)
//			u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file,
//								 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file);
			u8Transfert_StructToFile(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]);
			
			//**Etape n°4**: Conversion contenu FICHIER => STRUCTURE
			loc_u8_etat_bdd = u8Transfert_FileToStruct(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]);
			
			loc_u8_cpt_essai ++;
			
		}while( (FALSE == loc_u8_etat_bdd) &&
				(loc_u8_cpt_essai<2)
			  );

		//Avant de tester la cohérence de la configuration, on peut forcer certains paramètres de configuration
		if(NULL != PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8ImposeInitConfig)//CONDITION: Fonction existe?
		{
			if(TRUE == PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8ImposeInitConfig(loc_ps_config))//CONDITION: nouvelle configuration
			{
				printf("ExecuteStartConfig: IMPOSE INIT CONFIGURATION idx=%s \n",
					   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom);
				//->Puis on génère le nouveau fichier
				u8Transfert_StructToFile(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]);
				//->on copie bdd => base
				u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file,
									 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file);
				//->on copie bdd => backup
				u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file,
									 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file);
			}			
		}
		
		//**Etape n°5**: Test cohérence de la configuration (plages, valeurs, ...)
		if(FALSE == PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u8TestConfig(loc_ps_config))
		{
			printf("ExecuteStartConfig: PASSAGE CONFIGURATION PAR DEFAUT idx=%s \n",
				   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom);
			//Configuration incohérente
			//donc on passe en configuration par défaut
			//-> on copie en RAM les paramètres par défaut
			PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].CopyConfig((S_STRUCT_CONFIGURATION*)&S_CONFIG_EQUIPEMENT_DEFAUT, loc_ps_config);

			//->Puis on génère le nouveau fichier
			u8Transfert_StructToFile(loc_ps_config, &PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd ]);
			//->on copie bdd => base
			u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file,
								 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file);
			//->on copie bdd => backup
			u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file,
								 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file);
			//On signale un probleme de configuration
			pu8_signal_passage_config_par_defaut[loc_u8_idx_cfgfile] = TRUE;  //erreur signalée
		}
	}

	//On mémorise la configuration courante
	s_config_memo = *loc_ps_config;

}/*ExecuteStartConfig*/

//=====================================================================================
// Fonction		: ExecuteGestionConfig
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Execute les étapes suivantes (en régime établi):
//				-> vérification evolution de la configuration
//				-> application de la configuration aux services nécessaires
//				-> copie dans FLASH
//					appelée en tache de fond
//=====================================================================================
void ExecuteGestionConfig(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	u8sod loc_u8_idx_cfgfile;
	T_STRUCT_OF_FILE_NEWCFG_INI loc_t_newcfgini;
	u8sod loc_u8_signal_evolution_cfg;
	u8sod loc_u8_signal_diff_cfg;
	
	loc_u8_signal_evolution_cfg = FALSE; //INIT
	loc_u8_signal_diff_cfg = FALSE;	//INIT

	memset(&loc_t_newcfgini,'\0',sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //INIT
	
	//Lecture du fichier
	if(TRUE == u8Transfert_FileToStruct(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI))
	{
		for(loc_u8_idx_cfgfile=0;loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
		{
			if(TRUE == loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile])
			{
				/*printf("********************1*****************\n");
				s8sod loc_ps8_addr_ip[MAX_LG_FORMAT_ADRESSE_IP+1];
				s8sod loc_ps8_addr_mask[MAX_LG_FORMAT_ADRESSE_IP+1];
				strcpy(loc_ps8_addr_ip, ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_adresse_ip)); //INIT
				strcpy(loc_ps8_addr_mask, ps8GetStringIp(loc_ps_config->s_gene.u32_bridge_masque_reseau)); //INIT
				printf("MODE_IP_STATIQUE: ifconfig  %s netmask %s down\n",
				       loc_ps8_addr_ip,
				       loc_ps8_addr_mask);
				printf("********************1*****************\n");*/
				/*T_STRUCT_DEFINITION_FILE_FS *loc_pt_def_file;
				loc_pt_def_file=&PT_DEF_FILE_CONFIG[ PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd]; 
				FILE	*loc_p_handle;
				char * line = NULL;
				size_t len = 0;
				loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt");
				printf("************VuHai %d**************************\n",loc_u8_idx_cfgfile);
				while ((getline(&line, &len, loc_p_handle)) != -1) {
					printf("%s", line);
				}

				printf("************VuHai %d*************************\n",loc_u8_idx_cfgfile);*/
				
				printf("ExecuteGestionConfig: Signal nouvelle configuration %s\n",
					   PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].ps8_cfgnom);
				//On extrait la configuration du fichier
				u8FillConfigFile(loc_u8_idx_cfgfile, loc_ps_config);
				/*loc_p_handle = fopen( loc_pt_def_file->ps8_path_file, "rt");
				printf("************VuHai %d**************************\n",loc_u8_idx_cfgfile);
				while ((getline(&line, &len, loc_p_handle)) != -1) {
					printf("%s", line);
				}

				printf("************VuHai %d**************************\n",loc_u8_idx_cfgfile);*/
				loc_u8_signal_evolution_cfg = TRUE;
			}
		}
	}

	//Si il y a évolution de la configuration détectée, on acquitte le fichier
	if(TRUE == loc_u8_signal_evolution_cfg)
	{
//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
		if(TRUE != loc_t_newcfgini.u8_change_cfg_FTP) //CONDITION: ce n'est pas une configuration par FTP
		{
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
			//Sur changement de certains paramètres, on impose la configuration
			ImposeConfigSiEvolution(loc_ps_config, &s_config_memo, &loc_t_newcfgini);

		}

		loc_u8_signal_diff_cfg = u8DiffConfig(loc_ps_config, &s_config_memo);
		
		if((TRUE == loc_u8_signal_diff_cfg)||
		   (ORDRE_RECONFIG_TOTALE_ACTIVEE == u32_reconfiguration_total)
		  )//CONDITION: différence détectée ou reconfig demandée
		{
			printf("ExecuteGestionConfig: Evolution de la configuration\n");
			if(TRUE == loc_u8_signal_diff_cfg)//CONDITION: ce n'est pas un ordre de reconfiguration totale
			{
				//On signale l'évolution de la configuration à la tache de fond de principal
				SetSignalNewConfig(&loc_t_newcfgini);

				for(loc_u8_idx_cfgfile=0;loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
				{
					if(TRUE == loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile])
					{
						//on copie les fichiers dans la FLASH
						//->on copie bdd => base
						u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file,
											 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_base].ps8_path_file);
						//->on copie bdd => backup
						u8CmdSystem_CopyFile(PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_bdd].ps8_path_file,
											 PT_DEF_FILE_CONFIG[PT_DESCRIPTION_CONFIGURATION[loc_u8_idx_cfgfile].u16_idx_backup].ps8_path_file);

						loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile] = FALSE; //on acquitte

						//Il y a un changement dans la configuration
						pu8_signal_passage_config_par_defaut[loc_u8_idx_cfgfile] = FALSE; //RAZ

					}
				}
			}
			else //CONDITION: pas de changement de configuration
			{
				for(loc_u8_idx_cfgfile=0;loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
				{
					if(TRUE == loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile])
					{
						loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile] = FALSE; //on acquitte
					}
				}
			}

			//On signal une configuration en cours
			SignalConfig_InProgress();

			printf("=========== DEBUT APPLICATION CONFIGURATION ============== \n");
			//Application de la configuration
			ExecuteApplyConfig(loc_ps_config, &s_config_memo, u32_reconfiguration_total);
			printf("============ FIN APPLICATION CONFIGURATION =============== \n");

			u32_reconfiguration_total = ORDRE_RECONFIG_TOTALE_DESACTIVEE;	//RAZ
			
			//Dernière étape: on met à jour la configuration mémorisée
			s_config_memo = *loc_ps_config;

//d: BE063 27/10/2011 - configuration par sFTP
			//on efface le fichier sta courant
			CmdSystem_Generique("rm %s ",
								PATH_DIR_VAR_CONF NFILE_GLOBALE EXT_STA);
			//on cree le nouveau fichier config_wrm100.sta avec le contenu de la configuration
			u8Transfert_StructToFile(loc_ps_config,&PT_DEF_FILE_CONFIG_GLOBAL_STA);
//f: BE063 27/10/2011 - configuration par sFTP


			
		}
		else //CONDITION: pas d'évolution de la configuration
		{
			for(loc_u8_idx_cfgfile=0;loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
			{
				if(TRUE == loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile])
				{
					loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile] = FALSE; //on acquitte
				}
			}
		}
//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
		loc_t_newcfgini.u8_change_cfg_FTP = FALSE; //RAZ
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
		
		u8Transfert_StructToFile(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
	}
	
}/*ExecuteGestionConfig*/

//=====================================================================================
// Fonction		: Ordre_ReconfigurationTotale
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/10/2010 -
// Description	: Ordre de tout reconfigurer
//=====================================================================================
void Ordre_ReconfigurationTotale(void)
{
	u8sod loc_u8_idx_cfgfile;
	T_STRUCT_OF_FILE_NEWCFG_INI loc_t_newcfgini;

	memset(&loc_t_newcfgini,'\0',sizeof(T_STRUCT_OF_FILE_NEWCFG_INI)); //INIT

	//Lecture du fichier
	if(TRUE == u8Transfert_FileToStruct(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI))
	{
		for(loc_u8_idx_cfgfile=0;loc_u8_idx_cfgfile<NB_MAX_IDXCONFIG;loc_u8_idx_cfgfile++)
		{
			loc_t_newcfgini.pu8_flag[loc_u8_idx_cfgfile] = TRUE;
		}
		u32_reconfiguration_total = ORDRE_RECONFIG_TOTALE_ACTIVEE; //ordre activé
		u8Transfert_StructToFile(&loc_t_newcfgini, &T_DEF_FILE_NEWCFG_INI);
		printf("Ordre_ReconfigurationTotale\n");
	}
}/*Ordre_ReconfigurationTotale*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_GestConfig
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de gestconfig
//=====================================================================================
void InitModule_GestConfig(void)
{
	memset(&s_config_memo,'\0',sizeof(S_STRUCT_CONFIGURATION)); //INIT

	//Flag pour reconfigurer la totalité de l'équipement
	u32_reconfiguration_total = ORDRE_RECONFIG_TOTALE_DESACTIVEE; //INIT
	
}/*InitModule_GestConfig*/

