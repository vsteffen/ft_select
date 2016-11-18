/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:27:34 by vsteffen          #+#    #+#             */
/*   Updated: 2016/11/18 16:28:09 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_select.h"

char		*get_term_name(char **env, char *name)
{
	unsigned int i;

	if (name)
		return (ft_strdup(name));
	i = 0;
	while (env[i])
	{
		if (ft_strnequ("TERM=", env[i], 5))
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}
