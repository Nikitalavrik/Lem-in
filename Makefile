#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 17:55:29 by nlavrine          #+#    #+#              #
#    Updated: 2019/06/25 17:55:30 by nlavrine         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

SRC =	main.c			\
		rooms.c			\
		parsing.c		\
		sys_output.c	\
		dijkstra.c		\
		queue.c			\
		find_way.c		\
		free_all.c		\
		calculator.c	\

CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
H_DIR = includes
OBJ_DIR = obj
LIB = libft/libft.a
PRINTF = libft/ft_printf/libftprintf.a

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))

OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME) 

$(NAME): $(LIB) $(PRINTF) $(OBJS)
		@$(CC) $(FLAGS) $(OBJS) $(PRINTF) $(LIB) -o $(NAME) -g
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(H_DIR) -g

$(LIB):
	@make -C ./libft/

$(PRINTF):
	@make -C ./libft/ft_printf/

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -C ./libft/ clean
	@make -C ./libft/ft_printf/ clean

fclean: clean
	@rm $(NAME)
	@make -C ./libft/ fclean
	@make -C ./libft/ft_printf/ fclean

re: fclean all
	@make -C ./libft/ re
	@make -C ./libft/ft_printf/ re