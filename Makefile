# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 21:06:58 by fsabatie          #+#    #+#              #
#    Updated: 2017/11/06 21:07:01 by fsabatie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Defining variables

NAME = fillit

SRC_PATH = srcs
INC_PATH = includes

SRC_NAME =	fill_it.c \
			checkers.c \
			tetri.c \
			map.c

LIB_NAME = libft.a
LIB_PATH = libft
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
LIB = $(addprefix $(INC_PATH)/,$(LIB_PATH))
LIBGCC = $(addprefix $(LIB)/,$(LIB_NAME))
CPPFLAGS = -Wall -Werror -Wextra

# Defining colors

RED = \033[1;31m
GREEN = \033[0;32m
ORANGE = \033[0;33m
BLUE = \033[1;36m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
NC = \033[0m

# Defining rules

all: $(NAME)

$(NAME):
	@echo "${GREEN}Compiling libft." | tr -d '\n'
	@cd $(LIB) && make re
	@echo " ${GREEN}Done."
	@cd ../..
	@echo "${GREEN}Compiling fillit." | tr -d '\n'
	@gcc $(CPPFLAGS) -I$(INC_PATH) -c $(SRC)
	@gcc $(CPPFLAGS) $(OBJ_NAME) $(LIBGCC) -o $(NAME)
	@echo " ${GREEN}Done."
	@echo "${RED}A ${ORANGE}w${YELLOW}i${GREEN}l${BLUE}d \
	${PURPLE}u${RED}n${ORANGE}i${YELLOW}c${GREEN}o${BLUE}r${PURPLE}n \
	${RED}a${ORANGE}p${YELLOW}p${GREEN}e${BLUE}a${PURPLE}r${RED}e${ORANGE}d \
	${YELLOW}a${GREEN}n${BLUE}d${PURPLE}.${RED}.${ORANGE}. \
	${YELLOW}O${GREEN}h ${BLUE}w${PURPLE}a${RED}i${ORANGE}t${YELLOW}, \
	${GREEN}i${BLUE}t ${PURPLE}j${RED}u${ORANGE}s${YELLOW}t ${GREEN}p\
	${BLUE}o${PURPLE}o${RED}p${ORANGE}e${YELLOW}d \
	${GREEN}a ${BLUE}f${PURPLE}i${RED}l${ORANGE}l${YELLOW}i${GREEN}t \
	${BLUE}f${PURPLE}i${RED}l${ORANGE}e ${YELLOW}!"

clean:
	@rm -rf $(OBJ_NAME)
	@cd $(LIB) && make clean
	@cd ../..

fclean: clean
	@rm -rf $(NAME)
	@cd $(LIB) && make fclean
	@cd ../..

re: fclean all
