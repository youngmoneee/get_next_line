/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 01:07:40 by youngpar          #+#    #+#             */
/*   Updated: 2021/07/03 19:24:37 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		idx;
	int		ss;

	idx = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ss = ft_strlen(s1);
	if (!(s3 = (char *)malloc(sizeof(char ) * (1 + ss + ft_strlen(s2)))))
		return ((void *)0);
	while (s1[idx])
	{
		s3[idx] = s1[idx];
		idx++;
	}
	while (*s2)
		s3[idx++] = *s2++;
	s3[idx] = 0;
	free(s1);
	return (s3);
}

static int	find_nl(char *buffer)
{
	int		idx;

	idx = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

static int	ret_front(char **buffer, char **line, int nl_idx)
{
	char	*tmp;
	int		idx;

	(*buffer)[nl_idx] = '\0';
	*line = ft_strdup(*buffer);
	idx = ft_strlen(*buffer + nl_idx + 1);
	if (!idx)
	{
		free(*buffer);
		*buffer = 0;
		return (1);
	}
	tmp = ft_strdup(*buffer + nl_idx + 1);
	free(*buffer);
	*buffer = tmp;
	return (1);
}

static int	ret_all(char **buffer, char **line, int read_bytes)
{
	int		nl_idx;

	if (read_bytes < 0)
		return (-1);
	if (*buffer && (nl_idx = find_nl(*buffer)) >= 0)
		return (ret_front(buffer, line, nl_idx));
	if (*buffer)
	{
		*line = *buffer;
		*buffer = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*buf_list[OPEN_MAX];
	char			*buffer;
	int				read_bytes;
	int				nl_idx;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line ||
			!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_bytes] = '\0';
		buf_list[fd] = ft_strjoin(buf_list[fd], buffer);
		if ((nl_idx = find_nl(buf_list[fd])) >= 0)
		{
			free(buffer);
			return (ret_front(&buf_list[fd], line, nl_idx));
		}
	}
	free(buffer);
	return (ret_all(&buf_list[fd], line, read_bytes));
}
