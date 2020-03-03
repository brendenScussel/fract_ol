# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bscussel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 22:11:08 by bscussel          #+#    #+#              #
#    Updated: 2020/01/13 01:04:42 by bscussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

CFLAGS = -O2 -Wall -Wextra -Werror

MLXFLAGS = -lmlx -framework OpenGL -framework Appkit

THREADS = -lpthread

HEADER = ./inc/fractol.h

CFILES = ./src/fractol.c \
		./src/input.c \
		./src/mandelbrot.c \
		./src/julia.c \
		./src/gemini_sun.c \

LIBFT = ./libft/libft.a

MLIBX = minilibx/libmlx.a

OBJ_DIR = obj

all: $(NAME)

$(NAME):
	@echo "\033[0;35mBuilding Fractol...\033[0m"
	$(MAKE) -s -C libft
	ranlib $(LIBFT)
	ranlib $(MLIBX)
	$(CC) $(CFLAGS) -I=$(HEADER) -o $(NAME) $(CFILES) $(LIBFT) \
		-I minilibx -L minilibx $(MLXFLAGS) $(THREAD)

clean :
	@echo "\033[0;35mCleaning Object Files...\033[0m"
	$(MAKE) -s clean -C libft
	rm -rf $(O_FILES) obj/$(O_FILES) obj

fclean :
	@echo "\033[0;35mCleaning EVERYTHING...\033[0m"
	$(MAKE) -s fclean -C libft
	rm -rf $(NAME) $(O_FILES) obj/$(O_FILES) obj $(LIBFT)

re: fclean all

.PHONY: clean fclean all re
