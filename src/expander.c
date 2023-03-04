/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:17:24 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/04 11:36:09 by ahammoud         ###   ########.fr       */
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
		if (tab[i + 1] != NULL)
		{
			*tmp1 = ft_strjoin(*tmp2, " ");
			free(*tmp1);
		}
	}
}

char	*ft_merge(char **tab)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	if (ft_get_size(tab))
	{
		tmp2 = malloc(sizeof(char));
		if (!tmp2)
			return (0);
		if (tab[1])
			tmp1 = ft_strjoin(tab[0], " ");
		else
			tmp1 = ft_strjoin(tab[0], "");
		if (tab[1] == NULL || tab[1][0] == '\0')
		{
			free(tmp2);
			return (tmp1);
		}
		ft_merge_utils(&str, &tmp1, &tmp2, tab);
		return (str);
	}
	return (0);
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
				continue ;
			}
			*sst = ft_strtrimtail(tmp[i], *s);
			*s = ft_mygetenv(*s, all);
			free(tmp[i]);
			tmp[i] = ft_strjoin(*sst, *s);
			if (*sst)
				free(*sst);
		}
	}
	fprintf(stderr, "**********************  out exp utils.\n");
}

void	ft_fandr(char **s, char **st, char **tmp, char **origin)
{
	int		i;
	char	*sst;

	i = -1;
	fprintf(stderr, "this inside fand %s.\n", *st);
	*s = ft_strdup(*st);
	while (tmp[++i + 1])
	{
		sst = replaceword(*s, origin[i], tmp[i]);
		free(*s);
		*s = sst;
	}
	fprintf(stderr, "this inside fand %d.%d.\n", i,  (int)tmp[i][0]);
	if (tmp[i][0] != 0)
	{
		sst = replaceword(*s, origin[i], tmp[i]);
		free(*s);
		*s = sst;
	}
	fprintf(stderr, "this inside fand %d.%d.\n", i,  (int)tmp[i][0]);
}

void	expander(char **st, t_all *all)
{
	char	**tmp;
	char	**origin;
	char	*s;
	char	*sst;

	fprintf(stderr, "this exp: %s.\n", *st);
	fprintf(stderr, "********************** %s.\n", *st);
	origin = ft_split_delete(*st, ' ');
	fprintf(stderr, "********************** %s.\n", *st);
	ft_print_table(origin, 2);
	tmp = ft_split_delete(*st, ' ');
	fprintf(stderr, "********************** %s.\n", *st);
	ft_print_table(tmp, 2);
	fprintf(stderr, "********************** %s.\n", *st);
	ft_exp_utils(tmp, &s, &sst, all);
	ft_fandr(&s, st, tmp, origin);
	fprintf(stderr, "**********************  after fandr%s.\n", *st);
	freetable(tmp);
	freetable(origin);
	free(*st);
	*st = s;
	fprintf(stderr, "this exp: %s.\n", *st);
}
