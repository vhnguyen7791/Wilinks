/*========================================================================*/
/* NOM DU FICHIER  : statustrap.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 01/03/2010                                           */
/* Libelle         : NET-SNMP: gestion de la liste status traps			  */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE013 01/03/2010 CM
// - CREATION (source BE373 - SDVB200)
//BE058 21/01/2011 CM
// - Ajout champs info_sup1 dans gestion trap
//BE060 16/03/2011
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui gère la base de données de statustrap

/*_____II - DEFINE SBIT __________________________________________________*/
#define _STATUSTRAP		1

#define IDX_OID_INDISPONIBLE	0xFFFF

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u16SearchFreeLstStatusTrap
// Entrees		: rien
// Sortie		: <loc_u16_index>
// Auteur		: CM - 29/08/2007 -
// Description	: recherche dans s_trap[] une position disponible
//=====================================================================================
u16sod u16SearchFreeLstStatusTrap(void)
{
	u16sod	loc_u16_index;
	u16sod	loc_u16_i;

	loc_u16_index = IDX_OID_INDISPONIBLE; //INIT

	for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_TABLE_STATUSTRAP;loc_u16_i++)
	{
		if(IDX_OID_INDISPONIBLE == ps_status_trap->s_trap[loc_u16_i].u16_idx_table) //CONDITION: mémoire disponible
		{
			loc_u16_index = loc_u16_i;	//trouvé
			loc_u16_i = TAILLE_MAX_TABLE_STATUSTRAP+1;	//on sort
		}
	}

	return loc_u16_index;
}/*u16SearchFreeLstStatusTrap*/

//=====================================================================================
// Fonction		: AddLst_StatusTrap
// Entrees		: <loc_ps_trap< : info sur trap à ajouter
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Ajout trap à la liste chainée
//=====================================================================================
void AddLst_StatusTrap(S_STRUCT_STA_TRAP *loc_ps_trap)
{
	S_STRUCT_STA_TRAP		*loc_ps_encours;
	S_STRUCT_STA_TRAP		*loc_ps_trouve;
	S_STRUCT_STA_TRAP		*loc_ps_precedent;
	u16sod				loc_u16_cpt;
	u16sod				loc_u16_idx_dispo;

	loc_ps_precedent = NULL;	//INIT

	loc_u16_idx_dispo = u16SearchFreeLstStatusTrap();

	if(IDX_OID_INDISPONIBLE != loc_u16_idx_dispo)
	{
		if(NULL == ps_status_trap->ps_premier_trap) //CONDITION: premier trap
		{
			//on ajoute le premier trap
			loc_ps_trouve = &ps_status_trap->s_trap[loc_u16_idx_dispo];
			(*loc_ps_trouve) = (*loc_ps_trap);
			ps_status_trap->ps_premier_trap = loc_ps_trouve;
			loc_ps_trouve->u16_idx_table = loc_u16_idx_dispo;
			loc_ps_trouve->ps_next = NULL;
		}
		else
		{
			loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
			loc_u16_cpt = 0; //INIT
			while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP))
			{
				if(loc_u16_idx_dispo < loc_ps_encours->u16_idx_table)
				{
					loc_ps_trouve = &ps_status_trap->s_trap[loc_u16_idx_dispo];
					(*loc_ps_trouve) = (*loc_ps_trap);

					//on insere le service avant
					if(ps_status_trap->ps_premier_trap == loc_ps_encours)
					{
						ps_status_trap->ps_premier_trap = (S_STRUCT_STA_TRAP*)loc_ps_trouve;
					}
					else
					{
						loc_ps_precedent->ps_next = (struct S_STRUCT_STA_TRAP*)loc_ps_trouve;
					}

					loc_ps_trouve->u16_idx_table = loc_u16_idx_dispo;
					loc_ps_trouve->ps_next = (struct S_STRUCT_STA_TRAP*)loc_ps_encours;

					loc_u16_cpt = TAILLE_MAX_TABLE_STATUSTRAP+1;	//on sort
				}
				else
				{
					if(NULL == loc_ps_encours->ps_next) //CONDITION: c'est le dernier
					{
						loc_ps_trouve = &ps_status_trap->s_trap[loc_u16_idx_dispo];
						(*loc_ps_trouve) = (*loc_ps_trap);

						//on insere le trap après
						loc_ps_encours->ps_next = (struct S_STRUCT_STA_TRAP*)loc_ps_trouve;

						loc_ps_trouve->u16_idx_table = loc_u16_idx_dispo;
						loc_ps_trouve->ps_next = NULL;

						loc_u16_cpt = TAILLE_MAX_TABLE_STATUSTRAP+1;	//on sort
					}
				}
				//On passe au suivant
				loc_ps_precedent = loc_ps_encours;
				loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
				loc_u16_cpt++;
			}
		}
	}
	else //CONDITION: LISTE CHAINEE PLEINE
	{
		//ERREUR
		//ERREUR
		//ERREUR
		//ERREUR
	}

}/*AddLst_StatusTrap*/

//=====================================================================================
// Fonction		: u8Search_IdxStatusTrap
// Entrees		: <loc_u16_idx_table> : index à trouver dans liste chainée
//				  >loc_pps_trap< : statut du trap avec loc_u16_idx_table
// Sortie		: <loc_u8_resultat> : TRUE si trouvé, FALSE si non trouvé
// Auteur		: CM - 29/08/2007 -
// Description	: recherche i dans s_trap[] une position disponible
//=====================================================================================
u8sod u8Search_IdxStatusTrap(u16sod loc_u16_idx_table, S_STRUCT_STA_TRAP **loc_pps_trap)
{
	u8sod	loc_u8_resultat;
	S_STRUCT_STA_TRAP	*loc_ps_encours;
	u16sod				loc_u16_cpt;

	loc_u8_resultat = FALSE;	//INIT	
	loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
	loc_u16_cpt = 0; //INIT
	while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP))
	{
		if(loc_ps_encours->u16_idx_table == loc_u16_idx_table) //CONDITION: trouvé
		{
			//on copie la mémoire du trap en cours
			*loc_pps_trap = loc_ps_encours;
			
			loc_u8_resultat = TRUE;
			loc_u16_cpt = TAILLE_MAX_TABLE_STATUSTRAP+1;	//on sort
		}
		//On passe au suivant
		loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
		loc_u16_cpt++;
	}

	return loc_u8_resultat;
}/*u8Search_IdxStatusTrap*/

//=====================================================================================
// Fonction		: AcquitAllTraps
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 08/09/2008 -
// Description	: Acquittement de tous les traps
//=====================================================================================
void AcquitAllTraps(void)
{
	s32sod				loc_s32_sem;
	S_STRUCT_STA_TRAP	*loc_ps_encours;
	u16sod				loc_u16_cpt;

	s32Lock_Get(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on lève le sem
	if(NULL == ps_status_trap->ps_premier_trap) //CONDITION: premier trap
	{
		;	//on ne fait rien
	}
	else
	{
		loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
		loc_u16_cpt = 0; //INIT
		while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP))
		{
			if(loc_ps_encours->u32_cpt_emission_trap >= 1) //CONDITION: trap émis au moins 1 fois
			{
				loc_ps_encours->u8_val_snmp = VAL_SNMP_ACQUITTER;
			}

			//On passe au suivant
			loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
			loc_u16_cpt++;
		}
	}
	s32Lock_Release(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on relache le sem

}/*AcquitAllTraps*/

//=====================================================================================
// Fonction		: ptGetPtrStatusTrap
// Entrees		: rien
// Sortie		: <loc_pt_return< : adresse de la variable globale status_trap
// Auteur		: CM - 01/03/2010 -
// Description	: Retourne l'adresse de la variable globale status_trap
//=====================================================================================
S_STRUCT_STATUS_TRAPS* ptGetPtrStatusTrap(void)
{
	S_STRUCT_STATUS_TRAPS *loc_pt_return;

	loc_pt_return = &s_status_trap;

	return loc_pt_return;
}/*ptGetPtrStatusTrap*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitStatusTrap
// Entrees		: <loc_ps_trap< : pointeur sur élément trap de la liste chainée
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du status d'un trap
//=====================================================================================
void InitStatusTrap(S_STRUCT_STA_TRAP *loc_ps_trap)
{
	loc_ps_trap->ps_next = NULL;						//INIT
	loc_ps_trap->u16_idx_table = IDX_OID_INDISPONIBLE;	//INIT
	loc_ps_trap->u16_index_evt = 0;					//INIT
	loc_ps_trap->t_valeur_evt = 0;					//INIT
	loc_ps_trap->u32_cpt_emission_trap = 0;			//INIT
	loc_ps_trap->u32_cpt_interval_trap = 0;			//INIT

	InitStructDate(&loc_ps_trap->s_date);			//INIT
	loc_ps_trap->u8_val_snmp = VAL_SNMP_NON_ACQUITTER;	//INIT
	loc_ps_trap->u8_etat_evt = ETAT_EVT_NON_DEFINI;		//INIT
	loc_ps_trap->u_info_sup1.u32_term = 0;	//INIT
	loc_ps_trap->u8_info_sup2 = 0x00;				// INIT
	memset(loc_ps_trap->pu8_tab_info_sup3, 0, TAILLE_MAX_TAB_INFO_SUP3);  //INIT
}/*InitStatusTrap*/

//=====================================================================================
// Fonction		: InitLst_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation de la liste chainée
//=====================================================================================
void InitLst_StatusTrap(void)
{
	u16sod loc_u16_i;

	ps_status_trap->u32_sequence_counter = 0;			//INIT
	ps_status_trap->ps_premier_trap = NULL;				//INIT
	for(loc_u16_i=0;loc_u16_i<TAILLE_MAX_TABLE_STATUSTRAP;loc_u16_i++)
	{
		InitStatusTrap(&ps_status_trap->s_trap[loc_u16_i]); // INIT
	}
}/*InitLst_StatusTrap*/

// -------------------------------------------------------------
// Fonction		: InitBDD_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation de la base de données des statustraps
// -------------------------------------------------------------
void InitBDD_StatusTrap(void)
{
	s32sod	loc_s32_sem;
	
	s32Lock_Get(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on lève le sem
	
	memset(ps_status_trap, 0, sizeof(S_STRUCT_STATUS_TRAPS));	//INIT
	
	InitLst_StatusTrap();
	
	s32Lock_Release(SEMAPHORE_BDD_STATUT_TRAP, &loc_s32_sem);	//on relache le sem
	
}/*InitBDD_StatusTrap*/

//=====================================================================================
// Fonction		: InitModule_StatusTrap
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 29/08/2007 -
// Description	: Initialisation du module de StatusTrap
//=====================================================================================
void InitModule_StatusTrap(void)
{
	ps_status_trap = &s_status_trap;		//INIT
	memset(ps_status_trap, 0, sizeof(S_STRUCT_STATUS_TRAPS));	//INIT

	InitBDD_StatusTrap();	//INIT

}/*InitModule_StatusTrap*/

