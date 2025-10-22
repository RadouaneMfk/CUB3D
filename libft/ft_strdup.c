/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:29:11 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/22 10:29:28 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		n;
	int		i;

	p = (char *)s1;
	n = ft_strlen(s1) + 1;
	i = 0;
	p = (char *)malloc(n * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = (char)s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
