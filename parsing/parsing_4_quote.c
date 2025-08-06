/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:42:18 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/04 14:11:55 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_with_sep(const char *str, const char *sep, char *res)
{
	int	sep_len;
	int	i;
	int	j;
	int	k;

	sep_len = ft_strlen(sep);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		{
			k = 0;
			while (k < sep_len)
				res[j++] = sep[k++];
		}
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
}

char	*replace_spaces_with_sep(const char *str, const char *sep)
{
	int		space_count;
	int		len;
	int		new_len;
	char	*res;

	space_count = 0;
	if (!str || !sep)
		return (NULL);
	len = ft_strlen(str);
	if (!ft_strlen(sep) || only_spaces(str))
		str = sep;
	new_len = len * (ft_strlen(sep) - 1);
	res = malloc(new_len + 1);
	gr_t(res, 0);
	if (!res)
		return (NULL);
	copy_with_sep(str, sep, res);
	return (res);
}

char	*expand_dollar_token(t_shell *shell, int *i, char **token, int *flag)
{
	char	*exp;
	char	*part;

	exp = varible_ex(shell, i, token, flag);
	if (!exp)
		return (NULL);
	if (exp[0] != '\0' && !shell->flag_ex)
		part = replace_spaces_with_sep(exp, shell->rend.rnd_1);
	else if (*flag && !shell->flag_ex)
		part = ft_strdup(shell->rend.rnd_2);
	else
		part = ft_strdup(exp);
	return (part);
}
