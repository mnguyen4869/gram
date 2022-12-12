CC := gcc
CFLAGS := -Wall -pedantic -Wextra -Werror

SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := tests

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST := $(wildcard $(TEST_DIR)/*.c)
TEST_BIN := "$(TEST_DIR)/run-tests"
VAL := $(wildcard $(TEST_DIR)/valgrind-out.txt*)

LIBNAME := libgramlinalg

.PHONY: dynamic-lib static-lib run-tests clean

all: dynamic-lib

dynamic-lib: $(OBJ)
	$(CC) $< -shared -o "$(LIBNAME).so"

static-lib: $(OBJ)
	ar -cvq "$(LIBNAME).a" $<

$(TEST_BIN):
	$(CC) $(CFLAGS) -ggdb3 $(SRC) $(TEST) -o "$(TEST_DIR)/run-tests"

run-tests: $(TEST_BIN)
	."/$(TEST_BIN)"

run-valgrind: $(TEST_BIN)
	valgrind --leak-check=full \
    	--show-leak-kinds=all \
    	--track-origins=yes \
    	--verbose \
    	--log-file="$(TEST_DIR)/valgrind-out.txt" \
    	."/$(TEST_BIN)"
	cat "$(TEST_DIR)/valgrind-out.txt"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -fpic -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rfv $(OBJ_DIR)
	rm -rfv $(TEST_BIN)
	rm -rfv $(VAL)
