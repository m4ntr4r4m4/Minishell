/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:48:30 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/24 14:54:35 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//	void	all_fill(t_all *all)
//	{
//		strdup("./myls");
//	
//		all->size = 1;
//		all->cmd = malloc(sizeof(*all->cmd) * 1);
//	//	all->cmd[0].path = get_path(all->path, "ls", X_OK);
//	//	all->cmd[0].path = strdup("/Users/ahammoud/github/Minishell/myls");
//		all->cmd[0].path = strdup("./executor");
//		fprintf(stderr, "thdhfgkhjk ************ %s\n", all->cmd[0].path);
//	//	all->cmd[0].name = strdup("/Users/ahammoud/github/Minishell/myls");
//		all->cmd[0].name = strdup("./myls");
//		all->cmd[0].args = malloc(sizeof(*all->cmd[0].args) * 2);
//		all->cmd[0].token = malloc(sizeof(*all->cmd[0].token) * 1);
//		all->cmd[0].infile = malloc(sizeof(*all->cmd[0].infile) * 2);
//		all->cmd[0].outfile = malloc(sizeof(*all->cmd[0].outfile) * 2);
//		all->cmd[0].infile[0] = strdup("./myls");
//		all->cmd[0].infile[1] = NULL;
//		all->cmd[0].outfile[0] = strdup("./myls");
//		all->cmd[0].outfile[1] = NULL;
//	//	all->cmd[0].args[0] = strdup("/Users/ahammoud/github/Minishell/myls");
//		all->cmd[0].args[0] = strdup("./executor");
//		all->cmd[0].args[1] = NULL;
//		all->cmd[0].n_tokens = 0;
//	}

void	handlerint(int x)
{
	ioctl(0, TIOCSTI, "\n");
//	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handlerquit(int x)
{
	rl_on_new_line();
}

void	mysignal(void)
{
	signal(SIGINT, handlerint);
	signal(SIGQUIT, handlerquit);
}

void	minishell(char **envp)
{
	t_all	all;
	char	*rd;
	char	**new;

	all.exit_var = 0;
	while (1)
	{
		rd = readline("$_MINI_SHELL_$:");
		if (!rd)
			exit(0);
		if (rd)
		{
			if (ft_strncmp(rd, "\0", 1))
			{
				add_history (rd);
				ft_env_init(envp, &all);
				all.path = path_var(all.myenv);
				new = parser(rd, &all, all.myenv);
				if (new)
					prexec(&all, all.myenv);
			}
			free(rd);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
//	atexit(leaks);
	mysignal();
	minishell(envp);
	return (0);
}
