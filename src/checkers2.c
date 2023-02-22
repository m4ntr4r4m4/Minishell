/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:39:19 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 19:55:08 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token(char token, char prev, char str, int count)
{
	if (prev != CONTINUE)
	{
		if (token != prev || str != CONTINUE)
		{
			if (prev == LESS && token == GREAT)
				return (1);
			return (0);
		}
	}
	else if (!count)
		return (0);
	return (1);
}

int	pass(char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	return (i);
}

int	check_tokens(char *str)
{
	int		i;
	char	token;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		token = token_l(str[i]);
		if (str[i] == '"' || str[i] == 39)
		{
			i = pass(str, i);
			if (!str[i])
				return (0);
		}
		else if (token != CONTINUE)
		{
			if (i != 0 && !check_token(token, token_l(str[i - 1]),
					token_l(str[i + 1]), count))
				return (0);
			count = 0;
		}
		else if (str[i] != 32)
			count = 1;
	}
	if (!count)
		return (0);
	return (1);
}

void	ft_builtins(t_all *all, int i)
{
	int	x;

	x = 1;
	if (!strncmp(all->cmd[i].name, "echo", 4))
		ft_echo(&i, all);
	if (!strncmp(all->cmd[i].name, "pwd", 3))
		ft_pwd();
	if (!strncmp(all->cmd[i].name, "cd", 2))
		ft_cd(all->cmd[i].args[1], all);
	x = 1;
	if (!strncmp(all->cmd[i].name, "unset", 5))
		while (all->cmd[i].args[x])
			ft_unset(all->cmd[i].args[x++], all);
	if (!strncmp(all->cmd[i].name, "exit", 4))
		ft_exit();
	if (!strncmp(all->cmd[i].name, "env", 3) && !all->cmd[i].args[1])
		ft_print_table(all->myenv, 1);
	if (!strncmp(all->cmd[i].name, "export", 6))
		ft_export_init(all, i);
	all->exit_var = 1;
}
