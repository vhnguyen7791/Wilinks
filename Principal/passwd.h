/*========================================================================*/
/* NOM DU FICHIER  : passwd.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 30/05/2007											  */
/* Libelle         : Gestion des mots de passe pour login ftp et telnet   */
/* Projet          : WRM100                                               */
/* Indice          : BE036                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE036 02/07/2010 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _PASSWD
#define _PASSWD_EXT
#else
#define _PASSWD_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8SetPassword
// Entrees		: <loc_ps8_user<: nom de l'utilisateur
//				: <loc_ps8_password<: mot de passe
// Sortie		: <loc_u8_return>: TRUE si réussie sinon FALSE
// Auteur		: 
// Description	: Fixe un mot de passe pour un utilisateur
//=====================================================================================
u8sod u8SetPassword(const s8sod *loc_ps8_user, const s8sod *loc_ps8_password);

//=====================================================================================
// Fonction		: u8SetShadow
// Entrees		: <loc_ps8_user<: nom de l'utilisateur
//				: <loc_ps8_password<: mot de passe
// Sortie		: <loc_u8_return>: TRUE si réussie sinon FALSE
// Auteur		: 
// Description	: Fixe un mot de passe pour un utilisateur dans /etc/shadow
//=====================================================================================
u8sod u8SetShadow(const s8sod *loc_ps8_user, const s8sod *loc_ps8_password);

//=====================================================================================
// Fonction		: Install_LoginPassword
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: 
// Description	: creation du fichier /etc/passwd pour la gestion des connexions
//=====================================================================================
void Install_LoginPassword(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: InitModule_Passwd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/07/2010 -
// Description	: Initialisation du module de passwd
//=====================================================================================
void InitModule_Passwd(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

