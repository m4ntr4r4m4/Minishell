#include "minishell.h"

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

char	*check_bin(char *binary, char *path, int ac)
{
	int		x;

	if (ac == 2)
		x = access(ft_strjoin(path, binary), W_OK);
	if (ac == 1)
		x = access(ft_strjoin(path, binary), R_OK);
	if (ac == 3)
		x = access(ft_strjoin(path, binary), X_OK);
	if (x == 0)
		return (ft_strjoin(path, binary));
	return (NULL);
}

char *get_path(char **pathvar, char *cmd, int code)
{
	int		i;
	char 	*path;

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



int	main(int ac, char **av, char **envp)
{
//	atexit(leaks);
	t_cmd	cmd;
	int	i;	
	i = 0;
	if (ac || av)
	{
		cmd.num_args = ac - 2;
		cmd.name = av[i + 1];
		cmd.args = malloc(sizeof(char*) * cmd.num_args + 1);
		cmd.args[cmd.num_args] = NULL;
		printf("%d\n", cmd.num_args);
		cmd.pathvar = path_var(envp);
		cmd.path = get_path(cmd.pathvar, cmd.name, 3);
		while(i < cmd.num_args)
		{
			cmd.args[i] = get_path(cmd.pathvar, av[i + 2], 1);
			i++;
		}
	//	printf("%s\n", cmd.name);
	//	ft_print_table(cmd.pathvar, 1);
	//	ft_print_table(cmd.args, 1);
		printf("%s\n", cmd.path);
		if (execve(cmd.path, cmd.args, envp) < 0)
		{
			perror("command");
			exit(0);
		}

		freecmd(&cmd);
	}


}
