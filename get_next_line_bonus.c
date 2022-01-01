/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <sangmlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:36:18 by sangmlee          #+#    #+#             */
/*   Updated: 2022/01/01 19:53:52 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_new_line(int fd, char *cache)
{
	char	*read_buf;
	char	*temp;
	ssize_t	read_size;

	read_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buf == NULL)
		return (NULL);
	read_size = read(fd, read_buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		read_buf[read_size] = '\0';
		temp = cache;
		cache = ft_strjoin(cache, read_buf);
		free(temp);
		if (*find_newline_index(cache) == '\n')
			break ;
		read_size = read(fd, read_buf, BUFFER_SIZE);
	}
	free(read_buf);
	if (read_size < 0)
		return (NULL);
	return (cache);
}

static char	*ft_get_line_before_newline(char *buf)
{
	char	*line;
	char	*newline_index;

	if (*buf == '\0')
		return (NULL);
	newline_index = find_newline_index(buf);
	if (*newline_index == '\0')
		return (ft_strdup(buf));
	line = malloc(sizeof(char) * (newline_index - buf + 2));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, buf, newline_index - buf + 2);
	return (line);
}

static char	*ft_update_cache(char *cache)
{
	char	*line;
	char	*newline_index;

	newline_index = find_newline_index(cache);
	if (*newline_index == '\0')
	{
		free(cache);
		return (NULL);
	}
	line = ft_strdup(newline_index + 1);
	free(cache);
	return (line);
}

static t_node	*find_node_with_fd(t_node *head, int fd)
{
	t_node	*node;
	t_node	*node_before;

	node_before = head;
	node = head->next;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node_before = node;
		node = node->next;
	}
	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->cache = NULL;
	node->next = NULL;
	node_before->next = node;
	return (node);
}

char	*get_next_line(int fd)
{
	char			*line;
	t_node			*node_before;
	t_node			*node;
	static t_node	head;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	node = find_node_with_fd(&head, fd);
	if (node == NULL)
		return (NULL);
	node_before = head.next;
	while (node_before && node_before->next != node)
		node_before = node_before->next;
	node->cache = ft_read_new_line(fd, node->cache);
	if (node->cache == NULL)
	{
		node_before->next = NULL;
		free(node);
		return (NULL);
	}
	line = ft_get_line_before_newline(node->cache);
	if (line == NULL)
	{
		node_before->next = NULL;
		free(node);
		return (NULL);
	}
	node->cache = ft_update_cache(node->cache);
	return (line);
}
