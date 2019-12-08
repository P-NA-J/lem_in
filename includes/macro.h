/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:39:42 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/09 00:08:02 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H

# define MACRO_H

# define BUFF_SIZE 		4096
# define IGNORE 		-1
# define PRIME 			20543

/*
** Errors
*/ 

# define ERR_BAD_DATA	-2

/*
** Features
*/ 

# define MARKED 					00000001
# define END_CONNECT 				00000010
# define OCCUPIED 					00000100
# define ENTRY 						00001000
# define ADDED_NEIGHBORS			00010000

# define CUT 			00000001

# define COUCOU printf("coucou\n")

/*
**	Colors
*/ 

#  define _RED      "\x1b[31m"
#  define _GREEN    "\x1b[32m"
#  define _YELLOW   "\x1b[33m"
#  define _BLUE     "\x1b[34m"
#  define _MAGENTA  "\x1b[35m"
#  define _CYAN     "\x1b[36m"
#  define _RESET    "\x1b[0m"



#endif
