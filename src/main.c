#include "minishell.h"

int	main(int ac,char **av,  char **envp)
{
	t_all	all;
	char *rd;
	char **new;

	all.path = path_var(envp);
	all.size = 0;
	atexit(leaks);
	
	int x = -1;
	int i = -1;
	while(++x < 3)
	{
			/* printf("%s\n", rd); */
			/* ft_print_table(new, 1); */
		rd = readline("$:");

		/* add space to tokens */
		rd = check_spaces(rd);
		printf("rd %s\n",rd);
		if (rd != NULL)
		{
			new = parser(rd, &all, envp);
			/* executer */
			//prexec(&all, envp);
			//
			/* cmd free */
			if (rd)
				free(rd);
			printf("hola\n");
			if (new != NULL)
			{
				 i = -1;
				while(new[++i])
					free(new[i]);
				free(new);
			}
			freecmd(&all);
			/* cmd free */
		}
	}
	/* global free */
	i = -1;
	while(all.path[++i])
			free(all.path[i]);
	free(all.path);
	/* global free */
	return 0;
}

//
//
////	atexit(leaks);
//	t_cmd	cmd1;
//	t_cmd	cmd2;
//	t_cmd	cmd3;
//	char	**at;
//	char	**at2;
//	t_all	all;
//	int	i;	
//
//	i = 0;
//	av = NULL;
//	if (ac)
//	{
//		cmd1.pathvar = path_var(envp);
//		cmd2.pathvar = cmd1.pathvar;
//	//	cmd3.pathvar = cmd1.pathvar;
//		char *rd = NULL;
//		while(1)
//		{
//			////////    PArser        //////////
//			rd = readline("$_MINI-SHELL_$: ");
////			rd = "cat a";
////			printf("---%s\n", rd);
//			if(rd && word_c(rd, ' ') >= 1)
//			{
////				printf("begin\n");
//				at = ft_split(rd, ' ');
//				cmd_init(&cmd1, word_c(rd, ' '), at,  envp);
//				freetable(at);
//				free(rd);
////				rd = "grep my";
//				rd = readline("PIPE: ");
//				at2 = ft_split(rd, ' ');
//				cmd_init(&cmd2, word_c(rd, ' '), at2,  envp);
//	//			rd = readline("PIPE: ");
//	//			at = ft_split(rd, ' ');
//				freetable(at2);
//	//			cmd_init(&cmd3, word_c(rd, ' '), at,  envp);
//				free(rd);
//	//			freetable(at);
//			
////			printf("cmd1 : %s cmd2 : %s\n", cmd1.name, cmd2.name);
////			printf("---EROROR\n");
//			////////    EXECUTOR        //////////
//				all.size = 2;
//				all.cmd = malloc(sizeof(t_cmd) * all.size);
//				all.pipes = malloc(sizeof(t_pipe) * (all.size - 1));
//				if(!all.cmd)
//					return (0);
//				prexec(&all, envp);
//				all.cmd[0] = cmd1;
//				all.cmd[1] = cmd2;
//	//			all.cmd[2] = cmd3;
//	//			all.token = '|';
//
//				
////				printf(" before freeed*******\n");
//				freecmd(&all);
////				printf("freeed*******\n");
//				i = -1;
//
//			}
//		}
//	}
//

