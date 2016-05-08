# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fviolin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/29 10:22:18 by fviolin           #+#    #+#              #
#    Updated: 2016/03/20 12:56:03 by fviolin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

C_DIR = srcs
C_FILES = $(shell find $(C_DIR) -type f -follow -print | grep "\.c")

OBJ = $(C_FILES:.c=.o)
LIB = ../libft/libft.a
FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	make -C ../libft
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean :
	rm -f $(OBJ)
	make -C ../libft/ clean

fclean: clean
	rm -rf $(NAME)
	make fclean -C ../libft

re: fclean all

.PHONY : all clean fclean re
