#include "get_next_line.h"

int	ft_strlen(char	*s)
{
    int	i;

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
    int	    i;
    char    *dup;

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
    int	    i;
    char    *join;

    i = 0;
    join = malloc(sizeof(*join) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    while (*s1)
    {
	join[i] = *s1;
	s1++;
	i++;
    }
    while (*s2)
    {
	join[i] = *s2;
	s2++;
	i++;
    }
    join[i] = 0;
    return (join);
}

char	*ft_substr(char *s, int start, int len)
{
    char    *sub;
    int	    i;

    i = 0;
    sub = malloc(sizeof(*sub) * (len + 1));
    while (i < len)
    {
	sub[i] = s[start];
	i++;
	start++;
    }
    sub[i] = 0;
    return (sub);
}

int	readfile(char **buff)
{
    int	    ret;
    char    tmp[256];
    char    *freeptr;

    while ((ret = read(0, tmp, 255)) > 0)
    {
	tmp[ret] = 0;
	if (!*buff)
	    *buff = ft_strdup(tmp);
	else
	{
	    freeptr = *buff;
	    *buff = ft_strjoin(*buff, tmp);
	    free(freeptr);
	}
	if (ft_strchr(*buff, '\n'))
	    return (1);
    }
    return (ret);
}

void	readbuff(char **buff, char **line)
{
    char    *freeptr;
    char    *endline;
    int	    len;

    if (!*buff)
	*line = ft_strdup("");
    else
    {
	endline = ft_strchr(*buff, '\n');
	if (!endline)
	{
	    *line = ft_strdup(*buff);
	    free(*buff);
	    *buff = 0;
	}
	else
	{
	    len = endline - *buff;
	    *line = ft_substr(*buff, 0, len);
	    freeptr = *buff;
	    *buff = ft_strdup(&((*buff)[len + 1]));
	    free(freeptr);
	}
    }
}

int	get_next_line(char **line)
{
    int		ret;
    static char	*buff;

    if (!buff || !ft_strchr(buff, '\n'))
    {
	ret = readfile(&buff);
	if (ret < 0 && buff)
	{
	    free(buff);
	    buff = 0;
	    return (-1);
	}
    }
    readbuff(&buff, line);
    if (!buff || !ft_strchr(buff, '\n'))
    {
	ret = readfile(&buff);
	if (ret < 0 && buff)
	{
	    free(buff);
	    buff = 0;
	    return (-1);
	}
    }
    return (!!buff);
}
