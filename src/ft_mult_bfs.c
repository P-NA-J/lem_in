/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/12 13:02:43 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_debug_single_path(int *path, size_t len);

void	ft_mult_bfs(t_map *galery, int **adj_mat)
{
	int	*path;

	while ((path = ft_bfs(galery, adj_mat)) != NULL)
	{
		ft_debug_single_path(path, path[0]);
	}
}