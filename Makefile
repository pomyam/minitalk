# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 10:50:28 by pyamcha           #+#    #+#              #
#    Updated: 2021/07/27 10:50:29 by pyamcha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SER = server
CLI = client
BON_SERVER = servеr 
BON_CLIENT = cliеnt 

HEADER = main/minitalk.h
BON_HEADER = bonus/minitalk.h

DOP_SRCS = main/dop.c
CLI_SRCS = main/client.c
SER_SRCS = main/server.c
BONUS_DOP = bonus/dop.c
BONUS_SER = bonus/server.c
BONUS_CLI = bonus/client.c

CLI_OBJS = ${CLI_SRCS:.c=.o}
SER_OBJS = ${SER_SRCS:.c=.o}
DOP_OBJS = ${DOP_SRCS:.c=.o}
BON_CLI = ${BONUS_CLI:.c=.o}
BON_SER = ${BONUS_SER:.c=.o}
BON_DOP = ${BONUS_DOP:.c=.o}

FLAGS = -Wall -Werror -Wextra

all: ${SER} ${CLI}

${SER}: ${SER_OBJS} ${DOP_OBJS} ${HEADER}
	@gcc ${FLAGS} ${DOP_OBJS} ${SER_OBJS} -I ${HEADER} -o ${SER}

${CLI}: ${CLI_OBJS} ${DOP_OBJS} ${HEADER}
	@gcc ${FLAGS} ${DOP_OBJS} ${CLI_OBJS} -I ${HEADER} -o ${CLI}

clean:
	rm -f ${SER_OBJS} ${CLI_OBJS} ${DOP_OBJS}
	rm -f ${BON_SER} ${BON_CLI} ${BON_DOP}

fclean: clean
	rm -f ${SER} ${CLI}
	rm -f ${BON_SERVER} ${BON_CLIENT}

re: fclean all

bonus: fclean ${BON_SERVER} ${BON_CLIENT}

${BON_SERVER}: ${BON_SER} ${BON_DOP} ${BON_HEADER} 
	@gcc ${FLAGS} ${BON_DOP} ${BON_SER} -I ${BON_HEADER} -o ${BON_SERVER}

${BON_CLIENT}: ${BON_CLI} ${BON_DOP} ${BON_HEADER}
	@gcc ${FLAGS} ${BON_DOP} ${BON_CLI} -I ${BON_HEADER} -o ${BON_CLIENT}

.PHONY: all clean fclean re bonus