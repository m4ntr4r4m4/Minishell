/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/04 16:32:04 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_ut(char **str, int i, int z)
{
	int	x;

	x = 0;
	if (!ft_strisnum(str[i]))
	{
		if (z)
		{
			ft_putstr_fd("too many arguments\n", 2);
			return (-1);
		}
		x = 255 ;
	}
	else
	{
		if (z)
		{
			ft_putstr_fd("too many arguments\n", 2);
			return (-1);
		}
	}
	return (x);
}

void	ft_exit(char **str)
{
	int	x;
	int	i;
	int	z;

	x = 0;
	i = 0;
	z = 0;
	while (str[++i])
	{
		x = exit_ut(str, i, z);
		if (x == -1)
			return ;
		x = ft_atoi(str[i]);
		z = x;
	}
	exit(x);
}

void	ft_newpwd(t_all *all, char *buff)
{
	int	i;

	i = 0;
	while (ft_strncmp(all->myenv[i], "PWD", 3))
		i++;
	free(all->myenv[i]);
	all->myenv[i] = ft_strjoin("PWD=", buff);
}

void	ft_oldpwd(t_all *all, char *pwd)
{
	int	i;

	i = 0;
	while (ft_strncmp(all->myenv[i], "OLDPWD", 6))
		i++;
	free(all->myenv[i]);
	all->myenv[i] = ft_strjoin("OLDPWD=", pwd);
}

int	ft_cd(char *path, t_all *all)
{
	char	*buff;
	char	*pwd;
	char	*oldpwd;

	if (!path)
		path = ft_mygetenv("HOME", all);
	if (!chdir(path))
	{
		buff = malloc(sizeof(char) * PATH_MAX);
		if (getcwd(buff, PATH_MAX) == NULL)
			perror(path);
		pwd = ft_strdup(ft_mygetenv("PWD", all));
		oldpwd = ft_mygetenv("OLDPWD", all);
		ft_newpwd(all, buff);
		ft_oldpwd(all, pwd);
		free(pwd);
		free(buff);
		return (0);
	}
	else
		perror("cd");
	return (1);
}
