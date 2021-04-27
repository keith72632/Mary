CC = gcc
FLAGS = -Wall -Wextra
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard *.h)

all: run

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

mary: mary.o
	${CC} $^ -o $@

run: mary
	./$^

clean:
	rm *.o mary
