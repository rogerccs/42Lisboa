# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 14:04:37 by rcastelo          #+#    #+#              #
#    Updated: 2023/12/28 14:04:39 by rcastelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror

FILES = clean_exit.c main.c task_management.c parsing.c run_commands.c
LIBFTFILES = ft_split.c ft_strjoin.c ft_strjoinjoin.c ft_strncmp.c get_next_line.c get_next_line_utils.c quote_split.c 

SOURCES = $(addprefix sources/, $(FILES))
LIBFTSOURCES = $(addprefix sources/sources_libft/, $(LIBFTFILES))
BONUSSOURCES = $(addprefix sources/sources_bonus/, $(FILES:.c=_bonus.c)) sources/sources_bonus/infile_bonus.c 

OBJECTS = $(addprefix objects/, $(FILES:.c=.o))
LIBFTOBJECTS = $(addprefix objects/, $(LIBFTFILES:.c=.o))
BONUSOBJECTS = $(addprefix objects/, $(FILES:.c=_bonus.o)) objects/infile_bonus.o

all: $(NAME)

$(NAME): libft.a $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) libft.a -o $(NAME)

objects/%.o: sources/sources_libft/%.c | objects
	cc $(CFLAGS) -w -c $< -o $@

libft.a: $(LIBFTOBJECTS)
	ar rcs libft.a $(LIBFTOBJECTS)

objects/%.o: sources/%.c | objects
	cc $(CFLAGS) -c $< -o $@

bonus: pipex_bonus

pipex_bonus: libft.a $(BONUSOBJECTS)
	cc $(CFLAGS) $(BONUSOBJECTS) libft.a -o pipex_bonus

objects/%.o: sources/sources_bonus/%.c | objects
	cc $(CFLAGS) -c $< -o $@

objects:
	mkdir objects

clean:
	rm -fr objects libft.a

fclean: clean
	rm -f pipex pipex_bonus

re: fclean all
