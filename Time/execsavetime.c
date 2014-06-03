/*========================================================================*/
/* NOM DU FICHIER  : execsavetime.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/06/2010                                           */
/* Libelle         : SAVETIME: Processus de sauvegarde heure			  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECSAVETIME

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"
#include "execsavetime.h"

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
// Description	: PROCESSUS SAVETIME
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	printf("Debut processus savetime... \n");

	InitModule_ExecSavetime();

	//Initialisation des autres modules du processus
	InitModule_InfoTime();

	//Initialisation des modules de la librairie system
	InitModule_LibrarySystem();
	SetConfig_LibrarySystem(printf);

	//Récupération position / numéro partition en cours
	ReadInfoTime();

	//on passe dans la tache de fond
	do{
		
		sleep(1);

		//sauvegarde de l'heure
		SaveTimeToFlash();
		
	}while(1);
	
	
	return 0;
}/*main*/

//=====================================================================================
// Fonction		: SaveTimeToFlash
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Sauve la date/heure dans la FLASH NOR
//=====================================================================================
void SaveTimeToFlash(void)
{
	time_t	loc_s_time_t;

	//Lecture de l'heure courante
	time(&loc_s_time_t);

	if(u32_idx_position_time > TAILLE_MAX_PARTITION_TIME_SAVE) //CONDITION: position hors de la partition
	{
		//on efface l'autre partition
		if(TRUE == u8_ispartition_first) //CONDITION: Première partition en cours
		{
			u8_ispartition_first = FALSE;
			CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE2);
		}
		else //CONDITION: Seconde partition en cours
		{
			u8_ispartition_first = TRUE;
			CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE1);
		}
		//on raz index de position
		u32_idx_position_time = 0;	//RAZ
		printf("Savetime: erase partition %s \n",(TRUE == u8_ispartition_first)?"1":"2");
	}

	//On sauve l'heure dans la FLASH NOR à la position
	if(TRUE == u8CreateFileTimeBinary((u32sod)loc_s_time_t))
	{
		//d: debug
		WriteInfoTime(FILE_TIME_INFO_STA);
//		printf("position = %lu dans partition %s\n",u32_idx_position_time,(TRUE == u8_ispartition_first)?"1":"2");
//		CmdSystem_Generique("hexdump -v %s",FILE_MINITIME_BINARY);
		//f: debug
		
		if(TRUE == u8_ispartition_first) //CONDITION: Première partition en cours
		{
			CmdSystem_Generique("dd if=%s of=%s bs=%d seek=%lu count=1 >/dev/null 2>&1",
								FILE_MINITIME_BINARY,
								DEVICE_MTD_NOR_TIMESAVE1,
								NB_MAX_DATA_TIME,
								u32_idx_position_time/NB_MAX_DATA_TIME);
		}
		else //CONDITION: Seconde partition en cours
		{
			CmdSystem_Generique("dd if=%s of=%s bs=%d seek=%lu count=1 >/dev/null 2>&1",
								FILE_MINITIME_BINARY,
								DEVICE_MTD_NOR_TIMESAVE2,
								NB_MAX_DATA_TIME,
								u32_idx_position_time/NB_MAX_DATA_TIME);
		}
		u32_idx_position_time += NB_MAX_DATA_TIME;
	}
}/*SaveTimeToFlash*/

//=====================================================================================
// Fonction		: u8CreateFileTimeBinary
// Entrees		: <loc_u32_time>
// Sortie		: <loc_u8_resultat>: TRUE ou FALSE
// Auteur		: CM - 30/06/2010 -
// Description	: Création du fichier binaire minitime.bin (contenu à sauver dans la FLASH NOR)
//=====================================================================================
u8sod u8CreateFileTimeBinary(u32sod loc_u32_time)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s32sod	loc_s32_fwrite;
	u8sod	loc_pu8_datatime[NB_MAX_DATA_TIME+1];
	union 
	{
		u8sod		pu8_term[4];
		u32sod		u32_term;
	} loc_u_tempo32bit;

	loc_u8_resultat = TRUE;	//INIT
	loc_p_handle = NULL; //INIT
	loc_s32_fwrite = -1;	//INIT
	memset(loc_pu8_datatime, 0, NB_MAX_DATA_TIME);	//INIT

	loc_u_tempo32bit.u32_term = loc_u32_time; //INIT
	loc_pu8_datatime[0] = loc_u_tempo32bit.pu8_term[0];
	loc_pu8_datatime[1] = loc_u_tempo32bit.pu8_term[1];
	loc_pu8_datatime[2] = loc_u_tempo32bit.pu8_term[2];
	loc_pu8_datatime[3] = loc_u_tempo32bit.pu8_term[3];
	loc_pu8_datatime[4] = loc_u_tempo32bit.pu8_term[0];
	loc_pu8_datatime[5] = loc_u_tempo32bit.pu8_term[1];
	loc_pu8_datatime[6] = loc_u_tempo32bit.pu8_term[2];
	loc_pu8_datatime[7] = loc_u_tempo32bit.pu8_term[3];
	
	if(NULL != (loc_p_handle = fopen( FILE_MINITIME_BINARY, "wb" ))) //CONDITION: fichier présent
	{
		loc_s32_fwrite = fwrite(loc_pu8_datatime, sizeof(u8sod), NB_MAX_DATA_TIME, loc_p_handle);
		if(NB_MAX_DATA_TIME != loc_s32_fwrite)
		{
			printf("u8CreateFileTimeBinary: Probleme ecriture %s (seulement %ld octets écrits)\n",
				   FILE_MINITIME_BINARY,loc_s32_fwrite);
			loc_u8_resultat = FALSE;
		}
		fclose (loc_p_handle);
	}
	else
	{
		printf("u8CreateFileTimeBinary: Impossible ouverture en ecriture %s\n",
			   FILE_MINITIME_BINARY);
		loc_u8_resultat = FALSE;
	}

	return loc_u8_resultat;

}/*u8CreateFileTimeBinary*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecSavetime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Initialisation du module de ExecSavetime
//=====================================================================================
void InitModule_ExecSavetime(void)
{
	
}/*InitModule_ExecSavetime*/

