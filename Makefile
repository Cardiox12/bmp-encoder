# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/29 18:32:11 by bbellavi          #+#    #+#              #
#    Updated: 2020/05/30 21:20:33 by bbellavi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang
CFLAGS		= -Wall -Werror -Wextra -g
SRCS		= main.c
HEADERS 	= headers
MLX_NAME	= libmlx.a
MLX_HEADERS = minilibx
HEADERS_SRC = $(HEADERS)/bitmap.h

NAME		= main

all: $(NAME)

$(NAME): $(SRCS)
	@echo "Compiling"
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(MLX_NAME) -I$(HEADERS) -I$(MLX_HEADERS) -framework OpenGl -framework AppKit 

test: re
	@./$(NAME)
	@file img.bmp
	
clean:
	@echo "Cleaning"
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

fclean: clean

re: clean all