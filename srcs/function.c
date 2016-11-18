/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:18:10 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 16:20:24 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_elem		*get_last_elem(t_elem *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

int			get_nb_line(t_data *data, size_t length)
{
	if ((int)(length % data->win_x) == 0)
		return ((int)length / data->win_x + 1);
	return (((int)length / data->win_x) + 2);
}

void		print_pick(t_elem *list)
{
	int		found;

	found = 0;
	while (list)
	{
		if (list->pick == 1)
		{
			if (found)
				ft_putchar(' ');
			else
				found = 1;
			ft_putstr(list->content);
		}
		list = list->next;
	}
	if (found)
		ft_putchar('\n');
}

void		free_data(t_data *data)
{
	if (data->to_found)
		free(data->to_found);
	if (data->name_term)
		free(data->name_term);
}

void		quit_prog(t_data *data, int result)
{
	invert_term();
	if (result == 1)
		print_pick(data->elem);
	free_data(data);
	exit(0);
}
