/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/05 15:32:08 by ahammoud         ###   ########.fr       */
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

int	check_echo_n(size_t j, char **str)
{
	size_t	i;
	size_t	x;

	x = ft_get_size(str);
	while (j < x && !ft_strncmp(str[j], "-n", 2))
	{
		if (ft_strlen(str[j]) != 2)
		{
			i = 0;
			while (str[j][++i])
				if (str[j][i] != 'n')
					return (j);
		}
		j++;
	}
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
	j = check_echo_n(j, all->cmd[*i].args);
	if (j == -1)
		return ;
	str = ft_merge(&(all->cmd[*i].args[j]));
	if (j > 1)
		ft_putstr_fd(str, 1);
	else
	{
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	all->exit_var = 0;
	if (str)
		free(str);
}

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
