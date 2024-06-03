# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 19:28:15 by aneekhra          #+#    #+#              #
#    Updated: 2024/05/14 14:16:03 by aneekhra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_tolower.c\
 ft_toupper.c ft_strchr.c ft_strrchr.c ft_bzero.c ft_strncmp.c ft_strnstr.c ft_atoi.c ft_strlcpy.c  ft_strlcat.c\
 ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strmapi.c\
 ft_itoa.c ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strtrim.c ft_striteri.c ft_split.c \
 ft_printf.c ft_putchar.c ft_putstr.c ft_putptr.c ft_putnbr.c ft_putnbr.c ft_putunbr.c ft_puthexa_low.c ft_puthexa_up.c \
 get_next_line.c

OBJS = $(SRCS:.c=.o)

BONUS = ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c\
	ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstadd_front_bonus.c

BONUS_OBJS = $(BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra  -std=c99 -fPIE

RM = rm -f
HEADER = libft.h
LIBS	= -L -lft

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
		 @ar -rc $(NAME) $(OBJS) 
		 make all 
		 clear
	
.o:.c 
		 @$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS) 

bonus:	$(NAME) $(OBJS) $(BONUS_OBJS)
	@ar -rcs $(NAME) $(OBJS) $(BONUS_OBJS)	

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	clear

fclean: 
	$(RM) $(NAME) $(OBJS) $(BONUS_OBJS)
	clear

re: fclean all



.PHONY: all clean fclean re bonus
