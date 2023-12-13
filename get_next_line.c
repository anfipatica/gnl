#include "get_next_line.h"

int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
		i++;
	return (i);
}
void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}
char *ft_strnjoin(char *s1, char *s2, int n)
{
	char	*line;
	int		i;
	int		j;

	if (!s2 || n == 0)
		return (NULL);
	if (!s1)
		s1 = calloc(1, sizeof(char));
	if (!s1)
		return (NULL);
	line = calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!line)
		return(ft_free(&s1), NULL);
	i = -1;
	j = -1;
	while (s1[++i] && i < n)
		line[i] = s1[i];
	while (s2[++j] && (i + j) < n)
			line[i + j] = s2[j];
	return (ft_free(&s1),line);
}

int	ft_find_end_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line == NULL)
	{
		return (0);
	}
	while(line[i])
	{
		if (line[i] == '\n')
			return (i + 1);
		i++;
	}
	return(0);
}

char	*ft_read(int fd, char *remain)
{
	char	*read_line;
	int		read_chars;

	read_line = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_line)
		return (NULL);
	read_chars = 1;
	while (read_chars > 0 && ft_find_end_line(read_line) == 0)
	{
		read_chars = read(fd, read_line, BUFFER_SIZE);
		if (read_chars > 0)
			remain = ft_strnjoin(remain, read_line, read_chars + ft_strlen(remain));
	}
	if (read_chars == -1)
		return (ft_free(&read_line), ft_free(&remain), NULL);
	return (ft_free(&read_line), remain);
}

char	*clean_remain(char *remain)
{
	int		n;
	char	*line;

	n = ft_find_end_line(remain);
	if (n == 0)
	{
		line = NULL;
		return(ft_free(&remain), NULL);
	}
	ft_free(&line);
	line = ft_strnjoin(line, &remain[n], ft_strlen(remain) - n);
	ft_free(&remain);
	return(line);
}
char	*get_next_line(int fd){
	static char	*remain;
	char		*line;
	int			n;

	if (!fd || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain || (remain && ft_find_end_line(remain) == 0))
		remain = ft_read(fd, remain);
	if (!remain)
		return (NULL);
	n = ft_find_end_line(remain);
	if (n != 0)
		line = ft_strnjoin(NULL, remain,n);
	else
		line = ft_strnjoin(NULL, remain, ft_strlen(remain));
	if (!line || line == NULL)
		return (ft_free(&remain), NULL);
	remain = clean_remain(remain);
	return(line);
}

/*int		main (void)
{
	//static char *remain;
	char *str;
	int fd = open("prueba.txt", O_RDONLY);

	// for (int i = 0; i < 4; i++)
	// {
	// 	str = get_next_line(fd);
	// 	printf("--------------\nDe vuelta en el main. str = %s\n-----------------\n\n", str);
	// 	free(str);
	// 	//str[0] = "\0";
	// }
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("--------------\nDe vuelta en el main. str = %s\n-----------------\n\n", str);
		free(str);
	}
	//str = NULL;
	close(fd);
}*/