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

char	*ft_substr(char *s, int start, int len)
{
    char    *sub;
    int	    i;

    sub = malloc(sizeof(*sub) * (len + 1));
    i = 0;
    while (i < len)
    {
	sub[i] = s[start];
	i++;
	start++;
    }
    sub[i] = 0;
    return (sub);
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
    char    tmp[256];
    int	    ret;

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
	if (ft_strchr(tmp, '\n'))
	    return (1);
    }
    return (ret);
}

void	readbuff(char **buff, char **line)
{
    char    *tmp;
    int	    len;

    len = 0;
    if (*buff)
    {
	while ((*buff)[len] && (*buff)[len] != '\n')
	    len++;
	if (!(*buff)[len])
	{
	    *line = ft_strdup(*buff);
	    free(*buff);
	    *buff = 0;
	}
	else
	{
	    *line = ft_substr(*buff, 0, len);
	    tmp = ft_strdup(&((*buff)[len + 1]));
	    free(*buff);
	    *buff = tmp;
	}
    }
}

int	get_next_line(char **line)
{
    static char	*buff=NULL;
    int		ret;

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
