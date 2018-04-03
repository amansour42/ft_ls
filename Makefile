# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/30 10:19:33 by amansour          #+#    #+#              #
#    Updated: 2018/01/26 15:51:38 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LDFLAGS_LIB = -L libft
LDLIBS = -lft
LDFLAGS_PRINTF = -L libprint
LDLIBSPRINTF = -lprint
FLAGS = -Werror -Wall -Wextra
SRC_PATH = ./srcs
OBJ_PATH = ./obj
INCLUD  = ./includes
LIB = libft/libft.a
LIBPRINTF = libprint/libprint.a

SRC = ft_ls.c print_list.c list.c main.c sorting.c\
		 long_format_listing.c print_blocks_1.c reverse_flag.c time_flag.c error.c print_blocks_2.c\

OBJ = $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIB) $(LIBPRINTF) $(OBJ)
	@gcc $(OBJ) $(LDFLAGS_LIB) $(LDLIBS) $(LDFLAGS_PRINTF) $(LDLIBSPRINTF) -o $(NAME)
	@echo "\033[1;7;34mFT_LS\t\t\033[1;7;33mCOMPILATION\t\033[0m👌"

$(LIB):
	@make -C libft

$(LIBPRINTF):
	@make -C libprint

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -I $(INCLUD) -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;7;34mFT_LS\t\t\033[1;7;33mCLEANING\t\033[0m👌"
	@make -C libft clean
	@make -C libprint clean

fclean: clean
	@echo "\033[1;7;34mFT_LS\t\t\033[1;7;33mFCLEANING\t\033[0m👌"
	@rm -f $(NAME) $(LIB) $(LIBPRINTF)
re: fclean all
