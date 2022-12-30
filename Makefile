# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 13:14:42 by ahammoud          #+#    #+#              #
#    Updated: 2022/12/30 17:15:40 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./src/utils.c ./src/lexer.c ./src/main.c ./src/expander.c ./src/executor.c

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/

NAME	=	 executor

#CFLAGS	=	 -Wall -Wextra -Werror -lreadline
CFLAGS	=	 -lreadline -g -fsanitize=address
#CFLAGS	=	 -lreadline 


CC	=	gcc


${NAME}	:	${OBJS} 
			cd ./src/libft/ && make bonus
			${CC} ${CFLAGS} ${OBJS} ./src/libft/libft.a -o ${NAME}

all	:	${NAME}

RM	=	rm -f

clean	:
		${MAKE} clean -C ./src/libft
		${RM} ${OBJS}

fclean	:	clean

			${MAKE} fclean -C ./src/libft
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re
