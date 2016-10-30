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

typedef struct termios	t_termios;

typedef struct      s_elem {
  char        *content;
  int         pick;
  struct s_elem   *prec;
  struct s_elem   *next;
}           t_elem;

typedef struct			s_data {
              size_t  max_length;
              int     max_column;
              t_elem  *elem;
              int     win_y;
              int     win_x;
}						t_data;

t_termios	*init_term(char **env);
t_termios	*singleton_termios(t_termios *termios, int i);
void		invert_term(void);
void		exec_tcap(char *tcap);
void	signal_end(int sig);
void	signal_handler(void);
t_elem	*create_elem(char *content, t_data *data);
t_elem	*add_elem(t_elem *list, t_elem *elem);

void print_elem(t_elem *elem);

#endif
