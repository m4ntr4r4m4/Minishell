#include "../includes/minishell.h"
#include "libft/ft_split.c"
#include "libft/ft_substr.c"
#include "libft/ft_strlen.c"
#include "libft/ft_print_table.c"
#include "libft/ft_putstr_fd.c"
#include "libft/ft_putchar_fd.c"

#define AMPERSAND '1'
#define GREAT '2'
#define GREATAMPERSAND '3'
#define GREATGREAT '4'
#define LESS '5'
#define LESSLESS '6'
#define PIPE '7'
#define CONTINUE '8'

static char tokens(char *tokens);

/* TO DO */
/* check_error */
/* tratar de saber si es executable o no y que devuelva los size */

/* ITERATORS
	 *
	 * String -> i_s;	
	 * Command -> i_c;
	 * Token of all -> i_T;
	 * Token of command -> i_t;
	 * arguments -> i_a;
*/
void	init_iterators(t_i *i)
{
	i->s = 0;
	i->c = 0;
	i->t = 0;
	i->T = 0;
	i->a = 0;
}

/* READ DE COMMAND AND FILL THE STRUCT */
char lexer(char **str, t_all *all)
{
	char	token;
	t_i		i;

	init_iterators(&i);
	all->cmd[i.c].name = str[i.s++];
	while(str[i.s])
	{
		token = tokens(str[i.s]);
		if (token == PIPE || token == AMPERSAND)
		{
			all->token_l[i.T++] = token;
			all->cmd[i.c].args[i.a] = NULL;
			i.a = 0;
			i.c++;
		}
		else if (token == CONTINUE)
			all->cmd[i.c].args[i.a++] = str[i.s];
		else
			all->cmd[i.c].token[i.t++] = token;
		i.s++;
	}
	all->cmd[i.c].args[i.a] = NULL;
	return (CONTINUE);
}


void	init_structs(t_all *all, int count)
{
	int	x;

	x = 0;
	all->cmd = (t_cmd *)malloc(sizeof(*(all->cmd)) * count);
	all->token_l = (char *)malloc(sizeof(char *) * count);
	bzero(all->token_l, count);
	while (x < count)
	{
		all->cmd[x].token = (char *)malloc(count);
		bzero(all->cmd[x].token, count);
		all->cmd[x++].args = (char **)malloc(sizeof(char **) * count);
	}
}

/* crea la tabla de comandos */
char **parser(char **str, int count)
{
	t_all	all;
	int		x = 0;

	/* CHECK ERRORS AND FILL SIZES*/ 
		/* cmd->path = get_path(cmd->pathvar, cmd->name, 3); */
		/* check_error() */
	/* CHECK ERRORS AND FILL SIZES*/ 
	
	/* INICIALICE */ 
	init_structs(&all, count);
	/* INICIALICE */ 

	/* LEXER */ 
	lexer(str, &all);
	/* LEXER */ 

	x = 0;
	int y = 0;

	/* print all */
	while (all.cmd[y].args[x])
	{
		while (all.cmd[y].args[x])
			printf("arg %d %s\n", y,all.cmd[y].args[x++]);
		x = 0;
		while (all.cmd[y].token[x])
			printf("tokens %c\n", all.cmd[0].token[x++]);
		x = 0;
		y++;
	}
	x = 0;
	while (all.token_l[x])
		printf("T %c\n", all.token_l[x++]);
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

void	freetable(char **new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		printf("free: %s\n", new[i]);
		free(new[i++]);
	}
	free(new[i]);
	free(new);
}

void 	leaks(void)
{
	system("leaks a.out");
}

int	main(int argc, char **argv)
{
	char *rd;
	char **new;
	int count;

	atexit(leaks);
	while(1)
	{
		rd = readline("$:");
		count = word_c(rd, ' ');
		new = ft_split(rd,' ');
		parser(new, count);
		ft_print_table(new, 1);
		free(rd);
		freetable(new);
	}
	return 0;
}
