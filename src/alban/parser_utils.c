/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:19:11 by aboitier          #+#    #+#             */
/*   Updated: 2020/01/30 17:22:36 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int			end_or_start(t_preparse *prep, t_room *stend, t_map *data)
{
	if (prep->s_or_e == 1)
	{
		if (data->start)
			return (FALSE);
		data->start = stend;
	}
	else if (prep->s_or_e == 2)
	{
		if (data->end)
			return (FALSE);
		data->end = stend;
	}
	prep->s_or_e = 0;
	return (TRUE);
}

int			valid_coords(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != ' ')
		i++;
	while (buffer[i] != '\n')
	{
		if (buffer[i] == '-' && buffer[i - 1] != ' ')
			return (FALSE);
		if (ft_isdigit(buffer[i]) == 0 && buffer[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
