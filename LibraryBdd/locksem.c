/*========================================================================*/
/* NOM DU FICHIER  : locksem.c		                                      */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 13/06/2007                                           */
/* Libelle         : Base de données: gestion des sémaphores	 		  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
// BE000 CM 13/06/2007:
//		- gestion des sémaphores génériques
/*========================================================================*/

/*_____I COMMENTAIRES DEFINITIONS REMARQUES_______________________________*/

/*_____II DEFINE SBIT ____________________________________________________*/
#define _LOCKSEM

#define ACTIVATION_DEBUG_LOCKSEM	0	//0: désactivé , 1: activé
#define DBG_LOCKSEM	printf

/*_____III INCLUDE DIRECTIVES_____________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV PROCEDURES _____________________________________________________*/



// et oui! on est oblige de declarer nous meme l'union!
union t_semun
{
	s32sod s32_val;					// value for SETVAL
	struct semid_ds *ps_buf;		// buffer for IPC_STAT, IPC_SET
	u16sod *pu16_array;			    // array for GETALL, SETALL
	struct seminfo *ps___buf;		// buffer for IPC_INFO
};


//=====================================================================================
// Fonction		: s32Lock_Init
// Entrees		: <loc_u8_index_sem> : index du sémaphore
// Sortie		: rien
// Auteur		: CM (JP SFH252) - 13/06/2007
// Description: init d'un semaphore a 1 avec creation
//=====================================================================================
inline s32sod s32Lock_Init(u8sod loc_u8_index_sem)
{
	union t_semun loc_t_su;
	s32sod		loc_s32_lock;
	s32sod		loc_s32_retour;

	loc_s32_retour = 1; //INIT

  //creation du semaphore avec verification
	if ((-1) == (loc_s32_lock=semget(S_SEMAPHORE_DEFAUT[loc_u8_index_sem].u32_ipc_key, 1,0)))
	{ //le semaphore n'existe pas encore

		loc_s32_lock = semget(S_SEMAPHORE_DEFAUT[loc_u8_index_sem].u32_ipc_key, 1, IPC_CREAT | IPC_EXCL | 0666);

		if ((-1) == loc_s32_lock)
		{
			printf("Erreur creation semaphore %s : %d \n",
				   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom,
				   errno);
			loc_s32_retour = 0;
		}
		else
		{
			printf("Creation semaphore %s ok : %lu \n",
				   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom,
				   loc_s32_lock);
		}
	}
	else
	{
		printf("semaphore %s deja cree : %lu \n",
			   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom,
			   loc_s32_lock);
	}

	if (0 != loc_s32_retour)
	{
		//initialisation du semaphore
		loc_t_su.s32_val=1;
		if (semctl(loc_s32_lock, 0, SETVAL, loc_t_su)<0)
		{
		  /* init error*/
			printf("Erreur init semaphore %s : %d \n",
				   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom,
				   errno);
			loc_s32_retour = 0;
		}
		else
		{
			printf("Init semaphore %s ok \n",
				   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
		}
	}

	return(loc_s32_retour);

}/*s32Lock_Init*/

//=====================================================================================
// Fonction		: s32Lock_Get
// Entrees		:<loc_u8_index_sem> : index du sémaphore
//				 <loc_ps32_lock< : pointeur sur int (attention ecriture dedans!)
// Sortie		: rien
// Auteur		: CM (JP SFH252) - 13/06/2007
// Description: on prend le semaphore (avec attente si deja pris!)
//=====================================================================================
inline s32sod s32Lock_Get(u8sod loc_u8_index_sem, s32sod *loc_ps32_lock)
{
	struct sembuf loc_s_sop;
	s32sod		loc_s32_retour;

	loc_s32_retour = 0;	//INIT

  //verifions si le semaphore existe!
	if ((-1) == (*loc_ps32_lock=semget(S_SEMAPHORE_DEFAUT[loc_u8_index_sem].u32_ipc_key, 1,0)))
	{ //le semaphore n'existe pas encore!!
		loc_s32_retour = -1;
	}
	else
	{
		loc_s_sop.sem_num=0;
		loc_s_sop.sem_op=-1; /* down */
		loc_s_sop.sem_flg=SEM_UNDO; 

		//tryagain:
#if ACTIVATION_DEBUG_LOCKSEM
		if(SEMAPHORE_BDD_EXPLOIT == loc_u8_index_sem)
		{
			DBG_LOCKSEM("s32Lock_Get: Demande %s \n",
						S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
		}
#endif
		if ((-1) == semop(*loc_ps32_lock, &loc_s_sop, 1))
		{
			printf("Erreur dans le get semaphore %s\n",
				   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
			loc_s32_retour = -1;
		}
		else
		{
			; //on ne fait rien
#if ACTIVATION_DEBUG_LOCKSEM
			if(SEMAPHORE_BDD_EXPLOIT == loc_u8_index_sem)
			{
				DBG_LOCKSEM("s32Lock_Get: PRISE %s \n",
							S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
			}
#endif
		}
	}

	return(loc_s32_retour);
		
}/*s32Lock_Get*/

//=====================================================================================
// Fonction		: s32Lock_Release
// Entrees		:<loc_u8_index_sem> : index du sémaphore
//				 <loc_ps32_lock< : un pointeur sur gen_lock_t qui le numero du sem 
// Sortie		: rien
// Auteur		: CM (JP SFH252) - 13/06/2007
// Description: on relache le semaphore 
//=====================================================================================
inline s32sod s32Lock_Release(u8sod loc_u8_index_sem, s32sod *loc_ps32_lock)
{
	struct sembuf loc_s_sop;
	s32sod		loc_s32_retour;

	loc_s_sop.sem_num=0;
	loc_s_sop.sem_op=1; /* up */
	loc_s_sop.sem_flg=SEM_UNDO;//0;
	loc_s32_retour	= 0; //INIT

  //tryagain:
#if ACTIVATION_DEBUG_LOCKSEM
	if(SEMAPHORE_BDD_EXPLOIT == loc_u8_index_sem)
	{
		DBG_LOCKSEM("s32Lock_Release: Demande %s \n",
					S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
	}
#endif
	if ((-1)==semop(*loc_ps32_lock, &loc_s_sop, 1))
	{
		printf("Erreur dans le release semaphore %s \n",
			   S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
		loc_s32_retour = -1;
	}
	else
	{
		; //on ne fait rien
#if ACTIVATION_DEBUG_LOCKSEM
		if(SEMAPHORE_BDD_EXPLOIT == loc_u8_index_sem)
		{
			DBG_LOCKSEM("s32Lock_Release: RELACHE %s \n",
						S_SEMAPHORE_DEFAUT[loc_u8_index_sem].ps8_nom);
		}
#endif
	}

	return(loc_s32_retour);
	
}/*s32Lock_Release*/


//=====================================================================================
// Fonction		: InitAllSemaphores
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation de tous les sémaphores
//=====================================================================================
void InitAllSemaphores(void)
{
	u8sod	loc_u8_i;

	for(loc_u8_i=0;loc_u8_i<NB_MAX_SEMAPHORES;loc_u8_i++)
	{
		s32Lock_Init(loc_u8_i);
	}

}/*InitAllSemaphores*/

//=====================================================================================
// Fonction		: InitModule_Locksem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/06/2007 -
// Description	: Initialisation du module locksem
//=====================================================================================
void InitModule_Locksem(void)
{

}/*InitModule_Locksem*/
