
#include "ft_select.h"

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
		if (i != SIGSTOP && i != SIGTTOU && i != SIGTSTP && i != SIGTTIN
			&& i != SIGWINCH && i != SIGINT && i != SIGURG
			&& i != SIGIO && i != SIGCHLD && i != SIGCONT)
			signal(i, signal_end);
		i++;
	}
}
