# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 14:33:14 by ada-mata          #+#    #+#              #
#    Updated: 2024/01/30 14:32:24 by ada-mata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS =  $(wildcard src/*.c utils/*.c *.c)

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -std=c99 -O3 -g -fsanitize=address

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${MAKE} -C ./libs/libft
	@${MAKE} -C ./libs/printf
	@${CC} ${CFLAGS} ${OBJS} ./libs/libft/libft.a ./libs/printf/ft_printf.a -o ${NAME}

clean: 
	@${MAKE} -C ./libs/libft fclean
	@${MAKE} -C ./libs/printf fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
