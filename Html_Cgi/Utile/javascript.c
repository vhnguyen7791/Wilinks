/*========================================================================*/
/* NOM DU FICHIER  : javascript.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 30/05/2007											  */
/* Libelle         : HTML CGI: fonctions javascripts génériques			  */
/* Projet          : WRM100                                               */
/* Indice          : BE014                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
// - Correction javascript concernant test mask IP
//BE003 22/12/2009 CM
// - Modification javascript isValidText
//		possibilité d'interdire la saisie de caractères espaces
//BE010 03/02/2010 CM
// - Correction test configuration des adresses IP des interfaces
//  --> vérification que l'adresse IP n'est pas une adresse nulle pour le masque de sous-réseau défini
//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
// Module qui contient toutes les fonctions de javascript

/*_____II - DEFINE SBIT __________________________________________________*/
#define _JAVASCRIPT

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: JSActualiser
// Entrees		: <pc_nomPageHtml<
// Sortie		: rien
// Auteur		: CM - 13/04/2004 -
// Description	: fonction utilisée pour actualiser à partir de HomeB la page HTML
//=====================================================================================
void JSActualiser(char *pc_nomPageHtml)
{
	html_tag("<SCRIPT language=JavaScript> \n");	//Pour la fonction Actualiser
	html_tag("		 var FileName=\"%s\"; \n",pc_nomPageHtml);
	html_tag("</SCRIPT> \n");
	
}/*JSActualiser*/

//=====================================================================================
// Fonction		: JSNumCheck
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2004 -
// Description	: Javascript pour tester des valeurs numériques
//=====================================================================================
void JSNumCheck(void)
{
	html_tag("<SCRIPT language=JavaScript> \n");	//Pour la fonction Actualiser

	//function isFloat(tBox, nMin, nMax)
	html_tag("function isFloat(tBox, nMin, nMax) \n"
			 "{ \n"
			 "	var val = Number(tBox.value) \n"
			 " \n"
			 "	    if ( isNaN(val) == true ) \n"
			 "		{ \n");
	html_tag("			alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cette_valeur_dt_etre_nombre);
	html_tag("			tBox.value = tBox.defaultValue; \n"
			 "			return false; \n"
			 "		} \n"
			 "		if (val < nMin) \n"
			 "		{ \n");
	html_tag("			alert(\"%s \" + nMin + \".\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cette_valeur_dt_etre_sup_egale);
	html_tag("			tBox.value = tBox.defaultValue; \n"
			 "			return false; \n"
			 "		} \n"
			 "		if (val > nMax) \n"
			 "		{ \n");
	html_tag("			alert(\"%s  \" + nMax + \".\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cette_valeur_dt_etre_inf_egale);
	html_tag("			tBox.value = tBox.defaultValue; \n"
			 "			return false; \n"
			 "		} \n"
			 "		return true; \n"
			 "	} \n");

	//function isInteger(tBox, nMin, nMax)		 
	html_tag("function isInteger(tBox, nMin, nMax) \n"
			 "{ \n"
			 "	var re = /\\./; \n"

			 // First check bounds and if it's a number. isFloat does this.
			 "	 if ( !isFloat(tBox, nMin, nMax) ) \n"
			 "	 { \n"
			 "		 return false; \n"
			 "	 } \n"

			// Then check if it's an int.
			 "	 if (-1 != tBox.value.search(re)) \n"
			 "	 { \n");
	html_tag("		 alert(\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cette_valeur_dt_etre_entier);
	html_tag("		 tBox.value = tBox.defaultValue; \n"
			 "		 return false; \n"
			 "	 } \n"

			 "	 return true; \n"
			 "} \n");

	//function isFloatDecimale(tBox, nMin, nMax, nPas)
	html_tag("function isFloatDecimale(tBox, nMin, nMax, nPas) \n"
			 "{ \n"
			 "	var re = /\\./; \n"
			 "  var temp; \n"
			 "  var temp_arrondie;  \n"
			 "  var resultat;  \n"

			 // First check bounds and if it's a number. isFloat does this.
			 "	 if ( !isFloat(tBox, nMin, nMax) ) \n"
			 "	 { \n"
			 "		 return false; \n"
			 "	 } \n"

			 "	temp = tBox.value; \n"
			 "	 temp_arrondie = Math.round(temp*nPas)/nPas; \n"
			 "	 resultat = temp_arrondie-temp; \n"
			 "	 if(resultat!=0) \n"
			 "	 { \n"
			 "		 tBox.value = temp; \n");
	html_tag("		 alert(\"%s \" + 1/nPas); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cette_valeur_dt_etre_nombre_avec_pas_de);
	html_tag("		 tBox.value = tBox.defaultValue; \n"
			 "		 return false; \n"
			 "	 } \n"

			 "	 tBox.value = temp;\n"

			 "	 return true; \n"
			 "} \n");

	//function isIntegerMultiple(tBox, nMin, nMax, nPas) avec nPas > 1
	html_tag("function isIntegerMultiple(tBox, nMin, nMax, nPas) \n"
			 "{ \n"
			 "	var re = /\\./; \n"
			 "  var temp; \n"
			 "  var temp_arrondie;  \n"
			 "  var resultat;  \n"

			 // First check bounds and if it's a number. isFloat does this.
			 "	 if ( !isInteger(tBox, nMin, nMax) ) \n"
			 "	 { \n"
			 "		 return false; \n"
			 "	 } \n"

			 "	 temp = tBox.value/nPas; \n"
			 "	 temp_arrondie = Math.round(temp); \n"
			 "	 resultat = temp_arrondie-temp; \n"
			 "	 if(resultat!=0) \n"
			 "	 { \n"
			 "		 alert(\"%s \" + nPas); \n"
			 "		 tBox.value = temp_arrondie*nPas; \n"
			 "		 return false; \n"
			 "	 } \n"

			 "	 return true; \n"
			 "} \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_cette_valeur_dt_etre_nombre_avec_pas_de);
	
	html_tag("</SCRIPT> \n");

}/*JSNumCheck*/

//=====================================================================================
// Fonction		: JSIPCheck
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2004 -
// Description	: Javascript pour tester les adresses IP
//=====================================================================================
void JSIPCheck(void)
{
	html_tag("<SCRIPT language=JavaScript> \n");

	//function mem(seek, arr)
	html_tag("function mem(seek, arr) \n"
	"{ \n"
	"	for(var n = 0; n < arr.length; n++) \n"
	"		if(arr[n] == seek) \n"
	"			return n; \n"

	"	return -1; \n"
	"} \n");



	//function validMaskHelp(box)
//d: BE000 24/09/09 CM - Correction javascript concernant test mask IP
//	html_tag("function validMaskHelp(box) \n"
	html_tag("function validMaskHelp(box, flag_test_mask) \n"
//f: BE000 24/09/09 CM - Correction javascript concernant test mask IP
			"{ \n"
			"	var str, arr, n; \n"

			"	str = box.value; \n"

			"	str = new String(str); \n"

			"	arr = str.split(\".\"); \n"

			"	if(arr.length != 4) \n"
			"		return false; \n"

			"	var i, res, ok = true; \n"

			"	for(n = 0; n < 4; n++) \n"
			"	{ \n"
			"		i = Number(arr[n]); \n"

			 "		if (isNaN(i) == true ) \n"
			"			return false; \n"

			"		res = mem(i, [255, 254, 252, 248, 240, 224, 192, 128, 0]); \n"
			"		if( res >= 0) \n"
			"		{ \n"
			"			if(ok) \n"
			"				ok = res == 0; \n"
			"			else \n"
			"				if(res != 8) \n"
			"					return false; \n"
			"		} \n"
			"		else \n"
			"		{ \n"
			"			return false; \n"
			"		} \n"
			"	} \n"

			 //On interdit la saisie d'un masque de 0.0.0.0
			 "	if(0 == Number(arr[0])) \n"//Interdiction de saisir adresse IP 0.0.0.0
			 "	{ \n"
			 "			return false; \n"
			 "	} \n"
			 
//d: BE000 24/09/09 CM - Correction javascript concernant test mask IP
			 "  if(true == flag_test_mask) \n"
			 "  { \n"
//f: BE000 24/09/09 CM - Correction javascript concernant test mask IP
			 //On interdit la saisie d'un masque de 255.255.255.255
			"		if(255 == Number(arr[3])) \n"//Interdiction de saisir adresse IP 255.255.255.255
			"		{ \n"
			"			return false; \n"
			"		} \n"
//d: BE000 24/09/09 CM - Correction javascript concernant test mask IP
			"	} \n"
//f: BE000 24/09/09 CM - Correction javascript concernant test mask IP
			 
			"	return true; \n"
			"} \n");

	//function validAddr(box, flag_test_adresseIp_nulle)
	html_tag("function validAddr(box, flag_test_adresseIp_nulle) \n"
			 "{ \n"
			 "	if(validAddrHelp(box, flag_test_adresseIp_nulle)) \n"
			 "		return true; \n"

			"	alert(\"'\" + box.value + \"' %s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_n_est_pas_adresse_valide);
	html_tag("	box.value = box.defaultValue; \n"
			"	return false; \n"
			"	} \n");

	//function validAddrHelp(box, flag_test_adresseIp_nulle)
	html_tag("function validAddrHelp(box, flag_test_adresseIp_nulle) \n"
			 "{ \n"
			 "	var arr, str; \n"

			 "	str = box.value; \n"
			 
			 "	str = new String(str); \n"

			 "	arr = str.split(\".\"); \n"

			 "	if(arr.length != 4) \n"
			 "		return false; \n"

			 "	var n, i; \n"

			 "	for(n = 0; n < 4; n++) \n"
			 "	{ \n"
			 "		i = Number(arr[n]); \n"

			 "		if(\"NaN\" == \"\"+i) \n"
			 "			return false; \n"

			 "		if( (i < 0) || (i > 255) ) \n"
			 "			return false; \n"
			 "	} \n"
			 "	if(true == flag_test_adresseIp_nulle) \n" //CONDITION: test adresse IP nulle autorisée
			 "	{ \n"
			 "		i = Number(arr[0]); \n"		//Interdiction de saisir adresse IP 0.0.0.0
			 "		if( (i < 1) || (i > 255) ) \n"
			 "		{ \n"
			 "				return false; \n"
			 "		} \n"
			 "	} \n"
  			 "	return true; \n"
			 "} \n");

	//function validMask(box)
//d: BE000 24/09/09 CM - Correction javascript concernant test mask IP
//	html_tag("function validMask(box) \n"
//			 "{ \n"
//			 "	if(validMaskHelp(box)) \n"
	html_tag("function validMask(box, flag_test_mask) \n"
			"{ \n"
			"	if(validMaskHelp(box, flag_test_mask)) \n"
//f: BE000 24/09/09 CM - Correction javascript concernant test mask IP
			"		return true; \n"

			"	alert(\"'\" + box.value + \"' %s\"); \n",
	pt_tb_msg[u8_html_langue].ps8_msg_n_est_pas_masque_valide);
	
	html_tag("	box.value = box.defaultValue; \n"
			 " return false; \n"
			 "} \n");

	//function validMulticast(box)
	html_tag("function validMulticast(box) \n"
			 "{ \n"
			 "	if(validMulticastHelp(box)) \n"
			 "		return true; \n"

			 "	alert(\"'\" + box.value + \"' %s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_n_est_pas_adresse_multicast_valide);
	html_tag("	box.value = box.defaultValue; \n"
			 "	return false; \n"
			 "	} \n");

	//function validMulticastHelp(box)
	html_tag("function validMulticastHelp(box) \n"
			 "{ \n"
			 "	var arr, str; \n"

			 "	str = box.value; \n"

			 "	str = new String(str); \n"

			 "	arr = str.split(\".\"); \n"

			 "	if(arr.length != 4) \n"
			 "		return false; \n"

			 "	var n, i; \n"

			 "	for(n = 0; n < 4; n++) \n"
			 "	{ \n"
			 "		i = Number(arr[n]); \n"

			 "		if(\"NaN\" == \"\"+i) \n"
			 "			return false; \n"
			 "		if( (i < 0) || (i > 255) ) \n"
			 "			return false; \n"
			 "	} \n"
			 "	i = Number(arr[0]); \n"		//Adresse multicast autorisée entre 224.0.0.0 et 239.255.255.255
			 "	if( (i < 224) || (i > 239) ) \n"
			 "	{ \n"
			 "			return false; \n"
			 "	} \n"
			 "	return true; \n"
			 "} \n");	
	html_tag(" \n");

	//function IPAddressToUnsignedInteger (valeur_box)
	//		Convert an IP address formatted string into an unsigned integer.
	//		Return null if the string is not formatted correctly. 
	//		In JavaScript all numbers are floating-point numbers. The range of
	//		integer is from -2**53 to 2**53.
	//		Examples are
	//		IPAddressToUnsignedInteger("255.255.255.255") = 4294836225
	//  	IPAddressToInteger("255.255.255.255") = -1  
	html_tag("function IPAddressToUnsignedInteger (valeur_box) \n");
	html_tag("{ \n");
	html_tag("	var str; \n");
	html_tag("	str = valeur_box; \n");
	html_tag("	s = new String(str);\n");
	html_tag("	var got = s.match (/^\\s*(\\d+)\\s*[.]\\s*(\\d+)\\s*[.]\\s*(\\d+)\\s*[.]\\s*(\\d+)\\s*$/);\n");
	html_tag("	if (got) {\n");
	html_tag("		var x = 0;\n");
	html_tag("		for (var i=1; i <= 4; i++)\n");
	html_tag("		{\n");
	html_tag("			var q = parseInt(got[i],10);\n");
	html_tag("			if (q < 0 || q > 255)\n");
	html_tag("			{\n");
	html_tag("				return null;\n");
	html_tag("			}\n");
	html_tag("			x = x * 256 + q;\n");
	html_tag("		}\n");
	html_tag("		return x;\n");
	html_tag("	}\n");
	html_tag("	else\n");
	html_tag("	{\n");
	html_tag("		return null;\n");
	html_tag("	}\n");
	html_tag("}\n");
	html_tag(" \n");

	//function validateMACAddress(box)
	//	Return 1 if the string is a valid MAC address, else return 0 and give an
	//	error message.
	html_tag("function validateMACAddress (box) \n");
	html_tag("{ \n");
	html_tag("	var input_string = box.value; \n");
	html_tag("		input_string = new String (input_string); \n");
	html_tag("		var s = input_string; \n");
	html_tag("		s = s.replace (/[:-]/g,'');	 \n");	// Ignore the commonly used separator characters
	html_tag("		if (s.match (/^\\s*$/)) { \n"); //cas champ vide
	html_tag("			alert (\"'\" + input_string + \"' %s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_n_est_pas_adresse_mac_valide);
	html_tag("			box.value = box.defaultValue;  \n");
	html_tag("			return 0; \n");
	html_tag("		} \n");
	html_tag("		if (s.match (/^\\s*[0][0][0][0][0][0][0][0][0][0][0][0]\\s*$/)) { \n");
	html_tag("			alert (\"'\" + input_string + \"' %s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_n_est_pas_adresse_mac_valide);
	html_tag("			box.value = box.defaultValue;  \n");
	html_tag("			return 0; \n");
	html_tag("		} \n");
	html_tag("		if (!s.match (/^\\s*[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]\\s*$/)) { \n");
	html_tag("			alert (\"'\" + input_string + \"' %s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_n_est_pas_adresse_mac_valide);
	html_tag("			box.value = box.defaultValue;  \n");
	html_tag("			return 0; \n");
	html_tag("		} \n");
	html_tag("		return 1; \n");
	html_tag("	} \n");
	html_tag(" \n");

	//JsVerifyIP_Host()
	//	Vérifie si l'adresse IP de l'host est conforme au masque de sous-réseau
	html_tag("function JsVerifyIP_Host (subnet_ip, subnet_mask) \n");
	html_tag("{ \n");
	html_tag("		var loc_resultat = true; //init \n");
	html_tag("		var loc_ip = IPAddressToUnsignedInteger (subnet_ip); \n");
	html_tag("		var loc_mask = IPAddressToUnsignedInteger (subnet_mask); \n");
	html_tag("		if ((loc_ip==null) || (loc_mask==null)) \n");
	html_tag("		{ \n");
	html_tag("			loc_resultat = false; \n");
	html_tag("		} \n");
	html_tag("		else \n");
	html_tag("		{ \n");
	html_tag("			if (0 == (loc_ip & (~loc_mask))) \n"); //CONDITION: adresse IP saisie (de broadcast) non autorisée 
	html_tag("			{ \n");
	html_tag("				alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip_et_masque_non_valides);
	html_tag("				loc_resultat = false; \n");
	html_tag("			} \n");
	//Les traitements binaires se font avec un bit de signe en javascript, d'où le cast en s32sod
	html_tag("			if ((%ld) == (loc_ip | loc_mask)) \n",(s32sod)MASK_RESEAU_SUR_32); //CONDITION: adresse IP saisie (de diffusion) non autorisée
	html_tag("			{ \n");
	html_tag("				alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip_et_masque_non_valides);
	html_tag("				loc_resultat = false; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("		return loc_resultat; \n");
	html_tag("	} \n");
	html_tag(" \n");
	
	//JsVerifyIP_Subnet()
	//	Given a subnet (IP address and mask), test if another IP address is
	//	within the same subnet.
	html_tag("function JsVerifyIP_Subnet (subnet_ip, subnet_mask, ip_to_test) \n");
	html_tag("{ \n");
	html_tag("	var loc_resultat = true; //init \n");
	html_tag("	var loc_si = IPAddressToUnsignedInteger (subnet_ip); \n");
	html_tag("	var loc_sm = IPAddressToUnsignedInteger (subnet_mask); \n");
	html_tag("	var loc_ip = IPAddressToUnsignedInteger (ip_to_test); \n");
	html_tag("	if ((loc_si==null) || (loc_sm==null) || (loc_ip==null)) \n");
	html_tag("	{ \n");
	html_tag("		alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_adresse_ip_ou_masque_ou_passerelle_est_invalide);
	html_tag("		loc_resultat = false; \n");
	html_tag("	} \n");
	html_tag("	else \n");
	html_tag("	{ \n");
	html_tag("		if(loc_ip != 0) \n");
	html_tag("		{ \n");
	html_tag("			if ((loc_si & loc_sm) != (loc_ip & loc_sm)) \n"); //CONDITION: pas dans le meme sous-réseau
	html_tag("			{ \n");
	html_tag("				alert (\"%s\"); \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_la_passerelle_n_est_pas_dans_sous_reseau);
	html_tag("				loc_resultat = false; \n");
	html_tag("			} \n");
	html_tag("		} \n");
	html_tag("	} \n");
	html_tag("	return loc_resultat; \n");
	html_tag("} \n");
	html_tag(" \n");


	// JsGetSubnet()
	// 	return subnet from given subnet ip and subnet mask
	html_tag("function JsGetSubnet (subnet_ip, subnet_mask) \n");
	html_tag("{ \n");
	html_tag("	var loc_si = IPAddressToUnsignedInteger(subnet_ip); \n");
	html_tag("	var loc_sm = IPAddressToUnsignedInteger(subnet_mask); \n");
	html_tag("	return (loc_si & loc_sm); \n");
	html_tag("} \n");
	
	html_tag("</SCRIPT> \n");
	
}/*JSIPCheck*/


//=====================================================================================
// Fonction		: JSTextCheck
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 16/04/2004 -
// Description	: JavaScript pour tester texte
//=====================================================================================
void JSTextCheck(void)
{
	html_tag("<SCRIPT language=JavaScript> \n");

	//function isValidText(tBox, forbiddenSpace, allowEmpty)
	html_tag("function isValidText(tBox, forbiddenSpace, allowEmpty) \n"
			"{ \n"
			 "var loc_i_lg_chaine=tBox.value.length; \n"
			 "var loc_i_code_caract; \n"
			 "for(loc_i_i=0;loc_i_i<loc_i_lg_chaine;loc_i_i++) \n"
			 "{ \n"
			 "	loc_i_code_caract=tBox.value.charCodeAt(loc_i_i); \n" //retourne la valeur unicode du caractère lu
			 //ce unicode (codé sur 16 bits) doit etre compris dans la
			 //plage définie par la norme ISO 8859-1 (8 bits) (spécifiée dans la balise <head> des pages HTML)
			 "	if(	((%#X <= loc_i_code_caract) && (loc_i_code_caract <= %#X))\n"
			 "		&&	(%#X != loc_i_code_caract) \n"
			 "		&&	(%#X != loc_i_code_caract) \n"
			 "		&&	(%#X != loc_i_code_caract) \n"
			 "		&&	(%#X != loc_i_code_caract) \n"
			 "		&&	(%#X != loc_i_code_caract) \n"
			 "		&&	(%#X != loc_i_code_caract) \n"
			 "		&&	(!((%#X <= loc_i_code_caract) && (loc_i_code_caract <= %#X)))\n"
			 "	  ) \n"	//CONDITION caractère autorisé
			 "	{ \n"
			 "		; \n" //OK
			 "	} \n"
			 "	else \n"	//CONDITION: caractère non autorisé
			 "	{ \n"
			 "		loc_i_i = loc_i_lg_chaine + 1; \n"	//on sort
			 "		alert(\"%s\");  \n"
			 "		tBox.value = tBox.defaultValue;  \n"
			 "		return false;  \n"
			 "	} \n"
			 "} \n",
			 U8_CARACT_ASCII_AUTORISE_MIN, U8_CARACT_ASCII_AUTORISE_MAX,
			 U8_CARACT_ASCII_INTERDIT_GUILLEMENT,
			 U8_CARACT_ASCII_INTERDIT_POURCENTAGE,
			 U8_CARACT_ASCII_INTERDIT_ETNUMERIC,
			 U8_CARACT_ASCII_INTERDIT_APOSTROPHE,
			 U8_CARACT_ASCII_INTERDIT_BACKSLASH,
			 U8_CARACT_ASCII_INTERDIT_PIPE,
			 U8_CARACT_ASCII_INTERDIT_MIN, U8_CARACT_ASCII_INTERDIT_MAX,
			 pt_tb_msg[u8_html_langue].ps8_msg_js_caractere_non_valide);

	html_tag("	if(true == forbiddenSpace) \n"
			 "	{ \n"
			 "		if (-1 != tBox.value.search(\" \")) \n" //CONDITION: ESPACE trouvé
			 "		{ \n"
			 "			alert(\"%s\"); \n"
			 "		} \n"
			 "	} \n",
			pt_tb_msg[u8_html_langue].ps8_msg_js_caractere_espace_non_valide);
		
	html_tag("	if (\"\" == tBox.value) \n"
			"	{ \n"
			"		if (allowEmpty) \n"
			"		{ \n"
			"			tBox.value = \" \"; \n" // Otherwise this ctrl will not be submitted.
			"		} \n"
			"		else \n"
			"		{ \n"
			"			alert(\"%s\"); \n"
			"			tBox.value = tBox.defaultValue; \n"
			"			return false; \n"
			"		} \n"
			"	} \n"

			"	return true; \n"
			"} \n",
			 pt_tb_msg[u8_html_langue].ps8_msg_js_champs_ne_pt_etre_laisse_vide);


	//function replaceltgt(tStr)
	html_tag("function replaceltgt(tStr) \n"
	"{ \n"
	"	var lt = /\x3C/gi; \n"	// ASCII for "less-than".
	"	var gt = /\x3E/gi; \n"	// ASCII for "greater-than".

	"	tStr = tStr.replace(lt, \"&lt;\"); \n"
	"	tStr = tStr.replace(gt, \"&gt;\"); \n"

	"	return tStr; \n"
	"} \n");
	
	html_tag("</SCRIPT> \n");

}/*JSTextCheck*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: InitModuleJavaScript
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 13/04/2004 -
// Description	: Initialisation du module de JavaScript
//=====================================================================================
void InitModuleJavaScript(void)
{
}/*InitModuleJavaScript*/

