/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:02:51 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/28 05:06:16 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_line(char *line, char *next_line)
{
	char	*new_line;
	size_t	len_line;
	size_t	len_next_line;

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

char	*read_file(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	start = 0;
	static int	end = 0;
	char		*line;
	int			idx;

	if (start >= end)
	{
		end = read(fd, buffer, BUFFER_SIZE);
		if (end <= 0)
			return (NULL);
		start = 0;
	}
	idx = start;
	while (idx < end)
	{
		if (buffer[idx++] == '\n')
			break ;
	}
	line = ft_calloc(idx - start + 1, sizeof(char));
	ft_memcpy(line, buffer + start, idx - start);
	start = idx;
	return (line);
}

char	*get_next_line(int fd)
{
	char	*next_line;
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		next_line = read_file(fd);
		if (next_line == NULL)
			break ;
		tmp = append_line(line, next_line);
		if (!tmp)
			break ;
		free(line);
		free(next_line);
		line = tmp;
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

// int	main(void)
// {
// 	// char *filename = "lorem.txt";
// 	// char *filename = "large_file.txt";
// 	// char *filename = "very_long_line.txt";
// 	// char *filename = "null.txt";
// 	char *filename = "nonullend.txt";
// 	char *line = NULL;
// 	int fd = open(filename, O_RDONLY);
// 	int count = 0;
// 	if (fd == -1)
// 		return (fd);

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		printf("%s", line);
// 		count++;
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }