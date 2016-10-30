CC=gcc
EXEC=tri
SRC= main.c tri.c tri.h triAffichage.h triAffichage.c
OBJ= $(SRC:.c=.o)

#Flags sans warnings
#CFLAGS= -g -w
# Flags avec warnings
CFLAGS= -g -Wall

PACKAGES=
CLIBFLAGS=  $(shell pkg-config --cflags $(PACKAGES))
#LIBS= $(shell pkg-config --libs $(PACKAGES)) -lpthread
LIBS= $(shell pkg-config --libs $(PACKAGES))



$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

main.o: main.c tri.h triAffichage.h
	$(CC) $(CFLAGS) -o $@ -c $< 

tri.o: tri.c tri.h
	$(CC) $(CFLAGS) -o $@ -c $<

triAffichage.o: triAffichage.c triAffichage.h tri.h
	$(CC) $(CFLAGS) -o $@ -c $<

#terminal.o: terminal.c
#	$(CC) $(CFLAGS) -o $@ -c $< $(CLIBFLAGS)


.PHONY: clean
clean:
	@rm -rf *.o
