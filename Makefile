CC = gcc
FLAGS = -Wall -Wextra
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard *.h)

all: run

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

puke: ${OBJS} ${HEADERS}
	${CC} $^ -o $@

run: puke
	./$^

clean:
	rm *.o puke
