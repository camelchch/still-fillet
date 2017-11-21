/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:03:58 by fsabatie          #+#    #+#             */
/*   Updated: 2017/11/11 13:03:59 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fill_it.h"
#include "libft.h"
#include <stdio.h>

/*
** Checks if the maps are valid.
*/

static	void	ft_check_if_valid(char *tetri)
{
	short n;
	short i;

	n = 4;
	i = 0;
	tetri[BUFF_SIZE - 1] = 0;
	if (tetri[i] != '#' && tetri[i++] != '.')
		ft_putnexit("A tetrimino is invalid.");
	while (tetri[i])
	{
		if (i == n)
		{
			if (tetri[i] != '\n')
				ft_putnexit("A tetrimino is invalid.");
			else
				n += 5;
			i++;
		}
		if (tetri[i] != '#' && tetri[i] != '.' && tetri[i] != '\0')
			ft_putnexit("A tetrimino is invalid.");
		i++;
	}
	ft_strtrim(tetri);
	if (ft_strlen(tetri) != 20)
		ft_putnexit("A tetrimino is invalid.");
}

/*
** Opens, read, and returns the file passed as an argument.
*/

t_list			*ft_read_entry(const char *filename)
{
	int		fd;
	char	*tab;
	t_list	*list;
	t_list	*last;

	list = ft_lstnew(NULL, sizeof(t_etrimino*));
	last = list;
	tab = ft_memalloc(BUFF_SIZE + 1);
	if (!(fd = open(filename, O_RDONLY)))
		ft_putnexit("Could not open file.");
	while (read(fd, tab, BUFF_SIZE))
	{
		ft_check_if_valid(tab);
		last->content = ft_newtetri(ft_strtrim(tab));
		last->next = ft_lstnew(NULL, sizeof(t_etrimino*));
		last = last->next;
		ft_bzero(tab, BUFF_SIZE);
	}
	return (list);
}
