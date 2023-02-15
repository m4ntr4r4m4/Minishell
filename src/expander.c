/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:17:24 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 20:21:34 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_merge_utils(char **str, char **tmp1, char **tmp2, char **tab)
{
	int	i;

	i = 0;
	while (tab[++i] != NULL)
	{
		if (*tab[i] == '\0')
			continue ;
		free(*tmp2);
		*tmp2 = ft_strjoin(*tmp1, tab[i]);
		free(*tmp1);
		*str = *tmp2;
		*tmp1 = ft_strjoin(*tmp2, " ");
	}
}

char	*ft_merge(char **tab)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	tmp2 = malloc(sizeof(char));
	if (!tmp2)
		return (0);
	tmp1 = ft_strjoin(tab[0], " ");
	if (tab[1] == NULL || tab[1][0] == '\0')
	{
		free(tmp2);
		return (tmp1);
	}
	ft_merge_utils(&str, &tmp1, &tmp2, tab);
	free(tmp1);
	return (str);
}

void	ft_exp_utils(char **tmp, char **s, char **sst, t_all *all)
{
	int	i;

	i = -1;
	while (tmp[++i])
	{
		*s = ft_strrchr(tmp[i], '$');
		if (*s)
		{
			if (!ft_strncmp(*s, "$?", 2))
			{
				free(tmp[i]);
				tmp[i] = ft_itoa(WEXITSTATUS(all->exit_var));
				break ;
			}
			*sst = ft_strtrimtail(tmp[i], *s);
			*s = ft_mygetenv(*s, all);
			free(tmp[i]);
			tmp[i] = ft_strjoin(*sst, *s);
			if (*sst)
				free(*sst);
		}
	}
}

void	ft_fandr(char **s, char **st, char **tmp, char **origin)
{
	int	i;
	char	*sst;

	i = -1;
	*s = ft_strdup(*st);
	while (origin[++i])
	{
		sst = replaceWord(*s, origin[i], tmp[i]);
		free(*s);
		*s = sst;
	}
}

void	expander(char **st, t_all *all)
{
	char	**tmp;
	char	**origin;
	char	*s;
	char	*sst;

	origin = ft_split_delete(*st, ' ');
	tmp = ft_split_delete(*st, ' ');
	ft_exp_utils(tmp, &s, &sst, all);
	ft_fandr(&s, st, tmp, origin);
	freetable(tmp);
	freetable(origin);
	free(*st);
	*st = s;
}

void	leaks(void)
{
	system("leaks minishell");
}
