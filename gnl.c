/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:04:34 by fsuomins          #+#    #+#             */
/*   Updated: 2023/08/08 11:50:57 by fsuomins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];  // Buffer para armazenar caracteres lidos
    static int index = 0;             // Índice atual no buffer
    static int size = 0;              // Número de caracteres lidos no último bloco

    char *line = NULL;                // Linha sendo construída
    int line_size = 0;                // Tamanho atual da linha
    int line_capacity = 0;            // Capacidade atual da linha

    while (1)  // Loop principal
	{
        if (index >= size)  // Verifica se precisa ler um novo bloco
		{
            index = 0;  // Reseta o índice para o início do buffer
            size = read(fd, buffer, BUFFER_SIZE);  // Lê um bloco de caracteres

            if (size < 0)  // Se houver um erro de leitura
			{
                free(line);  // Libera a memória alocada para a linha (se houver)
                return NULL;  // Retorna NULL para indicar um erro
            }
			else if (size == 0)  // Se o final do arquivo for alcançado
			    break ;  // Sai do loop
        }

        char current_char = buffer[index++];  // Lê o caractere atual do buffer

        if (line_size >= line_capacity)  // Verifica se precisa realocar a linha
		{
            line_capacity += BUFFER_SIZE;  // Aumenta a capacidade da linha
            char *temp = realloc(line, line_capacity);  // Realoca a linha

            if (!temp)  // Se a realocação falhar
			{
                free(line);  // Libera a memória alocada para a linha
                return NULL;  // Retorna NULL para indicar um erro
            }
            line = temp;  // Atualiza o ponteiro da linha
        }

        line[line_size++] = current_char;  // Adiciona o caractere à linha

        if (current_char == '\n')  // Verifica se encontrou uma quebra de linha
            break ;  // Sai do loop
    }

    if (line)  // Se a linha não estiver vazia
	{
        char *temp = realloc(line, line_size + 1);  // Realoca a linha para o tamanho exato

        if (temp)  // Se a realocação for bem-sucedida
		{
            line = temp;             // Atualiza o ponteiro da linha
            line[line_size] = '\0';  // Adiciona um caractere nulo para terminar a string
        }
    }

    return line;  // Retorna a linha lida (ou NULL se houver erro)
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