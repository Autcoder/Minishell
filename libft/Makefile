# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flink <flink@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 14:35:44 by flenski           #+#    #+#              #
#    Updated: 2026/02/19 14:04:29 by flink            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER = checker/ft_isalnum.c checker/ft_isalpha.c checker/ft_isascii.c \
	checker/ft_isdigit.c checker/ft_isprint.c checker/ft_isspace.c \
	checker/ft_islower.c checker/ft_isupper.c

LIST = list/ft_lstadd_back.c list/ft_lstadd_front.c list/ft_lstclear.c \
	list/ft_lstdelone.c list/ft_lstiter.c list/ft_lstlast.c \
	list/ft_lstmap.c list/ft_lstnew.c list/ft_lstsize.c

MEMORY = memory/ft_bzero.c memory/ft_calloc.c memory/ft_memchr.c \
	memory/ft_memcmp.c memory/ft_memcpy.c memory/ft_memmove.c memory/ft_memset.c \
	memory/free_ptr_array.c

STRING = string/ft_split.c string/ft_strchr.c string/ft_strlcat.c \
	string/ft_strlen.c string/ft_strncmp.c string/ft_strnstr.c \
	string/ft_strrchr.c string/ft_strtrim.c string/ft_strlcpy.c \
	string/ft_strdup.c string/ft_substr.c string/ft_strjoin.c \
	string/ft_strmapi.c string/ft_striteri.c string/ft_strrev.c \
	string/ft_strlend.c

OUTPUTS = output/ft_putendl_fd.c output/ft_putnbr_fd.c output/ft_putstr_fd.c \
	output/ft_putchar_fd.c

CONVERT = convert/ft_itoa.c convert/ft_atoi.c convert/ft_tolower.c \
	convert/ft_toupper.c convert/ft_utoa.c convert/ft_strtol.c

INT = int/ft_numlen.c int/ft_unumlen.c int/ft_base_numlen.c

SRC = $(CHECKER) $(LIST) $(MEMORY) $(STRING) $(OUTPUTS) $(CONVERT) $(INT)
OBJS = $(SRC:.c=.o)

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I .
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
	ar rcs $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
