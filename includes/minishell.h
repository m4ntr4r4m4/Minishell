/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:23:07 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/08 16:48:39 by ahammoud         ###   ########.fr       */
/*   Updated: 2022/11/04 11:00:46 by ahammoud         ###   ########.fr       */
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

# define AMPERSAND '1'
# define GREAT '2'
# define GREATAMPERSAND '3'
# define GREATGREAT '4'
# define LESS '5'
# define LESSLESS '6'
# define PIPE '7'
# define CONTINUE '8'

typedef struct s_pipe {
	int		fd[2];
	int		fdin;
	int		fdout;
}	t_pipe;

typedef struct	s_cmd
{
	int		num_args;
	char	*name;
	char	**args;
	char	**pathvar;
	char	*path;
	char	*file;
	char	**infile;
	char	**outfile;
	char 	*token;
}	t_cmd;

typedef struct	s_all
{
	t_cmd	*cmd;
	char 	*token_l;
	int 	token;
	size_t	size;
	t_pipe	*pipes;
	char	**path;
	int		n_cmd;
}	t_all;

typedef struct	s_iterators
{
	int	s;
	int	c;
	int	t;
	int	T;
	int	a;
	int	i;
	int	o;
}	t_i;

char	*expander(char *str);
void	leaks(void);
//void	freecmd(t_cmd *cmd);
void	freecmd(t_all *all);
void	freetable(char **str);

void	print_all(t_all *all);
int		executor(t_all *all, char **envp);
int		prexec(t_all *all, char **envp);
void	child1(t_all *all, char **envp, int i, size_t size);
void	cmd_init(t_cmd *cmd, int ac, char **av, char **envp);
char	*get_path(char **pathvar, char *cmd, int code);
char	*check_bin(char *binary, char *path, int ac);
char	**path_var(char **envp);
char	tokens(char *token);
char	**parser(char **str, int count, t_all *all);
char	*search_cmd(t_all *all, char **str);
void	init_structs(t_all *all, int count);
char lexer(char **str, t_all *all);
void	init_iterators(t_i *i);



#endif
