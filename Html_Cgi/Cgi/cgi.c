/*========================================================================*/
/* NOM DU FICHIER  : cgi.c												  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 12/12/2005                                           */
/* Libelle         : HTML CGI: Gestion des pages HTML dynamiques          */
/* Projet          : WRM100                                               */
/* Indice          : BE060                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE060 16/03/2011
// - Correction bug au démarrage de l'équipement accès HTTP à des données pas encore initialisées
/*========================================================================*/


/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/
#define CGI_MAIN 1

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../services.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u16Cgi_GetPageIdx
// Entrees		: <loc_ps8_Url<
// Sortie		: <loc_u16_Idx>
// Auteur		: 
// Description	: 
//=====================================================================================
u16sod u16Cgi_GetPageIdx(s8sod *loc_ps8_Url);



//=====================================================================================
// Fonction		: main
// Entrees		: 
// Sortie		: 
// Auteur		: 
// Description	: PROCESSUS
//=====================================================================================
int main() 
{
	s8sod		**loc_p_postvars = NULL; /* POST request data repository */
	s8sod		**loc_p_getvars = NULL; /* GET request data repository */
	s8sod		**loc_p_varlist = NULL; /* Page input parameter */
	s32sod		loc_s32_form_method; /* POST = 1, GET = 0 */
	u16sod		loc_u16_no_page;
	s8sod		 *loc_ps8_UrlPtr = NULL;
	FILE	*loc_p_handle;

	loc_p_handle = NULL; //INIT

	//-----------------------------------------------
	//Fin d'initialisation de la bdd ?
	//-----------------------------------------------
	if(NULL != (loc_p_handle = fopen( FILE_INITBDD_ON, "r" ))) //CONDITION: fichier présent
	{
		//fermeture du fichier
		fclose (loc_p_handle);
		//on sort tout de suite
		exit(0);
	}
	
	//init diverses
	InitModule_Bdd_Html();
	
	//recuperation de la methode et des parametres
	loc_s32_form_method = getRequestMethod();
	
	if(CGIFORM_METHOD_POST == loc_s32_form_method)
	{
		loc_p_postvars = getPOSTvars();
		loc_p_varlist = loc_p_postvars;
	}
	else
	{ 
		if(CGIFORM_METHOD_GET == loc_s32_form_method)
		{
			loc_p_getvars = getGETvars();
			loc_p_varlist = loc_p_getvars;
		}
	}
	if(loc_p_varlist)
	{
		if(!strcmp(loc_p_varlist[0],"URL")) 
		{
			loc_ps8_UrlPtr = loc_p_varlist[1];
		}
	}
	
	//recherche de la page correspondante
	loc_u16_no_page = u16Cgi_GetPageIdx(loc_ps8_UrlPtr);
	
	//construction de la page
	if (0 == loc_u16_no_page)
	{
		PageWarning(loc_p_varlist, loc_s32_form_method); 
	}
	else
	{
		//  on lance la creation
		(*t_menu_table[loc_u16_no_page].Fct) (loc_p_varlist, loc_s32_form_method);
	}
	
	//liberation memoire
	s32CleanUp(loc_s32_form_method, loc_p_getvars, loc_p_postvars);
	fflush(stdout);
	
	exit(0);
	
}

//=====================================================================================
// Fonction		: u16Cgi_GetPageIdx
// Entrees		: <loc_ps8_Url<
// Sortie		: <loc_u16_Idx>
// Auteur		: 
// Description	: 
//=====================================================================================
u16sod u16Cgi_GetPageIdx(s8sod *loc_ps8_Url)
{
	u16sod loc_u16_Idx;
	
	for(loc_u16_Idx=0;t_menu_table[loc_u16_Idx].Fct != NULL;loc_u16_Idx++)
	{
		if(!strcmp(loc_ps8_Url,t_menu_table[loc_u16_Idx].ps8_PageName)) 
		{
			break;
		}
	}
	
	if (NULL == t_menu_table[loc_u16_Idx].Fct)
	{ //page pas trouve!
		loc_u16_Idx = 0;
	}
	
	return(loc_u16_Idx);
}/*u16Cgi_GetPageIdx*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/
