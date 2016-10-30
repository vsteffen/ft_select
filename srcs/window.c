#include "ft_select.h"

unsigned int	get_max_column(t_data *data)
{
  int ret;
  int tmp_win_y;

  if (data->jump_x > 1)
    return (1);
  tmp_win_y = data->win_x - data->max_length;
  return ((tmp_win_y / (data->max_length + 1) + 1);
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

int   get_jump_x(t_data *data)
{
  if (data->max_length > data->win_x * data->win_y)
    return (0);
  else if (data->max_length > data->win_y)
  {
    if (data->max_length % data->win_y) == 0)
      return (data->max_length / data->win_y);
    return ((data->max_length / data->win_y) + 1)
  }
  return (1);
}

int   get_max_line(t_data *data)
{
  return (data->win_x / data->jump_x);
}

int   get_more_column(t_data *data)
{
  return ((data->ac / (data->max_column * data->max_line)));
}

void get_window_info(t_data *data)
{
  get_winsize(t_data *data);
  //get_max_length(data);
  if ((data->jump_x = get_jump_x(data)))
  {
    data->max_line = get_max_line(data);
    data->max_column = get_max_column(data);
    data->more_column = get_more_column(data);
  }
  // -----> on calcule le nombre de ligne TOTAL utilisé pour lla lecture de gauche a droite

}

void	sigwinch(int sig)
{
  t_data *data;

  if (!isatty(0))
    exit(1);
  data = singleton_data(NULL, 0);
  get_window_info(data);
}
