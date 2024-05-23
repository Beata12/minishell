# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 10:08:35 by bmarek            #+#    #+#              #
#    Updated: 2024/05/22 14:27:06 by bmarek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -O2
#  CFLAGS += -fsanitize=memory

MAKE_LIB = ar -rcs

SRCS = ft_minishell.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline
# make title
#  @curl 'http://141.148.244.146:8080/ansi?start=3cc322&end=fdbb2d&padding=5&text=MiniShell'

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $^ 

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all title

.PHONY: all clean fclean re title

