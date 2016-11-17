/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_other1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:07:58 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/17 17:25:14 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	search_elem(t_data *data)
{
	t_elem	*list;
	int		length;

	list = data->elem;
	length = (int)ft_strlen(data->to_found);
	while (list)
	{
		if (ft_strnequ(data->to_found, list->content, length))
		{
			data->current->current = 0;
			data->current = list;
			data->current->current = 1;
			free(data->to_found);
			data->to_found = NULL;
			return ;
		}
		list = list->next;
	}
	free(data->to_found);
	data->to_found = NULL;
}

void		exec_key_return(t_data *data)
{
	if (data->search)
	{
		search_elem(data);
		data->search = 0;
	}
	else if (data->help)
		data->help = 0;
	else
		quit_prog(data, 1);
}

void		exec_key_space(t_data *data)
{
	if (data->current->pick == 0)
		data->current->pick = 1;
	else
		data->current->pick = 0;
	data->current->current = 0;
	data->current = (data->current->next) ? data->current->next : data->elem;
	data->current->current = 1;
}

void		exec_key_help(t_data *data)
{
	if (data->help)
		data->help = 0;
	else
	{
		data->help = 1;
		display_help(data);
	}
}

void		exec_key_search(t_data *data)
{
	if (!data->search)
		data->to_found = ft_strdup("");
	data->search = 1;
}
