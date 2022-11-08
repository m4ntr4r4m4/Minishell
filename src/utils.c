/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:58:45 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/08 16:46:47 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_all *all)
{
	int x = 0;
	int y = 0;

	while (y < all->n_cmd)
	{
		if (all->cmd[y].name)
			printf("name %d %s\n", y, all->cmd[y].name);
		if (all->cmd[y].path)
			printf("path %d %s\n", y, all->cmd[y].path);
		while (all->cmd[y].args[x])
			printf("arg %d %s\n", y, all->cmd[y].args[x++]);
		x = 0;
		while (all->cmd[y].token[x])
			printf("tokens %c\n", all->cmd[y].token[x++]);
		x = -1;
		while (all->cmd[y].infile[++x])
			printf("infile %d %d %s\n", y, x,all->cmd[y].infile[x]);
		x = -1;
		while (all->cmd[y].outfile[++x])
			printf("outfile %d %d %s\n", y, x, all->cmd[y].outfile[x]);
		x = 0;
		y++;
	}
	x = 0;
	while (all->token_l[x])
		printf("T %c\n", all->token_l[x++]);
}


void	freetable(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		/* printf("free: %s\n", str[i]); */
		free(str[i++]);
	}
	free(str[i]);
	free(str);
}
