/*========================================================================*/
/* NOM DU FICHIER  : infotime.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/06/2010                                           */
/* Libelle         : SAVETIME/RESTORETIME: module de dialogue			  */
/* Projet          : WRM100	                                              */
/* Indice          : BE035                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _INFOTIME

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: WriteInfoTime
// Entrees		: <loc_ps8_nomfichier< : Nom du fichier
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Ecriture du fichier d'information issu du processu restoretime
//=====================================================================================
void WriteInfoTime(s8sod *loc_ps8_nomfichier)
{
	FILE	*loc_p_handle;
	s8sod	loc_ps8_ligne[TAILLE_MAX_MSG_INFO_TIME+1];
	s32sod	loc_s32_numwritten;

	loc_p_handle = NULL;	//INIT
	strcpy(loc_ps8_ligne, ""); //INIT

	if(NULL != (loc_p_handle = fopen( loc_ps8_nomfichier, "wt" ))) //CONDITION: fichier présent
	{
		loc_s32_numwritten = fprintf(loc_p_handle, "%lu %lu\n",
									 (u32sod)u8_ispartition_first,
									 u32_idx_position_time);
		if(loc_s32_numwritten < 0)	//CONDITION: ecriture KO
		{
			printf("WriteInfoTime: Erreur ecriture %s \n",loc_ps8_nomfichier);
		}
		fclose (loc_p_handle);
	}
	else
	{
		printf("WriteInfoTime: Lecture impossible %s \n",loc_ps8_nomfichier);
	}


}/*WriteInfoTime*/

//=====================================================================================
// Fonction		: ReadInfoTime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Lecture du fichier d'information issu du processu restoretime
//=====================================================================================
void ReadInfoTime(void)
{
	u8sod	loc_u8_resultat;
	FILE	*loc_p_handle;
	s8sod	*loc_ps8_result_fgets;
	s8sod	loc_ps8_ligne[TAILLE_MAX_MSG_INFO_TIME+1];
	s32sod	loc_s32_sscanf;
	u32sod	loc_u32_valeur;

	loc_u8_resultat = TRUE;	//INIT
	loc_p_handle = NULL;	//INIT
	loc_ps8_result_fgets = NULL;	//INIT
	strcpy(loc_ps8_ligne, ""); //INIT
	loc_s32_sscanf = 0; //INIT
	loc_u32_valeur = 0;	//INIT
	
	if(NULL != (loc_p_handle = fopen( FILE_TIME_INFO_DLG, "rt" ))) //CONDITION: fichier présent
	{
		loc_ps8_result_fgets = fgets(loc_ps8_ligne,TAILLE_MAX_MSG_INFO_TIME,loc_p_handle);
		if(NULL != loc_ps8_result_fgets) //CONDITION: ligne lue
		{
			loc_s32_sscanf = sscanf(loc_ps8_ligne, "%lu %lu",
									&loc_u32_valeur,
								    &u32_idx_position_time);
			
			u8_ispartition_first = (u8sod)loc_u32_valeur;
			printf("ReadInfoTime: Lecture partition %d position %lu \n",  u8_ispartition_first,u32_idx_position_time);
			
			if(((TRUE != u8_ispartition_first)&&
			    (FALSE != u8_ispartition_first))||
			   (u32_idx_position_time > (TAILLE_MAX_PARTITION_TIME_SAVE+1))
			  )//CONDITION: informations erronées
			{
				//Normalement, on ne doit jamais passé ici
				printf("ReadInfoTime: LECTURE KO \n");
				loc_u8_resultat = FALSE;
			}
		}
		fclose (loc_p_handle);
	}
	else
	{
		loc_u8_resultat = FALSE;
		printf("ReadInfoTime: Lecture impossible %s \n",FILE_TIME_INFO_DLG);
	}

	if(FALSE == loc_u8_resultat) //CONDITION: ERREUR LECTURE INFO
	{
		u32_idx_position_time = 0;	//RAZ
		u8_ispartition_first = TRUE;	//RAZ
		printf("ReadInfoTime: erase partition %s \n",(TRUE == u8_ispartition_first)?"1":"2");
		CmdSystem_Generique("flash_eraseall %s >/dev/null 2>&1",DEVICE_MTD_NOR_TIMESAVE1);
	}
	
}/*ReadInfoTime*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_InfoTime
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 30/06/2010 -
// Description	: Initialisation du module de infotime
//=====================================================================================
void InitModule_InfoTime(void)
{
	u32_idx_position_time = 0;	//INIT
	u8_ispartition_first = TRUE;	//INIT
	
}/*InitModule_InfoTime*/

