#include "get_next_line.h"

int	readfile(char **buff)
{
    int	    ret;
    char    *freeptr;
    char    tmp[100001];

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
    return (readbuff(&buff, line));
}
