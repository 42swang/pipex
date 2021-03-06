/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:50:04 by swang             #+#    #+#             */
/*   Updated: 2021/10/11 00:20:24 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_info(t_info *info)
{
	info->file1_fd = 0;
	info->file2_fd = 0;
	info->file1 = 0;
	info->file2 = 0;
	info->cmd1 = 0;
	info->cmd2 = 0;
}

int	pre_open(t_info *info, char **argv)
{
	info->file1 = argv[1];
	info->file2 = argv[4];
	info->cmd1 = argv[2];
	info->cmd2 = argv[3];
	info->file1_fd = open(info->file1, O_RDONLY);
	if (info->file1_fd == -1)
	{
		ft_putstr_fd("Error\nCan't open file1\n", 2);
		exit(0);
	}
	info->file2_fd = open(info->file2, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (info->file2_fd == -1)
	{
		ft_putstr_fd("Error\nCan't open file2\n", 2);
		close(info->file1_fd);
		exit(0);
	}
	return (0);
}

int	check_quotation_mark(char *str, int *i)
{
	char	c;
	int		idx;

	idx = *i;
	c = *str;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			(*i) += idx + 1;
			return (0);
		}
		(*i)++;
	}
	ft_putstr_fd("Error\nnot closed quotation mark\n", 2);
	return (-1);
}

int	find_start_end(char *s, int *i, int *start, char c)
{
	char	quote;

	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			*start = *i + 1;
			quote = s[*i];
			(*i)++;
			while (s[*i] != quote)
				(*i)++;
			return (*i);
		}
		else
			(*i)++;
	}
	return (*i);
}
