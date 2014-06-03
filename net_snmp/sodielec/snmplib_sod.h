/*========================================================================*/
/* NOM DU FICHIER  : snmplib_sod.h		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM													  */
/* Date			   : 05/03/2010                                           */
/* Libelle         : SNMPD: Define pour snmplib/snmp_api.c		          */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 CM 05/03/2010
// - CREATION
// - Correction package net-snmp pour limiter nombre max de requete par destinataire
//		dans le but de ne pas trop utiliser de mémoire
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/002_netsnmp_sodielec.patch
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

//Définition du nombre max de request par session (=destinataire)
//pour ne pas utiliser trop de mémoire
#define NB_MAX_ISP_PENDING_REQUEST  50


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

