# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/01 12:36:18 by amansour          #+#    #+#              #
#    Updated: 2017/12/05 13:56:52 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
	ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
	ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
	ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
	ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
	ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
	ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
	ft_strtrim.c ft_tolower.c ft_toupper.c ft_swap.c ft_max.c\
	get_next_line.c ft_lstdel2.c belong.c ft_convert_base.c\

INCLUDS = libft.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) :
	@gcc $(FLAGS) -c $(SRC) -I $(INCLUDS)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[1;7;34mLIBFT\t\t\033[1;7;33mCOMPILATION\t\033[0m👌 "
clean:
	@rm -rf $(OBJ)
	@echo "\033[1;7;34mLIBFT\t\t\033[1;7;33mCLEANING\t\033[0m👌 "

fclean: clean
		@rm -f $(NAME)
	@echo "\033[1;7;34mLIBFT\t\t\033[1;7;33mFCLEANING\t\033[0m👌 "

re: fclean all
