/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:02:23 by erzhuo            #+#    #+#             */
/*   Updated: 2026/01/05 22:05:33 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(char *s)
{
    size_t  i;

    i = 0;
    if (!s)
        return(0);
    while (s[i])
        i++;
    return (i);
}

char    *ft_strchr(char *s, int c)
{
    
}