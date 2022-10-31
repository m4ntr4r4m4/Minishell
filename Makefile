# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 13:14:42 by ahammoud          #+#    #+#              #
#    Updated: 2022/10/31 12:19:24 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./src/expander.c

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	 expander

CFLAGS	=	-Wall -Werror -Wextra


CC	=	clang


${NAME}	:	${OBJS} 
			${CC} ${CFLAGS}  ${OBJS}  -o ${NAME}

all	:	${NAME}

RM	=	rm -f

clean	:
		${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
