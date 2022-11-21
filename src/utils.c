/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:58:45 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/21 15:13:47 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_all *all)
{
	int x = 0;
	int y = 0;

	fprintf(stderr,"size %zu\n", all->size);
	while (y < all->size)
	{
		if (all->cmd[y].name)
			fprintf(stderr,"name %d %s\n", y, all->cmd[y].name);
		if (all->cmd[y].path)
			fprintf(stderr,"path %d %s\n", y, all->cmd[y].path);
		while (all->cmd[y].args[x])
			fprintf(stderr,"arg %d %s\n", y, all->cmd[y].args[x++]);
		x = -1;
		while (all->cmd[y].token[++x])
			fprintf(stderr,"tokens %c\n", all->cmd[y].token[x]);
		x = -1;
		while (all->cmd[y].infile[++x])
			fprintf(stderr,"infile %d %d %s\n", y, x,all->cmd[y].infile[x]);
		x = -1;
		while (all->cmd[y].outfile[++x])
			fprintf(stderr,"outfile %d %d %s\n", y, x, all->cmd[y].outfile[x]);
		x = 0;
		y++;
	}
	x = 0;
	while (all->token_l[x])
		fprintf(stderr,"Token %c\n", all->token_l[x++]);
}

void	freetable(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		/* fprintf(stderr,"free: %s\n", str[i]); */
		free(str[i++]);
	}
	free(str[i]);
	free(str);
}
