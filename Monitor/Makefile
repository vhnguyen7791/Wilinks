#========================================================================
# NOM DU FICHIER  : Makefile
#========================================================================
# Auteur          : CM
# Date  		  : 21/10/2011
# Libelle         : Makefile du processus monitor
# Projet          : STREAMEASY
# Indice          : BE067
#========================================================================

CFLAGS=${ACTIA_CFLAGS}

LDFLAGS=${ACTIA_LDFLAGS}

LDFLAGS+= -lm

EXEC= monitor
SRC= Event/evt_debug.c \
	 Event/evt_generique.c \
	 Event/evt_system.c \
	 Event/evt_sta.c \
	 Event/evt_ap.c \
	 Event/execevent.c \
	 Event/internevent.c \
	 Exploit/exp_ntp.c \
	 Exploit/exp_sntp.c \
	 Exploit/exp_dhcp.c \
	 Exploit/exp_network.c \
	 Exploit/exp_versions.c \
	 Exploit/exp_wifi_ap.c \
	 Exploit/exp_wifi_station.c \
	 Exploit/exp_wlan_N.c \
	 Exploit/gestexploit.c \
	 custom_bdd.c \
	 execmonitor.c \
	 ../LibrarySystem/librarySystem.a \
	 ../LibraryWifi/libraryWifi.a \
	 ../LibraryBdd/libraryBdd.a \
	 ../LibraryNetwork/libraryNetwork.a

OBJ= ${SRC:.c=.o}

all: ${EXEC}

${EXEC}: ${OBJ}
	${CC} -o ${EXEC} ${OBJ} ${LDFLAGS}

%.o: .c
	${CC} -o $@ -c @< ${CFLAGS}

clean : 
	@find -name "*.o" | xargs rm -rf

distclean :
	@rm -rf ${EXEC} 


#	 Exploit/exp_ethernet.c \
