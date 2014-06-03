/*========================================================================*/
/* NOM DU FICHIER  : def_configfiles.h			                          */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 26/01/2010                                           */
/* Libelle         : Base de données: définition des fichiers de config	  */
/* Projet          : WRM100                                               */
/* Indice          : BE064                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE007 26/01/2010 CM
// - CREATION
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE054 11/01/2011 CM
// - Suppression du fichier de configuration advwf
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _DEF_CONFIGFILES
#define _DEF_CONFIGFILES_EXT
#else
#define _DEF_CONFIGFILES_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/

//=====================================================================================
// Fonction		: InitModule_Def_ConfigFiles
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 26/01/2010 -
// Description	: Initialisation du module de def_configfiles
//=====================================================================================
void InitModule_Def_ConfigFiles(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef _DEF_CONFIGFILES
#else
//Contenu des fichiers de configuration
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_ADMIN_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_CONSTRUCTEUR_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_SNMP_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_GENE_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_WIFI_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_ROUTING_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_NAT_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_MULTICAST_CFG[];
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_TABEVT_CFG[];

//Définition de la configuration
_DEF_CONFIGFILES_EXT T_STRUCT_DEFINITION_FILE_FS		PT_DEF_FILE_CONFIG[NB_MAX_ID_FILES_CONFIG];
_DEF_CONFIGFILES_EXT T_STRUCT_DEFINITION_FILE_FS		PT_DEF_FILE_CONFIG_GLOBAL_STA;
_DEF_CONFIGFILES_EXT T_STRUCT_DEFINITION_FILE_FS		PT_DEF_FILE_CONFIG_GLOBAL_SANSCHECKSUM;
//Description des configuration
_DEF_CONFIGFILES_EXT T_STRUCT_DESCRIPTION_CONFIGURATION PT_DESCRIPTION_CONFIGURATION[NB_MAX_IDXCONFIG];

//Contenu dy fichier newcfg.ini
_DEF_CONFIGFILES_EXT T_STRUCT_FILE_FIELD PT_CONTENU_FILE_NEWCFG_INI[];
//Définition dy fichier newcfg.ini
_DEF_CONFIGFILES_EXT T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_NEWCFG_INI;
#endif

