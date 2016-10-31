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
	printf("data->win_x = %d\n", data->win_x);
	if ((int)(length % data->win_x) == 0)
		return ((int)length / data->win_x);
	return (((int)length / data->win_x) + 1);
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
		data->elem = add_elem(data->elem, create_elem(ft_strdup(av[i]), data, get_nb_line(data, length)));
		i++;
	}
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

void display_fail(t_data *data)
{
	int		pos;
	int		line;
	int		column;

	column = data->win_x / 2 - 3;
	line = data->win_y / 2;
	exec_tcap("cl");
	exec_tcap("vi");
	pos = 0;
	while (pos < line)
	{
		exec_tcap("do");
		pos++;
	}
	while (pos < column)
	{
		exec_tcap("nd");
		pos++;
	}
	pos = 0;
	ft_putstr("RESIZE WIN PLS");
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
			// printf("123456789012ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
			ft_putchar(buf[0]);
			ft_bzero(buf, 11);
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
		print_elem(data.elem);
		print_data(&data);

		// printf("123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012 123456789012\n");

		// printf("Content begin by prec  = [%s]\n", data.elem->next->prec->content);
		// display_all(av, &data);
		boucle(&data);
	}
	return (1);
}
