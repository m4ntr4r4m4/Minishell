/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:41:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/01 16:38:22 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	word(char *str, char c)
{
	int	i;
	int	wc;
	int	quote;

	i = 0;
	quote = 0;
	wc = 0;
	if (str[i] != c && str[i] != '\0')
		wc++;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		if (str[i + 1] && str[i] == c && (str[i + 1] != c) && quote % 2 == 0)
			wc++;
		i++;
	}
	return (wc);
}

static	int	ft_tr(const char *s, int c, int *quote, int *i)
{
	int	len;

	len = 0;
	while (((s[*i] != c || (*quote % 2) != 0) && s[*i] != '\0'))
	{
		(*i)++;
		if (s[*i] == '"')
		{
			len++;
			*quote+=1;
		}
		len++;
	}
	return (len);
}

int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			while (str[++i] != '"')
				count++;
		}
		else if (str[i] == 39)
		{
			while (str[++i] != 39)
				count++;
		}
		else
			count++;
	}
	return (count);
}

char	*fill_str(char *str, char *new)
{
	int		x;
	int		i;

	x = 0;
	i = -1;
	while (str[++i])
	{	
		if (str[i] == 39)
		{
			while(str[++i] != 39)
				new[x++] = str[i];
		}
		else if (str[i] == '"')
		{
			while(str[++i] != '"')
				new[x++] = str[i];
		}
		else
			new[x++] = str[i];
	}
	free(str);
	return (new);
}

static char *delete_quotes(char *str)
{
	int		count;
	char	*new;
	
	count = count_quotes(str);
	new = malloc(count + 1);
	if (!new)
		return (NULL);
	new[count] = '\0';
	new = fill_str(str,new);
	return new;
}


static char	**cpy(char **mots, char *s, int wc, char c)
{
	int			i;
	int			j;
	int			len;
	int			start;
	static int	quote;

	i = 0;
	j = 0;
	while (j < wc)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '"')
			quote++;
		start = i;
		len = ft_tr(s, c, &quote, &i);
		mots[j] = ft_substr(s, start, len);
		mots[j] = delete_quotes(mots[j]);
		j++;
	}
	mots[j] = 0;
	return (mots);
}

char	**ft_split_parse(char *s, char c)
{
	char	**mots;
	int		wc;

	if (!s)
		return (NULL);
	wc = word(s, c);
	mots = malloc(sizeof(char *) * (wc + 1));
	if (!mots)
		return (0);
	mots = cpy(mots, s, wc, c);
	return (mots);
}

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
	else if (token == GREAT)
	{
		i->c_o = 1;
		all->cmd[i->c].token[1] = token;
		all->cmd[i->c].outfile[i->o++] = ft_strdup(str[++i->s]);
	}
	else if (token == GREATGREAT)
		all->cmd[i->c].token[3] = token;
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
	all->token_l[i->T++] = token;
	all->cmd[++i->c].name = ft_strdup(str[++i->s]);
	all->cmd[i->c].path = get_path(all->path, str[i->s], 3);
	if (!all->cmd[i->c].path)
		all->cmd[i->c].path = ft_strdup(str[i->s]);
	all->cmd[i->c].args[i->a++] = ft_strdup(all->cmd[i->c].path);
}

/* READ DE COMMAND AND FILL THE STRUCT */
char lexer(char **str, t_all *all)
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
	while(str[i.s])
	{
		token = tokens(str[i.s]);
		if (token == PIPE || token == AMPERSAND)
		{
			lexer_pipe(token, all, &i, str);
					}
		else
			lexer_check(token, all, &i, str);
		i.s++;
	}
	return (CONTINUE);
}

void	search_cmd(t_all *all, char **str)
{
	int		x;
	int		bol;
	char	token;

	x = 0;
	all->size = 0;
	bol = 1;
	while (str[x])
	{
		token = tokens(str[x]);
		if (bol)
		{
			all->size++;
			bol = 0;
		}
		else if (token == PIPE || token == AMPERSAND)
			bol = 1;
		x++;
	}
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
		if (token == CONTINUE && bol)
			bol = 0;
		else if (!bol && token == CONTINUE)
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
	all->s_eof = 0;
	i = all->i_f;
	while(str[++i])
	{
		token = tokens(str[i]);
		if (token == LESS)
			all->s_i++;
		else if (token == LESSLESS)
			all->s_eof++;
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
		return;
	all->token_l = malloc(sizeof(int) * (all->size - 1));
	if (!all->token_l)
		return;
	while ((size_t)++x < all->size)
	{
		if (!init_fill(x, str, all, -1))
			return ;
	}
}

int	check_quotes(char *str)
{
	int	y;

	y = -1;
	while (str[++y])
	{
		if (str[y] == 34)
		{
			while (str[++y] && str[y] != 34);
			if (!str[y])
				return	(0);
		}
		else if (str[y] == 39)
		{
			while (str[++y] && str[y] != 39);
			if (!str[y])
				return	(0);
		}
		else if (str[y] == 59 || str[y] == 92)
			return (0);
	}
	return	(1);
}

/* add a space on the mark and return all the str concatenated */ 
int	cpy_str(char **str, int y)
{
	const int	len = ft_strlen(*str);
	char		*newstr;
	
	newstr = malloc(sizeof(char) * (len + 2));
	if (!newstr)
		return (0);
	newstr[len + 1] = '\0';
	ft_memcpy(newstr, *str, y);
	newstr[y] = ' ';
	ft_memcpy(&newstr[y + 1], &(*str)[y], len - y);
	free(*str);
	*str = newstr;
	return (1);
	/* return (newstr); */
}

int	check_spaces(char **temp)
{
	int		y;
	char	token;
	int		vol;
	char	*str;

	str = *temp;
	vol = 0;
	y = -1;
	while (str[++y] != '\0')
	{
		token = token_l(str[y]);
		if (token != CONTINUE)
		{
			if (token_l(str[y + 1]) != CONTINUE)
			{
				y++;
				vol++;
			}
			if (str[y]) 
			{
				y++;
				if (!cpy_str(&str, y - (vol + 1)))
					return (0);
				if (!cpy_str(&str, y + 1))
					return (0);
				if (str[y] == '\0')
					return (1);
			}
			vol = 0;
		}
	}
	*temp = str;
	return (1);
}


void	check_expanser(char **str, t_all *all)
{
	int		i;
	char	*rd;

	rd = *str;
	i = -1;
	while (rd[++i] == '\0')
	{
		if (rd[i] == 39)
		{
			i++;
			while (rd[i] != 39)
				i++;
		}
		if (rd[i] == '$')
		{
			expander(rd, all);
			*str = rd;
		}
	}
}


int	check_token(char token, char prev, char str, int count)
{
	if (prev != CONTINUE)
	{
		if (token != prev || str != CONTINUE)
			return	(0);
	}
	else if (!count)
		return	(0);
	return	(1);
}

int	check_tokens(char *str)
{
	int		i;
	char	token;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		token = token_l(str[i]);
		if (token != CONTINUE)
		{
			if (!check_token(token, token_l(str[i - 1]), token_l(str[i + 1]), count))
				return (0);
			count = 0;
		}
		else if (str[i] != 32)
			count = 1;
	}
	if (!count)
		return	(0);
	return	(1);
}

int	check_error(char **rd, t_all *all)
{
	if (!check_tokens(*rd))
		return	(0);
	if (!check_spaces(rd))
		return	(0);
	if (!check_quotes(*rd))
		return	(0);
	return	(1);
}

int	parser(char **rd, t_all *all)
{
	char	**str;

	if (check_error(rd, all))
	{
		check_expanser(rd, all);
		/* CHECK ERRORS AND FILL SIZES*/
		str = ft_split_parse(*rd,' ');
		/* INICIALICE */ 
		init_structs(all, str);
		/* LEXER */ 
		lexer(str, all);
		/* PRINT */
		/* print_all(all); */
		freetable(str);
		/* fprintf(stderr,"rd %s\n", rd); */
		/* return	(1); */
		return (1);
	}
	return	(0);
}

char token_l(char token)
{
	if (token == 62)
		return	(GREAT);
	else if (token == 60)
		return	(LESS);
	else if (token == 124)
		return	(PIPE);
	else if (token == 38)
		return	(AMPERSAND);
	else 
		return	(CONTINUE);
}

/* enlaza los simbolos con comandos para que entienda el parser y los add a la tabla */
char tokens(char *token)
{
	if (!strcmp(token, ">"))
		return	(GREAT);
	else if (!strcmp(token, "<"))
		return	(LESS);
	else if (!strcmp(token, "<<"))
		return	(LESSLESS);
	else if (!strcmp(token, ">>"))
		return	(GREATGREAT);
	else if (!strcmp(token, ">&"))
		return	(GREATAMPERSAND);
	else if (!strcmp(token, "|"))
		return	(PIPE);
	else if (!strcmp(token, "&"))
		return	(AMPERSAND);
	else
		return	(CONTINUE);
}
