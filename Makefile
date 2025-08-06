# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: musajid <musajid@hive.student.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/06 12:49:09 by musajid           #+#    #+#              #
#    Updated: 2025/08/06 20:08:11 by musajid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

# Directories
SRCS = src/pipex.c

# libft
LIBFTDIR = libft
LIBFTNAME = $(LIBFTDIR)/libft.a


#
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFTNAME):
		$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJ) $(LIBFTNAME)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFTNAME) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

.SECONDARY: $(OBJ)

clean:
		$(MAKE) clean -C $(LIBFTDIR)
		rm -f $(OBJ)

fclean:
		$(MAKE) fclean -C $(LIBFTDIR)
		rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re
