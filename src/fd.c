/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:15:01 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/26 20:10:54 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dupfd(t_all *all, int id, size_t size)
{
	t_pipe	*pipes;

	pipes = all->pipes;
	//if ((id == 0 && pipes[id].fdin != -1))
	if (all->cmd[id].token[2] == 54 || all->cmd[id].token[0] == LESS) 
	{
		dup2(pipes[id].fdin, 0);
//		close(pipes[id].fd[0]);
		close(pipes[id].fdin);
	}
//	if (id > 0)
	if (all->cmd[id].token[2] == 0 && all->cmd[id].token[0] == 0) 
	{

			dup2(pipes[id - 1].fd[0], 0);
			close(pipes[id - 1].fd[0]);
	}
	if ((size_t) id < size)
	{
		dup2(pipes[id].fd[1], 1);
		close(pipes[id].fd[1]);
	}
	if ((size_t) id == size && pipes[id].fdout != -1)
	{
		dup2(pipes[id].fdout, 1);
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
	if (i == -1)
	{
		free(buff);
		free(str);
		return (NULL);
	}
	while (buff[0] != '\n' && i != 0)
	{
		tmp = ft_strjoin(str, buff);
		free(str);
		str = tmp;
		i = read(fd, buff, 1);
	}
	free(buff);
	return (str);
}

void	ft_here_doc(t_all *all)
{
	int		fd;
	char	*input;
	char	**infile;
	size_t	x;
	int	i;

	x = -1;
	i = -1;

//	while (all->cmd[x].token[2] != LESSLESS)
//
	while (++x < all->size)
	{
//			fprintf(stderr,"X:  %zu\n", x);
		if (all->cmd[x].token[2] == LESSLESS)
		{
			fd = open("file.tmp", O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (fd < 0)
				exit(0);

			while (all->cmd[x].eof[++i])
			{
				input = get_line(0);
				while (ft_strncmp(input, all->cmd[x].eof[i], \
					ft_strlen(all->cmd[x].eof[i])))
				{
					ft_putendl_fd(input, fd);
					free(input);
					input = get_line(0);
				}
			}
//			fprintf(stderr,"catched eof %zu %zu\n", x, all->size);
			close(fd);
			if (input)
				free(input);
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
//	fprintf(stderr,"out of read heredoc end \n");
}
