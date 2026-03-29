CC = clang
CFLAGS = -Wall -Wextra -g
BUILD_DIR = build
SRC_DIR = how_to
TEST_DIR = tests
LIB_HEADER = aids.h

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
EXECS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/tests/%.o,$(TEST_SRCS))
TEST_EXECS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/tests/%,$(TEST_SRCS))

all: $(EXECS) $(TEST_EXECS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_HEADER) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c $(LIB_HEADER) $(TEST_DIR)/shared.h | $(BUILD_DIR)/tests
	$(CC) $(CFLAGS) -I. -I$(TEST_DIR) -c $< -o $@

$(BUILD_DIR)/tests/%: $(BUILD_DIR)/tests/%.o
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/tests:
	mkdir -p $(BUILD_DIR)/tests

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
