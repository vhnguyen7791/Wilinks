#========================================================================
# NOM DU FICHIER  : Makefile
#========================================================================
# Auteur          : CM
# Date  		  : 21/10/2011
# Libelle         : Makefile de la librarie System
# Projet          : STREAMEASY
# Indice          : BE000
#========================================================================
# Historique      :                                                      
#BE000 21/10/2011 CM
# - CREATION
#========================================================================

CFLAGS=${ACTIA_CFLAGS}
LDFLAGS=${ACTIA_LDFLAGS}
EXEC= librarySystem
SRC= cmdsystem.c \
	 librarySystem.c \
	 date.c \
	 infosystem.c \
	 resetfile.c
OBJ= ${SRC:.c=.o}

#INSTALL=/usr/bin/install

all: ${EXEC}

${EXEC} : ${OBJ}
	${CROSS_COMPILE}ar rcs $@.a $^

%.o: %.c  
	$(CC) -o $@ -c $< ${CFLAGS}

clean : 
	@rm -rf *.o ${EXEC}.a

mrproper : clean
	@rm -rf ${EXEC}.a
