/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:41:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 12:23:38 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fix_behavior(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->size)
	{
		if (ft_strchr(all->cmd[i].name, '>') || ft_strchr(all->cmd[i].name, '<'))
		{
			free(all->cmd[i].name);
			free(all->cmd[i].path);
			free(all->cmd[i].args[0]);
			all->cmd[i].name = ft_strdup("echo");
			all->cmd[i].path = ft_strdup("echo");
			all->cmd[i].args[0] = ft_strdup("echo");
			all->cmd[i].builtins = 1;
		}
	}
}

int	parser(char **rd, t_all *all)
{
	char	**str;

	if (check_error(rd))
	{
		check_expanser(rd, all);
		str = ft_split_parse(*rd, ' ');
		init_structs(all, str);
		lexer(str, all);
		check_builtins(all);
		fix_behavior(all);
		print_all(all);
		freetable(str);
		return (1);
	}
	return (0);
}
