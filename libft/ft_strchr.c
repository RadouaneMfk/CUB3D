/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:18:00 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/22 10:18:17 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char) c == s[i])
			return ((char *)(&s[i]));
		i++;
	}
	if ((char )c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}
