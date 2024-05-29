# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:48:34 by aneekhra          #+#    #+#              #
#    Updated: 2024/05/28 18:02:57 by aneekhra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
#  CFLAGS += -fsanitize=memory

SRCS =  src/minishell.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lreadline
	@echo "${GREEN}✅ $(NAME) Compilation completed successfully! ✅${ENDCOLOR}"
	

clean:
	@echo "${RED}🧹 Cleaning objects... 🧹${ENDCOLOR}"
	@rm -f $(OBJS)
	@echo "${CYAN}✅ Simple clean completed! ✨${ENDCOLOR}"

fclean: clean
	@echo "${RED}🧹 Cleaning program... 🧹${ENDCOLOR}"
	@rm -f $(NAME)
	@echo "${MAGENTA}✅ Deep clean completed! ✨${ENDCOLOR}"

re: fclean all

.PHONY: all clean fclean re
