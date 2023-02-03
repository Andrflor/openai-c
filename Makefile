TCC=tcc
CC=gcc
DEBUGGER=gdb

CFLAGS=-lcurl

SRC=src
BUILD=build
TEST=tests

BIN=$(BUILD)/openai
OBJS=$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

SRCS=$(wildcard $(SRC)/*.c)
TESTS=$(wildcard $(TEST)/*.c))

INITBUILD=mkdir -p $(BUILD)
COMPILE=$(INITBUILD) && $(TCC) $(CFLAGS) $(SRCS)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@ -lcurl

$(OBJS): $(BUILD)/%.o : $(SRC)/%.c
	$(INITBUILD) && $(CC) -c $< -o $@ -lcurl

run:
	$(COMPILE) -o $(BIN) && ./$(BIN)

debug: $(BIN)
	$(COMPILE) -g -o $(BIN)  && $(DEBUGGER) -q -ex run $(BIN)

clean:
	rm -r $(BUILD)
