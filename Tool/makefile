CC=gcc
CFLAGS=-I.
DEPS = socket.h rpc_stub.h
LIBS=-lm
ODIR=obj

_OBJ = main.o socket.o rpc_stub.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
