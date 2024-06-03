# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:48:34 by aneekhra          #+#    #+#              #
#    Updated: 2024/06/03 10:08:39 by bmarek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -Iinclude
#  CFLAGS += -fsanitize=memory

SRCS =  src/minishell.c \
		src/util.c \
		src/parsing.c \
		src/lexical_parser.c \
		src/rediraction.c \
		src/special_char.c \
		src/shell_commands/echo.c \
		src/shell_commands/env.c \
		src/shell_commands/cd.c \
		src/shell_commands/exit.c \
		src/shell_commands/pwd.c \
		src/shell_commands/unset.c
#src/shell_commands/export.c
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
