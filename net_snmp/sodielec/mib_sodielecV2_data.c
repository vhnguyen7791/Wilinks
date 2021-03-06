/*========================================================================*/
/* NOM DU FICHIER  : mib_sodielecV2_data.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : NET-SNMP: MIB SODIELECV2							  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
/*
 * Note: this file originally auto-generated by mib2c using
 *         mib2c.sodielec_format.conf, v1.0 Juin 2006
 * Version: PC_SOUS_LINUX: 0, CARTE_EVAL: 0 [oui(1), non(0)]
 * Date: Mon Jun 12 10:32:20 2006
 */
/*========================================================================*/

/*_______II - DEFINE ______________________________________________________*/
#define MIB_SODIELECV2_DATA_H

/*_______III - INCLUDES - DIRECTIVES ______________________________________*/
#include "headers.h"
#include "mib_sodielecV2_data.h"

/*_______IV  - PROTOTYPES IMPORTES _____________________MODULE______________*/
/** Function declarations */
/** ** for MIB Tree       */

/** ** for Tables         */

/*_______VI  - PROCEDURES __________________________________________________*/
/** Capture functions */
/** ** for MIB Tree       */
char *
   captureString_sodielecV2(int vpmagic, WriteMethod ** write_method)
{
	s8sod loc_ps8_chaine[100];
	s8sod *loc_ps8_cp;
	loc_ps8_cp = NULL;
	
	switch (vpmagic) {
		case INFOCONSTRUCTEUR:
			loc_ps8_cp = (s8sod *)S_CONFIG_CONSTRUCTEUR_DEFAUT.ps8_nom;
			break;
		case INFOTELEPHONE:
			loc_ps8_cp = (s8sod *)S_CONFIG_CONSTRUCTEUR_DEFAUT.ps8_numero_telephone;
			break;
		case INFOSITE:
			loc_ps8_cp = (s8sod *)S_CONFIG_CONSTRUCTEUR_DEFAUT.ps8_site_web;
			break;
		default:
			DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureString_sodielecV2\n", vpmagic));
			break;
	}
	return (char *) loc_ps8_cp;
}

long
   captureInt_sodielecV2(int vpmagic, WriteMethod ** write_method)
{
	long_return = 0; //INIT
	
	switch (vpmagic) {
		default:
			DEBUGMSGTL(("sodielec", "unknown sub-id %d in captureInt_sodielecV2\n", vpmagic));
			break;
	}
	return long_return;
}


/** ** for Tables         */

