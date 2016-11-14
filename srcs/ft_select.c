/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 18:52:23 by vsteffen          #+#    #+#             */
/*   Updated: 2016/10/27 18:52:26 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		get_nb_line(t_data *data, size_t length)
{
	// printf("data->win_x = %d\n", data->win_x);
	if ((int)(length % data->win_x) == 0)
		return ((int)length / data->win_x + 1);
	return (((int)length / data->win_x) + 2);
}

t_elem	*get_last_elem(t_elem *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	init_elem(t_data *data, char **av)
{
	unsigned int	i;
	size_t				length_tmp;
	size_t				length;

	i = 1;
	length_tmp = 0;
	length = 0;
	get_winsize(data);
	while (av[i])
	{
		if ((length = ft_strlen(av[i])) > length_tmp)
			length_tmp = length;
		data->elem = add_elem(data->elem, create_elem(ft_strdup(av[i]), data, length));
		i++;
	}
	data->elem->current = 1;
	data->last = get_last_elem(data->elem);
	data->current = data->elem;
	data->max_length = length_tmp;
}

void print_elem(t_elem *elem)
{
	unsigned int	i;

	i = 1;
	while (elem)
	{
		printf("Id: %d\n", i);
		printf("Content: %s\n", elem->content);
		printf("Pick: %d\n", elem->pick);
		printf("Nb_line: %d\n", elem->nb_line);
		printf("\n");
		i++;
		elem = elem->next;
	}
}

void print_data(t_data *data)
{
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("max_length vaut %zu\n", data->max_length);
	printf("max_column vaut %d\n", data->max_column);
	printf("max_line vaut %d\n", data->max_line);
	printf("win_ok vaut %d\n", data->win_ok);
	printf("win_x %d\n", data->win_x);
	printf("win_y vaut %d\n", data->win_y);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

int init_select(t_data *data, char **av, char **env, int ac)
{
	// data->env = env;
	if (singleton_termios(init_term(env, NULL), 1) == NULL)
	{
		ft_putstr_fd("Can't find terminal definition. Exiting now.\n", 2);
		return (0);
	}
	ft_bzero(data, sizeof(t_data));
	data->name_term = get_term_name(env, NULL);
	signal_handler();
	singleton_data(data, 1);
	data->ac = ac;
	init_elem(data, av);
	get_window_info(data);
	exec_tcap("vi");
	exec_tcap("ti");
	return (1);
}

void print_pick(t_elem *list)
{
	int		found;

	found = 0;
	while (list)
	{
		if (list->pick == 1)
		{
			if (found)
				ft_putchar(' ');
			else
				found = 1;
			ft_putstr(list->content);
		}
		list = list->next;
	}
	if (found)
		ft_putchar('\n');
}

void free_elem(t_elem *elem)
{
	free(elem->content);
	free(elem);
}


void delete_button(t_data *data, t_elem *delem)
{
	t_elem	*prec;
	t_elem	*next;

	prec = delem->prec;
	next = delem->next;
	if (!next && !prec)
	{
		free_elem(delem);
		quit_prog(data, 0);
	}
	if (&delem->content == &data->elem->content)
		data->elem = (next) ? next : prec;
	if (&delem == &data->last)
		data->elem = (prec) ? prec : next;
	// printf("Le dernier vaut [%s]\n", data->last->content);
	free_elem(delem);
	if (prec)
	{
		prec->next = next;
		data->current = prec;
		prec->current = 1;
	}
	if (next)
	{
		next->prec = prec;
		if (!prec)
		{
			data->current = next;
			next->current = 1;
		}
	}
}

void search_elem(t_data *data)
{
	t_elem	*list;
	int			length;

	list = data->elem;
	length = (int)ft_strlen(data->to_found);
	while (list)
	{
		if (ft_strnequ(data->to_found, list->content, length))
		{
			data->current->current = 0;
			data->current = list;
			data->current->current = 1;
			free(data->to_found);
			data->to_found = NULL;
			return ;
		}
		list = list->next;
	}
	free(data->to_found);
	data->to_found = NULL;
}

void delete_search(t_data *data)
{
	char	*ptr;

	if (!data->to_found[0])
	{
		free(data->to_found);
		data->to_found = NULL;
		data->search = 0;
	}
	else
	{
		ptr = data->to_found;
		data->to_found[ft_strlen(data->to_found) - 1] = '\0';
		data->to_found = ft_strdup(data->to_found);
		free(ptr);
	}
}

int		small_penis_up(int x, int i, t_data *data)
{
	int		beg;
	int		ret;
	int		limit;

	beg = (x) ? x : data->max_column;
	ret = 0;
	limit = ((i - 1) == 0) ? data->max_column : i - 1;
	while (beg != limit)
	{
		if (beg == 1)
			beg = data->max_column;
		else
			beg--;
		ret++;
	}
	return (i + ret);
}

t_elem	*get_true_up(t_data *data, t_elem *elem)
{
	t_elem	*tmp;
	int			i;
	int			k;
	int			x;

	i = 1;
	k = 0;
	tmp = elem;
	while (tmp->prec)
	{
		tmp = tmp->prec;
		i++;
	}
	if (i <= data->max_column)
	{
		tmp = elem;
		while (tmp->next)
		{
			tmp = tmp->next;
			k++;
		}
		x = (i + k) % data->max_column;
		k = small_penis_up(x, i, data);
	}
	else
		k = data->max_column;
	i = 0;
	while (i < k)
	{
		if (elem->prec)
			elem = elem->prec;
		else
			elem = data->last;
		i++;
	}
	return (elem);
}

int		small_penis_down(int limit, int i, t_data *data)
{
	int		ret;

	ret = 1;
	limit = ((limit + 1) > data->max_column) ? 1 : limit + 1;
	while (ret < limit)
	{
		ret++;
	}
	return (i + ret);
}

t_elem	*get_true_down(t_data *data, t_elem *elem)
{
	t_elem	*tmp;
	int			i;
	int			k;
	int			x;

	i = 0;
	k = 1;
	tmp = elem;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < data->max_column)
	{
		tmp = elem;
		while (tmp->prec)
		{
			tmp = tmp->prec;
			k++;
		}
		x = (data->max_column - i) + ((i + k) % data->max_column);
		if (x > data->max_column)
			x = x % data->max_column;
		k = small_penis_down(x, i, data);
	}
	else
		k = data->max_column;
	i = 0;
	while (i < k)
	{
		if (elem->next)
			elem = elem->next;
		else
			elem = data->elem;
		i++;
	}
	return (elem);
}

void handle_boucle(t_data *data, char buf[11])
{
	int		i;
	t_elem		*elem;
	char			*ptr;

	i = 0;
	elem = data->current;
	if (buf[0] == 27 && buf[1] == 0)
	{
		quit_prog(data, 0);
	}
	else if (buf[0] == 10 && buf[1] == 0)
	{
		if (data->search)
		{
			search_elem(data);
			data->search = 0;
		}
		else if (data->help)
			data->help = 0;
		else
			quit_prog(data, 1);
	}
	else if (buf[0] == 127 && buf[1] == 0)
	{
		// DELETE
		if (data->search)
		{
			delete_search(data);
		}
		else if (data->help)
			data->help = 0;
		else
			delete_button(data, data->current);
		// elem = data->elem;
		// elem->current = 1;
	}
	else if (buf[0] == 104 && buf[1] == 0 && !data->search)
	{
		if (data->help)
			data->help = 0;
		else
		{
			data->help = 1;
			display_help(data);
		}
			// display_help();
	}
	else if (buf[0] == 18 && buf[1] == 0 && !data->help)
	{
		if (!data->search)
			data->to_found = ft_strdup("");
		data->search = 1;
	}
	else if (buf[0] == 32 && buf[1] == 0 && !data->search)
	{ // ESPACE
		if (data->current->pick == 0)
			data->current->pick = 1;
		else
			data->current->pick = 0;
		data->current->current = 0;
		data->current = (data->current->next) ? (data->current->next) : (data->elem);
		data->current->current = 1;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0 && !data->search)
	{ // GAUCHE
		// if (1 < elem->column)
		// {
			elem->current = 0;
			if (elem->prec)
				elem = elem->prec;
			else
				elem = data->last;
			elem->current = 1;
			data->current = elem;
		// }
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && buf[3] == 0 && !data->search)
	{ // DROITE
		// if (elem->column < data->max_column)
		// {
			elem->current = 0;
			if (elem->next)
				elem = elem->next;
			else
				elem = data->elem;
			elem->current = 1;
			data->current = elem;
		// }
		// else
		// {
		// 	printf("Max_line = %d\n", data->max_line);
		// }
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0 && !data->search)
	{ // HAUT
		elem->current = 0;
		elem = get_true_up(data, elem);
		elem->current = 1;
		data->current = elem;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0 && !data->search)
	{ // BAS
		elem->current = 0;
		elem = get_true_down(data, elem);
		elem->current = 1;
		data->current = elem;
	}
	else if (data->search && buf[1] == 0)
	{
		ptr = data->to_found;
		data->to_found = ft_strjoin(data->to_found, &buf[0]);
		free(ptr);
	}
}

// int	get_real_max_line(t_data *data)
// {
// 	int	line_used;
// 	t_elem *list;
//
// 	list = data->elem;
// 		if (!list->next || line_used + list->next->nb_line - 1 > data->max_line)
// 		{
// 			// printf("HAHA = %d > %d\n", line_used + list->next->nb_line - 1, data->max_line);
// 			return (0);
// 		}
// 		line_used += list->next->nb_line;
// 		return (1);
// }

void boucle(t_data *data)
{
	char	buf[11];
	int		r;

	ft_bzero(buf, 11);
	display_all(data);
	if (!data->win_ok)
		display_fail(data);
	while ((r = read(0, buf, 10)))
	{
		if (!data->win_ok)
			display_fail(data);
		else
		{
			if (data->help && !((buf[0] == 104 || buf[0] == 127 || buf[0] == 27) && buf[1] == 0))
				display_help(data);
			else
			{
				handle_boucle(data, buf);
				if (!data->help)
					display_all(data);
			}
				// printf("123456789012ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
				// printf("Touche = [%d][%d][%d][%d][%d][%d][%d][%d]\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
			ft_bzero(buf, 11);
			data->win_ok = verif_win(data);
		}
	}
	// free(singleton_termios(NULL, 0));
}

int	main(int ac, char **av, char **env) {
	t_data	data;

	if (ac > 1)
	{
		if (!init_select(&data, av, env, ac))
			return (1);
		// print_elem(data.elem);
		// print_data(&data);

		// printf("123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012\n");

		// printf("Content begin by prec  = [%s]\n", data.elem->next->prec->content);
		// display_all(av, &data);
		boucle(&data);
	}
	return (1);
}
