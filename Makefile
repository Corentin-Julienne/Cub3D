# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 16:19:40 by cjulienn          #+#    #+#              #
#    Updated: 2023/05/06 20:49:05 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# colors set
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

NAME := Cub3D
TEST_NAME := Cub3D_test

CC := gcc
CFLAGS := -Wall -Wextra -Werror

INCLUDES := -I includes

SRC_DIR := srcs
OBJ_DIR := objs
SUB_DIRS := algorithm bonus game free graphics main parsing utils
SOURCEDIRS := $(foreach dir, $(SUB_DIRS), $(addprefix $(SRC_DIR)/, $(dir)))

SRC_FILES := $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:.c=.o)))

RM = rm -rf
MKDIR = mkdir -p

# libft
LIB_DIR := libft
LIB_OBJ_DIR := libft/obj
LIB := libft.a

UNAME := $(shell uname)

# MiniLibX (last beta 2021 version)
ifeq ($(UNAME), Linux)

	MINILIBX_DIR := mlx_linux
	MINILIBX := mlx_Linux
	MINILIBX_LINK := mlx_Linux
	COMPILE_MLX_ARGS := -L/usr/lib -I$(MINILIBX_DIR) -lXext -lX11 -lm -lz

else

	MINILIBX_DIR := mlx
	MINILIBX := libmlx.dylib
	MINILIBX_LINK := mlx
	COMPILE_MLX_ARGS := -framework OpenGL -framework AppKit

endif

VPATH = $(SOURCEDIRS)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIB) $(MINILIBX)
	@printf "$(YELLOW)Linking Cub3D...\n\n$(END)"
	$(CC) $(CFLAGS) $(OBJ_FILES) -L$(MINILIBX_DIR) -l$(MINILIBX_LINK) $(COMPILE_MLX_ARGS) $(LIB) -o $(NAME)
	@printf "\n$(GREEN)Cub3D compiled.\n$(END)$(GREEN)Simply type$(END) $(WHITE)./Cub3D $(END)"
	@printf "$(GREEN)with a *.cub map as argument to execute the program. \n\n$(END)"

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(OBJ_DIR)
	@printf "$(YELLOW)Compiling object:\n$(END)"
	@$(CC) $(CFLAGS) -Imlx $(INCLUDES) -c -o $@ $<
	@printf "$(GREEN)Object $(UNDERLINE)$(WHITE)$(notdir $@)$(END)$(GREEN) successfully compiled\n\n$(END)"

$(LIB):
	@printf "$(YELLOW)Compiling libft.a...\n$(END)"
	@make --no-print-directory $(LIB) -C $(LIB_DIR)
	@mv $(LIB_DIR)/$(LIB) .
	@printf "$(GREEN)libft.a compiled\n\n$(END)"

$(MINILIBX):
	@printf "$(YELLOW)Compiling MiniLibX...\n$(END)"
	@$(MAKE) -C $(MINILIBX_DIR)
	@printf "$(GREEN)MiniLibX has been created\n$(END)"
	@cp ./mlx/libmlx.dylib . 2>/dev/null || :

clean:
	@printf "$(YELLOW)Removing objects...\n$(END)"
	$(RM) $(OBJ_DIR)
	$(RM) $(LIB_OBJ_DIR)
	$(MAKE) -C $(MINILIBX_DIR) clean
	@printf "$(GREEN)Objects removed!\n\n$(END)"

fclean: clean
	@printf "$(YELLOW)Removing objects, libft, MiniLibX and Cub3D executable...\n$(END)"
	$(RM) $(NAME)
	$(RM) $(LIB)
	@rm -f ./libmlx.dylib
	@printf "$(GREEN)All clean!\n\n$(END)"

re: fclean all

.PHONY: clean fclean all re
