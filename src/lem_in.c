/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/22 15:08:16 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(void)
{
	t_list	*data;
	t_lem	colony;

	data = NULL;
	colony.nb = IGNORE;
	data = ft_recover_data();
	if (ft_parsing(data, &colony) == FALSE)
		ft_putendl_fd(2, "Error");
//	ft_lst_free(&data);
	return (0);
}
