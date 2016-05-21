CC=gcc
CFLAGS=-Wall
LDFLAGS=-lrt
EXEC=TP_reel


all: $(EXEC)

TP_reel: utilities.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c utilities.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -rf $(EXEC)

demo : 
	make
	./$(EXEC) 100 1 1000 0 --verbose
	./$(EXEC) 100 1 100 0 --verbose
	./$(EXEC) 100 0 1000 0 --verbose
	./$(EXEC) 100 0 100 1 --verbose
