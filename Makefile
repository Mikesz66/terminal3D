CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses -lm

TARGET = renderer

SRCS = main.c engine.c engineMath.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
