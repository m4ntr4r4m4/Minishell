#include "minishell.h"

void	lexer_check(char token, t_all *all, t_i *i, char **str)
{
	if (token == LESS)
	{
		all->cmd[i->c].infile[i->i++] = ft_strdup(str[i->s + 1]);
		all->cmd[i->c].token[0] = token;
		i->s++;
	}
	else if (token == LESSLESS)
	{
		all->cmd[i->c].token[2] = token;
		all->cmd[i->c].eof[i->eof++] = ft_strdup(str[++i->s]);
	}
	else if (token == GREAT || token == GREATGREAT)
	{
		i->c_o = 1;
		if (token == GREAT)
			all->cmd[i->c].token[1] = token;
		else
			all->cmd[i->c].token[3] = token;
		all->cmd[i->c].outfile[i->o++] = ft_strdup(str[++i->s]);
	}
	else if (token == CONTINUE)
		all->cmd[i->c].args[i->a++] = ft_strdup(str[i->s]);
}

void	lexer_pipe(char token, t_all *all, t_i *i, char **str)
{
	if (token == PIPE || token == AMPERSAND)
	{
		i->a = 0;
		i->o = 0;
		i->i = 0;
		i->t = 0;
		i->eof = 0;
		++i->c;
		++i->s;
		all->token_l[i->t2++] = token;
	}
	else
		i->a--;
	all->cmd[i->c].name = ft_strdup(str[i->s]);
	all->cmd[i->c].path = get_path(all->path, str[i->s], 3);
	if (!all->cmd[i->c].path)
		all->cmd[i->c].path = ft_strdup(str[i->s]);
	all->cmd[i->c].args[i->a++] = ft_strdup(all->cmd[i->c].path);
}

void	fill_struct(char **str, t_all *all, t_i *i, int *path)
{
	all->cmd[i->c].name = ft_strdup(str[i->s]);
	all->cmd[i->c].path = get_path(all->path, str[i->s], 3);
	if (!all->cmd[i->c].path)
	{
		if (!ft_strncmp(str[i->s], "<", 1)
			|| !ft_strncmp(str[i->s], ">", 1))
			*path = 0;
		all->cmd[i->c].path = ft_strdup(str[i->s]);
	}
	all->cmd[i->c].args[i->a++] = ft_strdup(all->cmd[i->c].path);
	if (i->r == CONTINUE)
		i->s++;
}

char	lexer(char **str, t_all *all)
{
	char	token;
	int		path;
	t_i		i;

	path = 1;
	init_iterators(&i);
	i.r = tokens(str[i.s]);
	fill_struct(str, all, &i, &path);
	while (str[i.s])
	{
		token = tokens(str[i.s]);
		if (token == PIPE || token == AMPERSAND
			|| (!path && token == CONTINUE))
		{
			lexer_pipe(token, all, &i, str);
			path = 1;
		}
		else
			lexer_check(token, all, &i, str);
		i.s++;
	}
	return (CONTINUE);
}
