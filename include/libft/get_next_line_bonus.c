/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:49:17 by marvin            #+#    #+#             */
/*   Updated: 2025/08/29 12:49:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *buffer, char *rest);
static char	*get_rest(char *line);
static char	*free_buffer(char **buffer);

char	*get_next_line_bonus(int fd)
{
	char		*line;
	char		*buffer;
	static char	*rest[FD_LEN];
	char		*temp_rest;

	if (fd == -1 || BUFFER_SIZE <= 0 || fd > FD_LEN)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, rest[fd]);
	free_buffer(&buffer);
	if (!line)
	{
		free_buffer(&rest[fd]);
		return (NULL);
	}
	temp_rest = get_rest(line);
	free(rest[fd]);
	rest[fd] = temp_rest;
	return (line);
}

static char	*read_line(int fd, char *buffer, char *rest)
{
	ssize_t	buff_size;
	char	*temp;

	buff_size = 1;
	while (buff_size > 0)
	{
		buff_size = read(fd, buffer, BUFFER_SIZE);
		if (buff_size == -1)
			return (NULL);
		else if (buff_size == 0)
			break ;
		buffer[buff_size] = '\0';
		if (!rest)
			rest = ft_calloc(1, sizeof(char));
		temp = rest;
		rest = ft_strjoin(temp, buffer);
		free_buffer(&temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rest);
}

static char	*get_rest(char *line)
{
	int		linelen;
	int		restlen;
	char	*rest;
	char	*temp_line;

	linelen = 0;
	while (line[linelen] != '\n' && line[linelen] != '\0')
		linelen++;
	if (line[linelen] == '\n')
		linelen++;
	restlen = ft_strlen(line) - linelen;
	if (restlen > 0)
	{
		rest = ft_substr(line, linelen, restlen);
		temp_line = ft_substr(line, 0, linelen);
		ft_memcpy(line, temp_line, linelen);
		line[linelen] = '\0';
		free(temp_line);
	}
	else
		rest = NULL;
	return (rest);
}

static char	*free_buffer(char **buffer)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}
