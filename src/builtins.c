/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/12 16:18:30 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**ft_unset_utils(t_all *all, char *st, int x)
{
	int		i;
	int		j;
	char	**tmp;

	j = 0;
	i = -1;
	tmp = malloc(sizeof(char *) * (x));
	if (!tmp)
		exit(-1);
	tmp[x - 1] = NULL;
	while (all->myenv[++i + 1])
	{
		if (!ft_strncmp(all->myenv[i], st, ft_strlen(st)))
			i++;
		if (all->myenv[i])
			tmp[j++] = ft_strdup(all->myenv[i]);
	}
	return (tmp);
}

void	ft_unset(char *st, t_all *all)
{
	char	**tmp;
	size_t	x;
	int		i;

	i = -1;
	while (all->myenv[++i])
	{
		if (!ft_strncmp(all->myenv[i], st, ft_strlen(st)))
			break ;
	}
	x = ft_get_size(all->myenv);
	if (i != (int)x)
	{
		tmp = ft_unset_utils(all, st, x);
		freetable(all->myenv);
		all->myenv = tmp;
	}
}

void	ft_exit(void)
{
	exit(0);
}

void	ft_echo(int *i, t_all *all)
{
	int		j;
	char	*str;

	j = 1;
	while (!ft_strncmp(all->cmd[*i].args[j], "-n", 2) \
			&& ft_strlen(all->cmd[*i].args[j]) == 2)
		j++;
	str = ft_merge(&(all->cmd[*i].args[j]));
	if (j > 1)
		ft_putstr_fd(str, 1);
	else
	{
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free(str);
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
	if (!strncmp(all->cmd[i].name, "env", 3))
		ft_print_table(all->myenv, 1);
	x = 1;
	if (!strncmp(all->cmd[i].name, "export", 6))
		while (all->cmd[i].args[x])
			ft_export(all->cmd[i].args[x++], all);
}
