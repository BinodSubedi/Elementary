BINARY = elementary
CC = gcc
CODEDIRS= ./src
INCDIRS = ./src/includes/
OPTIMIZATION = -O0

DEPFLAGS = -MP -MD

CFLAGS = -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(OPTIMIZATION) $(DEPFLAGS)

# We used wildcard because we are maching up with files with use of *
CFILES = $(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEPFILES = $(patsubst %.c, %.d, $(CFILES))


all: $(BINARY)

$(BINARY): $(OBJECTS)
				$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)


-include $(DEPFILES)


.PHONY: all clean

