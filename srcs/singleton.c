
#include "ft_select.h"

t_termios	*singleton_termios(t_termios *termios, int i)
{
	static t_termios *singleton = NULL;

	if (i)
		singleton = termios;
	return (singleton);
}

t_data		*singleton_data(t_data *data, int i)
{
	static t_data *singleton = NULL;

	if (i)
		singleton = data;
	return (singleton);
}
