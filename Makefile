# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 10:18:53 by thbierne          #+#    #+#              #
#    Updated: 2024/09/02 14:52:34 by thbierne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc

SRCS = 	main.c 						\
		srcs/malloc.c 				\
		srcs/free.c 				\
		srcs/realloc.c 				\
		srcs/utils.c 				\
		srcs/display.c 				\

OBJS = $(SRCS:.c=.o)				\

CC = gcc 

LDFLAGS = -shared -fpic

HOSTTYPE = $(shell uname -m)_$(shell uname -s)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)



	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $(SRCS)
	@$(CC) $(SRCS) -o $(NAME)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Creating:\033[0m" $(NAME)


clean:
	@$(RM) $(OBJS)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Delete:\033[0m" $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Delete:\033[0m" $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJS)