/*========================================================================*/
/* NOM DU FICHIER  : execrestoretime.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/06/2010                                           */
/* Libelle         : RESTORETIME: Processus de restauration heure		  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECRESTORETIME


/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"
#include "execrestoretime.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0);

//=====================================================================================
// Fonction		: proc_Usage
// Entrees		: <loc_ps8_argv0<
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: affiche information utilisation du processus
//=====================================================================================
void proc_Usage(s8sod *loc_ps8_argv0)
{
	printf("Usage: %s\n"
		   ,loc_ps8_argv0);
}/*proc_Usage*/

//=====================================================================================
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: PROCESSUS RESTORETIME
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	printf("Debut processus restoretime... \n");

	InitModule_ExecRestoretime();

	//Initialisation des autres modules du processus
	InitModule_InfoTime();

	//Initialisation des modules de la librairie system
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(printf);

	//Restauration de l'heure au démarrrage
	RestoreTimeFromFlash();

	//On informe le processus savetime de la position / numéro partition en cours
	WriteInfoTime(FILE_TIME_INFO_DLG);
	
	printf("Fin processus restoretime. \n");
	return 0;
}/*main*/

//=====================================================================================
// Fonction		: RestoreTimeFromFlash
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: restaure au démarrage la date/heure de la FLASH NOR
//=====================================================================================
void RestoreTimeFromFlash(void)
{
	S_STRUCT_DATE loc_s_date;
	u8sod	loc_u8_flag_part1_ok;
	u8sod	loc_u8_flag_part2_ok;
	u32sod	loc_u32_time1;
	u32sod	loc_u32_time2;
	u32sod	loc_u32_idx_pos1;
	u32sod	loc_u32_idx_pos2;

	InitStructDate(&loc_s_date);	//INIT
	loc_s_date = S_DATE_DEFAUT;	//INIT
	loc_u8_flag_part1_ok = FALSE; //INIT
	loc_u8_flag_part2_ok = FALSE; //INIT
	loc_u32_time1 = VALEUR_TIME_VIERGE;	//INIT
	loc_u32_time2 = VALEUR_TIME_VIERGE;	//INIT
	
	//Lecture des 2 partitions de time_save
	//on copie dans le système de fichier l'image des partitions
	CmdSystem_Generique("dd if=%s of=%s >/dev/null 2>&1",
						DEVICE_MTD_NOR_TIMESAVE1,
						FILE_TIMESAVE1_BINARY);
	CmdSystem_Generique("dd if=%s of=%s >/dev/null 2>&1",
						DEVICE_MTD_NOR_TIMESAVE2,
						FILE_TIMESAVE2_BINARY);

	//on analyse chaque partition
	loc_u8_flag_part1_ok = u8ReadImageTimePartition(DEVICE_MTD_NOR_TIMESAVE1, &loc_u32_idx_pos1, &loc_u32_time1);
	loc_u8_flag_part2_ok = u8ReadImageTimePartition(DEVICE_MTD_NOR_TIMESAVE2, &loc_u32_idx_pos2, &loc_u32_time2);

	printf("********************************************************\n");
	printf("** RESTAURATION TIME \n");
	printf("** PARTITION TIME_SAVE_1: flag=%s time=%08lX position=%lu \n",
		  (TRUE == loc_u8_flag_part1_ok)?"OK":"KO",
		  loc_u32_time1,
		  loc_u32_idx_pos1);
	printf("** PARTITION TIME_SAVE_2: flag=%s time=%08lX position=%lu \n",
		   (TRUE == loc_u8_flag_part2_ok)?"OK":"KO",
		   loc_u32_time2,
		   loc_u32_idx_pos2);

	if((TRUE == loc_u8_flag_part1_ok)&&
	   (TRUE == loc_u8_flag_part2_ok)
	  )//CONDITION: les 2 partitions sont correctes
	{
		//on fait le choix du temps le plus récent
		if((VALEUR_TIME_VIERGE == loc_u32_time1)&&
		   (VALEUR_TIME_VIERGE == loc_u32_time2)
		  )
		{
			//On sélectionne la partition 1
			u32_idx_position_time = 0;
			u8_ispartition_first = TRUE;
		}
		else
		{
			if((VALEUR_TIME_VIERGE != loc_u32_time1)&&
			   (VALEUR_TIME_VIERGE != loc_u32_time2)
			  )
			{
				//on sélectionne la partition avec position la plus petite
				if(loc_u32_idx_pos2 > loc_u32_idx_pos1)
				{
					//On sélectionne la partition 1
					u32_idx_position_time = loc_u32_idx_pos1;
					u8_ispartition_first = TRUE;
					loc_s_date = sConvertTimeToDate((time_t)(loc_u32_time1+OFFSET_RESTORETIME));
					//on efface la partition 2
					printf("RestoreTimeFromFlash: erase partition 2\n");
					CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE2);
				}
				else
				{
					//On sélectionne la partition 2
					u32_idx_position_time = loc_u32_idx_pos2;
					u8_ispartition_first = FALSE;
					loc_s_date = sConvertTimeToDate((time_t)(loc_u32_time2+OFFSET_RESTORETIME));
					printf("RestoreTimeFromFlash: erase partition 1\n");
					CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE1);
				}
			}
			else //CONDITION: une des 2 valeurs est bonne
			{
				if(VALEUR_TIME_VIERGE != loc_u32_time1)
				{
					//On sélectionne la partition 1
					u32_idx_position_time = loc_u32_idx_pos1;
					u8_ispartition_first = TRUE;
					loc_s_date = sConvertTimeToDate((time_t)(loc_u32_time1+OFFSET_RESTORETIME));
				}
				else //VALEUR_TIME_VIERGE != loc_u32_time2
				{
					//On sélectionne la partition 2
					u32_idx_position_time = loc_u32_idx_pos2;
					u8_ispartition_first = FALSE;
					loc_s_date = sConvertTimeToDate((time_t)(loc_u32_time2+OFFSET_RESTORETIME));
				}
			}
		}
	}
	else
	{
		if(TRUE == loc_u8_flag_part1_ok)
		{
			//On sélectionne la partition 1
			u32_idx_position_time = loc_u32_idx_pos1;
			u8_ispartition_first = TRUE;
			if(VALEUR_TIME_VIERGE != loc_u32_time1)
			{
				loc_s_date = sConvertTimeToDate((time_t)(loc_u32_time1+OFFSET_RESTORETIME));
			}
		}
		else
		{
			if(TRUE == loc_u8_flag_part2_ok)
			{
				//On sélectionne la partition 2
				u32_idx_position_time = loc_u32_idx_pos2;
				u8_ispartition_first = FALSE;
				if(VALEUR_TIME_VIERGE != loc_u32_time2)
				{
					loc_s_date = sConvertTimeToDate((time_t)(loc_u32_time2+OFFSET_RESTORETIME));
				}
			}
			else //CONDTION: toutes les partitions sont KO
			{
				//on efface la partition 1
				printf("RestoreTimeFromFlash: erase partition 1\n");
				CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE1);
				//on efface la partition 2
				printf("RestoreTimeFromFlash: erase partition 2\n");
				CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE2);
				//On sélectionne la partition 1
				u32_idx_position_time = 0;
				u8_ispartition_first = TRUE;
			}
		}
	}

	//Mise à l'heure du système
	printf("***** SELECTION partition %s position %lu \n",
		   (TRUE == u8_ispartition_first)?"1":"2", u32_idx_position_time);
	printf("***** MISE A L'HEURE: %s *** \n",
		   ps8GetChDate(&loc_s_date));
	printf("********************************************************\n");
	CmdSysteme_MiseAHeure(&loc_s_date);

	//On fait du menage
	CmdSystem_Generique("rm %s",
						FILE_TIMESAVE1_BINARY);
	CmdSystem_Generique("rm %s",
						FILE_TIMESAVE2_BINARY);
	
}/*RestoreTimeFromFlash*/

//=====================================================================================
// Fonction		: u8ReadImageTimePartition
// Entrees		: <loc_ps8_fileimage<: fichier image de la partition
//				  <loc_pu32_new_position<: nouvelle position
//				  <loc_pu32_time_read<: valeur du temps lu
// Sortie		: <loc_u8_resultat>: TRUE ou FALSE
// Auteur		: CM - 30/06/2010 -
// Description	: Lecture de l'image de la partition time_save (et on s'assure que l'image est propre)
//=====================================================================================
u8sod u8ReadImageTimePartition(s8sod *loc_ps8_fileimage, u32sod *loc_pu32_new_position, u32sod *loc_pu32_time_read)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	u32sod	loc_u32_cpt;
	u8sod	loc_pu8_datatime[NB_MAX_DATA_TIME+1];
	union 
	{
		u8sod		pu8_term[4];
		u32sod		u32_term;
	} loc_u_tempo32bit;
	u32sod loc_u32_val1;
	u32sod loc_u32_val2;
	u8sod	loc_u8_isFlashVierge;

	loc_u8_resultat = TRUE; //INIT
	loc_p_handle = NULL; //INIT
	loc_u32_cpt = 0;	//INIT
	memset(loc_pu8_datatime, 0, NB_MAX_DATA_TIME);	//INIT
	loc_u_tempo32bit.u32_term = 0; //INIT
	loc_u32_val1 = 0; //INIT
	loc_u32_val2 = 0; //INIT
	loc_u8_isFlashVierge = FALSE; //INIT

	*loc_pu32_time_read = VALEUR_TIME_VIERGE;	//INIT
	*loc_pu32_new_position = TAILLE_MAX_PARTITION_TIME_SAVE+1;	//INIT
	
	if(NULL != (loc_p_handle = fopen( loc_ps8_fileimage, "rb" ))) //CONDITION: fichier présent
	{
		//on lit la totalité de l'image
		loc_u32_cpt = 0;//RAZ
		do{
			if (NB_MAX_DATA_TIME == fread(loc_pu8_datatime, sizeof(u8sod), NB_MAX_DATA_TIME, loc_p_handle))
			{
				//Lecture de la première valeur
				loc_u_tempo32bit.pu8_term[0] = loc_pu8_datatime[0];
				loc_u_tempo32bit.pu8_term[1] = loc_pu8_datatime[1];
				loc_u_tempo32bit.pu8_term[2] = loc_pu8_datatime[2];
				loc_u_tempo32bit.pu8_term[3] = loc_pu8_datatime[3];
				loc_u32_val1 = loc_u_tempo32bit.u32_term;
				//Lecture de la seconde valeur
				loc_u_tempo32bit.pu8_term[0] = loc_pu8_datatime[4];
				loc_u_tempo32bit.pu8_term[1] = loc_pu8_datatime[5];
				loc_u_tempo32bit.pu8_term[2] = loc_pu8_datatime[6];
				loc_u_tempo32bit.pu8_term[3] = loc_pu8_datatime[7];
				loc_u32_val2 = loc_u_tempo32bit.u32_term;

				if((VALEUR_TIME_VIERGE == loc_u32_val1)&&
				   (VALEUR_TIME_VIERGE == loc_u32_val2)
				  )//CONDITION: ZONE FLASH VIDE
				{
					loc_u8_isFlashVierge = TRUE;	//on signale qu'à partir de maintenant la FLASH doit etre vierge
				}
				else
				{
					if(FALSE == loc_u8_isFlashVierge) //CONDITION: FLASH ne doit pas etre détectée vierge
					{
						if(loc_u32_val1 == loc_u32_val2) //CONDITION: valeurs identiques
						{
							*loc_pu32_time_read = loc_u32_val1;
							*loc_pu32_new_position = (loc_u32_cpt + NB_MAX_DATA_TIME);
						}
						else
						{
							//on ne lit pas la valeur du temps
							//on saute
							*loc_pu32_new_position = (loc_u32_cpt + NB_MAX_DATA_TIME);
							loc_u8_isFlashVierge = TRUE;	//on signale qu'à partir de maintenant la FLASH doit etre vierge
						}
					}
					else //CONDITION: FLASH détectée non vierge
					{
						//C'est donc que le contenu de la FLASH n'est pas valide
						printf("u8ReadImageTimePartition: partition non valide %s position %lu \n",loc_ps8_fileimage, loc_u32_cpt);
						loc_u32_cpt = TAILLE_MAX_PARTITION_TIME_SAVE+1;	//on sort
						loc_u8_resultat = FALSE;
					}
				}
				loc_u32_cpt += NB_MAX_DATA_TIME;
			}
			else
			{
				printf("u8ReadImageTimePartition: erreur lecture %s position %lu \n",loc_ps8_fileimage, loc_u32_cpt);
				loc_u32_cpt = TAILLE_MAX_PARTITION_TIME_SAVE+1;	//on sort
				loc_u8_resultat = FALSE;
			}
		}while((TRUE == loc_u8_resultat)&&
			   (loc_u32_cpt<TAILLE_MAX_PARTITION_TIME_SAVE));
	}
	else
	{
		printf("u8ReadImageTimePartition: Lecture impossible %s \n",loc_ps8_fileimage);
		loc_u8_resultat = FALSE;
	}

	
	return loc_u8_resultat;
}/*u8ReadImageTimePartition*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecRestoretime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Initialisation du module de ExecRestoretime
//=====================================================================================
void InitModule_ExecRestoretime(void)
{
	
}/*InitModule_ExecRestoretime*/

