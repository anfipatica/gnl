/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:42:43 by ymunoz-m          #+#    #+#             */
/*   Updated: 2023/12/17 14:42:43 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*remain;
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain || (remain && ft_find_end_line(remain) == 0))
		remain = ft_read(fd, remain);
	if (!remain)
		return (NULL);
	n = ft_find_end_line(remain);
	if (n != 0)
		line = ft_strdup(remain, n);
	else
		line = ft_strdup(&remain[n], ft_strlen(remain) - n);
	if (!line || line == NULL)
		return (ft_free(&remain), NULL);
	remain = clean_remain(remain);
	return (line);
}

/*int		main (void)
{
	char *str;
	int fd = open("prueba.txt", O_RDONLY);

	while ((str = get_next_line(fd)) != NULL)
	{
		printf("--------------\nstr = %s\n-----------\n\n", str);
		free(str);
	}
	//str = NULL;
	close(fd);
}*/