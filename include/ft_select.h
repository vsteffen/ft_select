/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 18:52:35 by vsteffen          #+#    #+#             */
/*   Updated: 2016/10/27 18:52:37 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <curses.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct termios	t_termios;

typedef struct      s_elem {
  char        *content;
  int         pick;
	int					nb_line;
  struct s_elem   *prec;
  struct s_elem   *next;
}           t_elem;

typedef struct			s_data {
              size_t  max_length;
              int     max_column;
							int			max_line;
              int     win_ok;
              t_elem  *elem;
              int     win_y;
              int     win_x;
							int			ac;
}						t_data;

t_termios	*init_term(char **env);
t_termios	*singleton_termios(t_termios *termios, int i);
void		invert_term(void);
void		exec_tcap(char *tcap);
void	signal_end(int sig);
void	signal_handler(void);
t_elem	*create_elem(char *content, t_data *data, int nb_line);
t_elem	*add_elem(t_elem *list, t_elem *elem);
void	sigwinch(int sig);
void	get_window_info(t_data *data);
void	get_winsize(t_data *data);
t_data		*singleton_data(t_data *data, int i);
void		display_fail(t_data *data);
void	display_all(t_data *data);

void print_elem(t_elem *elem);

#endif
