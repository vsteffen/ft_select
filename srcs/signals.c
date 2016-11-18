/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:19:23 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 16:19:50 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		signal_end(int sig)
{
	invert_term();
	free_data(singleton_data(NULL, 0));
	exit(sig);
}

void		signal_stop(int sig)
{
	invert_term();
	(void)sig;
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void		signal_cont(int sig)
{
	t_data *data;

	exec_tcap("vi");
	exec_tcap("ti");
	exec_tcap("cl");
	signal(SIGTSTP, signal_stop);
	data = singleton_data(NULL, 0);
	if (singleton_termios(init_term(NULL, data->name_term), 1) == NULL)
	{
		ft_putstr_fd("Can't find terminal definition. Exiting now.\n", 2);
		exit(1);
	}
	get_window_info(data);
	if (!data->win_ok)
		display_fail(data);
	else if (data->help)
		display_help(data);
	else
		display_all(data);
	(void)sig;
}

void		signal_handler(void)
{
	int	i;

	i = 1;
	while (i < 28)
	{
		if (i != SIGTTIN && i != SIGINFO && i != SIGWINCH && i != SIGURG
				&& i != SIGIO && i != SIGCHLD && i != SIGCONT && i != SIGTSTP)
			signal(i, signal_end);
		i++;
	}
	signal(SIGTSTP, signal_stop);
	signal(SIGCONT, signal_cont);
	signal(SIGWINCH, sigwinch);
}

void		sigwinch(int sig)
{
	t_data *data;

	if (!isatty(0))
		exit(1);
	(void)sig;
	data = singleton_data(NULL, 0);
	get_window_info(data);
	if (!data->win_ok)
		display_fail(data);
	else if (data->help)
		display_help(data);
	else
		display_all(data);
}
