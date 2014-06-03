/*========================================================================*/
/* NOM DU FICHIER  : cgivars.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 12/12/2005                                           */
/* Libelle         : HTML CGI:											  */
/* Projet          : WRM100                                               */
/* Indice          : BE024                                                */
/*========================================================================*/
/* Historique      :                                                      */
/* cgivars.c
 * (C) Copyright 2000, Moreton Bay (http://www.moretonbay.com).
 * see HTTP (www.w3.org) and RFC
 */
//BE000 24/09/2009 CM
// - CREATION
// - On remplace le caractère '+' par un espace ' '
//		(ici et non plus dans boa, à la différence de ce qui a été fait dans le sdvb200)
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define _CGIVARS

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

/* local function prototypes */
//=====================================================================================
// Fonction		: hex2char
// Entrees		: <loc_ps8_hex<
// Sortie		: 
// Auteur		: 
// Description	: 
//=====================================================================================
s8sod hex2char(s8sod *loc_ps8_hex);

//=====================================================================================
// Fonction		: unescape_url
// Entrees		: <loc_ps8_url<
// Sortie		: 
// Auteur		: 
// Description	: 
//=====================================================================================
void unescape_url(s8sod *loc_ps8_url);



//=====================================================================================
// Fonction		: hex2char
// Entrees		: <loc_ps8_hex<
// Sortie		: 
// Auteur		: 
// Description	: 
//=====================================================================================
s8sod hex2char(s8sod *loc_ps8_hex)
{
	s8sod loc_s8_char_value;
	loc_s8_char_value = (loc_ps8_hex[0] >= 'A' ? ((loc_ps8_hex[0] & 0xdf) - 'A') + 10 : (loc_ps8_hex[0] - '0'));
	loc_s8_char_value *= 16;
	loc_s8_char_value += (loc_ps8_hex[1] >= 'A' ? ((loc_ps8_hex[1] & 0xdf) - 'A') + 10 : (loc_ps8_hex[1] - '0'));
	return loc_s8_char_value;
}/*hex2char*/

//=====================================================================================
// Fonction		: unescape_url
// Entrees		: <loc_ps8_url<
// Sortie		: 
// Auteur		: 
// Description	: 
//=====================================================================================
void unescape_url(s8sod *loc_ps8_url)
{
	s32sod loc_s32_n, loc_s32_k;

	for(loc_s32_n=0, loc_s32_k=0;(loc_ps8_url[loc_s32_k] != 0);++loc_s32_n, ++loc_s32_k)
	{
		if((loc_ps8_url[loc_s32_n] = loc_ps8_url[loc_s32_k]) == '%')
		{
			loc_ps8_url[loc_s32_n] = hex2char(&loc_ps8_url[loc_s32_k+1]);
			loc_s32_k += 2;
		}
	}
	loc_ps8_url[loc_s32_n] = '\0';
}/*unescape_url*/


//=====================================================================================
// Fonction		: getRequestMethod
// Entrees		: rien
// Sortie		: <form_method> (CGIFORM_METHOD_GET or CGIFORM_METHOD_POST) on success,	-1 on failure.
// Auteur		: 
// Description	: 
//=====================================================================================
int getRequestMethod()
{
	char *request_method;
	int form_method;

	request_method = getenv("REQUEST_METHOD");
	form_method = -1; //INIT
	if(NULL == request_method)
	{
		form_method = -1;
	}
	else
	{
		if (!strcmp(request_method, "GET") || !strcmp(request_method, "HEAD") ) {
			form_method = CGIFORM_METHOD_GET;
		} else if (!strcmp(request_method, "POST")) {
			form_method = CGIFORM_METHOD_POST;
		} else {
			/* wtf was it then?!! */
			form_method = -1;
		}
	}
	return form_method;
}/*getRequestMethod*/

//=====================================================================================
// Fonction		: getGETvars
// Entrees		: rien
// Sortie		: <getvars<
// Auteur		: 
// Description	: 
//=====================================================================================
s8sod **getGETvars()
{
	int i;
	s8sod **getvars;
	s8sod *getinput;
	s8sod **pairlist;
	int paircount = 0;
	s8sod *nvpair;
	s8sod *eqpos;
	//	char *pc_x;//debug


	//	pc_x = (char *)( ADRESSE_BSE_DEBUG);
	getinput = getenv("QUERY_STRING");
	if (getinput)
	{
		getinput = strdup(getinput);//duplique la chaine (utilisation de malloc!)
	}

	//On remplace les caractères '+' par des espaces
	if(NULL != getinput)
	{
		for(i=0; (NULL != getinput)&&(getinput[i] != 0); i++)
		{
			if('+' == getinput[i])
			{
				getinput[i] = ' ';
			}
		}		
	}
	
	pairlist = (s8sod **) malloc(256*sizeof(s8sod **));
	paircount = 0;
	nvpair = getinput ? strtok(getinput, "&") : NULL;
	while (nvpair) {
		pairlist[paircount++]= strdup(nvpair);
		if(!(paircount%256))
			pairlist = (s8sod **) realloc(pairlist,(paircount+256)*sizeof(s8sod **));
		nvpair = strtok(NULL, "&");
	}

	pairlist[paircount] = 0;
	getvars = (s8sod **) malloc((paircount*2+1)*sizeof(s8sod **));
	for (i= 0; i<paircount; i++) {
		if((eqpos=strchr(pairlist[i], '='))!=NULL) {
			*eqpos = '\0';
			unescape_url(getvars[i*2+1] = strdup(eqpos+1));
		} else {
			unescape_url(getvars[i*2+1] = strdup(""));
		}
		unescape_url(getvars[i*2] = strdup(pairlist[i]));
	}
	getvars[paircount*2] = 0;
	for(i=0;pairlist[i];i++)
	{
		free(pairlist[i]);
	}
	free(pairlist);
	if (getinput)
	{
		free(getinput);
	}
	return getvars;
}/*getGETvars*/

//=====================================================================================
// Fonction		: getPOSTvars
// Entrees		: rien
// Sortie		: <postvars<
// Auteur		: 
// Description	: 
//=====================================================================================
s8sod **getPOSTvars()
{
	int i;
	int content_length;
	s8sod **postvars;
	s8sod *postinput;
	s8sod **pairlist;
	int paircount = 0;
	s8sod *nvpair;
	s8sod *eqpos;

	postinput = getenv("CONTENT_LENGTH");
	if (!postinput)
	{
		exit(1);
	}
	if(!(content_length = atoi(postinput)))
	{
		exit(1);
	}
	if(!(postinput = (s8sod *) malloc(content_length+1)))
	{
		exit(1);
	}
	if (!fread(postinput, content_length, 1, stdin))
	{
		exit(1);
	}
	postinput[content_length] = '\0';
	//modif{
	//CgiCom_SendDbgMsgToApp(postinput);
	//modif1}
	for(i=0;(postinput[i] != 0);i++)
	{
		if('+' == postinput[i])
		{
			postinput[i] = ' ';
		}
	}

	pairlist = (s8sod **) malloc(256*sizeof(s8sod **));
	paircount = 0;
	nvpair = strtok(postinput, "&");
	while (nvpair) {
		pairlist[paircount++] = strdup(nvpair);
		if(!(paircount%256))
		{
			pairlist = (s8sod **) realloc(pairlist, (paircount+256)*sizeof(s8sod **));
		}
		nvpair = strtok(NULL, "&");
	}

	pairlist[paircount] = 0;
	postvars = (s8sod **) malloc((paircount*2+1)*sizeof(s8sod **));
	for(i = 0;i<paircount;i++) {
		if((eqpos = strchr(pairlist[i], '='))!=NULL) {
			*eqpos= '\0';
			unescape_url(postvars[i*2+1] = strdup(eqpos+1));
		} else {
			unescape_url(postvars[i*2+1] = strdup(""));
		}
		unescape_url(postvars[i*2]= strdup(pairlist[i]));
	}
	postvars[paircount*2] = 0;

	for(i=0;pairlist[i];i++)
	{
		free(pairlist[i]);
	}
	free(pairlist);
	free(postinput);

	return postvars;
}/*getPOSTvars*/

//=====================================================================================
// Fonction		: s32CleanUp
// Entrees		: 
// Sortie		: 
// Auteur		: 
// Description	: free the mallocs
//=====================================================================================
s32sod s32CleanUp(s32sod loc_s32_form_method, s8sod **loc_pps8_getvars, s8sod **loc_pps8_postvars)
{
	s32sod loc_s32_i;

	if (loc_pps8_postvars) {
		for(loc_s32_i=0;loc_pps8_postvars[loc_s32_i];loc_s32_i++)
		{
			free(loc_pps8_postvars[loc_s32_i]);
		}
		free(loc_pps8_postvars);
	}
	if (loc_pps8_getvars) {
		for(loc_s32_i=0;loc_pps8_getvars[loc_s32_i];loc_s32_i++)
		{
			free(loc_pps8_getvars[loc_s32_i]);
		}
		free(loc_pps8_getvars);
	}

	return 0;
}/*s32CleanUp*/

//=====================================================================================
// Fonction		: s32GetArgNb
// Entrees		: <loc_pps8_postvars<
// Sortie		: <loc_s32_Idx>
// Auteur		: 
// Description	: free the mallocs
//=====================================================================================
s32sod s32GetArgNb(s8sod **loc_pps8_postvars)
{
	s32sod loc_s32_Idx=0;
	if(loc_pps8_postvars)
	{
		while(loc_pps8_postvars[loc_s32_Idx])
		{
			loc_s32_Idx++;
		}
	}
	return(loc_s32_Idx);
}/*s32GetArgNb*/

/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/


