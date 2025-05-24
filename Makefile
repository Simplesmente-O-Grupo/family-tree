CC := gcc

DEP_DIR := .deps
BUILD_DIR := build
SRC_DIR := src

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(SRCS))

TARGET := ftree

DEPFLAGS = -MMD -MP -MF $(patsubst $(BUILD_DIR)/%.o,$(DEP_DIR)/%.d,$@)

CFLAGS := -g -Wextra -Wall -Werror -Isrc/include

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) $(dir $(patsubst $(BUILD_DIR)/%.o,$(DEP_DIR)/%.d,$@))
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)

# Limpeza
.PHONY: clean
clean:
	rm -rfv $(BUILD_DIR) $(DEP_DIR) $(TARGET)
