/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-nac <sait-nac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:01:58 by sait-nac          #+#    #+#             */
/*   Updated: 2024/11/18 18:02:35 by sait-nac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_lent;
	size_t	src_lent;
	size_t	i;

	i = 0;
	src_lent = ft_strlen(src);
	if (dstsize == 0)
		return (src_lent);
	dst_lent = ft_strlen(dst);
	if (dst_lent >= dstsize)
		return (dstsize + src_lent);
	while (i < (dstsize - dst_lent - 1) && src[i])
	{
		dst[dst_lent + i] = src[i];
		i++;
	}
	dst[dst_lent + i] = '\0';
	return (dst_lent + src_lent);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*original;
	size_t	s1_lent;

	s1_lent = ft_strlen(s1);
	s2 = (char *)malloc(s1_lent + 1);
	if (s2 == NULL)
		return (NULL);
	original = s2;
	while (*s1)
		*(s2++) = *(s1++);
	*s2 = '\0';
	return (original);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!*s1)
		return (ft_strdup(s2));
	if (!*s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len);
	ft_strlcat(result, s2, total_len);
	return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
