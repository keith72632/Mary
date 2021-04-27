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

mary: ${SRCS} ${HEADERS}
	${CC} $^ -o $@

run: mary
	./mary 

clean:
	rm *.o mary
