NAME = cub3D

SRC = src/intersections.c src/Draw_map.c src/ft_player.c src/rayCasting.c src/draw_utils.c

CC = cc


# CFLAGS = -Wall -Wextra -Werror
MLX = -I includes/MLX42/include -L includes/MLX42/build -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit

LGLFW = -L /Users/rmouafik/.brew/opt/glfw/lib -lglfw 

OBJ = $(SRC:.c=.o)

LIBFT = lib/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(MLX) $(OBJ) $(LGLFW) $(LIBFT) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) -c $< -o $@

# bonus:
# 	@make all -C src_bonus

clean:
	rm -f $(OBJ)
# make clean -C src_bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean