/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:48:30 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 16:02:45 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_init_exec(t_all *all, char **rd)
{
	if (ft_strncmp(*rd, "\0", 1))
	{
		add_history(*rd);
		all->path = path_var(all->myenv);
		if (parser(rd, all))
			prexec(all);
		else
		{
			freetable(all->path);
		}
	}
}

void	minishell(char **envp)
{
	t_all	all;
	char	*rd;

	all.exit_var = 0;
	ft_env_init(envp, &all);
	while (1)
	{
		rd = readline("$_MINI_SHELL_$:");
		if (!rd)
			exit(0);
		if (rd)
		{
			ft_init_exec(&all, &rd);
			free(rd);
		}
	}
	freetable(all.myenv);
}

int	main(int ac, char **av, char **envp)
{
	//atexit(leaks);
	if (ac > 0 && av[0])
	{
		mysignal();
		minishell(envp);
	}
	return (0);
}
