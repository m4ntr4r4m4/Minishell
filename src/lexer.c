#include "minishell.h"

void	init_iterators(t_i *i)
{
	i->s = 0;
	i->c = 0;
	i->t = 0;
	i->T = 0;
	i->a = 0;
	i->i = 0;
	i->o = 0;
}

/* READ DE COMMAND AND FILL THE STRUCT */
	char lexer(char **str, t_all *all)
	{
		char	token;
		t_i		i;
	
		init_iterators(&i);
		all->cmd[i.c].name = str[i.s];
		all->cmd[i.c].path = get_path(all->path, str[i.s++], 3);
		all->cmd[i.c].args[i.a++] = all->cmd[i.c].path;
		while(str[i.s])
		{
			token = tokens(str[i.s]);
			if (token == PIPE || token == AMPERSAND)
			{
				all->token_l[i.T++] = token;
				all->cmd[i.c].args[i.a] = NULL;
				all->cmd[i.c].infile[i.i] = NULL;
				all->cmd[i.c].outfile[i.o] = NULL;
				all->cmd[++i.c].name = str[++i.s];
				all->cmd[i.c].path = get_path(all->path, str[i.s], 3);
				i.a = 0;
				all->cmd[i.c].args[i.a] = all->cmd[i.c].path;
				i.o = 0;
				i.i = 0;
				i.t = 0;
			}
			else if (token == LESS)
			{
				all->cmd[i.c].token[i.t++] = token;
				all->cmd[i.c].infile[i.i++] = str[++i.s];
			}
			else if (token == GREAT)
			{
				all->cmd[i.c].token[i.t++] = token;
				all->cmd[i.c].outfile[i.o++] = str[++i.s];
			}
			else if (token == CONTINUE)
				all->cmd[i.c].args[i.a++] = str[i.s];
			else
				all->cmd[i.c].token[i.t++] = token;
			i.s++;
		}
		all->cmd[i.c].args[i.a] = NULL;
		all->cmd[i.c].infile[i.i] = NULL;
		all->cmd[i.c].outfile[i.o] = NULL;
		return (CONTINUE);
	}


void	init_structs(t_all *all, int count)
{
	int	x;

	x = -1;
	all->cmd = (t_cmd *)malloc(sizeof(*(all->cmd)) * count);
	all->token_l = (char *)malloc(sizeof(char *) * count);
	bzero(all->token_l, count);
	while (++x < all->size)
	{
		all->cmd[x].token = (char *)malloc(count);
		bzero(all->cmd[x].token, count);
		all->cmd[x].args = (char **)malloc(sizeof(char **) * count);
		all->cmd[x].outfile = (char **)malloc(sizeof(char **) * count);
		all->cmd[x].infile = (char **)malloc(sizeof(char **) * count);
	}
}


/* recorrer array */
/* ver numero de comandos */
/* asignar la ruta de los comandos */
/* return number of cmds */
char	*search_cmd(t_all *all, char **str)
{
	int		x;
	int		bol;
	char	*path;
	char	token;

	x = 0;
	all->size = 0;
	bol = 0;
	path = NULL;
	while (str[x])
	{
		token = tokens(str[x]);
		if (bol)
		{
			path = get_path(all->path, str[x], 3);
			if (path == NULL)
				return path;
			all->size++;
			bol = 0;
		}
		else if (x == 0)
		{
			path = get_path(all->path, str[x], 3);
			if (path == NULL)
				return path;
			all->size++;
		}
		else if (token == PIPE || token == AMPERSAND)
			bol = 1;
		x++;
	}
	return path;
}



/* crea la tabla de comandos */
char **parser(char **str, int count, t_all *all)
{

	/* CHECK ERRORS AND FILL SIZES*/ 
		/* check_error() */
		/* cmd->path = get_path(cmd->pathvar, cmd->name, 3); */
	
	/* look for cmds */
	if (search_cmd(all, str) == NULL)
	{
		printf("\033[1;31mcommand not found\n\033[0m");
		return str;
	}
	
	/* INICIALICE */ 
	fprintf(stderr, "count : %d\n", count);
	init_structs(all, count);

	fprintf(stderr,"********problem resolved\n");

	/* LEXER */ 
	lexer(str, all);

	/* PRINT */
	print_all(all);
	return str;
}
/* enlaza los simbolos con comandos para que entienda el parser y los add a la tabla */
char tokens(char *token)
{
	if (!strcmp(token, ">"))
		return GREAT;
	else if (!strcmp(token, "<"))
		return LESS;
	else if (!strcmp(token, ">>"))
		return GREATGREAT;
	else if (!strcmp(token, ">>"))
		return GREATGREAT;
	else if (!strcmp(token, ">&"))
		return GREATAMPERSAND;
	else if (!strcmp(token, "|"))
		return PIPE;
	else if (!strcmp(token, "&"))
		return AMPERSAND;
	else
		return CONTINUE;
}
