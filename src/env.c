/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:33:46 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 17:15:32 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_all *all)
{
	int	i;

	i = 0;
	while (all->myenv[i])
		printf("%s\n", all->myenv[i++]);
}

char	*ft_shell_level(char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, '=');
	tmp++;
	str = ft_strjoin("SHLVL=", tmp = ft_itoa(ft_atoi(tmp) + 1));
	free(tmp);
	return (str);
}

void	ft_env_cpy(char **envp, t_all *all)
{
	int		x;
	int		i;

	i = -1;
	x = ft_get_size(envp);
	all->myenv = malloc(sizeof(char *) * (x + 1));
	if (!all->myenv)
		return ;
	all->myenv[x] = NULL;
	while (++i < x)
	{
		if (!ft_strncmp(envp[i], "SHLVL", 4))
			all->myenv[i] = ft_shell_level(envp[i]);
		else
			all->myenv[i] = ft_strdup(envp[i]);
	}
}

void	ft_env_init_2(t_all *all)
{
	char	*buff;

	all->myenv = malloc(sizeof(char *) * 4);
	if (!all->myenv)
		exit(-1);
	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	all->myenv[0] = ft_strdup("PATH=/:./");
	all->myenv[1] = ft_strjoin("PWD=", buff);
	all->myenv[2] = ft_strdup("SHLVL=1");
	all->myenv[3] = NULL;
	free(buff);
}

void	ft_env_init(char **envp, t_all *all)
{
	if (envp[0])
		ft_env_cpy(envp, all);
	else
		ft_env_init_2(all);
}
