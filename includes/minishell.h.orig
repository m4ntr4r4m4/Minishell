/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:23:07 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/01 16:37:55 by ahammoud         ###   ########.fr       */
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
# include <signal.h>

# define AMPERSAND '1'
# define GREAT '2'
# define GREATAMPERSAND '3'
# define GREATGREAT '4'
# define LESS '5'
# define LESSLESS '6'
# define PIPE '7'
# define CONTINUE '8'
# define GOOD "GOOD"

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
	char	**infile;
	char	**outfile;
	char	**eof;
	int		*token;
	int		check;
	int		n_tokens; /*number of tokens */
	int		builtins;
}	t_cmd;

typedef struct	s_all
{
	t_cmd	*cmd;
	int 	*token_l; /* tokens for split cmds */
	size_t	size; /* size cmd for init */
	t_pipe	*pipes;
	char	**path;
	char	*pwd;
	int		s_t; /* size token for init */
	int		s_i; /* size inf for init */
	int		s_o; /* size outf for init */
	int		i_a; /* iterator args for init */
	int		i_t; /* iterator token for init */
	int		i_f; /* iterator file for init */
	int		s_eof; /* iterator file for init */
	char	**myenv;
	int		exit_var;
}	t_all;

typedef struct	s_iterators
{
	int	s; /* lexer iterator string */
	int	c; /* lexer iterator cmd */
	int	t; /* lexer iterator all->cmd.token_l*/
	int	T; /* lexer iterator all->token_l */
	int	a; /* lexer iterator arg */
	int	i; /* lexer iterator inf */
	int	o; /* lexer iterator outf */
	int	c_i; /* lexer checker inf */
	int	eof; /* lexer checker lessless */
	int	c_o; /* lexer checker outf */
}	t_i;

static 	int		sig_mini;
void	leaks(void);
void	ft_export(char *st, t_all *all);
size_t	ft_get_size(char **arr);
char	*ft_mygetenv(char *str, t_all *all);
void	ft_env_init(char **envp, t_all *all);
char	*expander(char **str, t_all *all);
void	freecmd(t_all *all);
void	freetable(char **str);
void	dupfd(t_all *all, int id, size_t size);
void	closefiledes(t_pipe *var, size_t size);
char	*get_line(int fd);
void	ft_here_doc(t_all *all);
void	print_all(t_all *all);
void		executor(t_all *all, char **envp);
int		prexec(t_all *all, char **envp);
void	child1(t_all *all, char **envp, int i, size_t size);
char	*get_path(char **pathvar, char *cmd, int code);
char	*check_bin(char *binary, char *path, int ac);
char	**path_var(char **envp);
	/* lexer.c */
char	tokens(char *token);
int		parser(char **rd, t_all *all);
void	search_cmd(t_all *all, char **str);
void	init_structs(t_all *all, char **str);
char	lexer(char **str, t_all *all);
void	init_iterators(t_i *i);
void	search_files(t_all *all,char **str);
int		search_arg(t_all *all,char **str);
int		search_token(t_all *all,char **str);
int		check_spaces(char **str);
char	token_l(char token);
char	**ft_split_parse(char *s, char c);
int		check_error(char	**rd, t_all	*all);
int		check_tokens(char *str);
int		check_quotes(char *str);
int		cpy_str(char **str, int y);
int		count_quotes(char *str);
void	lexer_pipe(char token, t_all *all, t_i *i, char **str);
void	lexer_check(char token, t_all *all, t_i *i, char **str);
void	check_expanser(char **str, t_all *all);
int		add_space(char **str, int *y);
int		word(char *str, char c);
void	word_iterate(char *str, int *i, char c, int *wc);
char	**cpy(char **mots, char *s, int wc, char c);
int		ft_tr(const char *s, int c, char quote, int *i);
char	*delete_quotes(char *str);
void	check_builtins(t_all *all);
#endif
