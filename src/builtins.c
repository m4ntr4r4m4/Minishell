/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2022/12/26 17:17:35 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_get_size(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_echo(char *str, int flag)
{
	if (!flag)
		printf("%s",str);
	else
		printf("%s\n",str);
}

int		ft_cd(char *path)
{
	return (chdir(path));
}

void	ft_pwd()
{
	char *buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	ft_echo(buff, 1);
	free(buff);
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

void	ft_env(t_all *all)
{
	int	i;

	i = 0;
	while (all->myenv[i])
		printf("%s\n", all->myenv[i++]);
}

void	unset(char *st, t_all *all)
{
	char	**tmp;
	size_t	x;
	int		i;
	int		j;

	i = -1;
	j = 0;
	x = ft_get_size(all->myenv);
	tmp = malloc(sizeof(char *) * (x));
	if (!tmp)
		return;
	tmp[x - 1] = NULL;
	while (++i < x)
	{
		if (all->myenv[j] == str)
			free(all->myenv[j++]);
		tmp[i] = all->myenv[j++];
	}
	free(all->myenv);
	all->myenv = tmp;
	///////////    test this function //////////////



}

void	ft_exit()
{
	exit(0);
}

/*
int	main(void)
{
	char *cmd = "echo";
	char *args = "hello there!";

	ft_pwd();

}
*/
