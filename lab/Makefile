# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 16:28:40 by cjulienn          #+#    #+#              #
#    Updated: 2022/09/18 11:43:04 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := Lab

CC := gcc
CFLAGS := -Wall -Wextra -Werror 

SRCS = ./tuto.c
OBJS = $(SRCS:.c=.o)

RM = rm -rf

# MiniLibX (2020 version)
MINILIBX_DIR := mlx
MINILIBX := libmlx.dylib

all: $(NAME)

$(NAME): $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@cp ./mlx/libmlx.dylib .

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR)

.c.o:
	$(CC) $(CFLAGS) -Imlx -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(MINILIBX_DIR) clean 
	rm ./libmlx.dylib

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
