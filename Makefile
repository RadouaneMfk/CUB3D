NAME = cub3D

SRC = src/intersections.c src/Draw_map.c src/main.c src/ft_player.c src/draw_utils.c \
	parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c \
		parsing/cub3d.c parsing/libft/ft_split.c parsing/libft/ft_strncmp.c parsing/libft/ft_isspace.c parsing/libft/ft_atoi.c \
		parsing/libft/ft_isdigit.c parsing/libft/ft_strcmp.c parsing/check_colors.c parsing/check_textures.c parsing/textures.c \
		parsing/check_textures1.c parsing/check_colors1.c parsing/count_utils.c parsing/utils_map.c parsing/utils_map1.c \
		parsing/utils.c src/ft_player_utils.c src/intersections_utils.c src/intersections_utils2.c parsing/free_textures.c \
		src/cleanup.c src/utils.c src/raycasting.c

CC = cc
CFLAGS = -Wall -Wextra -Werror 
MLX = -I $(HOME)/MLX42/include -L $(HOME)/MLX42/build -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit

LGLFW = -L $(HOME)/.brew/opt/glfw/lib -lglfw

OBJ = $(SRC:.c=.o)

LIBFT = lib/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(MLX) $(OBJ) $(LGLFW) $(LIBFT) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@make all -C src_bonus

clean:
	rm -f $(OBJ)
	make clean -C src_bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean