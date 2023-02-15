/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 12:54:35 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (++i < x)
	{
		if (!ft_strncmp(all->myenv[i], st, ft_strlen(st)))
			i++;
		if (all->myenv[i])
			tmp[j++] = ft_strdup(all->myenv[i]);
	}
	tmp[j] = NULL;
	return (tmp);
}

void	ft_unset(char *st, t_all *all)
{
	char	**tmp;
	size_t	x;
	int		i;
	char	*str;

	i = -1;
	str = ft_strjoin(st, "=");
	while (all->myenv[++i])
		if (!ft_strncmp(all->myenv[i], str, ft_strlen(str)))
			break ;
	x = ft_get_size(all->myenv);
	if (i != (int)x)
	{
		tmp = ft_unset_utils(all, str, x);
		freetable(all->myenv);
		all->myenv = tmp;
	}
	all->exit_var = 0;
	free(str);
}

int	check_echo_n(int j, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 1;
	while(str[i] && str[i] == 'n')
		++i;
	if (i == len)
		j += 1;
	return (j);
}

void	ft_echo(int *i, t_all *all)
{
	int		j;
	char	*str;

	j = 1;
	if (!all->cmd[*i].args[j])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	if (!ft_strncmp(all->cmd[*i].args[j], "-n", 2) && all->cmd[*i].args[j + 1])
	{
		while (!ft_strncmp(all->cmd[*i].args[j], "-n", 2))
		{
			j = check_echo_n(j, all->cmd[*i].args[j]);
			if (ft_strlen(all->cmd[*i].args[j]) == 2)
				j++;
		}
	}
		str = ft_merge(&(all->cmd[*i].args[j]));
		if (j > 1)
			ft_putstr_fd(str, 1);
		else
		{
			ft_putstr_fd(str, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		all->exit_var = 0;
		free(str);
}
//void	ft_echo(int *i, t_all *all)
//{
//	int		j;
//	char	*str;
//
//	j = 1;
//	if (!all->cmd[*i].args[j])
//		return ;
//	while (!ft_strncmp(all->cmd[*i].args[j], "-n", 2) \
//			&& ft_strlen(all->cmd[*i].args[j]) == 2)
//		j++;
//	str = ft_merge(&(all->cmd[*i].args[j]));
//	if (j > 1)
//		ft_putstr_fd(str, 1);
//	else
//	{
//		ft_putstr_fd(str, STDOUT_FILENO);
//		ft_putstr_fd("\n", STDOUT_FILENO);
//	}
//	all->exit_var = 0;
//	free(str);
//}

void	ft_export_init(t_all *all, int i)
{
	int	x;

	x = 1;
	if (ft_get_size(all->cmd[i].args) >= 2)
		while (all->cmd[i].args[x])
			ft_export(all->cmd[i].args[x++], all);
	else
		ft_print_table(all->myenv, 1);
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
