# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:58:04 by rcastelo          #+#    #+#              #
#    Updated: 2023/11/13 15:58:18 by rcastelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

FILES = cam_movement.c clean_exit.c color.c commit_pixels.c fildefer.c ft_atoi.c ft_htoi.c isometric.c main.c obtain_coordinates.c orbit.c parallel.c prepare.c pressed_released.c render.c get_next_line.c get_next_line_utils.c

MLXFILES = mlx_clear_window.c mlx_destroy_display.c mlx_destroy_image.c mlx_destroy_window.c mlx_expose_hook.c mlx_ext_randr.c mlx_flush_event.c mlx_get_color_value.c mlx_get_data_addr.c mlx_hook.c mlx_init.c mlx_int_anti_resize_win.c mlx_int_do_nothing.c mlx_int_get_visual.c mlx_int_param_event.c mlx_int_set_win_event_mask.c mlx_int_str_to_wordtab.c mlx_int_wait_first_expose.c mlx_key_hook.c mlx_loop.c mlx_loop_hook.c mlx_mouse.c mlx_mouse_hook.c mlx_new_image.c mlx_new_window.c mlx_pixel_put.c mlx_put_image_to_window.c mlx_rgb.c mlx_screen_size.c mlx_set_font.c mlx_string_put.c mlx_xpm.c

SOURCES = $(addprefix sources/, $(FILES))

MLXSOURCES = $(addprefix mlx/, $(FILES))

OBJECTS = $(addprefix objects/, $(FILES:.c=.o))

MLXOBJECTS = $(addprefix mlxobjects/, $(MLXFILES:.c=.o))

all: $(NAME)

$(NAME): libmlx.a objects $(OBJECTS)
	cc $(CFLAGS) -lz -lm -lX11 -lXext $(OBJECTS) libmlx.a -o $(NAME)

mlxobjects/%.o: mlx/%.c | mlxobjects
	cc -w -c $< -o $@
	
libmlx.a: $(MLXOBJECTS)
	ar rcs libmlx.a $(MLXOBJECTS)
	
objects/%.o: sources/%.c | objects
	cc $(CFLAGS) -c $< -o $@

objects:
	mkdir objects
	
mlxobjects:
	mkdir mlxobjects
	
bonus: $(NAME)

clean:
	rm -fr objects mlxobjects libmlx.a

fclean: clean
	rm -f $(NAME)

re: fclean all
