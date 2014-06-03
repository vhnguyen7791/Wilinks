/*========================================================================*/
/* NOM DU FICHIER  : mib_wrm100_data.h									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009											  */
/* Libelle         : NET-SNMP:											  */
/* Projet          : WRM100                                               */
/* Indice          : BE059				                                  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
//	- CREATION
//BE019 16/03/2010 CM
// - Ajout MIB wrm100 dans agent SNMP
//BE020 23/03/2010 CM
// - Ajout gestion VLAN
//BE022 29/03/2010 CM
// - Ajout gestion multicast
//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
// - Modification gestion routage par le processus bird
//BE038 09/07/2010 CM
// - Ajout variables SNMP : stp (bridge), seuil rx (wifi), temperature
//BE053 16/12/2010 CM
// - Modification de la MIB / agent SNMP (suite integration Driver-N)
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
// - Ajout dans exploitation du canal en cours (sur AP et STA)
//BE059 16/02/2011 CM/JP
// - Ajout mode RSSI (syslog)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/


/*_____II - DEFINE SBIT __________________________________________________*/

#ifdef MIB_WRM100_DATA_H
#define MIB_WRM100_DATA_H_EXT
#else
#define MIB_WRM100_DATA_H_EXT extern
#endif

/** ** for MIB Tree       */
enum LISTE_SCALAIRES_MIB_WRM100
{
	//Sous le noeud description
	DESCSTRUEQUIPMENTTYPE =	1,
	DESCSTRUID,
	DESCSTRULOCATION,
	DESCSTRULANGUAGE,

	//Sous le noeud managment
	MGMTMODERADIOMODEM,
	MGMTNETMODE,
	MGMTNETHOSTNAME,
	MGMTNETBRIDGEIPMODE,
	MGMTNETBRIDGEIPADDRESS,
	MGMTNETBRIDGEMASK,
	MGMTNETBRIDGEGATEWAY,
	MGMTNETBRIDGEDHCPFALLBACKIP,
	MGMTNETBRIDGESTP,
	MGMTNETLANIPMODE,
	MGMTNETLANIPADDRESS,
	MGMTNETLANMASK,
	MGMTNETWLANIPMODE,
	MGMTNETWLANIPADDRESS,
	MGMTNETWLANMASK,
	MGMTNETWLANGATEWAY,
	MGMTNETWLANDHCPFALLBACKIP,
	MGMTNETVLAN_SUPPORT,
	MGMTNETVLAN_NAME,
	MGMTNETVLAN_ID,
	MGMTNETVLAN_RESERVENOTAGGEDLAN,
	MGMTNETVLAN_NOTAGGEDLANIPADDRESS,
	MGMTNETVLAN_NOTAGGEDLANMASK,
	MGMTWIRELESSSSID,
	MGMTWIRELESSSSIDMASK,
	MGMTWIRELESS802DOT11MODE,
	MGMTWIRELESSCHANNELSPECTRUMWIDTH,
	MGMTWIRELESSCHANNEL,
	MGMTWIRELESSFREQUENCY_MHZ,
	MGMTWIRELESSCHANNELMODE,
	MGMTWIRELESSISOCHANNEL,
	MGMTWIRELESSISOFREQUENCY_MHZ,
	MGMTWIRELESSTRANSMITTERPOWER_DBM,
	MGMTWIRELESSDATARATE,
	MGMTWIRELESSSECURITYMODE,
	MGMTWIRELESSWPAAUTHENTICATION,
	MGMTWIRELESSADV_ACKTIMEOUT,
	MGMTWIRELESSADV_PREAMBLETYPE,
	MGMTWIRELESSADV_FRAGMENT_THRSLD,
	MGMTWIRELESSADV_RTS_CTS_THRSLD,
	MGMTWIRELESSADV_BEACONPERIOD,
	MGMTWIRELESSADV_WMMENABLED,
	MGMTWIRELESSADV_DFSDISABLED,
	MGMTWIRELESSANTENNA_TRANSMITTER,
	MGMTWIRELESSANTENNA_RECEIVER,
	MGMTWIRELESSRECEIVEDLEVELTHRESHOLD_DBM,
	MGMTWIRELESSENABLESECONDARYSSID,
	MGMTWIRELESSSECONDARYSSID,
	MGMTWIRELESSGUARDINTERVAL,
	MGMTIPROUTINGRIP_ACTIVATION,
	MGMTIPROUTINGRIP_LANUSEDINTERFACE,
	MGMTIPROUTINGRIP_WLANUSEDINTERFACE,
	MGMTIPROUTINGRIP_AUTHENTICATION,
	MGMTDHCPFUNCTION,
	MGMTDHCPIPADDRESSSTART,
	MGMTDHCPIPADDRESSSTOP,
	MGMTDHCPLEASETIME,
	MGMTDHCPRELAYTARGETIP,
	MGMTNAT_ENABLED,
	MGMTNTP_MODE,
	MGMTNTP_SERVER,
	MGMTNTP_TIMEZONE,
	MGMTNTP_FALLBACKSERVER,
	MGMTNTP_SNTPUPDATEFREQUENCY,
	MGMTLOGSYSTEM_ENABLED,
	MGMTLOGSYSTEM_IPADDRESS,
	MGMTLOGSYSTEM_PORT,
	MGMTLOGRSSIMODE_ENABLED,
	MGMTMULTICAST_IGMPPROXY,
	
	//Sous le noeud status
	STANETWORKLAN_MACADDRESS,
	STANETWORKLAN_IPADDRESS,
	STANETWORKWLAN_MACADDRESS,
	STANETWORKWLAN_IPADDRESS,
	STAWIRELESSAP_NUMBERASSOCIATION,
	STAWIRELESSAP_CHANNELINUSE,
	STAWIRELESSSTA_STATUS,
	STAWIRELESSSTA_RSSI_DBM,
	STAWIRELESSSTA_BSSID,
	STAWIRELESSSTA_SSID,
	STAWIRELESSSTA_CHANNELINUSE,
	STAGENERALTEMPERATURE,

	//Sous le noeud command
	CMDGENERALRESTART,
	CMDCLEARALARMS,
	CMDLASTDATEOFCLEANINGALARMS,
	CMDCLEARLOG,
	CMDLASTDATEOFCLEANINGLOG,
	CMDCLEARALL,
	CMDGENERATELOGFILE,
	
	
	NB_MAX_SCALAIRES_WRM100
};


/** ** for Tables         */
enum LISTE_VARIABLES_TABLE_FUNC
{
	FUNCSOFTWAREREVISIONINDEX = 1,
	FUNCSOFTWAREREVISIONDESCRIPTION,
	FUNCSOFTWAREREVISIONNUMBER,
};

enum LISTE_VARIABLES_TABLE_MGMT
{
	MGMTWIRELESSMULTI_INDEX = 1,
	MGMTWIRELESSMULTI_CHANNEL,
	MGMTWIRELESSMULTI_FREQUENCY,

	MGMTIPROUTINGSTATIC_INDEX,
	MGMTIPROUTINGSTATIC_DESTINATIONIP,
	MGMTIPROUTINGSTATIC_DESTINATIONMASK,
	MGMTIPROUTINGSTATIC_GATEWAY,
	MGMTIPROUTINGSTATIC_INTERFACE,

	MGMTIPROUTINGPOLICY_INDEX,
	MGMTIPROUTINGPOLICY_IPSOURCECRITERIA,
	MGMTIPROUTINGPOLICY_IPSOURCEVALUE,
	MGMTIPROUTINGPOLICY_IPSOURCENOT,
	MGMTIPROUTINGPOLICY_IPDESTINATIONCRITERIA,
	MGMTIPROUTINGPOLICY_IPDESTINATIONVALUE,
	MGMTIPROUTINGPOLICY_IPDESTINATIONNOT,
	MGMTIPROUTINGPOLICY_PACKETLENGTHCRITERIA,
	MGMTIPROUTINGPOLICY_PACKETLENGTHVALUE,
	MGMTIPROUTINGPOLICY_PACKETLENGTHNOT,
	MGMTIPROUTINGPOLICY_IPPROTOCOLCRITERIA,
	MGMTIPROUTINGPOLICY_IPPROTOCOLVALUE,
	MGMTIPROUTINGPOLICY_IPPROTOCOLNOT,
	MGMTIPROUTINGPOLICY_PORTSOURCECRITERIA,
	MGMTIPROUTINGPOLICY_PORTSOURCEVALUE,
	MGMTIPROUTINGPOLICY_PORTSOURCENOT,
	MGMTIPROUTINGPOLICY_PORTDESTINATIONCRITERIA,
	MGMTIPROUTINGPOLICY_PORTDESTINATIONVALUE,
	MGMTIPROUTINGPOLICY_PORTDESTINATIONNOT,
	MGMTIPROUTINGPOLICY_CLASSSELECTORCRITERIA,
	MGMTIPROUTINGPOLICY_CLASSSELECTORVALUE,
	MGMTIPROUTINGPOLICY_CLASSSELECTORNOT,
	MGMTIPROUTINGPOLICY_GATEWAYACTION,
	MGMTIPROUTINGPOLICY_GATEWAYNEW,
	MGMTIPROUTINGPOLICY_CLASSSELECTORACTION,
	MGMTIPROUTINGPOLICY_CLASSSELECTORNEW,
	
	MGMTNATPORTFORWARDING_INDEX,
	MGMTNATPORTFORWARDING_PRIVATEIPADDRESS,
	MGMTNATPORTFORWARDING_PRIVATEPORT,
	MGMTNATPORTFORWARDING_PROTOCOL,
	MGMTNATPORTFORWARDING_PUBLICPORT,
	MGMTNATPORTFORWARDING_COMMENT,
	MGMTNATPORTFORWARDING_ENABLED,

	MGMTNATADDRESSESMAPPING_INDEX,
	MGMTNATADDRESSESMAPPING_PRIVATEIPADDRESS,
	MGMTNATADDRESSESMAPPING_PUBLICIPADDRESS,
	MGMTNATADDRESSESMAPPING_COMMENT,
	MGMTNATADDRESSESMAPPING_ENABLED,
	
	MGMTEVTINDEX,
	MGMTEVTCODE,
	MGMTEVTSEVERITYLEVEL,
	MGMTEVTTEXT,
	MGMTEVTUSED,
	MGMTEVTLOG,
	MGMTEVTSYNTHESIS1,
	MGMTEVTAVAILABLE,

	MGMTMULTICAST_SOURCES_INDEX,
	MGMTMULTICAST_SOURCES_ADDRIP,
	MGMTMULTICAST_SOURCES_MASK,
	
};

enum LISTE_VARIABLES_TABLE_STA
{
	STAALARMSLISTINDEX,
	STAALARMSLISTDESCRIPTION,
	STAALARMSLISTSTATUS,
	STAALARMSLISTLATCHEDSTATUS,

	STAWIRELESSAP_CLIENT_INDEX,
	STAWIRELESSAP_CLIENT_MACADDRESS,
	STAWIRELESSAP_CLIENT_RSSI_DBM,
	STAWIRELESSAP_CLIENT_STATUS,

	STADHCPCLIENTS_INDEX,
	STADHCPCLIENTS_MACADDRESS,
	STADHCPCLIENTS_IPADDRESS,
	STADHCPCLIENTS_REMAININGLEASE,
	
};


/*_____III - DEFINITIONS DE TYPES_________________________________________*/

/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/** Déclarations de fonctions */
/** ** for MIB Tree       */
//=====================================================================================
// Fonction		: ps8CaptureString_wrm100
// Entrees		: <loc_s32_vpmagic> : 
//				  <loc_pt_write_method< : 
//				  <loc_pt_var_len< : 
// Sortie		: <loc_ps8_cp< : pointeur sur chaine retournée
// Auteur		: CM - 09/09/2009 -
// Description	: Gestion des variables scalaires de la MIB WRM100 de type STRING
//=====================================================================================
s8sod* ps8CaptureString_wrm100(s32sod loc_s32_vpmagic, WriteMethod ** loc_pt_write_method, size_t * loc_pt_var_len);

//=====================================================================================
// Fonction		: s32CaptureInt_wrm100
// Entrees		: <loc_s32_vpmagic> : 
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 09/09/2009 -
// Description	: Gestion des variables scalaires de la MIB WRM100 de type STRING
//=====================================================================================
s32sod s32CaptureInt_wrm100(s32sod loc_s32_vpmagic, WriteMethod ** loc_pt_write_method);

/** ** for Tables         */
//=====================================================================================
// Fonction		: captureString_funcSoftwareRevisionTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: type string de la table
//=====================================================================================
char * captureString_funcSoftwareRevisionTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_funcSoftwareRevisionTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: type integer de la table
//=====================================================================================
long captureInt_funcSoftwareRevisionTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtWirelessMultiTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char * captureString_mgmtWirelessMultiTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtWirelessMultiTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtWirelessMultiTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtIProutingStaticTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_mgmtIProutingStaticTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtIProutingStaticTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtIProutingStaticTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtIProutingPolicyTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 22/04/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_mgmtIProutingPolicyTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtIProutingPolicyTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 22/04/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtIProutingPolicyTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtNatPortForwardingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_mgmtNatPortForwardingTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtNatPortForwardingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtNatPortForwardingTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtNatAddressesMappingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_mgmtNatAddressesMappingTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtNatAddressesMappingTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtNatAddressesMappingTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtEvtTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_mgmtEvtTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtEvtTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtEvtTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_mgmtMulticast_Sources_Table
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_mgmtMulticast_Sources_Table(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_mgmtMulticast_Sources_Table
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_mgmtMulticast_Sources_Table(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_staAlarmslistTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char * captureString_staAlarmslistTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_staAlarmslistTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_staAlarmslistTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_staWirelessApClientTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_staWirelessApClientTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_staWirelessApClientTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_staWirelessApClientTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureString_staDhcpClientsTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <loc_ps8_cp> : pointeur sur chaine à retournée (sinon NULL)
// Auteur		: CM - 18/03/2010 -
// Description	: gestion String de la table
//=====================================================================================
char *captureString_staDhcpClientsTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: captureInt_staDhcpClientsTable
// Entrees		: <loc_s32_vpmagic> :
//				  <loc_s32_iindex> : index
//				  <loc_pt_write_method< : 
// Sortie		: <long_return> : variable globale
// Auteur		: CM - 18/03/2010 -
// Description	: gestion Integer de la table
//=====================================================================================
long captureInt_staDhcpClientsTable(s32sod, s32sod, WriteMethod **);

//=====================================================================================
// Fonction		: initdata_mib_wrm100
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation de ce module
//=====================================================================================
void initdata_mib_wrm100(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/




