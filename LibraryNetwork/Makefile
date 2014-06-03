#========================================================================
# NOM DU FICHIER  : Makefile
#========================================================================
# Auteur          : CM
# Date  		  : 21/10/2011
# Libelle         : Makefile de la librarie Langue
# Projet          : WiLink
# Indice          : BE000
#========================================================================
# Historique      :                                                      
#BE000 17/05/2013 HR
# - CREATION
#========================================================================

CFLAGS=${ACTIA_CFLAGS}
CFLAGS+=-DCOMPIL_LIBRARYNETWORK

LDFLAGS=${ACTIA_LDFLAGS}
EXEC= libraryNetwork
SRC= libraryNetwork.c \
	 ip_tools.c \
	 mac_tools.c
OBJ= ${SRC:.c=.o}

all: ${EXEC}

${EXEC} : ${OBJ}
	${CROSS_COMPILE}ar rcs $@.a $^

%.o: %.c  
	$(CC) -o $@ -c $< ${CFLAGS}

clean : 
	@rm -rf *.o ${EXEC}.a

mrproper : clean
	@rm -rf ${EXEC}.a
