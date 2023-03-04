/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/04 13:56:54 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char **str)
{
	int	x;
	int	i;

	x = 0;
	i = -1;
	while (str[++i])
	{
		if (!ft_strisnum(str[i]))
		{
			ft_putstr_fd("args ofr exit should be numeric\n", 2);
			return ;
		}
		x = ft_atoi(str[i]);
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

void	ft_pwd(void)
{
	char	*buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("Working Directory");
	printf("%s\n", buff);
	free(buff);
}
