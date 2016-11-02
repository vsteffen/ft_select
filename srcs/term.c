
#include "ft_select.h"

char 		*get_term_name(char **env)
{
	unsigned int i;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ("TERM=", env[i], 5))
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

t_termios	*init_term(char **env)
{
	t_termios	term;
	t_termios	*ret;
	char		*name_term;

	ret = (t_termios*)mallocp(sizeof(t_termios));
	tcgetattr(0, &term);
	tcgetattr(0, ret);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (isatty(0) && tcsetattr(0, TCSADRAIN, &term) == -1)
		return (NULL);
	name_term = get_term_name(env);
	if (name_term == NULL)
		return (NULL);
	if (tgetent(NULL, name_term) == ERR)
	{
		free(name_term);
		free(ret);
		return (NULL);
	}
	free(name_term);
	return (ret);
}

void my_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		my_putchar(str[i]);
		i++;
	}
}

int			my_putchar(int c)
{
	static int	fd = 0;

	if (!fd)
		fd = open("/dev/tty", O_RDWR);
	if (!isatty(fd))
	{
		ft_putstr("/dev/tty is not a valid tty.\n");
		exit(EXIT_FAILURE);
	}
	if (c == -1)
	{
		close(fd);
		return (c);
	}
	write(fd, &c, 1);
	return (c);
}

void		exec_tcap(char *tcap)
{
	tputs(tgetstr(tcap, NULL), 1, my_putchar);
}

void		invert_term(void)
{
	t_termios	*tmp_terms;
	t_termios	*current;

	current = (t_termios *)mallocp(sizeof(t_termios));
	if (current && (tmp_terms = singleton_termios(NULL, 0)))
	{
		tcgetattr(0, current);
		if (isatty(0))
			tcsetattr(0, TCSADRAIN, tmp_terms);
		exec_tcap("ve");
		free(tmp_terms);
		singleton_termios(current, 1);
	}
}
