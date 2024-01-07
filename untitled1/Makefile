CC=gcc
CFLAGS=-I.

# Object files
OBJ = main.o patient.o login.o

# Header dependencies
DEPS = patient.h login.h

# Compiling each source file
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Linking all object files to create the executable
myprogram: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Phony target for clean
.PHONY: clean

clean:
	rm -f *.o myprogram
