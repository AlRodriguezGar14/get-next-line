/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:02:51 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/23 14:02:54 by alberrod         ###   ########.fr       */
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

// #define BUFFER_SIZE 4092
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

char *read_file(int fd)
{
    int bytes_read;
    char *buffer;
	int	idx;

    buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

	idx = 0;
    while (idx < BUFFER_SIZE - 1)
    {
        bytes_read = read(fd, &buffer[idx], 1);
        if (bytes_read <= 0)
        {
            free(buffer);
            return NULL;
        }
		if (buffer[idx] == '\n')
		{
			idx++;
			break;
		}
        idx++;
    }
    buffer[idx] = '\0';
    return buffer;
}


size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	ret;

	idx = -1;
	while (++idx < dstsize && *dst)
		dst++;
	ret = ft_strlcpy(dst, src, dstsize - idx);
	return (ret + idx);
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

char *append_line(char *line, char *next_line)
{
    char *new_line;
    size_t len_line = 0;
    size_t len_next_line = 0;

    if (line)
        len_line = ft_strlen(line);
    if (next_line)
        len_next_line = ft_strlen(next_line);

    new_line = ft_calloc((len_line + len_next_line + 1), sizeof(char));
	
    if (line)
    {
		ft_strlcat(new_line, line, len_line + len_next_line);
        free(line);
    }
    if (next_line)
    {
		ft_strlcat(new_line + len_line, next_line, len_line + len_next_line);
        free(next_line);
    }
    return (new_line);
}

char *get_next_line(int fd)
{
    char *next_line;
    char *line = NULL;

    while (1)
    {
        next_line = read_file(fd);
        if (next_line == NULL)
            break;
        line = append_line(line, next_line);
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
    if (fd == -1)
        return (fd);

	line = get_next_line(fd);
	printf("%s", line);
    free(line);
    close(fd);
    return (0);
}
