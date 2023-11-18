#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ft_strjoin(char *s1, char *s2)
{
	size_t			len_s1;
	size_t			len_s2;
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	if (!s1)
		s1 = calloc(1, sizeof(char));
	if (!s1 && !s2)
		return (0);
	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	i = 0;
	j = 0;
	s3 = calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!s3)
		return (0);
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			s3[j] = s1[i];
		if (i < len_s2)
			s3[j + len_s1] = s2[i];
		j++;
		i++;
	}
	free(s1);
	return (s3);
}

void ft_static(char *src)
{
	static char *dst;

	dst = ft_strjoin(dst, src);
	printf("dst = %s", dst);
	
}

int main (void)
{
	ft_static("Hola1");
	ft_static("Hola2");
	ft_static("Hola3");
	ft_static("Hola4");
}