/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:41:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 15:02:20 by ahammoud         ###   ########.fr       */
/*   Updated: 2023/02/15 19:08:03 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	fix_behavior(t_all *all)
{
	if (ft_strchr(all->cmd[0].name, '>') || ft_strchr(all->cmd[0].name, '<'))
	{
		free(all->cmd[0].name);
		free(all->cmd[0].path);
		free(all->cmd[0].args[0]);
		all->cmd[0].name = ft_strdup("echo");
		all->cmd[0].path = ft_strdup("echo");
		all->cmd[0].args[0] = ft_strdup("echo");
		all->cmd[0].builtins = 1;
	}
}

int	parser(char **rd, t_all *all)
{
	char	**str;

	if (check_error(rd))
	{
		check_expanser(rd, all);
		if (**rd == '\0')
			return (0);
		str = ft_split_parse(*rd, ' ');
		init_structs(all, str);
		lexer(str, all);
		check_builtins(all);
		fix_behavior(all);
		freetable(str);
		return (1);
	}
	return (0);
}
