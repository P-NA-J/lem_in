/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:39:42 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/30 18:15:45 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H

# define MACRO_H

# define BUFF_SIZE 		4096
# define IGNORE 		-1

/*
** Errors
*/ 

# define ERR_BAD_DATA	-2
/*
** Features
*/ 
# define MARKED 		00000001
# define END_CONNECT 	00000010
# define OCCUPIED 		00000100
# define ENTRY 			00001000

# define CUT 			00000001

# define COUCOU printf("coucou\n")


#endif
