/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 18:52:35 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 19:31:18 by vsteffen         ###   ########.fr       */
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
# include <sys/stat.h>

typedef struct termios	t_termios;

typedef struct stat		t_stat;

typedef struct		s_elem {
	char			*content;
	size_t			length;
	int				current;
	int				pick;
	int				column;
	int				nb_line;
	int				color;
	struct s_elem	*prec;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_data {
	size_t			max_length;
	int				max_column;
	int				max_line;
	int				real_max_line;
	int				win_ok;
	int				help;
	int				search;
	char			*to_found;
	t_elem			*elem;
	t_elem			*current;
	t_elem			*last;
	int				win_y;
	int				win_x;
	int				ac;
	char			*name_term;
}					t_data;

t_termios			*init_term(char **env, char *name);
char				*get_term_name(char **env, char *name);
t_termios			*singleton_termios(t_termios *termios, int i);
void				invert_term(void);
void				exec_tcap(char *tcap);
void				signal_end(int sig);
void				signal_handler(void);
void				sigwinch(int sig);
void				get_window_info(t_data *data);
void				init_elem(t_data *data, char **av);
int					get_nb_line(t_data *data, size_t length);
t_elem				*get_last_elem(t_elem *list);
t_data				*singleton_data(t_data *data, int i);
void				display_fail(t_data *data);
void				display_all(t_data *data);
void				display_content(t_elem *elem, t_data *data, t_elem *list);
void				display_bottom(t_data *data, int line_used);
int					my_putchar(int c);
void				my_putstr(char *str);
void				display_help();
void				print_pick(t_elem *list);
void				quit_prog(t_data *data, int result);
void				free_data(t_data *data);
void				exec_key_up(t_data *data, t_elem *elem);
void				exec_key_down(t_data *data, t_elem *elem);
void				exec_key_return(t_data *data);
void				exec_key_delete(t_data *data);
void				exec_key_space(t_data *data);
void				exec_key_help(t_data *data);
void				exec_key_search(t_data *data);
void				exec_key_left(t_data *data, t_elem *elem);
void				exec_key_right(t_data *data, t_elem *elem);
void				exec_arrow_key(char buf[11], t_data *data, t_elem *elem);
#endif
