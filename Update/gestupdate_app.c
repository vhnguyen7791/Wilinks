/*========================================================================*/
/* NOM DU FICHIER  : gestupdate_app.c 	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 17/12/2009                                           */
/* Libelle         : Update: gestion mise à jour de l'application		  */
/* Projet          : WRM100                                               */
/* Indice          : BE010                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 17/12/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Modification processus update (independance avec principal)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _GESTUPDATE_APP

#define TIMEOUT_TEST_UPDATE_APP		10	//secondes
#define TIMEOUT_SANS_UPDATE_APP		180	//secondes

#define TAILLE_MAX_DETAIL_ERROR_GZ	200	//caractères

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "headers.h"
#include "image.h"
#include <arpa/inet.h>

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

u32sod u32_size_file_app;
u16sod	u16_cpt_test_update;
u16sod	u16_cpt_sans_update;

/*_____V - PROCEDURES ____________________________________________________*/

extern unsigned long crc32 (unsigned long, const unsigned char *, unsigned int);


//=====================================================================================
// Fonction		: u8TestIntegrityFileGz
// Entrees		: <loc_ps8_error< : detail erreur
// Sortie		: <loc_u8_resultat>: TRUE, sinon FALSE
// Auteur		: CM - 18/12/2009 -
// Description	: Test si le fichier compressé est valide
//					"corrupted data","crc error","incorrect length"
//=====================================================================================
u8sod u8TestIntegrityFileGz(s8sod *loc_ps8_error)
{
	u8sod loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_ps8_result_fgets = NULL;	//INIT
	strcpy(loc_ps8_error,""); //INIT

	if(NULL != (loc_p_handle = fopen( FICHIER_UPDATE_TESTGZ, "rt" ))) //CONDITION: fichier présent
	{
		loc_ps8_result_fgets = fgets(loc_ps8_error, TAILLE_MAX_DETAIL_ERROR_GZ, loc_p_handle);
		if (NULL != loc_ps8_result_fgets)
		{
			//La ligne est non vide: donc il y a une erreur détecté
			loc_u8_resultat = FALSE;
			printf("u8TestIntegrityFileGz: File KO: %s",loc_ps8_error);
		}
		else
		{
			printf("u8TestIntegrityFileGz: File OK\n");
		}

		fclose (loc_p_handle);
	}
	else
	{
		printf("u8TestIntegrityFileGz: File not present %s ",FICHIER_UPDATE_TESTGZ);
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;
}/*u8TestIntegrityFileGz*/


//=====================================================================================
// Fonction		: u8TestValidApp
// Entrees		: rien
// Sortie		: <loc_u8_resultat>: TRUE, sinon FALSE
// Auteur		: CM - 16/12/2009 -
// Description	: Test si l'application est valide
//=====================================================================================
u8sod u8TestValidApp(void)
{
	u8sod loc_u8_resultat;
	image_header_t loc_t_header;
	image_header_t *loc_pt_hdr = &loc_t_header;
	u32sod	loc_u32_data, loc_u32_len, loc_u32_checksum;
	FILE	*loc_p_handle;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT

	if(NULL != (loc_p_handle = fopen( FICHIER_UPDATE_CPU_BIN, "rb" ))) //CONDITION: fichier présent
	{
		//Lecture header
		printf("Test header de l'application: ...");
		if (sizeof(image_header_t) == fread(&loc_t_header, sizeof(u8sod), sizeof(image_header_t), loc_p_handle))
		{
			//Vérification header ...
			if (ntohl(loc_pt_hdr->ih_magic) != IH_MAGIC)
			{
				printf("KO: Bad Magic Number \n");
				loc_u8_resultat = FALSE;
			}
			else
			{
				loc_u32_data = (u32sod)&loc_t_header;
				loc_u32_len  = sizeof(image_header_t);

				//Vérification header checksum ...
				loc_u32_checksum = ntohl(loc_pt_hdr->ih_hcrc);
				loc_pt_hdr->ih_hcrc = 0;
				if (crc32 (0, (u8sod *)loc_u32_data, loc_u32_len) != loc_u32_checksum)
				{
					printf("KO: Bad Header Checksum \n");
					loc_u8_resultat = FALSE;
				}
				else
				{
					printf("OK\n");
				}
			}
		}
		fclose (loc_p_handle);		
	}
	else
	{
		printf("u8TestValidApp: File not present %s ",FICHIER_UPDATE_CPU_BIN);
		loc_u8_resultat = FALSE;
	}


	return loc_u8_resultat;
}/*u8TestValidApp*/

u8sod u8MiseAJourInfoSystem(T_E_LISTE_MODES_BOOT e_mode_boot_tmp, s8sod *UNUSED(ps8_update__version_be_uboot))
{
	printf("MISE A JOUR INFO SYSTEM ==> APP%d ACTIF\n",e_mode_boot_tmp);

	switch(e_mode_boot_tmp)
	{
		case E_MODE_BOOT_APP1 :			/* lancer l'appli 1 au prochain démarrage */
			CmdSystem_Generique("fw_setenv bootcmd run app1");
			break;
		case E_MODE_BOOT_APP2 :			/* lancer l'appli 2 au prochain démarrage */
			CmdSystem_Generique("fw_setenv bootcmd run app2");
			break;
		default :					/* Par défaut, lancer l'appli 1 au prochain démarrage */
			printf("MAJIS - err : valeur par defaut !");		/* Signalement de l'erreur (valeur inattendue) */
			CmdSystem_Generique("fw_setenv bootcmd run app1");
			break;
	}	

	return TRUE;
}

//=====================================================================================
// Fonction		: ExecuteGestionUpdateApp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/12/2009 -
// Description	: Gestion mise à jour de l'application
//=====================================================================================
void ExecuteGestionUpdateApp(void)
{
	FILE	*loc_p_handle;
	u32sod	loc_u32_size_file;
	s8sod	loc_ps8_error_gz[TAILLE_MAX_DETAIL_ERROR_GZ+1];
	
	loc_p_handle = NULL; //INIT
	loc_u32_size_file = 0;	//INIT
	strcpy(loc_ps8_error_gz, ""); //INIT

	//On vérifie si il y a le fichier de mise à jour du logiciel CPU compressé
	if(NULL != (loc_p_handle = fopen( FICHIER_UPDATE_CPU_BIN_GZ, "rb" ))) //CONDITION: fichier présent
	{
		printf("ExecuteGestionUpdateApp: Fichier initramfs_AP.bin.gz recu ...\n");
		
		//On vérifie ensuite si le fichier au format gz est correct (on retourne la sortie erreur dans le fichier testgz)
		CmdSystem_Generique("gunzip -t -v %s 2>%s", FICHIER_UPDATE_CPU_BIN_GZ, FICHIER_UPDATE_TESTGZ);

		//Si le fichier n'est pas corrompu
		if(TRUE == u8TestIntegrityFileGz(loc_ps8_error_gz))
		{
			printf("ExecuteGestionUpdateApp: Fichier initramfs_AP.bin.gz non corrompu ...\n");
			fclose (loc_p_handle);
			// On décompresse le fichier
			CmdSystem_Generique("gunzip -d %s", FICHIER_UPDATE_CPU_BIN_GZ);
			//On supprime le fichier testgz
			CmdSystem_Generique("rm %s",FICHIER_UPDATE_TESTGZ);
		}
		else
		{
			printf("ExecuteGestionUpdateApp: Fichier initramfs_AP.bin.gz corrompu ...\n");
			fclose (loc_p_handle);
			//On supprime le fichier
			CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN_GZ);
			//On supprime le fichier testgz
			CmdSystem_Generique("rm %s",FICHIER_UPDATE_TESTGZ);
		}
	}
	
	//On vérifie si il y a le fichier de mise à jour du logiciel CPU
	if(NULL != (loc_p_handle = fopen( FICHIER_UPDATE_CPU_BIN, "rb" ))) //CONDITION: fichier présent
	{
		fclose (loc_p_handle);
		
		if(0 == u32_size_file_app)
		{
			printf("ExecuteGestionUpdateApp: STARTING ...\n");
		}

		//Détermination taille du fichier
		loc_u32_size_file = u32GetSizeOfFile(FICHIER_UPDATE_CPU_BIN);

		if(loc_u32_size_file == u32_size_file_app) //CONDITION: taille du fichier stable
		{
			u16_cpt_test_update ++;
			u16_cpt_sans_update ++;
			if(u16_cpt_sans_update > TIMEOUT_SANS_UPDATE_APP)
			{
				//on annule le téléchargement
				printf("ExecuteGestionUpdateApp: CANCEL ...\n");

				//on supprime le fichier
				CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
			}
			else
			{
				//On vérifie l'intégrité du fichier tous les x secondes
				if(u16_cpt_test_update > TIMEOUT_TEST_UPDATE_APP)
				{
					u16_cpt_test_update = 0;	//RAZ
					
					if(loc_u32_size_file > sizeof(image_header_t)) //CONDITION: entete présent
					{
						if(TRUE == u8TestValidApp()) //CONDITION: Fichier valide
						{
							printf("ExecuteGestionUpdateApp: FICHIER VALIDE >>> COPIE EN FLASH ... [modeboot=%d]\n",e_modeboot_encours);
							
							switch(e_modeboot_encours)//mode où tourne le logiciel en ce momemt
							{
								case E_MODE_BOOT_AUCUN:
									//On met à jour APP1 par défaut
									//On efface la partition dans la FLASH NAND
									//On copie le fichier en nand
									CmdSystem_Generique("nandwrite -p %s %s",DEVICE_MTD_NAND_APP1,FICHIER_UPDATE_CPU_BIN);
									//Puis on met à jour les info systems
									if(TRUE == u8MiseAJourInfoSystem(E_MODE_BOOT_APP1, ps8_update__version_be_uboot))
									{
										printf("ExecuteGestionUpdateApp: DOWNLOAD APP1 TERMINE !!!\n");
										//on supprime le fichier
										CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
										sleep(1);
										//On envoie l'ordre du reset au process principal
//										OrdreResetUc(); //MISE A JOUR APP TERMINEE
										//On attend que le reset s'effectue (sinon on resete)
										sleep(15);
										CmdSystem_Generique("reboot &");
										sleep(5);
									}
									else
									{
										printf("ExecuteGestionUpdateApp: CANCEL ...\n");
										//on supprime le fichier
										CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
									}
									break;
								case E_MODE_BOOT_APP1:
									//On met à jour APP2
									//On efface la partition dans la FLASH NAND
//									CmdSystem_Generique("flash_eraseall -j %s",DEVICE_MTD_NAND_APP2); //JFFS2 - obso
									CmdSystem_Generique("flash_erase %s 0 0",DEVICE_MTD_NAND_APP2); //JFFS2
									//On copie le fichier en nand
									CmdSystem_Generique("nandwrite -p %s %s",DEVICE_MTD_NAND_APP2,FICHIER_UPDATE_CPU_BIN);
									//Puis on met à jour les info systems
									if(TRUE == u8MiseAJourInfoSystem(E_MODE_BOOT_APP2, ps8_update__version_be_uboot))
									{
										printf("ExecuteGestionUpdateApp: DOWNLOAD APP2 TERMINE !!!\n");
										//on supprime le fichier
										CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
										sleep(1);
										//On envoie l'ordre du reset au process principal
//										OrdreResetUc(); //MISE A JOUR APP TERMINEE
										//On attend que le reset s'effectue (sinon on resete)
										sleep(15);
										CmdSystem_Generique("reboot &");
										sleep(5);
									}
									else
									{
										printf("ExecuteGestionUpdateApp: CANCEL ...\n");
										//on supprime le fichier
										CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
									}
									break;
								case E_MODE_BOOT_APP2:
									//On met à jour APP1
									//On efface la partition dans la FLASH NAND
//									CmdSystem_Generique("flash_eraseall -j %s",DEVICE_MTD_NAND_APP1); //JFFS2	- obso
									CmdSystem_Generique("flash_erase %s 0 0",DEVICE_MTD_NAND_APP1); //JFFS2
									//On copie le fichier en nand
									CmdSystem_Generique("nandwrite -p %s %s",DEVICE_MTD_NAND_APP1,FICHIER_UPDATE_CPU_BIN);
									//Puis on met à jour les info systems
									if(TRUE == u8MiseAJourInfoSystem(E_MODE_BOOT_APP1, ps8_update__version_be_uboot))
									{
										printf("ExecuteGestionUpdateApp: DOWNLOAD APP1 TERMINE !!!\n");
										//on supprime le fichier
										CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
										sleep(1);
										//On envoie l'ordre du reset au process principal
//										OrdreResetUc(); //MISE A JOUR APP TERMINEE
										//On attend que le reset s'effectue (sinon on resete)
										sleep(15);
										CmdSystem_Generique("reboot &");
										sleep(5);
									}
									else
									{
										printf("ExecuteGestionUpdateApp: CANCEL ...\n");
										//on supprime le fichier
										CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
									}
									break;
								default:
									printf("ExecuteGestionUpdateApp: CANCEL ...\n");
									//on supprime le fichier
									CmdSystem_Generique("rm %s",FICHIER_UPDATE_CPU_BIN);
									break;
							}
						}
					}
				}
				//sinon on attend
			}
		}
		else
		{
			u32_size_file_app = loc_u32_size_file; //maj
			u16_cpt_test_update = 0;	//RAZ
			u16_cpt_sans_update = 0;	//RAZ
		}
	}
	else
	{
		u32_size_file_app = 0;	//RAZ
		u16_cpt_test_update = 0;	//RAZ
		u16_cpt_sans_update = 0;	//RAZ
	}
	
}/*ExecuteGestionUpdateApp*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_GestUpdate_App
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/12/2009 -
// Description	: Initialisation du module de gestupdate_app
//=====================================================================================
void InitModule_GestUpdate_App(void)
{
	u32_size_file_app = 0;	//INIT
	u16_cpt_test_update = 0;	//INIT
	u16_cpt_sans_update = 0;	//INIT
}/*InitModule_GestUpdate_App*/

