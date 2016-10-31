#include "ft_select.h"

t_elem	*create_elem(char *content, t_data *data, int nb_line)
{
	t_elem	*elem;

  (void)data;
	elem = mallocp(sizeof(t_elem));
	elem->content = content;
	elem->pick = 0;
	elem->nb_line = nb_line;
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
