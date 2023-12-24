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
#define BUFFER_SIZE 42

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


char *read_file(int fd)
{
	int		bytes_read;
	char	*buffer = NULL;
	

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';

	return (buffer);
}


int	main(void)
{
	char	*filename = "lorem.txt";
	char	*next_line;
	int		fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (fd);

	while (1)
	{
		next_line = read_file(fd);
		if (next_line == NULL)
			break ;
		printf("%s", next_line);
		free(next_line);
	}

	close(fd);
	return (0);
}

