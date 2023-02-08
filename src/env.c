/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:33:46 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/08 17:22:24 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_get_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

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

void	ft_env_init(char **envp, t_all *all)
{
	int		i;
	int		x;

	i = -1;
	if (envp)
	{
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
	else
	{
		all->myenv = malloc(sizeof(char *) * 1);
		all->myenv = NULL;
	}
}

void	ft_export(char *st, t_all *all)
{
	char	**tmp;
	int		x;	
	int		i;

	i = -1;
	x = ft_get_size(all->myenv);
	tmp = malloc(sizeof(char *) * (x + 1));
	if (!tmp)
		return ;
	tmp[x] = NULL;
	while (++i < x)
		tmp[i] = all->myenv[i];
	tmp[i] = ft_strdup(st);
	free(all->myenv);
	all->myenv = tmp;
}

char	*ft_mygetenv(char *str, t_all *all)
{
	int		i;
	int		j;
	int		len;
	char	*st;
	char	*tmp;

	st = ft_strjoin(str, "=");
	tmp = ft_strtrim(st, "$");
	free(st);
	st = tmp;
	i = -1;
	while (all->myenv[++i])
	{
		if (!ft_strncmp(st, all->myenv[i], ft_strlen(st)))
		{
			j = 0;
			while (st[j] == all->myenv[i][j])
				j++;
			free(st);
			return (&all->myenv[i][j]);
		}
	}
	free(st);
	free(str);
	return ("");
}
