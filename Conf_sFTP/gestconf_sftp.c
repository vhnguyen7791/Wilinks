/*========================================================================*/
/* NOM DU FICHIER  : gestconf_sftp.c 	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : JP                                                   */
/* Date			   : 25/10/2011                                           */
/* Libelle         : conf_sftp: gestion configuration par sFTP  		  */
/* Projet          : WRM100                                               */
/* Indice          : BE064                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 25/09/09 CM
// - Correction bug de la configuration par sFTP (lors changement countryId)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/
#define _GESTCONF_SFTP

#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

u32sod u32_size_file_conf;
u16sod u16_cpt_conf_transfert_fail;

S_STRUCT_CONFIGURATION s_config_ftp;

#define FICHIER_CONF_GLOBALE PATH_DIR_VAR_CONF NFILE_GLOBALE EXT_CFG
#define FICHIER_CONF_SFTP_LOG PATH_DIR_VAR_CONF NFILE_GLOBALE EXT_LOG

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8TestChecksumConfSFTP
// Entrees		: rien
// Sortie		: <loc_u8_resultat>: 0:checksum absent du fichier, 1:checksum ko, 2: ok
// Auteur		: CM - 16/12/2009 -
// Description	: Test si le checksum du fichier est valide
//=====================================================================================
u8sod u8TestChecksumConfSFTP(void)
{
	FILE	*loc_p_handle;
	s32sod	loc_s32_retour,loc_s32_temp;
	s8sod	loc_s8_ligne[TAILLE_MAX_LIGNE_BDDFILE+1];
	s8sod	loc_s8_checksum[6]; //au max 65536 plus la fin de chaine : 6 caracteres
	u16sod	loc_u16_checksum,loc_us_checksum_fichier,loc_u16_loop;
	u8sod	loc_u8_retour;

	loc_u16_checksum=0;
	loc_u16_loop=0;
	loc_u8_retour = 0;//par defaut checksum absent
	if(NULL != (loc_p_handle = fopen(FICHIER_CONF_GLOBALE, "rb" ))) //CONDITION: fichier présent
	{
		while(loc_u16_loop<2000) {
			loc_u16_loop++;
			//on parcourt ligne a ligne en limitant le nombre de ligne max a 2000
			// normalement, sans commentaire, il y a 422 lignes
			
			if (fgets(loc_s8_ligne,TAILLE_MAX_LIGNE_BDDFILE,loc_p_handle) == NULL) break;
			//on ne tient pas compte de la ligne de checksum!
			if (strncmp(CH_BDDFILECHECKSUM,loc_s8_ligne,15)==0)
			{
				//on recupere le checksum
				loc_s8_checksum[0]=loc_s8_ligne[16];
				loc_s8_checksum[1]=loc_s8_ligne[17];
				loc_s8_checksum[2]=loc_s8_ligne[18];
				loc_s8_checksum[3]=loc_s8_ligne[19];
				loc_s8_checksum[4]=loc_s8_ligne[20];
				loc_s8_checksum[5]=0;
				loc_us_checksum_fichier = atoi(loc_s8_checksum);
				loc_u8_retour = 1;
				break;
			}
			loc_s32_retour= strlen(loc_s8_ligne);
			for (loc_s32_temp=0;loc_s32_temp<(loc_s32_retour-1);loc_s32_temp++)
				loc_u16_checksum += (u16sod)(loc_s8_ligne[loc_s32_temp]);
		}

		if (loc_u8_retour==1)
		{
			//checksum prsent dans le fichier: on le compare a celui de notre calcul
			printf("checksum fichier= %d \n",loc_us_checksum_fichier);
			printf("checksum calcule= %d \n",loc_u16_checksum);				

			if (loc_u16_checksum==loc_us_checksum_fichier)
			{
				loc_u8_retour = 2;
			}
		}
	}
	return(loc_u8_retour);
}


//=====================================================================================
// Fonction		: u8GestionConfSFTP
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/12/2009 -
// Description	: Gestion de la configuration par SFTP
//=====================================================================================
void u8GestionConfSFTP(void)
{
	FILE	*loc_p_handle;
	u32sod	loc_u32_size_file;
	u8sod loc_u8_resultat,loc_uc_test_checksum;
	s32sod	loc_s32_sem;

	
	loc_p_handle = NULL; //INIT
	loc_u32_size_file = 0;	//INIT

	//On vérifie si il y a le fichier de mise à jour du logiciel CPU
	if(NULL != (loc_p_handle = fopen( FICHIER_CONF_GLOBALE, "rb" ))) //CONDITION: fichier présent
	{
		fclose (loc_p_handle);
		
		//Détermination taille du fichier
		loc_u32_size_file = u32GetSizeOfFile(FICHIER_CONF_GLOBALE);

		//CONDITION: taille du fichier stable
		if(loc_u32_size_file == u32_size_file_conf) 
		{
			u16_cpt_conf_transfert_fail++;
			//on test la validite de la config dans le fichier
			loc_uc_test_checksum=u8TestChecksumConfSFTP();
			if (1 != loc_uc_test_checksum)
			{
				//checksum correct ou absent. on doit alors verifier la coherence de la configuration

				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				//on copie la config actuel dans la structure config ftp
				u8FillConfigEquipement(&s_config_ftp);
				//on met a jour la config ftp avec le contenu du fichier recu
				loc_u8_resultat = u8Transfert_FileToStruct(&s_config_ftp, &PT_DEF_FILE_CONFIG_GLOBAL_SANSCHECKSUM);

				if (FALSE==loc_u8_resultat)
				{
					//erreur de lecture du fichier
					if(NULL != (loc_p_handle = fopen(FICHIER_CONF_SFTP_LOG, "wt" )))
					{
						fprintf(loc_p_handle,"Erreur d'ouverture du fichier de configuration / Error opening configuration file  \n");
						fclose (loc_p_handle);
						//on supprime le fichier de config
						CmdSystem_Generique("rm %s",FICHIER_CONF_GLOBALE);
					}						
				}
				else
				{
					loc_p_handle = fopen(FICHIER_CONF_SFTP_LOG, "wt" );
					loc_u8_resultat= TRUE;
					//la nouvelle config est dans s_config_ftp
					if (FALSE==u8TestConfigConstructeur(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Constructeur / Error on constructor part \n");
						}
					}
					if (FALSE==u8TestConfigAdmin(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Admin / Error on Admin part \n");
						}
					}
					if (FALSE==u8TestConfigSnmp(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Snmp / Error on SNMP part \n");
						}
					}
						
					if (FALSE==u8TestConfigGeneral(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie General / Error on General part \n");
						}
					}
						
					if (FALSE==u8TestConfigWifi(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Wifi / Error on Wifi part \n");
						}
					}
						
					if (FALSE==u8TestConfigHandoff(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Handoff / Error on Handoff part \n");
						}
					}
						
					if (FALSE==u8TestConfigRouting(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Routing / Error on Routing part \n");
						}
					}
						
					if (FALSE==u8TestConfigNAT(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie NAT / Error on NAT part \n");
						}
					}
						
					if (FALSE==u8TestConfigMulticast(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie Multicast / Error on Multicast part \n");
						}
					}
						
					if (FALSE==u8TestConfigTabEvt(&s_config_ftp))
					{
						loc_u8_resultat=FALSE;
						if (loc_p_handle!=NULL)
						{
							fprintf(loc_p_handle,"Erreur dans la partie TabEvt / Error on TabEvt part \n");
						}
					}
					
					if (FALSE==loc_u8_resultat)
					{
						printf("Fichier de configuration par sFTP incoherent! \n");
						if (loc_p_handle!=NULL)
						{
							fclose(loc_p_handle);							
						}

					}
					else
					{
						//configuration correcte. on peut l'appliquer
						printf("Fichier de configuration par sFTP correct \n");

						if (loc_p_handle!=NULL)
						{
							fclose(loc_p_handle);							
						}

//d: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
						//On signale une configuration par FTP
						SignalNewCfgFTP();
//f: BE064.0 25/11/2011 (CM) - Correction bug de la configuration par sFTP (lors changement countryId)
						
						// on applique la configuration!
						u8EditConfigEquipement(&s_config_ftp);
					}
					
					
					//on supprime le fichier de config
					CmdSystem_Generique("rm %s",FICHIER_CONF_GLOBALE);

				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				
			}
			else
			{
				//fichier ko!
				if (u16_cpt_conf_transfert_fail > 30)
				{
					// on se donne 30 secondes pour recevoir le fichier entier si le probleme provient du transfert...
					// puis on signale pb dans le fichier de log
					if(NULL != (loc_p_handle = fopen(FICHIER_CONF_SFTP_LOG, "wt" )))
					{
						printf("Fichier de configuration par sFTP erreur de checksum! \n");
						fprintf(loc_p_handle,"Checksum du fichier incorrect / File checksum error \n");
						fclose (loc_p_handle);

						//on supprime le fichier de config
						CmdSystem_Generique("rm %s",FICHIER_CONF_GLOBALE);
					}
				}
			}
		}
		else
		{
			u32_size_file_conf = loc_u32_size_file; //maj
			u16_cpt_conf_transfert_fail = 0;	//RAZ
		}
	}
	else
	{
		u32_size_file_conf = loc_u32_size_file; //maj
		u16_cpt_conf_transfert_fail = 0;	//RAZ
	}

} /*u8GestionConfSFTP*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_GestConfsFTP
// Entrees		: rien
// Sortie		: rien
// Description	: Initialisation du module 
//=====================================================================================
void InitModule_GestConfsFTP(void)
{
	u32_size_file_conf = 0;
	u16_cpt_conf_transfert_fail = 0;

	memset(&s_config_ftp,'\0',sizeof(S_STRUCT_CONFIGURATION));

}/*InitModule_GestConfsFTP*/

