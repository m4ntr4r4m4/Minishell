/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:17:24 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/26 18:23:14 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_merge(char **tab)
{
	int		i;
	char	*str;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	tmp2 = malloc(sizeof(char));
	tmp1 = ft_strjoin(tab[0], " ");
	while (tab[++i])
	{
		if (*tab[i] == '\0')
			continue ;
		free(tmp2);
		tmp2 = ft_strjoin(tmp1, tab[i]);
		free(tmp1);
		str = tmp2;
		tmp1 = ft_strjoin(tmp2, " ");
	}
	free(tmp1);
	return (str);
}

char	*expander(char *st, t_all *all)
{
	char	**tmp;
	int		i;
	char	*s;
	char	*sst;

	tmp = ft_split_parse(st, ' ');
	i = -1;
	while (tmp[++i])
	{
		s = ft_strrchr(tmp[i], '$');
		if (s)
		{
			sst = ft_strtrim(tmp[i], s);
			s = ft_mygetenv(s, all);
			free(tmp[i]);
			tmp[i] = ft_strjoin(sst, s);
			free(sst);
		}
	}
	s = ft_merge(tmp);
	freetable(tmp);
	free(st);
	return (s);
}

void	leaks(void)
{
//	system("leaks a.out");
	system("leaks minishell");
}
/*
int	main(int ac, char **av, char **envp)
{
	int i = -1;
	char *rd;
	rd = strdup("echo hola$PWD $CONDA $PWD $1PWD");
	t_all all;
	atexit(leaks);
	
	printf("this envp size: %zu\n", ft_get_size(envp));
	ft_env_init(envp, &all);

	rd = expander(rd, &all);

	printf("this rd: %s\n", rd);
	free(rd);

//	printf("this env var: %s\n", ft_mygetenv("$PWD", &all));
//	ft_export("hrllo I am Here!", &all);
	size_t	x = ft_get_size(all.myenv);
//	printf("this myenvp size: %zu\n", x);
	while(++i < x)
		free(all.myenv[i]);
	free(all.myenv);
}
*/
