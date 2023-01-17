/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:20:54 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/17 14:45:24 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freetable(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
//		fprintf(stderr,"********** FREE %s **********\n", str[i]);
		free(str[i]);
	}
	free(str[i]);
	free(str);
}

void	freecmd(t_all *all)
{
	size_t	i;

	i = 0;
	while(i < all->size)
	{
		free(all->cmd[i].name);
		freetable(all->cmd[i].args);
		free(all->cmd[i].path);
		freetable(all->cmd[i].infile);
		freetable(all->cmd[i].outfile);
		free(all->cmd[i].token);
		i++;
	}
	free(all->token_l);
	if (all->size >= 1)
		free(all->pipes);
	freetable(all->path);
	if (!access("./file.tmp", R_OK))
		unlink("file.tmp");
	free(all->cmd);
	freetable(all->myenv);
}
