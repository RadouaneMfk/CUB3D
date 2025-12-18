NAME = ../cub3D

SRC = intersections_bonus.c Draw_map_bonus.c main_bonus.c ft_player_bonus.c draw_utils_bonus.c \
	../parsing/get_next_line/get_next_line.c ../parsing/get_next_line/get_next_line_utils.c \
		../parsing/cub3d.c ../parsing/libft/ft_split.c ../parsing/libft/ft_strncmp.c ../parsing/libft/ft_isspace.c ../parsing/libft/ft_atoi.c \
		../parsing/libft/ft_isdigit.c ../parsing/libft/ft_strcmp.c ../parsing/check_colors.c ../parsing/check_textures.c ../parsing/textures.c \
		../parsing/check_textures1.c ../parsing/check_colors1.c ../parsing/count_utils.c ../parsing/utils_map.c ../parsing/utils_map1.c \
		utils_bonus.c ft_player_utils_bonus.c intersections_utils_bonus.c intersections_utils2_bonus.c ../parsing/free_textures.c \
		cleanup_bonus.c raycasting_bonus.c ../parsing/utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -I ../includes/MLX42/include -L ../includes/MLX42/build -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit

LGLFW = -L $(HOME)/.brew/opt/glfw/lib -lglfw

OBJ = $(SRC:.c=.o)

LIBFT = ../lib/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(MLX) $(OBJ) $(LGLFW) $(LIBFT) -o $(NAME)

%.o: %.c ../includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
