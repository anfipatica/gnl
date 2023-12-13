#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h> //strlen

char	*get_next_line(int fd);
char	*readbuf(int fd, char *storage);
char	*new_line(char *storage);
char	*clean_storage(char *storage);
void	ft_free(char **str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);

#endif