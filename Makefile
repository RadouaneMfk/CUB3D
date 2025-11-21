NAME = cub3D

SRC = src/intersections.c src/Draw_map.c src/ft_player.c src/rayCasting.c src/draw_utils.c
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I /Users/haboucha/.brew/MLX42/include

# Librairies
MLX_LIB   = -L /Users/haboucha/.brew/MLX42/build -lmlx42
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

# GLFW
GLFW_PREFIX = $(shell brew --prefix glfw)
GLFW_LIB    = -L $(GLFW_PREFIX)/lib -lglfw
GLFW_INC    = -I $(GLFW_PREFIX)/include

# Libft
LIBFT = lib/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(FRAMEWORKS) $(GLFW_LIB) $(LIBFT) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
