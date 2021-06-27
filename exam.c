#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(char **line)
{
    int		    r;
    int		    l;
    int		    i;
    char	    c;
    char	    *tmp;

    r = 0;
    l = 2;
    if (!(*line = malloc(sizeof(**line))))
	return (-1);
    (*line)[0] = 0;
    while ((r = read(0, &c, 1)) > 0 && c != '\n')
    {
	tmp = malloc(l);
	i = 0;
	while (i < l - 2)
	{
	    tmp[i] = (*line)[i];
	    i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
	l++;
    }
     return (r);
}
