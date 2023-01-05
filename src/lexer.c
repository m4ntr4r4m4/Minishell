/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:41:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/05 17:39:10 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"
#include "minishell.h"
/* TO DO */
/* finish env variable */
/* call ./executor should call t=he own path */
/* see if exists the file */
/* clean array for cases like cat > b > c only return cat > c or cat > b c return cat > b */ 

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
		if (str[i + 1] && str[i] == c && (str[i + 1] != c) && quote != 1)
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
			*quote+=1;
		len++;
	}
	return (len);
}

static char *delete_quotes(char *str)
{
	int		i;
	int		count;
	char	*new;
	int		x;
	
	count = 0;
	i = -1;
	while(str[++i])
	{
		if (str[i] != '"')
			count++;
	}
	new = malloc(count + 1);
	if (!new)
		return (NULL);
	i = -1;
	x = 0;
	new[count] = '\0';
	while (str[++i])
	{
		if (str[i] != '"')
			new[x++] = str[i];
	}
	free(str);
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
		{
			quote++;
			i++;
		}
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
}

/* READ DE COMMAND AND FILL THE STRUCT */
char lexer(char **str, t_all *all)
{
	char	token;
	t_i		i;

	init_iterators(&i);
	all->cmd[i.c].name = ft_strdup(str[i.s]);
	all->cmd[i.c].path = get_path(all->path, str[i.s++], 3);
	all->cmd[i.c].args[i.a++] = ft_strdup(all->cmd[i.c].path);
	while(str[i.s])
	{
		token = tokens(str[i.s]);
		if (token == PIPE || token == AMPERSAND)
		{
			all->token_l[i.T++] = token;
			all->cmd[++i.c].name = ft_strdup(str[++i.s]);
			all->cmd[i.c].path = get_path(all->path, str[i.s], 3);
			i.a = 0;
			all->cmd[i.c].args[i.a++] = ft_strdup(all->cmd[i.c].path);
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
		else if (token == CONTINUE)
			all->cmd[i.c].args[i.a++] = str[i.s];
		else
			all->cmd[i.c].token[i.t++] = token;
		i.s++;
	}
	return (CONTINUE);
}

char	*search_cmd(t_all *all, char **str, char **envp)
{
	int		x;
	int		bol;
	char	*path;
	char	token;

	x = 0;
	all->size = 0;
	bol = 1;
	path = NULL;
	while (str[x])
	{
		token = tokens(str[x]);
		if (str[x][0] == 36)
			{
				int i = 0;
				int size = ft_strlen(str[x]);
				char *new =  &str[x][1];
				while (envp[i] && ft_strncmp(envp[i], &str[x][1], size - 1))
					i++;
				if (envp[i] == NULL)
					return NULL;
				bol = 0;
			}
		else if (bol)
		{
			path = get_path(all->path, str[x], 3);
			if (path == NULL)
				return NULL;
			all->size++;
			bol = 0;
			free(path);
		}
		else if (token == PIPE || token == AMPERSAND)
			bol = 1;
		x++;
	}
	return GOOD;
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
	int			n_q;

	all->s_t = 0;
	n_q = 0;
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
	if (all->size == 0)
		all->size = 1;
	all->cmd = malloc(sizeof(*(all->cmd)) * all->size);
	if (!all->cmd)
		exit(0);
	all->token_l = malloc(sizeof(int) * (all->size - 1));
	if (!all->token_l)
		exit(0);
	while (++x < all->size)
	{
		all->cmd[x].token = malloc(sizeof(int) * search_token(all, str));
		if (!all->cmd[x].token)
			exit(0);
		all->cmd[x].n_tokens = all->s_t;
		all->cmd[x].args = malloc(sizeof(char *) * (search_arg(all, str) + 1));
		if (!all->cmd[x].args)
			exit(0);
		/* printf("%d\n", all->s_t); */
		all->cmd[x].args[all->s_t] = NULL;
		search_files(all, str);
		/* printf("%d %d\n", all->s_i, all->s_o); */
		all->cmd[x].outfile = malloc(sizeof(char *) * (all->s_o + 1));
		if (!all->cmd[x].outfile)
			exit(0);
		all->cmd[x].outfile[all->s_o] = NULL;
		all->cmd[x].infile = malloc(sizeof(char *) * (all->s_i + 1));
		if (!all->cmd[x].infile)
			exit(0);
		all->cmd[x].infile[all->s_i] = NULL;
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

/* add a space on the mark and return all the str concatenated */ 
char *cpy_str(char *str, int y, char bit)
{
	const int	len = ft_strlen(str);
	char		*newstr;
	
	if (bit == '1')
	{
		newstr = malloc(sizeof(char) * (len + 3));
		if (!newstr)
			return (NULL);
		newstr[len + 2] = '\0';
		ft_memcpy(newstr, str, y);
		newstr[y] = ' ';
		newstr[y+1] = str[y];
		newstr[y+2] = ' ';
		ft_memcpy(&newstr[y + 3], &str[y+1], len - y);
	}
	else
	{
		newstr = malloc(sizeof(char) * (len + 2));
		if (!newstr)
			return (NULL);
		newstr[len + 1] = '\0';
		ft_memcpy(newstr, str, y);
		newstr[y] = ' ';
		ft_memcpy(&newstr[y + 1], &str[y], len - y);
	}
	free(str);
	return (newstr);
}

char	*check_spaces(char *str)
{
	int		y;
	char	token;
	int		vol;

	vol = 0;
	y = -1;
	while (str[++y])
	{
		token = token_l(str[y]);
		if (str[y] == 34)
		{
			y++;
			while (str[y] && str[y] != 34)
				y++;
			if (!str[y])
			{
				free(str);
				return NULL;
			}
		}
		else if (vol && str[y] == 32)
			vol = 0;
		else if (vol >= 1 && token == CONTINUE && str[y] != 32)
		{
			if (str[y - 2] != 32) 
				str = cpy_str(str, y - 1, '1');
			else
				str = cpy_str(str, y, '0');
			while(str[y] && token_l(str[y]) == CONTINUE && str[y] != 32)
				y++;
			vol = 0;
			while(str[y] && token_l(str[y]) == CONTINUE && str[y] != 32)
				y++;
			if (!str[y])
				break;
		}
		else if (token == GREAT && str[y - 1] != 32 && token_l(str[y - 1]) == CONTINUE)
		{
			str = cpy_str(str, y, '0');
			vol = 0;
			while(str[y] && token_l(str[y]) == CONTINUE && str[y] != 32)
				y++;
			if (!str[y])
				break;
		}
		else if (vol >= 2 && (token == token_l(str[y - 1])) ||
				vol && (token != token_l(str[y - 1])))
		{
			free(str);
			return NULL;
		}
		else if (token != CONTINUE)
			vol++;
	}
	return (str);
}

char	*check_error(t_all *all, char **str, char **envp)
{
	char *cmd;

	if (check_quotes(str) == NULL || check_simbols(str) == NULL)
		return NULL;
	cmd = search_cmd(all, str, envp);
	if (cmd == NULL)
		return NULL;
	/* free(cmd); */
	return GOOD;
}

char **parser(char *rd, t_all *all, char **envp)
{
	char	**str;
	int		i;

	/* CHECK ERRORS AND FILL SIZES*/
	str = ft_split_parse(rd,' ');
	if (check_error(all ,str, envp) == NULL)
	{
		all->size = 0;
		i = -1;
		while(str[++i])
			free(str[i]);
		free(str);
		return NULL;
	}
	/* INICIALICE */ 
	init_structs(all, str);
	/* LEXER */ 
	lexer(str, all);
	/* PRINT */
//	print_all(all);
	return str;
}

char token_l(char token)
{
	if (token == 62)
		return GREAT;
	else if (token == 60)
		return LESS;
	else if (token == 124)
		return PIPE;
	else if (token == 38)
		return AMPERSAND;
	else 
		return CONTINUE;
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
