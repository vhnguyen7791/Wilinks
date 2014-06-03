/*========================================================================*/
/* NOM DU FICHIER  : locksem.h			                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007                                           */
/* Libelle         : Base de données: gestion des sémaphores	 		  */
/* Projet          : WRM100                                               */
/* Indice          : BE058                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE008 28/01/2010 CM
// - Gestion fichier configuration debug.ini
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE042 07/10/2010 CM
// - Ajout gestion liste des fréquences réglementaires
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE058 21/01/2011 CM
// - Synchronisation configuration / exploitation
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef _LOCKSEM
#define _LOCKSEM_EXT
#else
#define _LOCKSEM_EXT extern
#endif

enum LISTE_SEMAPHORES_IPC
{
	SEMAPHORE_SYNCHRO_PRNCPL_MNTR	, //Synchronisation des processus principal (qui gère la configuration et monitor (qui gère l'exploitation)
	SEMAPHORE_BDD_CONFIG_EQPT		, //Base de données de configuration
	SEMAPHORE_BDD_EXPLOIT			, //Base de données d'exploitation de l'équipement
	SEMAPHORE_BDD_PASSWORD			, //Base de données du password
	SEMAPHORE_BDD_JDB				, //Base de données du JDB
	SEMAPHORE_BDD_CONSOLE_HTTP		, //Base de données du message de console HTTP
	SEMAPHORE_BDD_FTP_CONFIG		, //Base de données de config par FTP
	SEMAPHORE_BDD_DEBUGLOG			, //Base de données de debug actia.log
	SEMAPHORE_BDD_DEBUGINI			, //Base de données de debug debug.ini
	SEMAPHORE_BDD_CIP_MONITOR		, //Base de données Communication Inter Processus (monitor)
	SEMAPHORE_BDD_CIP_SNMPD			, //Base de données Communication Inter Processus (snmpd)
	SEMAPHORE_BDD_CIP_FIFOTRAP		, //Base de données Communication Inter Processus (fifo Trap)  (monitor --> snmpd)
	SEMAPHORE_BDD_CIP_STATUSTRAP	, //Base de données Communication Inter Processus (status Trap)  (snmpd --> *)
	SEMAPHORE_BDD_CIP_FIFOJDB		, //Base de données Communication Inter Processus (fifo jdb)  (monitor --> jdb)
	SEMAPHORE_BDD_CIP_JDB			, //Base de données Communication Inter Processus (jdb)
	SEMAPHORE_BDD_STATUT_TRAP		, //BDD pour bdd statut des traps
	SEMAPHORE_BDD_SYSTEMEVENT		, //BDD pour bdd systeme des évènements
	SEMAPHORE_BDD_ENVIRONMT			, //BDD pour bdd systeme environnement
	SEMAPHORE_BDD_LIST_FREQ			, //BDD pour bdd liste freq
		NB_MAX_SEMAPHORES
};

/*_____III - DEFINITIONS DE TYPES_________________________________________*/


//Définition des différents programmes téléchargés
typedef struct 
{
	u32sod	u32_ipc_key;	//Clé associée au sémaphore
	s8sod	ps8_nom[30+1];	//Nom du sémaphore
}T_STRUCT_SEMAPHORE;


/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

//=====================================================================================
// Fonction		: s32Lock_Init
// Entrees		: <loc_u8_index_sem> : index du sémaphore
// Sortie		: rien
// Auteur		: CM (JP SFH252) - 13/06/2007
// Description: init d'un semaphore a 1 avec creation
//=====================================================================================
inline s32sod s32Lock_Init(u8sod loc_u8_index_sem);

//=====================================================================================
// Fonction		: s32Lock_Get
// Entrees		:<loc_u8_index_sem> : index du sémaphore
//				 <loc_ps32_lock< : pointeur sur int (attention ecriture dedans!)
// Sortie		: rien
// Auteur		: CM (JP SFH252) - 13/06/2007
// Description: on prend le semaphore (avec attente si deja pris!)
//=====================================================================================
inline s32sod s32Lock_Get(u8sod loc_u8_index_sem, s32sod *loc_ps32_lock);

//=====================================================================================
// Fonction		: s32Lock_Release
// Entrees		:<loc_u8_index_sem> : index du sémaphore
//				 <loc_ps32_lock< : un pointeur sur gen_lock_t qui le numero du sem 
// Sortie		: rien
// Auteur		: CM (JP SFH252) - 13/06/2007
// Description: on relache le semaphore 
//=====================================================================================
inline s32sod s32Lock_Release(u8sod loc_u8_index_sem, s32sod *loc_ps32_lock);

//=====================================================================================
// Fonction		: InitAllSemaphores
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/06/2007 -
// Description	: Initialisation de tous les sémaphores
//=====================================================================================
void InitAllSemaphores(void);

//=====================================================================================
// Fonction		: InitModule_Locksem
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/06/2007 -
// Description	: Initialisation du module locksem
//=====================================================================================
void InitModule_Locksem(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _LOCKSEM
const	T_STRUCT_SEMAPHORE	S_SEMAPHORE_DEFAUT[NB_MAX_SEMAPHORES] =
{									
	{	(key_t)(0x6432CAFE),	"SEMAPHORE_SYNCHRO_PRNCPL_MNTR"	},	//SEMAPHORE_SYNCHRO_PRNCPL_MNTR
	{	(key_t)(0x6524CAFE),	"SEMAPHORE_BDD_CONFIG_EQPT"		},	//SEMAPHORE_BDD_CONFIG_EQPT
	{	(key_t)(0x65CAFE24),	"SEMAPHORE_BDD_EXPLOIT"			},	//SEMAPHORE_BDD_EXPLOIT
	{	(key_t)(0xCAFE6524),	"SEMAPHORE_BDD_PASSWORD"		},	//SEMAPHORE_BDD_PASSWORD
	{	(key_t)(0x4A506569),	"SEMAPHORE_BDD_JDB"				},	//SEMAPHORE_BDD_JDB
	{	(key_t)(0x2CAFE465),	"SEMAPHORE_BDD_CONSOLE_HTTP"	},	//SEMAPHORE_BDD_CONSOLE_HTTP
	{	(key_t)(0xCA8465FE),	"SEMAPHORE_BDD_FTP_CONFIG"		},	//SEMAPHORE_BDD_FTP_CONFIG
	{	(key_t)(0xCA3344FE),	"SEMAPHORE_BDD_DEBUGLOG"		},	//SEMAPHORE_BDD_DEBUGLOG
	{	(key_t)(0xCA0011FE),	"SEMAPHORE_BDD_DEBUGINI"		},	//SEMAPHORE_BDD_DEBUGINI
	{	(key_t)(0xCA00FE33),	"SEMAPHORE_BDD_CIP_MONITOR"		},	//SEMAPHORE_BDD_CIP_MONITOR
	{	(key_t)(0xCA11FE44),	"SEMAPHORE_BDD_CIP_SNMPD"		},	//SEMAPHORE_BDD_CIP_SNMPD
	{	(key_t)(0xCA22FE55),	"SEMAPHORE_BDD_CIP_FIFOTRAP"	},	//SEMAPHORE_BDD_CIP_FIFOTRAP
	{	(key_t)(0xCA00FE55),	"SEMAPHORE_BDD_CIP_STATUSTRAP"	},	//SEMAPHORE_BDD_CIP_STATUSTRAP
	{	(key_t)(0xCA11FE55),	"SEMAPHORE_BDD_CIP_FIFOJDB"		},	//SEMAPHORE_BDD_CIP_FIFOJDB
	{	(key_t)(0xCA11FE66),	"SEMAPHORE_BDD_CIP_JDB"			},	//SEMAPHORE_BDD_CIP_JDB
	{	(key_t)(0xCA55FE88),	"SEMAPHORE_BDD_STATUT_TRAP"		},	//SEMAPHORE_BDD_STATUT_TRAP
	{	(key_t)(0xCA66FE99),	"SEMAPHORE_BDD_SYSTEMEVENT"		},	//SEMAPHORE_BDD_SYSTEMEVENT
	{	(key_t)(0xCA77FEAA),	"SEMAPHORE_BDD_ENVIRONMT"		},	//SEMAPHORE_BDD_ENVIRONMT
	{	(key_t)(0xCA88FEBB),	"SEMAPHORE_BDD_LIST_FREQ"		},	//SEMAPHORE_BDD_LIST_FREQ
};
#else
extern const	T_STRUCT_SEMAPHORE	S_SEMAPHORE_DEFAUT[NB_MAX_SEMAPHORES];
#endif

