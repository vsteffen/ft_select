/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:03:01 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 16:03:20 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			display_fail(t_data *data)
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
