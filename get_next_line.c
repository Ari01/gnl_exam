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

char	*ft_strchr(char *s, char c)
{
    while (*s)
    {
	if (*s == c)
	    return (s);
    }
    return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
    int	    i;
    char    *join;

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
    int	    ret;
    char    tmp[100001];
    char    *freeptr;

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

char	*cutbuff(char *buff, int i)
{
    int	    j;
    int	    len;

    len = i;
    while (buff[len])
	len++;
    len -= i;
    buff = malloc(sizeof(*buff) * (len + 1));
    j = 0;
    while (buff[i])
    {
	buff[j] = buff[i];
	i++;
	j++;
    }
    buff[j] = 0;
    return (buff);
}

char	*readbuff(char **buff)
{
    int	    i;
    char    *freeptr;
    char    *line;

    i = 0;
    freeptr = *buff;
    while ((*buff)[i] && (*buff)[i] != '\n')
	i++;
    line = malloc(sizeof(*line) * (i + 1));
    i = 0;
    while ((*buff)[i] && (*buff)[i] != '\n')
	line[i] = (*buff)[i];
    line[i] = 0;
    if ((*buff)[i] == '\n' && (*buff)[++i])
	*buff = cutbuff(*buff, i);
    free(freeptr);
    return (line);
}

int	get_next_line(char **line)
{
    static char    *buff;
    int		    ret;

    if (!buff)
    {
	buff = malloc(sizeof(*buff));
	*buff = 0;
    }
    if (*buff)
	*line = readbuff(&buff);
    else
    {
	ret = readfile(&buff);
	if (ret > 0)
	    *line = readbuff(&buff);
	else
	{
	    *line = malloc(sizeof(**line));
	    **line = 0;
	}
    }
    return (ret);
}
