#include "ft_select.h"

unsigned int	get_max_column(t_data *data)
{
  int ret;
  int tmp_win_x;

  tmp_win_x = data->win_x - data->max_length;
  if (tmp_win_x < 0)
    return (0);
  return ((tmp_win_x  / data->max_length + 1) + 1);
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
  if (data->max_length > data->win_x * data->win_y)
    return (0);
  else if (data->max_length > data->win_x)
    return (2);
  return (1);
}

void get_window_info(t_data *data)
{
  get_winsize(t_data *data);
  //get_max_length(data);
  if ((data->valid_win = verif_win(data)))
  {
    data->max_column = get_max_column(data);
  }

}

void	sigwinch(int sig)
{
  t_data *data;

  if (!isatty(0))
    exit(1);
  data = singleton_data(NULL, 0);
  get_window_info(data);
}
