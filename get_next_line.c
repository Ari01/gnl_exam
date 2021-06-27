#include "get_next_line.h"

int	ft_strlen(char *s)
{
    int	    i;

    i = 0;
    while (s[i])
	i++;
    return (i);
}

char	*ft_strchr(char *s, char c)
{
    while (*s)
    {
	if (*s == c)
	    return (s);
	s++;
    }
    return (NULL);
}

char	*ft_strdup(char *s)
{
    char    *dup;
    int	    i;

    i = 0;
    dup = malloc(sizeof(*dup) * (ft_strlen(s) + 1));
    while (s[i])
    {
	dup[i] = s[i];
	i++;
    }
    dup[i] = 0;
    return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
    char    *join;
    int	    i;

    join = malloc(sizeof(*join) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    i = 0;
    while (*s1)
    {
	join[i] = *s1;
	i++;
	s1++;
    }
    while (*s2)
    {
	join[i] = *s2;
	i++;
	s2++;
    }
    join[i] = 0;
    return (join);
}

int	readfile(char **buff)
{
    char    *freeptr;
    char    tmp[100001];
    int	    ret;

    while ((ret = read(0, tmp, 100000)) > 0)
    {
	tmp[ret] = 0;
	freeptr = *buff;
	*buff = ft_strjoin(*buff, tmp);
	free(freeptr);
	if (ft_strchr(tmp, '\n'))
	    return (1);
    }
    return (ret);
}

int	readbuff(char **buff, char **line)
{
    char    *endline;
    int	    len;
    int	    i;

    endline = ft_strchr(*buff, '\n');
    i = 0;
    if (!endline)
    {
	*line = malloc(1);
	**line = 0;
	free(*buff);
	*buff = 0;
	return (0);
    }
    else
    {
	len = endline - *buff;
	*line = malloc(len);
	while (i < len)
	{
	    (*line)[i] = (*buff)[i];
	    i++;
	}
	i++;
	*buff = ft_strdup(&(*buff)[i]);
	
    }
    return (1);
}

int	get_next_line(char **line)
{
    static char	*buff;

    if (!buff)
    {
	buff = malloc(1);
	*buff = 0;
    }
    if (buff[0] == '\n' && !buff[1])
    {
	free(buff);
	buff = 0;
	*line = malloc(1);
	**line = 0;
	return (1);
    }
    if (readfile(&buff) < 0)
    {
	free(buff);
	buff = 0;
	return (-1);
    }
    return (readbuff(&buff, line));
}
