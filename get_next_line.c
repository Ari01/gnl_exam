#include "get_next_line.h"

int	get_next_line(char **line)
{
    int	    i;
    int	    l;
    int	    r;
    char    c;
    char    *tmp;

    l = 2;
    r = 0;
    if (!(*line = malloc(1)))
	return (-1);
    **line = 0;
    while ((r = read(0, &c, 1)) > 0 && c != '\n')
    {
	if (!(tmp = malloc(l)))
	    return (-1);
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
