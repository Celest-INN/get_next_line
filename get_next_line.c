/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:02:29 by erzhuo            #+#    #+#             */
/*   Updated: 2026/01/09 22:13:55 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

static char	*read_and_stash(int fd, char *stash)
{
    char	*buf;
	ssize_t	r;

	buf = malloc (BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	r = 1; 
	while (!ft_strchr(stash, '\n') && r > 0)
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r < 0)	
			return (free(buf), free(stash), NULL);
		buf[r] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (free(buf), NULL);
	}
}

static char	*get_line(char *stash)
{
	size_t	i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}
//r = 实际读到的字节数

//在第 r 个位置 放一个字符串结束符