#include "minishell.h"

int	ft_tr(const char *s, char quote, int *i)
{
	int	len;
	int	vol;
	int	cq;
	int	sq;

	len = 0;
	cq = 0;
	vol = 0;
	sq = 0;
	if (quote == ' ')
		vol = 1;
	while ((s[*i] != '\0'))
	{
		if (s[*i] == quote && vol)
			return (len);
		if ((sq && s[*i] == 32) || (s[*i] == 32 && cq == 2))
			return (len);
		if (cq == 1 && s[*i] == quote && s[*i + 1] != 32)
			sq = 1;
		else if (s[*i] == quote)
			cq++;
		len++;
		(*i)++;
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
			while (str[++i] != 39)
				new[x++] = str[i];
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
				new[x++] = str[i];
		}
		else
			new[x++] = str[i];
	}
	free(str);
	return (new);
}

char	*delete_quotes(char *str)
{
	int		count;
	char	*new;

	count = count_quotes(str);
	new = malloc(count + 1);
	if (!new)
		return (NULL);
	new[count] = '\0';
	new = fill_str(str, new);
	return (new);
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
