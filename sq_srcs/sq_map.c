/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:15:35 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/22 15:27:59 by saxiao           ###   ########.fr       */
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

	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
			{
				if (x + i >= mpsize || y + j >= mpsize) 
					return (0); 
				//ft_putnbr(mpsize);
				if (map[x + i][y + j] != '.')
					return (0);
			}
			j++;
		}
	}
	return (1);
}

int		find_fit(char **map, int mpsize, tetri_list *list, int x, int y)
{
	//ft_putendl("find fit");
	while ( x  < mpsize)
	{
		while (y < mpsize)
		{
			if (check_fill(map, mpsize, list, x, y))
			{
				list->x = x;
				list->y = y;
				//ft_putstr("find a place for");
				//ft_putchar(list->letter);
				//ft_putendl("");
				return (1);
			}
			y++;
		}
		x++;
		y = 0;
	}
	//ft_putstr("DID NOT find a place for");
	//ft_putchar(list->letter);
	//ft_putendl("");
	return (0);
}


void	fill_map(char **map, tetri_list *list, int x, int y)
{
//	ft_putchar(list->letter);
//	ft_putendl("");
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
				map[x + i][y + j] = list->letter;
			j++;
		}
	}
}

void	remove_onete(char **map, int mpsize, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mpsize)
	{
		j = 0;
		while (j < mpsize)
		{
			if (map[i][j] == c)
				map[i][j] = '.';
			j++;
		}
		i++;
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

void		solve_map(tetri_map *map, tetri_list *list, int x, int y)
{
	tetri_list *head;

	head = list;
	if (list)
	{
		if (!find_fit(map->map, map->size, list, x, y))
		{
			list->x = 0;
			list->y = 0;
			if (list->letter == 'A')
				return solve_map(new_map(map->size + 1),head, head->x, head->y);
			remove_onete(map->map, map->size, list->pre->letter);
			return (solve_map(map, list->pre, list->pre->x, list->pre->y + 1));
		}
		fill_map(map->map, list, list->x, list->y);
		//print_map(map->map, map->size);
		if (!list->next)
		return ;
		printf("next %c\n", list->next->letter);
		return (solve_map(map, list->next, list->next->x, list->next->y));
		//print_map(map->map, map->size);
	//	else
	}
	return ;
}

int		main(int ac, char **av)
{
	tetri_list	*list;
	tetri_map	*n_map;

	if(ac != 2)
		ft_exit("not valid file number");
	list = ft_readfile(av[1]);
	n_map = new_map(mini_sq(list));
	//int k = check_fill(n_map->map, 4, list, list->x, list->y);
	//ft_putstr("not problem1111100000");
	solve_map(n_map,list, list->x, list->y);
	//printf("2222220000");
		print_map(n_map->map, n_map->size);
	return (0);
}
