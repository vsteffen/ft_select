/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 18:52:23 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/17 17:37:23 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	handle_boucle(t_data *data, char buf[11])
{
	t_elem		*elem;
	char		*ptr;

	elem = data->current;
	if (buf[0] == 27 && buf[1] == 0)
		quit_prog(data, 0);
	else if (buf[0] == 10 && buf[1] == 0)
		exec_key_return(data);
	else if (buf[0] == 127 && buf[1] == 0)
		exec_key_delete(data);
	else if (buf[0] == 104 && buf[1] == 0 && !data->search)
		exec_key_help(data);
	else if (buf[0] == 18 && buf[1] == 0 && !data->help)
		exec_key_search(data);
	else if (buf[0] == 32 && buf[1] == 0 && !data->search)
		exec_key_space(data);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] < 69 && buf[2] > 64)
		exec_arrow_key(buf, data, elem);
	else if (data->search && buf[1] == 0)
	{
		ptr = data->to_found;
		data->to_found = ft_strjoin(data->to_found, &buf[0]);
		free(ptr);
	}
}

static void	init_boucle(t_data *data, char buf[11])
{
	ft_bzero(buf, 11);
	if (!data->win_ok)
		display_fail(data);
	else
		display_all(data);
}

void		boucle(t_data *data)
{
	char	buf[11];
	int		r;

	init_boucle(data, buf);
	while ((r = read(0, buf, 10)))
	{
		if (!data->win_ok)
			display_fail(data);
		else
		{
			if (data->help && !((buf[0] == 104 || buf[0] == 127 || buf[0] == 27)
						&& buf[1] == 0))
				display_help(data);
			else
			{
				handle_boucle(data, buf);
				if (!data->help)
					display_all(data);
			}
			ft_bzero(buf, 11);
			data->win_ok = verif_win(data);
		}
	}
	ft_putstr_fd("Error while reading stdin. Exiting now\n", 2);
	exit(1);
}

static int	init_select(t_data *data, char **av, char **env, int ac)
{
	if (singleton_termios(init_term(env, NULL), 1) == NULL)
	{
		ft_putstr_fd("Can't find terminal definition. Exiting now.\n", 2);
		return (0);
	}
	ft_bzero(data, sizeof(t_data));
	data->name_term = get_term_name(env, NULL);
	signal_handler();
	singleton_data(data, 1);
	data->ac = ac;
	init_elem(data, av);
	get_window_info(data);
	exec_tcap("vi");
	exec_tcap("ti");
	return (1);
}

int			main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac > 1)
	{
		if (!init_select(&data, av, env, ac))
			return (1);
		boucle(&data);
	}
	return (1);
}
