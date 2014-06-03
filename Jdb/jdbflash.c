/*========================================================================*/
/* NOM DU FICHIER  : jdbflash.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/03/2010                                           */
/* Libelle         : Jdb: Gestion du journal de bord en Flash		      */
/* Projet          : WRM100                                               */
/* Indice          : BE017                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE015 09/03/2010 CM
// - CREATION
//BE017 12/03/2010 CM
// - Correction risque de corruption du journal de bord sauv� en FLASH (statut erron�) lors de la rotation
//	en effet, il faut que les pointeurs rd/wr soient coh�rents pendant la rotation (dans le cas d'un coupure secteur)
//	donc, on impl�mente 3 �tapes:
//			1) on incr�mente pointeur lecture => sauve statutjdb en flash
//			2) on supprime l'ancien fichier point� par pointeur rd et on cr�e un fichier vide
//			3) on incr�mente pointeur ecriture => sauve statutjdb en flash
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui g�re la sauvegarde des �v�nements du journal de bord dans la FLASH

/*_____II - DEFINE SBIT __________________________________________________*/
#define _JDBFLASH

/*_____III - INCLUDE DIRECTIVES __________________________________________*/
#include "headers.h"


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/


//=====================================================================================
// Fonction		: u8AjouteEvtJdbFlash
// Entrees		: <loc_ps_evtjdb<	: element qui doit etre ajout� 
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 09/03/2010 -
// Description	: Ajoute element jdb dans fichiers en Flash
//=====================================================================================
u8sod u8AjouteEvtJdbFlash(S_STRUCT_JDBEVT *loc_ps_evtjdb)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_rm_numrd;
	u8sod loc_u8_tempo_numwr;

	loc_u8_resultat = TRUE;		//INIT
	loc_u8_rm_numrd = (NB_MAX_JDBPART+1);//INIT
	loc_u8_tempo_numwr = (NB_MAX_JDBPART+1);//INIT

	if(s_statutjdb_courant.u16_nbevt_jdbpart_encours < NB_MAX_EVT_PAR_JDBPART) //CONDITION: JDBPART pas plein
	{
		if(s_statutjdb_courant.u8_numwr_jdbpart < NB_MAX_JDBPART)
		{
			//On ajoute le nouvel �v�nement
			if(FALSE == u8AddEvtJdbPart(loc_ps_evtjdb, &T_DEF_FILE_JDBPART, s_statutjdb_courant.u8_numwr_jdbpart))
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8AjouteEvtJdbFlash: [1] Impossible d'ajouter evt dans jdbpart\n"));
			}
			else
			{
				if(FALSE == u8AddEvtJdbPart(loc_ps_evtjdb, &T_DEF_FILE_JDBPART, NUM_JDBCUR))
				{
					loc_u8_resultat = FALSE;
					MACRO_PRINTF(("u8AjouteEvtJdbFlash: [1] Impossible d'ajouter evt dans jdbcur\n"));
				}
				else
				{
					s_statutjdb_courant.u16_nbevt_jdbpart_encours++;
					s_statutjdb_courant.u16_nb_total_evt++;
				}
			}
		}
		else
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8AjouteEvtJdbFlash: [2] Erreur numwr_jdbpart=%d \n",
						  s_statutjdb_courant.u8_numwr_jdbpart));
		}
	}
	else //CONDITION: JDBPART plein
	{
		//Pour que les pointeurs rd/wr soient coh�rents pendant la rotation (dans le cas d'un coupure secteur)
		//	donc, on impl�mente 3 �tapes:
		//	1) on incr�mente pointeur lecture => sauve statutjdb en flash
		//	2) on supprime l'ancien fichier point� par pointeur rd et on cr�e un fichier vide
		//	3) on incr�mente pointeur ecriture => sauve statutjdb en flash
		
		//On v�rifie si une rotation est n�cessaire
		loc_u8_tempo_numwr = s_statutjdb_courant.u8_numwr_jdbpart; //RAZ
		loc_u8_tempo_numwr++;
		if(loc_u8_tempo_numwr >= NB_MAX_JDBPART)
		{
			loc_u8_tempo_numwr = 0; //RAZ
		}

		if(loc_u8_tempo_numwr == s_statutjdb_courant.u8_numrd_jdbpart) //CONDITION: rotation compl�te sur les fichiers jdbpart
		{
			//On met � jour alors le pointeur de lecture
			
			//On m�morise le num�ro du premier fichier (dans la rotation): afin de le supprimer
			loc_u8_rm_numrd = s_statutjdb_courant.u8_numrd_jdbpart;

			//On incr�mente le pointeur de lecture
			s_statutjdb_courant.u8_numrd_jdbpart++;
			if(s_statutjdb_courant.u8_numrd_jdbpart >= NB_MAX_JDBPART)
			{
				s_statutjdb_courant.u8_numrd_jdbpart = 0; //RAZ
			}

			//On met � jour le nombre d'�v�nements total
			s_statutjdb_courant.u16_nb_total_evt -= NB_MAX_EVT_PAR_JDBPART; //Maj

			//Puis on sauve le nouveau satutjdb en FLASH
			u8EditStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_BASE);
			u8EditStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_BACKUP);

			//On supprime ensuite le premier fichier sauv�
			if(FALSE == u8RemoveJdbPart(loc_u8_rm_numrd))
			{
				MACRO_PRINTF(("u8AjouteEvtJdbFlash: [3] Impossible d'effacer numrd_jdbpart=%d\n",
							  loc_u8_rm_numrd));
			}
		}
		else
		{
			//On supprime le futur fichier (au cas o� il est pr�sent)
			if(FALSE == u8RemoveJdbPart(loc_u8_tempo_numwr))
			{
				MACRO_PRINTF(("u8AjouteEvtJdbFlash: [4] Impossible d'effacer tempo_numwr=%d\n",
							  loc_u8_tempo_numwr));
			}
		}

		//On supprime ensuite le fichier courant
		if(FALSE == u8RemoveJdbPart(NUM_JDBCUR))
		{
			MACRO_PRINTF(("u8AjouteEvtJdbFlash: [4] Impossible d'effacer tempo_numwr=%d\n",
						  NUM_JDBCUR));
		}
		
		//On met � jour le nombre d'�v�nements courant dans le fichier jdbpart
		s_statutjdb_courant.u16_nbevt_jdbpart_encours = 0; //RAZ
		
		//On met � jour le pointeur d'�criture
		s_statutjdb_courant.u8_numwr_jdbpart = loc_u8_tempo_numwr; //MAJ
	
		//Puis on sauve encore une fois le nouveau satutjdb en FLASH
		u8EditStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_BASE);
		u8EditStatutJdb(&s_statutjdb_courant, IDXSTATUTJDB_BACKUP);

		//Puis on ajoute le nouvel �v�nement
		if(FALSE == u8AddEvtJdbPart(loc_ps_evtjdb, &T_DEF_FILE_JDBPART, s_statutjdb_courant.u8_numwr_jdbpart))
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8AjouteEvtJdbFlash: [5] Impossible d'ajouter evt dans jdbpart\n"));
		}
		else
		{
			//Puis on copie dans le fichier courant
			if(FALSE == u8AddEvtJdbPart(loc_ps_evtjdb, &T_DEF_FILE_JDBPART, NUM_JDBCUR))
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8AjouteEvtJdbFlash: [5] Impossible d'ajouter evt dans jdbcur\n"));
			}
			else
			{
				s_statutjdb_courant.u16_nbevt_jdbpart_encours++;
				s_statutjdb_courant.u16_nb_total_evt++;
			}
		}
	}
	

	return loc_u8_resultat;
}/*u8AjouteEvtJdbFlash*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_JdbFlash
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/03/2010 -
// Description	: Initialisation du module de JdbFlash
//=====================================================================================
void InitModule_JdbFlash(void)
{
	
}/*InitModule_JdbFlash*/

