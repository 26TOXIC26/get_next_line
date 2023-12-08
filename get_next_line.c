/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:42:57 by amousaid          #+#    #+#             */
/*   Updated: 2023/12/08 21:27:53 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_strdup(const char *s)
{
	int		i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static void	ft_strcpy(char *d, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 && !s2)
	{
		return ft_strdup(s1);
	}
	else if (!s1 && s2)
	{
		return ft_strdup(s2);
	}
	else
	{
		result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (result == NULL)
			return (NULL);
		ft_strcpy(result, s1);
		ft_strcpy(result + ft_strlen(s1), s2);
	}
	return (result);
}

char *get_all_line (int fd, char *buffer)
{
	char *text;
	char *temp;
	int i;

	text = malloc((size_t)BUFFER_SIZE + 1);
	if (!text)
		return (NULL);
	i = 1;
	while (!ft_strchr(buffer, '\n'))
	{
		i = read(fd, text, BUFFER_SIZE);
		if (i <= 0)
			break;
		text[i] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, text);
		free(temp);
	}
	free(text);
	if (i < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (buffer);
}
char *get_correct_line(char *buffer)
{
	char *line;
	size_t i;
	
	i = 0;
	while (buffer[i] && buffer[i]!= '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i+1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i]!= '\n')
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
char *reload_line(char *buffer)
{
	char *new_buffer;
	size_t i;
	
	i = 0;
	new_buffer = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if(buffer[i] == '\0' || (buffer[i] == '\n' && buffer[i + 1] == '\0'))
	{
		free(buffer);
		buffer = NULL;
		return NULL;
	}
	new_buffer = ft_strjoin(new_buffer , (buffer + i) + 1);
	free(buffer);
	return (new_buffer);
}

char *get_next_line(int fd)
{
	static char *buffer;
	char *line;
	
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = get_all_line(fd, buffer);
	if(buffer == NULL)
		return NULL;
	line = get_correct_line(buffer);
	if(line == NULL)
		return NULL;
	buffer = reload_line(buffer);
	return (line);
}
// int main()
// {
// 	int fd = open("kokab.txt", O_RDWR);
// 	get_next_line(fd);
// 	close(fd);
// }