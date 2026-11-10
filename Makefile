Name 	    := prog

# variables

CC          := gcc
C_FLAGS     := -Wall -std=c99
# so i will get every little warning communicated


LIBS        := -lm

SRC_DIR     := src
BUILD_DIR   := build

SRCS        := $(shell find $(SRC_DIR) -name '*.c')
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# creates a list from the source files to create

# RECIPES


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) -o $@ $^

# $@ = target, $< = first prerequisite

$(OBJS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c -o $@ $<

clean:
	rm -r $(BUILD_DIR)
	rm $(NAME)

#   SPECS

.PHONY: all
.PHONY: clean

-include $(DEPS)


#we let the Makefile run with make to create a file called prog
