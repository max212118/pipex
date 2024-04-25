/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:34 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/25 19:29:49 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex {
	char	***cmds;
	char	**paths;
	char	**envp;
	char	**av;
	int		infile;
	int		outfile;
	char	*current_cmd;
	int		tube[2];
	int		cmd_number;
}	t_pipex;

char	**find_paths(char **env);
void	set_commands(int ac, char **av, t_pipex *pipex);
char	*ft_strjoin_three(char const *s1, char const *s2, const char *s3);
void	free_pipex(t_pipex	*pipex);
void	free_pipex_paths(t_pipex *pipex);
void	free_pipex_cmds(t_pipex	*pipex);
char	*test_paths(t_pipex	*pipex, int index_cmd);
void	try_open_in(t_pipex *pipex);
void	try_open_out(t_pipex *pipex);
void	ft_execute(t_pipex	*pipex, int i);
void	ft_child_process(t_pipex *pipex, int i);
void	ft_parent_process(t_pipex *pipex, int i);
void	ft_pipex(int ac, t_pipex *pipex, char **envp);

#endif
