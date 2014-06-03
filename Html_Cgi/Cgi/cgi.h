/*========================================================================*/
/* NOM DU FICHIER  : cgi.h												  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: gestion des pages HTML dynamiques		  */
/* Projet          : WRM100                                               */
/* Indice          : BE055                                                */
/*========================================================================*/
/* Historique      :                                                      */
//	[AUDIT DU CODE] [2008/09/04] [MS]
//BE000 24/09/2009 CM
// - CREATION
//BE003 22/12/2009 CM
// - Ajout exploitation adresse IP/Mask des interfaces
//		=> ajout page HTML Exploitation - Réseau
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//		-> ajout page HTML Configuration - DHCP serveur /relai
//BE008 28/01/2010 CM
// - Ajout syslog: journalisation du système
//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//BE013 26/02/2010 CM
// - Intégration gestion des évènements
//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//BE016 11/03/2010 CM
// - Ajout gestion des alarmes
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
//BE037 06/07/2010 CM
// - Ajout exploitation temperature 
// - Modification page HTML Admin - Mise à l'heure
//		-> surveillance etat NTP
//BE040 13/09/2010 CM
// - Ajout des paramètres de configuration hand-off
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE055 17/01/2011 CM
// - Modification configuration des antennes
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef CGI_MAIN
#define CGI_MAIN_EXT
#else
#define CGI_MAIN_EXT	extern
#endif

/*_____III - DEFINITIONS DE TYPES_________________________________________*/


typedef struct
{
  s8sod	*ps8_PageName;
  void (* Fct)(s8sod **loc_p_varlist, s32sod form_method);
} PAGE_ENT;

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

#ifdef CGI_MAIN

PAGE_ENT t_menu_table[] =
{	
  // HOME
  { "",								home					},
  {	"\0",							home					},
  {	"\n",							home					},
  {	"index",						home					},
  {	"HomeA",						HomeA					},
#if AFFICHAGE_INFORMATIONS_SUPPLEMENTAIRES_HOMEA
  {	"HomeA_Dyn",					HomeA_Dyn				},
#endif
  {	"HomeB",						HomeB					},
  {	"HomeC",						HomeC					},
  {	"Vaccueil",						Vaccueil				},
  {	"VContact",						VContact				},
#if ACTIVATION_PRESENCE_SYNOPTIQUE
  {	"VSynoptique",					VSynoptique				},
#endif
#if ACTIVATION_CONSOLE_HTML
  {	"VConsole",						VConsole				},
  {	"VConsole_Dyn",					VConsole_Dyn			},
#endif
  {	"Vwarning",						PageWarning				},
  {	"VCfgInProgress",				VCfgInProgress			},
  {	"VCfgInProgress_Dyn",			VCfgInProgress_Dyn		},

  // PASSWORD
  {	"enter_pwd",					enter_pwd				},

  
  //Administration
  {	"SUAdmIdentification",			SUAdmIdentification		},
  {	"SUAdmControle",				SUAdmControle			},
  {	"SUAdmSecurite",				SUAdmSecurite			},
  {	"SUtime",						SUtime					},
  {	"SUtime_Dyn",					SUtime_Dyn				},
  {	"Adm_Versions",					VAdmVersionsLogicielles	},
  {	"SUAdmLangue",					SUAdmLangue				},
  {	"SUAdmRefresh",					SUAdmRefresh			},
  {	"SUAdmSystemLog",				SUAdmSystemLog			},

  //Configuration
  {	"SUConfigMode",					SUConfigMode			},
  {	"SUConfigNetwork",				SUConfigNetwork			},
  {	"SUConfigWirelessBasic",		SUConfigWirelessBasic	},
  {	"SUConfigWirelessAdv",			SUConfigWirelessAdv		},
  {	"SUConfigHandoff",				SUConfigHandoff			},
  {	"SUConfigRoutingGene",			SUConfigRoutingGene		},
  {	"SUConfigRoutingStatic",		SUConfigRoutingStatic	},
  {	"SUConfigRoutingPolitic",		SUConfigRoutingPolitic	},
  {	"SUConfigRoutingRip",			SUConfigRoutingRip		},
  {	"SUConfigDhcp",					SUConfigDhcp			},
  {	"SUConfigSNMP",					SUConfigSNMP			},
  {	"SUConfigNat_Dyn",				SUConfigNat_Dyn			},
  {	"SUConfigNat",					SUConfigNat				},
  {	"SUConfigMulticast",			SUConfigMulticast		},
//  {	"VconfigEquipement",			VconfigEquipement		},

  //Exploitation
  {	"VExploitGeneral",				VExploitGeneral			},
  {	"VExploitGeneral_Dyn",			VExploitGeneral_Dyn		},
  {	"VExploitWireless",				VExploitWireless		},
  {	"VExploitWireless_Dyn",			VExploitWireless_Dyn	},
  {	"VExploitNetwork",				VExploitNetwork			},
  {	"VExploitNetwork_Dyn",			VExploitNetwork_Dyn		},
  {	"VExploitDhcpClient",			VExploitDhcpClient		},
  {	"VExploitDhcpClient_Dyn",		VExploitDhcpClient_Dyn	},
  
  //Evenement
  {	"VListeEvt",					VListeEvt				},
  {	"SUConfigEvt",					SUConfigEvt				},
  {	"VJDBEvenement",				VJDBEvenement			},
  {	"VJDBEvenement_Dyn",			VJDBEvenement_Dyn		},
  {	"VTrap",						VTrap					},

  //Alarme
  {	"VAlarme_Dyn",					VAlarme_Dyn				},
  {	"VAlarme",						VAlarme					},
  {	"VListeAlarme_Dyn",				VListeAlarme_Dyn		},
  {	"VListeAlarme",					VListeAlarme			},

  //Debug	
  {	"VdbgSodielec",					VdbgSodielec			},
  {	"VDebugMsgDebug",				VDebugMsgDebug			},
  {	"VDebugInformations",			VDebugInformations		},
  {	"VDebugSizeOf",					VDebugSizeOf			},
  {	"VDebugLogOut",					VDebugLogOut			},
  {	"VDebugConfiguration",			VDebugConfiguration		},
  {	"VDebugSystemEvent",			VDebugSystemEvent		},
  {	"VTestFinal",					VTestFinal				},
  {	"VTestFinal_Dyn",				VTestFinal_Dyn			},
  
  {	NULL, NULL},

};
#else
extern PAGE_ENT menu_table[];
#endif

