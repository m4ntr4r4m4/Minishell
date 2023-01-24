/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/18 15:48:16 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *str, int flag)
{
	if (!flag)
		printf("%s", str);
	else
		printf("%s\n", str);
}

int	ft_cd(char *path, t_all *all)
{
	char	*buff;
	char	*pwd;
	char	*oldpwd;
	int		i;

	i = 0;
	chdir(path);
	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	pwd = ft_strdup(ft_mygetenv("PWD", all));
	oldpwd = ft_mygetenv("OLDPWD", all);
	while (ft_strncmp(all->myenv[i], pwd, ft_strlen(pwd)))
		i++;
	free(all->myenv[i]);
	all->myenv[i] = ft_strjoin("PWD=", buff);
	i = 0;
	while (ft_strncmp(all->myenv[i], oldpwd, ft_strlen(oldpwd)))
		i++;
	free(all->myenv[i]);
	all->myenv[i] = ft_strjoin("OLD", pwd);
	free(pwd);
	free(buff);
	return (0);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	ft_echo(buff, 1);
	free(buff);
}

void	ft_unset(char *st, t_all *all)
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
		return ;
	tmp[x - 1] = NULL;
	while (++i < x - 1)
	{
		if (all->myenv[j] == st)
		{
			printf("free unset\n");
			free(all->myenv[j++]);
		}
		tmp[i] = all->myenv[j++];
	}
	if (all->myenv[i])
		free(all->myenv[j++]);
	free(all->myenv);
	all->myenv = tmp;
}

void	ft_exit(void)
{
	exit(0);
}

/*
int	main(int ac, char **av, char **envp)
{

	t_all all;
	int i = -1;
	ft_env_init(envp, &all);

//	atexit(leaks);


//	ft_env(&all);
	ft_cd("libft", &all);
//	ft_pwd();
//	ft_env(&all);

	ft_pwd();



//	ft_export("hello='echo hello my friend'", &all);
//	ft_unset("hello='echo hello my friend'", &all);
//	printf("thi is what i look for %s\n", ft_mygetenv("hello", &all));



	size_t	x = ft_get_size(all.myenv);
	while(++i < x)
		free(all.myenv[i]);
	free(all.myenv);

}
*/
