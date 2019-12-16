/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/16 18:44:03 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_debug_galery(t_map *galery);
void	ft_debug_room(t_room *room, int mode);
void	ft_debug_single_path(int *path, size_t len);
void	ft_mult_bfs(t_map *galery, int **adj_mat);
void	ft_debug_rooms(t_room **rooms, size_t size, int mode);

int	main(void)
{
	t_map	*data;

	if ((data = parser()) == NULL)
		return (FALSE);
	data->start->features = IS_START;
	ft_mult_bfs(data, data->adj_mat);
	print_info(data);
	free_all(data);
	return (0);
}
