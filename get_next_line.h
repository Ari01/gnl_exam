#include <unistd.h>
#include <stdlib.h>

typedef struct	s_list
{
    char	    *content;
    struct s_list   *next;
}		t_list;

int	get_next_line(char **line);
