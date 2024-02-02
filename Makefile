# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 16:44:03 by ada-mata          #+#    #+#              #
#    Updated: 2024/02/02 18:00:14 by ada-mata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =  $(wildcard srcs/*.c utils/*.c *.c)

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -std=c99 -O3 -g #-fsanitize=address

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${MAKE} -C ./libs/libft -s
	@${MAKE} -C ./libs/printf -s
	@${CC} ${CFLAGS} ${OBJS} ./libs/libft/libft.a ./libs/printf/ft_printf.a -o ${NAME}

clean: 
	@${MAKE} -C ./libs/libft fclean -s
	@${MAKE} -C ./libs/printf fclean -s
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

.SILENT:
