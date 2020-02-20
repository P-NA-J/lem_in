/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubble_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:34 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 21:28:53 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

static void	ft_swap_int(int tab[MAX_LEN_PATH], int i, int j)
{
	int	tmp;

	tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

static void	ft_sort_max(t_opti *opti, int len)
{
	int	i;
	int	max;
	int	i_max;

	max = opti->len_p[0][0];
	i_max = 0;
	i = 0;
	while (i < len)
	{
		if (opti->len_p[0][i] > max)
		{
			max = opti->len_p[0][i];
			i_max = i;
		}
		i += 1;
	}
	ft_swap_int(opti->len_p[0], i - 1, i_max);
	ft_swap_int(opti->index_p[0], i - 1, i_max);
}

void		ft_bubble_sort(t_opti *opti, int len)
{
	while (len > 0)
	{
		ft_sort_max(opti, len);
		len -= 1;
	}
}
