CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		cub3d.c libft/ft_split.c libft/ft_strncmp.c libft/ft_isspace.c libft/ft_atoi.c \
		libft/ft_isdigit.c libft/ft_strcmp.c check_colors.c check_textures.c

OBJS = $(SRCS:.c=.o)

NAME = cub3d

all :$(NAME)

$(NAME):$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean:clean
	@rm -f $(NAME)

re:fclean all

.PHONY: clean

