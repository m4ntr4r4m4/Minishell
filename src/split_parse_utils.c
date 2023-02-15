#include "minishell.h"

int	case_two(const char *s, int *i, char quote)
{
	int	len;
	int	sq;

	len = 0;
	sq = 0;
	while ((s[*i] != '\0'))
	{
		if (s[*i] == 32 && sq % 2 == 0)
			return (len);
		else if (s[*i] == 39)
			sq++;
		len++;
		(*i)++;
	}
	return (len);
}

int	case_vol(const char *s, int *i)
{
	int	len;
	int	cq;
	int	sq;

	len = 0;
	cq = 0;
	sq = 0;
	while ((s[*i] != '\0'))
	{
		if (s[*i] == 32 && (sq % 2 == 0 && cq % 2 == 0))
			return (len);
		else if (s[*i] == '"')
			sq++;
		else if (s[*i] == 39)
			cq++;
		len++;
		(*i)++;
	}
	return (len);
}
