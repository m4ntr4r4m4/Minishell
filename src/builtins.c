/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:25:22 by ahammoud          #+#    #+#             */
/*   Updated: 2022/12/21 21:51:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_echo(char *str, int flag)
{
	if (!flag)
		printf("%s",str);
	else
		printf("%s\n",str);
}

int		ft_cd(char *path)
{
	return (chdir(path));
}

void	ft_pwd()
{
	char *buff;

	buff = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(buff, PATH_MAX) == NULL)
		perror("getcwd() error");
	ft_echo(buff, 1);
	free(buff);
}

void	ft_export(char *str)
{





}

int	main(void)
{
	char *cmd = "echo";
	char *args = "hello there!";

	ft_pwd();

}
