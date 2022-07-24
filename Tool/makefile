CC=gcc
LIBS=-lm
CFLAGS=-I.
INPUT=main.c rpc/stub/rpc_stub.c socket.c rpc/shell/shell.c
DEPS=rpc/stub/rpc_stub.h socket.h rpc/shell/shell.h
ODIR=obj

OFILES=$(patsubst %.c,%.o,$(INPUT))

%.o: $(INPUT) $(DEPS)
	$(CC) -c -o $(ODIR)/$(shell basename $@) $(patsubst %.o,%.c,$@) $(CFLAGS)

bin/main: $(OFILES) 
	$(CC) -o $@ $(patsubst %,$(ODIR)/%,$(foreach file,$^,$(shell basename $(file)))) $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm bin/main obj/*.o
