/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <sangmlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:36:18 by sangmlee          #+#    #+#             */
/*   Updated: 2021/12/23 12:56:50 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	detect_init_error(int fd)
{
	return (fd < 0 || fd >= 13000 || BUFFER_SIZE < 1);
}

char	*process_new_read_line(int fd, char **cache_storage)
{
	char	*read_buf;
	ssize_t	read_size;

	while (1)
	{
		read_size = read(fd, read_buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(read_buf);
			free(cache_storage);
			cache_storage = NULL;
			return (NULL);
		}
		read_buf[read_size] = '\0';
		cache_storage[fd] = ft_strjoin(cache_storage[fd], read_buf);
	}
	return (read_buf);
}

char	*get_next_line(int fd)
{
	int			error;
	char		*read_buf;
	static char	*cache_storage[13000];

	if (detect_init_error(fd))
		return (NULL);
	read_buf = NULL;
	if (cache_storage[fd])
		cache_storage[fd] = ft_strdup("");
	if (cache_storage[fd])
		read_buf = process_existing_line(fd, &cache_storage);
	if (read_buf == NULL)
		read_buf = process_new_read_line(fd, read_buf, &cache_storage);
	return (read_buf);
}
