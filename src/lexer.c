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

int	parser(char **rd, t_all *all)
{
	char	**str;

	if (check_error(rd, all))
	{
		printf("rd => %s\n", *rd);
		check_expanser(rd, all);
		printf("rd => %s\n", *rd);
		str = ft_split_parse(*rd, ' ');
		init_structs(all, str);
		lexer(str, all);
		check_builtins(all);
		print_all(all);
		freetable(str);
		return (1);
	}
	return (0);
}
