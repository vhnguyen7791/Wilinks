/*========================================================================*/
/* NOM DU FICHIER  : mib_wrm100.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009                                           */
/* Libelle         : NET-SNMP: MIB WRM100								  */
/* Projet          : WRM100                                               */
/* Indice          : BE059				                                  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
// - CREATION
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
//BE051 13/12/2010 CM
// - Probleme horodatage de l'évènement JDB lors d'un RAZ général
//BE053 16/12/2010 CM
// - Modification de la MIB / agent SNMP (suite integration Driver-N)
//BE058 21/01/2011 CM
// - Ajout configuration "desactivation DFS" (WRM100-N)
//BE059 16/02/2011 CM/JP
// - Correction bug sur variable SNMP staWirelessAP-ChannelInUse et staWirelessSta-ChannelInUse
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_______II - DEFINE ______________________________________________________*/

/*_______III - INCLUDES - DIRECTIVES ______________________________________*/
#include "headers.h"
#include "mib_wrm100.h"
#include "mib_wrm100_data.h"
#include "util_funcs.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/** OID Variables         */
/** ** for MIB Tree       */
oid wrm100_variables7_oid[] = {_NOEUD_OID_MIB_PRODUIT};

/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, Longueur(=nb oidsuffix), oidsuffix */
struct variable7 wrm100_variables7[] = {
	//Sous le noeud description
   {DESCSTRUEQUIPMENTTYPE, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,1,1,1}},
   {DESCSTRUID, ASN_OCTET_STR, RWRITE, var_wrm100, 4, {1,1,1,2}},
   {DESCSTRULOCATION, ASN_OCTET_STR, RWRITE, var_wrm100, 4, {1,1,1,3}},
   {DESCSTRULANGUAGE, ASN_INTEGER, RWRITE, var_wrm100, 4, {1,1,1,4}},
	//Sous le noeud managment
   {MGMTMODERADIOMODEM, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,1,1}},
   {MGMTNETMODE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,2,1}},
   {MGMTNETHOSTNAME, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,2,2}},
   {MGMTNETBRIDGEIPMODE, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,3,1}},
   {MGMTNETBRIDGEIPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,3,2}},
   {MGMTNETBRIDGEMASK, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,3,3}},
   {MGMTNETBRIDGEGATEWAY, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,3,4}},
   {MGMTNETBRIDGEDHCPFALLBACKIP, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,3,5}},
   {MGMTNETBRIDGESTP, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,3,6}},
   {MGMTNETLANIPMODE, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,4,1}},
   {MGMTNETLANIPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,4,2}},
   {MGMTNETLANMASK, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,4,3}},
   {MGMTNETWLANIPMODE, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,5,1}},
   {MGMTNETWLANIPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,5,2}},
   {MGMTNETWLANMASK, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,5,3}},
   {MGMTNETWLANGATEWAY, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,5,4}},
   {MGMTNETWLANDHCPFALLBACKIP, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,5,5}},
   {MGMTNETVLAN_SUPPORT, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,6,1}},
   {MGMTNETVLAN_NAME, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,6,2}},
   {MGMTNETVLAN_ID, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,6,3}},
   {MGMTNETVLAN_RESERVENOTAGGEDLAN, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,2,6,4}},
   {MGMTNETVLAN_NOTAGGEDLANIPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,6,5}},
   {MGMTNETVLAN_NOTAGGEDLANMASK, ASN_OCTET_STR, RONLY, var_wrm100, 5, {1,2,2,6,6}},
   {MGMTWIRELESSSSID, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,3,1}},
   {MGMTWIRELESSSSIDMASK, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,2}},
   {MGMTWIRELESS802DOT11MODE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,3}},
   {MGMTWIRELESSCHANNELSPECTRUMWIDTH, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,3,4}},
   {MGMTWIRELESSCHANNEL, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,5}},
   {MGMTWIRELESSFREQUENCY_MHZ, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,6}},
   {MGMTWIRELESSCHANNELMODE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,7}},
   {MGMTWIRELESSISOCHANNEL, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,8}},
   {MGMTWIRELESSISOFREQUENCY_MHZ, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,9}},
   {MGMTWIRELESSTRANSMITTERPOWER_DBM, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,11}},
   {MGMTWIRELESSDATARATE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,12}},
   {MGMTWIRELESSSECURITYMODE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,13}},
   {MGMTWIRELESSWPAAUTHENTICATION, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,14}},
   {MGMTWIRELESSADV_ACKTIMEOUT, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,1}},
   {MGMTWIRELESSADV_PREAMBLETYPE, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,2}},
   {MGMTWIRELESSADV_FRAGMENT_THRSLD, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,3}},
   {MGMTWIRELESSADV_RTS_CTS_THRSLD, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,4}},
   {MGMTWIRELESSADV_BEACONPERIOD, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,5}},
   {MGMTWIRELESSADV_WMMENABLED, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,6}},
   {MGMTWIRELESSADV_DFSDISABLED, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,15,7}},
   {MGMTWIRELESSANTENNA_TRANSMITTER, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,16,1}},
   {MGMTWIRELESSANTENNA_RECEIVER, ASN_INTEGER, RONLY, var_wrm100, 5, {1,2,3,16,2}},
   {MGMTWIRELESSRECEIVEDLEVELTHRESHOLD_DBM, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,17}},
   {MGMTWIRELESSENABLESECONDARYSSID, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,18}},
   {MGMTWIRELESSSECONDARYSSID, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,3,19}},
   {MGMTWIRELESSGUARDINTERVAL, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,3,20}},
   {MGMTIPROUTINGRIP_ACTIVATION, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,4,3}},
   {MGMTIPROUTINGRIP_LANUSEDINTERFACE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,4,4}},
   {MGMTIPROUTINGRIP_WLANUSEDINTERFACE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,4,5}},
   {MGMTIPROUTINGRIP_AUTHENTICATION, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,4,6}},
   {MGMTDHCPFUNCTION, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,5,1}},
   {MGMTDHCPIPADDRESSSTART, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,5,2}},
   {MGMTDHCPIPADDRESSSTOP, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,5,3}},
   {MGMTDHCPLEASETIME, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,5,4}},
   {MGMTDHCPRELAYTARGETIP, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,5,5}},
   {MGMTNAT_ENABLED, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,6,1}},
   {MGMTNTP_MODE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,8,1}},
   {MGMTNTP_SERVER, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,8,2}},
   {MGMTNTP_TIMEZONE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,8,3}},
   {MGMTNTP_FALLBACKSERVER, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,8,4}},
   {MGMTNTP_SNTPUPDATEFREQUENCY, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,8,5}},
   {MGMTLOGSYSTEM_ENABLED, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,9,1}},
   {MGMTLOGSYSTEM_IPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,2,9,2}},
   {MGMTLOGSYSTEM_PORT, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,9,3}},
   {MGMTLOGRSSIMODE_ENABLED, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,9,4}},
   {MGMTMULTICAST_IGMPPROXY, ASN_INTEGER, RONLY, var_wrm100, 4, {1,2,10,1}},
   
	//Sous le noeud status
   {STANETWORKLAN_MACADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,2,1}},
   {STANETWORKLAN_IPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,2,2}},
   {STANETWORKWLAN_MACADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,2,3}},
   {STANETWORKWLAN_IPADDRESS, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,2,4}},
   {STAWIRELESSAP_NUMBERASSOCIATION, ASN_INTEGER, RONLY, var_wrm100, 4, {1,3,3,1}},
   {STAWIRELESSAP_CHANNELINUSE, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,3,3}},
   {STAWIRELESSSTA_STATUS, ASN_INTEGER, RONLY, var_wrm100, 4, {1,3,4,1}}, 
   {STAWIRELESSSTA_RSSI_DBM, ASN_INTEGER, RONLY, var_wrm100, 4, {1,3,4,2}}, 
   {STAWIRELESSSTA_BSSID, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,4,3}},
   {STAWIRELESSSTA_SSID, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,4,4}},
   {STAWIRELESSSTA_CHANNELINUSE, ASN_OCTET_STR, RONLY, var_wrm100, 4, {1,3,4,5}},
   {STAGENERALTEMPERATURE, ASN_INTEGER, RONLY, var_wrm100, 4, {1,3,6,1}}, 
   
	//Sous le noeud command
   {CMDGENERALRESTART, ASN_INTEGER, RWRITE, var_wrm100, 3, {1,4,1}},
   {CMDCLEARALARMS, ASN_INTEGER, RWRITE, var_wrm100, 3, {1,4,2}},
   {CMDLASTDATEOFCLEANINGALARMS, ASN_OCTET_STR, RONLY, var_wrm100, 3, {1,4,3}},
   {CMDCLEARLOG, ASN_INTEGER, RWRITE, var_wrm100, 3, {1,4,4}},
   {CMDLASTDATEOFCLEANINGLOG, ASN_OCTET_STR, RONLY, var_wrm100, 3, {1,4,5}},
   {CMDCLEARALL, ASN_INTEGER, RWRITE, var_wrm100, 3, {1,4,6}},
   {CMDGENERATELOGFILE, ASN_INTEGER, RWRITE, var_wrm100, 3, {1,4,7}},
};

/** ** for Tables         */
oid funcSoftwareRevision_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,1,2,1,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 funcSoftwareRevision_variables[] = {
	{FUNCSOFTWAREREVISIONINDEX, ASN_INTEGER, RONLY, var_funcSoftwareRevisionTable, 2, {1,1}},
	{FUNCSOFTWAREREVISIONDESCRIPTION, ASN_OCTET_STR, RONLY, var_funcSoftwareRevisionTable, 2, {1,2}},
	{FUNCSOFTWAREREVISIONNUMBER, ASN_OCTET_STR, RONLY, var_funcSoftwareRevisionTable, 2, {1,3}},
};

oid mgmtWirelessMulti_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,3,10};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtWirelessMulti_variables[] = {
	{MGMTWIRELESSMULTI_INDEX, ASN_INTEGER, RONLY, var_mgmtWirelessMultiTable, 2, {1,1}},
	{MGMTWIRELESSMULTI_CHANNEL, ASN_INTEGER, RONLY, var_mgmtWirelessMultiTable, 2, {1,2}},
	{MGMTWIRELESSMULTI_FREQUENCY, ASN_INTEGER, RONLY, var_mgmtWirelessMultiTable, 2, {1,3}},
};

oid mgmtIProutingStaticTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,4,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtIProutingStaticTable_variables[] = {
	{MGMTIPROUTINGSTATIC_INDEX, ASN_INTEGER, RONLY, var_mgmtIProutingStaticTable, 2, {1,1}},
	{MGMTIPROUTINGSTATIC_DESTINATIONIP, ASN_OCTET_STR, RONLY, var_mgmtIProutingStaticTable, 2, {1,2}},
	{MGMTIPROUTINGSTATIC_DESTINATIONMASK, ASN_OCTET_STR, RONLY, var_mgmtIProutingStaticTable, 2, {1,3}},
	{MGMTIPROUTINGSTATIC_GATEWAY, ASN_OCTET_STR, RONLY, var_mgmtIProutingStaticTable, 2, {1,4}},
	{MGMTIPROUTINGSTATIC_INTERFACE, ASN_INTEGER, RONLY, var_mgmtIProutingStaticTable, 2, {1,5}},
};

oid mgmtIProutingPolicyTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,4,2};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtIProutingPolicyTable_variables[] = {
	{MGMTIPROUTINGPOLICY_INDEX, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,1}},
	{MGMTIPROUTINGPOLICY_IPSOURCECRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,2}},
	{MGMTIPROUTINGPOLICY_IPSOURCEVALUE, ASN_OCTET_STR, RONLY, var_mgmtIProutingPolicyTable, 2, {1,3}},
	{MGMTIPROUTINGPOLICY_IPSOURCENOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,4}},
	{MGMTIPROUTINGPOLICY_IPDESTINATIONCRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,5}},
	{MGMTIPROUTINGPOLICY_IPDESTINATIONVALUE, ASN_OCTET_STR, RONLY, var_mgmtIProutingPolicyTable, 2, {1,6}},
	{MGMTIPROUTINGPOLICY_IPDESTINATIONNOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,7}},
	{MGMTIPROUTINGPOLICY_PACKETLENGTHCRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,8}},
	{MGMTIPROUTINGPOLICY_PACKETLENGTHVALUE, ASN_OCTET_STR, RONLY, var_mgmtIProutingPolicyTable, 2, {1,9}},
	{MGMTIPROUTINGPOLICY_PACKETLENGTHNOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,10}},
	{MGMTIPROUTINGPOLICY_IPPROTOCOLCRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,11}},
	{MGMTIPROUTINGPOLICY_IPPROTOCOLVALUE, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,12}},
	{MGMTIPROUTINGPOLICY_IPPROTOCOLNOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,13}},
	{MGMTIPROUTINGPOLICY_PORTSOURCECRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,14}},
	{MGMTIPROUTINGPOLICY_PORTSOURCEVALUE, ASN_OCTET_STR, RONLY, var_mgmtIProutingPolicyTable, 2, {1,15}},
	{MGMTIPROUTINGPOLICY_PORTSOURCENOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,16}},
	{MGMTIPROUTINGPOLICY_PORTDESTINATIONCRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,17}},
	{MGMTIPROUTINGPOLICY_PORTDESTINATIONVALUE, ASN_OCTET_STR, RONLY, var_mgmtIProutingPolicyTable, 2, {1,18}},
	{MGMTIPROUTINGPOLICY_PORTDESTINATIONNOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,19}},
	{MGMTIPROUTINGPOLICY_CLASSSELECTORCRITERIA, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,20}},
	{MGMTIPROUTINGPOLICY_CLASSSELECTORVALUE, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,21}},
	{MGMTIPROUTINGPOLICY_CLASSSELECTORNOT, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,22}},
	{MGMTIPROUTINGPOLICY_GATEWAYACTION, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,23}},
	{MGMTIPROUTINGPOLICY_GATEWAYNEW, ASN_OCTET_STR, RONLY, var_mgmtIProutingPolicyTable, 2, {1,24}},
	{MGMTIPROUTINGPOLICY_CLASSSELECTORACTION, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,25}},
	{MGMTIPROUTINGPOLICY_CLASSSELECTORNEW, ASN_INTEGER, RONLY, var_mgmtIProutingPolicyTable, 2, {1,26}},
};

oid mgmtNatPortForwardingTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,6,2};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtNatPortForwardingTable_variables[] = {
	{MGMTNATPORTFORWARDING_INDEX, ASN_INTEGER, RONLY, var_mgmtNatPortForwardingTable, 2, {1,1}},
	{MGMTNATPORTFORWARDING_PRIVATEIPADDRESS, ASN_OCTET_STR, RONLY, var_mgmtNatPortForwardingTable, 2, {1,2}},
	{MGMTNATPORTFORWARDING_PRIVATEPORT, ASN_INTEGER, RONLY, var_mgmtNatPortForwardingTable, 2, {1,3}},
	{MGMTNATPORTFORWARDING_PROTOCOL, ASN_INTEGER, RONLY, var_mgmtNatPortForwardingTable, 2, {1,4}},
	{MGMTNATPORTFORWARDING_PUBLICPORT, ASN_INTEGER, RONLY, var_mgmtNatPortForwardingTable, 2, {1,5}},
	{MGMTNATPORTFORWARDING_COMMENT, ASN_OCTET_STR, RONLY, var_mgmtNatPortForwardingTable, 2, {1,6}},
	{MGMTNATPORTFORWARDING_ENABLED, ASN_INTEGER, RONLY, var_mgmtNatPortForwardingTable, 2, {1,7}},
};

oid mgmtNatAddressesMappingTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,6,3};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtNatAddressesMappingTable_variables[] = {
	{MGMTNATADDRESSESMAPPING_INDEX, ASN_INTEGER, RONLY, var_mgmtNatAddressesMappingTable, 2, {1,1}},
	{MGMTNATADDRESSESMAPPING_PRIVATEIPADDRESS, ASN_OCTET_STR, RONLY, var_mgmtNatAddressesMappingTable, 2, {1,2}},
	{MGMTNATADDRESSESMAPPING_PUBLICIPADDRESS, ASN_OCTET_STR, RONLY, var_mgmtNatAddressesMappingTable, 2, {1,3}},
	{MGMTNATADDRESSESMAPPING_COMMENT, ASN_OCTET_STR, RONLY, var_mgmtNatAddressesMappingTable, 2, {1,4}},
	{MGMTNATADDRESSESMAPPING_ENABLED, ASN_INTEGER, RONLY, var_mgmtNatAddressesMappingTable, 2, {1,5}},
};

oid mgmtEvtTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,7,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtEvtTable_variables[] = {
	{MGMTEVTINDEX, ASN_INTEGER, RONLY, var_mgmtEvtTable, 2, {1,1}},
	{MGMTEVTCODE, ASN_INTEGER, RONLY, var_mgmtEvtTable, 2, {1,2}},
	{MGMTEVTSEVERITYLEVEL, ASN_OCTET_STR, RONLY, var_mgmtEvtTable, 2, {1,3}},
	{MGMTEVTTEXT, ASN_OCTET_STR, RONLY, var_mgmtEvtTable, 2, {1,4}},
	{MGMTEVTUSED, ASN_INTEGER, RWRITE, var_mgmtEvtTable, 2, {1,5}},
	{MGMTEVTLOG, ASN_INTEGER, RWRITE, var_mgmtEvtTable, 2, {1,6}},
	{MGMTEVTSYNTHESIS1, ASN_INTEGER, RWRITE, var_mgmtEvtTable, 2, {1,7}},
	{MGMTEVTAVAILABLE, ASN_INTEGER, RONLY, var_mgmtEvtTable, 2, {1,8}},
};

oid mgmtMulticast_Sources_Table_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,2,10,2};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 mgmtMulticast_Sources_Table_variables[] = {
	{MGMTMULTICAST_SOURCES_INDEX, ASN_INTEGER, RONLY, var_mgmtMulticast_Sources_Table, 2, {1,1}},
	{MGMTMULTICAST_SOURCES_ADDRIP, ASN_OCTET_STR, RONLY, var_mgmtMulticast_Sources_Table, 2, {1,2}},
	{MGMTMULTICAST_SOURCES_MASK, ASN_OCTET_STR, RONLY, var_mgmtMulticast_Sources_Table, 2, {1,3}},
};

oid staAlarmslistTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,3,1,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 staAlarmslistTable_variables[] = {
	{STAALARMSLISTINDEX, ASN_INTEGER, RONLY, var_staAlarmslistTable, 2, {1,1}},
	{STAALARMSLISTDESCRIPTION, ASN_OCTET_STR, RONLY, var_staAlarmslistTable, 2, {1,2}},
	{STAALARMSLISTSTATUS, ASN_INTEGER, RONLY, var_staAlarmslistTable, 2, {1,3}},
	{STAALARMSLISTLATCHEDSTATUS, ASN_INTEGER, RONLY, var_staAlarmslistTable, 2, {1,4}},
};

oid staWirelessApClientTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,3,3,2};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 staWirelessApClientTable_variables[] = {
	{STAWIRELESSAP_CLIENT_INDEX, ASN_INTEGER, RONLY, var_staWirelessApClientTable, 2, {1,1}},
	{STAWIRELESSAP_CLIENT_MACADDRESS, ASN_OCTET_STR, RONLY, var_staWirelessApClientTable, 2, {1,2}},
	{STAWIRELESSAP_CLIENT_RSSI_DBM, ASN_INTEGER, RONLY, var_staWirelessApClientTable, 2, {1,3}},
	{STAWIRELESSAP_CLIENT_STATUS, ASN_INTEGER, RONLY, var_staWirelessApClientTable, 2, {1,4}},
};

oid staDhcpClientsTable_variables_oid[] = {_NOEUD_OID_MIB_PRODUIT,1,3,5,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 staDhcpClientsTable_variables[] = {
	{STADHCPCLIENTS_INDEX, ASN_INTEGER, RONLY, var_staDhcpClientsTable, 2, {1,1}},
	{STADHCPCLIENTS_MACADDRESS, ASN_OCTET_STR, RONLY, var_staDhcpClientsTable, 2, {1,2}},
	{STADHCPCLIENTS_IPADDRESS, ASN_OCTET_STR, RONLY, var_staDhcpClientsTable, 2, {1,3}},
	{STADHCPCLIENTS_REMAININGLEASE, ASN_INTEGER, RONLY, var_staDhcpClientsTable, 2, {1,4}},
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: var_wrm100
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 09/09/2009 -
// Description	: gestion des variables scalaires de la MIB WRM100
//					Callback functions
//					called whenever an incoming request refers to an object within this sub-tree
//					for MIB Tree
//=====================================================================================
u_char* var_wrm100(struct variable *loc_ps_vp,
					oid * loc_pt_name,
					size_t * loc_pt_length,
					int loc_s32_exact,
					size_t * loc_pt_var_len,
					WriteMethod ** loc_pt_write_method)
{
	u_char *loc_pt_return;
	s8sod *loc_ps8_cp;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0; //INIT

//   DEBUGMSGTL(("sodielec", "var_wrm100 called\n"));
	if (MATCH_FAILED == header_generic(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method))
	{
		;
	}
	else
	{
	   if(ASN_OCTET_STR == loc_ps_vp->type) {
		loc_ps8_cp = (char *)(ps8CaptureString_wrm100(loc_ps_vp->magic, loc_pt_write_method, loc_pt_var_len));
		*loc_pt_var_len = strlen(loc_ps8_cp);
		loc_pt_return = (u_char *) loc_ps8_cp;
	   }
	   if(ASN_INTEGER == loc_ps_vp->type) {
		long_return = (s32sod)(s32CaptureInt_wrm100(loc_ps_vp->magic, loc_pt_write_method));
		loc_pt_return = (u_char *) &long_return;
	   }
	}
	
	return loc_pt_return;
}/*var_wrm100*/

//=====================================================================================
// Fonction		: write_descStruID
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_descStruID(int action,
					u_char * var_val,
					u_char var_val_type,
					size_t var_val_len,
					u_char * statP,
					oid * name,
					size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;

	if (u8CheckClientSnmpAllowed())
	{
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 descStruID called\n"));
				if (var_val_type != ASN_OCTET_STR) {
					snmp_log(LOG_ERR, "Value is not a string\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > LG_NOM_IDENTIFIANT) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION descStruID called\n"));

				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_cfg_tempo_snmpd))
				{
					memset(s_cfg_tempo_snmpd.s_admin.ps8_identifiant, '\0', LG_NOM_IDENTIFIANT);
					strncpy(s_cfg_tempo_snmpd.s_admin.ps8_identifiant ,	(s8sod*)var_val, var_val_len);
					if(TRUE==u8TestConfigAdmin(&s_cfg_tempo_snmpd))
					{
						u8EditConfigAdmin(&s_cfg_tempo_snmpd);
						CopyConfigAdmin(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
					}
					else
					{
						loc_s32_return = SNMP_ERR_WRONGVALUE;
					}
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

				break;

			default:
				break;
		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_descStruID*/

//=====================================================================================
// Fonction		: write_descStruLocation
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_descStruLocation(int action,
						  u_char * var_val,
						  u_char var_val_type,
						  size_t var_val_len,
						  u_char * statP,
						  oid * name,
						  size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 descStruLocation called\n"));
				if (var_val_type != ASN_OCTET_STR) {
					snmp_log(LOG_ERR, "Value is not a string\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > LG_NOM_LOCALISATION) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION descStruLocation called\n"));

				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_cfg_tempo_snmpd))
				{
					memset(s_cfg_tempo_snmpd.s_admin.ps8_localisation, '\0', LG_NOM_LOCALISATION);
					strncpy(s_cfg_tempo_snmpd.s_admin.ps8_localisation ,	(s8sod*)var_val, var_val_len);
					if(TRUE==u8TestConfigAdmin(&s_cfg_tempo_snmpd))
					{
						u8EditConfigAdmin(&s_cfg_tempo_snmpd);
						CopyConfigAdmin(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
					}
					else
					{
						loc_s32_return = SNMP_ERR_WRONGVALUE;
					}
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

				break;

			default:
				break;
		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_descStruLocation*/

//=====================================================================================
// Fonction		: write_descStruLanguage
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_descStruLanguage(int action,
						  u_char * var_val,
						  u_char var_val_type,
						  size_t var_val_len,
						  u_char * statP,
						  oid * name,
						  size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 write_descStruLanguage called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((0 <= (*(int*)(var_val)-1))&&
				   ((*(int*)(var_val)-1) < NB_MAX_LANGUES )
				  )
				{
					;	//OK
				}
				else
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION write_descStruLanguage called\n"));

				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
				if(TRUE == u8FillConfigAdmin(&s_cfg_tempo_snmpd))
				{
					s_cfg_tempo_snmpd.s_admin.u8_langue = (u8sod)(*(int*)(var_val)-1);
					if(TRUE==u8TestConfigAdmin(&s_cfg_tempo_snmpd))
					{
						u8EditConfigAdmin(&s_cfg_tempo_snmpd);
						CopyConfigAdmin(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
					}
					else
					{
						loc_s32_return = SNMP_ERR_WRONGVALUE;
					}
				}
				s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem

				break;

			default:
				break;

		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_descStruLanguage*/

//=====================================================================================
// Fonction		: write_cmdGeneralRestart
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_cmdGeneralRestart(int action,
						   u_char * var_val,
						   u_char var_val_type,
						   size_t var_val_len,
						   u_char * statP,
						   oid * name,
						   size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 cmdGeneralRestart called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((*(int*)(var_val) != 1)&&
				   (*(int*)(var_val) != 2)
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION cmdGeneralRestart called\n"));
				
				if(2 == *(int*)(var_val))
				{
					//Ordre RESET EQUIPEMENT
					OrdreResetUc();
				}
				
				break;
				
			default:
				break;

		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}
	
	return loc_s32_return;
}/*write_cmdGeneralRestart*/

//=====================================================================================
// Fonction		: write_cmdClearAlarms
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_cmdClearAlarms(int action,
						u_char * var_val,
						u_char var_val_type,
						size_t var_val_len,
						u_char * statP,
						oid * name,
						size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod loc_s32_sem;

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 cmdClearAlarms called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((*(int*)(var_val) != 1)&&
				   (*(int*)(var_val) != 2)
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION cmdClearAlarms called\n"));
				
				if(2 == *(int*)(var_val))
				{
					//On signale le RAZ des alarmes mémorisées au processus monitor
					s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillCipMonitor(&s_cip_monitor_from_snmpd))
					{
						s_cip_monitor_from_snmpd.u8_raz_alarmes_memorisees = TRUE;
						u8EditCipMonitor(&s_cip_monitor_from_snmpd);
					}
					s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem
				}
				
				break;
				
			default:
				break;

		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}
	
	return loc_s32_return;
}/*write_cmdClearAlarms*/

//=====================================================================================
// Fonction		: write_cmdClearLog
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_cmdClearLog(int action,
					 u_char * var_val,
					 u_char var_val_type,
					 size_t var_val_len,
					 u_char * statP,
					 oid * name,
					 size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;
	
	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 cmdClearLog called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((*(int*)(var_val) != 1)&&
				   (*(int*)(var_val) != 2)
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION cmdClearLog called\n"));
				
				if(2 == *(int*)(var_val))
				{
					//On signale le RAZ du journal de bord au processus jdb
					s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillCipJdb(&s_cip_jdb_from_snmpd))
					{
						s_cip_jdb_from_snmpd.u8_effacer_jdb = TRUE;
						u8EditCipJdb(&s_cip_jdb_from_snmpd);
					}
					s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
				}
				
				break;
				
			default:
				break;

		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}
	
	return loc_s32_return;
}/*write_cmdClearLog*/

//=====================================================================================
// Fonction		: write_cmdClearAll
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_cmdClearAll(int action,
					 u_char * var_val,
					 u_char var_val_type,
					 size_t var_val_len,
					 u_char * statP,
					 oid * name,
					 size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod loc_s32_sem;

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 cmdClearAll called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((*(int*)(var_val) != 1)&&
				   (*(int*)(var_val) != 2)
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION cmdClearAll called\n"));

				if(2 == *(int*)(var_val))
				{
					//On signale le RAZ des alarmes mémorisées au processus monitor
					s32Lock_Get(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillCipMonitor(&s_cip_monitor_from_snmpd))
					{
						s_cip_monitor_from_snmpd.u8_raz_general = TRUE;
						u8EditCipMonitor(&s_cip_monitor_from_snmpd);
					}
					s32Lock_Release(SEMAPHORE_BDD_CIP_MONITOR, &loc_s32_sem);	//on relache le sem

					//On signale le RAZ du journal de bord au processus jdb
					s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillCipJdb(&s_cip_jdb_from_snmpd))
					{
						s_cip_jdb_from_snmpd.u8_effacer_jdb = TRUE;
						u8EditCipJdb(&s_cip_jdb_from_snmpd);
					}
					s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
					
				}
				break;
				
			default:
				break;

		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}
	
	return loc_s32_return;
}/*write_cmdClearAll*/

//=====================================================================================
// Fonction		: write_cmdGenerateLogFile
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_cmdGenerateLogFile(int action,
						 u_char * var_val,
						 u_char var_val_type,
						 size_t var_val_len,
						 u_char * statP,
						 oid * name,
						 size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 write_cmdGenerateLogFile called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((*(int*)(var_val) != 1)&&
				   (*(int*)(var_val) != 2)
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION cmdResetMeasPC called\n"));
				if(2 == *(int*)(var_val))
				{
					s32Lock_Get(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillCipJdb(&s_cip_jdb_from_snmpd))
					{
						s_cip_jdb_from_snmpd.u8_generer_jdb = TRUE;
						u8EditCipJdb(&s_cip_jdb_from_snmpd);
					}
					s32Lock_Release(SEMAPHORE_BDD_CIP_JDB, &loc_s32_sem);	//on relache le sem
				}
				break;

			default:
				break;

		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_cmdGenerateLogFile*/

//=====================================================================================
// Fonction		: s32Header_funcSoftwareRevisionTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp : funcSoftwareRevisionTable
//=====================================================================================
static s32sod s32Header_funcSoftwareRevisionTable(struct variable *loc_ps_vp,
													oid * loc_pt_name,
													size_t * loc_pt_length,
													s32sod loc_s32_exact,
													size_t * loc_pt_var_len,
													WriteMethod ** loc_pt_write_method)
{ 
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u8sod	loc_u8_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u8_i=0; loc_u8_i<NB_MAX_VERSIONS_LOGICIELLES; loc_u8_i++)
	{
		if(TRUE == T_TB_VAL.pu8_flag_affichage_version[loc_u8_i]) //CONDITION: affichage autorisée
		{
			//Le dernier oid
			loc_pt_newname[19] = (oid)(loc_u8_i+1);
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if ((loc_s32_exact && (0 == loc_s32_result))||
				(!loc_s32_exact && (loc_s32_result < 0))
			   ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u8_i = NB_MAX_VERSIONS_LOGICIELLES + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_funcSoftwareRevisionTable*/

//=====================================================================================
// Fonction		: var_funcSoftwareRevisionTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp : funcSoftwareRevisionTable
//=====================================================================================
u_char *
   var_funcSoftwareRevisionTable(struct variable *loc_ps_vp,
								 oid * loc_pt_name,
								 size_t * loc_pt_length,
								 int loc_s32_exact,
								 size_t * loc_pt_var_len,
								 WriteMethod ** loc_pt_write_method)
{
	u_char *loc_pt_return;
	s8sod  *loc_ps8_cp;
	s32sod loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_funcSoftwareRevisionTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1] - 1;

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (char *)(captureString_funcSoftwareRevisionTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_funcSoftwareRevisionTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}

	return loc_pt_return;
}/*var_funcSoftwareRevisionTable*/

//=====================================================================================
// Fonction		: var_mgmtWirelessMultiTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "simple" snmp : mgmtWirelessMultiTable
//=====================================================================================
u_char *
   var_mgmtWirelessMultiTable(struct variable *loc_ps_vp,
							  oid * loc_pt_name,
							  size_t * loc_pt_length,
							  int loc_s32_exact,
							  size_t * loc_pt_var_len,
							  WriteMethod ** loc_pt_write_method)
{
	u_char *loc_pt_return;
	s8sod  *loc_ps8_cp;
	s32sod loc_s32_iindex;

	loc_pt_return = NULL; //INIT
	*loc_pt_write_method = 0;

	if (header_simple_table(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method, NB_MAX_MULTI_CANAUX))
	{
		loc_pt_return = NULL;
	}
	else
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1] - 1;

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (char *)(captureString_mgmtWirelessMultiTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtWirelessMultiTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}

	return loc_pt_return;
}/*var_mgmtWirelessMultiTable*/

//=====================================================================================
// Fonction		: s32Header_mgmtIProutingStaticTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_mgmtIProutingStaticTable(struct variable *loc_ps_vp,
												oid * loc_pt_name,
												size_t * loc_pt_length,
												s32sod loc_s32_exact,
												size_t * loc_pt_var_len,
												WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u16_i=0; loc_u16_i<NB_MAX_ROUTES_IP_STATIC; loc_u16_i++)
	{
		if(TRUE == s_config_process_snmpd.s_ip_routing.ps_route_ip_static[loc_u16_i].u8_enabled)
		{
			//Le dernier oid
			loc_pt_newname[18] = (oid)loc_u16_i+1;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if((loc_s32_exact && (0 == loc_s32_result))||
			   (!loc_s32_exact && (loc_s32_result < 0))
			  ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));
//				DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
//							loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
//							loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
//							loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
//						    loc_pt_name[15],loc_pt_name[16]));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u16_i = NB_MAX_ROUTES_IP_STATIC + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_mgmtIProutingStaticTable*/

//=====================================================================================
// Fonction		: var_mgmtIProutingStaticTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_mgmtIProutingStaticTable(struct variable *loc_ps_vp,
								oid * loc_pt_name,
								size_t * loc_pt_length,
								int loc_s32_exact,
								size_t * loc_pt_var_len,
								WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_mgmtIProutingStaticTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_mgmtIProutingStaticTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtIProutingStaticTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_mgmtIProutingStaticTable*/

//=====================================================================================
// Fonction		: s32Header_mgmtIProutingPolicyTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_mgmtIProutingPolicyTable(struct variable *loc_ps_vp,
	oid * loc_pt_name,
	size_t * loc_pt_length,
	s32sod loc_s32_exact,
	size_t * loc_pt_var_len,
	WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u16_i=0; loc_u16_i<NB_MAX_POLICY_ROUTING; loc_u16_i++)
	{
		if(TRUE == s_config_process_snmpd.s_ip_routing.ps_route_policy[loc_u16_i].u8_enabled)
		{
			//Le dernier oid
			loc_pt_newname[18] = (oid)loc_u16_i+1;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if((loc_s32_exact && (0 == loc_s32_result))||
			   (!loc_s32_exact && (loc_s32_result < 0))
			  ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));
//				DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
//							loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
//							loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
//							loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
//						    loc_pt_name[15],loc_pt_name[16]));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u16_i = NB_MAX_POLICY_ROUTING + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_mgmtIProutingPolicyTable*/

//=====================================================================================
// Fonction		: var_mgmtIProutingPolicyTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_mgmtIProutingPolicyTable(struct variable *loc_ps_vp,
								oid * loc_pt_name,
								size_t * loc_pt_length,
								int loc_s32_exact,
								size_t * loc_pt_var_len,
								WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_mgmtIProutingPolicyTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_mgmtIProutingPolicyTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtIProutingPolicyTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_mgmtIProutingPolicyTable*/

//=====================================================================================
// Fonction		: s32Header_mgmtNatPortForwardingTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_mgmtNatPortForwardingTable(struct variable *loc_ps_vp,
													oid * loc_pt_name,
													size_t * loc_pt_length,
													s32sod loc_s32_exact,
													size_t * loc_pt_var_len,
													WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_RULES_PORT_FORWARDING;loc_u16_i++)
	{
		if(NAT_PROTOCOLE_NON_SELECTIONNE != s_config_process_snmpd.s_nat.ps_rule_port_forwarding[loc_u16_i].u8_protocole)
		{
			//Le dernier oid
			loc_pt_newname[18] = (oid)loc_u16_i+1;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if((loc_s32_exact && (0 == loc_s32_result))||
			   (!loc_s32_exact && (loc_s32_result < 0))
			  ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));
//				DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
//							loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
//							loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
//							loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
//						    loc_pt_name[15],loc_pt_name[16]));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u16_i = NB_MAX_RULES_PORT_FORWARDING + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_mgmtNatPortForwardingTable*/

//=====================================================================================
// Fonction		: var_mgmtNatPortForwardingTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_mgmtNatPortForwardingTable(struct variable *loc_ps_vp,
								oid * loc_pt_name,
								size_t * loc_pt_length,
								int loc_s32_exact,
								size_t * loc_pt_var_len,
								WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_mgmtNatPortForwardingTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_mgmtNatPortForwardingTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtNatPortForwardingTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_mgmtNatPortForwardingTable*/

//=====================================================================================
// Fonction		: s32Header_mgmtNatAddressesMappingTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_mgmtNatAddressesMappingTable(struct variable *loc_ps_vp,
	oid * loc_pt_name,
	size_t * loc_pt_length,
	s32sod loc_s32_exact,
	size_t * loc_pt_var_len,
	WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	if(MODE_IP_STATIQUE == s_config_process_snmpd.s_gene.u8_wlan_mode_ip)
	{
		for(loc_u16_i=0;loc_u16_i<NB_MAX_NAT_ALIAS_IP;loc_u16_i++)
		{
			if(ADRESSE_IP_NULLE != s_config_process_snmpd.s_nat.ps_rule_mapping_adresse[loc_u16_i].u32_public_alias_ip)
			{
				//Le dernier oid
				loc_pt_newname[18] = (oid)loc_u16_i+1;
				loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
				if((loc_s32_exact && (0 == loc_s32_result))||
				   (!loc_s32_exact && (loc_s32_result < 0))
				  ) //CONDITION: oid identique à celui demandé ou ..."
				{

					loc_s32_iindex = MATCH_SUCCEEDED;

					//on applique le nouvel oid
					memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));
	//				DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
	//							loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
	//							loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
	//							loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
	//						    loc_pt_name[15],loc_pt_name[16]));

					*loc_pt_length = loc_ps_vp->namelen + 1;
					*loc_pt_write_method = 0;
					*loc_pt_var_len = sizeof(long);
					loc_u16_i = NB_MAX_NAT_ALIAS_IP + 1;	//on sort
				}
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_mgmtNatAddressesMappingTable*/

//=====================================================================================
// Fonction		: var_mgmtNatAddressesMappingTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_mgmtNatAddressesMappingTable(struct variable *loc_ps_vp,
								  oid * loc_pt_name,
								  size_t * loc_pt_length,
								  int loc_s32_exact,
								  size_t * loc_pt_var_len,
								  WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_mgmtNatAddressesMappingTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_mgmtNatAddressesMappingTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtNatAddressesMappingTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_mgmtNatAddressesMappingTable*/

//=====================================================================================
// Fonction		: s32Header_mgmtEvtTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_mgmtEvtTable(struct variable *loc_ps_vp,
									 oid * loc_pt_name,
									 size_t * loc_pt_length,
									 s32sod loc_s32_exact,
									 size_t * loc_pt_var_len,
									 WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_indEvt;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u16_indEvt=0; loc_u16_indEvt<NB_MAX_EVENEMENTS; loc_u16_indEvt++)
	{
		if(TRUE == u8TestEvenementValide(loc_u16_indEvt))
		{
			//Le dernier oid
			loc_pt_newname[18] = (oid)S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if((loc_s32_exact && (0 == loc_s32_result))||
			   (!loc_s32_exact && (loc_s32_result < 0))
			  ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));
//				DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
//							loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
//							loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
//							loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
//						    loc_pt_name[15],loc_pt_name[16]));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u16_indEvt = NB_MAX_EVENEMENTS + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_mgmtEvtTable*/

//=====================================================================================
// Fonction		: var_mgmtEvtTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_mgmtEvtTable(struct variable *loc_ps_vp,
					oid * loc_pt_name,
					size_t * loc_pt_length,
					int loc_s32_exact,
					size_t * loc_pt_var_len,
					WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_mgmtEvtTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_mgmtEvtTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtEvtTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_mgmtEvtTable*/

//=====================================================================================
// Fonction		: write_mgmtEvtUsed
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_mgmtEvtUsed(int action,
					 u_char * var_val,
					 u_char var_val_type,
					 size_t var_val_len,
					 u_char * statP,
					 oid * name,
					 size_t name_len)
{
	s32sod	loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_iindex;
	s32sod	loc_s32_sem;
	u16sod	loc_u16_indEvt;

	loc_s32_iindex = name[name_len - 1];

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtEvt-Used called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if((*(int*)(var_val) != 1)&&		//on
				   (*(int*)(var_val) != 2)		//off
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION mgmtEvt-Used called\n"));
				//On recherche index de l'evt (car loc_s32_iindex = numéro de l'évt)
				loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);
				if(US_INDICE_NON_TROUVE != loc_u16_indEvt)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_cfg_tempo_snmpd))
					{
						switch(*(int*)(var_val))
						{
							case 1:  //on
								SetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_VALIDE);
								break;
							case 2: //off
								ResetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_VALIDE);
								break;
							default:
								break;
						}
						if(TRUE==u8TestConfigTabEvt(&s_cfg_tempo_snmpd))
						{
							u8EditConfigTabEvt(&s_cfg_tempo_snmpd);
							CopyConfigTabEvt(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
						}
						else
						{
							loc_s32_return = SNMP_ERR_WRONGVALUE;
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				else
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
			default:
				break;
		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_mgmtEvtUsed*/

//=====================================================================================
// Fonction		: write_mgmtEvtLOG
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_mgmtEvtLOG(int action,
					u_char * var_val,
					u_char var_val_type,
					size_t var_val_len,
					u_char * statP,
					oid * name,
					size_t name_len)
{
	s32sod	loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_iindex;
	s32sod	loc_s32_sem;
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;
	u16sod	loc_u16_indEvt;

	loc_s32_iindex = name[name_len - 1];

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtEvt-LOG called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		  (*(int*)(var_val) != 1)		//on
						  &&(*(int*)(var_val) != 2)		//off
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION mgmtEvt-LOG called\n"));
				//On recherche index de l'evt (car loc_s32_iindex = numéro de l'évt)
				loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);
				if(US_INDICE_NON_TROUVE != loc_u16_indEvt)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_cfg_tempo_snmpd))
					{
						switch(*(int*)(var_val))
						{
							case 1:  //on
								SetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_JDB);
								break;
							case 2: //off
								ResetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_JDB);
								break;
							default:
								break;
						}
						if(TRUE==u8TestConfigTabEvt(&s_cfg_tempo_snmpd))
						{
							u8EditConfigTabEvt(&s_cfg_tempo_snmpd);
							CopyConfigTabEvt(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
						}
						else
						{
							loc_s32_return = SNMP_ERR_WRONGVALUE;
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				else
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
			default:
				break;
		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_mgmtEvtLOG*/

//=====================================================================================
// Fonction		: write_mgmtEvtSynthesis1
// Entrees		: <action> : action associé
//				  <var_val< : pointeur sur valeur à appliquée
//				  <var_val_type> : type de valeur
//				  <var_val_len> : longueur de valeur
//				  <statP< : 
//				  <name< : 
//				  <name_len< : 
// Sortie		: <loc_s32_return>
// Auteur		: CM - 18/03/2010 -
// Description	: Write function
//=====================================================================================
int
   write_mgmtEvtSynthesis1(int action,
						   u_char * var_val,
						   u_char var_val_type,
						   size_t var_val_len,
						   u_char * statP,
						   oid * name,
						   size_t name_len)
{
	s32sod	loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_iindex;
	s32sod	loc_s32_sem;
	S_STRUCT_CFG_EVENT loc_s_cfg_evt;
	u16sod	loc_u16_indEvt;

	loc_s32_iindex = name[name_len - 1];

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtEvt-Synthesis1 called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		  (*(int*)(var_val) != 1)		//on
						  &&(*(int*)(var_val) != 2)		//off
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;

			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION mgmtEvt-Synthesis1 called\n"));
				//On recherche index de l'evt (car loc_s32_iindex = numéro de l'évt)
				loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);
				if(US_INDICE_NON_TROUVE != loc_u16_indEvt)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on lève le sémaphore
					if(TRUE == u8FillConfigTabEvt(&s_cfg_tempo_snmpd))
					{
						switch(*(int*)(var_val))
						{
							case 1:  //on
								SetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_SYNTHESE_1);
								break;
							case 2: //off
								ResetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_SYNTHESE_1);
								break;
							default:
								break;
						}
						if(TRUE==u8TestConfigTabEvt(&s_cfg_tempo_snmpd))
						{
							u8EditConfigTabEvt(&s_cfg_tempo_snmpd);
							CopyConfigTabEvt(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
						}
						else
						{
							loc_s32_return = SNMP_ERR_WRONGVALUE;
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				else
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
			default:
				break;
		}
	}
	else
	{
		loc_s32_return = SNMP_ERR_AUTHORIZATIONERROR;
	}

	return loc_s32_return;
}/*write_mgmtEvtSynthesis1*/

//=====================================================================================
// Fonction		: s32Header_mgmtMulticast_Sources_Table
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_mgmtMulticast_Sources_Table(struct variable *loc_ps_vp,
													oid * loc_pt_name,
													size_t * loc_pt_length,
													s32sod loc_s32_exact,
													size_t * loc_pt_var_len,
													WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	if((MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)&&
	   (TRUE == s_config_process_snmpd.s_multicast.u8_proxy_igmp_activation)
	  )
	{
		for(loc_u16_i=0;loc_u16_i<NB_MAX_SRC_MULTICAST;loc_u16_i++)
		{
			if(TRUE == s_config_process_snmpd.s_multicast.ps_source_multicast[loc_u16_i].u8_enable)
			{
				//Le dernier oid
				loc_pt_newname[18] = (oid)loc_u16_i+1;
				loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
				if((loc_s32_exact && (0 == loc_s32_result))||
				   (!loc_s32_exact && (loc_s32_result < 0))
				  ) //CONDITION: oid identique à celui demandé ou ..."
				{

					loc_s32_iindex = MATCH_SUCCEEDED;

					//on applique le nouvel oid
					memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));
	//				DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
	//							loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
	//							loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
	//							loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
	//						    loc_pt_name[15],loc_pt_name[16]));

					*loc_pt_length = loc_ps_vp->namelen + 1;
					*loc_pt_write_method = 0;
					*loc_pt_var_len = sizeof(long);
					loc_u16_i = NB_MAX_SRC_MULTICAST + 1;	//on sort
				}
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_mgmtMulticast_Sources_Table*/

//=====================================================================================
// Fonction		: var_mgmtMulticast_Sources_Table
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_mgmtMulticast_Sources_Table(struct variable *loc_ps_vp,
									oid * loc_pt_name,
									size_t * loc_pt_length,
									int loc_s32_exact,
									size_t * loc_pt_var_len,
									WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_mgmtMulticast_Sources_Table(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_mgmtMulticast_Sources_Table(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_mgmtMulticast_Sources_Table(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_mgmtMulticast_Sources_Table*/

//=====================================================================================
// Fonction		: s32Header_staAlarmslistTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_staAlarmslistTable(struct variable *loc_ps_vp,
										   oid * loc_pt_name,
										   size_t * loc_pt_length,
										   s32sod loc_s32_exact,
										   size_t * loc_pt_var_len,
										   WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_indEvt;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u16_indEvt=0; loc_u16_indEvt<NB_MAX_EVENEMENTS; loc_u16_indEvt++)
	{
		if((TRUE == u8TestEvenementValide(loc_u16_indEvt))&&
		   (TYPE_EVT_ALARME == S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u8_type_evt)
		  )
		{
			//Le dernier oid
			loc_pt_newname[18] = (oid)S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if (	(loc_s32_exact && (0 == loc_s32_result))
					||	(!loc_s32_exact && (loc_s32_result < 0))
			   ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u16_indEvt = NB_MAX_EVENEMENTS + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_staAlarmslistTable*/

//=====================================================================================
// Fonction		: var_staAlarmslistTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_staAlarmslistTable(struct variable *loc_ps_vp,
						  oid * loc_pt_name,
						  size_t * loc_pt_length,
						  int loc_s32_exact,
						  size_t * loc_pt_var_len,
						  WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;
	s32sod	loc_s32_sem;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	loc_s32_ifirst = s32Header_staAlarmslistTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);

	s32Lock_Get(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on lève le sémaphore
	if(FALSE == u8FillEventSystemFile(pt_eventsystem_process_snmpd))
	{
		loc_s32_ifirst = MATCH_FAILED;	//erreur lecture
	}
	s32Lock_Release(SEMAPHORE_BDD_SYSTEMEVENT, &loc_s32_sem);	//on relache le sem

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(FALSE == u8FillExploitEventsGlobalFile(&s_exp_events_process_snmpd))
	{
		loc_s32_ifirst = MATCH_FAILED;	//erreur lecture
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem
	
	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_staAlarmslistTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_staAlarmslistTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_staAlarmslistTable*/

//=====================================================================================
// Fonction		: s32Header_staWirelessApClientTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_staWirelessApClientTable(struct variable *loc_ps_vp,
										   oid * loc_pt_name,
										   size_t * loc_pt_length,
										   s32sod loc_s32_exact,
										   size_t * loc_pt_var_len,
										   WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	for(loc_u16_i=0; loc_u16_i<NB_ASSOCIATED_STATIONS_MAX; loc_u16_i++)
	{
		if(TRUE == s_exploit_process_snmpd.s_access_point.s_wifi_client[loc_u16_i].u8_present)
		{
			//Le dernier oid
			loc_pt_newname[18] = (oid)loc_u16_i+1;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if (	(loc_s32_exact && (0 == loc_s32_result))
					||	(!loc_s32_exact && (loc_s32_result < 0))
			   ) //CONDITION: oid identique à celui demandé ou ..."
			{

				loc_s32_iindex = MATCH_SUCCEEDED;

				//on applique le nouvel oid
				memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));

				*loc_pt_length = loc_ps_vp->namelen + 1;
				*loc_pt_write_method = 0;
				*loc_pt_var_len = sizeof(long);
				loc_u16_i = NB_ASSOCIATED_STATIONS_MAX + 1;	//on sort
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_staWirelessApClientTable*/

//=====================================================================================
// Fonction		: var_staWirelessApClientTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_staWirelessApClientTable(struct variable *loc_ps_vp,
						  oid * loc_pt_name,
						  size_t * loc_pt_length,
						  int loc_s32_exact,
						  size_t * loc_pt_var_len,
						  WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;
	s32sod	loc_s32_sem;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(TRUE == u8FillExploitAccessPointFile(&s_exploit_process_snmpd.s_access_point))
	{
		loc_s32_ifirst = s32Header_staWirelessApClientTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);
	}
	else
	{
		loc_s32_ifirst = MATCH_FAILED;	//erreur lecture
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_staWirelessApClientTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_staWirelessApClientTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_staWirelessApClientTable*/

//=====================================================================================
// Fonction		: s32Header_staDhcpClientsTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
static s32sod s32Header_staDhcpClientsTable(struct variable *loc_ps_vp,
	oid * loc_pt_name,
	size_t * loc_pt_length,
	s32sod loc_s32_exact,
	size_t * loc_pt_var_len,
	WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_i;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	if((MODE_RADIO_MODEM_STATION == s_config_process_snmpd.s_gene.u8_mode_radio_modem)&&
	   (MODE_NETWORK_ROUTER == s_config_process_snmpd.s_gene.u8_mode_network)&&
	   (FCT_DHCP_SERVER == s_config_process_snmpd.s_gene.u8_lan_fonction_dhcp)
	  )
	{
		for(loc_u16_i=0; loc_u16_i<NB_MAX_CLIENTS_DHCP; loc_u16_i++)
		{
			if(TRUE == s_exploit_process_snmpd.s_dhcp.s_client_connected[loc_u16_i].u8_present)
			{
				//Le dernier oid
				loc_pt_newname[18] = (oid)loc_u16_i+1;
				loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
				if (	(loc_s32_exact && (0 == loc_s32_result))
						||	(!loc_s32_exact && (loc_s32_result < 0))
				   ) //CONDITION: oid identique à celui demandé ou ..."
				{

					loc_s32_iindex = MATCH_SUCCEEDED;

					//on applique le nouvel oid
					memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));

					*loc_pt_length = loc_ps_vp->namelen + 1;
					*loc_pt_write_method = 0;
					*loc_pt_var_len = sizeof(long);
					loc_u16_i = NB_MAX_CLIENTS_DHCP + 1;	//on sort
				}
			}
		}
	}

	return loc_s32_iindex;
}/*s32Header_staDhcpClientsTable*/

//=====================================================================================
// Fonction		: var_staDhcpClientsTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 18/06/2008 -
// Description	: gestion table "complexe" snmp
//=====================================================================================
u_char *
   var_staDhcpClientsTable(struct variable *loc_ps_vp,
								oid * loc_pt_name,
								size_t * loc_pt_length,
								int loc_s32_exact,
								size_t * loc_pt_var_len,
								WriteMethod ** loc_pt_write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;
	s32sod	loc_s32_sem;

	loc_pt_return = NULL;	//INIT
	*loc_pt_write_method = 0;

	s32Lock_Get(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on lève le sem
	if(TRUE == u8FillExploitDHCPFile(&s_exploit_process_snmpd.s_dhcp))
	{
		loc_s32_ifirst = s32Header_staDhcpClientsTable(loc_ps_vp, loc_pt_name, loc_pt_length, loc_s32_exact, loc_pt_var_len, loc_pt_write_method);
	}
	else
	{
		loc_s32_ifirst = MATCH_FAILED;	//erreur lecture
	}
	s32Lock_Release(SEMAPHORE_BDD_EXPLOIT, &loc_s32_sem);	//on relache le sem

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = loc_pt_name[*loc_pt_length - 1];

		if (ASN_OCTET_STR == loc_ps_vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_staDhcpClientsTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			*loc_pt_var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if (ASN_INTEGER == loc_ps_vp->type) {
			long_return = (long )(captureInt_staDhcpClientsTable(loc_ps_vp->magic, loc_s32_iindex, loc_pt_write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}/*var_staDhcpClientsTable*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: init_mib_wrm100
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 09/09/2009 -
// Description	: Initialisation de la mib WRM100
//					Main Function called when SNMP is loaded
//=====================================================================================
void init_mib_wrm100(void)
{
	DEBUGMSGTL(("sodielec", "init_mib_wrm100 called\n"));

	/** Registration of MIB Tree and tables with the agent */
	/** ** MIB Tree       */
	REGISTER_MIB("wrm100-variables7", wrm100_variables7, variable7,
				 wrm100_variables7_oid);


	
	/** ** Tables         */
	REGISTER_MIB("funcSoftwareRevisionTable", funcSoftwareRevision_variables, variable2,
				 funcSoftwareRevision_variables_oid);
	REGISTER_MIB("mgmtWirelessMultiTable", mgmtWirelessMulti_variables, variable2,
				 mgmtWirelessMulti_variables_oid);
	REGISTER_MIB("mgmtIProutingStatic-Table", mgmtIProutingStaticTable_variables, variable2,
				 mgmtIProutingStaticTable_variables_oid);
	REGISTER_MIB("mgmtIProutingPolicy-Table", mgmtIProutingPolicyTable_variables, variable2,
				 mgmtIProutingPolicyTable_variables_oid);
	REGISTER_MIB("mgmtNatPortForwarding-Table", mgmtNatPortForwardingTable_variables, variable2,
				 mgmtNatPortForwardingTable_variables_oid);
	REGISTER_MIB("mgmtNatAddressesMapping-Table", mgmtNatAddressesMappingTable_variables, variable2,
				 mgmtNatAddressesMappingTable_variables_oid);
	REGISTER_MIB("mgmtEvt-Table", mgmtEvtTable_variables, variable2,
				 mgmtEvtTable_variables_oid);
	REGISTER_MIB("mgmtMulticast-Sources-Table", mgmtMulticast_Sources_Table_variables, variable2,
				 mgmtMulticast_Sources_Table_variables_oid);
	
	REGISTER_MIB("staAlarmslist-Table", staAlarmslistTable_variables, variable2,
				 staAlarmslistTable_variables_oid);
	REGISTER_MIB("staWirelessApClient-Table", staWirelessApClientTable_variables, variable2,
				 staWirelessApClientTable_variables_oid);
	REGISTER_MIB("staDhcpClients-Table", staDhcpClientsTable_variables, variable2,
				 staDhcpClientsTable_variables_oid);

	/* if necessary, data will be initialised here */
	initdata_mib_wrm100();
}/*init_mib_wrm100*/

