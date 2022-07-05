# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 18:12:17 by daalmeid          #+#    #+#              #
#    Updated: 2022/05/03 13:04:25 by daalmeid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_isalnum.c ft_itoa.c ft_memset.c ft_split.c ft_strlcat.c\
		ft_strnstr.c ft_toupper.c ft_isalpha.c ft_memchr.c ft_putchar_fd.c\
		ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_atoi.c ft_isascii.c\
		ft_memcmp.c ft_putendl_fd.c ft_strdup.c ft_strlen.c ft_strtrim.c\
		ft_bzero.c ft_isdigit.c ft_memcpy.c ft_putnbr_fd.c ft_striteri.c\
		ft_strmapi.c ft_substr.c ft_calloc.c ft_isprint.c ft_memmove.c\
		ft_putstr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c get_next_line.c

SRCS_BONUS	= ft_lstadd_back.c ft_lstsize.c ft_lstadd_front.c ft_lstclear.c\
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c

OBJS	= *.o

RM = rm -f

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS):
	gcc -Wall -Wextra -Werror -c $(SRCS)
	
all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

bonus: clean
	gcc -Wall -Wextra -Werror -c $(SRCS) $(SRCS_BONUS)
	ar rc $(NAME) $(OBJS)

.PHONY: all clean fclean re