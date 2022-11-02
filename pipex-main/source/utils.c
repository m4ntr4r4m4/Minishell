/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:36:36 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/13 17:17:13 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_var(char **envp)
{
	int		i;
	char	**pathvar;
	char	*str;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	envp[i] = ft_strtrim(envp[i], "PATH=");
	pathvar = ft_split(envp[i], ':');
	i = 0;
	while (pathvar[i])
	{
		str = ft_strjoin(pathvar[i], "/");
		free(pathvar[i]);
		pathvar[i] = str;
		i++;
	}
	return (pathvar);
}

char	*check_bin(char *binary, char *bin, int ac)
{
	int		x;

	if (ac == 2)
		x = access(ft_strjoin(bin, binary), W_OK);
	if (ac == 1)
		x = access(ft_strjoin(bin, binary), R_OK);
	if (ac == 3)
		x = access(ft_strjoin(bin, binary), X_OK);
	if (x == 0)
		return (ft_strjoin(bin, binary));
	return (NULL);
}

void	freevars(t_pip *vars)
{
	int	i;

	i = 0;
	while (vars->pathvar[i])
		free(vars->pathvar[i++]);
	free(vars->pathvar);
}
