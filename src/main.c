/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:02:01 by swang             #+#    #+#             */
/*   Updated: 2021/10/07 15:26:46 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_arr_free(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_exit(int i, t_info *info, char **str)
{
	if (i == 0)
		exit(i);
	else if (i == 1)
	{	close(info->file1_fd);
		close(info->file2_fd);
		exit(0);
	}
	else
	{
		ft_arr_free(str);
		exit(0);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int	ret;

	ret = 0;
	if (argc != 5)
	{
		ft_putstr_fd("Error\ncheck parameter\n./pipex file1 \"cmd1\" \"cmd2\" file2\n", 2);
		return (0);
	}
	ret = pipex(argv, envp);
	return (ret);
}