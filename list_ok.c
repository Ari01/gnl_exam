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

t_list	*new_list(char *content)
{
    t_list  *new;

    new = malloc(sizeof(*new));
    new->content = content;
    new->next = NULL;
    return (new);
}

void	list_clear(t_list **list)
{
    t_list  *ite;

    while (*list)
    {
	ite = (*list)->next;
	free((*list)->content);
	free(*list);
	*list = ite;
    }
}

t_list	*push_back(t_list *list, char *content)
{
    t_list  *ite;

    ite = list;
    if (!list)
	return (new_list(content));
    while (ite->next)
	ite = ite->next;
    ite->next = new_list(content);
    return (list);
}

int	find_char(t_list *list, char c)
{
    while (list)
    {
	if (ft_strchr(list->content, c))
	    return (1);
	list = list->next;
    }
    return (0);
}

int	get_len(t_list *list)
{
    int	    len;
    int	    i;

    len = 0;
    while (list)
    {
	i = 0;
	while (list->content[i] && list->content[i] != '\n')
	    i++;
	len += i;
	if (list->content[i] == '\n')
	    return (len);
	list = list->next;
    }
    return (len);
}

int	read_file(t_list **list)
{
    char    buffer[129];
    int	    ret;

    while ((ret = read(0, buffer, 128)) > 0)
    {
	buffer[ret] = 0;
	*list = push_back(*list, ft_strdup(buffer));
	if (ft_strchr(buffer, '\n'))
	    return (1);
    }
    return (ret);
}

int	read_buff(t_list **list, char **line)
{
    int	    len;
    int	    i;
    int	    j;
    t_list  *tmp;

    len = get_len(*list);
    *line = malloc(sizeof(**line) * (len + 1));
    i = 0;
    while (*list)
    {
	j = 0;
	while ((*list)->content[j] && (*list)->content[j] != '\n')
	{
	    (*line)[i] = (*list)->content[j];
	    i++;
	    j++;
	}
	(*line)[i] = 0;
	if ((*list)->content[j] == '\n')
	{
	    j++;
	    i = 0;
	    while ((*list)->content[j])
	    {
		(*list)->content[i] = (*list)->content[j];
		i++;
		j++;
	    }
	    (*list)->content[i] = 0;
	    return (1);
	}
	else
	{
	    tmp = (*list)->next;
	    free((*list)->content);
	    free(*list);
	    *list = tmp;
	}
    }
    return (1);
}

int	get_next_line(char **line)
{
    static t_list   *buff;
    int		    ret;

    if (!buff || !find_char(buff, '\n'))
    {
	ret = read_file(&buff);
	if (ret < 0)
	{
	    list_clear(&buff);
	    return (-1);
	}
    }
    read_buff(&buff, line);
    if (!buff || !find_char(buff, '\n'))
    {
	ret = read_file(&buff);
	if (ret < 0)
	{
	    list_clear(&buff);
	    return (-1);
	}
    }
    return (!!buff);
}
