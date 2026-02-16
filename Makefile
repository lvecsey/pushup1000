
CC=gcc

CFLAGS=-O3 -Wall -g -pg

PROGRAMS=pushup_routine

all : $(PROGRAMS)

pushup_routine : LIBS+=-lyaml

pushup_routine : festival_saytext.o difftime.o rndseed_setup.o fitness_msgloop.o yaml_msgloop.o pushup_routine.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

clean :
	@rm *.o $(PROGRAMS)

install : $(PROGRAMS)
	@cp $^ ~/bin
