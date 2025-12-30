NAME = ../cub3D

SRC = intersections_bonus.c Draw_map_bonus.c main_bonus.c ft_player_bonus.c draw_utils_bonus.c \
	../parsing_bonus/get_next_line/get_next_line.c ../parsing_bonus/get_next_line/get_next_line_utils.c \
		../parsing_bonus/cub3d.c ../parsing_bonus/libft/ft_split.c ../parsing_bonus/libft/ft_strncmp.c ../parsing_bonus/libft/ft_isspace.c ../parsing_bonus/libft/ft_atoi.c \
		../parsing_bonus/libft/ft_isdigit.c ../parsing_bonus/libft/ft_strcmp.c ../parsing_bonus/check_colors.c ../parsing_bonus/check_textures.c ../parsing_bonus/textures.c \
		../parsing_bonus/check_textures1.c ../parsing_bonus/check_colors1.c ../parsing_bonus/count_utils.c ../parsing_bonus/utils_map.c ../parsing_bonus/utils_map1.c \
		utils_bonus.c ft_player_utils_bonus.c intersections_utils_bonus.c intersections_utils2_bonus.c ../parsing_bonus/free_textures.c \
		cleanup_bonus.c raycasting_bonus.c ../parsing_bonus/utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -I $(HOME)/MLX42/include -L $(HOME)/MLX42/build -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit

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
