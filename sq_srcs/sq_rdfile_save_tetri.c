/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_rdfile_save_tetri.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:03:21 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/22 15:27:35 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../includes/libft/libft.h"
#include "sq_fillit.h"

void	ft_exit(char const *s)
{
	ft_putendl(s);
	exit(1);
}

void	only_dot_hash(char *s, int len)
{
	int		hash_count;
	int		index;

	hash_count = 0;
	index = 0;
	while (index < len)
	{
		if ((!((index + 1) % 5) || index == len -1))
		{
			if (s[index] && s[index]!= '\n')
				ft_exit("error");
		}
		else
		{
			if (s[index] != '.' && s[index] != '#')
				ft_exit("error");
			if (s[index] == '#')
				hash_count++;
		}
		index++;
	}
	if (hash_count != 4)
		ft_exit("error");
}

void	valid_tetri(char *s)
{
	int		touch_count;
	int		i;

	touch_count = 0;
	i = 0;
	while (i < BUFF_SIZE)
	{
		if (s[i] == '#')
		{
			if (i + 5 < BUFF_SIZE && s[i + 5] == '#')
				touch_count++;
			if (i != 3 && i != 8 && i != 13 && i != 18)
			{
				if (i + 1 < BUFF_SIZE && s[i+1] == '#')
					touch_count++;
			}
		}
		i++;
	}
	if (touch_count != 3 && touch_count != 4)
		ft_exit("not valid file");
}

void  mv_left_top(char **s)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		k;

	x = 0;
	y = 0;
	k = 0;
	i = -1;
	while (!ft_strchr(s[k],'#'))
		k++;
	x = 0;
	while ( y < 4 && s[x][y] != '#')
	{
		x = 0;
		while (x < 4 && s[x][y] != '#')
			x++;
		if (s[x][y] != '#')
		y++;
	}
	ft_putnbr(k);
	ft_putnbr(y);
	ft_putendl("");
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if(s[i][j] == '#')
				ft_swap(&s[i][j], &s[i - k][j - y]);
		}
	}
}

tetri_list	*add_tetri(char **s, int nb, tetri_list *old_list)
{
	tetri_list	*list;
	tetri_list	*temp;

	if(!(list = (tetri_list *)malloc(sizeof(*list))))
		return (NULL);
	if(!(list->str = (char **)malloc(sizeof(char *) * 5)))
		return (NULL);
	list->str = s;
	list->letter = 'A' + nb;
	list->x = 0;
	list->y = 0;
	list->next = NULL;
	list->pre = NULL;
	if(!old_list)
		old_list = list;
	else 
	{
		temp = old_list;
		while (temp->next)
			temp = temp->next;
		list->pre = temp;
		temp->next = list;
	}
	return (old_list);
}

tetri_list	*ft_readfile(char const *file_name)
{
	char		*buff;
	int			fd;
	char		**s;
	int			nb_tetri;
	tetri_list	*list;

	nb_tetri = 0;
	list = NULL;
	fd = open(file_name, O_RDONLY);
	if(fd == -1)
		ft_exit("error");
	if(!(buff = (char *)malloc(BUFF_SIZE)))
		return (NULL);
	while (read(fd, buff, BUFF_SIZE))
	{
		ft_putendl("here12312333333333333333");
		if (nb_tetri > 25)
			ft_exit("maxi tetri is 26");
		only_dot_hash(buff,BUFF_SIZE);
		valid_tetri(buff);
		s = ft_strsplit((char const *)buff, '\n');
		mv_left_top(s);
		list = add_tetri(s, nb_tetri, list);
		nb_tetri++;
		ft_bzero(buff, BUFF_SIZE);
	}
	return (list);
}

