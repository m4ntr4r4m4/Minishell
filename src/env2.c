/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:33:46 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 14:37:03 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export_cpy(char *st, char *var, t_all *all)
{
	int	x;

	x = -1;
	while (all->myenv[++x])
	{
		if (!ft_strncmp(st, all->myenv[x], ft_strlen(var) + 1))
		{
			free(all->myenv[x]);
			all->myenv[x] = ft_strdup(st);
			free(var);
			return (0);
		}
	}
	return (1);
}

void	ft_export(char *st, t_all *all)
{
	char	**tmp;
	char	*var;
	int		x;	
	int		i;

	var = ft_strchr(st, '=');
	if (!var)
		return ;
	var = ft_strtrimtail(st, var);
	if (!ft_export_cpy(st, var, all))
		return ;
	free(var);
	x = ft_get_size(all->myenv);
	tmp = malloc(sizeof(char *) * (x + 2));
	if (!tmp)
		return ;
	tmp[x + 1] = NULL;
	i = -1;
	while (++i < x)
		tmp[i] = ft_strdup(all->myenv[i]);
	tmp[i] = ft_strdup(st);
	freetable(all->myenv);
	all->myenv = tmp;
}


char	*ft_mygetenv(char *str, t_all *all)
{
	int		i;
	int		j;
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
	return ("");
}

//char	*ft_mygetenv(char *str, t_all *all)
//{
//	int		i;
//	int		j;
//	char	*st;
//	char	*tmp;
//
//	if (str[0] == '\0')
//	{
//		st = ft_strjoin(str, "=");
//		tmp = ft_strtrim(st, "$");
//		free(st);
//		st = tmp;
//		i = -1;
//		while (all->myenv[++i])
//		{
//			if (!ft_strncmp(st, all->myenv[i], ft_strlen(st)))
//			{
//				j = 0;
//				while (st[j] == all->myenv[i][j])
//					j++;
//				free(st);
//				return (&all->myenv[i][j]);
//			}
//		}
//		free(st);
//		free(str);
//	}
//	return ("");
//}

