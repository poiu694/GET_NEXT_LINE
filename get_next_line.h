/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <sangmlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 11:40:17 by sangmlee          #+#    #+#             */
/*   Updated: 2021/12/29 13:28:44 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
