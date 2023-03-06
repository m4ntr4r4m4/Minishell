/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:20:54 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/06 16:43:46 by ahammoud         ###   ########.fr       */
/*   Updated: 2023/03/06 12:49:50 by ahammoud         ###   ########.fr       */
/*   Updated: 2023/02/15 18:53:33 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	freetable(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str[i]);
	free(str);
}

void	freecmd(t_all *all)
{
	int	i;

	i = -1;
	while (++i < (int)all->size)
	{
		free(all->cmd[i].name);
		freetable(all->cmd[i].args);
		freetable(all->cmd[i].out.token);
		free(all->cmd[i].path);
		freetable(all->cmd[i].infile);
		freetable(all->cmd[i].outfile);
		freetable(all->cmd[i].eof);
		free(all->cmd[i].token);
	}
	free(all->token_l);
	if (all->size >= 1)
		free(all->pipes);
	if (all->path)
		freetable(all->path);
	if (!access("./file.tmp", R_OK))
		unlink("file.tmp");
	free(all->cmd);
}
