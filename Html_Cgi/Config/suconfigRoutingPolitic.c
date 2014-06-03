/*========================================================================*/
/* NOM DU FICHIER  : suconfigRoutingPolitic.c							  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM				                                      */
/* Date			   : 15/04/2010                                           */
/* Libelle         : HTML CGI: page HTML configuration - Routing /Politic */
/* Projet          : WRM100                                               */
/* Indice          : BE048                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE025 15/04/2010 CM
// - CREATION
//BE026 26/04/2010 CM
// - Correction erreur javascript dans page HTML politique de routage
//BE048 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _SUCONFIGROUTINGPOLITIC


/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

enum LISTE_DES_FORM_SUCONFIGROUTINGPOLITIC
{
	FORM_SUCONFIGROUTINGPOLITIC_NULL = 0,	//à ne pas utiliser
	FORM_SUCONFIGROUTINGPOLITIC_AJOUTER_VALIDER,
	FORM_SUCONFIGROUTINGPOLITIC_EFFACER,
	FORM_SUCONFIGROUTINGPOLITIC_SUPPRIMER,
	NB_MAX_FORM_SUCONFIGROUTINGPOLITIC
};


/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/* Structures pour la modificaton de la configuration */
typedef struct
{
	s8sod	ps8_policyname	[TAILLE_MAX_POLICY_NAME + 1];
	//Liste des critères
	s8sod	ps8_validcritere[NB_MAX_CRITERIA_POLICY] [10 + 1];
	s8sod	ps8_notcritere	[NB_MAX_CRITERIA_POLICY] [10 + 1];
	s8sod	ps8_srcIpstart	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_srcIpend	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_dstIpstart	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_dstIpend	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_lengthmin	[10 + 1];
	s8sod	ps8_lengthmax	[10 + 1];
	s8sod	ps8_ipprotocol	[10 + 1];
	s8sod	ps8_srcPortstart[10 + 1];
	s8sod	ps8_srcPortend	[10 + 1];
	s8sod	ps8_dstPortstart[10 + 1];
	s8sod	ps8_dstPortend	[10 + 1];
	s8sod	ps8_classSelector[10 + 1];
	//Liste des actions
	s8sod	ps8_validaction[NB_MAX_ACTIONS_POLICY] [10 + 1];
	s8sod	ps8_actadrGw	[MAX_LG_FORMAT_ADRESSE_IP + 1];
	s8sod	ps8_actCS		[10 + 1];
	
	s8sod	ps8_parametre	[10 + 1];
	s8sod	ps8_hidden1		[10 + 1];
} S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS;

FIELD_LIST s_FormConfigRoutingPoliticFields[] = {
	{"name",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_policyname)	},
	//Liste des critères
	{"vC0",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_SRC_IP])	},
	{"vC1",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_DST_IP])	},
	{"vC2",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_LENGTH_PACKET])	},
	{"vC3",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_IP_PROTOCOL])	},
	{"vC4",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_SRC_PORT])	},
	{"vC5",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_DST_PORT])	},
	{"vC6",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validcritere[CRITERIAPOLICY_CLASS_SELECTOR])	},
	{"nC0",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_SRC_IP])	},
	{"nC1",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_DST_IP])	},
	{"nC2",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_LENGTH_PACKET])	},
	{"nC3",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_IP_PROTOCOL])	},
	{"nC4",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_SRC_PORT])	},
	{"nC5",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_DST_PORT])	},
	{"nC6",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_notcritere[CRITERIAPOLICY_CLASS_SELECTOR])	},
	{"scrIpS",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_srcIpstart)	},
	{"scrIpE",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_srcIpend)	},
	{"dstIpS",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_dstIpstart)	},
	{"dstIpE",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_dstIpend)	},
	{"lenmin",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_lengthmin)	},
	{"lenmax",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_lengthmax)	},
	{"protoc",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_ipprotocol)	},
	{"srcPrtS",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_srcPortstart)},
	{"srcPrtE",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_srcPortend)	},
	{"dstPrtS",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_dstPortstart)},
	{"dstPrtE",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_dstPortend)	},
	{"claSel",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_classSelector)},
	//Liste des actions
	{"vA0",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validaction[ACTIONPOLICY_GATEWAY])	},
	{"vA1",			"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_validaction[ACTIONPOLICY_CLASS_SELECTOR])	},
	{"actGW",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_actadrGw)	},
	{"actCS",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_actCS)		},
	
	{"param",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_parametre)	},
	{"hidden1",		"%s",	offsetof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS, ps8_hidden1)	},
	{NULL	}
};

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingPolitic
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: code de javascript de la page HTML SUConfigRoutingPolitic
//=====================================================================================
void proc_JavaScript_SUConfigRoutingPolitic(void);

//=====================================================================================
// Fonction		: proc_JavaScript_SUConfigRoutingPolitic
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 15/04/2010
// Description	: code de javascript de la page HTML SUConfigRoutingPolitic
//=====================================================================================
void proc_JavaScript_SUConfigRoutingPolitic(void)
{
	u8sod loc_u8_i;

	html_tag("<SCRIPT language=\"javascript\">\n");

	//Fonction javascript : StartJavaScript
	//*************************************
	html_tag("function StartJavaScript() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{  \n");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CRITERIA_POLICY;loc_u8_i++)
	{
		html_tag("		JSChangeEnableCriteria(%d); \n",loc_u8_i);
	}
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ACTIONS_POLICY;loc_u8_i++)
	{
		html_tag("		JSChangeEnableAction(%d); \n",loc_u8_i);
	}
	html_tag("		JSCollapseAllServices();  \n");
	html_tag("	}  \n");
	html_tag("} \n");/*StartJavaScript*/

	
	//Fonction javascript : SelectFormulaire
	//*************************************
	html_tag("function SelectFormulaire(i_numForm,form) \n");
	html_tag("{\n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("		with(document) \n");
	html_tag("		{  \n");
	html_tag("			switch(i_numForm)  \n");
	html_tag("			{  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGROUTINGPOLITIC_AJOUTER_VALIDER);
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CRITERIA_POLICY;loc_u8_i++)
	{
		html_tag("					if(false == JSTestCriteria(%d))",loc_u8_i);
		html_tag("					{  \n");
		html_tag("						loc_result = false;  \n");
		html_tag("					}  \n");
	}
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ACTIONS_POLICY;loc_u8_i++)
	{
		html_tag("					if(false == JSTestAction(%d))",loc_u8_i);
		html_tag("					{  \n");
		html_tag("						loc_result = false;  \n");
		html_tag("					}  \n");
	}
	//Puis il faut tester qu'il y a au moins un critère et au moins une action (pour que la route politique soit prise en compte)
	html_tag("						var loc_count_critere = 0;");
	html_tag("						var loc_count_action = 0;");
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CRITERIA_POLICY;loc_u8_i++)
	{
		html_tag("					if(true == form.vC%d.checked)",loc_u8_i);
		html_tag("					{  \n");
		html_tag("						loc_count_critere ++;  \n");
		html_tag("					}  \n");
	}
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ACTIONS_POLICY;loc_u8_i++)
	{
		html_tag("					if(true == form.vA%d.checked)",loc_u8_i);
		html_tag("					{  \n");
		html_tag("						loc_count_action ++;  \n");
		html_tag("					}  \n");
	}
	html_tag("						if((0==loc_count_critere)||(0==loc_count_action))  \n");
	html_tag("						{  \n");
	html_tag("							alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_selectionner_un_critere_et_une_action);
	html_tag("							loc_result = false;  \n");
	html_tag("						}  \n");
	html_tag("					break;  \n");
	html_tag("				case %d: \n",
			 FORM_SUCONFIGROUTINGPOLITIC_EFFACER);
	html_tag("					form.name.value = \"\"; \n"); //RAZ
	for(loc_u8_i=0;loc_u8_i<NB_MAX_CRITERIA_POLICY;loc_u8_i++)
	{
		html_tag("					JSClearCriteria(%d); \n",loc_u8_i); //RAZ
		html_tag("					JSChangeEnableCriteria(%d); \n",loc_u8_i);
	}
	for(loc_u8_i=0;loc_u8_i<NB_MAX_ACTIONS_POLICY;loc_u8_i++)
	{
		html_tag("					JSClearAction(%d); \n",loc_u8_i); //RAZ
		html_tag("					JSChangeEnableAction(%d); \n",loc_u8_i);
	}
	html_tag("					loc_result = false;  \n");
	html_tag("					break;  \n");
	html_tag("				default:  \n");
	html_tag("					loc_result = true; \n");
	html_tag("					break;	  \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag( "	if(true == loc_result) \n");
	html_tag("	{\n");
	html_tag("		form.hidden1.value = i_numForm; \n");
	html_tag("		form.submit(); \n");
	html_tag("	}\n");
	html_tag("}\n");/*SelectFormulaire*/

	//Fonction javascript : JSReduc
	//*************************************
	html_tag("function JSReduc(loc_sid) \n");
	html_tag("{ \n");
	html_tag("  var loc_tr_champ_id = \"DIV_DETAILS\"+loc_sid; \n");
	html_tag("	var loc_valeur_class = document.getElementById(loc_tr_champ_id).className; \n");
	html_tag("  if (\"contentVisible\" == loc_valeur_class) \n");
	html_tag("  {\n");
	html_tag("		document.getElementById(loc_tr_champ_id).className = \"contentInvisible\";\n");
	html_tag("  }\n");
	html_tag("  else\n");
	html_tag("  {\n");
	html_tag("		document.getElementById(loc_tr_champ_id).className = \"contentVisible\";\n");
	html_tag("  }\n");
	html_tag("}\n");/*JSReduc*/

	//Fonction javascript : JSExpandAllServices
	//*************************************
	html_tag("function JSExpandAllServices()\n");
	html_tag("{\n");
	html_tag("	var elmt = document.getElementsByTagName(\"tr\");\n");
	html_tag("	var loc_i_i; \n");
	html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++)\n");
	html_tag("	{\n");
	html_tag("		if(		(\"contentVisible\" == elmt[loc_i_i].className) \n");
	html_tag("			||	(\"contentInvisible\" == elmt[loc_i_i].className) \n");
	html_tag("		 ) \n");
	html_tag("		 { \n");
	html_tag("			elmt[loc_i_i].className = \"contentVisible\";\n");
	html_tag("		 } \n");
	html_tag("	}\n");
	html_tag("}\n");/*JSExpandAllServices*/

	//Fonction javascript : JSCollapseAllServices
	//*************************************
	html_tag("function JSCollapseAllServices()\n");
	html_tag("{\n");
	html_tag("	var elmt = document.getElementsByTagName(\"tr\");\n");
	html_tag("	var loc_i_i; \n");
	html_tag("	for(loc_i_i=1;loc_i_i<elmt.length;loc_i_i++)\n");
	html_tag("	{\n");
	html_tag("		if(		(\"contentVisible\" == elmt[loc_i_i].className) \n");
	html_tag("			||	(\"contentInvisible\" == elmt[loc_i_i].className) \n");
	html_tag("		 ) \n");
	html_tag("		 { \n");
	html_tag("			elmt[loc_i_i].className = \"contentInvisible\";\n");
	html_tag("		 } \n");
	html_tag("	}\n");
	html_tag("}\n");/*JSCollapseAllServices*/

	//Fonction javascript : JSClearCriteria
	//*************************************
	html_tag("function JSClearCriteria(loc_numCritere) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numCritere) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				form.scrIpS.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("				form.scrIpS.disabled = true; \n");
	html_tag("				form.scrIpE.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("				form.scrIpE.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_IP);
	html_tag("				form.dstIpS.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("				form.dstIpS.disabled = true; \n");
	html_tag("				form.dstIpE.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("				form.dstIpE.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_DST_IP);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_DST_IP);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_DST_IP);
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				form.lenmin.value = %d; \n",LEN_PACKET_MIN);
	html_tag("				form.lenmin.disabled = true; \n");
	html_tag("				form.lenmax.value = %d; \n",LEN_PACKET_MAX);
	html_tag("				form.lenmax.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				form.protoc.value = %d; \n",POLICYROUTE_PROTOCOLE_UDP);
	html_tag("				form.protoc.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				JSChangeProtocol(); \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				form.srcPrtS.value = %d; \n",PORT_UDP_TCP_MIN);
	html_tag("				form.srcPrtS.disabled = true; \n");
	html_tag("				form.srcPrtE.value = %d; \n",PORT_UDP_TCP_MAX);
	html_tag("				form.srcPrtE.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				form.dstPrtS.value = %d; \n",PORT_UDP_TCP_MIN);
	html_tag("				form.dstPrtS.disabled = true; \n");
	html_tag("				form.dstPrtE.value = %d; \n",PORT_UDP_TCP_MAX);
	html_tag("				form.dstPrtE.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				form.claSel.value = %d; \n",CLASSSELECTOR_CS0);
	html_tag("				form.claSel.disabled = true; \n");
	html_tag("				form.vC%d.checked = false; \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				form.nC%d.checked = false; \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				form.nC%d.disabled = true; \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSClearCriteria*/
	
	//Fonction javascript : JSChangeEnableCriteria
	//*************************************
	html_tag("function JSChangeEnableCriteria(loc_numCritere) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numCritere) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				{ \n");
	html_tag("					form.scrIpS.disabled = false; \n");
	html_tag("					form.scrIpE.disabled = false; \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.scrIpS.disabled = true; \n");
	html_tag("					form.scrIpE.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_IP);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_DST_IP);
	html_tag("				{ \n");
	html_tag("					form.dstIpS.disabled = false;  \n");
	html_tag("					form.dstIpE.disabled = false;  \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_DST_IP);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.dstIpS.disabled = true; \n");
	html_tag("					form.dstIpE.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_DST_IP);
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				{ \n");
	html_tag("					form.lenmin.disabled = false; \n");
	html_tag("					form.lenmax.disabled = false; \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.lenmin.disabled = true; \n");
	html_tag("					form.lenmax.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				{ \n");
	html_tag("					form.protoc.disabled = false;  \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.protoc.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				} \n");
	html_tag("				JSChangeProtocol(); \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				{ \n");
	html_tag("					form.srcPrtS.disabled = false; \n");
	html_tag("					form.srcPrtE.disabled = false; \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.srcPrtS.disabled = true; \n");
	html_tag("					form.srcPrtE.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				{ \n");
	html_tag("					form.dstPrtS.disabled = false; \n");
	html_tag("					form.dstPrtE.disabled = false; \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.dstPrtS.disabled = true; \n");
	html_tag("					form.dstPrtE.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				{ \n");
	html_tag("					form.claSel.disabled = false;  \n");
	html_tag("					form.nC%d.disabled = false; \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.claSel.disabled = true; \n");
	html_tag("					form.nC%d.disabled = true; \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeEnableCriteria*/

	//Fonction javascript : JSChangeNotCriteria
	//*************************************
	html_tag("function JSChangeNotCriteria(loc_numCritere) \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numCritere) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_IP);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_DST_IP);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				JSChangeProtocol(); \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				if (true == form.nC%d.checked) \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeNotCriteria*/

	//Fonction javascript : JSTestCriteria
	//*************************************
	html_tag("function JSTestCriteria(loc_numCritere) \n");
	html_tag("{ \n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numCritere) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_SRC_IP);
	html_tag("				{ \n");
	html_tag("					if((false == validAddr(form.scrIpS, true))|| \n");
	html_tag("					   (false == validAddr(form.scrIpE, true)) \n");
	html_tag("					  ) \n");
	html_tag("					{  \n");
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("					else  \n");
	html_tag("					{  \n");
	html_tag("						var loc_ip_start = IPAddressToUnsignedInteger(form.scrIpS.value); \n");
	html_tag("						var loc_ip_end = IPAddressToUnsignedInteger(form.scrIpE.value); \n");
	html_tag("						if(loc_ip_start > loc_ip_end) \n");
	html_tag("						{  \n");
	html_tag("							alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_erreur_saisie_critere[CRITERIAPOLICY_SRC_IP]);
	html_tag("							loc_result = false;  \n");
	html_tag("						}  \n");
	html_tag("					}  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_IP);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_DST_IP);
	html_tag("				{ \n");
	html_tag("					if((false == validAddr(form.dstIpS, true))|| \n");
	html_tag("					   (false == validAddr(form.dstIpE, true)) \n");
	html_tag("					  ) \n");
	html_tag("					{  \n");
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("					else  \n");
	html_tag("					{  \n");
	html_tag("						var loc_ip_start = IPAddressToUnsignedInteger(form.dstIpS.value); \n");
	html_tag("						var loc_ip_end = IPAddressToUnsignedInteger(form.dstIpE.value); \n");
	html_tag("						if(loc_ip_start > loc_ip_end) \n");
	html_tag("						{  \n");
	html_tag("							alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_erreur_saisie_critere[CRITERIAPOLICY_DST_IP]);
	html_tag("							loc_result = false;  \n");
	html_tag("						}  \n");
	html_tag("					}  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_LENGTH_PACKET);
	html_tag("				{ \n");
	html_tag("					if(Number(form.lenmin.value) > Number(form.lenmax.value)) \n");
	html_tag("					{  \n");
	html_tag("						alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_erreur_saisie_critere[CRITERIAPOLICY_LENGTH_PACKET]);
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_SRC_PORT);
	html_tag("				{ \n");
	html_tag("					if(Number(form.srcPrtS.value) > Number(form.srcPrtE.value)) \n");
	html_tag("					{  \n");
	html_tag("						alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_erreur_saisie_critere[CRITERIAPOLICY_SRC_PORT]);
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_DST_PORT);
	html_tag("				{ \n");
	html_tag("					if(Number(form.dstPrtS.value) > Number(form.dstPrtE.value)) \n");
	html_tag("					{  \n");
	html_tag("						alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_erreur_saisie_critere[CRITERIAPOLICY_DST_PORT]);
	html_tag("						loc_result = false;  \n");
	html_tag("					}  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				if (true == form.vC%d.checked) \n",CRITERIAPOLICY_CLASS_SELECTOR);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return (loc_result); \n");
	html_tag("} \n");/*JSTestCriteria*/

	//Fonction javascript : JSClearAction
	//*************************************
	html_tag("function JSClearAction(loc_numAction) \n");
	html_tag("{ \n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numAction) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",ACTIONPOLICY_GATEWAY);
	html_tag("				form.vA%d.checked = false; \n",ACTIONPOLICY_GATEWAY);
	html_tag("				form.actGW.value = \"%s\";  \n",ps8GetStringIp(ADRESSE_IP_NULLE));
	html_tag("				form.actGW.disabled = true;  \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",ACTIONPOLICY_CLASS_SELECTOR);
	html_tag("				form.vA%d.checked = false; \n",ACTIONPOLICY_CLASS_SELECTOR);
	html_tag("				form.actCS.value = %d;  \n",CLASSSELECTOR_CS0);
	html_tag("				form.actCS.disabled = true;  \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSClearAction*/
	
	//Fonction javascript : JSChangeEnableAction
	//*************************************
	html_tag("function JSChangeEnableAction(loc_numAction) \n");
	html_tag("{ \n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numAction) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",ACTIONPOLICY_GATEWAY);
	html_tag("				if (true == form.vA%d.checked) \n",ACTIONPOLICY_GATEWAY);
	html_tag("				{ \n");
	html_tag("					form.actGW.disabled = false;  \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.actGW.disabled = true;  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",ACTIONPOLICY_CLASS_SELECTOR);
	html_tag("				if (true == form.vA%d.checked) \n",ACTIONPOLICY_CLASS_SELECTOR);
	html_tag("				{ \n");
	html_tag("					form.actCS.disabled = false;  \n");
	html_tag("				} \n");
	html_tag("				else \n");
	html_tag("				{ \n");
	html_tag("					form.actCS.disabled = true;  \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeEnableAction*/

	//Fonction javascript : JSTestAction
	//*************************************
	html_tag("function JSTestAction(loc_numAction) \n");
	html_tag("{ \n");
	html_tag("	var	loc_result = true; \n"); //INIT
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		switch(loc_numAction) \n");
	html_tag("		{ \n");
	html_tag("			case %d: \n",ACTIONPOLICY_GATEWAY);
	html_tag("				if (!form.vA%d.checked) \n",ACTIONPOLICY_GATEWAY);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			case %d: \n",ACTIONPOLICY_CLASS_SELECTOR);
	html_tag("				if (!form.vA%d.checked) \n",ACTIONPOLICY_CLASS_SELECTOR);
	html_tag("				{ \n");
	html_tag("				} \n");
	html_tag("				break; \n");
	html_tag("			default: \n");
	html_tag("				break; \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return (loc_result); \n");
	html_tag("} \n");/*JSTestAction*/

	//Fonction javascript : JSChangeProtocol
	//*************************************
	html_tag("function JSChangeProtocol() \n");
	html_tag("{ \n");
	html_tag("	with(document) \n");
	html_tag("	{ \n");
	html_tag("		if((true == form.vC%d.checked)&&(false == form.nC%d.checked)) \n",
			 CRITERIAPOLICY_IP_PROTOCOL,
			 CRITERIAPOLICY_IP_PROTOCOL);
	html_tag("		{ \n");
	html_tag("			switch(Number(form.protoc.value)) \n");
	html_tag("			{ \n");
	html_tag("				case %d: \n",POLICYROUTE_PROTOCOLE_UDP);
	html_tag("				case %d: \n",POLICYROUTE_PROTOCOLE_TCP);
	html_tag("					getElementById(\"TR_PORT_SOURCE\").style.display=\"\";   \n");
	html_tag("					getElementById(\"TR_PORT_DESTINATION\").style.display=\"\";   \n");
	html_tag("					break; \n");
	html_tag("				case %d: \n",POLICYROUTE_PROTOCOLE_ICMP);
	html_tag("				default: \n");
	html_tag("					getElementById(\"TR_PORT_SOURCE\").style.display=\"none\";   \n");
	html_tag("					getElementById(\"TR_PORT_DESTINATION\").style.display=\"none\"; \n");
	html_tag("					break; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			getElementById(\"TR_PORT_SOURCE\").style.display=\"none\";   \n");
	html_tag("			getElementById(\"TR_PORT_DESTINATION\").style.display=\"none\";   \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("} \n");/*JSChangeProtocol*/


	html_tag("</SCRIPT>\n");
}/*proc_JavaScript_SUConfigRoutingPolitic*/

//=====================================================================================
// Fonction		: proc_HtmlDetailRoutePolicy
// Entrees		: <loc_ps_route< : route IP
//				: <loc_u16_idx_route> : index de la route 
// Sortie		: <loc_u8_resultat>  : TRUE ou FALSE
// Auteur		: CM - 15/04/2010 -
// Description	: Affiche dans le cadre jaune l'état de configuration de la route
//=====================================================================================
void proc_HtmlDetailRoutePolicy(S_STRUCT_ROUTE_POLICY *loc_ps_route, u16sod loc_u16_idx_route)
{
	s8sod loc_ps8_addr_ip_start[MAX_LG_FORMAT_ADRESSE_IP+1];
	s8sod loc_ps8_addr_ip_end[MAX_LG_FORMAT_ADRESSE_IP+1];

	strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(ADRESSE_IP_NULLE)); //INIT
	
	html_tag("<tr class=\"contentVisible\" id=\"DIV_DETAILS%d\"> \n",
			loc_u16_idx_route);
	html_tag("<td><table width=450 class=\"infoJaune\"> \n");
	html_tag("<tr> \n");
	html_tag("	<td><B>%s</B></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_nom_route_politique);
	html_tag("	<td><B>:</B></td> \n");
	html_tag("	<td><B>%s</B></td> \n",
			 loc_ps_route->ps8_policy_name);
	html_tag("	<td colspan=5>&nbsp;</td> \n");
	html_tag("</tr> \n");
	//Liste des critères sélectionnés
	html_tag("<tr> \n");
	html_tag("	<td colspan=6><u>%s</u></td> \n",
			pt_tb_msg[u8_html_langue].ps8_msg_liste_criteres_selectionnes);
	html_tag("</tr> \n");
	//Source IP
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_SRC_IP])
	{
		strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(loc_ps_route->u32_critere_src_ip_start));
		strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(loc_ps_route->u32_critere_src_ip_end));
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_source_ip);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%s - %s</td> \n",
				 loc_ps8_addr_ip_start,
				 loc_ps8_addr_ip_end);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_SRC_IP])? "checked" : "");
		html_tag("</tr> \n");
	}
	//Destination IP
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_DST_IP])
	{
		strcpy(loc_ps8_addr_ip_start, ps8GetStringIp(loc_ps_route->u32_critere_dst_ip_start));
		strcpy(loc_ps8_addr_ip_end, ps8GetStringIp(loc_ps_route->u32_critere_dst_ip_end));
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_destination_ip);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%s - %s</td> \n",
				 loc_ps8_addr_ip_start,
				 loc_ps8_addr_ip_end);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_DST_IP])? "checked" : "");
		html_tag("</tr> \n");
	}
	//Longueur des paquets
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_longueur_paquet);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%d - %d</td> \n",
				 loc_ps_route->u16_critere_len_packet_min,
				 loc_ps_route->u16_critere_len_packet_max);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET])? "checked" : "");
		html_tag("</tr> \n");
	}
	//Protocole IP
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_protocole_ip);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_routepolicy_protocole[loc_ps_route->u8_critere_ip_protocol]);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL])? "checked" : "");
		html_tag("</tr> \n");
	}
	//Port source
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_source);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%d - %d</td> \n",
				 loc_ps_route->u16_critere_src_port_start,
				 loc_ps_route->u16_critere_src_port_end);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_SRC_PORT])? "checked" : "");
		html_tag("</tr> \n");
	}
	//Port destination
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_DST_PORT])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_destination);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%d - %d</td> \n",
				 loc_ps_route->u16_critere_dst_port_start,
				 loc_ps_route->u16_critere_dst_port_end);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_DST_PORT])? "checked" : "");
		html_tag("</tr> \n");
	}
	//Class selector
	if(TRUE == loc_ps_route->pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_class_selector);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_class_selector[loc_ps_route->u8_critere_class_selector]);
		html_tag("	<td>&nbsp;&nbsp;&nbsp;</td> \n");
		html_tag("	<td>%s&nbsp;:&nbsp;<input disabled %s type=\"checkbox\"></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M,
				 (TRUE == loc_ps_route->pu8_not_critere[CRITERIAPOLICY_CLASS_SELECTOR])? "checked" : "");
		html_tag("</tr> \n");
	}
	html_tag("<tr> \n");
	html_tag("	<td colspan=6><u>%s</u></td> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_liste_actions_selectionnees);
	html_tag("</tr> \n");
	//Nouvelle passerelle
	if(TRUE == loc_ps_route->pu8_valid_action[ACTIONPOLICY_GATEWAY])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nouvelle_passerelle);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%s</td> \n",
				 ps8GetStringIp(loc_ps_route->u32_new_gateway));
		html_tag("</tr> \n");
	}
	//Nouvelle class selector
	if(TRUE == loc_ps_route->pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])
	{
		html_tag("<tr> \n");
		html_tag("	<td><B>%s</B></td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nouvelle_class_selector);
		html_tag("	<td><B>:</B></td> \n");
		html_tag("	<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_choix_class_selector[loc_ps_route->u8_new_class_selector]);
		html_tag("</tr> \n");
	}
	html_tag("</table></td> \n");
	html_tag("</tr> \n");
}/*proc_HtmlDetailRoutePolicy*/

   
//=====================================================================================
// Fonction		: SUConfigRoutingPolitic
// Entrees		: <loc_p_varlist< : liste des paramètres URL
//				  <loc_s32_form_method> : méthode du formulaire
// Sortie		: Rien
// Auteur		: CM - 15/04/2010
// Description	: Page HTML Configuration: IP Routing 
//				"URL=SUConfigRoutingPolitic"
//=====================================================================================
void SUConfigRoutingPolitic(s8sod **loc_p_varlist, s32sod loc_s32_form_method)
{
	S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS loc_s_results;
	s8sod	loc_ps8_emsg[50];
	s32sod	loc_s32_sem;
	u8sod	loc_u8_result_test;
	u8sod	loc_u8_numForm;
	u8sod	loc_u8_i;
	u16sod	loc_u16_i;
	u16sod	loc_u16_route_a_supprimer;
	S_STRUCT_ROUTE_POLICY	loc_s_route;	//une route
	u8sod	loc_u8_param_html;
	u8sod	loc_u8_flag_configure_route;
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;

	loc_u8_result_test = FALSE; //INIT
	memset(&loc_s_route, 0, sizeof(S_STRUCT_ROUTE_POLICY)); //INIT
	loc_u8_param_html = PARAM_SUCONFIGROUTINGPOLITIC_NULL;	//INIT
	loc_u16_route_a_supprimer = 0;	//INIT
	loc_u8_flag_configure_route = TRUE;	//INIT	
	
	printf("Content-type: text/html\n\n");/* Mandatory */

	//Test paramètres de la page HTML
	if (s32GetArgNb(loc_p_varlist) > 3)  //deja 3 utilise pour URL=SUConfigRoutingPolitic&param=<num_page_html>
	{
		loc_u8_param_html = (u8sod)atoi(loc_p_varlist[3]);
		if(loc_u8_param_html < NB_MAX_PARAM_SUCONFIGROUTINGPOLITIC)
		{
			;	//page ok
		}
		else//CONDITION: page KO
		{
			PagePbdebug(loc_p_varlist,loc_ps8_emsg);
			return;
		}
	}
	else
	{
		PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		return;
	}

	// Entrée au setup par mot de passe
	if(!TestPassword(getenv("REMOTE_ADDR"), MIDDLE_LEVEL_ACCESS))
	{
		sprintf(ps8_pageHtmlEnCours,"SUConfigRoutingPolitic&param=%d",
				loc_u8_param_html);

		PreparePagePswd(ps8_pageHtmlEnCours);
		return;
	}
	
	if (s32GetArgNb(loc_p_varlist) > 4)  //URL=SUConfigRoutingPolitic&param=<num_page_html>&hidden1=<numForm>"&...
	{
		// Initialisation de la structure loc_s_results
		memset(&loc_s_results,'\0',sizeof(S_FORM_CONFIG_ROUTINGPOLITIC_RESULTS));

		// Décodage de la requête
		if (!form_decode(s_FormConfigRoutingPoliticFields, &loc_s_results, loc_p_varlist, loc_ps8_emsg))
		{//on sort a 0 : pb dans decodage 
		  //on fait une page pour le debug
		  PagePbdebug(loc_p_varlist,loc_ps8_emsg);
		  return; // on sort!
		}
		else
		{
			loc_u8_numForm =  (u8sod)atoi(loc_s_results.ps8_hidden1);
			if(loc_u8_numForm < NB_MAX_FORM_SUCONFIGROUTINGPOLITIC)
			{
				if(FORM_SUCONFIGROUTINGPOLITIC_AJOUTER_VALIDER == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigRouting(&s_html_cfg_eqpmt))
					{
						loc_s_route.u8_enabled = TRUE;
						
						strcpy(loc_s_route.ps8_policy_name, loc_s_results.ps8_policyname);
						//Liste des critères
						for(loc_u16_i=0;loc_u16_i<NB_MAX_CRITERIA_POLICY;loc_u16_i++)
						{
							if(0 == strcmp(loc_s_results.ps8_validcritere[loc_u16_i], CHECKBOX_VALUE_CHECKED))
							{
								loc_s_route.pu8_valid_critere[loc_u16_i] = TRUE;
							}
							else
							{
								loc_s_route.pu8_valid_critere[loc_u16_i] = FALSE;
							}
						}
						for(loc_u16_i=0;loc_u16_i<NB_MAX_CRITERIA_POLICY;loc_u16_i++)
						{
							if(TRUE == loc_s_route.pu8_valid_critere[loc_u16_i])
							{
								if(0 == strcmp(loc_s_results.ps8_notcritere[loc_u16_i], CHECKBOX_VALUE_CHECKED))
								{
									loc_s_route.pu8_not_critere[loc_u16_i] = TRUE;
								}
								else
								{
									loc_s_route.pu8_not_critere[loc_u16_i] = FALSE;
								}
							}
							else
							{
								loc_s_route.pu8_not_critere[loc_u16_i] = FALSE;
							}
						}

						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_IP])
						{
							loc_s_route.u32_critere_src_ip_start = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_srcIpstart, &loc_u8_ret);
							loc_s_route.u32_critere_src_ip_end = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_srcIpend, &loc_u8_ret);
						}
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_IP])
						{
							loc_s_route.u32_critere_dst_ip_start = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_dstIpstart, &loc_u8_ret);
							loc_s_route.u32_critere_dst_ip_end = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_dstIpend, &loc_u8_ret);
						}
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])
						{
							loc_s_route.u16_critere_len_packet_min = (u16sod)atoi(loc_s_results.ps8_lengthmin);
							loc_s_route.u16_critere_len_packet_max = (u16sod)atoi(loc_s_results.ps8_lengthmax);
						}
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])
						{
							loc_s_route.u8_critere_ip_protocol = (u8sod)atoi(loc_s_results.ps8_ipprotocol);
						}
						
						if(TRUE == u8TestPolicyCriteriaPort_Allowed(&loc_s_route))
						{
							if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])
							{
								loc_s_route.u16_critere_src_port_start = (u16sod)atoi(loc_s_results.ps8_srcPortstart);
								loc_s_route.u16_critere_src_port_end = (u16sod)atoi(loc_s_results.ps8_srcPortend);
							}
							if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT])
							{
								loc_s_route.u16_critere_dst_port_start = (u16sod)atoi(loc_s_results.ps8_dstPortstart);
								loc_s_route.u16_critere_dst_port_end = (u16sod)atoi(loc_s_results.ps8_dstPortend);
							}
						}
						else
						{
							loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_PORT] = FALSE;
							loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT] = FALSE;
						}
						if(TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])
						{
							loc_s_route.u8_critere_class_selector = (u8sod)atoi(loc_s_results.ps8_classSelector);
						}
						
						//Liste des actions
						for(loc_u16_i=0;loc_u16_i<NB_MAX_ACTIONS_POLICY;loc_u16_i++)
						{
							if(0 == strcmp(loc_s_results.ps8_validaction[loc_u16_i], CHECKBOX_VALUE_CHECKED))
							{
								loc_s_route.pu8_valid_action[loc_u16_i] = TRUE;
							}
							else
							{
								loc_s_route.pu8_valid_action[loc_u16_i] = FALSE;
							}
						}
						if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY])
						{
							loc_s_route.u32_new_gateway = (u32sod)u32DecodageAdresseReseau(loc_s_results.ps8_actadrGw, &loc_u8_ret);
						}
						if(TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])
						{
							loc_s_route.u8_new_class_selector = (u8sod)atoi(loc_s_results.ps8_actCS);
						}

						
						if(PARAM_SUCONFIGROUTINGPOLITIC_NULL == loc_u8_param_html) //CONDITION: bouton Ajouter
						{
							if(TRUE == u8AddRoutePolitic(&s_html_cfg_eqpmt, &loc_s_route))
							{
								if(TRUE==u8TestConfigRouting(&s_html_cfg_eqpmt))
								{
									if(TRUE == u8EditConfigRouting(&s_html_cfg_eqpmt))
									{
										loc_u8_result_test = TRUE;
									}
								}
							}
						}
						else //CONDITION: bouton Valider
						{
							if((PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN <= loc_u8_param_html)&&
							   (loc_u8_param_html <= PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MAX)
							  )
							{
								 s_html_cfg_eqpmt.s_ip_routing.ps_route_policy[(loc_u8_param_html-PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN)] = loc_s_route;
								 if(TRUE==u8TestConfigRouting(&s_html_cfg_eqpmt))
								 {
									 if(TRUE == u8EditConfigRouting(&s_html_cfg_eqpmt))
									 {
										 loc_u8_result_test = TRUE;
									 }
								 }
							}
							
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}

				if(FORM_SUCONFIGROUTINGPOLITIC_SUPPRIMER == loc_u8_numForm)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigRouting(&s_html_cfg_eqpmt))
					{
						if((PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN <= loc_u8_param_html)&&
						   (loc_u8_param_html <= PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MAX)
						  )
						{
							loc_u16_route_a_supprimer = (u16sod)(loc_u8_param_html-PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN);
							if(loc_u16_route_a_supprimer < NB_MAX_POLICY_ROUTING)
							{
								s_html_cfg_eqpmt.s_ip_routing.ps_route_policy[loc_u16_route_a_supprimer] = S_CONFIG_EQUIPEMENT_DEFAUT.s_ip_routing.ps_route_policy[0]; //RAZ
								if(TRUE==u8TestConfigRouting(&s_html_cfg_eqpmt))
								{
									if(TRUE == u8EditConfigRouting(&s_html_cfg_eqpmt))
									{
										loc_u8_result_test = TRUE;
									}
								}
							}
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				
				if(FALSE == loc_u8_result_test)
				{
					sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
							WARNING_CONFIG_KO);
					Html_GotoPage(ps8_pageHtmlRetour);
					return;
				}
				//On recharge la page pour re-initialiser les champs "objets" HTML
				sprintf(ps8_pageHtmlEnCours,"SUConfigRoutingPolitic&param=%d",
						PARAM_SUCONFIGROUTINGPOLITIC_NULL);
				PreparePageCfgInProgress(ps8_pageHtmlEnCours);
				VCfgInProgress(loc_p_varlist, loc_s32_form_method);
				return; // on sort!
			}
			else//CONDITION: page KO
			{
				PagePbdebug(loc_p_varlist,loc_ps8_emsg);
				return;
			}
		}
	}
	

	//Lecture de la base de données
	s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
	if( (FALSE == u8FillConfigGeneral(&s_html_cfg_eqpmt)) ||
		(FALSE == u8FillConfigRouting(&s_html_cfg_eqpmt))
	  )
	{
		u8_html_base_donnees_inaccessible = TRUE; //defaut accès bdd
	}
	s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

	//Test si accès au contenu page 
	if(FALSE == u8TestStartHtml()) //CONDITION: accès au contenu page HTML immpossible
	{
		return; // on sort!
	}

	//Page accéssible uniquement en mode STATION / router
	if((MODE_RADIO_MODEM_STATION != s_html_cfg_eqpmt.s_gene.u8_mode_radio_modem) ||
	   (MODE_NETWORK_ROUTER != s_html_cfg_eqpmt.s_gene.u8_mode_network)
	  )//CONDITION: STATION / router
	{
		sprintf(ps8_pageHtmlRetour,"/cgi-bin/cgi_fh?URL=Vwarning&%d",
				WARNING_MODE_ONLY_STATION_ROUTER);
		Html_GotoPage(ps8_pageHtmlRetour);
		return;
	}
	
	html_tag("<html> \n");
	html_tag("<head> \n");
	html_tag("<title>%s: %s</title> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<LINK href=\"../style.css\" type=text/css rel=stylesheet></LINK> \n");
	html_tag ("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> \n");
	html_tag ("<meta http-equiv=\"Pragma\" content=\"no-cache\"> \n");
	html_tag ("<meta http-equiv=\"Expires\" content=\"-1\"> \n");
	html_tag("<STYLE type=text/css>\n");
	html_tag("tr.contentVisible {\n");
	html_tag("	cursor:auto; \n");		//display:inline ;
	html_tag("} \n");
	html_tag("tr.contentInvisible { \n");
	html_tag("	display:none;cursor:auto; \n");
	html_tag("}\n");
	html_tag("table.infoJaune { \n");
	html_tag("	FONT-SIZE: 8pt; FONT-FAMILY: courier; BORDER-RIGHT: 1px solid; PADDING-RIGHT: 5px; BORDER-TOP: 1px solid; PADDING-LEFT: 5px; PADDING-BOTTOM: 5px; BORDER-LEFT: 1px solid; PADDING-TOP: 5px; BORDER-BOTTOM: 1px solid; BACKGROUND-COLOR: #FFFFD7; cursor:text; \n");
	html_tag("}\n");
	html_tag("</STYLE>\n");
	html_tag("</head> \n");

	html_tag("<body onload=\"return(StartJavaScript());\"> \n");

	sprintf(ps8_pageHtmlEnCours,"/cgi-bin/cgi_fh?URL=SUConfigRoutingPolitic&param=%d",
			loc_u8_param_html);
	JSActualiser(ps8_pageHtmlEnCours);	//pour la fonction Actualiser

	JSIPCheck();
	JSNumCheck();
	JSTextCheck();

	proc_JavaScript_SUConfigRoutingPolitic();

	// Start the form
	html_tag("<form action=\"/cgi-bin/cgi_fh\" method=\"GET\" name=\"form\" target=\"frame_c\"> \n");
	form_hidden("URL","SUConfigRoutingPolitic");//permet d'avoir la bonne page de rafraichit!!
	html_tag("<input type=\"hidden\"  name=\"param\"  value=\"%d\" >",
			 loc_u8_param_html);
	form_hidden("hidden1","0");

	html_tag("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"580\"> \n");
	html_tag("<TR><TD vAlign=top height=40><P class=header>%s: %s</P></TD></TR> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_configuration,
			 pt_tb_msg[u8_html_langue].ps8_msg_routage_IP);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_sous_titre_SUConfigRouting);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
		

	
	//	===========================================
	//	AFFICHAGE D'INFORMATIONS
	//	communes à toutes les pages HTML
	//	===========================================
	AfficheDansToutesLesPages();

	//ONGLET
	HtmlPrint_OngletRouting(PAGE_HTML_SUCONFIGROUTING__POLITIC);
	html_tag("<tr><td><P>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_detail_onglet_SUConfigRoutingPolitic);

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_table_politique_routage);
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	if(TRUE == u8TestAllRoutePoliticFree(&s_html_cfg_eqpmt)) //CONDITION: Aucune route politique configurée
	{
		html_tag("<tr><td>&nbsp;<B>%s</B></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_aucune_route_politique_activee);
	}
	else
	{
		for(loc_u16_i=0;loc_u16_i<NB_MAX_POLICY_ROUTING;loc_u16_i++)
		{
			if(TRUE == s_html_cfg_eqpmt.s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled)
			{
				html_tag("<tr><td><table border=\"0\">  \n");
				html_tag("	<tr>\n");
				html_tag("	   <td width=450><span style=\"cursor: pointer;\" onclick=\"JSReduc(%d)\"><u>%d:&nbsp;&nbsp; %s</u></span></td> \n",
						 loc_u16_i,
						 (loc_u16_i+1),
						 s_html_cfg_eqpmt.s_ip_routing.ps_route_policy[loc_u16_i].ps8_policy_name);
				html_tag("	   <td>&nbsp;<input type=\"button\" value=\"%s\" onClick=\"self.location.replace('/cgi-bin/cgi_fh?URL=SUConfigRoutingPolitic&param=%d');\"></td> \n",
						 pt_tb_msg[u8_html_langue].ps8_msg_modifier,
						 (PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN+loc_u16_i));
				html_tag("	</tr>\n");
				html_tag("</table></td></tr>\n");

				proc_HtmlDetailRoutePolicy(&s_html_cfg_eqpmt.s_ip_routing.ps_route_policy[loc_u16_i], loc_u16_i);
			}
		}
	}

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	memset(&loc_s_route, 0, sizeof(S_STRUCT_ROUTE_POLICY)); //RAZ
	if(PARAM_SUCONFIGROUTINGPOLITIC_NULL == loc_u8_param_html)
	{
		html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_ajouter_route_politique);
		if(FALSE == u8TestRoutePoliticFree(&s_html_cfg_eqpmt))
		{
			html_tag("<tr><td>&nbsp;<P class=warning><B>%s!</B> %s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_attention,
					 pt_tb_msg[u8_html_langue].ps8_msg_table_politique_routage_complete);
			loc_u8_flag_configure_route = FALSE;
		}
		else
		{
			//route par défaut
			loc_s_route = S_CONFIG_EQUIPEMENT_DEFAUT.s_ip_routing.ps_route_policy[0];
		}
	}
	else
	{
		if((PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN <= loc_u8_param_html)&&
		   (loc_u8_param_html <= PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MAX)
		  )
		{
			html_tag("<tr><td><P class=undermenu>%s</P></td></tr> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_modifier_route_politique);
			loc_s_route = s_html_cfg_eqpmt.s_ip_routing.ps_route_policy[(loc_u8_param_html-PARAM_SUCONFIGROUTINGPOLITIC_CHANGE_MIN)];
		}
		else
		{
			loc_u8_flag_configure_route = FALSE;
		}
	}

	if(TRUE == loc_u8_flag_configure_route)
	{
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		//Table générale
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
		html_tag("		</tr> \n");
		//Nom politique de routage
		html_tag("		<tr> \n");
		html_tag("			<td nowrap>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nom_route_politique);
		html_tag("			<td><input type=\"text\" size=\"%d\" maxlength=\"%d\" name=\"name\" value=\"%s\" onchange=\"return(isValidText(this,false,true))\"></td> \n",
				 TAILLE_MAX_POLICY_NAME,
				 TAILLE_MAX_POLICY_NAME,
				 loc_s_route.ps8_policy_name);
		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");

		//Table critères
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_critere);
		html_tag("			<th>%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_non_M);
		html_tag("		</tr> \n");
		//Source IP
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_source_ip);
		html_tag("			<td><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_SRC_IP,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_IP])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_SRC_IP);
		html_tag("			<td nowrap>");
		html_tag("<input type=\"text\" size=\"15\" name=\"scrIpS\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"> ",
				 ps8GetStringIp(loc_s_route.u32_critere_src_ip_start));
		html_tag("&nbsp;-&nbsp;\n");
		html_tag("<input type=\"text\" size=\"15\" name=\"scrIpE\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\">",
				  ps8GetStringIp(loc_s_route.u32_critere_src_ip_end));
		html_tag("</td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_SRC_IP,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_SRC_IP])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_SRC_IP);
		html_tag("		</tr> \n");
		//Destination IP
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_destination_ip);
		html_tag("			<td><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_DST_IP,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_IP])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_DST_IP);
		html_tag("			<td nowrap>");
		html_tag("<input type=\"text\" size=\"15\" name=\"dstIpS\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"> ",
				 ps8GetStringIp(loc_s_route.u32_critere_dst_ip_start));
		html_tag("&nbsp;-&nbsp;\n");
		html_tag("<input type=\"text\" size=\"15\" name=\"dstIpE\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\">",
				 ps8GetStringIp(loc_s_route.u32_critere_dst_ip_end));
		html_tag("</td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_DST_IP,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_DST_IP])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_DST_IP);
		html_tag("		</tr> \n");
		//Longueur des paquets
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_longueur_paquet);
		html_tag("			<td nowrap><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_LENGTH_PACKET,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_LENGTH_PACKET])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_LENGTH_PACKET);
		html_tag("			<td>");
		html_tag("<input type=\"text\" size=\"5\" maxlength=5 name=\"lenmin\" value=%d onchange=\"return(isInteger(this,%d,%d))\"> ",
				 loc_s_route.u16_critere_len_packet_min,
				 LEN_PACKET_MIN,
				 LEN_PACKET_MAX);
		html_tag("&nbsp;-&nbsp;\n");
		html_tag("<input type=\"text\" size=\"5\" maxlength=5 name=\"lenmax\" value=%d onchange=\"return(isInteger(this,%d,%d))\">",
				 loc_s_route.u16_critere_len_packet_max,
				 LEN_PACKET_MIN,
				 LEN_PACKET_MAX);
		html_tag("</td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_LENGTH_PACKET,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_LENGTH_PACKET])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_LENGTH_PACKET);
		html_tag("		</tr> \n");
		//Protocole IP
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_protocole_ip);
		html_tag("			<td><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_IP_PROTOCOL,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_IP_PROTOCOL])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_IP_PROTOCOL);
		html_tag("			<td><SELECT name=\"protoc\" size=\"1\" onchange=\"return(JSChangeProtocol())\"> \n");
		for(loc_u8_i=0;loc_u8_i<NB_MAX_POLICYROUTE_PROTOCOLES;loc_u8_i++)
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_s_route.u8_critere_ip_protocol == loc_u8_i) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_routepolicy_protocole[loc_u8_i]);
		}
		html_tag("				  </select></td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_IP_PROTOCOL,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_IP_PROTOCOL])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_IP_PROTOCOL);
		html_tag("		</tr> \n");
		//Port source
		html_tag("		<tr id=TR_PORT_SOURCE> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_source);
		html_tag("			<td><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_SRC_PORT,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_SRC_PORT])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_SRC_PORT);
		html_tag("			<td nowrap>");
		html_tag("<input type=\"text\" size=\"5\" maxlength=5 name=\"srcPrtS\" value=%d onchange=\"return(isInteger(this,%d,%d))\"> ",
				 loc_s_route.u16_critere_src_port_start,
				 PORT_UDP_TCP_MIN,
				 PORT_UDP_TCP_MAX);
		html_tag("&nbsp;-&nbsp;\n");
		html_tag("<input type=\"text\" size=\"5\" maxlength=5 name=\"srcPrtE\" value=%d onchange=\"return(isInteger(this,%d,%d))\">",
				 loc_s_route.u16_critere_src_port_end,
				 PORT_UDP_TCP_MIN,
				 PORT_UDP_TCP_MAX);
		html_tag("</td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_SRC_PORT,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_SRC_PORT])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_SRC_PORT);
		html_tag("		</tr> \n");
		//Port destination
		html_tag("		<tr id=TR_PORT_DESTINATION> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_port_destination);
		html_tag("			<td><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_DST_PORT,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_DST_PORT])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_DST_PORT);
		html_tag("			<td nowrap>");
		html_tag("<input type=\"text\" size=\"5\" maxlength=5 name=\"dstPrtS\" value=%d onchange=\"return(isInteger(this,%d,%d))\"> ",
				 loc_s_route.u16_critere_dst_port_start,
				 PORT_UDP_TCP_MIN,
				 PORT_UDP_TCP_MAX);
		html_tag("&nbsp;-&nbsp;\n");
		html_tag("<input type=\"text\" size=\"5\" maxlength=5 name=\"dstPrtE\" value=%d onchange=\"return(isInteger(this,%d,%d))\">",
				 loc_s_route.u16_critere_dst_port_end,
				 PORT_UDP_TCP_MIN,
				 PORT_UDP_TCP_MAX);
		html_tag("</td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_DST_PORT,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_DST_PORT])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_DST_PORT);
		html_tag("		</tr> \n");
		//Class selector
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_class_selector);
		html_tag("			<td><input name=\"vC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_CLASS_SELECTOR,
				 (TRUE == loc_s_route.pu8_valid_critere[CRITERIAPOLICY_CLASS_SELECTOR])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_CLASS_SELECTOR);
		html_tag("			<td><SELECT name=\"claSel\" size=\"1\"> \n");
		for(loc_u8_i=0;loc_u8_i<NB_MAX_CLASSSELECTOR;loc_u8_i++)
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_s_route.u8_critere_class_selector == loc_u8_i) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_class_selector[loc_u8_i]);
		}
		html_tag("				  </select></td> \n");
		html_tag("			<td><input name=\"nC%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeNotCriteria(%d))\"></td> \n",
				 CRITERIAPOLICY_CLASS_SELECTOR,
				 (TRUE == loc_s_route.pu8_not_critere[CRITERIAPOLICY_CLASS_SELECTOR])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 CRITERIAPOLICY_CLASS_SELECTOR);
		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");


		//Table actions
		html_tag("<tr><td><table border=\"1\" cellpadding=\"2\" cellspacing=\"1\">  \n");
		html_tag("		<tr> \n");
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_parametre);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_action);
		html_tag("			<th width=\"150\">%s</th> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_valeur);
		html_tag("		</tr> \n");
		//Nouvelle passerelle
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nouvelle_passerelle);
		html_tag("			<td><input name=\"vA%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableAction(%d))\"></td> \n",
				 ACTIONPOLICY_GATEWAY,
				 (TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_GATEWAY])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 ACTIONPOLICY_GATEWAY);
		html_tag("			<td>");
		html_tag("<input type=\"text\" size=\"15\" name=\"actGW\" value=\"%s\" width=\"15\" onchange=\"return(validAddr(this, false))\"> ",
				 ps8GetStringIp(loc_s_route.u32_new_gateway));
		html_tag("</td> \n");
		html_tag("		</tr> \n");
		//Nouvelle class selector
		html_tag("		<tr> \n");
		html_tag("			<td>%s</td> \n",
				 pt_tb_msg[u8_html_langue].ps8_msg_nouvelle_class_selector);
		html_tag("			<td><input name=\"vA%d\" type=\"checkbox\" %s value=\"%s\" onchange=\"return(JSChangeEnableAction(%d))\"></td> \n",
				 ACTIONPOLICY_CLASS_SELECTOR,
				 (TRUE == loc_s_route.pu8_valid_action[ACTIONPOLICY_CLASS_SELECTOR])? "checked" : "",
				 CHECKBOX_VALUE_CHECKED,
				 ACTIONPOLICY_CLASS_SELECTOR);
		html_tag("			<td><SELECT name=\"actCS\" size=\"1\"> \n");
		for(loc_u8_i=0;loc_u8_i<NB_MAX_CLASSSELECTOR;loc_u8_i++)
		{
			html_tag("		   <option %s value=\"%d\">%s</option>	\n",
					 ((loc_s_route.u8_new_class_selector == loc_u8_i) ? "selected" : ""),
					 loc_u8_i,
					 pt_tb_msg[u8_html_langue].ps8_msg_choix_class_selector[loc_u8_i]);
		}
		html_tag("				  </select></td> \n");
		html_tag("		</tr> \n");
		html_tag("</table></td></tr> \n");

		html_tag("<tr><td>&nbsp;</td></tr> \n");
		
		html_tag("<tr><td>&nbsp;</td></tr> \n");
		html_tag("<tr><td>&nbsp;");
		if(PARAM_SUCONFIGROUTINGPOLITIC_NULL == loc_u8_param_html) //CONDITION: bouton Ajouter
		{
			html_tag("<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\" > \n",
					pt_tb_msg[u8_html_langue].ps8_msg_ajouter,
					FORM_SUCONFIGROUTINGPOLITIC_AJOUTER_VALIDER);
			html_tag("&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_effacer,
					 FORM_SUCONFIGROUTINGPOLITIC_EFFACER);
		}
		else //CONDITION: bouton Valider
		{
			html_tag("<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_valider,
					 FORM_SUCONFIGROUTINGPOLITIC_AJOUTER_VALIDER);
			html_tag("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"return SelectFormulaire(%d,form)\"> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_supprimer,
					 FORM_SUCONFIGROUTINGPOLITIC_SUPPRIMER);
			html_tag("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"button\" value=\"%s\" onClick=\"self.location.replace('/cgi-bin/cgi_fh?URL=SUConfigRoutingPolitic&param=%d');\"> \n",
					 pt_tb_msg[u8_html_langue].ps8_msg_annuler,
					 PARAM_SUCONFIGROUTINGPOLITIC_NULL);

			
		}
		html_tag("&nbsp;</td></tr> \n");
	}

	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	html_tag("<tr><td>&nbsp;</td></tr> \n");
	
	html_tag("</table> \n");

	html_tag("</form> \n");
	html_tag("</body> \n");
	html_tag("</html> \n");

}/*SUConfigRoutingPolitic*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModule_SUConfigRoutingPolitic
// Entrees		: rien
// Sortie		: rien
// Auteur		: 
// Description	: Initialisation du module de SUConfigRoutingPolitic
//=====================================================================================
void InitModule_SUConfigRoutingPolitic(void)
{
}/*InitModule_SUConfigRoutingPolitic*/
