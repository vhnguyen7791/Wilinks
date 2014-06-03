/*========================================================================*/
/* NOM DU FICHIER  : cip_snmpd.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/03/2010                                           */
/* Libelle         : Base de données: CIP pour processus snmpd			  */
/* Projet          : WRM100                                               */
/* Indice	       : BE013												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 02/03/2010 CM
// - CREATION
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _CIP_SNMPD
#define _CIP_SNMPD_EXT
#else
#define _CIP_SNMPD_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillCipSnmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 02/03/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillCipSnmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd);

//=====================================================================================
// Fonction		: u8EditCipSnmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 02/03/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditCipSnmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd);

//=====================================================================================
// Fonction		: Raz_Cip_Snmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: RAZ des ordres de la base de données de cip_snmpd
//=====================================================================================
void Raz_Cip_Snmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd);

//=====================================================================================
// Fonction		: InitBDD_Cip_Snmpd
// Entrees		: <loc_ps_cip_snmpd< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation de la base de données de cip_snmpd
//=====================================================================================
void InitBDD_Cip_Snmpd(S_STRUCT_CIP_SNMPD *loc_ps_cip_snmpd);

//=====================================================================================
// Fonction		: InitModule_Cip_Snmpd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/03/2010 -
// Description	: Initialisation du module de cip_snmpd
//=====================================================================================
void InitModule_Cip_Snmpd(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
