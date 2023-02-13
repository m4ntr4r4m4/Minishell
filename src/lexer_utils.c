/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:40:14 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 19:32:27 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_heredoc(char token, t_all *all, t_i *i, char **str)
{
	all->cmd[i->c].token[2] = token;
	all->cmd[i->c].eof[i->eof++] = ft_strdup(str[++i->s]);

}

void	lexer_check(char token, t_all *all, t_i *i, char **str)
{
	if (token == LESS)
	{
		all->cmd[i->c].infile[i->i++] = ft_strdup(str[i->s + 1]);
		all->cmd[i->c].token[0] = token;
		i->s++;
	}
	else if (token == LESSLESS)
		lexer_heredoc(token, all, i, str);
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
	i->a = 0;
	i->o = 0;
	i->i = 0;
	i->t = 0;
	i->eof = 0;
	all->token_l[i->t2++] = token;
	all->cmd[++i->c].name = ft_strdup(str[++i->s]);
	all->cmd[i->c].path = get_path(all->path, str[i->s], 3);
	if (!all->cmd[i->c].path)
		all->cmd[i->c].path = ft_strdup(str[i->s]);
	all->cmd[i->c].args[i->a++] = ft_strdup(all->cmd[i->c].path);
}

char	lexer(char **str, t_all *all)
{
	char	token;
	t_i		i;

	init_iterators(&i);
	all->cmd[i.c].name = ft_strdup(str[i.s]);
	all->cmd[i.c].path = get_path(all->path, str[i.s], 3);
	if (!all->cmd[i.c].path)
		all->cmd[i.c].path = ft_strdup(str[i.s]);
	all->cmd[i.c].args[i.a++] = ft_strdup(all->cmd[i.c].path);
	i.s++;
	while (str[i.s])
	{
		token = tokens(str[i.s]);
		if (token == PIPE || token == AMPERSAND)
			lexer_pipe(token, all, &i, str);
		else
		{
			lexer_check(token, all, &i, str);
		}
		i.s++;
	}
	return (CONTINUE);
}
