/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:03:40 by swang             #+#    #+#             */
/*   Updated: 2021/10/06 20:28:45 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
/*

0. 선처리는 언제하지?
1. redirection
	-자식 : file1_fd-> 커맨드 -> pipe_fd[1]; (fd[0]은 닫아줘야함)
	-부모 : pipe_fd[0] -> 커맨드2 -> file2_fd; (fd[1] 닫아줘야함)
2. 파일경로, 커맨드 쓰기편하게 만든 다음에 access해보고 되면 바로 리턴해서 execve하기
*/

void	redirect_parent(t_info *info, int *pipe_fd)
{
	if (dup2(pipe_fd[0], STDIN) == -1)
	{
		ft_putstr_fd("Error\nFailed to stdin redirect in parent process\n", 2);
		close(info->file1_fd);
		close(info->file2_fd);
		ft_exit(0);
	}
	if (dup2(info->file2_fd, STDOUT) == -1)
	{
		ft_putstr_fd("Error\nFailed to stdout redirect in parent process\n", 2);
		close(info->file1_fd);
		close(info->file2_fd);
		ft_exit(0);
	}
	close(pipe_fd[1]);
	close(info->file2_fd);
}

void	parent(t_info *info, int *pipe_fd, char **envp)
{
	redirect_parent(info, pipe_fd);
	execute_cmd(info->cmd2, envp);
	//에러처리?,,
}

void	redirect_child(t_info *info, int *pipe_fd)
{
	if (dup2(info->file1_fd, 0) == -1)
	{
		ft_putstr_fd("Error\nFailed to stdin redirect in child process\n", 2);
		close(info->file1_fd);
		close(info->file2_fd);
		ft_exit(0);
	}
	if (dup2(pipe_fd[1], 1) == -1)// 프리오픈을 자식프로세스에서 열어서 그런가 제대로 듑되고있지않았음
	{
		ft_putstr_fd("Error\nFailed to stdout redirect in child process\n", 2);
		close(info->file1_fd);
		close(info->file2_fd);
		ft_exit(0);
	}
	close(pipe_fd[0]);
	close(info->file1_fd);
}

void	child(t_info *info, int *pipe_fd, char **envp)
{
	redirect_child(info, pipe_fd);
	execute_cmd(info->cmd1, envp);
	//에러처리?
}

int		pipex(char **argv, char **envp)
{
	int		fd[2];
	int		status;
	t_info	info;
	pid_t	pid;

	init_info(&info);
	if (first_open(&info, argv) == -1)
			return (-1);
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error\n Failed to fork\n", 2);
		return (-1);
	}
	else if (pid == 0)
		child(&info, fd, envp);
	else
	{
		waitpid(pid, &status, 0);
		parent(&info, fd, envp);
	}
	return (0);
}