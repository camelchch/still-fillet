/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:15:35 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/21 09:55:23 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "sq_fillit.h"
#include "../includes/libft/libft.h"

int		mini_sq(tetri_list *list)
{
	int		i;

	i = 1;
	while (list->next)
		list = list->next;
	while ( i * i <= (list->letter - 'A' + 1) * 4)
		i++;
	return (i);
}

short	int *new_map(int size)
{
	short	int *map;

	if(!(map = (short int *)malloc(sizeof(*map) * size)))
	return (NULL);
	bzero(map, size* sizeof(*map));
	return (map);
}

int		fit_map(short int *map, int size_map, tetri_list *list)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < size_map - list->length)
	{
		while (y < size_map - list->heigt)
		{
			if 





void	print_tetri(unsigned short t)
{
	int		i;

	i = 15;
	while (i >= 0)
	{
		if (t & (1 << i))
			printf("1");
		else
			printf("0");
		i--;
	}
	printf("\n");
}

int		main(int ac, char **av)
{
	tetri_list	*list;


	if(ac != 2)
		ft_exit("not valid file number");
	list = ft_readfile(av[1]);

	while(list)
	{
		print_tetri(list->tetri_value);
		list = list->next;
	}
	
	return (0);
}
