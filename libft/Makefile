# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/17 16:38:23 by nmustach          #+#    #+#              #
#    Updated: 2020/11/22 18:56:13 by nmustach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = $(wildcard ft_*.c)

BIN = $(SRCS:.c=.o) 
HEAD = ./libft.h

all: $(NAME)

$(NAME):$(BIN)
	@echo 'Build libft'
	@ar rc $(NAME) $(BIN)
	@ranlib $(NAME)

%.o : %.c $(HEAD)
	@gcc -Wall -Wextra -Werror -c $< -o $@
	@echo 'Compile $<'

clean:
	@echo 'Deleting object files...'
	@rm -f $(BIN)
	@echo 'Done'

fclean:
	@echo 'Deleting object files and libft.a ...'
	@rm -f $(NAME)
	@rm -f $(BIN)
	@echo 'Done'
	
re: fclean all