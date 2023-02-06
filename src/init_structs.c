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
	i->c_i = 0;
	i->eof = 0;
	i->c_o = 0;
}

int	init_fill(int x, char **str, t_all *all, int s)
{
	all->cmd[x].token = malloc(sizeof(int) * 4);
	while (++s < 4)
		all->cmd[x].token[s] = 0;
	if (!all->cmd[x].token)
		return (0);
	all->cmd[x].n_tokens = 4;
	all->cmd[x].args = malloc(sizeof(char *) * (search_arg(all, str) + 1));
	if (!all->cmd[x].args)
		return (0);
	all->cmd[x].args[all->s_t] = NULL;
	search_files(all, str);
	all->cmd[x].eof = malloc(sizeof(char *) * (all->s_eof + 1));
	if (!all->cmd[x].eof)
		return (0);
	all->cmd[x].eof[all->s_eof] = NULL;
	all->cmd[x].outfile = malloc(sizeof(char *) * (all->s_o + 1));
	if (!all->cmd[x].outfile)
		return (0);
	all->cmd[x].outfile[all->s_o] = NULL;
	all->cmd[x].infile = malloc(sizeof(char *) * (all->s_i + 1));
	if (!all->cmd[x].infile)
		return (0);
	all->cmd[x].infile[all->s_i] = NULL;
	return (1);
}

void	init_structs(t_all *all, char **str)
{
	int	x;

	search_cmd(all, str);
	x = -1;
	all->i_t = 0;
	all->i_f = 0;
	all->i_a = 0;
	all->s_eof = 0;
	if (all->size == 0)
		all->size = 1;
	all->cmd = malloc(sizeof(*(all->cmd)) * all->size);
	if (!all->cmd)
		return ;
	all->token_l = malloc(sizeof(int) * (all->size - 1));
	if (!all->token_l)
		return ;
	while ((size_t)++x < all->size)
	{
		if (!init_fill(x, str, all, -1))
			return ;
	}
}
