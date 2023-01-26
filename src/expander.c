/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:17:24 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/25 17:25:52 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expander(char *st, t_all *all)
{
	char	**tmp;

	tmp = ft_split_parse(st, ' ');
	ft_print_table(tmp, 1);


	freetable(tmp);

	return(st);
}

void	leaks(void)
{
	system("leaks a.out");
//	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	int i = -1;
	char *rd;
	rd = "'echo $PWD $PWD'";
	t_all all;
	atexit(leaks);
	
	printf("this envp size: %zu\n", ft_get_size(envp));
	ft_env_init(envp, &all);

	rd = expander(rd, &all);

//	printf("this env var: %s\n", ft_mygetenv("$PWD", &all));
//	ft_export("hrllo I am Here!", &all);
	size_t	x = ft_get_size(all.myenv);
//	printf("this myenvp size: %zu\n", x);
	while(++i < x)
		free(all.myenv[i]);
	free(all.myenv);
}
