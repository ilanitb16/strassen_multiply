CC = gcc
CFLAGS = -O3
SRCS = fmm.c main.c utilities.c
OBJS = $(SRCS:.c=.o)
OUT = main

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJS)
