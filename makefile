CC=gcc
CCFLAGS = -g -std=c99
LIBS += -lm


pgmEcho:	pgmEcho.c pgmRead.c pgmWrite.c
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.c
pgmComp:	pgmComp.c pgmEcho.c pgmRead.c pgmEcho.h
	${CC} ${CCFLAGS} -o pgmComp pgmComp.c
pgma2b: 	pgma2b.c  pgmRead.c pgmWrite.c pgmEcho.h
	${CC} ${CCFLAGS} -o pgma2b pgma2b.c
pgmb2a: 	pgmb2a.c  pgmRead.c pgmWrite.c pgmEcho.h
	${CC} ${CCFLAGS} -o pgmb2a pgmb2a.c
pgmReduce:	pgmReduce.c pgmRead.c pgmWrite.c pgmEcho.h
	${CC} ${CCFLAGS} -o pgmReduce pgmReduce.c
pgmTile:	pgmTile.c pgmRead.c pgmWrite.c pgmEcho.h
	${CC} ${CCFLAGS} -o pgmTile  pgmTile.c ${LIBS}
pgmAssemble:	pgmAssemble.c pgmRead.c pgmWrite.c pgmEcho.h
	${CC} ${CCFLAGS} -o pgmAssemble  pgmAssemble.c ${LIBS}
all: pgmEcho pgmComp pgmb2a pgma2b pgmReduce pgmTile pgmAssemble

clean:
	rm -rf pgmEcho pgmComp pgma2b pgmb2a pgmReduce pgmTile pgmAssemble