#include "get_next_line.h"


int	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		i++;
	}
	return (i);
}

char *ft_strnjoin(char *remain, char *buf, int n)
{
	int	len_remain;
	int	i;
	int	j;
	char	*new;

	if (!buf)
		return (NULL);
	if (!remain)
		remain = calloc(1, sizeof(char));

	if (!remain)
		return (NULL);
	len_remain = ft_strlen(remain);
	i = -1;
	j = 0;
	new = calloc((len_remain + n + 1), sizeof(char));
	if (!new)
		return (free(remain), NULL);
	while ( ++i < len_remain || (j + len_remain) < n)
	{
	
		//printf(" i = %d\n",i);	
		if (i < len_remain)
		{
			//	printf("new[j] = %c. remain[i] = %c\n", new[j], remain[i]);
			new[j] = remain[i];
		}
		if (i < n)
		{
			//printf("new[j] = %c. buf[i] = %c.\n", new[j + len_remain], buf[i]);
			new[j + len_remain] = buf[i];
		}
		j++;
		}
	return (free(remain), remain = NULL, new);
}

char	*ft_end_line_found(char *remain, char **line, int n)
{
	char	*temp;
	int	len_remain;

	len_remain = ft_strlen(remain);
	temp = calloc(len_remain + 1, sizeof(char));
	temp = ft_strnjoin(temp, remain, len_remain);
	*line = ft_strnjoin(*line, remain, n);
	free (remain);
	remain = NULL;
	remain = ft_strnjoin(remain, &temp[n], len_remain - n);
	return(free(temp),remain);
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


char	*get_next_line(int fd)
{
	static char *remain;
	char			*buf;
	char			*line;
	int			read_chars;
	int			n;

	read_chars = 1;
	buf = calloc(BUFFER_SIZE + 1, sizeof(char));
	while (buf)
	{
		//printf("Antes de hacer nada, remain = %s.\n", remain);
		if ((n = ft_find_end_line(&remain[0])) == 0) //No he encontrado salto de línea. O remain estaba vacío.
		{
			read_chars = read(fd, buf, BUFFER_SIZE); //Quizás habría que hacer un free o algo así de buf?
	//printf("buf = %s\n", buf);
	//printf("He entrado al primer condicional. read_chars = %d. a strnjoin meto: %d\n", n, ft_strlen(buf) + ft_strlen(remain));
			remain = ft_strnjoin(remain, buf, (ft_strlen(buf) + ft_strlen(remain)));
		}
		if (read_chars > 0 && n != 0)
		{
			line = calloc(n + 1, sizeof(char));
			remain =ft_end_line_found(remain, &line, n);
		//	printf("Antes de salir, remain = %s, line = %s.\n", remain, line);		
			return (free(buf), line);
		}
		else if (read_chars <= 0)
			break;
	}

	return (free(buf), free(remain), NULL);
}


int		main (void)
{
	//static char *remain;
	char *str;
	int fd = open("prueba.txt", O_RDONLY);

	while ((str = get_next_line(fd)) != NULL)
	{
		printf("--------------\nDe vuelta en el main. str = %s\n-----------------\n\n", str);
	free(str);
	}

	close(fd);
}