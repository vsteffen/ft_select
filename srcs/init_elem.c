#include "ft_select.h"

static int		get_color(char *name)
{
	int		ret;
	t_stat		stat;

	if ((ret = lstat(name, &stat)) != -1)
	{
		if (S_ISDIR(stat.st_mode))
			return (2);
		else if (stat.st_mode & S_IXUSR || stat.st_mode & S_IXGRP ||
				stat.st_mode & S_IXOTH)
				return (3);
		else
				return (1);
	}
	else
		return (0);
}

static t_elem	*create_elem(char *content, t_data *data, size_t length)
{
	t_elem	*elem;

  (void)data;
	elem = mallocp(sizeof(t_elem));
	elem->content = content;
	elem->length = length;
	elem->pick = 0;
	elem->nb_line = get_nb_line(data, length);
	elem->color = get_color(content);
	elem->prec = NULL;
	elem->next = NULL;
	return (elem);
}

static t_elem	*add_elem(t_elem *list, t_elem *elem)
{
	t_elem *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
  elem->prec = list;
	return (tmp);
}

void	init_elem(t_data *data, char **av)
{
	unsigned int	i;
	size_t				length_tmp;
	size_t				length;

	i = 1;
	length_tmp = 0;
	length = 0;
	get_winsize(data);
	while (av[i])
	{
		if ((length = ft_strlen(av[i])) > length_tmp)
			length_tmp = length;
		data->elem = add_elem(data->elem, create_elem(ft_strdup(av[i]), data, length));
		i++;
	}
	data->elem->current = 1;
	data->last = get_last_elem(data->elem);
	data->current = data->elem;
	data->max_length = length_tmp;
}
