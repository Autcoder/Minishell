CHECKER = ${addprefix checker/, ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_isspace.c ft_islower.c ft_isupper.c}

LIST = ${addprefix list/, ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c}

MEMORY = ${addprefix memory/, ft_bzero.c ft_calloc.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c free_ptr_array.c}

STRING = ${addprefix string/, ft_split.c ft_strchr.c ft_strlcat.c \
	ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_strlcpy.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strmapi.c ft_striteri.c ft_strrev.c ft_strlend.c}

OUTPUTS = ${addprefix output/, ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c}

CONVERT = ${addprefix convert/, ft_itoa.c ft_atoi.c ft_tolower.c ft_toupper.c ft_utoa.c ft_strtol.c}

INT = ${addprefix int/, ft_numlen.c ft_unumlen.c ft_base_numlen.c}

GNL = ${addprefix gnl/, get_next_line.c get_next_line_utils.c}

SRC = $(CHECKER) $(LIST) $(MEMORY) $(STRING) $(OUTPUTS) $(CONVERT) $(INT) $(GNL)

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I .
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

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "compiled objects.!."

# FIX: Added a recipe step to auto-create the subdirectory structures inside objs/ and deps/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(DEP_DIR)/$(dir $*)
	@$(CC) $(CFLAGS) $(LDFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "cleaned objects.!."

fclean: clean
	@rm -f $(NAME)
	@echo "cleaned all.!."

re: fclean all

.PHONY: all clean fclean re
