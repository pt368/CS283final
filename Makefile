CC=gcc
FLAGS=-I./src/ `pkg-config --cflags opencv` -fopenmp
TARGETS= mosaic etch sharpen tsh testapi
LIBS=-lm `pkg-config --libs opencv` -fopenmp

main: $(TARGETS)


lib/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) lib/*.o

%:lib/%.o lib/hw4.o
	$(CC) -o $@ $^ $(LIBS)
	gcc -Wall -lssl -lcrypto -o testapi src/testapi.c
