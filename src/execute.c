/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:53:21 by swang             #+#    #+#             */
/*   Updated: 2021/10/07 17:02:58 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_arr;
	char	*cmd_path;

	cmd_arr = ft_split_cmd(cmd, ' ');
	if (cmd_arr == NULL)
	{
		ft_putstr_fd("Error : Failed to make cmd_arr.", 2);
		return (-1);
	}
	cmd_path = get_cmd_path(envp, cmd_arr[0]);
	if (cmd_path == NULL)
	{
		ft_arr_free(cmd_arr);
		ft_putstr_fd("Error : Failed to execute cmd", 2);
		return (-1);
	}
	execve(cmd_path, cmd_arr, envp);
	free(cmd_path);
	ft_arr_free(cmd_arr);
	return (-1);
}
