/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:17:24 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/08 13:35:06 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(char *str)
{
	char	*var;
	char	*s;
	bool	allocated;

	allocated = false;
	if (!str)
		return (NULL);
	if (str[0] == '$')
		str++;
	if (str[0] == '{')
	{
		s = ft_strtrim(str, "{");
		str = ft_strtrim(s, "}");
		allocated = true;
	}
	var = getenv(str);
	if (allocated)
	{
		free(str);
		free(s);
	}
	if (!var)
		return (NULL);
	return (var);
}

void	leaks(void)
{
	system("leaks expander");
}

void	freecmd(t_all *all)
{
	int	i;
	int	j;

	i = -1;
	while(++i < all->size)
	{
		j = -1;
		/* while(all->cmd[i].args[++j]) */
		/* { */
		/* 	printf(" -> %s\n",all->cmd[i].args[j]); */
		/* 	free(all->cmd[i].args[j]); */
		/* } */
		/* printf(" -> hola\n"); */
		j = -1;
		/* while(all->cmd[i].infile[++j]) */
		/* 	free(all->cmd[i].infile[j]); */
		j = -1;
		/* while(all->cmd[i].outfile[++j]) */
		/* 	free(all->cmd[i].outfile[j]); */
		if (all->cmd[i].token)
			free(all->cmd[i].token);
		/* if (all->cmd[i].name) */
		/* 	free(all->cmd[i].name); */
		free(all->cmd[i].infile);
		free(all->cmd[i].outfile);
		free(all->cmd[i].args);
		free(all->cmd[i].path);
	}
	if (i)
	{
		int i = -1;
		free(all->token_l);
		free(all->cmd);
	/* free(all->pipes); */
	}
}
