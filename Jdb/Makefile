#========================================================================
# NOM DU FICHIER  : Makefile
#========================================================================
# Auteur          : CM
# Date  		  : 21/10/2011
# Libelle         : Makefile du processus jdb
# Projet          : STREAMEASY
# Indice          : BE010
#========================================================================

CFLAGS=${ACTIA_CFLAGS}
LDFLAGS=${ACTIA_LDFLAGS}
EXEC= jdb
SRC= execjdb.c \
	 jdbflash.c \
	 ../LibrarySystem/librarySystem.a \
	 ../LibraryBdd/libraryBdd.a
OBJ= ${SRC:.c=.o}

all: ${EXEC}

${EXEC} : ${OBJ}
	${CC} -o ${EXEC} ${OBJ} ${LDFLAGS}

%.o: .c
	${CC} -o $@ -c @< ${CFLAGS}

clean : 
	@rm -rf *.o

distclean :
	@rm -rf ${EXEC} 
