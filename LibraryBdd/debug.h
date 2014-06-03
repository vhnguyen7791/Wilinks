/*========================================================================*/
/* NOM DU FICHIER  : debug.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 16/10/2009                                           */
/* Libelle         : Base de données: debug								  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE035 30/06/2010 CM
// - Creation de la library static LibrarySystem
//BE055 17/01/2011 CM
// - Ajout information "Debug Activé" sur frame A
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _DEBUG
#define _DEBUG_EXT
#else
#define _DEBUG_EXT extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8FillDebugFile
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/01/2010 -
// Description	: Lecture du fichier
//=====================================================================================
u8sod u8FillDebugFile(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global);

//=====================================================================================
// Fonction		: u8EditDebugFile
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 28/01/2010 -
// Description	: Ecriture  du fichier
//=====================================================================================
u8sod u8EditDebugFile(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global);

//=========================================================================
//Procedure	 : AddMsgDbgLog
//Entrée	 : <loc_ps8_fmtp< : message du texte dans debug
//Sortie	 : Rien
//Auteur	 : CM - 16/10/2009 -
//Description: Ajoute message debug
//=========================================================================
void AddMsgDbgLog(s8sod *loc_ps8_fmtp, ...);

//=====================================================================================
// Fonction		: u8AddInFileDebugLog
// Entrees		: loc_ps8_message
// Sortie		: <loc_u8_resultat> : TRUE (si OK),sinon FALSE
// Auteur		: CM - 16/10/2009 -
// Description	: Ajoute un message dans le fichier actia.log
//=====================================================================================
u8sod u8AddInFileDebugLog(s8sod *loc_ps8_message);

//=====================================================================================
// Fonction		: u8TestDebugActive
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: <loc_u8_resultat> : TRUE (si OK),sinon FALSE
// Auteur		: CM - 17/01/2011 -
// Description	: Test si debug activé
//=====================================================================================
u8sod u8TestDebugActive(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global);

//=====================================================================================
// Fonction		: FunctionMacroPrintf
// Entrees		: <loc_ps8_message<: message à afficher
// Sortie		: void
// Auteur		: CM - 07/07/2010 -
// Description	: Fonction de la macro printf
//=====================================================================================
void FunctionMacroPrintf(s8sod *loc_ps8_message);

//=====================================================================================
// Fonction		: InitDebugGlobal
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: rien
// Auteur		: CM - 29/01/2010 -
// Description	: Initialisation de la structure de debug globale
//=====================================================================================
void InitDebugGlobal(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global);

//=====================================================================================
// Fonction		: InitBDD_Debug
// Entrees		: <loc_ps_debug_global< : pointeur sur la base de données DEBUG
// Sortie		: rien
// Auteur		: CM - 16/10/2009 -
// Description	: Initialisation de la base de données de debug
//=====================================================================================
void InitBDD_Debug(S_STRUCT_DEBUG_GLOBAL *loc_ps_debug_global);

//=====================================================================================
// Fonction		: InitModule_Debug
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/10/2009 -
// Description	: Initialisation du module de Debug de l'équipement
//=====================================================================================
void InitModule_Debug(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/


