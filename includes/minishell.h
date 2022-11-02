/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:23:07 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/02 16:34:28 by ahammoud         ###   ########.fr       */
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

typedef struct	s_cmd
{
	int		num_args;
	char	*name;
	char	**args;
	char	**pathvar;
	char	*path;
}	t_cmd;

char	*expander(char *str);
void	leaks(void);
void	freecmd(t_cmd *cmd);
#endif
