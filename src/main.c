/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/09 00:07:07 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	main(void)
{
	t_map	*data;
//	t_map	colony;

	data = parser();
	print_info(data);
//	if (ft_parsing(data, &colony) == FALSE)
//		perror("Error in input");
//	ft_lst_free(&data);
//	print_info();
	return (0);
}
