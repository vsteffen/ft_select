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

size_t	search_max_length(char **av)
{
	unsigned int	i;
	size_t				ret;
	size_t				length;

	i = 0;
	ret =  0;
	length = 0;
	while (av[i])
	{
		if ((length = ft_strlen(av[i])) > ret)
			ret = length;
		i++;
	}
	return (ret);
}

void display_all(char **av, t_data *data)
{
	data->max_column = get_max_column(data);
}

void av_to_elem(t_data *data, char **av)
{
	unsigned int i;

	i = 1;
	while (av[i])
	{
			data->elem = add_elem(data->elem, create_elem(ft_strdup(av[i]), data));
			i++;
	}
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
		printf("\n");
		i++;
		elem = elem->next;
	}
}

int init_select(t_data *data, char **av, char **env, int ac)
{
	if (singleton_termios(init_term(env), 1) == NULL)
	{
		ft_putstr_fd("Can't find terminal definition. Exiting now.\n", 2);
		return (0);
	}
	ft_bzero(data, sizeof(t_data));
	av_to_elem(data, av);
	signal_handler();
	signal(SIGINT, sigint);
	signal(SIGWINCH, sigwinch);
	singleton_data(data, 1);
	data->ac = ac;
	data->max_length = search_max_length(av);
	return (1);
}

int	main(int ac, char **av, char **env) {
	char	buf[11];
	int		r;
	t_data	data;

	if (ac > 1)
	{
		if (!init_select(&data, av, env, ac))
			return (0);
		print_elem(data.elem);
		// printf("Content begin by prec  = [%s]\n", data.elem->next->prec->content);
		display_all(av, &data);
		ft_bzero(buf, 11);
		while ((r = read(0, buf, 10)))
		{
			ft_putchar(buf[0]);
			ft_bzero(buf, 11);
		}
		free(singleton_termios(NULL, 0));
	}
	return (1);
}
