#========================================================================
# NOM DU FICHIER  : Makefile
#========================================================================
# Auteur          : GT
# Date  		  : 11/01/2012
# Libelle         : Makefile du processus de test du Hard
# Projet          : STREAMEASY
# Indice          : BE067
#========================================================================
# Historique      :                                                      
#BE067 CM 18/06/2012
# - Ajout library GPIO
#========================================================================

CFLAGS=${ACTIA_CFLAGS}
LDFLAGS=${ACTIA_LDFLAGS}
EXEC= confsftp
SRC= execconf_sftp.c \
	 gestconf_sftp.c \
	 ../LibrarySystem/librarySystem.a \
	 ../LibraryBdd/libraryBdd.a 

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
