NAME		=	cub3D
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
FILES		=	cub3D.c \
				input/gnl.c input/parsing.c input/check.c \
				mlx/mlx.c mlx/move.c mlx/rotate.c \
				render/walls.c render/sprites.c \
				utils/global.c utils/check.c utils/color.c utils/render.c
				# test_scenes.c
SRC			=	$(addprefix $(SRCDIR)/,$(FILES))
OBJ			= 	$(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRC:.c=.o))
OBJDIR		=	./obj
SRCDIR		=	./src
LIBFT		=	$(LIBFTDIR)/libft.a
LIBFTDIR	=	./libft
DYLIB		=	./mlx_mms/libmlx.dylib

all: mlx $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $^ $(LIBFT) ./libmlx.dylib -o $@
	@printf "%-80.80b\n" "\e[1;32m•\e[0m Compiling \033[1m$@\033[0m... done"

$(LIBFT):
	@make -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Imlx_mms -Imlx_opengl -Iinc -c $^ -o $@
	@printf "%-80.80b\r" "○ Compiling \033[1m$(NAME)\033[0m... $^"

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

mlx:
	@make -C ./mlx_mms
	@make -C ./mlx_opengl
	@cp $(DYLIB) ./

test: all
	./cub3D maps/test.cub

clean:
	@rm -f $(OBJ)
	@printf "%-80.80b\n" "\e[1;31m•\e[0m Deleted objects for \033[1m$(NAME)\033[0m"
#	rm -r $(OBJDIR)
	@make clean -C $(LIBFTDIR)
	@make clean -C ./mlx_mms
	@make clean -C ./mlx_opengl

fclean: clean
	@rm -f $(NAME) libmlx.dylib
	@printf "%-80.80b\n" "\e[1;31m•\e[0m Deleted archive for \033[1m$(NAME)\033[0m"
	@make fclean -C $(LIBFTDIR)

re: fclean all

bonus: re

.PHONY: all bonus clean fclean re
