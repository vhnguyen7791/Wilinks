/*========================================================================*/
/* NOM DU FICHIER  : list_freq.c										  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 11/10/2010                                           */
/* Libelle         : Base de données: liste des fréquences réglementaires */
/* Projet          : WRM100                                               */
/* Indice	       : BE056												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE042 11/10/2010 CM
// - CREATION
//BE043 29/10/2010 CM
// - Correction enum modes 802.11 (meilleur ergonomie)
//BE045 04/11/2010 CM
// - Correction bug liste frequences en 11nght40plus
//BE047 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
//BE056 18/01/2011 CM
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/
//Base de données de gestion de la liste des fréquences réglementaires
//Pour Driver-ABG: configurée à la main
//Pour Driver-N: configurée à partir du driver en fonction de la configuration countryID


/*_____II - DEFINE SBIT __________________________________________________*/

#define _LIST_FREQ

/*_____III - INCLUDE - DIRECTIVES ________________________________________*/
#include "../Include/headers.h"
#include "headers.h"

/*_____IV - VARIABLES GLOBALES ___________________________________________*/

//***************************************************************************
//**************** CONTENU DU FICHIER SYSTEM LISTFREQ.INI
//***************************************************************************
T_STRUCT_FILE_FIELD PT_DEF_STRUCT_CHANNEL[] = {
	{	CH_TAB_INDEX,		FTYPVAL_U16SOD,	NULL, 0,	0,	0},
	{	"ieee",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CHANNEL, u16_ieee)},
	{	"freq",				FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CHANNEL, u16_freq_MHz)},
	{	"flags",			FTYPVAL_U16SOD,	NULL, 0,	0,	MACRO_OFFSETOF(S_STRUCT_CHANNEL, u16_flags)},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

T_STRUCT_FILE_FIELD PT_CONTENU_FILE_LISTFREQ_INI[] = {
	{	"s_channel",	FTYPVAL_TABSTRUCT,	(struct T_STRUCT_FILE_FIELD*)PT_DEF_STRUCT_CHANNEL,	sizeof(S_STRUCT_CHANNEL),	NB_MAX_CHANNEL,	MACRO_OFFSETOF(S_STRUCT_LIST_FREQ, s_channel[0])	},
	{	NULL,	0,	NULL,	0,	0,	0	}
};

//****************************************
//DEFINITION DU FICHIER LISTFREQ.INI
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_LISTFREQ_INI =
{
	PATH_DIR__BDD_CONFIG "listfreq.ini", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
	PT_CONTENU_FILE_LISTFREQ_INI,//pt_contenu
};

//****************************************
//DEFINITION DU FICHIER IWLISTFREQ //Add by VuHai
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_IWLISTFREQ =
{
	PATH_DIR__BDD_CONFIG "iwlistfreq", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
};

//****************************************
//DEFINITION DU FICHIER HT40ALLOWMAP //Add by VuHai
//****************************************
T_STRUCT_DEFINITION_FILE_FS T_DEF_FILE_HT40_ALLOW_MAP =
{
	PATH_DIR__BDD_CONFIG "ht40_allow_map", //ps8_path_file
	DEFFILE_TYPE_SYSTEM, //u8_type
	FALSE,	//u8_avec_checksum
};


/*_____V - PROCEDURES ____________________________________________________*/

//=====================================================================================
// Fonction		: u8FillListFreqFile
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
// Sortie		: <loc_u8_resultat>	: Lecture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Lecture du fichier 
//=====================================================================================
u8sod u8FillListFreqFile(S_STRUCT_LIST_FREQ *loc_ps_list_freq)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = u8Transfert_FileToStruct(loc_ps_list_freq, &T_DEF_FILE_LISTFREQ_INI);
	if(FALSE == loc_u8_resultat)
	{
		MACRO_PRINTF(("u8FillListFreqFile KO \n"));
	}

	return loc_u8_resultat;
}/*u8FillListFreqFile*/

//=====================================================================================
// Fonction		: u8EditListFreqFile
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Ecriture  du fichier 
//=====================================================================================
u8sod u8EditListFreqFile(S_STRUCT_LIST_FREQ *loc_ps_list_freq)
{
	//u8sod loc_u8_resultat;VuHai

	//loc_u8_resultat = u8Transfert_StructToFile(loc_ps_list_freq, &T_DEF_FILE_LISTFREQ_INI);

	//Add by VuHai
	FILE *	loc_pf_file;
	FILE *	loc_pf_file_iwlist;
	FILE *	loc_pf_file_ht40allowmap;
	u8sod	loc_u8_resultat;
	u16sod loc_u16_i;
	f32sod f32_txpower;
	u16sod u16_ieee;	//Numero de canal
	u16sod u16_iwfreq_MHz;	//Valeur en MHz
	u16sod u16_htfreq_MHz;	//Valeur en MHz
	u16sod u16_flags;		//Flags
	s8sod str[10] = {'\0'};
	s8sod str2[10] = {'\0'};
	s8sod str3[10] = {'\0'};
	u16sod loc_u16_idx_line = 1;


	loc_u8_resultat = TRUE;	//INIT
	if(NULL == (loc_pf_file_iwlist = fopen(T_DEF_FILE_IWLISTFREQ.ps8_path_file, "r")))
	{
		MACRO_PRINTF(("u8EditListFreqFile: Erreur ouvert fichier %s\n",T_DEF_FILE_IWLISTFREQ.ps8_path_file));
		loc_u8_resultat = FALSE;
	}
	else
	{
		if(NULL == (loc_pf_file_ht40allowmap= fopen(T_DEF_FILE_HT40_ALLOW_MAP.ps8_path_file, "r")))
		{
			MACRO_PRINTF(("u8EditListFreqFile: Erreur ouvert fichier %s\n",T_DEF_FILE_HT40_ALLOW_MAP.ps8_path_file));
			loc_u8_resultat = FALSE;
		}
		else
		{
			if(NULL == (loc_pf_file = fopen(T_DEF_FILE_LISTFREQ_INI.ps8_path_file, "wt")))
			{
				MACRO_PRINTF(("u8EditListFreqFile: Erreur creation fichier %s\n",T_DEF_FILE_LISTFREQ_INI.ps8_path_file));
				loc_u8_resultat = FALSE;
			}
			else
			{
				while (!feof(loc_pf_file_iwlist)&&!feof(loc_pf_file_ht40allowmap))
				{
					fscanf(loc_pf_file_iwlist, "%s %hu MHz [%hu] (%f dBm)", str, &u16_iwfreq_MHz, &u16_ieee, &f32_txpower);
					//printf ("1111 iwchannel: %d \n", u16_iwfreq_MHz);
					fscanf(loc_pf_file_ht40allowmap, "%hu %s %s", &u16_htfreq_MHz, str2, str3);
					//printf ("2222 iwchannel: %d \n", u16_iwfreq_MHz);
					//printf ("2222 htchannel: %d \n", u16_htfreq_MHz);
					if ((strcmp(str2,"HT40"))==0)
					{  
						if (u16_iwfreq_MHz==u16_htfreq_MHz)
						{ 
							u16_flags = 0;//RAZ	
							if((u16_htfreq_MHz/1000)==2)
							{
								u16_flags |= (1 << BIT0_FLAG_CHANNEL_2GHZ);
							}
							if((u16_htfreq_MHz/1000)==5)
							{
								u16_flags |= (1 << BIT1_FLAG_CHANNEL_5GHZ);
							}
#ifdef _WRM100_N_SELECT
								//if(IEEE80211_IS_CHAN_11N_HT20(loc_pt_channel))
								//{
							u16_flags |= (1 << BIT2_FLAG_CHANNEL_HT20);
								//}
							if(strcmp(str3,"-+")==0)
							{
								u16_flags |= (1 << BIT3_FLAG_CHANNEL_HT40PLUS);
								u16_flags |= (1 << BIT4_FLAG_CHANNEL_HT40MINUS);
							}
							else if (strcmp(str3,"+")==0)
								u16_flags |= (1 << BIT3_FLAG_CHANNEL_HT40PLUS);
							else if (strcmp(str3,"-")==0)
								u16_flags |= (1 << BIT4_FLAG_CHANNEL_HT40MINUS);
							else printf ("unknow param HT40 -+ \n");
#endif						
							fprintf(loc_pf_file, "s_channel=|idx=%hu|ieee=%hu|freq=%hu|flags=%hu|\n", loc_u16_idx_line-1, u16_ieee, u16_htfreq_MHz, u16_flags);
							loc_u16_idx_line++;
						}
						else printf("u8EditListFreqFile: Conflict between 2 files iwlistfreq and ht40_allow_map\n");
					}
					
				}
				for (loc_u16_i=loc_u16_idx_line-1;loc_u16_i<NB_MAX_CHANNEL;loc_u16_i++)
				{
					fprintf(loc_pf_file,"s_channel=|idx=%hu|ieee=65535|freq=65535|flags=65535|\n",loc_u16_i);		
				}

				/*fprintf(loc_pf_file,"s_channel=|idx=0|ieee=1|freq=2412|flags=13|\n");
				fprintf(loc_pf_file,"s_channel=|idx=1|ieee=2|freq=2417|flags=13|\n");
				fprintf(loc_pf_file,"s_channel=|idx=2|ieee=3|freq=2422|flags=13|\n");
				fprintf(loc_pf_file,"s_channel=|idx=3|ieee=4|freq=2427|flags=13|\n");
				fprintf(loc_pf_file,"s_channel=|idx=4|ieee=5|freq=2432|flags=29|\n");
				fprintf(loc_pf_file,"s_channel=|idx=5|ieee=6|freq=2437|flags=29|\n");
				fprintf(loc_pf_file,"s_channel=|idx=6|ieee=7|freq=2442|flags=29|\n");
				fprintf(loc_pf_file,"s_channel=|idx=7|ieee=8|freq=2447|flags=29|\n");
				fprintf(loc_pf_file,"s_channel=|idx=8|ieee=9|freq=2452|flags=29|\n");
				fprintf(loc_pf_file,"s_channel=|idx=9|ieee=10|freq=2457|flags=21|\n");
				fprintf(loc_pf_file,"s_channel=|idx=10|ieee=11|freq=2462|flags=21|\n");
				fprintf(loc_pf_file,"s_channel=|idx=11|ieee=12|freq=2467|flags=21|\n");
				fprintf(loc_pf_file,"s_channel=|idx=12|ieee=13|freq=2472|flags=21|\n");
				fprintf(loc_pf_file,"s_channel=|idx=13|ieee=36|freq=5180|flags=14|\n");
				fprintf(loc_pf_file,"s_channel=|idx=14|ieee=40|freq=5200|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=15|ieee=44|freq=5220|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=16|ieee=48|freq=5240|flags=22|\n");
				fprintf(loc_pf_file,"s_channel=|idx=17|ieee=52|freq=5260|flags=14|\n");
				fprintf(loc_pf_file,"s_channel=|idx=18|ieee=56|freq=5280|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=19|ieee=60|freq=5300|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=20|ieee=64|freq=5320|flags=22|\n");
				fprintf(loc_pf_file,"s_channel=|idx=21|ieee=100|freq=5500|flags=14|\n");
				fprintf(loc_pf_file,"s_channel=|idx=22|ieee=104|freq=5520|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=23|ieee=108|freq=5540|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=24|ieee=112|freq=5560|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=25|ieee=116|freq=5580|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=26|ieee=120|freq=5600|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=27|ieee=124|freq=5620|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=28|ieee=128|freq=5640|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=29|ieee=132|freq=5660|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=30|ieee=136|freq=5680|flags=30|\n");
				fprintf(loc_pf_file,"s_channel=|idx=31|ieee=140|freq=5700|flags=22|\n");
				for (loc_u16_i=32;loc_u16_i<NB_MAX_CHANNEL;loc_u16_i++)
				{
					fprintf(loc_pf_file,"s_channel=|idx=%d|ieee=65535|freq=65535|flags=65535|\n",loc_u16_i);		
				}*/
				//fprintf(loc_pf_file,"s_channel=|idx=%d|ieee=65535|freq=65535|flags=65535|",loc_u16_i);
			}
		}
	}
	//fermeture du fichier
	fclose(loc_pf_file_iwlist);
	fclose(loc_pf_file_ht40allowmap);
	fclose(loc_pf_file);
	//Fixe permission du fichier
	u8CmdSystem_ChmodFile(T_DEF_FILE_LISTFREQ_INI.ps8_path_file, CHMOD_FILE_ROOT_751);
	return loc_u8_resultat;
}/*u8EditListFreqFile*/

//=====================================================================================
// Fonction		: u16GetIdx_ForChannelAndMode
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
//				: <loc_u16_numero_canal> : numero de canal
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u16_x_index>	: index dans s_channel[] si trouvé, sinon IDX_CHANNEL_UNKNOWN
// Auteur		: CM - 11/10/2010 -
// Description	: Retourne index dans s_channel[] du numéro canal et mode 802.11
//=====================================================================================
u16sod u16GetIdx_ForChannelAndMode(S_STRUCT_LIST_FREQ *loc_ps_list_freq, u16sod loc_u16_numero_canal, u8sod loc_u8_mode80211)
{
	u16sod loc_u16_x_index;
	u16sod loc_u16_i;
	S_STRUCT_CHANNEL *loc_ps_channel;

	loc_u16_x_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_ps_channel = NULL;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_CHANNEL;loc_u16_i++)
	{
		loc_ps_channel = &loc_ps_list_freq->s_channel[loc_u16_i];
		if(TRUE == u8IsChannelForMode80211(loc_ps_channel, loc_u8_mode80211))
		{
			if(loc_ps_channel->u16_ieee == loc_u16_numero_canal)
			{
				loc_u16_x_index = loc_u16_i;	//trouvé
				loc_u16_i = NB_MAX_CHANNEL+1;	//on sort
			}
		}
	}
	
	return loc_u16_x_index;
}/*u16GetIdx_ForChannelAndMode*/

//=====================================================================================
// Fonction		: u16GetIdx_Min_ForMode
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u16_x_index>	: index dans s_channel[] si trouvé, sinon IDX_CHANNEL_UNKNOWN
// Auteur		: CM - 11/10/2010 -
// Description	: Retourne index du canal minimum défini dans  s_channel[] pour mode 802.11
//=====================================================================================
u16sod u16GetIdx_Min_ForMode(S_STRUCT_LIST_FREQ *loc_ps_list_freq, u8sod loc_u8_mode80211)
{
	u16sod loc_u16_x_index;
	u16sod loc_u16_num_canal_min;
	u16sod loc_u16_i;
	S_STRUCT_CHANNEL *loc_ps_channel;

	loc_u16_x_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_ps_channel = NULL;	//INIT
	loc_u16_num_canal_min = 0xFFFF;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_CHANNEL;loc_u16_i++)
	{
		loc_ps_channel = &loc_ps_list_freq->s_channel[loc_u16_i];
		if(TRUE == u8IsChannelForMode80211(loc_ps_channel, loc_u8_mode80211))
		{
			if(loc_ps_channel->u16_ieee < loc_u16_num_canal_min)
			{
				loc_u16_num_canal_min = loc_ps_channel->u16_ieee;
				loc_u16_x_index = loc_u16_i;
			}
		}
	}

	return loc_u16_x_index;
}/*u16GetIdx_Min_ForMode*/

//=====================================================================================
// Fonction		: u16GetIdx_Max_ForMode
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données liste freq
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u16_x_index>	: index dans s_channel[] si trouvé, sinon IDX_CHANNEL_UNKNOWN
// Auteur		: CM - 11/10/2010 -
// Description	: Retourne index du canal maximum défini dans s_channel[] pour mode 802.11
//=====================================================================================
u16sod u16GetIdx_Max_ForMode(S_STRUCT_LIST_FREQ *loc_ps_list_freq, u8sod loc_u8_mode80211)
{
	u16sod loc_u16_x_index;
	s32sod loc_s32_num_canal_max;
	u16sod loc_u16_i;
	S_STRUCT_CHANNEL *loc_ps_channel;

	loc_u16_x_index = IDX_CHANNEL_UNKNOWN;	//INIT
	loc_ps_channel = NULL;	//INIT
	loc_s32_num_canal_max = -1;	//INIT

	for(loc_u16_i=0;loc_u16_i<NB_MAX_CHANNEL;loc_u16_i++)
	{
		loc_ps_channel = &loc_ps_list_freq->s_channel[loc_u16_i];
		if(TRUE == u8IsChannelForMode80211(loc_ps_channel, loc_u8_mode80211))
		{
			if((s32sod)(loc_ps_channel->u16_ieee) > loc_s32_num_canal_max)
			{
				loc_s32_num_canal_max = (u32sod)loc_ps_channel->u16_ieee;
				loc_u16_x_index = loc_u16_i;
			}
		}
	}

	return loc_u16_x_index;
}/*u16GetIdx_Max_ForMode*/

//=====================================================================================
// Fonction		: u8IsChannelForMode80211
// Entrees		: <loc_ps_channel< : pointeur sur canal
//				: <loc_u8_mode80211> : mode 802.11
// Sortie		: <loc_u8_resultat>	: ecriture OK(si TRUE), sinon FALSE
// Auteur		: CM - 11/10/2010 -
// Description	: Test si canal est valide pour mode 802.11 
//=====================================================================================
u8sod u8IsChannelForMode80211(S_STRUCT_CHANNEL *loc_ps_channel, u8sod loc_u8_mode80211)
{
	u8sod loc_u8_resultat;

	loc_u8_resultat = FALSE;	//INIT

	if(IEEE_CHANNEL_NO_VALID != loc_ps_channel->u16_ieee) //CONDITION: numéro de canal valide
	{
		switch(loc_u8_mode80211)
		{
			case MODE_WIFI_802_11G:
				if(loc_ps_channel->u16_flags & (1 << BIT0_FLAG_CHANNEL_2GHZ))
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11B:
				if(loc_ps_channel->u16_flags & (1 << BIT0_FLAG_CHANNEL_2GHZ))
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11A:
				if(loc_ps_channel->u16_flags & (1 << BIT1_FLAG_CHANNEL_5GHZ))
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NGHT20:
				if((loc_ps_channel->u16_flags & (1 << BIT0_FLAG_CHANNEL_2GHZ))&&
				   (loc_ps_channel->u16_flags & (1 << BIT2_FLAG_CHANNEL_HT20))
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NGHT40PLUS:
				if((loc_ps_channel->u16_flags & (1 << BIT0_FLAG_CHANNEL_2GHZ))&&
				   (loc_ps_channel->u16_flags & (1 << BIT3_FLAG_CHANNEL_HT40PLUS))
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NGHT40MINUS:
				if((loc_ps_channel->u16_flags & (1 << BIT0_FLAG_CHANNEL_2GHZ))&&
				   (loc_ps_channel->u16_flags & (1 << BIT4_FLAG_CHANNEL_HT40MINUS))
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NGHT40:
				if((loc_ps_channel->u16_flags & (1 << BIT0_FLAG_CHANNEL_2GHZ))&&
				   ((loc_ps_channel->u16_flags & (1 << BIT4_FLAG_CHANNEL_HT40MINUS))||
					  (loc_ps_channel->u16_flags & (1 << BIT3_FLAG_CHANNEL_HT40PLUS))
				   )
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NAHT20:
				if((loc_ps_channel->u16_flags & (1 << BIT1_FLAG_CHANNEL_5GHZ))&&
				   (loc_ps_channel->u16_flags & (1 << BIT2_FLAG_CHANNEL_HT20))
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NAHT40PLUS:
				if((loc_ps_channel->u16_flags & (1 << BIT1_FLAG_CHANNEL_5GHZ))&&
				   (loc_ps_channel->u16_flags & (1 << BIT3_FLAG_CHANNEL_HT40PLUS))
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NAHT40MINUS:
				if((loc_ps_channel->u16_flags & (1 << BIT1_FLAG_CHANNEL_5GHZ))&&
				   (loc_ps_channel->u16_flags & (1 << BIT4_FLAG_CHANNEL_HT40MINUS))
				  )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			case MODE_WIFI_802_11NAHT40:
			case MODE_WIFI_802_11ACHT80: //VuHai FixMe
				if((loc_ps_channel->u16_flags & (1 << BIT1_FLAG_CHANNEL_5GHZ))&&
				   ((loc_ps_channel->u16_flags & (1 << BIT4_FLAG_CHANNEL_HT40MINUS))||
					(loc_ps_channel->u16_flags & (1 << BIT3_FLAG_CHANNEL_HT40PLUS))
				   )
				 )
				{
					loc_u8_resultat = TRUE;
				}
				break;
			default:
				break;
		}
	}
	

	return loc_u8_resultat;
}/*u8IsChannelForMode80211*/

//=====================================================================================
// Fonction		: u16IeeeToMhz
// Entrees		: <loc_u16_ieee> : numéro de canal
// Sortie		: <loc_u16_frequence> : fréquence en MHz
// Auteur		: CM - 25/01/2011 -
// Description	: Retourne la fréquence associée au numéro du canal
//=====================================================================================
u16sod u16IeeeToMhz(u16sod loc_u16_ieee)
{
	u16sod loc_u16_frequence;

	loc_u16_frequence = 0; //INIT

//d: zone copie code ieee80211_ieee2mhz (de wlanconfig.c)
	if(loc_u16_ieee <= 255)
	{
		if(14 == loc_u16_ieee)
		{
			loc_u16_frequence = 2484;
		}
		else
		{
			if(loc_u16_ieee < 14)			/* 0-13 */
			{
				loc_u16_frequence = 2407 + loc_u16_ieee*5;
			}
			else
			{
				if(loc_u16_ieee < 27)			/* 15-26 */
				{
					loc_u16_frequence = 2512 + ((loc_u16_ieee-15)*20);
				}
				else
				{
					loc_u16_frequence = 5000 + (loc_u16_ieee*5);
				}
			}
		}
	}
//f: zone copie code ieee80211_ieee2mhz (de wlanconfig.c)

	return loc_u16_frequence;
}/*u16MhzToIeee*/

//=====================================================================================
// Fonction		: u16MhzToIeee
// Entrees		: <loc_u16_frequence> : fréquence en MHz
// Sortie		: <loc_u16_ieee> : numéro de canal, sinon si freq invalid, CHANNEL_RADIO_DISABLED
// Auteur		: CM - 25/01/2011 -
// Description	: Retourne numéro du canal associé à la fréquence
//=====================================================================================
u16sod u16MhzToIeee(u16sod loc_u16_frequence)
{
	u16sod loc_u16_ieee;

	loc_u16_ieee = CHANNEL_RADIO_DISABLED; //INIT

//d: zone copie code ieee80211_mhz2ieee (de wlanconfig.c)
	if(0 != loc_u16_frequence)
	{
		if(2484 == loc_u16_frequence)
		{
			loc_u16_ieee = 14;
		}
		else
		{
			if(loc_u16_frequence < 2484)
			{
				loc_u16_ieee = (loc_u16_frequence-2407)/5;
			}
			else
			{
				if(loc_u16_frequence < 5000)
				{
					loc_u16_ieee = (loc_u16_frequence - 4800) / 5 + 216; // 216 = (6080MHz - 5000MHz) / 5 , 6080MHz is the first freq which Atheros Hardware cannot achieve anymore
				}
				else
				{
					loc_u16_ieee = (loc_u16_frequence - 5000) / 5;
				}
			}
		}
	}
//f: zone copie code ieee80211_mhz2ieee (de wlanconfig.c)
	
	return loc_u16_ieee;
}/*u16MhzToIeee*/


/*_____VI - PROCEDURE D'INITIALISATION ___________________________________*/

//=====================================================================================
// Fonction		: BuildListFreq
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données à initialiser
//				: <loc_pt_req_listchans< : pointeur sur requete listchan (réponse du driver)
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Construction de la base de données de la liste des frequences pour driver-N et Driver-ABG
//=====================================================================================
void BuildListFreq(S_STRUCT_LIST_FREQ *loc_ps_list_freq, struct ieee80211req_chaninfo *loc_pt_req_listchans)
{
	/*u16sod loc_u16_cpt;
	u16sod loc_u16_i;
	u16sod loc_u16_frequence;
	u16sod loc_u16_ieee;
	struct ieee80211_channel *loc_pt_channel;*/
	s32sod	loc_s32_sem;

	/*loc_u16_cpt = 0;	//INIT
	loc_u16_frequence = 0;	//INIT
	loc_u16_ieee = 0;	//INIT*/

	s32Lock_Get(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on leve le semaphore
	
	/*memset(loc_ps_list_freq,0xFF,sizeof(S_STRUCT_LIST_FREQ)); //RAZ
	
	for (loc_u16_i=0; ((loc_u16_i<loc_pt_req_listchans->ic_nchans)&&(loc_u16_i < NB_MAX_CHANNEL)); loc_u16_i++)
	{
		if(loc_u16_cpt < NB_MAX_CHANNEL)
		{
			loc_pt_channel = &loc_pt_req_listchans->ic_chans[loc_u16_i]; //RAZ

			loc_u16_frequence = (u16sod)loc_pt_channel->ic_freq;
			loc_ps_list_freq->s_channel[loc_u16_cpt].u16_freq_MHz = loc_u16_frequence;
//			printf("%d: %dMHz maxregpower=%d ic_maxpower=%d ic_minpower=%d regClassId=%d \n",loc_u16_i,loc_pt_channel->ic_freq,loc_pt_channel->ic_maxregpower,loc_pt_channel->ic_maxpower,loc_pt_channel->ic_minpower,loc_pt_channel->ic_regClassId);

			loc_u16_ieee = u16MhzToIeee(loc_u16_frequence);
			if(CHANNEL_RADIO_DISABLED == loc_u16_ieee)
			{
				loc_u16_ieee = 0; //RAZ
			}			

			loc_ps_list_freq->s_channel[loc_u16_cpt].u16_ieee = loc_u16_ieee;
			loc_ps_list_freq->s_channel[loc_u16_cpt].u16_flags = 0;	//RAZ
			if(IEEE80211_IS_CHAN_2GHZ(loc_pt_channel))
			{
				loc_ps_list_freq->s_channel[loc_u16_cpt].u16_flags |= (1 << BIT0_FLAG_CHANNEL_2GHZ);
			}
			if(IEEE80211_IS_CHAN_5GHZ(loc_pt_channel))
			{
				loc_ps_list_freq->s_channel[loc_u16_cpt].u16_flags |= (1 << BIT1_FLAG_CHANNEL_5GHZ);
			}
#ifdef _WRM100_N_SELECT
			if(IEEE80211_IS_CHAN_11N_HT20(loc_pt_channel))
			{
				loc_ps_list_freq->s_channel[loc_u16_cpt].u16_flags |= (1 << BIT2_FLAG_CHANNEL_HT20);
			}
			if(IEEE80211_IS_CHAN_11N_CTL_U_CAPABLE(loc_pt_channel))
			{
				loc_ps_list_freq->s_channel[loc_u16_cpt].u16_flags |= (1 << BIT3_FLAG_CHANNEL_HT40PLUS);
			}
			if(IEEE80211_IS_CHAN_11N_CTL_L_CAPABLE(loc_pt_channel))
			{
				loc_ps_list_freq->s_channel[loc_u16_cpt].u16_flags |= (1 << BIT4_FLAG_CHANNEL_HT40MINUS);
			}
#endif

			//on incremente
			loc_u16_cpt++;
		}
	}*/

	u8EditListFreqFile(loc_ps_list_freq);
	//u8EditListFreqFile();
	u8Transfert_FileToStruct(loc_ps_list_freq, &T_DEF_FILE_LISTFREQ_INI);
	
	s32Lock_Release(SEMAPHORE_BDD_LIST_FREQ, &loc_s32_sem);	//on relache le sem
	
}/*BuildListFreq*/

//=====================================================================================
// Fonction		: InitBDD_ListFreq
// Entrees		: <loc_ps_list_freq< : pointeur sur la base de données à initialiser
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation de la base de données de la liste des frequences
//=====================================================================================
void InitBDD_ListFreq(S_STRUCT_LIST_FREQ *loc_ps_list_freq)
{
	memset(loc_ps_list_freq,0xFF,sizeof(S_STRUCT_LIST_FREQ)); //INIT
	
	//On attend la configuration du driver par setCountryID
	
}/*InitBDD_ListFreq*/

//=====================================================================================
// Fonction		: InitModule_ListFreq
// Entrees		: rien
// Sortie		: rien
// Auteur		: CM - 11/10/2010 -
// Description	: Initialisation du module de listfreq de l'équipement
//=====================================================================================
void InitModule_ListFreq(void)
{
	
}/*InitModule_ListFreq*/