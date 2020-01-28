/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 16:34:01 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(void)
{
	t_map	*data;
	int		**tab_path;
	int		i;

	i = 0;
	if ((data = parser()) == NULL)
	{
		ft_putstr("ERROR\n");
		return (FALSE);
	}
	ft_clean(data, data->adj_mat);
	data->start->features = IS_START;
	if ((tab_path = ft_mult_bfs(data, data->adj_mat)) == NULL)
	{
		ft_putstr("ERROR\n");
		return (0);
	}
	while (i < data->nb_rooms)
		data->rooms[i++]->features = EMPTY;
	ft_print(tab_path, data);
//	ft_free(data, tab_path);
	return (0);
}
