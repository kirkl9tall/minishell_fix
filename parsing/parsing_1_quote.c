/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:15:00 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/04 14:12:39 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_token(int *i, t_shell *shell, char **token)
{
	char	*first;
	int		flag;
	int		err;

	flag = 0;
	first = analys_token(i, shell, &flag);
	err = 0;
	if (flag)
		err = 1;
	if (!err && first)
	{
		if (join(token, first))
			err = 1;
	}
	return (err);
}

static int	handle_split_tokens_loop(char **splits, int count, t_shell *shell)
{
	int		k;
	char	*dup;

	k = 0;
	while (k < count)
	{
		if (splits[k][0] != '\0')
		{
			if (add_token_to_list(&shell->token_list, splits[k], 1,
					shell->rend.flag))
				return (1);
		}
		else
		{
			dup = ft_strdup(shell->rend.rnd_1);
			if (!dup)
				return (1);
			if (add_token_to_list(&shell->token_list, dup, 1, shell->rend.flag))
				return (1);
		}
		k++;
	}
	return (0);
}

static int	handle_split_tokens(char *token, t_shell *shell)
{
	int		count;
	char	**tmp;
	char	**splits;

	count = 0;
	tmp = split_by_custom_separator(token, shell->rend.rnd_1, &count);
	splits = merge_tokens_if_rnd2(tmp, &count, &shell->rend);
	if (!splits)
		return (1);
	return (handle_split_tokens_loop(splits, count, shell));
}

int	lexical(int *i, t_shell *shell)
{
	char	*token;

	token = NULL;
	if (build_token(i, shell, &token))
		return (1);
	if (token)
	{
		if (ft_strstr(token, shell->rend.rnd_1) || ft_strstr(token,
				shell->rend.rnd_2))
		{
			check_ambiguous(token, &shell->rend, &shell->rend.flag);
			if (handle_split_tokens(token, shell))
				return (1);
		}
		else
		{
			if (add_token_to_list(&shell->token_list, token, 1, 0))
				return (1);
		}
	}
	return (0);
}
