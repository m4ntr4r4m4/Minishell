#include "minishell.h"

void	all_fill(t_all *all)
{
	all->size = 1;
	all->cmd = malloc(sizeof(*all->cmd) * 1);
	all->cmd[0].path = get_path(all->path, "ls", X_OK);
	fprintf(stderr, "thdhfgkhjk ************ %s\n", all->cmd[0].path);
	all->cmd[0].name = strdup("ls");
	all->cmd[0].args = malloc(sizeof(*all->cmd[0].args) * 2);
	all->cmd[0].infile = malloc(sizeof(*all->cmd[0].infile) * 2);
	all->cmd[0].outfile = malloc(sizeof(*all->cmd[0].outfile) * 2);
	all->cmd[0].infile[0] = strdup("/bin/ls");
	all->cmd[0].outfile[0] = strdup("/bin/ls");
	all->cmd[0].args[0] = strdup("/bin/ls");
	all->cmd[0].n_tokens = 0;
}

int	main(int ac,char **av,  char **envp)
{
	t_all	all;
	char *rd;
	char **new;

	all.exit_var = 0;
//	atexit(leaks);
	while(1)
	{
	      	rd = readline("$_MINI_SHELL_$:");
			if (strncmp(rd, "\0", 1))
			{
				add_history (rd);
				ft_env_init(envp, &all);
	  		   	all.path = path_var(all.myenv);

			//	all_fill(&all);
	      	/* printf("%s\n", rd); */
	      	/* ft_print_table(new, 1); */
		      	new = parser(rd, &all, all.myenv);
	      	/* executer */
	
				if (new)
			      	prexec(&all, all.myenv);
			}
	
	      	/* free */
	      	free(rd);
	}
	return 0;
}
