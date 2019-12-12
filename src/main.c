/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/12 18:42:38 by pauljull         ###   ########.fr       */
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
//	t_map	colony;

	data = parser();
//	if (data != NULL)
//		print_info(data);
	data->start->features = IS_START;
	ft_bfs(data, data->adj_mat);
//	ft_mult_bfs(data, data->adj_mat);
	print_info(data);
//	if (data != NULL)
//		print_info(data);
//	if (ft_parsing(data, &colony) == FALSE)
//		perror("Error in input");
//	ft_lst_free(&data);
//	print_info();
	return (0);
}