#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(char *s)
{
    int	    i;

    i = 0;
    while (s[i])
	i++;
    return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
    int	    i;
    char    *join;

    i = 0;
    join = malloc(sizeof(*join) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    while (*s1)
    {
	join[i] = s1[i];
	i++;
	s1++;
    }
     while (*s2)
    {
	join[i] = s2[i];
	i++;
	s2++;
    }
    join[i] = 0;
    return (join);
}

int	get_next_line(char **line)
{
    int		    ret;
    int		    i;
    int		    j;
    char	    c;
    char	    tmp[100001];
    static char	    *buff;
    char	    *freeptr;

    if (!(*line = malloc(sizeof(**line))))
	return (-1);
    (*line)[0] = 0;
    if (!buff)
    {
	ret = read(0, &c, 1);
	if (ret <= 0 || c == '\n')
	    return (ret);
	buff = malloc(sizeof(*buff) * 2);
	buff[0] = c;
	buff[1] = 0;
    }
    while ((ret = read(0, &tmp, 100000)) > 0)
    {
	i = 0;
	tmp[ret] = 0;
	freeptr = buff;
	buff = ft_strjoin(buff, tmp);
	free(freeptr);
	while (buff[i] && buff[i] != '\n')
	    i++;
	*line = malloc(sizeof(**line) * (i + 1));
	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
	    (*line)[i] = buff[i];
	if (buff[i])
	{
	    i++;
	    j = i;
	    while (buff[i])
		i++;
	    buff = malloc(sizeof(*buff) * (i - j + 1));
	    i = 0;
	    while (buff[j])
	    {
		buff[i] = buff[j];
		i++;
		j++;
	    }
	    return (1);
	}
	else
	{
	    buff = malloc(sizeof(*buff));
	    *buff = 0;
	}
	if (!ret && !*buff)
	    return (0);
    }
    return (ret);
}
