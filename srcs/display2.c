/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:33:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 15:40:16 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	choose_style(t_elem *elem)
{
	if (elem->current == 1)
		exec_tcap("us");
	if (elem->pick == 1)
		exec_tcap("mr");
}

static void	put_color(t_elem *elem)
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

void		display_content(t_elem *elem, t_data *data, t_elem *list)
{
	size_t	i;

	choose_style(list);
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

void		display_help(t_data *data)
{
	if (data->win_x <= 24 || data->win_y < 6)
		display_fail(data);
	exec_tcap("cl");
	my_putstr("Move : arrow keys\n");
	my_putstr("Select : space key\n");
	my_putstr("Valid : return key\n");
	my_putstr("Delete : delete key\n");
	my_putstr("Search : R key\n");
	my_putstr("Quit : echap key");
	my_putstr(data->current->content);
	display_bottom(data, 6);
}

void		display_bottom(t_data *data, int line_used)
{
	while (line_used <= data->win_y)
	{
		my_putstr("\n");
		line_used++;
	}
	if (data->help && data->win_x >= 14)
		my_putstr("Press H or DEL");
	else if (data->search && data->to_found
			&& data->win_x >= 14 + (int)ft_strlen(data->to_found))
	{
		my_putstr("Key to find : ");
		my_putstr(data->to_found);
	}
	else if (data->win_x >= 19)
		my_putstr("Push on H for help");
}
