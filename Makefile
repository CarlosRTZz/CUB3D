# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/09 12:45:03 by dopeyrat          #+#    #+#              #
#    Updated: 2023/09/19 11:15:15 by dopeyrat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			free.c \
			INIT/args.c \
			INIT/check_map.c \
			INIT/init.c \
			INIT/map_id.c \
			INIT/remalloc.c \

OBJS	=	${SRCS:.c=.o}

NAME	= cub3D

LIBFT	= LIBFT/libft.a

MLX		= libmlx.a

MLXFLAGS	= -Lmlx -framework OpenGL -framework Appkit

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -O3 -O2 -Os -O1 #-fsanitize=address -g

all:	${NAME}

$(LIBFT):
	make -C LIBFT/

%.o:	%.c
	${CC} ${CFLAGS} -Imlx -c $< -o $@

${NAME}:	$(LIBFT) ${OBJS}
	make -C mlx
	cp mlx/libmlx.a ./
	${CC} ${CFLAGS} ${MLXFLAGS} -o ${NAME} ${LIBFT} ${OBJS} ${MLX}

clean:
	rm -rf ${OBJS}
	make -C LIBFT/ clean

fclean:	clean
	rm -rf ${NAME}
	rm -rf ${MLX}
	make -C LIBFT/ fclean
	make clean -C mlx

re:	fclean all

.PHONY:	re clean fclean all
