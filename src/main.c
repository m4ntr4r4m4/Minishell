#include "minishell.h"

int	main(int ac,char **av,  char **envp)
{
//	atexit(leaks);
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**at;
	t_all	all;
	int	i;	

	i = 0;
	av = NULL;
	if (ac)
	{
		cmd1.pathvar = path_var(envp);
		char *rd = NULL;
		while(1)
		{
			////////    PArser        //////////

//			rd = readline("$_MINI-SHELL_$: ");
			rd = "cat a";
//			printf("---%s\n", rd);
			if(rd && word_c(rd, ' ') >= 1)
			{
//				printf("begin\n");
				at = ft_split(rd, ' ');
				cmd_init(&cmd1, word_c(rd, ' '), at,  envp);
				rd = "grep my";
				cmd_init(&cmd2, word_c(rd, ' '), at,  envp);
			
//			printf("---EROROR\n");
			////////    EXECUTOR        //////////
				all.size = 1;
				all.cmd = malloc(sizeof(t_cmd) * all.size);
				if(!all.cmd)
					return (0);
				all.cmd[0] = cmd1;
//				all.cmd[1] = cmd2;

				executor(&all, envp);
				
//				printf(" before freeed*******\n");
				freecmd(&all);
//				printf("freeed*******\n");
				i = -1;
				while (at[++i])
					free(at[i]);
				free(at);

			}
			sleep(1);
//			free(rd);
		}
	}


}
