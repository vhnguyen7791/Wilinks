/*========================================================================*/
/* NOM DU FICHIER  : execgetversionuboot.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 17/12/2009                                           */
/* Libelle         : getversion_uboot: Processus r�cup�re version U-BOOT  */
/* Projet          : WRM100	                                              */
/* Indice          : BE002                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 17/12/09 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _EXECGETVERSIONUBOOT


/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"
#include "../Update/execupdate.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: main
// Entrees		: <loc_s32_argc<: nombre d'arguments
//				  <loc_pps8_argv<: tableau de pointeur de chaque argument
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: PROCESSUS getversion_uboot
//=====================================================================================
int main(int loc_s32_argc, s8sod *loc_pps8_argv[]) 
{
	FILE	*loc_p_handle;
	u16sod	loc_u16_i;
	u8sod	loc_pu8_infosystem[NB_MAX_DATA_INFOSYSTEM];
	s32sod	loc_s32_numread;

	
	InitModule_ExecGetVersionUboot();
	loc_p_handle = NULL; //INIT
	for(loc_u16_i=0;loc_u16_i<NB_MAX_DATA_INFOSYSTEM;loc_u16_i++)
	{
		loc_pu8_infosystem[loc_u16_i] = 0xFF; //INIT
	}
	loc_s32_numread = 0;	//INIT

	//V�rification si fichier binaire info syst�me pr�sent (Normalement info system 1 valid)
	if(NULL != (loc_p_handle = fopen( FILE_INFOSYSTEM_1, "rb" ))) //CONDITION: fichier pr�sent
	{

		for(loc_u16_i=0;loc_u16_i<NB_MAX_DATA_INFOSYSTEM;loc_u16_i++)
		{
			loc_s32_numread = fread(&loc_pu8_infosystem[loc_u16_i], sizeof(u8sod), 1, loc_p_handle);
			if (0 == loc_s32_numread) //CONDITION: probl�me lecture
			{
				printf("getversion_uboot: probl�me lecture fichier %s [2]\n",FILE_INFOSYSTEM_1);
				loc_u16_i = NB_MAX_DATA_INFOSYSTEM+1; //on sort
			}
		}
		fclose (loc_p_handle);

		if (0 != loc_s32_numread) //CONDITION: lecture OK
		{
			printf("getversion_uboot: Test validite info system ... :");
			if(TRUE == u8TestValidInfoSystem(loc_pu8_infosystem))
			{
				printf("OK\n");
				//On r�cup�re la version UBOOT et on copie dans uboot.ini
				if(NULL != (loc_p_handle = fopen( FILE_UBOOT_INIT, "wt" ))) //CONDITION: fichier pr�sent
				{
					printf("getversion_uboot: %s\n",&loc_pu8_infosystem[INFOSYS_VERSION]);
					fprintf(loc_p_handle,"%s",&loc_pu8_infosystem[INFOSYS_VERSION]);
					
					fclose (loc_p_handle);
				}
			}
			else
			{
				printf("KO\n");
			}
		}
		

	}
	else
	{
		printf("getversion_uboot: probl�me lecture fichier %s [1]\n",FILE_INFOSYSTEM_1);
	}


	
	return 0;
}/*main*/

//=====================================================================================
// Fonction		: u8TestValidInfoSystem
// Entrees		: <loc_pu8_infosystem< : pointeur sur zone info systeme
// Sortie		: <loc_u8_resultat>: TRUE, sinon FALSE
// Auteur		: CM - 16/12/2009 -
// Description	: Test si les infos syst�mes sont valides
//=====================================================================================
u8sod u8TestValidInfoSystem(u8sod *loc_pu8_infosystem)
{
	u8sod loc_u8_resultat;
	u16sod loc_u16_length;
	u16sod loc_u16_i;
	u16sod loc_u16_checksum_calcul;
	u16sod loc_u16_checksum_lu;


	loc_u8_resultat = TRUE; //INIT
	loc_u16_length = 0;	//INIT
	loc_u16_i = 0;	//INIT
	loc_u16_checksum_calcul = 0;	//INIT
	loc_u16_checksum_lu = 0xFFFF;	//INIT

	if(VALEUR_INFOSYSSTART == loc_pu8_infosystem[INFOSYS_START])
	{
		loc_u16_length = (u16sod)loc_pu8_infosystem[INFOSYS_LENGTH]; //LSB
		loc_u16_length += (u16sod)((u16sod)loc_pu8_infosystem[INFOSYS_LENGTH+1] << 8); //MSB
		if((NB_MIN_DATA_INFOSYSTEM <= loc_u16_length) && (loc_u16_length < NB_MAX_DATA_INFOSYSTEM)) //CONDITION: longueur coh�rente
		{
			//Calcul du checksum sur les donn�es (sauf les 2 octets du checksum)
			for(loc_u16_i=0;loc_u16_i<(loc_u16_length-2);loc_u16_i++)	
			{
				loc_u16_checksum_calcul += (u16sod)loc_pu8_infosystem[loc_u16_i];
			}
			//Lecture du checksum
			loc_u16_checksum_lu = (u16sod)loc_pu8_infosystem[loc_u16_length-2]; //LSB
			loc_u16_checksum_lu += (u16sod)((u16sod)loc_pu8_infosystem[loc_u16_length-1] << 8); //MSB

			if(loc_u16_checksum_lu == loc_u16_checksum_calcul) //CONDITION: checksum OK
			{
				if((E_MODE_BOOT_APP1 != loc_pu8_infosystem[INFOSYS_APP_ACTIF])&&
				   (E_MODE_BOOT_APP2 != loc_pu8_infosystem[INFOSYS_APP_ACTIF])
				  )
				{
					loc_u8_resultat = FALSE;
					printf ("INFOSYS_APP_ACTIF=%d: ",loc_pu8_infosystem[INFOSYS_APP_ACTIF]);
				}

			}
			else //CONDITION: checksum KO
			{
				loc_u8_resultat = FALSE;
				printf ("chk_lu=%04X / chk_calcul=%04X: ",loc_u16_checksum_lu, loc_u16_checksum_calcul);
			}
		}
		else //CONDITION: longueur incoh�rente
		{
			loc_u8_resultat = FALSE;
			printf ("longueur=%d: ",loc_u16_length);
		}
	}
	else
	{
		loc_u8_resultat = FALSE;
		printf ("start=%02X: ",loc_pu8_infosystem[INFOSYS_START]);
	}

	return loc_u8_resultat;
}/*u8TestValidInfoSystem*/


/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_ExecGetVersionUboot
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 17/12/2009 -
// Description	: Initialisation du module de ExecGetVersionUboot
//=====================================================================================
void InitModule_ExecGetVersionUboot(void)
{
	
}/*InitModule_ExecGetVersionUboot*/

