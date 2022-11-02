
/* lee el comando, busca los tokens y se lo pasa al parser */
char **lexer(char **str)
{
	/* 1. recorrer */
	/* 2. llamar a tokens */

	token = tokens(str[x]);
	if (token != CONTINUE)
	{
		/* copiar el str  con el nuevo token */
	}

}

/* crea la tabla de comandos */
char **parser(char **str)
{

}

enlaza los simbolos con comandos para que entienda el parser y los add a la tabla
char *tokens(char *tokens)
{
	if (tokens == ">")
		return GREAT;
	else if (tokens == "<")
		return LESS;
	else if (tokens == ">>")
		return GREATGREAT;
	else if (tokens == ">&")
		return GREATAMPERSAND;
	else if (tokens == "|")
		return PIPE;
	else if (tokens == "&")
		return AMPERSAND;
	else
		return CONTINUE;
}
