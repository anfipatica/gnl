/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:15:33 by ymunoz-m          #+#    #+#             */
/*   Updated: 2023/12/21 14:50:07 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *string, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		((char *)string)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(int nitems, int size)
{
	void	*str;

	str = (char *)(malloc(nitems * size));
	if (!str)
	{
		return (NULL);
	}
	ft_bzero(str, (nitems * size));
	return (str);
}

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

char	*ft_strdup(char *s1, int n)
{
	char	*s2;
	int		i;

	if (!s1 || n <= 0)
		return (NULL);
	s2 = ft_calloc((n + 1), sizeof(char));
	if (!s2)
		return (NULL);
	i = -1;
	while (++i < n && s1[i])
		s2[i] = s1[i];
	return (s2);
}
