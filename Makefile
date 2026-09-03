CC       := gcc
CFLAGS   := -Wall -Wextra -Wpedantic -std=c11 -g -O2
DEPFLAGS := -MMD -MP

TARGET   := spalkc
SRC_DIR  := src
BUILD_DIR:= build

SRCS     := $(wildcard $(SRC_DIR)/*.c)
OBJS     := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
