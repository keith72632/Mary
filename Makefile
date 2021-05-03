CC = gcc
FLAGS = -Wall -Wextra
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard *.h)

all: run

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

mary.o: mary.c
	${CC} ${FLAGS} -c $^ -o $@

mary: ${SRCS} 
	${CC} $^ -o $@

run: mary
	./mary 

test: mary
	./mary test.txt

clean:
	rm *.o mary
