CC=clang
CFLAGS=-I.
DEPS = main.h pit.h signer.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spv: main.o pit.o signer.o
	$(CC) -o spv main.o pit.o signer.o
