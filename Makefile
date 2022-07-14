# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 16:48:15 by daalmeid          #+#    #+#              #
#    Updated: 2022/07/14 17:10:09 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################## Program #################

NAME = Cub3D

################## COLORS ##################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################## TERMINAL ################

RM		=		rm -f

################## COMPILER ################

CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra

################## FILES ###################

SRCS	=	srcs/main.c\
			srcs/image_draw_utils.c\
			srcs/raycaster.c\
			srcs/handlers.c\
			srcs/collision.c\
			srcs/minimap.c

OBJ	=	$(patsubst %.c, %.o, $(SRCS))

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

#LIB_DIR	=	-L./libft -L/usr/local/lib/
#LIBS	=	-lft -lmlx
#FRMWRKS	=	-framework OpenGL -framework AppKit


################## RULES ###################

all: $(NAME)

libft:
	cd libft && make

$(NAME): $(OBJ) libft
	$(CC) $(OBJ) -L./mlx_linux -lmlx_Linux  -Llibft -lft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME)

################## CLEAN ###################

clean:
	cd libft && make clean
	$(RM) $(OBJ)

fclean: clean
	cd libft && make fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
