#========================================================================
# NOM DU FICHIER  : Makefile
#========================================================================
# Auteur          : HR
# Date  		  : 11/7/2013
# Libelle         : Makefile du processus update
# Projet          : WILINK
# Indice          : 0
#========================================================================
# Historique      :                                                      
# - CREATION
#========================================================================

CFLAGS=${ACTIA_CFLAGS}

LDFLAGS=${ACTIA_LDFLAGS}

EXEC= update
SRC= crc32.c \
     execupdate.c \
	 gestupdate_app.c \
	 ../LibrarySystem/librarySystem.a

OBJ= ${SRC:.c=.o}


all: ${EXEC}

${EXEC} : ${OBJ}
	${CC} -o ${EXEC} ${OBJ} ${LDFLAGS}

%.o: .c
	${CC} -o $@ -c @< ${CFLAGS}

clean : 
	@find -name "*.o" | xargs rm -rf

distclean :
	@rm -rf ${EXEC} 
