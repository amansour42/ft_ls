# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/01 12:36:18 by amansour          #+#    #+#              #
#    Updated: 2017/12/05 13:53:13 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprint.a

FLAGS = -Wall -Wextra -Werror
SRCLIBPATH = ./srclib
SRCPATH = ./src
OBJLIBPATH = ./objlib
OBJPATH = ./obj

SRCLIB_NAME = ft_isdigit.c ft_strlen.c\
	ft_strdup.c\
	convert_unicode.c\
	ft_wstrlen.c ft_strncpy.c\

SRC_NAME = ft_printf.c conversion.c test.c util.c nbr_to_string.c\
	to_n.c to_p.c to_bigc.c to_bigs.c to_string.c display.c\
	to_sign_decimal.c to_decimal.c format.c\

INCLUDS = includes/ft_printf.h

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(SRCLIB_NAME:.c=.o)
SRC = $(addprefix $(SRCPATH)/, $(SRC_NAME))
LIB = $(addprefix $(SRCLIBPATH)/, $(SRCLIB_NAME))
OBJ = $(addprefix $(OBJPATH)/,$(OBJ_NAME))
OBJLIB = $(addprefix $(OBJLIBPATH)/,$(OBJLIB_NAME))

all: $(NAME)

$(NAME) : $(OBJ) $(OBJLIB)
	@ar rc $(NAME) $(OBJ) $(OBJLIB)
	@ranlib $(NAME)
	@echo "\033[1;7;34mFT_PRINTF\t\033[1;7;33mCOMPILATION\t\033[0m👌 "

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	@mkdir $(OBJPATH) 2> /dev/null || true
	@gcc $(FLAGS) -o $@ -c $< -I $(INCLUDS)

$(OBJLIBPATH)/%.o: $(SRCLIBPATH)/%.c
	@mkdir $(OBJLIBPATH) 2> /dev/null || true
	@gcc $(FLAGS) -o $@ -c $< -I $(INCLUDS)

clean:
	@rm -rf $(OBJPATH) $(OBJLIBPATH)
	@echo "\033[1;7;34mFT_PRINTF\t\033[1;7;33mCLEANING\t\033[0m👌 "

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;7;34mFT_PRINTF\t\033[1;7;33mFCLEANING\t\033[0m👌 "
re: fclean all

norme: 
	@norminette $(SRC) $(LIB) $(INCLUDS)
	@echo "\033[1;34mft_printf\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"
