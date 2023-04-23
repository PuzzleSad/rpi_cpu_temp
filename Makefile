# CC=ccache gcc
CC=gcc
CFLAGS=-Wall -Wextra -O2 --std=c11

BIN=a.elf

HEADERDIR=.
SOURCEDIR=.
BUILDDIR=build


SOURCES= $(wildcard *.c)\
	$(wildcard src/*.c)\


OBJECTS= $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCES)) )


all: bin run

# all: 
# 	@echo $(SOURCES)
# 	@echo $(OBJECTS)

nrun: bin

bin: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN): $(OBJECTS)
	@echo "linking..."
	@$(CC) $(CFLAGS) -o $@ $^ -lm -lsqlite3 -lpthread

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

