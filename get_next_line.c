/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:58:34 by sait-nac          #+#    #+#             */
/*   Updated: 2024/11/18 18:55:01 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;

	d = (char)c;
	while (*s)
	{
		if (*s == d)
			return ((char *)s);
		s++;
	}
	if (*s == d)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*set_line(char **line_buffer)
{
	char	*result;
	size_t	i;
	size_t	st_lent;
	char	*new_line;

	i = 0;
	while (((*line_buffer)[i] != '\n') && ((*line_buffer)[i] != '\0'))
		i++;
	result = ft_substr(*line_buffer, 0, i);
	st_lent = ft_strlen(*line_buffer + i + 1);
	new_line = ft_substr(*line_buffer, i + 1, st_lent);
	free(*line_buffer);
	*line_buffer = new_line;
	return (result);
}

char	*get_the_line(int fd, char *left, char *buffer)
{
	ssize_t	check;
	char	*temp;

	check = 1;
	while (check > 0)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check < 0)
			return (NULL);
		buffer[check] = '\0';
		if (left == NULL)
			left = ft_strdup("");
		if (check == 0)
			break ;
		temp = left;
		left = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(left, '\n'))
			break ;
	}
	return (left);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*left;
	char		*whole_line;
	char		*final;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
    {
        free(left);
        free(buffer);
        left = NULL;
        buffer = NULL;
        return (NULL);
    }
	if (!buffer)
		return (NULL);
	whole_line = get_the_line(fd, left, buffer);
	free(buffer);
	buffer = NULL;
	if (!whole_line)
		return (NULL);
	left = set_line(whole_line);
	return (whole_line);
}
