/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collecter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:14:17 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/30 20:52:14 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_back(t_gc *gr, t_gc *new)
{
	t_gc	*tmp;

	if (!gr || !new)
		return ;
	tmp = gr;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_gc	*free_gc_list(t_gc *gr)
{
	t_gc	*tmp;

	while (gr)
	{
		tmp = gr;
		gr = gr->next;
		free(tmp->ptr);
		free(tmp);
	}
	return (NULL);
}

void	gr_t(void *str, int flag)
{
	static t_gc	*gr;
	t_gc		*new;

	if (str)
	{
		new = malloc(sizeof(t_gc));
		if (!new)
		{
			gr = free_gc_list(gr);
			return ;
		}
		new->ptr = str;
		new->next = NULL;
		if (!gr)
			gr = new;
		else
			add_back(gr, new);
	}
	else
	{
		gr = free_gc_list(gr);
		if(flag)
			exit(2); //? free env
	}
}
