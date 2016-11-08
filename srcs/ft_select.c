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
	if (singleton_termios(init_term(env), 1) == NULL)
	{
		ft_putstr_fd("Can't find terminal definition. Exiting now.\n", 2);
		return (0);
	}
	ft_bzero(data, sizeof(t_data));

	// signal_handler();

	signal(SIGWINCH, sigwinch);
	singleton_data(data, 1);
	data->ac = ac;
	init_elem(data, av);
	get_window_info(data);
	return (1);
}

void print_pick(t_elem *list)
{
	if (list)
	{
		if (list->pick == 1)
			ft_putstr(list->content);
		list = list->next;
	}
	while (list)
	{
		if (list->pick == 1)
		{
			ft_putchar(' ');
			ft_putstr(list->content);
		}
		list = list->next;
	}
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

void handle_boucle(t_data *data, char buf[11])
{
	int		i;
	t_elem		*elem;

	i = 0;
	elem = data->current;
	if (buf[0] == 27 && buf[1] == 0)
	{
		quit_prog(data, 0);
	}
	else if (buf[0] == 10 && buf[1] == 0)
	{
		quit_prog(data, 1);
	}
	else if (buf[0] == 127 && buf[1] == 0)
	{
		// DELETE
		delete_button(data, data->current);
		// elem = data->elem;
		// elem->current = 1;
	}
	else if (buf[0] == 32 && buf[1] == 0)
	{ // ESPACE
		if (data->current->pick == 0)
			data->current->pick = 1;
		else
			data->current->pick = 0;
		data->current->current = 0;
		data->current = (data->current->next) ? (data->current->next) : (data->elem);
		data->current->current = 1;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
	{ // GAUCHE
		elem->current = 0;
		if (elem->prec)
			elem = elem->prec;
		else
			elem = data->last;
		elem->current = 1;
		data->current = elem;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && buf[3] == 0)
	{ // DROITE
		elem->current = 0;
		if (elem->next)
			elem = elem->next;
		else
			elem = data->elem;
		elem->current = 1;
		data->current = elem;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0)
	{ // HAUT
		elem->current = 0;
		while (i < data->max_column && data->more_one_line)
		{
			if (elem->prec)
				elem = elem->prec;
			else
			{
				// i = data->max_column - i;
				elem = data->last;
			}
			i++;
		}
		elem->current = 1;
		data->current = elem;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0)
	{ // BAS
		elem->current = 0;
		while (i < data->max_column && data->more_one_line)
		{
			if (elem->next)
				elem = elem->next;
			else
				elem = data->elem;
			i++;
		}
		elem->current = 1;
		data->current = elem;
	}
}

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
			if (buf[0] == 104)
				print_data(data);
			else
			{
				handle_boucle(data, buf);
				display_all(data);
				// printf("123456789012ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
				// printf("Touche = [%d][%d][%d][%d][%d][%d][%d][%d]\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
				ft_bzero(buf, 11);
			}
		}
	}
	free(singleton_termios(NULL, 0));
}

int	main(int ac, char **av, char **env) {
	t_data	data;

	if (ac > 1)
	{
		if (!init_select(&data, av, env, ac))
			return (0);
		// print_elem(data.elem);
		// print_data(&data);

		// printf("123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012\n");

		// printf("Content begin by prec  = [%s]\n", data.elem->next->prec->content);
		// display_all(av, &data);
		boucle(&data);
	}
	return (1);
}
