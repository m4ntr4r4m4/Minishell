/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/08 17:48:07 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *path, t_all *all)
{
	char	*buff;
	char	*pwd;
	char	*oldpwd;
	int		i;

	i = 0;
	fprintf(stderr,"____________ inside cd func %s\n", path);
	fprintf(stderr,"____________ inside cd func all address %p\n", all);
	if (!chdir(path))
	{
		fprintf(stderr,"____________ SUCCESS\n");
		buff = malloc(sizeof(char) * PATH_MAX);
		if (getcwd(buff, PATH_MAX) == NULL)
			perror("getcwd() error");
		pwd = ft_strdup(ft_mygetenv("PWD", all));
		oldpwd = ft_mygetenv("OLDPWD", all);
		i = 0;
		while (ft_strncmp(all->myenv[i], "PWD", 3))
			i++;
		free(all->myenv[i]);
		all->myenv[i] = ft_strjoin("PWD=", buff);
		i = 0;
		while (ft_strncmp(all->myenv[i], "OLDPWD", 6))
			i++;
		free(all->myenv[i]);
		all->myenv[i] = ft_strjoin("OLDPWD=", pwd);
		free(pwd);
		free(buff);
		return (0);
	}
	return (1);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	printf("%s\n", buff);
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

void	ft_echo(int *i,  t_all *all)
{
	int		j;
	char	*str;

	j = 1;

	while (!ft_strncmp(all->cmd[*i].args[j], "-n", 2) && ft_strlen(all->cmd[*i].args[j]) == 2)
		j++;
	str = ft_merge(&(all->cmd[*i].args[j]));
	if (j > 1)
		ft_putstr_fd(str, 1);
	else
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
}


void	ft_builtins(t_all *all, int i)
{
	int	x;

	x = 1;
	if (!strncmp(all->cmd[i].name, "echo", 4))
			ft_echo(&i, all);
	if (!strncmp(all->cmd[i].name, "pwd", 3))
		ft_pwd();
	if (!strncmp(all->cmd[i].name, "cd", 2))
		ft_cd(all->cmd[i].args[1], all);
	x = 1;
	if (!strncmp(all->cmd[i].name, "unset", 5))
		while (all->cmd[i].args[x])
			ft_unset(all->cmd[i].args[x++], all);
	if (!strncmp(all->cmd[i].name, "exit", 4))
		ft_exit();
	if (!strncmp(all->cmd[i].name, "env", 3))
		ft_print_table(all->myenv, 1);
	if (!strncmp(all->cmd[i].name, "export", 6))
		ft_export(all->cmd[i].args[1], all);

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
