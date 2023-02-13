/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 17:36:39 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(void)
{
	exit(0);
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

	if (!chdir(path))
	{
		buff = malloc(sizeof(char) * PATH_MAX);
		if (getcwd(buff, PATH_MAX) == NULL)
			perror("getcwd() error");
		pwd = ft_strdup(ft_mygetenv("PWD", all));
		oldpwd = ft_mygetenv("OLDPWD", all);
		ft_newpwd(all, buff);
		ft_oldpwd(all, pwd);
		free(pwd);
		free(buff);
		return (0);
	}
	return (1);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	printf("%s\n", buff);
	free(buff);
}
