
#include "ft_select.h"

void quit_prog(t_data *data, int result)
{
	exec_tcap("cl");
	if (result == 1)
		print_pick(data->elem);
	signal_end(0);
}

void	signal_end(int sig)
{
	invert_term();
	free(singleton_termios(NULL, 0));
  // ft_putstr("Je suis un singleton qui rage quit\n");
	exit(sig);
}

void	signal_handler(void)
{
	int	i;

	i = 1;
	while (i < 28)
	{
		if (i != SIGTTIN && i != SIGINFO && i != SIGWINCH && i != SIGURG
			&& i != SIGIO && i != SIGCHLD && i != SIGCONT)
			signal(i, signal_end);
		i++;
	}
}
