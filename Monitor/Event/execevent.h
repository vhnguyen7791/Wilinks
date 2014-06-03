/*========================================================================*/
/* NOM DU FICHIER  : execevent.h										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : Monitor: gestion du statut des �v�nements			  */
/* Projet          : WRM100                                               */
/* Indice          : BE016                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source SDVB200 - BE373)
//BE016 11/03/2010 CM
// - Modification struture de la gestion interne des �v�nements
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui g�re le statut des �v�nements


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _EXECEVENT
#define _EXECEVENT_EXT
#else
#define _EXECEVENT_EXT	extern
#endif


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: OrdreMntr_RAZ_Trap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/03/2010 -
// Description	: Ordre de raz des traps
//=====================================================================================
void OrdreMntr_RAZ_Trap(void);

//=====================================================================================
// Fonction		: GestionExecEvent
// Entrees		: <loc_ps_exp_events< : pointeur sur base de donn�es exploit des �v�nements � mettre � jour
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Gestion � la seconde du statut des �v�nements
//=====================================================================================
void GestionExecEvent(S_STRUCT_EXPLOIT_EVENTS *loc_ps_exp_events);

//=====================================================================================
// Fonction		: MajEtatEvent
// Entrees		: <loc_ps_intern_evt< : pointeur sur statut d'un evt
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Mise � jour de l'�tat de l'�v�nement
//=====================================================================================
void MajEtatEvent(S_STRUCT_INTERNAL_EVENTS *loc_ps_intern_evt);

//=====================================================================================
// Fonction		: MajImageConfigEvt
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Mise � jour de l'image de la configuration des
//					�v�nements
//=====================================================================================
void MajImageConfigEvt(void);

//=====================================================================================
// Fonction		: InitModule_ExecEvent
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 03/10/2007 -
// Description	: Initialisation du module de ExecEvent
//=====================================================================================
void InitModule_ExecEvent(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/



