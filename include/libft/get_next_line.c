/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:49:11 by marvin            #+#    #+#             */
/*   Updated: 2025/08/29 12:49:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *buffer, char **rest);
static char	*get_rest_and_line(char **rest);
static char	*free_buffer(char **buffer);

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*rest;
	char		*full_content;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	full_content = read_line(fd, buffer, &rest);
	free_buffer(&buffer);
	if (!full_content)
	{
		free_buffer(&rest);
		return (NULL);
	}
	line = get_rest_and_line(&rest);
	return (line);
}

static char	*read_line(int fd, char *buffer, char **rest)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!*rest)
			*rest = ft_strdup("");
		temp = *rest;
		*rest = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*rest);
}

static char	*get_rest_and_line(char **rest)
{
	char	*line;
	char	*temp_rest;
	int		i;

	if (!*rest || **rest == '\0')
		return (NULL);
	i = 0;
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	if ((*rest)[i] == '\n')
		i++;
	line = ft_substr(*rest, 0, i);
	temp_rest = ft_substr(*rest, i, ft_strlen(*rest) - i);
	free(*rest);
	*rest = temp_rest;
	if (**rest == '\0')
		free_buffer(rest);
	return (line);
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
