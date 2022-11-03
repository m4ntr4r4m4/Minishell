#include "../includes/minishell.h"
#include "libft/ft_split.c"
#include "libft/ft_substr.c"
#include "libft/ft_strlen.c"

static char *tokens(char *tokens);
/* lee el comando, busca los tokens y se lo pasa al parser */
char **lexer(char **str)
{
	char	*token;
	int		i;

	i = 0;
	while(str[i])
	{
		token = tokens(str[i]);
		if (token != "CONTINUE")
			str[i] = token;
		i++;
	}
	return (str);
}

/* crea la tabla de comandos */
/* char **parser(char **str) */
/* { */

/* } */

/* enlaza los simbolos con comandos para que entienda el parser y los add a la tabla */
char *tokens(char *token)
{
	if (!strcmp(token, ">"))
		return "GREAT";
	else if (!strcmp(token, "<"))
		return "LESS";
	else if (!strcmp(token, ">>"))
		return "GREATGREAT";
	else if (!strcmp(token, ">&"))
		return "GREATGREAT";
	else if (!strcmp(token, "|"))
		return "PIPE";
	else if (!strcmp(token, "&"))
		return "AMPERSAND";
	else
		return "CONTINUE";
}

int	main(int argc, char **argv)
{
	char *rd;
	char **new;

	while(1)
	{
		new = ft_split(readline("$:"), ' ');
		lexer(new);
		while (*new)
			printf("%s", *new++);
	}
	return 0;
}
