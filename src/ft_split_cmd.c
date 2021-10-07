/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swang <swang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:28:28 by swang             #+#    #+#             */
/*   Updated: 2021/10/07 15:28:37 by swang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**ft_split_free(char **res, int res_i)
{
	while (res_i >= 0)
	{
		free(res[res_i]);
		res[res_i] = 0;
		res_i--;
	}
	free(res);
	res = 0;
	return (NULL);
}

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			if (s[i] == '\'' || s[i] == '\"')
			{
				if (check_quotation_mark((char *)s + i, &i) == -1)
					return (-1);
			}
			else
			{
				while (s[i] != c && s[i])
					i++;
			}
		}
	}
	return (count);
}

static char	**ft_make_res(char const *s, char c, char **res, int c_word)
{
	int	i;
	int	start;
	int	end;
	int	res_i;
	char keep;

	i = 0;
	start = 0;
	end = 0;
	res_i = 0;
	while (res_i < c_word && s[i])
	{
		while (s[i] && s[i] == c)// ' '
			i++;
		start = i;
		while (s[i] && s[i] != c)
		{
			if(s[i] == '\'' || s[i] == '\"')
			{
				start = i + 1;
				keep = s[i++];
				while (s[i] != keep)
					i++;
				break ;
			}
			else
				i++;
		}		
		end = i - 1;
		res[res_i] = ft_substr(s, (unsigned int)start,
				(size_t)(end - start + 1));
		if (!res[res_i])
			return (ft_split_free(res, res_i));
		res_i++;
	}
	return (res);
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**res;
	int		c_word;

	if (s == 0)
		return (NULL);
	c_word = ft_count_word(s, c);
	if (c_word == -1)
		return (NULL);
	res = ft_calloc((size_t)c_word + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_make_res(s, c, res, c_word);
	return (res);
}
