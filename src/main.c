/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:02:01 by swang             #+#    #+#             */
/*   Updated: 2021/10/11 00:22:26 by swang            ###   ########.fr       */
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

int	main(int argc, char *argv[], char **envp)
{
	int	ret;

	ret = 0;
	if (argc != 5)
	{
		ft_putstr_fd("Error\ncheck parameter\n", 2);
		ft_putstr_fd("./pipex file1\"cmd1\" \"cmd2\" file2\n", 2);
		return (0);
	}
	ret = pipex(argv, envp);
	return (ret);
}
