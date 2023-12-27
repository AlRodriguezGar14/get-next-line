/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:02:51 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/27 21:22:47 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
- Call the function get_next_line in a loop in your main function

	- Return the  line that has just been read. If there is nothing else to read or if an error has occurred it should return NULL.

	- The needed functions go to the get_next_line_utils.c file.

	- The program must compile with (where 42 might change):
		cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 <archivos>.c.

	- Functions allowed:
		read, malloc, free.
*/

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
# endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != 0)
		idx++;
	return (idx);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*char_dest;
	const unsigned char	*char_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	char_dest = (unsigned char *)dest;
	char_src = (const unsigned char *)src;
	while (n--)
		*char_dest++ = *char_src++;
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c && *str != '\0')
		str++;
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	idx;
	size_t	len;

	len = ft_strlen(src);
	if (size <= 0)
		return (len);
	idx = 0;
	while (idx < size - 1 && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (len);
}

void	*ft_memset(void *buffer, int val, size_t len)
{
	unsigned char	*p;

	p = buffer;
	while (len--)
		*p++ = (unsigned char)val;
	return (buffer);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*allocated;

	total = count * size;
	allocated = malloc(total);
	if (allocated == NULL)
		return (NULL);
	ft_memset(allocated, 0, total);
	return (allocated);
}

char	*ft_strdup(const char *str1)
{
	int		len;
	char	*out;

	len = ft_strlen(str1) + 1;
	out = ft_calloc(len, sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, (char *)str1, len);
	return (out);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	len_s1;
	size_t	len_s2;
	char	*output;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total_len = len_s1 + len_s2 + 1;
	output = (char *)ft_calloc(total_len, sizeof(char));
	if (output == NULL)
		return (NULL);
	ft_memcpy(output, (char *)s1, len_s1);
	ft_memcpy(output + len_s1, (char *)s2, len_s2);
	return (output);
}


char *append_line(char *line, char *next_line)
{
    char *new_line;
    size_t len_line;
    size_t len_next_line;

	len_line = 0;
	len_next_line = 0;
    if (line)
        len_line = ft_strlen(line);
    if (next_line)
        len_next_line = ft_strlen(next_line);
    new_line = ft_calloc((len_line + len_next_line + 1), sizeof(char));
	if (!new_line)
		return (NULL);
    if (line)
		ft_memcpy(new_line, line, len_line);
    if (next_line)
		ft_memcpy(new_line + len_line, next_line, len_next_line);
	new_line[len_line + len_next_line] = '\0';
    return (new_line);
}

char *read_file(int fd)
{
    static char	buffer[BUFFER_SIZE + 1];
    char		*line = NULL;
	char		*tmp;
    ssize_t		bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        if (line == NULL)
            line = ft_strdup(buffer);
        else
		{
			tmp = ft_strjoin(line, buffer);
			free(line);
			line = tmp;
		}
        if (ft_strchr(buffer, '\n'))
            break;
    }
    return (line);
}


char *get_next_line(int fd)
{
    char	*next_line;
    char 	*line = NULL;
	char	*tmp;

    while (1)
    {
        next_line = read_file(fd);
        if (next_line == NULL)
            break;
        tmp = append_line(line, next_line);
		free(line);
		free(next_line);
		line = tmp;
        if (ft_strchr(line, '\n'))
            break;
    }
	return (line);
}

int main(void)
{
    char	*filename = "lorem.txt";
	char	*line = NULL;
    int fd = open(filename, O_RDONLY);
	int	count = 0;
    if (fd == -1)
        return (fd);

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("line[%d]: %s", count, line);
		count++;
		free(line);
	}
    close(fd);
    return (0);
}