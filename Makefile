# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 16:48:15 by daalmeid          #+#    #+#              #
#    Updated: 2022/07/21 16:39:09 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################## Program #################

NAME	=		Cub3D

################## COLORS ##################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################## TERMINAL ################

RM		=		rm -f
MAKE	+=		-s

################## COMPILER ################

CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra -O2

################## FILES ###################

_OBJ	=	./objs/
_SRC	=	./srcs/

SRCS_	=	main.c\
			image_draw_utils.c\
			raycaster.c\
			handlers.c\
			collision.c\
			minimap.c\
			fov_minimap.c\
			hooks.c\
			rc_painter.c\
			rc_hit_find.c\
			map/content.c\
			map/errors.c\
			map/map.c\
			map/resize.c\
			map/types.c\
			map/utils.c\
			map/verify.c

SRCS	=	$(addprefix $(_SRC), $(SRCS_))
OBJS	=	$(patsubst $(_SRC)%.c, $(_OBJ)%.o, $(SRCS))

DEPS	=	srcs/libmlx/libmlx_Linux.a srcs/libft/libft.a

LDFLAGS	=	-lmlx -lft -lXext -lX11 -lm

LDLIBS_	=	./srcs/libmlx ./srcs/libft /usr/lib
LDLIBS	=	$(addprefix -L , $(LDLIBS_))

INCS_	=	./include/ /usr/include ./src/libmlx ./src/libft
INCS	=	$(addprefix -I, $(INCS_))

################## RULES ###################

all: $(NAME)

$(NAME): $(DEPS) $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCS) $(LDLIBS) $(LDFLAGS) -o $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

srcs/libmlx/libmlx_Linux.a:
	$(MAKE) -C $(dir $@)

srcs/libft/libft.a: $(shell make -C ./srcs/libft/ -q libft.a || echo force)
	$(MAKE) $(notdir $@) -C $(dir $@)

$(_OBJ):
	mkdir $@
	mkdir $@/map

################## CLEAN ###################

clean:
	$(RM) -r $(_OBJ)
	$(MAKE) clean -C srcs/libmlx/
	$(MAKE) clean -C srcs/libft/

fclean: clean
	$(MAKE) fclean -C srcs/libft/
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re force
