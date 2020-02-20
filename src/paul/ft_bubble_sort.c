/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:34 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/14 17:56:17 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_bubble_sort(int *tab_l, int *tab_i, int len)
{
	int i;
	int j;
	int	i_min;
	int	min;
	int	tmp;

	i_min = 0;
	i = 0;
	while (i < len)
	{
		min = tab_l[i];
		i_min = i;
		j = i + 1;
		while (j < len)
		{
			if (tab_l[j] < min)
			{
				min = tab_l[j];
				i_min = j;
			}
			j += 1;
		}
		tab_l[i_min] = tab_l[i];
		tmp = tab_i[i_min];
		tab_i[i_min] = tab_i[i];
		tab_l[i] = min;
		tab_i[i] = tmp;
		i += 1;
	}
}