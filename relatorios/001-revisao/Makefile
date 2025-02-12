CC = gcc
CFLAGS = -Wall -Wextra -g
SRCS = $(wildcard *.c)
TARGETS = $(patsubst %.c, ./out/%,$(SRCS))

# Create the output directory if it doesn't exist
$(shell mkdir -p ./out)

# Pattern rule to compile each .c file into the corresponding target
./out/%: %.c
	$(CC) $(CFLAGS) $< -o $@

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

.PHONY: all clean
