/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:15:35 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/24 14:11:30 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "sq_fillit.h"
#include "../includes/libft/libft.h"

int		mini_sq(tetri_list *list)
{
	int			i;
	tetri_list	*temp;

	i = 1;
	temp = list;
	while (temp->next)
		temp = temp->next;
	while ( i * i < (temp->letter - 'A' + 1) * 4)
		i++;
	return (i);
}

tetri_map	*new_map(int size)
{
	int			i;
	int			j;
	tetri_map	*newmap;

	i = -1;
	if (!(newmap = (tetri_map *)malloc(sizeof(*newmap))))
		return (NULL);
	if(!(newmap->map = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	while (++i < size)
	{
		if(!((newmap->map)[i] = (char *)malloc(sizeof(char) * size)))
			return (NULL);
		j = -1;
		while(++j < size)
			(newmap->map)[i][j] = '.';
	}
	newmap->size = size;
	newmap->add_map = newmap;
	return (newmap);
}

int		check_fill(char **map, int mpsize, tetri_list *list, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
			{
				if (x + i >= mpsize || y + j >= mpsize || map[x + i][y + j] != '.')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		find_fit(char **map, int mpsize, tetri_list *list)
{
	int		x;
	int		y;

	x = list->x;
	y = list->y;
	while ( x  < mpsize)
	{
		while (y < mpsize)
		{
			if (check_fill(map, mpsize, list, x, y))
			{
				list->x = x;
				list->y = y;
				return (1);
			}
			y++;
		}
		x++;
		y = 0;
	}
	return (0);
}


void	fill_map(char **map, tetri_list *list)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
				map[list->x + i][list->y + j] = list->letter;
			j++;
		}
	}
}

void	remove_onete(char **map, int mpsize, tetri_list *list)
{
	int		i;
	int		j;

	i = -1;
	while (++i < mpsize)
	{
		j = -1;
		while (++j < mpsize)
		{
			if (map[i][j] == list->letter)
				map[i][j] = '.';
		}
	}
	if (list->y < mpsize - 1)
		list->y++;
	else if (list->y == mpsize - 1)
	{
		list->x++;
		list->y = 0;
	}
}

void	print_map(char **map, int size)
{
	int i = 0;
	int j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_putchar(map[i][j]);
			j++;
		}
		ft_putendl("");
		i++;
	}
}

int		solve_map(tetri_map *map, tetri_list *list)
{
	if (list)
	{
		if (!find_fit(map->map, map->size, list))
		{
			list->x = 0;
			list->y = 0;
			if (list->letter != 'A')
				remove_onete(map->map, map->size, list->pre);
			return (0);
		}
		else
		{
			fill_map(map->map, list);
		}
		return (solve_map(map,list->next));
	}
	return (1);
}

int		main(int ac, char **av)
{
	tetri_list	*list;
	tetri_map	*n_map;
	tetri_map	*temp;

	if(ac != 2)
		ft_exit("not valid file number");
	list = ft_readfile(av[1]);
	n_map = new_map(mini_sq(list));
	while (!solve_map(n_map, list))
	{
		if (list->letter != 'A')
			list = list->pre;
		else
			temp = n_map;
		n_map = new_map(temp->size + 1);
		free (temp);
	}
	print_map(n_map->map,n_map->size);
	return (0);
}
