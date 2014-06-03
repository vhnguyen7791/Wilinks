/*========================================================================*/
/* NOM DU FICHIER  : cfg_snmp.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 12/11/2009                                           */
/* Libelle         : Principal: Configuration du serveur SNMP			  */
/* Projet          : WRM100                                               */
/* Indice          : BE034                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE034 28/06/2010 CM
// - Correction pour SNMP du type d'interfaces (ifType dans la table ifTable)
/*========================================================================*/

/*_______I - COMMENTAIRES - DEFINITIONS - REMARQUES ________________________*/

/*_______II - DEFINE _______________________________________________________*/

#ifdef _CFG_SNMP
#define _CFG_SNMP_EXT
#else
#define _CFG_SNMP_EXT	extern
#endif

//define issus de snmp-5.4/agent/mibgroup/if-mib/ifTable/ifTable_constants.h
#define IANAIFTYPE_OTHER  1
#define IANAIFTYPE_REGULAR1822  2
#define IANAIFTYPE_HDH1822  3
#define IANAIFTYPE_DDNX25  4
#define IANAIFTYPE_RFC877X25  5
#define IANAIFTYPE_ETHERNETCSMACD  6
#define IANAIFTYPE_ISO88023CSMACD  7
#define IANAIFTYPE_ISO88024TOKENBUS  8
#define IANAIFTYPE_ISO88025TOKENRING  9
#define IANAIFTYPE_ISO88026MAN  10
#define IANAIFTYPE_STARLAN  11
#define IANAIFTYPE_PROTEON10MBIT  12
#define IANAIFTYPE_PROTEON80MBIT  13
#define IANAIFTYPE_HYPERCHANNEL  14
#define IANAIFTYPE_FDDI  15
#define IANAIFTYPE_LAPB  16
#define IANAIFTYPE_SDLC  17
#define IANAIFTYPE_DS1  18
#define IANAIFTYPE_E1  19
#define IANAIFTYPE_BASICISDN  20
#define IANAIFTYPE_PRIMARYISDN  21
#define IANAIFTYPE_PROPPOINTTOPOINTSERIAL  22
#define IANAIFTYPE_PPP  23
#define IANAIFTYPE_SOFTWARELOOPBACK  24
#define IANAIFTYPE_EON  25
#define IANAIFTYPE_ETHERNET3MBIT  26
#define IANAIFTYPE_NSIP  27
#define IANAIFTYPE_SLIP  28
#define IANAIFTYPE_ULTRA  29
#define IANAIFTYPE_DS3  30
#define IANAIFTYPE_SIP  31
#define IANAIFTYPE_FRAMERELAY  32
#define IANAIFTYPE_RS232  33
#define IANAIFTYPE_PARA  34
#define IANAIFTYPE_ARCNET  35
#define IANAIFTYPE_ARCNETPLUS  36
#define IANAIFTYPE_ATM  37
#define IANAIFTYPE_MIOX25  38
#define IANAIFTYPE_SONET  39
#define IANAIFTYPE_X25PLE  40
#define IANAIFTYPE_ISO88022LLC  41
#define IANAIFTYPE_LOCALTALK  42
#define IANAIFTYPE_SMDSDXI  43
#define IANAIFTYPE_FRAMERELAYSERVICE  44
#define IANAIFTYPE_V35  45
#define IANAIFTYPE_HSSI  46
#define IANAIFTYPE_HIPPI  47
#define IANAIFTYPE_MODEM  48
#define IANAIFTYPE_AAL5  49
#define IANAIFTYPE_SONETPATH  50
#define IANAIFTYPE_SONETVT  51
#define IANAIFTYPE_SMDSICIP  52
#define IANAIFTYPE_PROPVIRTUAL  53
#define IANAIFTYPE_PROPMULTIPLEXOR  54
#define IANAIFTYPE_IEEE80212  55
#define IANAIFTYPE_FIBRECHANNEL  56
#define IANAIFTYPE_HIPPIINTERFACE  57
#define IANAIFTYPE_FRAMERELAYINTERCONNECT  58
#define IANAIFTYPE_AFLANE8023  59
#define IANAIFTYPE_AFLANE8025  60
#define IANAIFTYPE_CCTEMUL  61
#define IANAIFTYPE_FASTETHER  62
#define IANAIFTYPE_ISDN  63
#define IANAIFTYPE_V11  64
#define IANAIFTYPE_V36  65
#define IANAIFTYPE_G703AT64K  66
#define IANAIFTYPE_G703AT2MB  67
#define IANAIFTYPE_QLLC  68
#define IANAIFTYPE_FASTETHERFX  69
#define IANAIFTYPE_CHANNEL  70
#define IANAIFTYPE_IEEE80211  71
#define IANAIFTYPE_IBM370PARCHAN  72
#define IANAIFTYPE_ESCON  73
#define IANAIFTYPE_DLSW  74
#define IANAIFTYPE_ISDNS  75
#define IANAIFTYPE_ISDNU  76
#define IANAIFTYPE_LAPD  77
#define IANAIFTYPE_IPSWITCH  78
#define IANAIFTYPE_RSRB  79
#define IANAIFTYPE_ATMLOGICAL  80
#define IANAIFTYPE_DS0  81
#define IANAIFTYPE_DS0BUNDLE  82
#define IANAIFTYPE_BSC  83
#define IANAIFTYPE_ASYNC  84
#define IANAIFTYPE_CNR  85
#define IANAIFTYPE_ISO88025DTR  86
#define IANAIFTYPE_EPLRS  87
#define IANAIFTYPE_ARAP  88
#define IANAIFTYPE_PROPCNLS  89
#define IANAIFTYPE_HOSTPAD  90
#define IANAIFTYPE_TERMPAD  91
#define IANAIFTYPE_FRAMERELAYMPI  92
#define IANAIFTYPE_X213  93
#define IANAIFTYPE_ADSL  94
#define IANAIFTYPE_RADSL  95
#define IANAIFTYPE_SDSL  96
#define IANAIFTYPE_VDSL  97
#define IANAIFTYPE_ISO88025CRFPINT  98
#define IANAIFTYPE_MYRINET  99
#define IANAIFTYPE_VOICEEM  100
#define IANAIFTYPE_VOICEFXO  101
#define IANAIFTYPE_VOICEFXS  102
#define IANAIFTYPE_VOICEENCAP  103
#define IANAIFTYPE_VOICEOVERIP  104
#define IANAIFTYPE_ATMDXI  105
#define IANAIFTYPE_ATMFUNI  106
#define IANAIFTYPE_ATMIMA  107
#define IANAIFTYPE_PPPMULTILINKBUNDLE  108
#define IANAIFTYPE_IPOVERCDLC  109
#define IANAIFTYPE_IPOVERCLAW  110
#define IANAIFTYPE_STACKTOSTACK  111
#define IANAIFTYPE_VIRTUALIPADDRESS  112
#define IANAIFTYPE_MPC  113
#define IANAIFTYPE_IPOVERATM  114
#define IANAIFTYPE_ISO88025FIBER  115
#define IANAIFTYPE_TDLC  116
#define IANAIFTYPE_GIGABITETHERNET  117
#define IANAIFTYPE_HDLC  118
#define IANAIFTYPE_LAPF  119
#define IANAIFTYPE_V37  120
#define IANAIFTYPE_X25MLP  121
#define IANAIFTYPE_X25HUNTGROUP  122
#define IANAIFTYPE_TRASNPHDLC  123
#define IANAIFTYPE_INTERLEAVE  124
#define IANAIFTYPE_FAST  125
#define IANAIFTYPE_IP  126
#define IANAIFTYPE_DOCSCABLEMACLAYER  127
#define IANAIFTYPE_DOCSCABLEDOWNSTREAM  128
#define IANAIFTYPE_DOCSCABLEUPSTREAM  129
#define IANAIFTYPE_A12MPPSWITCH  130
#define IANAIFTYPE_TUNNEL  131
#define IANAIFTYPE_COFFEE  132
#define IANAIFTYPE_CES  133
#define IANAIFTYPE_ATMSUBINTERFACE  134
#define IANAIFTYPE_L2VLAN  135
#define IANAIFTYPE_L3IPVLAN  136
#define IANAIFTYPE_L3IPXVLAN  137
#define IANAIFTYPE_DIGITALPOWERLINE  138
#define IANAIFTYPE_MEDIAMAILOVERIP  139
#define IANAIFTYPE_DTM  140
#define IANAIFTYPE_DCN  141
#define IANAIFTYPE_IPFORWARD  142
#define IANAIFTYPE_MSDSL  143
#define IANAIFTYPE_IEEE1394  144
#define IANAIFTYPE_IF_GSN  145
#define IANAIFTYPE_DVBRCCMACLAYER  146
#define IANAIFTYPE_DVBRCCDOWNSTREAM  147
#define IANAIFTYPE_DVBRCCUPSTREAM  148
#define IANAIFTYPE_ATMVIRTUAL  149
#define IANAIFTYPE_MPLSTUNNEL  150
#define IANAIFTYPE_SRP  151
#define IANAIFTYPE_VOICEOVERATM  152
#define IANAIFTYPE_VOICEOVERFRAMERELAY  153
#define IANAIFTYPE_IDSL  154
#define IANAIFTYPE_COMPOSITELINK  155
#define IANAIFTYPE_SS7SIGLINK  156
#define IANAIFTYPE_PROPWIRELESSP2P  157
#define IANAIFTYPE_FRFORWARD  158
#define IANAIFTYPE_RFC1483  159
#define IANAIFTYPE_USB  160
#define IANAIFTYPE_IEEE8023ADLAG  161
#define IANAIFTYPE_BGPPOLICYACCOUNTING  162
#define IANAIFTYPE_FRF16MFRBUNDLE  163
#define IANAIFTYPE_H323GATEKEEPER  164
#define IANAIFTYPE_H323PROXY  165
#define IANAIFTYPE_MPLS  166
#define IANAIFTYPE_MFSIGLINK  167
#define IANAIFTYPE_HDSL2  168
#define IANAIFTYPE_SHDSL  169
#define IANAIFTYPE_DS1FDL  170
#define IANAIFTYPE_POS  171
#define IANAIFTYPE_DVBASIIN  172
#define IANAIFTYPE_DVBASIOUT  173
#define IANAIFTYPE_PLC  174
#define IANAIFTYPE_NFAS  175
#define IANAIFTYPE_TR008  176
#define IANAIFTYPE_GR303RDT  177
#define IANAIFTYPE_GR303IDT  178
#define IANAIFTYPE_ISUP  179
#define IANAIFTYPE_PROPDOCSWIRELESSMACLAYER  180
#define IANAIFTYPE_PROPDOCSWIRELESSDOWNSTREAM  181
#define IANAIFTYPE_PROPDOCSWIRELESSUPSTREAM  182
#define IANAIFTYPE_HIPERLAN2  183
#define IANAIFTYPE_PROPBWAP2MP  184
#define IANAIFTYPE_SONETOVERHEADCHANNEL  185
#define IANAIFTYPE_DIGITALWRAPPEROVERHEADCHANNEL  186
#define IANAIFTYPE_AAL2  187
#define IANAIFTYPE_RADIOMAC  188
#define IANAIFTYPE_ATMRADIO  189
#define IANAIFTYPE_IMT  190
#define IANAIFTYPE_MVL  191
#define IANAIFTYPE_REACHDSL  192
#define IANAIFTYPE_FRDLCIENDPT  193
#define IANAIFTYPE_ATMVCIENDPT  194
#define IANAIFTYPE_OPTICALCHANNEL  195
#define IANAIFTYPE_OPTICALTRANSPORT  196
#define IANAIFTYPE_PROPATM  197
#define IANAIFTYPE_VOICEOVERCABLE  198
#define IANAIFTYPE_INFINIBAND  199
#define IANAIFTYPE_TELINK  200
#define IANAIFTYPE_Q2931  201
#define IANAIFTYPE_VIRTUALTG  202
#define IANAIFTYPE_SIPTG  203
#define IANAIFTYPE_SIPSIG  204
#define IANAIFTYPE_DOCSCABLEUPSTREAMCHANNEL  205
#define IANAIFTYPE_ECONET  206
#define IANAIFTYPE_PON155  207
#define IANAIFTYPE_PON622  208
#define IANAIFTYPE_BRIDGE  209
#define IANAIFTYPE_LINEGROUP  210
#define IANAIFTYPE_VOICEEMFGD  211
#define IANAIFTYPE_VOICEFGDEANA  212
#define IANAIFTYPE_VOICEDID  213
#define IANAIFTYPE_MPEGTRANSPORT  214
#define IANAIFTYPE_SIXTOFOUR  215
#define IANAIFTYPE_GTP  216
#define IANAIFTYPE_PDNETHERLOOP1  217
#define IANAIFTYPE_PDNETHERLOOP2  218
#define IANAIFTYPE_OPTICALCHANNELGROUP  219
#define IANAIFTYPE_HOMEPNA  220
#define IANAIFTYPE_GFP  221
#define IANAIFTYPE_CISCOISLVLAN  222
#define IANAIFTYPE_ACTELISMETALOOP  223
#define IANAIFTYPE_FCIPLINK  224

/*_____III - DEFINITIONS DE TYPES_____________________________________________*/

/*_______IV - PROTOTYPES DEFINIS___________________________________________*/


//=====================================================================================
// Fonction		: Install_Snmp
// Entrees		: <loc_ps_config< : pointeur sur configuration courante
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Installe snmp
//=====================================================================================
void Install_Snmp(S_STRUCT_CONFIGURATION *loc_ps_config);

//=====================================================================================
// Fonction		: u8CreationFichierCfgSnmpd
// Entrees		: <loc_ps_config< : config de l'�quipement
//				: <loc_u8_type_equipement> : type de l'�quipement
//				  <loc_u8_langue> : langue
// Sortie		: <loc_u8_resultat> : TRUE si OK, sinon FALSE
// Auteur		: CM - 12/11/2009 -
// Description	: Edition du fichier snmpd.conf pour le processus snmpd
//=====================================================================================
u8sod u8CreationFichierCfgSnmpd(S_STRUCT_CONFIGURATION *loc_ps_config, u8sod loc_u8_type_equipement, u8sod loc_u8_langue);

//=====================================================================================
// Fonction		: InitModule_Cfg_Snmp
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 12/11/2009 -
// Description	: Initialisation du module de cfg_snmp
//=====================================================================================
void InitModule_Cfg_Snmp(void);

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/

