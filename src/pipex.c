/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:03:40 by swang             #+#    #+#             */
/*   Updated: 2021/10/11 00:23:52 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	redirect_parent(t_info *info, int *pipe_fd)
{
	if (dup2(pipe_fd[0], STDIN) == -1)
	{
		ft_putstr_fd("Error\nFailed to stdin redirect in parent process\n", 2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(info->file1_fd);
		close(info->file2_fd);
		exit(0);
	}
	if (dup2(info->file2_fd, STDOUT) == -1)
	{
		ft_putstr_fd("Error\nFailed to stdout redirect in parent process\n", 2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(info->file1_fd);
		close(info->file2_fd);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(info->file1_fd);
	close(info->file2_fd);
}

void	redirect_child(t_info *info, int *pipe_fd)
{
	if (dup2(info->file1_fd, 0) == -1)
	{
		ft_putstr_fd("Error : Failed to stdin redirect in child process\n", 2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(info->file1_fd);
		close(info->file2_fd);
		exit(0);
	}
	if (dup2(pipe_fd[1], 1) == -1)
	{
		ft_putstr_fd("Error : Failed to stdout redirect in child process\n", 2);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(info->file1_fd);
		close(info->file2_fd);
		exit(0);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(info->file1_fd);
	close(info->file2_fd);
}

void	parent(t_info *info, int *pipe_fd, char **envp)
{
	redirect_parent(info, pipe_fd);
	execute_cmd(info->cmd2, envp);
}

void	child(t_info *info, int *pipe_fd, char **envp)
{
	redirect_child(info, pipe_fd);
	execute_cmd(info->cmd1, envp);
}

int	pipex(char **argv, char **envp)
{
	int		fd[2];
	int		status;
	t_info	info;
	pid_t	pid;

	init_info(&info);
	if (pre_open(&info, argv) == -1)
		return (-1);
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error : Failed to fork\n", 2);
		return (-1);
	}
	else if (pid == 0)
		child(&info, fd, envp);
	else
	{
		waitpid(pid, &status, WNOHANG);
		parent(&info, fd, envp);
	}
	return (0);
}
