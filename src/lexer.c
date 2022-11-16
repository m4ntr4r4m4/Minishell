#include "minishell.h"

/* TO DO */

/* control de argumentos con quotes */

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
	int		quote;

	quote = 0;
	init_iterators(&i);
	all->cmd[i.c].name = str[i.s];
	all->cmd[i.c].path = get_path(all->path, str[i.s++], 3);
	all->cmd[i.c].args[i.a++] = all->cmd[i.c].path;
	while(str[i.s])
	{
		token = tokens(str[i.s]);
		/* si tiene " */
		/* activar */
		if (str[i.s][0] == 34)
			quote += 1;
		if (token == PIPE || token == AMPERSAND)
		{
			all->token_l[i.T++] = token;
			all->cmd[++i.c].name = str[++i.s];
			all->cmd[i.c].path = get_path(all->path, str[i.s], 3);
			i.a = 0;
			all->cmd[i.c].args[i.a++] = all->cmd[i.c].path;
			i.o = 0;
			i.i = 0;
			i.t = 0;
		}
		else if (token == LESS || token == LESSLESS)
		{
			all->cmd[i.c].token[i.t++] = token;
			all->cmd[i.c].infile[i.i++] = str[++i.s];
		}
		else if (token == GREAT || token == GREATGREAT)
		{
			all->cmd[i.c].token[i.t++] = token;
			all->cmd[i.c].outfile[i.o++] = str[++i.s];
		}
		else if (token == CONTINUE && quote % 2 == 0)
			all->cmd[i.c].args[i.a++] = str[i.s];
		else
			all->cmd[i.c].token[i.t++] = token;
		i.s++;
	}
	return (CONTINUE);
}

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

int	search_token(t_all *all,char **str)
{
	int	i;
	char		token;

	i = all->i_t;
	all->s_t = 0;
	while(str[i])
	{
		token = tokens(str[i]);
		if (token != PIPE && token != AMPERSAND && token != CONTINUE)
			all->s_t++;
		else if (token != CONTINUE)
		{
			i++;
			break;
		}
		i++;
	}
	all->i_t = i;
	return (all->s_t);
}

int	search_arg(t_all *all,char **str)
{
	int			i;
	char		token;
	int			bol;

	all->s_t = 0;
	bol = 0;
	i = all->i_a;
	while(str[++i])
	{
		token = tokens(str[i]);
		if (!bol && token == CONTINUE)
			all->s_t++;
		else if (token == PIPE || token == AMPERSAND) 
		{
			i++;
			break;
		}
		else
			bol = 1;
	}
	all->i_a = i;
	return (++all->s_t);
}

void	search_files(t_all *all,char **str)
{
	int			i;
	char		token;

	all->s_i = 0;
	all->s_o = 0;
	i = all->i_f;
	while(str[++i])
	{
		token = tokens(str[i]);
		if (token == LESS || token == LESSLESS)
			all->s_i++;
		else if (token == GREAT || token == GREATGREAT) 
			all->s_o++;
		else if (token == PIPE || token == AMPERSAND) 
		{
			i++;
			break;
		}
	}
	all->i_f = i;
}

void	init_structs(t_all *all, char **str)
{
	int	x;

	x = -1;
	all->i_t = 0;
	all->i_f = 0;
	all->i_a = 0;
	all->cmd = (t_cmd *)malloc(sizeof(*(all->cmd)) * all->size);
	all->token_l = (char *)malloc(sizeof(char *) * all->size);
	bzero(all->token_l, all->size);
	while (++x < all->size)
	{
		all->cmd[x].token = (char *)malloc(search_token(all, str) + 1);
		all->cmd[x].token[all->s_t] = '\0';
		all->cmd[x].args = (char **)malloc(sizeof(char **) * (search_arg(all, str) + 1));
		all->cmd[x].args[all->s_t] = '\0';
		search_files(all, str);
		all->cmd[x].outfile = (char **)malloc(sizeof(char **) * (all->s_o + 1));
		all->cmd[x].outfile[all->s_o] = '\0';
		all->cmd[x].infile = (char **)malloc(sizeof(char **) * (all->s_i + 1));
		all->cmd[x].infile[all->s_i] = '\0';
	}
}

char	*check_quotes(char **str)
{
	int	x;
	int	y;
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	y = -1;
	while(str[++y])
	{
		x = -1;
		while (str[y][++x])
		{
			if (str[y][x] == 34)
				d_q++;
			if (str[y][x] == 39 && str[y][0] != 34)
				s_q++;
			if (str[y][x] == 59 || str[y][x] == 92)
				return NULL;
		}
	}
	if (d_q % 2 != 0 || s_q % 2 != 0)
		return NULL;
	return GOOD;
}

/* cmd arg simbol file */
char	*check_simbols(char **str)
{
	int		y;
	char	token;
	int		vol;

	vol = 0;
	y = -1;
	while(str[++y])
	{
		token = tokens(str[y]);
		if (vol == 1 && token != CONTINUE)
			break;
		else if (token != CONTINUE)
			vol = 1;
		else
			vol = 0;
	}
	if (vol == 1)
		return NULL;
	return GOOD;
}

char **parser(char **str, t_all *all)
{

	/* CHECK ERRORS AND FILL SIZES*/
	if (check_quotes(str) == NULL)
	{
		printf("\033[1;31mquotes error \n\033[0m");
		all->size = 0;
		return str;
	}
	if (check_simbols(str) == NULL)
	{
		printf("\033[1;31mparse error\n\033[0m");
		all->size = 0;
		return str;
	}
	/* look for cmds */
	if (search_cmd(all, str) == NULL)
	{
		printf("\033[1;31mcommand not found\n\033[0m");
		return str;
	}
	else
	{
		/* INICIALICE */ 
		init_structs(all, str);
		/* LEXER */ 
		lexer(str, all);

		/* PRINT */
		print_all(all);
	}
	return str;
}
/* enlaza los simbolos con comandos para que entienda el parser y los add a la tabla */
char tokens(char *token)
{
	if (!strcmp(token, ">"))
		return GREAT;
	else if (!strcmp(token, "<"))
		return LESS;
	else if (!strcmp(token, "<<"))
		return LESSLESS;
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
