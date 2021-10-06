/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:02:01 by swang             #+#    #+#             */
/*   Updated: 2021/10/06 22:29:36 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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