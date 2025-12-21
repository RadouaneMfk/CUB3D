/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:11:56 by haboucha          #+#    #+#             */
/*   Updated: 2025/12/21 13:11:57 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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