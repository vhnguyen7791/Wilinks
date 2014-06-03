/*========================================================================*/
/* NOM DU FICHIER  : mib_sodielecV2.c									  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 07/06/2007                                           */
/* Libelle         : NET-SNMP: MIB SODIELECV2							  */
/* Projet          : WRM100                                               */
/* Indice          : BE000                                                */
/*========================================================================*/
/* Historique      :                                                      */
/*========================================================================*/

/*_______II - DEFINE ______________________________________________________*/

/*_______III - INCLUDES - DIRECTIVES ______________________________________*/
#include "headers.h"
#include "mib_sodielecV2.h"
#include "mib_sodielecV2_data.h"


/*_______V   - VARIABLES GLOBALES __________________________________________*/
/** Declarations for old values in UNDO actions */
/** ** for MIB Tree       */

/** ** for Tables         */


/** OID Variables         */
/** ** for MIB Tree       */
oid sodielecV2_variables_oid[] = {1,3,6,1,4,1,9153,2};

/** This array structure defines a representation of the MIB being implemented */
/** magic number, variable type, ro/rw, callback fct, L, oidsuffix */
struct variable3 sodielecV2_variables[] = {
   {INFOCONSTRUCTEUR, ASN_OCTET_STR, RONLY, var_sodielecV2, 3, {2,1,1}},
   {INFOTELEPHONE, ASN_OCTET_STR, RONLY, var_sodielecV2, 3, {2,1,2}},
   {INFOSITE, ASN_OCTET_STR, RONLY, var_sodielecV2, 3, {2,1,3}},
};

/** ** for Tables         */


/*_______VI  - PROCEDURES __________________________________________________*/
/** Main Function */
/** called when SNMP is loaded */
void
init_mib_sodielecV2(void)
{
    DEBUGMSGTL(("sodielec", "init_mib_sodielecV2 called\n"));

/** Registration of MIB Tree and tables with the agent */
/** ** MIB Tree       */
REGISTER_MIB("sodielecV2", sodielecV2_variables, variable3,
               sodielecV2_variables_oid);

/** ** Tables         */

/* if necessary, data will be initialised here */
//initdata_mib_sodielecV2();

}


/** Header Functions for tables with CODE column */

/** Callback functions */
/** called whenever an incoming request refers to an object within this sub-tree */
/** ** for MIB Tree       */
u_char *
var_sodielecV2(struct variable *vp,
				oid * name,
				size_t * length,
				int exact,
				size_t * var_len,
				WriteMethod ** write_method)
{
   char *loc_ps8_cp;
   *write_method = 0;

//   DEBUGMSGTL(("sodielec", "var_sodielecV2 called\n"));
   if(MATCH_FAILED == header_generic(vp, name, length, exact, var_len, write_method))
	return NULL;

   if(ASN_OCTET_STR == vp->type) {
	loc_ps8_cp = (char *)(captureString_sodielecV2(vp->magic, write_method));
	*var_len = strlen(loc_ps8_cp);
	return (u_char *) loc_ps8_cp;
   }
   if(ASN_INTEGER == vp->type) {
	long_return = (long )(captureInt_sodielecV2(vp->magic, write_method));
	return (u_char *) &long_return;
   }
}

/** ** for Tables         */

/** Write functions */
/** ** for MIB Tree       */


/** ** for Tables         */
