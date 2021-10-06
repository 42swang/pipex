# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 15:39:21 by swang             #+#    #+#              #
#    Updated: 2021/10/06 20:14:39 by swang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB_DIR = ./libft
LFLAGS = -L./libft -lft

SRC_DIR = src/

SRC_NAME = main.c\
			pipex.c\
			ft_pipex_utils.c\
			ft_split_pipex.c\
			execute.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		make -C $(LIB_DIR) all
		$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)
	
clean :
		make -C $(LIB_DIR) clean
		rm $(OBJS)

fclean : clean
		make -C $(LIB_DIR) fclean
		rm $(NAME)

re : clean all

.PHONY : all clean fclean re