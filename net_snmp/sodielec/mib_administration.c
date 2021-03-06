/*========================================================================*/
/* NOM DU FICHIER  : mib_administration.c								  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : NET-SNMP: MIB ADMINISTRATION						  */
/* Projet          : WRM100                                               */
/* Indice          : BE019                                                */
/*========================================================================*/
/* Historique      :                                                      */
/*
 * Note: this file originally auto-generated by mib2c using
 *         mib2c.sodielec_format.conf, v1.0 Juin 2006
 * Version: PC_SOUS_LINUX: 0, CARTE_EVAL: 0 [oui(1), non(0)]
 * Date: Mon Jun 12 10:39:44 2006
 */
//BE019 16/03/2010 CM
// - CREATION source bas�e sur SDVB200 BE373
/*========================================================================*/

/*_______II - DEFINE ______________________________________________________*/

/*_______III - INCLUDES - DIRECTIVES ______________________________________*/
#include "headers.h"
#include "mib_administration.h"
#include "mib_administration_data.h"
#include "util_funcs.h"

/*_______V   - VARIABLES GLOBALES __________________________________________*/

/** OID Variables         */
/** ** for MIB Tree       */
oid administration_variables_oid[] = {_ENTERPRISE_SODIELECV2_ADMINISTRATION};

/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable4 administration_variables[] = {
	{EQUINFOV1NOM, ASN_OCTET_STR, RONLY, var_administration, 3, {1,1,1}},
	{EQUINFOV1LOCALISATION, ASN_OCTET_STR, RONLY, var_administration, 3, {1,1,2}},
	{EQUINFOV1ID, ASN_OCTET_STR, RONLY, var_administration, 3, {1,1,3}},
	{MGMTV1REEMISSIONTRAP, ASN_INTEGER, RWRITE, var_administration, 3, {1,2,1}},
	{MGMTV1SIGNEVIECMD, ASN_INTEGER, RWRITE, var_administration, 4, {1,2,2,1}},
	{MGMTV1SIGNEVIECYCLE, ASN_INTEGER, RWRITE, var_administration, 4, {1,2,2,2}},
	{MGMTV1AUTORISATIONTRAP, ASN_INTEGER, RWRITE, var_administration, 3, {1,2,3}},
};

/** ** for Tables         */
oid evtV1configTable_variables_oid[] = {_ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,3,1,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 evtV1configTable_variables[] = {
	{EVTV1CFGINDEX, ASN_INTEGER, RONLY, var_evtV1configTable, 2, {1,1}},
	{EVTV1CFGEQUIPEMENT, ASN_OCTET_STR, RONLY, var_evtV1configTable, 2, {1,2}},
	{EVTV1CFGID, ASN_INTEGER, RONLY, var_evtV1configTable, 2, {1,3}},
	{EVTV1CFGDESCRIPTION, ASN_OCTET_STR, RONLY, var_evtV1configTable, 2, {1,4}},
	{EVTV1CFGNIVEAUGRAVITE, ASN_INTEGER, RWRITE, var_evtV1configTable, 2, {1,5}},
	{EVTV1CFGACTION, ASN_INTEGER, RWRITE, var_evtV1configTable, 2, {1,6}},
	{EVTV1CFGTYPE, ASN_INTEGER, RONLY, var_evtV1configTable, 2, {1,7}},
};

oid evtV1PrototrapTable_variables_oid[] = {_ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,3,2,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 evtV1PrototrapTable_variables[] = {
	{EVTV1PROTOTRAPINDEX, ASN_INTEGER, RONLY, var_evtV1PrototrapTable, 2, {1,1}},
	{EVTV1PROTOTRAPNIVEAUGRAVITE, ASN_INTEGER, RONLY, var_evtV1PrototrapTable, 2, {1,2}},
	{EVTV1PROTOTRAPCYCLE, ASN_INTEGER, RWRITE, var_evtV1PrototrapTable, 2, {1,3}},
	{EVTV1PROTOTRAPNOMBRE, ASN_INTEGER, RWRITE, var_evtV1PrototrapTable, 2, {1,4}},
};

oid alarmeV1Table_variables_oid[] = {_ENTERPRISE_SODIELECV2_ADMINISTRATIONV1,4,1};
/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable2 alarmeV1Table_variables[] = {
	{ALARMEV1INDEX, ASN_INTEGER, RONLY, var_alarmeV1Table, 2, {1,1}},
	{ALARMEV1ID, ASN_INTEGER, RONLY, var_alarmeV1Table, 2, {1,2}},
	{ALARMEV1VALEUR, ASN_INTEGER, RONLY, var_alarmeV1Table, 2, {1,3}},
	{ALARMEV1EQUIPEMENT, ASN_OCTET_STR, RONLY, var_alarmeV1Table, 2, {1,4}},
	{ALARMEV1STATUT, ASN_INTEGER, RONLY, var_alarmeV1Table, 2, {1,5}},
	{ALARMEV1DATE, ASN_OCTET_STR, RONLY, var_alarmeV1Table, 2, {1,6}},
	{ALARMEV1HEURE, ASN_OCTET_STR, RONLY, var_alarmeV1Table, 2, {1,7}},
	{ALARMEV1ACQUIT, ASN_INTEGER, RWRITE, var_alarmeV1Table, 2, {1,8}},
};



/*_______VI  - PROCEDURES __________________________________________________*/
/** Main Function */
/** called when SNMP is loaded */
void
   init_mib_administration(void)
{
	DEBUGMSGTL(("sodielec", "init_mib_administration called\n"));
	
	/** Registration of MIB Tree and tables with the agent */
	/** ** MIB Tree       */
	REGISTER_MIB("administration", administration_variables, variable4,
				 administration_variables_oid);
	
	/** ** Tables         */
	REGISTER_MIB("evtV1configTable", evtV1configTable_variables, variable2,
				 evtV1configTable_variables_oid);
	REGISTER_MIB("evtV1PrototrapTable", evtV1PrototrapTable_variables, variable2,
				 evtV1PrototrapTable_variables_oid);
	REGISTER_MIB("alarmeV1Table", alarmeV1Table_variables, variable2,
				 alarmeV1Table_variables_oid);
	
	/* if necessary, data will be initialised here */
	initdata_mib_administration();
	
}


/** Header Functions for tables with CODE column */

/** Callback functions */
/** called whenever an incoming request refers to an object within this sub-tree */
/** ** for MIB Tree       */
u_char *
   var_administration(struct variable *vp,
					  oid * name,
					  size_t * length,
					  int exact,
					  size_t * var_len,
					  WriteMethod ** write_method)
{
	u_char *loc_pt_return;
	s8sod *loc_ps8_cp;
	
	loc_pt_return = NULL;	//INIT
	*write_method = 0;
	
	//   DEBUGMSGTL(("sodielec", "var_administration called\n"));
	if(MATCH_FAILED == header_generic(vp, name, length, exact, var_len, write_method))
	{
		;
	}
	else
	{
		if(ASN_OCTET_STR == vp->type) {
			loc_ps8_cp = (char *)(captureString_administration(vp->magic, write_method));
			*var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if(ASN_INTEGER == vp->type) {
			long_return = (long )(captureInt_administration(vp->magic, write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	return loc_pt_return;
}

/** ** for Tables         */

//=====================================================================================
// Fonction		: s32Header_evtV1configTable
// Entrees		: <loc_ps_vp< : variable
//				  <loc_pt_name< : oid de la variable
//				  <loc_pt_length< : longueur de l'oid de la variable
//				  <loc_s32_exact> : 
//				  <loc_pt_var_len< : 
//				  <loc_pt_write_method< : 
// Sortie		: <loc_s32_iindex> : MATCH_SUCCEEDED ou MATCH_FAILED
// Auteur		: CM - 31/08/2007 -
// Description	: gestion table "complexe" snmp : evtV1configTable
//=====================================================================================
static s32sod s32Header_evtV1configTable(struct variable *loc_ps_vp,
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
			loc_pt_newname[16] = (oid)S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_u16_indEvt].u16_numero_evt;
			loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
			if (	(loc_s32_exact && (0 == loc_s32_result))
				|| (!loc_s32_exact && (loc_s32_result < 0))
			   ) //CONDITION: oid identique � celui demand� ou ..."
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
}/*s32Header_evtV1configTable*/


u_char *
   var_evtV1configTable(struct variable *vp,
						oid * name,
						size_t * length,
						int exact,
						size_t * var_len,
						WriteMethod ** write_method)
{
	u_char	*loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod  loc_s32_iindex;
	s32sod	loc_s32_ifirst;
	

	loc_pt_return = NULL;	//INIT
	*write_method = 0;
	
	loc_s32_ifirst = s32Header_evtV1configTable(vp, name, length, exact, var_len, write_method);

	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = name[*length - 1];

		if(ASN_OCTET_STR == vp->type) {
			loc_ps8_cp = (s8sod *)(captureString_evtV1configTable(vp->magic, loc_s32_iindex, write_method));
			*var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if(ASN_INTEGER == vp->type) {
			long_return = (long )(captureInt_evtV1configTable(vp->magic, loc_s32_iindex, write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	else //MATCH_FAILED
	{
	}
	return loc_pt_return;
}

u_char *
   var_evtV1PrototrapTable(struct variable *vp,
						   oid * name,
						   size_t * length,
						   int exact,
						   size_t * var_len,
						   WriteMethod ** write_method)
{
	u_char *loc_pt_return;
	s8sod	*loc_ps8_cp;
	s32sod	loc_s32_iindex;
	
	loc_pt_return = NULL;	//INIT
	*write_method = 0;
	
	if (header_simple_table(vp, name, length, exact, var_len, write_method, EVTV1PROTOTRAPTABLE_LINES))
	{
		;
	}
	else
	{
		loc_s32_iindex = name[*length - 1] - 1;

		if(ASN_OCTET_STR == vp->type) {
			loc_ps8_cp = (char *)(captureString_evtV1PrototrapTable(vp->magic, loc_s32_iindex, write_method));
			*var_len = strlen(loc_ps8_cp);
			loc_pt_return = (u_char *) loc_ps8_cp;
		}
		if(ASN_INTEGER == vp->type) {
			long_return = (long )(captureInt_evtV1PrototrapTable(vp->magic, loc_s32_iindex, write_method));
			loc_pt_return = (u_char *) &long_return;
		}
	}
	
	return loc_pt_return;	
}

//=====================================================================================
// Fonction		: s32Header_alarmeV1Table_Entries
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
static s32sod s32Header_alarmeV1Table_Entries(struct variable *loc_ps_vp,
								oid * loc_pt_name,
								size_t * loc_pt_length,
								s32sod loc_s32_exact,
								size_t * loc_pt_var_len,
								WriteMethod ** loc_pt_write_method)
{
	oid loc_pt_newname[MAX_OID_LEN];
	s32sod	loc_s32_iindex;

	s32sod	loc_s32_result;
	u16sod	loc_u16_cpt;
	S_STRUCT_STA_TRAP		*loc_ps_encours;

	loc_s32_iindex = MATCH_FAILED;	//INIT

	memcpy((s8sod *) loc_pt_newname, (s8sod *) loc_ps_vp->name, (s32sod) loc_ps_vp->namelen * sizeof(oid)); //INIT

	//on recherche le prochain oid
	loc_ps_encours = ps_status_trap->ps_premier_trap; // INIT
	loc_u16_cpt = 0; //INIT
	while( (NULL != loc_ps_encours) && (loc_u16_cpt<TAILLE_MAX_TABLE_STATUSTRAP))
	{
		//Est-ce cette oid?
		loc_pt_newname[15] = (oid)(loc_ps_encours->u16_idx_table+1);
		
		loc_s32_result = snmp_oid_compare(loc_pt_name, *loc_pt_length, loc_pt_newname, (int) loc_ps_vp->namelen + 1); //return 0 si loc_pt_name = loc_pt_newname, return < 0 ou > 0 si loc_pt_name != loc_pt_newname 
		if (	(loc_s32_exact && (0 == loc_s32_result))
			 || (!loc_s32_exact && (loc_s32_result < 0))
		   ) //CONDITION: oid identique � celui demand� ou ..."
		{
			loc_s32_iindex = MATCH_SUCCEEDED;
			
			//on applique le nouvel oid
			memcpy((s8sod *) loc_pt_name, (s8sod *) loc_pt_newname, ((s32sod) loc_ps_vp->namelen + 1) * sizeof(oid));

			DEBUGMSGTL(("sodielec", "oid:%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d\n",
						loc_pt_name[0],loc_pt_name[1],loc_pt_name[2],loc_pt_name[3],loc_pt_name[4],
						loc_pt_name[5],loc_pt_name[6],loc_pt_name[7],loc_pt_name[8],loc_pt_name[9],
						loc_pt_name[10],loc_pt_name[11],loc_pt_name[12],loc_pt_name[13],loc_pt_name[14],
						loc_pt_name[15]));
			
			*loc_pt_length = loc_ps_vp->namelen + 1;
			*loc_pt_write_method = 0;
			*loc_pt_var_len = sizeof(long);
			loc_u16_cpt = TAILLE_MAX_TABLE_STATUSTRAP + 1;	//on sort
		}
		loc_ps_encours = (S_STRUCT_STA_TRAP*)loc_ps_encours->ps_next;
		loc_u16_cpt++;
	}

	return loc_s32_iindex;
}/*s32Header_alarmeV1Table_Entries*/

u_char *
   var_alarmeV1Table(struct variable *vp,
					 oid * name,
					 size_t * length,
					 int exact,
					 size_t * var_len,
					 WriteMethod ** write_method)
{
	s8sod	*loc_ps8_cp;
	u8sod	loc_u8_type_equipement;
	s32sod	loc_s32_ifirst;
	u_char *loc_pt_return;
	S_STRUCT_STA_TRAP		*loc_ps_trap;
	s32sod	loc_s32_sem;
	
	s32sod loc_s32_iindex;

	loc_pt_return = NULL;	//INIT
	*write_method = 0;

	loc_s32_ifirst = s32Header_alarmeV1Table_Entries(vp, name, length, exact, var_len, write_method);
	DEBUGMSGTL(("sodielec", "s32Header_alarmeV1Table_Entries %d\n",loc_s32_ifirst));
	if (MATCH_SUCCEEDED == loc_s32_ifirst) //CONDITION: index ok
	{
		loc_s32_iindex = name[*length - 1] - 1;
		if(TRUE == u8Search_IdxStatusTrap((u16sod)loc_s32_iindex,&loc_ps_trap)) //CONDITION: on lit les donn�es de la ligne de la table
		{
			DEBUGMSGTL(("sodielec", "u8Search_IdxStatusTrap TRUE: %d=> indexEvt=%d,%d (%d)\n",
						loc_s32_iindex,
						loc_ps_trap->u16_index_evt,loc_ps_trap->t_valeur_evt,
						loc_ps_trap->u8_etat_evt));

			DEBUGMSGTL(("sodielec", "vp->magic %d\n",vp->magic));
			
			switch (vp->magic) {
				case ALARMEV1INDEX:
					long_return = loc_s32_iindex;
					loc_pt_return = (u_char *) &long_return;
					break;
				case ALARMEV1ID:
					long_return = S_DESCRIPTION_EVENT_PAR_DEFAUT[loc_ps_trap->u16_index_evt].u16_numero_evt;
					loc_pt_return = (u_char *) &long_return;
					break;
				case ALARMEV1VALEUR:
					long_return = loc_ps_trap->t_valeur_evt;
					loc_pt_return = (u_char *) &long_return;
					break;
				case ALARMEV1EQUIPEMENT:
					loc_ps8_cp = ps8ConvertChaineToSnmp((s8sod*)S_DESCRIPT_EQUIPEMENT[ u8_snmp_type_equipement ].ps8_nom[u8_snmp_langue]);
					*var_len = strlen(loc_ps8_cp);
					loc_pt_return = (u_char *) loc_ps8_cp;
					break;
				case ALARMEV1STATUT:
					switch(loc_ps_trap->u8_etat_evt)
					{
						case ETAT_EVT_DEBUT:
							long_return = 1; //alarme-on
							break;
						case ETAT_EVT_FIN:
							long_return = 2; //alarme-off
							break;
						case ETAT_EVT_INFO:
							long_return = 3; //info
							break;
						default:
							long_return = 0;
							break;
					}
					loc_pt_return = (u_char *) &long_return;
					break;
				case ALARMEV1DATE:
					sprintf(ps8_data_a_tout_faire, "%04d%02d%02d",loc_ps_trap->s_date.u16_annee,loc_ps_trap->s_date.u8_mois,loc_ps_trap->s_date.u8_jour);
					loc_ps8_cp = ps8_data_a_tout_faire;
					*var_len = strlen(loc_ps8_cp);
					loc_pt_return = (u_char *) loc_ps8_cp;
					break;
				case ALARMEV1HEURE:
					sprintf(ps8_data_a_tout_faire, "%02d%02d%02d",loc_ps_trap->s_date.u8_heure,loc_ps_trap->s_date.u8_minute,loc_ps_trap->s_date.u8_seconde);
					loc_ps8_cp = ps8_data_a_tout_faire;
					*var_len = strlen(loc_ps8_cp);
					loc_pt_return = (u_char *) loc_ps8_cp;
					break;
				case ALARMEV1ACQUIT:
					if(VERSION_SNMPV1 == s_config_process_snmpd.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
					{
						switch(loc_ps_trap->u8_val_snmp)
						{
							case VAL_SNMP_NON_ACQUITTER:
								long_return = 1; //non-acquitter
								break;
							case VAL_SNMP_ACQUITTER:
								long_return = 2; //acquitter
								break;
							case VAL_SNMP_SUPPRIMER:
								long_return = 3; //supprimer
								break;
							default:
								long_return = 0;
								break;
						}
						*write_method = write_alarmeV1Acquit;
						loc_pt_return = (u_char *) &long_return;
					}
					else
					{
						long_return = 0;
						loc_pt_return = (u_char *) &long_return;
					}
					break;
				default:
					DEBUGMSGTL(("sodielec", "unknown sub-id %d in var_alarmeV1Table\n", vp->magic));
					break;
			}
		}
		else
		{
			DEBUGMSGTL(("sodielec", "u8Search_IdxStatusTrap FALSE: %d\n",loc_s32_iindex));
		}
	}
	else //MATCH_FAILED
	{
	}
	
	return loc_pt_return;
}


/** Write functions */
/** ** for MIB Tree       */
int
   write_mgmtV1ReemissionTrap(int action,
							  u_char * var_val,
							  u_char var_val_type,
							  size_t var_val_len,
							  u_char * statP,
							  oid * name,
							  size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	S_STRUCT_CIP_SNMPD s_cip_snmpd_tempo;
	s32sod loc_s32_sem;

	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtV1ReemissionTrap called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(*(int*)(var_val) != 1)			//1 : off
					 &&	(*(int*)(var_val) != 2)			//2 : on
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION mgmtV1ReemissionTrap called\n"));
				if(VERSION_SNMPV1 == s_config_process_snmpd.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
				{
					s32Lock_Get(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on l�ve le s�maphore
					if(TRUE == u8FillCipSnmpd(&s_cip_snmpd_tempo))
					{
						s_cip_snmpd_tempo.u8_replay_trap = TRUE;
						u8EditCipSnmpd(&s_cip_snmpd_tempo);
					}
					s32Lock_Release(SEMAPHORE_BDD_CIP_SNMPD, &loc_s32_sem);	//on relache le sem
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
}

int
   write_mgmtV1SigneVieCmd(int action,
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
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtV1SigneVieCmd called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(*(int*)(var_val) != 1)			//1 : off
					&&	(*(int*)(var_val) != 2)			//2 : on
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION mgmtV1SigneVieCmd called\n"));
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
				if(TRUE == u8FillConfigSnmp(&s_cfg_tempo_snmpd))
				{
					if (1 == *(int*)(var_val)) // off(1)
					{
						s_cfg_tempo_snmpd.s_snmp.s_trap_signevie.u8_activation = FALSE;
					}
					else
					{
						s_cfg_tempo_snmpd.s_snmp.s_trap_signevie.u8_activation = TRUE;
					}
					if(TRUE==u8TestConfigSnmp(&s_cfg_tempo_snmpd))
					{
						u8EditConfigSnmp(&s_cfg_tempo_snmpd);
						CopyConfigSnmp(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
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
}

int
   write_mgmtV1SigneVieCycle(int action,
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
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtV1SigneVieCycle called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(VALEUR_MIN_CYCLE_VIE <= *(int*)(var_val))
					&&	(*(int*)(var_val) <= VALEUR_MAX_CYCLE_VIE)
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
				DEBUGMSGTL(("sodielec", "ACTION mgmtV1SigneVieCycle called\n"));
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
				if(TRUE == u8FillConfigSnmp(&s_cfg_tempo_snmpd))
				{
					s_cfg_tempo_snmpd.s_snmp.s_trap_signevie.u16_cycle = (u16sod)*(int*)(var_val);
					if(TRUE==u8TestConfigSnmp(&s_cfg_tempo_snmpd))
					{
						u8EditConfigSnmp(&s_cfg_tempo_snmpd);
						CopyConfigSnmp(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
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
}

int
   write_mgmtV1AutorisationTrap(int action,
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
				DEBUGMSGTL(("sodielec", "RESERVE1 mgmtV1AutorisationTrap called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(*(int*)(var_val) != 1)			//1 : off
					&&	(*(int*)(var_val) != 2)			//2 : on
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
					DEBUGMSGTL(("sodielec", "RESERVE1:mgmtV1AutorisationTrap SNMP_ERR_WRONGVALUE %d\n",*(int*)(var_val)));
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION mgmtV1AutorisationTrap called %d\n",*(int*)(var_val)));
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
				if(TRUE == u8FillConfigSnmp(&s_cfg_tempo_snmpd))
				{
					if (1 == *(int*)(var_val)) // off(1)
					{
						s_cfg_tempo_snmpd.s_snmp.u8_emission_trap = EMISSION_TRAP_INACTIVE;
					}
					else
					{
						s_cfg_tempo_snmpd.s_snmp.u8_emission_trap = EMISSION_TRAP_ACTIVE;
					}
					if(TRUE==u8TestConfigSnmp(&s_cfg_tempo_snmpd))
					{
						u8EditConfigSnmp(&s_cfg_tempo_snmpd);
						CopyConfigSnmp(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
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
}



/** ** for Tables         */
int
   write_evtV1cfgNiveauGravite(int action,
							   u_char * var_val,
							   u_char var_val_type,
							   size_t var_val_len,
							   u_char * statP,
							   oid * name,
							   size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;
	u16sod	loc_u16_indEvt;
	s32sod	loc_s32_iindex;
	
	loc_s32_iindex = name[name_len - 1];
	
	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 evtV1cfgNiveauGravite called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(*(int*)(var_val) != 1)			//1 : indetermine
					&&	(*(int*)(var_val) != 2)			//2 : critique
					&&	(*(int*)(var_val) != 3)			//2 : majeur
					&&	(*(int*)(var_val) != 4)			//2 : mineur
					&&	(*(int*)(var_val) != 5)			//2 : avertissement
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION evtV1cfgNiveauGravite called %d\n",loc_s32_iindex));
				//On recherche index de l'evt (car loc_s32_iindex = num�ro de l'�vt)
				loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);
//				DEBUGMSGTL(("sodielec", "loc_u16_indEvt= %d\n",loc_u16_indEvt));
				if(US_INDICE_NON_TROUVE != loc_u16_indEvt)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
					if(TRUE == u8FillConfigTabEvt(&s_cfg_tempo_snmpd))
					{
						s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u8_niveau_gravite = (u8sod)(*(int*)(var_val) - 1);
						if(TRUE==u8TestConfigTabEvt(&s_cfg_tempo_snmpd))
						{
							u8EditConfigTabEvt(&s_cfg_tempo_snmpd);
							CopyConfigTabEvt(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
						}
					}
					s32Lock_Release(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on relache le sem
				}
				else
				{
//					DEBUGMSGTL(("sodielec", "ACTION evtV1cfgNiveauGravite: KO loc_s32_iindex=%d\n",loc_s32_iindex));
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
//	DEBUGMSGTL(("sodielec", "return evtV1cfgNiveauGravite %d\n",loc_s32_return));

	return loc_s32_return;
}

int
   write_evtV1cfgAction(int action,
						u_char * var_val,
						u_char var_val_type,
						size_t var_val_len,
						u_char * statP,
						oid * name,
						size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;
	s32sod	loc_s32_iindex;
	u16sod	loc_u16_indEvt;
	
	loc_s32_iindex = name[name_len - 1];
	
	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 evtV1cfgAction called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(*(int*)(var_val) != 1)			//1 : off
					&&	(*(int*)(var_val) != 2)			//2 : on
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				//On recherche index de l'evt (car loc_s32_iindex = num�ro de l'�vt)
				loc_u16_indEvt = u16RechercheIndiceEvt((u16sod)loc_s32_iindex);
				if(US_INDICE_NON_TROUVE != loc_u16_indEvt)
				{
					s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
					if(TRUE == u8FillConfigTabEvt(&s_cfg_tempo_snmpd))
					{
						if (1 == *(int*)(var_val)) // off(1)
						{
							ResetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_TRAP);
						}
						else
						{
							SetEventAction(&s_cfg_tempo_snmpd.s_tabevt.s_event[loc_u16_indEvt].u16_action, ACTION_EVT_TRAP);
						}
						
						if(TRUE==u8TestConfigTabEvt(&s_cfg_tempo_snmpd))
						{
							u8EditConfigTabEvt(&s_cfg_tempo_snmpd);
							CopyConfigTabEvt(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
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
}

int
   write_evtV1PrototrapCycle(int action,
							 u_char * var_val,
							 u_char var_val_type,
							 size_t var_val_len,
							 u_char * statP,
							 oid * name,
							 size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;
	s32sod loc_s32_iindex;
	
	loc_s32_iindex = name[name_len - 1] - 1;
	
	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 evtV1PrototrapCycle called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(REEMISSION_TRAPV1_MIN <= *(int*)(var_val))
					&&	(*(int*)(var_val) <= REEMISSION_TRAPV1_MAX)
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
				DEBUGMSGTL(("sodielec", "ACTION evtV1PrototrapCycle called\n"));
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
				if(TRUE == u8FillConfigSnmp(&s_cfg_tempo_snmpd))
				{
					if(VERSION_SNMPV1 == s_cfg_tempo_snmpd.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
					{
						s_cfg_tempo_snmpd.s_snmp.s_trap_SNMPv1[loc_s32_iindex].u16_interval = (u16sod)*(int*)(var_val);
						if(TRUE==u8TestConfigSnmp(&s_cfg_tempo_snmpd))
						{
							u8EditConfigSnmp(&s_cfg_tempo_snmpd);
							CopyConfigSnmp(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
						}
						else
						{
							loc_s32_return = SNMP_ERR_WRONGVALUE;
						}
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
}

int
   write_evtV1PrototrapNombre(int action,
							  u_char * var_val,
							  u_char var_val_type,
							  size_t var_val_len,
							  u_char * statP,
							  oid * name,
							  size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod	loc_s32_sem;
	s32sod	loc_s32_iindex;

	loc_s32_iindex = name[name_len - 1] - 1;
	
	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 evtV1PrototrapNombre called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(REEMISSION_TRAPV1_MIN <= *(int*)(var_val))
					&&	(*(int*)(var_val) <= REEMISSION_TRAPV1_MAX)
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
				DEBUGMSGTL(("sodielec", "ACTION evtV1PrototrapNombre called\n"));
				s32Lock_Get(SEMAPHORE_BDD_CONFIG_EQPT, &loc_s32_sem);	//on l�ve le s�maphore
				if(TRUE == u8FillConfigSnmp(&s_cfg_tempo_snmpd))
				{
					if(VERSION_SNMPV1 == s_cfg_tempo_snmpd.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
					{
						s_cfg_tempo_snmpd.s_snmp.s_trap_SNMPv1[loc_s32_iindex].u16_nb_emission = (u16sod)*(int*)(var_val);
						if(TRUE==u8TestConfigSnmp(&s_cfg_tempo_snmpd))
						{
							u8EditConfigSnmp(&s_cfg_tempo_snmpd);
							CopyConfigSnmp(&s_cfg_tempo_snmpd, &s_config_process_snmpd);
						}
						else
						{
							loc_s32_return = SNMP_ERR_WRONGVALUE;
						}
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
}

int
   write_alarmeV1Acquit(int action,
						u_char * var_val,
						u_char var_val_type,
						size_t var_val_len,
						u_char * statP,
						oid * name,
						size_t name_len)
{
	s32sod loc_s32_return = SNMP_ERR_NOERROR; // INIT
	s32sod loc_s32_iindex;
	S_STRUCT_STA_TRAP		*loc_ps_trap;
	s32sod	loc_s32_sem;

	loc_ps_trap = NULL; //INIT
	loc_s32_iindex = name[name_len - 1] - 1;
	
	if (u8CheckClientSnmpAllowed()) {
		switch (action) {
			case RESERVE1:
				DEBUGMSGTL(("sodielec", "RESERVE1 alarmeV1Acquit called\n"));
				if (var_val_type != ASN_INTEGER) {
					snmp_log(LOG_ERR, "Value is not an integer\n");
					loc_s32_return = SNMP_ERR_WRONGTYPE;
				}
				if (var_val_len > sizeof(int)) {
					snmp_log(LOG_ERR, "Value has a bad length\n");
					loc_s32_return = SNMP_ERR_WRONGLENGTH;
				}
				if(		(*(int*)(var_val) != 1)			//1 : non-acquitter
					&&	(*(int*)(var_val) != 2)			//2 : acquitter
					&&	(*(int*)(var_val) != 3)			//3 : supprimer
				  )
				{
					loc_s32_return = SNMP_ERR_WRONGVALUE;
				}
				break;
				
			case ACTION:
				DEBUGMSGTL(("sodielec", "ACTION alarmeV1Acquit called\n"));
				if(VERSION_SNMPV1 == s_config_process_snmpd.s_snmp.u8_version_snmp) //CONDITION: uniquement SNMPv1
				{
					if(TRUE == u8Search_IdxStatusTrap((u16sod)loc_s32_iindex,&loc_ps_trap)) //CONDITION: on lit les donn�es de la ligne de la table
					{
						switch(*(int*)(var_val))
						{
							case 1:  //non-acquitter
								loc_ps_trap->u8_val_snmp = VAL_SNMP_NON_ACQUITTER;
								break;
							case 2: //acquitter
								if(loc_ps_trap->u32_cpt_emission_trap >= 1) //CONDITION: trap �mis au moins 1 fois
								{
									loc_ps_trap->u8_val_snmp = VAL_SNMP_ACQUITTER;
								}
								else
								{
									loc_s32_return = SNMP_ERR_WRONGVALUE;
								}
								break;
							case 3: //supprimer
								if(		(ETAT_EVT_DEBUT != loc_ps_trap->u8_etat_evt)
									&&	(loc_ps_trap->u32_cpt_emission_trap >= 1)
								  ) //CONDITION: on ne peut pas supprimer si l'�vt est � DEBUT ET trap �mis au moins 1 fois
								{
									loc_ps_trap->u8_val_snmp = VAL_SNMP_SUPPRIMER;
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
						loc_s32_return = SNMP_ERR_WRONGVALUE;
					}
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
}

