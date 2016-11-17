/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_other2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 17:08:08 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/17 17:10:07 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		exec_key_left(t_data *data, t_elem *elem)
{
	elem->current = 0;
	if (elem->prec)
		elem = elem->prec;
	else
		elem = data->last;
	elem->current = 1;
	data->current = elem;
}

void		exec_key_right(t_data *data, t_elem *elem)
{
	elem->current = 0;
	if (elem->next)
		elem = elem->next;
	else
		elem = data->elem;
	elem->current = 1;
	data->current = elem;
}

void		exec_arrow_key(char buf[11], t_data *data, t_elem *elem)
{
	if (buf[2] == 68 && buf[3] == 0 && !data->search)
		exec_key_left(data, elem);
	else if (buf[2] == 67 && buf[3] == 0 && !data->search)
		exec_key_right(data, elem);
	else if (buf[2] == 65 && buf[3] == 0 && !data->search)
		exec_key_up(data, elem);
	else if (buf[2] == 66 && buf[3] == 0 && !data->search)
		exec_key_down(data, elem);
}
