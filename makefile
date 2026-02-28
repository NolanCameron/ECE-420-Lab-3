CC = gcc
CFLAGS = -Wall -Werror -Wvla -lpthread -ggdb3 -lm
DEPS = timer.h Lab3IO.h
OBJ = main.o Lab3IO.o

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

all: datagen main
	
.PHONY: datagen
datagen: datagen.o
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: memtest
memtest: main 
	valgrind --tool=memcheck --leak-check=yes ./main 100

.PHONY: threadtest
threadtest: main
	valgrind --tool=helgrind ./main 100

.PHONY: clean
clean:
	rm -f *.o main datagen