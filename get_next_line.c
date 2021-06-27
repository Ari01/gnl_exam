#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(char **line)
{
    int	    ret;
    int	    size;
    int	    i;
    char    c;
    char    *tmp;

    if (!(*line = malloc(sizeof(**line))))
	return (-1);
    (*line)[0] = 0;
    size = 2;
    while ((ret = read(0, &c, 1)) > 0 && c != '\n')
    {
	if (!(tmp = malloc(sizeof(*tmp) * (size))))
	    return (-1);
	i = 0;
	while (i < size - 2)
	{
	    tmp[i] = (*line)[i];
	    i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
	size++;
    }
    return (ret);
}
