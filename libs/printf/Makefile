# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 15:11:36 by ada-mata          #+#    #+#              #
#    Updated: 2024/02/01 17:02:09 by ada-mata         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
RM = rm -rf
NAME = ft_printf.a

SRCS = ft_printf.c ft_words.c ft_numbers.c

OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)
		# ranlib ${NAME}
clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re

.SILENT:
