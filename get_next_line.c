//For the first call of read the cursor stat at the begining 
//each time we read we chift the cursor
//

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 8
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	if (!*s1 && !*s2)
		return (strdup(""));
	total_len = strlen(s1) + strlen(s2) + 1;
	result = (char *)malloc(total_len);
	if (!result)
		return (NULL);
	strlcpy(result, s1, total_len);
	strlcat(result, s2, total_len);
	return (result);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	if (start >= strlen(s))
		return (strdup(""));
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
char *set_line(char **line_buffer)
{
    char    *result;
   size_t   i;
   size_t   st_lent;
   char *new_line;

   i = 0;
   while ((*line_buffer)[i] != '\n')
        i++;
    result = ft_substr(*line_buffer, 0, i);
    st_lent = strlen(*line_buffer + i + 1);
    new_line = ft_substr(*line_buffer, i + 1, st_lent);
    free(*line_buffer);
    *line_buffer = new_line;
    return (result);
}

char *get_the_line(int fd, char *left, char *buffer)
{
    ssize_t check;
    char    *new_line;
    char    *temp;

    check = 1;
    while (check > 0)
    {
        check = read(fd, buffer, BUFFER_SIZE);
        if (check < 0)
            return (NULL);
        if (check == 0)
            return (NULL);
        buffer[check] = '\0';
        if (left == NULL)
            left = strdup("");
        temp = left;
        printf("the value of the temp :%s\n ", temp);
        left = ft_strjoin(temp, buffer);
        printf("this is out string string : %s\n", left);

        free(temp);
        if (strchr(left, '\n'))
            break;
    }
    free(buffer);
    printf("this is the value of the final result %s\n", left);
    return (left);
}
char *get_next_line(int fd)
{
    char *buffer;
    static char *left;
    char *line;
    char *final;

    if (fd < 0)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    line = get_the_line(fd, left, buffer);
    final = set_line(&line);
    return (final);
}

int main()
{
    int fd = open("test.text", O_RDONLY);
    get_next_line(fd);
}