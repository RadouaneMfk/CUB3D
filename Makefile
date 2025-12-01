NAME = cub3D

SRC = src/intersections.c src/Draw_map.c src/rayCasting.c src/ft_player.c src/draw_utils.c \
	parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c \
		parsing/cub3d.c parsing/libft/ft_split.c parsing/libft/ft_strncmp.c parsing/libft/ft_isspace.c parsing/libft/ft_atoi.c \
		parsing/libft/ft_isdigit.c parsing/libft/ft_strcmp.c parsing/check_colors.c parsing/check_textures.c parsing/textures.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I /Users/haboucha/.brew/MLX42/include #-fsanitize=address -g

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


# --------------------------------


# NAME = cub3D

# SRC = src/intersections.c src/Draw_map.c src/rayCasting.c src/ft_player.c src/draw_utils.c \
# 	parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c \
# 		parsing/cub3d.c parsing/libft/ft_split.c parsing/libft/ft_strncmp.c parsing/libft/ft_isspace.c parsing/libft/ft_atoi.c \
# 		parsing/libft/ft_isdigit.c parsing/libft/ft_strcmp.c parsing/check_colors.c parsing/check_textures.c

# CC = cc
# # CFLAGS = -Wall -Wextra -Werror
# MLX = -I includes/MLX42/include -L includes/MLX42/build -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit

# LGLFW = -L /Users/rmouafik/.brew/opt/glfw/lib -lglfw 

# OBJ = $(SRC:.c=.o)

# LIBFT = lib/libft.a

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(MLX) $(OBJ) $(LGLFW) $(LIBFT) -o $(NAME)

# %.o: %.c includes/cub3d.h
# 	$(CC) -c $< -o $@

# # bonus:
# # 	@make all -C src_bonus

# clean:
# 	rm -f $(OBJ)
# # make clean -C src_bonus

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: clean