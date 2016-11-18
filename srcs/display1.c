/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:42:41 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 15:44:00 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		verif_empty_line(int *line_used, t_data *data, t_elem *nxt_elem)
{
	if (!nxt_elem || *line_used + nxt_elem->nb_line - 1 > data->max_line)
		return (0);
	*line_used += nxt_elem->nb_line;
	return (1);
}

static t_elem	*init_if_new_page(int *line_used, t_elem *list,
	t_elem *beg_page)
{
	if (list->next)
	{
		*line_used = list->next->nb_line;
		return (list->next);
	}
	else
		return (beg_page);
}

static t_elem	*get_page_of_elem(t_data *data, t_elem *list)
{
	int			line_used;
	int			actual_column;
	int			end_page;
	t_elem		*beg_page;

	actual_column = 1;
	end_page = 0;
	line_used = list->nb_line;
	beg_page = list;
	while (list)
	{
		if (list->current == 1)
			return (beg_page);
		if (actual_column == data->max_column)
		{
			if (!verif_empty_line(&line_used, data, list->next))
				beg_page = init_if_new_page(&line_used, list, beg_page);
			actual_column = 1;
		}
		else
			actual_column++;
		list = list->next;
	}
	return (data->elem);
}

static int		verif_right_border(t_data *data, int *line_used,
		int *actual_column, t_elem *list)
{
	if (*actual_column == data->max_column)
	{
		if (verif_empty_line(line_used, data, list->next))
			my_putstr("\n\n");
		else
			return (0);
		*actual_column = 1;
	}
	else
	{
		exec_tcap("nd");
		(*actual_column)++;
	}
	return (1);
}

void			display_all(t_data *data)
{
	t_elem	*list;
	int		line_used;
	int		actual_column;
	int		end_page;

	actual_column = 1;
	end_page = 1;
	exec_tcap("cl");
	list = get_page_of_elem(data, data->elem);
	line_used = list->nb_line;
	while (list)
	{
		list->column = actual_column;
		display_content(list, data, list);
		exec_tcap("me");
		if (verif_right_border(data, &line_used, &actual_column, list))
			list = list->next;
		else
			list = NULL;
	}
	display_bottom(data, line_used);
}
