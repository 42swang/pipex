/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:56:20 by swang             #+#    #+#             */
/*   Updated: 2021/10/07 17:06:10 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_access_path(char **path_arr, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (path_arr[i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		if (tmp == 0)
			break ;
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (path == 0)
			break ;
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		else
			i++;
	}
	ft_putstr_fd("Can't access path.\n", 2);
	free (path);
	return (NULL);
}

static char	*get_path_str(char **envp)
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
	if (envp[i] == 0)
	{
		ft_putstr_fd("Can't find path in envp.\n", 2);
		return (NULL);
	}
	path_str = ft_strdup(envp[i] + 5);
	if (path_str == 0)
	{
		ft_putstr_fd("Failed to ft_strdup in get_path_str.\n", 2);
		return (NULL);
	}
	return (path_str);
}

char	*get_cmd_path(char **envp, char *cmd)
{
	char	*path_str;
	char	**path_arr;
	char	*access_path;

	path_str = get_path_str(envp);
	if (path_str == 0)
		return (NULL);
	path_arr = ft_split(path_str, ':');
	free(path_str);
	if (path_arr == 0)
		return (NULL);
	access_path = get_access_path(path_arr, cmd);
	return (access_path);
}
