/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:58:34 by sait-nac          #+#    #+#             */
/*   Updated: 2024/11/21 17:54:09 by marvin           ###   ########.fr       */
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

char	*set_line(char **left)
{
	char	*result;
	size_t	i;
	size_t	st_lent;
	char	*new_line;

	i = 0;
	while (((*left)[i] != '\n') && ((*left)[i] != '\0'))
		i++;
	if ((*left)[i] == 0 && !(*left)[0])
	{
		free(*left);
		*left = NULL;
		return (NULL);
	}
	if ((*left)[i] == '\n')
		i++;
	result = ft_substr(*left, 0, i);
	st_lent = ft_strlen(*left + i);
	new_line = ft_substr(*left, i, st_lent);
	free(*left);
	*left = new_line;
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
		if (!left)
			return (NULL);
		if (check == 0)
			break ;
		temp = left;
		left = ft_strjoin(temp, buffer);
		if (!left)
		{
			free(temp);
			return (NULL);
		}
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
	char		*final;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	left = get_the_line(fd, left, buffer);
	free(buffer);
	buffer = NULL;
	final = set_line(&left);
	return final;
}

