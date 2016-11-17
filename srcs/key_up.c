/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:56:51 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/17 17:28:06 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		small_penis_up(int x, int i, t_data *data)
{
	int		beg;
	int		ret;
	int		limit;

	beg = (x) ? x : data->max_column;
	ret = 0;
	limit = ((i - 1) == 0) ? data->max_column : i - 1;
	while (beg != limit)
	{
		if (beg == 1)
			beg = data->max_column;
		else
			beg--;
		ret++;
	}
	return (i + ret);
}

static void		init_true_up(int var[3], t_elem *tmp)
{
	var[0] = 1;
	var[1] = 0;
	while (tmp->prec)
	{
		tmp = tmp->prec;
		var[0]++;
	}
}

static t_elem	*ret_true_up(int var[3], t_elem *elem, t_data *data)
{
	var[0] = 0;
	while (var[0] < var[1])
	{
		if (elem->prec)
			elem = elem->prec;
		else
			elem = data->last;
		var[0]++;
	}
	return (elem);
}

static t_elem	*get_true_up(t_data *data, t_elem *elem)
{
	t_elem	*tmp;
	int		var[3];

	init_true_up(var, elem);
	if (var[0] <= data->max_column)
	{
		tmp = elem;
		while (tmp->next)
		{
			tmp = tmp->next;
			var[1]++;
		}
		var[2] = (var[0] + var[1]) % data->max_column;
		var[1] = small_penis_up(var[2], var[0], data);
	}
	else
		var[1] = data->max_column;
	return (ret_true_up(var, elem, data));
}

void			exec_key_up(t_data *data, t_elem *elem)
{
	elem->current = 0;
	elem = get_true_up(data, elem);
	elem->current = 1;
	data->current = elem;
}
