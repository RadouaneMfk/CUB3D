/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:11:50 by haboucha          #+#    #+#             */
/*   Updated: 2025/12/21 13:11:51 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(char *res, int fd)
{
	int		nbr;
	char	*buffer;
	char	*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(res), NULL);
	nbr = 1;
	while (nbr > 0)
	{
		nbr = read(fd, buffer, BUFFER_SIZE);
		if (nbr < 0)
			return (free(buffer), free(res), NULL);
		buffer[nbr] = '\0';
		if (res == NULL)
			res = ft_strdup1("");
		if (!res)
			return (free(buffer), NULL);
		tmp = res;
		res = ft_strjoin1(res, buffer);
		free(tmp);
		if (nbr == 0 || ft_strchr1(buffer, '\n'))
			break ;
	}
	return (free(buffer), res);
}

char	*cpy_buffer(char *res)
{
	char	*cpy;
	int		i;

	if (!res || res[0] == '\0')
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\n')
		i++;
	cpy = malloc((i + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
	{
		cpy[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
		cpy[i++] = '\n';
	cpy[i] = '\0';
	return (cpy);
}

char	*after_newline(char *res)
{
	char	*n_line;
	int		i;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\0')
		return (free(res), NULL);
	n_line = ft_strdup1(&res[i + 1]);
	if (!n_line)
	{
		free(res);
		return (NULL);
	}
	free(res);
	return (n_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(res), res = NULL, NULL);
	res = read_buffer(res, fd);
	if (!res)
		return (NULL);
	line = cpy_buffer(res);
	if (!line)
		return (free(res), res = NULL, NULL);
	res = after_newline(res);
	return (line);
}
