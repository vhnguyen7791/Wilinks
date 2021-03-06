/*========================================================================*/
/* NOM DU FICHIER  : infosystem.c   		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 21/12/2009                                           */
/* Libelle         : Base de donn�es: gestion partition infosystem		  */
/* Projet          : WRM100                                               */
/* Indice          : BE014                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE002 21/12/09 CM
// - CREATION
//BE010 03/02/2010 CM
// - Modification processus update (independance avec principal)
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _INFOSYSTEM

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8MiseAJourInfoSystem
// Entrees		: <loc_u8_mode> : mode app � activer
//				: <loc_ps8_version_uboot< : version u-boot
// Sortie		: <loc_u8_resultat>: TRUE,sinon FALSE
// Auteur		: CM - 18/12/2009 -
// Description	: Mise � jour info syst�me
//=====================================================================================
/*u8sod u8MiseAJourInfoSystem(u8sod loc_u8_mode, s8sod *loc_ps8_version_uboot)
{
	u8sod loc_u8_resultat;
	u16sod loc_u16_length;
	u16sod loc_u16_i;
	u16sod loc_u16_checksum_calcul;
	u8sod	loc_pu8_infosystem[NB_MAX_DATA_INFOSYSTEM];
	FILE	*loc_p_handle;
	s32sod	loc_s32_fwrite;

	loc_u8_resultat = TRUE; //INIT
	loc_u16_length = NB_MIN_DATA_INFOSYSTEM; //INIT
	loc_u16_checksum_calcul = 0; //INIT
	for(loc_u16_i=0;loc_u16_i<NB_MAX_DATA_INFOSYSTEM;loc_u16_i++)
	{
		loc_pu8_infosystem[loc_u16_i] = 0xFF; //INIT
	}
	loc_p_handle = NULL; //INIT
	loc_s32_fwrite = -1;	//INIT

	printf("MISE A JOUR INFO SYSTEM ==> APP%d ACTIF\n",loc_u8_mode);

	//Formatage des donn�es
	loc_pu8_infosystem[INFOSYS_START] = VALEUR_INFOSYSSTART;
	loc_pu8_infosystem[INFOSYS_LENGTH] = (u8sod)(loc_u16_length & 0x00FF); //LSB
	loc_pu8_infosystem[INFOSYS_LENGTH+1] = (u8sod)((loc_u16_length & 0xFF00)>>8); //MSB
	for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_VALEUR_INFOSYSVERSION;loc_u16_i++)
	{
		loc_pu8_infosystem[INFOSYS_VERSION+loc_u16_i] = loc_ps8_version_uboot[loc_u16_i];	//ne pas caster (car il faut conserver tous les bits)
	}
	loc_pu8_infosystem[INFOSYS_APP_ACTIF] = loc_u8_mode;

	//Calcul checksum
	for(loc_u16_i=0;loc_u16_i<loc_u16_length-2;loc_u16_i++)
	{
		loc_u16_checksum_calcul += (u16sod)loc_pu8_infosystem[loc_u16_i];
	}
	loc_pu8_infosystem[loc_u16_length-2] = (u8sod)(loc_u16_checksum_calcul & 0x00FF); //LSB
	loc_pu8_infosystem[loc_u16_length-1] = (u8sod)((loc_u16_checksum_calcul & 0xFF00)>>8); //MSB

	//On �crit dans un fichier ce tableau
	if(NULL != (loc_p_handle = fopen( FILE_INFOSYSTEM_X, "wb" ))) //CONDITION: fichier pr�sent
	{
		loc_s32_fwrite = fwrite(loc_pu8_infosystem, sizeof(u8sod), NB_MAX_DATA_INFOSYSTEM, loc_p_handle);
		if(NB_MAX_DATA_INFOSYSTEM != loc_s32_fwrite)
		{
			printf("u8MiseAJourInfoSystem: Probleme ecriture %s (seulement %ld octets �crits)\n",
				   FILE_INFOSYSTEM_X,loc_s32_fwrite);
			loc_u8_resultat = FALSE;
		}
		fclose (loc_p_handle);

		if(TRUE == loc_u8_resultat)
		{
			//On sauve info system 1
			printf("Sauvegarde info systeme 1\n");
			CmdSystem_Generique("flash_eraseall %s",DEVICE_MTD_NOR_INFOSYSTEM1);
			CmdSystem_Generique("dd if=%s of=%s bs=%d count=1",
								FILE_INFOSYSTEM_X,
								DEVICE_MTD_NOR_INFOSYSTEM1,
								NB_MAX_DATA_INFOSYSTEM);

			//On sauve info system 2
			printf("Sauvegarde info systeme 2\n");
			CmdSystem_Generique("flash_eraseall %s",DEVICE_MTD_NOR_INFOSYSTEM2);
			CmdSystem_Generique("dd if=%s of=%s bs=%d count=1",
								FILE_INFOSYSTEM_X,
								DEVICE_MTD_NOR_INFOSYSTEM2,
								NB_MAX_DATA_INFOSYSTEM);
		}
	}
	else
	{
		printf("u8MiseAJourInfoSystem: Probleme ouverture fichier %s \n",FILE_INFOSYSTEM_X);
	}

	return loc_u8_resultat;

}*//*u8MiseAJourInfoSystem*/


/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_InfoSystem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 21/12/2009 -
// Description	: Initialisation du module de infosystem
//=====================================================================================
void InitModule_InfoSystem(void)
{
	
}/*InitModule_InfoSystem*/

