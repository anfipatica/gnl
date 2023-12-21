/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:42:43 by ymunoz-m          #+#    #+#             */
/*   Updated: 2023/12/21 15:19:01 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*line;
	int		i;
	int		j;

	if (!s2 || n == 0)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1)
		return (NULL);
	line = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!line)
		return (ft_free(&s1), NULL);
	i = -1;
	j = -1;
	while (s1[++i] && i < n)
		line[i] = s1[i];
	while (s2[++j] && (i + j) < n)
		line[i + j] = s2[j];
	return (ft_free(&s1), line);
}

int	ft_find_end_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line == NULL)
	{
		return (0);
	}
	while (line[i])
	{
		if (line[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*clean_remain(char *remain)
{
	int		n;
	char	*line;

	line = NULL;
	if (!remain)
		return (ft_free(&remain), NULL);
	n = ft_find_end_line(remain);
	if (n == 0)
	{
		line = NULL;
		return (ft_free(&remain), NULL);
	}
	line = ft_strdup(&remain[n], ft_strlen(remain) - n);
	if (!line)
		return (ft_free(&line), ft_free(&remain), NULL);
	ft_free(&remain);
	return (line);
}

char	*ft_read(int fd, char *remain)
{
	char	*read_line;
	int		read_chars;

	read_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_line)
		return (NULL);
	read_chars = 1;
	while (read_chars > 0 && ft_find_end_line(read_line) == 0)
	{
		read_chars = read(fd, read_line, BUFFER_SIZE);
		if (read_chars > 0)
			remain = ft_strnjoin(remain, read_line,
					read_chars + ft_strlen(remain));
	}
	if (read_chars == -1)
		return (ft_free(&read_line), ft_free(&remain), NULL);
	return (ft_free(&read_line), remain);
}

char	*get_next_line(int fd)
{
	static char	*remain[OPEN_MAX];
	char		*line;
	int			n;
	int			i;

	i = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain[fd] || (remain[fd] && ft_find_end_line(remain[fd]) == 0))
		remain[fd] = ft_read(fd, remain[fd]);
	if (!remain[fd])
		return (NULL);
	n = ft_find_end_line(remain[fd]);
	if (n != 0)
		line = ft_strdup(remain[fd], n);
	else
		line = ft_strdup(&remain[fd][n], ft_strlen(remain[fd]) - n);
	if (!line || line == NULL)
		return (ft_free(&remain[fd]), NULL);
	remain[fd] = clean_remain(remain[fd]);
	return (line);
}

int		main (void)
{
	char	*str[3];
	int fd[3];
	fd[0] = open("long_line.txt", O_RDONLY);
	fd[1] = open("no_line.txt", O_RDONLY);
	fd[2] = open("many_nl.txt", O_RDONLY);
	int i = 1;
	int check;

	while (i < 10)
	{
		i = 0;
		check = 0;

		str[i] = get_next_line(fd[i]);
		printf("fd_%d = %s\n", i, str[i]);
		i++;
		
		str[i] = get_next_line(fd[i]);
		printf("fd_%d = %s\n", i, str[i]);
		i++;

		str[i] = get_next_line(fd[i]);
		printf("fd_%d = %s\n", i, str[i]);
		i++;

		printf("\n · · · · · · · · · · · · · · · · · · · ·\n");
		for (int j = 0; j < i; j++)
		{
			if (!str[j])
				check++;
		}

		for (int j = 0; j < i; j++)
			free(str[j]);

		if (check == i)
			break;
	}
	while (++i < 3)
		close(fd[i]);
}
