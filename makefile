CC = gcc
CFLAGS = -Wall -Werror -Wvla -fopenmp -lpthread -ggdb3 -lm

DEPS = timer.h Lab3IO.h
OBJ = main.o Lab3IO.o



main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
all: datagen main

.PHONY: datagen
datagen: datagen.o Lab3IO.o
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: memtest
memtest: main 
	valgrind -s --track-origins=yes --tool=memcheck --leak-check=yes --show-leak-kinds=all ./main 1
	
.PHONY: threadtest
threadtest: main
	valgrind --tool=helgrind ./main 4

.PHONY: clean
clean:
	rm -f *.o main datagen