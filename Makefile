# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrocca <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 16:49:45 by lrocca            #+#    #+#              #
#    Updated: 2021/03/28 23:21:44 by lrocca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinc -I/Library/Frameworks/SDL2.framework/Headers -g
OBJDIR		=	./obj
SRCDIR		=	./src
LIBDIR		=	./lib
FILES		=	main.c \
				input/gnl.c input/parsing.c input/check.c \
				mlx/mlx.c mlx/move.c mlx/rotate.c render/floor.c render/life.c \
				render/walls.c render/sprites.c render/minimap.c render/bmp.c \
				utils/global.c utils/check.c utils/color.c utils/render.c \
				utils/parsing.c utils/mlx.c
				# test_scenes.c
SRC			=	$(addprefix $(SRCDIR)/,$(FILES))
OBJ			= 	$(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRC:.c=.o))
LIB			=	$(LIBFT) ./libmlx.dylib $(LIBDIR)/mlx_opengl/libmlx.a $(LIBDIR)/simple-sdl2-audio/audio.o
LIBFTDIR	=	$(LIBDIR)/libft
LIBFT		=	$(LIBFTDIR)/libft.a
DYLIB		=	$(LIBDIR)/mlx_mms/libmlx.dylib

all: $(NAME)
# @osascript -e 'display notification "Program is ready" with title "cub3D"'

$(NAME): libraries $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -framework OpenGL -framework AppKit -F/Library/Frameworks -framework SDL2 $(OBJ) $(LIB) -o $@
	@printf "%-80.80b\n" "\e[1;32m•\e[0m Compiling \033[1m$@\033[0m... done"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@
	@printf "%-80.80b\r" "○ Compiling \033[1m$(NAME)\033[0m... $^"

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	@mkdir $(OBJDIR)

$(LIBFT):
	@make -C $(LIBFTDIR)

libraries:
	@printf "Making mlx_mms..." && make -C $(LIBDIR)/mlx_mms &> /dev/null && echo " done"
	@printf "Making mlx_opengl..." && make -C $(LIBDIR)/mlx_opengl &> /dev/null && echo " done"
	@printf "Making simple-sdl2-audio..." && $(CC) $(CFLAGS) -c $(LIBDIR)/simple-sdl2-audio/audio.c -o $(LIBDIR)/simple-sdl2-audio/audio.o && echo " done"
	@cp $(DYLIB) ./

test: all
	./cub3D maps/test.cub

clean:
	@rm -f $(OBJ) ./lib/simple-sdl2-audio/audio.o
	@printf "%-80.80b\n" "\e[1;31m•\e[0m Deleted objects for \033[1m$(NAME)\033[0m"
# @rm -r $(OBJDIR)
	@make clean -C $(LIBFTDIR)
	@make clean -C $(LIBDIR)/mlx_mms
	@make clean -C $(LIBDIR)/mlx_opengl

fclean: clean
	@rm -f $(NAME) ./libmlx.dylib ./save.bmp
	@printf "%-80.80b\n" "\e[1;31m•\e[0m Deleted target for \033[1m$(NAME)\033[0m"
	@make fclean -C $(LIBFTDIR)

re: fclean all

bonus: re

.PHONY: all bonus clean fclean re
