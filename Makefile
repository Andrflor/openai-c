TCC=tcc
CC=gcc
DEBUGGER=gdb

CFLAGS=-lcurl
CCOV=-fprofile-arcs -ftest-coverage

SRC=src
BUILD=build
TEST=tests

BIN=$(BUILD)/openai
OBJS=$(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

SRCS=$(wildcard $(SRC)/*.c)
TESTS=$(wildcard $(TEST)/*.c))

INITBUILD=mkdir -p $(BUILD)
COMPILE=$(INITBUILD) && $(TCC) $(CFLAGS) $(SRCS)

all: $(BIN) $(BUILD)/libopenai-c.a $(BUILD)/libopenai-c.so

$(BIN): $(OBJS)
	$(CC) $^ -o $@ -lcurl

$(OBJS): $(BUILD)/%.o : $(SRC)/%.c
	$(INITBUILD) && $(CC) -c $< -o $@ $(CFLAGS) -fPIC

$(BUILD)/libopenai-c.a: $(OBJS)
	ar rcs $@ $^

$(BUILD)/libopenai-c.so: $(SRCS)
	$(CC) -fPIC -shared $(SRCS) -o $@ $(CFLAGS)

run:
	$(COMPILE) -g -o $(BIN) && ./$(BIN)

debug:
	$(COMPILE) -g -o $(BIN)  && $(DEBUGGER) -q -ex run $(BIN)

clean:
	rm -r $(BUILD)
