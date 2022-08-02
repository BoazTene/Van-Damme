CC=gcc
LIBS=-lm
CFLAGS=-I.
INPUT_DEPS = rpc/stub/rpc_stub.c socket.c rpc/shell/shell.c rpc/tunnel/tunnel.c
DEPS=rpc/stub/rpc_stub.h socket.h rpc/shell/shell.h rpc/tunnel/tunnel.h
ODIR=obj

OFILES=$(patsubst %.c,%.o,$(INPUT_DEPS))

%.o: $(INPUT) $(DEPS)
	$(CC) -c -o $(ODIR)/$(shell basename $@) $(patsubst %.o,%.c,$@) $(CFLAGS)

bin/tool: tool.o $(OFILES) 
	$(CC) -o $@ $(patsubst %,$(ODIR)/%,$(foreach file,$^,$(shell basename $(file)))) $(CFLAGS) $(LIBS)

bin/server: server.o $(OFILES)
	$(CC) -o $@ $(patsubst %,$(ODIR)/%,$(foreach file,$^,$(shell basename $(file)))) $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm bin/main obj/*.o
