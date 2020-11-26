# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmustach <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 19:44:11 by nmustach          #+#    #+#              #
#    Updated: 2020/07/07 02:08:25 by nmustach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

HEADERS = lem_in.h

OBJDIR = objs/

CC = clang

LFTPATH = ./libft -lft

SRC = $(wildcard *.c)

LIBSRC = $(wildcard ./libft/*.c)

OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))
 
all: $(NAME)

$(NAME): $(LIBSRC) $(OBJ)
		@make -C $(LFTPATH)
		@echo 'Linking $@... '
		@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LFTPATH)
		@echo 'DONE'

include $(wildcard $(OBJDIR)*.d)  

$(OBJDIR)%.o : %.c
		@mkdir -p $(@D)
		@$(CC) -MMD $(FLAGS) -c $< -o $@
		@echo 'Compile $<'

clean:
		@echo 'rm object files..'
		@make clean -C $(LFTPATH)
		@rm -rf $(OBJDIR)
		@echo 'DONE'

fclean:
		@echo 'rm object files & executable..'
		@make fclean -C $(LFTPATH)
		@rm -rf $(OBJDIR)
		@rm -f $(NAME)
		@echo 'DONE'

re: fclean all
