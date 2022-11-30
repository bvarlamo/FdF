# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 17:19:59 by bvarlamo          #+#    #+#              #
#    Updated: 2021/12/13 11:58:30 by bvarlamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FDF=	fdf.c get_next_line.c get_next_line_utils.c image.c read_map.c\

NAME	=	fdf

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

lib=./Libft

minilbx=./minilibx_macos

FRAMEWORKS	=		-framework OpenGL -framework AppKit

INCLUDES	=		libft/libft.a minilibx_macos/libmlx.a

FDFO=	$(FDF:.c=.o)

all :		$(NAME)

${NAME}:	${FDFO}
		make -C ${lib}
		make -C ${minilbx}
		${CC} ${CFLAGS} ${FDFO} $(INCLUDES) $(FRAMEWORKS) -o ${NAME}

clean :
	make clean -C ${lib}
	$(RM) ${FDFO}

fclean :	clean
	$(RM) $(NAME)
	$(RM) $(FDFO)
	make clean -C ${lib}
	make fclean -C ${lib}
	make clean -C ${minilbx}

re :		fclean all