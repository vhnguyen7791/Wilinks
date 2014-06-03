/*========================================================================*/
/* NOM DU FICHIER  : bddfile.c   		                                  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 24/09/2009                                           */
/* Libelle         : Base de données: gestion des fichiers de la BDD	  */
/* Projet          : WRM100                                               */
/* Indice          : BE061                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 24/09/09 CM
// - CREATION
//BE006 20/01/2010 CM
// - Modification gestion couche basse base de données de fichiers
//BE010 03/02/2010 CM
// - Correction BUG lecture fichier avec variable dans tableau de type string contenant des espaces
//	--> les espaces ne sont pas pris en compte à la lecture du contenu du fichier
//BE013 26/02/2010 CM
// - Ajout type FTYPVAL_DATE dans gestion des fichiers
// - Ajout fonction lecture / écriture dans fichier ligne par ligne
//BE014 08/03/2010 CM
// - Ajout option compilation "-Wall" + correction w@rning
//BE017 12/03/2010 CM
// - Ajout structure simple dans gestion bddfile
//BE024 03/04/2010 CM
// - Correction suite revue de codage de Caf (sur BE023)
//BE060 16/03/2011
// - Ajout nouveau type dans gestion bdd/file
//BE061 10/05/2011
// - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
//BE061 10/05/2011
// - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
//BE063.0 06/10/2011
// - gestion des lignes de commentaires dans les fichiers, utilise le caractere # comme delimiteur
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
#warning "REVOIR commentaires revue_codage de Caf"

/*_____II - DEFINE SBIT __________________________________________________*/
#define _BDDFILE

#define NB_MAX_VAL_SSCANF	10

//d: BE061 10/05/2011 - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
#define SIGNAL_ERROR_Si_CHAMP_INCONNU	0
//f: BE061 10/05/2011 - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

#include "arpa/inet.h" //pour la fonction inet_addr, pour WRM, mais sur Wilinks on utilise u32DecodageAdresseReseau

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//Une ligne du fichier est constitué du champs nom + champs valeur
static s8sod	ps8_champ_nom[TAILLE_MAX_LIGNE_BDDFILE+1];
static s8sod	ps8_champ_valeur[TAILLE_MAX_LIGNE_BDDFILE+1];

//Champs Nom + valeur associé à une structure de type "complexe"
static s8sod	ps8_cmplxligne[TAILLE_MAX_LIGNE_BDDFILE+1];
static s8sod	ps8_cmplxnom[TAILLE_MAX_LIGNE_BDDFILE+1];
static s8sod	ps8_cmplxval[TAILLE_MAX_LIGNE_BDDFILE+1];

static s8sod	ps8_ligne_tempo[TAILLE_MAX_LIGNE_BDDFILE+1];

static s8sod	ps8_ligne_bddfile[TAILLE_MAX_LIGNE_BDDFILE+1];
static u16sod	u16_checksum_calcule_fileRd;
static u16sod	u16_checksum_read_fileRd;
static u16sod	u16_checksum_calcule_fileWr;

static s8sod	ps8_valeur_tempo[TAILLE_MAX_LIGNE_BDDFILE+1];

/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: func_u16CalculChecksum
// Entrees		: <loc_ps8_chaine<	    : pointeur de la chaine de caractères
//				  <loc_u16_taille_max>	: taille max estimée de la chaîne 
// Sortie		: <loc_u16_checksum<	: checksum de la chaine
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui calcule le checksum d'une chaine de caractère
//=====================================================================================
u16sod func_u16CalculChecksum(s8sod *loc_ps8_chaine, u16sod loc_u16_taille_max);

//=====================================================================================
// Fonction		: func_u8IsFieldChecksumBddFile
// Entrees		: <loc_ps8_chaine< : nom du champ
// Sortie		: <loc_u8_resultat>: (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Test si le champs est celui du checksum du fichier
//=====================================================================================
u8sod func_u8IsFieldChecksumBddFile(s8sod	*loc_ps8_chaine);

//=====================================================================================
// Fonction		: func_u8IsFieldChecksumBddFile
// Entrees		: <loc_ps8_chaine< : nom du champ
// Sortie		: <loc_u8_resultat>: (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Test si le champs est celui du checksum du fichier
//=====================================================================================
u8sod func_u8IsFieldChecksumBddFile(s8sod	*loc_ps8_chaine)
{
	u8sod	loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(0 == strcmp(loc_ps8_chaine, CH_BDDFILECHECKSUM))
	{
		loc_u8_resultat = TRUE;
	}

	return loc_u8_resultat;
}/*func_u8IsFieldChecksumBddFile*/

//=====================================================================================
// Fonction		: func_u16CalculChecksum
// Entrees		: <loc_ps8_chaine<	    : pointeur de la chaine de caractères
//				  <loc_u16_taille_max>	: taille max estimée de la chaîne 
// Sortie		: <loc_u16_checksum<	: checksum de la chaine
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui calcule le checksum d'une chaine de caractère
//=====================================================================================
u16sod func_u16CalculChecksum(s8sod *loc_ps8_chaine, u16sod loc_u16_taille_max)
{
	u16sod	loc_u16_i;
	u16sod	loc_u16_checksum;

	loc_u16_checksum = 0;	//INIT
	for(loc_u16_i=0;((loc_u16_i<(u16sod)strlen(loc_ps8_chaine))&&(loc_u16_i<loc_u16_taille_max));loc_u16_i++)
	{
		loc_u16_checksum += (u16sod)loc_ps8_chaine[loc_u16_i];
//		MACRO_PRINTF(("\nchecksum calculé:%d (%d)",loc_u16_checksum,(u16sod)loc_ps8_chaine[loc_u16_i]));
	}

	return loc_u16_checksum;
}/*func_u16CalculChecksum*/

//=====================================================================================
// Fonction		: u8PrintFieldValueSimple
// Entrees		: <loc_ps_one_field< : pointeur sur un champs du fichier
//				  <loc_pt_variable<	: pointeur sur variable de la structure
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui édite le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8PrintFieldValueSimple(T_STRUCT_FILE_FIELD *loc_ps_one_field, void *loc_pt_variable)
{
	u8sod	loc_u8_resultat;
	s32sod	loc_s32_numwritten;
	u16sod	loc_u16_i;
	s8sod	loc_ps8_mot_hexa[10+1];

	loc_u8_resultat = TRUE;	//INIT
	loc_s32_numwritten = 0; //INIT
	strcpy(ps8_ligne_tempo, ""); //RAZ
	strcpy(loc_ps8_mot_hexa, "");	//RAZ

	//Revue_caf - 07/04/10 - CETTE REMARQUE VAUT POUR TOUS LES SPRINTF - Info : sprintf : 1er paramètre ps8_ligne_tempo "doit être assez grande pour recevoir le résultat" (p248 du langage C) -- le tester par rapport à TAILLE_MAX_LIGNE_BDDFILE??????
	//Réponse: loc_ps_one_field->ps8_nom est défini par le développeur (à lui à ne pas définir nom trop grand)

	switch(loc_ps_one_field->u8_type_valeur)
	{
		case FTYPVAL_STRING:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%s",
										 loc_ps_one_field->ps8_nom,
										 (s8sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_U8SOD:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%d",
										 loc_ps_one_field->ps8_nom,
										 *(u8sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_S8SOD:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%d",
										 loc_ps_one_field->ps8_nom,
										 *(s8sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_U16SOD:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%d",
										 loc_ps_one_field->ps8_nom,
										 *(u16sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_S16SOD:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%d",
										 loc_ps_one_field->ps8_nom,
										 *(s16sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_U32SOD:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%lu",
										 loc_ps_one_field->ps8_nom,
										 *(u32sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_S32SOD:
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%ld",
										 loc_ps_one_field->ps8_nom,
										 *(s32sod *)(loc_pt_variable) );
			break;
		case FTYPVAL_ADR_MAC: //adresse MAC
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%02X:%02X:%02X:%02X:%02X:%02X",
										 loc_ps_one_field->ps8_nom,
										 ((u8sod *)(loc_pt_variable))[0],
										 ((u8sod *)(loc_pt_variable))[1],
										 ((u8sod *)(loc_pt_variable))[2],
										 ((u8sod *)(loc_pt_variable))[3],
										 ((u8sod *)(loc_pt_variable))[4],
										 ((u8sod *)(loc_pt_variable))[5]);
			break;					
		case FTYPVAL_DATE: //date
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%04d/%02d/%02d %02d:%02d:%02d",
										 loc_ps_one_field->ps8_nom,
										 ((u16sod)(((S_STRUCT_DATE *)loc_pt_variable)->u16_annee)),
										 ((u8sod)(((S_STRUCT_DATE *)loc_pt_variable)->u8_mois)),
										 ((u8sod)(((S_STRUCT_DATE *)loc_pt_variable)->u8_jour)),
										 ((u8sod)(((S_STRUCT_DATE *)loc_pt_variable)->u8_heure)),
										 ((u8sod)(((S_STRUCT_DATE *)loc_pt_variable)->u8_minute)),
										 ((u8sod)(((S_STRUCT_DATE *)loc_pt_variable)->u8_seconde)));
			break;
		case FTYPVAL_TABU8_HEXA:
			//Construction du champs valeur
			strcpy(ps8_valeur_tempo, "");	//RAZ
			for(loc_u16_i=0; (loc_u16_i<loc_ps_one_field->u16_taille_elt);loc_u16_i++)
			{
				sprintf(loc_ps8_mot_hexa, "%02X", ((u8sod *)(loc_pt_variable))[loc_u16_i]);
				strcat(ps8_valeur_tempo, loc_ps8_mot_hexa);
			}
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%s",
										 loc_ps_one_field->ps8_nom,
										 ps8_valeur_tempo);
			break;
//d: BE063.0 06/10/2011
		case FTYPVAL_COMMENT: //ligne de commentaire
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "# %s",
										 loc_ps_one_field->ps8_nom);			
			break;
		case FTYPVAL_ADDIP: //adresse IP  en notation pointee
			loc_s32_numwritten = sprintf(ps8_ligne_tempo, "%s=%d.%d.%d.%d",
										 loc_ps_one_field->ps8_nom,
										 (int)(*(u32sod *)(loc_pt_variable)>>24)&0x000000FF,
										 (int)(*(u32sod *)(loc_pt_variable)>>16)&0x000000FF,
										 (int)(*(u32sod *)(loc_pt_variable)>>8)&0x000000FF,
										 (int)(*(u32sod *)(loc_pt_variable))&0x000000FF);
			
			break;
//f: BE063.0 06/10/2011

		default:
			MACRO_PRINTF(("u8PrintFieldValueSimple: Erreur type_offset KO = %d\n",loc_ps_one_field->u8_type_valeur));
			loc_s32_numwritten = -1; //Force erreur
			break;
	}

	if(loc_s32_numwritten < 0)	//CONDITION: ecriture KO
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8PrintFieldValueSimple: Erreur formatage\n"));
	}
	else
	{
		//Revue_caf - 07/04/10 - VAUT POUR TOUS LES STRCAT - Info : vérifier size(ps8_ligne_bddfile) + size(ps8_ligne_tempo) < TAILLE_MAX_LIGNE_BDDFILE avant de faire le strcat ("leur comportement est indéterminé en cas de copie entre des objets qui se chevauchent" p254 langage C)
		strcat(ps8_ligne_bddfile, ps8_ligne_tempo);
	}

	return loc_u8_resultat;
}/*u8PrintFieldValueSimple*/

//=====================================================================================
// Fonction		: u8PrintFieldValueComplex
// Entrees		: <loc_u16_idx>	: index du tableau
//				  <loc_ps8_name<: nom du tableau
//				  <loc_ps_list_complex<: pointeur sur list complex
//				  <loc_pt_tabstruct<: pointeur sur premier élément du tableau de structure
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui édite le contenu du fichier avec des lignes de type
//					  "|idx=xx|nom1=val1|...|nomN=valN|"
//=====================================================================================
u8sod u8PrintFieldValueComplex(u16sod loc_u16_idx, s8sod *loc_ps8_name, T_STRUCT_FILE_FIELD *loc_ps_list_complex, void *loc_pt_tabstruct)
{
	u8sod	loc_u8_resultat;
	s32sod	loc_s32_numwritten;
	u16sod	loc_u16_cpt;

	loc_u8_resultat = TRUE;	//INIT
	loc_s32_numwritten = 0; //INIT

	loc_u16_cpt = 0;	//INIT
	
	strcpy(ps8_ligne_tempo, ""); //RAZ
	sprintf(ps8_ligne_tempo,"%s=",loc_ps8_name);
	strcat(ps8_ligne_bddfile, ps8_ligne_tempo);
	strcat(ps8_ligne_bddfile, "|");

	//Edite toute la liste complexe des champs définis
	while(	(NULL!=loc_ps_list_complex->ps8_nom) &&
			(TRUE == loc_u8_resultat) &&
			(loc_u16_cpt < NB_MAX_FIELDS_STRUCT)
		 )
	{
		if(0 == strcmp(loc_ps_list_complex->ps8_nom, CH_TAB_INDEX))
		{
			sprintf(ps8_ligne_tempo,"%s=%d",CH_TAB_INDEX,loc_u16_idx);
			strcat(ps8_ligne_bddfile, ps8_ligne_tempo);
		}
		else
		{
			if(NULL == loc_ps_list_complex->pt_contenu_elt)//CONDITION: champs défini de type simple
			{
				//Edition de la ligne "nom=valeur"
				if(FALSE == u8PrintFieldValueSimple(loc_ps_list_complex, (loc_pt_tabstruct + loc_ps_list_complex->u32_moffset)))
				{
					loc_u8_resultat = FALSE;
				}
			}
			else//CONDITION: champs défini de type complexe
			{
				MACRO_PRINTF(("u8PrintFieldValueComplex: type valeur non autorisé\n"));
				loc_u8_resultat = FALSE;
			}
		}

		if(TRUE == loc_u8_resultat)
		{
			strcat(ps8_ligne_bddfile, "|");
		}
		loc_ps_list_complex ++;
		loc_u16_cpt ++;

	}

	return loc_u8_resultat;
}/*u8PrintFieldValueComplex*/

//=====================================================================================
// Fonction		: BddFile_DisplayFieldValue
// Entrees		: <loc_ps_field_list<	: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
// Sortie		: void
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui affiche sur la console les valeurs associées au fichier
//=====================================================================================
void BddFile_DisplayFieldValue(T_STRUCT_FILE_FIELD *loc_ps_field_list, void *loc_pt_structure)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_idx;
	u16sod	loc_u16_cpt;
	T_STRUCT_FILE_FIELD		*loc_ps_list;

	loc_u8_resultat = TRUE; //INIT
	loc_u16_idx = 0;	//INIT
	loc_u16_cpt = 0;	//INIT
	loc_ps_list = loc_ps_field_list;	//INIT

	//Initialise toute la liste 
	while( (NULL!=loc_ps_list->ps8_nom) &&
		   (TRUE == loc_u8_resultat) &&
		   (loc_u16_cpt < NB_MAX_FIELDS_BDDFILE)
		 )
	{
		strcpy(ps8_ligne_bddfile, ""); //RAZ
		if(NULL == loc_ps_list->pt_contenu_elt) //CONDITION: champs de type simple
		{
			//Edition de la ligne "nom=valeur"
			if(FALSE == u8PrintFieldValueSimple(loc_ps_list, (loc_pt_structure + loc_ps_list->u32_moffset))) //CONDITION: écriture simple KO
			{
				loc_u8_resultat = FALSE;
			}
			else //CONDITION: écriture simple OK
			{
				printf("%s\n", ps8_ligne_bddfile);
			}
		}
		else //CONDITION: champs de type complexe
		{
			//On parcourt tout le tableau
			for(loc_u16_idx=0;loc_u16_idx<loc_ps_list->u16_nb_max_elt;loc_u16_idx++)
			{
				strcpy(ps8_ligne_bddfile, ""); //RAZ
				if(FALSE == u8PrintFieldValueComplex(loc_u16_idx,
													loc_ps_list->ps8_nom,
													(T_STRUCT_FILE_FIELD *)loc_ps_list->pt_contenu_elt,
													(loc_pt_structure + loc_ps_list->u32_moffset + (u32sod)loc_u16_idx*(u32sod)loc_ps_list->u16_taille_elt)) //pointe sur l'élément du tableau de structure: &tabstruct[loc_u16_idx]
				  )//CONDITION: écriture complexe KO
				{
					loc_u8_resultat = FALSE;
				}
				else //CONDITION: écriture OK
				{
					printf("%s\n", ps8_ligne_bddfile);
				}
			}
		}

		//On passe au champs suivant
		loc_ps_list ++;
		loc_u16_cpt ++;
	}

}/*BddFile_DisplayFieldValue*/

//=====================================================================================
// Fonction		: u8BddFilePrintf
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_presence_checksum>: Présence du checksum (TRUE ou FALSE)
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui édite le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFilePrintf(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u8sod loc_u8_presence_checksum)
{
	u8sod	loc_u8_resultat;
	s32sod	loc_s32_numwritten;
	u16sod	loc_u16_cpt;
	u16sod	loc_u16_idx;
	u8sod	loc_u8_suivant;
	
	loc_u8_resultat = TRUE;	//INIT
	loc_u16_cpt = 0;	//INIT
	loc_u16_idx = 0; //INIT
	loc_u8_suivant = TRUE; //INIT

	u16_checksum_calcule_fileWr = 0; //RAZ

	//Edite toute la liste des champs définis
	while(	(NULL!=loc_ps_list->ps8_nom) &&
			(TRUE == loc_u8_resultat) &&
			(loc_u16_cpt < NB_MAX_FIELDS_BDDFILE)
		 )
	{

//		MACRO_PRINTF(("u8BddFilePrintf: name:%s format:%s\n",
//				   loc_ps_list->ps8_nom,
//				   PPS8_FORMAT_PRINTF_SCANF[loc_ps_list->u8_type_valeur]));

		//On édite la ligne dans le fichier
		loc_u8_resultat = u8BddFile_WriteLine(loc_pt_fichier,
											  loc_ps_list,
											  loc_pt_structure,
											  &loc_u16_idx,
											  &loc_u8_suivant);

		if(TRUE == loc_u8_resultat)	//CONDITION: ecriture OK
		{
			if(TRUE == loc_u8_presence_checksum) //CONDITION: Fichier avec checksum
			{
				//on calcule le checksum du fichier
				u16_checksum_calcule_fileWr += func_u16CalculChecksum(ps8_ligne_bddfile, TAILLE_MAX_LIGNE_BDDFILE);
			}
		}

		//On passe au champs suivant
		if(TRUE == loc_u8_suivant)
		{
			loc_ps_list ++;
			loc_u16_idx = 0; //RAZ
		}
		loc_u16_cpt ++;
	}
	
	//On ecrit en fin du fichier le checksum (si nécessaire)
	if((TRUE == loc_u8_presence_checksum) &&
	   (TRUE == loc_u8_resultat)
	  )	//CONDITION: Fichier avec checksum
	{
		loc_s32_numwritten = fprintf(loc_pt_fichier, "%s=%d\n",
									 (const s8sod*)CH_BDDFILECHECKSUM,
									 u16_checksum_calcule_fileWr);
		if(loc_s32_numwritten < 0)	//CONDITION: ecriture KO
		{
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8BddFilePrintf: Erreur ecriture (CHK)\n"));
		}
	}

	
	return loc_u8_resultat;
}/*u8BddFilePrintf*/

//=====================================================================================
// Fonction		: u8BddFileScanf
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_verif_checksum>: vérification du checksum (TRUE ou FALSE)
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui lit le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFileScanf(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u8sod loc_u8_verif_checksum)
{
	u8sod	loc_u8_resultat;
	u16sod	loc_u16_cpt;
	u8sod	loc_u8_isEndOfFile;

	loc_u8_resultat = TRUE;	//INIT
	loc_u16_cpt = 0;	//INIT
	loc_u8_isEndOfFile = FALSE; //INIT

	u16_checksum_calcule_fileRd = 0;	//RAZ
	u16_checksum_read_fileRd = 0; //RAZ

	//Lit tout le fichier jusqu'à la fin du fichier
	do
	{
		//Lit ligne par ligne
		loc_u8_resultat = u8BddFile_ReadLine(loc_pt_fichier, loc_ps_list, loc_pt_structure, loc_u8_verif_checksum, &loc_u8_isEndOfFile);
		
		loc_u16_cpt ++;

		if(TRUE == loc_u8_isEndOfFile) //CONDITION: fin de fichier
		{
			loc_u16_cpt = (NB_MAX_FIELDS_BDDFILE+1);
		}
		
	}while( (loc_u16_cpt < NB_MAX_FIELDS_BDDFILE) &&
			(TRUE == loc_u8_resultat)
		  );

	//On vérifie le checksum (si nécessaire)
	if(	(TRUE == loc_u8_verif_checksum) &&
		(TRUE == loc_u8_resultat)
	  )
	{
		if(u16_checksum_calcule_fileRd != u16_checksum_read_fileRd) //CONDITION: checksum CALCULE différent de celui LU
		{
			//CHECKSUM KO
			loc_u8_resultat = FALSE;
			
			MACRO_PRINTF(("u8BddFileScanf: u16_checksum_calcule_fileRd= 0x%X\n",u16_checksum_calcule_fileRd));
			MACRO_PRINTF(("u8BddFileScanf: u16_checksum_read_fileRd= 0x%X\n",u16_checksum_read_fileRd));
			
			MACRO_PRINTF(("**** CHECKSUM KO ****\n"));
			MACRO_PRINTF(("**** CHECKSUM KO ****\n"));
			MACRO_PRINTF(("**** CHECKSUM KO ****\n"));
			
		}
	}
	
	
	return loc_u8_resultat;
}/*u8BddFileScanf*/

//=====================================================================================
// Fonction		: u8ScanFieldValueSimple
// Entrees		: <loc_ps_one_field<	: pointeur sur un champs du fichier
//				  <loc_pt_variable<: pointeur sur la variable de la structure
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction extrait le contenu du fichier avec des lignes de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8ScanFieldValueSimple(T_STRUCT_FILE_FIELD *loc_ps_one_field, void *loc_pt_variable, s8sod *loc_ps8_valeur)
{
	u8sod loc_u8_resultat;
	u8sod loc_u8_i;
	u16sod loc_u16_i;
	u32sod	loc_pu32_valsscanf[NB_MAX_VAL_SSCANF];
	u8sod	*loc_pu8_valeur;
	s8sod	loc_ps8_mot_hexa[10+1];
	u8sod	loc_u8_ret;
	loc_u8_ret = FALSE;

	loc_u8_resultat = TRUE; //INIT
	for(loc_u8_i=0;loc_u8_i<NB_MAX_VAL_SSCANF;loc_u8_i++)
	{
		loc_pu32_valsscanf[loc_u8_i] = 0x00;	//INIT
	}
	loc_pu8_valeur = NULL; //INIT    
	strcpy(loc_ps8_mot_hexa, ""); //INIT

	switch(loc_ps_one_field->u8_type_valeur)
	{
		case FTYPVAL_STRING:
			if((0 == loc_ps_one_field->u16_taille_elt) ||
			   ((u32sod)strlen(loc_ps8_valeur) <= (u32sod)loc_ps_one_field->u16_taille_elt)
			  )//CONDITION: longueur de la chaine de caractères acceptable
			{
				strcpy((s8sod *)(loc_pt_variable), loc_ps8_valeur);
			}
			else
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8ScanFieldValueSimple: FTYPVAL_STRING KO (lg:%d)\n",strlen(loc_ps8_valeur)));
			}
			break;
		case FTYPVAL_U8SOD:
			*(u8sod *)(loc_pt_variable) = (u8sod)atoi(loc_ps8_valeur);
			break;
		case FTYPVAL_S8SOD:
			*(s8sod *)(loc_pt_variable) = (s8sod)atoi(loc_ps8_valeur);
			break;
		case FTYPVAL_U16SOD:
			*(u16sod *)(loc_pt_variable) = (u16sod)atoi(loc_ps8_valeur);
			break;
		case FTYPVAL_S16SOD:
			*(s16sod *)(loc_pt_variable) = (s16sod)atoi(loc_ps8_valeur);
			break;
		case FTYPVAL_U32SOD:
			*(u32sod *)(loc_pt_variable) = (u32sod)atoll(loc_ps8_valeur); //atoll: pour convertir un (long long)
			break;
		case FTYPVAL_S32SOD:
			*(s32sod *)(loc_pt_variable) = (s32sod)atoi(loc_ps8_valeur);
			break;
		case FTYPVAL_ADR_MAC: //adresse MAC
			if(ETHER_ADDR_LEN !=  sscanf(loc_ps8_valeur,"%02lX:%02lX:%02lX:%02lX:%02lX:%02lX",
										 &loc_pu32_valsscanf[0],
										 &loc_pu32_valsscanf[1],
										 &loc_pu32_valsscanf[2],
										 &loc_pu32_valsscanf[3],
										 &loc_pu32_valsscanf[4],
										 &loc_pu32_valsscanf[5])
			  )//CONDITION: lecture adresse MAC KO
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8ScanFieldValueSimple: FTYPVAL_ADR_MAC KO\n"));
			}
			else//CONDITION: lecture adresse MAC OK
			{
				loc_pu8_valeur = (u8sod *)(loc_pt_variable); //RAZ
				for(loc_u8_i=0;loc_u8_i<ETHER_ADDR_LEN;loc_u8_i++)
				{
					*loc_pu8_valeur = (u8sod)loc_pu32_valsscanf[loc_u8_i];
					loc_pu8_valeur++;
				}
			}
			break;					
		case FTYPVAL_DATE: //date
			if(6 !=  sscanf(loc_ps8_valeur,"%04lu/%02lu/%02lu %02lu:%02lu:%02lu",		//6: nombre de champ à lire
										 &loc_pu32_valsscanf[0],
										 &loc_pu32_valsscanf[1],
										 &loc_pu32_valsscanf[2],
										 &loc_pu32_valsscanf[3],
										 &loc_pu32_valsscanf[4],
										 &loc_pu32_valsscanf[5])
			  )//CONDITION: lecture date KO
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8ScanFieldValueSimple: FTYPVAL_DATE KO\n"));
			}
			else//CONDITION: lecture date OK
			{
				((S_STRUCT_DATE *)loc_pt_variable)->u16_annee = (u16sod)loc_pu32_valsscanf[0];
				((S_STRUCT_DATE *)loc_pt_variable)->u8_mois = (u8sod)loc_pu32_valsscanf[1];
				((S_STRUCT_DATE *)loc_pt_variable)->u8_jour = (u8sod)loc_pu32_valsscanf[2];
				((S_STRUCT_DATE *)loc_pt_variable)->u8_heure = (u8sod)loc_pu32_valsscanf[3];
				((S_STRUCT_DATE *)loc_pt_variable)->u8_minute = (u8sod)loc_pu32_valsscanf[4];
				((S_STRUCT_DATE *)loc_pt_variable)->u8_seconde = (u8sod)loc_pu32_valsscanf[5];
			}
			break;
		case FTYPVAL_TABU8_HEXA:
			if((u32sod)strlen(loc_ps8_valeur) == (u32sod)loc_ps_one_field->u16_taille_elt*2)//CONDITION: longueur de la chaine est égale 2*taille (car 2: "%02X")
			{
				for(loc_u16_i=0; (loc_u16_i<loc_ps_one_field->u16_taille_elt);loc_u16_i++)
				{
					loc_ps8_mot_hexa[0] = loc_ps8_valeur[2*loc_u16_i];
					loc_ps8_mot_hexa[1] = loc_ps8_valeur[2*loc_u16_i+1];
					loc_ps8_mot_hexa[2] = 0;	//fin de chaine de caractères
					if(1 !=  sscanf(loc_ps8_mot_hexa,"%02lX", &loc_pu32_valsscanf[0]))
					{
						loc_u8_resultat = FALSE;
						MACRO_PRINTF(("u8ScanFieldValueSimple: FTYPVAL_TABU8_HEXA KO\n"));
					}
					else
					{
						((u8sod *)(loc_pt_variable))[loc_u16_i] = (u8sod)loc_pu32_valsscanf[0];
					}
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8ScanFieldValueSimple: FTYPVAL_TABU8_HEXA longueur %d/%d KO\n",strlen(loc_ps8_valeur), loc_ps_one_field->u16_taille_elt));
			}
			break;
//d: BE063.0 06/10/2011
		case FTYPVAL_COMMENT: //ligne de commentaire: on ne fait rien
			break;
		case FTYPVAL_ADDIP: //adresse IP  en notation pointee
			*(u32sod *)(loc_pt_variable) = (u32sod)u32DecodageAdresseReseau(loc_ps8_valeur,&loc_u8_ret);
			break;
//f: BE063.0 06/10/2011
			
		default:
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8ScanFieldValueSimple: Erreur type_offset KO = %d\n",loc_ps_one_field->u8_type_valeur));
			break;
	}
	return loc_u8_resultat;
}/*u8ScanFieldValueSimple*/

//=====================================================================================
// Fonction		: u8ScanFieldValueComplex
// Entrees		: <loc_pt_contenu_elt<	: pointeur sur la définition du contenu  du tableau
//				  <loc_u16_taille_elt>  : taille élément du tableau
//				  <loc_u16_nb_max_elt>  : taille maximum du tableau
//				  <loc_pt_tabstruct<: pointeur sur premier élément du tableau de structure
//				  <loc_ps8_complex_valeur<: chaine de caractères
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Fonction qui extrait le contenu du fichier avec des lignes de type
//					  "|idx=xx|nom1=val1|...|nomN=valN|"
//=====================================================================================
u8sod u8ScanFieldValueComplex(T_STRUCT_FILE_FIELD *loc_pt_contenu_elt, u16sod loc_u16_taille_elt, u16sod loc_u16_nb_max_elt, void *loc_pt_tabstruct, s8sod *loc_ps8_complex_valeur)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_trouve;
	s8sod	*loc_ps8_token;
	u16sod	loc_u16_cpt;
	u16sod	loc_u16_idx;
	T_STRUCT_FILE_FIELD *loc_ps_tempo_list;
	s32sod loc_s32_numread;

	loc_u8_resultat = TRUE; //INIT
	loc_u8_trouve = FALSE; //INIT
	loc_ps8_token = NULL; //INIT
	loc_u16_cpt = 0; //INIT
	loc_u16_idx = 0xFFFF; //INIT
	loc_ps_tempo_list = NULL; //INIT
	loc_s32_numread = 0;	//INIT

	do{
		if(0==loc_u16_cpt)
		{
			loc_ps8_token = strtok(loc_ps8_complex_valeur, "|");	//1ere lecture
		}
		else
		{
			loc_ps8_token = strtok(NULL, "|");	// lecture suivante
		}

		if(loc_ps8_token!=NULL)
		{
			strcpy(ps8_cmplxnom,"");	//RAZ
			strcpy(ps8_cmplxval,"");	//RAZ
			//Lecture du champs=valeur
			//Comme sscanf(loc_ps8_token, "%[^=]=%s", ne fonctionne pas correctement quand il y a des caractères 'espace'
			//On copie la chaine extraite de la ligne dans une variable temporaire
			//On rajoute le caractère "\n"
			
			//Revue_caf - 07/04/10 - Info : vérifier que la longueur de ps8_cmplxligne n'atteint pas déjà la taille limite??? avant d'insérer le retour chariot?
			
			strcpy(ps8_cmplxligne,loc_ps8_token); //RAZ
			strcat(ps8_cmplxligne,"\n");
			loc_s32_numread = sscanf(ps8_cmplxligne, "%[^=]=%[^\n]\n",
									 ps8_cmplxnom,
									 ps8_cmplxval);

			//Cas où valeur est de chaine vide
			if((1 == loc_s32_numread)&&
			   (0 == strcmp(ps8_cmplxval,""))
			  )
			{
				//on signale qu'il y a bien 2 champs
				loc_s32_numread = 2;
			}
			
			if(2 == loc_s32_numread) //CONDITION: lecture OK
			{
				//On recherche l'élément de la liste associé au nom
				loc_u8_trouve = FALSE; //INIT
				loc_ps_tempo_list = (T_STRUCT_FILE_FIELD *)loc_pt_contenu_elt;  //RAZ
				while(	(NULL!=loc_ps_tempo_list->ps8_nom) &&
						(FALSE == loc_u8_trouve)
					 )
				{
					if(0 == strcmp(ps8_cmplxnom, loc_ps_tempo_list->ps8_nom))  //CONDITION: nom trouvé
					{
						loc_u8_trouve = TRUE;	//chaine identique
					}
					else //CONDITION: nom non trouvé
					{
						//On passe au champs suivant
						loc_ps_tempo_list ++;
					}
				}

				if(TRUE == loc_u8_trouve) //CONDITION: nom trouvé
				{
					if(0 == strcmp(ps8_cmplxnom, CH_TAB_INDEX)) //CONDITION: il s'agit du champs "index"
					{
						//Détermination de l'index
						loc_u16_idx = (u16sod)atoi(ps8_cmplxval);
					}
					else //CONDITION: il s'agit des autres champs de la structure complexe
					{
						//Cas d'un structure de type simple
						if(0 == loc_u16_nb_max_elt) //CONDITION: Structure simple
						{
							loc_u16_idx = 0;	//RAZ
						}
						
						if((loc_u16_idx < loc_u16_nb_max_elt)||
						   (0 == loc_u16_nb_max_elt)
						  ) //CONDITION: index valide du tableau ou  structure simple
						{
							if(NULL == loc_ps_tempo_list->pt_contenu_elt) //CONDITION: champs simple
							{
								//Transcodage de la chaine de caractères "valeur" => résultat copié dans la structure
								if(FALSE == u8ScanFieldValueSimple(loc_ps_tempo_list,
																	loc_pt_tabstruct + (u32sod)loc_u16_idx*(u32sod)loc_u16_taille_elt + loc_ps_tempo_list->u32_moffset, //pointe sur le champs de tabstruct[idx]
																	ps8_cmplxval)
								  )//CONDITION: Lecture simple KO
								{
									loc_u8_resultat = FALSE;
									MACRO_PRINTF(("u8ScanFieldValueComplex: transcodage KO\n"));
								}
							}
							else  //CONDITION: champs complexe
							{
								loc_u8_resultat = FALSE; 
								MACRO_PRINTF(("u8ScanFieldValueComplex: type non autorisé\n"));
							}						
						}
						else  //CONDITION: index KO
						{
							loc_u8_resultat = FALSE; 
							MACRO_PRINTF(("u8ScanFieldValueComplex: index=%d / %d KO\n",
										  loc_u16_idx,
										  loc_u16_nb_max_elt));
						}
					}
				}
				else  //CONDITION: nom KO
				{
//d: BE061 10/05/2011 - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
#if SIGNAL_ERROR_Si_CHAMP_INCONNU
//f: BE061 10/05/2011 - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
					loc_u8_resultat = FALSE; 
					MACRO_PRINTF(("u8ScanFieldValueComplex: nom non trouvé\n"));
#endif
				}
			}
			else  //CONDITION: lecture KO
			{
				loc_u8_resultat = FALSE; 
				MACRO_PRINTF(("u8ScanFieldValueComplex: lecture KO\n"));
			}
		}
		
		loc_u16_cpt ++;
//		MACRO_PRINTF(("loc_u16_cpt:%d/loc_ps8_token=%d/loc_u8_resultat=%d\n",loc_u16_cpt,(u32sod)loc_ps8_token,loc_u8_resultat));

	}while((loc_u16_cpt < NB_MAX_FIELDS_STRUCT) &&
		   (NULL != loc_ps8_token) &&
		   (TRUE == loc_u8_resultat));

	return loc_u8_resultat;

}/*u8ScanFieldValueComplex*/

//=====================================================================================
// Fonction		: u8BddFile_Decode
// Entrees		: <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_ps8_ligne_code<	: ligne du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_verif_checksum>: vérification du checksum (TRUE ou FALSE)
//				  >loc_pps_next_list<	: pointeur sur le prochain de la liste
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 24/09/2009 -
// Description	: Decode ligne du fichier au format suivant
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFile_Decode(T_STRUCT_FILE_FIELD *loc_ps_list, s8sod *loc_ps8_ligne_code, void *loc_pt_structure, u8sod loc_u8_verif_checksum, T_STRUCT_FILE_FIELD **loc_pps_next_list)
{
	u8sod	loc_u8_resultat;
	u8sod	loc_u8_trouve;
	s32sod  loc_s32_cpt_champ;

	loc_u8_resultat = TRUE;	//INIT
	loc_u8_trouve = FALSE;	//INIT

//	printf("%s\n",loc_ps8_ligne_code);
	strcpy(ps8_champ_nom, ""); //RAZ
	strcpy(ps8_champ_valeur, ""); //RAZ
	loc_s32_cpt_champ = sscanf(loc_ps8_ligne_code,"%[^=]=%[^\n]\n",
							   ps8_champ_nom,
							   ps8_champ_valeur);
//	printf("ps8_champ_nom=%s\n",ps8_champ_nom);
//	printf("ps8_champ_valeur=%s\n",ps8_champ_valeur);

	//Cas où valeur est de chaine vide
	if((1 == loc_s32_cpt_champ)&&
	   (0 == strcmp(ps8_champ_valeur,""))
	  )
	{
		//on signale qu'il y a bien 2 champs
		loc_s32_cpt_champ = 2;
	}


	if(2 == loc_s32_cpt_champ) //CONDITION: Lecture "<nom>=<valeur>"est correcte
	{
		//Recherche du nom dans la liste
		//Dans le cas où le fichier lu est construit comme sa définition
		//On vérifie d'abord qu'au pointeur de next_list, il s'agit du bon nom
		//Si ce n'est pas le cas, on part à la recherche sur toute la liste
		if(NULL != (*loc_pps_next_list)->ps8_nom)
		{
			//printf("(*loc_pps_next_list)->ps8_nom=%s\n",(*loc_pps_next_list)->ps8_nom);
			if(0 == strcmp(ps8_champ_nom, (*loc_pps_next_list)->ps8_nom)) //CONDITION: nom trouvé
			{
				//printf("LECTURE DIRECTE\n");
				loc_ps_list = (*loc_pps_next_list);
				loc_u8_trouve = TRUE;	//chaine identique
			}
		}
		
		if(FALSE == loc_u8_trouve) //CONDITION: nom pas trouvé
		{
			//printf("LECTURE INDIRECTE\n");
			//Recherche du nom dans la liste
			while(	(NULL!=loc_ps_list->ps8_nom) &&
					(FALSE == loc_u8_trouve)
				 )
			{
				if(0 == strcmp(ps8_champ_nom, loc_ps_list->ps8_nom))  //CONDITION: nom trouvé
				{
					loc_u8_trouve = TRUE;	//chaine identique
				}

				//On passe au champs suivant
				loc_ps_list ++;
			}

			if(TRUE == loc_u8_trouve)
			{
				//on revient sur la liste trouvée
				loc_ps_list --;
				//par défaut, le prochain de la liste c'est celui trouvé
				(*loc_pps_next_list) = loc_ps_list;
			}
		}

		if(TRUE == loc_u8_trouve)
		{
			if(strlen(ps8_champ_valeur) > LG_MAX_FIELD_VALUE)	//CONDITION: taille champs valeur trop grande
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8BddFile_Decode: longueur champs ligne trop grande\n"));
			}
			else	//CONDITION: OK
			{
				if(TRUE == loc_u8_verif_checksum) //CONDITION: vérification du checksum
				{
					if(FALSE == func_u8IsFieldChecksumBddFile(loc_ps_list->ps8_nom)) //CONDITION: ce n'est pas le champ checksum
					{
						u16_checksum_calcule_fileRd += func_u16CalculChecksum(loc_ps_list->ps8_nom, LG_MAX_FIELD_NAME);
						u16_checksum_calcule_fileRd += '=';
						u16_checksum_calcule_fileRd += func_u16CalculChecksum(ps8_champ_valeur, LG_MAX_FIELD_VALUE);
					}
					else
					{
						if(FTYPVAL_U16SOD == loc_ps_list->u8_type_valeur)
						{
							u16_checksum_read_fileRd = (u16sod)atoi(ps8_champ_valeur);
						}
						else
						{
							MACRO_PRINTF(("u8BddFile_Decode: checksum avec type_offset=%d KO\n",loc_ps_list->u8_type_valeur));
						}
					}
				}

				if(NULL == loc_ps_list->pt_contenu_elt) //CONDITION: champs simple
				{
					//Transcodage de la chaine de caractères "valeur" => résultat copié dans la structure
					if(FALSE == u8ScanFieldValueSimple(loc_ps_list, (loc_pt_structure + loc_ps_list->u32_moffset), ps8_champ_valeur))//CONDITION: Transcodage KO
					{
						loc_u8_resultat = FALSE;
						MACRO_PRINTF(("u8BddFile_Decode: u8ScanFieldValueSimple KO\n"));
					}
					else //CONDITION: Transcodage OK
					{
						//à la prochaine lecture, ça sera le suivant
						if(NULL != (*loc_pps_next_list)->ps8_nom)
						{
//							printf("PASSAGE de %s =>",(*loc_pps_next_list)->ps8_nom);

							//on passe au prochain de la liste
							(*loc_pps_next_list)++;
							
//							if(NULL != (*loc_pps_next_list)->ps8_nom)
//							{
//								printf(" %s\n",(*loc_pps_next_list)->ps8_nom);
//							}
						}
					}
				}
				else //CONDITION: champs complexe
				{
					//Transcodage de la chaine de caractères "valeur" => résultat copié dans la structure
					if(FALSE == u8ScanFieldValueComplex((T_STRUCT_FILE_FIELD *)loc_ps_list->pt_contenu_elt, //contenu de l'elt du tableau
														loc_ps_list->u16_taille_elt, //taille de l'élément du tableau
														loc_ps_list->u16_nb_max_elt, //taille max du tableau
														(loc_pt_structure + loc_ps_list->u32_moffset), //pointe sur le premier élément du tableau de structure: &tabstruct[0]
														ps8_champ_valeur)
					  )//CONDITION: Transcodage KO
					{
						loc_u8_resultat = FALSE;
						MACRO_PRINTF(("u8BddFile_Decode: u8ScanFieldValueComplex KO\n"));
					}
				}
			}
		}
		else
		{
//d: BE061 10/05/2011 - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
#if !SIGNAL_ERROR_Si_CHAMP_INCONNU
//f: BE061 10/05/2011 - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
			if(TRUE == loc_u8_verif_checksum) //CONDITION: vérification du checksum
			{
				//on calule le checksum (afin que le test soit toujours valide, si checksum fichier OK)
				u16_checksum_calcule_fileRd += func_u16CalculChecksum(loc_ps8_ligne_code, TAILLE_MAX_LIGNE_BDDFILE);
			}
#else
#warning "ACTIVATION ERREUR SI CHAMP INCONNU"
			loc_u8_resultat = FALSE;
			MACRO_PRINTF(("u8BddFile_Decode: Erreur champs ligne non trouvee\n"));
#endif
		}

	}
	else
	{
		loc_u8_resultat = FALSE;
		MACRO_PRINTF(("u8BddFile_Decode: Erreur 1 cpt=%d\n",(s16sod)loc_s32_cpt_champ));
	}

	return loc_u8_resultat;
}/*u8BddFile_Decode*/


//=====================================================================================
// Fonction		: u8BddFile_WriteLine
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure<	: pointeur sur structure contenant les données
//				  <loc_pu16_idx<		: pointeur sur index
//				  <loc_pu8_suivant<		: pointeur sur suivant
// Sortie		: <loc_u8_resultat> (TRUE ou FALSE)
// Auteur		: CM - 02/03/2010 -
// Description	: Fonction qui édite une seule ligne
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFile_WriteLine(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u16sod *loc_pu16_idx, u8sod *loc_pu8_suivant)
{
	u8sod	loc_u8_resultat;
	s32sod	loc_s32_numwritten;

	loc_u8_resultat = TRUE;	//INIT

	strcpy(ps8_ligne_bddfile, ""); //RAZ

	if(FALSE == func_u8IsFieldChecksumBddFile(loc_ps_list->ps8_nom)) //CONDITION: ce n'est pas le champ checksum
	{
		if(NULL == loc_ps_list->pt_contenu_elt) //CONDITION: champs de type simple
		{
			//Edition de la ligne "nom=valeur"
			if(FALSE == u8PrintFieldValueSimple(loc_ps_list, (loc_pt_structure + loc_ps_list->u32_moffset)))//CONDITION: Ecriture simple KO
			{
				loc_u8_resultat = FALSE;
			}
			(*loc_pu8_suivant) = TRUE;
			(*loc_pu16_idx) = 0; //RAZ
		}
		else //CONDITION: champs de type complexe
		{
			//Puis on édite la ligne avec le contenu de l'élément à l'index
			if(FALSE == u8PrintFieldValueComplex((*loc_pu16_idx),		//index du tableau de structure
												 loc_ps_list->ps8_nom,	//nom du tableau
												 (T_STRUCT_FILE_FIELD *)loc_ps_list->pt_contenu_elt,	//contenu de la structure
												 (loc_pt_structure + loc_ps_list->u32_moffset + (u32sod)(*loc_pu16_idx)*(u32sod)loc_ps_list->u16_taille_elt)) //pointe sur l'élément du tableau de structure: &tabstruct[(*loc_pu16_idx)]
			  )//CONDITION: Ecriture complexe KO
			{
				loc_u8_resultat = FALSE;
			}
			(*loc_pu16_idx) ++;
			if((*loc_pu16_idx) < loc_ps_list->u16_nb_max_elt)
			{
				(*loc_pu8_suivant) = FALSE;
			}
			else
			{
				(*loc_pu8_suivant) = TRUE;
				(*loc_pu16_idx) = 0; //RAZ
			}
		}

		if(TRUE == loc_u8_resultat)	//CONDITION: ecriture OK
		{
			//puis on écrit dans le fichier
			loc_s32_numwritten = fprintf(loc_pt_fichier, "%s\n", ps8_ligne_bddfile);
			if(loc_s32_numwritten < 0)	//CONDITION: ecriture KO
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8BddFile_WriteLine: Erreur ecriture\n"));
			}
		}
	}

	return loc_u8_resultat;
}/*u8BddFile_WriteLine*/

//=====================================================================================
// Fonction		: u8BddFile_ReadLine
// Entrees		: <loc_pt_fichier<		: pointeur sur fichier
//				  <loc_ps_list<			: pointeur sur la liste des champs du fichier
//				  <loc_pt_structure< : pointeur sur structure contenant les données
//				  <loc_u8_verif_checksum>: vérification du checksum (TRUE ou FALSE)
//				  <loc_pu8_isEndOfFile<	: pointeur sur info "fin de fichier" (signalé avec val
// Sortie		: <loc_u8_resultat> : (TRUE ou FALSE)
// Auteur		: CM - 02/03/2010 -
// Description	: Fonction qui lit une seule ligne du fichier de type
//					<nom_variable>=<valeur>
//=====================================================================================
u8sod u8BddFile_ReadLine(FILE *loc_pt_fichier, T_STRUCT_FILE_FIELD *loc_ps_list, void *loc_pt_structure, u8sod loc_u8_verif_checksum, u8sod *loc_pu8_isEndOfFile)
{
	u8sod	loc_u8_resultat;
	s8sod	*loc_ps8_result_fgets;
	s8sod	*ps8_ligne_bddfile_tempo;
	T_STRUCT_FILE_FIELD *loc_ps_next_list;

	loc_u8_resultat = TRUE;	//INIT
	loc_ps8_result_fgets = NULL; //INIT
	ps8_ligne_bddfile_tempo = NULL; //INIT
	loc_ps_next_list = loc_ps_list;	//INIT

	(*loc_pu8_isEndOfFile) = FALSE; //INIT
	
	loc_ps8_result_fgets = fgets(ps8_ligne_bddfile,TAILLE_MAX_LIGNE_BDDFILE,loc_pt_fichier); //lecture de TAILLE_MAX_LIGNE_BDDFILE caractères du fichier loc_pt_fichier que l'on place dans le tableau ps8_ligne_bddfile
	if(NULL != loc_ps8_result_fgets)
	{
//BE063.0 06/10/2011
		if (ps8_ligne_bddfile[0]== '#')
		{
			/* ligne de commentaire */
			loc_u8_resultat = TRUE;
		}
		else
		{
//			ps8_ligne_bddfile_tempo = strtok(ps8_ligne_bddfile, "\n\r\t"); //recherche dans ps8_ligne_bddfile des chaînes délimitées par \n\r\t
			ps8_ligne_bddfile_tempo = strtok(ps8_ligne_bddfile, "#\n\r\t"); //recherche dans ps8_ligne_bddfile des chaînes délimitées par \n\r\t
//BE063.0 06/10/2011
			if(ps8_ligne_bddfile_tempo!=NULL) //CONDITION : OK
			{
				if(FALSE == u8BddFile_Decode(loc_ps_list, ps8_ligne_bddfile_tempo, loc_pt_structure, loc_u8_verif_checksum, &loc_ps_next_list))
				{
					loc_u8_resultat = FALSE;
					MACRO_PRINTF(("u8BddFile_ReadLine: Erreur décodage ligne \n"));
				}
			}
			else
			{
				loc_u8_resultat = FALSE;
				MACRO_PRINTF(("u8BddFile_ReadLine: ligne KO \n"));
			}
		}
	}
	else//sinon on n'arrive à la fin du fichier
	{
		(*loc_pu8_isEndOfFile) = TRUE;
	}
			

	return loc_u8_resultat;
}/*u8BddFile_ReadLine*/

/*_____VII - PROCEDURE D'INITIALISATION __________________________________*/

//=====================================================================================
// Fonction		: InitModule_BddFile
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 24/09/2009 -
// Description	: Initialisation du module de BddFile
//=====================================================================================
void InitModule_BddFile(void)
{
	u16_checksum_calcule_fileRd = 0;	//INIT
	u16_checksum_read_fileRd = 0;	//INIT
	u16_checksum_calcule_fileWr = 0; //INIT
	strcpy(ps8_ligne_bddfile,"");	//INIT
	strcpy(ps8_ligne_tempo,"");	//INIT

	strcpy(ps8_champ_nom,"");	//INIT
	strcpy(ps8_champ_valeur,"");	//INIT

	strcpy(ps8_cmplxligne,"");	//INIT
	strcpy(ps8_cmplxnom,"");	//INIT
	strcpy(ps8_cmplxval,"");	//INIT

	strcpy(ps8_valeur_tempo, "");	//INIT
	
}/*InitModule_BddFile*/

