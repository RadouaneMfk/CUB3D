NAME = cub3D

CC = cc

SRC = src/main.c

MLX = includes/MLX42/build/libmlx42.a

LFLAGS = -Imlx -lmlx -framework OpenGL -framework AppKit

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	
