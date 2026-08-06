SRC = minishell.c parser.c env_thingie.c scan_expand_save.c scan_expand_utils.c expand_and_quotes.c built_ins.c \
		builtin_center.c execution_utils.c more_utils.c signals.c export.c init.c exit.c freeing.c ft_unset.c \
		more_exec_utils.c execute.c execute_utils.c build_cmds.c child_process.c

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Uncomment if device needs readline
# Tell the linker where to search
LDFLAGS := -L/opt/homebrew/opt/readline/lib -lreadline

READLINE_INC = -I/opt/homebrew/opt/readline/include

DEP_DIR = deps
DEBUG ?= 0

# Generate a true ASCII escape character for $(info) or echo
ESC := $(shell printf '\033')
RED := $(ESC)[0;31m
RESET := $(ESC)[0m

ifeq ($(DEBUG),1)
    CFLAGS += -g
else ifeq ($(DEBUG),2)
    CFLAGS += -g -fsanitize=address -Wconversion -Wsign-conversion -fsanitize=undefined -Warray-bounds -Wnull-dereference
endif

# Print ONLY if DEBUG is active AND we are in the main execution pass
ifneq ($(filter 1 2,$(DEBUG)),)
    ifndef DEBUG_PRINTED
        $(info $(RED)========================================$(RESET))
        $(info $(RED)=====!!! DEBUG FLAGS ARE ACTIVE !!!=====$(RESET))
        $(info $(RED)========================================$(RESET))
        export DEBUG_PRINTED := 1
    endif
endif

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "Minishell compiled successfully!"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(DEP_DIR)/$(dir $*)
	@$(CC) $(CFLAGS) $(READLINE_INC) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "cleaned objects.!."

fclean:
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@rm -f $(NAME)
	@echo "cleaned all.!."

re: fclean all

urmom:
	make fclean
	compiledb -n make
cl:
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@rm -f $(NAME)
	@echo "cleaned all (BUT LIBFT).!."

r: cl all

.PHONY: all clean fclean re
