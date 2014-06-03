/*========================================================================*/
/* NOM DU FICHIER  : gestconf_sftp.h 	                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : JP                                                   */
/* Date			   : 25/10/2011                                           */
/* Libelle         : conf_sftp: gestion configuration par sFTP  		  */
/* Projet          : WRM100                                               */
/* Indice          : BE063                                                */
/*========================================================================*/
/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _GESTCONF_SFTP
#define _GESTCONF_SFTP_EXT
#else
#define _GESTCONF_SFTP_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/


/*_______IV - PROTOTYPES DEFINIS___________________________________________*/
//=====================================================================================
// Fonction		: u8TestChecksumConfSFTP
// Entrees		: rien
// Sortie		: <loc_u8_resultat>: 0:checksum absent du fichier, 1:checksum ko, 2: ok
// Auteur		: CM - 16/12/2009 -
// Description	: Test si le checksum du fichier est valide
//=====================================================================================
u8sod u8TestChecksumConfSFTP(void);

//=====================================================================================
// Fonction		: u8GestionConfSFTP
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/12/2009 -
// Description	: Gestion de la configuration par SFTP
//=====================================================================================
void u8GestionConfSFTP(void);

//=====================================================================================
// Fonction		: InitModule_GestConfsFTP
// Entrees		: rien
// Sortie		: rien
// Description	: Initialisation du module 
//=====================================================================================
void InitModule_GestConfsFTP(void);


/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
