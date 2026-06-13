SRC = minishell.c parser.c

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Uncomment if device needs readline
LDFLAGS := -lreadline

DEP_DIR = deps
DEBUG ?= 0
RED := \033[1;31m
RESET := \033[0m

define debug_warning
$(warning $(RED)========================================$(RESET))
$(warning $(RED)=====!!! DEBUG FLAGS ARE ACTIVE !!!===== $(RESET))
$(warning $(RED)========================================$(RESET))
endef

ifeq ($(DEBUG),1)
CFLAGS += -g
$(eval $(call debug_warning))
endif
ifeq ($(DEBUG),2)
CFLAGS += -g -fsanitize=address -Wconversion -Wsign-conversion -fsanitize=undefined
$(eval $(call debug_warning))
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
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "cleaned objects.!."

fclean:
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "cleaned all.!."

re: fclean all

.PHONY: all clean fclean re