

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strdup1(char *s1);
char	*ft_strjoin1(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_strchr1(char *s, int c);
char	*read_buffer(char *res, int fd);

#endif