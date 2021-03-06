/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:01:49 by swang             #+#    #+#             */
/*   Updated: 2021/10/11 00:25:15 by swang            ###   ########.fr       */
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

typedef struct s_info
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
void	ft_arr_free(char **str);

/* pipex utils */
int		pre_open(t_info *info, char **argv);
void	init_info(t_info *info);
int		check_quotation_mark(char *str, int *i);
int		find_start_end(char *s, int *i, int *start, char c);
char	**ft_split_cmd(char const *s, char c);

/* pipex */
int		pipex(char **argv, char **envp);
void	child(t_info *info, int *pipe_fd, char **envp);
void	redirect_child(t_info *info, int *pipe_fd);
void	parent(t_info *info, int *pipe_fd, char **envp);
void	redirect_parent(t_info *info, int *pipe_fd);

/* execute */
void		execute_cmd(char *cmd, char **envp);
char	*get_cmd_path(char **envp, char *cmd);

#endif