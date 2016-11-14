
#include "ft_select.h"

void free_data(t_data *data)
{
	// (void)data;
	if (data->to_found)
		free(data->to_found);
	if (data->name_term)
		free(data->name_term);
	// free(data);
}

void quit_prog(t_data *data, int result)
{
	invert_term();
	if (result == 1)
		print_pick(data->elem);
	free_data(data);
	exit(0);
}

void	signal_end(int sig)
{
	invert_term();
	free_data(singleton_data(NULL, 0));
	exit(sig);
}

void	signal_stop(int sig)
{
	// //free(singleton_termios(NULL, 0));
	// sleep(20);
	invert_term();
	(void)sig;
	// printf("ARNAQUE MALGACHE\n");
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
	// //free(singleton_termios(NULL, 0));
}

void	signal_cont(int sig)
{
	t_data *data;

	exec_tcap("vi");
	exec_tcap("ti");
	exec_tcap("cl");
	// printf("PUTAIN DE MERDE\n");
	signal(SIGTSTP, signal_stop);
	data = singleton_data(NULL, 0);
	if (singleton_termios(init_term(NULL, data->name_term), 1) == NULL)
	{
		ft_putstr_fd("Can't find terminal definition. Exiting now.\n", 2);
		exit(1);
	}
	// exec_tcap("is");
	if (singleton_termios(NULL, 0))
		printf("J'EXISTE LOL\n");
	else
		printf("FML LOOOOOL\n");
	// sleep(5);
	get_window_info(data);
	if (!data->win_ok)
		display_fail(data);
	else if (data->help)
		display_help(data);
	else
		display_all(data);
		// display_all(data);
	// t_termios *term = singleton_termios(NULL, 0);
	// (void)term;
	(void)sig;
}

void	signal_handler(void)
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
