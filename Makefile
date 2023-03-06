# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 13:14:42 by ahammoud          #+#    #+#              #
#    Updated: 2023/03/06 16:52:16 by ahammoud         ###   ########.fr        #
#    Updated: 2023/02/16 19:05:10 by jvelasco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./src/find_replace.c ./src/checkers2.c ./src/signals.c ./src/trim.c ./src/builtins2.c ./src/executor2.c ./src/env2.c ./src/builtins.c ./src/ft_split_delete.c ./src/env.c ./src/fd.c ./src/free.c ./src/utils.c ./src/lexer.c ./src/main.c ./src/expander.c ./src/executor.c ./src/checkers.c ./src/split_parse.c ./src/search.c ./src/lexer_utils.c ./src/init_structs.c ./src/tokens.c ./src/split_utils.c ./src/parser_utils.c ./src/split_parse_utils.c

OBJS	=	${SRCS:.c=.o}

.c.o	:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I includes/ -I /Users/${USER}/.brew/opt/readline/include

NAME	=	 minishell

LIB		=		 -lreadline -L /Users/${USER}/.brew/opt/readline/lib/
#LIB		=	 -lreadline -L /usr/local/Cellar/readline/8.1/lib/ -I /usr/local/Cellar/readline/8.1/include/readline/

#CFLAGS	=	 -g
CFLAGS	=	 -g -Wall -Wextra -Werror
#CFLAGS	=	 -g -fsanitize=address


CC	=	gcc


${NAME}	:	${OBJS} 
			cd ./src/libft/ && make bonus
			${CC} ${CFLAGS} ${OBJS} ./src/libft/libft.a -o ${NAME} ${LIB} -I includes/ -I /Users/${USER}/.brew/opt/readline/include

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
