/*========================================================================*/
/* NOM DU FICHIER  : passwd.c											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM (JP SFH252)                                       */
/* Date			   : 10/07/2007											  */
/* Libelle         : Gestion des mots de passe pour login sftp/ssh		  */
/* Projet          : WRM100                                               */
/* Indice          : BE056                                                */
/*========================================================================*/
/* Historique      :                                                      */
//BE036 02/07/2010 CM
// - CREATION
//BE038 09/07/2010 CM
// - Modification des droits de permissions pour /etc/passwd
//	afin de pouvoir se connecter avec sftp (o751 -> o755) avec usermiddle et userlow
//BE056 18/01/2011 CM
// - Sur WRM100-ABG, mot de passe du login root est root
//	pour conserver cohérence avec ancienne version
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

/*_____II - DEFINE SBIT __________________________________________________*/

#define _PASSWD

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pwd.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

#include "headers.h"
#include <crypt.h>
#include <sys/types.h>

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

#define FICHIER_ETC_PASSWD PATH_DIR_ETC	 "passwd"
#define FICHIER_ETC_NEW_PASSWD PATH_DIR_ETC	 "npasswd"

#define FICHIER_ETC_SHADOW PATH_DIR_ETC	 "shadow"
#define FICHIER_ETC_NEW_SHADOW PATH_DIR_ETC	 "nshadow"

//Droits / Permissions
#define UID_ROOT	0
#define GID_ROOT	0
#define UID_USERMIDDLE		1000
#define GID_USERMIDDLE		1000
#define UID_USERLOW			1001
#define GID_USERLOW			1001


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: s8I64c
// Entrees		: <loc_s32_value>: mot de 32 bits
// Sortie		: <loc_s8_return>: caractère
// Auteur		: 
// Description	: Convertir un mot de 32bit en un caractère
//=====================================================================================
static s8sod s8I64c(s32sod loc_s32_value)
{
	s8sod	loc_s8_return;

	loc_s8_return = 'z';	//INIT
	
	if (loc_s32_value <= 0)
	{
		loc_s8_return = ('.');
	}
	else
	{
		if (1 == loc_s32_value)
		{
			loc_s8_return = ('/');
		}
		else
		{
			if((loc_s32_value >= 2) && (loc_s32_value < 12))
			{
				loc_s8_return = ('0' - 2 + loc_s32_value);
			}
			else
			{
				if((loc_s32_value >= 12) && (loc_s32_value < 38))
				{
					loc_s8_return = ('A' - 12 + loc_s32_value);
				}
				else
				{
					if((loc_s32_value >= 38) && (loc_s32_value < 63))
					{
						loc_s8_return = ('a' - 38 + loc_s32_value);
					}
					else
					{
						loc_s8_return = ('z');
					}
				}
			}
		}
	}
	
	return loc_s8_return;
}/*s8I64c*/

//=====================================================================================
// Fonction		: ps8Crypt_make_salt
// Entrees		: rien
// Sortie		: <loc_ps8_result<
// Auteur		: 
// Description	: crée un salt en concaténant les caractères
//=====================================================================================
static s8sod *ps8Crypt_make_salt(void)
{
	time_t loc_t_now;
	static u32sod loc_u32_x;
	static s8sod loc_ps8_result[3];

	time(&loc_t_now);
	loc_u32_x += (u32sod)loc_t_now + (u32sod)getpid();
	loc_ps8_result[0] = s8I64c(((loc_u32_x >> 18) ^ (loc_u32_x >> 6)) & 077);
	loc_ps8_result[1] = s8I64c(((loc_u32_x >> 12) ^ loc_u32_x) & 077);
	loc_ps8_result[2] = '\0';
	return loc_ps8_result;
}/*ps8Crypt_make_salt*/

//=====================================================================================
// Fonction		: u8SetPassword
// Entrees		: <loc_ps8_user<: nom de l'utilisateur
//				: <loc_ps8_password<: mot de passe
// Sortie		: <loc_u8_return>: TRUE si réussie sinon FALSE
// Auteur		: 
// Description	: Fixe un mot de passe pour un utilisateur
//=====================================================================================
u8sod u8SetPassword(const s8sod *loc_ps8_user, const s8sod *loc_ps8_password)
{
	u8sod loc_u8_return;
	struct passwd *loc_ps_pwp;
	struct passwd loc_s_pws;
	u8sod	loc_u8_foundit;
	FILE *loc_pf_fto;
	FILE *loc_pf_fd;

	loc_u8_return = TRUE;	//INIT
	loc_u8_foundit = FALSE;	//INIT

	//Détruit le fichier ou son lien
	unlink(FICHIER_ETC_NEW_PASSWD);

	if(NULL != (loc_pf_fto = fopen(FICHIER_ETC_NEW_PASSWD, "wt"))) //CONDITION: fichier présent
	{
		//On vérifie que le fichier original est présent
		if (NULL == (loc_pf_fd = fopen(FICHIER_ETC_PASSWD, "rt")))
		{
			//pas de fichier cree : on le cree!
			if (NULL == (loc_pf_fd = fopen(FICHIER_ETC_PASSWD, "wt")))
			{
				MACRO_PRINTF(("u8SetPassword: Erreur lecture / creation fichier %s\n",FICHIER_ETC_PASSWD));
				loc_u8_return = FALSE;
			}
		}

		if(TRUE == loc_u8_return)
		{
			for(; (loc_ps_pwp = fgetpwent(loc_pf_fd)) != NULL;)
			{
				if(0 == strcmp(loc_ps_pwp->pw_name, loc_ps8_user))
				{
					loc_ps_pwp->pw_passwd = crypt(loc_ps8_password, ps8Crypt_make_salt());
					loc_u8_foundit = TRUE;
				}
				putpwent(loc_ps_pwp, loc_pf_fto);
			}
			fclose(loc_pf_fd);
			
			if(!loc_u8_foundit)
			{
				if(0 == strcmp(loc_ps8_user, NOM_USER_ROOT))
				{
					loc_s_pws.pw_uid = UID_ROOT;
					loc_s_pws.pw_gid = GID_ROOT;
					loc_s_pws.pw_gecos = "superuser";
				}
				else
				{
					if(0 == strcmp(loc_ps8_user, NOM_USER_HIGH))
					{
						loc_s_pws.pw_uid = UID_ROOT;
						loc_s_pws.pw_gid = GID_ROOT;
						loc_s_pws.pw_gecos = (s8sod *)loc_ps8_user;
					}
					else
					{
						if(0 == strcmp(loc_ps8_user, NOM_USER_MIDDLE))
						{
							loc_s_pws.pw_uid = UID_USERMIDDLE;
							loc_s_pws.pw_gid = GID_USERMIDDLE;
							loc_s_pws.pw_gecos = (s8sod *)loc_ps8_user;
						}
						else
						{
							if(0 == strcmp(loc_ps8_user, NOM_USER_LOW))
							{
								loc_s_pws.pw_uid = UID_USERLOW;
								loc_s_pws.pw_gid = GID_USERLOW;
								loc_s_pws.pw_gecos = (s8sod *)loc_ps8_user;
							}
						}
					}
				}
				loc_s_pws.pw_name = (s8sod *)loc_ps8_user;
				loc_s_pws.pw_passwd = crypt(loc_ps8_password, ps8Crypt_make_salt());
				loc_s_pws.pw_dir = "/";	
				loc_s_pws.pw_shell = "/bin/sh";
				putpwent(&loc_s_pws, loc_pf_fto);
			}
			fclose(loc_pf_fto);

			rename(FICHIER_ETC_NEW_PASSWD, FICHIER_ETC_PASSWD);
			u8CmdSystem_ChmodFile(FICHIER_ETC_PASSWD, CHMOD_FILE_ROOT_755);
		}
	}
	else
	{
		MACRO_PRINTF(("u8SetPassword: Erreur creation fichier %s\n",FICHIER_ETC_NEW_PASSWD));
		loc_u8_return = FALSE;
	}
	return 1;	  
}/*u8SetPassword*/

//=====================================================================================
// Fonction		: u8SetShadow
// Entrees		: <loc_ps8_user<: nom de l'utilisateur
//				: <loc_ps8_password<: mot de passe
// Sortie		: <loc_u8_return>: TRUE si réussie sinon FALSE
// Auteur		: 
// Description	: Fixe un mot de passe pour un utilisateur dans /etc/shadow
//=====================================================================================
u8sod u8SetShadow(const s8sod *loc_ps8_user, const s8sod *loc_ps8_password)
{
	u8sod loc_u8_return;
	struct passwd *loc_ps_pwp;
	struct passwd loc_s_pws;
	u8sod	loc_u8_foundit;
	u8sod	loc_u8_isroot;
	FILE *loc_pf_fto;
	FILE *loc_pf_fd;

	loc_u8_return = TRUE;	//INIT
	loc_u8_foundit = FALSE;	//INIT
	loc_u8_isroot = FALSE;	//INIT

	//Détruit le fichier ou son lien
	unlink(FICHIER_ETC_NEW_PASSWD);

	if(NULL != (loc_pf_fto = fopen(FICHIER_ETC_NEW_SHADOW, "wt"))) //CONDITION: fichier présent
	{
		//On vérifie que le fichier original est présent
		if (NULL == (loc_pf_fd = fopen(FICHIER_ETC_SHADOW, "rt")))
		{
			//pas de fichier cree : on le cree!
			if (NULL == (loc_pf_fd = fopen(FICHIER_ETC_SHADOW, "wt")))
			{
				MACRO_PRINTF(("u8SetShadow: Erreur lecture / creation fichier %s\n",FICHIER_ETC_SHADOW));
				loc_u8_return = FALSE;
			}
		}

		if(TRUE == loc_u8_return)
		{
			for(; (loc_ps_pwp = fgetpwent(loc_pf_fd)) != NULL;)
			{
				if(0 == strcmp(loc_ps_pwp->pw_name, loc_ps8_user))
				{
					loc_ps_pwp->pw_passwd = crypt(loc_ps8_password, ps8Crypt_make_salt());
					loc_u8_foundit = TRUE;
				}
				putpwent(loc_ps_pwp, loc_pf_fto);
			}
			fclose(loc_pf_fd);

			if(!loc_u8_foundit)
			{
				if(0 == strcmp(loc_ps8_user, NOM_USER_ROOT))
				{
					loc_u8_isroot = TRUE;
				}
				loc_s_pws.pw_name = (s8sod *)loc_ps8_user;
				loc_s_pws.pw_passwd = crypt(loc_ps8_password, ps8Crypt_make_salt());
				loc_s_pws.pw_uid = 0;
				loc_s_pws.pw_gid = 0;
				loc_s_pws.pw_gecos = (TRUE == loc_u8_isroot)?"superuser":(s8sod *)loc_ps8_user;
				loc_s_pws.pw_dir = "/";	//isroot?"/":"/home";
				loc_s_pws.pw_shell = "/bin/sh";
				putpwent(&loc_s_pws, loc_pf_fto);
			}
			fclose(loc_pf_fto);

			rename(FICHIER_ETC_NEW_SHADOW, FICHIER_ETC_SHADOW);
			u8CmdSystem_ChmodFile(FICHIER_ETC_SHADOW, CHMOD_FILE_ROOT_751);
		}
	}
	else
	{
		MACRO_PRINTF(("u8SetShadow: Erreur creation fichier %s\n",FICHIER_ETC_NEW_SHADOW));
		loc_u8_return = FALSE;
	}
	return 1;	  
}/*u8SetShadow*/

//=====================================================================================
// Fonction		: Install_LoginPassword
// Entrees		: <loc_ps_config< : configuration (RAM) pour ce processus
// Sortie		: rien
// Auteur		: 
// Description	: creation du fichier /etc/passwd pour la gestion des connexions
//=====================================================================================
void Install_LoginPassword(S_STRUCT_CONFIGURATION *loc_ps_config)
{
	//le root: son mot de passe est stocké dans /etc/shadow (dont les informations sont prioritaires sur /etc/passwd)
#ifdef _WRM100_ABG_SELECT
	u8SetShadow(NOM_USER_ROOT, "root");
#else //_WRM100_N_SELECT
	u8SetShadow(NOM_USER_ROOT, MOT_DE_PASSE_SODIELEC);
#endif
	
	//le user high
	u8SetPassword(NOM_USER_HIGH, loc_ps_config->s_admin.ps8_mot_de_passe_high);
	//le user middle
	u8SetPassword(NOM_USER_MIDDLE, loc_ps_config->s_admin.ps8_mot_de_passe_middle);
	//le user low
	u8SetPassword(NOM_USER_LOW, loc_ps_config->s_admin.ps8_mot_de_passe_low);

	
}/*Install_LoginPassword*/

/*_______VII - PROCEDURES D 'INITIALISATION _________________________________*/

//=====================================================================================
// Fonction		: InitModule_Passwd
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 02/07/2010 -
// Description	: Initialisation du module de passwd
//=====================================================================================
void InitModule_Passwd(void)
{
}/*InitModule_Passwd*/


