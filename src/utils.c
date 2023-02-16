/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:58:45 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 18:55:52 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_put_endfile(char *eof, char **input, t_all *all, int fd)
{
	while (ft_strncmp(*input, eof, ft_strlen(*input)))
	{
		ft_putendl_fd(*input, fd);
		free(*input);
		*input = get_line(0);
		if (!(*input))
			break ;
		check_expanser(input, all);
	}
}

char	**ft_path_var(char **envp, char **tmp)
{
	size_t		i;
	char		**pathvar;
	char		*str;

	i = 0;
	pathvar = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (i < ft_get_size(envp))
	{
		*tmp = ft_strtrim(envp[i], "PATH=");
		pathvar = ft_split(*tmp, ':');
		i = 0;
		while (pathvar[i])
		{
			str = ft_strjoin(pathvar[i], "/");
			free(pathvar[i]);
			pathvar[i] = str;
			i++;
		}
		if (*tmp)
			free(*tmp);
	}
	return (pathvar);
}

char	**path_var(char **envp)
{
	size_t		i;
	char		**pathvar;
	char		*tmp;

	pathvar = NULL;
	i = 0;
	if (envp[0])
		pathvar = ft_path_var(envp, &tmp);
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
	if (!pathvar)
		return (0);
	while (pathvar[i])
	{
		path = check_bin(cmd, pathvar[i++], code);
		if (path)
			break ;
	}
	return (path);
}
