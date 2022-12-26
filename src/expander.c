/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:17:24 by ahammoud          #+#    #+#             */
/*   Updated: 2022/12/26 12:00:39 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(char *str)
{
	char	*var;
	char	*s;
	bool	allocated;

	allocated = false;
	if (!str)
		return (NULL);
	if (str[0] == '$')
		str++;
	if (str[0] == '{')
	{
		s = ft_strtrim(str, "{");
		str = ft_strtrim(s, "}");
		allocated = true;
	}
	var = getenv(str);
	if (allocated)
	{
		free(str);
		free(s);
	}
	if (!var)
		return (NULL);
	return (var);
}

void	leaks(void)
{
	system("leaks executor");
}
