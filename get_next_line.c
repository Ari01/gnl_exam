#include "get_next_line.h"

int	ft_strlen(char *s)
{
    int i;

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

char	*ft_substr(char *s, int start, int len)
{
    int	    i;
    char    *sub;

    sub = malloc(sizeof(*sub) * (len + 1));
    i = 0;
    while (i < len)
    {
	sub[i] = s[start];
	start++;
	i++;
    }
    sub[i] = 0;
    return (sub);
}

int	readfile(char **buff)
{
    int	    ret;
    char    *freeptr;
    char    tmp[100001];

    while ((ret = read(0, tmp, 100000)) > 0)
    {
	tmp[ret] = 0;
	if (tmp[0] == '\n' && !tmp[1])
	    return(2);
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
    int	    ret;
    int	    len;
    char    *freeptr;
    char    *endline;

    endline = ft_strchr(*buff, '\n');
    freeptr = *buff;
    if (!endline)
    {
	*line = ft_strdup(*buff);
	*buff = 0;
	ret = 0;
    }
    else
    {
	len = endline - *buff;
	*line = ft_substr(*buff, 0, len);
	len++;
	*buff = ft_substr(*buff, len, ft_strlen(*buff) - len);
	ret = 1;
    }
    free(freeptr);
    return (ret);
}

int	get_next_line(char **line)
{
    static char	*buff;
    int		ret;

    if (!buff)
	buff = ft_strdup("");
    ret = readfile(&buff);
    if (ret < 0)
    {
	free(buff);
	buff = 0;
	return (-1);
    }
    if (ret == 2)
    {
	*line = ft_strdup("");
	free(buff);
	buff = 0;
	return (1);
    }
    return (readbuff(&buff, line));
}
