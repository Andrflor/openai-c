TCC=tcc
CC=gcc
DEBUGGER=gdb

CFLAGS=-lcurl

SRC=src
BUILD=build
TEST=tests

BIN=$(BUILD)/openai

SRCS=$(wildcard $(SRC)/*.c)
TESTS=$(wildcard $(TEST)/*.c))

INITBUILD=mkdir -p $(BUILD)
COMPILE=$(INITBUILD) && $(TCC) $(CFLAGS) $(SRCS)

all:
	$(COMPILE) -o $(BIN)

run:
	$(COMPILE) -o $(BIN) && ./$(BIN)

clean:
	rm -r $(BUILD)

debug:
	$(COMPILE) -g -o $(BIN)  && $(DEBUGGER) $(BIN)
