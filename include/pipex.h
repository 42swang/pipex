/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:01:49 by swang             #+#    #+#             */
/*   Updated: 2021/10/06 22:34:16 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef	struct s_info
{
	int		file1_fd;
	int		file2_fd;
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	*cmd2;
}	t_info;

/* main*/
int		main(int argc, char *argv[], char **envp);

/* pipex utils */
int		first_open(t_info *info, char **argv);
void	init_info(t_info *info);
void	ft_free(char **str);
void	ft_exit(int i);
int	check_quotation_mark(char *str, int *i);

char	**ft_split_cmd(char const *s, char c);

/* pipex */
int		pipex(char **argv, char **envp);
void	child(t_info *info, int *pipe_fd, char **envp);
void	redirect_child(t_info *info, int *pipe_fd);
void	parent(t_info *info, int *pipe_fd, char **envp);
void	redirect_parent(t_info *info, int *pipe_fd);

/* execute */
void	execute_cmd(char *cmd, char **envp);
char	*get_path_str(char **envp);
char	*check_cmd(char **path_arr, char *cmd);

#endif