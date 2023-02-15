/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:15:01 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 18:52:43 by jvelasco         ###   ########.fr       */
/*   Updated: 2023/02/15 16:48:59 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dupfd(t_all *all, int id, size_t size)
{
	t_pipe	*pipes;

	pipes = all->pipes;
	if (all->cmd[id].token[2] == 54 || all->cmd[id].token[0] == LESS)
	{
		dup2(pipes[id].fdin, STDIN_FILENO);
		close(pipes[id].fdin);
	}
	if (id != 0 && all->cmd[id].token[2] == 0 && all->cmd[id].token[0] == 0)
	{
		dup2(pipes[id - 1].fd[0], STDIN_FILENO);
		close(pipes[id - 1].fd[0]);
	}
	if ((size_t) id < size)
	{
		dup2(pipes[id].fd[1], STDOUT_FILENO);
		close(pipes[id].fd[1]);
	}
	if (pipes[id].fdout != -1)
	{
		dup2(pipes[id].fdout, STDOUT_FILENO);
		close(pipes[id].fdout);
	}
}

void	closefiledes(t_pipe *var, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		close(var[i].fd[0]);
		close(var[i].fd[1]);
		i++;
	}
}

char	*get_line(int fd)
{
	char	*buff;
	char	*str;
	char	*tmp;
	int		i;

	buff = malloc(sizeof(char) * 2);
	str = malloc(sizeof(char) * 1);
	str[0] = '\0';
	buff[1] = '\0';
	i = read(fd, buff, 1);
	if (i <= 0)
	{
		free(buff);
		free(str);
		return (NULL);
	}
	while (buff[0] != '\n' && i != 0 && buff[0] != '\4')
	{
		tmp = ft_strjoin(str, buff);
		free(str);
		str = tmp;
		i = read(fd, buff, 1);
	}
	free(buff);
	return (str);
}

void	ft_here_doc_utils(t_all *all, size_t *x)
{
	int		i;
	int		fd;
	char	*input;

	fd = open("file.tmp", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		exit(0);
	i = -1;
	while (all->cmd[*x].eof[++i])
	{
		input = get_line(0);
		if (!input)
			break ;
		check_expanser(&input, all);
		while (ft_strncmp(input, all->cmd[*x].eof[i], \
			ft_strlen(input)))
		{
			ft_putendl_fd(input, fd);
			free(input);
			input = get_line(0);
			if (!input)
				break ;
			check_expanser(&input, all);
		}
	}
	close(fd);
	if (input)
		free(input);
}

void	ft_here_doc(t_all *all)
{
	char	**infile;
	size_t	x;
	int		i;

	x = -1;
	i = -1;
	while (++x < all->size)
	{
		if (all->cmd[x].token[2] == LESSLESS)
		{
			ft_here_doc_utils(all, &x);
			i = -1;
			infile = malloc(sizeof(char *) * (2));
			if (!infile)
				exit(0);
			infile[1] = NULL;
			infile[0] = ft_strdup("./file.tmp");
			freetable(all->cmd[x].infile);
			all->cmd[x].infile = infile;
		}
	}
}
