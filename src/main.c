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
	  		   	all.path = path_var(envp);

			//	all_fill(&all);
	      	/* printf("%s\n", rd); */
	      	/* ft_print_table(new, 1); */
		      	new = parser(rd, &all, envp);
	      	/* executer */
	
				if (new)
			      	prexec(&all, envp);
			}
	
	      	/* free */
	      	free(rd);
	}
	return 0;
}


//	t_all	all;
//	char *rd;
//	char **new;
//	int count;
//
//	all.path = path_var(envp);
//	atexit(leaks);
//	//while(1)
//	int i = 5;
//	while(i-- > 0)
//	{
//		rd = readline("$:");
//		fprintf(stderr, "char   rd= %s\n", rd);
//		if(rd && word_c(rd, ' ') >= 1)
//		{
//			count = word_c(rd, ' ');
//			new = ft_split(rd,' ');
//			ft_print_table(new, 1);
//			parser(new, count, &all);
//		//	ft_print_table(new, 1);
//			///////
//			// EXECUTER		
//		//	print_all(&all);
//
//			fprintf(stderr, "************************ going to execute *****************\n");
//			prexec(&all, envp);
//					
//			///////
//			freetable(new);
//		}
//		free(rd);
//		//freecmd(&all);
//	}
//	return 0;
//}
//

//	fprintf(stderr, "************ hello im inside minishell *******\n");
//
//	//	atexit(leaks);
//		t_cmd	cmd1;
//		t_cmd	cmd2;
//		t_cmd	cmd3;
//		char	**at;
//		char	**at2;
//		t_all	all;
//		int	i;	
//	
//		i = 0;
//		av = NULL;
//		if (ac)
//		{
//			cmd1.pathvar = path_var(envp);
//		//	cmd2.pathvar = cmd1.pathvar;
//		//	cmd3.pathvar = cmd1.pathvar;
//			char *rd = NULL;
//			while(1)
//			{
//				////////    PArser        //////////
//				rd = readline("$_MINI-SHELL_$: ");
//	//			rd = "cat a";
//	//			printf("---%s\n", rd);
//				if(rd && word_c(rd, ' ') >= 1)
//				{
//	//				printf("begin\n");
//					at = ft_split(rd, ' ');
//					cmd_init(&cmd1, word_c(rd, ' '), at,  envp);
//					freetable(at);
//					free(rd);
//	//				rd = "grep my";
//		//			rd = readline("PIPE: ");
//		//			at2 = ft_split(rd, ' ');
//		//			cmd_init(&cmd2, word_c(rd, ' '), at2,  envp);
//		//			rd = readline("PIPE: ");
//		//			at = ft_split(rd, ' ');
//		//			freetable(at2);
//		//			cmd_init(&cmd3, word_c(rd, ' '), at,  envp);
//		//			free(rd);
//		//			freetable(at);
//				
//	//			printf("cmd1 : %s cmd2 : %s\n", cmd1.name, cmd2.name);
//	//			printf("---EROROR\n");
//				////////    EXECUTOR        //////////
//					all.size = 1;
//					all.cmd = malloc(sizeof(t_cmd) * all.size);
//					if(!all.cmd)
//						return (0);
//					all.cmd[0] = cmd1;
//		//			all.cmd[1] = cmd2;
//		//			all.cmd[2] = cmd3;
//		//			all.token = '|';
//	
//		//			print_all(&all);
//					prexec(&all, envp);
//					
//	//				printf(" before freeed*******\n");
//	//				freecmd(&all);
//	//				printf("freeed*******\n");
//	
//				}
//			}
//		}
//	
//	}
