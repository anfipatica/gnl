/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymunoz-m <ymunoz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:46:12 by ymunoz-m          #+#    #+#             */
/*   Updated: 2023/12/17 16:05:34 by ymunoz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h> //strlen
# include <limits.h> //OPEN_MAX

char	*get_next_line(int fd);
char	*ft_read(int fd, char *remain);
char	*clean_remain(char *remain);
int		ft_find_end_line(char *line);
char	*ft_strnjoin(char *s1, char *s2, int n);
void	ft_free(char **str);
int		ft_strlen(const char *s);
void	*ft_calloc(int nitems, int size);
void	ft_bzero(void *string, int n);
char	*ft_strdup(char *s1, int n);

#endif