/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/16 18:39:09 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_debug_single_path(int *path, size_t len);
void		print_info(t_map *data);
void	ft_reset_matrix(t_map *galery);

void	ft_mult_bfs(t_map *galery, int **adj_mat)
{
	int	*path;
	int i;

	i = 0;
	galery->is_augmented = 0;
	while ((path = ft_bfs(galery, adj_mat, galery->start)) != NULL)
	{
		ft_debug_single_path(path, path[0]);
		print_info(galery);
		printf("\n\n\n");
		if (path[0] == 2)
			return ;
		if (galery->is_augmented == 1)
		{
			ft_reset_matrix(galery);
			galery->is_augmented = 0;
//			print_info(galery);
		}
		i += 1;
	}
	if (i == 0)
		printf("C'est la merde.\n");
}
