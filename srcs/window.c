#include "ft_select.h"

unsigned int	get_max_column(t_data *data)
{
  int tmp_win_x;

  tmp_win_x = data->win_x - data->max_length;
  return ((tmp_win_x / (data->max_length + 1) + 1));
}

void	get_winsize(t_data *data)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	data->win_y = w.ws_row;
	data->win_x = w.ws_col;
  if (!isatty(0))
    exit(1);
}

int   verif_win(t_data *data)
{
  if ((int)data->max_length > data->win_x * data->win_y - 1)
    return (0);
  return (1);
}

int   get_max_line(t_data *data)
{
	return ((data->win_y - 1) / 2 + ((data->win_y - 1) % 2));
	// 	return (data->win_y / 2);
	// return ((data->win_y / 2) - 1);
}

int   get_more_column(t_data *data)
{
  return ((data->ac / (data->max_column * data->max_line)));
}

void get_window_info(t_data *data)
{
  get_winsize(data);
  if ((data->win_ok = verif_win(data)))
  {
    data->max_column = get_max_column(data);
		data->max_line = get_max_line(data);
  }
}

void	sigwinch(int sig)
{
  t_data *data;
	// int		tmp;

  if (!isatty(0))
    exit(1);
	(void)sig;
  data = singleton_data(NULL, 0);
	// tmp = data->win_ok;

		exec_tcap("cl");
  get_window_info(data);
	if (data->win_ok)
	{
		// printf("GG\n");
		// exit(0);
			exec_tcap("cl");
			exec_tcap("ve");
			display_all(data);
	}
	else
	{
		display_fail(data);
	}
}
