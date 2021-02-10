
CFLAGS = -W -Wall -g -O0
CC = gcc 
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = interface
RM = rm -rf

all: $(EXEC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

clean:
	$(RM) $(EXEC)
	$(RM) $(OBJ)
	make -C doc clean

.PHONY: all clean doc

doc:
	make -C doc

