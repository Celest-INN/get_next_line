/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erzhuo <erzhuo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:02:29 by erzhuo            #+#    #+#             */
/*   Updated: 2026/01/11 18:23:51 by erzhuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  read_and_stash
//  stash 里现在有：
// 	一整行 + 可能的“下一行残余”
// 	或者最后一行（没有 \n）
// 
// 	r = 实际读到的字节数
//  buf[r] = '\0';在第 r 个位置 放一个字符串结束符
//  r > 0, 读到了 r 字节
//	r = 0, EOF
//	r = -1, error

#include "get_next_line.h"
#include <stddef.h>

char	*read_and_stash(int fd, char *stash)
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
	free (buf);
	return (stash);
}

char	*get_line_before_seperator(char *stash)
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

char	*free_stash(char *stash, unsigned int i, size_t len)
{
	char	*nouveau_stash;

	nouveau_stash = ft_substr(stash, i, len);
	free (stash);
	return (nouveau_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash; // stash au debut est null
	char		*line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash && stash[0] == '\0') // si stash est null, on peut pas faire stash[0]
	{
		return (free(stash), stash = NULL, NULL);
	}
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line_before_seperator(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	stash = free_stash(stash, i, ft_strlen(stash + i));
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <file>\n", argv[0]);
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	//line = get_next_line(fd);
// 	//free (line);
// 	close(fd);
// 	return (0);
// }

// get_line: 从 stash 里“切”出第一行，作为返回值。
// // verification??

// get_next_line 中， stash + i 不是“加法”，而是：指针向后移动 i 个字符
// a static variable retains their value between multiple function calls.

// si on free stash, stash n'est pas forcement null
// mais si stash est null, on n'a plus besoin de free

// test de leak != test de malloc
// test de leak : voir si tu free tous les malloc
// test de malloc : quand le malloc fail, est-ce que le programme crash (il devrait pas crasher... il doit simplement exit) et si le programme a du leak (il devrait pas en avoir)