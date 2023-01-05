/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:58:45 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/05 16:17:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_all(t_all *all)
{
	size_t x = 0;
	size_t y = 0;

	printf("comands %zu\n", all->size);
	while (y < all->size)
	{
		if (all->cmd[y].name)
			printf("name[%zu] %s\n", y, all->cmd[y].name);
		if (all->cmd[y].path)
			printf("path[%zu] %s\n", y, all->cmd[y].path);
		while (all->cmd[y].args[x])
		{
			printf("arg[%zu] %zu %s\n", y,x, all->cmd[y].args[x]);
			x++;
		}
		x = -1;
		while (++x < (size_t) all->cmd[y].n_tokens)
			printf("token[%zu] %d\n", x,all->cmd[y].token[x]);
		x = -1;
		while (all->cmd[y].infile[++x])
			printf("infile[%zu] %zu %s\n", y, x,all->cmd[y].infile[x]);
		x = -1;
		while (all->cmd[y].outfile[++x])
			printf("outfile[%zu] %zu %s\n", y, x, all->cmd[y].outfile[x]);
		x = 0;
		y++;
	}
	x = -1;
	while (++x < all->size - 1)
		printf("global tokens %d\n", all->token_l[x]);
}

char	**path_var(char **envp)
{
	int		i;
	char	**pathvar;
	char	*str;
	char	*tmp;

	pathvar = NULL;
	i = 0;
	if(envp[0])
	{
		while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
			i++;
		tmp = ft_strtrim(envp[i], "PATH=");
		pathvar = ft_split(tmp, ':');
		i = 0;
		while (pathvar[i])
		{
			str = ft_strjoin(pathvar[i], "/");
			free(pathvar[i]);
			pathvar[i] = str;
			i++;
		}
		if (tmp)
			free(tmp);
	}
	return (pathvar);
}

char	*check_bin(char *binary, char *path, int ac)
{
	int		x;
	char	*tmp;


	tmp = ft_strjoin(path, binary);
	x = 0;
	if (ac == 2)
		x = access(tmp, W_OK);
	if (ac == 1)
		x = access(tmp, R_OK);
	if (ac == 3)
		x = access(tmp, X_OK);
	if (x == 0 && tmp)
		return (tmp);
	if (tmp)
		free(tmp);
	return (NULL);
}

char	*get_path(char **pathvar, char *cmd, int code)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (pathvar[i])
	{
		path = check_bin(cmd, pathvar[i++], code);
		if (path)
			break ;
	}
	return (path);
}
