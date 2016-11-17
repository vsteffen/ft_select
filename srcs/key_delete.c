/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:52:51 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/17 17:23:05 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	delete_search(t_data *data)
{
	char	*ptr;

	if (!data->to_found[0])
	{
		free(data->to_found);
		data->to_found = NULL;
		data->search = 0;
	}
	else
	{
		ptr = data->to_found;
		data->to_found[ft_strlen(data->to_found) - 1] = '\0';
		data->to_found = ft_strdup(data->to_found);
		free(ptr);
	}
}

static void	free_elem(t_elem *elem)
{
	free(elem->content);
	free(elem);
}

static void	get_delete_new_elem(t_data *data, t_elem *prec, t_elem *next)
{
	if (prec)
	{
		prec->next = next;
		data->current = prec;
		prec->current = 1;
	}
	if (next)
	{
		next->prec = prec;
		if (!prec)
		{
			data->current = next;
			next->current = 1;
		}
	}
}

void		delete_button(t_data *data, t_elem *delem)
{
	t_elem	*prec;
	t_elem	*next;

	prec = delem->prec;
	next = delem->next;
	if (!next && !prec)
	{
		free_elem(delem);
		quit_prog(data, 0);
	}
	if (&delem->content == &data->elem->content)
		data->elem = (next) ? next : prec;
	if (&delem->content == &data->last->content)
		data->last = (prec) ? prec : next;
	free_elem(delem);
	get_delete_new_elem(data, prec, next);
}

void		exec_key_delete(t_data *data)
{
	if (data->search)
		delete_search(data);
	else if (data->help)
		data->help = 0;
	else
		delete_button(data, data->current);
}
