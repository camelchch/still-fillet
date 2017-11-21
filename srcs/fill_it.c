/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:15:46 by fsabatie          #+#    #+#             */
/*   Updated: 2017/11/19 23:44:02 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/fill_it.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	t_etrimino	*tetriminos;
	t_map		*map;

	if (argc != 2)
		ft_putnexit("usage : ./fillit map");
	tetriminos = ft_read_entry(argv[1]);
	map = ft_newmap(NULL, ft_minmapsize(tetriminos));
	ft_solve_map(map, tetriminos, 0, 0);
	ft_print_map(map);
	return 0;
}
