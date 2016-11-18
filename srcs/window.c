/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:18:23 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 16:22:40 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static unsigned int	get_max_column(t_data *data)
{
	int		tmp_win_x;

	tmp_win_x = data->win_x - data->max_length;
	if (tmp_win_x <= 0)
		return (1);
	return ((tmp_win_x / (data->max_length + 1) + 1));
}

static void			get_winsize(t_data *data)
{
	struct winsize	w;

	if (!isatty(0))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	data->win_y = w.ws_row;
	data->win_x = w.ws_col;
}

static int			verif_win(t_data *data)
{
	if (data->help && (data->win_x < 20 || data->win_y < 6))
		return (0);
	else if ((int)data->max_length > data->win_x * data->win_y - 1)
		return (0);
	else if (data->search && data->to_found
			&& data->win_x < 14 + (int)ft_strlen(data->to_found))
		return (0);
	return (1);
}

static void			actualize_nb_line(t_data *data, t_elem *list)
{
	while (list)
	{
		list->nb_line = get_nb_line(data, list->length);
		list = list->next;
	}
}

void				get_window_info(t_data *data)
{
	get_winsize(data);
	if ((data->win_ok = verif_win(data)))
	{
		data->max_column = get_max_column(data);
		data->max_line = data->win_y - 1;
		actualize_nb_line(data, data->elem);
	}
}
