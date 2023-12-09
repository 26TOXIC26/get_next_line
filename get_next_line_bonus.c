/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 23:31:42 by amousaid          #+#    #+#             */
/*   Updated: 2023/12/09 00:09:25 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_all_line(int fd, char *buffer)
{
	char	*text;
	char	*temp;
	ssize_t		i;

	text = malloc((size_t)BUFFER_SIZE + 1);
	if (!text)
		return (NULL);
	i = 1;
	while (!ft_strchr(buffer, '\n'))
	{
		i = read(fd, text, BUFFER_SIZE);
		if (i <= 0)
			break ;
		text[i] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, text);
		free(temp);
	}
	free(text);
	if (i < 0)
	{
		free(buffer);
		return (buffer = NULL);
	}
	return (buffer);
}

char	*get_correct_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*reload_line(char *buffer)
{
	char	*new_buffer;
	size_t	i;

	i = 0;
	new_buffer = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0' || (buffer[i] == '\n' && buffer[i + 1] == '\0'))
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	new_buffer = ft_strjoin(new_buffer, (buffer + i) + 1);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer[fd] = get_all_line(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = get_correct_line(buffer[fd]);
	if (line == NULL)
		return (NULL);
	buffer[fd] = reload_line(buffer[fd]);
	return (line);
}