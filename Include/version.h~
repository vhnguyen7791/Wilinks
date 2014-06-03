/*========================================================================*/
/* NOM DU FICHIER  : Version.h											  */
/*========================================================================*/
/* Compilateur     : GCC                                                  */
/* Linking locator : GCC                                                  */
/* Formatter       : GCC                                                  */
/* Auteur          : CM                                                   */
/* Date			   : 09/09/2009											  */
/* Libelle         : Base de données: version							  */
/* Projet          : WRM100                                               */
/* Indice          : BE065												  */
/*========================================================================*/
/* Historique      :                                                      */
//BE000 09/09/2009 CM
// - CREATION
/*========================================================================*/

/*_____I - COMMENTAIRES - DEFINITIONS -  REMARQUES _______________________*/

// * Configurer la toolchain:
//export PATH=/home/cm/WindRiver/wrlinux-3.0/layers/wrll-toolchain-4.3-85/powerpc/toolchain/x86-linux2/bin:$PATH
// * Pour compiler sous <DIR_PRJ>:
//make boot-image BOOTIMAGE_FSTYPE=initramfs BOOTIMAGE_TYPE=flash

/*_____II - DEFINE SBIT __________________________________________________*/


#define		VERSION_BE	"BE065.1 CM 02/05/2012" //- Affichage version be dans page debug

#ifdef _WRM100_ABG_SELECT //X106536
	#define VERSION_OFFICIELLE " 4 "
#endif

#ifdef _WRM100_N_SELECT //X106600
	#define VERSION_OFFICIELLE " 11 "
#endif


//----------------------------------------------------
// LISTE EVOLUTION LOGICIELLE
//----------------------------------------------------
//BE000 09/09/2009 CM
// - CREATION
//	source basée sur BE369 (SDVB200)
// - Modification du source du kernel (2.6.27.18)
//		-> [IMPACT] <dir>_prj/build/linux/arch/powerpc/include/asm/mpc52xx_psc.h
//		-> [IMPACT] <dir>_prj/build/linux/arch/powerpc/platforms/52xx/lite5200.c
//		-> [IMPACT] <dir>_prj/build/linux/drivers/mtd/nand/Makefile
//		-> [IMPACT] <dir>_prj/build/linux/drivers/mtd/nand/powerengine_nand.c (new file)
//		-> [IMPACT] <dir>_prj/build/linux/drivers/net/fec_mpc52xx.c
//		-> [IMPACT] <dir>_prj/build/linux/drivers/net/fec_mpc52xx.h
//		-> [IMPACT] <dir>_prj/build/linux/drivers/net/fec_mpc52xx_phy.c
//		-> [IMPACT] <dir>_prj/build/linux/drivers/serial/mpc52xx_uart.c
// - Correction package boa (pour lancer boa en root, sinon impossible de faire des actions en root, par exemple copie)
//		-> [IMPACT] <dir>_prj/build/boa-0.94.13/src/boa.c
// - Ajout package hostapd-0.6.9 (qui n'est pas compris dans les sources WindRiver)
// - Correction package net-snmp (ajout mib WRM100)
//		-> [IMPACT] <dir>_prj/build/net-snmp-5.4-xxxxx/BUILD/net-snmp-xx/agent/snmpd.c
//		-> [IMPACT] <dir>_prj/build/net-snmp-5.4-xxxxx/BUILD/net-snmp-xx/agent/mibgroup: ln -s ../../../../../../../WRM100_APPLI/Source/net-snmp/sodielec/
// - Ajout gestion filesysteme pour WRM100_APPLI
//		-> [IMPACT] <dir>_prj/fs_final00.sh
// - Correction type s8sod (ajout "signed") (car sur PowerPC char is not signed char)
//BE001 01/12/2009 CM
// - Mise à jour du "Update Pack 1 for Wind River Linux 3.0"
//		=> correction montage en yaffs2 d'une partition de la FLASH NAND
// - Evolution du source du kernel  (2.6.27.18)
//		-> [IMPACT] <dir>_prj/build/linux/arch/powerpc/platforms/52xx/lite5200.c (new)
//		-> [IMPACT] <dir>_prj/build/linux/drivers/serial/mpc52xx_uart.c (new)
// - Montage en YAFFS2 d'un système de fichiers en NAND (partiton config) pour sauver la configuration
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//		-> [IMPACT] <dir>_prj/filesystem/fs-install: add /dev/mtdblock7
//BE002 14/12/2009 CM
// - Intégration du projet dans une Layer
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/boa-0.94.13.tar.gz
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/bridge-utils-1.2-6.fc10.src.rpm
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/hostapd-0.6.9.tar.gz
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/mtd-utils-1.2.0-1.fc10.src.rpm
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/ncurses-5.6-19.20080628.fc10.src.rpm
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/net-snmp-5.4-13.fc7.src.rpm*
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/openssl-0.9.8g-5.fc9.src.rpm
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/readline-5.2.tar.gz
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/wireless-tools-29-2.fc9.src.rpm
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/wpa_supplicant-0.5.10-5.fc8.src.rpm
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/packages/yaffs2-2006-01-30.tar.gz
// - Modification définition des partitions de la flash NOR
//		ce n'est plus définit dans le fichier dts, mais dans <dir>_prj/build/linux/drivers/mtd/maps/powerengine.c
//		-> [IMPACT] <dir>_prj/build/linux/drivers/mtd/maps/Makefile
//		-> [IMPACT] <dir>_prj/build/linux/drivers/mtd/maps/Kconfig
//		-> [IMPACT] <dir>_prj/build/linux/drivers/mtd/maps/powerengine.c (new file)
//		-> [IMPACT] <dir>_prj/build/linux-fsl-xxx/.config
//				$$ désactivation CONFIG_MTD_PHYSMAP_OF
//				$$ activation CONFIG_MTD_POWERENGINE=y (new parameter)
//
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/templates/default/fs/fs-install-only
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//		compatible avec version U-BOOT version BE05
//		compatible avec version wrm100.dts version BE02
// - Probleme avec mtd device de type char lors des commandes flash_eraseall, flash_info ....
//		-> [IMPACT] <dir>_prj/build/linux-fsl-xxx/.config
//				$$ activation CONFIG_MTD_CHAR
// - Ajout gestion mise à jour de l'application par ssh rcp
//		-> ajout processus update
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//		-> ajout fichier infosystem.[ch] dans /LibraryBdd
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/001_netsnmp_sodielec.patch
// - Récupération de la version du bootloader
//		-> ajout processus getversion_uboot
//BE003 22/12/2009 CM
// - Configuration busybox: ajout commande "top"
//		-> Process Utilities -> [*] top
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/busybox/
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/busybox-1.11.1.tar.bz2
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/templates/feature/busybox/pkglist.add
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Modification chemin des fichiers de configuration
//		/home/httpd/boa.conf => /etc/boa/boa.conf   + [IMPACT] /etc/inittab
//		/tmp/hostapd.conf => /etc/hostapd.conf
//		/tmp/wpa_supplicant.conf => /etc/wpa_supplicant.conf
//		-> [IMPACT] <dir>_prj/fs_final00.sh
// - Modification chemin des fichiers de pid
//		/var/snmpd.pid => /var/run/snmpd.pid
//		/var/hostapd.pid => /var/run/hostapd.pid
//		/var/wpa_supplicant.pid => /var/run/wpa_supplicant.pid
// - Intégration configuration par DHCP client
//		ajout paramètres de configuration (adresse IP de repli en DHCP)
// - Intégration configuration hostname
//		la fonction hostname permet à un utilisateur d'accéder aux serveurs du WRM100, si celui-ci a
//		son adresse IP attribué par un serveur DHCP couplé à un serveur DNS dynamique.
//		Cette configuration est optionnelle. Les espaces et tabulations ne sont pas autorisés.
// - Modification javascript isValidText
//		possibilité d'interdire la saisie de caractères espaces
// - Ajout exploitation adresse IP/Mask des interfaces
//		=> ajout page HTML Exploitation - Réseau
// - Gestion "force modules wifi" si version magic entre kernel et modules différente
//	(dans le cas où la version magic entre les modules et le kernel est différente)
//	 il suffit de poster dans /mnt/nand-config le fichier "force_modules_wifi.on"
//	 pour forcer à charger les fichiers malgré que la version magic est différente
//	 a utiliser uniquement au cours du développement si nécessaire
//	 avec configuration du kernel: CONFIG_MODULE_FORCE_LOAD=y
//		-> [IMPACT] WRM100_APPLI/FileSystem/tmp/driver/force_load_modules_ap.sh
//		-> [IMPACT] WRM100_APPLI/FileSystem/tmp/driver/force_load_modules_sta.sh
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Modification configuration de busybox
//		car il manque des outils suite à l'intégration projet dans une layer
//			(date, pidof, tail, usleep, ....)
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Modification configuration du noyau
//		car il manque gestion bridge suite à l'intégration projet dans une layer (CONFIG_BRIDGE)
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxxx/templates/default/linux/enable-export_layer.cfg   [FICHIER DE CONFIGURATION KERNEL]
//BE004 13/01/2010 CM
// - Modification layer wpa_supplicant
//		car fichier de configuration .config incorrecte (pas de référence à madwifi)
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/wpa_supplicant/patches/wpa_supplicant.WRS.config
//				(CONFIG_DRIVER_MADWIFI=y et CFLAGS += -I......)
//BE005 14/01/2010 CM
// - Intégration serveur DHCP + relai DHCP
//		-> ajout page HTML Configuration - DHCP serveur /relai
// - Modification configuration de busybox
//		suppression des fonctions "console utilities"
//		ajout option ps wide
//		ajout dhcp server + dhcp relay
//		ajout option dans dhcp client: verify that the offered address is free, using ARP ping
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Ajout option arping pour le client DHCP
//	afin de vérifier que l'adresse proposée par le serveur DHCP n'est pas déjà utilisée
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Correction bug saisi mode ip WLAN (page HTML Configuration - Network)

//BE006 20/01/2010 CM
// - Modification gestion couche basse base de données de fichiers
//	=> ajout gestion tableau de données
//	=> ajout gestion adresse MAC
//	=> ajout information supplémentaire sur définition du contenu du fichier
//		(cas de variable de type string: on rajoute la longueur max autorisée)
// - Modification définition de certains fichiers de la base de données
//		suite aux modifications en couche basse
//		-> [IMPACT] Incompatibilité de la configuration avec version précédente (donc config/defaut)
//  => passage nombre de routes static de 12 à 20
// - Correction page HTML Configuration - Routage
//	ne pas autoriser l'ajout d'une route lorsque la table est pleine
// - Modification gestion couche haute des fichiers
//		modif appel u8Transfert_StructToFile, u8Transfert_FileToStruct, u8Display_FileToStruct
// - Ajout outil pour tester format fichier (test_tools -file) (debug)

//BE007 25/01/2010 CM
// - Correction bug hostapd lors de modification paramètres réseau (en particulier ath0 down)
//	=> la connexion WPA n'était plus possible suite à une modification de paramètres réseau
//	il faut reconfigurer alors hostapd
// - Ajout dans configuration du noyau (gestion temps message du kernel + augmentation taille log kernel)
//		=> CONFIG_PRINTK_TIME
//		=> CONFIG_BUF_SHIFT: 14 (16ko) => 17 (128ko)
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxxx/templates/default/linux/enable-export_layer.cfg   [FICHIER DE CONFIGURATION KERNEL]
// - Ajout exploitation de l'ACCESS POINT
//	=> nb stations associés
//	=> tableau des clients (connus par l'access point) avec statut du client
//  => modification page HTML Exploitation - Wifi (Access point)
// - Ajout nouveaux fichiers def_configfiles.[ch], def_exploitfiles.[ch], resetfile.[ch]
//	et suppression fichier cst_bddfile.[ch]
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout configuration du "forward delay" du bridge 
//	C'est conseillé pour l'utilisation de hostapd (voir madwifi-project.org/wiki/UserDocs/HostAP) : "brctl setfd br0 0"
// - Modification gestion routage statique
//	=> ajouter filtre saisie sur page HTML Configuration - Routage
//	=> pour une route vers un host: il faut que le masque de sous-réseau soit à 255.255.255.255
//	=> pour une route vers un sous-réseau: il faut que l'adresse IP de destination et le masque forme bien un sous-réseau
//	=> toute reconfiguration de l'interface WLAN nécessite la reconfiguration de la table de routage (concernant l'accès WLAN)

//BE008 28/01/2010 CM
// - Modification chemin des fichiers de configuration
//		/var/snmpd.conf => /etc/snmp/snmpd.conf
//		-> [IMPACT] <dir>_prj/fs_final00.sh
// - Ajout syslog: journalisation du système
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Modification page HTML langue (+générique)
// - Gestion fichier configuration debug.ini
// - Modification package hostapd 
//	-> suppression debug "Dumping hostapd state ... " (car pollue la console en mode debug)
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/hostapd/patches/002_hostapd_sodielec.patch

//BE009 01/02/2010 CM
// - Ajout client NTP
//	Modification bdd de configuration: NTP (et non SNTP)
//	nouveaux packages: ntp + timezone (+ attr + libcap + db4 + flex + pam)
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/pkglist.add
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/templates/default/fs/fs-install-only
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/ntp-4.2.4p0-1.fc7.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/tzcode2008e.tar.gz
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/tzdata2008e.tar.gz
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/attr-2.4.43-1.fc10.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/libcap-2.10-2.fc10.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/db-4.6.21.tar.gz
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/flex-2.5.35-1.fc9.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/flex-2.5.35.tar.bz2
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/pam_passwdqc-1.0.2-1.2.2.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/Linux-PAM-1.0.1.tar.bz2

//BE010 03/02/2010 CM
// - Ajout routeur NAT (Network Address Translation)
//	nouveau package: iptables
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/iptables
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/iptables/patches/iptables-wr-integration.patch
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/iptables-1.4.0-4.fc9.src.rpm
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/pkglist.add
//  nouvelle configuration du kernel
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxxx/templates/default/linux/enable-export_layer.cfg   [FICHIER DE CONFIGURATION KERNEL]
// - Correction problème accès au serveur HTTP (dernière un serveur NAT, avec port forwarding)
//	si un client HTTP (sur le réseau public) se connecte au serveur WEB de l'équipement (du réseau privé) derrière
//	un serveur NAT configuré en port forwarding (redirection de port) 8080 => 80
//	en saisissant http://xxx.yyy.zzz.www:8080 sur le navigateur, alors le serveur WEB ne sera pas accessible
//	--> problème javascript : on recharge la page HTML en chemin absolue et non en relatif
//		self.location.replace(\"http://\" + document.location.hostname + \"/cgi-bin/cgi_fh?URL=XXXXXX)
// - Ajout fonction arping
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Correction BUG lecture fichier avec variable dans tableau de type string contenant des espaces
//	--> les espaces ne sont pas pris en compte à la lecture du contenu du fichier
// - Correction test configuration des adresses IP des interfaces
//  --> vérification que l'adresse IP n'est pas une adresse nulle pour le masque de sous-réseau défini
//  --> vérification que l'adresse IP n'est pas une adresse de broadcast pour le masque de sous-réseau défini
//  --> vérification que le sous-réseau du LAN soit différent du sous-réseau du WLAN / ip statique (mode router)
//  --> vérification que l'adresse IP de repli doit etre différente du sous-réseau du LAN (mode router)
// - Ajout information statut IP des interfaces
//		valeur: static, DHCP in progress, success DHCP, failure DHCP
// - Modification processus update (independance avec principal)
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//		-> on lit la version de uboot directement dans le fichier généré aud démarrage
//		-> on reboot la carte à la fin du téléchargement (15 secondes après, au cas où le process principal ne le fait pas)
// - Correction configuration / defaut de la station (champs: u8_type_selection_canal)
// - Correction BUG statut des clients Wifi erroné (en mode non sécurisé)
//		-> affiche "non associé" au lieu de "associé"


//BE011 18/02/2010 CM
// - Correction layer
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/hostapd/Makefile
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/templates/default/fs_final.sh
// - Ajout script pour installer un projet plate-forme linux
//		-> [IMPACT] ADD WRM100_APPLI/INSTALL_PROJECT_PLATFORM.sh
//		-> [IMPACT] ADD WRM100_APPLI/Makefile_Sodielec
// - Ajout script pour installer le projet application
//		-> [IMPACT] ADD WRM100_APPLI/INSTALL_MAKEFILE_APPLI.sh

//BE012 24/02/2010 CM
// - Correction chemin du fichier snmpd.conf
// - Integration SNMPv1/SNMPv2c
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/002_netsnmp_sodielec.patch
// - Disable ipv6 pour net-snmp
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout dans net-snmp la mib-module "ieee802dot11"
//	 avec patch téléchargé de https://dev.openwrt.org/browser/packages/libs/net-snmp/patches/750-ieee802dot11.patch?rev=16593
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/patches/750-ieee802dot11.patch
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout package vlan
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/vlan
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/vlan.1.9.tar.gz
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/pkglist.add
// - Modification nom de l'interface "BRIDGE"
//		"bridge" remplacé par "br0"

//BE013 26/02/2010 CM
// - Correction bug javascript page configuration Wifi
//		cght du mode wifi avec plusieurs canaux
// - Intégration gestion des évènements
//		-> nouveau fichier source: LibraryBdd/event.[ch]
//		-> nouveau fichier source: LibraryBdd/cip_trap.[ch]
//		-> nouveau fichier source: LibraryBdd/cip_snmpd.[ch]
//		-> nouveau fichier source: LibraryBdd/cip_monitor.[ch]
//		-> nouveau processus "monitor": calcul des alarmes/infos, extrait l'exploitation
//		-> nouveau fichier source: Monitor/execmonitor.[ch]
//		-> nouveau fichier source: Monitor/custom_bdd.[ch]
//		-> nouveau fichier source: Monitor/Event/statevent.[ch]
//		-> nouveau fichier source: Monitor/Event/execevent.[ch]
//		-> nouveau fichier source: Monitor/Event/evt_generique.[ch]
//		-> nouveau fichier source: net-snmp/Sodielec/statustrap.[ch]
//		-> [IMPACT] WRM100_APPLI/Layer/vxx/templates/default/fs/fs-install-only
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/003_netsnmp_sodielec.patch
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/fs_final.sh
// - Modification chemins des bdd (sous /tmp)
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Ajout type FTYPVAL_DATE dans gestion des fichiers
// - Ajout fonction lecture / écriture dans fichier ligne par ligne
// - Ajout fonction affichage de la date complète
// - Ajout fonction pour calculer le nombre de ligne d'un fichier (commande linux)
// - Ajout fonction pour supprimer fichier (commande linux)
// - Correction package net-snmp pour limiter nombre max de requete par destinataire
//		dans le but de ne pas trop utiliser de mémoire
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/004_netsnmp_sodielec.patch

//BE014 08/03/2010 CM
// - Modification gestion de l'exploitation
//	=> toute l'exploitation est calculée dans le processus 'monitor'.
// - Modification demande du fichier hostapd.dump
//			=> demande pour la prochaine seconde
// - Correction bug appel udhcpc (client) commamde ligne trop grande
//		->toutes les options ne sont pas passées (défaut lié à la busybox, mais défaut non corrigé)
//		taille limite des options de udhcpc est de 100 caractères
//		en attendant, on diminue la taille de la commande udhcpc
// - Ajout option compilation "-Wall" + correction w@rning
//		ex de correction formattage texte pour un u32sod:"%u" => "%lu" et s32sod:"%d" => "%ld" 
// - Ajout option de compilation -fsigned-char
//		pour que char soit considéré comme signé (sinon w@rning à la compilation avec Wall sur des fonctions de type strcmp,...)

//BE015 09/03/2010 CM
// - Ajout gestion du journal de bord
//		-> nouveau fichier source: LibraryBdd/bddjdb.[ch]
//		-> nouveau fichier source: LibraryBdd/cip_jdb.[ch]
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
//		-> nouveau fichier source: Principal/Config/cfg_jdb.[ch]
//		-> nouveau processus 'jdb'
//			-> nouveau fichier source: jdb/execjdb.[ch]
//			-> nouveau fichier source: jdb/jdbflash.[ch]
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/fs_final.sh
//- Nouvelle partition "jdb-flash" dans la FLASH NAND (dédiée à la sauvegarde du jdb) de 2Mo: mtd13
//		-> modification taille partition "user" dans la FLASH NAND: 56Mo -> 54Mo
//		-> modification numéro mtd partition "user" dans la FLASH NAND : mtd13 -> mtd14 
//			-> [IMPACT] MODIFIY Layer/vxxx/templates/default/linux/linux.scc
//			-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0003_linux_sodielec.patch
//						-> [IMPACT] <dir>_prj/build/linux/drivers/mtd/maps/powerengine.c
//			-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal

// - Correction fichier style.css - suppression ligne "input.boutonDefault"
//		car w@rning sur console du navigateur
//		-> [IMPACT] MODIFY WRM100_APPLI/FileSystem/home/httpd/style.css

//BE016 11/03/2010 CM
// - Modification struture de la gestion interne des évènements
//		-> S_STRUCT_STATUS_EVENTS remplacé par S_STRUCT_INTERNAL_EVENTS
//		-> Suppression fichier source td_statevent.h
//		-> internevent.[ch] remplacés par statevent.[ch] pour processus monitor
//		-> Suppression sémaphore SEMAPHORE_BDD_STAT_EVENTS
// - Ajout gestion des alarmes
//		-> nouveau fichier source: LibraryBdd/td_exp_event.h
//		-> nouveau fichier source: LibraryBdd/exp_event.[ch]
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout calcul evt EquipmentOn

//BE017 12/03/2010 CM
// - Correction bug evt Equipment ON non calculé
// - Correction risque de corruption du journal de bord sauvé en FLASH (statut erroné) lors de la rotation
//	en effet, il faut que les pointeurs rd/wr soient cohérents pendant la rotation (dans le cas d'un coupure secteur)
//	donc, on implémente 3 étapes:
//			1) on incrémente pointeur lecture => sauve statutjdb en flash
//			2) on supprime l'ancien fichier pointé par pointeur rd et on crée un fichier vide
//			3) on incrémente pointeur ecriture => sauve statutjdb en flash
// - Ajout structure simple dans gestion bddfile
//		=> pour cela il faut définir comme valeur u16_nb_max_elt=0 dans T_STRUCT_FILE_FIELD
// - Optimisation contenu des fichiers jdbpart, cip_fifojdb et cip_fifotrap
// - Optimisation contenu du fichier evt_global.exp

//BE018 15/03/2010 CM
// - Correction libellé page HTML Configuration - Mode
// - Correction libellé page HTML Configuration - DHCP
// - Correction risque de corruption du journal de bord sauvé en FLASH lors de l'écriture d'un évènement
//	en effet, on va sécurisé l'écriture dans le fichier jdbpart en doublant l'écriture dans un autre fichier (jdbcur.log)

//BE019 16/03/2010 CM
// - Correction erreur boa "favicon.ico" non présent
//		-> [IMPACT] ADD WRM100_APPLI/FileSystem/home/httpd/favicon.ico (transparent)
// - Ajout MIB administration dans agent SNMP
//		-> nouveau fichier source: net-snmp/sodielec/mib_administration.[ch]
//		-> nouveau fichier source: net-snmp/sodielec/mib_administration_data.[ch]
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Correction libellés page HTML Configuration - SNMP
// - Suppression trap specific (3) émis à chaque modif de config de net-snmp
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/005_netsnmp_sodielec.patch
// - Suppression trap specific (2) émis à chaque command "reboot" de la carte
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/005_netsnmp_sodielec.patch
// - Correction envoi trap coldstart uniquement si émission trap autorisé
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/005_netsnmp_sodielec.patch
// - Ajout MIB wrm100 dans agent SNMP
// - Ajout gestion sysservice de la MIB-II
// - Suppression des mibs intégrées par défaut par net-snmp
//		UCD-SNMP-MIB, NET-SNMP-AGENT-MIB 
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout option compilation pour net-snmp -fsigned-char
//	pour qu'il gère le char comme signé
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout option de compilation "-fsigned-char" pour gérer les valeurs char signées (telle que s8_fuseau_horaire)
// - Optimisation contenu du fichier newcfg.ini
// - Autorisation de passer la station en bridge

//BE020 23/03/2010 CM
// - Ajout gestion VLAN
// - Correction erreur javascript dans page HTML Configuration - DHCP
// - Correction w@rning dans FireFox "Element referencé par son ID/NAME ..."

//BE021 24/03/2010 CM
// - Ajout package tcpdump (afin de sniffer les paquets reçus sur les interfaces)
//	=> necessite packages "tcpdump + shadow-utils + libpcap" [EN OPTION]: il suffira d'ajouter ces packages dans pkglist.add
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/libpcap
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/shadow-utils
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/tcpdump
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/libpcap-0.9.8-2.fc9.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/shadow-utils-4.1.1-1.fc9.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/tcpdump-3.9.5-3.fc7.src.rpm
// - Correction BUG liaison bridge-bridge

//BE022 29/03/2010 CM
// - Ajout gestion multicast
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/igmpproxy
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/igmpproxy-0.1.tar.gz
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/pkglist.add
// - Ajout fonction générique test masque sous-réseau
// - Ajout fonction générique test ip de type NET
// - Correction bug dhcp fallback sur station / bridge

//BE023 01/04/2010 CM
// - Correction w@rning du linux (kernel)
//		sources corrigés: lite5200.c + powerengine_nand.c
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0004_linux_sodielec.patch
// - Ajout gestion premier démarrage du processus principal
//		=> avec gestion du fichier firststart.on (créé par S22principal et supprimé par principal)
//		permet de gérer la désinstallation de la configuration
//			-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal

//BE024 03/04/2010 CM
// - Ajout option "-mlongcall" pour compiler shared library (pour utilisation future)
//		=> fichier ".wrproject" du workbench
// - Correction test config Multicast
// - Correction suite revue de codage de Caf (sur BE023)
//		Tout sauf net-snmp et html_cgi
// - Ajout nouvelle configuration du kernel pour pouvoir faire du politique de routage IP
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxxx/templates/default/linux/enable-export_layer.cfg   [FICHIER DE CONFIGURATION KERNEL]

//BE025 15/04/2010 CM
// - Ajout gestion politique de routage IP
// - Ajout gestion routage dynamique RIPv2
//		assuré par le processus bird
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/bird
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/bird-1.2.1.tar.gz
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/pkglist.add
// - Correction bug passerelle perdue (quand interface down) (cas avec cmd route)
// - Modification gestion routage par le processus bird
//	et non plus via des commandes de type "route" 
//		-> impact routage statique / routage passerelle (coté STATION / ROUTER)
//	par contre, le routage multicast reste configurable par la commande route
//	de plus, on modifie la méthode de configuration des routes statiques:
//	 la métric n'est plus utilisée
//	 l'interface sélectionnée est prioritaire sur la passerelle (3 valeur possibles: automatique, LAN, WLAN)
// - Modification gestion reconfiguration (quand interface down)
//	=> on simplifie la gestion des ordres de reconfiguration
// - Ajout test configuration fonctionnelle pour le routage
// - Correction désinstallation wpa_supplicant (à sécuriser)
//	car le processus wpa_supplicant se tue lentement

//BE026 26/04/2010 CM
// - Correction gestion passerelle via bird (qd station / router en client DHCP)
// - Correction lecture /proc/net/route
//	il faut comptabiliser les routes statiques, dynamiques
// - Ajout fonction test fonctionnelle des routes statiques
// - Ajout fonction test fonctionnelle des routes dynamiques
// - Correction erreur javascript dans page HTML politique de routage
// - Correction bug désactivation client DHCP en mode station/router
// - Ajout nouveau driver atheros datant de 20100427 (fourni par embeddedsystem)
//			-> [IMPACT] WRM100_APPLI/FileSystem/tmp/driver/*.ko

//BE027 28/04/2010 CM
// - Correction partition pour nouvelle FLASH NOR (8 --> 16Mo)
//		sources corrigés: powerengine.c
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0005_linux_sodielec.patch
// - Création des partitions config et jdb dans la FLASH NOR
//	=> dédiées pour la carte CPU uniquement (sodielec)
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0005_linux_sodielec.patch
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Renommer les partitions config et jdb dans la FLASH NAND
//	=> dédiées pour la carte I+ME uniquement
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0006_linux_sodielec.patch
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Modification des partitions config et jdb
//	=> nouveau algo systeme fichiers: yaffs2 -> jffs2
// - Creation de lien symbolic pour les mtd devices
//	afin de simplifier la gestion des devices entre cartes
// - Détection automatique du type de carte (en fonction bootargs)
//		sources corrigés: powerengine.c
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0007_linux_sodielec.patch
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Modification nom /mnt/nand-config --> /mnt/flash-config
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Modification nom /mnt/nand-jdb --> /mnt/flash-jdb
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal

//BE028 04/05/2010 JP
// - Correction statistique de l'interface eth0 bloquee a zero.
//   Le probleme apparait suite a un evenement de type FEC_IEVENT_RFIFO_ERROR, on
//   reset alors le fec. Cependant, l'activation des statistiques n'est alors pas relance!
//   rajout dans la fonction de reset du fec d'une ligne pour remettre a zero le registre
//   mib_control du fec.
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0008_linux_sodielec.patch
// - BE028.2 : ajout de la ligne CONFIG_PPC_MPC5200_GPIO=y dans le fichier de config du
//   kernel.
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/enable-export_layer.cfg
// - Ajout gestion dans le kernel du 2ème port Ethernet (pour la carte CPU)
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0009_linux_sodielec.patch
// - Ajout gestion de la temperature et des leds pour la carte CPU
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0010_linux_sodielec.patch

//BE029 10/05/2010 CM
// - Ajout autorisation routage au démarrage dans S22principal
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Ajout autorisation gestion du 2ème port ethernet sur la carte CPU (WRM100)
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Correction plantage page HTML Journal de bord (lors de plusieurs actualisations de la plage)
//	=> conséquences sémaphore SEMAPHORE_BDD_JDB bloqué, et jdb bloqué...
//	il semble que le le processus plante lors du html_tag (printf) raison ????
//	solution: on copie tout le jdb dans la RAM pour l'afficher
// - Désactivation du log du processus boa (pour éviter que le fichier soit trop grop)
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/boa/boa.conf
// - Ajout des modes sécurités Wifi de type WPA2

// VERSION_OFFICIELLE " 0 "  (_WRM100_ABG_SELECT)

//BE030 31/05/2010 CM
// - Démarrage du script personnel "ew_script.sh" sous /mnt/nand-user (si présent)

//BE031.0 04/06/2010 JP - ajout des pages html pour test final en production + script test ping
//BE031.1 07/06/2010 JP - ajout d'un test des fichiers de configuration avant application de la configuration
//BE031.2 08/06/2010 JP - correction du script test_ping.sh
//BE031.3 08/06/2010 JP - dans la page test production final, l'etat de la connexion de la station est memorise avec code couleur (rouge, orange,vert)

// VERSION_OFFICIELLE " 1 "  (_WRM100_ABG_SELECT)

//##########################################################
//BE031.4 16/06/2010 JP - dans la page test production final, rajout de la config PE en mode AP et correction pb config pe
//                        + ajout des patch de CM sur fuite memoire driver fec smi et adtemp (0012_linux_sodielec.patch et 0013_linux_sodielec.patch)

// VERSION_OFFICIELLE " 2 "  (_WRM100_ABG_SELECT)
//##########################################################


//BE032 16/06/2010 CM
// - Correction libellé du bouton "Valider" sur la page HTML password
//		-> "Valider" remplacé par "Se connecter"
//		-> "Accept changes" remplacé par "Log in"
// - Correction commande iwconfig 'txpower' (Wifi) repasse au maximum sur A/M ou sur down/up interface Wifi
//		-> impact fonction CmdIfconfig_Up
// - Correction BUG SSID avec des espaces
//	=> iwconfig ath0 essid <chaine avec espace> => KO
// - Correction BUG SSID si longueur chaine égale 32 caractères
//	=> iwconfig ne prend pas en compte une chaine de 32 caractères
//	par contre 31 caractères OK
// - Correction probleme de compilation de bird : problème de dépendance avec librairie readline
//		-> [IMPACT] MODIFY Layer/vxx/dist/bird/Makefile
// - Ajout gestion Radius / WPA - EAP
// - Correction des défauts observés lors du changement de paramètres Wifi
//		kernel panic suite à changement de fréquence (en WPA EAP), ....
//	solution: décharger/charger les modules wifi sur changement de paramètres Wifi

//BE033 25/06/2010 CM
// - Modification package wpa_supplicant 0.5.10 ==> 0.6.10
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/wpa_supplicant
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/wpa_supplicant-0.6.10.tar.gz
// - Modification package hostapd 0.6.9 ==> 0.6.10
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/hostapd
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/packages/hostapd-0.6.10.tar.gz
// - Correction configuration  wpa_supplicant en WPAxxxx - PSK (ap_scan=1)
//	=> il faut laisser ap_scan=1 (car pour c'est wpa_supplicant qui doit gérer le fast roaming)

//BE034 28/06/2010 CM
// - Correction bug commande pidof
//	sur AP apparition message "sh: cannot kill pid xxxxx: No such process" apparait de temps en temps
//	=> le défaut est lié à la commande "pidof" qui retourne plusieurs PIDs erronés
// - Correction pour SNMP du type d'interfaces (ifType dans la table ifTable)
//	de plus il faut gérer le cas où l'interface VLAN est configuré
// - Correction gestion table iftable de la MIB-II
//	A chaque fois q'une interface passe de down à up, le nombre d'interfaces (ifNumber) s'incrémente
//	et une nouvelle ligne associée à cet interface est ajoutée (en double avec les précédentes existante)
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/net-snmp/006_netsnmp_sodielec.patch
// - Correction bug BIRD en mode RIP avec auth=MD5
//	on a le message suivant: "bird: MD5 tail signature is not there"
//		-> [IMPACT] ADD WRM100_APPLI/Layer/vxx/dist/bird/001_bird_sodielec.patch (qui corrige défaut auth=MD5 en RIP)
// - Correction configuration par défaut suite modif BE032

//BE035 30/06/2010 CM
// - Ajout gestion de l'heure courante
//	=> Nouvelles partitions de la FLASH NOR (time_save_1 et time_save_2), qui remplace partition time_save
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0011_linux_sodielec.patch
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//	=> nouveaux processus restoretime et savetime
//		-> [IMPACT] WRM100_APPLI/fsl_lite5200b-glibc_small-ppc_e300c2-fsl_lite5200b_glibc_small/Makefile
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/default/fs_final.sh
// - Creation de la library static LibrarySystem
//	afin de définir une librairie avec des fonctions qui ne dépendent pas de la librairie BDD
//	par conséquent, les processus update, restoretime, savetime ne dépendent plus de la librarie Bdd
//		(gain mémoire code / ram)
//	cela consiste à deplacer les fichiers sources date, cmdsystem, infosystem, resetfile de LibraryBdd à LibrarySystem
//		-> [IMPACT] WRM100_APPLI/fsl_lite5200b-glibc_small-ppc_e300c2-fsl_lite5200b_glibc_small/Makefile
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Correction bug dans le mode test du fichier modele

//BE036 02/07/2010 CM
// - Ajout gestion des logins
//		userhigh / usermiddle / userlow
//		=> ajout source Principal/passwd.[ch]
//		-> [IMPACT] WRM100_APPLI/fsl_lite5200b-glibc_small-ppc_e300c2-fsl_lite5200b_glibc_small/Makefile
//		=> ajout permission root only pour fichiers de configuration
// - Ajout 'passwd' de la busybox
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
// - Modification des chemins de fichiers qui se trouvent dans /var => /tmp
//		bdd_boot et bdd_time
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//

//BE037 06/07/2010 CM
// - Ajout parametre config seuil de reception (wifi) sur station
// - Ajout gestion des évènements spécifiques à l'équipement
//		alarme synthese, alarme Ethernet LAN, alarme température,
//		alarme station non connectée, alarme probleme configuration,*
//		journal de bord effacé, Effacement historique des alarmes
//		Redémarrage télécommandé, Evolution de la configuration
// - Ajout exploitation temperature 
//		-> [IMPACT] WRM100_APPLI/fsl_lite5200b-glibc_small-ppc_e300c2-fsl_lite5200b_glibc_small/Makefile
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
// - Ajout récupération statut ethernet des 2 ports ethernet
//	afin de calculer l'alarme LAN ethernet
//		-> [IMPACT] WRM100_APPLI/fsl_lite5200b-glibc_small-ppc_e300c2-fsl_lite5200b_glibc_small/Makefile
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0012_linux_sodielec.patch
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/dist/net-snmp/net-snmp.spec
//	comme le kernel a évolué, il faut recompiler le driver wifi
//		-> [IMPACT] MODIFY WRM100_APPLI/Filesytem/tmp/driver/*.ko
// - Modification page HTML Admin - Controle pour redémarrer équipement
//		afin de confirmer un redémarrage par javascript
// - Modification page HTML Admin - Controle pour raz générale
//		afin de confirmer le raz par javascript
// - Ajout exploitation du client NTP
//		-> [IMPACT] WRM100_APPLI/fsl_lite5200b-glibc_small-ppc_e300c2-fsl_lite5200b_glibc_small/Makefile
// - Modification page HTML Admin - Mise à l'heure
//		-> surveillance etat NTP

//BE038 09/07/2010 CM
// - Modification des droits de permissions pour /etc/passwd
//	afin de pouvoir se connecter avec sftp (o751 -> o755) avec usermiddle et userlow
// - Ajout configuration STP pour bridge
//		STP= Spanning Tree Protocol
// - Correction fuite de mémoire (vmalloc) lors des requetes vers ad_temp et portX_link_status
//		défaut présent depuis BE037 (empeche au bout d'un certain temps le chargement du driver wifi)
//		-> [IMPACT] ADD Layer/vxxx/templates/default/linux/0013_linux_sodielec.patch
// - Correction libellé seuil niveau rx
//		"Seuil de l'alarme niveau reçu"
// - Ajout variables SNMP : stp (bridge), seuil rx (wifi), temperature

//BE039 26/08/2010 CM
// - Intégration des modifications release_v2
//		qui correspondent aux modif apportées dans BE031.4
// - Correction bug test configuration (pb canal fonction si AP ou STA)
// - Correction bug "Serveur NTP" est détecté par erreur inaccessible
//	 car l'intervalle de temps de l'emission des requetes NTP du client n'est pas constant

//BE040 13/09/2010 CM
// - Ajout 'sum' et chksum de la busybox
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/vxx/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]
//
// - Nouveaux projets WRM100
//	on définit : - un projet WRM100-ABG compatible avec la carte DCMA (802.11abg)
//						défini par define "_WRM100_ABG_SELECT"
//               - un nouveau projet WRM100-N compatible avec la carte wifi DNMA (802.11abgn)
//						défini par define "_WRM100_N_SELECT"
//     -> Définition de nouveaux layer
//				pour WRM100-ABG: on remplace vxx par "Commun,wrm100-ABG"
//				pour WRM100-N: on remplace vxx par "Commun,wrm100-N"
//     -> Définition nouveaux Makefile
//				pour WRM100-ABG: Build.wrm100-ABG/Makefile
//				pour WRM100-N: Build.wrm100-N/Makefile
// - Ajout nouveaux modules dans LibraryWifi: wifi_ABG_tools.[ch] + libraryWifi.[ch]
// - Integration de net-snmp spécifique à chaque projet
//		net-snmp dépend des define  _WRM100_N_SELECT et _WRM100_ABG_SELECT
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-ABG/dist/net-snmp/net-snmp.spec
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-N/dist/net-snmp/net-snmp.spec
// - Ajout nouveaux modules dans Monitor: exp_wlan_ABG.[ch] + exp_wlan_N.[ch]
// - Ajout nouveaux modules dans Principal: cfg_wlan_ABG.[ch] + cfg_wlan_N.[ch]
// - Integration de la gestion du wifi pour la carte compatible à 802.11n
//     -> nouveaux modes 802.11
//     -> nouveaux parametres gérant la sélection des antennes RX/TX
// - On ne monte pas automatiquement la partition nand-user
//	suite à des problèmes de pertes de données et de montage de cette partition au démarrage://	
//		"Cowardly refusing to erase blocks on filesystem with no valid JFFS2 nodes"
//		"JFFS2 notice: (310) check_node_data: wrong data CRC in data node at "
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
//	 le montage de la partition nécessite la présence du fichier nand-user.on dans /mnt/flash-config
// - Ajout des paramètres de configuration hand-off

//BE041 22/09/2010 CM
// - Ajout IOCTL_GETUSERINFO entre nos applis et driver-N
//	afin de récupérer rssi filter/raw
// - Correction dans Driver-N débit incorrecte (get sur iwconfig)

//BE042 07/10/2010 CM
// - Correction compilation big_endian (associé au driver-N)
// - Correction configuration mode 802.11 (associé au driver-N)
//		fonction si AP ou STA
// - Ajout gestion liste des fréquences réglementaires
//	=> on sauve le countryID dans fichier environnement dans la partition "flash-config"
//	=> puis en se basant sur la commande "wlanconfig ath0 list channel", on va déterminer la liste
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-ABG/dist/net-snmp/net-snmp.spec
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-N/dist/net-snmp/net-snmp.spec
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-N/Makefile
// - Ajout paramètre de configuration pour 11n intervalle de garde
// - Ajout gestion debit MCS pour 802.11n
// - Ajout fonctions generiques dans la description de la configuration
//		u8DiffConfig, u8FillConfig, u8TestConfig
// - Modification scripts du driver-N FileSystem/tmp/driver-N/
//		-> load_ap.sh
//		-> load_sta.sh
//		-> load_modules_ap.sh
//		-> load_modules_sta.sh
//		-> unload_modules.sh
// - Integration des paramètres handoff
// - Definition macro RSSI => dBm (et inverse)
// - Ajout possibilité de reconfigurer entierement l'équipement
// - Correction libellé fr diversite + relais
// - Configuration seuil de framentation (adv wifi) non autorisé en 11n


//BE043 29/10/2010 CM
// - Correction reconfiguration du channel width de l'AP par STATION (en mode 11nht40) non désiré
//		-> donc AP est rejeté par la STATION
// En effet, par défaut le mode CWM (Channel Width Management) est activé.
// Il existe plusieurs conditions pour que la STATION décide de reconfigurer le channel width.
// Il y a par exemple la mesure de l'occupation spectrale.
// Si celui-ci est au-dessus du seuil (extbusythres), alors la STATION reconfigure le channel width de l'AP.
//	(en envoyant un message 802.11 de type ACTION).
// Donc, on va désaciver ce mode (ce sera plus sur)
// - Correction enum modes 802.11 (meilleur ergonomie)


//BE044 29/10/2010 CM
// - Modification déchargement des modules du driver wifi
// - Correction kernel panic "ASSERT" lors de la désinstallation du driver-N de la STATION (liaison Bridge-Bridge)
//		"Assertion failed! (*ss)->ss_num_handlers == 0:ieee80211_scan_detach"
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//	Ce défaut apparait si il y a plusieurs msg de type "Adding WDS entry for 00:19:d1:7d:3a:62, through ni=00:0b:6b:b7:48:83".
// - Modification scripts du driver-N FileSystem/tmp/driver-N/
//		-> load_sta.sh (insertion bridge fonction)

//BE045 04/11/2010 CM
// - Correction AP rejete authentication de STATION à tort
//		AP affiche msg suivant vap-0: [@mac_station] num auth'd STAs is 65535, max is 128, rejecting new auth
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction plage des seuils des paramètres handoff
//	afin de pouvoir désactiver le handoff
// - Correction bug liste frequences en 11nght40plus

//BE046 17/11/2010 CM
//BE046.0
// - Ajout des applis du driver-N athstats et athstatsclr au filesystem
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-N/templates/default/fs_final.sh
// - Correction probleme reseau (ping ap -> sta) après 30 secondes (due à "long" calibration)
//	après chargement du driver, l'AP ping la STA pendant 30 secondes, puis le ping est perturbé pendant 60 secondes (réponse lente de la STATION).
//	On a du Carrier Sense Timeout (CST) et du Global Transmit Timeout (GTT). (cf athstats)
//	Ce défaut a été constaté:
//		- à certaines fréquences (5220MHz, 5500MHz),
//		- dans les modes 802.11 naht20 ou a
//		- sécurité wifi ou non
//	Note: au frequence 4800MHZ, 5700MHz, 6075MHz défaut absent
//	L'analyse montre que le défaut est lié à la calibration "long" (définie dans la fonction ath_calibrate).
//	Le workaround consiste à faire 2 "long calibration" pour que le défaut n'apparaisse plus.
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction msg debug (données issues de l'AP non traitées par la STA)
//	il n'est pas nécessaire de polluer le debug avec msg suivant "vap-0:  discard unhandled information element id 74"
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//BE046.1
// - Ajout gestion du SSID secondaire (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/ (pas encore fonctionnel!!!)
// - Ajout debug / timing roaming (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction émission premier probe request par STATION (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction timing roaming (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction disassociation permanente de la STATION
//		On re-initialise la machine d'état si disassociation ou deauthentification de la STATION (quelque soit la raison)
//		ce défaut permet de corriger le probleme de disassociation de la STATION quand disassoc pour raison "auth expire"
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction alarme Ethernet pour chaque accès
//	alarme ethernet lan 1 et alarme ethernet lan 2
//	L'alarme "ethernet lan 2" est non validée par défaut
//	+ aussi disponible sur ACCESS POINT
// - Ajout debounce des alarmes ethernet
//	car alarme à tort quand traffic important sur STATION
// - Correction plage du parametre de config vlan id
//	-> valeur 0 non autorisée
// - Correction force horodatage identique à tous les évènements dans la seconde
//BE046.2
// - Ajout dans wpa_supplicant/hostapd methode EAP (pour Driver-N)
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
// - Mise en commentaire du message de debug suivant dans hostapd (pollue debug)
//	"Dumping hostapd state to ..."
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
// - Correction bug dans le mode WPA/EAP (dans Driver-N / wpa_supplicant)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//BE046.3
// - Correction configuration par défaut
//		si AP => passage en STA / Bridge par erreur
//BE046.4
// - Correction alarme température à tort suite A/M
//		durée de 1 seconde

// VERSION_OFFICIELLE " 3 "  (_WRM100_N_SELECT)

//BE047 29/11/2010 CM
//BE047.0
// - Optimisation traitement gestion trap sodielec
// - Gestion mode dégradé - connection à AP impossible en permanence suite à configuration wifi 
//	Deux défauts ont été constaté:
//		--> bug "Reject (Privacy bit set)": le candidat AP est rejeté à tort
//		--> bug AP disassocie STA à cause de "Group Chiper is not valid (0x0012)" (dixit Wireshark) à tort
//			la station est alors marqué BAD
//	Il semble que c'est une mauvaise configuration du driver-N par le wpa_supplicant.
//	(la commande de type "iwlist ath0 scan" déplante le défaut).
//	Ajout dans command "wpa_cli status" un champ "cptsecond_noconnected"
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
//	Ajout nouveau source watchdogwifi
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-N/Makefile
//BE047.1
// - Optimisation configuration radio modem / amelioration ergonomie
//	Les temps de configuration du radio modem (load / unload driver, setup ...) sont très long.
//	Sur versions précédentes, reconfiguration AP: 10 secondes et reconfiguration STA: 30 secondes
//	avec inaccessibilité de l'accès ethernet et donc du serveur WEB.
//		-> afin que l'accès ethernet soit disponible au maximum (lors de la reconfiguration wifi): on crée un alias temporaire (accessible uniquement sur reseau local)
//		-> et aussi que le serveur WEB soit egalement disponible (affichage msg "configuration en cours")
//	Ajout nouveau source vcfginprogress (html_cgi)
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-N/Makefile
// - Correction configuration du paramètre bmiss (handoff)
//	uniquement prise en compte suite à un "ifconfig ath0 up"

//BE048 29/11/2010 CM
// - Optimisation configuration radio modem / amelioration ergonomie
// - Correction routage statique vers un HOST
//	le test de la route n'est pas correct (trop strict)
// - Correction bug sur re-configuration des politiques de routage
//		=> certaines règles ne sont plus appliquées
// - Correction re-configuration wpa_supplicant
//	il faut acquitter cette re-config (pas de défaut constaté, mais il faut le faire)
// - Correction bug sur configuration du serveur DHCP
// - Correction libellé fr erroné
// - Correction statut IP (Succès DHCP non affiché) en bridge

//BE049 08/12/2010 CM
// - Ajout affichage des commandes dans la page de Configuration - Routage Ip - Général
// - Ajout affichage des commandes dans la page de Configuration - NAT
// - Ajout gestion du SSID secondaire (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/ 
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
// - Ajout commande pour forcer le channel probing (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/ 
// - Workaround sur stuck beacon  (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/ 
// - Correction configuration du paramètre bmiss (handoff)
//	annule correction faite dans BE047
// - Modification mode scanning (handoff)
//	-> modif valeurs (et valeur passive non autorisée)
// - Correction libellé handoff
// - Correction actualiser page vcfginprogress
// - Correction libellé javascript avertissement chaine vide
// - Correction test valeur SSID (champs vide non autorisé)

//BE050 09/12/2010 CM
// - Correction gestion NTP/SNTP
//	ajout nouveaux paramètres de config: mode mise à l'heure (manuel,ntp,sntp) + adresse de serveur de secours + fréquence maj sntp
//		-> nouveaux sources cfg_time / cfg_sntp / exp_sntp
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-N/Makefile
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/Commun/dist/ntp/ntp.spec
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/dist/ntp/patches/001_ntp_sodielec.patch
//		-> passage config/defaut de admin
// - Ajout valeur PEAP/MSCHAPv2 dans authentification EAP (Radius)
// - Modification valeur antennes TX / RX
//		"antennes 1 & 2" au lieu de "antennes 1 & 3"
// - Correction fonction s32GetPidProcessus
//	=> retourne un seul PID -> via commande pidof -s
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/Commun/templates/feature/busybox/busybox/config   [FICHIER DE CONFIGURATION BUSYBOX]

//BE051 13/12/2010 CM
// - Ajout exploitation SSID (utile si dual ssid activé)
// - Incohérence horodatage de l'action suppression jdb et de l'évènement
// - Probleme horodatage de l'évènement JDB lors d'un RAZ général
//	-> ce n'est pas le premier
// - Correction probleme construct chanlist
//	par exemple: "44 (5220MHz) , 216 (4800MHz)", seul le canal 216 est activé pour le scanning
//		-> [IMPACT] WRM100_APPLI/Driver-N/ 
// - Ajout debug pour désactiver watchdog_wifi
// - Correction page liste des évènements
// - Correction debounce alarme non connecté de la station
// - Correction gestion alarme niveau rx de la station

//BE052 15/12/2010 CM
// - Correction bug affichage antennes rx dans pages configuration
// - Ajout configuration WMM (Wireless forMultiMedia)
// - Ajout gestion plage puissance TX fonction debit / nb antennes (Driver-N)
//	-> deplace parametres antennes dans structure wifi
//		-> passage config/defaut de wifi
// - Correction bug configuration delay GTK (pb cast)

//BE053 16/12/2010 CM
// - Modification une seule antenne autorisée dans les modes 802.11abg (Driver-N)
// - Désactivation de la gestion de l'heure dans la FLASH NOR
//		car non ergonomique d'après la Qualité ActiaSodielec
//	on n'appelle pas restoretime / savetime
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Modification de la MIB / agent SNMP (suite integration Driver-N)
// - Modification plage de timeout ACK (Driver-N)
//		-> plage de 0 à 204 en mode 11nht40
//		-> plage de 0 à 409 pour autres modes
// - Correction bug commande pidof via hostapd
//	sur AP apparition message "sh: cannot kill pid xxxxx: No such process" apparait de temps en temps
//	=> on debounce la valeur du PID

// VERSION_OFFICIELLE " 4 "  (_WRM100_N_SELECT)

//BE054 11/01/2011 CM
//BE54.0
// - Correction compilation WRM100-ABG
// - Ajout gestion mode monitor
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/dist/tcpdump
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/dist/shadow-utils
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/dist/libpcap
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/packages/shadow-utils-4.1.1-1.fc9.src.rpm
//
// rmq: on ne prend pas les versions tcpdump/libpcap de WindRiver suivantes:
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/packages/tcpdump-3.9.5-3.fc7.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/packages/libpcap-0.9.8-2.fc9.src.rpm
//	mais les dernières versions stables (intégrant des infos 802.11n)
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/packages/tcpdump-4.1.1-1.fc14.src.rpm
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/packages/libpcap-1.1.1-1.fc14.src.rpm
//
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/Commun/templates/default/pkglist.add
//		-> [IMPACT] WRM100_APPLI/Driver-N/ 
//		-> [IMPACT] ADD WRM100_APPLI/Layer/Commun/packages/libpcap-0.9.8-2.fc9.src.rpm
//		- Ajout script du driver-N FileSystem/tmp/driver-N/load_monitor.sh
//		- Ajout script du driver-ABG FileSystem/tmp/driver-ABG/load_monitor.sh
//		- Ajout script "syslg_tcpdump.sh" sous FileSystem/etc
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-N/templates/default/fs_final.sh
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-ABG/templates/default/fs_final.sh
//	-> Gestion format prism2 header / radiotap header / ppi header
// - Modification débit emission MCS0 à MCS15 autorisé quelque soit nb antennes
//		-> [IMPACT] WRM100_APPLI/Driver-N/ 
// - Suppression message de l'AP qui pollue le log du kernel (quand debug activé)
//		"vap-0: ieee80211_add_htinfo_pre_ana: use HT info IE pre-ANA"
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Suppression du fichier de configuration advwf
//		paramètres de configuration deplacés
// - Correction bug affichage commande table mangle
//		fichier errone
// - Correction bug affichage commande ip route info
//			mesg suivant sur page HTML Routage IP: "Accès à la base de données impossible ! (/tmp/bdd_misc/ip_route.info)
//			dans le cas où aucune passerelle activée dans les règles de politique de routage
// - Correction bug dans MIB/agent SNMP variables specifique au mode radio modem
// - Correction bug HTLML affichage des password sous Internet Explorer (IE)
//		-> on ne peut change le type d'une balise INPUT de "text" --> "password" (ou vice et versa)
// - Correction libelle gb alarms list avec s
// - Correction libelle tiroir --> equipement
//BE54.1
// - Correction bug limitation a 20dbm en mode 11g et 11ng (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Gestion de l'ordre des frequences (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Suppression msg debug "ieee80211_crypto_decap: WEP data frame no valid key, len %u mcast %d" (JP)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Ajout Test final WRM100-3-1-2 (JP)
// - Modification info snmp debit max de l'interface wifi

//BE055 17/01/2011 CM
// - Modification configuration des antennes
//	=>elles se configurent dans la pages de configuration des paramètres basiques (meilleur ergonomie)
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-N/Makefile
//	=>un seul paramètre de configuration autorisé pour antenne rx/tx (Driver-N)
// - Correction limitation puissance pour 11ag dans Driver-N
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Ajout configuration Country ID pour le client
//		à partir d'une liste (dans page HTML)
// - Correction en mode monitor ne pas configurer ssid
// - Correction kernel panic de temps en temps dans page HTML test final
//		conflit de requete pour temperature
// - Correction taille page configuration wifi basique
//		au niveau de la listbox du canal
// - Suppression message de l'AP qui pollue le log du kernel
//		"vap-0: ieee80211_add_htcap_pre_ana: use HT caps IE pre-ANA"
// - Ajout information "Debug Activé" sur frame A
// - Correction kernel panic sur ACCESS POINT en mode HT40 suite à déchargement du driver-N
//		suite à "vap-795044208: ieee80211_ht40intol_evhandler event 8 reason 1"
//			ieee80211_note+0xa0/0xd4 [umac] (unreliable ) 
//			wlan_attempt_ht40_bss+0x198/0x22b0 [umac] 

//BE056 18/01/2011 CM
// - Correction puissance maximum en fonction config mode 802.11/debit/antenne
//	pour éviter sur-consommation de l'équipement
// - Ajout des outils du Driver-N: radartool et reg
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//		copie fichiers reg.c et diag.h (de os/linux/tools/hal_diag) sous la racine de os/linux/tools/
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-N/templates/default/fs_final.sh
// - Ajout limitation de la bande de fréquence aux canaux ETSI non DFS pour WRM100-ABG
//	c'est à dire pour la version 3-1-1
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
//		-> Modif script du driver-ABG FileSystem/tmp/driver-ABG/load_modules_ap.sh
//		-> Modif script du driver-ABG FileSystem/tmp/driver-ABG/load_modules_sta.sh
//		-> Modif script du driver-ABG FileSystem/tmp/driver-ABG/load_modules_monitor.sh
//		remarque: sur WRM100-ABG, la configuration test_tools -setcountryid <valeur>
//			avec <valeur>:regdomain 0x29F (EW_DMN) pour toutes frequences
//			avec <valeur>:regdomain 0x31 (ETSI1_WORLD) pour toutes frequences
// - Suppression msg de debug qui pollue le kernel dans Driver-ABG
//		-> [IMPACT] WRM100_APPLI/Build.wrm100-ABG/Makefile
// - Modification compilation hostapd (pour WRM100-ABG) : indépendant de madwifi
//		-> [IMPACT] ADD WRM100_APPLI/Layer/wrm100-ABG/dist/wpa_supplicant/patches/001_wpa_supplicant_sodielec.patch
//		-> [IMPACT] ADD WRM100_APPLI/Layer/wrm100-ABG/dist/hostapd/patches/001_hostapd_sodielec.patch
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-ABG/dist/net-snmp/net-snmp.spec
// - Sur WRM100-ABG, mot de passe du login root est root
//	pour conserver cohérence avec ancienne version

//BE057 20/01/2011 CM
// - Ajout de nouveaux codes pays
//		Les pays concernés par la demande de mise sur le marché  via le portail européen OSN sont:
//				Autriche-Belgique-Bulgarie-Suisse-Chypre-République Tchèque
//				Allemagne-Danemark-Estonie-Finlande-France-Grèce
//				Irlande-Islande-Lituanie-Luxembourg-Lettonie-Malte-Pays bas-Norvège
//				Portugal-Roumanie-Suède-Slovénie-Slovaquie-Grande Bretagne
//		Attention!!!:   Hongrie  ===> A ce jour seule la Hongrie a interdit l'équipement.
//	+ on ajoute Espagne, l'Italie  et la Pologne qui ne sont pas adhérents à ce portail européen mais sont aussi concernés par cet équipement.
// - Ne pas afficher evenements liés à ssid secondaire  sur WRM100-ABG
// - Modification test vlan config pour éviter de passer en config/defaut sur config generale du WRM100-ABG
//	en supposant que vlan n'est pas activé avec id=0
// - Désactivation du mode monitor en WRM100-ABG
//		bien qu'il fonctionne!

// VERSION_OFFICIELLE " 3 "  (_WRM100_ABG_SELECT)

//BE058 21/01/2011 CM
// - Correction bug configuration des canaux (multi-freq) erronée si chgt de mode 802.11 (g -> a) et de type radiomodem
// - Ajout alarme "aucun serveur NTP accessible"
// - Ajout dans exploitation du canal en cours (sur AP et STA)
// - Correction bug pas d'emission de AP si radar détecté et basculement sur canal non DFS 
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Ajout nouveaux évènements liés au DFS
//	Radar détecté sur canal + Basculement vers canal
// - Ajout configuration "desactivation DFS" (WRM100-N)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//		-> Modif script du driver-N FileSystem/tmp/driver-N/load_ap.sh
//		-> Modif script du driver-N FileSystem/tmp/driver-N/load_sta.sh
//		-> Modif script du driver-N FileSystem/tmp/driver-N/load_modules_sta.sh
//		-> Modif script du driver-N FileSystem/tmp/driver-N/load_modules_ap.sh
// - AJout fonction arret AP si ethernet deconnecte
//		+ modification debounce alarme ethernet 8 sec --> 3 sec (pour que la station se déconnecte le plus rapidement)
// - Correction bug mode scanning non appliqué sur Driver-N
//		nom de commande non valide "fr_scanmode" --> "fr_actprob"
// - Ajout champs info_sup1 dans gestion trap
// - Modification gestion exploitation wifi
// - Synchronisation configuration / exploitation
//		c'est à dire synchro des processus "principal" (qui gère la configuration) et "monitor" (qui gère l'exploitation)
//		nouveaux fichiers sources evt_sta.[ch] et evt_ap.[ch]
// - Correction bug incohérence dans configuration par défaut
//		canal iso: 1 (non valid) --> 36 (valid) en mode 11a

// VERSION_OFFICIELLE " 5 "  (_WRM100_N_SELECT)

//BE059 16/02/2011 CM/JP
// - Correction compilation de tcpdump sur une machine HOST 64bits
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/Commun/dist/tcpdump : nouveaux patches
// - Ajout filtrage rssi pour fast roaming
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Ajout config intervalle de temps entre 2 beacon pour fast roaming
//		pour améliorer le fast roaming entre 2 handoffs
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Ajout mode RSSI (syslog)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
// - Correction bug sur variable SNMP staWirelessAP-ChannelInUse et staWirelessSta-ChannelInUse
// - Correction bug sur variable SNMP mgmtWirelessAdv-Fragment-Thrsld
// - Correction mesure RSSI (ecart de 10 dB entre debut de connexion et 30 secondes après connexion a un AP)
//		30 secondes , il y a une calibration
//		on modifie la valeur du noise floor max à 5GHz (-90 --> -80dB)
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction bug sur variable SNMP staWirelessAP-Client-Status
// - Correction bug sur variable SNMP retournant une chaine date en mode 12H
//	 (comme cmdLastDatEOfCleaningAlarms)

// VERSION_OFFICIELLE " 6 "  (_WRM100_N_SELECT)


//BE060 16/03/2011
// - DEP: Ajout des évenements de connexion et déconnexion d'une STATION
//		-> par defaut, ces evts ne sont pas validés dans JDB / TRAP (meme suite à la mise à jour logicielle)
//		-> [IMPACT] WRM100_APPLI/Driver-N/: on diminue les temps de pollings de l'AP
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
// - Ajout champs info_sup3 dans gestion trap/jdb/evt
// - Ajout nouveau type dans gestion bdd/file (FTYPVAL_TABU8_HEXA)
// - DEP: Ajout du mode d'Authentification EAP-TLS
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Correction bug du mode debug de hostapd (pid file non généré)
//		et pour afficher debug il faut etre non daemon
//		-> [IMPACT] WRM100_APPLI/hostap-0.7.1/
// - Ajout fonction qui liste les fichiers dans répertoire
// - Correction bug alarmes station non connectée et niveau recu bagottent si station n'est pas connectée
//	à cause de la fonction de watchdog wifi
// - Ajout fonction impose config au démarrage (pour chaque bdd de config)
// - Ajout configuration date/heure au démarrage de l'équipement
//	car les certificats EAP-TLS sont valides pour une durée
// - Ajout fonction qui calcule la taille d'un fichier
// - Correction bug au démarrage de l'équipement accès HTTP à des données pas encore initialisées
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Correction bug lors de l'exploitation hostapd.dump quand nombreuses stations connectées
//	chaque station occupe au moins 60 lignes
// - Correction bug pb liaison bridge-bridge de temps en temps (adresse MAC du bridge affecté est @MAC de l'ethernet)
//		la connexion réseau ne fonctionne pas (si @MAC du bridge est celle de l'ethernet)!
//		ne pas appliquer en mode monitor
// - Correction ergonomie dans page HTML Config Mode 
//		qd on ne confirme pas le changement de mode (si bridge), on revient dans le mode configuré

// VERSION_OFFICIELLE " 7 "  (_WRM100_N_SELECT)


//BE061 10/05/2011
// - Modification gestion fichiers - pas d'erreurs retournées si champs inconnu dans fichier lu
// - Ajout fonction ImposeInitConfigXXXX si configuration incohérente pour éviter de passer en configuration par défaut
//		si par exemple on vient du logiciel WRM100-MESH
// - Conservation des fichiers nécessaires à la connexion SSH
//		-> [ADD] WRM100_APPLI/FileSystem/etc/dropbear/dropbear_dss_host_key
//		-> [ADD] WRM100_APPLI/FileSystem/etc/dropbear/dropbear_rsa_host_key
//		-> [IMPACT] MODIFY WRM100_APPLI/Layer/wrm100-N/templates/default/fs_final.sh
//	car ils sont recalculés sur chaque compilation du projet
//	Cela permet d'éviter sur connexion ssh ce type de message	" WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED! "
// - Correction w@rning compilation dans appel de u8AddCipStatusTrap
// - Ajout possibilité d'executer script au démarrage (présent dans /mnt/flash-config)
//	et suppression des autres scripts executés dans nand-user
//		-> [IMPACT] WRM100_APPLI/FileSystem/etc/rcS.d/S22principal
// - Ajout restauration de la configuration  par défaut du WIFI lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).
// - Ajout suppression du JDB lors du passage de WRM100-N --> WRM100-MESH (ou vice versa).



//BE062.0 12/09/2011 (JP)
// - gestion des leds sur le PCB:
//     gestion faite dans la fonction execmonitor
// - gestion de l'entree passage en config par defaut :
//     modification du driver WRM100 pour acceder a l'etat de la broche PSC3_7 du micro (/proc/sys/wrm100/conf_def)
//     test si broche a zero pendant les 7 premieres secondes du demarrage => application de la config par defaut.
//     suivi d'un reset

// VERSION_OFFICIELLE " 8 "  (_WRM100_N_SELECT)


//BE063.0 06/10/2011 (JP)
// - gestion de la configuration par sFTP :
//     Ajout des fichiers Conf-sFTP/execconf_sftp.c, Conf-sFTP/gestconf_sftp.c
//     Ajout du processus confsftp (lance par execprincipal)
//     Ajout dans la gestion des fichiers de configuration de deux nouveaux types de champ :
//        FTYPVAL_ADDIP: adresse IP en notation pointee
//        FTYPVAL_COMMENT: ligne de commentaire
//     Ajout du fichier de configuration config_wrm100 avec description de son contenu
//

// VERSION_OFFICIELLE " 9 "  (_WRM100_N_SELECT)

//BE064.0 25/11/2011 (CM)
// - Correction bug de la configuration par sFTP (lors changement countryId)
//		-> ajout d'un flag "change_ftp", activé lors de la config par FTP
//		-> on n'impose pas de configuration lors de la config par FTP


// VERSION_OFFICIELLE "10 "  (_WRM100_N_SELECT)

//BE065.0 14/03/2012 (CM)
// - Suppression workaround beacon stuck
//		-> [IMPACT] WRM100_APPLI/Driver-N/
// - Correction bug inactivité Quelque soit le mode de sécurité
//		Quand la STATION est en inactivité (pendant au moins 90 secondes), elle n'est plus accessible de l'ACCESS POINT. 
//	  L'AP ne liste plus la station inacessible. Quant à la STATION, elle se croit toujours connectée à l'AP.
//		L'analyse montre que l'AP envoie un seul paquet wifi "data null" et supprime la station (il doit y avoir un bug dans la fonction ieee80211_timeout_stations(struct ieee80211_node_table *nt). )
//		Or, la station a acquitté le paquet "data null" (cf wireshark)
//		Solution implémentée:
//		   Il faut faire du polling toutes les 30 secondes sur la station vers l'AP (envoie de paquet null data). Pour éviter que l'AP supprime la station pour inactivité.
//		   Si par malheur, la station est supprimée, l'envoi du  paquet "null data" entraine par l'AP l'envoie d'un message de désassociation de la station.
//		-> [IMPACT] WRM100_APPLI/Driver-N/
//		-> [IMPACT] WRM100_APPLI/Source
// - Correction bug libellé "LAN Ethernet 1/2 alarm" (GB)

//BE065.1 02/05/2012 (CM)
// - Correction libellé GB HTML
//		->	"ou" à la place de "or" (dans page Configuration - Network)
//		->	Majuscule pour "Filter type" (dans page Configuration - Hand-off)
// - Correction libellé dans page Html Administration - Sécurité
// - Correction libellé dans page Html Administration - Controle
//		-> correction warning sur restauration config par défaut
// - Correction ergonomie page HTML Configuration - Réseau
//		-> ajout bouton valider formulaire

// VERSION_OFFICIELLE "11 "  (_WRM100_N_SELECT)








// VERSION_OFFICIELLE " 4 "  (_WRM100_ABG_SELECT)


/*_____III - DEFINITIONS DE TYPES_________________________________________*/
												
/*_____IV - PROTOTYPES DEFINIS ___________________________________________*/

/*_______V - CONSTANTES ET VARIABLES _____________________________________*/
