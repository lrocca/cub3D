NAME		=	cub3D
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
FILES		=	cub3D.c gnl.c parsing.c check.c mlx.c render.c \
				utils.c utils_check.c utils_color.c utils_render.c \
				test_scenes.c
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
	@$(CC) $(CFLAGS) -Imlx_mms -Imlx_opengl -c $^ -o $@
	@printf "%-80.80b\r" "○ Compiling \033[1m$(NAME)\033[0m... $^"

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

mlx: $(DYLIB)
	@make -C ./mlx_mms
	@make -C ./mlx_opengl
	cp $^ ./

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
