/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:04:34 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/08 10:58:48 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int index = 0;
    static int size = 0;

    char *line = NULL;
    int line_size = 0;
    int line_capacity = 0;

    while (1)
	{
        if (index >= size)
		{
            index = 0;
            size = read(fd, buffer, BUFFER_SIZE);
            if (size < 0)
			{
                free(line);
                return NULL;
            }
			else if (size == 0)
			    break ;
        }
        char current_char = buffer[index++];
        if (line_size >= line_capacity)
		{
            line_capacity += BUFFER_SIZE;
            char *temp = realloc(line, line_capacity);
            if (!temp)
			{
                free(line);
                return NULL;
            }
            line = temp;
        }

        line[line_size++] = current_char;

        if (current_char == '\n')
            break ;
    }
    
    if (line)
	{
        char *temp = realloc(line, line_size + 1);
        if (temp)
		{
            line = temp;
            line[line_size] = '\0';
        }
    }
    return (line);
}

/* 
int main()
{
    int fd = open("test_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening the file");
        return 1;
    }

    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
} */