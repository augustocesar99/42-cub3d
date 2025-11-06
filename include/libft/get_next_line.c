/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:55:23 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/11/06 16:22:59 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_and_stored(int fd, char *stored)
{
	char	*buf;
	ssize_t	bytes_read;
	size_t	i;

	i = 0;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (i < ((BUFFER_SIZE + 1) * sizeof(char)))
		((unsigned char *)buf)[i++] = 0;
	bytes_read = 1;
	while (bytes_read > 0 && (ft_strchr(buf, '\n') == NULL || stored == NULL))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(stored);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stored = get_line(stored, buf);
	}
	free(buf);
	return (stored);
}

static size_t	line_size(char *str)
{
	size_t	line_len;

	line_len = 0;
	while (str[line_len] && str[line_len] != '\n')
		line_len++;
	if (str[line_len] == '\n')
		line_len++;
	return (line_len);
}

static char	**get_stored_array(void)
{
	static char	*stored[1024];

	return (stored);
}

char	*get_next_line(int fd)
{
	char		**stored;
	char		*line;
	char		*temp;
	size_t		line_len;
	size_t		substr_len;

	stored = get_stored_array();
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stored[fd] = read_and_stored(fd, stored[fd]);
	if (stored[fd] == NULL || *stored[fd] == '\0')
	{
		free(stored[fd]);
		stored[fd] = NULL;
		return (NULL);
	}
	line_len = line_size(stored[fd]);
	line = ft_substr(stored[fd], 0, line_len);
	temp = stored[fd];
	substr_len = ft_strlen(stored[fd]) - line_len;
	stored[fd] = ft_substr(stored[fd], line_len, substr_len);
	free(temp);
	return (line);
}

void	gnl_clear_all_fds(void)
{
	char	**stored;
	int		fd;

	stored = get_stored_array();
	fd = 0;
	while (fd < 1024)
	{
		if (stored[fd])
		{
			free(stored[fd]);
			stored[fd] = NULL;
		}
		fd++;
	}
}
