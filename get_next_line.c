/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <sangmlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:36:18 by sangmlee          #+#    #+#             */
/*   Updated: 2021/12/29 13:28:07 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_new_line(int fd, char **cache_storage)
{
	char	*read_buf;
	ssize_t	read_size;

	while (1)
	{
		read_size = read(fd, read_buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(read_buf);
			cache_storage = NULL;
			return (NULL);
		}
		read_buf[read_size] = '\0';
		cache_storage[fd] = ft_strjoin(cache_storage[fd], read_buf);
	}
	return (cache_storage[fd]);
}

static char	*find_newline_index(char *buf)
{
	while (*buf != '\0' && *buf != '\n')
		buf++;
	return (buf);
}

static char	*ft_get_line_before_newline(char *buf)
{
	char	*line;
	char	*newline_index;

	newline_index = find_newline(buf);
	if (*buf == '\0' || *newline_index == '\0')
		return (NULL);
	line = malloc(sizeof(char) * (newline_index - buf + 1));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, buf, newline_index - buf + 1);
	return (line);
}

static char	*ft_update_cache(char *buf)
{
	char	*line;
	char	*newline_index;

	newline_index = find_newline(buf);
	if (newline_index == '\0')
	{
		free(buf);
		return (NULL);
	}
	line = ft_strdup(newline_index + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	int			error;
	char		*read_buf;
	static char	*cache_storage[13000];

	if (fd < 0 || fd >= 13000 || BUFFER_SIZE < 1)
		return (NULL);
	read_buf = NULL;
	if (cache_storage[fd] == NULL)
		cache_storage[fd] = ft_strdup("");
	read_buf = ft_read_new_line(fd, &cache_storage[fd]);
	if (read_buf)
	{
		read_buf = ft_get_line_before_newline(read_buf);
		if (read_buf)
			cache_storage[fd] = ft_update_cache(cache_storage[fd]);
	}
	return (read_buf);
}
