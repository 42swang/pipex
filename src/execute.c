/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:53:21 by swang             #+#    #+#             */
/*   Updated: 2021/10/06 21:16:04 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
환경변수 자르고 / 붙이기.
명령어 경로 + 커맨드 액세스 체크하고 실행가능하면 총경로 반환하는 함수만들기
명령어 실행하기
에러처리
*/

char	*get_path_str(char **envp)
{
	int		i;
	char	*path_str;

	i = 0;
	path_str = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path_str = ft_strdup(envp[i] + 5);
	if (path_str == 0)
	{
		ft_putstr_fd("Error\nFailed to find PATH in envp", 2);
		return (NULL);
	}
	return (path_str);
}

int check_cmd(char **path_arr, char **cmd_arr, char **envp)
{
	int	i;
	char	*tmp;
	char	*cmd_path;
	int	ret;

	i = 0;
	tmp = 0;
	cmd_path = 0;
	while (path_arr[i])
	{
		tmp = ft_strjoin(path_arr[i], "/" );
		if (tmp == 0)
		{
			ft_putstr_fd("Malloc_Error\n", 2);
			break ;
		}
		cmd_path = ft_strjoin(tmp, cmd_arr[0]);
		if (cmd_path == 0)
		{
			ft_putstr_fd("Malloc_Error\n", 2);
			break ;
		}
		free(tmp);
		if (access(cmd_path, X_OK | F_OK) == 0)
			ret = execve(cmd_path, cmd_arr, envp);
		else
		{
			free(cmd_path);
			i++;
		}
	}
	if (!cmd_path)
		free(cmd_path);
	return (-1);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	*path_str;
	char	**path_arr;
	char	**cmd_arr;

	path_str = get_path_str(envp);
	if (path_str == NULL)
		return ;
	path_arr = ft_split(path_str, ':');
	if (path_arr == NULL)
	{
		free(path_str);
		return ;
	}
	cmd_arr = ft_split_pipex(cmd, ' ');
	if (cmd_arr == NULL)
	{
		free(path_str);
		ft_free(path_arr);
		return ;
	}
	if (check_cmd(path_arr, cmd_arr, envp) == -1)
	{
		ft_putstr_fd("Error\nFailed to execute ", 2);
		ft_putstr_fd(cmd_arr[0], 2);
		ft_putstr_fd("\n", 2);
	}
	ft_free(path_arr);
	ft_free(cmd_arr);
}