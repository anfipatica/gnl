/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:56:57 by marvin            #+#    #+#             */
/*   Updated: 2023/11/05 18:56:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strnjoin(char *remain, char *buf, int n)
{
	int		len_remain;
	int		len_buf;
	int		i;
	int		j;
	char	*new;

	if (!buf)
		return (NULL);
	if (!remain)
		remain = calloc(1, sizeof(char));
	if (!remain)
		return (NULL);
	len_remain = strlen(remain);
	len_buf = strlen(buf);
	i = -1;
	j = 0;
	new = calloc((len_remain + n + 1), sizeof(char));
	if (!new)
		return (free(remain), NULL);
	while (++i < len_remain || i < n)
	{
		if (i < len_remain)
			new[j] = remain[i];
		if (i < n)
			new[j + len_remain] = buf[i];
		j++;
	}
	return (free(remain), new);
}


//Tengo que comprobar si el motivo de que me detecte el salto de línea una posición
//más adelante de la real se debe a cómo trata windows los saltos de línea!!
int		ft_find_end_line(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (-2);
	while(buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return(-1);
}
char	*patata(int n, int read_chars, char *buf, char *remain)
{
	char	*line;
	printf("en patata: %p\n", buf);
	printf("entré en patata wwwweeeee\n");
	if (n == -2)
		return (free(buf),NULL);
	else if (n == -1)
	{
		printf("n = -1\n");
		remain = ft_strnjoin(remain, buf, read_chars);
		return(remain);
	}
	else
	{
		printf("hemos encontrado el final de línea\n");
		line = ft_strnjoin(remain, buf, n);
		remain = '\0';
		remain = ft_strnjoin(remain, &buf[n + 1], read_chars - n);
		printf("line = %s\n", line);
		printf("remain = %s\n",remain);
		return (free(buf), line);
	}
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*buf;
	int			read_chars;

	if (!fd)
		return (NULL);
	if (!remain)
		remain = calloc(1, sizeof(char));
	while (remain)
	{
		buf = calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
		return (NULL);
		printf("en gnl: %p\n", buf);
		printf("Hola holita%s\n", remain);
		read_chars = read(fd, buf, BUFFER_SIZE);
		if (read_chars == -1)
			return (free(buf), NULL);
		else if (read_chars == 0)
			return(free(buf), remain);
		remain = patata(ft_find_end_line(buf), read_chars, buf, remain);
		printf("En gnl, tras patata, remain vale: %s\n", remain);
	}
	return (NULL);
}

int		main (void)
{
	char *str;
	int fd = open("prueba.txt", O_RDONLY);

	while (str = get_next_line(fd))
	{
		printf("hola\n");
		printf("---------------------------------------------\nDe vuelta en el main. str = %s\n---------------------------------------------\n\n", str);
		free(str);
	}

	close(fd);
}