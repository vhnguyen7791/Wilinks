/*========================================================================*/
/* NOM DU FICHIER  : jdbflash.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Jdb: Gestion du journal de bord en Flash		      */
/* Projet          : WRM100                                               */
/* Indice          : BE015                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION (à partir source SDVB200 - BE374)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la sauvegarde des évènements du journal de bord dans la FLASH


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _JDBFLASH
#define _JDBFLASH_EXT
#else
#define _JDBFLASH_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: u8AjouteEvtJdbFlash
// Entrees		: <loc_ps_evtjdb<	: element qui doit etre ajouté 
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ajoute element jdb dans fichiers en Flash
//=====================================================================================
u8sod u8AjouteEvtJdbFlash(S_STRUCT_JDBEVT *loc_ps_elt_fifojdb);

//=====================================================================================
// Fonction		: InitModule_JdbFlash
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation du module de JdbFlash
//=====================================================================================
void InitModule_JdbFlash(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




