#include "ft_select.h"

int		get_color(char *name)
{
	int		ret;
	t_stat		stat;
	// if ((fd = open(name, O_DIRECTORY)))
	// {
	// 	close(fd);
	// 	printf("LOL");
	// 	return (2);
	// }
	if ((ret = lstat(name, &stat)) != -1)
	{
		printf("File = [%s]\n", name);
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
	// if ((fd = open(name, O_SYMLINK, S_IXUSR | S_IXGRP | S_IXOTH)) != -1)
	// {
	// 	close(fd);
	// 	return (3);
	// }
	// if ((fd = open(name, O_SYMLINK)) != -1)
	// {
	// 	close(fd);
	// 	return (1);
	// }
	// else
	// 	return (0);
}

t_elem	*create_elem(char *content, t_data *data, size_t length)
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

t_elem	*add_elem(t_elem *list, t_elem *elem)
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
