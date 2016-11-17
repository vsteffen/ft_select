/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_down.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 15:58:12 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/17 17:23:58 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		small_penis_down(int limit, int i, t_data *data)
{
	int		ret;

	ret = 1;
	limit = ((limit + 1) > data->max_column) ? 1 : limit + 1;
	while (ret < limit)
	{
		ret++;
	}
	return (i + ret);
}

static void		init_true_down(int var[3], t_elem *elem)
{
	var[0] = 0;
	var[1] = 1;
	while (elem->next)
	{
		elem = elem->next;
		var[0]++;
	}
}

static t_elem	*ret_true_down(int var[3], t_elem *elem, t_data *data)
{
	var[0] = 0;
	while (var[0] < var[1])
	{
		if (elem->next)
			elem = elem->next;
		else
			elem = data->elem;
		var[0]++;
	}
	return (elem);
}

static t_elem	*get_true_down(t_data *data, t_elem *elem)
{
	t_elem	*tmp;
	int		v[3];

	init_true_down(v, elem);
	if (v[0] < data->max_column)
	{
		tmp = elem;
		while (tmp->prec)
		{
			tmp = tmp->prec;
			v[1]++;
		}
		v[2] = (data->max_column - v[0]) + ((v[0] + v[1]) % data->max_column);
		if (v[2] > data->max_column)
			v[2] = v[2] % data->max_column;
		v[1] = small_penis_down(v[2], v[0], data);
	}
	else
		v[1] = data->max_column;
	return (ret_true_down(v, elem, data));
}

void			exec_key_down(t_data *data, t_elem *elem)
{
	elem->current = 0;
	elem = get_true_down(data, elem);
	elem->current = 1;
	data->current = elem;
}
