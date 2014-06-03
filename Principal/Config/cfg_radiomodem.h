/*========================================================================*/
/* NOM DU FICHIER  : cfg_radiomodem.h		                              */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 02/03/2010                                           */
/* Libelle         : Principal: Configuration du radio modem			  */
/* Projet          : WRM100                                               */
/* Indice          : BE013                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 02/03/2010 CM
// - CREATION
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_RADIOMODEM
#define _CFG_RADIOMODEM_EXT
#else
#define _CFG_RADIOMODEM_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: Install_RadioModem
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Installe la configuration du radio modem configuré
//		!!!!ATTENTION: CETTE FONCTION N'EST PAS PROTEGE PAR SEMAPHORE DE CONFIGURATION!!!!
//=====================================================================================
void Install_RadioModem(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: Uninstall_RadioModem
// Entrees		: <loc_ps_config< : pointeur sur ancienne configuration
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Désinstalle la configuration du radio modem configuré
//=====================================================================================
void Uninstall_RadioModem(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Cfg_RadioModem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de cfg_radiomodem
//=====================================================================================
void InitModule_Cfg_RadioModem(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

