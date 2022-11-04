/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:23:07 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/04 12:19:33 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h> 
# include <termios.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <stdbool.h>


typedef struct s_pip {
	int		*fd;
	int		fdin;
	int		fdout;
}	t_pip;

typedef struct	s_cmd
{
	int		num_args;
	char	*name;
	char	**args;
	char	**pathvar;
	char	*path;
	char	*file;
	int 	token;
}	t_cmd;

typedef struct	s_all
{
	t_cmd	*cmd;
	int token;
	size_t	size;
	t_pip	pipes;
}	t_all;

char	*expander(char *str);
void	leaks(void);
//void	freecmd(t_cmd *cmd);
void	freecmd(t_all *all);

int		executor(t_all *all, char **envp);
int		prexec(t_all *all, char **envp);
void	child1(t_cmd *cmd, char **envp);
void	cmd_init(t_cmd *cmd, int ac, char **av, char **envp);
char	*get_path(char **pathvar, char *cmd, int code);
char	*check_bin(char *binary, char *path, int ac);
char	**path_var(char **envp);

void	freetable(char **str);

#endif
