# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/13 12:18:50 by cjulienn          #+#    #+#              #
#    Updated: 2022/09/12 14:31:10 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
UNDERLINE	= \e[4m
RESET		= \033[0m
END			= \e[0m

NAME = libft.a

SRC_DIR := .

SRC := $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR := obj
OBJ := $(SRC:.c=.o)
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ)))

INCLUDE := .

CC := gcc
CC_FLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(OBJ_DIR)/%.o : %.c libft.h
	@mkdir -p $(OBJ_DIR)
	@echo " Compiling: $< "
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_PREFIXED)
	@echo "$(NAME) has been created!\n"

clean:
	@printf "$(YELLOW)Removing object files...\n$(END)"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)Objects files have been removed\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing executable file...\n$(END)"
	@rm -f $(NAME)
	@printf "$(GREEN)Executable has been deleted\n$(END)"

re: fclean all

.PHONY: clean fclean all re
