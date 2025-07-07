CC = gcc
CFLAGS = -Wall -Wextra -I./src
LDFLAGS = -lncurses
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = boilercrate

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f src/*.o $(TARGET)