CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		cub3d.c ft_split.c

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

