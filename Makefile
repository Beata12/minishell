# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:48:34 by aneekhra          #+#    #+#              #
#    Updated: 2024/06/04 19:22:46 by aneekhra         ###   ########.fr        #
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
		src/shell_commands/unset.c \
		src/shell_commands/ls.c \
		src/shell_commands/touch.c \
		src/shell_commands/export.c \
		src/shell_commands/rm.c \
		src/shell_commands/mkdir.c \
		src/shell_commands/clear.c \
#src/shell_commands/export.c

LIBFTFOLDER = Libft

LIBFT = $(LIBFTFOLDER)/libft.a

OBJS = $(SRCS:.c=.o)

# Color definitions
GREEN = \033[0;32m
RED = \033[0;31m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
ENDCOLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "${GREEN}✅ $(NAME) Compilation completed successfully! ✅${ENDCOLOR}"
	
$(LIBFT):
	@make -C $(LIBFTFOLDER) --silent
		clear

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
