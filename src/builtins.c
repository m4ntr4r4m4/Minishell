/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2022/12/28 17:53:12 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd();
char	*ft_mygetenv(char *str, t_all *all);
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

int		ft_cd(char *path, t_all *all)
{
	char *buff;
	char *pwd;
	char *oldpwd;
	int	i;

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

	if (!ft_mygetenv(st, all))
	{
		i = -1;
		x = ft_get_size(all->myenv);
		printf("this size %zu\n", x);
		tmp = malloc(sizeof(char *) * (x + 2));
		if (!tmp)
			return;
		tmp[x + 1] = NULL;
		while (++i < x)
			tmp[i] = all->myenv[i];
		tmp[i] = ft_strdup(st);
		free(all->myenv);
		all->myenv = tmp;
	}
}

void	ft_env(t_all *all)
{
	int	i;

	i = 0;
	while (all->myenv[i])
		printf("%s\n", all->myenv[i++]);
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
		return;
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

void	ft_exit()
{
	exit(0);
}

void	leaks()
{
	system("leaks a.out");
}


char	*ft_mygetenv(char *str, t_all *all)
{
	int	i;
	int len;
	char	*st;

	st = ft_strjoin(str, "=");
	i = -1;
	len = ft_strlen(st);
	while(all->myenv[++i])
	{
		if(!ft_strncmp(st, all->myenv[i], len))
		{
			free(st);
			return (all->myenv[i]);
		}
	}
	free(st);
	return (NULL);
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
