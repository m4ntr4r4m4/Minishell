#include "../includes/minishell.h"
#include "libft/ft_split.c"
#include "libft/ft_substr.c"
#include "libft/ft_strlen.c"
#include "libft/ft_print_table.c"
#include "libft/ft_putstr_fd.c"
#include "libft/ft_putchar_fd.c"

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
		if (strcmp(token, "CONTINUE") != 0)
			str[i] = token;
		i++;
	}
	return (str);
}

/* crea la tabla de comandos */
/* char **parser(char **str) */
/* { */

/* } */

#define AMPERSAND '&'

/* enlaza los simbolos con comandos para que entienda el parser y los add a la tabla */
int tokens(char *token)
{
	if (!strcmp(token, ">"))
		return GREAT;
	else if (!strcmp(token, "<"))
		return LESS;
	else if (!strcmp(token, ">>"))
		return GREATGREAT;
	else if (!strcmp(token, ">&"))
		return GREATGREAT;
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
	atexit(leaks);
	while(1)
	{
		new = ft_split(rd = readline("$:"), ' ');
		lexer(new);
		ft_print_table(new, 1);
		free(rd);
		freetable(new);


	}
	return 0;
}
