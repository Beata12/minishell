# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 17:48:34 by aneekhra          #+#    #+#              #
#    Updated: 2024/06/07 19:36:14 by aneekhra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
CC 			= cc
#CFLAGS 		= -Wall -Wextra -Werror -Iinclude

LIBFTFOLDER = Libft
LIBFT 		= $(LIBFTFOLDER)/libft.a

#  CFLAGS += -fsanitize=memory

SRCS 	=  	src/minishell.c \
			src/utils/util.c \
			src/parsing/parsing.c \
			src/parsing/lexer.c \
			src/parsing/rediraction.c \
			src/execution/builtins/echo.c \
			src/execution/builtins/env.c \
			src/execution/builtins/cd.c \
			src/execution/builtins/exit.c \
			src/execution/builtins/pwd.c \
			src/execution/builtins/unset.c \
			src/execution/builtins/export.c \
			src/execution/execution.c \
			src/utils/special_char.c \
			src/utils/signal.c \
			src/execution/utils_exec.c \
			src/execution/utils_error.c \


OBJS 	= $(SRCS:.c=.o)

# Color definitions
GREEN = \033[0;32m
RED = \033[0;31m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
ENDCOLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
#clear
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
