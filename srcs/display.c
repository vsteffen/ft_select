#include "ft_select.h"

void display_fail(t_data *data)
{
	int		pos;
	int		line;
	int		column;

	column = data->win_x / 2 - 3;
	line = data->win_y / 2;
	exec_tcap("cl");
	exec_tcap("vi");
	pos = 0;
	while (pos < line)
	{
		exec_tcap("do");
		pos++;
	}
	while (pos < column)
	{
		exec_tcap("nd");
		pos++;
	}
	pos = 0;
	my_putstr("RESIZE WIN PLS");
}

void choose_style(t_elem *elem)
{
	if (elem->current == 1)
	{
			exec_tcap("us");
	}
	if (elem->pick == 1)
	{
			exec_tcap("mr");
	}
	// if (elem->pick == 3)
	// {
	// 		exec_tcap("mr");
	// 		exec_tcap("us");
	// }
}

void put_color(t_elem *elem)
{
	if (elem->color == 2)
		my_putstr(FG_LCYAN);
	else if (elem->color == 3)
		my_putstr(FG_RED);
	else if (elem->color == 1)
		my_putstr(FG_WHITE);
	else
		my_putstr(FG_LGRAY);
}

void display_content(t_elem *elem, t_data *data)
{
	size_t	i;

	put_color(elem);
	my_putstr(elem->content);
	my_putstr(CS_RESET);
	i = elem->length;
	while (i < data->max_length)
	{
		exec_tcap("nd");
		i++;
	}
}

void display_bottom(t_data *data)
{
	(void)data;
	/* if (data->) */
}

int	verif_empty_line(int *line_used, t_data *data, t_elem *nxt_elem)
{
		if (!nxt_elem || *line_used + nxt_elem->nb_line - 1 > data->max_line)
		{
			// printf("HAHA = %d > %d\n", *line_used + nxt_elem->nb_line - 1, data->max_line);
			return (0);
		}
		*line_used += nxt_elem->nb_line;
		return (1);
}

t_elem	*get_page_of_elem(t_data *data)
{
	t_elem		*list;
	int				line_used;
	int				actual_column;
	int				end_page;
	t_elem		*beg_page;

	actual_column = 1;
	end_page = 0;
	list = data->elem;
 	line_used = list->nb_line;
	beg_page = list;
	while (list)
	{
		if (list->current == 1)
			return beg_page;
		if (actual_column == data->max_column)
		{
			if (!verif_empty_line(&line_used, data, list->next))
			{
				if (list->next)
				{
					line_used = list->next->nb_line;
					beg_page = list->next;
				}
			}
			actual_column = 1;
		}
		else
			actual_column++;
		list = list->next;
	}
	return (data->elem);
}

void display_all(t_data *data)
{
	t_elem		*list;
	int				line_used;
	int				actual_column;
	int				end_page;

	actual_column = 1;
	end_page = 1;
	data->more_one_line = 0;
	exec_tcap("cl");
	exec_tcap("ve");
	list = get_page_of_elem(data);
	// printf("Elem return = [%s]\n", list->content);
 	line_used = list->nb_line;
	while (list)
	{
		// if (list->current == 1)
		// 	end_page = 0;
		list->column = actual_column;
		choose_style(list);
		display_content(list, data);
		exec_tcap("me");
		// printf("data->max_column = [%d], [%d], [%d]\n", data->max_column, data->win_x, data->win_y);
		if (actual_column == data->max_column)
		{
			if (verif_empty_line(&line_used, data, list->next))
				my_putstr("\n\n");
			else
			{
				// printf("\n*-*-*-*-*-*-*-*-*\n");
				// printf("line_used = %d", line_used);
				// printf("\n*-*-*-*-*-*-*-*-*\n");
				// if (end_page)
				// {
					list = NULL;
					continue ;
				// }
			}
			if (list->next)
				data->more_one_line = 1;
			actual_column = 1;
		}
		else
		{
			exec_tcap("nd");
			actual_column++;
		}
		// line_used += list->nb_line;
		list = list->next;
		// if (data->max_column)
	}
	display_bottom(data);
}
