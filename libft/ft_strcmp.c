/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:11:05 by haboucha          #+#    #+#             */
/*   Updated: 2025/10/29 12:53:17 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strcmp(char *s1,char *s2)
{
    int i = 0;
    if(!s1 && !s2 )
        return 0;
    if(!s1)
        return -1;
    if(!s2)
        return 1;
    while(s1[i] && s2[i])
    {
        if(s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i]- s2[i]);
}