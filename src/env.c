/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:33:46 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/05 14:24:44 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_size(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_env_init(char **envp, t_all *all)
{
	int		i;
	size_t	x;

	i = -1;
	if(envp)
	{
		x = ft_get_size(envp);
		all->myenv = malloc(sizeof(char *) * (x + 1));
		if (!all->myenv)
			return;
		all->myenv[x] = NULL;
		while (++i < x)
			all->myenv[i] = ft_strdup(envp[i]);
	}
	else
	{
		all->myenv = malloc(sizeof(char *) * 1);
		all->myenv = NULL;
	}
//	ft_print_table(all->myenv, 1);
}

void	ft_export(char *st, t_all *all)
{
	char	**tmp;
	size_t	x;	
	int		i;

	i = -1;
	x = ft_get_size(all->myenv);
	tmp = malloc(sizeof(char *) * (x + 1));
	if (!tmp)
		return;
	tmp[x] = NULL;
	while (++i < x)
		tmp[i] = all->myenv[i];
	tmp[i] = ft_strdup(st);
	free(all->myenv);
	all->myenv = tmp;
//	ft_print_table(tmp, 1);
}
void	leaks()
{
	system("leaks a.out");
}
/*
int	main(int ac, char **av, char **envp)
{
	int i = -1;
	atexit(leaks);
	t_all all;
	
	printf("this envp size: %zu\n", ft_get_size(envp));
	ft_env_init(envp, &all);
	ft_export("hrllo I am Here!", &all);
	size_t	x = ft_get_size(all.myenv);
	printf("this myenvp size: %zu\n", x);
	while(++i < x)
		free(all.myenv[i]);
	free(all.myenv);
}
*/
